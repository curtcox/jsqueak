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

package org.squeak.potato.objects;

import java.io.Serializable;
import java.math.BigInteger;
import java.util.*;
import java.util.logging.Logger;

import org.squeak.potato.*;
import org.squeak.potato.image.SqueakImage;
import org.squeak.potato.image.SqueakObjectHeader;

/**
 * @author Daniel Ingalls
 *
 * @author Frank Feinbube
 * @author Robert Wierschke
 *
 * Squeak objects are modelled by Java objects with separate binary and pointer data.
 * Later this could be optimized for objects that have only one or the other, but for
 * now it is simple, and handles the inhomogeneous case of CompiledMethods nicely.
 *
 * Weak fields are not currently supported.  The plan for doing this would be
 * to make those objects a subclass, and put pointers in a WeakField.  We would
 * need to replace all patterns of obj.pointers with an access function.
 * Then we would associate a finalization routine with those pointers.
 */
public class SqueakObject extends AbstractSqueakObject implements Serializable
{//Later make variants for common formats

	private transient Logger logger=Logger.getLogger(getClass().getName());
	private static final long serialVersionUID = 1L;

	public short hash;        //12-bit Squeak hash
    public short format;      // 4-bit Squeak format
    public int size = 0;
    public int baseAddr = 0;
    public Object sqClass;  //squeak class
    public Object bits;       //indexable binary data (bytes or ints)
    private boolean fixByteOrder;
    private SqueakObjectHeader header;

    /** Needed by XMLSerializer
     *
     */
    public SqueakObject(){

    }

    public boolean isByteArray(){
    	return (""+sqClass).equals( "Class ByteArray" );
    }


    public SqueakObject(SqueakObjectHeader header, int objectOffset, int[] content, boolean fixByteOrder) {
        this.format = header.format;
        this.hash = header.hash;
        // the offset of the object pointing to the object's base header
        this.baseAddr = objectOffset + header.getHeaderSize() - 4;
        this.size = header.getHeaderSize() + header.objectSizeInWords * 4;
        this.sqClass = header.classIndex;
        this.bits = content;
        this.header = header;
        this.fixByteOrder = fixByteOrder;
    }

    public Object[] pointers; //pointer fields; fixed as well as indexable
    // for Large****tiveInteger instances, pointers[0] holds the BigInteger rep

    protected SqueakObject(SqueakImage img) {
        //Creation of stub object (no pointers or bits)
        hash = img.registerObject(this);
    }

    public SqueakObject(SqueakImage img, SqueakObject cls, int indexableSize, SqueakObject filler) {
        //Creation of objects from Squeak
        this(img);
        sqClass = cls;
        int instSpec = SmallInteger.intFromSmall(cls.fetchInteger(Constants.Class_format));
        int instSize = ((instSpec >> 1) & 0x3F) + ((instSpec >> 10) & 0xC0) - 1; //0-255
        format = ((short) ((instSpec >> 7) & 0xF)); //This is the 0-15 code

        if (format < 8) {
            if (format !=  SpecialObjectConstants.splOb_ClassString /* 6*/) {
                pointers = new Object[instSize + indexableSize];
                Arrays.fill(pointers, filler);

            } else if (indexableSize >= 0) {
                bits = new int[indexableSize];
            }
        } else {
            bits = new byte[indexableSize];
        } //Methods require further init of pointers
    }

//      Definition of Squeak's format code...
//
//      Pointers only...
//        0      no fields
//        1      fixed fields only (all containing pointers)
//        2      indexable fields only (all containing pointers)
//        3      both fixed and indexable fields (all containing pointers)
//        4      both fixed and indexable weak fields (all containing pointers).
//        5      unused
//      Bits only...
//        6      indexable word fields only (no pointers)
//        7      unused
//        8-11   indexable byte fields only (no pointers) (low 2 bits are low 2 bits of size)
//      Pointer and bits (CompiledMethods only)...
//       12-15   compiled methods:
//               # of literal oops specified in method header,
//               followed by indexable bytes (same interpretation of low 2 bits as above)
    //General access
    public SqueakObject getSqClass() {
        return (SqueakObject) sqClass;
    }

