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

import java.awt.Image;
import java.awt.Point;
import java.awt.image.BufferedImage;
import java.awt.image.ColorModel;
import java.awt.image.DataBuffer;
import java.awt.image.DataBufferInt;
import java.awt.image.DirectColorModel;
import java.awt.image.IndexColorModel;
import java.awt.image.MultiPixelPackedSampleModel;
import java.awt.image.Raster;
import java.awt.image.SampleModel;
import java.awt.image.SinglePixelPackedSampleModel;
import java.awt.image.WritableRaster;
import java.util.HashMap;
import java.util.Map;
import java.util.logging.Logger;

/**
 * @author Dan Ingalls
 *
 * @author Frank Feinbube
 * @author Robert Wierschke
 */
public class DisplayAdapter {
	static Logger logger=Logger.getLogger(DisplayAdapter.class.getName());

     // cf. http://doc.novsu.ac.ru/oreilly/java/awt/ch12_02.htm
    private final static byte kComponents[] = new byte[]{(byte) 255, 0};
    private final static ColorModel kBlackAndWhiteModel = new IndexColorModel(1, 2, kComponents, kComponents, kComponents);

    private final static byte kComponents2[] = new byte[]{(byte)0, (byte) 255};
    private final static byte kComponentsA[] = new byte[]{(byte)255};
    private final static ColorModel kBlackAndWhiteTransparentModel = new IndexColorModel(1, 1, kComponents2, kComponents2, kComponents2, kComponentsA);

    public static Image createDisplayAdapter(int storage[], int width, int height, int depth) {
        Image result = null;
        if(depth == 1){
            result = createDisplayAdapter1(storage, width, height);
        } else if (depth == 32){
            result = createDisplayAdapter32(storage, width, height);
        } else {
//        	logger.severe("Unsupported display depth " + depth+" Running at 32bit");
//        	result = createDisplayAdapter32(storage, width, height);

            throw new IllegalArgumentException("Unsupported display depth " + depth
                    + ". Supported display depth: 1 or 32.");
        }
        return result;
    }

    static Map<int[], Image> cursorCache = new HashMap<int[], Image>();

    public static Image createDisplayAdapterCursor(int storage[], int width, int height, int BWMask) {
        if(!cursorCache.containsKey(storage)){
            for(int i=0;i<storage.length; i++){
                storage[i] ^= ~BWMask;
            }

            DataBuffer buf = new DataBufferInt(storage, (height * width / 8) * 1);// single bank

            SampleModel sm = new MultiPixelPackedSampleModel(DataBuffer.TYPE_INT, width, height, 1 /* bpp */);
            WritableRaster raster = Raster.createWritableRaster(sm, buf, new Point(0, 0));
            Image image = new BufferedImage(kBlackAndWhiteTransparentModel, raster, true, null);

            cursorCache.put(storage, image);
        }

        return cursorCache.get(storage);
    }

    protected static Image createDisplayAdapter1(int storage[], int width, int height) {
        DataBuffer buf = new DataBufferInt(storage, (height * width / 8) * 1);// single bank

        SampleModel sm = new MultiPixelPackedSampleModel(DataBuffer.TYPE_INT, width, height, 1 /* bpp */);
        WritableRaster raster = Raster.createWritableRaster(sm, buf, new Point(0, 0));
        Image image = new BufferedImage(kBlackAndWhiteModel, raster, true, null);

        return image;
    }

    protected static Image createDisplayAdapter32(int storage[], int width, int height) {
        DirectColorModel colorModel = (DirectColorModel) ColorModel.getRGBdefault();
        DataBuffer buf = new DataBufferInt(storage, (height * width / 8) * 32);

        // SinglePixelPackedSampleModel is required by the color model
        // also we need to specify the bitmasks for ARGB components again
        SampleModel sm = new SinglePixelPackedSampleModel(buf.getDataType(), width, height,
                new int[]{colorModel.getRedMask(), colorModel.getGreenMask(), colorModel.getBlueMask(), colorModel.getAlphaMask()});

        WritableRaster raster = Raster.createWritableRaster(sm, buf, new Point(0, 0));
        Image image = new BufferedImage(colorModel, raster, true, null);

        return image;
    }
}
