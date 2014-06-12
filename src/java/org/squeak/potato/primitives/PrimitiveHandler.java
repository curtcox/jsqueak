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
package org.squeak.potato.primitives;

import static org.squeak.potato.objects.SpecialObjectConstants.splOb_CharacterTable;
import static org.squeak.potato.objects.SpecialObjectConstants.splOb_ClassArray;
import static org.squeak.potato.objects.SpecialObjectConstants.splOb_ClassBlockContext;
import static org.squeak.potato.objects.SpecialObjectConstants.splOb_ClassCharacter;
import static org.squeak.potato.objects.SpecialObjectConstants.splOb_ClassFloat;
import static org.squeak.potato.objects.SpecialObjectConstants.splOb_ClassLargePositiveInteger;
import static org.squeak.potato.objects.SpecialObjectConstants.splOb_ClassPoint;
import static org.squeak.potato.objects.SpecialObjectConstants.splOb_ClassSemaphore;
import static org.squeak.potato.objects.SpecialObjectConstants.splOb_ClassString;
import static org.squeak.potato.objects.SpecialObjectConstants.splOb_SchedulerAssociation;
import static org.squeak.potato.objects.SpecialObjectConstants.splOb_TheDisplay;
import static org.squeak.potato.objects.SpecialObjectConstants.splOb_TheInterruptSemaphore;
import static org.squeak.potato.objects.SpecialObjectConstants.splOb_TheLowSpaceSemaphore;
import static org.squeak.potato.objects.SpecialObjectConstants.splOb_TheTimerSemaphore;

import java.awt.Dimension;
import java.awt.Point;
import java.math.BigInteger;
import java.util.Arrays;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.squeak.potato.Arithmetics;
import org.squeak.potato.Constants;
import org.squeak.potato.clipboard.CliboardHelper;
import org.squeak.potato.drawing.BitBlt;
import org.squeak.potato.drawing.FormCache;
import org.squeak.potato.drawing.Screen;
import org.squeak.potato.image.SqueakImage;
import org.squeak.potato.objects.LargeInteger;
import org.squeak.potato.objects.ObjectTable;
import org.squeak.potato.objects.SmallInteger;
import org.squeak.potato.objects.SpecialObjects;
import org.squeak.potato.objects.SqueakObject;
import org.squeak.potato.vm.InterruptHandler;
import org.squeak.potato.vm.MethodCache;
import org.squeak.potato.vm.Stack;
import org.squeak.potato.vm.VM;

/**
 * @author Daniel Ingalls
 *
 * @author Frank Feinbube
 * @author Robert Wierschke
 *
 * Implements the indexed primitives for the Squeak VM.
 * Yet to do...
 *      this file should be split up into...
 *      assorted prims,
 *      Array/string prims,
 *      scheduler prims.  Also
 *      quick sends should probably go back into VM
 *  make a new file with send, return, block copy and value (ie contexts)
 */

/*
Portions of the software are derived from classes of the VMMaker-Package 3.8b3.
The Smalltalk code is still annotated as comments.
 */

public class PrimitiveHandler {
	Logger logger=Logger.getLogger(getClass().getName());

	private final Stack stack;
	private final MethodCache methodCache;
	private final InterruptHandler interruptHandler;
	private final ObjectTable objectTable;
	private final VM vm;
	private final SqueakImage image;
	boolean successFlag;
	private Screen theDisplay;
	int[] displayBitmap;
	int displayRaster;
	BitBlt bitbltTable;
	int BWMask = 0;
	// Its purpose of the at-cache is to allow fast (bytecode) access to at/atput code
	// without having to check whether this object has overridden at, etc.
	int atCacheSize = 32; // must be power of 2

	int atCacheMask = atCacheSize - 1; //...so this is a mask

	AtCacheInfo[] atCache;
	AtCacheInfo[] atPutCache;
	AtCacheInfo nonCachedInfo;

	Stack stack() { return stack; }

	//
	// support for externalised primitives
	//

	private final FileSystemPrimitives fileSystemPrimitives =
			new FileSystemPrimitives(this);

	private final LargeIntegerPrimitives largeIntegerPrimitives =
			new LargeIntegerPrimitives(this);

	//
	// support for primitive failure
	//
	// There are three exception classes to be used in conjunction with
	// reporting primitive failure. PrimitiveFailedException is the common
	// abstract super class. UnexpectedPrimitiveFailedException is used to
	// report failures that should really not happen. On the other hand,
	// ExpectedPrimitiveFailedException is used to report a failure that is
	// considered "normal".
	//
	// The latter are reported by means of a singleton instance of the
	// ExpectedPrimitiveFailedException class. It has a fixed and not very
	// informative stack trace. The former, conversely, are created on request
	// and carry a meaningful stack trace.
	//

	private static ExpectedPrimitiveFailedException epfe =
			new ExpectedPrimitiveFailedException();

	public static PrimitiveFailedException failExpected() {
		return epfe;
	}

	/**
	 * FIXME: surely something better can be devised?
	 *        Idea: make argCount a field, then this method
	 *        needs no argument
	 */
	Object stackReceiver( int argCount )
	{
		return vm.stack.stackValue( argCount );
	}

	Object pos32BitIntFor( long pos32Val )
	{
		if ( pos32Val < Integer.MIN_VALUE ||
				pos32Val > Integer.MAX_VALUE )
		{
			throw new UnexpectedPrimitiveFailedException(new ArithmeticException("long to int overflow"));
		}

		return pos32BitIntFor( (int) pos32Val );
	}

	/**
	 * Note: this method does not check to see that the passed
	 *       object is an instance of Boolean.
	 *
	 * @return true iff object is the special Squeak true object
	 */
	boolean javaBool( SqueakObject object )
	{
		return object == SpecialObjects.trueObj;
	}

	SqueakObject squeakNil()
	{
		return SpecialObjects.nilObj;
	}

	SqueakObject squeakArray( Object[] javaArray )
	{
		SqueakObject array = vm.instantiateClass(
				SpecialObjects.getSpecialObject(splOb_ClassArray),
				javaArray.length
				);
		for ( int index = 0; index < javaArray.length; index++ ) {
			array.setPointer( index, javaArray[index] );
		}

		return array;
	}

	Object squeakSeconds( long millis )
	{
		int secs = (int) ( millis / 1000 ); //milliseconds -> seconds
		secs += ( 69 * 365 + 17 ) * 24 * 3600; //Adjust from 1901 to 1970

		return pos32BitIntFor(secs);
	}

	/**
	 * snapshotPrimitive
	 *    "Primitive. Write the current state of the object memory on a file in the
	 *    same format as the Smalltalk-80 release. The file can later be resumed,
	 *    returning you to this exact state. Return normally after writing the file.
	 *    Essential. See Object documentation whatIsAPrimitive."
	 *
	 *    <primitive: 97>
	 *     ^nil "indicates error writing image file"
	 */
	private void primitiveSnapshot()
	{

		logger.info("Save disabled");
		return ;

		//		logger.info( "Saving the image into:" + vm.image.imageFile());
		//		try
		//		{
		//			vm.image.saveImage( vm.image.imageFile() );
		//		}
		//		catch ( Exception e )
		//		{
		//			throw new UnexpectedPrimitiveFailedException(e);
		//		}
	}

	/**
	 * Primitive 121
	 * "When called with a single string argument, record the string
	 * as the current image file name. When called with zero
	 * arguments, return a string containing the current image file
	 * name."
	 */
	private Object primitiveImageFileName( int argCount )
	{
		if ( argCount == 0 ) {
			return makeStString( vm.image.imageFile().getAbsolutePath() );
		} else {
			throw new UnexpectedPrimitiveFailedException(new UnsupportedOperationException(
					"Cannot set the image name yet, argument is '" +
							stackNonInteger( 0 ) + "'"
					));
		}
	}

	/**
	 * SystemDictionary>>vmPath.
	 * Primitive 142.
	 *
	 * primVmPath
	 *   "Answer the path for the directory containing the Smalltalk virtual machine.
	 *   Return the empty string if this primitive is not implemented."
	 *        "Smalltalk vmPath"
	 *
	 *   <primitive: 142>
	 *   ^ ''
	 */
	private SqueakObject primitiveVmPath()
	{
		return makeStString( System.getProperty( "user.dir" ) +
				System.getProperty("file.separator"));
	}

	//
	// primitive handling
	//

	public PrimitiveHandler(VM theVM) {
		vm = theVM;
		stack = theVM.stack;
		methodCache = theVM.methodCache;
		interruptHandler = theVM.interruptHandler;
		image = vm.image;
		objectTable = image.objectTable;
		bitbltTable = new BitBlt(vm);
		initAtCache();
	}

	class AtCacheInfo {

		SqueakObject array;
		int size;
		int ivarOffset;
		boolean convertChars;
	}

	void initAtCache() {
		atCache = new AtCacheInfo[atCacheSize];
		atPutCache = new AtCacheInfo[atCacheSize];
		nonCachedInfo = new AtCacheInfo();
		for (int i = 0; i < atCacheSize; i++) {
			atCache[i] = new AtCacheInfo();
			atPutCache[i] = new AtCacheInfo();
		}
	}

	public void clearAtCache() { //clear at-cache pointers (prior to GC)

		for (int i = 0; i < atCacheSize; i++) {
			atCache[i].array = null;
			atPutCache[i].array = null;
		}
	}

	AtCacheInfo makeCacheInfo(AtCacheInfo[] atOrPutCache, Object atOrPutSelector, SqueakObject array, boolean convertChars, boolean includeInstVars) {
		//Make up an info object and store it in the atCache or the atPutCache.
		//If it's not cacheable (not a non-super send of at: or at:put:)
		//then return the info in nonCachedInfo.
		//Note that info for objectAt (includeInstVars) will have
		//a zero ivarOffset, and a size that includes the extra instVars
		AtCacheInfo info;
		boolean cacheable = (vm.verifyAtSelector == atOrPutSelector) //is at or atPut
				&& (vm.verifyAtClass == array.getSqClass()) //not a super send
				&& (array.format == 3 && vm.stack.isContext(array));        //not a context (size can change)

		if (cacheable) {
			info = atOrPutCache[array.hashCode() & atCacheMask];
		} else {
			info = nonCachedInfo;
		}
		info.array = array;
		info.convertChars = convertChars;
		if (includeInstVars) {
			info.size = Math.max(0, indexableSize(array)) + array.instSize();
			info.ivarOffset = 0;
		} else {
			info.size = indexableSize(array);
			info.ivarOffset = (array.format < 6) ? array.instSize() : 0;
		}
		return info;
	}

