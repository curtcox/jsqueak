JSqueak -- Java implementation of the Squeak Smalltalk Virtual Machine

This is an unofficial repository for JSqueak, a Java 
implementation of the Squeak Smalltalk virtual machine.

The official site, where you can download official sources
is located at http://research.sun.com/projects/JSqueak.

JSqueak was released under the MIT license (see the announcement[1]).

Any original code released on this repository is also released under
the MIT license.

This repository is maintained by Giovanni Giorgi (jj@gioorgi.com) 

Forked from repo of Victor Rodriguez (victorr@gmail.com)
and merged with work from Jan Tomsa (tomy@tomsovi.com) 

BUG FIXES
----------
+ SqueakImage: Removed usage of System.gc which is bad for new JVM
+ TODO Added JDK logging framework to track down stuff. Removed System.{out,err} to uniform this use
+ TODO Better launch help
+ Created "etc/" directory with some launch configurations


Notes
-----
Based on a Squeaj 2.2 mini image (2.2 is of Sep-1998)



Purpose of this repository: to understand Squeak, to understand JSqueak, hopefully enhance JSqueak.

Goals:
* Working Squeak GUI
* Comprehensible source code
* Saving image (not necessarily to the original binary format)
* Loading image of current Squeak 3.9
* Java interop: Java calling Smalltalk
   e.g.:
   ```java
    Smalltalk st = new Smalltalk("my.image");
    SmalltalkCallResult fiveSquares = st.eval("(1 to: 5) collect: [ :it | it*it ]");
   ```
* Java interop: Smalltalk calling Java
   e.g.:
   ```smalltalk
   |jre|
   jre := Java runtime.
   (1 to: 5) do [ :it |
      (jre getClass: System) out println: it. 
   ]
   ```

[1] http://www.nabble.com/-squeak-dev--JSqueak%2C-the-erstwhile-Potato%2C-is-out%21-p18045925.html
