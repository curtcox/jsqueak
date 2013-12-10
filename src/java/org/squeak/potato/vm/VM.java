/*
This work is a derivative of JSqueak (http://research.sun.com/projects/JSqueak).

Copyright (c) 2008  Daniel H. H. Ingalls, Sun Microsystems, Inc.  All rights reserved.

Portions copyright Frank Feinbube, Robert Wierschke.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
package org.squeak.potato.vm;

import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.io.FileInputStream;
import java.lang.reflect.Method;

import org.squeak.potato.*;
import org.squeak.potato.image.SqueakImage;
import org.squeak.potato.javainterop.JavaProxyObject;
import org.squeak.potato.objects.AbstractSqueakObject;
import org.squeak.potato.objects.SmallInteger;
import org.squeak.potato.objects.SpecialObjects;
import org.squeak.potato.objects.SqueakObject;
import org.squeak.potato.primitives.PrimitiveFailedException;
import org.squeak.potato.primitives.PrimitiveHandler;

import static org.squeak.potato.objects.SpecialObjectConstants.*;

/**
 * @author Daniel Ingalls
 *
 * @author Frank Feinbube
 * @author Robert Wierschke
 *
 * The virtual machinery for executing Squeak bytecode.
 */
public class VM {
	public static final int MAX_SENDS_TO_PRINT=30;
    int sendsPrinted=0;

	Logger logger=Logger.getLogger(getClass().getName());

    // static state:
    public SqueakImage image;
    PrimitiveHandler primHandler;
    public Object[] specialSelectors;
    // dynamic state:
    Object receiver;
    public SqueakObject activeContext;
    SqueakObject homeContext;
    public SqueakObject method;
    byte[] methodBytes;
    public int pc;
    public boolean success;
    private SqueakObject freeContexts;
    private SqueakObject freeLargeContexts;
    public int reclaimableContextCount; //Not #available, but how far down the current stack is recyclable

    public SqueakObject verifyAtSelector;
    public SqueakObject verifyAtClass;
    public boolean screenEvent = false;
    public int lowSpaceThreshold;

    public Stack stack;
    public MethodCache methodCache;
    public InterruptHandler interruptHandler;

    int byteCount = 0;
    FileInputStream byteTracker;
    int nRecycledContexts = 0;
    int nAllocatedContexts = 0;
    Object[] stackedReceivers = new Object[100];
    Object[] stackedSelectors = new Object[100];

    public VM(SqueakImage anImage) { // canonical creation

        SpecialObjects.init(anImage);
        stack = new Stack(this);
        methodCache = new MethodCache();
        interruptHandler = new InterruptHandler();

        image = anImage;
        image.bindVM(this);
        primHandler = new PrimitiveHandler(this);

        loadImageState();
        initVMState();
        loadInitialContext();
    }

    public void clearCaches() { // Some time store null above SP in contexts

        primHandler.clearAtCache();
        methodCache.clearMethodCache();
        freeContexts = SpecialObjects.nilObj;
        freeLargeContexts = SpecialObjects.nilObj;
    }

    private void loadImageState() {
        SqueakObject ssObj = SpecialObjects.getSpecialObject(splOb_SpecialSelectors);
        specialSelectors = ssObj.pointers;
    }

    private void initVMState() {
        interruptHandler.setPrimitiveHandler(primHandler);
        freeContexts = SpecialObjects.nilObj;
        freeLargeContexts = SpecialObjects.nilObj;
        reclaimableContextCount = 0;
        methodCache.initMethodCache();
    }

    private void loadInitialContext() {
        SqueakObject schedAssn = SpecialObjects.getSpecialObject(splOb_SchedulerAssociation);
        SqueakObject sched = schedAssn.fetchPointerNI(Constants.Assn_value);
        SqueakObject proc = sched.fetchPointerNI(Constants.ProcSched_activeProcess);
        activeContext = proc.fetchPointerNI(Constants.Proc_suspendedContext);
        fetchContextRegisters(activeContext);
        reclaimableContextCount = 0;
    }

    public void newActiveContext(SqueakObject newContext) {
        storeContextRegisters();
        activeContext = newContext; //We're off and running...

        fetchContextRegisters(newContext);
    }

    public void fetchContextRegisters(SqueakObject ctxt) {
        Object meth = ctxt.fetchPointer(Constants.Context_method);
        if (SmallInteger.isSmallInt(meth)) { //if the Method field is an integer, activeCntx is a block context

            homeContext = (SqueakObject) ctxt.fetchPointer(Constants.BlockContext_home);
            meth = homeContext.fetchPointerNI(Constants.Context_method);
        } else { //otherwise home==ctxt

            if (!SpecialObjects.isA(meth, splOb_ClassCompiledMethod)) {
                //meth = meth; // <-- break here
            }
            homeContext = ctxt;
        }
        receiver = homeContext.fetchPointer(Constants.Context_receiver);
        method = (SqueakObject) meth;
        methodBytes = (byte[]) method.bits;
        pc = decodeSqueakPC(ctxt.fetchInteger(Constants.Context_instructionPointer), method);
        if (pc < -1) {
            dumpStack();
        }
        stack.sp = decodeSqueakSP(ctxt.fetchInteger(Constants.Context_stackPointer));
    }

    public void storeContextRegisters() {
        //Save pc, sp into activeContext object, prior to change of context
        //   see fetchContextRegisters for symmetry
        //   expects activeContext, pc, sp, and method state vars to still be valid
        activeContext.setPointer(Constants.Context_instructionPointer, encodeSqueakPC(pc, method));
        activeContext.setPointer(Constants.Context_stackPointer, encodeSqueakSP(stack.sp));
    }

    public Integer encodeSqueakPC(int intPC, SqueakObject aMethod) {
        // Squeak pc is offset by header and literals
        // and 1 for z-rel addressing, and 1 for pre-increment of fetch
        return SmallInteger.smallFromInt(intPC + (((aMethod.methodNumLits() + 1) * 4) + 1 + 1));
    }

    public int decodeSqueakPC(Integer squeakPC, SqueakObject aMethod) {
        return SmallInteger.intFromSmall(squeakPC) - (((aMethod.methodNumLits() + 1) * 4) + 1 + 1);
    }

    public Integer encodeSqueakSP(int intSP) {
        // sp is offset by tempFrameStart, -1 for z-rel addressing
        return SmallInteger.smallFromInt(intSP - (Constants.Context_tempFrameStart - 1));
    }

    public int decodeSqueakSP(Integer squeakPC) {
        return SmallInteger.intFromSmall(squeakPC) + (Constants.Context_tempFrameStart - 1);
    }

    // INNER BYTECODE INTERPRETER:
    public int nextByte() {
        return methodBytes[++pc] & 0xff;
    }

