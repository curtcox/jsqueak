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

package com.gioorgi.squeak.test;

import java.io.File;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.squeak.potato.image.SqueakImage;
import org.squeak.potato.vm.VM;

/**
 * @author Daniel Ingalls
 *  
 * @author Frank Feinbube
 * @author Robert Wierschke
 */ 
public class ImageReloadTest {


	/**
	 *Test a minimal save and reload
	 */
	public static void main(String[] args)  {
		try {


			(new File("java-test.image")).delete();
			//SmallInteger.initSmallIntegerCache();
			{
				SqueakImage squeakImage = new SqueakImage("test_images/test-image1.image");
				VM squeakVM = new VM(squeakImage);
				// To run test and stimulate serialization bugs we *need* to execute at least 1 million opcodes
				squeakVM.run( 1 );
				//squeakVM.run( 1000000 );


				squeakImage.saveImage(new File("java-test.image"));
			}


			SqueakImage squeakImage = SqueakImage.readJVMFormatimage("java-test.image");
			VM squeakVM = new VM(squeakImage);
			squeakVM.run( 1 );
			System.err.println(" Worked baby! ");
			// optional for further testing
			//squeakVM.run( );
			//(new File("java-test.image")).deleteOnExit();
		} catch (Throwable ex) {
			Logger.getLogger(ImageReloadTest.class.getName()).log(Level.SEVERE, "Error in ImageSaveTest.", ex);
			ex.printStackTrace();
		}
		System.exit(0);
	}
}
