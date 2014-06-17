/*
This work is a derivative of JSqueak (http://research.sun.com/projects/JSqueak). 

Copyright (c) 2008  Frank Feinbube, Robert Wierschke.  All rights reserved.

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
package org.squeak.potato.tools;

import java.io.FileWriter;
import java.io.IOException;
import java.lang.reflect.Field;

import org.apache.log4j.Logger;
import org.squeak.potato.drawing.BitBlt;
import org.squeak.potato.objects.SqueakObject;

/**
 *
 * @author Frank Feinbube
 * @author Robert Wierschke
 */
public class DebugHelper {

	transient Logger logger=Logger.getLogger(this.getClass());
	BitBlt bitBlt;    

	public DebugHelper(BitBlt bitBlt){
		this.bitBlt = bitBlt;
	}

	public String copyBitsInfo(){
		return String.format("From(%1$6d|%2$4d,%3$4d,%4$4d,%5$4d)", 
				bitBlt.sourceForm.baseAddr, bitBlt.sourceX, bitBlt.sourceY, bitBlt.source.width, bitBlt.source.height) 
				+ String.format("  To(%1$6d|%2$4d,%3$4d,%4$4d,%5$4d)", 
						bitBlt.destForm.baseAddr, bitBlt.destX, bitBlt.destY, bitBlt.width, bitBlt.height);
	}

	String content;
	public String bitBltInfo() {
		content = "";

		content += "Instance variables:" + "\r\n";

		appendAllToContent("affectedB, affectedL, affectedR, affectedT, bbH, bbW, bitCount");
		appendAllToContent("clipHeight, clipWidth, clipX, clipY, cmBitsPerColor, cmFlags, cmLookupTable, cmMask, cmMaskTable, cmShiftTable, combinationRule");

		appendToContent("destBits", bitBlt.dest.bits);
		appendToContent("destDelta");
		appendToContent("destDepth", bitBlt.dest.depth);
		appendToContent("destForm");
		appendToContent("destHeight", bitBlt.dest.height);
		appendAllToContent("destIndex, destMask");
		appendToContent("destMSB", bitBlt.dest.msb);
		appendToContent("destPitch", bitBlt.dest.pitch);
		appendToContent("destPPW", bitBlt.dest.pixPerWord);
		appendToContent("destWidth", bitBlt.dest.width);
		appendAllToContent("destX, destY");

		appendAllToContent("dstBitShift, dx, dy, halftoneForm, halftoneHeight, hasSurfaceLock, hDir, height");
		appendAllToContent("isWarping, mask1, mask2, noHalftone, noSource, nWords, preload, skew, sourceAlpha");

		appendToContent("sourceBits", bitBlt.source.bits);
		appendToContent("sourceDelta");
		appendToContent("sourceDepth", bitBlt.source.depth);
		appendToContent("sourceForm");
		appendToContent("sourceHeight", bitBlt.source.height);
		appendToContent("sourceIndex");
		appendToContent("sourceMSB", bitBlt.source.msb);
		appendToContent("sourcePitch", bitBlt.source.pitch);
		appendToContent("sourcePPW", bitBlt.source.pixPerWord);
		appendToContent("sourceWidth", bitBlt.source.width);
		appendAllToContent("sourceX, sourceY, srcBitShift, sx, sy, vDir, width");

		return content;
	}

	public void saveDebugInformations(int id){
		saveFile(System.getProperty("java.io.tmpdir") + "\\DebugHelper", new Integer(id).toString() +  ".txt", bitBltInfo());
	}

	void appendAllToContent(String commaSeperatedFieldNames){
		String[] fieldNames = commaSeperatedFieldNames.split(",");

		for(String fieldName : fieldNames){
			appendToContent(fieldName.trim());
		}
	}

	void appendToContent(String fieldName){
		try {

			Class c = bitBlt.getClass();
			Field field = c.getDeclaredField(fieldName);
			field.setAccessible(true);
			appendToContent(fieldName, field.get(bitBlt));

		} catch (Exception ex) {
			Logger.getLogger(DebugHelper.class).error("appendToContent "+fieldName+ " FAILED", ex);
		}
	}

	void appendToContent(String fieldName, Object value){
		content += fieldName.trim() + " " + mapValue(value).toString() + "\r\n";
	}

	Object mapValue(Object value){
		if(value == null){
			return "nil";
		}

		if(value instanceof SqueakObject){
			return ((SqueakObject)value).baseAddr;
		}

		if(value instanceof int[]){
			String intContent = "";
			for( int i = 0; i<((int[]) value).length && i<100; i++ ){
				intContent += mapValue(((int[]) value)[i]) + " ";
			}
			intContent = "#(" + intContent.trim() + ")";
			return intContent;
		}

		if(value.toString().equals("-1")){
			return "4294967295";
		}

		if(value.toString().equals("-16777215")){
			return "4278190081";
		}

		return value;
	}

	void saveFile(String directory, String filename, String content){
		FileWriter fileWriter = null;
		String path = directory + "\\" + filename;
		try {
			if (directory == null) {
				return;
			}

			fileWriter = new FileWriter(path);
			fileWriter.write(content);
			System.out.println("Created " + path);
		} catch (IOException ex) {
			logger.error(null, ex);
		} finally {
			try {
				if (fileWriter != null) {
					fileWriter.close();
				}
			} catch (IOException ex) {
				logger.error(null, ex);
			}
		}
	}
}
