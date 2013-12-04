
# BUG001
When loading Suqeak 2.2 full image, we got a recursive error like this:

a primitive has failed
Bitmap class(Object)>>error:
Bitmap class(Object)>>primitiveFailed
Bitmap class(Behavior)>>new:
Bitmap class>>decompressFromByteArray:
Form>>unhibernate
DisplayScanner(BitBlt)>>copyBits
DisplayScanner(CharacterScanner)>>scanCharactersFrom:to:in:rightX:stopConditions:displaying:
DisplayScanner(CharacterScanner)>>scanCharactersFrom:to:in:rightX:stopConditions:kern:displaying:
[] in DisplayScanner>>displayLines:in:clippedBy:
Interval>>do:
DisplayScanner>>displayLines:in:clippedBy:
Paragraph>>displayLines:affectedRectangle:
Paragraph>>displayLines:
Paragraph>>displayOn:lines:
Paragraph>>displayOn:at:clippingBox:rule:fillColor:
Paragraph>>asForm
DisplayText>>composeForm
DisplayText>>form
DisplayText>>displayOn:at:clippingBox:rule:fillColor:
DisplayText(DisplayObject)>>displayOn:at:
String>>displayOn:at:
String>>displayAt:
Debugger class(Object)>>primitiveError:
Debugger class>>openContext:label:contents:
Bitmap class(Object)>>error:
Bitmap class(Object)>>primitiveFailed
Bitmap class(Behavior)>>new:
Bitmap class>>decompressFromByteArray:
Form>>unhibernate
BitBlt>>copyBits
# BUG 002
Test Method

Launching 
"Java JAVAMyClassXmyMethod"
generate a stack trace

INFO: isJavaCall>>JAVAMyClassXmyMethod
Exception in thread "main" java.lang.RuntimeException: Could not acces Class/Method to be called.
        at potato.javaAccess.JavaCall.getMethodFromSelectorString(JavaCall.java:119)
        at potato.javaAccess.JavaCall.<init>(JavaCall.java:61)
        at potato.vm.VM.send(VM.java:925)
        at potato.vm.VM.run(VM.java:647)
        at potato.Main.main(Main.java:80)
Caused by: java.lang.ClassNotFoundException: MyClass
        at java.net.URLClassLoader$1.run(URLClassLoader.java:202)
        at java.security.AccessController.doPrivileged(Native Method)
        at java.net.URLClassLoader.findClass(URLClassLoader.java:190)
        at java.lang.ClassLoader.loadClass(ClassLoader.java:306)
        at sun.misc.Launcher$AppClassLoader.loadClass(Launcher.java:301)
        at java.lang.ClassLoader.loadClass(ClassLoader.java:247)
        at java.lang.Class.forName0(Native Method)
        at java.lang.Class.forName(Class.java:169)
        at potato.javaAccess.JavaCall.getMethodFromSelectorString(JavaCall.java:113)
        ... 4 more
