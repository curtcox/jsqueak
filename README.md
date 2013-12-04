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

GOALS
-------------
At the time of writing the first goal is to enable image saving in a custom format (at least)
and to be able to do minimal Java interoperability (already some machinery in place, but not working right now).

Documentation
-----------------
Blue Book: http://stephane.ducasse.free.fr/FreeBooks/BlueBook/Bluebook.pdf


Change History
---------------
December 2013
+ SqueakImage: Removed usage of System.gc() which is bad design practice for new JVM. We must find a better way to remove weak references
+ Added JDK logging framework to track down stuff. Removed System.{out,err} to uniform this use
+ Added a strong jsqueak launcher leveraging JDK 1.6+ new GC technologies



Notes
-----
Based on a Squeak 2.2 mini image (2.2 is of Sep-1998)




[1] http://www.nabble.com/-squeak-dev--JSqueak%2C-the-erstwhile-Potato%2C-is-out%21-p18045925.html
[2] http://news.squeak.org/2008/07/07/potato-version-of-jsqueak-from-hpi/

Local Variables:
mode: markdown
End:
