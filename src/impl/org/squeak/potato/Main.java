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

/*
 The author is indebted to Helge Horch for the outer framework of this VM.
 I knew nothing about how to write a Java program, and he provided the basic
 structure of main program, mouse input and display output for me.
 The object model, interpreter and primitives are all my design, but Helge
 continued to help whenever I was particularly stuck during the project.
 */

package org.squeak.potato;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

import org.apache.log4j.Logger;
import org.squeak.potato.image.SqueakImage;
import org.squeak.potato.vm.VM;

/**
 * @author Daniel Ingalls
 *  
 * @author Frank Feinbube
 * @author Robert Wierschke
 */ 
public class Main {

	private static SqueakImage locateStartableImage(String args[]) throws IOException {
		String name;

		if (args.length == 0) {
			name = "mini.image";
		} else {
			name = args[0];
		}

		File saved = new File(name);
		if (saved.exists()) {
			return new SqueakImage(name);
		} else {
			throw new FileNotFoundException("Cannot find image: " + name);
		}
	}

	/**
	 * @param args first arg may specify image file name
	 */
	public static void main(String[] args) {
		Logger logger=Logger.getLogger(Main.class);
		logger.info("JSqueak "+Constants.VERSION);
		try {
			SqueakImage squeakImage;			
			//SmallInteger.initSmallIntegerCache();
			String fname=args[0];
			if(fname.contains(".gz")) {
				squeakImage= SqueakImage.readJVMFormatimage(fname);
			}else {
				squeakImage = new SqueakImage(fname);
			}
			VM squeakVM = new VM(squeakImage);

			squeakVM.run();
		} catch (IOException ex) {
			logger.error( "Error in Main.", ex);
		}
	}
}
