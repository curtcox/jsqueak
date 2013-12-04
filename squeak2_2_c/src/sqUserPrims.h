/* Header file for Squeak user-defined primitives.
 *
 * Author: Ian.Piumarta@inria.fr
 *
 * Last edited: Wed Oct 22 12:32:24 1997 by piumarta (Ian Piumarta) on olrik
 *
 * Note: the definitions in this file are acutely dependent on many
 *	 internal details of the interpreter and image.
 *
 * Note: this user-defined primitive interface is UNSAFE.  Bugs in user
 *	 primitives can IRREVERSABLY damage an image!
 */

#include "sq.h"

typedef int oop;	/* object pointer */
typedef oop (*udp)();	/* primitive function */


/**
 **  interpreter functions required herein: NOT intended for user code!
 **/

extern int formatOf(oop);
extern int stSizeOf(oop);
extern int stInstVarSizeOf(oop);
extern oop instantiateClassindexableSize(oop, int);
extern int beRootIfOld(oop);
extern int youngStart;


/**
 **  user primitive management
 **/

/* user primitive startup code MUST define the following function... */

extern void sqInitializeUserPrimitives(void);

/* ...which in turn calls the following for each user primitive */

extern void declarePrimitiveIndexFunctionArgs(int index, udp func, int nArgs);

/* user primitive implementations call this to fail the primitive */

extern int primitiveFail(void);


/**
 **  objects -- should be obvious
 **/

extern oop nilObj;
extern oop trueObj;
extern oop falseObj;


/**
 **  classes and other globals -- also obvious
 **/

#define Bitmap		splObj(4)	/* class */
#define SmallInteger	splObj(5)	/* class */
#define String		splObj(6)	/* class */
#define Array		splObj(7)	/* class */
#define Float		splObj(9)	/* class */
#define Point		splObj(12)	/* class */
#define Character	splObj(19)	/* class */
#define ByteArray	splObj(26)	/* class */

#define Smalltalk	splObj(8)	/* global (a SystemDictionary) */
#define Display		splObj(14)	/* global (a DisplayScreen) */
#define CharacterTable	splObj(24)	/* Array of 256 Characters */


/**
 **  integer operations
 **/

/* true if oop is a SmallInteger */

extern int isIntegerObject(oop);

/* convert a SmallInteger from Smalltalk -> C representation */

extern int integerValueOf(oop);

/* true if int is in range for a SmallInteger */

extern int isIntegerValue(int);

/* convert a SmallInteger from C -> Smalltalk representation */

extern oop integerObjectOf(int);


/**
 **  float operations
 **/

/* true if OBJ is a Float */

#define isFloatObject(OBJ)	(fetchClassOf(OBJ) == Float)

/* fetch the value of the Float OBJ into the double VAR */

#define fetchFloat(OBJ,VAR)	fetchFloatAtinto((4 + (int)(OBJ)), VAR)

/* store the value of the double VAR into the Float OBJ */

#define storeFloat(OBJ,VAR)	storeFloatAtfrom((4 + (int)(OBJ)), VAR)


/**
 **  object class and format -- mostly self explanatory
 **/

/* answer the class of oop */

extern oop fetchClassOf(oop);

/* true if OBJ is an instance of a variable class */

#define isIndexable(OBJ)	(formatOf(OBJ) >= 2)

/* true if the indexable fields of oop are of the given kind */

extern int isBytes(oop);
extern int isWords(oop);
extern int isPointers(oop);

/* the number of instance variables (fixed fields) in OBJ */

#define instVarSize(OBJ)	 stInstVarSizeOf(OBJ)

/* the address of the first instance variable in OBJ */

#define firstFixedField(OBJ)	 ((char *)(OBJ) + 4)

/* the number of indexable fields in OBJ */

#define indexableSize(OBJ)	 stSizeOf(OBJ)

/* the address of the first indexable field in OBJ */

#define firstIndexableField(OBJ) ((char *)(OBJ) + 4 + (4 * instVarSize(OBJ)))


/**
 **  object access: C-style 0-based indeces, NOT 1-based (is this wrong???)
 **/

/* get or set the instance variable at offset IDX in OBJ */

#define instVarAt(OBJ,IDX)	(((oop *)(OBJ) + 1)[IDX])
#define instVarAtPut(OBJ,IDX,P)	(((oop *)(OBJ) + 1)[IDX]=(P))

/* get or set the indexable byte/word/pointer field at offset IDX in OBJ */

#define byteAt(OBJ,IDX)		(((char *)firstIndexableField(OBJ))[IDX])
#define byteAtPut(OBJ,IDX,B)	(((char *)firstIndexableField(OBJ))[IDX]= (B))
#define wordAt(OBJ,IDX)		(((int *)firstIndexableField(OBJ))[IDX])
#define wordAtPut(OBJ,IDX,W)	(((int *)firstIndexableField(OBJ))[IDX]= (W))
#define objectAt(OBJ,IDX)	(((oop *)firstIndexableField(OBJ))[IDX])
#define objectAtPut(OBJ,IDX,P)	(((oop *)firstIndexableField(OBJ))[IDX]= (P))


/**
 **  object instantiation and GC-protection, with Interpreter-style rules
 **/

/* return a new instance of CLS with LBS indexable fields.  LBS must
   be zero if CLS is not a variable class. */

#define new(CLS,LBS)		instantiateClassindexableSize((CLS), (LBS))

/* add OBJ to the root set if it is in old space */

#define registerRoot(OBJ) \
 (((OBJ) < youngStart && !isIntegerObject(OBJ)) && beRootIfOld(OBJ))

/* push/pop oop onto/off the remap stack before/after allocation.
   Pairs of calls to these functions must be matched precisely, or
   havoc may ensue! */

extern int pushRemappableOop(oop);
extern oop popRemappableOop(void);




/**
 **  plus other stuff as/when required...
 **/
