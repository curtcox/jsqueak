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

/*
Portions of the software are derived from classes of the VMMaker-Package 3.8b3.
The Smalltalk code is still annotated as comments.
 */

package org.squeak.potato.drawing;

import java.awt.Rectangle;

import org.squeak.potato.Arithmetics;
import org.squeak.potato.objects.SmallInteger;
import org.squeak.potato.objects.SpecialObjects;
import org.squeak.potato.objects.SqueakObject;
import org.squeak.potato.primitives.PrimitiveHandler;
import org.squeak.potato.tools.DebugHelper;
import org.squeak.potato.vm.Stack;
import org.squeak.potato.vm.VM;

/**
 * @author Dan Ingalls
 *
 * @author Frank Feinbube
 * @author Robert Wierschke
 * A transcription of the Squeak BitBlt into Java.
 * Will eventually implement the full BitBlt plus Warp Drive(tm).
 */
public class BitBlt {
    // Bitblt layout:
    public final static int Bitblt_function = 0;
    public final static int Bitblt_gray = 1;
    public final static int Bitblt_destbits = 2;
    public final static int Bitblt_destraster = 3;
    public final static int Bitblt_destx = 4;
    public final static int Bitblt_desty = 5;
    public final static int Bitblt_width = 6;
    public final static int Bitblt_height = 7;
    public final static int Bitblt_sourcebits = 8;
    public final static int Bitblt_sourceraster = 9;
    public final static int Bitblt_sourcex = 10;
    public final static int Bitblt_sourcey = 11;
    public final static int Bitblt_clipx = 12;
    public final static int Bitblt_clipy = 13;
    public final static int Bitblt_clipwidth = 14;
    public final static int Bitblt_clipheight = 15;
    public final static int Bitblt_sourcefield = 16;
    public final static int Bitblt_destfield = 17;
    public final static int Bitblt_source = 18;
    public final static int Bitblt_dest = 19;
    private final VM vm;
    private final Stack stack;
    private final MergeFnwith mergeFnwith;
    public SqueakObject destForm;
    public FormCache dest;
    public int destX,  destY,  width,  height;
    private int destIndex;
    private int destDelta;
    private int dstBitShift;
    private boolean noSource;
    public SqueakObject sourceForm;
    public FormCache source;
    public int sourceX,  sourceY;
    private int sourceIndex;
    private int sourceDelta;
    private int srcBitShift;
    private int sourceAlpha;
    private boolean noHalftone;
    private SqueakObject halftoneForm;
    private int[] halftoneBits;
    private int halftoneHeight;
    public boolean success;
    private boolean destIsDisplay;
    private int clipX,  clipY,  clipWidth,  clipHeight;
    private boolean isWarping;
    public int combinationRule;
    public int bitCount;
    private int skew;
    private int mask1,  mask2;
    private boolean preload;
    private int nWords;
    private int destMask;
    private int hDir,  vDir;
    private int sx,  sy;
    private int dx,  dy;
    private int bbW,  bbH;
    private SqueakObject bitBltOop;
    private int affectedL,  affectedR,  affectedT,  affectedB;
    private int opTable;
    private int ditherMatrix4x4;
    private int ditherThresholds16;
    private int ditherValues16;
    private boolean hasSurfaceLock;
    private int warpSrcShift;
    private int warpSrcMask;
    private int warpAlignShift;
    private int warpAlignMask;
    private int warpBitShiftTable;
    private int querySurfaceFn;
    private int lockSurfaceFn;
    private int unlockSurfaceFn;
    private int methodArgumentCount;
    public int cmFlags;
    public int cmMask;
    private int[] cmShiftTable;
    private int[] cmMaskTable;
    public int[] cmLookupTable;
    public int cmBitsPerColor;
    final static int RedIndex = 0;
    final static int GreenIndex = 1;
    final static int BlueIndex = 2;
    final static int AlphaIndex = 3;
    final static int ColorMapPresent = 1;
    final static int ColorMapFixedPart = 2;
    final static int ColorMapIndexedPart = 4;
    final static int ColorMapNewStyle = 8;
    // "BitBlt fields"
    final static int BBDestFormIndex = 0;
    final static int BBSourceFormIndex = 1;
    final static int BBHalftoneFormIndex = 2;
    final static int BBRuleIndex = 3;
    final static int BBDestXIndex = 4;
    final static int BBDestYIndex = 5;
    final static int BBWidthIndex = 6;
    final static int BBHeightIndex = 7;
    final static int BBSourceXIndex = 8;
    final static int BBSourceYIndex = 9;
    final static int BBClipXIndex = 10;
    final static int BBClipYIndex = 11;
    final static int BBClipWidthIndex = 12;
    final static int BBClipHeightIndex = 13;
    final static int BBColorMapIndex = 14;
    final static int BBWarpBase = 15;
    final static int BBLastIndex = 15;
    final static int BBXTableIndex = 16;
    // "Form fields"
    final static int FormBitsIndex = 0;
    final static int FormWidthIndex = 1;
    final static int FormHeightIndex = 2;
    final static int FormDepthIndex = 3;
    final static int FN_XOR = 2;
    final static int FN_STORE_CONST = 12;
    final static int AllOnes = 0xFFFFFFFF;
    public final static int maskTable[] = {
        // Squeak's table for masking pixels within a word, based on depth'
        //	#(1 2 4 5 8 16 32) do:[:i| maskTable at: i put: (1 << i)-1].
        0x0,
        0x1, 0x3, 0, 0xF, 0x1F, 0, 0, 0xFF,
        0, 0, 0, 0, 0, 0, 0, 0xFFFF,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0xFFFFFFFF
    };

    DebugHelper debugHelper;

    public BitBlt(VM theVM) {
        vm = theVM;
        stack = theVM.stack;
        mergeFnwith = new MergeFnwith(this);
        dest = new FormCache();
        source = new FormCache();
        debugHelper = new DebugHelper(this);
    }

    /*
    primitiveCopyBits
	"Invoke the copyBits primitive. If the destination is the display, then copy it to the screen."
	| rcvr |
	self export: true.
	rcvr := interpreterProxy stackValue: interpreterProxy methodArgumentCount.
	(self loadBitBltFrom: rcvr)  ifFalse:[^interpreterProxy primitiveFail].
	self copyBits.
	interpreterProxy failed ifTrue:[^nil].
	self showDisplayBits.
	interpreterProxy failed ifTrue:[^nil].
	interpreterProxy pop: interpreterProxy methodArgumentCount.
	(combinationRule = 22) | (combinationRule = 32) ifTrue:[
		interpreterProxy pop: 1.
		^ interpreterProxy pushInteger: bitCount].
     */
    public void primitiveCopyBits(int argCount, Screen theDisplay) { // no rcvr class check, to allow unknown subclasses (e.g. under Turtle)
        SqueakObject rcvr;
        rcvr = (SqueakObject) stack.stackValue(argCount); // rcvr := interpreterProxy stackValue: interpreterProxy methodArgumentCount.

        if (!loadBitBltFrom(rcvr, argCount)) { // (self loadBitBltFrom: rcvr)
            success = false;
            throw PrimitiveHandler.failExpected();
        }

        copyBits(); // self copyBits.

        if( failed())
		 {
			return; // ifTrue:[^nil].
		}

        showDisplayBits(theDisplay); // self showDisplayBits.
        if( failed())
		 {
			return; // ifTrue:[^nil].
		}

        stack.popN(argCount); // interpreterProxy pop: interpreterProxy methodArgumentCount.

        if (combinationRule == 22 || combinationRule == 32) { // (combinationRule = 22) | (combinationRule = 32) ifTrue:[
            stack.popN(1); // interpreterProxy pop: 1.
            stack.push(SmallInteger.smallFromInt(bitCount)); // ^ interpreterProxy pushInteger: bitCount].
        }
    }

     /*
    loadBitBltFrom: bbObj
	"Load BitBlt from the oop.
	This function is exported for the Balloon engine."
	self export: true.
	^self loadBitBltFrom: bbObj warping: false.
     */
    boolean loadBitBltFrom(SqueakObject bbObj, int argCount) {
         return loadBitBltFromWarping(bbObj, false, argCount);
    }

    /*
    showDisplayBits
	interpreterProxy
		showDisplayBits: destForm
		Left: affectedL
		Top: affectedT
		Right: affectedR
		Bottom: affectedB
     */
    void showDisplayBits(Screen theDisplay){
        Rectangle affectedArea = new Rectangle(affectedL, affectedT, affectedR - affectedL, affectedB - affectedT);
        if (/*GG affectedArea != null &&*/ theDisplay != null) {
            theDisplay.redisplay(false, affectedArea); // self showDisplayBits.
        }
    }

    /*
    primitiveWarpBits
	"Invoke the warpBits primitive. If the destination is the display, then copy it to the screen."
	| rcvr |
	self export: true.
	rcvr := interpreterProxy stackValue: interpreterProxy methodArgumentCount.
	(self loadWarpBltFrom: rcvr)
		ifFalse:[^interpreterProxy primitiveFail].
	self warpBits.
	interpreterProxy failed ifTrue:[^nil].
	self showDisplayBits.
	interpreterProxy failed ifTrue:[^nil].
	interpreterProxy pop: interpreterProxy methodArgumentCount.
     */
    public boolean primitiveWarpBits(int argCount, Screen theDisplay) { // no rcvr class check, to allow unknown subclasses (e.g. under Turtle)
        SqueakObject rcvr;
        rcvr = (SqueakObject) stack.stackValue(argCount); // rcvr := interpreterProxy stackValue: interpreterProxy methodArgumentCount.

        if (!loadWarpBltFrom(rcvr, argCount)) { // (self loadWarpBltFrom: rcvr)
            success = false;
            throw PrimitiveHandler.failExpected();
        }

        warpBits(); // self warpBits.
        if( failed())
		 {
			return true; // ifTrue:[^nil].
		}

        showDisplayBits(theDisplay); // self showDisplayBits.
        if( failed())
		 {
			return true; // ifTrue:[^nil].
		}

        stack.popN(argCount); // interpreterProxy pop: interpreterProxy methodArgumentCount.

        return true;
    }

     /*
    loadWarpBltFrom: bbObj
	^self loadBitBltFrom: bbObj warping: true
     */
    boolean loadWarpBltFrom(SqueakObject bbObj, int argCount) {
         return loadBitBltFromWarping(bbObj, true, argCount);
    }

    /*
    primitiveDrawLoop
	"Invoke the line drawing primitive."
	| rcvr xDelta yDelta |
	self export: true.
	rcvr := interpreterProxy stackValue: 2.
	xDelta := interpreterProxy stackIntegerValue: 1.
	yDelta := interpreterProxy stackIntegerValue: 0.
	(self loadBitBltFrom: rcvr) ifFalse:[^interpreterProxy primitiveFail].
	interpreterProxy failed ifFalse:[
		self drawLoopX: xDelta Y: yDelta.
		self showDisplayBits].
	interpreterProxy failed ifFalse:[interpreterProxy pop: 2].
     */
    public void primitiveDrawLoop(int argCount, Screen theDisplay) { // no rcvr class check, to allow unknown subclasses (e.g. under Turtle)
        SqueakObject rcvr;
        int xDelta, yDelta;
        rcvr = (SqueakObject) stack.stackValue(2); // rcvr := interpreterProxy stackValue: 2.
        xDelta = (Integer)stack.stackValue(1); // xDelta := interpreterProxy stackIntegerValue: 1.
        yDelta = (Integer)stack.stackValue(0); // yDelta := interpreterProxy stackIntegerValue: 0.

        if (!loadBitBltFrom(rcvr, argCount)) { // (self loadBitBltFrom: rcvr)
            success = false;
            throw PrimitiveHandler.failExpected();
        }

        if(!failed()) { // interpreterProxy failed ifFalse:[
            drawLoopX(xDelta, yDelta, theDisplay); // self drawLoopX: xDelta Y: yDelta.
            showDisplayBits(theDisplay); // self showDisplayBits].
        }

        if(!failed()){ // interpreterProxy failed ifFalse:[
            stack.popN(2); // interpreterProxy pop: 2].
        }
    }

