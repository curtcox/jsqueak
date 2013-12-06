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
package org.squeak.potato.javaAccess;

import java.lang.reflect.Method;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.squeak.potato.objects.SmallInteger;
import org.squeak.potato.objects.SqueakObject;
import org.squeak.potato.vm.Stack;

/**
 * @author Frank Feinbube
 * @author Robert Wierschke
 */
public class JavaCall {

	Logger logger=Logger.getLogger(getClass().getName());
    /**
     * The VM stack used to pass argument and result values.
     */
    private final Stack stack;
    /**
     * The Java method to be called.
     */
    private final Method method;
    /**
     * The Java (!) parameters uesd for the methdo call.
     */
    private final Object[] params;

    /**
     * Simple sets the stack to be uses during method operation.
     * @param stack The stak to use.
     */
    public JavaCall(Stack stack, SqueakObject selector) {
        this.stack = stack;

        int numberOfParameters = getNumberOfParameters(selector.toString());
        this.params = getParamsFromStack(numberOfParameters);
        this.method = getMethodFromSelectorString(selector.toString());
    }

//    /**
//     * Checks if sending a given message to the given receiver is a Java call.
//     * @param selector  The message to be sended.
//     * @param newRcvr   The receiver of the message.
//     * @return          true if it is a Java call.
//     */
//    public static boolean isJavaCall(SqueakObject selector, Object newRcvr) {
//    	boolean isJavaCall=newRcvr.toString().equals("a UndefinedObject") && selector.toString().startsWith("JAVA");
//    	if(isJavaCall) {
//    		Logger.getLogger(JavaCall.class.getName()).info("isJavaCall>>" +selector );
//    	}
//        return isJavaCall;
//    }

    public void invokeAndPushResult() {
        try {
            Object result = this.method.invoke(null, this.params);
            // just leave the receiver on stack if there is no return value
            if (result != null) {
                this.convertAndPushAsResult(result);
            }
        } catch (Exception ex) {
            Logger.getLogger(JavaCall.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * Converts the given Java type into a suitable Squeak type and pushs this
     * on the stack as the result value of the method call.
     *
     * @param result    The result value to be places on the stack.
     */
    private void convertAndPushAsResult(Object result) {
        this.stack.pop();   // remove the receiver from stack

        if (result instanceof Integer) {
            // TODO check if the result fits into SmallInteger value range
            // SmallInteger are already java.lang.Integer within Potato
        	Object oop=SmallInteger.smallFromInt((Integer) result);
        	logger.info("BUG001? "+result+" Converted to:"+oop);
            this.stack.push(oop);
        }
    }

    private Method getMethodFromSelectorString(String selectorString) {
    	return null;

    }


    private Method getMethodFromSelectorStringOLD(String selectorString) {
        if (!selectorString.startsWith("JAVA")) {
            throw new IllegalArgumentException(selectorString + " is no Java call.");
        } else {
            selectorString = selectorString.substring(4);
            String[] methodAndClass = selectorString.split("X");
            try {
                Class<?> javaClass = Class.forName(methodAndClass[0]);

                String methodName = methodAndClass[1].replace(":", "");
                Class<?>[] parameterTypes = getParameterTypes();
                return javaClass.getMethod(methodName,parameterTypes);
            } catch (Exception e) {
                throw new RuntimeException("Could not acces Class/Method to be called.", e);
            }
        }
    }

    private int getNumberOfParameters(String selectorString) {
        return selectorString.contains(":") ? selectorString.split(":").length : 0;
    }

    private Object[] getParamsFromStack(int numberOfParams) {
        if (numberOfParams == 0) {
            return null;
        } else {
            Object[] result = new Object[numberOfParams];
            for (int i = 0; i < numberOfParams; i++) {
                Object param = this.stack.pop();
                if (param instanceof SqueakObject) {
					result[i] = param.toString();
				} else {
					result[i] = param;
				}
            }
            return result;
        }
    }

    private Class<?>[] getParameterTypes() {
        Class<?>[] result = null;
        if (this.params != null) {
            result = new Class<?>[this.params.length];
            for (int i = 0; i < this.params.length; i++) {
                if (this.params[i] instanceof SqueakObject) {
					result[i] = String.class;   // HACK
				} else {
					result[i] = this.params[i].getClass();
				}
            }
        }
        return result;
    }
}