    public Object fetchPointer(int zeroBasedIndex) {
        // FIXME This causes an ArrayIndexOutOfBoundsException when loading a
        // modern Squeak image. Maybe this indicates that restoring objects
        // from image does not work.
        return pointers[zeroBasedIndex];
    }

    public SqueakObject fetchPointerNI(int zeroBasedIndex) {
        //Returns only SqueakObjects, not Integers
        return (SqueakObject) pointers[zeroBasedIndex];
    }

    public Integer fetchInteger(int zeroBasedIndex) {
        //Returns only SmallIntegers
        return (Integer) pointers[zeroBasedIndex];
    }

    public void setPointer(int zeroBasedIndex, Object aPointer) {
        pointers[zeroBasedIndex] = aPointer;
    }

    public int pointersSize() {
        return pointers == null ? 0 : pointers.length;
    }

    public int bitsSize() {
        if (bits == null) {
            return 0;
        }
        if (bits instanceof byte[]) {
            return ((byte[]) bits).length;
        }
        if (bits instanceof Double) {
            return 2;
        }
        return ((int[]) bits).length;
    }

    public int instSize() {//same as class.classInstSize, but faster from format
        if (format > 4 || format == 2) {
            return 0;
        } //indexable fields only
        if (format < 2) {
            return pointers.length;
        } //indexable fields only
        return ((SqueakObject) sqClass).classInstSize();
    } //0-255

    public int classInstSize() {
        int instSpec = SmallInteger.intFromSmall(this.fetchInteger(Constants.Class_format));
        return ((instSpec >> 1) & 0x3F) + ((instSpec >> 10) & 0xC0) - 1;
    } //0-255

    public SqueakObject classGetName() {
        return this.fetchPointerNI(Constants.Class_name);
    }

    public SqueakObject cloneIn(SqueakImage img) {
        //Need to get new hash, OT entry...
        SqueakObject clone = new SqueakObject(img);
        clone.copyStateFrom(this);
        return clone;
    }

    private void copyStateFrom(SqueakObject other) {
        sqClass = other.sqClass;
        format = other.format;
        pointers = other.pointers.clone();
        Object otherBits = other.bits;
        if (otherBits == null) {
            return;
        }
        if (otherBits instanceof byte[]) {
            bits = ((byte[]) other.bits).clone();
        } else if (otherBits instanceof int[]) {
            bits = ((int[]) other.bits).clone();
        }
    }

    public double getFloatBits() { // isn't this slow?'
        return ((Double) bits).doubleValue();
    }

    public void setFloatBits(double value) {
        bits = new Double(value);
    }


    //CompiledMethods
    public int methodHeader() {
        return ((Integer) fetchPointer(0)).intValue();
    }

    public int methodNumLits() {
        return (methodHeader() >> 9) & 0xFF;
    }

    public int methodNumArgs() {
        return (methodHeader() >> 24) & 0xF;
    }

    public int methodPrimitiveIndex() {
        int primBits = (methodHeader()) & 0x300001FF;
        if (primBits > 0x1FF) {
            return (primBits & 0x1FF) + (primBits >> 19);
        } else {
            return primBits;
        }
    }

    public SqueakObject methodClassForSuper() {//assn found in last literal
        SqueakObject assn = fetchPointerNI(methodNumLits());
        return assn.fetchPointerNI(Constants.Assn_value);
    }

    public boolean methodNeedsLargeFrame() {
        return (methodHeader() & 0x20000) > 0;
    }

    public void methodAddPointers(Object[] headerAndLits) {
        pointers = headerAndLits;
    }

    public int methodTempCount() {
        return (methodHeader() >> 18) & 63;
    }

    public Object methodGetLiteral(int zeroBasedIndex) {
        return fetchPointer(1 + zeroBasedIndex);
    }	// step over header

