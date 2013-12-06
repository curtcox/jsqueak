JSqueak -- Java implementation of the Squeak Smalltalk Virtual Machine
----------------------------------------------------------------------

This is an official repository fork of JSqueak, a Java 
implementation of the Squeak Smalltalk virtual machine first born in 2008

The official site, where you can download official sources
was located at http://research.sun.com/projects/JSqueak (now a dead link)

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
+ seems a bit more advanced, even if a bit less commented on primitive stuff

At the moment
+ cannot work with the original Dan's mini.image (undefined primitive: 103 which is optional)


Jump Start
------------
A special modified test-image1 is provided for unit testing (look at the zip inside test_images folder)
This image has been altered via Squeak22.exe to provide an hook to a special bootstrap class
The entry point is
 SystemDictionary << processStartUpList
 Class DisplayScreen << startUp



GOALS
-------------
At the time of writing the first goal is to do minimal Java interoperability and to enable image saving in a custom format (at least)

Java interoperability can be reached defining a new special primitive "1993" to get a SqueakObject proxy of a 
Java object instance (i.e. "Java" pseudo object).
The primitive 1993 is able to create a new java object (empty construct right now).
The produced object is seen as a "String" but can trap every call versus java world.

Secondary Goal is to be able to boot Squeak 2.2 image and then Squeak 3.x image (very far away).

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
Based on a Squeak 2.2 mini image (2.2 is of Sep-1998)


Original Dan Ingalls Intro
----------------------------
Dan Ingalls has released JSqueak, a Squeak interpreter written in Java. 

JSqueak (formerly known as Potato) is less than 5000 lines of code, available under the MIT licence. It runs the Mini2.1 image, which is included for convenience. This image contains a complete Smalltalk development environment, including:

    Rich text and Text editor
    File browser (no file access in VM yet)
    Code browser
    Decompiler (plus temp-name hints)
    Compiler
    Source Code Debugger

Dan wrote JSqueak to teach himself NetBeans and Java in the fall of 2006. Although he developed it as a throw-away project, he notes that

    it has features that recommend it for further useful service:

        It is simple
            Uses Java objects and storage management
            Uses Java Integers for SmallIntegers
        It is general
            A weak(*) object table enables enumeration and mutation
        It is efficient
            Includes a method cache and an at-cache (**)
            Also a cache of common SmallIntegers

        (*) – This does not mean wimpy — it’s a good sturdy object table — it just doesn’t hold onto garbage.
        (**) – This is not an automated teller machine, but a device that speeds up array and stream access.

    These properties make it a reasonable base for teaching about VM design.

Dan adds that a number of things should be finished or improved if this VM is to see further use – it currently runs between 10 and 30 times slower than the C-based VM! If you wish to track or contribute to such projects, he invites you to add yourself to the (brand new!) JSqueak Interest mailing list.

You can find out more, and run the application as a WebStart Java Application at the JSqueak home page.


[1] http://www.nabble.com/-squeak-dev--JSqueak%2C-the-erstwhile-Potato%2C-is-out%21-p18045925.html
[2] http://news.squeak.org/2008/06/21/jsqueak-smalltalk-interpreter-written-in-java/
[3] http://news.squeak.org/2008/07/07/potato-version-of-jsqueak-from-hpi/


http://lists.squeakfoundation.org/pipermail/squeak-dev/2008-June/129178.html

Local Variables:
mode: markdown
mode: visual-line
coding: utf-8
End:
