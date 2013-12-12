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

import org.squeak.potato.objects.SpecialObjects;
import org.squeak.potato.objects.SqueakObject;

import static org.squeak.potato.objects.SpecialObjectConstants.*;

/**
 * @author Daniel Ingalls
 *
 * @author Frank Feinbube
 * @author Robert Wierschke
 */
public class Stack {
    VM squeakVM;
    public int sp;

    public Stack(VM squeakVM){
        this.squeakVM = squeakVM;
    }

    // STACKFRAME ACCESS:
    public boolean isContext(SqueakObject obj) {//either block or methodContext

        if (SpecialObjects.isA(obj, splOb_ClassMethodContext)) {
            return true;
        }
        if (SpecialObjects.isA(obj, splOb_ClassBlockContext)) {
            return true;
        }
        return false;
    }

    public boolean isMethodContext(SqueakObject obj) {
        if (SpecialObjects.isA(obj, splOb_ClassMethodContext)) {
            return true;
        }
        return false;
    }

    public Object pop() {
        //Note leaves garbage above SP.  Serious reclaim should store nils above SP
        return squeakVM.activeContext.pointers[sp--];
    }

    public void popN(int nToPop) {
        sp -= nToPop;
    }

    public void push(Object oop) {
        squeakVM.activeContext.pointers[++sp] = oop;
    }

    public void popNandPush(int nToPop, Object oop) {
        squeakVM.activeContext.pointers[sp -= nToPop - 1] = oop;
    }

    public Object top() {
        return squeakVM.activeContext.pointers[sp];
    }

    /**
     * Do a peek on the stack without altering it
     * @param depthIntoStack
     * @return
     */
    public Object stackValue(int depthIntoStack) {
        return squeakVM.activeContext.pointers[sp - depthIntoStack];
    }
}
