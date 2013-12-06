package org.squeak.potato.objects;

import static org.squeak.potato.objects.SpecialObjectConstants.splOb_ClassString;

import java.lang.reflect.Method;
import java.util.logging.Logger;

import org.squeak.potato.image.SqueakImage;
import org.squeak.potato.vm.Stack;


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
	 * How selector are traslaated
	 * <pre>
	 * Smalltalk                                       - Java
	 * object toString                                 - object.toString()
	 * object firstParameter:arg secondParameter:borg  - object.firstParameter_secondParameter(arg,borg)
	 * object stupidJavaMethod: [ 1, 2 , 3]            - object.stupidJavaMethod(1,2,3)
	 * </pre>
	 * @param selectorName
	 * @return
	 */
	public boolean canRespondTo(String selectorName) {
		int expectedParameters=selectorName.split(":").length-1;
		if(expectedParameters>0){
			logger.info(selectorName+" Parameters Expected:"+expectedParameters);
		}else{
			logger.info("0Parameters Selector:"+selectorName);
		}
		for(Method m:realJavaObjectRequested.getClass().getMethods()){
			if(m.getName().equals(selectorName)){
				return true;
			}
		}
		return false;
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

	public void invokeAndPushResult(Stack stack, String selectorName) {
		logger.info("Fake "+selectorName);
		convertAndPushAsResult(new Integer(1),stack);
//        try {
//            Object result = this.method.invoke(null, this.params);
//            // just leave the receiver on stack if there is no return value
//            if (result != null) {
//                this.convertAndPushAsResult(result);
//            }
//        } catch (Exception ex) {
//            Logger.getLogger(JavaCall.class.getName()).log(Level.SEVERE, null, ex);
//        }

	}

}