    public void run() throws java.io.IOException {


    	logger.info("JSqueak "+Constants.VERSION);

        int b, b2;
        while (true) { //...Here's the basic evaluator loop...'
//        printContext();
//        byteCount++;
//        int b= nextByte();

            b = methodBytes[++pc] & 0xff;
            switch (b) { /* The Main Bytecode Dispatch Loop */

                // load receiver variable
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    stack.push(((SqueakObject) receiver).fetchPointer(b & 0xF));
                    break;

                // load temporary variable
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                    stack.push(homeContext.fetchPointer(Constants.Context_tempFrameStart + (b & 0xF)));
                    break;

                // loadLiteral
                case 32:
                case 33:
                case 34:
                case 35:
                case 36:
                case 37:
                case 38:
                case 39:
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                case 48:
                case 49:
                case 50:
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                case 56:
                case 57:
                case 58:
                case 59:
                case 60:
                case 61:
                case 62:
                case 63:
                    stack.push(method.methodGetLiteral(b & 0x1F));
                    break;

                // loadLiteralIndirect
                case 64:
                case 65:
                case 66:
                case 67:
                case 68:
                case 69:
                case 70:
                case 71:
                case 72:
                case 73:
                case 74:
                case 75:
                case 76:
                case 77:
                case 78:
                case 79:
                case 80:
                case 81:
                case 82:
                case 83:
                case 84:
                case 85:
                case 86:
                case 87:
                case 88:
                case 89:
                case 90:
                case 91:
                case 92:
                case 93:
                case 94:
                case 95:
                    stack.push(((SqueakObject) method.methodGetLiteral(b & 0x1F)).fetchPointer(Constants.Assn_value));
                    break;

                // storeAndPop rcvr, temp
                case 96:
                case 97:
                case 98:
                case 99:
                case 100:
                case 101:
                case 102:
                case 103:
                    ((SqueakObject) receiver).setPointer(b & 7, stack.pop());
                    break;
                case 104:
                case 105:
                case 106:
                case 107:
                case 108:
                case 109:
                case 110:
                case 111:
                    homeContext.setPointer(Constants.Context_tempFrameStart + (b & 7), stack.pop());
                    break;

                // Quick push constant
                case 112:
                    stack.push(receiver);
                    break;
                case 113:
                    stack.push(SpecialObjects.trueObj);
                    break;
                case 114:
                    stack.push(SpecialObjects.falseObj);
                    break;
                case 115:
                    stack.push(SpecialObjects.nilObj);
                    break;
                case 116:
                    stack.push(SmallInteger.smallFromInt(-1));
                    break;
                case 117:
                    stack.push(SmallInteger.smallFromInt(0));
                    break;
                case 118:
                    stack.push(SmallInteger.smallFromInt(1));
                    break;
                case 119:
                    stack.push(SmallInteger.smallFromInt(2));
                    break;

                // Quick return
                case 120:
                    doReturn(receiver, homeContext.fetchPointerNI(Constants.Context_sender));
                    break;
                case 121:
                    doReturn(SpecialObjects.trueObj, homeContext.fetchPointerNI(Constants.Context_sender));
                    break;
                case 122:
                    doReturn(SpecialObjects.falseObj, homeContext.fetchPointerNI(Constants.Context_sender));
                    break;
                case 123:
                    doReturn(SpecialObjects.nilObj, homeContext.fetchPointerNI(Constants.Context_sender));
                    break;
                case 124:
                    doReturn(stack.pop(), homeContext.fetchPointerNI(Constants.Context_sender));
                    break;
                case 125:
                    doReturn(stack.pop(), activeContext.fetchPointerNI(Constants.BlockContext_caller));
                    break;
                case 126:
                    nono();
                    break;
                case 127:
                    nono();
                    break;

                // Sundry
                case 128:
                    extendedPush(nextByte());
                    break;
                case 129:
                    extendedStore(nextByte());
                    break;
                case 130:
                    extendedStorePop(nextByte());
                    break;
                // singleExtendedSend
                case 131:
                    b2 = nextByte();
                    send(method.methodGetSelector(b2 & 31), b2 >> 5, false);
                    break;
                case 132:
                    doubleExtendedDoAnything(nextByte());
                    break;
                // singleExtendedSendToSuper
                case 133:
                    b2 = nextByte();
                    send(method.methodGetSelector(b2 & 31), b2 >> 5, true);
                    break;
                // secondExtendedSend
                case 134:
                    b2 = nextByte();
                    send(method.methodGetSelector(b2 & 63), b2 >> 6, false);
                    break;
                case 135:
                    stack.pop();
                    break;	// pop

                case 136:
                    stack.push(stack.top());
                    break;	// dup
                // push thisContext

                case 137:
                    stack.push(activeContext);
                    reclaimableContextCount = 0;
                    break;

                //Unused...
                case 138:
                case 139:
                case 140:
                case 141:
                case 142:
                case 143:
                    nono();
                    break;

                // Short jmp
                case 144:
                case 145:
                case 146:
                case 147:
                case 148:
                case 149:
                case 150:
                case 151:
                    pc += (b & 7) + 1;
                    break;
                // Short bfp
                case 152:
                case 153:
                case 154:
                case 155:
                case 156:
                case 157:
                case 158:
                case 159:
                    jumpIf(false, (b & 7) + 1);
                    break;
                // Long jump, forward and back
                case 160:
                case 161:
                case 162:
                case 163:
                case 164:
                case 165:
                case 166:
                case 167:
                    b2 = nextByte();
                    pc += (((b & 7) - 4) * 256 + b2);
                    if ((b & 7) < 4) {
                        interruptHandler.checkForInterrupts();  //check on backward jumps (loops)

                    }
                    break;
                // Long btp
                case 168:
                case 169:
                case 170:
                case 171:
                    jumpIf(true, (b & 3) * 256 + nextByte());
                    break;
                // Long bfp
                case 172:
                case 173:
                case 174:
                case 175:
                    jumpIf(false, (b & 3) * 256 + nextByte());
                    break;

                // Arithmetic Ops... + - < > <= >= = ~=    * / \ @ lshift: lxor: land: lor:
                case 176:
                    success = true;
                    if (!pop2AndPushIntResult(stackInteger(1) + stackInteger(0))) {
                        sendSpecial(b & 0xF);
                    }
                    break;	// PLUS +

                case 177:
                    success = true;
                    if (!pop2AndPushIntResult(stackInteger(1) - stackInteger(0))) {
                        sendSpecial(b & 0xF);
                    }
                    break;	// PLUS +

                case 178:
                    success = true;
                    if (!pushBoolAndPeek(stackInteger(1) < stackInteger(0))) {
                        sendSpecial(b & 0xF);
                    }
                    break;  // LESS <

                case 179:
                    success = true;
                    if (!pushBoolAndPeek(stackInteger(1) > stackInteger(0))) {
                        sendSpecial(b & 0xF);
                    }
                    break;  // GRTR >

                case 180:
                    success = true;
                    if (!pushBoolAndPeek(stackInteger(1) <= stackInteger(0))) {
                        sendSpecial(b & 0xF);
                    }
                    break;  // LEQ <=

                case 181:
                    success = true;
                    if (!pushBoolAndPeek(stackInteger(1) >= stackInteger(0))) {
                        sendSpecial(b & 0xF);
                    }
                    break;  // GEQ >=

                case 182:
                    success = true;
                    if (!pushBoolAndPeek(stackInteger(1) == stackInteger(0))) {
                        sendSpecial(b & 0xF);
                    }
                    break;  // EQU =

                case 183:
                    success = true;
                    if (!pushBoolAndPeek(stackInteger(1) != stackInteger(0))) {
                        sendSpecial(b & 0xF);
                    }
                    break;  // NEQ ~=

                case 184:
                    success = true;
                    if (!pop2AndPushIntResult(Arithmetics.safeMultiply(stackInteger(1), stackInteger(0)))) {
                        sendSpecial(b & 0xF);
                    }
                    break;  // TIMES *

                case 185:
                    success = true;
                    if (!pop2AndPushIntResult(Arithmetics.quickDivide(stackInteger(1), stackInteger(0)))) {
                        sendSpecial(b & 0xF);
                    }
                    break;  // Divide /

                case 186:
                    success = true;
                    if (!pop2AndPushIntResult(Arithmetics.mod(stackInteger(1), stackInteger(0)))) {
                        sendSpecial(b & 0xF);
                    }
                    break;  // MOD \\

                case 187:
                    success = true;
                    primHandler.primitiveMakePoint();
                    break;  // MakePt int@int

                case 188:
                    success = true; // Something is wrong with this one...
                /*if(!pop2AndPushIntResult(safeShift(stackInteger(1),stackInteger(0))))*/ sendSpecial(b & 0xF);
                    break; // bitShift:

                case 189:
                    success = true;
                    if (!pop2AndPushIntResult(Arithmetics.div(stackInteger(1), stackInteger(0)))) {
                        sendSpecial(b & 0xF);
                    }
                    break;  // Divide //

                case 190:
                    success = true;
                    if (!pop2AndPushIntResult(stackInteger(1) & stackInteger(0))) {
                        sendSpecial(b & 0xF);
                    }
                    break; // bitAnd:

                case 191:
                    success = true;
                    if (!pop2AndPushIntResult(stackInteger(1) | stackInteger(0))) {
                        sendSpecial(b & 0xF);
                    }
                    break; // bitOr:

                // at:, at:put:, size, next, nextPut:, ...
                case 192:
                case 193:
                case 194:
                case 195:
                case 196:
                case 197:
                case 198:
                case 199:
                case 200:
                case 201:
                case 202:
                case 203:
                case 204:
                case 205:
                case 206:
                case 207:
                    if (!primHandler.quickSendOther(receiver, b & 0xF)) {
                        sendSpecial((b & 0xF) + 16);
                    }
                    break;

                // Send Literal Selector with 0, 1, and 2 args
                case 208:
                case 209:
                case 210:
                case 211:
                case 212:
                case 213:
                case 214:
                case 215:
                case 216:
                case 217:
                case 218:
                case 219:
                case 220:
                case 221:
                case 222:
                case 223:
                    send(method.methodGetSelector(b & 0xF), 0, false);
                    break;
                case 224:
                case 225:
                case 226:
                case 227:
                case 228:
                case 229:
                case 230:
                case 231:
                case 232:
                case 233:
                case 234:
                case 235:
                case 236:
                case 237:
                case 238:
                case 239:
                    send(method.methodGetSelector(b & 0xF), 1, false);
                    break;
                case 240:
                case 241:
                case 242:
                case 243:
                case 244:
                case 245:
                case 246:
                case 247:
                case 248:
                case 249:
                case 250:
                case 251:
                case 252:
                case 253:
                case 254:
                case 255:
                    send(method.methodGetSelector(b & 0xF), 2, false);
                    break;
            }
        }
    }