    /*
    drawLoopX: xDelta Y: yDelta
	"This is the primitive implementation of the line-drawing loop.
	See the comments in BitBlt>>drawLoopX:Y:"
	| dx1 dy1 px py P affL affR affT affB |
	xDelta > 0
		ifTrue: [dx1 := 1]
		ifFalse: [xDelta = 0
				ifTrue: [dx1 := 0]
				ifFalse: [dx1 := -1]].
	yDelta > 0
		ifTrue: [dy1 := 1]
		ifFalse: [yDelta = 0
				ifTrue: [dy1 := 0]
				ifFalse: [dy1 := -1]].
	px := yDelta abs.
	py := xDelta abs.
	affL := affT := 9999.  "init null rectangle"
	affR := affB := -9999.
	py > px
		ifTrue:
			["more horizontal"
			P := py // 2.
			1 to: py do:
				[:i |
				destX := destX + dx1.
				(P := P - px) < 0 ifTrue:
					[destY := destY + dy1.
					P := P + py].
				i < py ifTrue:
					[self copyBits.
					interpreterProxy failed ifTrue:
						[^ nil "bail out now on failure -- avoid storing x,y"].
					(affectedL < affectedR and: [affectedT < affectedB]) ifTrue:
						["Affected rectangle grows along the line"
						affL := affL min: affectedL.
						affR := affR max: affectedR.
						affT := affT min: affectedT.
						affB := affB max: affectedB.
						(affR - affL) * (affB - affT) > 4000 ifTrue:
							["If affected rectangle gets large, update it in chunks"
							affectedL := affL.  affectedR := affR.
							affectedT := affT.  affectedB := affB.
							self showDisplayBits.
							affL := affT := 9999.  "init null rectangle"
							affR := affB := -9999]].
					]]]
		ifFalse:
			["more vertical"
			P := px // 2.
			1 to: px do:
				[:i |
				destY := destY + dy1.
				(P := P - py) < 0 ifTrue:
					[destX := destX + dx1.
					P := P + px].
				i < px ifTrue:
					[self copyBits.
					interpreterProxy failed ifTrue:
						[^ nil "bail out now on failure -- avoid storing x,y"].
					(affectedL < affectedR and: [affectedT < affectedB]) ifTrue:
						["Affected rectangle grows along the line"
						affL := affL min: affectedL.
						affR := affR max: affectedR.
						affT := affT min: affectedT.
						affB := affB max: affectedB.
						(affR - affL) * (affB - affT) > 4000 ifTrue:
							["If affected rectangle gets large, update it in chunks"
							affectedL := affL.  affectedR := affR.
							affectedT := affT.  affectedB := affB.
							self showDisplayBits.
							affL := affT := 9999.  "init null rectangle"
							affR := affB := -9999]].
					]]].

	"Remaining affected rect"
	affectedL := affL.  affectedR := affR.
	affectedT := affT.  affectedB := affB.

	"store destX, Y back"
	interpreterProxy storeInteger: BBDestXIndex ofObject: bitBltOop withValue: destX.
	interpreterProxy storeInteger: BBDestYIndex ofObject: bitBltOop withValue: destY.
     */
    void drawLoopX(int xDelta, int yDelta, Screen theDisplay){
        int dx1, dy1, px, py, P, affL, affR, affT, affB;

        if(xDelta > 0){ // xDelta > 0
            dx1 = 1; // ifTrue: [dx1 := 1]
        } else { // ifFalse: [
            if(xDelta == 0) {// xDelta = 0
                dx1 = 0; // ifTrue: [dx1 := 0]
            } else {
                dx1 = -1; // ifFalse: [dx1 := -1]].
            }
        }

        if(yDelta > 0){ // yDelta > 0
            dy1 = 1; // ifTrue: [dy1 := 1]
        } else { // ifFalse: [
            if(yDelta == 0) {// yDelta = 0
                dy1 = 0; // ifTrue: [dy1 := 0]
            } else {
                dy1 = -1; // ifFalse: [dy1 := -1]].
            }
        }

        px = Math.abs(yDelta); // px := yDelta abs.
        py = Math.abs(xDelta); // py := xDelta abs.
        affL = affT = 9999; // affL := affT := 9999.  "init null rectangle"
        affR = affB = -9999; // affR := affB := -9999.

        if(py > px){ // ifTrue:
            // ["more horizontal"
            P = py / 2; // P := py // 2.
            for(int i=1; i<=py; i++){ // 1 to: py do: // [:i |
                destX += dx1; // destX := destX + dx1.
                if((P-=px) < 0) { // (P := P - px) < 0 ifTrue:
                    destY += dy1; // [destY := destY + dy1.
                    P += py; // P := P + py].
                }
                if(i<py){ // i < py ifTrue:
                    copyBits(); // [self copyBits.
                    if(failed()){ // interpreterProxy failed ifTrue:
                        return; // [^ nil "bail out now on failure -- avoid storing x,y"].
                    }
                    if(affectedL < affectedR && affectedT < affectedB ){ // (affectedL < affectedR and: [affectedT < affectedB]) ifTrue:
                        // ["Affected rectangle grows along the line"
                        affL = Math.min(affL, affectedL); // affL := affL min: affectedL.
			affR = Math.min(affR, affectedR); // affR := affR max: affectedR.
			affT = Math.min(affT, affectedT); // affT := affT min: affectedT.
			affB = Math.min(affB, affectedB); // affB := affB max: affectedB.

                        if((affR - affL) * (affB - affT) > 4000) { // (affR - affL) * (affB - affT) > 4000 ifTrue:
                            // ["If affected rectangle gets large, update it in chunks"
                            affectedL = affL; affectedR = affR; // affectedL := affL.  affectedR := affR.
                            affectedT = affT; affectedB = affB; // affectedT := affT.  affectedB := affB.
                            showDisplayBits(theDisplay); // self showDisplayBits.
                            affL = affT = 9999; // affL := affT := 9999.  "init null rectangle"
                            affR = affB = -9999;// affR := affB := -9999]].
                        }
                    }
                }
            }
        } else { // ifFalse:
            // ["more vertical"
            P = px / 2; // P := px // 2.
            for(int i=1; i<=px; i++){ // 1 to: px do: // [:i |
                destY += dy1; // destY := destY + dy1.
                if((P-=py) < 0) { // (P := P - py) < 0 ifTrue:
                    destX += dx1; // [destX := destX + dx1.
                    P += px; // P := P + px].
                }
                if(i<px){ // i < px ifTrue:
                    copyBits(); // [self copyBits.
                    if(failed()){ // interpreterProxy failed ifTrue:
                        return; // [^ nil "bail out now on failure -- avoid storing x,y"].
                    }
                    if(affectedL < affectedR && affectedT < affectedB ){ // (affectedL < affectedR and: [affectedT < affectedB]) ifTrue:
                        // ["Affected rectangle grows along the line"
                        affL = Math.min(affL, affectedL); // affL := affL min: affectedL.
			affR = Math.min(affR, affectedR); // affR := affR max: affectedR.
			affT = Math.min(affT, affectedT); // affT := affT min: affectedT.
			affB = Math.min(affB, affectedB); // affB := affB max: affectedB.

                        if((affR - affL) * (affB - affT) > 4000) { // (affR - affL) * (affB - affT) > 4000 ifTrue:
                            // ["If affected rectangle gets large, update it in chunks"
                            affectedL = affL; affectedR = affR; // affectedL := affL.  affectedR := affR.
                            affectedT = affT; affectedB = affB; // affectedT := affT.  affectedB := affB.
                            showDisplayBits(theDisplay); // self showDisplayBits.
                            affL = affT = 9999; // affL := affT := 9999.  "init null rectangle"
                            affR = affB = -9999;// affR := affB := -9999]].
                        }
                    }
                }
            }
        }

        // "Remaining affected rect"
	affectedL = affL; affectedR = affR; // affectedL := affL.  affectedR := affR.
	affectedT = affT; affectedB = affB; // affectedT := affT.  affectedB := affB.

	// "store destX, Y back"
	bitBltOop.setPointer(BBDestXIndex, destX); // interpreterProxy storeInteger: BBDestXIndex ofObject: bitBltOop withValue: destX.
	bitBltOop.setPointer(BBDestYIndex, destY); // interpreterProxy storeInteger: BBDestYIndex ofObject: bitBltOop withValue: destY.
    }

    /*
    loadBitBltFrom: bbObj warping: aBool
	"Load context from BitBlt instance.  Return false if anything is amiss"
	"NOTE this should all be changed to minX/maxX coordinates for simpler clipping
		-- once it works!"
	| ok |
	self inline: false.
	bitBltOop := bbObj.
	isWarping := aBool.
	combinationRule := interpreterProxy fetchInteger: BBRuleIndex ofObject: bitBltOop.
	(interpreterProxy failed
		or: [combinationRule < 0 or: [combinationRule > (OpTableSize - 2)]])
		 ifTrue: [^ false  "operation out of range"].
	(combinationRule >= 16 and: [combinationRule <= 17])
		 ifTrue: [^ false  "fail for old simulated paint, erase modes"].
	sourceForm := interpreterProxy fetchPointer: BBSourceFormIndex ofObject: bitBltOop.
	noSource := self ignoreSourceOrHalftone: sourceForm.
	halftoneForm := interpreterProxy fetchPointer: BBHalftoneFormIndex ofObject: bitBltOop.
	noHalftone := self ignoreSourceOrHalftone: halftoneForm.

	destForm := interpreterProxy fetchPointer: BBDestFormIndex ofObject: bbObj.
	((interpreterProxy isPointers: destForm) and: [(interpreterProxy slotSizeOf: destForm) >= 4])
		ifFalse: [^ false].
	ok := self loadBitBltDestForm.
	ok ifFalse:[^false].

	destX := self fetchIntOrFloat: BBDestXIndex ofObject: bitBltOop ifNil: 0.
	destY := self fetchIntOrFloat: BBDestYIndex ofObject: bitBltOop ifNil: 0.
	width := self fetchIntOrFloat: BBWidthIndex ofObject: bitBltOop ifNil: destWidth.
	height := self fetchIntOrFloat: BBHeightIndex ofObject: bitBltOop ifNil: destHeight.
		interpreterProxy failed ifTrue: [^ false  "non-integer value"].

	noSource ifTrue:
		[sourceX := sourceY := 0]
		ifFalse:
		[((interpreterProxy isPointers: sourceForm) and: [(interpreterProxy slotSizeOf: sourceForm) >= 4])
			ifFalse: [^ false].
		ok := self loadBitBltSourceForm.
		ok ifFalse:[^false].
		ok := self loadColorMap.
		ok ifFalse:[^false].
		"Need the implicit setup here in case of 16<->32 bit conversions"
		(cmFlags bitAnd: ColorMapNewStyle) = 0 ifTrue:[self setupColorMasks].
		sourceX := self fetchIntOrFloat: BBSourceXIndex ofObject: bitBltOop ifNil: 0.
		sourceY := self fetchIntOrFloat: BBSourceYIndex ofObject: bitBltOop ifNil: 0].

	ok := self loadHalftoneForm.
	ok ifFalse:[^false].
	clipX := self fetchIntOrFloat: BBClipXIndex ofObject: bitBltOop ifNil: 0.
	clipY := self fetchIntOrFloat: BBClipYIndex ofObject: bitBltOop ifNil: 0.
	clipWidth := self fetchIntOrFloat: BBClipWidthIndex ofObject: bitBltOop ifNil: destWidth.
	clipHeight := self fetchIntOrFloat: BBClipHeightIndex ofObject: bitBltOop ifNil: destHeight.
		interpreterProxy failed ifTrue: [^ false  "non-integer value"].
	clipX < 0 ifTrue: [clipWidth := clipWidth + clipX.  clipX := 0].
	clipY < 0 ifTrue: [clipHeight := clipHeight + clipY.  clipY := 0].
	clipX+clipWidth > destWidth ifTrue: [clipWidth := destWidth - clipX].
	clipY+clipHeight > destHeight ifTrue: [clipHeight := destHeight - clipY].
	^ true
     */
    boolean loadBitBltFromWarping(SqueakObject bbObj, boolean aBool, int argCount) {
        methodArgumentCount = argCount;
        success = true;
        bitBltOop = bbObj; // bitBltOop := bbObj.
        isWarping = aBool; // isWarping := aBool.
        combinationRule = bitBltOop.fetchInteger(BBRuleIndex); // combinationRule := interpreterProxy fetchInteger: BBRuleIndex ofObject: bitBltOop.
        if(failed() || combinationRule < 0 || combinationRule > (41-2)) { // (interpreterProxy failed or: [combinationRule < 0 or: [combinationRule > (OpTableSize - 2)]])
            return false; // ifTrue: [^ false  "operation out of range"].
        }
        if (combinationRule >= 16 && combinationRule <= 17) { // (combinationRule >= 16 and: [combinationRule <= 17])
            return false; // ifTrue: [^ false  "fail for old simulated paint, erase modes"].
        }
        sourceForm = bitBltOop.fetchPointerNI(BBSourceFormIndex); // sourceForm := interpreterProxy fetchPointer: BBSourceFormIndex ofObject: bitBltOop.
        noSource = ignoreSourceOrHalftone(sourceForm); // noSource := self ignoreSourceOrHalftone: sourceForm.
        halftoneForm = bitBltOop.fetchPointerNI(BBHalftoneFormIndex); // halftoneForm := interpreterProxy fetchPointer: BBHalftoneFormIndex ofObject: bitBltOop.
        noHalftone = ignoreSourceOrHalftone(halftoneForm); // noHalftone := self ignoreSourceOrHalftone: halftoneForm.
        destForm = bbObj.fetchPointerNI(BBDestFormIndex); // destForm := interpreterProxy fetchPointer: BBDestFormIndex ofObject: bbObj.

        if(!(destForm.isPointers() && (destForm.slotSizeOf() >= 4))){ // ((interpreterProxy isPointers: destForm) and: [(interpreterProxy slotSizeOf: destForm) >= 4])
            return false; // ifFalse: [^ false].
        }
        if (!dest.loadFrom(destForm, vm)) { // ok := self loadBitBltDestForm.
            return false; // ok ifFalse:[^false].
        }

        destX = fetchIntOrFloatofObjectifNil(BBDestXIndex, bitBltOop, 0); // destX := self fetchIntOrFloat: BBDestXIndex ofObject: bitBltOop ifNil: 0.
        destY = fetchIntOrFloatofObjectifNil(BBDestYIndex, bitBltOop, 0); // destY := self fetchIntOrFloat: BBDestYIndex ofObject: bitBltOop ifNil: 0.
        width = fetchIntOrFloatofObjectifNil(BBWidthIndex, bitBltOop, dest.width); // width := self fetchIntOrFloat: BBWidthIndex ofObject: bitBltOop ifNil: destWidth.
        height = fetchIntOrFloatofObjectifNil(BBHeightIndex, bitBltOop, dest.height); // height := self fetchIntOrFloat: BBHeightIndex ofObject: bitBltOop ifNil: destHeight.
        if(failed()){ // interpreterProxy failed ifTrue: [^ false  "non-integer value"].
            return false;
        }

        if( noSource){ // noSource ifTrue:
            sourceX = sourceY = 0; // [sourceX := sourceY := 0]
        } else { // ifFalse:
            if(!(sourceForm.isPointers() && (sourceForm.slotSizeOf() >= 4))){ // [((interpreterProxy isPointers: sourceForm) and: [(interpreterProxy slotSizeOf: sourceForm) >= 4])
                return false; // ifFalse: [^ false].
            }
            if (!source.loadFrom(sourceForm, vm)) { //ok := self loadBitBltSourceForm.
                return false; // ok ifFalse:[^false].
            }

            if (!loadColorMap()) { // ok := self loadColorMap.
                return false; // ok ifFalse:[^false].
            }

            // "Need the implicit setup here in case of 16<->32 bit conversions"
            if ((cmFlags & ColorMapNewStyle) == 0) { // (cmFlags bitAnd: ColorMapNewStyle) = 0
                setUpColorMasks(); // ifTrue:[self setupColorMasks].
            }
            sourceX = fetchIntOrFloatofObjectifNil(BBSourceXIndex, bitBltOop, 0); // sourceX := self fetchIntOrFloat: BBSourceXIndex ofObject: bitBltOop ifNil: 0.
            sourceY = fetchIntOrFloatofObjectifNil(BBSourceYIndex, bitBltOop, 0); // sourceY := self fetchIntOrFloat: BBSourceYIndex ofObject: bitBltOop ifNil: 0].
        }
        if (!loadHalftoneForm()) { // ok := self loadHalftoneForm.
            return false; // ok ifFalse:[^false].
        }

        clipX = fetchIntOrFloatofObjectifNil(BBClipXIndex, bitBltOop, 0); // clipX := self fetchIntOrFloat: BBClipXIndex ofObject: bitBltOop ifNil: 0.
        clipY = fetchIntOrFloatofObjectifNil(BBClipYIndex, bitBltOop, 0); // clipY := self fetchIntOrFloat: BBClipYIndex ofObject: bitBltOop ifNil: 0.
        clipWidth = fetchIntOrFloatofObjectifNil(BBClipWidthIndex, bitBltOop, dest.width); // clipWidth := self fetchIntOrFloat: BBClipWidthIndex ofObject: bitBltOop ifNil: destWidth.
        clipHeight = fetchIntOrFloatofObjectifNil(BBClipHeightIndex, bitBltOop, dest.height); // clipHeight := self fetchIntOrFloat: BBClipHeightIndex ofObject: bitBltOop ifNil: destHeight.
        if(failed()){ // interpreterProxy failed ifTrue: [^ false  "non-integer value"].
            return false;
        }

        if (clipX < 0) { // clipX < 0 ifTrue: [
            clipWidth += clipX; // clipWidth := clipWidth + clipX.
            clipX = 0; // clipX := 0].
        }
        if (clipY < 0) { // clipY < 0 ifTrue: [
            clipHeight += clipY; // clipHeight := clipHeight + clipY.
            clipY = 0; // clipY := 0].
        }
	if ((clipX + clipWidth) > dest.width) { // clipX+clipWidth > destWidth ifTrue: [
            clipWidth = dest.width - clipX; // clipWidth := destWidth - clipX].
        }
        if ((clipY + clipHeight) > dest.height) { // clipY+clipHeight > destHeight ifTrue: [
            clipHeight = dest.height - clipY; // clipHeight := destHeight - clipY].
        }

        return true; // ^ true
    }

    /*
    ignoreSourceOrHalftone: formPointer

	formPointer = interpreterProxy nilObject ifTrue: [ ^true ].
	combinationRule = 0 ifTrue: [ ^true ].
	combinationRule = 5 ifTrue: [ ^true ].
	combinationRule = 10 ifTrue: [ ^true ].
	combinationRule = 15 ifTrue: [ ^true ].
	^false
     */
    boolean ignoreSourceOrHalftone(Object formPointer) {
        if (formPointer == SpecialObjects.nilObj) { // formPointer = interpreterProxy nilObject ifTrue: [ ^true ].
            return true;
        }
        if (combinationRule == 0) { // combinationRule = 0 ifTrue: [ ^true ].
            return true;
        }
        if (combinationRule == 5) { // combinationRule = 5 ifTrue: [ ^true ].
            return true;
        }
        if (combinationRule == 10) { // combinationRule = 10 ifTrue: [ ^true ].
            return true;
        }
        if (combinationRule == 15) { // combinationRule = 15 ifTrue: [ ^true ].
            return true;
        }
        return false; // ^false
    }

    /*
    fetchIntOrFloat: fieldIndex ofObject: objectPointer ifNil: defaultValue
	"Return the integer value of the given field of the given object. If the field contains a Float, truncate it and return its integral part. Fail if the given field does not contain a small integer or Float, or if the truncated Float is out of the range of small integers."
	| fieldOop floatValue |
	self var: #floatValue declareC:'double floatValue'.
	fieldOop := interpreterProxy fetchPointer: fieldIndex ofObject: objectPointer.
	(interpreterProxy isIntegerObject: fieldOop)
		ifTrue:[^interpreterProxy integerValueOf: fieldOop].
	(fieldOop = interpreterProxy nilObject) ifTrue:[^defaultValue].
	floatValue := interpreterProxy floatValueOf: fieldOop.
	(-2147483648.0 <= floatValue and:[floatValue <= 2147483647.0])
		ifFalse:[interpreterProxy primitiveFail. ^0].
	^floatValue asInteger
     */
    int fetchIntOrFloatofObjectifNil(int fieldIndex, SqueakObject objectPointer, int defaultValue) {
        double floatValue;

	Object fieldOop = objectPointer.fetchPointer(fieldIndex); // fieldOop := interpreterProxy fetchPointer: fieldIndex ofObject: objectPointer.
        if (SmallInteger.isSmallInt(fieldOop)) { // (interpreterProxy isIntegerObject: fieldOop)
            return SmallInteger.intFromSmall((Integer) fieldOop); // ifTrue:[^interpreterProxy integerValueOf: fieldOop].
        }
        if (fieldOop == SpecialObjects.nilObj) { // (fieldOop = interpreterProxy nilObject)
            return defaultValue; // ifTrue:[^defaultValue].
        }
        floatValue = ((SqueakObject)fieldOop).getFloatBits(); // floatValue := interpreterProxy floatValueOf: fieldOop.
        if (!((-2147483648.0 <= floatValue) && (floatValue <= 2147483647.0))) { // (-2147483648.0 <= floatValue and:[floatValue <= 2147483647.0])
            success = false; // ifFalse:[interpreterProxy primitiveFail.
            return 0; // ^0].
        }
        return ((int) floatValue); // ^floatValue asInteger
    }

    /*
    loadHalftoneForm
	"Load the halftone form"
	| halftoneBits |
	self inline: true.
	noHalftone ifTrue:[
		halftoneBase := nil.
		^true].
	((interpreterProxy isPointers: halftoneForm) and: [(interpreterProxy slotSizeOf: halftoneForm) >= 4])
		ifTrue:
		["Old-style 32xN monochrome halftone Forms"
		halftoneBits := interpreterProxy fetchPointer: FormBitsIndex ofObject: halftoneForm.
		halftoneHeight := interpreterProxy fetchInteger: FormHeightIndex ofObject: halftoneForm.
		(interpreterProxy isWords: halftoneBits)
			ifFalse: [noHalftone := true]]
		ifFalse:
		["New spec accepts, basically, a word array"
		((interpreterProxy isPointers: halftoneForm) not
			and: [interpreterProxy isWords: halftoneForm])
			ifFalse: [^ false].
		halftoneBits := halftoneForm.
		halftoneHeight := interpreterProxy slotSizeOf: halftoneBits].
	halftoneBase := self cCoerce: (interpreterProxy firstIndexableField: halftoneBits) to:'int'.
	^true
     */
    boolean loadHalftoneForm() {
        if (noHalftone) { // noHalftone ifTrue:[
            // halftoneBase := nil.
            return true; // ^true].
        }

        if(halftoneForm.isPointers() && (halftoneForm.slotSizeOf() >= 4)){ // ((interpreterProxy isPointers: halftoneForm) and: [(interpreterProxy slotSizeOf: halftoneForm) >= 4])
            // ["Old-style 32xN monochrome halftone Forms"
            halftoneBits = (int[])halftoneForm.fetchPointerNI(FormBitsIndex).bits ; // halftoneBits := interpreterProxy fetchPointer: FormBitsIndex ofObject: halftoneForm.
            halftoneHeight = halftoneForm.fetchInteger(FormHeightIndex); // halftoneHeight := interpreterProxy fetchInteger: FormHeightIndex ofObject: halftoneForm.
            if(halftoneForm.fetchPointerNI(FormBitsIndex).isWords())
			 {
				noHalftone = true; // ifFalse: [noHalftone := true]]
			}
        } else {
            // ["New spec accepts, basically, a word array"
            if(!(!halftoneForm.isPointers() && halftoneForm.isWords()))
			 {
				return false; // ifFalse: [^ false].
			}

            halftoneBits = (int[])halftoneForm.bits; // halftoneBits := halftoneForm.
            halftoneHeight = halftoneForm.slotSizeOf();// halftoneHeight := interpreterProxy slotSizeOf: halftoneBits].
        }

        // halftoneBase := self cCoerce: (interpreterProxy firstIndexableField: halftoneBits) to:'int'.
        return true; // ^true
    }

    /*
    loadColorMap
	"ColorMap, if not nil, must be longWords, and
	2^N long, where N = sourceDepth for 1, 2, 4, 8 bits,
	or N = 9, 12, or 15 (3, 4, 5 bits per color) for 16 or 32 bits."
	| cmSize oldStyle oop cmOop |
	self inline: true.
	cmFlags := cmMask := cmBitsPerColor := 0.
	cmShiftTable := nil.
	cmMaskTable := nil.
	cmLookupTable := nil.
	cmOop := interpreterProxy fetchPointer: BBColorMapIndex ofObject: bitBltOop.
	cmOop = interpreterProxy nilObject ifTrue:[^true].
	cmFlags := ColorMapPresent. "even if identity or somesuch - may be cleared later"
	oldStyle := false.
	(interpreterProxy isWords: cmOop) ifTrue:[
		"This is an old-style color map (indexed only, with implicit RGBA conversion)"
		cmSize := interpreterProxy slotSizeOf: cmOop.
		cmLookupTable := interpreterProxy firstIndexableField: cmOop.
		oldStyle := true.
	] ifFalse: [
		"A new-style color map (fully qualified)"
		((interpreterProxy isPointers: cmOop)
			and:[(interpreterProxy slotSizeOf: cmOop) >= 3]) ifFalse:[^false].
		cmShiftTable := self loadColorMapShiftOrMaskFrom:
			(interpreterProxy fetchPointer: 0 ofObject: cmOop).
		cmMaskTable := self loadColorMapShiftOrMaskFrom:
			(interpreterProxy fetchPointer: 1 ofObject: cmOop).
		oop := interpreterProxy fetchPointer: 2 ofObject: cmOop.
		oop = interpreterProxy nilObject
			ifTrue:[cmSize := 0]
			ifFalse:[(interpreterProxy isWords: oop) ifFalse:[^false].
					cmSize := (interpreterProxy slotSizeOf: oop).
					cmLookupTable := interpreterProxy firstIndexableField: oop].
		cmFlags := cmFlags bitOr: ColorMapNewStyle.
	].
	(cmSize bitAnd: cmSize - 1) = 0 ifFalse:[^false].
	cmMask := cmSize - 1.
	cmBitsPerColor := 0.
	cmSize = 512 ifTrue: [cmBitsPerColor := 3].
	cmSize = 4096 ifTrue: [cmBitsPerColor := 4].
	cmSize = 32768 ifTrue: [cmBitsPerColor := 5].
	cmSize = 0
		ifTrue:[cmLookupTable := nil. cmMask := 0]
		ifFalse:[cmFlags := cmFlags bitOr: ColorMapIndexedPart].
	oldStyle "needs implicit conversion"
		ifTrue:[	self setupColorMasks].
	"Check if colorMap is just identity mapping for RGBA parts"
	(self isIdentityMap: cmShiftTable with: cmMaskTable)
		ifTrue:[ cmMaskTable := nil. cmShiftTable := nil ]
		ifFalse:[ cmFlags := cmFlags bitOr: ColorMapFixedPart].
	^true
     */
    boolean loadColorMap() {
        int cmSize;
        SqueakObject oop;
        SqueakObject cmOop;
        boolean oldStyle;

        cmFlags = cmMask = cmBitsPerColor = 0; // cmFlags := cmMask := cmBitsPerColor := 0.
        cmShiftTable = null; // cmShiftTable := nil.
        cmMaskTable = null; // cmMaskTable := nil.
        cmLookupTable = null; // cmLookupTable := nil.

        cmOop = bitBltOop.fetchPointerNI(BBColorMapIndex); // cmOop := interpreterProxy fetchPointer: BBColorMapIndex ofObject: bitBltOop.
        if (cmOop == SpecialObjects.nilObj) { // cmOop = interpreterProxy nilObject
            return true; // ifTrue:[^true].
        }

        cmFlags = ColorMapPresent; // cmFlags := ColorMapPresent. "even if identity or somesuch - may be cleared later"
        oldStyle = false; // oldStyle := false.

        if (cmOop.isWords()) { // (interpreterProxy isWords: cmOop) ifTrue:[

            // "This is an old-style color map (indexed only, with implicit RGBA conversion)"
            cmSize = cmOop.slotSizeOf(); // cmSize := interpreterProxy slotSizeOf: cmOop.
            cmLookupTable = firstIndexableField(cmOop); // cmLookupTable := interpreterProxy firstIndexableField: cmOop.
            oldStyle = true; // oldStyle := true.
        } else { // ] ifFalse: [

            // "A new-style color map (fully qualified)"
            if (!((cmOop.isPointers()) && (cmOop.slotSizeOf() >= 3))) { // ((interpreterProxy isPointers: cmOop) and:[(interpreterProxy slotSizeOf: cmOop) >= 3])
                return false; // ifFalse:[^false].
            }

            // cmShiftTable := self loadColorMapShiftOrMaskFrom: (interpreterProxy fetchPointer: 0 ofObject: cmOop).
            cmShiftTable = loadColorMapShiftOrMaskFrom(cmOop.fetchPointerNI(0));
            // cmMaskTable := self loadColorMapShiftOrMaskFrom: (interpreterProxy fetchPointer: 1 ofObject: cmOop).
            cmShiftTable = loadColorMapShiftOrMaskFrom(cmOop.fetchPointerNI(1));
            oop = cmOop.fetchPointerNI(2); // oop := interpreterProxy fetchPointer: 2 ofObject: cmOop.
            if(oop == SpecialObjects.nilObj){ // oop = interpreterProxy nilObject
                cmSize = 0; // ifTrue:[cmSize := 0]
            } else { // ifFalse:[
                if(!oop.isWords()){ // (interpreterProxy isWords: oop) ifFalse:[^false].
                    return false;
                }
                cmSize = oop.slotSizeOf(); // cmSize := (interpreterProxy slotSizeOf: oop).
		cmLookupTable = firstIndexableField(oop); // cmLookupTable := interpreterProxy firstIndexableField: oop].
            }
            cmFlags |= ColorMapNewStyle; // cmFlags := cmFlags bitOr: ColorMapNewStyle.
        } // ].

        if (!((cmSize & (cmSize - 1)) == 0)) { // (cmSize bitAnd: cmSize - 1) = 0 ifFalse:[^false].
            return false;
        }

        cmMask = cmSize - 1; // cmMask := cmSize - 1.
        cmBitsPerColor = 0; // cmBitsPerColor := 0.
        if (cmSize == 512) { // cmSize = 512 ifTrue: [cmBitsPerColor := 3].
            cmBitsPerColor = 3;
        }
        if (cmSize == 4096) { // cmSize = 4096 ifTrue: [cmBitsPerColor := 4].
            cmBitsPerColor = 4;
        }
        if (cmSize == 32768) { // cmSize = 32768 ifTrue: [cmBitsPerColor := 5].
            cmBitsPerColor = 5;
        }
        if (cmSize == 0) { // cmSize = 0 // ifTrue:[
            cmLookupTable = null; // cmLookupTable := nil.
            cmMask = 0; // cmMask := 0]
        } else { // ifFalse:[
            cmFlags |= ColorMapIndexedPart; // cmFlags := cmFlags bitOr: ColorMapIndexedPart].
        }

        if (oldStyle) { // oldStyle "needs implicit conversion"
            setUpColorMasks(); // ifTrue:[self setupColorMasks].
        }

        // "Check if colorMap is just identity mapping for RGBA parts"
        if (isIdentityMapwith(cmShiftTable, cmMaskTable)) { // (self isIdentityMap: cmShiftTable with: cmMaskTable) // ifTrue:[
            cmMaskTable = null; // cmMaskTable := nil.
            cmShiftTable = null; // cmShiftTable := nil ]
        } else {
            cmFlags |= ColorMapFixedPart; // ifFalse:[ cmFlags := cmFlags bitOr: ColorMapFixedPart].
        }

        return true; // ^true
    }

    /*
    isIdentityMap: shifts with: masks
	"Return true if shiftTable/maskTable define an identity mapping."
	self var: #shifts declareC:'int *shifts'.
	self var: #masks declareC:'unsigned int *masks'.
	(shifts == nil or:[masks == nil]) ifTrue:[^true].
	((shifts at: RedIndex) = 0
		and:[(shifts at: GreenIndex) = 0
		and:[(shifts at: BlueIndex) = 0
		and:[(shifts at: AlphaIndex) = 0
			and:[((masks at: RedIndex) = 16rFF0000)
			and:[((masks at: GreenIndex) = 16r00FF00)
			and:[((masks at: BlueIndex) = 16r0000FF)
			and:[((masks at: AlphaIndex) = 16rFF000000)]]]]]]])
		ifTrue:[^true].
	^false
     */
    boolean isIdentityMapwith(int[] shifts, int[] masks) {
        if ((shifts == null) || (masks == null)) { // (shifts == nil or:[masks == nil])
            return true; // ifTrue:[^true].
        }
        if ((shifts[RedIndex] == 0)  // ((shifts at: RedIndex) = 0
                && (shifts[GreenIndex] == 0) // and:[(shifts at: GreenIndex) = 0
                && (shifts[BlueIndex] == 0) // and:[(shifts at: BlueIndex) = 0
                && (shifts[AlphaIndex] == 0) // and:[(shifts at: AlphaIndex) = 0
                    && (masks[RedIndex] == 0xFF0000) // and:[((masks at: RedIndex) = 16rFF0000)
                    && (masks[GreenIndex] == 0x00FF00) // and:[((masks at: GreenIndex) = 16r00FF00)
                    && (masks[BlueIndex] == 0x0000FF) // and:[((masks at: BlueIndex) = 16r0000FF)
                    && (masks[AlphaIndex] == 0xFF000000)) { // and:[((masks at: AlphaIndex) = 16rFF000000)]]]]]]])
            return true; // ifTrue:[^true].
        }
        return false; // ^false
    }

