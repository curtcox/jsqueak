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
package potato.drawing;

import java.awt.event.MouseEvent;

import javax.swing.event.MouseInputAdapter;

import potato.vm.VM;

class MouseStatus extends MouseInputAdapter 
{
    private final VM fSqueakVM;
    
    // FIXME: Make this fields private
    int fX, fY;
    int fButtons;
    
    private final static int RED = 4;
    private final static int YELLOW = 2;
    private final static int BLUE = 1;
    
    MouseStatus( VM squeakVM )
    {
        fSqueakVM = squeakVM;
    }
    
    private int mapButton(MouseEvent evt) 
    {
        switch (evt.getButton()) 
        {
            case MouseEvent.BUTTON1:
                if (evt.isControlDown()) 
                    return YELLOW;
                if (evt.isAltDown()) 
                    return BLUE;
                return RED;
            case MouseEvent.BUTTON2:    return BLUE;        // middle (frame menu)
            case MouseEvent.BUTTON3:    return YELLOW;  // right (pane menu)
            case MouseEvent.NOBUTTON:   return 0;
        }
        throw new RuntimeException("unknown mouse button in event"); 
    }
    
    public void mouseMoved(MouseEvent evt) 
    {
        fX = evt.getX();
        fY = evt.getY();
        fSqueakVM.wakeVM(); 
    }
    
    public void mouseDragged(MouseEvent evt) 
    {
        fX= evt.getX();
        fY= evt.getY();
        fSqueakVM.wakeVM(); 
    }
    
    public void mousePressed(MouseEvent evt) 
    {
        fButtons |= mapButton(evt);
        fSqueakVM.wakeVM(); 
    }
    
    public void mouseReleased(MouseEvent evt) 
    {
        fButtons &= ~mapButton(evt);
        fSqueakVM.wakeVM();
    }
}