	// Quick Sends from inner Interpreter
	public boolean quickSendOther(Object rcvr, int lobits) {
		// QuickSendOther returns true if it succeeds
		successFlag = true;
		try {
			switch (lobits) {
				case 0x0:
					popNandPushIfOK(2, primitiveAt(true, true, false)); // at:
					break;

				case 0x1:
					popNandPushIfOK(3, primitiveAtPut(true, true, false)); // at:put:
					break;

				case 0x2:
					popNandPushIfOK(1, primitiveSize()); // size
					break;

				case 0x3:
					return false; // next

				case 0x4:
					return false; // nextPut

				case 0x5:
					return false; // atEnd

				case 0x6:
					pop2andDoBoolIfOK(primitiveEq(vm.stack.stackValue(1), vm.stack.stackValue(0))); // ==
					break;

				case 0x7:
					popNandPushIfOK(1, SpecialObjects.getClass(vm.stack.top())); // class
					break;

				case 0x8:
					popNandPushIfOK(2, primitiveBlockCopy()); // blockCopy:
					break;

				case 0x9:
					primitiveBlockValue(0); // value
					break;

				case 0xa:
					primitiveBlockValue(1); // value:
					break;

				case 0xb:
					return false; // do:

				case 0xc:
					return false; // new

				case 0xd:
					return false; // new:

				case 0xe:
					return false; // x

				case 0xf:
					return false; // y

				default:
					return false;
			}
		} catch(UnexpectedPrimitiveFailedException pfe) {
			pfe.printStackTrace();
			return false;
		} catch(ExpectedPrimitiveFailedException pfe) {
			return false;
		}
		return true;
	}

	boolean primitiveEq(Object arg1, Object arg2) {// == must work for uninterned small ints

		if (SmallInteger.isSmallInt(arg1) && SmallInteger.isSmallInt(arg2)) {
			return ((Integer) arg1).intValue() == ((Integer) arg2).intValue();
		}
		return arg1 == arg2;
	}

	Object primitiveBitAnd() {
		int rcvr = stackPos32BitValue(1);
		int arg = stackPos32BitValue(0);
		if (!successFlag) {
			return SpecialObjects.nilObj;
		}
		return pos32BitIntFor(rcvr & arg);
	}

	Object primitiveBitOr() {
		int rcvr = stackPos32BitValue(1);
		int arg = stackPos32BitValue(0);
		if (!successFlag) {
			return SpecialObjects.nilObj;
		}
		return pos32BitIntFor(rcvr | arg);
	}

	Object primitiveBitXor() {
		int rcvr = stackPos32BitValue(1);
		int arg = stackPos32BitValue(0);
		if (!successFlag) {
			return SpecialObjects.nilObj;
		}
		return pos32BitIntFor(rcvr ^ arg);
	}

	Object primitiveBitShift() {
		int rcvr = stackPos32BitValue(1);
		int arg = stackInteger(0);
		if (!successFlag) {
			return SpecialObjects.nilObj;
		}
		return pos32BitIntFor(Arithmetics.safeShift(rcvr, arg));
	}

	int doQuo(int rcvr, int arg) {
		if (arg == 0) {
			success(false);
			return 0;
		}
		if (rcvr > 0) {
			if (arg > 0) {
				return rcvr / arg;
			} else {
				return 0 - (rcvr / (0 - arg));
			}
		} else {
			if (arg > 0) {
				return 0 - ((0 - rcvr) / arg);
			} else {
				return (0 - rcvr) / (0 - arg);
			}
		}
	}

