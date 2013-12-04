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
package potato.image;

import potato.objects.ObjectTable;
import potato.objects.SqueakObject;
import potato.vm.VM;

import java.io.*;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.lang.ref.*;

import static potato.objects.SpecialObjectConstants.*;

/**
 * @author Daniel Ingalls
 *
 * @author Frank Feinbube
 * @author Robert Wierschke
 *
 * @author Giovanni Giorgi
 *
 * A SqueakImage represents the complete state of a running Squeak.
 * This implemenatation uses Java objects (see SqueakObject) for all Squeak objects,
 * with direct pointers between them. Enumeration is supported by objectTable,
 * which points weakly to all objects. SmallIntegers are modelled by Java Integers.
 *
 * Some care is taken in reclaiming OT slots, to preserve the order of creation of objects,
 * as this matters for Squeak weak objects, should we ever support them.
 */
public class SqueakImage implements Serializable {

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;

	Logger logger=Logger.getLogger(getClass().getName());

    public ObjectTable objectTable;
    SqueakImageHeader squeakImageHeader;
    public SqueakObject specialObjectsArray;
    private SqueakImageInputStream imageInputStream;
    VM vm;


    public SqueakImage(String fileName) {
        try {
            this.imageInputStream = new SqueakImageInputStream(fileName);
            imageFile = new File( fileName );
        } catch (IOException ex) {
            Logger.getLogger(SqueakImage.class.getName()).log(Level.SEVERE,
                    "cannot read image file " + fileName, ex);
        }
        objectTable = new ObjectTable();
        readImage();
    }

    private void readImage() {
        Map<Integer, SqueakObject> oopMap = new HashMap<Integer, SqueakObject>();
        squeakImageHeader = imageInputStream.readImageHeader();

        for (SqueakObject object : imageInputStream.readSqueakObjects()) {
            registerObject(object);

            //oopMap is from old oops to new objects
            oopMap.put(squeakImageHeader.mapAddress(object.baseAddr), object);
        }

        //Temp version of spl objs needed for makeCCArray; not a good object yet
        specialObjectsArray = (oopMap.get(squeakImageHeader.specialObjectsOopInt));
        Integer[] ccArray = makeCCArray(oopMap, specialObjectsArray);
        int oldOop = specialObjectsArray.oldOopAt(splOb_ClassFloat);
        SqueakObject floatClass = oopMap.get(new Integer(oldOop));

        for (WeakReference<SqueakObject> squeakObjectHolder : objectTable.getObjectTable()) {
            squeakObjectHolder.get().install(oopMap, ccArray, floatClass);
        //Proper version of spl objs -- it's a good object
        }
        specialObjectsArray = (oopMap.get(new Integer(squeakImageHeader.specialObjectsOopInt)));
    }

    public void saveImage(File filename) throws Exception {

    	final String fname = filename.toString();
    	logger.info("Serializing image:"+fname);
		//XMLEncoder out=new XMLEncoder(new FileOutputStream(fname));
    	ObjectOutputStream out= new ObjectOutputStream(new FileOutputStream(fname));
		logger.info("Serializing Header...");
    	out.writeObject(squeakImageHeader);
    	logger.info("Serializing objectTable...");
    	int written=0;
    	for(WeakReference<SqueakObject>  r:objectTable.getObjectTable()){
    		if(r.get()!=null){
    			// GG hint imitate copyStateFrom() to extract data to store...
    			out.writeObject(r.get());
    			written++;
    		}
    	}
    	out.close();
    	logger.info("Serializing Written:"+written+" objects");
    // Introduce SqueakImageWriter here
    // DataOutputStream dataOutputStream = new DataOutputStream(new GZIPOutputStream(new BufferedOutputStream(new FileOutputStream(filename))));
    // writeImage(dataOutputStream);
    // dataOutputStream.flush();
    // dataOutputStream.close();
    }

    public void bindVM(VM squeakVM) {
        vm = squeakVM;
        objectTable.bindVM(vm);
    }

    public short registerObject(SqueakObject obj) {
        //All enumerable objects must be registered
        objectTable.add(obj);

        squeakImageHeader.lastHash = 13849 + (27181 * squeakImageHeader.lastHash);
        return (short) (squeakImageHeader.lastHash & 0xFFF);
    }

    private Integer[] makeCCArray(Map<Integer, SqueakObject> oopMap, SqueakObject splObs) {
        //Makes an aray of the complact classes as oldOops (still need to be mapped)
        int oldOop = splObs.oldOopAt(splOb_CompactClasses);
        SqueakObject compactClassesArray = oopMap.get(new Integer(oldOop));
        Integer[] ccArray = new Integer[31];
        for (int i = 0; i < 31; i++) {
            ccArray[i] = new Integer(compactClassesArray.oldOopAt(i));
        }
        return ccArray;
    }

    //
    // save image support
    //

    private File imageFile;

    public File imageFile()
    {
        return imageFile;
    }

}