    /*
    setupColorMasks
	"WARNING: For WarpBlt w/ smoothing the source depth is wrong here!"
	| bits targetBits |
	bits := targetBits := 0.
	sourceDepth <= 8 ifTrue:[^nil].
	sourceDepth = 16 ifTrue:[bits := 5].
	sourceDepth = 32 ifTrue:[bits := 8].

	cmBitsPerColor = 0
		ifTrue:["Convert to destDepth"
				destDepth <= 8 ifTrue:[^nil].
				destDepth = 16 ifTrue:[targetBits := 5].
				destDepth = 32 ifTrue:[targetBits := 8]]
		ifFalse:[targetBits := cmBitsPerColor].

	self setupColorMasksFrom: bits to: targetBits
     */
    boolean setUpColorMasks() {
        int bits;
        int targetBits;

        bits = targetBits = 0; // bits := targetBits := 0.
        if (source.depth <= 8) { // sourceDepth <= 8 ifTrue:[^nil].
            return false;
        }
        if (source.depth == 16) { // sourceDepth = 16 ifTrue:[bits := 5].
            bits = 5;
        }
        if (source.depth == 32) { // sourceDepth = 32 ifTrue:[bits := 8].
            bits = 8;
        }
        if (cmBitsPerColor == 0) { // cmBitsPerColor = 0 // ifTrue:["Convert to destDepth"
            if (dest.depth <= 8) { // destDepth <= 8 ifTrue:[^nil].
                return false;
            }
            if (dest.depth == 16) { // destDepth = 16 ifTrue:[targetBits := 5].
                targetBits = 5;
            }
            if (dest.depth == 32) { // destDepth = 32 ifTrue:[targetBits := 8]]
                targetBits = 8;
            }
        } else { // ifFalse:[targetBits := cmBitsPerColor].
            targetBits = cmBitsPerColor;
        }
        return setupColorMasksFromto(bits, targetBits); // self setupColorMasksFrom: bits to: targetBits
    }

    /*
    setupColorMasksFrom: srcBits to: targetBits
	"Setup color masks for converting an incoming RGB pixel value from srcBits to targetBits."
	| mask shifts masks deltaBits |
	self var: #shifts declareC:'static int shifts[4] = {0, 0, 0, 0}'.
	self var: #masks declareC:'static unsigned int masks[4] = {0, 0, 0, 0}'.
	self cCode:'' inSmalltalk:[
		shifts := CArrayAccessor on: (IntegerArray new: 4).
		masks := CArrayAccessor on: (WordArray new: 4).
	].
	deltaBits := targetBits - srcBits.
	deltaBits = 0 ifTrue:[^0].
	deltaBits <= 0
		ifTrue:[	mask := 1 << targetBits - 1.
				"Mask for extracting a color part of the source"
				masks at: RedIndex put: mask << (srcBits*2 - deltaBits).
				masks at: GreenIndex put: mask << (srcBits - deltaBits).
				masks at: BlueIndex put: mask << (0 - deltaBits).
				masks at: AlphaIndex put: 0]
		ifFalse:[	mask := 1 << srcBits - 1.
				"Mask for extracting a color part of the source"
				masks at: RedIndex put: mask << (srcBits*2).
				masks at: GreenIndex put: mask << srcBits.
				masks at: BlueIndex put: mask].

	"Shifts for adjusting each value in a cm RGB value"
	shifts at: RedIndex put: deltaBits * 3.
	shifts at: GreenIndex put: deltaBits * 2.
	shifts at: BlueIndex put: deltaBits.
	shifts at: AlphaIndex put: 0.

	cmShiftTable := shifts.
	cmMaskTable := masks.
	cmFlags := cmFlags bitOr: (ColorMapPresent bitOr: ColorMapFixedPart).
     */
    boolean setupColorMasksFromto(int srcBits, int targetBits) {
        int mask;
        int deltaBits;
        int[] shifts = {0, 0, 0, 0}; // self var: #shifts declareC:'static int shifts[4] = {0, 0, 0, 0}'.
        int[] masks = {0, 0, 0, 0}; // self var: #masks declareC:'static unsigned int masks[4] = {0, 0, 0, 0}'.

        deltaBits = targetBits - srcBits; // deltaBits := targetBits - srcBits.
        if (deltaBits == 0) { // deltaBits = 0 ifTrue:[^0].
            return false;
        }
        if (deltaBits <= 0) { // deltaBits <= 0 // ifTrue:[
            mask = (1 << targetBits) - 1; // mask := 1 << targetBits - 1.

            // "Mask for extracting a color part of the source"
            masks[RedIndex] = (mask << ((srcBits * 2) - deltaBits)); // masks at: RedIndex put: mask << (srcBits*2 - deltaBits).
            masks[GreenIndex] = (mask << (srcBits - deltaBits)); // masks at: GreenIndex put: mask << (srcBits - deltaBits).
            masks[BlueIndex] = (mask << (0 - deltaBits)); // masks at: BlueIndex put: mask << (0 - deltaBits).
            masks[AlphaIndex] = 0; // masks at: AlphaIndex put: 0]
        } else { // ifFalse:[
            mask = (1 << srcBits) - 1; // mask := 1 << srcBits - 1.

            // "Mask for extracting a color part of the source"
            masks[RedIndex] = (mask << (srcBits * 2)); // masks at: RedIndex put: mask << (srcBits*2).
            masks[GreenIndex] = (mask << srcBits); // masks at: GreenIndex put: mask << srcBits.
            masks[BlueIndex] = mask; // masks at: BlueIndex put: mask].
        }

        // "Shifts for adjusting each value in a cm RGB value"
        shifts[RedIndex] = (deltaBits * 3); // shifts at: RedIndex put: deltaBits * 3.
        shifts[GreenIndex] = (deltaBits * 2); // shifts at: GreenIndex put: deltaBits * 2.
        shifts[BlueIndex] = deltaBits; // shifts at: BlueIndex put: deltaBits.
        shifts[AlphaIndex] = 0; // shifts at: AlphaIndex put: 0.

        cmShiftTable = shifts; // cmShiftTable := shifts.
        cmMaskTable = masks; // cmMaskTable := masks.
        cmFlags |= (ColorMapPresent | ColorMapFixedPart); // cmFlags := cmFlags bitOr: (ColorMapPresent bitOr: ColorMapFixedPart).

        return true;
    }

    /*
    clipRange
	"clip and adjust source origin and extent appropriately"
	"first in x"
	destX >= clipX
		ifTrue: [sx := sourceX.
				dx := destX.
				bbW := width]
		ifFalse: [sx := sourceX + (clipX - destX).
				bbW := width - (clipX - destX).
				dx := clipX].
	(dx + bbW) > (clipX + clipWidth)
		ifTrue: [bbW := bbW - ((dx + bbW) - (clipX + clipWidth))].
	"then in y"
	destY >= clipY
		ifTrue: [sy := sourceY.
				dy := destY.
				bbH := height]
		ifFalse: [sy := sourceY + clipY - destY.
				bbH := height - (clipY - destY).
				dy := clipY].
	(dy + bbH) > (clipY + clipHeight)
		ifTrue: [bbH := bbH - ((dy + bbH) - (clipY + clipHeight))].
	noSource ifTrue: [^ nil].
	sx < 0
		ifTrue: [dx := dx - sx.
				bbW := bbW + sx.
				sx := 0].
	sx + bbW > sourceWidth
		ifTrue: [bbW := bbW - (sx + bbW - sourceWidth)].
	sy < 0
		ifTrue: [dy := dy - sy.
				bbH := bbH + sy.
				sy := 0].
	sy + bbH > sourceHeight
		ifTrue: [bbH := bbH - (sy + bbH - sourceHeight)]
     */
    void clipRange() {
        // "first in x"
        if (destX >= clipX) { // destX >= clipX // ifTrue: [
            sx = sourceX; // sx := sourceX.
            dx = destX; // dx := destX.
            bbW = width; // bbW := width]
        } else { // ifFalse: [
            sx = sourceX + (clipX - destX); // sx := sourceX + (clipX - destX).
            bbW = width - (clipX - destX); // bbW := width - (clipX - destX).
            dx = clipX; // dx := clipX].
        }
        if ((dx + bbW) > (clipX + clipWidth)) { // (dx + bbW) > (clipX + clipWidth)
            bbW = bbW - ((dx + bbW) - (clipX + clipWidth)); // ifTrue: [bbW := bbW - ((dx + bbW) - (clipX + clipWidth))].
        }

        // "then in y"
        if (destY >= clipY) { // destY >= clipY // ifTrue: [
            sy = sourceY; // sy := sourceY.
            dy = destY; // dy := destY.
            bbH = height; // bbH := height]
        } else { // ifFalse: [
            sy = (sourceY + clipY) - destY; // sy := sourceY + clipY - destY.
            bbH = height - (clipY - destY); // bbH := height - (clipY - destY).
            dy = clipY; // dy := clipY].
        }
        if ((dy + bbH) > (clipY + clipHeight)) { // (dy + bbH) > (clipY + clipHeight)
            bbH = bbH - ((dy + bbH) - (clipY + clipHeight)); // ifTrue: [bbH := bbH - ((dy + bbH) - (clipY + clipHeight))].
        }

        if (noSource) { // noSource ifTrue: [^ nil].
            return;
        }

        if (sx < 0) { // sx < 0 // ifTrue: [
            dx -= sx; // dx := dx - sx.
            bbW += sx; // bbW := bbW + sx.
            sx = 0; // sx := 0].
        }
        if ((sx + bbW) > source.width) { // sx + bbW > sourceWidth // ifTrue: [
            bbW = bbW - ((sx + bbW) - source.width); // bbW := bbW - (sx + bbW - sourceWidth)].
        }
        if (sy < 0) { // sy < 0 // ifTrue: [
            dy -= sy; // dy := dy - sy.
            bbH += sy; // bbH := bbH + sy.
            sy = 0; // sy := 0].
        }
        if ((sy + bbH) > source.height) { // sy + bbH > sourceHeight
            bbH = bbH - ((sy + bbH) - source.height); // ifTrue: [bbH := bbH - (sy + bbH - sourceHeight)]
        }
    }

    /*
    copyBits
	"This function is exported for the Balloon engine"
	self export: true.
	self inline: false.
	self clipRange.
	(bbW <= 0 or: [bbH <= 0]) ifTrue:
		["zero width or height; noop"
		affectedL := affectedR := affectedT := affectedB := 0.
		^ nil].
	"Lock the surfaces"
	self lockSurfaces ifFalse:[^interpreterProxy primitiveFail].
	self copyBitsLockedAndClipped.
	self unlockSurfaces.
     */
    public boolean copyBits() {
        clipRange(); // self clipRange.
        if (bbW <= 0 || bbH <= 0) { // (bbW <= 0 or: [bbH <= 0]) ifTrue:
            // ["zero width or height; noop"
            affectedL = affectedR = affectedT = affectedB = 0; // affectedL := affectedR := affectedT := affectedB := 0.
            return false; // ^ nil].
        }

        // "Lock the surfaces"
        if( !lockSurfaces() ){ // self lockSurfaces ifFalse:[
            success = false;
            throw PrimitiveHandler.failExpected();
        } // ].

	copyBitsLockedAndClipped(); // self copyBitsLockedAndClipped.
	unlockSurfaces(); // self unlockSurfaces.

        return true;
    }

    private boolean lockSurfaces(){
        return true; // not yet implemented
    }

    private void unlockSurfaces(){
        // not yet implemented
    }

    /*
    copyBitsLockedAndClipped
	"Perform the actual copyBits operation.
	Assume: Surfaces have been locked and clipping was performed."
	| done |
	self inline: true.
	"Try a shortcut for stuff that should be run as quickly as possible"
 	done := self tryCopyingBitsQuickly.
	done ifTrue:[^nil].

	(combinationRule = 30) | (combinationRule = 31) ifTrue:
		["Check and fetch source alpha parameter for alpha blend"
		interpreterProxy methodArgumentCount = 1
			ifTrue: [sourceAlpha := interpreterProxy stackIntegerValue: 0.
					(interpreterProxy failed not and: [(sourceAlpha >= 0) & (sourceAlpha <= 255)])
						ifFalse: [^ interpreterProxy primitiveFail]]
			ifFalse: [^ interpreterProxy primitiveFail]].

	bitCount := 0.
	"Choose and perform the actual copy loop."
	self performCopyLoop.

	(combinationRule = 22) | (combinationRule = 32) ifTrue:
		["zero width and height; return the count"
		affectedL := affectedR := affectedT := affectedB := 0].
	hDir > 0
		ifTrue: [affectedL := dx.
				affectedR := dx + bbW]
		ifFalse: [affectedL := dx - bbW + 1.
				affectedR := dx + 1].
	vDir > 0
		ifTrue: [affectedT := dy.
				affectedB := dy + bbH]
		ifFalse: [affectedT := dy - bbH + 1.
				affectedB := dy + 1]
     */
    private boolean copyBitsLockedAndClipped(){
        // "Try a shortcut for stuff that should be run as quickly as possible"
 	boolean done = tryCopyingBitsQuickly(); // done := self tryCopyingBitsQuickly.
	if(done) {
		return true;
	}

        if ((combinationRule == 30) || (combinationRule == 31)) { // (combinationRule = 30) | (combinationRule = 31) ifTrue:
            // ["Check and fetch source alpha parameter for alpha blend"
            if(methodArgumentCount == 1){ // interpreterProxy methodArgumentCount = 1 // ifTrue: [
               sourceAlpha = (Integer)stack.stackValue(0); //  sourceAlpha := interpreterProxy stackIntegerValue: 0.
               if(!(!failed() && sourceAlpha >= 0 && sourceAlpha <= 255)){ // (interpreterProxy failed not and: [(sourceAlpha >= 0) & (sourceAlpha <= 255)])
                   success = false;
                    throw PrimitiveHandler.failExpected();
               }
            } else {
                success = false;
                throw PrimitiveHandler.failExpected();
            }
        }

        bitCount = 0; // bitCount := 0.

	// "Choose and perform the actual copy loop."
	performCopyLoop();// self performCopyLoop.

        if ((combinationRule == 22) || (combinationRule == 32)) { // (combinationRule = 22) | (combinationRule = 32) ifTrue:
            // ["zero width and height; return the count"
            affectedL = affectedR = affectedT = affectedB = 0; // affectedL := affectedR := affectedT := affectedB := 0].
        }

        if (hDir > 0) { // hDir > 0
            affectedL = dx; // ifTrue: [affectedL := dx.
            affectedR = dx + bbW; // affectedR := dx + bbW]
        } else {
            affectedL = (dx - bbW) + 1; // ifFalse: [affectedL := dx - bbW + 1.
            affectedR = dx + 1; // affectedR := dx + 1].
        }

        if (vDir > 0) { // vDir > 0
            affectedT = dy; // ifTrue: [affectedT := dy.
            affectedB = dy + bbH; // affectedB := dy + bbH]
        } else {
            affectedT = (dy - bbH) + 1; // ifFalse: [affectedT := dy - bbH + 1.
            affectedB = dy + 1; // affectedB := dy + 1]
        }

        return true;
    }

