JSqueak -- Java implementation of the Squeak Smalltalk Virtual Machine
----------------------------------------------------------------------

This is a fork of JSqueak, a Java  implementation of the Squeak Smalltalk virtual machine first born in 2008

This repository is maintained by Giovanni Giorgi (jj@gioorgi.com) 

This repository has been forked from repository  of Victor Rodriguez (victorr@gmail.com)
and merged with work from Jan Tomsa (tomy@tomsovi.com) and the potato fork [3] taken from https://svn.code.sf.net/p/potatovm/code/trunk/


Jump Start
------------
A special modified test-image1 is provided for unit testing (look at the zip inside test_images folder)
This image has been altered via Squeak22.exe to provide an hook to a special bootstrap class.
The Special bootstrap class is used for running a bunch of test at boot.
The entry point is
 SystemDictionary << processStartUpList
 Class DisplayScreen << startUp

## Requirements
JDK 1.6.33 64bit or better. 
Garbage Collector GC1 is the default choice for low latency.
Suggested at least 4GB of RAM, and a 64-bit Operating System.
Tested on MS Windows, and MAC OS X, should work without problem under Linux too.




Java Inteoperability
----------------------
There is an Alpha stage java interoperability.
The new primitive javaNew (number 1993) is able to create a java object instance, so you can write something like

```smalltalk
(Object javaNew: 'java.lang.Object') hashCode asString
```

Or try out a simple test class:

```smalltalk
(Object javaNew: 'org.squeak.potato.javainterop.Tester')
				test: 1 two: 2
```

At the time of writing you can pass easily String, Integers and java object back and forward.


## Debug support
A strong debug support is provided.
Use 
 -Djsqueak.debug.flag=true
to enable it
The breakPointMonitor vatiable defined in VM can set a list of selector to trigger the debug sniper.


DOCUMENTATION
--------------
See http://potatovm.blogspot.it/ for two articles on potato VM internals.


LICENSE
-------------

JSqueak was released under the MIT license (see the announcement[1] but also [2]).
Any original code released on this repository is also released under
the MIT license.



GOALS
-------------
At the time of writing the first goal is to do minimal Java interoperability and to enable image saving in a custom format (at least)
Secondary Goal is to be able to boot Squeak 2.2 image and then Squeak 3.x image (very far away target, anyway).





Documentation
-----------------
Blue Book: http://stephane.ducasse.free.fr/FreeBooks/BlueBook/Bluebook.pdf


Change History
---------------
Please see ChangeLog for important release notes.

Bugs
--------
See GitHub tracker





[1] http://www.nabble.com/-squeak-dev--JSqueak%2C-the-erstwhile-Potato%2C-is-out%21-p18045925.html
[2] http://news.squeak.org/2008/06/21/jsqueak-smalltalk-interpreter-written-in-java/
[3] http://news.squeak.org/2008/07/07/potato-version-of-jsqueak-from-hpi/

```emacs
Local Variables:
mode: markdown
mode: visual-line
coding: utf-8
End:
```