	public boolean doPrimitive(int index, int argCount) {
		successFlag = true;
		try {
			switch (index) {	// 0..127

				case 1:
					popNandPushIntIfOK(2, stackInteger(1) + stackInteger(0));  // Integer.add
					break;

				case 2:
					popNandPushIntIfOK(2, stackInteger(1) - stackInteger(0));  // Integer.subtract
					break;

				case 3:
					pop2andDoBoolIfOK(stackInteger(1) < stackInteger(0));  // Integer.less
					break;

				case 4:
					pop2andDoBoolIfOK(stackInteger(1) > stackInteger(0));  // Integer.greater
					break;

				case 5:
					pop2andDoBoolIfOK(stackInteger(1) <= stackInteger(0));  // Integer.leq
					break;

				case 6:
					pop2andDoBoolIfOK(stackInteger(1) >= stackInteger(0));  // Integer.geq
					break;

				case 7:
					pop2andDoBoolIfOK(stackInteger(1) == stackInteger(0));  // Integer.equal
					break;

				case 8:
					pop2andDoBoolIfOK(stackInteger(1) != stackInteger(0));  // Integer.notequal
					break;

				case 9:
					popNandPushIntIfOK(2, Arithmetics.safeMultiply(stackInteger(1), stackInteger(0)));  // Integer.multiply *
					break;

				case 10:
					popNandPushIntIfOK(2, Arithmetics.quickDivide(stackInteger(1), stackInteger(0)));  // Integer.divide /  (fails unless exact exact)
					break;

				case 11:
					popNandPushIntIfOK(2, Arithmetics.mod(stackInteger(1),stackInteger(0)));  // Integer.mod \\
					break;

				case 12:
					popNandPushIntIfOK(2, Arithmetics.div(stackInteger(1), stackInteger(0)));  // Integer.div //
					break;

				case 13:
					popNandPushIntIfOK(2, doQuo(stackInteger(1), stackInteger(0)));  // Integer.quo
					break;

				case 14:
					popNandPushIfOK(2, primitiveBitAnd());  // SmallInt.bitAnd
					break;

				case 15:
					popNandPushIfOK(2, primitiveBitOr());  // SmallInt.bitOr
					break;

				case 16:
					popNandPushIfOK(2, primitiveBitXor());  // SmallInt.bitXor
					break;

				case 17:
					popNandPushIfOK(2, primitiveBitShift());  // SmallInt.bitShift
					break;

				case 18:
					primitiveMakePoint();
					break;

				case 19:
					// guard primitive for simulation - *must* fail
					// we don't use the exception solution here to make this
					// more explicit
					return false;

				case 21:
					largeIntegerPrimitives.primitiveLargeIntegerAdd(
							stack.stackValue(1), stack.stackValue(0));
					break;

				case 22:
					largeIntegerPrimitives.primitiveLargeIntegerSubtract(
							stack.stackValue(1), stack.stackValue(0));
					break;

				case 23:
					largeIntegerPrimitives.primitiveLargeIntegerLT(
							stack.stackValue(1), stack.stackValue(0));
					break;

				case 24:
					largeIntegerPrimitives.primitiveLargeIntegerGT(
							stack.stackValue(1), stack.stackValue(0));
					break;

				case 25:
					largeIntegerPrimitives.primitiveLargeIntegerLE(
							stack.stackValue(1), stack.stackValue(0));
					break;

				case 26:
					largeIntegerPrimitives.primitiveLargeIntegerGE(
							stack.stackValue(1), stack.stackValue(0));
					break;

				case 29:
					largeIntegerPrimitives.primitiveLargeIntegerMultiply(
							stack.stackValue(1), stack.stackValue(0));
					break;

				case 30:
					largeIntegerPrimitives.primitiveLargeIntegerDivide(
							stack.stackValue(1), stack.stackValue(0));
					break;

				case 31:
					largeIntegerPrimitives.primitiveLargeIntegerModulo(
							stack.stackValue(1), stack.stackValue(0));
					break;

				case 32:
					largeIntegerPrimitives.primitiveLargeIntegerIntegralDivide(
							stack.stackValue(1), stack.stackValue(0));
					break;

				case 33:
					largeIntegerPrimitives.primitiveLargeIntegerQuo(
							stack.stackValue(1), stack.stackValue(0));
					break;

				case 40:
					primitiveAsFloat();
					break;
				case 41:
					popNandPushFloatIfOK(2, stackFloat(1) + stackFloat(0));  // Float +		// +
					break;

				case 42:
					popNandPushFloatIfOK(2, stackFloat(1) - stackFloat(0));  // Float -
					break;

				case 43:
					pop2andDoBoolIfOK(stackFloat(1) < stackFloat(0));  // Float <
					break;

				case 44:
					pop2andDoBoolIfOK(stackFloat(1) > stackFloat(0));  // Float >
					break;

				case 45:
					pop2andDoBoolIfOK(stackFloat(1) <= stackFloat(0));  // Float <=
					break;

				case 46:
					pop2andDoBoolIfOK(stackFloat(1) >= stackFloat(0));  // Float >=
					break;

				case 47:
					pop2andDoBoolIfOK(stackFloat(1) == stackFloat(0));  // Float =
					break;

				case 48:
					pop2andDoBoolIfOK(stackFloat(1) != stackFloat(0));  // Float !=
					break;

				case 49:
					popNandPushFloatIfOK(2, stackFloat(1) * stackFloat(0));  // Float.mul
					break;

				case 50:
					popNandPushFloatIfOK(2, safeFDiv(stackFloat(1), stackFloat(0)));  // Float.div
					break;

				case 51:
					popNandPushIntIfOK(1, primitiveTruncate(stackFloat(0)));
					break;

				case 52:
					popNandPushFloatIfOK(1, primitiveFractionalPart(stackFloat(0)));
					break;

				case 53:
					popNandPushIntIfOK(1, primitiveExponent(stackFloat(0)));
					break;

				case 54:
					popNandPushFloatIfOK(2, primitiveTimesTwoPower(stackFloat(1), stackInteger(0)));
					break;

				case 58:
					popNandPushFloatIfOK(1, StrictMath.log(stackFloat(0)));  // Float.ln
					break;

				case 60:
					popNandPushIfOK(2, primitiveAt(false, false, false)); // basicAt:
					break;

				case 61:
					popNandPushIfOK(3, primitiveAtPut(false, false, false)); // basicAt:put:
					break;

				case 62:
					popNandPushIfOK(1, primitiveSize()); // size
					break;

				case 63:
					popNandPushIfOK(2, primitiveAt(false, true, false)); // basicAt:
					break;

				case 64:
					popNandPushIfOK(3, primitiveAtPut(false, true, false)); // basicAt:put:
					break;

				case 65:
					primitiveNext();
					break;

				case 66:
					primitiveNextPut();
					break;

				case 67:
					primitiveAtEnd();
					break;

				case 68:
					popNandPushIfOK(2, primitiveAt(false, false, true)); // Method.objectAt:
					break;

				case 69:
					popNandPushIfOK(3, primitiveAtPut(false, false, true)); // Method.objectAt:put:
					break;

					/*
					 * basicNew
	<primitive: 70>
	self isVariable ifTrue: [^ self basicNew: 0].
	Smalltalk signalLowSpace.
	^ self basicNew
					 */
				case 70:
					popNandPushIfOK(1, vm.instantiateClass(stackNonInteger(0), 0)); // Class.new
					break;

					/*
					 * 'From Squeak 2.2 of Sept 23, 1998 on 6 December 2013 at 2:21:53 pm'!

    				!Behavior methodsFor: 'as yet unclassified'!
    				basicNew: t1
    					<primitive: 71>
    					(t1 isInteger and: [t1 >= 0])
    						ifTrue:
    							[Smalltalk signalLowSpace.
    							^ self basicNew: t1].
    					self primitiveFailed! !

					 */
				case 71:
					popNandPushIfOK(2, primitiveNewWithSize()); // Class.new
					break;

				case 72:
					popNandPushIfOK(2, primitiveArrayBecome(false));
					break;
				case 73:
					popNandPushIfOK(2, primitiveAt(false, false, true)); // instVarAt:
					break;

				case 74:
					popNandPushIfOK(3, primitiveAtPut(false, false, true)); // instVarAt:put:
					break;

				case 75:
					popNandPushIfOK(1, primitiveHash()); // Class.identityHash
					break;

				case 77:
					popNandPushIfOK(1, primitiveSomeInstance(stackNonInteger(0))); // Class.someInstance
					break;

				case 78:
					popNandPushIfOK(1, primitiveNextInstance(stackNonInteger(0))); // Class.someInstance
					break;

				case 79:
					popNandPushIfOK(3, primitiveNewMethod()); // Compiledmethod.new
					break;

				case 80:
					popNandPushIfOK(2, primitiveBlockCopy()); // Context.blockCopy:
					break;

				case 81:
					primitiveBlockValue(argCount); // BlockContext.value
					break;

				case 83:
					vm.primitivePerform(argCount); // rcvr.perform:(with:)*
					break;

				case 84:
					vm.primitivePerformWithArgs(SpecialObjects.getClass(vm.stack.stackValue(2))); // rcvr.perform:withArguments:
					break;

				case 85:
					semaphoreSignal(); // Semaphore.wait
					break;

				case 86:
					semaphoreWait(); // Semaphore.wait
					break;

				case 87:
					processResume(); // Process.resume
					break;

				case 88:
					processSuspend(); // Process.suspend
					break;

				case 89:
					methodCache.clearMethodCache();  // selective
					break;

				case 90:
					popNandPushIfOK(1, primitiveMousePoint()); // mousePoint
					break;

				case 91:
					// This primitive is unimplemented on purpose. In Squeak
					// 2.2, it is supposed to be primCursorLocPut, while in 3.9,
					// it is primitiveTestDisplayDepth.
					throw failExpected();

				case 96:
					bitbltTable.primitiveCopyBits(argCount, theDisplay); // CopyBits
					break;

				case 97:
					primitiveSnapshot();
					break;

				case 100:
					vm.primitivePerformInSuperclass((SqueakObject) vm.stack.top()); // rcvr.perform:withArguments:InSuperclass
					break;

				case 101:
					beCursor(argCount); // Cursor.beCursor
					break;

				case 102:
					beDisplay(); // DisplayScreen.beDisplay
					break;



					// GG PRIMITIVE 103
					// See http://www.mirandabanda.org/bluebook/bluebook_chapter29.html
					//                    102 	DisplayScreen beDisplay
					//                    103* 	CharacterScanner scanCharactersFrom:to:in:rightX:stopConditions:displaying:
					//                    104* 	BitBlt drawLoopX:Y:
					// See
					//                    scanCharactersFrom: startIndex to: stopIndex in: sourceString rightX: rightX stopConditions: stops displaying: display
					//                	"Primitive. This is the inner loop of text display--but see
					//                	scanCharactersFrom: to:rightX: which would get the string,
					//                	stopConditions and displaying from the instance. March through source
					//                	String from startIndex to stopIndex. If any character is flagged with a
					//                	non-nil entry in stops, then return the corresponding value. Determine
					//                	width of each character from xTable. If dextX would exceed rightX, then
					//                	return stops at: 258. If displaying is true, then display the character.
					//                	Advance destX by the width of the character. If stopIndex has been
					//                	reached, then return stops at: 257. Fail under the same conditions that
					//                	the Smalltalk code below would cause an error. Optional. See Object
					//                	documentation whatIsAPrimitive."

					/*
					 * 	| ascii nextDestX maxAscii |
	<primitive: 103>
	maxAscii _ xTable size-2.
	lastIndex _ startIndex.
	[lastIndex <= stopIndex]
		whileTrue:
			[ascii _ (sourceString at: lastIndex) asciiValue.
			"ascii > maxAscii ifTrue: [ascii _ maxAscii]."
			(stopConditions at: ascii + 1) == nil
				ifFalse: [^stops at: ascii + 1].
			sourceX _ xTable at: ascii + 1.
			nextDestX _ destX + (width _ (xTable at: ascii + 2) - sourceX).
			nextDestX > rightX ifTrue: [^stops at: CrossedX].
			display ifTrue: [self copyBits].
			destX _ nextDestX.
			lastIndex _ lastIndex + 1].
	lastIndex _ stopIndex.
	^stops at: EndOfRun
					 */
				case 103:
					return false;


				case 104:
					bitbltTable.primitiveDrawLoop(argCount, theDisplay); // DrawLoop
					break;

				case 105:
					popNandPushIfOK(5, primitiveStringReplace()); // string and array replace
					break;

				case 106:

					popNandPushIfOK(1, makePointWithXandY(SmallInteger.smallFromInt(Constants.DEFAULT_WIDTH), SmallInteger.smallFromInt(Constants.DEFAULT_HEIGHT))); // actualScreenSize
					break;

				case 107:
					popNandPushIfOK(1, primitiveMouseButtons()); // Sensor mouseButtons
					break;

				case 108:
					popNandPushIfOK(1, primitiveKbdNext()); // Sensor kbdNext
					break;

				case 109:
					popNandPushIfOK(1, primitiveKbdPeek()); // Sensor kbdPeek
					break;

				case 110:
					popNandPushIfOK(2, (vm.stack.stackValue(1) == vm.stack.stackValue(0)) ? SpecialObjects.trueObj : SpecialObjects.falseObj); // ==
					break;

				case 112:
					popNandPushIfOK(1, SmallInteger.smallFromInt(objectTable.spaceLeft())); // bytesLeft
					break;

				case 113: 
					/* quitPrimitive*/
					System.exit(0);	
					logger.severe("Asked for quit");
					return true;					

				case 116:
					methodCache.flushMethodCacheForMethod((SqueakObject) vm.stack.top());
					break;

				case 119:
					methodCache.flushMethodCacheForSelector((SqueakObject) vm.stack.top());
					break;

				case 121:
					popNandPushIfOK(1, primitiveImageFileName(argCount));
					break;

				case 122:
					BWMask = ~BWMask;
					break;

				case 124:
					popNandPushIfOK(2, registerSemaphore(splOb_TheLowSpaceSemaphore));
					break;
				case 125:
					popNandPushIfOK(2, setLowSpaceThreshold());
					break;
				case 128:
					popNandPushIfOK(2, primitiveArrayBecome(true));
					break;
				case 129:
					popNandPushIfOK(1, image.specialObjectsArray);
					break;
				case 130:
					popNandPushIfOK(1, SmallInteger.smallFromInt(objectTable.fullGC())); // GC
					break;

				case 131:
					popNandPushIfOK(1, SmallInteger.smallFromInt(objectTable.partialGC())); // GCmost
					break;

				case 132:
					popNandPushIfOK(2, primitiveObjectPointsTo());
					break;

				case 134:
					popNandPushIfOK(2, registerSemaphore(splOb_TheInterruptSemaphore));
					break;
				case 135:
					popNandPushIfOK(1, millisecondClockValue());
					break;
				case 136:
					popNandPushIfOK(3, primitiveSignalAtMilliseconds()); //Delay signal:atMs:());
					break;

				case 137:
					popNandPushIfOK(1, primSeconds()); //Seconds since Jan 1, 1901
					break;

				case 138:
					popNandPushIfOK(1, primitiveSomeObject()); // Class.someInstance
					break;

				case 139:
					popNandPushIfOK(1, primitiveNextObject(stackNonInteger(0))); // Class.someInstance
					break;


				case 141:
					primitiveClipboardText(argCount);
					break;

				case 142:
					popNandPushIfOK(1, primitiveVmPath());
					break;

				case 148:
					popNandPushIfOK(1, ((SqueakObject) vm.stack.top()).cloneIn(image)); //imageName
					break;

				case 149:
					popNandPushIfOK(2, SpecialObjects.nilObj); //getAttribute
					break;

					// File System primitives
				case 150:
					popNandPushIfOK(2, fileSystemPrimitives.fileAtEnd(argCount));
					break;
				case 151:
					popNandPushIfOK(2, fileSystemPrimitives.fileClose(argCount));
					break;
				case 152:
					popNandPushIfOK(2, fileSystemPrimitives.getPosition(argCount));
					break;
				case 153:
					popNandPushIfOK(3, fileSystemPrimitives.openWritable(argCount));
					break;
				case 154:
					popNandPushIfOK(5, fileSystemPrimitives.readIntoStartingAtCount(argCount));
					break;
				case 155:
					popNandPushIfOK(3, fileSystemPrimitives.fileSetPosition(argCount));
					break;
				case 156:
					popNandPushIfOK(2, fileSystemPrimitives.fileDelete(argCount));
					break;
				case 157:
					popNandPushIfOK(2, fileSystemPrimitives.fileSize(argCount));
					break;
				case 158:
					popNandPushIfOK(5, fileSystemPrimitives.fileWrite(argCount));
					break;
				case 159:
					popNandPushIfOK(3, fileSystemPrimitives.fileRename(argCount));
					break;
				case 160:
					popNandPushIfOK(2, fileSystemPrimitives.directoryCreate(argCount));
					break;
				case 161:
					popNandPushIfOK(1, fileSystemPrimitives.directoryDelimitor()); //path delimiter
					break;
				case 162:
					popNandPushIfOK(3, fileSystemPrimitives.lookupEntryInIndex(argCount)); //path delimiter
					break;

				case 230:
					primitiveYield(argCount); //yield for 10ms
					break;

				case 231:
					theDisplay.redisplay(true);
					break;

					//                case 234:
					//                	logger.info("FAILING 234");
					//                	return false;
					//                	//break;



				case 235:
					popNandPushIntIfOK(3, primitiveStringCompareWithCollated());
					break;

				case 243:
					primitiveStringTranslateFromToTable();
					break;

				case 245:
					popNandPushIntIfOK(4, primitiveStringIndexOfAsciiInStringStartingAt());
					break;

					//                case 576:
					//                    String s = vm.stack.pop().toString();
					//                    logger.info("PRIM576\t"+s);
					//                    break;

					// From inerp.c of Squeak 2.2:
					// 	case 545:primitiveAsyncFileWriteStart();
					//  case 546:700: UNDEFINED

					//Class.new example:: popNandPushIfOK(2, primitiveNewWithSize()); // Class.new

				case 1993:
					// newJavaObject:'java.lang.String'
					logger.info("Java interop primitive 1993. argCount="+argCount);
					popNandPushIfOK(2, primitiveNewJavaProxyWithName());
					break;
					//makeStString("TEST");
					//popNandPushIntIfOK(1,  1);
					//break;

				default: {
					// undefined primitve
					//throw primitiveFailed("undefined primitive: " + index);
					logger.severe("undefined primitive: " + index);
					return false;
				}

			}
		} catch (UnexpectedPrimitiveFailedException pfe) {
			logger.log(Level.SEVERE, "FAILED PRIM "+index+" Arg Count:"+argCount, pfe);
			// pfe.printStackTrace();
			return false;
		} catch(ExpectedPrimitiveFailedException pfe) {
			//logger.log(Level.INFO, "EXPECTED FAILED PRIM "+index+" Arg Count:"+argCount, pfe);
			return false;
		}
		return true;
	}