    /*
    performCopyLoop
	"Based on the values provided during setup choose and
	perform the appropriate inner loop function."
	self inline: true. "Should be inlined into caller for speed"
	self destMaskAndPointerInit.
	noSource ifTrue: ["Simple fill loop"
		self copyLoopNoSource.
	] ifFalse: ["Loop using source and dest"
		self checkSourceOverlap.
		(sourceDepth ~= destDepth or: [(cmFlags ~= 0) or:[sourceMSB ~= destMSB]]) ifTrue: [
			"If we must convert between pixel depths or use
			color lookups or swap pixels use the general version"
			self copyLoopPixMap.
		] ifFalse: [
			"Otherwise we simple copy pixels and can use a faster version"
			self sourceSkewAndPointerInit.
			self copyLoop.
		]
	].
     */
    private void performCopyLoop(){
        destMaskAndPointerInit(); // self destMaskAndPointerInit.

        if (noSource) { // noSource ifTrue: ["Simple fill loop"
            copyLoopNoSource(); // self copyLoopNoSource.
        } else { // ] ifFalse: ["Loop using source and dest"
            checkSourceOverlap(); // self checkSourceOverlap.
            if ((source.depth != dest.depth) || ((cmFlags != 0) || (source.msb != dest.msb))) { // (sourceDepth ~= destDepth or: [(cmFlags ~= 0) or:[sourceMSB ~= destMSB]]) ifTrue: [
                // "If we must convert between pixel depths or use
                // color lookups or swap pixels use the general version"
                copyLoopPixMap(); // self copyLoopPixMap.
            } else { // ] ifFalse: [
                // "Otherwise we simple copy pixels and can use a faster version"
                sourceSkewAndPointerInit(); // self sourceSkewAndPointerInit.
                copyLoop(); // self copyLoop.
            } // ]
        } // ].
    }

    /*
    destMaskAndPointerInit
	"Compute masks for left and right destination words"
	| startBits pixPerM1 endBits |
	self inline: true.
	pixPerM1 := destPPW - 1.  "A mask, assuming power of two"
	"how many pixels in first word"
	startBits := destPPW - (dx bitAnd: pixPerM1).
	destMSB
		ifTrue:[ mask1 := AllOnes >> (32 - (startBits*destDepth))]
		ifFalse:[ mask1 := AllOnes << (32 - (startBits*destDepth))].
	"how many pixels in last word"
	endBits := ((dx + bbW - 1) bitAnd: pixPerM1) + 1.
	destMSB
		ifTrue:[mask2 := AllOnes << (32 - (endBits*destDepth))]
		ifFalse:[mask2 := AllOnes >> (32 - (endBits*destDepth))].
	"determine number of words stored per line; merge masks if only 1"
	bbW < startBits
		ifTrue: [mask1 := mask1 bitAnd: mask2.
				mask2 := 0.
				nWords := 1]
		ifFalse: [nWords := (bbW - startBits) + pixPerM1 // destPPW + 1].
	hDir := vDir := 1. "defaults for no overlap with source"

	"calculate byte addr and delta, based on first word of data"
	"Note pitch is bytes and nWords is longs, not bytes"
	destIndex := destBits + (dy * destPitch) + ((dx // destPPW) *4).
	destDelta := destPitch * vDir - (4 * (nWords * hDir)).  "byte addr delta"
     */
    void destMaskAndPointerInit() {
        int pixPerM1;
        int endBits;
        int startBits;
        pixPerM1 = dest.pixPerWord - 1;  // pixPerM1 := destPPW - 1.  "A mask, assuming power of two"

        // "how many pixels in first word"
        startBits = dest.pixPerWord - (dx & pixPerM1); // startBits := destPPW - (dx bitAnd: pixPerM1).
        mask1 = dest.msb ? AllOnes >>> (32 - (startBits * dest.depth)) // destMSB ifTrue:[ mask1 := AllOnes >> (32 - (startBits*destDepth))]
                : AllOnes << (32 - (startBits * dest.depth)); // ifFalse:[ mask1 := AllOnes << (32 - (startBits*destDepth))].

        // "how many pixels in last word"
        endBits = (((dx + bbW) - 1) & pixPerM1) + 1; // endBits := ((dx + bbW - 1) bitAnd: pixPerM1) + 1.
        mask2 = dest.msb ? AllOnes << (32 - (endBits * dest.depth)) // destMSB ifTrue:[mask2 := AllOnes << (32 - (endBits*destDepth))]
                : AllOnes >>> (32 - (endBits * dest.depth)); // ifFalse:[mask2 := AllOnes >> (32 - (endBits*destDepth))].

        // "determine number of words stored per line; merge masks if only 1"
        if (bbW < startBits) { //start and end in same word, so merge masks // bbW < startBits
            mask1 = mask1 & mask2; // ifTrue: [mask1 := mask1 bitAnd: mask2.
            mask2 = 0; // mask2 := 0.
            nWords = 1; // nWords := 1]
        } else {
            nWords = (((bbW - startBits) + pixPerM1) / dest.pixPerWord) + 1; // ifFalse: [nWords := (bbW - startBits) + pixPerM1 // destPPW + 1].
        }

        hDir = vDir = 1; // hDir := vDir := 1. "defaults for no overlap with source"

        // "calculate byte addr and delta, based on first word of data"
	// "Note pitch is bytes and nWords is longs, not bytes"

        destIndex = (dy * dest.pitch) + ((dx / dest.pixPerWord)*4); // destIndex := destBits + (dy * destPitch) + ((dx // destPPW) *4).
                // we do not use destBits here, because we access an array, not a memory address

        destDelta = (dest.pitch * vDir) - (4 * nWords * hDir); // destDelta := destPitch * vDir - (4 * (nWords * hDir)).  "byte addr delta"
    }

    /*
    checkSourceOverlap
	"check for possible overlap of source and destination"
	"ar 10/19/1999: This method requires surfaces to be locked."
	| t |
	self inline: true.
	(sourceForm = destForm and: [dy >= sy]) ifTrue:
		[dy > sy ifTrue:
			["have to start at bottom"
			vDir := -1.
			sy := sy + bbH - 1.
			dy := dy + bbH - 1]
		ifFalse:
			[(dy = sy) & (dx > sx) ifTrue:
				["y's are equal, but x's are backward"
				hDir := -1.
				sx := sx + bbW - 1.
				"start at right"
				dx := dx + bbW - 1.
				"and fix up masks"
				nWords > 1 ifTrue:
					[t := mask1.
					mask1 := mask2.
					mask2 := t]]].
		"Dest inits may be affected by this change"
		destIndex := destBits + (dy * destPitch) + ((dx // destPPW) *4).
		destDelta := (destPitch * vDir) - (4 * (nWords * hDir))]
     */
    void checkSourceOverlap() {
        int t;
        if ((sourceForm == destForm) && (dy >= sy)) { // (sourceForm = destForm and: [dy >= sy]) ifTrue:
            if (dy > sy) { // [dy > sy ifTrue: // ["have to start at bottom"
                vDir = -1; // vDir := -1.
                sy = (sy + bbH) - 1; // sy := sy + bbH - 1.
                dy = (dy + bbH) - 1; // dy := dy + bbH - 1]
            } else { // ifFalse:
                if ((dy == sy) && (dx > sx)) { // [(dy = sy) & (dx > sx) ifTrue: // ["y's are equal, but x's are backward"
                    hDir = -1; // hDir := -1.
                    sx = (sx + bbW) - 1; // sx := sx + bbW - 1.

                    // "start at right"
                    dx = (dx + bbW) - 1; // dx := dx + bbW - 1.

                    // "and fix up masks"
                    if (nWords > 1) { // nWords > 1 ifTrue:
                        t = mask1; // [t := mask1.
                        mask1 = mask2; // mask1 := mask2.
                        mask2 = t; // mask2 := t]]].
                    }
                }
            }

            // "Dest inits may be affected by this change"
            destIndex = (dy * dest.pitch) + ((dx / dest.pixPerWord)*4); // destIndex := destBits + (dy * destPitch) + ((dx // destPPW) *4).
                    // we do not use destBits here, because we access an array, not a memory address

            destDelta = (dest.pitch * vDir) - (4 * nWords * hDir); // destDelta := (destPitch * vDir) - (4 * (nWords * hDir))]
        }
    }

    /*
    sourceSkewAndPointerInit
	"This is only used when source and dest are same depth,
	ie, when the barrel-shift copy loop is used."
	| dWid sxLowBits dxLowBits pixPerM1 |
	self inline: true.
	pixPerM1 := destPPW - 1.  "A mask, assuming power of two"
	sxLowBits := sx bitAnd: pixPerM1.
	dxLowBits := dx bitAnd: pixPerM1.
	"check if need to preload buffer
	(i.e., two words of source needed for first word of destination)"
	hDir > 0 ifTrue:
		["n Bits stored in 1st word of dest"
		dWid := bbW min: destPPW - dxLowBits.
		preload := (sxLowBits + dWid) > pixPerM1]
	ifFalse:
		[dWid := bbW min: dxLowBits + 1.
		preload := (sxLowBits - dWid + 1) < 0].

	"calculate right-shift skew from source to dest"
	sourceMSB
		ifTrue:[skew := (sxLowBits - dxLowBits) * destDepth]
		ifFalse:[skew := (dxLowBits - sxLowBits) * destDepth].  " -32..32 "
	preload ifTrue:
		[skew < 0
			ifTrue: [skew := skew+32]
			ifFalse: [skew := skew-32]].

	"Calc byte addr and delta from longWord info"
	sourceIndex := sourceBits + (sy * sourcePitch) + ((sx // (32//sourceDepth)) *4).
	"calculate increments from end of 1 line to start of next"
	sourceDelta := (sourcePitch * vDir) - (4 * (nWords * hDir)).

	preload ifTrue:
		["Compensate for extra source word fetched"
		sourceDelta := sourceDelta - (4*hDir)].
     */
    void sourceSkewAndPointerInit() {
        int pixPerM1;
        int dxLowBits;
        int dWid;
        int sxLowBits;
        pixPerM1 = dest.pixPerWord - 1;  // pixPerM1 := destPPW - 1.  "A mask, assuming power of two"
        sxLowBits = sx & pixPerM1; // sxLowBits := sx bitAnd: pixPerM1.
        dxLowBits = dx & pixPerM1; // dxLowBits := dx bitAnd: pixPerM1.

        // "check if need to preload buffer (i.e., two words of source needed for first word of destination)"
        if (hDir > 0) { // hDir > 0 ifTrue:
            // ["n Bits stored in 1st word of dest"
            dWid = Math.min(bbW, dest.pixPerWord - dxLowBits); // dWid := bbW min: destPPW - dxLowBits.
            preload = (sxLowBits + dWid) > pixPerM1; // preload := (sxLowBits + dWid) > pixPerM1]
        } else { // ifFalse:
            dWid = Math.min(bbW, dxLowBits + 1); // [dWid := bbW min: dxLowBits + 1.
            preload = ((sxLowBits - dWid) + 1) < 0; // preload := (sxLowBits - dWid + 1) < 0].
        }
        if(source.msb){ // sourceMSB
            skew = (sxLowBits - dxLowBits) * dest.depth; // ifTrue:[skew := (sxLowBits - dxLowBits) * destDepth]
        } else {
            skew = (dxLowBits - sxLowBits) * dest.depth; // ifFalse:[skew := (dxLowBits - sxLowBits) * destDepth].  " -32..32 "
        }

        if (preload) { // preload ifTrue:
            if (skew < 0) { // [skew < 0
                skew += 32; // ifTrue: [skew := skew+32]
            } else {
                skew -= 32; // ifFalse: [skew := skew-32]].
            }
        }

        // "Calc byte addr and delta from longWord info"
	sourceIndex = (sy * source.pitch) + ((sx / (32 / source.depth))*4); // sourceIndex := sourceBits + (sy * sourcePitch) + ((sx // (32//sourceDepth)) *4).
                // we do not use sourceBits here, because we access an array, not a memory address

	// "calculate increments from end of 1 line to start of next"
	sourceDelta = (source.pitch * vDir) - (4 * (nWords * hDir)); // sourceDelta := (sourcePitch * vDir) - (4 * (nWords * hDir)).

        if (preload) { // preload ifTrue:
            // ["Compensate for extra source word fetched"
            sourceDelta -= 4* hDir; // sourceDelta := sourceDelta - (4*hDir)].
        }
    }

    /*
    copyLoopNoSource
	"Faster copyLoop when source not used. hDir and vDir are both
	positive, and perload and skew are unused"
	| halftoneWord mergeWord mergeFnwith destWord destIndexLocal nWordsMinusOne |
	self inline: false.
	self var: #mergeFnwith declareC: 'int (*mergeFnwith)(int, int)'.
	mergeFnwith := self
				cCoerce: (opTable at: combinationRule + 1)
				to: 'int (*)(int, int)'.
	mergeFnwith.
	"null ref for compiler"
	destIndexLocal := destIndex.
	nWordsMinusOne := nWords - 1.
	1
		to: bbH
		do: [:i |
			"here is the vertical loop"
			noHalftone
				ifTrue: [halftoneWord := AllOnes]
				ifFalse: [halftoneWord := self halftoneAt: dy + i - 1].
			"Note: the horizontal loop has been expanded into three parts for
			speed:"
			"This first section requires masking of the destination store..."
			destMask := mask1.
			destWord := self dstLongAt: destIndexLocal.
			mergeWord := self mergeFn: halftoneWord with: destWord.
			destWord := (destMask bitAnd: mergeWord)
						bitOr: (destWord bitAnd: destMask bitInvert32).
			self dstLongAt: destIndexLocal put: destWord.
			destIndexLocal := destIndexLocal + 4.
			"This central horizontal loop requires no store masking"
			destMask := AllOnes.
			combinationRule = 3
				ifTrue: ["Special inner loop for STORE"
					destWord := halftoneWord.
					2
						to: nWordsMinusOne
						do: [:word |
							self dstLongAt: destIndexLocal put: destWord.
							destIndexLocal := destIndexLocal + 4]]
				ifFalse: ["Normal inner loop does merge"
					2
						to: nWordsMinusOne
						do: [:word |
							"Normal inner loop does merge"
							destWord := self dstLongAt: destIndexLocal.
							mergeWord := self mergeFn: halftoneWord with: destWord.
							self dstLongAt: destIndexLocal put: mergeWord.
							destIndexLocal := destIndexLocal + 4]].
			"This last section, if used, requires masking of the destination
			store..."
			nWords > 1
				ifTrue: [destMask := mask2.
					destWord := self dstLongAt: destIndexLocal.
					mergeWord := self mergeFn: halftoneWord with: destWord.
					destWord := (destMask bitAnd: mergeWord)
								bitOr: (destWord bitAnd: destMask bitInvert32).
					self dstLongAt: destIndexLocal put: destWord.
					destIndexLocal := destIndexLocal + 4].
			destIndexLocal := destIndexLocal + destDelta]
     */
    void copyLoopNoSource() {
        int mergeWord;
        int halftoneWord;
        int destWord;
        int destIndexLocal;
        int nWordsMinusOne;

        destIndexLocal = destIndex; // destIndexLocal := destIndex.
        nWordsMinusOne = nWords -1; // nWordsMinusOne := nWords - 1.

        for (int i = 1; i <= bbH; i += 1) { // 1 to: bbH do: [:i |
            // "here is the vertical loop"
            if (noHalftone) { // noHalftone
                halftoneWord = AllOnes; // ifTrue: [halftoneWord := AllOnes]
            }else{
                halftoneWord = halftoneAt((dy + i) - 1); // ifFalse: [halftoneWord := self halftoneAt: dy + i - 1].
            }

            // "Note: the horizontal loop has been expanded into three parts for speed:"
            // "This first section requires masking of the destination store..."
            destMask = mask1; // destMask := mask1.
            destWord = dstLongAt(destIndexLocal); // destWord := self dstLongAt: destIndexLocal.
            mergeWord = mergeFnwith.mergeFnwith(halftoneWord, destWord); // mergeWord := self mergeFn: halftoneWord with: destWord.
            destWord = (destMask & mergeWord) | (destWord & (~destMask)); // destWord := (destMask bitAnd: mergeWord) bitOr: (destWord bitAnd: destMask bitInvert32).
            dstLongAtput(destIndexLocal, destWord); // self dstLongAt: destIndexLocal put: destWord.
            destIndexLocal += 4; // destIndexLocal := destIndexLocal + 4.

            // "This central horizontal loop requires no store masking"
            destMask = AllOnes; // destMask := AllOnes.
            if (combinationRule == 3) { // combinationRule = 3 ifTrue:
                // ["Special inner loop for STORE"
                destWord = halftoneWord; // destWord := halftoneWord.
                for (int word = 2; word <= nWordsMinusOne; word++) { // 2 to: nWordsMinusOne do: [:word |
                    dstLongAtput(destIndexLocal, destWord); // self dstLongAt: destIndexLocal put: destWord.
                    destIndexLocal += 4; // destIndexLocal := destIndexLocal + 4]]
                }
            } else { // ifFalse: ["Normal inner loop does merge"
                for (int word = 2; word <= nWordsMinusOne; word++) { // 2 to: nWordsMinusOne do: [:word |
                    // "Normal inner loop does merge"
                    destWord = dstLongAt(destIndexLocal); // destWord := self dstLongAt: destIndexLocal.
                    mergeWord = mergeFnwith.mergeFnwith(halftoneWord, destWord); // mergeWord := self mergeFn: halftoneWord with: destWord.
                    dstLongAtput(destIndexLocal, mergeWord); // self dstLongAt: destIndexLocal put: mergeWord.
                    destIndexLocal += 4; // destIndexLocal := destIndexLocal + 4]].
                }
            }

            // "This last section, if used, requires masking of the destination store..."
            if (nWords > 1) { // nWords > 1 ifTrue:
                destMask = mask2; // [destMask := mask2.
                destWord = dstLongAt(destIndexLocal); // destWord := self dstLongAt: destIndexLocal.
                mergeWord = mergeFnwith.mergeFnwith(halftoneWord, destWord); // mergeWord := self mergeFn: halftoneWord with: destWord.
                destWord = (destMask & mergeWord) | (destWord & (~destMask)); // destWord := (destMask bitAnd: mergeWord) bitOr: (destWord bitAnd: destMask bitInvert32).
                dstLongAtput(destIndexLocal, destWord); // self dstLongAt: destIndexLocal put: destWord.
                destIndexLocal += 4; // destIndexLocal := destIndexLocal + 4].
            }
            destIndexLocal += destDelta; // destIndexLocal := destIndexLocal + destDelta]
        }
    }

