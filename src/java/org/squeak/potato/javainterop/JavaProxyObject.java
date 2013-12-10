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
import org.squeak.potato.vm.VM;


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

		} catch(Exception e) {
			logger.log(Level.SEVERE,"Cannot proceed:",e);
			throw new JavaProxyRuntimeException("Cannot create instance of "+fullClassName,e);
		}



	}

//	public JavaProxyObject(SqueakImage img) {
//		super(img);
//
//	}
//
//	public JavaProxyObject(SqueakImage img, SqueakObject cls,
//			int indexableSize, SqueakObject filler) {
//		super(img, cls, indexableSize, filler);
//	}

	public JavaProxyObject(SqueakImage image, Object instance) {
		super(image,
				SpecialObjects.getSpecialObject(splOb_ClassString),
				instance.getClass().getName().length(), SpecialObjects.nilObj);

		String fullClassName=instance.getClass().getName();
		// potato.primitives.PrimitiveHandler.makeStString(String)
		byte[] byteString = fullClassName.getBytes();
		System.arraycopy(byteString, 0, this.bits, 0, byteString.length);

		realJavaObjectRequested=instance;
		String pseudoString=realJavaObjectRequested.hashCode()+" @ " +fullClassName;
		logger.info("Java proxy From Instance OK");
		this.bits = new byte[pseudoString.length()];
		System.arraycopy(pseudoString.getBytes(), 0, this.bits, 0, pseudoString.getBytes().length);

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


	/** Embed (converts) a java object into a Squak SmallTalk type if possible
	 *
	 * See also PrimitiveHandler for duplicated code like
	 * org.squeak.potato.primitives.PrimitiveHandler.makeStString(String)
	 *
	 * @param instance
	 * @return SqueakObject/Integer/JavaProxyObject
	 */
	public Object embed(Object result, VM vm){


		if (result instanceof Integer && SmallInteger.canBeSmallInt((Integer) result)) {
			// TODO check if the result fits into SmallInteger value range
			// SmallInteger are already java.lang.Integer within Potato
			Object oop=SmallInteger.smallFromInt((Integer) result);
			return oop;
		}


		/** Known BUG:
		 * When comparing a string result, weird things happens.
		 *
		 * '3'=='3' in SmallTalk
		 * but here we are allocating a brand new object so seems only
		 * '3' = '3'
		 * because strings are not the same.
		 *
		 */
		if(result instanceof String ){
			String javaString=(String)result;
	        byte[] byteString = javaString.getBytes();
	        SqueakObject stString = vm.instantiateClass(SpecialObjects.getSpecialObject(splOb_ClassString), javaString.length());
	        System.arraycopy(byteString, 0, stString.bits, 0, byteString.length);
	        return stString;
		}


		// TODO: Consider storing big Integer (!) like  splOb_ClassLargePositiveInteger

//		if (result instanceof Integer && !SmallInteger.canBeSmallInt((Integer) result)) {

//          byte[] lpi_bytes = LargeInteger.squeakBytes(new BigInteger(result));
//          SqueakObject squeak_result = vm.instantiateClass(
//                  SpecialObjects.getSpecialObject(splOb_ClassLargePositiveInteger),
//                  lpi_bytes.length
//              );
//          System.arraycopy(lpi_bytes, 0, squeak_result.bits, 0, lpi_bytes.length);
//          squeak_result.assignLarge(big);
//		}

		// Embed in special object

		return new JavaProxyObject(vm.image,result);
//		JavaProxyObject jpo=vm.instantiateJavaProxyClass(result.getClass().getName());


	}


	public void invokeAndPushResult(Method m, Stack stack,VM vm) {
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
			convertAndPushAsResult(result,stack,vm);
		}catch(Exception ex){
			logger.log(Level.SEVERE, "Invoke "+m+" FAILED", ex);
			convertAndPushAsResult(new Integer(-1),stack,vm);
		}


	}

	private void convertAndPushAsResult(Object result,Stack stack,VM vm) {
		stack.pop();   // remove the receiver from stack

		Object oop = embed(result, vm);
		logger.info(" "+result+" Converted to:"+oop);
		stack.push(oop);
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
