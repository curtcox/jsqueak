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
package potato;

import java.awt.Rectangle;
import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import potato.objects.SmallInteger;

/**
 * @author Daniel Ingalls
 *  
 * @author Frank Feinbube
 * @author Robert Wierschke
 */
public class Arithmetics {
// Java rounds toward zero, we also need towards -infinity, so...
    public static int div(int rcvr, int arg) { // do this without floats asap
        if (arg == 0) {
            return SmallInteger.nonSmallInt;  // fail if divide by zero
        }
        return (int) Math.floor((double) rcvr / arg);
    }

    public static int quickDivide(int rcvr, int arg) { // only handles exact case
        if (arg == 0) {
            return SmallInteger.nonSmallInt;  // fail if divide by zero
        }
        int result = rcvr / arg;
        if (result * arg == rcvr) {
            return result;
        }
        return SmallInteger.nonSmallInt;
    } // fail if result is not exact

    public static int mod(int rcvr, int arg) {
        if (arg == 0) {
            return SmallInteger.nonSmallInt;  // fail if divide by zero
        }
        return rcvr - div(rcvr, arg) * arg;
    }

    public static int safeMultiply(int multiplicand, int multiplier) {
        int product = multiplier * multiplicand;
        //check for overflow by seeing if computation is reversible
        if (multiplier == 0) {
            return product;
        }
        if ((product / multiplier) == multiplicand) {
            return product;
        }
        return SmallInteger.nonSmallInt;
    }  //non-small result will cause failure

    public static int safeShift(int bitsToShift, int shiftCount) {
        if (shiftCount < 0) {
            return bitsToShift >> -shiftCount; //OK ot lose bits shifting right
        }
        //check for lost bits by seeing if computation is reversible
        int shifted = bitsToShift << shiftCount;
        if ((shifted >> shiftCount) == bitsToShift) {
            return shifted;
        }
        return SmallInteger.nonSmallInt;
    }  //non-small result will cause failure

    public static void copyBitmapToByteArray(int[] words, byte[] bytes, Rectangle rect, int raster, int depth, int BWMask) {
        // Copy our 32-bit words into a byte array  until we find out
        // how to make AWT happy with int buffers
        int word;
        int ix1 = rect.x / depth / 32;
        int ix2 = (rect.x + rect.width - 1) / depth / 32 + 1;
        for (int y = rect.y; y < rect.y + rect.height; y++) {
            int iy = y * raster;
            for (int ix = ix1; ix < ix2; ix++) {
                word = (words[iy + ix]) ^ BWMask;
                for (int j = 0; j < 4; j++) {
                    bytes[((iy + ix) * 4) + j] = (byte) ((word >> ((3 - j) * 8)) & 255);
                }
            }
        }
    }

    public static byte[] toByteArray(int[] values) throws IOException {
        ByteArrayOutputStream bytes = new ByteArrayOutputStream();
        DataOutputStream dataOut = new DataOutputStream(bytes);

        for (int i : values) {
            dataOut.writeInt(i);
        }
        return bytes.toByteArray();
    }
    
    public static int bitShift(int bitsToShift, int shiftCount){
        if (shiftCount < 0) {
            return bitsToShift >> -shiftCount;
        } else {
            return bitsToShift << shiftCount;
        }
    }
}