    private void jumpIf(boolean condition, int delta) {
        Object top = stack.pop();
        if (top == (condition ? SpecialObjects.trueObj : SpecialObjects.falseObj)) {
            pc += delta;
            return;
        }
        if (top == (condition ? SpecialObjects.falseObj : SpecialObjects.trueObj)) {
            return;
        }
        stack.push(top); //Uh-oh it's not even a boolean (that we know of ;-).  Restore stack...

        send(SpecialObjects.getSpecialObject(splOb_SelectorMustBeBoolean), 1, false);
    }

    public void sendSpecial(int lobits) {
        send((SqueakObject) specialSelectors[lobits * 2],
                ((Integer) specialSelectors[(lobits * 2) + 1]).intValue(),
                false);
    }  //specialSelectors is  {...sel,nArgs,sel,nArgs,...)


    public void extendedPush(int nextByte) {
        int lobits = nextByte & 63;
        switch (nextByte >> 6) {
            case 0:
                stack.push(((SqueakObject) receiver).fetchPointer(lobits));
                break;
            case 1:
                stack.push(homeContext.fetchPointer(Constants.Context_tempFrameStart + lobits));
                break;
            case 2:
                stack.push(method.methodGetLiteral(lobits));
                break;
            case 3:
                stack.push(((SqueakObject) method.methodGetLiteral(lobits)).fetchPointer(Constants.Assn_value));
                break;
        }
    }

    public void extendedStore(int nextByte) {
        int lobits = nextByte & 63;
        switch (nextByte >> 6) {
            case 0:
                ((SqueakObject) receiver).setPointer(lobits, stack.top());
                break;
            case 1:
                homeContext.setPointer(Constants.Context_tempFrameStart + lobits, stack.top());
                break;
            case 2:
                nono();
                break;
            case 3:
                ((SqueakObject) method.methodGetLiteral(lobits)).setPointer(Constants.Assn_value, stack.top());
                break;
        }
    }

    public void extendedStorePop(int nextByte) {
        int lobits = nextByte & 63;
        switch (nextByte >> 6) {
            case 0:
                ((SqueakObject) receiver).setPointer(lobits, stack.pop());
                break;
            case 1:
                homeContext.setPointer(Constants.Context_tempFrameStart + lobits, stack.pop());
                break;
            case 2:
                nono();
                break;
            case 3:
                ((SqueakObject) method.methodGetLiteral(lobits)).setPointer(Constants.Assn_value, stack.pop());
                break;
        }
    }

    public void doubleExtendedDoAnything(int nextByte) {
        int byte3 = nextByte();
        switch (nextByte >> 5) {
            case 0:
                send(method.methodGetSelector(byte3), nextByte & 31, false);
                break;
            case 1:
                send(method.methodGetSelector(byte3), nextByte & 31, true);
                break;
            case 2:
                stack.push(((SqueakObject) receiver).fetchPointer(byte3));
                break;
            case 3:
                stack.push(method.methodGetLiteral(byte3));
                break;
            case 4:
                stack.push(((SqueakObject) method.methodGetLiteral(byte3)).fetchPointer(Constants.Assn_key));
                break;
            case 5:
                ((SqueakObject) receiver).setPointer(byte3, stack.top());
                break;
            case 6:
                ((SqueakObject) receiver).setPointer(byte3, stack.pop());
                break;
            case 7:
                ((SqueakObject) method.methodGetLiteral(byte3)).setPointer(Constants.Assn_key, stack.top());
                break;
        }
    }

