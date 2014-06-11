package org.squeak.potato.javainterop;

import static org.squeak.potato.objects.SpecialObjectConstants.splOb_ClassString;

import java.io.Externalizable;
import java.io.IOException;
import java.io.ObjectInput;
import java.io.ObjectOutput;
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
 * A special Squeak Object which can proxy real Java instances.
 * Proxed object can be saved only if serailized
 * 
 * @author Giorgig
 *
 */
public class JavaProxyObject extends SqueakObject implements Externalizable{

	private transient Logger logger=Logger.getLogger(getClass().getName());

	private transient Object realJavaObjectRequested;
	/**
	 *
	 */
	private static final long serialVersionUID = 1L;

	private Object[] currentParamsFromStacks;

	private final String pseudoString;

	public JavaProxyObject() {
		pseudoString="???";
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
			pseudoString = realJavaObjectRequested.hashCode()+" @ " +fullClassName;
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
		pseudoString=realJavaObjectRequested.hashCode()+" @ " +fullClassName;
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
	public Method translate2JavaMethod(String smallTalkSelectorName,Stack stack) {
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


						currentParamsFromStacks = getParamsFromStackAndRemoveThem(stack, expectedParameters);
						Class<?>[] parameterTypes = getParameterTypes(currentParamsFromStacks);
						Method m;
						try {
							logger.info("Searching for:"+selectorName+" "+Arrays.asList(parameterTypes));
							m = realJavaObjectRequested.getClass().getMethod(selectorName,parameterTypes);
						} catch (NoSuchMethodException e) {
							m=null;
							logger.info("Parmeter Match failed:"+m+"#" +parameterTypes.length+
									" vs "+selectorName);
						}
						return m;

						//		for(Method m:realJavaObjectRequested.getClass().getMethods()){
						//
						//
						//			if(m.getName().equals(selectorName)){
						//				if(m.getParameterTypes().length == expectedParameters) {
						//
						//
						//
						//					logger.info("FOUND:"+m);
						//					return m;
						//				}else{
						//					logger.info("Parmeter Match failed:"+m+"#" +m.getParameterTypes().length+
						//							" vs "+selectorName);
						//				}
						//
						//			}
						//		}
						//		return null;
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

		if(result==null){
			return SpecialObjects.nilObj;
		}

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


		//  Boolean conversion
		if( result instanceof Boolean){
			Boolean b=(Boolean)result;
			if(b) {
				return SpecialObjects.trueObj;
			} else {
				return SpecialObjects.falseObj;
			}
		}

		if( result instanceof JavaProxyObject){
			return result;
		}

		//  Standard Generic Proxy & FallbackObject
		return new JavaProxyObject(vm.image,result);
	}



	private Class<?>[] getParameterTypes(Object[] params) {
		Class<?>[] result = new Class<?>[0];
		if (params != null) {
			result = new Class<?>[params.length];
			for (int i = 0; i < params.length; i++) {
				if (params[i] instanceof SqueakObject) {
					result[i] = String.class;   // HACK
				} else {
					result[i] = params[i].getClass();
				}
			}
		}
		return result;
	}

	public void invokeAndPushResult(Method m, Stack stack,VM vm) {
		int p=m.getParameterTypes().length;
		Object parameters[];
		if(p>0){
			parameters=currentParamsFromStacks;
			// Ok parameters must be REVERTED

			final List<Object> ltemp = Arrays.asList(parameters);
			Collections.reverse(ltemp);

			parameters=ltemp.toArray(new Object[0]);
		} else {
			parameters = new Object[0];
		}

		logger.info("Preparing to call "+m);
		int pi=1;
		for(Object px: parameters){
			logger.info("\tParam: "+pi+" "+px);
			pi++;
		}


		try {
			Object result=m.invoke(realJavaObjectRequested, parameters);
			logger.info("<< "+m+" returns:"+result);
			convertAndPushAsResult(result,stack,vm);
		}catch(Exception ex){
			logger.log(Level.SEVERE, "Invoke "+m+" FAILED", ex);
			convertAndPushAsResult(new Integer(0),stack,vm);
		}


	}

	private void convertAndPushAsResult(Object result,Stack stack,VM vm) {
		stack.pop();   // remove the receiver from stack

		Object oop = embed(result, vm);
		logger.info(" "+result+" Converted to:"+oop);
		stack.push(oop);
	}


	/**
	 * This method must convert primitive SmallTalk types to Java type
	 * @param stack
	 * @param numberOfParams
	 * @return
	 */
	private Object[] getParamsFromStackAndRemoveThem(Stack stack, int numberOfParams) {
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
			logger.info("Parameters from stack:"+Arrays.asList(result));
			return result;
		}
	}

	@Override
	public void writeExternal(ObjectOutput out) throws IOException {
		logger.severe("Write unsupported:"+pseudoString);
		out.writeObject(pseudoString);

	}

	@Override
	public void readExternal(ObjectInput in) throws IOException,
	ClassNotFoundException {
		String ps=(String) in.readObject();
		logger.severe("read unsupported 4 proxy on"+ps);

	}




}
