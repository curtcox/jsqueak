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
	public Integer test_two(Integer a, Integer b){
		return a+b;
	}

	public String test_string(Integer a, Integer b){
		return ""+(a+b);
	}

	public boolean test_is42(Integer n) {
		return n ==42;
	}

	// A group of classes to test overloading and type conversion between SmallTalk
	// and java

	public Object testOverloading(String s){
		return s+s;
	}

	public Object testOverloading(Integer i){
		return i+i;
	}

	public Object testOverloading(PassExample p){
		p.value=p.value+" Passed";
		return p;
	}

//	public Object testOverloading(Float f){
//		return f+f;
//	}

}
