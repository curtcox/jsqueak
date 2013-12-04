/*
This work is a derivative of JSqueak (http://research.sun.com/projects/JSqueak). 

Copyright (c) 2008  Daniel H. H. Ingalls, Sun Microsystems, Inc.  All rights reserved.
 
Portions copyright Frank Feinbube, Robert Wierschke, Michael Haupt.

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

package potato.objects;

/**
 * This class serves as a pure constant container. The various constants are
 * indices for special objects in the special objects array.
 * 
 * @author Michael Haupt
 */
public final class SpecialObjectConstants {
    
    public final static int splOb_NilObject = 0;
    public final static int splOb_FalseObject = 1;
    public final static int splOb_TrueObject = 2;
    public final static int splOb_SchedulerAssociation = 3;
    public final static int splOb_ClassBitmap = 4;
    public final static int splOb_ClassInteger = 5;
    public final static int splOb_ClassString = 6;
    public final static int splOb_ClassArray = 7;
    //public final static int splOb_SmalltalkDictionary= 8;  old slot 8
    public final static int splOb_ClassFloat = 9;
    public final static int splOb_ClassMethodContext = 10;
    public final static int splOb_ClassBlockContext = 11;
    public final static int splOb_ClassPoint = 12;
    public final static int splOb_ClassLargePositiveInteger = 13;
    public final static int splOb_TheDisplay = 14;
    public final static int splOb_ClassMessage = 15;
    public final static int splOb_ClassCompiledMethod = 16;
    public final static int splOb_TheLowSpaceSemaphore = 17;
    public final static int splOb_ClassSemaphore = 18;
    public final static int splOb_ClassCharacter = 19;
    public final static int splOb_SelectorDoesNotUnderstand = 20;
    public final static int splOb_SelectorCannotReturn = 21;
    public final static int splOb_TheInputSemaphore = 22;
    public final static int splOb_SpecialSelectors = 23;
    public final static int splOb_CharacterTable = 24;
    public final static int splOb_SelectorMustBeBoolean = 25;
    public final static int splOb_ClassByteArray = 26;
    public final static int splOb_ClassProcess = 27;
    public final static int splOb_CompactClasses = 28;
    public final static int splOb_TheTimerSemaphore = 29;
    public final static int splOb_TheInterruptSemaphore = 30;
    public final static int splOb_FloatProto = 31;
    public final static int splOb_SelectorCannotInterpret = 34;
    public final static int splOb_MethodContextProto = 35;
    public final static int splOb_BlockContextProto = 37;
    public final static int splOb_ExternalObjectsArray = 38;
    public final static int splOb_ClassPseudoContext = 39;
    public final static int splOb_ClassTranslatedMethod = 40;
    public final static int splOb_TheFinalizationSemaphore = 41;
    public final static int splOb_ClassLargeNegativeInteger = 42;
    public final static int splOb_ClassExternalAddress = 43;
    public final static int splOb_ClassExternalStructure = 44;
    public final static int splOb_ClassExternalData = 45;
    public final static int splOb_ClassExternalFunction = 46;
    public final static int splOb_ClassExternalLibrary = 47;
    public final static int splOb_SelectorAboutToReturn = 48;

}