    public void doReturn(Object returnValue, SqueakObject targetContext) {
        if (targetContext == SpecialObjects.nilObj) {
            cannotReturn();
        }
        if (targetContext.fetchPointer(Constants.Context_instructionPointer) == SpecialObjects.nilObj) {
            cannotReturn();
        }
        SqueakObject thisContext = activeContext;
        while (thisContext != targetContext) {
            if (thisContext == SpecialObjects.nilObj) {
                cannotReturn();
            }
            if (isUnwindMarked(thisContext)) {
                aboutToReturn(returnValue, thisContext);
            }
            thisContext = thisContext.fetchPointerNI(Constants.Context_sender);
        }
        //No unwind to worry about, just peel back the stack (usually just to sender)
        SqueakObject nextContext;
        thisContext = activeContext;
        while (thisContext != targetContext) {
            nextContext = thisContext.fetchPointerNI(Constants.Context_sender);
            thisContext.setPointer(Constants.Context_sender, SpecialObjects.nilObj);
            thisContext.setPointer(Constants.Context_instructionPointer, SpecialObjects.nilObj);
            if (reclaimableContextCount > 0) {
                reclaimableContextCount--;
                recycleIfPossible(thisContext);
            }
            thisContext = nextContext;
        }
        activeContext = thisContext;
        fetchContextRegisters(activeContext);
        stack.push(returnValue);
//System.err.println("***returning " + printString(returnValue));
    }

    public void cannotReturn() {
    }

    public boolean isUnwindMarked(SqueakObject ctxt) {
        return false;
    }

    public void aboutToReturn(Object obj, SqueakObject ctxt) {
    }

    public void nono() {
        throw new RuntimeException("bad code");
    }

    int stackInteger(int nDeep) {
        return checkSmallInt(stack.stackValue(nDeep));
    }

    int checkSmallInt(Object maybeSmall) { // returns an int and sets success

        if (SmallInteger.isSmallInt(maybeSmall)) {
            return SmallInteger.intFromSmall((Integer) maybeSmall);
        }
        success = false;
        return 1;
    }

    public boolean pop2AndPushIntResult(int intResult) {//Note returns sucess boolean

        if (!success) {
            return false;
        }
        Object smallInt = SmallInteger.smallFromInt(intResult);
        if (smallInt != null) {
            stack.popNandPush(2, smallInt);
            return true;
        }
        return false;
    }

    public boolean pushBoolAndPeek(boolean boolResult) {
        //Peek ahead to see if next bytecode is a conditional jump
        if (!success) {
            return false;
        }
        int originalPC = pc;
        int nextByte = nextByte();
        if (nextByte >= 152 && nextByte < 160) {// It's a BFP

            stack.popN(2);
            if (boolResult) {
                return true;
            } else {
                pc += (nextByte - 152 + 1);
            }
            return true;
        }
        if (nextByte == 172) {// It's a long BFP
            // Could check for all long cond jumps later

            stack.popN(2);
            nextByte = nextByte();
            if (boolResult) {
                return true;
            } else {
                pc += nextByte;
            }
            return true;
        }
        stack.popNandPush(2, boolResult ? SpecialObjects.trueObj : SpecialObjects.falseObj);
        pc = originalPC;
        return true;
    }


    public void send(SqueakObject selector, int argCount, boolean doSuper) {
        SqueakObject newMethod;
        int primIndex;


        Object newRcvr = stack.stackValue(argCount);

        // GG:Useful but very verobse
        // For boot processsing. Enabled for the first x sends
    	if(++sendsPrinted < MAX_SENDS_TO_PRINT) {
    		System.err.println(sendsPrinted+" ["+
    				(newRcvr!=null?newRcvr.getClass():"null")
    					+"] "+
    				newRcvr+" << "+ selector +" Args:"+argCount);
    	}
        // logger.finer("Rcv="+newRcvr+" << "+selector);


    	if(printString(selector).equals("error:")){
    		logger.severe("--- Error! --- Sends Breakpoint:"+sendsPrinted+" Max Printed:"+MAX_SENDS_TO_PRINT);
    		dumpStack(); // <---break here
    		/*Exception in thread "main" java.lang.ArrayIndexOutOfBoundsException: 100
				at potato.vm.VM.dumpStack(VM.java:1328)
				at potato.vm.VM.send(VM.java:934)
				at potato.vm.VM.run(VM.java:665)
				at potato.Main.main(Main.java:80)
    		 */
    	}

		//if(printString(selector).equals("error:"))
		//  dumpStack();// <---break here
		//     int stackDepth=stackDepth();
		//     stackedReceivers[stackDepth]=newRcvr;
		//     stackedSelectors[stackDepth]=selector;
        SqueakObject lookupClass = SpecialObjects.getClass(newRcvr);


        // Revert: Can Java object Respond? if true delegate,
        // otherwise proceed
        String selectorName=""+selector;
        if(newRcvr instanceof AbstractSqueakObject)   {
			if( ((AbstractSqueakObject)newRcvr).isJavaProxy())
        	{
				JavaProxyObject jpo=(JavaProxyObject)newRcvr;
				Method m=jpo.translate2JavaMethod(selectorName);
				if(m!=null){
	        		logger.info(sendsPrinted+" [ __ JAVA __ PROXY CALL: " + newRcvr + " << " + selector +"]");

	        		jpo.invokeAndPushResult(m,stack,this);

//	        		JavaCall javaAdapter = new JavaCall(stack, selector);
//	        		javaAdapter.invokeAndPushResult();
	        		return;
				}else{
					logger.finer(sendsPrinted+" [ Java "+newRcvr + " Ignored: " + selector+"]");
				}
        	}
        }



        if (doSuper) {
            lookupClass = method.methodClassForSuper();
            lookupClass = lookupClass.fetchPointerNI(Constants.Class_superclass);
        }
        int priorSP = stack.sp; // to check if DNU changes argCount

        MethodCacheEntry entry = findSelectorInClass(selector, argCount, lookupClass);

        newMethod = entry.method;
        primIndex = entry.primIndex;
        if (primIndex > 0) { //note details for verification of at/atput primitives

            verifyAtSelector = selector;
            verifyAtClass = lookupClass;
        }

        executeNewMethod(newRcvr, newMethod, argCount + (stack.sp - priorSP), primIndex); //DNU may affest argCount
    }

