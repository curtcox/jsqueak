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
package org.squeak.potato.drawing;

import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Image;
import java.awt.Point;
import java.awt.Toolkit;

/**
 * @author Dan Ingalls
 *
 * @author Frank Feinbube
 * @author Robert Wierschke
 */
public class SqueakCursor {
    private final static int Squeak_CURSOR_WIDTH = 16;
    private final static int Squeak_CURSOR_HEIGHT = 16;

    Cursor cursor;
    
    public SqueakCursor(int[] cursorBits, int BWMask){
        createCursorAdapter(cursorBits, BWMask);
    }
    
    private void createCursorAdapter(int[] cursorBits, int BWMask){
        Toolkit tk = Toolkit.getDefaultToolkit();
        Dimension cx = tk.getBestCursorSize(Squeak_CURSOR_WIDTH, Squeak_CURSOR_HEIGHT);
        if (cx.width == 0 || cx.height == 0) {
            cursor = Cursor.getDefaultCursor();
        } else {
            Image ci = DisplayAdapter.createDisplayAdapterCursor(cursorBits, Squeak_CURSOR_WIDTH, Squeak_CURSOR_HEIGHT, BWMask);
            cursor = tk.createCustomCursor(ci, new Point(0, 0), "Smalltalk-78 cursor");    
        }
    }
    
    public Cursor asCursor(){
        return cursor;
    }
}