    public SqueakObject methodGetSelector(int zeroBasedIndex) {
        return fetchPointerNI(1 + zeroBasedIndex);
    }	// step over header

    public void methodSetLiteral(int zeroBasedIndex, Object rawValue) {
        setPointer(1 + zeroBasedIndex, rawValue);
    }	// step over header

    //Methods below here are only used for reading the Squeak image format
    public void install(Map<Integer, SqueakObject> oopMap, Integer[] ccArray, SqueakObject floatClass) {
        //Install this object by decoding format, and rectifying pointers
        int ccInt = ((Integer) sqClass).intValue();
        if ((ccInt > 0) && (ccInt < 32)) {
            sqClass = oopMap.get(ccArray[ccInt - 1]);
        } else {
            sqClass = oopMap.get(sqClass);
        }
        int nWords = ((int[]) bits).length;
        if (format < 5) {
            //Formats 0...4 -- Pointer fields
            pointers = decodePointers(nWords, ((int[]) bits), oopMap);
            bits = null;
        } else {
            if (format >= 12) {
                //Formats 12-15 -- CompiledMethods both pointers and bits
                int methodHeader = ((int[]) bits)[0];
                int numLits = ((methodHeader >> 10) & 255);
                pointers = decodePointers(numLits+1, ((int[]) bits), oopMap); //header+lits
                bits = decodeBytes(nWords - (numLits + 1), ((int[]) bits), numLits + 1, format & 3);
            } else if (format >= 8) {
                //Formats 8..11 -- ByteArrays (and Strings)
                bits = decodeBytes(nWords, ((int[]) bits), 0, format & 3);
            } //Format 6 word objects are already OK (except Floats...)
            else if (sqClass == floatClass) {
                //Floats need two ints to be converted to double
                long longBits = (((long) ((int[]) bits)[0]) << 32) | (((long) ((int[]) bits)[0]) & 0xFFFFFFFF);
//System.err.println();
//System.err.println(((int[])bits)[0] + " " + ((int[])bits)[1] + " -> " + longBits);
                bits = new Double(Double.longBitsToDouble(longBits));
            }
//System.err.println((Double)bits + " " + Double.doubleToRawLongBits(((Double)bits).doubleValue()));
        }
    }

    private Object[] decodePointers(int nWords, int[] theBits, Map<Integer, SqueakObject> oopMap) {
        //Convert small ints and look up object pointers in oopMap
        Object[] ptrs = new Object[nWords];
        for (int i = 0; i < nWords; i++) {
            int oldOop = theBits[i];
            if ((oldOop & 1) == 1) {
                ptrs[i] = SmallInteger.smallFromInt(oldOop >> 1);
            } else {
                ptrs[i] = oopMap.get(new Integer(oldOop));
            }
        }
        return ptrs;
    }

    private byte[] decodeBytes(int nWords, int[] theBits, int wordOffset, int fmtLoBits) {
        byte[] newBits = null;

            int nBytes = (nWords * 4) - (format & 3);
            newBits = new byte[nBytes];

            int wordIx = wordOffset;
            int fourBytes = 0;
            for (int i = 0; i < nBytes; i++) {
                if ((i & 3) == 0) {
                    fourBytes = theBits[wordIx++];
                    if (fixByteOrder) {
						fourBytes = Integer.reverseBytes(fourBytes);
					}
                }

                int pickByte = (fourBytes >> (8 * (3 - (i & 3)))) & 255;
                if (pickByte >= 128) {
                    pickByte = pickByte - 256;
                }
                newBits[i] = (byte) pickByte;
            }
        return newBits;
    }

    public int oldOopAt(int zeroBasedOffset) {
        return ((int[]) bits)[zeroBasedOffset];
    }


        /*
    isWords: oop
	^oop class isPointers not and:[oop class isBytes not]
     */
    public boolean isWords() {
        return !isPointers() && !((SqueakObject)this.sqClass).isBytes(); // ^oop class isPointers not and:[oop class isBytes not]
    }

