/*
This work is a derivative of JSqueak (http://research.sun.com/projects/JSqueak). 

Copyright (c) 2008  Daniel H. H. Ingalls, Sun Microsystems, Inc.  All rights reserved.
 
Portions copyright Frank Feinbube, Robert Wierschke, Michael Haupt.

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
package potato.objects;

import java.math.BigInteger;

import static potato.objects.SpecialObjectConstants.*;

/**
 * This is a tool class collecting various static methods and constants for
 * helping in the management of both LargePositiveInteger and LargeNegativeInteger
 * instances. Objects of both kinds are represented by instances of Java's
 * BigInteger class.
 * 
 * @author Michael Haupt
 */
public class LargeInteger {
    
    /**
     * This factory method returns a corresponding BigInteger to represent the
     * requested number.
     * 
     * @param lpi The Squeak object to be represented.
     * @return A BigInteger instance representing the passed Squeak object.
     */
    public static BigInteger fromLargePositiveInteger(SqueakObject lpi) {
        byte[] bytes = (byte[])lpi.bits;
        // Should the MSB of the to-be BigInteger creation array have a set
        // sign bit, another byte needs to be prepended to avoid misinterpretation
        // of the number as being negative.
        int ext = ((bytes[bytes.length - 1] & 0x80) != 0) ? 1 : 0;
        byte[] rev = new byte[bytes.length + ext];
        for(int i = 0; i < bytes.length; i++)
            rev[i + ext] = bytes[bytes.length - i - 1];
        return new BigInteger(rev);
    }

    /**
     * This factory method returns a corresponding BigInteger to represent the
     * requested number.
     * 
     * @param lni The Squeak object to be represented.
     * @return A BigInteger instance representing the passed Squeak object.
     */
    public static BigInteger fromLargeNegativeInteger(SqueakObject lni) {
        // We can rely on the fact that Squeak large integers are stored as the
        // absolute value of the corresponding number. The sign is determined by
        // the class: LargePositiveInteger or LargeNegativeInteger. Internally,
        // the bytes are the same. Hence, we let BigInteger.negate() do the work
        // of transforming the number into correct two's complement representation.
        return fromLargePositiveInteger(lni).negate();
    }
    
    /**
     * This method returns a byte array representing the large integer's absolute
     * value for storage in a Squeak Large****tiveInteger object.
     * 
     * @param The Java BigInteger instance whose bytes have to be extracted.
     * @return A byte array containing the Squeak representation of this number.
     */
    public static byte[] squeakBytes(BigInteger bi) {
        // To determine the absolute value, it has first to be checked whether
        // the number is negative.
        if(bi.signum() == -1)
            bi = bi.negate();
        byte[] bytes = bi.toByteArray();
        int ext = (bytes[0] == 0) ? 1 : 0;
        byte[] rev = new byte[bytes.length - ext];
        for(int i = 0; i < bytes.length - ext; i++)
            rev[i] = bytes[bytes.length - i - 1];
        return rev;
    }
    
    // Some values for range checking.
    public static final BigInteger min_small = BigInteger.valueOf(SmallInteger.minSmallInt);
    public static final BigInteger max_small = BigInteger.valueOf(SmallInteger.maxSmallInt);
    
    public static boolean isBig(BigInteger b) {
        return
            b.compareTo(max_small) > 0 ||
            b.compareTo(min_small) < 0;
    }
    
    /**
     * Create or extract a BigInteger from a Large****tiveInteger that is surely
     * known to be one (i.e., surely not a SmallInteger). If the Squeak object
     * already carries a BigInteger, it is returned. Otherwise, it is created
     * and stored.
     * 
     * @param li a Squeak Large****tiveInteger.
     * @return a BigInteger representing the passed Squeak Large****tiveInteger.
     */
    public static BigInteger getOrCacheBig(SqueakObject li) {
        if(li.hasLarge()) {
            return li.large();
        }
        
        BigInteger big;
        if(SpecialObjects.isA(li, splOb_ClassLargePositiveInteger))
            big = LargeInteger.fromLargePositiveInteger(li);
        else
            // In this last case, because we cannot check for splOb_ClassLargeNegativeInteger,
            // we have to adopt a fall-back strategy using exceptions to cover
            // the case that li is not a LargeNegativeInteger but, e.g., a
            // Double. That is, this code may throw a ClassCastException.
            big = LargeInteger.fromLargeNegativeInteger(li);
        li.assignLarge(big);
        
        return big;
    }
    
    /**
     * Coerce the passed object, which may be a SmallInteger or Large****tiveInteger,
     * into a BigInteger for further processing.
     * 
     * @param o a SmallInteger or Large****tiveInteger.
     * @return a corresponding BigInteger.
     */
    public static BigInteger coerceToBig(Object o) {
        if(SmallInteger.isSmallInt(o))
            return BigInteger.valueOf(((Integer)o).intValue());
        else
            return LargeInteger.getOrCacheBig((SqueakObject)o);
    }
    
}
