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
package org.squeak.potato.image;

import java.io.Serializable;

/**
 * @author Daniel Ingalls
 *
 * @author Frank Feinbube
 * @author Robert Wierschke
 */
public class SqueakImageHeader implements Serializable{

    /**
	 *
	 */
	private static final long serialVersionUID = 1L;


	int version;
    int headerSize;
    int endOfMemory; //first unused location in heap
    int oldBaseAddr; //object memory base address of image
    int specialObjectsOopInt; //oop of array of special oops
    public int lastHash; //Should be loaded from, and saved to the image header
    int savedWindowSize;
    int fullScreenFlag;
    int extraVMMemory;

    public SqueakImageHeader(int version, int headerSize, int endOfMemory, int oldBaseAddr, int specialObjectsOopInt, int lastHash, int savedWindowSize, int fullScreenFlag, int extraVMMemory) {
        this.version = version;
        this.headerSize = headerSize;
        this.endOfMemory = endOfMemory;
        this.oldBaseAddr = oldBaseAddr;
        this.specialObjectsOopInt = specialObjectsOopInt;
        this.lastHash = lastHash;
        this.savedWindowSize = savedWindowSize;
        this.fullScreenFlag = fullScreenFlag;
        this.extraVMMemory = extraVMMemory;
    }

    public int mapAddress(int baseAddr)
    {
        return baseAddr + oldBaseAddr;
    }
}
