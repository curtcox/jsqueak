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
package potato.vm;

import potato.objects.SqueakObject;

/**
 * @author Daniel Ingalls
 *  
 * @author Frank Feinbube
 * @author Robert Wierschke
 */
public class MethodCache {

    static int randomish = 0;
    static int methodCacheSize = 1024; // must be power of two

    static int methodCacheMask = methodCacheSize - 1; // so this is a mask

    MethodCacheEntry[] methodCache = new MethodCacheEntry[methodCacheSize];

    void initMethodCache() {
        methodCache = new MethodCacheEntry[methodCacheSize];
        for (int i = 0; i < methodCacheSize; i++) {
            methodCache[i] = new MethodCacheEntry();
        }
    }

    public void clearMethodCache() { //clear method cache entirely (prim 89)

        for (int i = 0; i < methodCacheSize; i++) {
            methodCache[i].selector = null;   // mark it free

            methodCache[i].method = null;
        }    // release the method
    }

    public void flushMethodCacheForSelector(SqueakObject selector) { //clear cache entries for selector (prim 119)

        for (int i = 0; i < methodCacheSize; i++) {
            if (methodCache[i].selector == selector) {
                methodCache[i].selector = null;   // mark it free

                methodCache[i].method = null;
            }
        }  // release the method
    }

    public void flushMethodCacheForMethod(SqueakObject method) { //clear cache entries for selector (prim 116)

        for (int i = 0; i < methodCacheSize; i++) {
            if (methodCache[i].method == method) {
                methodCache[i].selector = null;   // mark it free

                methodCache[i].method = null;
            }
        }  // release the method
    }

    public MethodCacheEntry findMethodCacheEntry(SqueakObject selector, SqueakObject lkupClass) {
        //Probe the cache, and return the matching entry if found
        //Otherwise return one that can be used (selector and class set) with method= null.
        //Initial probe is class xor selector, reprobe delta is selector
        //We don not try to optimize probe time -- all are equally 'fast' compared to lookup
        //Instead we randomize the reprobe so two or three very active conflicting entries
        //will not keep dislodging each other
        MethodCacheEntry entry;
        int nProbes = 4;
        randomish = (randomish + 1) % nProbes;
        int firstProbe = (selector.hash ^ lkupClass.hash) & methodCacheMask;
        int probe = firstProbe;
        for (int i = 0; i < 4; i++) { // 4 reprobes for now

            entry = methodCache[probe];
            if (entry.selector == selector && entry.lkupClass == lkupClass) {
                return entry;
            }
            if (i == randomish) {
                firstProbe = probe;
            }
            probe = (probe + selector.hash) & methodCacheMask;
        }
        entry = methodCache[firstProbe];
        entry.lkupClass = lkupClass;
        entry.selector = selector;
        entry.method = null;
        return entry;
    }
}