	private void primitiveClipboardText(int argCount) {
		/* primitiveClipboardText
		 * If with arg store content,
		 * otherwise get content.
		 */
		if( argCount==1){
			String v=""+stack.pop();
			logger.info("Storing in cliboard:"+v);
			CliboardHelper.setContent(v);
		}else{
			logger.info("Got from Clipboard:"+CliboardHelper.getContent());
			popNandPushIfOK(1,makeStString(CliboardHelper.getContent()));
		}
	}

	void pop2andDoBoolIfOK(boolean bool) {
		vm.success = successFlag;
		if(!vm.pushBoolAndPeek(bool)) {
			throw failExpected();
		}
	}

	void popNandPushIfOK(int nToPop, Object returnValue) {
		if (!successFlag || returnValue == null) {
			throw failExpected();
		}
		vm.stack.popNandPush(nToPop, returnValue);
	}

	void popNandPushIntIfOK(int nToPop, int returnValue) {
		popNandPushIfOK(nToPop, SmallInteger.smallFromInt(returnValue));
	}

	void popNandPushFloatIfOK(int nToPop, double returnValue) {
		if (!successFlag) {
			throw failExpected();
		}
		popNandPushIfOK(nToPop, makeFloat(returnValue));
	}

	int stackInteger(int nDeep) {
		return checkSmallInt(vm.stack.stackValue(nDeep));
	}

	int checkSmallInt(Object maybeSmall) { // returns an int and sets success

		if (SmallInteger.isSmallInt(maybeSmall)) {
			return SmallInteger.intFromSmall((Integer) maybeSmall);
		}
		success(false);
		return 0;
	}

	double stackFloat(int nDeep) {
		return checkFloat(vm.stack.stackValue(nDeep));
	}

	double checkFloat(Object maybeFloat) { // returns a float and sets success

		if (SpecialObjects.isA(maybeFloat, splOb_ClassFloat)) {
			return ((SqueakObject) maybeFloat).getFloatBits();
		}
		success(false);
		return 0.0d;
	}

	double safeFDiv(double dividend, double divisor) {
		if (divisor == 0.0d) {
			success(false);
			return 1.0d;
		}
		return dividend / divisor;
	}

	SqueakObject checkNonSmallInt(Object maybeSmall) { // returns a SqObj and sets success

		if (SmallInteger.isSmallInt(maybeSmall)) {
			success(false);
			return SpecialObjects.nilObj;
		}
		return (SqueakObject) maybeSmall;
	}

	int stackPos32BitValue(int nDeep) {
		Object stackVal = vm.stack.stackValue(nDeep);
		if (SmallInteger.isSmallInt(stackVal)) {
			int value = SmallInteger.intFromSmall((Integer) stackVal);
			if (value >= 0) {
				return value;
			}
			success(false);
			return 0;
		}
		if (!SpecialObjects.isA(stackVal, splOb_ClassLargePositiveInteger)) {
			success(false);
			return 0;
		}
		byte[] bytes = (byte[]) ((SqueakObject) stackVal).bits;
		int value = 0;
		for (int i = 0; i < 4; i++) {
			value = value + ((bytes[i] & 255) << (8 * i));
		}
		return value;
	}

	Object pos32BitIntFor(int pos32Val) {
		// Return the 32-bit quantity as a positive 32-bit integer
		if (pos32Val >= 0) {
			Object smallInt = SmallInteger.smallFromInt(pos32Val);
			if (smallInt != null) {
				return smallInt;
			}
		}
		SqueakObject lgIntClass = SpecialObjects.getSpecialObject(splOb_ClassLargePositiveInteger);
		SqueakObject lgIntObj = vm.instantiateClass(lgIntClass, 4);
		byte[] bytes = (byte[]) lgIntObj.bits;
		for (int i = 0; i < 4; i++) {
			bytes[i] = (byte) ((pos32Val >> (8 * i)) & 255);
		}
		return lgIntObj;
	}

	SqueakObject stackNonInteger(int nDeep) {
		return checkNonSmallInt(vm.stack.stackValue(nDeep));
	}

	SqueakObject squeakBool(boolean bool) {
		return bool ? SpecialObjects.trueObj : SpecialObjects.falseObj;
	}

	void primitiveAsFloat() {
		int intValue = stackInteger(0);
		if (!successFlag) {
			throw failExpected();
		}
		vm.stack.popNandPush(1, makeFloat(intValue));
	}

	int primitiveTruncate(double floatVal) {
		if (!(-1073741824.0 <= floatVal) && (floatVal <= 1073741823.0)) {
			throw failExpected();
		}
		return (new Double(floatVal)).intValue(); //**must be a better way
	}

	double primitiveFractionalPart(double floatVal) {
		return floatVal - (int)floatVal;
	}

	int primitiveExponent(double floatVal) {
		if(floatVal >= 1.0) {
			return (int)StrictMath.floor(StrictMath.log(floatVal) / StrictMath.log(2.0));
		}
		if(floatVal > 0.0) {
			int positive = primitiveExponent(1.0 / floatVal);
			if(floatVal == (1.0 / primitiveTimesTwoPower(1.0, positive))) {
				return -positive;
			}
			return -positive - 1;
		}
		if(floatVal == 0.0) {
			return -1;
		}
		return primitiveExponent(-floatVal);
	}

	double primitiveTimesTwoPower(double floatVal, int power) {
		return floatVal * StrictMath.pow(2.0, power);
	}

	SqueakObject makeFloat(double value) {
		SqueakObject floatClass = SpecialObjects.getSpecialObject(splOb_ClassFloat);
		SqueakObject newFloat = vm.instantiateClass(floatClass, -1);
		newFloat.setFloatBits(value);
		return newFloat;
	}

	public void primitiveMakePoint() {
		Object x = vm.stack.stackValue(1);
		Object y = vm.stack.stackValue(0);
		vm.stack.popNandPush(2, makePointWithXandY(x, y));
	}

	SqueakObject makePointWithXandY(Object x, Object y) {
		SqueakObject pointClass = SpecialObjects.getSpecialObject(splOb_ClassPoint);
		SqueakObject newPoint = vm.instantiateClass(pointClass, 0);
		newPoint.setPointer(Constants.Point_x, x);
		newPoint.setPointer(Constants.Point_y, y);
		return newPoint;
	}

	SqueakObject primitiveNewJavaProxyWithName(){
		SqueakObject o=stackNonInteger(0);
		if (!successFlag) {
			return SpecialObjects.nilObj;
		}
		final String fullClassName=""+o;
		logger.info("primitiveNewJavaProxyWithName:"+o+" ["+o.getClass()+"]");

		return vm.instantiateJavaProxyClass(fullClassName);
		//return SpecialObjects.nilObj;
	}


	SqueakObject primitiveNewWithSize() {
		int size = stackPos32BitValue(0);
		if (!successFlag) {
			return SpecialObjects.nilObj;
		}
		return vm.instantiateClass(((SqueakObject) vm.stack.stackValue(1)), size);
	}

	SqueakObject primitiveNewMethod() {
		Object headerInt = vm.stack.top();
		int byteCount = stackInteger(1);
		int methodHeader = checkSmallInt(headerInt);
		if (!successFlag) {
			return SpecialObjects.nilObj;
		}
		int litCount = (methodHeader >> 9) & 0xFF;
		SqueakObject method = vm.instantiateClass(((SqueakObject) vm.stack.stackValue(2)), byteCount);
		Object[] pointers = new Object[litCount + 1];
		Arrays.fill(pointers, SpecialObjects.nilObj);
		pointers[0] = headerInt;
		method.methodAddPointers(pointers);
		return method;
	}

	//String and Array Primitives
	SqueakObject makeStString(String javaString) {
		byte[] byteString = javaString.getBytes();
		SqueakObject stString = vm.instantiateClass(SpecialObjects.getSpecialObject(splOb_ClassString), javaString.length());
		System.arraycopy(byteString, 0, stString.bits, 0, byteString.length);
		return stString;
	}

	Object primitiveSize() {//Returns size Integer (but may set success false)

		Object rcvr = vm.stack.top();
		int size = indexableSize(rcvr);
		if (size == -1) {
			success(false); //not indexable

		}
		return pos32BitIntFor(size);
	}

