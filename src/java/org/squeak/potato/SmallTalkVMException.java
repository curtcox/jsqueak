package org.squeak.potato;

public class SmallTalkVMException extends RuntimeException {

//	public SmallTalkVMException() {
//		// TODO Auto-generated constructor stub
//	}

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;

	public SmallTalkVMException(String message) {
		super(message);
	}

	public SmallTalkVMException(Throwable cause) {
		super(cause);
	}

	public SmallTalkVMException(String message, Throwable cause) {
		super(message, cause);
	}

}
