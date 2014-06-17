package org.squeak.potato.vm;

import java.util.HashMap;

public class PrimitiveDocMan {

	enum Primitive {
		floatDivision(50,"(Primitive FAILED status)",false),
		wait(86,"wait. Primitive. The active Process must receive a signal through the receiver",true),
		quitPrimitive(113,"Exit to another operating system on the host machine",false),
		compareWithCollated(235,"compare: string1 with: string2 collated: order",false)


		;

		private int i;
		private String desc;
		private boolean fundamental; // false= avoid implement it but performance will suffer

		private Primitive(int c, String descs,boolean fundamentalb){
			i=c;			
			desc=descs;
			fundamental=fundamentalb;
		}

		public int i() {
			return i;
		}


		@Override public String toString() {
			return i+"#"+desc+ (fundamental?"F":"optional");
		}

		private static HashMap<Integer, Primitive> map=new HashMap<Integer, Primitive>();
		static {
			for(Primitive p:Primitive.values()) {
				map.put(p.i, p);
			}
		}

		public static Primitive valueOf(int primIndex) {
			return map.get(primIndex);			
		}

	}



	public String getDoc(int primIndex) {
		Primitive p=Primitive.valueOf(primIndex);
		if(p!=null) {
			return p.toString();
		}else {
			return primIndex+"#Undocumented";
		}
	}

}