	Object primitiveAt(boolean cameFromAtBytecode, boolean convertChars, boolean includeInstVars) {
		//Returns result of at: or sets success false
		SqueakObject array = stackNonInteger(1);
		int index = stackPos32BitValue(0); //note non-int returns zero

		if (!successFlag) {
			return array;
		}
		AtCacheInfo info;
		if (cameFromAtBytecode) {// fast entry checks cache

			info = atCache[array.hashCode() & atCacheMask];
			if (info.array != array) {
				success(false);
				return array;
			}
		} else {// slow entry installs in cache if appropriate

			if (array.format == 6 && SpecialObjects.isA(array, splOb_ClassFloat)) {
				// hack to make Float hash work
				long floatBits = Double.doubleToRawLongBits(array.getFloatBits());
				if (index == 1) {
					return pos32BitIntFor((int) (floatBits >> 32));
				}
				if (index == 2) {
					return pos32BitIntFor((int) (floatBits & 0xFFFFFFFF));
				}
				success(false);
				return array;
			}
			info = makeCacheInfo(atCache, vm.specialSelectors[32], array, convertChars, includeInstVars);
		}
		if (index < 1 || index > info.size) {
			success(false);
			return array;
		}
		if (includeInstVars) //pointers...   instVarAt and objectAt
		{
			return array.pointers[index - 1];
		}
		if (array.format < 6) //pointers...   normal at:
		{
			return array.pointers[index - 1 + info.ivarOffset];
		}
		if (array.format < 8) { // words...

			int value = ((int[]) array.bits)[index - 1];
			return pos32BitIntFor(value);
		}
		if (array.format < 12) { // bytes...

			int value = (((byte[]) array.bits)[index - 1]) & 0xFF;
			if (info.convertChars) {
				return charFromInt(value);
			} else {
				return SmallInteger.smallFromInt(value);
			}
		}
		// methods (format>=12) must simulate Squeak's method indexing
		int offset = array.pointersSize() * 4;
		if (index - 1 - offset < 0) {
			success(false);
			return array;
		} //reading lits as bytes

		return SmallInteger.smallFromInt((((byte[]) array.bits)[index - 1 - offset]) & 0xFF);
	}

	SqueakObject charFromInt(int ascii) {
		SqueakObject charTable = SpecialObjects.getSpecialObject(splOb_CharacterTable);
		return charTable.fetchPointerNI(ascii);
	}

	Object primitiveAtPut(boolean cameFromAtBytecode, boolean convertChars, boolean includeInstVars) {
		//Returns result of at:put: or sets success false
		SqueakObject array = stackNonInteger(2);
		int index = stackPos32BitValue(1); //note non-int returns zero

		if (!successFlag) {
			return array;
		}
		AtCacheInfo info;
		if (cameFromAtBytecode) {// fast entry checks cache

			info = atPutCache[array.hashCode() & atCacheMask];
			if (info.array != array) {
				success(false);
				return array;
			}
		} else {// slow entry installs in cache if appropriate

			info = makeCacheInfo(atPutCache, vm.specialSelectors[34], array, convertChars, includeInstVars);
		}
		if (index < 1 || index > info.size) {
			success(false);
			return array;
		}
		Object objToPut = vm.stack.stackValue(0);
		if (includeInstVars) { // pointers...   instVarAtPut and objectAtPut

			array.pointers[index - 1] = objToPut; //eg, objectAt:

			return objToPut;
		}
		if (array.format < 6) {  // pointers...   normal atPut

			array.pointers[index - 1 + info.ivarOffset] = objToPut;
			return objToPut;
		}
		int intToPut;
		if (array.format < 8) {  // words...

			intToPut = stackPos32BitValue(0);
			if (!successFlag) {
				return objToPut;
			}
			((int[]) array.bits)[index - 1] = intToPut;
			return objToPut;
		}
		// bytes...
		if (info.convertChars) {
			// put a character...
			if (SmallInteger.isSmallInt(objToPut)) {
				success(false);
				return objToPut;
			}
			SqueakObject sqObjToPut = (SqueakObject) objToPut;
			if (!SpecialObjects.isA(sqObjToPut, splOb_ClassCharacter)) {
				success(false);
				return objToPut;
			}
			Object asciiToPut = sqObjToPut.fetchPointer(0);
			if (!(SmallInteger.isSmallInt(asciiToPut))) {
				success(false);
				return objToPut;
			}
			intToPut = SmallInteger.intFromSmall((Integer) asciiToPut);
		} else { // put a byte...

			if (!(SmallInteger.isSmallInt(objToPut))) {
				success(false);
				return objToPut;
			}
			intToPut = SmallInteger.intFromSmall((Integer) objToPut);
		}
		if (intToPut < 0 || intToPut > 255) {
			success(false);
			return objToPut;
		}
		if (array.format < 8) {  // bytes...

			((byte[]) array.bits)[index - 1] = (byte) intToPut;
			return objToPut;
		}
		// methods (format>=12) must simulate Squeak's method indexing
		// If the object is a Large****tiveInteger with a cached BigInteger,
		// the offset must be 0 to avoid confusion.
		boolean hasLarge = array.hasLarge();
		int offset = hasLarge ? 0 : array.pointersSize() * 4;
		if (index - 1 - offset < 0) {
			success(false);
			return array;
		} //writing lits as bytes

		((byte[]) array.bits)[index - 1 - offset] = (byte) intToPut;
		// If the object is a Large****tiveInteger, update the stored BigInteger.
		if(hasLarge) {
			array.invalidateLarge();
			LargeInteger.getOrCacheBig(array);
		}
		return objToPut;
	}

	int indexableSize(Object obj) {
		if (SmallInteger.isSmallInt(obj)) {
			return -1; // -1 means not indexable

		}
		SqueakObject sqObj = (SqueakObject) obj;
		short fmt = sqObj.format;
		if (fmt < 2) {
			return -1; //not indexable

		}
		if (fmt == 3 && vm.stack.isContext(sqObj)) {
			return sqObj.fetchInteger(Constants.Context_stackPointer).intValue();
		}
		if (fmt < 6) {
			return sqObj.pointersSize() - sqObj.instSize(); // pointers

		}
		if (fmt < 12) {
			return sqObj.bitsSize(); // words or bytes

		}
		return sqObj.bitsSize() + (4 * sqObj.pointersSize());
	} // methods


	SqueakObject primitiveStringReplace() {
		SqueakObject dst = (SqueakObject) vm.stack.stackValue(4);
		int dstPos = stackInteger(3) - 1;
		int count = stackInteger(2) - dstPos;
		//	if(count<=0) {success= false; return dst;} //fail for compat, later succeed
		SqueakObject src = (SqueakObject) vm.stack.stackValue(1);
		int srcPos = stackInteger(0) - 1;
		if (!successFlag) {
			return SpecialObjects.nilObj; //some integer not right

		}
		short srcFmt = src.format;
		short dstFmt = dst.format;
		if (dstFmt < 8) {
			if (dstFmt != srcFmt) {
				success(false);
				return dst;
			} //incompatible formats
			else if ((dstFmt & 0xC) != (srcFmt & 0xC)) {
				success(false);
				return dst;
			} //incompatible formats

		}
		if (srcFmt < 4) {//pointer type objects

			int totalLength = src.pointersSize();
			int srcInstSize = src.instSize();
			srcPos += srcInstSize;
			if ((srcPos < 0) || (srcPos + count) > totalLength) {
				success(false);
				return SpecialObjects.nilObj;
			} //would go out of bounds

			totalLength = dst.pointersSize();
			int dstInstSize = dst.instSize();
			dstPos += dstInstSize;
			if ((dstPos < 0) || (dstPos + count) > totalLength) {
				success(false);
				return SpecialObjects.nilObj;
			} //would go out of bounds

			System.arraycopy(src.pointers, srcPos, dst.pointers, dstPos, count);
			return dst;
		} else {//bits type objects

			int totalLength = src.bitsSize();
			if ((srcPos < 0) || (srcPos + count) > totalLength) {
				success(false);
				return SpecialObjects.nilObj;
			} //would go out of bounds

			totalLength = dst.bitsSize();
			if ((dstPos < 0) || (dstPos + count) > totalLength) {
				success(false);
				return SpecialObjects.nilObj;
			} //would go out of bounds

			System.arraycopy(src.bits, srcPos, dst.bits, dstPos, count);
			// If this object is a Large****tiveInteger, update the cached
			// BigInteger.
			if(dst.hasLarge()) {
				dst.invalidateLarge();
				LargeInteger.getOrCacheBig(dst);
			}
			return dst;
		}
	}

	void primitiveNext() {
		SqueakObject stream = stackNonInteger(0);
		if (!successFlag) {
			throw failExpected();
		}
		Object[] streamBody = stream.pointers;
		if (streamBody == null || streamBody.length < (Constants.Stream_limit + 1)) {
			throw failExpected();
		}
		Object array = streamBody[Constants.Stream_array];
		if (SmallInteger.isSmallInt(array)) {
			throw failExpected();
		}
		int index = checkSmallInt(streamBody[Constants.Stream_position]);
		int limit = indexableSize(array);
		if(index >= limit) {
			throw failExpected();
		}
		index++;
		Object result;
		SqueakObject sqArray = (SqueakObject)array;
		int fmt = sqArray.format;
		if(fmt <= 4) {
			result = sqArray.fetchPointer(index - 1);
		} else if(fmt < 8) {
			result = pos32BitIntFor(((int[])sqArray.bits)[index - 1]);
		} else if(fmt >= 16) {
			result = charFromInt(((byte[])sqArray.bits)[index - 1]);
		} else {
			if(SpecialObjects.isA(sqArray, splOb_ClassString)) {
				result = charFromInt(((byte[])sqArray.bits)[index - 1]);
			} else {
				result = SmallInteger.smallFromInt(((byte[])sqArray.bits)[index - 1]);
			}
		}
		if(successFlag) {
			streamBody[Constants.Stream_position] = SmallInteger.smallFromInt(index);
			popNandPushIfOK(1, result);
		} else {
			failExpected();
		}
	}