    /*
    copyLoop
	"This version of the inner loop assumes noSource = false."
	| prevWord thisWord skewWord halftoneWord mergeWord hInc y unskew skewMask notSkewMask mergeFnwith destWord skewLocal sourceIndexLocal destIndexLocal vDirLocal hDirLocal nWordsMinusOne |
	self inline: false.
	self var: #mergeFnwith declareC: 'int (*mergeFnwith)(int, int)'.
	mergeFnwith := self
				cCoerce: (opTable at: combinationRule + 1)
				to: 'int (*)(int, int)'.
	mergeFnwith.
	"null ref for compiler"
	hInc := hDir * 4.
	skewLocal := skew.
	sourceIndexLocal := sourceIndex.
	destIndexLocal := destIndex.
	vDirLocal := vDir.
	hDirLocal := hDir.
	nWordsMinusOne := nWords - 1.
	"Byte delta"
	"degenerate skew fixed for Sparc. 10/20/96 ikp"
	skewLocal == -32
		ifTrue: [skewLocal := unskew := skewMask := 0]
		ifFalse: [skewLocal < 0
				ifTrue: [unskew := skewLocal + 32.
					skewMask := AllOnes << (0 - skewLocal)]
				ifFalse: [skewLocal = 0
						ifTrue: [unskew := 0.
							skewMask := AllOnes]
						ifFalse: [unskew := skewLocal - 32.
							skewMask := AllOnes >> skewLocal]]].
	notSkewMask := skewMask bitInvert32.
	noHalftone
		ifTrue: [halftoneWord := AllOnes.
			halftoneHeight := 0]
		ifFalse: [halftoneWord := self halftoneAt: 0].
	y := dy.
	1
		to: bbH
		do: [:i |
			"here is the vertical loop"
			halftoneHeight > 1
				ifTrue: ["Otherwise, its always the same"
					halftoneWord := self halftoneAt: y.
					y := y + vDirLocal].
			preload
				ifTrue: ["load the 64-bit shifter"
					prevWord := self srcLongAt: sourceIndexLocal.
					sourceIndexLocal := sourceIndexLocal + hInc]
				ifFalse: [prevWord := 0].
			"Note: the horizontal loop has been expanded into three parts for
			speed:"
			"This first section requires masking of the destination store..."
			destMask := mask1.
			thisWord := self srcLongAt: sourceIndexLocal.
			"pick up next word"
			sourceIndexLocal := sourceIndexLocal + hInc.
			skewWord := ((prevWord bitAnd: notSkewMask)
						bitShift: unskew)
						bitOr: ((thisWord bitAnd: skewMask)
								bitShift: skewLocal).
			"32-bit rotate"
			prevWord := thisWord.
			destWord := self dstLongAt: destIndexLocal.
			mergeWord := self
						mergeFn: (skewWord bitAnd: halftoneWord)
						with: destWord.
			destWord := (destMask bitAnd: mergeWord)
						bitOr: (destWord bitAnd: destMask bitInvert32).
			self dstLongAt: destIndexLocal put: destWord.
			destIndexLocal := destIndexLocal + hInc.
			"This central horizontal loop requires no store masking"
			destMask := AllOnes.
			combinationRule = 3
				ifTrue: [skewLocal = 0 & (halftoneWord = AllOnes)
						ifTrue: ["Very special inner loop for STORE mode with no
							skew -- just move words"
							hDirLocal = -1
								ifTrue: ["Woeful patch: revert to older code for
									hDir = -1"
									2
										to: nWordsMinusOne
										do: [:word |
											thisWord := self srcLongAt: sourceIndexLocal.
											sourceIndexLocal := sourceIndexLocal + hInc.
											self dstLongAt: destIndexLocal put: thisWord.
											destIndexLocal := destIndexLocal + hInc]]
								ifFalse: [2
										to: nWordsMinusOne
										do: [:word |
											"Note loop starts with prevWord
											loaded (due to preload)"
											self dstLongAt: destIndexLocal put: prevWord.
											destIndexLocal := destIndexLocal + hInc.
											prevWord := self srcLongAt: sourceIndexLocal.
											sourceIndexLocal := sourceIndexLocal + hInc]]]
						ifFalse: ["Special inner loop for STORE mode -- no need to
							call merge"
							2
								to: nWordsMinusOne
								do: [:word |
									thisWord := self srcLongAt: sourceIndexLocal.
									sourceIndexLocal := sourceIndexLocal + hInc.
									skewWord := ((prevWord bitAnd: notSkewMask)
												bitShift: unskew)
												bitOr: ((thisWord bitAnd: skewMask)
														bitShift: skewLocal).
									"32-bit rotate"
									prevWord := thisWord.
									self
										dstLongAt: destIndexLocal
										put: (skewWord bitAnd: halftoneWord).
									destIndexLocal := destIndexLocal + hInc]]]
				ifFalse: [2
						to: nWordsMinusOne
						do: [:word |
							"Normal inner loop does merge:"
							thisWord := self srcLongAt: sourceIndexLocal.
							"pick up next word"
							sourceIndexLocal := sourceIndexLocal + hInc.
							skewWord := ((prevWord bitAnd: notSkewMask)
										bitShift: unskew)
										bitOr: ((thisWord bitAnd: skewMask)
												bitShift: skewLocal).
							"32-bit rotate"
							prevWord := thisWord.
							mergeWord := self
										mergeFn: (skewWord bitAnd: halftoneWord)
										with: (self dstLongAt: destIndexLocal).
							self dstLongAt: destIndexLocal put: mergeWord.
							destIndexLocal := destIndexLocal + hInc]].
			"This last section, if used, requires masking of the destination
			store..."
			nWords > 1
				ifTrue: [destMask := mask2.
					thisWord := self srcLongAt: sourceIndexLocal.
					"pick up next word"
					sourceIndexLocal := sourceIndexLocal + hInc.
					skewWord := ((prevWord bitAnd: notSkewMask)
								bitShift: unskew)
								bitOr: ((thisWord bitAnd: skewMask)
										bitShift: skewLocal).
					"32-bit rotate"
					destWord := self dstLongAt: destIndexLocal.
					mergeWord := self
								mergeFn: (skewWord bitAnd: halftoneWord)
								with: destWord.
					destWord := (destMask bitAnd: mergeWord)
								bitOr: (destWord bitAnd: destMask bitInvert32).
					self dstLongAt: destIndexLocal put: destWord.
					destIndexLocal := destIndexLocal + hInc].
			sourceIndexLocal := sourceIndexLocal + sourceDelta.
			destIndexLocal := destIndexLocal + destDelta]
     */
    void copyLoop() {
        int prevWord;
        int thisWord;
        int skewWord;
        int halftoneWord;
        int mergeWord;
        int hInc;
        int y;
        int unskew;
        int skewMask;
        int notSkewMask;
        int destWord;
        int skewLocal;
        int sourceIndexLocal;
        int destIndexLocal;
        int vDirLocal;
        int hDirLocal;
        int nWordsMinusOne;

        hInc = hDir * 4; // hInc := hDir * 4.
        skewLocal = skew; // skewLocal := skew.
        sourceIndexLocal = sourceIndex; // sourceIndexLocal := sourceIndex.
	destIndexLocal = destIndex; // destIndexLocal := destIndex.
	vDirLocal = vDir; // vDirLocal := vDir.
	hDirLocal = hDir; // hDirLocal := hDir.
	nWordsMinusOne = nWords -1; // nWordsMinusOne := nWords - 1.

        // "Byte delta"
	// "degenerate skew fixed for Sparc. 10/20/96 ikp"
        if (skewLocal == -32) { // skewLocal == -32
            skewLocal = unskew = skewMask = 0; // ifTrue: [skewLocal := unskew := skewMask := 0]
        } else { // ifFalse:
            if (skewLocal < 0) { // [skewLocal < 0
                unskew = skewLocal + 32; // ifTrue: [unskew := skewLocal + 32.
                skewMask = AllOnes << (0 - skewLocal); // skewMask := AllOnes << (0 - skewLocal)]
            } else { // ifFalse:
                if (skewLocal == 0) { // [skewLocal = 0 // ifTrue:
                    unskew = 0; // [unskew := 0.
                    skewMask = AllOnes; // skewMask := AllOnes]
                } else { // ifFalse:
                    unskew = skewLocal - 32; // [unskew := skewLocal - 32.
                    skewMask = (AllOnes) >>> skewLocal; // skewMask := AllOnes >> skewLocal]]].
                }
            }
        }
        notSkewMask = ~skewMask; // notSkewMask := skewMask bitInvert32.
        if (noHalftone) { // noHalftone // ifTrue:
            halftoneWord = AllOnes; // [halftoneWord := AllOnes.
            halftoneHeight = 0; // halftoneHeight := 0]
        } else { // ifFalse:
            halftoneWord = halftoneAt(0); // [halftoneWord := self halftoneAt: 0].
        }
        y = dy; // y := dy.

        for (int i = 1; i <= bbH; i ++) { // 1 to: bbH do: [:i |
            // "here is the vertical loop"
            if (halftoneHeight > 1) { // halftoneHeight > 1 // ifTrue: ["Otherwise, its always the same"
                halftoneWord = halftoneAt(y); // halftoneWord := self halftoneAt: y.
                y += vDirLocal; // y := y + vDirLocal].
            }
            if (preload) { // preload // ifTrue: ["load the 64-bit shifter"
                prevWord = srcLongAt(sourceIndexLocal); // prevWord := self srcLongAt: sourceIndexLocal.
                sourceIndexLocal += hInc; // sourceIndexLocal := sourceIndexLocal + hInc]
            } else { // ifFalse:
                prevWord = 0; // [prevWord := 0].
            }

            // "Note: the horizontal loop has been expanded into three parts for speed:"
            // "This first section requires masking of the destination store..."
            destMask = mask1; // destMask := mask1.
            thisWord = srcLongAt(sourceIndexLocal); // thisWord := self srcLongAt: sourceIndexLocal.

            // "pick up next word"
            sourceIndexLocal += hInc; // sourceIndexLocal := sourceIndexLocal + hInc.

            // skewWord := ((prevWord bitAnd: notSkewMask) bitShift: unskew) bitOr: ((thisWord bitAnd: skewMask) bitShift: skewLocal).
            skewWord = (Arithmetics.bitShift((prevWord & notSkewMask), unskew)) | (Arithmetics.bitShift((thisWord & skewMask), skewLocal));

            // "32-bit rotate"
            prevWord = thisWord; // prevWord := thisWord.
            destWord = dstLongAt(destIndexLocal); // destWord := self dstLongAt: destIndexLocal.
            mergeWord = mergeFnwith.mergeFnwith(skewWord & halftoneWord, destWord); // mergeWord := self mergeFn: (skewWord bitAnd: halftoneWord) with: destWord.
            destWord = (destMask & mergeWord) | (destWord & (~destMask)); // destWord := (destMask bitAnd: mergeWord) bitOr: (destWord bitAnd: destMask bitInvert32).
            dstLongAtput(destIndexLocal, destWord); // self dstLongAt: destIndexLocal put: destWord.
            destIndexLocal += hInc; // destIndexLocal := destIndexLocal + hInc.

            // "This central horizontal loop requires no store masking"
            destMask = AllOnes; // destMask := AllOnes.
            if (combinationRule == 3) { // combinationRule = 3 // ifTrue:
                if ((skewLocal == 0) && (halftoneWord == AllOnes)) { // [skewLocal = 0 & (halftoneWord = AllOnes) // ifTrue:
                    // ["Very special inner loop for STORE mode with no skew -- just move words"
                    if (hDirLocal == -1) { // hDirLocal = -1 // ifTrue: ["Woeful patch: revert to older code for hDir = -1"
                        for (int word = 2; word <= nWordsMinusOne; word ++) { // 2 to: nWordsMinusOne do: [:word |
                            thisWord = srcLongAt(sourceIndexLocal); // thisWord := self srcLongAt: sourceIndexLocal.
                            sourceIndexLocal += hInc; // sourceIndexLocal := sourceIndexLocal + hInc.
                            dstLongAtput(destIndexLocal, thisWord); // self dstLongAt: destIndexLocal put: thisWord.
                            destIndexLocal += hInc; // destIndexLocal := destIndexLocal + hInc]]
                        }
                    } else { // ifFalse:
                        for (int word = 2; word <= nWordsMinusOne; word ++) { // [2 to: nWordsMinusOne do: [:word |
                            // "Note loop starts with prevWord loaded (due to preload)"
                            dstLongAtput(destIndexLocal, prevWord); // self dstLongAt: destIndexLocal put: prevWord.
                            destIndexLocal += hInc; // destIndexLocal := destIndexLocal + hInc.
                            prevWord = srcLongAt(sourceIndexLocal); // prevWord := self srcLongAt: sourceIndexLocal.
                            sourceIndexLocal += hInc; // sourceIndexLocal := sourceIndexLocal + hInc]]]
                        }
                    }
                } else { // ifFalse: ["Special inner loop for STORE mode -- no need to call merge"
                    for (int word = 2; word <= nWordsMinusOne; word ++) { // 2 to: nWordsMinusOne do: [:word |
                        thisWord = srcLongAt(sourceIndexLocal); // thisWord := self srcLongAt: sourceIndexLocal.
                        sourceIndexLocal += hInc; // sourceIndexLocal := sourceIndexLocal + hInc.
                        // skewWord := ((prevWord bitAnd: notSkewMask) bitShift: unskew) bitOr: ((thisWord bitAnd: skewMask) bitShift: skewLocal).
                        skewWord = Arithmetics.bitShift((prevWord & notSkewMask), unskew) | Arithmetics.bitShift((thisWord & skewMask), skewLocal);

                        // "32-bit rotate"
                        prevWord = thisWord; // prevWord := thisWord.
                        dstLongAtput(destIndexLocal, skewWord & halftoneWord); // self dstLongAt: destIndexLocal put: (skewWord bitAnd: halftoneWord).
                        destIndexLocal += hInc; // destIndexLocal := destIndexLocal + hInc]]]
                    }
                }
            } else { // ifFalse:
                for (int word = 2; word <= nWordsMinusOne; word ++) { // [2 to: nWordsMinusOne do: [:word |
                    // "Normal inner loop does merge:"
                    thisWord = srcLongAt(sourceIndexLocal); // thisWord := self srcLongAt: sourceIndexLocal.

                    // "pick up next word"
                    sourceIndexLocal += hInc; // sourceIndexLocal := sourceIndexLocal + hInc.
                    // skewWord := ((prevWord bitAnd: notSkewMask) bitShift: unskew) bitOr: ((thisWord bitAnd: skewMask) bitShift: skewLocal).
                    skewWord = Arithmetics.bitShift((prevWord & notSkewMask), unskew) | Arithmetics.bitShift((thisWord & skewMask), skewLocal);

                    // "32-bit rotate"
                    prevWord = thisWord; // prevWord := thisWord.
                    // mergeWord := self mergeFn: (skewWord bitAnd: halftoneWord) with: (self dstLongAt: destIndexLocal).
                    mergeWord = mergeFnwith.mergeFnwith(skewWord & halftoneWord, dstLongAt(destIndexLocal));
                    dstLongAtput(destIndexLocal, mergeWord); // self dstLongAt: destIndexLocal put: mergeWord.
                    destIndexLocal += hInc; // destIndexLocal := destIndexLocal + hInc]].
                }
            }

            // "This last section, if used, requires masking of the destination store..."
            if (nWords > 1) { // nWords > 1 // ifTrue: [
                destMask = mask2; // destMask := mask2.
                thisWord = srcLongAt(sourceIndexLocal); // thisWord := self srcLongAt: sourceIndexLocal.

                // "pick up next word"
                sourceIndexLocal += hInc; // sourceIndexLocal := sourceIndexLocal + hInc.
                // skewWord := ((prevWord bitAnd: notSkewMask) bitShift: unskew) bitOr: ((thisWord bitAnd: skewMask) bitShift: skewLocal).
                skewWord = Arithmetics.bitShift((prevWord & notSkewMask), unskew) | Arithmetics.bitShift((thisWord & skewMask), skewLocal);

                // "32-bit rotate"
                destWord = dstLongAt(destIndexLocal); // destWord := self dstLongAt: destIndexLocal.
                mergeWord = mergeFnwith.mergeFnwith(skewWord & halftoneWord, destWord); // mergeWord := self mergeFn: (skewWord bitAnd: halftoneWord) with: destWord.
                destWord = (destMask & mergeWord) | (destWord & (~destMask)); // destWord := (destMask bitAnd: mergeWord) bitOr: (destWord bitAnd: destMask bitInvert32).
                dstLongAtput(destIndexLocal, destWord); // self dstLongAt: destIndexLocal put: destWord.
                destIndexLocal += hInc; // destIndexLocal := destIndexLocal + hInc].
            }
            sourceIndexLocal += sourceDelta; // sourceIndexLocal := sourceIndexLocal + sourceDelta.
            destIndexLocal += destDelta; // destIndexLocal := destIndexLocal + destDelta]
        }
    }