    public MethodCacheEntry findSelectorInClass(SqueakObject selector, int argCount, SqueakObject startingClass) {
        MethodCacheEntry cacheEntry = methodCache.findMethodCacheEntry(selector, startingClass);
        if (cacheEntry.method != null) {
            return cacheEntry; // Found it in the method cache

        }
        SqueakObject currentClass = startingClass;
        SqueakObject mDict;
        while (!(currentClass == SpecialObjects.nilObj)) {
            mDict = currentClass.fetchPointerNI(Constants.Class_mdict);
            if (mDict == SpecialObjects.nilObj) {
//                ["MethodDict pointer is nil (hopefully due a swapped out stub)
//                        -- raise exception #cannotInterpret:."
//                self createActualMessageTo: class.
//                messageSelector _ self splObj: SelectorCannotInterpret.
//                ^ self lookupMethodInClass: (self superclassOf: currentClass)]
                }
            SqueakObject newMethod = lookupSelectorInDict(mDict, selector);
            if (!(newMethod == SpecialObjects.nilObj)) {
                //load cache entry here and return
                cacheEntry.method = newMethod;
                cacheEntry.primIndex = newMethod.methodPrimitiveIndex();
                return cacheEntry;
            }
            currentClass = currentClass.fetchPointerNI(Constants.Class_superclass);
        }

        logger.info(""+selector);

        //Cound not find a normal message -- send #doesNotUnderstand:
//if(printString(selector).equals("zork"))
//    System.err.println(printString(selector));
        SqueakObject dnuSel = SpecialObjects.getSpecialObject(splOb_SelectorDoesNotUnderstand);
        if (selector == dnuSel) // Cannot find #doesNotUnderstand: -- unrecoverable error.
        {
            throw new RuntimeException("Recursive not understood error encountered");
        }
        SqueakObject dnuMsg = createActualMessage(selector, argCount, startingClass); //The argument to doesNotUnderstand:

        stack.popNandPush(argCount, dnuMsg);
        return findSelectorInClass(dnuSel, 1, startingClass);
    }

    public SqueakObject createActualMessage(SqueakObject selector, int argCount, SqueakObject cls) {
        //Bundle up receiver, args and selector as a messageObject
        SqueakObject argArray = instantiateClass(SpecialObjects.getSpecialObject(splOb_ClassArray), argCount);
        System.arraycopy(activeContext.pointers, stack.sp - argCount + 1, argArray.pointers, 0, argCount); //copy args from stack

        SqueakObject message = instantiateClass(SpecialObjects.getSpecialObject(splOb_ClassMessage), 0);
        message.setPointer(Constants.Message_selector, selector);
        message.setPointer(Constants.Message_arguments, argArray);
        if (message.pointers.length < 3) {
            return message; //Early versions don't have lookupClass

        }
        message.setPointer(Constants.Message_lookupClass, cls);
        return message;
    }

    public SqueakObject lookupSelectorInDict(SqueakObject mDict, SqueakObject messageSelector) {
        //Returns a method or nilObject
        int dictSize = mDict.pointersSize();
        int mask = (dictSize - Constants.MethodDict_selectorStart) - 1;
        int index = (mask & messageSelector.hash) + Constants.MethodDict_selectorStart;
        // If there are no nils(should always be), then stop looping on second wrap.
        boolean hasWrapped = false;
        while (true) {
            SqueakObject nextSelector = mDict.fetchPointerNI(index);
            //System.err.println("index= "+index+" "+printString(nextSelector));
            if (nextSelector == messageSelector) {
                SqueakObject methArray = mDict.fetchPointerNI(Constants.MethodDict_array);
                return methArray.fetchPointerNI(index - Constants.MethodDict_selectorStart);
            }
            if (nextSelector == SpecialObjects.nilObj) {
                return SpecialObjects.nilObj;
            }
            if (++index == dictSize) {
                if (hasWrapped) {
                    return SpecialObjects.nilObj;
                }
                index = Constants.MethodDict_selectorStart;
                hasWrapped = true;
            }
        }
    }


