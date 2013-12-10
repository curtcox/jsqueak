package org.squeak.potato.javainterop;

import org.squeak.potato.SmallTalkVMException;

public final class JavaProxyRuntimeException extends SmallTalkVMException {

	/**
	 *
	 */
	private static final long serialVersionUID = 3988528830178445820L;

	public JavaProxyRuntimeException(String message) {
		super(message);
	}

	public JavaProxyRuntimeException(Throwable cause) {
		super(cause);
	}

	public JavaProxyRuntimeException(String message, Throwable cause) {
		super(message, cause);
	}

}
