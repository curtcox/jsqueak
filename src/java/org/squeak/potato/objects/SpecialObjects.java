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

import org.squeak.potato.image.SqueakImage;

import static org.squeak.potato.objects.SpecialObjectConstants.*;

/**
 * @author Daniel Ingalls
 *  
 * @author Frank Feinbube
 * @author Robert Wierschke
 * @author Michael Haupt
 */
public class SpecialObjects {

    public static SqueakObject nilObj;
    public static SqueakObject falseObj;
    public static SqueakObject trueObj;
    
    private static Object[] specialObjects;
    
    //
    // singleton management
    //
    
    private static boolean initialised = false;
    
    //
    // special objects instance creation
    //
    
    public static void init(SqueakImage image) {
        if(initialised)
            throw new IllegalStateException("special objects already initialised");
        specialObjects = image.specialObjectsArray.pointers;
        initialised = true;
        nilObj = getSpecialObject(splOb_NilObject);
        falseObj = getSpecialObject(splOb_FalseObject);
        trueObj = getSpecialObject(splOb_TrueObject);
    }
    
    //
    // special objects management
    //

    public static SqueakObject getSpecialObject(int zeroBasedIndex) {
        if(!initialised)
            throw new IllegalStateException("special objects not initialised");
        return (SqueakObject)specialObjects[zeroBasedIndex];
    }

    // MEMORY ACCESS:
    public static SqueakObject getClass(Object obj) {
        if(!initialised)
            throw new IllegalStateException("special objects not initialised");
        if (SmallInteger.isSmallInt(obj)) {
            return getSpecialObject(splOb_ClassInteger);
        }
        return ((SqueakObject) obj).getSqClass();
    }
    
    public static boolean isA(Object obj, int knownClass) {
        if(!initialised)
            throw new IllegalStateException("special objects not initialised");
        Object itsClass = getClass(obj);
        return itsClass == specialObjects[knownClass];
    }
    
    public static void registerSpecialObject(SqueakObject object, int specialObjSpec, int knownClass){
        if(!initialised)
            throw new IllegalStateException("special objects not initialised");
        if (isA(object, knownClass)) {
            specialObjects[specialObjSpec] = object;
        } else {
            specialObjects[specialObjSpec] = nilObj;
        }
    }
    
    // Use this one with extreme care!
    public static void forceRegisterSpecialObject(SqueakObject object, int specialObjectSpec) {
        if(!initialised)
            throw new IllegalStateException("special objects not initialised");
        specialObjects[specialObjectSpec] = object;
    }

}
