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

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteOrder;
import java.util.ArrayList;
import java.util.List;
import java.util.zip.GZIPInputStream;

import javax.imageio.stream.FileCacheImageInputStream;

import org.apache.log4j.Logger;
import org.squeak.potato.objects.SqueakObject;

/**
 * @author Daniel Ingalls
 *
 * @author Frank Feinbube
 * @author Robert Wierschke
 *
 * Provides methods to read content of Squeak image files.
 */
public class SqueakImageInputStream extends  FileCacheImageInputStream {
	transient Logger logger=Logger.getLogger(this.getClass());
	/**
	 * Tha magic number / version number of Squeak image files.
	 */
	public static final int MAGIC_NUMBER = 6502;

	/**
	 * The offset of the current object in the image. The offset starts behind
	 * the image header, hence the offset of the first object is 0.
	 */
	private int currentObjectOffset;

	/**
	 * The number of bytes the objects consume in the immage (e.g. from offset
	 * of the first object to the end of the image).
	 */
	private int objectsMemorySize;

	/**
	 * Creates a new SqueakImageInputStream for the specified image file.
	 * @param fileName  The path to the image file.
	 * @throws java.io.IOException  If reading the file fails.
	 */
	public SqueakImageInputStream(String fileName) throws IOException {
		super(createInputStream(fileName), null);
		super.setByteOrder(detectAndSetEndianess());
		this.currentObjectOffset = 0;
	}

	/**
	 * Creates an InputStream for the given file. Optionally wrapping it with
	 * a uncompressing capabilities.
	 *
	 * @param fileName  The path to the image file.
	 * @return          An InputStream for reading the image file.
	 * @throws java.io.IOException
	 */
	public static InputStream createInputStream(String fileName) throws  IOException {
		InputStream inputStream = new FileInputStream(fileName);

		if (fileName.endsWith(".gz")) {
			inputStream = new GZIPInputStream(inputStream);
		}

		return inputStream;
	}

	/**
	 * Detects the byte order of image file and configured the InputStream for
	 * the detected endianness. This method as no effect on the stream position
	 * hence subsequent calls to read method start at stream postion 0.
	 *
	 * @return  The byte order of the image file or null if the file seems not
	 *          to be a valid Squeak image.
	 */
	ByteOrder detectAndSetEndianess() {
		ByteOrder result = null;
		try {
			int firstWordinImage = super.readInt();

			if (firstWordinImage == MAGIC_NUMBER) {
				result = ByteOrder.BIG_ENDIAN;  // Java's default endianess
			} else if (Integer.reverseBytes(firstWordinImage) == MAGIC_NUMBER) {
				result = ByteOrder.LITTLE_ENDIAN;
			}

			// TODO According to the Squeak documentation image files may have
			// an offest of 512 bytes. We should handle these case here.

			super.seek(0);      // reset stream


		} catch (IOException ex) {
			logger.error(null, ex);
		}
		return result;
	}

	/**
	 * Reads the image header information from the image file. Optional header
	 * are ignored. After successfully reading the header the stream position
	 * points directly behind the image header (e.g. at the firsr object).
	 *
	 * @return  The image header or null in case of failure.
	 */
	SqueakImageHeader readImageHeader() {
		SqueakImageHeader result = null;
		try {
			int version = super.readInt();
			int headerSize = super.readInt();
			int endOfMemory = super.readInt(); //first unused location in heap
			int oldBaseAddr = super.readInt(); //object memory base address of image
			int specialObjectsOopInt = super.readInt(); //oop of array of special oops
			int lastHash = super.readInt(); //Should be loaded from, and saved to the image header
			int savedWindowSize = super.readInt();
			int fullScreenFlag = super.readInt();
			int extraVMMemory = super.readInt();

			result = new SqueakImageHeader(version, headerSize, endOfMemory,
					oldBaseAddr, specialObjectsOopInt, lastHash,
					savedWindowSize, fullScreenFlag, extraVMMemory);

			// skip optional header fields
			// TODO use optional header fields
			super.skipBytes(headerSize - (9 * 4));
		} catch (IOException ex) {
			logger.error("cannot read image header", ex);
			// GG
			throw new RuntimeException("readImageHeader FAILED",ex);
		}

		// rembemer this for bulk object reading
		this.objectsMemorySize = result.endOfMemory;

		return result;
	}

	/**
	 * Reads the header of a Sqeak object from the stream. After succesful
	 * reading the stream is postioned directly after the header.
	 *
	 * @return  The read SqueakObjectHeader
	 */
	public SqueakObjectHeader readSqueakObjectHeader() {
		SqueakObjectHeader result = null;
		try {
			// XXX don't let this be the only one how reads itself
			result = new SqueakObjectHeader(this);
		} catch (IOException ex) {
			logger.error("cannot read squeak object header", ex);
		}
		return result;
	}

	/**
	 * Reads a Squeak object including its header from the stream. After
	 * succesfull reading the stream is positions points directly after the
	 * read object.
	 *
	 * @param startAddress
	 * @return      The read SqueakObject.
	 */
	SqueakObject readSqueakObject(int offset) {
		SqueakObject result = null;
		try {
			SqueakObjectHeader header = this.readSqueakObjectHeader();
			int[] content = new int[header.objectSizeInWords];
			super.readFully(content, 0, content.length);
			boolean hasWrongByteOrder = super.getByteOrder() == ByteOrder.LITTLE_ENDIAN;

			result = new SqueakObject(header, offset, content, hasWrongByteOrder);
		} catch (IOException ex) {
			logger.error("cannot read squeak object", ex);
		}
		return result;
	}

	/**
	 * Reads all Squeak objects from the image.
	 *
	 * @return  All objects in the image.
	 */
	SqueakObject[] readSqueakObjects() {
		List<SqueakObject> result = new ArrayList<SqueakObject>();

		do {
			SqueakObject newObject = this.readSqueakObject(this.currentObjectOffset);
			this.currentObjectOffset += newObject.size;
			result.add(newObject);
		} while(this.currentObjectOffset < this.objectsMemorySize);

		return result.toArray(new SqueakObject[0]);
	}
}
