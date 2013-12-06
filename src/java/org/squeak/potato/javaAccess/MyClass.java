package org.squeak.potato.javaAccess;

/*
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

/** 
 * @author Frank Feinbube
 * @author Robert Wierschke
 * 
 * Demo class for Java access
 * 
 * Usage:
 * Java JAVAMyClassXmyMethod
 * Java JAVAMyClassXmyMethod: 42
 * Java JAVAMyClassXhello: 'Welt!'
 * Java JAVAMyClassXadd: 42 to: 23
 */
public class MyClass {

    public static int myMethod() {
        System.out.println("myMethod was called");
        return 23;
    }

    public static int myMethod(Integer arg) {
        System.out.println("myMethod_int was called");
        return arg;
    }
    
    public static void hello(String arg) {
        System.out.println("Hallo " + arg);
    }
    
    public static int addto(Integer a, Integer b) {
        return a+b;
    }    
}
