JSqueak -- Java implementation of the Squeak Smalltalk Virtual Machine
----------------------------------------------------------------------

This is an unofficial repository for JSqueak, a Java 
implementation of the Squeak Smalltalk virtual machine.

The official site, where you can download official sources
is located at http://research.sun.com/projects/JSqueak.

JSqueak was released under the MIT license (see the announcement[1]).

Any original code released on this repository is also released under
the MIT license.

This repository is maintained by Giovanni Giorgi (jj@gioorgi.com) 
This repository has been forked from repository 
of Victor Rodriguez (victorr@gmail.com)
and merged with work from Jan Tomsa (tomy@tomsovi.com).

The Potato fork [2] with master trunk: https://svn.code.sf.net/p/potatovm/code/trunk/
is much more interesting because:
+ supports color
+ can read back an image saved with Squeak 2.2
+ cannot work with the original Dan's mini.image (undefined primitive: 103 which is optional)
+ seems a bit more advanced, even if a bit less commented on primitive stuff



Jump Start
------------
A special modified test-image1 is provided for unit testing (look at the zip inside test_images folder)
This image has been altered via Squeak22.exe to provide an hook to a special bootstrap class
The entry point is
 SystemDictionary << processStartUpList

Class DisplayScreen << startUp





Change History
---------------
December 2013
+ SqueakImage: Removed usage of System.gc which is bad design parctice for new JVM. We must find a better way to remove weak references
+ Added JDK logging framework to track down stuff. Removed System.{out,err} to uniform this use
+ TODO Better launch help
+ Created "etc/" directory with some launch configurations



Notes
-----
Based on a Squeak 2.2 mini image (2.2 is of Sep-1998)


RESEE
------

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
[2] http://news.squeak.org/2008/07/07/potato-version-of-jsqueak-from-hpi/

Local Variables:
mode: markdown
End:
