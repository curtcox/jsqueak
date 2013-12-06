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

package org.squeak.potato;

/**
 * @author Daniel Ingalls
 *
 * @author Frank Feinbube
 * @author Robert Wierschke
 *
 * Yet to do...
 * Reorganize as primitives < byte interpreter < message sending < contexts, object memory
 * object memory includes smallInts, classes, pointers, enumeration but NOT image reading
 * contexts includes load/save context, stack access, blocks, ctxt recycling
 * message sending includes, lookup, method cache, activate
 * byte interp is mainly dispatch
 * separate out sched, array and stream(with at-cache), files, as well as bitblt
 */
public interface Constants {

	public final static String VERSION="0.3 CodeName: Red Bean";

	// Class layout:
	public final static int Class_superclass= 0;
	public final static int Class_mdict= 1;
	public final static int Class_format= 2;
	public final static int Class_name= 6;

        // Context layout
	public final static int Context_sender= 0;
	public final static int Context_instructionPointer= 1;
	public final static int Context_stackPointer= 2;
	public final static int Context_method= 3;
	public final static int Context_receiver= 5;
	public final static int Context_tempFrameStart= 6;
	public final static int Context_smallFrameSize= 17;
	public final static int Context_largeFrameSize= 57;
	public final static int BlockContext_caller= 0;
	public final static int BlockContext_argumentCount= 3;
	public final static int BlockContext_initialIP= 4;
	public final static int BlockContext_home= 5;
        // Stream layout:
	public final static int Stream_array= 0;
	public final static int Stream_position= 1;
	public final static int Stream_limit= 2;
	//Class ProcessorScheduler"
	public final static int ProcSched_processLists= 0;
	public final static int ProcSched_activeProcess= 1;
	//Class Link"
	public final static int Link_nextLink= 0;
	//Class LinkedList"
	public final static int LinkedList_firstLink= 0;
	public final static int LinkedList_lastLink= 1;
	//Class Semaphore"
	public final static int Semaphore_excessSignals= 2;
	//Class Process"
	public final static int Proc_suspendedContext= 1;
	public final static int Proc_priority= 2;
	public final static int Proc_myList= 3;
	// Association layout:
	public final static int Assn_key= 0;
	public final static int Assn_value= 1;
	// MethodDict layout:
	public final static int MethodDict_array= 1;
	public final static int MethodDict_selectorStart= 2;
        // Message layout
	public final static int Message_selector= 0;
	public final static int Message_arguments= 1;
	public final static int Message_lookupClass= 2;
	// Point layout:
	public final static int Point_x= 0;
	public final static int Point_y= 1;
	// Largetinteger layout:
	public final static int Largeinteger_bytes= 0;
	public final static int Largeinteger_neg= 1;
        // Character layout
        public final static int CharacterValueIndex = 0;

    // WINDOW LAYOUT:
    public static final int DEFAULT_WIDTH =  800;  // Orig was 640
    public static final int DEFAULT_HEIGHT = 600; //   Orig was 480

}