    public void executeNewMethod(Object newRcvr, SqueakObject newMethod, int argumentCount, int primitiveIndex) {

        if (primitiveIndex > 0) {
            if (tryPrimitive(primitiveIndex, argumentCount)) {
                return;  //Primitive succeeded -- end of story

            }
        }

        // GG: WHERE GETS EXECUTED?!
        SqueakObject newContext = allocateOrRecycleContext(newMethod.methodNeedsLargeFrame());
        //logger.info("\tnewContext="+newContext.);
        int methodNumLits = method.methodNumLits();
        //Our initial IP is -1, so first fetch gets bits[0]
        //The stored IP should be 1-based index of *next* instruction, offset by hdr and lits
        int newPC = -1;
        int tempCount = newMethod.methodTempCount();
        int newSP = tempCount;
        newSP += Constants.Context_tempFrameStart - 1; //-1 for z-rel addressing

        newContext.setPointer(Constants.Context_method, newMethod);
        //Following store is in case we alloc without init; all other fields get stored
        newContext.setPointer(Constants.BlockContext_initialIP, SpecialObjects.nilObj);
        newContext.setPointer(Constants.Context_sender, activeContext);
        //Copy receiver and args to new context
        //Note this statement relies on the receiver slot being contiguous with args...
        System.arraycopy(activeContext.pointers, stack.sp - argumentCount, newContext.pointers, Constants.Context_tempFrameStart - 1, argumentCount + 1);
        //...and fill the remaining temps with nil
        try {
			Arrays.fill(newContext.pointers, Constants.Context_tempFrameStart
					+ argumentCount, Constants.Context_tempFrameStart
					+ tempCount, SpecialObjects.nilObj);
        } catch (IllegalArgumentException e) {
        	logger.log(Level.SEVERE, "Cannot Build new Context newMethod="+newMethod+" newRcvr="+newRcvr,e);
        	throw new SmallTalkVMException("Cannot Build new Context newMethod="+newMethod+" newRcvr="+newRcvr,e);
        }

        stack.popN(argumentCount + 1);
        reclaimableContextCount++;
        storeContextRegisters();
        activeContext = newContext; //We're off and running...
//      Following are more efficient than fetchContextRegisters in newActiveContext:

        homeContext = newContext;
        method = newMethod;
        methodBytes = (byte[]) method.bits;
        pc = newPC;
        stack.sp = newSP;
        storeContextRegisters(); // not really necessary, I claim

        receiver = newContext.fetchPointer(Constants.Context_receiver);
        if (receiver != newRcvr) {
        	logger.severe("receiver doesn't match:"
				        	+"\n\t  receiver: " + receiver
				        	+"\n\t  newRcvr: " + newRcvr);
        }
        interruptHandler.checkForInterrupts();
    }

    public boolean tryPrimitive(int primIndex, int argCount) {
        if ((primIndex > 255) && (primIndex < 520)) {
            if (primIndex >= 264) {//return instvars

                stack.popNandPush(1, ((SqueakObject) stack.top()).fetchPointer(primIndex - 264));
                return true;
            } else {
                if (primIndex == 256) {
                    return true; //return self

                }
                if (primIndex == 257) {
                    stack.popNandPush(1, SpecialObjects.trueObj); //return true

                    return true;
                }
                if (primIndex == 258) {
                    stack.popNandPush(1, SpecialObjects.falseObj); //return false

                    return true;
                }
                if (primIndex == 259) {
                    stack.popNandPush(1, SpecialObjects.nilObj); //return nil

                    return true;
                }
                stack.popNandPush(1, SmallInteger.smallFromInt(primIndex - 261)); //return -1...2

                return true;
            }
        } else {
            int spBefore = stack.sp;
            boolean success = primHandler.doPrimitive(primIndex, argCount);
//            if(success) {
//                if(primIndex>=81 && primIndex<=88) return success; // context switches and perform
//                if(primIndex>=43 && primIndex<=48) return success; // boolean peeks
//                if(sp != (spBefore-argCount))
//                    System.err.println("***Stack imbalance on primitive #" + primIndex);}
//            else{
//                if(sp != spBefore)
//                    System.err.println("***Stack imbalance on primitive #" + primIndex);
//                if(primIndex==103) return success; // scan chars
//                if(primIndex==230) return success; // yield
//                if(primIndex==19) return success; // fail
//                System.err.println("At bytecount " + byteCount + " failed primitive #" + primIndex);
//                if (primIndex==80) {
//                    dumpStack();
//                    int a=primIndex; } // <-- break here
//                }
            return success;
        }
    }

    public void primitivePerform(int argCount) {
        SqueakObject selector = (SqueakObject) stack.stackValue(argCount - 1);
        Object rcvr = stack.stackValue(argCount);




//      NOTE: findNewMethodInClass may fail and be converted to #doesNotUnderstand:,
//            (Whoah) so we must slide args down on the stack now, so that would work
        int trueArgCount = argCount - 1;
        int selectorIndex = stack.sp - trueArgCount;
        Object[] stack_ = activeContext.pointers; // slide eveything down...

        System.arraycopy(stack_, selectorIndex + 1, stack_, selectorIndex, trueArgCount);
        stack.sp = stack.sp - 1; // adjust sp accordingly

        MethodCacheEntry entry = findSelectorInClass(selector, trueArgCount, SpecialObjects.getClass(rcvr));
        SqueakObject newMethod = entry.method;
        executeNewMethod(rcvr, newMethod, newMethod.methodNumArgs(), entry.primIndex);
    }

