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
package org.squeak.potato.objects;

import java.lang.ref.WeakReference;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.List;
import java.util.logging.Logger;

import org.squeak.potato.vm.VM;


/**
 * @author Daniel Ingalls
 *
 * @author Frank Feinbube
 * @author Robert Wierschke
 */
public class ObjectTable {

	Logger logger=Logger.getLogger(getClass().getName());

    private final List<WeakReference> objectTable;
    int lastOTindex;

    VM vm;

    public ObjectTable(){
        objectTable = new ArrayList<WeakReference>();
    }

    public void bindVM(VM vm){
         this.vm = vm;
    }

    public void add(SqueakObject obj){
        objectTable.add(new WeakReference(obj));
    }

    public int otIndexOfObject(SqueakObject lastObj) {
        // hint: lastObj should be at lastOTindex
        SqueakObject obj = (SqueakObject) objectTable.get(lastOTindex).get();
        if (lastOTindex <= objectTable.size() && obj == lastObj) {
            return lastOTindex;
        } else {
            for (int i = 0; i <= objectTable.size(); i++) { // Alas no; have to find it again...

                obj = (SqueakObject) objectTable.get(i).get();
                if (obj == lastObj) {
                    return i;
                }
            }
        }

        //should not happen
        System.err.print("otIndexOfObject - this should never happen!!");
        return -1;
    }

    public SqueakObject nextInstance(int startingIndex, SqueakObject sqClass) {
        //if sqClass is null, then find next object, else find next instance of sqClass
        for (int i = startingIndex; i < objectTable.size(); i++) { // For every object...

            SqueakObject obj = (SqueakObject) objectTable.get(i).get();
            if (obj != null && (sqClass == null | obj.sqClass == sqClass)) {
                lastOTindex = i; // save hint for next scan

                return obj;
            }
        }
        return SpecialObjects.nilObj;
    } // Return nil if none found

    public boolean bulkBecome(Object[] fromPointers, Object[] toPointers, boolean twoWay) {
        int n = fromPointers.length;
        Object p, ptr, body[], mut;
        SqueakObject obj;
        if (n != toPointers.length) {
            return false;
        }
        Hashtable mutations = new Hashtable(n * 4 * (twoWay ? 2 : 1));

        if(!copyPointersToMutationTable(mutations, n, fromPointers, toPointers)) {
			return false;
		}

        if (twoWay) {
            if(!copyPointersToMutationTable(mutations, n, toPointers, fromPointers)) {
				return false;
			}
        }

        for (WeakReference<SqueakObject> squeakObjectHolder : objectTable) {
            // Now, for every object...
            obj = squeakObjectHolder.get();
            if (obj != null) { // mutate the class

                mut = mutations.get(obj.sqClass);
                if (mut != null) {
                    obj.sqClass = mut;
                }
                if ((body = obj.pointers) != null) { // and mutate body pointers

                    for (int j = 0; j < body.length; j++) {
                        ptr = body[j];
                        mut = mutations.get(ptr);
                        if (mut != null) {
                            body[j] = mut;
                        }
                    }
                }
            }
        }
        return true;
    }

    private boolean copyPointersToMutationTable(Hashtable mutations, int n, Object[] fromPointers, Object[] toPointers){
        Object p;

        for (int i = 0; i < n; i++) {
            p = fromPointers[i];
            if (!(p instanceof SqueakObject)) {
                return false;
            }  //non-objects in from array

            if (mutations.get(p) != null) {
                return false;
            } //repeated oops in from array
            else {
                mutations.put(p, toPointers[i]);
            }
        }

        return true;
    }

    public int fullGC() {
    	logger.info("...Full GC..");
        vm.clearCaches();
//        for (int i = 0; i < 5; i++) {
//            partialGC();
//        }
        reclaimNullOTSlots();
        return spaceLeft();
    }

    public int partialGC() {
    	// GG On newer JDK is discouraged
        // System.gc();
        reclaimNullOTSlots();
        return spaceLeft();
    }

    public int spaceLeft() {
        return (int) Math.min(Runtime.getRuntime().freeMemory(), SmallInteger.maxSmallInt);
    }

    private void reclaimNullOTSlots() {
        // Java GC will null out slots in the weak Object Table.
        // This procedure compacts the occupied slots (retaining order),
        // and returns a new value for otMaxUsed.
    	int reclaimed=0;
        while (objectTable.contains(null)) {
            objectTable.remove(null);
            reclaimed++;
        }
        logger.info("Reclaimed nulls:"+reclaimed);
    }

	public final List<WeakReference> getObjectTable() {
		reclaimNullOTSlots();
		return objectTable;
	}



}