    /*
    copyLoopPixMap
	"This version of the inner loop maps source pixels
	to a destination form with different depth. Because it is already
	unweildy, the loop is not unrolled as in the other versions.
	Preload, skew and skewMask are all overlooked, since pickSourcePixels
	delivers its destination word already properly aligned.
	Note that pickSourcePixels could be copied in-line at the top of
	the horizontal loop, and some of its inits moved out of the loop."
	"ar 12/7/1999:
	The loop has been rewritten to use only one pickSourcePixels call.
	The idea is that the call itself could be inlined. If we decide not
	to inline pickSourcePixels we could optimize the loop instead."
	| skewWord halftoneWord mergeWord scrStartBits nSourceIncs startBits endBits sourcePixMask destPixMask mergeFnwith nPix srcShift dstShift destWord words srcShiftInc dstShiftInc dstShiftLeft mapperFlags destIndexLocal |
	self inline: false.
	self var: #mergeFnwith declareC: 'int (*mergeFnwith)(int, int)'.
	mergeFnwith := self
				cCoerce: (opTable at: combinationRule + 1)
				to: 'int (*)(int, int)'.
	mergeFnwith.
	"null ref for compiler"
	destIndexLocal := destIndex.
	"Additional inits peculiar to unequal source and dest pix size..."
	sourcePPW := 32 // sourceDepth.
	sourcePixMask := maskTable at: sourceDepth.
	destPixMask := maskTable at: destDepth.
	mapperFlags := cmFlags bitAnd: ColorMapNewStyle bitInvert32.
	sourceIndex := sourceBits + (sy * sourcePitch) + (sx // sourcePPW * 4).
	scrStartBits := sourcePPW
				- (sx bitAnd: sourcePPW - 1).
	bbW < scrStartBits
		ifTrue: [nSourceIncs := 0]
		ifFalse: [nSourceIncs := bbW - scrStartBits // sourcePPW + 1].
	sourceDelta := sourcePitch - (nSourceIncs * 4).
	"Note following two items were already calculated in destmask setup!"
	startBits := destPPW
				- (dx bitAnd: destPPW - 1).
	endBits := (dx + bbW - 1 bitAnd: destPPW - 1)
				+ 1.
	bbW < startBits
		ifTrue: [startBits := bbW].
	"Precomputed shifts for pickSourcePixels"
	srcShift := (sx bitAnd: sourcePPW - 1)
				* sourceDepth.
	dstShift := (dx bitAnd: destPPW - 1)
				* destDepth.
	srcShiftInc := sourceDepth.
	dstShiftInc := destDepth.
	dstShiftLeft := 0.
	sourceMSB
		ifTrue: [srcShift := 32 - sourceDepth - srcShift.
			srcShiftInc := 0 - srcShiftInc].
	destMSB
		ifTrue: [dstShift := 32 - destDepth - dstShift.
			dstShiftInc := 0 - dstShiftInc.
			dstShiftLeft := 32 - destDepth].
	1
		to: bbH
		do: [:i |
			"here is the vertical loop"
			"*** is it possible at all that noHalftone == false? ***"
			noHalftone
				ifTrue: [halftoneWord := AllOnes]
				ifFalse: [halftoneWord := self halftoneAt: dy + i - 1].
			"setup first load"
			srcBitShift := srcShift.
			dstBitShift := dstShift.
			destMask := mask1.
			nPix := startBits.
			"Here is the horizontal loop..."
			words := nWords.
			["pick up the word"
			skewWord := self
						pickSourcePixels: nPix
						flags: mapperFlags
						srcMask: sourcePixMask
						destMask: destPixMask
						srcShiftInc: srcShiftInc
						dstShiftInc: dstShiftInc.
			"align next word to leftmost pixel"
			dstBitShift := dstShiftLeft.
			destMask = AllOnes
				ifTrue: ["avoid read-modify-write"
					mergeWord := self
								mergeFn: (skewWord bitAnd: halftoneWord)
								with: (self dstLongAt: destIndexLocal).
					self
						dstLongAt: destIndexLocal
						put: (destMask bitAnd: mergeWord)]
				ifFalse: ["General version using dest masking"
					destWord := self dstLongAt: destIndexLocal.
					mergeWord := self
								mergeFn: (skewWord bitAnd: halftoneWord)
								with: (destWord bitAnd: destMask).
					destWord := (destMask bitAnd: mergeWord)
								bitOr: (destWord bitAnd: destMask bitInvert32).
					self dstLongAt: destIndexLocal put: destWord].
			destIndexLocal := destIndexLocal + 4.
			words = 2
				ifTrue: ["e.g., is the next word the last word?"
					"set mask for last word in this row"
					destMask := mask2.
					nPix := endBits]
				ifFalse: ["use fullword mask for inner loop"
					destMask := AllOnes.
					nPix := destPPW].
			(words := words - 1) = 0] whileFalse.
			"--- end of inner loop ---"
			sourceIndex := sourceIndex + sourceDelta.
			destIndexLocal := destIndexLocal + destDelta]
     */
    void copyLoopPixMap() {
        /*	This version of the inner loop maps source pixels
        to a destination form with different depth.  Because it is already
        unweildy, the loop is not unrolled as in the other versions.
        Preload, skew and skewMask are all overlooked, since pickSourcePixels
        delivers its destination word already properly aligned.
        Note that pickSourcePixels could be copied in-line at the top of
        the horizontal loop, and some of its inits moved out of the loop. */
        /*	The loop has been rewritten to use only one pickSourcePixels call.
        The idea is that the call itself could be inlined. If we decide not
        to inline pickSourcePixels we could optimize the loop instead. */
        int mergeWord;
        int i;
        int destPixMask;
        int nPix;
        int endBits;
        int nSourceIncs;
        int halftoneWord;
        int sourcePixMask;
        int skewWord;
        int words;
        int mapperFlags;
        int destWord;
        int dstShiftInc;
        int startBits;
        int dstShift;
        int srcShiftInc;
        int dstShiftLeft;
        int srcShift;
        int scrStartBits;
        int destIndexLocal;

	destIndexLocal = destIndex; // destIndexLocal := destIndex.

	// "Additional inits peculiar to unequal source and dest pix size..."
	source.pixPerWord = 32 / source.depth; // sourcePPW := 32 // sourceDepth.
        sourcePixMask = maskTable[source.depth]; //  sourcePixMask := maskTable at: sourceDepth.
        destPixMask = maskTable[dest.depth]; // destPixMask := maskTable at: destDepth.
        mapperFlags = cmFlags & (~ColorMapNewStyle); // mapperFlags := cmFlags bitAnd: ColorMapNewStyle bitInvert32.
        sourceIndex = (sy * source.pitch) + ((sx / source.pixPerWord) *4); // sourceIndex := sourceBits + (sy * sourcePitch) + (sx // sourcePPW * 4).
                // we do not use sourceBits here, because we access an array, not a memory address

        scrStartBits = source.pixPerWord - (sx & (source.pixPerWord - 1)); // scrStartBits := sourcePPW - (sx bitAnd: sourcePPW - 1).
        nSourceIncs = (bbW < scrStartBits) ? 0  // bbW < scrStartBits ifTrue: [nSourceIncs := 0]
                        : ((bbW - scrStartBits) / source.pixPerWord) + 1; // ifFalse: [nSourceIncs := bbW - scrStartBits // sourcePPW + 1].
        sourceDelta = source.pitch - (nSourceIncs *4); // sourceDelta := sourcePitch - (nSourceIncs * 4).

        // "Note following two items were already calculated in destmask setup!"
        startBits = dest.pixPerWord - (dx & (dest.pixPerWord - 1)); // startBits := destPPW - (dx bitAnd: destPPW - 1).
        endBits = (((dx + bbW) - 1) & (dest.pixPerWord - 1)) + 1; // endBits := (dx + bbW - 1 bitAnd: destPPW - 1) + 1.
        if (bbW < startBits) { // bbW < startBits
            startBits = bbW; // ifTrue: [startBits := bbW].
        }

        //  "Precomputed shifts for pickSourcePixels"
        srcShift = (sx & (source.pixPerWord - 1)) * source.depth; // srcShift := (sx bitAnd: sourcePPW - 1) * sourceDepth.
        dstShift = (dx & (dest.pixPerWord - 1)) * dest.depth; // dstShift := (dx bitAnd: destPPW - 1) * destDepth.
        srcShiftInc = source.depth; // srcShiftInc := sourceDepth.
        dstShiftInc = dest.depth; // dstShiftInc := destDepth.
        dstShiftLeft = 0; // dstShiftLeft := 0.
        if (source.msb) { // sourceMSB ifTrue: [
            srcShift = (32 - source.depth) - srcShift; // srcShift := 32 - sourceDepth - srcShift.
            srcShiftInc = 0 - srcShiftInc; // srcShiftInc := 0 - srcShiftInc].
        }
        if (dest.msb) { // destMSB ifTrue: [
            dstShift = (32 - dest.depth) - dstShift; // dstShift := 32 - destDepth - dstShift.
            dstShiftInc = 0 - dstShiftInc; // dstShiftInc := 0 - dstShiftInc.
            dstShiftLeft = 32 - dest.depth; // dstShiftLeft := 32 - destDepth].
        }

        for (i = 1; i <= bbH; i += 1) { // 1 to: bbH do: [:i |
            // "here is the vertical loop"
            // "*** is it possible at all that noHalftone == false? ***"
            halftoneWord = (noHalftone) ? AllOnes // noHalftone ifTrue: [halftoneWord := AllOnes]
                    : halftoneAt((dy + i) - 1); // ifFalse: [halftoneWord := self halftoneAt: dy + i - 1].

            // "setup first load"
            srcBitShift = srcShift; // srcBitShift := srcShift.
            dstBitShift = dstShift; // dstBitShift := dstShift.
            destMask = mask1; // destMask := mask1.
            nPix = startBits; // nPix := startBits.

            // "Here is the horizontal loop..."
            words = nWords; // words := nWords.
            do { // ["pick up the word"

                // skewWord := self pickSourcePixels: nPix flags: mapperFlags srcMask: sourcePixMask destMask: destPixMask srcShiftInc: srcShiftInc dstShiftInc: dstShiftInc.
                skewWord = pickSourcePixelsflagssrcMaskdestMasksrcShiftIncdstShiftInc(nPix, mapperFlags, sourcePixMask, destPixMask, srcShiftInc, dstShiftInc);

                /* align next word to leftmost pixel */
                dstBitShift = dstShiftLeft; // dstBitShift := dstShiftLeft.
                if (destMask == AllOnes) { //  destMask = AllOnes // ifTrue: ["avoid read-modify-write"
                    mergeWord = mergeFnwith.mergeFnwith(skewWord & halftoneWord, dstLongAt(destIndexLocal)); // mergeWord := self mergeFn: (skewWord bitAnd: halftoneWord) with: (self dstLongAt: destIndexLocal).
                    dstLongAtput(destIndexLocal, destMask & mergeWord); // self dstLongAt: destIndexLocal put: (destMask bitAnd: mergeWord)]
                } else { // ifFalse: ["General version using dest masking"
                    destWord = dstLongAt(destIndexLocal); // destWord := self dstLongAt: destIndexLocal.
                    mergeWord = mergeFnwith.mergeFnwith(skewWord & halftoneWord, destWord & destMask); // mergeWord := self mergeFn: (skewWord bitAnd: halftoneWord) with: (destWord bitAnd: destMask).
                    destWord = (destMask & mergeWord) | (destWord & (~destMask)); // destWord := (destMask bitAnd: mergeWord) bitOr: (destWord bitAnd: destMask bitInvert32).
                    dstLongAtput(destIndexLocal, destWord); // self dstLongAt: destIndexLocal put: destWord].
                }
                destIndexLocal += 4; // destIndexLocal := destIndexLocal + 4.
                if (words == 2) { // words = 2 // ifTrue: ["e.g., is the next word the last word?"
                    // "set mask for last word in this row"
                    destMask = mask2; // destMask := mask2.
                    nPix = endBits; // nPix := endBits]
                } else { // ifFalse: ["use fullword mask for inner loop"
                    destMask = AllOnes; // destMask := AllOnes.
                    nPix = dest.pixPerWord; // nPix := destPPW].
                }
            } while (!((words -= 1) == 0)); // (words := words - 1) = 0] whileFalse.
            // "--- end of inner loop ---"

            sourceIndex += sourceDelta; // sourceIndex := sourceIndex + sourceDelta.
            destIndexLocal += destDelta; // destIndexLocal := destIndexLocal + destDelta
        } // ]
    }

