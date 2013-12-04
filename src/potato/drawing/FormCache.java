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

package potato.drawing;

import potato.objects.SqueakObject;
import potato.objects.SmallInteger;
import potato.objects.SpecialObjects;
import potato.vm.VM;

/**
 * @author Dan Ingalls
 *
 * @author Frank Feinbube
 * @author Robert Wierschke
 */
public class FormCache {

    // Form layout:
    public final static int Form_bits = 0;
    public final static int Form_width = 1;
    public final static int Form_height = 2;
    public final static int Form_depth = 3;
    public SqueakObject squeakForm;
    public int[] bits;
    public int width;
    public int height;
    public int depth;
    public boolean msb;
    public int pixPerWord;
    public int pitch; // aka raster

    FormCache() {
    }

    public FormCache(SqueakObject obj, VM squeakVM) {
        this.loadFrom(obj, squeakVM);
    }
    
 /*
     loadBitBltSourceForm
	"Load the source form for BitBlt. Return false if anything is wrong, true otherwise."
	| sourceBitsSize |
	self inline: true.
	sourceBits := interpreterProxy fetchPointer: FormBitsIndex ofObject: sourceForm.
	sourceWidth := self fetchIntOrFloat: FormWidthIndex ofObject: sourceForm.
	sourceHeight := self fetchIntOrFloat: FormHeightIndex ofObject: sourceForm.
	(sourceWidth >= 0 and: [sourceHeight >= 0])
		ifFalse: [^ false].
	sourceDepth := interpreterProxy fetchInteger: FormDepthIndex ofObject: sourceForm.
	sourceMSB := sourceDepth > 0.
	sourceDepth < 0 ifTrue:[sourceDepth := 0 - sourceDepth].
	"Ignore an integer bits handle for Display in which case 
	the appropriate values will be obtained by calling ioLockSurfaceBits()."
	(interpreterProxy isIntegerObject: sourceBits) ifTrue:[
		"Query for actual surface dimensions"
		(self querySourceSurface: (interpreterProxy integerValueOf: sourceBits))
			ifFalse:[^false].
		sourcePPW := 32 // sourceDepth.
		sourceBits := sourcePitch := 0.
	] ifFalse:[
		sourcePPW := 32 // sourceDepth.
		sourcePitch := sourceWidth + (sourcePPW-1) // sourcePPW * 4.
		sourceBitsSize := interpreterProxy byteSizeOf: sourceBits.
		((interpreterProxy isWordsOrBytes: sourceBits)
			and: [sourceBitsSize = (sourcePitch * sourceHeight)])
			ifFalse: [^ false].
		"Skip header since external bits don't have one"
		sourceBits := self cCoerce: (interpreterProxy firstIndexableField: sourceBits) to:'int'.
	].
	^true
     */ 
    boolean loadFrom(Object aForm, VM squeakVM) {
        //We do not reload if this is the same form as before
        if (squeakForm == aForm) {
            return true;
        }
        squeakForm = null; //Marks this as failed until very end...

        if (SmallInteger.isSmallInt(aForm)) {
            return false;
        }
        
        // extract and check formpointers
        Object[] formPointers = ((SqueakObject) aForm).pointers;
        if (formPointers == null || formPointers.length < 4) {
            return false;
        }
        for (int i = 1; i < 4; i++) {
            if (!SmallInteger.isSmallInt(formPointers[i])) {
                return false;
            }
        }
        
        SqueakObject bitsObject = (SqueakObject)formPointers[0]; // sourceBits := interpreterProxy fetchPointer: FormBitsIndex ofObject: sourceForm.
        width = SmallInteger.intFromSmall((Integer) formPointers[1]); // sourceWidth := self fetchIntOrFloat: FormWidthIndex ofObject: sourceForm.
        height = SmallInteger.intFromSmall((Integer) formPointers[2]); // sourceHeight := self fetchIntOrFloat: FormHeightIndex ofObject: sourceForm.
        if ((width < 0) || (height < 0)) { // (sourceWidth >= 0 and: [sourceHeight >= 0])
            return false; // ifFalse: [^ false].
        }
        depth = SmallInteger.intFromSmall((Integer) formPointers[3]); // sourceDepth := interpreterProxy fetchInteger: FormDepthIndex ofObject: sourceForm.
        
        msb = depth > 0; // sourceMSB := sourceDepth > 0.
        if (depth < 0) { // sourceDepth < 0 ifTrue:[sourceDepth := 0 - sourceDepth].
            depth = 0 - depth;
        }
        
        if(bitsObject == SpecialObjects.nilObj)
            return false;
        
        // "Ignore an integer bits handle for Display in which case 
        // the appropriate values will be obtained by calling ioLockSurfaceBits()."
        // (interpreterProxy isIntegerObject: sourceBits) ifTrue:[
        if ( SmallInteger.isSmallInt(bitsObject)) {
            // "Query for actual surface dimensions"
            
            // TODO (self querySourceSurface: (interpreterProxy integerValueOf: sourceBits))
            //           ifFalse:[^false].
            
            System.out.println("This should not happen! (FormCache.loadFrom)");
            
            pixPerWord = 32 / depth; // sourcePPW := 32 // sourceDepth.
            pitch = 0; // sourceBits := sourcePitch := 0.
            bitsObject = null;
        }
        else // ] ifFalse:[
        {
            pixPerWord = 32 / depth; // sourcePPW := 32 // sourceDepth.
            pitch = ((width + (pixPerWord - 1)) / pixPerWord)*4; // sourcePitch := sourceWidth + (sourcePPW-1) // sourcePPW * 4.
            int bitsSize = bitsObject.byteSizeOf(); // sourceBitsSize := interpreterProxy byteSizeOf: sourceBits.
            if (bitsObject.isWordsOrBytes() && bitsSize != (pitch * height)) { // ((interpreterProxy isWordsOrBytes: sourceBits) and: [sourceBitsSize = (sourcePitch * sourceHeight)])
                return false; // ifFalse: [^ false].
            }
            // "Skip header since external bits don't have one"
             bits = toIntArray(((SqueakObject) bitsObject).bits); // sourceBits := self cCoerce: (interpreterProxy firstIndexableField: sourceBits) to:'int'.

        } // ].

        squeakForm = (SqueakObject) aForm; //Only now is it marked as OK
        return true; // ^true
    }   
    
    private int[] toIntArray(Object obj){
        return (int[])obj;
    }
}
