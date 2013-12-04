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

package potato.image;

import java.io.IOException;

/**
 * @author Daniel Ingalls
 *  
 * @author Frank Feinbube
 * @author Robert Wierschke
 */
public class SqueakObjectHeader {

    
    public final static int BaseHeaderSize = 4;
    
    public final static int TypeMask = 3;
    public final static int AllButTypeMask = 0xFFFFFFFF - TypeMask;
    
    public final static int SizeMask = 0xFC;
    
    // Squeak Headers
    public final static int HeaderTypeSizeAndClass = 0; //3-word header
    public final static int HeaderTypeClass = 1;        //2-word header
    public final static int HeaderTypeFree = 2;         //free block
    public final static int HeaderTypeShort = 3;        //1-word header

    public int headerType;
    public int objectSizeInWords;
    public int classIndex;
    public short hash;        //12-bit Squeak hash

    public short format;      // 4-bit Squeak format


    public SqueakObjectHeader(SqueakImageInputStream imageInputStream) throws IOException {
        int currentHeaderWord = imageInputStream.readInt();

        headerType = getHeaderType(currentHeaderWord);

        // Note the missing break statements!
        //  Hence all catch blocks beginning from the matching block will
        //  be executed.
        switch (headerType) {
            case HeaderTypeSizeAndClass:
                readSizeHeader(currentHeaderWord);
                currentHeaderWord = imageInputStream.readInt();
            case HeaderTypeClass:
                readClassHeader(currentHeaderWord);
                currentHeaderWord = imageInputStream.readInt();
            case HeaderTypeShort:
                readBaseHeader(currentHeaderWord);
                break;
            default:
                throw new RuntimeException("unknown object header");
        }
    }

    // TODO should we test if this is a know header type?
    private int getHeaderType(int currentHeaderWord) {
        // this is the same for all header types
        int result = currentHeaderWord & TypeMask;
        return result;
    }

    private void readBaseHeader(int currentHeaderWord) {
        int baseHeaderWord = currentHeaderWord;
        // read hash
        hash = (short) ((baseHeaderWord >> 17) & 4095);

        if (headerType == HeaderTypeShort) {
            classIndex = (baseHeaderWord >> 12) & 31;
        }

        // read format        
        format = (short) ((baseHeaderWord >> 8) & 15);

        // read the object size if not get from size header
        if (headerType == HeaderTypeShort || headerType == HeaderTypeClass) {
            objectSizeInWords = (baseHeaderWord >> 2) & 63;
            objectSizeInWords--;
        }
    }

    private void readClassHeader(int currentHeaderWord) {
        int classHeaderWord = currentHeaderWord;

        // remove last to bits (header type)
        if (headerType == HeaderTypeSizeAndClass) {
            classIndex = classHeaderWord - HeaderTypeSizeAndClass;
        } else {
            classIndex = classHeaderWord - HeaderTypeClass;
        }
    }

    // we only need the size from this header
    private void readSizeHeader(int currentHeaderWord) {
        int sizeHeaderWord = currentHeaderWord;
        objectSizeInWords = sizeHeaderWord >> 2; // remove the header type info

        objectSizeInWords--;    // substract the base header

    }

    public int getHeaderSize() {
        if (headerType == HeaderTypeShort) {
            return 4;
        } else if (headerType == HeaderTypeClass) {
            return 8;
        } else if (headerType == HeaderTypeSizeAndClass) {
            return 12;
        } else {
            throw new RuntimeException("unknown header type");
        }
    }
    
    /*
    lengthOf: oop
	"Return the number of indexable bytes or words in the given object. Assume the argument is not an integer. For a CompiledMethod, the size of the method header (in bytes) should be subtracted from the result."

	| header |
	self inline: true.
	header := self baseHeader: oop.
	^ self lengthOf: oop baseHeader: header format: ((header >> 8) bitAnd: 16rF)
     */ 
    public int lengthOf(){
        return lengthOfbaseHeaderformat(headerType, headerType>>8 & 0xF);
    }
    
    /*
    lengthOf: oop baseHeader: hdr format: fmt
	"Return the number of indexable bytes or words in the given object. Assume the given oop is not an integer. For a CompiledMethod, the size of the method header (in bytes) should be subtracted from the result of this method."

	| sz |
	self inline: true.
	(hdr bitAnd: TypeMask) = HeaderTypeSizeAndClass
		ifTrue: [ sz := (self sizeHeader: oop) bitAnd: AllButTypeMask ]
		ifFalse: [ sz := hdr bitAnd: SizeMask ].

	fmt < 8
		ifTrue: [ ^ (sz - BaseHeaderSize) >> 2 ]  "words"
		ifFalse: [ ^ (sz - BaseHeaderSize) - (fmt bitAnd: 3) ]  "bytes"
     */ 
    private int lengthOfbaseHeaderformat(int hdr, int fmt){
        int sz;
        if((hdr & TypeMask) == HeaderTypeSizeAndClass){
            sz = getHeaderSize() & AllButTypeMask;
        } else {
            sz = hdr & SizeMask;
        }
        
        if(fmt<8){
            return (sz-BaseHeaderSize) >> 2;
        } else {
            return (sz-BaseHeaderSize) - (fmt & 3);
        }
    }
}
