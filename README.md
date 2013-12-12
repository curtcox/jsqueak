JSqueak -- Java implementation of the Squeak Smalltalk Virtual Machine
----------------------------------------------------------------------

This is a fork of JSqueak, a Java 
implementation of the Squeak Smalltalk virtual machine first born in 2008

JSqueak was released under the MIT license (see the announcement[1] but also [2]).

Any original code released on this repository is also released under
the MIT license.

This repository is maintained by Giovanni Giorgi (jj@gioorgi.com) 

This repository has been forked from repository  of Victor Rodriguez (victorr@gmail.com)
and merged with work from Jan Tomsa (tomy@tomsovi.com) and the potato fork [3]

The Potato fork [3] with master trunk: https://svn.code.sf.net/p/potatovm/code/trunk/
is the major trunk right now becase:
+ supports color
+ can read back an image saved with Squeak 2.2
+ seems the more advanced one


Jump Start
------------
A special modified test-image1 is provided for unit testing (look at the zip inside test_images folder)
This image has been altered via Squeak22.exe to provide an hook to a special bootstrap class.
The Special bootstrap class is used for running a bunch of test at boot.
The entry point is
 SystemDictionary << processStartUpList
 Class DisplayScreen << startUp


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


GOALS
-------------
At the time of writing the first goal is to do minimal Java interoperability and to enable image saving in a custom format (at least)

Java interoperability can be reached defining a new special primitive "1993" to get a SqueakObject proxy of a 
Java object instance (i.e. "Java" pseudo object).
The primitive 1993 is able to create a new java object (empty construct right now).
At the meantime the produced object is seen as a "Smalltalk String" but can trap every call versus java world.

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



Notes
-----
The code base seems based on a Squeak 2.2 mini image (2.2 is of Sep-1998)

Squeak2.0 and Squeak 2.2 32bit image got a fatal error.
Squeak 1.31 image starts, but for a display bug show very bad even with 1 bit depth. 
Anyway it is unable to boot on Squeak2 VM so it is unlikely will be useful to be compatible.





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