    /*
    isPointers
	^ self isBits not
     */
    public boolean isPointers() {
        return !isBits(); // ^ self isBits not
    }

    /*
    isBits
	^ self instSpec >= 6
     */
    boolean isBits(){
        return format >= 6; // ^ self instSpec >= 6
    }

    /*
    isBytes
	^ self instSpec >= 8
     */
    boolean isBytes(){
        return format >= 8; // ^ self instSpec >= 8
    }

    /*
    byteSizeOf: oop
	"Return the size of the receiver in bytes"
	^oop class isBytes
		ifTrue:[(self slotSizeOf: oop)]
		ifFalse:[(self slotSizeOf: oop) * 4]
     */
    public int byteSizeOf() {
        if( ((SqueakObject)sqClass).isBytes() ) { // ^oop class isBytes
            return slotSizeOf(); // ifTrue:[(self slotSizeOf: oop)]
        } else {
            return slotSizeOf() * 4; // ifFalse:[(self slotSizeOf: oop) * 4]
        }
    }

    /*
    isWordsOrBytes: oop
	^(self isBytes: oop) or:[self isWords: oop]
     */
    public boolean isWordsOrBytes(){
        return isBytes() || isWords(); // ^(self isBytes: oop) or:[self isWords: oop]
    }

    public int slotSizeOf() {
        int result = bitsSize();
        if( result == 0){
            result = fetchPointerNI(0).bitsSize();
        }
        return result;
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
        return header.lengthOf();
    }

    public String asString() {	// debugging only: if body consists of bytes, make a Java String from them
        if (bits != null && bits instanceof byte[]) {
            if (pointers != null) {
                return "a CompiledMethod";
            } else {
                // GG FIXME this returns unreadable stuff in some cases
                return new String((byte[]) bits);
            }
        } else {
            SqueakObject itsClass = this.getSqClass();
            if (itsClass.pointersSize() >= 9) {
                return "a " + itsClass.classGetName().asString();
            } else {
                return "Class " + this.classGetName().asString();
            }
        }
    }

    @Override
    public String toString() {
        return this.asString();
    }

    /**
     * FIXME: what is the right way to achieve this?
     */
    public void setByte( int zeroBasedIndex, byte value )
    {
        byte[] bytes = (byte[]) bits;

        bytes[ zeroBasedIndex ] = value;
    }

    /**
     * FIXME: what is the right way to achieve this?
     */
    public byte getByte( int zeroBasedIndex )
    {
        byte[] bytes = (byte[]) bits;

        return bytes[ zeroBasedIndex ];
    }

    /**
     * Check whether this object, which is supposed to be a Large****Integer,
     * already has a BigInteger representation. No security checks are performed.
     * This method is supposed to be called in correct contexts.
     *
     * @return true if this object already holds a BigInteger.
     */
    public boolean hasLarge() {
        return pointers != null && pointers[0] instanceof BigInteger;
    }

    /**
     * This method returns this object's BigInteger representation. No security
     * checks are performed to ensure this is a Large****Integer. This method
     * is simply expected to be called in appropriate situations.
     *
     * @return a BigInteger representing this object.
     */
    public BigInteger large() {
        return (BigInteger)pointers[0];
    }

    /**
     * Assign the passed BigInteger to this object's pointers array. No security
     * checks are done in this case: this method is simply not supposed to be
     * invoked in illegal situations. That is, it might well overwrite the
     * pointers array with something unexpected. (More detail: the above method
     * hasLarge() is supposed to be called before this one.)
     */
    public void assignLarge(BigInteger big) {
        pointers = new Object[] { big };
    }

    /**
     * Invalidate the large representation of this object by setting it to null.
     * No security checks are performed to ensure that this object represents a
     * Large****tiveInteger. This method is expected to be called in appropriate
     * situations.
     */
    public void invalidateLarge() {
        pointers[0] = null;
    }

	@Override
	public boolean isJavaProxy() {
		return false;
	}


}