    /*
     pickSourcePixels: nPixels flags: mapperFlags srcMask: srcMask destMask: dstMask srcShiftInc: srcShiftInc dstShiftInc: dstShiftInc
	"Pick nPix pixels starting at srcBitIndex from the source, map by the
	color map, and justify them according to dstBitIndex in the resulting destWord."
	| sourceWord destWord sourcePix destPix srcShift dstShift nPix |
	self inline: true. "oh please"
	sourceWord := self srcLongAt: sourceIndex.
	destWord := 0.
	srcShift := srcBitShift. "Hint: Keep in register"
	dstShift := dstBitShift. "Hint: Keep in register"
	nPix := nPixels. "always > 0 so we can use do { } while(--nPix);"

	(mapperFlags = (ColorMapPresent bitOr: ColorMapIndexedPart)) ifTrue:[
		"a little optimization for (pretty crucial) blits using indexed lookups only"
		[	"grab, colormap and mix in pixel"
			sourcePix := sourceWord >> srcShift bitAnd: srcMask.
			destPix := self tableLookup: cmLookupTable at: (sourcePix bitAnd: cmMask).
			destWord := destWord bitOr: (destPix bitAnd: dstMask) << dstShift.
			"adjust dest pix index"
			dstShift := dstShift + dstShiftInc.
			"adjust source pix index"
			((srcShift := srcShift + srcShiftInc) bitAnd: 16rFFFFFFE0) = 0 ifFalse:[
				sourceMSB ifTrue:[srcShift := srcShift + 32] ifFalse:[srcShift := srcShift - 32].
				sourceWord := self srcLongAt: (sourceIndex := sourceIndex + 4)].
		(nPix := nPix - 1) = 0] whileFalse.
	] ifFalse:[
		[	"grab, colormap and mix in pixel"
			sourcePix := sourceWord >> srcShift bitAnd: srcMask.
			destPix := self mapPixel: sourcePix flags: mapperFlags.
			destWord := destWord bitOr: (destPix bitAnd: dstMask) << dstShift.
			"adjust dest pix index"
			dstShift := dstShift + dstShiftInc.
			"adjust source pix index"
			((srcShift := srcShift + srcShiftInc) bitAnd: 16rFFFFFFE0) = 0 ifFalse:[
				sourceMSB ifTrue:[srcShift := srcShift + 32] ifFalse:[srcShift := srcShift - 32].
				sourceWord := self srcLongAt: (sourceIndex := sourceIndex + 4)].
		(nPix := nPix - 1) = 0] whileFalse.
	].
	srcBitShift := srcShift. "Store back"
	^destWord
     */

    int pickSourcePixelsflagssrcMaskdestMasksrcShiftIncdstShiftInc(int nPixels, int mapperFlags, int srcMask, int dstMask, int srcShiftInc, int dstShiftInc) {
        /*	Pick nPix pixels starting at srcBitIndex from the source, map by the
        color map, and justify them according to dstBitIndex in the resulting destWord. */
        int sourcePix;
        int nPix;
        int sourceWord;
        int destPix;
        int destWord;
        int dstShift;
        int srcShift;

        sourceWord = srcLongAt(sourceIndex); // sourceWord := self srcLongAt: sourceIndex.
        destWord = 0; // destWord := 0.

        //These two vars to get into registers -- needed in Java??
        srcShift = srcBitShift; // srcShift := srcBitShift. "Hint: Keep in register"
        dstShift = dstBitShift; // dstShift := dstBitShift. "Hint: Keep in register"

        nPix = nPixels; // nPix := nPixels. "always > 0 so we can use do { } while(--nPix);"

        if (mapperFlags == (ColorMapPresent | ColorMapIndexedPart)) { // (mapperFlags = (ColorMapPresent bitOr: ColorMapIndexedPart)) ifTrue:[
            // "a little optimization for (pretty crucial) blits using indexed lookups only"
            do { // [	"grab, colormap and mix in pixel"
                sourcePix = (sourceWord >>> srcShift) & srcMask; // sourcePix := sourceWord >> srcShift bitAnd: srcMask.
                destPix = cmLookupTable[sourcePix & cmMask]; // destPix := self tableLookup: cmLookupTable at: (sourcePix bitAnd: cmMask).
                destWord = destWord | ((destPix & dstMask) << dstShift); // destWord := destWord bitOr: (destPix bitAnd: dstMask) << dstShift.

                // "adjust dest pix index"
                dstShift += dstShiftInc; // dstShift := dstShift + dstShiftInc.

                // "adjust source pix index"
                if (!(((srcShift += srcShiftInc) & 0xFFFFFFE0) == 0)) { // ((srcShift := srcShift + srcShiftInc) bitAnd: 16rFFFFFFE0) = 0 ifFalse:[
                    if (source.msb) { // sourceMSB ifTrue:[srcShift := srcShift + 32] ifFalse:[srcShift := srcShift - 32].
                        srcShift += 32;
                    } else {
                        srcShift -= 32;
                    }
                    sourceWord = srcLongAt(sourceIndex += 4); // sourceWord := self srcLongAt: (sourceIndex := sourceIndex + 4)].
                }
            } while (!((nPix -= 1) == 0)); // (nPix := nPix - 1) = 0] whileFalse.
        } /*clean double-neg here*/ else { //  ] ifFalse:[
            do { // [	"grab, colormap and mix in pixel"
                sourcePix = (sourceWord >>> srcShift) & srcMask; // sourcePix := sourceWord >> srcShift bitAnd: srcMask.
                destPix = mapPixelflags(sourcePix, mapperFlags); // destPix := self mapPixel: sourcePix flags: mapperFlags.
                destWord = destWord | ((destPix & dstMask) << dstShift); // destWord := destWord bitOr: (destPix bitAnd: dstMask) << dstShift.

                // "adjust dest pix index"
                dstShift += dstShiftInc; // dstShift := dstShift + dstShiftInc.

                // "adjust source pix index"
                if (!(((srcShift += srcShiftInc) & 0xFFFFFFE0) == 0)) { // ((srcShift := srcShift + srcShiftInc) bitAnd: 16rFFFFFFE0) = 0 ifFalse:[
                    if (source.msb) { // sourceMSB ifTrue:[srcShift := srcShift + 32] ifFalse:[srcShift := srcShift - 32].
                        srcShift += 32;
                    } else {
                        srcShift -= 32;
                    }
                    sourceWord = srcLongAt(sourceIndex += 4); // sourceWord := self srcLongAt: (sourceIndex := sourceIndex + 4)].
                }
            } while (!((nPix -= 1) == 0)); // (nPix := nPix - 1) = 0] whileFalse.
        } /*clean double-neg here*/ // ].

        srcBitShift = srcShift; // srcBitShift := srcShift. "Store back"
        return destWord; // ^destWord
    }

    /*
     mapPixel: sourcePixel flags: mapperFlags
	"Color map the given source pixel."
	| pv |
	self inline: true.
	pv := sourcePixel.
	(mapperFlags bitAnd: ColorMapPresent) ~= 0 ifTrue:[
		(mapperFlags bitAnd: ColorMapFixedPart) ~= 0 ifTrue:[
			pv := self rgbMapPixel: sourcePixel flags: mapperFlags.
			"avoid introducing transparency by color reduction"
			(pv = 0 and:[sourcePixel ~= 0]) ifTrue:[pv := 1]].
		(mapperFlags bitAnd: ColorMapIndexedPart) ~= 0
			ifTrue:[pv := cmLookupTable at: (pv bitAnd: cmMask)].
	].
	^pv
     */
    int mapPixelflags(int sourcePixel, int mapperFlags) {
        int pv;
        pv = sourcePixel; // pv := sourcePixel.
        if ((mapperFlags & ColorMapPresent) != 0) { // (mapperFlags bitAnd: ColorMapPresent) ~= 0 ifTrue:[
            if ((mapperFlags & ColorMapFixedPart) != 0) { // (mapperFlags bitAnd: ColorMapFixedPart) ~= 0 ifTrue:[
                pv = rgbMapPixelflags(sourcePixel, mapperFlags); // pv := self rgbMapPixel: sourcePixel flags: mapperFlags.

                // "avoid introducing transparency by color reduction"
                if ((pv == 0) && (sourcePixel != 0)) { // (pv = 0 and:[sourcePixel ~= 0]) ifTrue:[pv := 1]].
                    pv = 1;
                }
            }
            if ((mapperFlags & ColorMapIndexedPart) != 0) { // (mapperFlags bitAnd: ColorMapIndexedPart) ~= 0
                pv = cmLookupTable[pv & cmMask]; // ifTrue:[pv := cmLookupTable at: (pv bitAnd: cmMask)].
            }
        } // ].
        return pv; // ^pv
    }

    /*
    rgbMapPixel: sourcePixel flags: mapperFlags
	"Perform the RGBA conversion for the given source pixel"
	| val |
	self inline: true.
	val :=                  ((sourcePixel bitAnd: (cmMaskTable at: 0)) bitShift: (cmShiftTable at: 0)).
	val := val bitOr:       ((sourcePixel bitAnd: (cmMaskTable at: 1)) bitShift: (cmShiftTable at: 1)).
	val := val bitOr:       ((sourcePixel bitAnd: (cmMaskTable at: 2)) bitShift: (cmShiftTable at: 2)).
		  ^val bitOr:   ((sourcePixel bitAnd: (cmMaskTable at: 3)) bitShift: (cmShiftTable at: 3)).
     */
    int rgbMapPixelflags(int sourcePixel, int mapperFlags) {
        int val = Arithmetics.bitShift((sourcePixel & cmMaskTable[0]), cmShiftTable[0]);
        val = val | Arithmetics.bitShift((sourcePixel & cmMaskTable[1]), cmShiftTable[1]);
        val = val | Arithmetics.bitShift((sourcePixel & cmMaskTable[2]), cmShiftTable[2]);
        return val | Arithmetics.bitShift((sourcePixel & cmMaskTable[3]), cmShiftTable[3]);
    }

    /*
    loadColorMapShiftOrMaskFrom: mapOop
	self returnTypeC:'void *'.
	mapOop = interpreterProxy nilObject ifTrue:[^nil].
	(interpreterProxy isIntegerObject: mapOop)
		ifTrue:[interpreterProxy primitiveFail. ^nil].
	((interpreterProxy isWords: mapOop)
		and:[(interpreterProxy slotSizeOf: mapOop) = 4])
			ifFalse:[interpreterProxy primitiveFail. ^nil].
	^interpreterProxy firstIndexableField: mapOop
     */
    private int[] loadColorMapShiftOrMaskFrom(SqueakObject mapOop){
        if(mapOop == SpecialObjects.nilObj)
		 {
			return null; // ifTrue:[^nil].
		}
        if(SmallInteger.isSmallInt(mapOop)) // (interpreterProxy isIntegerObject: mapOop) // ifTrue:[
        {
            success = false; // interpreterProxy primitiveFail.
            return null; // ^nil].
        }
        if( !(mapOop.isWords() && mapOop.slotSizeOf() == 4)) // ((interpreterProxy isWords: mapOop) and:[(interpreterProxy slotSizeOf: mapOop) = 4]) // ifFalse:[
        {
            success = false; // interpreterProxy primitiveFail.
            return null; // ^nil].
        }

        return firstIndexableField(mapOop);
    }

    /*
    firstIndexableField: oop
	self returnTypeC:'void *'.
	^CArrayAccessor on: oop
     */
    int[] firstIndexableField(SqueakObject squeakObject) {
        return (int[]) squeakObject.bits;
    }

    /*
    srcLongAt: idx
	^interpreterProxy longAt: idx

    longAt: byteAddress
	"Note: Adjusted for Smalltalk's 1-based array indexing."

	^memory at: (byteAddress // 4) + 1
     */
    int srcLongAt(int index) {
        if( index == -4 ) {
            return source.bits.length;
        }

        if( index/4 >= source.bits.length){
            index = (index/4)%source.bits.length;
        }

        return source.bits[index/4]; // ^memory at: (byteAddress // 4) + 1
    }

    /*
    dstLongAt: idx
	^interpreterProxy longAt: idx

    longAt: byteAddress
	"Note: Adjusted for Smalltalk's 1-based array indexing."

	^memory at: (byteAddress // 4) + 1
     */
    int dstLongAt(int index) {
        return dest.bits[index/4]; // ^memory at: (byteAddress // 4) + 1
    }

    /*
    dstLongAt: idx put: value
	^interpreterProxy longAt: idx put: value

    longAt: byteAddress put: a32BitValue
	"Note: Adjusted for Smalltalk's 1-based array indexing."

	^memory at: (byteAddress // 4) + 1 put: a32BitValue
     */
    void dstLongAtput(int index, int intToPut) {
        dest.bits[index/4] = intToPut; // ^memory at: (byteAddress // 4) + 1 put: a32BitValue
    }

    /*
    halftoneAt: idx
	"Return a value from the halftone pattern."
	^interpreterProxy longAt: halftoneBase + (idx \\ halftoneHeight * 4)

    longAt: byteAddress
	"Note: Adjusted for Smalltalk's 1-based array indexing."

	^memory at: (byteAddress // 4) + 1
     */
    int halftoneAt(int index) {
        index = index % (halftoneHeight*4); // ^interpreterProxy longAt: halftoneBase + (idx \\ halftoneHeight * 4)
        return halftoneBits[index/4]; // ^memory at: (byteAddress // 4) + 1
    }

    /*
    failed

	^successFlag not
     */
    boolean failed(){
        return !success; // ^successFlag not
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // LEFT TO IMPLEMENT
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------

    void warpBits(){
        System.out.println("This should never happen!");
        return;
    }

    boolean tryCopyingBitsQuickly(){
        return false;
    }
}

