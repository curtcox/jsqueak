package org.squeak.potato.javainterop;

import static org.squeak.potato.objects.SpecialObjectConstants.splOb_ClassString;

import java.lang.reflect.Method;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.squeak.potato.image.SqueakImage;
import org.squeak.potato.objects.SmallInteger;
import org.squeak.potato.objects.SpecialObjects;
import org.squeak.potato.objects.SqueakObject;
import org.squeak.potato.vm.Stack;


/**
 * A special Squeak Object which can proxy real Java instances
 * TODO: Enable support for other java types
 * TODO:
 * @author Giorgig
 *
 */
public class JavaProxyObject extends SqueakObject {

	Logger logger=Logger.getLogger(getClass().getName());

	private Object realJavaObjectRequested;
	/**
	 *
	 */
	private static final long serialVersionUID = 1L;

	public JavaProxyObject() {

	}

	public JavaProxyObject(SqueakImage image,String fullClassName){
		super(image,
				SpecialObjects.getSpecialObject(splOb_ClassString),
				fullClassName.length(), SpecialObjects.nilObj);

		// potato.primitives.PrimitiveHandler.makeStString(String)
		byte[] byteString = fullClassName.getBytes();
		System.arraycopy(byteString, 0, this.bits, 0, byteString.length);

		try {
			realJavaObjectRequested=Thread.currentThread().getContextClassLoader().loadClass(fullClassName).newInstance();
			String pseudoString=realJavaObjectRequested.hashCode()+" @ " +fullClassName;
			logger.info("Java proxy OK");

			this.bits = new byte[pseudoString.length()];
			System.arraycopy(pseudoString.getBytes(), 0, this.bits, 0, pseudoString.getBytes().length);

		} catch (InstantiationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}



	}

	public JavaProxyObject(SqueakImage img) {
		super(img);

	}

	public JavaProxyObject(SqueakImage img, SqueakObject cls,
			int indexableSize, SqueakObject filler) {
		super(img, cls, indexableSize, filler);
	}

	@Override
	final public boolean isJavaProxy() {
		return true;
	}

	/**
	 * How selector are traslated
	 * <pre>
	 * Smalltalk                                       - Java
	 * object toString                                 - object.toString()
	 * object firstParameter:arg secondParameter:borg  - object.firstParameter_secondParameter(arg,borg)
	 * object test:1 two: 2                            - object.test_two(1,2)
	 * //object stupidJavaMethod: [ 1, 2 , 3]            - object.stupidJavaMethod(1,2,3)
	 * </pre>
	 *
	 * @param selectorName
	 * @return The Method if possible, null if cannot respond
	 */
	public Method translate2JavaMethod(String smallTalkSelectorName) {
		int expectedParameters=
				smallTalkSelectorName.contains(":")?
				smallTalkSelectorName.split(":").length:0;
		String  selectorName;
		if(expectedParameters>0){
			selectorName=smallTalkSelectorName.replaceAll(":", "_");
			// Chop last "_"
			selectorName=selectorName.endsWith("_")?selectorName.substring(0,selectorName.length()-1):selectorName;
			logger.info(selectorName+" Parameters Expected:"+expectedParameters);
		}else{
			selectorName=smallTalkSelectorName;
			logger.info("Parameters Selector:"+selectorName);
		}
		for(Method m:realJavaObjectRequested.getClass().getMethods()){

			if(m.getName().equals(selectorName)){
				if(m.getParameterTypes().length == expectedParameters) {
					logger.info("FOUND:"+m);
					return m;
				}else{
					logger.info("Parmeter Match failed:"+m+"#" +m.getParameterTypes().length+
							" vs "+selectorName);
				}

			}
		}
		return null;
	}



	public void invokeAndPushResult(Stack stack, Method m) {
		int p=m.getParameterTypes().length;
		Object parameters[];
		if(p>0){
			parameters=getParamsFromStack(stack,p);
			// Ok parameters must be REVERTED

			final List<Object> ltemp = Arrays.asList(parameters);
			Collections.reverse(ltemp);

			parameters=ltemp.toArray(new Object[0]);
		} else {
			parameters = new Object[0];
		}

		logger.info("Preparing to call "+m);
		for(Object px: parameters){
			logger.info("\tParam: "+px);
		}


		try {
			Object result=m.invoke(realJavaObjectRequested, parameters);
			logger.info("<< "+m+" returns:"+result);
			convertAndPushAsResult(result,stack);
		}catch(Exception ex){
			logger.log(Level.SEVERE, "Invoke "+m+" FAILED", ex);
			convertAndPushAsResult(new Integer(-1),stack);
		}


	}

	private void convertAndPushAsResult(Object result,Stack stack) {
		stack.pop();   // remove the receiver from stack

		if (result instanceof Integer) {
			// TODO check if the result fits into SmallInteger value range
			// SmallInteger are already java.lang.Integer within Potato
			Object oop=SmallInteger.smallFromInt((Integer) result);
			logger.info(" "+result+" Converted to:"+oop);
			stack.push(oop);
		}else{
			throw new RuntimeException("Not yet implemented");
		}
	}


    private Object[] getParamsFromStack(Stack stack, int numberOfParams) {
        if (numberOfParams == 0) {
            return null;
        } else {
            Object[] result = new Object[numberOfParams];
            for (int i = 0; i < numberOfParams; i++) {
                Object param = stack.pop();
                if (param instanceof SqueakObject) {
					result[i] = param.toString();
				} else {
					result[i] = param;
				}
            }
            return result;
        }
    }




}