    public void primitivePerformWithArgs(SqueakObject lookupClass) {
        Object rcvr = stack.stackValue(2);
        SqueakObject selector = (SqueakObject) stack.stackValue(1);
        if (SmallInteger.isSmallInt(stack.stackValue(0))) {
            throw primHandler.failExpected();
        }
        SqueakObject args = (SqueakObject) stack.stackValue(0);
        if (args.pointers == null) {
            throw primHandler.failExpected();
        }
        int trueArgCount = args.pointers.length;
        System.arraycopy(args.pointers, 0, activeContext.pointers, stack.sp - 1, trueArgCount);
        stack.sp = stack.sp - 2 + trueArgCount; //pop selector and array then push args

        MethodCacheEntry entry = findSelectorInClass(selector, trueArgCount, lookupClass);
        SqueakObject newMethod = entry.method;
        if (newMethod.methodNumArgs() != trueArgCount) {
            throw primHandler.failExpected();
        }
        executeNewMethod(rcvr, newMethod, newMethod.methodNumArgs(), entry.primIndex);
    }

    public void primitivePerformInSuperclass(SqueakObject lookupClass) {
        //verify that lookupClass is actually in reciver's inheritance
        SqueakObject currentClass = SpecialObjects.getClass(stack.stackValue(3));
        while (currentClass != lookupClass) {
            currentClass = (SqueakObject) currentClass.pointers[Constants.Class_superclass];
            if (currentClass == SpecialObjects.nilObj) {
                throw primHandler.failExpected();
            }
        }
        stack.pop(); //pop the lookupClass for now

        try {
            primitivePerformWithArgs(lookupClass);
        } catch(PrimitiveFailedException pfe) {
            stack.push(lookupClass);
            throw pfe;
        }
    }

    public void recycleIfPossible(SqueakObject ctxt) {
        if (!stack.isMethodContext(ctxt)) {
            return;
//if(isContext(ctxt)) return; //Defeats recycling of contexts
        }
        if (ctxt.pointersSize() == (Constants.Context_tempFrameStart + Constants.Context_smallFrameSize)) { // Recycle small contexts

            ctxt.setPointer(0, freeContexts);
            freeContexts = ctxt;
        } else { // Recycle large contexts

            if (ctxt.pointersSize() != (Constants.Context_tempFrameStart + Constants.Context_largeFrameSize)) {
                // GG ??? freeContexts = freeContexts;
                return;
            } //  <-- break here

            ctxt.setPointer(0, freeLargeContexts);
            freeLargeContexts = ctxt;
        }
    }

    public SqueakObject allocateOrRecycleContext(boolean needsLarge) {
        //Return a recycled context or a newly allocated one if none is available for recycling."
        SqueakObject freebie;
        if (needsLarge) {
            if (freeLargeContexts != SpecialObjects.nilObj) {
                freebie = freeLargeContexts;
                freeLargeContexts = freebie.fetchPointerNI(0);
                nRecycledContexts++;
                return freebie;
            }
            nAllocatedContexts++;
            return instantiateClass(SpecialObjects.getSpecialObject(splOb_ClassMethodContext), Constants.Context_largeFrameSize);
        } else {
            if (freeContexts != SpecialObjects.nilObj) {
                freebie = freeContexts;
                freeContexts = freebie.fetchPointerNI(0);
                nRecycledContexts++;
                return freebie;
            }
            nAllocatedContexts++;
            return instantiateClass(SpecialObjects.getSpecialObject(splOb_ClassMethodContext), Constants.Context_smallFrameSize);
        }
    }

    public SqueakObject instantiateClass(SqueakObject theClass, int indexableSize) {
        return new SqueakObject(image, theClass, indexableSize, SpecialObjects.nilObj);
    }




	public SqueakObject instantiateJavaProxyClass(final String fullClassName) {
		return new JavaProxyObject(image,fullClassName);
	}




    public void printContext() {
        if ((byteCount % 100) == 0 && stackDepth() > 100) {
            System.err.println("******Stack depth over 100******");
            dumpStack();
            //GG ? byteCount = byteCount;
        } // <-- break here
//        if(mod(byteCount,1000) != 0) return;

        if (byteCount != -1) {
            return;
        }
        System.err.println();
        System.err.println(byteCount + " rcvr= " + printString(receiver));
        System.err.println("depth= " + stackDepth() + "; top= " + printString(stack.top()));
        System.err.println("pc= " + pc + "; sp= " + stack.sp + "; nextByte= " + (((byte[]) method.bits)[pc + 1] & 0xff));
        if (byteCount == 1764) {
            // GG ?? byteCount = byteCount; // <-- break here

        }
    }

    int stackDepth() {
        SqueakObject ctxt = activeContext;
        int depth = 0;
        while ((ctxt = ctxt.fetchPointerNI(Constants.Context_sender)) != SpecialObjects.nilObj) {
            depth = depth + 1;
        }
        return depth;
    }

    String printString(Object obj) {//Handles SqueakObjs and SmallInts as wells

        if (obj == null) {
            return "null";
        }
        if (SmallInteger.isSmallInt(obj)) {
            return "=" + ((Integer) obj).intValue();
        } else {
            return ((SqueakObject) obj).asString();
        }
    }

    void dumpStack() {
    	logger.info("Stack Dump....BEGIN");
        for (int i = 0; i < stackDepth(); i++) {
            if (stackedSelectors != null) {
                logger.info(stackedReceivers[i] + " >> " + stackedSelectors[i]);
            }
        }
        logger.info("Stack Dump....ENDS");
    }

    public void wakeVM()
    {
        screenEvent = true;
        synchronized( this )
        {
            notify();
        }
        try
        {
            Thread.sleep(0,200);
        }
        catch(InterruptedException e) {}

        screenEvent = false;
    }
}


