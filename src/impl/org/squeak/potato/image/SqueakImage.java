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


import static org.squeak.potato.objects.SpecialObjectConstants.splOb_ClassFloat;
import static org.squeak.potato.objects.SpecialObjectConstants.splOb_CompactClasses;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.lang.ref.WeakReference;
import java.util.HashMap;
import java.util.Map;
import java.util.zip.GZIPInputStream;
import java.util.zip.GZIPOutputStream;

import org.apache.log4j.Logger;
import org.squeak.potato.objects.ObjectTable;
import org.squeak.potato.objects.SqueakObject;
import org.squeak.potato.vm.VM;

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

	transient Logger logger=Logger.getLogger(getClass().getName());

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
			Logger.getLogger(SqueakImage.class.getName()).error(
					"cannot read image file " + fileName, ex);
		}
		objectTable = new ObjectTable();
		readImage();
	}

	private SqueakImage() {		
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


	public static SqueakImage readJVMFormatimage(String fname) throws IOException 
	{
		Logger logger=Logger.getLogger(SqueakImage.class.getName());
		// ENSURE we are friends...
		//SmallInteger.initSmallIntegerCache();

		File fnameObj = new File(fname);
		ObjectInputStream ois=new ObjectInputStream(
				new GZIPInputStream(
						new FileInputStream(fnameObj)));

		SqueakImage s= new SqueakImage();

		try {
			s.imageFile=fnameObj;
			s.squeakImageHeader=(SqueakImageHeader) ois.readObject();	
			// image.specialObjectsArray.pointers
			s.specialObjectsArray=(SqueakObject) ois.readObject();	
			s.objectTable = new ObjectTable();

			Object obj;
			do {
				// while( !(obj instanceof String && (""+obj).equals(END_OF_STREAM)) ) {
				obj=ois.readObject();			
				if(END_OF_STREAM.equals(obj)) {
					// finished
					logger.info("OK Java Image loaded.");
					break;
				}else {
					s.objectTable.add((SqueakObject) obj);
				}

			}while(true);
		} catch (ClassNotFoundException e) {
			throw new RuntimeException("JVM Read failed:"+e);
		} catch(java.io.EOFException eof){			
		}

		// specialObjectsArray = (oopMap.get(new Integer(squeakImageHeader.specialObjectsOopInt)));		
		return s;

	}

	private static final String END_OF_STREAM="DaitanGioRulez";

	public void saveImage(File filename) throws Exception {

		final String fname = filename.toString()+".gz";
		logger.info("Serializing image:"+fname);
		//XMLEncoder out=new XMLEncoder(new FileOutputStream(fname));
		ObjectOutputStream out= new ObjectOutputStream(
				new GZIPOutputStream(
						new FileOutputStream(fname)));
		logger.info("Serializing Header...");
		out.writeObject(squeakImageHeader);
		out.writeObject(specialObjectsArray);
		logger.info("Serializing objectTable...");
		int written=0;
		int logLimit=1;
		int errors=0;
		for(WeakReference<SqueakObject>  r:objectTable.getObjectTable()){
			if(r.get()!=null){
				// GG hint imitate copyStateFrom() to extract data to store...
				SqueakObject obj=r.get();
				//    			try {
				out.writeObject(obj);
				//    			}catch( java.io.NotSerializableException nse) {
				//    				if(--logLimit >=0) {
				//    					logger.error("Skipped:"+obj+" " +obj.getClass()+" ");
				//    					//nse.printStackTrace();
				//    				}else {
				//    					// System.err.print("E");
				//    				}
				//    				errors ++;
				//    			}
				written++;
			}
		}
		out.writeObject(END_OF_STREAM);
		out.close();
		logger.info("Serializing Written:"+written+" objects. Errors:"+errors);
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