	void primitiveNextPut() {
		SqueakObject stream = stackNonInteger(1);
		if (!successFlag) {
			throw failExpected();
		}
		Object[] streamBody = stream.pointers;
		if (streamBody == null || streamBody.length < (Constants.Stream_limit + 1)) {
			throw failExpected();
		}
		Object array = streamBody[Constants.Stream_array];
		if (SmallInteger.isSmallInt(array)) {
			throw failExpected();
		}
		int index = checkSmallInt(streamBody[Constants.Stream_position]);
		int limit = indexableSize(array);
		Object value = stack.stackValue(0);
		if(!successFlag) {
			throw failExpected();
		}
		if (index >= limit) {
			throw failExpected();
		}
		index++;
		SqueakObject sqArray = (SqueakObject)array;
		int fmt = sqArray.format;
		if(fmt <= 4) {
			sqArray.setPointer(index - 1, value);
		}
		else if(fmt < 8) {
			((int[])sqArray.bits)[index - 1] = SmallInteger.intFromSmall((Integer)value);
		}
		else {
			Object valToPut;
			if(SpecialObjects.isA(value, splOb_ClassCharacter) || fmt >= 16) {
				valToPut = asciiOfCharacter((SqueakObject)value);
			} else {
				valToPut = value;
			}
			if(SmallInteger.isSmallInt(valToPut)) {
				int intValToPut = SmallInteger.intFromSmall((Integer)valToPut);
				if(!(intValToPut >= 0 && intValToPut <= 255)) {
					throw failExpected();
				}
				if(fmt >= 12 && fmt <= 15) {
					((byte[])sqArray.bits)[index - 4 * sqArray.pointersSize() - 1] = (byte)intValToPut;
				} else {
					((byte[])sqArray.bits)[index - 1] = (byte)intValToPut;
				}
			} else {
				throw failExpected();
			}
		}
		if(successFlag) {
			streamBody[Constants.Stream_position] = SmallInteger.smallFromInt(index);
			popNandPushIfOK(2, value);
		} else {
			throw failExpected();
		}
	}

	Integer asciiOfCharacter(SqueakObject c) {
		if(!SpecialObjects.isA(c, splOb_ClassCharacter)) {
			return SmallInteger.smallFromInt(0);
		} else {
			return c.fetchInteger(Constants.CharacterValueIndex);
		}
	}

	void primitiveAtEnd() {
		SqueakObject stream = (SqueakObject)stack.stackValue(0);
		if (!successFlag) {
			throw failExpected();
		}
		Object[] streamBody = stream.pointers;
		if (streamBody == null || streamBody.length < (Constants.Stream_limit + 1)) {
			throw failExpected();
		}
		Object array = streamBody[Constants.Stream_array];
		int index = checkSmallInt(streamBody[Constants.Stream_position]);
		int limit = indexableSize(array);
		if(successFlag) {
			popNandPushIfOK(1, squeakBool(index >= limit));
		} else {
			throw failExpected();
		}
	}

	SqueakObject primitiveBlockCopy() {
		Object rcvr = vm.stack.stackValue(1);
		if (SmallInteger.isSmallInt(rcvr)) {
			success(false);
		}
		Object sqArgCount = vm.stack.top();
		if (!(SmallInteger.isSmallInt(sqArgCount))) {
			success(false);
		}
		SqueakObject homeCtxt = (SqueakObject) rcvr;
		if (!vm.stack.isContext(homeCtxt)) {
			success(false);
		}
		if (!successFlag) {
			return SpecialObjects.nilObj;
		}
		if (SmallInteger.isSmallInt(homeCtxt.fetchPointer(Constants.Context_method))) // ctxt is itself a block; get the context for its enclosing method
		{
			homeCtxt = homeCtxt.fetchPointerNI(Constants.BlockContext_home);
		}
		int blockSize = homeCtxt.pointersSize() - homeCtxt.instSize(); //can use a const for instSize

		SqueakObject newBlock = vm.instantiateClass((SpecialObjects.getSpecialObject(splOb_ClassBlockContext)), blockSize);
		Integer initialPC = vm.encodeSqueakPC(vm.pc + 2, vm.method); //*** check this...

		newBlock.setPointer(Constants.BlockContext_initialIP, initialPC);
		newBlock.setPointer(Constants.Context_instructionPointer, initialPC);// claim not needed; value will set it

		newBlock.setPointer(Constants.Context_stackPointer, SmallInteger.smallFromInt(0));
		newBlock.setPointer(Constants.BlockContext_argumentCount, sqArgCount);
		newBlock.setPointer(Constants.BlockContext_home, homeCtxt);
		newBlock.setPointer(Constants.Context_sender, SpecialObjects.nilObj);
		return newBlock;
	}

	void primitiveBlockValue(int argCount) {
		Object rcvr = vm.stack.stackValue(argCount);
		if (!SpecialObjects.isA(rcvr, splOb_ClassBlockContext)) {
			throw failExpected();
		}
		SqueakObject block = (SqueakObject) rcvr;
		Object blockArgCount = block.fetchPointer(Constants.BlockContext_argumentCount);
		if (!SmallInteger.isSmallInt(blockArgCount)) {
			throw failExpected();
		}
		if ((((Integer) blockArgCount).intValue() != argCount)) {
			throw failExpected();
		}
		if (block.fetchPointer(Constants.BlockContext_caller) != SpecialObjects.nilObj) {
			throw failExpected();
		}
		System.arraycopy(vm.activeContext.pointers, vm.stack.sp - argCount + 1, block.pointers, Constants.Context_tempFrameStart, argCount);
		Integer initialIP = block.fetchInteger(Constants.BlockContext_initialIP);
		block.setPointer(Constants.Context_instructionPointer, initialIP);
		block.setPointer(Constants.Context_stackPointer, new Integer(argCount));
		block.setPointer(Constants.BlockContext_caller, vm.activeContext);
		vm.stack.popN(argCount + 1);
		vm.newActiveContext(block);
	}

	Object primitiveHash() {
		Object rcvr = vm.stack.top();
		if (SmallInteger.isSmallInt(rcvr)) {
			success(false);
			return SpecialObjects.nilObj;
		}
		return new Integer(((SqueakObject) rcvr).hash);
	}

	Object setLowSpaceThreshold() {
		int nBytes = stackInteger(0);
		if (successFlag) {
			vm.lowSpaceThreshold = nBytes;
		}
		return vm.stack.stackValue(1);
	}

	// Scheduler Primitives
	SqueakObject getScheduler() {
		SqueakObject assn = SpecialObjects.getSpecialObject(splOb_SchedulerAssociation);
		return assn.fetchPointerNI(Constants.Assn_value);
	}

	void processResume() {
		SqueakObject process = (SqueakObject) vm.stack.top();
		resume(process);
	}

	void processSuspend() {
		SqueakObject activeProc = getScheduler().fetchPointerNI(Constants.ProcSched_activeProcess);
		if (vm.stack.top() != activeProc) {
			throw failExpected();
		}
		vm.stack.popNandPush(1, SpecialObjects.nilObj);
		transferTo(pickTopProcess());
	}

	void semaphoreWait() {
		SqueakObject sema = (SqueakObject) vm.stack.top();
		if (!SpecialObjects.isA(sema, splOb_ClassSemaphore)) {
			throw failExpected();
		}
		int excessSignals = sema.fetchInteger(Constants.Semaphore_excessSignals).intValue();
		if (excessSignals > 0) {
			sema.setPointer(Constants.Semaphore_excessSignals, SmallInteger.smallFromInt(excessSignals - 1));
		} else {
			SqueakObject activeProc = getScheduler().fetchPointerNI(Constants.ProcSched_activeProcess);
			linkProcessToList(activeProc, sema);
			transferTo(pickTopProcess());
		}
	}

	void semaphoreSignal() {
		SqueakObject sema = (SqueakObject) vm.stack.top();
		if (!SpecialObjects.isA(sema, splOb_ClassSemaphore)) {
			throw failExpected();
		}
		synchronousSignal(sema);
	}

	public void synchronousSignal(SqueakObject sema) {
		if (isEmptyList(sema)) {
			//no process is waiting on this semaphore"
			int excessSignals = sema.fetchInteger(Constants.Semaphore_excessSignals).intValue();
			sema.setPointer(Constants.Semaphore_excessSignals, SmallInteger.smallFromInt(excessSignals + 1));
		} else {
			resume(removeFirstLinkOfList(sema));
		}
		return;
	}

	void resume(SqueakObject newProc) {
		SqueakObject activeProc = getScheduler().fetchPointerNI(Constants.ProcSched_activeProcess);
		int activePriority = activeProc.fetchInteger(Constants.Proc_priority).intValue();
		int newPriority = newProc.fetchInteger(Constants.Proc_priority).intValue();
		if (newPriority > activePriority) {
			putToSleep(activeProc);
			transferTo(newProc);
		} else {
			putToSleep(newProc);
		}
	}

	void putToSleep(SqueakObject aProcess) {
		//Save the given process on the scheduler process list for its priority.
		int priority = aProcess.fetchInteger(Constants.Proc_priority).intValue();
		SqueakObject processLists = getScheduler().fetchPointerNI(Constants.ProcSched_processLists);
		SqueakObject processList = processLists.fetchPointerNI(priority - 1);
		linkProcessToList(aProcess, processList);
	}

	void transferTo(SqueakObject newProc) { //Record a process to be awakened on the next interpreter cycle.

		SqueakObject sched = getScheduler();
		SqueakObject oldProc = sched.fetchPointerNI(Constants.ProcSched_activeProcess);
		sched.setPointer(Constants.ProcSched_activeProcess, newProc);
		oldProc.setPointer(Constants.Proc_suspendedContext, vm.activeContext);
		//int prio= SmallInteger.intFromSmall((Integer)newProc.pointers[Squeak.Proc_priority]);
		//System.err.println("Transfer to priority " + prio + " at byteCount " + vm.byteCount);
		//if(prio==8)
		//    vm.dumpStack();
		vm.newActiveContext(newProc.fetchPointerNI(Constants.Proc_suspendedContext));
		//System.err.println("new pc is " + vm.pc + "; method offset= " + ((vm.method.pointers.length+1)*4));
		newProc.setPointer(Constants.Proc_suspendedContext, SpecialObjects.nilObj);
		vm.reclaimableContextCount = 0;
	}

