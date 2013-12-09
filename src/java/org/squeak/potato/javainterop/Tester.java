package org.squeak.potato.javainterop;

/**
 * Test Class for interop
 * @author Giorgig
 *
 */
public class Tester {

	/**
	 * Simple interop test class.
	 * @param a
	 * @param b
	 * @return
	 */
	public Integer test_two(int a, int b){
		return a+b;
	}

	public String test_string(int a, int b){
		return ""+(a+b);
	}
}
