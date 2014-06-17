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

package org.squeak.potato.drawing;

import java.awt.AWTException;
import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.Robot;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.lang.reflect.InvocationTargetException;

import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;
import javax.swing.Timer;
import javax.swing.WindowConstants;

import org.apache.log4j.Logger;
import org.squeak.potato.vm.VM;


/**
 * @author Helge Horch
 * @author Daniel Ingalls
 *  
 * @author Frank Feinbube
 * @author Robert Wierschke
 * 
 * Next to do... put in other color models and try depth = 2, 4, 8
 * Also clean up the cursor spec to use real Squeak masks
 *
 * Actually, more than screen display: also handles keyboard and mouse input,
 * keybard mapping (<i>to</i> scancodes), and creates custom cursors from
 * NoteTaker specs.
 */
public class Screen {
	transient Logger logger=Logger.getLogger(this.getClass());

	Dimension fExtent;
	private int fDepth;
	private JFrame fFrame;
	private JLabel fDisplay;
	private int fDisplayBits[];
	private MouseStatus fMouseStatus;
	private KeyboardQueue fKeyboardQueue;
	private Timer fHeartBeat;
	private boolean fScreenChanged;
	private Object fVMSemaphore;
	private final static boolean WITH_HEARTBEAT = true;
	private final static int FPS = 25;

	public Screen(String title, int width, int height, int depth, Object vmSema) {
		fVMSemaphore = vmSema;
		fExtent = new Dimension(width, height);
		fDepth = depth;
		fFrame = new JFrame(title);
		fFrame.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
		JPanel content = new JPanel(new BorderLayout());

		fDisplay = new JLabel(getNoDisplay());
		fDisplay.setSize(fExtent);
		content.add(fDisplay, BorderLayout.CENTER);
		fFrame.setContentPane(content);
		Dimension screen = Toolkit.getDefaultToolkit().getScreenSize();
		fFrame.setLocation((screen.width - fExtent.width) / 2, (screen.height - fExtent.height) / 2);	// center

		fDisplay.addMouseMotionListener(fMouseStatus = new MouseStatus( (VM) fVMSemaphore ));
		fDisplay.addMouseListener(fMouseStatus);
		fDisplay.setFocusable(true);	// enable keyboard input

		fDisplay.addKeyListener(fKeyboardQueue = new KeyboardQueue( (VM) fVMSemaphore ));

		fDisplay.setOpaque(true);
		fDisplay.getRootPane().setDoubleBuffered(false);	// prevents losing intermediate redraws (how?!)

		getFrame().addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent evt) {
				// TODO ask before shutdown
				// FIXME at least lock out quitting until concurrent image save has finished

				System.exit(1);
			}
		});
	}

	private Icon getNoDisplay() {
		return new Icon() {

			//@Override
			@Override
			public int getIconWidth() {
				return fExtent.width;
			}

			//@Override
			@Override
			public int getIconHeight() {
				return fExtent.height;
			}

			//@Override
			@Override
			public void paintIcon(Component c, Graphics g, int x, int y) {
			}
		};
	}

	public JFrame getFrame() {
		return fFrame;
	}

	public void setBits(int storage[], int depth) {
		fDepth = depth;
		fDisplay.setIcon(new ImageIcon(DisplayAdapter.createDisplayAdapter(storage, fExtent.width, fExtent.height, depth)));
		fDisplayBits = storage;
	}

	int[] getBits() {
		return fDisplayBits;
	}

	public void open() {
		fFrame.pack();
		fFrame.setVisible(true);
		if (WITH_HEARTBEAT) {
			fHeartBeat = new Timer(100 / FPS /* ms */, new ActionListener() {

				//@Override
				@Override
				public void actionPerformed(ActionEvent evt) {
					// Swing timers execute on EHT
					if (fScreenChanged) {
						// could use synchronization, but lets rather paint too often
						fScreenChanged = false;
						Dimension extent = fDisplay.getSize();
						fDisplay.paintImmediately(0, 0, extent.width, extent.height);
					}
				}
			});
			fHeartBeat.start();
		}
	}

	public void close() {
		fFrame.setVisible(false);
		fFrame.dispose();
		if (WITH_HEARTBEAT) {
			fHeartBeat.stop();
		}

	}

	public void redisplay(boolean immediately, Rectangle area) {
		redisplay(immediately, area.x, area.y, area.width, area.height);
	}

	public void redisplay(boolean immediately, final int cornerX, final int cornerY, final int width, final int height) {
		fDisplay.repaint(cornerX, cornerY, width, height);
		fScreenChanged = true;
	}

	public void redisplay(boolean immediately) {
		fDisplay.repaint();
		fScreenChanged = true;
	}

	protected boolean scheduleRedisplay(boolean immediately, Runnable trigger) {
		if (immediately) {
			try {
				SwingUtilities.invokeAndWait(trigger);
				return true;
			} catch (InterruptedException e) {
				logRedisplayException(e);
			} catch (InvocationTargetException e) {
				logRedisplayException(e);
			}
			return false;
		} else {
			SwingUtilities.invokeLater(trigger);
			return true;
		}
	}

	protected void logRedisplayException(Exception ex) {
		logger.error("logRedisplayException", ex);
	}
	// extension point, default is ignorance

	public void setCursor(int[] cursorBits, int BWMask) {
		fDisplay.setCursor(new SqueakCursor(cursorBits, BWMask).asCursor());
	}

	public Dimension getExtent() {
		return fDisplay.getSize();
	}

	public void setExtent(Dimension extent) {
		fDisplay.setSize(extent);
		fFrame.setSize(extent);
	}

	public Point getLastMousePoint() {
		return new Point(fMouseStatus.fX, fMouseStatus.fY);
	}

	public int getLastMouseButtonStatus() {
		return fMouseStatus.fButtons & 7 | fKeyboardQueue.modifierKeys();
	}

	public void setMousePoint(int x, int y) {
		Point origin = fDisplay.getLocationOnScreen();
		x += origin.x;
		y += origin.y;
		try {
			Robot robot = new Robot();
			robot.mouseMove(x, y);
		} catch (AWTException ex) {
			// ignore silently?
					logger.error("Mouse move to " + x + "@" + y + " failed.", ex);
		}
	}

	public int keyboardPeek() {
		return fKeyboardQueue.peek();
	}

	public int keyboardNext() {
		return fKeyboardQueue.next();
	}
}