	SqueakObject pickTopProcess() { // aka wakeHighestPriority
		//Return the highest priority process that is ready to run.
		//Note: It is a fatal VM error if there is no runnable process.

		SqueakObject schedLists = getScheduler().fetchPointerNI(Constants.ProcSched_processLists);
		int p = schedLists.pointersSize() - 1;  // index of last indexable field"

		p = p - 1;
		SqueakObject processList = schedLists.fetchPointerNI(p);
		while (isEmptyList(processList)) {
			p = p - 1;
			if (p < 0) {
				return SpecialObjects.nilObj; //self error: 'scheduler could not find a runnable process' ].

			}
			processList = schedLists.fetchPointerNI(p);
		}
		return removeFirstLinkOfList(processList);
	}

	void linkProcessToList(SqueakObject proc, SqueakObject aList) {
		// Add the given process to the given linked list and set the backpointer
		// of process to its new list."
		if (isEmptyList(aList)) {
			aList.setPointer(Constants.LinkedList_firstLink, proc);
		} else {
			SqueakObject lastLink = aList.fetchPointerNI(Constants.LinkedList_lastLink);
			lastLink.setPointer(Constants.Link_nextLink, proc);
		}
		aList.setPointer(Constants.LinkedList_lastLink, proc);
		proc.setPointer(Constants.Proc_myList, aList);
	}

	boolean isEmptyList(SqueakObject aLinkedList) {
		return aLinkedList.fetchPointerNI(Constants.LinkedList_firstLink) == SpecialObjects.nilObj;
	}

	SqueakObject removeFirstLinkOfList(SqueakObject aList) {
		//Remove the first process from the given linked list."
		SqueakObject first = aList.fetchPointerNI(Constants.LinkedList_firstLink);
		SqueakObject last = aList.fetchPointerNI(Constants.LinkedList_lastLink);
		if (first == last) {
			aList.setPointer(Constants.LinkedList_firstLink, SpecialObjects.nilObj);
			aList.setPointer(Constants.LinkedList_lastLink, SpecialObjects.nilObj);
		} else {
			SqueakObject next = first.fetchPointerNI(Constants.Link_nextLink);
			aList.setPointer(Constants.LinkedList_firstLink, next);
		}
		first.setPointer(Constants.Link_nextLink, SpecialObjects.nilObj);
		return first;
	}

	SqueakObject primitiveObjectPointsTo() {
		Object thang = stack.stackValue(0);
		Object rcvr = stack.stackValue(1);
		if(SmallInteger.isSmallInt(rcvr)) {
			return squeakBool(false);
		}
		SqueakObject sqr = (SqueakObject)rcvr;
		if(!sqr.isPointers()) {
			throw failExpected();
		}
		for(int i = 0; i < sqr.pointersSize(); i++) {
			if(sqr.fetchPointer(i) == thang) {
				return squeakBool(true);
			}
		}
		return squeakBool(false);
	}

	SqueakObject registerSemaphore(int specialObjSpec) {
		SqueakObject sema = (SqueakObject) vm.stack.top();
		SpecialObjects.registerSpecialObject(sema,specialObjSpec, splOb_ClassSemaphore );
		return (SqueakObject) vm.stack.stackValue(1);
	}

	Object primitiveSignalAtMilliseconds() { //Delay signal:atMs:

		int msTime = stackInteger(0);
		Object sema = stackNonInteger(1);
		Object rcvr = stackNonInteger(2);
		if (!successFlag) {
			return SpecialObjects.nilObj;
			//System.err.println("Signal at " + msTime);
			//vm.dumpStack();
		}
		if (SpecialObjects.isA(sema, splOb_ClassSemaphore)) {
			SpecialObjects.registerSpecialObject((SqueakObject)sema, splOb_TheTimerSemaphore, splOb_ClassSemaphore);
			interruptHandler.nextWakeupTick = msTime;
		} else {
			SpecialObjects.registerSpecialObject(SpecialObjects.nilObj, splOb_TheTimerSemaphore, splOb_ClassSemaphore);
			interruptHandler.nextWakeupTick = 0;
		}
		return rcvr;
	}

	//Other Primitives
	Integer millisecondClockValue() {
		//Return the value of the millisecond clock as an integer.
		//Note that the millisecond clock wraps around periodically.
		//The range is limited to SmallInteger maxVal / 2 to allow
		//delays of up to that length without overflowing a SmallInteger."
		return SmallInteger.smallFromInt((int) (System.currentTimeMillis() & (SmallInteger.maxSmallInt >> 1)));
	}

	/*
    primitiveBeDisplay
	"Record the system Display object in the specialObjectsTable."
	| rcvr |
	rcvr := self stackTop.
	self success: ((self isPointers: rcvr) and: [(self lengthOf: rcvr) >= 4]).
	successFlag ifTrue: [self storePointer: TheDisplay ofObject: specialObjectsOop withValue: rcvr]
	 */
	void beDisplay() {
		SqueakObject rcvr = (SqueakObject) vm.stack.top(); // rcvr := self stackTop.
		success(rcvr.isPointers() && rcvr.lengthOf() >= 4); // self success: ((self isPointers: rcvr) and: [(self lengthOf: rcvr) >= 4]).

		if(successFlag){ // successFlag ifTrue: [self storePointer: TheDisplay ofObject: specialObjectsOop withValue: rcvr]
			//SpecialObjects.specialObjects[splOb_TheDisplay] = rcvr;
			SpecialObjects.forceRegisterSpecialObject(rcvr, splOb_TheDisplay);
		}

		FormCache disp = new FormCache(rcvr, vm);
		if (disp.squeakForm == null) {
			throw failExpected();
		}
		displayBitmap = disp.bits;
		boolean remap = theDisplay != null;
		if (remap) {
			Dimension requestedExtent = new Dimension(disp.width, disp.height);
			if (!theDisplay.getExtent().equals(requestedExtent)) {
				System.err.println("Squeak: changing screen size to " + disp.width + "@" + disp.height);
				theDisplay.setExtent(requestedExtent);
			}
		} else {
			theDisplay = new Screen("Potato", disp.width, disp.height, disp.depth, vm);
		}

		theDisplay.setBits(displayBitmap, disp.depth);

		if (!remap) {
			theDisplay.open();
		}
	}

	//    /*
	//    primitiveBeCursor
	//	"Set the cursor to the given shape. The Mac only supports 16x16 pixel cursors. Cursor offsets are handled by Smalltalk."
	//
	//	| cursorObj maskBitsIndex maskObj bitsObj extentX extentY depth offsetObj offsetX offsetY cursorBitsIndex ourCursor |
	//	argumentCount = 0 ifTrue: [
	//		cursorObj := self stackTop.
	//		maskBitsIndex := nil].
	//	argumentCount = 1 ifTrue: [
	//		cursorObj := self stackValue: 1.
	//		maskObj := self stackTop].
	//	self success: (argumentCount < 2).
	//
	//	self success: ((self isPointers: cursorObj) and: [(self lengthOf: cursorObj) >= 5]).
	//	successFlag ifTrue: [
	//		bitsObj := self fetchPointer: 0 ofObject: cursorObj.
	//		extentX := self fetchInteger: 1 ofObject: cursorObj.
	//		extentY := self fetchInteger: 2 ofObject: cursorObj.
	//		depth := self fetchInteger: 3 ofObject: cursorObj.
	//		offsetObj := self fetchPointer: 4 ofObject: cursorObj].
	//		self success: ((self isPointers: offsetObj) and: [(self lengthOf: offsetObj) >= 2]).
	//
	//	successFlag ifTrue: [
	//		offsetX := self fetchInteger: 0 ofObject: offsetObj.
	//		offsetY := self fetchInteger: 1 ofObject: offsetObj.
	//		self success: ((extentX = 16) and: [extentY = 16 and: [depth = 1]]).
	//		self success: ((offsetX >= -16) and: [offsetX <= 0]).
	//		self success: ((offsetY >= -16) and: [offsetY <= 0]).
	//		self success: ((self isWords: bitsObj) and: [(self lengthOf: bitsObj) = 16]).
	//		cursorBitsIndex := bitsObj + BaseHeaderSize.
	//		self cCode: '' inSmalltalk:
	//			[ourCursor := Cursor
	//				extent: extentX @ extentY
	//				fromArray: ((1 to: 16) collect: [:i |
	//					((self fetchWord: i-1 ofObject: bitsObj) >> 16) bitAnd: 16rFFFF])
	//				offset: offsetX  @ offsetY]].
	//
	//	argumentCount = 1 ifTrue: [
	//		self success: ((self isPointers: maskObj) and: [(self lengthOf: maskObj) >= 5]).
	//		successFlag ifTrue: [
	//			bitsObj := self fetchPointer: 0 ofObject: maskObj.
	//			extentX := self fetchInteger: 1 ofObject: maskObj.
	//			extentY := self fetchInteger: 2 ofObject: maskObj.
	//			depth := self fetchInteger: 3 ofObject: maskObj].
	//
	//		successFlag ifTrue: [
	//			self success: ((extentX = 16) and: [extentY = 16 and: [depth = 1]]).
	//			self success: ((self isWords: bitsObj) and: [(self lengthOf: bitsObj) = 16]).
	//			maskBitsIndex := bitsObj + BaseHeaderSize]].
	//
	//	successFlag ifTrue: [
	//		argumentCount = 0
	//			ifTrue: [self cCode: 'ioSetCursor(cursorBitsIndex, offsetX, offsetY)'
	//						inSmalltalk: [ourCursor show]]
	//			ifFalse: [self cCode: 'ioSetCursorWithMask(cursorBitsIndex, maskBitsIndex, offsetX, offsetY)'
	//						inSmalltalk: [ourCursor show]].
	//		self pop: argumentCount].
	//     */
	void beCursor(int argCount) {
		// For now we ignore the white outline form (maskObj)
		if (theDisplay == null) {
			return;
		}

		SqueakObject cursorObj = SpecialObjects.nilObj;
		SqueakObject maskBitsIndex;
		SqueakObject bitsObj = SpecialObjects.nilObj;
		SqueakObject offsetObj = SpecialObjects.nilObj;
		int extentX, extentY, depth, offsetX, offsetY;
		extentX = extentY = depth = 0;

		if (argCount == 0) { // argumentCount = 0 ifTrue: [
			cursorObj = stackNonInteger(0); // cursorObj := self stackTop.
			maskBitsIndex = SpecialObjects.nilObj; // maskBitsIndex := nil].
		}
		if(argCount == 1) {
			cursorObj = stackNonInteger(1); // cursorObj := self stackValue: 1.
			maskBitsIndex = stackNonInteger(0); // maskObj := self stackTop].
		}
		//        success(argCount < 2); // self success: (argumentCount < 2).
		//
		//        success(cursorObj.isPointers() && (cursorObj.lengthOf() >= 5)); // self success: ((self isPointers: cursorObj) and: [(self lengthOf: cursorObj) >= 5]).
		//
		//        if(successFlag){ // successFlag ifTrue: [
		//            bitsObj = cursorObj.fetchPointerNI(0); // bitsObj := self fetchPointer: 0 ofObject: cursorObj.
		//            extentX = cursorObj.fetchInteger(1); // extentX := self fetchInteger: 1 ofObject: cursorObj.
		//            extentY = cursorObj.fetchInteger(2); // extentY := self fetchInteger: 2 ofObject: cursorObj.
		//            depth = cursorObj.fetchInteger(3); // depth := self fetchInteger: 3 ofObject: cursorObj.
		//            offsetObj = cursorObj.fetchPointerNI(4); // offsetObj := self fetchPointer: 4 ofObject: cursorObj].
		//
		//            success(offsetObj.isPointers() && (offsetObj.lengthOf() >= 2)); // self success: ((self isPointers: offsetObj) and: [(self lengthOf: offsetObj) >= 2]).
		//        }
		//
		//        if(successFlag){
		//            offsetX = offsetObj.fetchInteger(0); // offsetX := self fetchInteger: 0 ofObject: offsetObj.
		//            offsetY = offsetObj.fetchInteger(1); // offsetY := self fetchInteger: 1 ofObject: offsetObj.
		//            success((extentX == 16) && (extentY == 16 && depth == 1)); // self success: ((extentX = 16) and: [extentY = 16 and: [depth = 1]]).
		//            success((offsetX >= -16) && (offsetX <= 0)); // self success: ((offsetX >= -16) and: [offsetX <= 0]).
		//            success((offsetY >= -16) && (offsetY <= 0)); // self success: ((offsetY >= -16) and: [offsetY <= 0]).
		//            success(bitsObj.isWords() && (bitsObj.lengthOf() == 16)); // self success: ((self isWords: bitsObj) and: [(self lengthOf: bitsObj) = 16]).
		////		cursorBitsIndex := bitsObj + BaseHeaderSize.
		////		self cCode: '' inSmalltalk:
		////			[ourCursor := Cursor
		////				extent: extentX @ extentY
		////				fromArray: ((1 to: 16) collect: [:i |
		////					((self fetchWord: i-1 ofObject: bitsObj) >> 16) bitAnd: 16rFFFF])
		////				offset: offsetX  @ offsetY]].
		//        }



		FormCache cursorForm = new FormCache(cursorObj, vm);
		if (!successFlag || cursorForm.squeakForm == null) {
			throw failExpected();
		}
		//Following code for offset is not yet used...
		offsetObj = checkNonSmallInt(cursorObj.fetchPointer(4));
		if (!SpecialObjects.isA(offsetObj, splOb_ClassPoint)) {
			throw failExpected();
		}
		offsetX = checkSmallInt(offsetObj.pointers[0]);
		offsetY = checkSmallInt(offsetObj.pointers[1]);
		if (!successFlag) {
			throw failExpected();
		}
		//Current cursor code in Screen expects cursor and mask to be packed in cursorBytes
		//For now we make them be equal copies of incoming 16x16 cursor
		theDisplay.setCursor(cursorForm.bits, BWMask);
	}

	void primitiveYield(int numArgs) { // halts execution until EHT callbacks notify us
		long millis = 100;
		if (numArgs > 1) {
			throw failExpected();
		}
		if (numArgs > 0) { // But, for now, wait time is ignored...
			int micros = stackInteger(0);
			if (!successFlag) {
				throw failExpected();
			}
			vm.stack.pop();
			millis = micros / 1000;
		}
		// try { synchronized (vm) { vm.wait(); }
		//         } catch (InterruptedException e) { }
		// TODO how to handle third-party interruptions?

		synchronized (vm) {
			try {
				while (!vm.screenEvent) {
					vm.wait(millis);
				}
			} catch (InterruptedException ex) {
				Logger.getLogger(PrimitiveHandler.class.getName()).log(Level.SEVERE, null, ex);
			}
		}
	}

	SqueakObject primitiveMousePoint() {
		SqueakObject pointClass = SpecialObjects.getSpecialObject(splOb_ClassPoint);
		SqueakObject newPoint = vm.instantiateClass(pointClass, 0);
		Point lastMouse = theDisplay.getLastMousePoint();
		newPoint.setPointer(Constants.Point_x, SmallInteger.smallFromInt(lastMouse.x));
		newPoint.setPointer(Constants.Point_y, SmallInteger.smallFromInt(lastMouse.y));
		return newPoint;
	}

	Integer primitiveMouseButtons() {
		return SmallInteger.smallFromInt(theDisplay.getLastMouseButtonStatus());
	}

	Object primitiveKbdNext() {
		return SmallInteger.smallFromInt(theDisplay.keyboardNext());
	}

	Object primitiveKbdPeek() {
		if (theDisplay == null) {
			return SpecialObjects.nilObj;
		}
		int peeked = theDisplay.keyboardPeek();
		return peeked == 0 ? (Object) SpecialObjects.nilObj : SmallInteger.smallFromInt(peeked);
	}

	SqueakObject primitiveArrayBecome(boolean doBothWays) {
		// Should flush method cache
		SqueakObject rcvr = stackNonInteger(1);
		SqueakObject arg = stackNonInteger(0);
		if (!successFlag) {
			return rcvr;
		}
		success(objectTable.bulkBecome(rcvr.pointers, arg.pointers, doBothWays));
		return rcvr;
	}

	SqueakObject primitiveSomeObject() {
		return objectTable.nextInstance(0, null);
	}

	SqueakObject primitiveSomeInstance(SqueakObject sqClass) {
		return objectTable.nextInstance(0, sqClass);
	}

	Object primitiveNextObject(SqueakObject priorObject) {
		SqueakObject nextObject = objectTable.nextInstance(objectTable.otIndexOfObject(priorObject) + 1, null);
		if (nextObject == SpecialObjects.nilObj) {
			return SmallInteger.smallFromInt(0);
		}
		return nextObject;
	}

	SqueakObject primitiveNextInstance(SqueakObject priorInstance) {
		SqueakObject sqClass = (SqueakObject) priorInstance.sqClass;
		return objectTable.nextInstance(objectTable.otIndexOfObject(priorInstance) + 1, sqClass);
	}

	Object primSeconds() {
		int secs = (int) (System.currentTimeMillis() / 1000); //milliseconds -> seconds

		secs += ((69 * 365 + 17) * 24 * 3600); //Adjust from 1901 to 1970

		return pos32BitIntFor(secs);
	}

	void success(boolean value){
		successFlag = successFlag && value;
	}

	//
	// addenda (primitives)
	//

	int primitiveStringCompareWithCollated() {
		SqueakObject string1 = (SqueakObject)vm.stack.stackValue(2);
		SqueakObject string2 = (SqueakObject)vm.stack.stackValue(1);
		SqueakObject order = (SqueakObject)vm.stack.stackValue(0);
		int len1 = ((byte[])string1.bits).length; // string1 size
		int len2 = ((byte[])string2.bits).length; // string2 size
		for(int i = 0; i < Math.min(len1, len2); i++) {
			char c1 = (char)((byte[])order.bits)[((byte[])string1.bits)[i]]; // order at: (string1 basicAt: i) + 1
			char c2 = (char)((byte[])order.bits)[((byte[])string2.bits)[i]]; // order at: (string2 basicAt: i) + 1
			if(c1 != c2) {
				if(c1 < c2) {
					return 1;
				} else {
					return 3;
				}
			}
		}
		if(len1 == len2) {
			return 2;
		}
		if(len1 < len2) {
			return 1;
		}
		return 3;
	}

	void primitiveStringTranslateFromToTable() {
		SqueakObject string = stackNonInteger(3);
		int start = stackInteger(2);
		int stop = stackInteger(1);
		SqueakObject table = stackNonInteger(0);
		if(!successFlag) {
			throw failExpected();
		}
		byte[] stringBits = (byte[])string.bits;
		byte[] tableBits = (byte[])table.bits;
		for(int k = start; k <= stop; k++) {
			stringBits[k - 1] = tableBits[stringBits[k - 1]];
		}
		stack.popN(4);
	}

	int primitiveStringIndexOfAsciiInStringStartingAt() {
		int startAt = stackInteger(0);
		if(!successFlag) {
			throw new UnexpectedPrimitiveFailedException("startAt is not an int");
		}
		SqueakObject str = stackNonInteger(1);
		SqueakObject rcvr = stackNonInteger(3);
		byte ascii = (byte)stackInteger(2);
		if(!successFlag) {
			throw new UnexpectedPrimitiveFailedException("ascii is not an int");
		}
		int size = str.bitsSize();
		for(int k = startAt; k <= size; k++) {
			if(((byte[])str.bits)[k - 1] == ascii) {
				return k;
			}
		}
		return 0;
	}

	/**
	 * This method is to be used to push the result of a LargeInteger primitive.
	 * If the result of the primitive is a SmallInteger, the passed BigInteger
	 * is coerced into a SmallInteger and pushed. Otherwise, the result is a
	 * Large****tiveInteger, which is pushed if possible.
	 *
	 * @param big the result of a LargeInteger primitive.
	 */
	void pop2andPushPossiblyCoercedBigIfOK(BigInteger big) {
		if(LargeInteger.isBig(big)) {
			if(big.compareTo(BigInteger.ZERO) > 0) {
				byte[] lpi_bytes = LargeInteger.squeakBytes(big);
				SqueakObject squeak_result = vm.instantiateClass(
						SpecialObjects.getSpecialObject(splOb_ClassLargePositiveInteger),
						lpi_bytes.length
						);
				System.arraycopy(lpi_bytes, 0, squeak_result.bits, 0, lpi_bytes.length);
				squeak_result.assignLarge(big);
				popNandPushIfOK(2, squeak_result);
			} else {
				// Unfortunately, LargeNegativeInteger is not available from the
				// special objects array right now, so we can't create such an
				// object here.
				throw failExpected();
			}
		} else {
			popNandPushIntIfOK(2, big.intValue());
		}
	}



}