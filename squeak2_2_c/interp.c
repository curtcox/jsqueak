/* Automatically generated from Squeak on (2 October 1998 6:43:42 pm ) */

#include "sq.h"
#include "sqMachDep.h"  /* needed only by the JIT virtual machine */

/* memory access macros */
#define byteAt(i) (*((unsigned char *) (i)))
#define byteAtput(i, val) (*((unsigned char *) (i)) = val)
#define longAt(i) (*((int *) (i)))
#define longAtput(i, val) (*((int *) (i)) = val)

int printCallStack(void);
void error(char *s);
void error(char *s) {
	/* Print an error message and exit. */
	static int printingStack = false;

	printf("\n%s\n\n", s);
	if (!printingStack) {
		/* flag prevents recursive error when trying to print a broken stack */
		printingStack = true;
		printCallStack();
	}
	exit(-1);
}

/*** Variables ***/
int activeContext;
int affectedB;
int affectedL;
int affectedR;
int affectedT;
int allocationCount;
int allocationsBetweenGCs;
int argumentCount;
int bbH;
int bbW;
int bitBltOop;
int bitCount;
int checkAssertions;
int child;
int clipHeight;
int clipWidth;
int clipX;
int clipY;
int cmBitsPerColor;
int colorMap;
int combinationRule;
int compEnd;
int compStart;
int deferDisplayUpdates;
int destBits;
int destDelta;
int destForm;
int destIndex;
int destMask;
int destPixSize;
int destRaster;
int destX;
int destY;
int displayBits;
int dx;
int dy;
int endOfMemory;
int falseObj;
int field;
int freeBlock;
int freeLargeContexts;
int freeSmallContexts;
int fullScreenFlag;
int fwdTableLast;
int fwdTableNext;
int hDir;
int halftoneBase;
int halftoneForm;
int halftoneHeight;
int height;
int instructionPointer;
int interpreterProxy;
int interruptCheckCounter;
int interruptKeycode;
int interruptPending;
int lastHash;
int lastTick;
int lowSpaceThreshold;
int mask1;
int mask2;
int mcProbe;
unsigned char *memory;
int memoryLimit;
int messageSelector;
int method;
int methodCache[2049];
int nWords;
int newMethod;
int nextPollTick;
int nextWakeupTick;
int nilObj;
int noHalftone;
int noSource;
int opTable[35];
int parentField;
int pixPerWord;
int preload;
int primitiveIndex;
int receiver;
int reclaimableContextCount;
int remapBuffer[26];
int remapBufferCount;
int rootTable[1001];
int rootTableCount;
int savedWindowSize;
int scanDisplayFlag;
int scanRightX;
int scanStart;
int scanStop;
int scanStopArray;
int scanString;
int scanXTable;
int semaphoresToSignal[26];
int semaphoresToSignalCount;
int signalLowSpace;
int skew;
int sourceAlpha;
int sourceBits;
int sourceDelta;
int sourceForm;
int sourceIndex;
int sourcePixSize;
int sourceRaster;
int sourceX;
int sourceY;
int specialObjectsOop;
int srcBitIndex;
int srcHeight;
int srcWidth;
int stackPointer;
int statFullGCMSecs;
int statFullGCs;
int statIncrGCMSecs;
int statIncrGCs;
int statRootTableOverflows;
int statTenures;
int stopCode;
int successFlag;
int sx;
int sy;
int tenuringThreshold;
int theHomeContext;
int trueObj;
int vDir;
int width;
int youngStart;

/*** Function Prototypes ***/
int OLDrgbDiffwith(int sourceWord, int destinationWord);
int OLDtallyIntoMapwith(int sourceWord, int destinationWord);
int aComment(void);
int accessibleObjectAfter(int oop);
int activateNewMethod(void);
int addLastLinktoList(int proc, int aList);
int addToMethodCacheSelclassmethodprimIndex(int selector, int class, int meth, int primIndex);
int addWordwith(int sourceWord, int destinationWord);
int adjustAllOopsBy(int bytesToShift);
int adjustFieldsAndClassOfby(int oop, int offsetBytes);
int affectedBottom(void);
int affectedLeft(void);
int affectedRight(void);
int affectedTop(void);
int allAccessibleObjectsOkay(void);
int allYoungand(int array1, int array2);
int allocateheaderSizeh1h2h3fill(int byteSize, int hdrSize, int baseHeader, int classOop, int extendedSize, int fillWord);
int allocateChunk(int byteSize);
int allocateOrRecycleContext(int smallContextWanted);
int alphaBlendwith(int sourceWord, int destinationWord);
int alphaBlendConstwith(int sourceWord, int destinationWord);
int alphaBlendConstwithpaintMode(int sourceWord, int destinationWord, int paintMode);
int alphaPaintConstwith(int sourceWord, int destinationWord);
int areIntegersand(int oop1, int oop2);
int argCount(void);
int argumentCountOf(int methodPointer);
int argumentCountOfBlock(int blockPointer);
void * arrayValueOf(int arrayOop);
int asciiDirectoryDelimiter(void);
int asciiOfCharacter(int characterObj);
int assertClassOfis(int oop, int classOop);
int assertFloatand(int oop1, int oop2);
AsyncFile * asyncFileValueOf(int oop);
int baseHeader(int oop);
int beRootIfOld(int oop);
int beRootWhileForwarding(int oop);
int becomewith(int array1, int array2);
int bitAndwith(int sourceWord, int destinationWord);
int bitAndInvertwith(int sourceWord, int destinationWord);
int bitInvertAndwith(int sourceWord, int destinationWord);
int bitInvertAndInvertwith(int sourceWord, int destinationWord);
int bitInvertDestinationwith(int sourceWord, int destinationWord);
int bitInvertOrwith(int sourceWord, int destinationWord);
int bitInvertOrInvertwith(int sourceWord, int destinationWord);
int bitInvertSourcewith(int sourceWord, int destinationWord);
int bitInvertXorwith(int sourceWord, int destinationWord);
int bitOrwith(int sourceWord, int destinationWord);
int bitOrInvertwith(int sourceWord, int destinationWord);
int bitXorwith(int sourceWord, int destinationWord);
int booleanValueOf(int obj);
int byteLengthOf(int oop);
int byteSwapByteObjects(void);
int byteSwapped(int w);
int caller(void);
int characterForAscii(int integerObj);
int checkAddress(int byteAddress);
int checkBooleanResultfrom(int result, int primIndex);
int checkForInterrupts(void);
int checkImageVersionFrom(sqImageFile f);
int checkIntegerResultfrom(int integerResult, int primIndex);
int checkSourceOverlap(void);
int checkedByteAt(int byteAddress);
int checkedByteAtput(int byteAddress, int byte);
int checkedIntegerValueOf(int intOop);
int checkedLongAt(int byteAddress);
int checkedLongAtput(int byteAddress, int a32BitInteger);
int chunkFromOop(int oop);
int classHeader(int oop);
int clearRootsTable(void);
int clearWordwith(int source, int destination);
int clipRange(void);
int clone(int oop);
int commonAt(int stringy);
int commonAtPut(int stringy);
int compare31or32Bitsequal(int obj1, int obj2);
int containOnlyOopsand(int array1, int array2);
int copyBits(void);
int copyLoop(void);
int copyLoopNoSource(void);
int copyLoopPixMap(void);
int cr(void);
int createActualMessage(void);
int deltaFromtonSteps(int x1, int x2, int n);
int destMaskAndPointerInit(void);
int destinationWordwith(int sourceWord, int destinationWord);
int drawLoopXY(int xDelta, int yDelta);
int exchangeHashBitswith(int oop1, int oop2);
int executeNewMethod(void);
int extraHeaderBytes(int oopOrChunk);
int failSpecialPrim(int primIndex);
int failed(void);
void * fetchArrayofObject(int fieldIndex, int objectPointer);
int fetchByteofObject(int byteIndex, int oop);
int fetchClassOf(int oop);
int fetchContextRegisters(int activeCntx);
double fetchFloatofObject(int fieldIndex, int objectPointer);
int fetchIntegerofObject(int fieldIndex, int objectPointer);
int fetchIntegerOrTruncFloatofObject(int fieldIndex, int objectPointer);
int fetchPointerofObject(int fieldIndex, int oop);
int fetchWordofObject(int fieldIndex, int oop);
int fetchWordLengthOf(int objectPointer);
int fileRecordSize(void);
SQFile * fileValueOf(int objectPointer);
int findClassOfMethodforReceiver(int meth, int rcvr);
int findNewMethodInClass(int class);
int findSelectorOfMethodforReceiver(int meth, int rcvr);
int firstAccessibleObject(void);
int firstObject(void);
int fixedFieldsOfformatlength(int oop, int fmt, int wordLength);
double floatValueOf(int oop);
int flushMethodCache(void);
int formatOf(int oop);
int formatOfClass(int classPointer);
int fullCompaction(void);
int fullDisplayUpdate(void);
int fullGC(void);
int fwdBlockGet(void);
int fwdBlockValidate(int addr);
int fwdTableInit(void);
int getCurrentBytecode(void);
int getLongFromFileswap(sqImageFile f, int swapFlag);
int hashBitsOf(int oop);
int headerOf(int methodPointer);
int headerType(int oop);
int ignoreSourceOrHalftone(int formPointer);
int imageFormatVersion(void);
int incCompBody(void);
int incCompMakeFwd(void);
int incCompMove(int bytesFreed);
int incrementalCompaction(void);
int incrementalGC(void);
int initBBOpTable(void);
int initForwardBlockmappingto(int fwdBlock, int oop, int newOop);
int initialInstanceOf(int classPointer);
int initializeInterpreter(int bytesToShift);
int initializeMemoryFirstFree(int firstFree);
int initializeObjectMemory(int bytesToShift);
int instanceAfter(int objectPointer);
int instantiateClassindexableSize(int classPointer, int size);
int instantiateSmallClasssizeInBytesfill(int classPointer, int sizeInBytes, int fillValue);
int intToNetAddress(int addr);
int integerObjectOf(int value);
int integerValueOf(int objectPointer);
int interpret(void);
int isBytes(int oop);
int isEmptyList(int aLinkedList);
int isFreeObject(int oop);
int isIntegerObject(int objectPointer);
int isIntegerValue(int intValue);
int isObjectForwarded(int oop);
int isPointers(int oop);
int isWords(int oop);
int isWordsOrBytes(int oop);
int lastPointerOf(int objectPointer);
int lastPointerWhileForwarding(int oop);
int lengthOf(int oop);
int lengthOfbaseHeaderformat(int oop, int hdr, int fmt);
int literal(int offset);
int literalofMethod(int offset, int methodPointer);
int literalCountOf(int methodPointer);
int literalCountOfHeader(int headerPointer);
int loadBitBltFrom(int bbObj);
int loadInitialContext(void);
int loadScannerFromstartstopstringrightXstopArraydisplayFlag(int bbObj, int start, int stop, int string, int rightX, int stopArray, int displayFlag);
int lookupInMethodCacheSelclass(int selector, int class);
int lookupMethodInClass(int class);
int lookupMethodInDictionary(int dictionary);
int lowestFreeAfter(int chunk);
int makeDirEntryNamesizecreateDatemodDateisDirfileSize(char *entryName, int entryNameSize, int createDate, int modifiedDate, int dirFlag, int fileSize);
int makePointwithxValueyValue(int xValue, int yValue);
int mapInterpreterOops(void);
int mapPointersInObjectsFromto(int memStart, int memEnd);
int markAndTrace(int oop);
int markAndTraceInterpreterOops(void);
int markPhase(void);
int mergewith(int sourceWord, int destinationWord);
int methodClassOf(int methodPointer);
int netAddressToInt(int oop);
int newActiveContext(int aContext);
int newObjectHash(void);
int nilObject(void);
int objectAfter(int oop);
int objectAfterWhileForwarding(int oop);
int okArrayClass(int cl);
int okStreamArrayClass(int cl);
int okayActiveProcessStack(void);
int okayFields(int oop);
int okayInterpreterObjects(void);
int okayOop(int oop);
int oopFromChunk(int chunk);
int oopHasOkayClass(int oop);
int partitionedANDtonBitsnPartitions(int word1, int word2, int nBits, int nParts);
int partitionedAddtonBitsnPartitions(int word1, int word2, int nBits, int nParts);
int partitionedMaxwithnBitsnPartitions(int word1, int word2, int nBits, int nParts);
int partitionedMinwithnBitsnPartitions(int word1, int word2, int nBits, int nParts);
int partitionedSubfromnBitsnPartitions(int word1, int word2, int nBits, int nParts);
int pickSourcePixelsnullMapsrcMaskdestMask(int nPix, int nullMap, int sourcePixMask, int destPixMask);
int pickSourcePixelssrcMaskdestMask(int nPix, int sourcePixMask, int destPixMask);
int pickSourcePixelsNullMapsrcMaskdestMask(int nPix, int sourcePixMask, int destPixMask);
int pickSourcePixelsRGBnullMapsrcMaskdestMask(int nPix, int nullMap, int sourcePixMask, int destPixMask);
int pixMaskwith(int sourceWord, int destinationWord);
int pixPaintwith(int sourceWord, int destinationWord);
int pop(int nItems);
int popthenPush(int nItems, int oop);
double popFloat(void);
int popInteger(void);
int popPos32BitInteger(void);
int popRemappableOop(void);
int popStack(void);
int positive32BitIntegerFor(int integerValue);
int positive32BitValueOf(int oop);
int possibleRootStoreIntovalue(int oop, int valueObj);
int postGCAction(void);
int preGCAction(int fullGCFlag);
int prepareForwardingTableForBecomingwith(int array1, int array2);
int primIndex(void);
int primitiveAdd(void);
int primitiveArctan(void);
int primitiveArrayBecome(void);
int primitiveAsFloat(void);
int primitiveAsOop(void);
int primitiveAsyncFileClose(void);
int primitiveAsyncFileOpen(void);
int primitiveAsyncFileReadResult(void);
int primitiveAsyncFileReadStart(void);
int primitiveAsyncFileWriteResult(void);
int primitiveAsyncFileWriteStart(void);
int primitiveAt(void);
int primitiveAtEnd(void);
int primitiveAtPut(void);
int primitiveBeCursor(void);
int primitiveBeDisplay(void);
int primitiveBeep(void);
int primitiveBitAnd(void);
int primitiveBitOr(void);
int primitiveBitShift(void);
int primitiveBitXor(void);
int primitiveBlockCopy(void);
int primitiveBytesLeft(void);
int primitiveClass(void);
int primitiveClipboardText(void);
int primitiveClone(void);
int primitiveConstantFill(void);
int primitiveCopyBits(void);
int primitiveDeferDisplayUpdates(void);
int primitiveDirectoryCreate(void);
int primitiveDirectoryDelimitor(void);
int primitiveDirectoryLookup(void);
int primitiveDirectorySetMacTypeAndCreator(void);
int primitiveDiv(void);
int primitiveDivide(void);
int primitiveDoPrimitiveWithArgs(void);
int primitiveDrawLoop(void);
int primitiveEqual(void);
int primitiveEquivalent(void);
int primitiveExitToDebugger(void);
int primitiveExp(void);
int primitiveExponent(void);
int primitiveFail(void);
int primitiveFileAtEnd(void);
int primitiveFileClose(void);
int primitiveFileDelete(void);
int primitiveFileGetPosition(void);
int primitiveFileOpen(void);
int primitiveFileRead(void);
int primitiveFileRename(void);
int primitiveFileSetPosition(void);
int primitiveFileSize(void);
int primitiveFileWrite(void);
int primitiveFloatAdd(void);
int primitiveFloatDivide(void);
int primitiveFloatEqual(void);
int primitiveFloatGreaterOrEqual(void);
int primitiveFloatGreaterThan(void);
int primitiveFloatLessOrEqual(void);
int primitiveFloatLessThan(void);
int primitiveFloatMultiply(void);
int primitiveFloatNotEqual(void);
int primitiveFloatSubtract(void);
int primitiveFlushCache(void);
int primitiveFlushCacheSelective(void);
int primitiveForceDisplayUpdate(void);
int primitiveFormPrint(void);
int primitiveFractionalPart(void);
int primitiveFullGC(void);
int primitiveGetAttribute(void);
int primitiveGreaterOrEqual(void);
int primitiveGreaterThan(void);
int primitiveImageName(void);
int primitiveIncrementalGC(void);
int primitiveIndexOf(int methodPointer);
int primitiveInitializeNetwork(void);
int primitiveInputSemaphore(void);
int primitiveInputWord(void);
int primitiveInstVarAt(void);
int primitiveInstVarAtPut(void);
int primitiveInterruptSemaphore(void);
int primitiveKbdNext(void);
int primitiveKbdPeek(void);
int primitiveLessOrEqual(void);
int primitiveLessThan(void);
int primitiveLoadInstVar(void);
int primitiveLogN(void);
int primitiveLowSpaceSemaphore(void);
int primitiveMIDIClosePort(void);
int primitiveMIDIGetClock(void);
int primitiveMIDIGetPortCount(void);
int primitiveMIDIGetPortDirectionality(void);
int primitiveMIDIGetPortName(void);
int primitiveMIDIOpenPort(void);
int primitiveMIDIParameterGetOrSet(void);
int primitiveMIDIRead(void);
int primitiveMIDIWrite(void);
int primitiveMakePoint(void);
int primitiveMillisecondClock(void);
int primitiveMod(void);
int primitiveMouseButtons(void);
int primitiveMousePoint(void);
int primitiveMultiply(void);
int primitiveNew(void);
int primitiveNewMethod(void);
int primitiveNewWithArg(void);
int primitiveNext(void);
int primitiveNextInstance(void);
int primitiveNextObject(void);
int primitiveNextPut(void);
int primitiveNoop(void);
int primitiveNotEqual(void);
int primitiveObjectAt(void);
int primitiveObjectAtPut(void);
int primitiveObjectPointsTo(void);
int primitivePerform(void);
int primitivePerformWithArgs(void);
int primitivePointX(void);
int primitivePointY(void);
int primitivePushFalse(void);
int primitivePushMinusOne(void);
int primitivePushNil(void);
int primitivePushOne(void);
int primitivePushSelf(void);
int primitivePushTrue(void);
int primitivePushTwo(void);
int primitivePushZero(void);
int primitiveQuit(void);
int primitiveQuo(void);
int primitiveReadJoystick(void);
int primitiveRelinquishProcessor(void);
int primitiveResolverAbortLookup(void);
int primitiveResolverAddressLookupResult(void);
int primitiveResolverError(void);
int primitiveResolverLocalAddress(void);
int primitiveResolverNameLookupResult(void);
int primitiveResolverStartAddressLookup(void);
int primitiveResolverStartNameLookup(void);
int primitiveResolverStatus(void);
int primitiveResponse(void);
int primitiveResume(void);
int primitiveScanCharacters(void);
int primitiveScreenSize(void);
int primitiveSecondsClock(void);
int primitiveSerialPortClose(void);
int primitiveSerialPortOpen(void);
int primitiveSerialPortRead(void);
int primitiveSerialPortWrite(void);
int primitiveSetFullScreen(void);
int primitiveSetInterruptKey(void);
int primitiveShortAt(void);
int primitiveShortAtPut(void);
int primitiveShowDisplayRect(void);
int primitiveSignal(void);
int primitiveSignalAtBytesLeft(void);
int primitiveSignalAtMilliseconds(void);
int primitiveSine(void);
int primitiveSize(void);
int primitiveSnapshot(void);
int primitiveSocketAbortConnection(void);
int primitiveSocketCloseConnection(void);
int primitiveSocketConnectToPort(void);
int primitiveSocketConnectionStatus(void);
int primitiveSocketCreate(void);
int primitiveSocketDestroy(void);
int primitiveSocketError(void);
int primitiveSocketListenOnPort(void);
int primitiveSocketLocalAddress(void);
int primitiveSocketLocalPort(void);
int primitiveSocketReceiveDataAvailable(void);
int primitiveSocketReceiveDataBufCount(void);
int primitiveSocketRemoteAddress(void);
int primitiveSocketRemotePort(void);
int primitiveSocketSendDataBufCount(void);
int primitiveSocketSendDone(void);
int primitiveSomeInstance(void);
int primitiveSomeObject(void);
int primitiveSoundAvailableSpace(void);
int primitiveSoundGetRecordingSampleRate(void);
int primitiveSoundInsertSamples(void);
int primitiveSoundPlaySamples(void);
int primitiveSoundPlaySilence(void);
int primitiveSoundRecordSamples(void);
int primitiveSoundSetRecordLevel(void);
int primitiveSoundStart(void);
int primitiveSoundStartRecording(void);
int primitiveSoundStartWithSemaphore(void);
int primitiveSoundStop(void);
int primitiveSoundStopRecording(void);
int primitiveSpecialObjectsOop(void);
int primitiveSquareRoot(void);
int primitiveStringAt(void);
int primitiveStringAtPut(void);
int primitiveStringReplace(void);
int primitiveSubtract(void);
int primitiveSuspend(void);
int primitiveTimesTwoPower(void);
int primitiveTruncated(void);
int primitiveVMParameter(void);
int primitiveVMPath(void);
int primitiveValue(void);
int primitiveValueWithArgs(void);
int primitiveWait(void);
int primitiveWarpBits(void);
int print(char *s);
int printCallStack(void);
int printChar(int aByte);
int printNameOfClasscount(int classOop, int cnt);
int printNum(int n);
int printStringOf(int oop);
int push(int object);
int pushBool(int trueOrFalse);
int pushFloat(double f);
int pushInteger(int integerValue);
int pushRemappableOop(int oop);
int putLongtoFile(int n, sqImageFile f);
int putToSleep(int aProcess);
int quickCheckForInterrupts(void);
int quickFetchIntegerofObject(int fieldIndex, int objectPointer);
int readImageFromFileHeapSize(sqImageFile f, int desiredHeapSize);
int recycleContextIfPossiblemethodContextClass(int cntxOop, int methodCntxClass);
int remap(int oop);
int remapClassOf(int oop);
int remapFieldsAndClassOf(int oop);
int removeFirstLinkOfList(int aList);
int reportContexts(void);
int restoreHeaderOf(int oop);
int restoreHeadersAfterBecomingwith(int list1, int list2);
int resume(int aProcess);
int returnAtlastIndexlefttop(int stopIndex, int lastIndex, int left, int top);
int reverseBytesFromto(int startAddr, int stopAddr);
int reverseBytesInImage(void);
int rgbAddwith(int sourceWord, int destinationWord);
int rgbDiffwith(int sourceWord, int destinationWord);
int rgbMapfromto(int sourcePixel, int nBitsIn, int nBitsOut);
int rgbMaxwith(int sourceWord, int destinationWord);
int rgbMinwith(int sourceWord, int destinationWord);
int rgbMinInvertwith(int wordToInvert, int destinationWord);
int rgbSubwith(int sourceWord, int destinationWord);
int rightType(int headerWord);
int scanCharacters(void);
int schedulerPointer(void);
int sendSelectorToClass(int classPointer);
int sender(void);
int setInterpreter(int anInterpreter);
int setSizeOfFreeto(int chunk, int byteSize);
int showDisplayBits(void);
int signExtend16(int int16);
int signalSemaphoreWithIndex(int index);
int sizeBitsOf(int oop);
int sizeBitsOfSafe(int oop);
int sizeHeader(int oop);
int sizeOfFree(int oop);
int sizeOfSTArrayFromCPrimitive(void *cPtr);
int smoothPixatXfyfdxhdyhdxvdyvpixPerWordpixelMasksourceMap(int n, int xf, int yf, int dxh, int dyh, int dxv, int dyv, int srcPixPerWord, int sourcePixMask, int sourceMap);
int socketRecordSize(void);
SQSocket * socketValueOf(int socketOop);
int sourcePixAtXypixPerWord(int x, int y, int srcPixPerWord);
int sourceSkewAndPointerInit(void);
int sourceWordwith(int sourceWord, int destinationWord);
int specialSelector(int index);
int splObj(int index);
int stObjectat(int array, int index);
int stObjectatput(int array, int index, int value);
int stSizeOf(int oop);
int stackIntegerValue(int offset);
int stackObjectValue(int offset);
int stackPointerIndex(void);
int stackTop(void);
int stackValue(int offset);
int startField(void);
int startObj(void);
int startOfMemory(void);
int stopReason(void);
int storeByteofObjectwithValue(int byteIndex, int oop, int valueByte);
int storeContextRegisters(int activeCntx);
int storeInstructionPointerValueinContext(int value, int contextPointer);
int storeIntegerofObjectwithValue(int fieldIndex, int objectPointer, int integerValue);
int storePointerofObjectwithValue(int fieldIndex, int oop, int valuePointer);
int storePointerUncheckedofObjectwithValue(int fieldIndex, int oop, int valuePointer);
int storeStackPointerValueinContext(int value, int contextPointer);
int storeWordofObjectwithValue(int fieldIndex, int oop, int valueWord);
int subWordwith(int sourceWord, int destinationWord);
int subscriptwithformat(int array, int index, int fmt);
int subscriptwithstoringformat(int array, int index, int oopToStore, int fmt);
int success(int successValue);
int sufficientSpaceAfterGC(int minFree);
int sufficientSpaceToAllocate(int bytes);
int sufficientSpaceToInstantiateindexableSize(int classOop, int size);
int superclassOf(int classPointer);
int sweepPhase(void);
int synchronousSignal(int aSemaphore);
int tallyIntoMapwith(int sourceWord, int destinationWord);
int targetForm(void);
int temporary(int offset);
int transferfromIndexofObjecttoIndexofObject(int count, int firstFrom, int fromOop, int firstTo, int toOop);
int transferTo(int newProc);
int unPop(int nItems);
int unknownBytecode(void);
int upward(void);
int wakeHighestPriority(void);
int warpBits(void);
int warpLoop(void);
int warpSourcePixelsxDeltahyDeltahxDeltavyDeltavsmoothingsourceMap(int nPix, int xDeltah, int yDeltah, int xDeltav, int yDeltav, int n, int sourceMapOop);
int writeImageFile(int imageBytes);

int OLDrgbDiffwith(int sourceWord, int destinationWord) {
    int diff;
    int pixMask;

	if (destPixSize < 16) {
		diff = sourceWord ^ destinationWord;
		pixMask = (((destPixSize < 0) ? ((unsigned) 1 >> -destPixSize) : ((unsigned) 1 << destPixSize))) - 1;
		while (!(diff == 0)) {
			if ((diff & pixMask) != 0) {
				bitCount += 1;
			}
			diff = ((unsigned) diff) >> destPixSize;
		}
		return destinationWord;
	}
	if (destPixSize == 16) {
		diff = partitionedSubfromnBitsnPartitions(sourceWord, destinationWord, 5, 3);
		bitCount = ((bitCount + (diff & 31)) + ((((unsigned) diff) >> 5) & 31)) + ((((unsigned) diff) >> 10) & 31);
		diff = partitionedSubfromnBitsnPartitions(((unsigned) sourceWord) >> 16, ((unsigned) destinationWord) >> 16, 5, 3);
		bitCount = ((bitCount + (diff & 31)) + ((((unsigned) diff) >> 5) & 31)) + ((((unsigned) diff) >> 10) & 31);
	} else {
		diff = partitionedSubfromnBitsnPartitions(sourceWord, destinationWord, 8, 3);
		bitCount = ((bitCount + (diff & 255)) + ((((unsigned) diff) >> 8) & 255)) + ((((unsigned) diff) >> 16) & 255);
	}
	return destinationWord;
}

int OLDtallyIntoMapwith(int sourceWord, int destinationWord) {
    int mapIndex;
    int pixMask;
    int shiftWord;
    int i;
    int mask;
    int srcPix;
    int destPix;
    int d;
    int mask3;
    int srcPix1;
    int destPix1;
    int d1;
    int mask4;
    int srcPix2;
    int destPix2;
    int d2;

	if (colorMap == nilObj) {
		return destinationWord;
	}
	if (destPixSize < 16) {
		pixMask = (1 << destPixSize) - 1;
		shiftWord = destinationWord;
		for (i = 1; i <= pixPerWord; i += 1) {
			mapIndex = shiftWord & pixMask;
			longAtput(((((char *) colorMap)) + 4) + (mapIndex << 2), (longAt(((((char *) colorMap)) + 4) + (mapIndex << 2))) + 1);
			shiftWord = ((unsigned) shiftWord) >> destPixSize;
		}
		return destinationWord;
	}
	if (destPixSize == 16) {
		/* begin rgbMap:from:to: */
		if ((d = cmBitsPerColor - 5) > 0) {
			mask = (1 << 5) - 1;
			srcPix = (destinationWord & 65535) << d;
			mask = mask << d;
			destPix = srcPix & mask;
			mask = mask << cmBitsPerColor;
			srcPix = srcPix << d;
			mapIndex = (destPix + (srcPix & mask)) + ((srcPix << d) & (mask << cmBitsPerColor));
			goto l1;
		} else {
			if (d == 0) {
				mapIndex = destinationWord & 65535;
				goto l1;
			}
			if ((destinationWord & 65535) == 0) {
				mapIndex = destinationWord & 65535;
				goto l1;
			}
			d = 5 - cmBitsPerColor;
			mask = (1 << cmBitsPerColor) - 1;
			srcPix = ((unsigned) (destinationWord & 65535)) >> d;
			destPix = srcPix & mask;
			mask = mask << cmBitsPerColor;
			srcPix = ((unsigned) srcPix) >> d;
			destPix = (destPix + (srcPix & mask)) + ((((unsigned) srcPix) >> d) & (mask << cmBitsPerColor));
			if (destPix == 0) {
				mapIndex = 1;
				goto l1;
			}
			mapIndex = destPix;
			goto l1;
		}
	l1:	/* end rgbMap:from:to: */;
		longAtput(((((char *) colorMap)) + 4) + (mapIndex << 2), (longAt(((((char *) colorMap)) + 4) + (mapIndex << 2))) + 1);
		/* begin rgbMap:from:to: */
		if ((d1 = cmBitsPerColor - 5) > 0) {
			mask3 = (1 << 5) - 1;
			srcPix1 = (((unsigned) destinationWord) >> 16) << d1;
			mask3 = mask3 << d1;
			destPix1 = srcPix1 & mask3;
			mask3 = mask3 << cmBitsPerColor;
			srcPix1 = srcPix1 << d1;
			mapIndex = (destPix1 + (srcPix1 & mask3)) + ((srcPix1 << d1) & (mask3 << cmBitsPerColor));
			goto l2;
		} else {
			if (d1 == 0) {
				mapIndex = ((unsigned) destinationWord) >> 16;
				goto l2;
			}
			if ((((unsigned) destinationWord) >> 16) == 0) {
				mapIndex = ((unsigned) destinationWord) >> 16;
				goto l2;
			}
			d1 = 5 - cmBitsPerColor;
			mask3 = (1 << cmBitsPerColor) - 1;
			srcPix1 = ((unsigned) (((unsigned) destinationWord) >> 16)) >> d1;
			destPix1 = srcPix1 & mask3;
			mask3 = mask3 << cmBitsPerColor;
			srcPix1 = ((unsigned) srcPix1) >> d1;
			destPix1 = (destPix1 + (srcPix1 & mask3)) + ((((unsigned) srcPix1) >> d1) & (mask3 << cmBitsPerColor));
			if (destPix1 == 0) {
				mapIndex = 1;
				goto l2;
			}
			mapIndex = destPix1;
			goto l2;
		}
	l2:	/* end rgbMap:from:to: */;
		longAtput(((((char *) colorMap)) + 4) + (mapIndex << 2), (longAt(((((char *) colorMap)) + 4) + (mapIndex << 2))) + 1);
	} else {
		/* begin rgbMap:from:to: */
		if ((d2 = cmBitsPerColor - 8) > 0) {
			mask4 = (1 << 8) - 1;
			srcPix2 = destinationWord << d2;
			mask4 = mask4 << d2;
			destPix2 = srcPix2 & mask4;
			mask4 = mask4 << cmBitsPerColor;
			srcPix2 = srcPix2 << d2;
			mapIndex = (destPix2 + (srcPix2 & mask4)) + ((srcPix2 << d2) & (mask4 << cmBitsPerColor));
			goto l3;
		} else {
			if (d2 == 0) {
				mapIndex = destinationWord;
				goto l3;
			}
			if (destinationWord == 0) {
				mapIndex = destinationWord;
				goto l3;
			}
			d2 = 8 - cmBitsPerColor;
			mask4 = (1 << cmBitsPerColor) - 1;
			srcPix2 = ((unsigned) destinationWord) >> d2;
			destPix2 = srcPix2 & mask4;
			mask4 = mask4 << cmBitsPerColor;
			srcPix2 = ((unsigned) srcPix2) >> d2;
			destPix2 = (destPix2 + (srcPix2 & mask4)) + ((((unsigned) srcPix2) >> d2) & (mask4 << cmBitsPerColor));
			if (destPix2 == 0) {
				mapIndex = 1;
				goto l3;
			}
			mapIndex = destPix2;
			goto l3;
		}
	l3:	/* end rgbMap:from:to: */;
		longAtput(((((char *) colorMap)) + 4) + (mapIndex << 2), (longAt(((((char *) colorMap)) + 4) + (mapIndex << 2))) + 1);
	}
	return destinationWord;
}

int aComment(void) {
}

int accessibleObjectAfter(int oop) {
    int obj;
    int sz;
    int header;
    int extra;
    int type;
    int extra1;
    int sz1;
    int header1;
    int extra2;
    int type1;
    int extra11;

	/* begin objectAfter: */
	if (checkAssertions) {
		if (oop >= endOfMemory) {
			error("no objects after the end of memory");
		}
	}
	if (((longAt(oop)) & 3) == 2) {
		sz1 = (longAt(oop)) & 536870908;
	} else {
		/* begin sizeBitsOf: */
		header1 = longAt(oop);
		if ((header1 & 3) == 0) {
			sz1 = (longAt(oop - 8)) & 4294967292U;
			goto l2;
		} else {
			sz1 = header1 & 252;
			goto l2;
		}
	l2:	/* end sizeBitsOf: */;
	}
	/* begin oopFromChunk: */
	/* begin extraHeaderBytes: */
	type1 = (longAt(oop + sz1)) & 3;
	if (type1 > 1) {
		extra11 = 0;
	} else {
		if (type1 == 1) {
			extra11 = 4;
		} else {
			extra11 = 8;
		}
	}
	extra2 = extra11;
	obj = (oop + sz1) + extra2;
	while (obj < endOfMemory) {
		if (!(((longAt(obj)) & 3) == 2)) {
			return obj;
		}
		/* begin objectAfter: */
		if (checkAssertions) {
			if (obj >= endOfMemory) {
				error("no objects after the end of memory");
			}
		}
		if (((longAt(obj)) & 3) == 2) {
			sz = (longAt(obj)) & 536870908;
		} else {
			/* begin sizeBitsOf: */
			header = longAt(obj);
			if ((header & 3) == 0) {
				sz = (longAt(obj - 8)) & 4294967292U;
				goto l1;
			} else {
				sz = header & 252;
				goto l1;
			}
		l1:	/* end sizeBitsOf: */;
		}
		/* begin oopFromChunk: */
		/* begin extraHeaderBytes: */
		type = (longAt(obj + sz)) & 3;
		if (type > 1) {
			extra1 = 0;
		} else {
			if (type == 1) {
				extra1 = 4;
			} else {
				extra1 = 8;
			}
		}
		extra = extra1;
		obj = (obj + sz) + extra;
	}
	return null;
}

int activateNewMethod(void) {
    int methodHeader;
    int smallContext;
    char * toIndex;
    int nilOop;
    int tempCount;
    int newContext;
    int initialIP;
    char * fromIndex;
    char * lastIndex;
    int cntxt;
    int tmp;

	methodHeader = longAt(((((char *) newMethod)) + 4) + (0 << 2));
	smallContext = ((((unsigned) methodHeader) >> 18) & 1) == 0;
	/* begin allocateOrRecycleContext: */
	if (smallContext) {
		if (freeSmallContexts != 1) {
			cntxt = freeSmallContexts;
			freeSmallContexts = longAt(((((char *) cntxt)) + 4) + (0 << 2));
		} else {
			cntxt = instantiateSmallClasssizeInBytesfill(longAt(((((char *) specialObjectsOop)) + 4) + (10 << 2)), 76, nilObj);
		}
	} else {
		if (freeLargeContexts != 1) {
			cntxt = freeLargeContexts;
			freeLargeContexts = longAt(((((char *) cntxt)) + 4) + (0 << 2));
		} else {
			cntxt = instantiateSmallClasssizeInBytesfill(longAt(((((char *) specialObjectsOop)) + 4) + (10 << 2)), 156, nilObj);
		}
	}
	newContext = cntxt;
	initialIP = ((1 + ((((unsigned) methodHeader) >> 10) & 255)) * 4) + 1;
	tempCount = (((unsigned) methodHeader) >> 19) & 63;
	longAtput(((((char *) newContext)) + 4) + (0 << 2), activeContext);
	longAtput(((((char *) newContext)) + 4) + (1 << 2), ((initialIP << 1) | 1));
	longAtput(((((char *) newContext)) + 4) + (2 << 2), ((tempCount << 1) | 1));
	longAtput(((((char *) newContext)) + 4) + (3 << 2), newMethod);
	fromIndex = (((char *) activeContext)) + (((((unsigned) ((stackPointer - activeContext) - 4)) >> 2) - argumentCount) * 4);
	toIndex = (((char *) newContext)) + (5 * 4);
	lastIndex = fromIndex + ((argumentCount + 1) * 4);
	while (fromIndex < lastIndex) {
		fromIndex += 4;
		toIndex += 4;
		longAtput(toIndex, longAt(fromIndex));
	}
	nilOop = nilObj;
	if (smallContext) {
		lastIndex = ((((char *) newContext)) + 76) - 4;
	} else {
		lastIndex = ((((char *) newContext)) + 156) - 4;
	}
	while (toIndex < lastIndex) {
		toIndex += 4;
		longAtput(toIndex, nilOop);
	}
	/* begin pop: */
	stackPointer -= (argumentCount + 1) * 4;
	reclaimableContextCount += 1;
	/* begin newActiveContext: */
	/* begin storeContextRegisters: */
	longAtput(((((char *) activeContext)) + 4) + (1 << 2), ((((instructionPointer - method) - (4 - 2)) << 1) | 1));
	longAtput(((((char *) activeContext)) + 4) + (2 << 2), (((((((unsigned) ((stackPointer - activeContext) - 4)) >> 2) - 6) + 1) << 1) | 1));
	if (newContext < youngStart) {
		beRootIfOld(newContext);
	}
	activeContext = newContext;
	/* begin fetchContextRegisters: */
	tmp = longAt(((((char *) newContext)) + 4) + (3 << 2));
	if ((tmp & 1)) {
		tmp = longAt(((((char *) newContext)) + 4) + (5 << 2));
		if (tmp < youngStart) {
			beRootIfOld(tmp);
		}
	} else {
		tmp = newContext;
	}
	theHomeContext = tmp;
	receiver = longAt(((((char *) tmp)) + 4) + (5 << 2));
	method = longAt(((((char *) tmp)) + 4) + (3 << 2));
	tmp = ((longAt(((((char *) newContext)) + 4) + (1 << 2))) >> 1);
	instructionPointer = ((method + tmp) + 4) - 2;
	tmp = ((longAt(((((char *) newContext)) + 4) + (2 << 2))) >> 1);
	stackPointer = (newContext + 4) + (((6 + tmp) - 1) * 4);
}

int addLastLinktoList(int proc, int aList) {
    int lastLink;

	if ((longAt(((((char *) aList)) + 4) + (0 << 2))) == nilObj) {
		/* begin storePointer:ofObject:withValue: */
		if (aList < youngStart) {
			possibleRootStoreIntovalue(aList, proc);
		}
		longAtput(((((char *) aList)) + 4) + (0 << 2), proc);
	} else {
		lastLink = longAt(((((char *) aList)) + 4) + (1 << 2));
		/* begin storePointer:ofObject:withValue: */
		if (lastLink < youngStart) {
			possibleRootStoreIntovalue(lastLink, proc);
		}
		longAtput(((((char *) lastLink)) + 4) + (0 << 2), proc);
	}
	/* begin storePointer:ofObject:withValue: */
	if (aList < youngStart) {
		possibleRootStoreIntovalue(aList, proc);
	}
	longAtput(((((char *) aList)) + 4) + (1 << 2), proc);
	/* begin storePointer:ofObject:withValue: */
	if (proc < youngStart) {
		possibleRootStoreIntovalue(proc, aList);
	}
	longAtput(((((char *) proc)) + 4) + (3 << 2), aList);
}

int addToMethodCacheSelclassmethodprimIndex(int selector, int class, int meth, int primIndex) {
    int probe;

	mcProbe = (mcProbe + 1) % 3;
	probe = ((((unsigned) (selector ^ class)) >> (mcProbe + 2)) & 511) + 1;
	methodCache[probe] = selector;
	methodCache[probe + 512] = class;
	methodCache[probe + (512 * 2)] = meth;
	methodCache[probe + (512 * 3)] = primIndex;
}

int addWordwith(int sourceWord, int destinationWord) {
	return sourceWord + destinationWord;
}

int adjustAllOopsBy(int bytesToShift) {
    int oop;
    int last;
    int newClassOop;
    int fieldAddr;
    int fieldOop;
    int classHeader;
    int chunk;
    int extra;
    int type;
    int extra1;
    int sz;
    int header;
    int extra2;
    int type1;
    int extra11;

	if (bytesToShift == 0) {
		return null;
	}
	/* begin oopFromChunk: */
	chunk = startOfMemory();
	/* begin extraHeaderBytes: */
	type = (longAt(chunk)) & 3;
	if (type > 1) {
		extra1 = 0;
	} else {
		if (type == 1) {
			extra1 = 4;
		} else {
			extra1 = 8;
		}
	}
	extra = extra1;
	oop = chunk + extra;
	while (oop < endOfMemory) {
		if (!(((longAt(oop)) & 3) == 2)) {
			/* begin adjustFieldsAndClassOf:by: */
			fieldAddr = oop + (lastPointerOf(oop));
			while (fieldAddr > oop) {
				fieldOop = longAt(fieldAddr);
				if (!((fieldOop & 1))) {
					longAtput(fieldAddr, fieldOop + bytesToShift);
				}
				fieldAddr -= 4;
			}
			if (((longAt(oop)) & 3) != 3) {
				classHeader = longAt(oop - 4);
				newClassOop = (classHeader & 4294967292U) + bytesToShift;
				longAtput(oop - 4, newClassOop | (classHeader & 3));
			}
		}
		last = oop;
		/* begin objectAfter: */
		if (checkAssertions) {
			if (oop >= endOfMemory) {
				error("no objects after the end of memory");
			}
		}
		if (((longAt(oop)) & 3) == 2) {
			sz = (longAt(oop)) & 536870908;
		} else {
			/* begin sizeBitsOf: */
			header = longAt(oop);
			if ((header & 3) == 0) {
				sz = (longAt(oop - 8)) & 4294967292U;
				goto l1;
			} else {
				sz = header & 252;
				goto l1;
			}
		l1:	/* end sizeBitsOf: */;
		}
		/* begin oopFromChunk: */
		/* begin extraHeaderBytes: */
		type1 = (longAt(oop + sz)) & 3;
		if (type1 > 1) {
			extra11 = 0;
		} else {
			if (type1 == 1) {
				extra11 = 4;
			} else {
				extra11 = 8;
			}
		}
		extra2 = extra11;
		oop = (oop + sz) + extra2;
	}
}

int adjustFieldsAndClassOfby(int oop, int offsetBytes) {
    int newClassOop;
    int fieldAddr;
    int fieldOop;
    int classHeader;

	fieldAddr = oop + (lastPointerOf(oop));
	while (fieldAddr > oop) {
		fieldOop = longAt(fieldAddr);
		if (!((fieldOop & 1))) {
			longAtput(fieldAddr, fieldOop + offsetBytes);
		}
		fieldAddr -= 4;
	}
	if (((longAt(oop)) & 3) != 3) {
		classHeader = longAt(oop - 4);
		newClassOop = (classHeader & 4294967292U) + offsetBytes;
		longAtput(oop - 4, newClassOop | (classHeader & 3));
	}
}

int affectedBottom(void) {
	return affectedB;
}

int affectedLeft(void) {
	return affectedL;
}

int affectedRight(void) {
	return affectedR;
}

int affectedTop(void) {
	return affectedT;
}

int allAccessibleObjectsOkay(void) {
    int oop;
    int obj;
    int chunk;
    int extra;
    int type;
    int extra1;
    int sz;
    int header;
    int extra2;
    int type1;
    int extra11;

	/* begin firstAccessibleObject */
	/* begin oopFromChunk: */
	chunk = startOfMemory();
	/* begin extraHeaderBytes: */
	type = (longAt(chunk)) & 3;
	if (type > 1) {
		extra1 = 0;
	} else {
		if (type == 1) {
			extra1 = 4;
		} else {
			extra1 = 8;
		}
	}
	extra = extra1;
	obj = chunk + extra;
	while (obj < endOfMemory) {
		if (!(((longAt(obj)) & 3) == 2)) {
			oop = obj;
			goto l2;
		}
		/* begin objectAfter: */
		if (checkAssertions) {
			if (obj >= endOfMemory) {
				error("no objects after the end of memory");
			}
		}
		if (((longAt(obj)) & 3) == 2) {
			sz = (longAt(obj)) & 536870908;
		} else {
			/* begin sizeBitsOf: */
			header = longAt(obj);
			if ((header & 3) == 0) {
				sz = (longAt(obj - 8)) & 4294967292U;
				goto l1;
			} else {
				sz = header & 252;
				goto l1;
			}
		l1:	/* end sizeBitsOf: */;
		}
		/* begin oopFromChunk: */
		/* begin extraHeaderBytes: */
		type1 = (longAt(obj + sz)) & 3;
		if (type1 > 1) {
			extra11 = 0;
		} else {
			if (type1 == 1) {
				extra11 = 4;
			} else {
				extra11 = 8;
			}
		}
		extra2 = extra11;
		obj = (obj + sz) + extra2;
	}
	error("heap is empty");
l2:	/* end firstAccessibleObject */;
	while (!(oop == null)) {
		okayFields(oop);
		oop = accessibleObjectAfter(oop);
	}
}

int allYoungand(int array1, int array2) {
    int fieldOffset;
    int methodHeader;
    int sz;
    int fmt;
    int header;
    int type;

	if (array1 < youngStart) {
		return false;
	}
	if (array2 < youngStart) {
		return false;
	}
	/* begin lastPointerOf: */
	fmt = (((unsigned) (longAt(array1))) >> 8) & 15;
	if (fmt < 4) {
		/* begin sizeBitsOfSafe: */
		header = longAt(array1);
		/* begin rightType: */
		if ((header & 252) == 0) {
			type = 0;
			goto l2;
		} else {
			if ((header & 126976) == 0) {
				type = 1;
				goto l2;
			} else {
				type = 3;
				goto l2;
			}
		}
	l2:	/* end rightType: */;
		if (type == 0) {
			sz = (longAt(array1 - 8)) & 4294967292U;
			goto l3;
		} else {
			sz = header & 252;
			goto l3;
		}
	l3:	/* end sizeBitsOfSafe: */;
		fieldOffset = sz - 4;
		goto l1;
	}
	if (fmt < 12) {
		fieldOffset = 0;
		goto l1;
	}
	methodHeader = longAt(array1 + 4);
	fieldOffset = (((((unsigned) methodHeader) >> 10) & 255) * 4) + 4;
l1:	/* end lastPointerOf: */;
	while (fieldOffset >= 4) {
		if ((longAt(array1 + fieldOffset)) < youngStart) {
			return false;
		}
		if ((longAt(array2 + fieldOffset)) < youngStart) {
			return false;
		}
		fieldOffset -= 4;
	}
	return true;
}

int allocateheaderSizeh1h2h3fill(int byteSize, int hdrSize, int baseHeader, int classOop, int extendedSize, int fillWord) {
    int i;
    int newObj;
    int remappedClassOop;
    int end;
    int oop;
    int newFreeSize;
    int enoughSpace;
    int newChunk;
    int minFree;

	if (hdrSize > 1) {
		/* begin pushRemappableOop: */
		remapBuffer[remapBufferCount += 1] = classOop;
	}
	/* begin allocateChunk: */
	if (allocationCount >= allocationsBetweenGCs) {
		incrementalGC();
	}
	/* begin sufficientSpaceToAllocate: */
	minFree = (lowSpaceThreshold + (byteSize + ((hdrSize - 1) * 4))) + 4;
	if (((longAt(freeBlock)) & 536870908) >= minFree) {
		enoughSpace = true;
		goto l1;
	} else {
		enoughSpace = sufficientSpaceAfterGC(minFree);
		goto l1;
	}
l1:	/* end sufficientSpaceToAllocate: */;
	if (!(enoughSpace)) {
		signalLowSpace = true;
		lowSpaceThreshold = 0;
		interruptCheckCounter = 0;
	}
	if (((longAt(freeBlock)) & 536870908) < ((byteSize + ((hdrSize - 1) * 4)) + 4)) {
		error("out of memory");
	}
	newFreeSize = ((longAt(freeBlock)) & 536870908) - (byteSize + ((hdrSize - 1) * 4));
	newChunk = freeBlock;
	freeBlock += byteSize + ((hdrSize - 1) * 4);
	/* begin setSizeOfFree:to: */
	longAtput(freeBlock, (newFreeSize & 536870908) | 2);
	allocationCount += 1;
	newObj = newChunk;
	if (hdrSize > 1) {
		/* begin popRemappableOop */
		oop = remapBuffer[remapBufferCount];
		remapBufferCount -= 1;
		remappedClassOop = oop;
	}
	if (hdrSize == 3) {
		longAtput(newObj, extendedSize | 0);
		longAtput(newObj + 4, remappedClassOop | 0);
		longAtput(newObj + 8, baseHeader | 0);
		newObj += 8;
	}
	if (hdrSize == 2) {
		longAtput(newObj, remappedClassOop | 1);
		longAtput(newObj + 4, baseHeader | 1);
		newObj += 4;
	}
	if (hdrSize == 1) {
		longAtput(newObj, baseHeader | 3);
	}
	end = newObj + byteSize;
	i = newObj + 4;
	while (i < end) {
		longAtput(i, fillWord);
		i += 4;
	}
	if (checkAssertions) {
		okayOop(newObj);
		oopHasOkayClass(newObj);
		if (!((objectAfter(newObj)) == freeBlock)) {
			error("allocate bug: did not set header of new oop correctly");
		}
		if (!((objectAfter(freeBlock)) == endOfMemory)) {
			error("allocate bug: did not set header of freeBlock correctly");
		}
	}
	return newObj;
}

int allocateChunk(int byteSize) {
    int newFreeSize;
    int enoughSpace;
    int newChunk;
    int minFree;

	if (allocationCount >= allocationsBetweenGCs) {
		incrementalGC();
	}
	/* begin sufficientSpaceToAllocate: */
	minFree = (lowSpaceThreshold + byteSize) + 4;
	if (((longAt(freeBlock)) & 536870908) >= minFree) {
		enoughSpace = true;
		goto l1;
	} else {
		enoughSpace = sufficientSpaceAfterGC(minFree);
		goto l1;
	}
l1:	/* end sufficientSpaceToAllocate: */;
	if (!(enoughSpace)) {
		signalLowSpace = true;
		lowSpaceThreshold = 0;
		interruptCheckCounter = 0;
	}
	if (((longAt(freeBlock)) & 536870908) < (byteSize + 4)) {
		error("out of memory");
	}
	newFreeSize = ((longAt(freeBlock)) & 536870908) - byteSize;
	newChunk = freeBlock;
	freeBlock += byteSize;
	/* begin setSizeOfFree:to: */
	longAtput(freeBlock, (newFreeSize & 536870908) | 2);
	allocationCount += 1;
	return newChunk;
}

int allocateOrRecycleContext(int smallContextWanted) {
    int cntxt;

	if (smallContextWanted) {
		if (freeSmallContexts != 1) {
			cntxt = freeSmallContexts;
			freeSmallContexts = longAt(((((char *) cntxt)) + 4) + (0 << 2));
		} else {
			cntxt = instantiateSmallClasssizeInBytesfill(longAt(((((char *) specialObjectsOop)) + 4) + (10 << 2)), 76, nilObj);
		}
	} else {
		if (freeLargeContexts != 1) {
			cntxt = freeLargeContexts;
			freeLargeContexts = longAt(((((char *) cntxt)) + 4) + (0 << 2));
		} else {
			cntxt = instantiateSmallClasssizeInBytesfill(longAt(((((char *) specialObjectsOop)) + 4) + (10 << 2)), 156, nilObj);
		}
	}
	return cntxt;
}

int alphaBlendwith(int sourceWord, int destinationWord) {
    int shift;
    int alpha;
    int i;
    int blend;
    int unAlpha;
    int result;
    int colorMask;

	alpha = ((unsigned) sourceWord) >> 24;
	unAlpha = 255 - alpha;
	colorMask = 255;
	result = 0;
	for (i = 1; i <= 3; i += 1) {
		shift = (i - 1) * 8;
		blend = ((((((((unsigned) sourceWord) >> shift) & colorMask) * alpha) + (((((unsigned) destinationWord) >> shift) & colorMask) * unAlpha)) + 254) / 255) & colorMask;
		result = result | (blend << shift);
	}
	return result;
}

int alphaBlendConstwith(int sourceWord, int destinationWord) {
	return alphaBlendConstwithpaintMode(sourceWord, destinationWord, false);
}

int alphaBlendConstwithpaintMode(int sourceWord, int destinationWord, int paintMode) {
    int j;
    int destPixVal;
    int pixMask;
    int destShifted;
    int sourceShifted;
    int sourcePixVal;
    int pixBlend;
    int shift;
    int blend;
    int maskShifted;
    int bitsPerColor;
    int i;
    int unAlpha;
    int result;
    int rgbMask;

	if (destPixSize < 16) {
		return destinationWord;
	}
	unAlpha = 255 - sourceAlpha;
	pixMask = (1 << destPixSize) - 1;
	if (destPixSize == 16) {
		bitsPerColor = 5;
	} else {
		bitsPerColor = 8;
	}
	rgbMask = (1 << bitsPerColor) - 1;
	maskShifted = destMask;
	destShifted = destinationWord;
	sourceShifted = sourceWord;
	result = destinationWord;
	for (j = 1; j <= pixPerWord; j += 1) {
		sourcePixVal = sourceShifted & pixMask;
		if (!(((maskShifted & pixMask) == 0) || (paintMode && (sourcePixVal == 0)))) {
			destPixVal = destShifted & pixMask;
			pixBlend = 0;
			for (i = 1; i <= 3; i += 1) {
				shift = (i - 1) * bitsPerColor;
				blend = ((((((((unsigned) sourcePixVal) >> shift) & rgbMask) * sourceAlpha) + (((((unsigned) destPixVal) >> shift) & rgbMask) * unAlpha)) + 254) / 255) & rgbMask;
				pixBlend = pixBlend | (blend << shift);
			}
			if (destPixSize == 16) {
				result = (result & (~(pixMask << ((j - 1) * 16)))) | (pixBlend << ((j - 1) * 16));
			} else {
				result = pixBlend;
			}
		}
		maskShifted = ((unsigned) maskShifted) >> destPixSize;
		sourceShifted = ((unsigned) sourceShifted) >> destPixSize;
		destShifted = ((unsigned) destShifted) >> destPixSize;
	}
	return result;
}

int alphaPaintConstwith(int sourceWord, int destinationWord) {
	if (sourceWord == 0) {
		return destinationWord;
	}
	return alphaBlendConstwithpaintMode(sourceWord, destinationWord, true);
}

int areIntegersand(int oop1, int oop2) {
	return ((oop1 & oop2) & 1) != 0;
}

int argCount(void) {
	return argumentCount;
}

int argumentCountOf(int methodPointer) {
	return (((unsigned) (longAt(((((char *) methodPointer)) + 4) + (0 << 2)))) >> 25) & 31;
}

int argumentCountOfBlock(int blockPointer) {
    int argCount;

	argCount = longAt(((((char *) blockPointer)) + 4) + (3 << 2));
	if ((argCount & 1)) {
		return (argCount >> 1);
	} else {
		primitiveFail();
		return 0;
	}
}

void * arrayValueOf(int arrayOop) {
	if ((!((arrayOop & 1))) && (isWordsOrBytes(arrayOop))) {
		return (void *) (arrayOop + 4);
	}
	primitiveFail();
}

int asciiDirectoryDelimiter(void) {
	return dir_Delimitor();
}

int asciiOfCharacter(int characterObj) {
    int ccIndex;
    int cl;

	/* begin assertClassOf:is: */
	if ((characterObj & 1)) {
		successFlag = false;
		goto l1;
	}
	ccIndex = (((unsigned) (longAt(characterObj))) >> 12) & 31;
	if (ccIndex == 0) {
		cl = (longAt(characterObj - 4)) & 4294967292U;
	} else {
		cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
	}
	/* begin success: */
	successFlag = (cl == (longAt(((((char *) specialObjectsOop)) + 4) + (19 << 2)))) && successFlag;
l1:	/* end assertClassOf:is: */;
	if (successFlag) {
		return longAt(((((char *) characterObj)) + 4) + (0 << 2));
	} else {
		return 1;
	}
}

int assertClassOfis(int oop, int classOop) {
    int ccIndex;
    int cl;

	if ((oop & 1)) {
		successFlag = false;
		return null;
	}
	ccIndex = (((unsigned) (longAt(oop))) >> 12) & 31;
	if (ccIndex == 0) {
		cl = (longAt(oop - 4)) & 4294967292U;
	} else {
		cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
	}
	/* begin success: */
	successFlag = (cl == classOop) && successFlag;
}

int assertFloatand(int oop1, int oop2) {
    int floatClass;
    int ccIndex;
    int cl;
    int ccIndex1;
    int cl1;

	if (((oop1 | oop2) & 1) != 0) {
		successFlag = false;
	} else {
		floatClass = longAt(((((char *) specialObjectsOop)) + 4) + (9 << 2));
		/* begin assertClassOf:is: */
		if ((oop1 & 1)) {
			successFlag = false;
			goto l1;
		}
		ccIndex = (((unsigned) (longAt(oop1))) >> 12) & 31;
		if (ccIndex == 0) {
			cl = (longAt(oop1 - 4)) & 4294967292U;
		} else {
			cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl == floatClass) && successFlag;
	l1:	/* end assertClassOf:is: */;
		/* begin assertClassOf:is: */
		if ((oop2 & 1)) {
			successFlag = false;
			goto l2;
		}
		ccIndex1 = (((unsigned) (longAt(oop2))) >> 12) & 31;
		if (ccIndex1 == 0) {
			cl1 = (longAt(oop2 - 4)) & 4294967292U;
		} else {
			cl1 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex1 - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl1 == floatClass) && successFlag;
	l2:	/* end assertClassOf:is: */;
	}
}

AsyncFile * asyncFileValueOf(int oop) {
    int successValue;

	/* begin success: */
	successValue = (!((oop & 1))) && ((((((unsigned) (longAt(oop))) >> 8) & 15) >= 8) && ((lengthOf(oop)) == (sizeof(AsyncFile))));
	successFlag = successValue && successFlag;
	if (!(successFlag)) {
		return null;
	}
	return (AsyncFile *) (oop + 4);
}

int baseHeader(int oop) {
	return longAt(oop);
}

int beRootIfOld(int oop) {
    int header;

	if ((oop < youngStart) && (!((oop & 1)))) {
		header = longAt(oop);
		if ((header & 1073741824) == 0) {
			if (rootTableCount < 1000) {
				rootTableCount += 1;
				rootTable[rootTableCount] = oop;
				longAtput(oop, header | 1073741824);
			}
		}
	}
}

int beRootWhileForwarding(int oop) {
    int fwdBlock;
    int forwarding;
    int header;
    int newHeader;

	header = longAt(oop);
	if ((header & 2147483648U) != 0) {
		forwarding = true;
		fwdBlock = header & 2147483644;
		if (checkAssertions) {
			/* begin fwdBlockValidate: */
			if (!((fwdBlock > endOfMemory) && ((fwdBlock <= fwdTableNext) && ((fwdBlock & 3) == 0)))) {
				error("invalid fwd table entry");
			}
		}
		header = longAt(fwdBlock + 4);
	} else {
		forwarding = false;
	}
	if ((header & 1073741824) == 0) {
		if (rootTableCount < 1000) {
			rootTableCount += 1;
			rootTable[rootTableCount] = oop;
			newHeader = header | 1073741824;
			if (forwarding) {
				longAtput(fwdBlock + 4, newHeader);
			} else {
				longAtput(oop, newHeader);
			}
		}
	}
}

int becomewith(int array1, int array2) {
    int fieldOffset;
    int oop1;
    int oop2;
    int hdr1;
    int hdr2;
    int fwdBlock;
    int fwdHeader;
    int fwdBlock1;
    int fwdHeader1;
    int methodHeader;
    int sz;
    int fmt;
    int header;
    int type;

	if (!((fetchClassOf(array1)) == (longAt(((((char *) specialObjectsOop)) + 4) + (7 << 2))))) {
		return false;
	}
	if (!((fetchClassOf(array2)) == (longAt(((((char *) specialObjectsOop)) + 4) + (7 << 2))))) {
		return false;
	}
	if (!((lastPointerOf(array1)) == (lastPointerOf(array2)))) {
		return false;
	}
	if (!(containOnlyOopsand(array1, array2))) {
		return false;
	}
	if (!(prepareForwardingTableForBecomingwith(array1, array2))) {
		return false;
	}
	if (allYoungand(array1, array2)) {
		mapPointersInObjectsFromto(youngStart, endOfMemory);
	} else {
		mapPointersInObjectsFromto(startOfMemory(), endOfMemory);
	}
	/* begin restoreHeadersAfterBecoming:with: */
	/* begin lastPointerOf: */
	fmt = (((unsigned) (longAt(array1))) >> 8) & 15;
	if (fmt < 4) {
		/* begin sizeBitsOfSafe: */
		header = longAt(array1);
		/* begin rightType: */
		if ((header & 252) == 0) {
			type = 0;
			goto l2;
		} else {
			if ((header & 126976) == 0) {
				type = 1;
				goto l2;
			} else {
				type = 3;
				goto l2;
			}
		}
	l2:	/* end rightType: */;
		if (type == 0) {
			sz = (longAt(array1 - 8)) & 4294967292U;
			goto l3;
		} else {
			sz = header & 252;
			goto l3;
		}
	l3:	/* end sizeBitsOfSafe: */;
		fieldOffset = sz - 4;
		goto l1;
	}
	if (fmt < 12) {
		fieldOffset = 0;
		goto l1;
	}
	methodHeader = longAt(array1 + 4);
	fieldOffset = (((((unsigned) methodHeader) >> 10) & 255) * 4) + 4;
l1:	/* end lastPointerOf: */;
	while (fieldOffset >= 4) {
		oop1 = longAt(array1 + fieldOffset);
		oop2 = longAt(array2 + fieldOffset);
		/* begin restoreHeaderOf: */
		fwdHeader = longAt(oop1);
		fwdBlock = fwdHeader & 2147483644;
		if (checkAssertions) {
			if ((fwdHeader & 2147483648U) == 0) {
				error("attempting to restore the header of an object that has no forwarding block");
			}
			/* begin fwdBlockValidate: */
			if (!((fwdBlock > endOfMemory) && ((fwdBlock <= fwdTableNext) && ((fwdBlock & 3) == 0)))) {
				error("invalid fwd table entry");
			}
		}
		longAtput(oop1, longAt(fwdBlock + 4));
		/* begin restoreHeaderOf: */
		fwdHeader1 = longAt(oop2);
		fwdBlock1 = fwdHeader1 & 2147483644;
		if (checkAssertions) {
			if ((fwdHeader1 & 2147483648U) == 0) {
				error("attempting to restore the header of an object that has no forwarding block");
			}
			/* begin fwdBlockValidate: */
			if (!((fwdBlock1 > endOfMemory) && ((fwdBlock1 <= fwdTableNext) && ((fwdBlock1 & 3) == 0)))) {
				error("invalid fwd table entry");
			}
		}
		longAtput(oop2, longAt(fwdBlock1 + 4));
		/* begin exchangeHashBits:with: */
		hdr1 = longAt(oop1);
		hdr2 = longAt(oop2);
		longAtput(oop1, (hdr1 & 3758227455U) | (hdr2 & 536739840));
		longAtput(oop2, (hdr2 & 3758227455U) | (hdr1 & 536739840));
		fieldOffset -= 4;
	}
	initializeMemoryFirstFree(freeBlock);
	return true;
}

int bitAndwith(int sourceWord, int destinationWord) {
	return sourceWord & destinationWord;
}

int bitAndInvertwith(int sourceWord, int destinationWord) {
	return sourceWord & (~destinationWord);
}

int bitInvertAndwith(int sourceWord, int destinationWord) {
	return (~sourceWord) & destinationWord;
}

int bitInvertAndInvertwith(int sourceWord, int destinationWord) {
	return (~sourceWord) & (~destinationWord);
}

int bitInvertDestinationwith(int sourceWord, int destinationWord) {
	return ~destinationWord;
}

int bitInvertOrwith(int sourceWord, int destinationWord) {
	return (~sourceWord) | destinationWord;
}

int bitInvertOrInvertwith(int sourceWord, int destinationWord) {
	return (~sourceWord) | (~destinationWord);
}

int bitInvertSourcewith(int sourceWord, int destinationWord) {
	return ~sourceWord;
}

int bitInvertXorwith(int sourceWord, int destinationWord) {
	return (~sourceWord) ^ destinationWord;
}

int bitOrwith(int sourceWord, int destinationWord) {
	return sourceWord | destinationWord;
}

int bitOrInvertwith(int sourceWord, int destinationWord) {
	return sourceWord | (~destinationWord);
}

int bitXorwith(int sourceWord, int destinationWord) {
	return sourceWord ^ destinationWord;
}

int booleanValueOf(int obj) {
	if (obj == trueObj) {
		return true;
	}
	if (obj == falseObj) {
		return false;
	}
	successFlag = false;
	return null;
}

int byteLengthOf(int oop) {
    int sz;
    int header;
    int fmt;

	header = longAt(oop);
	if ((header & 3) == 0) {
		sz = (longAt(oop - 8)) & 4294967292U;
	} else {
		sz = header & 252;
	}
	fmt = (((unsigned) header) >> 8) & 15;
	if (fmt < 8) {
		return sz - 4;
	} else {
		return (sz - 4) - (fmt & 3);
	}
}

int byteSwapByteObjects(void) {
    int methodHeader;
    int wordAddr;
    int oop;
    int fmt;
    int stopAddr;
    int addr;
    int chunk;
    int extra;
    int type;
    int extra1;
    int sz;
    int header;
    int extra2;
    int type1;
    int extra11;

	/* begin oopFromChunk: */
	chunk = startOfMemory();
	/* begin extraHeaderBytes: */
	type = (longAt(chunk)) & 3;
	if (type > 1) {
		extra1 = 0;
	} else {
		if (type == 1) {
			extra1 = 4;
		} else {
			extra1 = 8;
		}
	}
	extra = extra1;
	oop = chunk + extra;
	while (oop < endOfMemory) {
		if (!(((longAt(oop)) & 3) == 2)) {
			fmt = (((unsigned) (longAt(oop))) >> 8) & 15;
			if (fmt >= 8) {
				wordAddr = oop + 4;
				if (fmt >= 12) {
					methodHeader = longAt(oop + 4);
					wordAddr = (wordAddr + 4) + (((((unsigned) methodHeader) >> 10) & 255) * 4);
				}
				/* begin reverseBytesFrom:to: */
				stopAddr = oop + (sizeBitsOf(oop));
				addr = wordAddr;
				while (addr < stopAddr) {
					longAtput(addr, ((((((unsigned) (longAt(addr)) >> 24)) & 255) + ((((unsigned) (longAt(addr)) >> 8)) & 65280)) + ((((unsigned) (longAt(addr)) << 8)) & 16711680)) + ((((unsigned) (longAt(addr)) << 24)) & 4278190080U));
					addr += 4;
				}
			}
		}
		/* begin objectAfter: */
		if (checkAssertions) {
			if (oop >= endOfMemory) {
				error("no objects after the end of memory");
			}
		}
		if (((longAt(oop)) & 3) == 2) {
			sz = (longAt(oop)) & 536870908;
		} else {
			/* begin sizeBitsOf: */
			header = longAt(oop);
			if ((header & 3) == 0) {
				sz = (longAt(oop - 8)) & 4294967292U;
				goto l1;
			} else {
				sz = header & 252;
				goto l1;
			}
		l1:	/* end sizeBitsOf: */;
		}
		/* begin oopFromChunk: */
		/* begin extraHeaderBytes: */
		type1 = (longAt(oop + sz)) & 3;
		if (type1 > 1) {
			extra11 = 0;
		} else {
			if (type1 == 1) {
				extra11 = 4;
			} else {
				extra11 = 8;
			}
		}
		extra2 = extra11;
		oop = (oop + sz) + extra2;
	}
}

int byteSwapped(int w) {
	return ((((((unsigned) w >> 24)) & 255) + ((((unsigned) w >> 8)) & 65280)) + ((((unsigned) w << 8)) & 16711680)) + ((((unsigned) w << 24)) & 4278190080U);
}

int caller(void) {
	return longAt(((((char *) activeContext)) + 4) + (0 << 2));
}

int characterForAscii(int integerObj) {
	return longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (24 << 2))))) + 4) + (((integerObj >> 1)) << 2));
}

int checkAddress(int byteAddress) {
	if (byteAddress < (startOfMemory())) {
		error("bad address: negative");
	}
	if (byteAddress >= memoryLimit) {
		error("bad address: past end of heap");
	}
}

int checkBooleanResultfrom(int result, int primIndex) {
    int sp;
    int sp1;

	if (successFlag) {
		/* begin pushBool: */
		if (result) {
			/* begin push: */
			longAtput(sp = stackPointer + 4, trueObj);
			stackPointer = sp;
		} else {
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, falseObj);
			stackPointer = sp1;
		}
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
		failSpecialPrim(primIndex);
	}
}

int checkForInterrupts(void) {
    int sema;
    int semaClass;
    int i;
    int now;
    int externalObjects;
    int index;

	interruptCheckCounter = 1000;
	now = (ioMSecs()) & 536870911;
	if (now < lastTick) {
		nextPollTick = now + (nextPollTick - lastTick);
		if (nextWakeupTick != 0) {
			nextWakeupTick = now + (nextWakeupTick - lastTick);
		}
	}
	lastTick = now;
	if (signalLowSpace) {
		signalLowSpace = false;
		sema = longAt(((((char *) specialObjectsOop)) + 4) + (17 << 2));
		if (!(sema == nilObj)) {
			synchronousSignal(sema);
		}
	}
	if (now >= nextPollTick) {
		ioProcessEvents();
		nextPollTick = now + 500;
	}
	if (interruptPending) {
		interruptPending = false;
		sema = longAt(((((char *) specialObjectsOop)) + 4) + (30 << 2));
		if (!(sema == nilObj)) {
			synchronousSignal(sema);
		}
	}
	if ((nextWakeupTick != 0) && (now >= nextWakeupTick)) {
		nextWakeupTick = 0;
		sema = longAt(((((char *) specialObjectsOop)) + 4) + (29 << 2));
		if (!(sema == nilObj)) {
			synchronousSignal(sema);
		}
	}
	if (semaphoresToSignalCount > 0) {
		externalObjects = longAt(((((char *) specialObjectsOop)) + 4) + (38 << 2));
		semaClass = longAt(((((char *) specialObjectsOop)) + 4) + (18 << 2));
		for (i = 1; i <= semaphoresToSignalCount; i += 1) {
			index = semaphoresToSignal[i];
			sema = longAt(((((char *) externalObjects)) + 4) + ((index - 1) << 2));
			if ((fetchClassOf(sema)) == semaClass) {
				synchronousSignal(sema);
			}
		}
		semaphoresToSignalCount = 0;
	}
}

int checkImageVersionFrom(sqImageFile f) {
    int version;
    int expectedVersion;
    int firstVersion;

	expectedVersion = 6502;
	sqImageFileSeek(f, 0);
	version = firstVersion = getLongFromFileswap(f, false);
	if (version == expectedVersion) {
		return false;
	}
	sqImageFileSeek(f, 0);
	version = getLongFromFileswap(f, true);
	if (version == expectedVersion) {
		return true;
	}
	sqImageFileSeek(f, 512);
	version = getLongFromFileswap(f, false);
	if (version == expectedVersion) {
		return false;
	}
	sqImageFileSeek(f, 512);
	version = getLongFromFileswap(f, true);
	if (version == expectedVersion) {
		return true;
	}
	print("This interpreter (vers. ");
	printNum(expectedVersion);
	print(" cannot read image file (vers. ");
	printNum(firstVersion);
	/* begin cr */
	printf("\n");
	ioExit();
}

int checkIntegerResultfrom(int integerResult, int primIndex) {
    int sp;

	if (successFlag && ((integerResult ^ (integerResult << 1)) >= 0)) {
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, ((integerResult << 1) | 1));
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
		failSpecialPrim(primIndex);
	}
}

int checkSourceOverlap(void) {
    int t;

	if ((sourceForm == destForm) && (dy >= sy)) {
		if (dy > sy) {
			vDir = -1;
			sy = (sy + bbH) - 1;
			dy = (dy + bbH) - 1;
		} else {
			if ((dy == sy) && (dx > sx)) {
				hDir = -1;
				sx = (sx + bbW) - 1;
				dx = (dx + bbW) - 1;
				if (nWords > 1) {
					t = mask1;
					mask1 = mask2;
					mask2 = t;
				}
			}
		}
		destIndex = (destBits + 4) + (((dy * destRaster) + (dx / pixPerWord)) * 4);
		destDelta = 4 * ((destRaster * vDir) - (nWords * hDir));
	}
}

int checkedByteAt(int byteAddress) {
	/* begin checkAddress: */
	if (byteAddress < (startOfMemory())) {
		error("bad address: negative");
	}
	if (byteAddress >= memoryLimit) {
		error("bad address: past end of heap");
	}
	return byteAt(byteAddress);
}

int checkedByteAtput(int byteAddress, int byte) {
	/* begin checkAddress: */
	if (byteAddress < (startOfMemory())) {
		error("bad address: negative");
	}
	if (byteAddress >= memoryLimit) {
		error("bad address: past end of heap");
	}
	byteAtput(byteAddress, byte);
}

int checkedIntegerValueOf(int intOop) {
	if ((intOop & 1)) {
		return (intOop >> 1);
	} else {
		primitiveFail();
		return 0;
	}
}

int checkedLongAt(int byteAddress) {
	/* begin checkAddress: */
	if (byteAddress < (startOfMemory())) {
		error("bad address: negative");
	}
	if (byteAddress >= memoryLimit) {
		error("bad address: past end of heap");
	}
	/* begin checkAddress: */
	if ((byteAddress + 3) < (startOfMemory())) {
		error("bad address: negative");
	}
	if ((byteAddress + 3) >= memoryLimit) {
		error("bad address: past end of heap");
	}
	return longAt(byteAddress);
}

int checkedLongAtput(int byteAddress, int a32BitInteger) {
	/* begin checkAddress: */
	if (byteAddress < (startOfMemory())) {
		error("bad address: negative");
	}
	if (byteAddress >= memoryLimit) {
		error("bad address: past end of heap");
	}
	/* begin checkAddress: */
	if ((byteAddress + 3) < (startOfMemory())) {
		error("bad address: negative");
	}
	if ((byteAddress + 3) >= memoryLimit) {
		error("bad address: past end of heap");
	}
	longAtput(byteAddress, a32BitInteger);
}

int chunkFromOop(int oop) {
    int extra;
    int type;
    int extra1;

	/* begin extraHeaderBytes: */
	type = (longAt(oop)) & 3;
	if (type > 1) {
		extra1 = 0;
	} else {
		if (type == 1) {
			extra1 = 4;
		} else {
			extra1 = 8;
		}
	}
	extra = extra1;
	return oop - extra;
}

int classHeader(int oop) {
	return longAt(oop - 4);
}

int clearRootsTable(void) {
    int oop;
    int i;

	for (i = 1; i <= rootTableCount; i += 1) {
		oop = rootTable[i];
		longAtput(oop, (longAt(oop)) & 3221225471U);
		rootTable[i] = 0;
	}
	rootTableCount = 0;
}

int clearWordwith(int source, int destination) {
	return 0;
}

int clipRange(void) {
	if (destX >= clipX) {
		sx = sourceX;
		dx = destX;
		bbW = width;
	} else {
		sx = sourceX + (clipX - destX);
		bbW = width - (clipX - destX);
		dx = clipX;
	}
	if ((dx + bbW) > (clipX + clipWidth)) {
		bbW -= (dx + bbW) - (clipX + clipWidth);
	}
	if (destY >= clipY) {
		sy = sourceY;
		dy = destY;
		bbH = height;
	} else {
		sy = (sourceY + clipY) - destY;
		bbH = height - (clipY - destY);
		dy = clipY;
	}
	if ((dy + bbH) > (clipY + clipHeight)) {
		bbH -= (dy + bbH) - (clipY + clipHeight);
	}
	if (noSource) {
		return null;
	}
	if (sx < 0) {
		dx -= sx;
		bbW += sx;
		sx = 0;
	}
	if ((sx + bbW) > srcWidth) {
		bbW -= (sx + bbW) - srcWidth;
	}
	if (sy < 0) {
		dy -= sy;
		bbH += sy;
		sy = 0;
	}
	if ((sy + bbH) > srcHeight) {
		bbH -= (sy + bbH) - srcHeight;
	}
}

int clone(int oop) {
    int newOop;
    int header;
    int hash;
    int fromIndex;
    int lastFrom;
    int extraHdrBytes;
    int bytes;
    int remappedOop;
    int newChunk;
    int toIndex;
    int oop1;
    int type;
    int extra;
    int header1;
    int newFreeSize;
    int enoughSpace;
    int newChunk1;
    int minFree;

	/* begin extraHeaderBytes: */
	type = (longAt(oop)) & 3;
	if (type > 1) {
		extra = 0;
	} else {
		if (type == 1) {
			extra = 4;
		} else {
			extra = 8;
		}
	}
	extraHdrBytes = extra;
	/* begin sizeBitsOf: */
	header1 = longAt(oop);
	if ((header1 & 3) == 0) {
		bytes = (longAt(oop - 8)) & 4294967292U;
		goto l1;
	} else {
		bytes = header1 & 252;
		goto l1;
	}
l1:	/* end sizeBitsOf: */;
	bytes += extraHdrBytes;
	/* begin pushRemappableOop: */
	remapBuffer[remapBufferCount += 1] = oop;
	/* begin allocateChunk: */
	if (allocationCount >= allocationsBetweenGCs) {
		incrementalGC();
	}
	/* begin sufficientSpaceToAllocate: */
	minFree = (lowSpaceThreshold + bytes) + 4;
	if (((longAt(freeBlock)) & 536870908) >= minFree) {
		enoughSpace = true;
		goto l2;
	} else {
		enoughSpace = sufficientSpaceAfterGC(minFree);
		goto l2;
	}
l2:	/* end sufficientSpaceToAllocate: */;
	if (!(enoughSpace)) {
		signalLowSpace = true;
		lowSpaceThreshold = 0;
		interruptCheckCounter = 0;
	}
	if (((longAt(freeBlock)) & 536870908) < (bytes + 4)) {
		error("out of memory");
	}
	newFreeSize = ((longAt(freeBlock)) & 536870908) - bytes;
	newChunk1 = freeBlock;
	freeBlock += bytes;
	/* begin setSizeOfFree:to: */
	longAtput(freeBlock, (newFreeSize & 536870908) | 2);
	allocationCount += 1;
	newChunk = newChunk1;
	/* begin popRemappableOop */
	oop1 = remapBuffer[remapBufferCount];
	remapBufferCount -= 1;
	remappedOop = oop1;
	toIndex = newChunk - 4;
	fromIndex = (remappedOop - extraHdrBytes) - 4;
	lastFrom = fromIndex + bytes;
	while (fromIndex < lastFrom) {
		longAtput(toIndex += 4, longAt(fromIndex += 4));
	}
	newOop = newChunk + extraHdrBytes;
	/* begin newObjectHash */
	lastHash = (13849 + (27181 * lastHash)) & 65535;
	hash = lastHash;
	header = (longAt(newOop)) & 131071;
	header = header | ((hash << 17) & 536739840);
	longAtput(newOop, header);
	return newOop;
}

int commonAt(int stringy) {
    int index;
    int result;
    int rcvr;
    int sp;

	index = longAt(stackPointer);
	rcvr = longAt(stackPointer - (1 * 4));
	if (((index & 1)) && (!((rcvr & 1)))) {
		index = (index >> 1);
		result = stObjectat(rcvr, index);
		if (stringy && (successFlag)) {
			result = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (24 << 2))))) + 4) + (((result >> 1)) << 2));
		}
	} else {
		successFlag = false;
	}
	if (successFlag) {
		/* begin pop:thenPush: */
		longAtput(sp = stackPointer - ((2 - 1) * 4), result);
		stackPointer = sp;
	} else {
		if (stringy) {
			failSpecialPrim(63);
		} else {
			failSpecialPrim(60);
		}
	}
}

int commonAtPut(int stringy) {
    int value;
    int valToStore;
    int index;
    int rcvr;
    int sp;

	value = valToStore = longAt(stackPointer);
	index = longAt(stackPointer - (1 * 4));
	rcvr = longAt(stackPointer - (2 * 4));
	if (((index & 1)) && (!((rcvr & 1)))) {
		index = (index >> 1);
		if (stringy) {
			valToStore = asciiOfCharacter(value);
		}
		stObjectatput(rcvr, index, valToStore);
	} else {
		successFlag = false;
	}
	if (successFlag) {
		/* begin pop:thenPush: */
		longAtput(sp = stackPointer - ((3 - 1) * 4), value);
		stackPointer = sp;
	} else {
		if (stringy) {
			failSpecialPrim(64);
		} else {
			failSpecialPrim(61);
		}
	}
}

int compare31or32Bitsequal(int obj1, int obj2) {
	if (((obj1 & 1)) && ((obj2 & 1))) {
		return obj1 == obj2;
	}
	return (positive32BitValueOf(obj1)) == (positive32BitValueOf(obj2));
}

int containOnlyOopsand(int array1, int array2) {
    int fieldOffset;
    int methodHeader;
    int sz;
    int fmt;
    int header;
    int type;

	/* begin lastPointerOf: */
	fmt = (((unsigned) (longAt(array1))) >> 8) & 15;
	if (fmt < 4) {
		/* begin sizeBitsOfSafe: */
		header = longAt(array1);
		/* begin rightType: */
		if ((header & 252) == 0) {
			type = 0;
			goto l2;
		} else {
			if ((header & 126976) == 0) {
				type = 1;
				goto l2;
			} else {
				type = 3;
				goto l2;
			}
		}
	l2:	/* end rightType: */;
		if (type == 0) {
			sz = (longAt(array1 - 8)) & 4294967292U;
			goto l3;
		} else {
			sz = header & 252;
			goto l3;
		}
	l3:	/* end sizeBitsOfSafe: */;
		fieldOffset = sz - 4;
		goto l1;
	}
	if (fmt < 12) {
		fieldOffset = 0;
		goto l1;
	}
	methodHeader = longAt(array1 + 4);
	fieldOffset = (((((unsigned) methodHeader) >> 10) & 255) * 4) + 4;
l1:	/* end lastPointerOf: */;
	while (fieldOffset >= 4) {
		if (((longAt(array1 + fieldOffset)) & 1)) {
			return false;
		}
		if (((longAt(array2 + fieldOffset)) & 1)) {
			return false;
		}
		fieldOffset -= 4;
	}
	return true;
}

int copyBits(void) {
    int integerPointer;
    int dWid;
    int sxLowBits;
    int dxLowBits;
    int pixPerM1;
    int t;
    int sp;

	clipRange();
	if ((bbW <= 0) || (bbH <= 0)) {
		affectedL = affectedR = affectedT = affectedB = 0;
		return null;
	}
	destMaskAndPointerInit();
	bitCount = 0;
	if ((combinationRule == 30) || (combinationRule == 31)) {
		if (argumentCount == 1) {
			/* begin stackIntegerValue: */
			integerPointer = longAt(stackPointer - (0 * 4));
			if ((integerPointer & 1)) {
				sourceAlpha = (integerPointer >> 1);
				goto l1;
			} else {
				primitiveFail();
				sourceAlpha = 0;
				goto l1;
			}
		l1:	/* end stackIntegerValue: */;
			if ((!(!successFlag)) && ((sourceAlpha >= 0) && (sourceAlpha <= 255))) {
				/* begin pop: */
				stackPointer -= 1 * 4;
			} else {
				return primitiveFail();
			}
		} else {
			return primitiveFail();
		}
	}
	if (noSource) {
		copyLoopNoSource();
	} else {
		/* begin checkSourceOverlap */
		if ((sourceForm == destForm) && (dy >= sy)) {
			if (dy > sy) {
				vDir = -1;
				sy = (sy + bbH) - 1;
				dy = (dy + bbH) - 1;
			} else {
				if ((dy == sy) && (dx > sx)) {
					hDir = -1;
					sx = (sx + bbW) - 1;
					dx = (dx + bbW) - 1;
					if (nWords > 1) {
						t = mask1;
						mask1 = mask2;
						mask2 = t;
					}
				}
			}
			destIndex = (destBits + 4) + (((dy * destRaster) + (dx / pixPerWord)) * 4);
			destDelta = 4 * ((destRaster * vDir) - (nWords * hDir));
		}
		if ((sourcePixSize != destPixSize) || (colorMap != nilObj)) {
			copyLoopPixMap();
		} else {
			/* begin sourceSkewAndPointerInit */
			pixPerM1 = pixPerWord - 1;
			sxLowBits = sx & pixPerM1;
			dxLowBits = dx & pixPerM1;
			if (hDir > 0) {
				dWid = ((bbW < (pixPerWord - dxLowBits)) ? bbW : (pixPerWord - dxLowBits));
				preload = (sxLowBits + dWid) > pixPerM1;
			} else {
				dWid = ((bbW < (dxLowBits + 1)) ? bbW : (dxLowBits + 1));
				preload = ((sxLowBits - dWid) + 1) < 0;
			}
			skew = (sxLowBits - dxLowBits) * destPixSize;
			if (preload) {
				if (skew < 0) {
					skew += 32;
				} else {
					skew -= 32;
				}
			}
			sourceIndex = (sourceBits + 4) + (((sy * sourceRaster) + (sx / (32 / sourcePixSize))) * 4);
			sourceDelta = 4 * ((sourceRaster * vDir) - (nWords * hDir));
			if (preload) {
				sourceDelta -= 4 * hDir;
			}
			copyLoop();
		}
	}
	if ((combinationRule == 22) || (combinationRule == 32)) {
		affectedL = affectedR = affectedT = affectedB = 0;
		/* begin pop: */
		stackPointer -= 1 * 4;
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, ((bitCount << 1) | 1));
		stackPointer = sp;
		return null;
	}
	if (hDir > 0) {
		affectedL = dx;
		affectedR = dx + bbW;
	} else {
		affectedL = (dx - bbW) + 1;
		affectedR = dx + 1;
	}
	if (vDir > 0) {
		affectedT = dy;
		affectedB = dy + bbH;
	} else {
		affectedT = (dy - bbH) + 1;
		affectedB = dy + 1;
	}
}

int copyLoop(void) {
    int y;
    int prevWord;
    int skewWord;
    int mergeWord;
    int skewMask;
    int (*mergeFnwith)(int, int);
    int hInc;
    int i;
    int thisWord;
    int word;
    int halftoneWord;
    int notSkewMask;
    int unskew;

	mergeFnwith = ((int (*)(int, int)) (opTable[combinationRule + 1]));
	mergeFnwith;
	hInc = hDir * 4;
	if (skew == -32) {
		skew = unskew = skewMask = 0;
	} else {
		if (skew < 0) {
			unskew = skew + 32;
			skewMask = 4294967295U << (0 - skew);
		} else {
			if (skew == 0) {
				unskew = 0;
				skewMask = 4294967295U;
			} else {
				unskew = skew - 32;
				skewMask = ((unsigned) 4294967295U) >> skew;
			}
		}
	}
	notSkewMask = ~skewMask;
	if (noHalftone) {
		halftoneWord = 4294967295U;
		halftoneHeight = 0;
	} else {
		halftoneWord = longAt(halftoneBase);
	}
	y = dy;
	for (i = 1; i <= bbH; i += 1) {
		if (halftoneHeight > 1) {
			halftoneWord = longAt(halftoneBase + ((y % halftoneHeight) * 4));
			y += vDir;
		}
		if (preload) {
			prevWord = longAt(sourceIndex);
			sourceIndex += hInc;
		} else {
			prevWord = 0;
		}
		destMask = mask1;
		thisWord = longAt(sourceIndex);
		sourceIndex += hInc;
		skewWord = (((unskew < 0) ? ((unsigned) (prevWord & notSkewMask) >> -unskew) : ((unsigned) (prevWord & notSkewMask) << unskew))) | (((skew < 0) ? ((unsigned) (thisWord & skewMask) >> -skew) : ((unsigned) (thisWord & skewMask) << skew)));
		prevWord = thisWord;
		mergeWord = mergeFnwith(skewWord & halftoneWord, longAt(destIndex));
		longAtput(destIndex, (destMask & mergeWord) | ((~destMask) & (longAt(destIndex))));
		destIndex += hInc;
		destMask = 4294967295U;
		if (combinationRule == 3) {
			if (noHalftone && (notSkewMask == 0)) {
				for (word = 2; word <= (nWords - 1); word += 1) {
					thisWord = longAt(sourceIndex);
					sourceIndex += hInc;
					longAtput(destIndex, thisWord);
					destIndex += hInc;
				}
			} else {
				for (word = 2; word <= (nWords - 1); word += 1) {
					thisWord = longAt(sourceIndex);
					sourceIndex += hInc;
					skewWord = (((unskew < 0) ? ((unsigned) (prevWord & notSkewMask) >> -unskew) : ((unsigned) (prevWord & notSkewMask) << unskew))) | (((skew < 0) ? ((unsigned) (thisWord & skewMask) >> -skew) : ((unsigned) (thisWord & skewMask) << skew)));
					prevWord = thisWord;
					longAtput(destIndex, skewWord & halftoneWord);
					destIndex += hInc;
				}
			}
		} else {
			for (word = 2; word <= (nWords - 1); word += 1) {
				thisWord = longAt(sourceIndex);
				sourceIndex += hInc;
				skewWord = (((unskew < 0) ? ((unsigned) (prevWord & notSkewMask) >> -unskew) : ((unsigned) (prevWord & notSkewMask) << unskew))) | (((skew < 0) ? ((unsigned) (thisWord & skewMask) >> -skew) : ((unsigned) (thisWord & skewMask) << skew)));
				prevWord = thisWord;
				mergeWord = mergeFnwith(skewWord & halftoneWord, longAt(destIndex));
				longAtput(destIndex, mergeWord);
				destIndex += hInc;
			}
		}
		if (nWords > 1) {
			destMask = mask2;
			thisWord = longAt(sourceIndex);
			sourceIndex += hInc;
			skewWord = (((unskew < 0) ? ((unsigned) (prevWord & notSkewMask) >> -unskew) : ((unsigned) (prevWord & notSkewMask) << unskew))) | (((skew < 0) ? ((unsigned) (thisWord & skewMask) >> -skew) : ((unsigned) (thisWord & skewMask) << skew)));
			mergeWord = mergeFnwith(skewWord & halftoneWord, longAt(destIndex));
			longAtput(destIndex, (destMask & mergeWord) | ((~destMask) & (longAt(destIndex))));
			destIndex += hInc;
		}
		sourceIndex += sourceDelta;
		destIndex += destDelta;
	}
}

int copyLoopNoSource(void) {
    int mergeWord;
    int (*mergeFnwith)(int, int);
    int i;
    int word;
    int halftoneWord;

	mergeFnwith = ((int (*)(int, int)) (opTable[combinationRule + 1]));
	mergeFnwith;
	for (i = 1; i <= bbH; i += 1) {
		if (noHalftone) {
			halftoneWord = 4294967295U;
		} else {
			halftoneWord = longAt(halftoneBase + ((((dy + i) - 1) % halftoneHeight) * 4));
		}
		destMask = mask1;
		mergeWord = mergeFnwith(halftoneWord, longAt(destIndex));
		longAtput(destIndex, (destMask & mergeWord) | ((~destMask) & (longAt(destIndex))));
		destIndex += 4;
		destMask = 4294967295U;
		if (combinationRule == 3) {
			for (word = 2; word <= (nWords - 1); word += 1) {
				longAtput(destIndex, halftoneWord);
				destIndex += 4;
			}
		} else {
			for (word = 2; word <= (nWords - 1); word += 1) {
				mergeWord = mergeFnwith(halftoneWord, longAt(destIndex));
				longAtput(destIndex, mergeWord);
				destIndex += 4;
			}
		}
		if (nWords > 1) {
			destMask = mask2;
			mergeWord = mergeFnwith(halftoneWord, longAt(destIndex));
			longAtput(destIndex, (destMask & mergeWord) | ((~destMask) & (longAt(destIndex))));
			destIndex += 4;
		}
		destIndex += destDelta;
	}
}

int copyLoopPixMap(void) {
    int skewWord;
    int mergeWord;
    int srcPixPerWord;
    int scrStartBits;
    int nSourceIncs;
    int startBits;
    int sourcePixMask;
    int destPixMask;
    int nullMap;
    int endBits;
    int (*mergeFnwith)(int, int);
    int halftoneWord;
    int i;
    int word;
    int nPix;
    int nPix1;

	mergeFnwith = ((int (*)(int, int)) (opTable[combinationRule + 1]));
	mergeFnwith;
	srcPixPerWord = 32 / sourcePixSize;
	if (sourcePixSize == 32) {
		sourcePixMask = -1;
	} else {
		sourcePixMask = (1 << sourcePixSize) - 1;
	}
	if (destPixSize == 32) {
		destPixMask = -1;
	} else {
		destPixMask = (1 << destPixSize) - 1;
	}
	nullMap = colorMap == nilObj;
	sourceIndex = (sourceBits + 4) + (((sy * sourceRaster) + (sx / srcPixPerWord)) * 4);
	scrStartBits = srcPixPerWord - (sx & (srcPixPerWord - 1));
	if (bbW < scrStartBits) {
		nSourceIncs = 0;
	} else {
		nSourceIncs = ((bbW - scrStartBits) / srcPixPerWord) + 1;
	}
	sourceDelta = (sourceRaster - nSourceIncs) * 4;
	startBits = pixPerWord - (dx & (pixPerWord - 1));
	endBits = (((dx + bbW) - 1) & (pixPerWord - 1)) + 1;
	for (i = 1; i <= bbH; i += 1) {
		if (noHalftone) {
			halftoneWord = 4294967295U;
		} else {
			halftoneWord = longAt(halftoneBase + ((((dy + i) - 1) % halftoneHeight) * 4));
		}
		srcBitIndex = (sx & (srcPixPerWord - 1)) * sourcePixSize;
		destMask = mask1;
		if (bbW < startBits) {
			/* begin pickSourcePixels:nullMap:srcMask:destMask: */
			nPix = bbW;
			if (sourcePixSize >= 16) {
				skewWord = pickSourcePixelsRGBnullMapsrcMaskdestMask(nPix, nullMap, sourcePixMask, destPixMask);
				goto l1;
			}
			if (nullMap) {
				skewWord = pickSourcePixelsNullMapsrcMaskdestMask(nPix, sourcePixMask, destPixMask);
				goto l1;
			}
			skewWord = pickSourcePixelssrcMaskdestMask(nPix, sourcePixMask, destPixMask);
		l1:	/* end pickSourcePixels:nullMap:srcMask:destMask: */;
			skewWord = ((((startBits - bbW) * destPixSize) < 0) ? ((unsigned) skewWord >> -((startBits - bbW) * destPixSize)) : ((unsigned) skewWord << ((startBits - bbW) * destPixSize)));
		} else {
			/* begin pickSourcePixels:nullMap:srcMask:destMask: */
			if (sourcePixSize >= 16) {
				skewWord = pickSourcePixelsRGBnullMapsrcMaskdestMask(startBits, nullMap, sourcePixMask, destPixMask);
				goto l2;
			}
			if (nullMap) {
				skewWord = pickSourcePixelsNullMapsrcMaskdestMask(startBits, sourcePixMask, destPixMask);
				goto l2;
			}
			skewWord = pickSourcePixelssrcMaskdestMask(startBits, sourcePixMask, destPixMask);
		l2:	/* end pickSourcePixels:nullMap:srcMask:destMask: */;
		}
		for (word = 1; word <= nWords; word += 1) {
			mergeWord = mergeFnwith(skewWord & halftoneWord, (longAt(destIndex)) & destMask);
			longAtput(destIndex, (destMask & mergeWord) | ((~destMask) & (longAt(destIndex))));
			destIndex += 4;
			if (word >= (nWords - 1)) {
				if (!(word == nWords)) {
					destMask = mask2;
					/* begin pickSourcePixels:nullMap:srcMask:destMask: */
					if (sourcePixSize >= 16) {
						skewWord = pickSourcePixelsRGBnullMapsrcMaskdestMask(endBits, nullMap, sourcePixMask, destPixMask);
						goto l3;
					}
					if (nullMap) {
						skewWord = pickSourcePixelsNullMapsrcMaskdestMask(endBits, sourcePixMask, destPixMask);
						goto l3;
					}
					skewWord = pickSourcePixelssrcMaskdestMask(endBits, sourcePixMask, destPixMask);
				l3:	/* end pickSourcePixels:nullMap:srcMask:destMask: */;
					skewWord = ((((pixPerWord - endBits) * destPixSize) < 0) ? ((unsigned) skewWord >> -((pixPerWord - endBits) * destPixSize)) : ((unsigned) skewWord << ((pixPerWord - endBits) * destPixSize)));
				}
			} else {
				destMask = 4294967295U;
				/* begin pickSourcePixels:nullMap:srcMask:destMask: */
				nPix1 = pixPerWord;
				if (sourcePixSize >= 16) {
					skewWord = pickSourcePixelsRGBnullMapsrcMaskdestMask(nPix1, nullMap, sourcePixMask, destPixMask);
					goto l4;
				}
				if (nullMap) {
					skewWord = pickSourcePixelsNullMapsrcMaskdestMask(nPix1, sourcePixMask, destPixMask);
					goto l4;
				}
				skewWord = pickSourcePixelssrcMaskdestMask(nPix1, sourcePixMask, destPixMask);
			l4:	/* end pickSourcePixels:nullMap:srcMask:destMask: */;
			}
		}
		sourceIndex += sourceDelta;
		destIndex += destDelta;
	}
}

int cr(void) {
	printf("\n");
}

int createActualMessage(void) {
    int argumentArray;
    int message;
    int oop;
    int valuePointer;
    int toIndex;
    int fromIndex;
    int lastFrom;
    int sp;

	argumentArray = instantiateClassindexableSize(longAt(((((char *) specialObjectsOop)) + 4) + (7 << 2)), argumentCount);
	/* begin pushRemappableOop: */
	remapBuffer[remapBufferCount += 1] = argumentArray;
	message = instantiateClassindexableSize(longAt(((((char *) specialObjectsOop)) + 4) + (15 << 2)), 0);
	/* begin popRemappableOop */
	oop = remapBuffer[remapBufferCount];
	remapBufferCount -= 1;
	argumentArray = oop;
	if (argumentArray < youngStart) {
		beRootIfOld(argumentArray);
	}
	/* begin storePointer:ofObject:withValue: */
	valuePointer = messageSelector;
	if (message < youngStart) {
		possibleRootStoreIntovalue(message, valuePointer);
	}
	longAtput(((((char *) message)) + 4) + (0 << 2), valuePointer);
	/* begin storePointer:ofObject:withValue: */
	if (message < youngStart) {
		possibleRootStoreIntovalue(message, argumentArray);
	}
	longAtput(((((char *) message)) + 4) + (1 << 2), argumentArray);
	/* begin transfer:fromIndex:ofObject:toIndex:ofObject: */
	fromIndex = activeContext + (((((unsigned) ((stackPointer - activeContext) - 4)) >> 2) - (argumentCount - 1)) * 4);
	toIndex = argumentArray + (0 * 4);
	lastFrom = fromIndex + (argumentCount * 4);
	while (fromIndex < lastFrom) {
		fromIndex += 4;
		toIndex += 4;
		longAtput(toIndex, longAt(fromIndex));
	}
	/* begin pop: */
	stackPointer -= argumentCount * 4;
	/* begin push: */
	longAtput(sp = stackPointer + 4, message);
	stackPointer = sp;
	argumentCount = 1;
}

int deltaFromtonSteps(int x1, int x2, int n) {
	if (x2 > x1) {
		return (((x2 - x1) + 16384) / (n + 1)) + 1;
	} else {
		if (x2 == x1) {
			return 0;
		}
		return 0 - ((((x1 - x2) + 16384) / (n + 1)) + 1);
	}
}

int destMaskAndPointerInit(void) {
    int startBits;
    int endBits;
    int pixPerM1;

	pixPerM1 = pixPerWord - 1;
	startBits = pixPerWord - (dx & pixPerM1);
	mask1 = ((unsigned) 4294967295U) >> (32 - (startBits * destPixSize));
	endBits = (((dx + bbW) - 1) & pixPerM1) + 1;
	mask2 = 4294967295U << (32 - (endBits * destPixSize));
	if (bbW < startBits) {
		mask1 = mask1 & mask2;
		mask2 = 0;
		nWords = 1;
	} else {
		nWords = (((bbW - startBits) + pixPerM1) / pixPerWord) + 1;
	}
	hDir = vDir = 1;
	destIndex = (destBits + 4) + (((dy * destRaster) + (dx / pixPerWord)) * 4);
	destDelta = 4 * ((destRaster * vDir) - (nWords * hDir));
}

int destinationWordwith(int sourceWord, int destinationWord) {
	return destinationWord;
}

int drawLoopXY(int xDelta, int yDelta) {
    int affL;
    int dx1;
    int dy1;
    int px;
    int py;
    int affR;
    int affT;
    int affB;
    int i;
    int P;
    int objectPointer;
    int integerValue;
    int objectPointer1;
    int integerValue1;

	if (xDelta > 0) {
		dx1 = 1;
	} else {
		if (xDelta == 0) {
			dx1 = 0;
		} else {
			dx1 = -1;
		}
	}
	if (yDelta > 0) {
		dy1 = 1;
	} else {
		if (yDelta == 0) {
			dy1 = 0;
		} else {
			dy1 = -1;
		}
	}
	px = abs(yDelta);
	py = abs(xDelta);
	affL = affT = 9999;
	affR = affB = -9999;
	if (py > px) {
		P = ((int) py >> 1);
		for (i = 1; i <= py; i += 1) {
			destX += dx1;
			if ((P -= px) < 0) {
				destY += dy1;
				P += py;
			}
			if (i < py) {
				copyBits();
				if ((affectedL < affectedR) && (affectedT < affectedB)) {
					affL = ((affL < affectedL) ? affL : affectedL);
					affR = ((affR < affectedR) ? affectedR : affR);
					affT = ((affT < affectedT) ? affT : affectedT);
					affB = ((affB < affectedB) ? affectedB : affB);
					if (((affR - affL) * (affB - affT)) > 4000) {
						affectedL = affL;
						affectedR = affR;
						affectedT = affT;
						affectedB = affB;
						showDisplayBits();
						affL = affT = 9999;
						affR = affB = -9999;
					}
				}
			}
		}
	} else {
		P = ((int) px >> 1);
		for (i = 1; i <= px; i += 1) {
			destY += dy1;
			if ((P -= py) < 0) {
				destX += dx1;
				P += px;
			}
			if (i < px) {
				copyBits();
				if ((affectedL < affectedR) && (affectedT < affectedB)) {
					affL = ((affL < affectedL) ? affL : affectedL);
					affR = ((affR < affectedR) ? affectedR : affR);
					affT = ((affT < affectedT) ? affT : affectedT);
					affB = ((affB < affectedB) ? affectedB : affB);
					if (((affR - affL) * (affB - affT)) > 4000) {
						affectedL = affL;
						affectedR = affR;
						affectedT = affT;
						affectedB = affB;
						showDisplayBits();
						affL = affT = 9999;
						affR = affB = -9999;
					}
				}
			}
		}
	}
	affectedL = affL;
	affectedR = affR;
	affectedT = affT;
	affectedB = affB;
	/* begin storeInteger:ofObject:withValue: */
	objectPointer = bitBltOop;
	integerValue = destX;
	if ((integerValue ^ (integerValue << 1)) >= 0) {
		longAtput(((((char *) objectPointer)) + 4) + (4 << 2), ((integerValue << 1) | 1));
	} else {
		primitiveFail();
	}
	/* begin storeInteger:ofObject:withValue: */
	objectPointer1 = bitBltOop;
	integerValue1 = destY;
	if ((integerValue1 ^ (integerValue1 << 1)) >= 0) {
		longAtput(((((char *) objectPointer1)) + 4) + (5 << 2), ((integerValue1 << 1) | 1));
	} else {
		primitiveFail();
	}
}

int exchangeHashBitswith(int oop1, int oop2) {
    int hdr1;
    int hdr2;

	hdr1 = longAt(oop1);
	hdr2 = longAt(oop2);
	longAtput(oop1, (hdr1 & 3758227455U) | (hdr2 & 536739840));
	longAtput(oop2, (hdr2 & 3758227455U) | (hdr1 & 536739840));
}

int executeNewMethod(void) {
	if ((primitiveIndex == 0) || (!(primitiveResponse()))) {
		activateNewMethod();
		/* begin quickCheckForInterrupts */
		if ((interruptCheckCounter -= 1) <= 0) {
			checkForInterrupts();
		}
	}
}

int extraHeaderBytes(int oopOrChunk) {
    int type;
    int extra;

	type = (longAt(oopOrChunk)) & 3;
	if (type > 1) {
		extra = 0;
	} else {
		if (type == 1) {
			extra = 4;
		} else {
			extra = 8;
		}
	}
	return extra;
}

int failSpecialPrim(int primIndex) {
    int selectorIndex;
    int bytecode;
    int newReceiver;
    int rcvrClass;
    int ccIndex;
    int ok;
    int probe;
    int p;
    int hash;
    int primBits;

	bytecode = byteAt(instructionPointer);
	if ((bytecode < 176) || (bytecode > 207)) {
		return primitiveFail();
	}
	selectorIndex = (bytecode - 176) * 2;
	messageSelector = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (23 << 2))))) + 4) + (selectorIndex << 2));
	argumentCount = ((longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (23 << 2))))) + 4) + ((selectorIndex + 1) << 2))) >> 1);
	newReceiver = longAt(stackPointer - (argumentCount * 4));
	/* begin fetchClassOf: */
	if ((newReceiver & 1)) {
		rcvrClass = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
		goto l1;
	}
	ccIndex = ((((unsigned) (longAt(newReceiver))) >> 12) & 31) - 1;
	if (ccIndex < 0) {
		rcvrClass = (longAt(newReceiver - 4)) & 4294967292U;
		goto l1;
	} else {
		rcvrClass = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
		goto l1;
	}
l1:	/* end fetchClassOf: */;
	/* begin findNewMethodInClass: */
	/* begin lookupInMethodCacheSel:class: */
	hash = ((unsigned) (messageSelector ^ rcvrClass)) >> 2;
	probe = (hash & 511) + 1;
	for (p = 1; p <= 3; p += 1) {
		if (((methodCache[probe]) == messageSelector) && ((methodCache[probe + 512]) == rcvrClass)) {
			newMethod = methodCache[probe + (512 * 2)];
			primitiveIndex = methodCache[probe + (512 * 3)];
			ok = true;
			goto l3;
		}
		probe = ((((unsigned) hash) >> p) & 511) + 1;
	}
	ok = false;
l3:	/* end lookupInMethodCacheSel:class: */;
	if (!(ok)) {
		lookupMethodInClass(rcvrClass);
		/* begin primitiveIndexOf: */
		primBits = (((unsigned) (longAt(((((char *) newMethod)) + 4) + (0 << 2)))) >> 1) & 805306879;
		if (primBits > 511) {
			primitiveIndex = (primBits & 511) + (((unsigned) primBits) >> 19);
			goto l2;
		} else {
			primitiveIndex = primBits;
			goto l2;
		}
	l2:	/* end primitiveIndexOf: */;
		addToMethodCacheSelclassmethodprimIndex(messageSelector, rcvrClass, newMethod, primitiveIndex);
	}
	if ((primitiveIndex > 37) && (primitiveIndex != primIndex)) {
		/* begin executeNewMethod */
		if ((primitiveIndex == 0) || (!(primitiveResponse()))) {
			activateNewMethod();
			/* begin quickCheckForInterrupts */
			if ((interruptCheckCounter -= 1) <= 0) {
				checkForInterrupts();
			}
		}
	} else {
		activateNewMethod();
	}
}

int failed(void) {
	return !successFlag;
}

void * fetchArrayofObject(int fieldIndex, int objectPointer) {
    int arrayOop;

	arrayOop = longAt(((((char *) objectPointer)) + 4) + (fieldIndex << 2));
	return arrayValueOf(arrayOop);
}

int fetchByteofObject(int byteIndex, int oop) {
	return byteAt(((((char *) oop)) + 4) + byteIndex);
}

int fetchClassOf(int oop) {
    int ccIndex;

	if ((oop & 1)) {
		return longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
	}
	ccIndex = ((((unsigned) (longAt(oop))) >> 12) & 31) - 1;
	if (ccIndex < 0) {
		return (longAt(oop - 4)) & 4294967292U;
	} else {
		return longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
	}
}

int fetchContextRegisters(int activeCntx) {
    int tmp;

	tmp = longAt(((((char *) activeCntx)) + 4) + (3 << 2));
	if ((tmp & 1)) {
		tmp = longAt(((((char *) activeCntx)) + 4) + (5 << 2));
		if (tmp < youngStart) {
			beRootIfOld(tmp);
		}
	} else {
		tmp = activeCntx;
	}
	theHomeContext = tmp;
	receiver = longAt(((((char *) tmp)) + 4) + (5 << 2));
	method = longAt(((((char *) tmp)) + 4) + (3 << 2));
	tmp = ((longAt(((((char *) activeCntx)) + 4) + (1 << 2))) >> 1);
	instructionPointer = ((method + tmp) + 4) - 2;
	tmp = ((longAt(((((char *) activeCntx)) + 4) + (2 << 2))) >> 1);
	stackPointer = (activeCntx + 4) + (((6 + tmp) - 1) * 4);
}

double fetchFloatofObject(int fieldIndex, int objectPointer) {
    int floatOop;

	floatOop = longAt(((((char *) objectPointer)) + 4) + (fieldIndex << 2));
	return floatValueOf(floatOop);
}

int fetchIntegerofObject(int fieldIndex, int objectPointer) {
    int intOop;

	intOop = longAt(((((char *) objectPointer)) + 4) + (fieldIndex << 2));
	if ((intOop & 1)) {
		return (intOop >> 1);
	} else {
		primitiveFail();
		return 0;
	}
}

int fetchIntegerOrTruncFloatofObject(int fieldIndex, int objectPointer) {
    double trunc;
    double frac;
    double floatVal;
    int intOrFloat;
    int ccIndex;
    int cl;

	intOrFloat = longAt(((((char *) objectPointer)) + 4) + (fieldIndex << 2));
	if ((intOrFloat & 1)) {
		return (intOrFloat >> 1);
	}
	/* begin assertClassOf:is: */
	if ((intOrFloat & 1)) {
		successFlag = false;
		goto l1;
	}
	ccIndex = (((unsigned) (longAt(intOrFloat))) >> 12) & 31;
	if (ccIndex == 0) {
		cl = (longAt(intOrFloat - 4)) & 4294967292U;
	} else {
		cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
	}
	/* begin success: */
	successFlag = (cl == (longAt(((((char *) specialObjectsOop)) + 4) + (9 << 2)))) && successFlag;
l1:	/* end assertClassOf:is: */;
	if (successFlag) {
		fetchFloatAtinto(intOrFloat + 4, floatVal);
		frac = modf(floatVal, &trunc);
		success((-2147483648.0 <= trunc) && (trunc <= 2147483647.0));
	}
	if (successFlag) {
		return ((int) trunc);
	} else {
		return 0;
	}
}

int fetchPointerofObject(int fieldIndex, int oop) {
	return longAt(((((char *) oop)) + 4) + (fieldIndex << 2));
}

int fetchWordofObject(int fieldIndex, int oop) {
	return longAt(((((char *) oop)) + 4) + (fieldIndex << 2));
}

int fetchWordLengthOf(int objectPointer) {
    int sz;
    int header;

	/* begin sizeBitsOf: */
	header = longAt(objectPointer);
	if ((header & 3) == 0) {
		sz = (longAt(objectPointer - 8)) & 4294967292U;
		goto l1;
	} else {
		sz = header & 252;
		goto l1;
	}
l1:	/* end sizeBitsOf: */;
	return ((unsigned) (sz - 4)) >> 2;
}

int fileRecordSize(void) {
	return sizeof(SQFile);
}

SQFile * fileValueOf(int objectPointer) {
    int fileIndex;
    int successValue;

	/* begin success: */
	successValue = (((((unsigned) (longAt(objectPointer))) >> 8) & 15) >= 8) && ((lengthOf(objectPointer)) == (fileRecordSize()));
	successFlag = successValue && successFlag;
	if (successFlag) {
		fileIndex = objectPointer + 4;
		return (SQFile *) fileIndex;
	} else {
		return null;
	}
}

int findClassOfMethodforReceiver(int meth, int rcvr) {
    int methodArray;
    int done;
    int i;
    int classDict;
    int currClass;
    int classDictSize;
    int sz;
    int header;
    int ccIndex;
    int ccIndex1;

	/* begin fetchClassOf: */
	if ((rcvr & 1)) {
		currClass = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
		goto l2;
	}
	ccIndex = ((((unsigned) (longAt(rcvr))) >> 12) & 31) - 1;
	if (ccIndex < 0) {
		currClass = (longAt(rcvr - 4)) & 4294967292U;
		goto l2;
	} else {
		currClass = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
		goto l2;
	}
l2:	/* end fetchClassOf: */;
	done = false;
	while (!(done)) {
		classDict = longAt(((((char *) currClass)) + 4) + (1 << 2));
		/* begin fetchWordLengthOf: */
		/* begin sizeBitsOf: */
		header = longAt(classDict);
		if ((header & 3) == 0) {
			sz = (longAt(classDict - 8)) & 4294967292U;
			goto l1;
		} else {
			sz = header & 252;
			goto l1;
		}
	l1:	/* end sizeBitsOf: */;
		classDictSize = ((unsigned) (sz - 4)) >> 2;
		methodArray = longAt(((((char *) classDict)) + 4) + (1 << 2));
		i = 0;
		while (i < (classDictSize - 2)) {
			if (meth == (longAt(((((char *) methodArray)) + 4) + (i << 2)))) {
				return currClass;
			}
			i += 1;
		}
		currClass = longAt(((((char *) currClass)) + 4) + (0 << 2));
		done = currClass == nilObj;
	}
	/* begin fetchClassOf: */
	if ((rcvr & 1)) {
		return longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
	}
	ccIndex1 = ((((unsigned) (longAt(rcvr))) >> 12) & 31) - 1;
	if (ccIndex1 < 0) {
		return (longAt(rcvr - 4)) & 4294967292U;
	} else {
		return longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex1 << 2));
	}
	return null;
}

int findNewMethodInClass(int class) {
    int ok;
    int probe;
    int p;
    int hash;
    int primBits;

	/* begin lookupInMethodCacheSel:class: */
	hash = ((unsigned) (messageSelector ^ class)) >> 2;
	probe = (hash & 511) + 1;
	for (p = 1; p <= 3; p += 1) {
		if (((methodCache[probe]) == messageSelector) && ((methodCache[probe + 512]) == class)) {
			newMethod = methodCache[probe + (512 * 2)];
			primitiveIndex = methodCache[probe + (512 * 3)];
			ok = true;
			goto l1;
		}
		probe = ((((unsigned) hash) >> p) & 511) + 1;
	}
	ok = false;
l1:	/* end lookupInMethodCacheSel:class: */;
	if (!(ok)) {
		lookupMethodInClass(class);
		/* begin primitiveIndexOf: */
		primBits = (((unsigned) (longAt(((((char *) newMethod)) + 4) + (0 << 2)))) >> 1) & 805306879;
		if (primBits > 511) {
			primitiveIndex = (primBits & 511) + (((unsigned) primBits) >> 19);
			goto l2;
		} else {
			primitiveIndex = primBits;
			goto l2;
		}
	l2:	/* end primitiveIndexOf: */;
		addToMethodCacheSelclassmethodprimIndex(messageSelector, class, newMethod, primitiveIndex);
	}
}

int findSelectorOfMethodforReceiver(int meth, int rcvr) {
    int methodArray;
    int done;
    int i;
    int classDict;
    int currClass;
    int classDictSize;
    int sz;
    int header;
    int ccIndex;

	/* begin fetchClassOf: */
	if ((rcvr & 1)) {
		currClass = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
		goto l2;
	}
	ccIndex = ((((unsigned) (longAt(rcvr))) >> 12) & 31) - 1;
	if (ccIndex < 0) {
		currClass = (longAt(rcvr - 4)) & 4294967292U;
		goto l2;
	} else {
		currClass = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
		goto l2;
	}
l2:	/* end fetchClassOf: */;
	done = false;
	while (!(done)) {
		classDict = longAt(((((char *) currClass)) + 4) + (1 << 2));
		/* begin fetchWordLengthOf: */
		/* begin sizeBitsOf: */
		header = longAt(classDict);
		if ((header & 3) == 0) {
			sz = (longAt(classDict - 8)) & 4294967292U;
			goto l1;
		} else {
			sz = header & 252;
			goto l1;
		}
	l1:	/* end sizeBitsOf: */;
		classDictSize = ((unsigned) (sz - 4)) >> 2;
		methodArray = longAt(((((char *) classDict)) + 4) + (1 << 2));
		i = 0;
		while (i <= (classDictSize - 2)) {
			if (meth == (longAt(((((char *) methodArray)) + 4) + (i << 2)))) {
				return longAt(((((char *) classDict)) + 4) + ((i + 2) << 2));
			}
			i += 1;
		}
		currClass = longAt(((((char *) currClass)) + 4) + (0 << 2));
		done = currClass == nilObj;
	}
	return longAt(((((char *) specialObjectsOop)) + 4) + (20 << 2));
}

int firstAccessibleObject(void) {
    int obj;
    int chunk;
    int extra;
    int type;
    int extra1;
    int sz;
    int header;
    int extra2;
    int type1;
    int extra11;

	/* begin oopFromChunk: */
	chunk = startOfMemory();
	/* begin extraHeaderBytes: */
	type = (longAt(chunk)) & 3;
	if (type > 1) {
		extra1 = 0;
	} else {
		if (type == 1) {
			extra1 = 4;
		} else {
			extra1 = 8;
		}
	}
	extra = extra1;
	obj = chunk + extra;
	while (obj < endOfMemory) {
		if (!(((longAt(obj)) & 3) == 2)) {
			return obj;
		}
		/* begin objectAfter: */
		if (checkAssertions) {
			if (obj >= endOfMemory) {
				error("no objects after the end of memory");
			}
		}
		if (((longAt(obj)) & 3) == 2) {
			sz = (longAt(obj)) & 536870908;
		} else {
			/* begin sizeBitsOf: */
			header = longAt(obj);
			if ((header & 3) == 0) {
				sz = (longAt(obj - 8)) & 4294967292U;
				goto l1;
			} else {
				sz = header & 252;
				goto l1;
			}
		l1:	/* end sizeBitsOf: */;
		}
		/* begin oopFromChunk: */
		/* begin extraHeaderBytes: */
		type1 = (longAt(obj + sz)) & 3;
		if (type1 > 1) {
			extra11 = 0;
		} else {
			if (type1 == 1) {
				extra11 = 4;
			} else {
				extra11 = 8;
			}
		}
		extra2 = extra11;
		obj = (obj + sz) + extra2;
	}
	error("heap is empty");
}

int firstObject(void) {
    int chunk;
    int extra;
    int type;
    int extra1;

	/* begin oopFromChunk: */
	chunk = startOfMemory();
	/* begin extraHeaderBytes: */
	type = (longAt(chunk)) & 3;
	if (type > 1) {
		extra1 = 0;
	} else {
		if (type == 1) {
			extra1 = 4;
		} else {
			extra1 = 8;
		}
	}
	extra = extra1;
	return chunk + extra;
}

int fixedFieldsOfformatlength(int oop, int fmt, int wordLength) {
    int classFormat;
    int class;
    int ccIndex;

	if ((fmt > 3) || (fmt == 2)) {
		return 0;
	}
	if (fmt < 2) {
		return wordLength;
	}
	/* begin fetchClassOf: */
	if ((oop & 1)) {
		class = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
		goto l1;
	}
	ccIndex = ((((unsigned) (longAt(oop))) >> 12) & 31) - 1;
	if (ccIndex < 0) {
		class = (longAt(oop - 4)) & 4294967292U;
		goto l1;
	} else {
		class = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
		goto l1;
	}
l1:	/* end fetchClassOf: */;
	classFormat = (longAt(((((char *) class)) + 4) + (2 << 2))) - 1;
	return (((((unsigned) classFormat) >> 11) & 192) + ((((unsigned) classFormat) >> 2) & 63)) - 1;
}

double floatValueOf(int oop) {
    double result;
    int ccIndex;
    int cl;

	/* begin assertClassOf:is: */
	if ((oop & 1)) {
		successFlag = false;
		goto l1;
	}
	ccIndex = (((unsigned) (longAt(oop))) >> 12) & 31;
	if (ccIndex == 0) {
		cl = (longAt(oop - 4)) & 4294967292U;
	} else {
		cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
	}
	/* begin success: */
	successFlag = (cl == (longAt(((((char *) specialObjectsOop)) + 4) + (9 << 2)))) && successFlag;
l1:	/* end assertClassOf:is: */;
	if (successFlag) {
		fetchFloatAtinto(oop + 4, result);
	} else {
		result = 0.0;
	}
	return result;
}

int flushMethodCache(void) {
    int i;

	for (i = 1; i <= 2048; i += 1) {
		methodCache[i] = 0;
	}
	mcProbe = 0;
}

int formatOf(int oop) {
	return (((unsigned) (longAt(oop))) >> 8) & 15;
}

int formatOfClass(int classPointer) {
	return (longAt(((((char *) classPointer)) + 4) + (2 << 2))) - 1;
}

int fullCompaction(void) {
	compStart = lowestFreeAfter(startOfMemory());
	if (compStart == freeBlock) {
		return initializeMemoryFirstFree(freeBlock);
	}
	while (compStart < freeBlock) {
		compStart = incCompBody();
	}
}

int fullDisplayUpdate(void) {
    int displayObj;
    int dispBits;
    int dispBitsIndex;
    int h;
    int w;
    int d;

	displayObj = longAt(((((char *) specialObjectsOop)) + 4) + (14 << 2));
	if ((((((unsigned) (longAt(displayObj))) >> 8) & 15) <= 4) && ((lengthOf(displayObj)) >= 4)) {
		dispBits = longAt(((((char *) displayObj)) + 4) + (0 << 2));
		w = fetchIntegerofObject(1, displayObj);
		h = fetchIntegerofObject(2, displayObj);
		d = fetchIntegerofObject(3, displayObj);
		dispBitsIndex = dispBits + 4;
		ioShowDisplay(dispBitsIndex, w, h, d, 0, w, 0, h);
	}
}

int fullGC(void) {
    int startTime;
    int oop;
    int i;

	/* begin preGCAction: */
	startTime = ioMicroMSecs();
	/* begin clearRootsTable */
	for (i = 1; i <= rootTableCount; i += 1) {
		oop = rootTable[i];
		longAtput(oop, (longAt(oop)) & 3221225471U);
		rootTable[i] = 0;
	}
	rootTableCount = 0;
	youngStart = startOfMemory();
	markPhase();
	sweepPhase();
	/* begin fullCompaction */
	compStart = lowestFreeAfter(startOfMemory());
	if (compStart == freeBlock) {
		initializeMemoryFirstFree(freeBlock);
		goto l1;
	}
	while (compStart < freeBlock) {
		compStart = incCompBody();
	}
l1:	/* end fullCompaction */;
	allocationCount = 0;
	statFullGCs += 1;
	statFullGCMSecs += (ioMicroMSecs()) - startTime;
	youngStart = freeBlock;
	/* begin postGCAction */
	if (activeContext < youngStart) {
		beRootIfOld(activeContext);
	}
	if (theHomeContext < youngStart) {
		beRootIfOld(theHomeContext);
	}
}

int fwdBlockGet(void) {
	fwdTableNext += 8;
	if (fwdTableNext <= fwdTableLast) {
		return fwdTableNext;
	} else {
		return null;
	}
}

int fwdBlockValidate(int addr) {
	if (!((addr > endOfMemory) && ((addr <= fwdTableNext) && ((addr & 3) == 0)))) {
		error("invalid fwd table entry");
	}
}

int fwdTableInit(void) {
	/* begin setSizeOfFree:to: */
	longAtput(freeBlock, (4 & 536870908) | 2);
	endOfMemory = freeBlock + 4;
	/* begin setSizeOfFree:to: */
	longAtput(endOfMemory, (4 & 536870908) | 2);
	fwdTableNext = endOfMemory + 4;
	fwdTableLast = memoryLimit - 8;
	if (checkAssertions && ((fwdTableLast & 2147483648U) != 0)) {
		error("fwd table must be in low half of the 32-bit address space");
	}
	return ((int) (fwdTableLast - fwdTableNext) >> 3);
}

int getCurrentBytecode(void) {
	return byteAt(instructionPointer);
}

int getLongFromFileswap(sqImageFile f, int swapFlag) {
    int w;

	sqImageFileRead(&w, sizeof(char), 4, f);
	if (swapFlag) {
		return ((((((unsigned) w >> 24)) & 255) + ((((unsigned) w >> 8)) & 65280)) + ((((unsigned) w << 8)) & 16711680)) + ((((unsigned) w << 24)) & 4278190080U);
	} else {
		return w;
	}
}

int hashBitsOf(int oop) {
	return (((unsigned) (longAt(oop))) >> 17) & 4095;
}

int headerOf(int methodPointer) {
	return longAt(((((char *) methodPointer)) + 4) + (0 << 2));
}

int headerType(int oop) {
	return (longAt(oop)) & 3;
}

int ignoreSourceOrHalftone(int formPointer) {
	if (formPointer == nilObj) {
		return true;
	}
	if (combinationRule == 0) {
		return true;
	}
	if (combinationRule == 5) {
		return true;
	}
	if (combinationRule == 10) {
		return true;
	}
	if (combinationRule == 15) {
		return true;
	}
	return false;
}

int imageFormatVersion(void) {
	return 6502;
}

int incCompBody(void) {
    int bytesFreed;
    int fwdBlock;
    int oop;
    int bytesFreed1;
    int newOop;
    int extra;
    int type;
    int extra1;
    int originalHeader;
    int originalHeaderType;
    int extra2;
    int type1;
    int extra11;
    int sz;
    int header;
    int newOop1;
    int newFreeChunk;
    int next;
    int bytesToMove;
    int w;
    int fwdBlock1;
    int oop1;
    int firstWord;
    int lastWord;
    int header1;
    int extra3;
    int type2;
    int extra12;
    int extra21;
    int type11;
    int extra111;
    int sz2;
    int fwdBlock2;
    int realHeader;
    int header2;
    int extra4;
    int type3;
    int extra13;
    int sz1;
    int header11;
    int extra22;
    int type12;
    int extra112;
    int sz3;
    int fwdBlock3;
    int realHeader1;
    int header3;
    int extra5;
    int type4;
    int extra14;
    int sz11;
    int header12;
    int extra23;
    int type13;
    int extra113;

	fwdTableInit();
	/* begin incCompMakeFwd */
	bytesFreed1 = 0;
	/* begin oopFromChunk: */
	/* begin extraHeaderBytes: */
	type1 = (longAt(compStart)) & 3;
	if (type1 > 1) {
		extra11 = 0;
	} else {
		if (type1 == 1) {
			extra11 = 4;
		} else {
			extra11 = 8;
		}
	}
	extra2 = extra11;
	oop = compStart + extra2;
	while (oop < endOfMemory) {
		if (((longAt(oop)) & 3) == 2) {
			bytesFreed1 += (longAt(oop)) & 536870908;
		} else {
			/* begin fwdBlockGet */
			fwdTableNext += 8;
			if (fwdTableNext <= fwdTableLast) {
				fwdBlock = fwdTableNext;
				goto l1;
			} else {
				fwdBlock = null;
				goto l1;
			}
		l1:	/* end fwdBlockGet */;
			if (fwdBlock == null) {
				/* begin chunkFromOop: */
				/* begin extraHeaderBytes: */
				type = (longAt(oop)) & 3;
				if (type > 1) {
					extra1 = 0;
				} else {
					if (type == 1) {
						extra1 = 4;
					} else {
						extra1 = 8;
					}
				}
				extra = extra1;
				compEnd = oop - extra;
				bytesFreed = bytesFreed1;
				goto l2;
			}
			newOop = oop - bytesFreed1;
			/* begin initForwardBlock:mapping:to: */
			originalHeader = longAt(oop);
			if (checkAssertions) {
				if (fwdBlock == null) {
					error("ran out of forwarding blocks in become");
				}
				if ((originalHeader & 2147483648U) != 0) {
					error("object already has a forwarding table entry");
				}
			}
			originalHeaderType = originalHeader & 3;
			longAtput(fwdBlock, newOop);
			longAtput(fwdBlock + 4, originalHeader);
			longAtput(oop, fwdBlock | (2147483648U | originalHeaderType));
		}
		/* begin objectAfterWhileForwarding: */
		header2 = longAt(oop);
		if ((header2 & 2147483648U) == 0) {
			/* begin objectAfter: */
			if (checkAssertions) {
				if (oop >= endOfMemory) {
					error("no objects after the end of memory");
				}
			}
			if (((longAt(oop)) & 3) == 2) {
				sz1 = (longAt(oop)) & 536870908;
			} else {
				/* begin sizeBitsOf: */
				header11 = longAt(oop);
				if ((header11 & 3) == 0) {
					sz1 = (longAt(oop - 8)) & 4294967292U;
					goto l4;
				} else {
					sz1 = header11 & 252;
					goto l4;
				}
			l4:	/* end sizeBitsOf: */;
			}
			/* begin oopFromChunk: */
			/* begin extraHeaderBytes: */
			type12 = (longAt(oop + sz1)) & 3;
			if (type12 > 1) {
				extra112 = 0;
			} else {
				if (type12 == 1) {
					extra112 = 4;
				} else {
					extra112 = 8;
				}
			}
			extra22 = extra112;
			oop = (oop + sz1) + extra22;
			goto l5;
		}
		fwdBlock2 = header2 & 2147483644;
		if (checkAssertions) {
			/* begin fwdBlockValidate: */
			if (!((fwdBlock2 > endOfMemory) && ((fwdBlock2 <= fwdTableNext) && ((fwdBlock2 & 3) == 0)))) {
				error("invalid fwd table entry");
			}
		}
		realHeader = longAt(fwdBlock2 + 4);
		if ((realHeader & 3) == 0) {
			sz2 = (longAt(oop - 8)) & 268435452;
		} else {
			sz2 = realHeader & 252;
		}
		/* begin oopFromChunk: */
		/* begin extraHeaderBytes: */
		type3 = (longAt(oop + sz2)) & 3;
		if (type3 > 1) {
			extra13 = 0;
		} else {
			if (type3 == 1) {
				extra13 = 4;
			} else {
				extra13 = 8;
			}
		}
		extra4 = extra13;
		oop = (oop + sz2) + extra4;
	l5:	/* end objectAfterWhileForwarding: */;
	}
	compEnd = endOfMemory;
	bytesFreed = bytesFreed1;
l2:	/* end incCompMakeFwd */;
	mapPointersInObjectsFromto(youngStart, endOfMemory);
	/* begin incCompMove: */
	newOop1 = null;
	/* begin oopFromChunk: */
	/* begin extraHeaderBytes: */
	type11 = (longAt(compStart)) & 3;
	if (type11 > 1) {
		extra111 = 0;
	} else {
		if (type11 == 1) {
			extra111 = 4;
		} else {
			extra111 = 8;
		}
	}
	extra21 = extra111;
	oop1 = compStart + extra21;
	while (oop1 < compEnd) {
		/* begin objectAfterWhileForwarding: */
		header3 = longAt(oop1);
		if ((header3 & 2147483648U) == 0) {
			/* begin objectAfter: */
			if (checkAssertions) {
				if (oop1 >= endOfMemory) {
					error("no objects after the end of memory");
				}
			}
			if (((longAt(oop1)) & 3) == 2) {
				sz11 = (longAt(oop1)) & 536870908;
			} else {
				/* begin sizeBitsOf: */
				header12 = longAt(oop1);
				if ((header12 & 3) == 0) {
					sz11 = (longAt(oop1 - 8)) & 4294967292U;
					goto l6;
				} else {
					sz11 = header12 & 252;
					goto l6;
				}
			l6:	/* end sizeBitsOf: */;
			}
			/* begin oopFromChunk: */
			/* begin extraHeaderBytes: */
			type13 = (longAt(oop1 + sz11)) & 3;
			if (type13 > 1) {
				extra113 = 0;
			} else {
				if (type13 == 1) {
					extra113 = 4;
				} else {
					extra113 = 8;
				}
			}
			extra23 = extra113;
			next = (oop1 + sz11) + extra23;
			goto l7;
		}
		fwdBlock3 = header3 & 2147483644;
		if (checkAssertions) {
			/* begin fwdBlockValidate: */
			if (!((fwdBlock3 > endOfMemory) && ((fwdBlock3 <= fwdTableNext) && ((fwdBlock3 & 3) == 0)))) {
				error("invalid fwd table entry");
			}
		}
		realHeader1 = longAt(fwdBlock3 + 4);
		if ((realHeader1 & 3) == 0) {
			sz3 = (longAt(oop1 - 8)) & 268435452;
		} else {
			sz3 = realHeader1 & 252;
		}
		/* begin oopFromChunk: */
		/* begin extraHeaderBytes: */
		type4 = (longAt(oop1 + sz3)) & 3;
		if (type4 > 1) {
			extra14 = 0;
		} else {
			if (type4 == 1) {
				extra14 = 4;
			} else {
				extra14 = 8;
			}
		}
		extra5 = extra14;
		next = (oop1 + sz3) + extra5;
	l7:	/* end objectAfterWhileForwarding: */;
		if (!(((longAt(oop1)) & 3) == 2)) {
			fwdBlock1 = (longAt(oop1)) & 2147483644;
			if (checkAssertions) {
				/* begin fwdBlockValidate: */
				if (!((fwdBlock1 > endOfMemory) && ((fwdBlock1 <= fwdTableNext) && ((fwdBlock1 & 3) == 0)))) {
					error("invalid fwd table entry");
				}
			}
			newOop1 = longAt(fwdBlock1);
			header = longAt(fwdBlock1 + 4);
			longAtput(oop1, header);
			bytesToMove = oop1 - newOop1;
			/* begin sizeBitsOf: */
			header1 = longAt(oop1);
			if ((header1 & 3) == 0) {
				sz = (longAt(oop1 - 8)) & 4294967292U;
				goto l3;
			} else {
				sz = header1 & 252;
				goto l3;
			}
		l3:	/* end sizeBitsOf: */;
			firstWord = oop1 - (extraHeaderBytes(oop1));
			lastWord = (oop1 + sz) - 4;
			for (w = firstWord; w <= lastWord; w += 4) {
				longAtput(w - bytesToMove, longAt(w));
			}
		}
		oop1 = next;
	}
	if (newOop1 == null) {
		/* begin oopFromChunk: */
		/* begin extraHeaderBytes: */
		type2 = (longAt(compStart)) & 3;
		if (type2 > 1) {
			extra12 = 0;
		} else {
			if (type2 == 1) {
				extra12 = 4;
			} else {
				extra12 = 8;
			}
		}
		extra3 = extra12;
		oop1 = compStart + extra3;
		if ((((longAt(oop1)) & 3) == 2) && ((objectAfter(oop1)) == (oopFromChunk(compEnd)))) {
			newFreeChunk = oop1;
		} else {
			newFreeChunk = freeBlock;
		}
	} else {
		newFreeChunk = newOop1 + (sizeBitsOf(newOop1));
		/* begin setSizeOfFree:to: */
		longAtput(newFreeChunk, (bytesFreed & 536870908) | 2);
	}
	if (checkAssertions) {
		if (!((objectAfter(newFreeChunk)) == (oopFromChunk(compEnd)))) {
			error("problem creating free chunk after compaction");
		}
	}
	if ((objectAfter(newFreeChunk)) == endOfMemory) {
		initializeMemoryFirstFree(newFreeChunk);
	} else {
		initializeMemoryFirstFree(freeBlock);
	}
	return newFreeChunk;
}

int incCompMakeFwd(void) {
    int fwdBlock;
    int oop;
    int bytesFreed;
    int newOop;
    int extra;
    int type;
    int extra1;
    int originalHeader;
    int originalHeaderType;
    int extra2;
    int type1;
    int extra11;
    int sz;
    int fwdBlock1;
    int realHeader;
    int header;
    int extra3;
    int type2;
    int extra12;
    int sz1;
    int header1;
    int extra21;
    int type11;
    int extra111;

	bytesFreed = 0;
	/* begin oopFromChunk: */
	/* begin extraHeaderBytes: */
	type1 = (longAt(compStart)) & 3;
	if (type1 > 1) {
		extra11 = 0;
	} else {
		if (type1 == 1) {
			extra11 = 4;
		} else {
			extra11 = 8;
		}
	}
	extra2 = extra11;
	oop = compStart + extra2;
	while (oop < endOfMemory) {
		if (((longAt(oop)) & 3) == 2) {
			bytesFreed += (longAt(oop)) & 536870908;
		} else {
			/* begin fwdBlockGet */
			fwdTableNext += 8;
			if (fwdTableNext <= fwdTableLast) {
				fwdBlock = fwdTableNext;
				goto l1;
			} else {
				fwdBlock = null;
				goto l1;
			}
		l1:	/* end fwdBlockGet */;
			if (fwdBlock == null) {
				/* begin chunkFromOop: */
				/* begin extraHeaderBytes: */
				type = (longAt(oop)) & 3;
				if (type > 1) {
					extra1 = 0;
				} else {
					if (type == 1) {
						extra1 = 4;
					} else {
						extra1 = 8;
					}
				}
				extra = extra1;
				compEnd = oop - extra;
				return bytesFreed;
			}
			newOop = oop - bytesFreed;
			/* begin initForwardBlock:mapping:to: */
			originalHeader = longAt(oop);
			if (checkAssertions) {
				if (fwdBlock == null) {
					error("ran out of forwarding blocks in become");
				}
				if ((originalHeader & 2147483648U) != 0) {
					error("object already has a forwarding table entry");
				}
			}
			originalHeaderType = originalHeader & 3;
			longAtput(fwdBlock, newOop);
			longAtput(fwdBlock + 4, originalHeader);
			longAtput(oop, fwdBlock | (2147483648U | originalHeaderType));
		}
		/* begin objectAfterWhileForwarding: */
		header = longAt(oop);
		if ((header & 2147483648U) == 0) {
			/* begin objectAfter: */
			if (checkAssertions) {
				if (oop >= endOfMemory) {
					error("no objects after the end of memory");
				}
			}
			if (((longAt(oop)) & 3) == 2) {
				sz1 = (longAt(oop)) & 536870908;
			} else {
				/* begin sizeBitsOf: */
				header1 = longAt(oop);
				if ((header1 & 3) == 0) {
					sz1 = (longAt(oop - 8)) & 4294967292U;
					goto l2;
				} else {
					sz1 = header1 & 252;
					goto l2;
				}
			l2:	/* end sizeBitsOf: */;
			}
			/* begin oopFromChunk: */
			/* begin extraHeaderBytes: */
			type11 = (longAt(oop + sz1)) & 3;
			if (type11 > 1) {
				extra111 = 0;
			} else {
				if (type11 == 1) {
					extra111 = 4;
				} else {
					extra111 = 8;
				}
			}
			extra21 = extra111;
			oop = (oop + sz1) + extra21;
			goto l3;
		}
		fwdBlock1 = header & 2147483644;
		if (checkAssertions) {
			/* begin fwdBlockValidate: */
			if (!((fwdBlock1 > endOfMemory) && ((fwdBlock1 <= fwdTableNext) && ((fwdBlock1 & 3) == 0)))) {
				error("invalid fwd table entry");
			}
		}
		realHeader = longAt(fwdBlock1 + 4);
		if ((realHeader & 3) == 0) {
			sz = (longAt(oop - 8)) & 268435452;
		} else {
			sz = realHeader & 252;
		}
		/* begin oopFromChunk: */
		/* begin extraHeaderBytes: */
		type2 = (longAt(oop + sz)) & 3;
		if (type2 > 1) {
			extra12 = 0;
		} else {
			if (type2 == 1) {
				extra12 = 4;
			} else {
				extra12 = 8;
			}
		}
		extra3 = extra12;
		oop = (oop + sz) + extra3;
	l3:	/* end objectAfterWhileForwarding: */;
	}
	compEnd = endOfMemory;
	return bytesFreed;
}

int incCompMove(int bytesFreed) {
    int sz;
    int header;
    int newOop;
    int newFreeChunk;
    int next;
    int bytesToMove;
    int w;
    int fwdBlock;
    int oop;
    int firstWord;
    int lastWord;
    int header1;
    int extra;
    int type;
    int extra1;
    int extra2;
    int type1;
    int extra11;
    int sz2;
    int fwdBlock1;
    int realHeader;
    int header2;
    int extra3;
    int type2;
    int extra12;
    int sz1;
    int header11;
    int extra21;
    int type11;
    int extra111;

	newOop = null;
	/* begin oopFromChunk: */
	/* begin extraHeaderBytes: */
	type1 = (longAt(compStart)) & 3;
	if (type1 > 1) {
		extra11 = 0;
	} else {
		if (type1 == 1) {
			extra11 = 4;
		} else {
			extra11 = 8;
		}
	}
	extra2 = extra11;
	oop = compStart + extra2;
	while (oop < compEnd) {
		/* begin objectAfterWhileForwarding: */
		header2 = longAt(oop);
		if ((header2 & 2147483648U) == 0) {
			/* begin objectAfter: */
			if (checkAssertions) {
				if (oop >= endOfMemory) {
					error("no objects after the end of memory");
				}
			}
			if (((longAt(oop)) & 3) == 2) {
				sz1 = (longAt(oop)) & 536870908;
			} else {
				/* begin sizeBitsOf: */
				header11 = longAt(oop);
				if ((header11 & 3) == 0) {
					sz1 = (longAt(oop - 8)) & 4294967292U;
					goto l2;
				} else {
					sz1 = header11 & 252;
					goto l2;
				}
			l2:	/* end sizeBitsOf: */;
			}
			/* begin oopFromChunk: */
			/* begin extraHeaderBytes: */
			type11 = (longAt(oop + sz1)) & 3;
			if (type11 > 1) {
				extra111 = 0;
			} else {
				if (type11 == 1) {
					extra111 = 4;
				} else {
					extra111 = 8;
				}
			}
			extra21 = extra111;
			next = (oop + sz1) + extra21;
			goto l3;
		}
		fwdBlock1 = header2 & 2147483644;
		if (checkAssertions) {
			/* begin fwdBlockValidate: */
			if (!((fwdBlock1 > endOfMemory) && ((fwdBlock1 <= fwdTableNext) && ((fwdBlock1 & 3) == 0)))) {
				error("invalid fwd table entry");
			}
		}
		realHeader = longAt(fwdBlock1 + 4);
		if ((realHeader & 3) == 0) {
			sz2 = (longAt(oop - 8)) & 268435452;
		} else {
			sz2 = realHeader & 252;
		}
		/* begin oopFromChunk: */
		/* begin extraHeaderBytes: */
		type2 = (longAt(oop + sz2)) & 3;
		if (type2 > 1) {
			extra12 = 0;
		} else {
			if (type2 == 1) {
				extra12 = 4;
			} else {
				extra12 = 8;
			}
		}
		extra3 = extra12;
		next = (oop + sz2) + extra3;
	l3:	/* end objectAfterWhileForwarding: */;
		if (!(((longAt(oop)) & 3) == 2)) {
			fwdBlock = (longAt(oop)) & 2147483644;
			if (checkAssertions) {
				/* begin fwdBlockValidate: */
				if (!((fwdBlock > endOfMemory) && ((fwdBlock <= fwdTableNext) && ((fwdBlock & 3) == 0)))) {
					error("invalid fwd table entry");
				}
			}
			newOop = longAt(fwdBlock);
			header = longAt(fwdBlock + 4);
			longAtput(oop, header);
			bytesToMove = oop - newOop;
			/* begin sizeBitsOf: */
			header1 = longAt(oop);
			if ((header1 & 3) == 0) {
				sz = (longAt(oop - 8)) & 4294967292U;
				goto l1;
			} else {
				sz = header1 & 252;
				goto l1;
			}
		l1:	/* end sizeBitsOf: */;
			firstWord = oop - (extraHeaderBytes(oop));
			lastWord = (oop + sz) - 4;
			for (w = firstWord; w <= lastWord; w += 4) {
				longAtput(w - bytesToMove, longAt(w));
			}
		}
		oop = next;
	}
	if (newOop == null) {
		/* begin oopFromChunk: */
		/* begin extraHeaderBytes: */
		type = (longAt(compStart)) & 3;
		if (type > 1) {
			extra1 = 0;
		} else {
			if (type == 1) {
				extra1 = 4;
			} else {
				extra1 = 8;
			}
		}
		extra = extra1;
		oop = compStart + extra;
		if ((((longAt(oop)) & 3) == 2) && ((objectAfter(oop)) == (oopFromChunk(compEnd)))) {
			newFreeChunk = oop;
		} else {
			newFreeChunk = freeBlock;
		}
	} else {
		newFreeChunk = newOop + (sizeBitsOf(newOop));
		/* begin setSizeOfFree:to: */
		longAtput(newFreeChunk, (bytesFreed & 536870908) | 2);
	}
	if (checkAssertions) {
		if (!((objectAfter(newFreeChunk)) == (oopFromChunk(compEnd)))) {
			error("problem creating free chunk after compaction");
		}
	}
	if ((objectAfter(newFreeChunk)) == endOfMemory) {
		initializeMemoryFirstFree(newFreeChunk);
	} else {
		initializeMemoryFirstFree(freeBlock);
	}
	return newFreeChunk;
}

int incrementalCompaction(void) {
	if (compStart == freeBlock) {
		initializeMemoryFirstFree(freeBlock);
	} else {
		incCompBody();
	}
}

int incrementalGC(void) {
    int startTime;
    int survivorCount;
    int oop;
    int i;

	if (rootTableCount >= 1000) {
		statRootTableOverflows += 1;
		return fullGC();
	}
	/* begin preGCAction: */
	startTime = ioMicroMSecs();
	markPhase();
	survivorCount = sweepPhase();
	/* begin incrementalCompaction */
	if (compStart == freeBlock) {
		initializeMemoryFirstFree(freeBlock);
	} else {
		incCompBody();
	}
	allocationCount = 0;
	statIncrGCs += 1;
	statIncrGCMSecs += (ioMicroMSecs()) - startTime;
	if (survivorCount > tenuringThreshold) {
		statTenures += 1;
		/* begin clearRootsTable */
		for (i = 1; i <= rootTableCount; i += 1) {
			oop = rootTable[i];
			longAtput(oop, (longAt(oop)) & 3221225471U);
			rootTable[i] = 0;
		}
		rootTableCount = 0;
		youngStart = freeBlock;
	}
	/* begin postGCAction */
	if (activeContext < youngStart) {
		beRootIfOld(activeContext);
	}
	if (theHomeContext < youngStart) {
		beRootIfOld(theHomeContext);
	}
}

int initBBOpTable(void) {
	opTable[0+1] = (int)clearWordwith;
	opTable[1+1] = (int)bitAndwith;
	opTable[2+1] = (int)bitAndInvertwith;
	opTable[3+1] = (int)sourceWordwith;
	opTable[4+1] = (int)bitInvertAndwith;
	opTable[5+1] = (int)destinationWordwith;
	opTable[6+1] = (int)bitXorwith;
	opTable[7+1] = (int)bitOrwith;
	opTable[8+1] = (int)bitInvertAndInvertwith;
	opTable[9+1] = (int)bitInvertXorwith;
	opTable[10+1] = (int)bitInvertDestinationwith;
	opTable[11+1] = (int)bitOrInvertwith;
	opTable[12+1] = (int)bitInvertSourcewith;
	opTable[13+1] = (int)bitInvertOrwith;
	opTable[14+1] = (int)bitInvertOrInvertwith;
	opTable[15+1] = (int)destinationWordwith;
	opTable[16+1] = (int)destinationWordwith;
	opTable[17+1] = (int)destinationWordwith;
	opTable[18+1] = (int)addWordwith;
	opTable[19+1] = (int)subWordwith;
	opTable[20+1] = (int)rgbAddwith;
	opTable[21+1] = (int)rgbSubwith;
	opTable[22+1] = (int)OLDrgbDiffwith;
	opTable[23+1] = (int)OLDtallyIntoMapwith;
	opTable[24+1] = (int)alphaBlendwith;
	opTable[25+1] = (int)pixPaintwith;
	opTable[26+1] = (int)pixMaskwith;
	opTable[27+1] = (int)rgbMaxwith;
	opTable[28+1] = (int)rgbMinwith;
	opTable[29+1] = (int)rgbMinInvertwith;
	opTable[30+1] = (int)alphaBlendConstwith;
	opTable[31+1] = (int)alphaPaintConstwith;
	opTable[32+1] = (int)rgbDiffwith;
	opTable[33+1] = (int)tallyIntoMapwith;
}

int initForwardBlockmappingto(int fwdBlock, int oop, int newOop) {
    int originalHeader;
    int originalHeaderType;

	originalHeader = longAt(oop);
	if (checkAssertions) {
		if (fwdBlock == null) {
			error("ran out of forwarding blocks in become");
		}
		if ((originalHeader & 2147483648U) != 0) {
			error("object already has a forwarding table entry");
		}
	}
	originalHeaderType = originalHeader & 3;
	longAtput(fwdBlock, newOop);
	longAtput(fwdBlock + 4, originalHeader);
	longAtput(oop, fwdBlock | (2147483648U | originalHeaderType));
}

int initialInstanceOf(int classPointer) {
    int thisClass;
    int thisObj;
    int ccIndex;
    int obj;
    int chunk;
    int extra;
    int type;
    int extra1;
    int sz;
    int header;
    int extra2;
    int type1;
    int extra11;

	/* begin firstAccessibleObject */
	/* begin oopFromChunk: */
	chunk = startOfMemory();
	/* begin extraHeaderBytes: */
	type = (longAt(chunk)) & 3;
	if (type > 1) {
		extra1 = 0;
	} else {
		if (type == 1) {
			extra1 = 4;
		} else {
			extra1 = 8;
		}
	}
	extra = extra1;
	obj = chunk + extra;
	while (obj < endOfMemory) {
		if (!(((longAt(obj)) & 3) == 2)) {
			thisObj = obj;
			goto l3;
		}
		/* begin objectAfter: */
		if (checkAssertions) {
			if (obj >= endOfMemory) {
				error("no objects after the end of memory");
			}
		}
		if (((longAt(obj)) & 3) == 2) {
			sz = (longAt(obj)) & 536870908;
		} else {
			/* begin sizeBitsOf: */
			header = longAt(obj);
			if ((header & 3) == 0) {
				sz = (longAt(obj - 8)) & 4294967292U;
				goto l2;
			} else {
				sz = header & 252;
				goto l2;
			}
		l2:	/* end sizeBitsOf: */;
		}
		/* begin oopFromChunk: */
		/* begin extraHeaderBytes: */
		type1 = (longAt(obj + sz)) & 3;
		if (type1 > 1) {
			extra11 = 0;
		} else {
			if (type1 == 1) {
				extra11 = 4;
			} else {
				extra11 = 8;
			}
		}
		extra2 = extra11;
		obj = (obj + sz) + extra2;
	}
	error("heap is empty");
l3:	/* end firstAccessibleObject */;
	while (!(thisObj == null)) {
		/* begin fetchClassOf: */
		if ((thisObj & 1)) {
			thisClass = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
			goto l1;
		}
		ccIndex = ((((unsigned) (longAt(thisObj))) >> 12) & 31) - 1;
		if (ccIndex < 0) {
			thisClass = (longAt(thisObj - 4)) & 4294967292U;
			goto l1;
		} else {
			thisClass = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
			goto l1;
		}
	l1:	/* end fetchClassOf: */;
		if (thisClass == classPointer) {
			return thisObj;
		}
		thisObj = accessibleObjectAfter(thisObj);
	}
	return nilObj;
}

int initializeInterpreter(int bytesToShift) {
    int i;
    int sched;
    int proc;
    int activeCntx;
    int tmp;

	initializeObjectMemory(bytesToShift);
	initBBOpTable();
	activeContext = nilObj;
	theHomeContext = nilObj;
	method = nilObj;
	receiver = nilObj;
	messageSelector = nilObj;
	newMethod = nilObj;
	/* begin flushMethodCache */
	for (i = 1; i <= 2048; i += 1) {
		methodCache[i] = 0;
	}
	mcProbe = 0;
	/* begin loadInitialContext */
	sched = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (3 << 2))))) + 4) + (1 << 2));
	proc = longAt(((((char *) sched)) + 4) + (1 << 2));
	activeContext = longAt(((((char *) proc)) + 4) + (1 << 2));
	if (activeContext < youngStart) {
		beRootIfOld(activeContext);
	}
	/* begin fetchContextRegisters: */
	activeCntx = activeContext;
	tmp = longAt(((((char *) activeCntx)) + 4) + (3 << 2));
	if ((tmp & 1)) {
		tmp = longAt(((((char *) activeCntx)) + 4) + (5 << 2));
		if (tmp < youngStart) {
			beRootIfOld(tmp);
		}
	} else {
		tmp = activeCntx;
	}
	theHomeContext = tmp;
	receiver = longAt(((((char *) tmp)) + 4) + (5 << 2));
	method = longAt(((((char *) tmp)) + 4) + (3 << 2));
	tmp = ((longAt(((((char *) activeCntx)) + 4) + (1 << 2))) >> 1);
	instructionPointer = ((method + tmp) + 4) - 2;
	tmp = ((longAt(((((char *) activeCntx)) + 4) + (2 << 2))) >> 1);
	stackPointer = (activeCntx + 4) + (((6 + tmp) - 1) * 4);
	reclaimableContextCount = 0;
	interruptCheckCounter = 0;
	nextPollTick = 0;
	nextWakeupTick = 0;
	lastTick = 0;
	interruptKeycode = 2094;
	interruptPending = false;
	semaphoresToSignalCount = 0;
	deferDisplayUpdates = false;
}

int initializeMemoryFirstFree(int firstFree) {
    int fwdBlockBytes;

	fwdBlockBytes = 16000;
	if (!((memoryLimit - fwdBlockBytes) >= (firstFree + 4))) {
		fwdBlockBytes = memoryLimit - (firstFree + 4);
	}
	endOfMemory = memoryLimit - fwdBlockBytes;
	freeBlock = firstFree;
	/* begin setSizeOfFree:to: */
	longAtput(freeBlock, ((endOfMemory - firstFree) & 536870908) | 2);
	/* begin setSizeOfFree:to: */
	longAtput(endOfMemory, (4 & 536870908) | 2);
	if (checkAssertions) {
		if (!((freeBlock < endOfMemory) && (endOfMemory < memoryLimit))) {
			error("error in free space computation");
		}
		if (!((oopFromChunk(endOfMemory)) == endOfMemory)) {
			error("header format must have changed");
		}
		if (!((objectAfter(freeBlock)) == endOfMemory)) {
			error("free block not properly initialized");
		}
	}
}

int initializeObjectMemory(int bytesToShift) {
    int oop;
    int last;
    int newClassOop;
    int fieldAddr;
    int fieldOop;
    int classHeader;
    int chunk;
    int extra;
    int type;
    int extra1;
    int sz;
    int header;
    int extra2;
    int type1;
    int extra11;

	checkAssertions = false;
	youngStart = endOfMemory;
	initializeMemoryFirstFree(endOfMemory);
	/* begin adjustAllOopsBy: */
	if (bytesToShift == 0) {
		goto l2;
	}
	/* begin oopFromChunk: */
	chunk = startOfMemory();
	/* begin extraHeaderBytes: */
	type = (longAt(chunk)) & 3;
	if (type > 1) {
		extra1 = 0;
	} else {
		if (type == 1) {
			extra1 = 4;
		} else {
			extra1 = 8;
		}
	}
	extra = extra1;
	oop = chunk + extra;
	while (oop < endOfMemory) {
		if (!(((longAt(oop)) & 3) == 2)) {
			/* begin adjustFieldsAndClassOf:by: */
			fieldAddr = oop + (lastPointerOf(oop));
			while (fieldAddr > oop) {
				fieldOop = longAt(fieldAddr);
				if (!((fieldOop & 1))) {
					longAtput(fieldAddr, fieldOop + bytesToShift);
				}
				fieldAddr -= 4;
			}
			if (((longAt(oop)) & 3) != 3) {
				classHeader = longAt(oop - 4);
				newClassOop = (classHeader & 4294967292U) + bytesToShift;
				longAtput(oop - 4, newClassOop | (classHeader & 3));
			}
		}
		last = oop;
		/* begin objectAfter: */
		if (checkAssertions) {
			if (oop >= endOfMemory) {
				error("no objects after the end of memory");
			}
		}
		if (((longAt(oop)) & 3) == 2) {
			sz = (longAt(oop)) & 536870908;
		} else {
			/* begin sizeBitsOf: */
			header = longAt(oop);
			if ((header & 3) == 0) {
				sz = (longAt(oop - 8)) & 4294967292U;
				goto l1;
			} else {
				sz = header & 252;
				goto l1;
			}
		l1:	/* end sizeBitsOf: */;
		}
		/* begin oopFromChunk: */
		/* begin extraHeaderBytes: */
		type1 = (longAt(oop + sz)) & 3;
		if (type1 > 1) {
			extra11 = 0;
		} else {
			if (type1 == 1) {
				extra11 = 4;
			} else {
				extra11 = 8;
			}
		}
		extra2 = extra11;
		oop = (oop + sz) + extra2;
	}
l2:	/* end adjustAllOopsBy: */;
	specialObjectsOop += bytesToShift;
	nilObj = longAt(((((char *) specialObjectsOop)) + 4) + (0 << 2));
	falseObj = longAt(((((char *) specialObjectsOop)) + 4) + (1 << 2));
	trueObj = longAt(((((char *) specialObjectsOop)) + 4) + (2 << 2));
	rootTableCount = 0;
	child = 0;
	field = 0;
	parentField = 0;
	freeLargeContexts = 1;
	freeSmallContexts = 1;
	allocationCount = 0;
	lowSpaceThreshold = 0;
	signalLowSpace = false;
	compStart = 0;
	compEnd = 0;
	fwdTableNext = 0;
	fwdTableLast = 0;
	remapBufferCount = 0;
	allocationsBetweenGCs = 4000;
	tenuringThreshold = 2000;
	statFullGCs = 0;
	statFullGCMSecs = 0;
	statIncrGCs = 0;
	statIncrGCMSecs = 0;
	statTenures = 0;
	statRootTableOverflows = 0;
	displayBits = 0;
}

int instanceAfter(int objectPointer) {
    int thisClass;
    int classPointer;
    int thisObj;
    int ccIndex;
    int ccIndex1;

	/* begin fetchClassOf: */
	if ((objectPointer & 1)) {
		classPointer = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
		goto l2;
	}
	ccIndex1 = ((((unsigned) (longAt(objectPointer))) >> 12) & 31) - 1;
	if (ccIndex1 < 0) {
		classPointer = (longAt(objectPointer - 4)) & 4294967292U;
		goto l2;
	} else {
		classPointer = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex1 << 2));
		goto l2;
	}
l2:	/* end fetchClassOf: */;
	thisObj = accessibleObjectAfter(objectPointer);
	while (!(thisObj == null)) {
		/* begin fetchClassOf: */
		if ((thisObj & 1)) {
			thisClass = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
			goto l1;
		}
		ccIndex = ((((unsigned) (longAt(thisObj))) >> 12) & 31) - 1;
		if (ccIndex < 0) {
			thisClass = (longAt(thisObj - 4)) & 4294967292U;
			goto l1;
		} else {
			thisClass = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
			goto l1;
		}
	l1:	/* end fetchClassOf: */;
		if (thisClass == classPointer) {
			return thisObj;
		}
		thisObj = accessibleObjectAfter(thisObj);
	}
	return nilObj;
}

int instantiateClassindexableSize(int classPointer, int size) {
    int sizeHiBits;
    int newObj;
    int binc;
    int hash;
    int header1;
    int header2;
    int header3;
    int hdrSize;
    int byteSize;
    int format;
    int inc;
    int cClass;
    int fillWord;
    int i;
    int newObj1;
    int remappedClassOop;
    int end;
    int oop;
    int newFreeSize;
    int enoughSpace;
    int newChunk;
    int minFree;

	if (checkAssertions) {
		if (size < 0) {
			error("cannot have a negative indexable field count");
		}
	}
	/* begin newObjectHash */
	lastHash = (13849 + (27181 * lastHash)) & 65535;
	hash = lastHash;
	header1 = (longAt(((((char *) classPointer)) + 4) + (2 << 2))) - 1;
	sizeHiBits = ((unsigned) (header1 & 393216)) >> 9;
	header1 = (header1 & 131071) | ((hash << 17) & 536739840);
	header2 = classPointer;
	header3 = 0;
	cClass = header1 & 126976;
	byteSize = (header1 & 252) + sizeHiBits;
	format = (((unsigned) header1) >> 8) & 15;
	if (format < 8) {
		inc = size * 4;
	} else {
		inc = (size + 3) & 536870908;
		binc = 3 - ((size + 3) & 3);
		header1 = header1 | (binc << 8);
	}
	if ((byteSize + inc) > 255) {
		header3 = byteSize + inc;
		header1 -= byteSize & 255;
	} else {
		header1 += inc;
	}
	byteSize += inc;
	if (header3 > 0) {
		hdrSize = 3;
	} else {
		if (cClass == 0) {
			hdrSize = 2;
		} else {
			hdrSize = 1;
		}
	}
	if (format < 4) {
		fillWord = nilObj;
	} else {
		fillWord = 0;
	}
	/* begin allocate:headerSize:h1:h2:h3:fill: */
	if (hdrSize > 1) {
		/* begin pushRemappableOop: */
		remapBuffer[remapBufferCount += 1] = header2;
	}
	/* begin allocateChunk: */
	if (allocationCount >= allocationsBetweenGCs) {
		incrementalGC();
	}
	/* begin sufficientSpaceToAllocate: */
	minFree = (lowSpaceThreshold + (byteSize + ((hdrSize - 1) * 4))) + 4;
	if (((longAt(freeBlock)) & 536870908) >= minFree) {
		enoughSpace = true;
		goto l1;
	} else {
		enoughSpace = sufficientSpaceAfterGC(minFree);
		goto l1;
	}
l1:	/* end sufficientSpaceToAllocate: */;
	if (!(enoughSpace)) {
		signalLowSpace = true;
		lowSpaceThreshold = 0;
		interruptCheckCounter = 0;
	}
	if (((longAt(freeBlock)) & 536870908) < ((byteSize + ((hdrSize - 1) * 4)) + 4)) {
		error("out of memory");
	}
	newFreeSize = ((longAt(freeBlock)) & 536870908) - (byteSize + ((hdrSize - 1) * 4));
	newChunk = freeBlock;
	freeBlock += byteSize + ((hdrSize - 1) * 4);
	/* begin setSizeOfFree:to: */
	longAtput(freeBlock, (newFreeSize & 536870908) | 2);
	allocationCount += 1;
	newObj1 = newChunk;
	if (hdrSize > 1) {
		/* begin popRemappableOop */
		oop = remapBuffer[remapBufferCount];
		remapBufferCount -= 1;
		remappedClassOop = oop;
	}
	if (hdrSize == 3) {
		longAtput(newObj1, header3 | 0);
		longAtput(newObj1 + 4, remappedClassOop | 0);
		longAtput(newObj1 + 8, header1 | 0);
		newObj1 += 8;
	}
	if (hdrSize == 2) {
		longAtput(newObj1, remappedClassOop | 1);
		longAtput(newObj1 + 4, header1 | 1);
		newObj1 += 4;
	}
	if (hdrSize == 1) {
		longAtput(newObj1, header1 | 3);
	}
	end = newObj1 + byteSize;
	i = newObj1 + 4;
	while (i < end) {
		longAtput(i, fillWord);
		i += 4;
	}
	if (checkAssertions) {
		okayOop(newObj1);
		oopHasOkayClass(newObj1);
		if (!((objectAfter(newObj1)) == freeBlock)) {
			error("allocate bug: did not set header of new oop correctly");
		}
		if (!((objectAfter(freeBlock)) == endOfMemory)) {
			error("allocate bug: did not set header of freeBlock correctly");
		}
	}
	newObj = newObj1;
	return newObj;
}

int instantiateSmallClasssizeInBytesfill(int classPointer, int sizeInBytes, int fillValue) {
    int header1;
    int header2;
    int hdrSize;
    int hash;
    int i;
    int newObj;
    int remappedClassOop;
    int end;
    int oop;
    int newFreeSize;
    int enoughSpace;
    int newChunk;
    int minFree;

	/* begin newObjectHash */
	lastHash = (13849 + (27181 * lastHash)) & 65535;
	hash = lastHash;
	header1 = ((hash << 17) & 536739840) | ((longAt(((((char *) classPointer)) + 4) + (2 << 2))) - 1);
	header1 += sizeInBytes - (header1 & 252);
	header2 = classPointer;
	if ((header1 & 126976) == 0) {
		hdrSize = 2;
	} else {
		hdrSize = 1;
	}
	/* begin allocate:headerSize:h1:h2:h3:fill: */
	if (hdrSize > 1) {
		/* begin pushRemappableOop: */
		remapBuffer[remapBufferCount += 1] = header2;
	}
	/* begin allocateChunk: */
	if (allocationCount >= allocationsBetweenGCs) {
		incrementalGC();
	}
	/* begin sufficientSpaceToAllocate: */
	minFree = (lowSpaceThreshold + (sizeInBytes + ((hdrSize - 1) * 4))) + 4;
	if (((longAt(freeBlock)) & 536870908) >= minFree) {
		enoughSpace = true;
		goto l1;
	} else {
		enoughSpace = sufficientSpaceAfterGC(minFree);
		goto l1;
	}
l1:	/* end sufficientSpaceToAllocate: */;
	if (!(enoughSpace)) {
		signalLowSpace = true;
		lowSpaceThreshold = 0;
		interruptCheckCounter = 0;
	}
	if (((longAt(freeBlock)) & 536870908) < ((sizeInBytes + ((hdrSize - 1) * 4)) + 4)) {
		error("out of memory");
	}
	newFreeSize = ((longAt(freeBlock)) & 536870908) - (sizeInBytes + ((hdrSize - 1) * 4));
	newChunk = freeBlock;
	freeBlock += sizeInBytes + ((hdrSize - 1) * 4);
	/* begin setSizeOfFree:to: */
	longAtput(freeBlock, (newFreeSize & 536870908) | 2);
	allocationCount += 1;
	newObj = newChunk;
	if (hdrSize > 1) {
		/* begin popRemappableOop */
		oop = remapBuffer[remapBufferCount];
		remapBufferCount -= 1;
		remappedClassOop = oop;
	}
	if (hdrSize == 3) {
		longAtput(newObj, 0 | 0);
		longAtput(newObj + 4, remappedClassOop | 0);
		longAtput(newObj + 8, header1 | 0);
		newObj += 8;
	}
	if (hdrSize == 2) {
		longAtput(newObj, remappedClassOop | 1);
		longAtput(newObj + 4, header1 | 1);
		newObj += 4;
	}
	if (hdrSize == 1) {
		longAtput(newObj, header1 | 3);
	}
	end = newObj + sizeInBytes;
	i = newObj + 4;
	while (i < end) {
		longAtput(i, fillValue);
		i += 4;
	}
	if (checkAssertions) {
		okayOop(newObj);
		oopHasOkayClass(newObj);
		if (!((objectAfter(newObj)) == freeBlock)) {
			error("allocate bug: did not set header of new oop correctly");
		}
		if (!((objectAfter(freeBlock)) == endOfMemory)) {
			error("allocate bug: did not set header of freeBlock correctly");
		}
	}
	return newObj;
}

int intToNetAddress(int addr) {
    int netAddressOop;

	netAddressOop = instantiateSmallClasssizeInBytesfill(longAt(((((char *) specialObjectsOop)) + 4) + (26 << 2)), 8, 0);
	byteAtput(((((char *) netAddressOop)) + 4) + 0, (((unsigned) addr) >> 24) & 255);
	byteAtput(((((char *) netAddressOop)) + 4) + 1, (((unsigned) addr) >> 16) & 255);
	byteAtput(((((char *) netAddressOop)) + 4) + 2, (((unsigned) addr) >> 8) & 255);
	byteAtput(((((char *) netAddressOop)) + 4) + 3, addr & 255);
	return netAddressOop;
}

int integerObjectOf(int value) {
	if (value < 0) {
		return ((2147483648U + value) << 1) + 1;
	} else {
		return (value << 1) + 1;
	}
}

int integerValueOf(int objectPointer) {
	if ((objectPointer & 2147483648U) != 0) {
		return ((((unsigned) (objectPointer & 2147483647U)) >> 1) - 1073741823) - 1;
	} else {
		return ((unsigned) objectPointer) >> 1;
	}
}

int interpret(void) {
    int localTP;
    int localCP;
    char * localSP;
    char * localIP;
    int currentBytecode;
    int t1;
    int t2;
    int t3;
    int t4;
    int t5;
    int t6;
    int t7;
    int t8;
    int t9;
    int t10;
    int t11;
    int t12;
    int t13;
    int t14;
    int t15;
    int t16;
    int t17;
    int t18;
    int t19;
    int t20;
    int t21;

	/* begin internalizeIPandSP */
	localIP = ((char *) instructionPointer);
	localSP = ((char *) stackPointer);
	while (true) {
		currentBytecode = byteAt(++localIP);
		switch (currentBytecode) {
		case 0:
			/* pushReceiverVariableBytecode */
			/* begin pushReceiverVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) receiver)) + 4) + ((0 & 15) << 2)));
			break;
		case 1:
			/* pushReceiverVariableBytecode */
			/* begin pushReceiverVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) receiver)) + 4) + ((1 & 15) << 2)));
			break;
		case 2:
			/* pushReceiverVariableBytecode */
			/* begin pushReceiverVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) receiver)) + 4) + ((2 & 15) << 2)));
			break;
		case 3:
			/* pushReceiverVariableBytecode */
			/* begin pushReceiverVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) receiver)) + 4) + ((3 & 15) << 2)));
			break;
		case 4:
			/* pushReceiverVariableBytecode */
			/* begin pushReceiverVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) receiver)) + 4) + ((4 & 15) << 2)));
			break;
		case 5:
			/* pushReceiverVariableBytecode */
			/* begin pushReceiverVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) receiver)) + 4) + ((5 & 15) << 2)));
			break;
		case 6:
			/* pushReceiverVariableBytecode */
			/* begin pushReceiverVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) receiver)) + 4) + ((6 & 15) << 2)));
			break;
		case 7:
			/* pushReceiverVariableBytecode */
			/* begin pushReceiverVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) receiver)) + 4) + ((7 & 15) << 2)));
			break;
		case 8:
			/* pushReceiverVariableBytecode */
			/* begin pushReceiverVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) receiver)) + 4) + ((8 & 15) << 2)));
			break;
		case 9:
			/* pushReceiverVariableBytecode */
			/* begin pushReceiverVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) receiver)) + 4) + ((9 & 15) << 2)));
			break;
		case 10:
			/* pushReceiverVariableBytecode */
			/* begin pushReceiverVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) receiver)) + 4) + ((10 & 15) << 2)));
			break;
		case 11:
			/* pushReceiverVariableBytecode */
			/* begin pushReceiverVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) receiver)) + 4) + ((11 & 15) << 2)));
			break;
		case 12:
			/* pushReceiverVariableBytecode */
			/* begin pushReceiverVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) receiver)) + 4) + ((12 & 15) << 2)));
			break;
		case 13:
			/* pushReceiverVariableBytecode */
			/* begin pushReceiverVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) receiver)) + 4) + ((13 & 15) << 2)));
			break;
		case 14:
			/* pushReceiverVariableBytecode */
			/* begin pushReceiverVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) receiver)) + 4) + ((14 & 15) << 2)));
			break;
		case 15:
			/* pushReceiverVariableBytecode */
			/* begin pushReceiverVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) receiver)) + 4) + ((15 & 15) << 2)));
			break;
		case 16:
			/* pushTemporaryVariableBytecode */
			/* begin pushTemporaryVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) theHomeContext)) + 4) + (((16 & 15) + 6) << 2)));
			break;
		case 17:
			/* pushTemporaryVariableBytecode */
			/* begin pushTemporaryVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) theHomeContext)) + 4) + (((17 & 15) + 6) << 2)));
			break;
		case 18:
			/* pushTemporaryVariableBytecode */
			/* begin pushTemporaryVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) theHomeContext)) + 4) + (((18 & 15) + 6) << 2)));
			break;
		case 19:
			/* pushTemporaryVariableBytecode */
			/* begin pushTemporaryVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) theHomeContext)) + 4) + (((19 & 15) + 6) << 2)));
			break;
		case 20:
			/* pushTemporaryVariableBytecode */
			/* begin pushTemporaryVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) theHomeContext)) + 4) + (((20 & 15) + 6) << 2)));
			break;
		case 21:
			/* pushTemporaryVariableBytecode */
			/* begin pushTemporaryVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) theHomeContext)) + 4) + (((21 & 15) + 6) << 2)));
			break;
		case 22:
			/* pushTemporaryVariableBytecode */
			/* begin pushTemporaryVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) theHomeContext)) + 4) + (((22 & 15) + 6) << 2)));
			break;
		case 23:
			/* pushTemporaryVariableBytecode */
			/* begin pushTemporaryVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) theHomeContext)) + 4) + (((23 & 15) + 6) << 2)));
			break;
		case 24:
			/* pushTemporaryVariableBytecode */
			/* begin pushTemporaryVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) theHomeContext)) + 4) + (((24 & 15) + 6) << 2)));
			break;
		case 25:
			/* pushTemporaryVariableBytecode */
			/* begin pushTemporaryVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) theHomeContext)) + 4) + (((25 & 15) + 6) << 2)));
			break;
		case 26:
			/* pushTemporaryVariableBytecode */
			/* begin pushTemporaryVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) theHomeContext)) + 4) + (((26 & 15) + 6) << 2)));
			break;
		case 27:
			/* pushTemporaryVariableBytecode */
			/* begin pushTemporaryVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) theHomeContext)) + 4) + (((27 & 15) + 6) << 2)));
			break;
		case 28:
			/* pushTemporaryVariableBytecode */
			/* begin pushTemporaryVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) theHomeContext)) + 4) + (((28 & 15) + 6) << 2)));
			break;
		case 29:
			/* pushTemporaryVariableBytecode */
			/* begin pushTemporaryVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) theHomeContext)) + 4) + (((29 & 15) + 6) << 2)));
			break;
		case 30:
			/* pushTemporaryVariableBytecode */
			/* begin pushTemporaryVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) theHomeContext)) + 4) + (((30 & 15) + 6) << 2)));
			break;
		case 31:
			/* pushTemporaryVariableBytecode */
			/* begin pushTemporaryVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) theHomeContext)) + 4) + (((31 & 15) + 6) << 2)));
			break;
		case 32:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((32 & 31) + 1) << 2)));
			break;
		case 33:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((33 & 31) + 1) << 2)));
			break;
		case 34:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((34 & 31) + 1) << 2)));
			break;
		case 35:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((35 & 31) + 1) << 2)));
			break;
		case 36:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((36 & 31) + 1) << 2)));
			break;
		case 37:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((37 & 31) + 1) << 2)));
			break;
		case 38:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((38 & 31) + 1) << 2)));
			break;
		case 39:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((39 & 31) + 1) << 2)));
			break;
		case 40:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((40 & 31) + 1) << 2)));
			break;
		case 41:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((41 & 31) + 1) << 2)));
			break;
		case 42:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((42 & 31) + 1) << 2)));
			break;
		case 43:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((43 & 31) + 1) << 2)));
			break;
		case 44:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((44 & 31) + 1) << 2)));
			break;
		case 45:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((45 & 31) + 1) << 2)));
			break;
		case 46:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((46 & 31) + 1) << 2)));
			break;
		case 47:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((47 & 31) + 1) << 2)));
			break;
		case 48:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((48 & 31) + 1) << 2)));
			break;
		case 49:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((49 & 31) + 1) << 2)));
			break;
		case 50:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((50 & 31) + 1) << 2)));
			break;
		case 51:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((51 & 31) + 1) << 2)));
			break;
		case 52:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((52 & 31) + 1) << 2)));
			break;
		case 53:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((53 & 31) + 1) << 2)));
			break;
		case 54:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((54 & 31) + 1) << 2)));
			break;
		case 55:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((55 & 31) + 1) << 2)));
			break;
		case 56:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((56 & 31) + 1) << 2)));
			break;
		case 57:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((57 & 31) + 1) << 2)));
			break;
		case 58:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((58 & 31) + 1) << 2)));
			break;
		case 59:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((59 & 31) + 1) << 2)));
			break;
		case 60:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((60 & 31) + 1) << 2)));
			break;
		case 61:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((61 & 31) + 1) << 2)));
			break;
		case 62:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((62 & 31) + 1) << 2)));
			break;
		case 63:
			/* pushLiteralConstantBytecode */
			/* begin pushLiteralConstant: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) method)) + 4) + (((63 & 31) + 1) << 2)));
			break;
		case 64:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((64 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 65:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((65 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 66:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((66 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 67:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((67 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 68:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((68 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 69:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((69 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 70:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((70 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 71:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((71 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 72:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((72 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 73:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((73 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 74:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((74 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 75:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((75 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 76:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((76 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 77:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((77 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 78:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((78 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 79:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((79 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 80:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((80 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 81:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((81 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 82:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((82 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 83:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((83 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 84:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((84 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 85:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((85 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 86:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((86 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 87:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((87 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 88:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((88 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 89:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((89 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 90:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((90 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 91:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((91 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 92:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((92 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 93:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((93 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 94:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((94 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 95:
			/* pushLiteralVariableBytecode */
			/* begin pushLiteralVariable: */
			/* begin internalPush: */
			longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + (((95 & 31) + 1) << 2))))) + 4) + (1 << 2)));
			break;
		case 96:
			/* storeAndPopReceiverVariableBytecode */
			t2 = receiver;
			t1 = longAt(localSP);
			if (t2 < youngStart) {
				possibleRootStoreIntovalue(t2, t1);
			}
			longAtput(((((char *) t2)) + 4) + ((96 & 7) << 2), t1);
			/* begin internalPop: */
			localSP -= 1 * 4;
			break;
		case 97:
			/* storeAndPopReceiverVariableBytecode */
			t2 = receiver;
			t1 = longAt(localSP);
			if (t2 < youngStart) {
				possibleRootStoreIntovalue(t2, t1);
			}
			longAtput(((((char *) t2)) + 4) + ((97 & 7) << 2), t1);
			/* begin internalPop: */
			localSP -= 1 * 4;
			break;
		case 98:
			/* storeAndPopReceiverVariableBytecode */
			t2 = receiver;
			t1 = longAt(localSP);
			if (t2 < youngStart) {
				possibleRootStoreIntovalue(t2, t1);
			}
			longAtput(((((char *) t2)) + 4) + ((98 & 7) << 2), t1);
			/* begin internalPop: */
			localSP -= 1 * 4;
			break;
		case 99:
			/* storeAndPopReceiverVariableBytecode */
			t2 = receiver;
			t1 = longAt(localSP);
			if (t2 < youngStart) {
				possibleRootStoreIntovalue(t2, t1);
			}
			longAtput(((((char *) t2)) + 4) + ((99 & 7) << 2), t1);
			/* begin internalPop: */
			localSP -= 1 * 4;
			break;
		case 100:
			/* storeAndPopReceiverVariableBytecode */
			t2 = receiver;
			t1 = longAt(localSP);
			if (t2 < youngStart) {
				possibleRootStoreIntovalue(t2, t1);
			}
			longAtput(((((char *) t2)) + 4) + ((100 & 7) << 2), t1);
			/* begin internalPop: */
			localSP -= 1 * 4;
			break;
		case 101:
			/* storeAndPopReceiverVariableBytecode */
			t2 = receiver;
			t1 = longAt(localSP);
			if (t2 < youngStart) {
				possibleRootStoreIntovalue(t2, t1);
			}
			longAtput(((((char *) t2)) + 4) + ((101 & 7) << 2), t1);
			/* begin internalPop: */
			localSP -= 1 * 4;
			break;
		case 102:
			/* storeAndPopReceiverVariableBytecode */
			t2 = receiver;
			t1 = longAt(localSP);
			if (t2 < youngStart) {
				possibleRootStoreIntovalue(t2, t1);
			}
			longAtput(((((char *) t2)) + 4) + ((102 & 7) << 2), t1);
			/* begin internalPop: */
			localSP -= 1 * 4;
			break;
		case 103:
			/* storeAndPopReceiverVariableBytecode */
			t2 = receiver;
			t1 = longAt(localSP);
			if (t2 < youngStart) {
				possibleRootStoreIntovalue(t2, t1);
			}
			longAtput(((((char *) t2)) + 4) + ((103 & 7) << 2), t1);
			/* begin internalPop: */
			localSP -= 1 * 4;
			break;
		case 104:
			/* storeAndPopTemporaryVariableBytecode */
			longAtput(((((char *) theHomeContext)) + 4) + (((104 & 7) + 6) << 2), longAt(localSP));
			/* begin internalPop: */
			localSP -= 1 * 4;
			break;
		case 105:
			/* storeAndPopTemporaryVariableBytecode */
			longAtput(((((char *) theHomeContext)) + 4) + (((105 & 7) + 6) << 2), longAt(localSP));
			/* begin internalPop: */
			localSP -= 1 * 4;
			break;
		case 106:
			/* storeAndPopTemporaryVariableBytecode */
			longAtput(((((char *) theHomeContext)) + 4) + (((106 & 7) + 6) << 2), longAt(localSP));
			/* begin internalPop: */
			localSP -= 1 * 4;
			break;
		case 107:
			/* storeAndPopTemporaryVariableBytecode */
			longAtput(((((char *) theHomeContext)) + 4) + (((107 & 7) + 6) << 2), longAt(localSP));
			/* begin internalPop: */
			localSP -= 1 * 4;
			break;
		case 108:
			/* storeAndPopTemporaryVariableBytecode */
			longAtput(((((char *) theHomeContext)) + 4) + (((108 & 7) + 6) << 2), longAt(localSP));
			/* begin internalPop: */
			localSP -= 1 * 4;
			break;
		case 109:
			/* storeAndPopTemporaryVariableBytecode */
			longAtput(((((char *) theHomeContext)) + 4) + (((109 & 7) + 6) << 2), longAt(localSP));
			/* begin internalPop: */
			localSP -= 1 * 4;
			break;
		case 110:
			/* storeAndPopTemporaryVariableBytecode */
			longAtput(((((char *) theHomeContext)) + 4) + (((110 & 7) + 6) << 2), longAt(localSP));
			/* begin internalPop: */
			localSP -= 1 * 4;
			break;
		case 111:
			/* storeAndPopTemporaryVariableBytecode */
			longAtput(((((char *) theHomeContext)) + 4) + (((111 & 7) + 6) << 2), longAt(localSP));
			/* begin internalPop: */
			localSP -= 1 * 4;
			break;
		case 112:
			/* pushReceiverBytecode */
			/* begin internalPush: */
			longAtput(localSP += 4, receiver);
			break;
		case 113:
			/* pushConstantTrueBytecode */
			/* begin internalPush: */
			longAtput(localSP += 4, trueObj);
			break;
		case 114:
			/* pushConstantFalseBytecode */
			/* begin internalPush: */
			longAtput(localSP += 4, falseObj);
			break;
		case 115:
			/* pushConstantNilBytecode */
			/* begin internalPush: */
			longAtput(localSP += 4, nilObj);
			break;
		case 116:
			/* pushConstantMinusOneBytecode */
			/* begin internalPush: */
			longAtput(localSP += 4, 4294967295U);
			break;
		case 117:
			/* pushConstantZeroBytecode */
			/* begin internalPush: */
			longAtput(localSP += 4, 1);
			break;
		case 118:
			/* pushConstantOneBytecode */
			/* begin internalPush: */
			longAtput(localSP += 4, 3);
			break;
		case 119:
			/* pushConstantTwoBytecode */
			/* begin internalPush: */
			longAtput(localSP += 4, 5);
			break;
		case 120:
			/* returnReceiver */
			t2 = longAt(((((char *) theHomeContext)) + 4) + (0 << 2));
			t1 = receiver;
			/* begin returnValue:to: */
		commonReturn:	/*  */;
			t4 = nilObj;
			t5 = activeContext;
			t3 = longAt(((((char *) specialObjectsOop)) + 4) + (10 << 2));
			if ((t2 == t4) || ((longAt(((((char *) t2)) + 4) + (1 << 2))) == t4)) {
				/* begin internalPush: */
				longAtput(localSP += 4, activeContext);
				/* begin internalPush: */
				longAtput(localSP += 4, t1);
				messageSelector = longAt(((((char *) specialObjectsOop)) + 4) + (21 << 2));
				argumentCount = 1;
				/* begin normalSend */
				goto commonSend;
			l3:	/* end fetchClassOf: */;
			l1:	/* end lookupInMethodCacheSel:class: */;
			}
			while (!(t5 == t2)) {
				t6 = longAt(((((char *) t5)) + 4) + (0 << 2));
				longAtput(((((char *) t5)) + 4) + (0 << 2), t4);
				longAtput(((((char *) t5)) + 4) + (1 << 2), t4);
				if (reclaimableContextCount > 0) {
					reclaimableContextCount -= 1;
					/* begin recycleContextIfPossible:methodContextClass: */
					if (t5 >= youngStart) {
						t7 = longAt(t5);
						t8 = t7 & 126976;
						if (t8 == 0) {
							t9 = ((longAt(t5 - 4)) & 4294967292U) == t3;
						} else {
							t9 = t8 == (((longAt(((((char *) t3)) + 4) + (2 << 2))) - 1) & 126976);
						}
						if (t9) {
							if ((t7 & 252) == 76) {
								longAtput(((((char *) t5)) + 4) + (0 << 2), freeSmallContexts);
								freeSmallContexts = t5;
							} else {
								longAtput(((((char *) t5)) + 4) + (0 << 2), freeLargeContexts);
								freeLargeContexts = t5;
							}
						}
					}
				}
				t5 = t6;
			}
			activeContext = t5;
			if (t5 < youngStart) {
				beRootIfOld(t5);
			}
			/* begin internalFetchContextRegisters: */
			t10 = longAt(((((char *) t5)) + 4) + (3 << 2));
			if ((t10 & 1)) {
				t10 = longAt(((((char *) t5)) + 4) + (5 << 2));
				if (t10 < youngStart) {
					beRootIfOld(t10);
				}
			} else {
				t10 = t5;
			}
			theHomeContext = t10;
			receiver = longAt(((((char *) t10)) + 4) + (5 << 2));
			method = longAt(((((char *) t10)) + 4) + (3 << 2));
			t10 = ((longAt(((((char *) t5)) + 4) + (1 << 2))) >> 1);
			localIP = ((char *) (((method + t10) + 4) - 2));
			t10 = ((longAt(((((char *) t5)) + 4) + (2 << 2))) >> 1);
			localSP = ((char *) ((t5 + 4) + (((6 + t10) - 1) * 4)));
			/* begin internalPush: */
			longAtput(localSP += 4, t1);
			/* begin internalQuickCheckForInterrupts */
			if ((interruptCheckCounter -= 1) <= 0) {
				/* begin externalizeIPandSP */
				instructionPointer = ((int) localIP);
				stackPointer = ((int) localSP);
				checkForInterrupts();
				/* begin internalizeIPandSP */
				localIP = ((char *) instructionPointer);
				localSP = ((char *) stackPointer);
			}
		l4:	/* end returnValue:to: */;
			break;
		case 121:
			/* returnTrue */
			t2 = longAt(((((char *) theHomeContext)) + 4) + (0 << 2));
			t1 = trueObj;
			/* begin returnValue:to: */
			goto commonReturn;
		l8:	/* end returnValue:to: */;
			break;
		case 122:
			/* returnFalse */
			t2 = longAt(((((char *) theHomeContext)) + 4) + (0 << 2));
			t1 = falseObj;
			/* begin returnValue:to: */
			goto commonReturn;
		l12:	/* end returnValue:to: */;
			break;
		case 123:
			/* returnNil */
			t2 = longAt(((((char *) theHomeContext)) + 4) + (0 << 2));
			t1 = nilObj;
			/* begin returnValue:to: */
			goto commonReturn;
		l16:	/* end returnValue:to: */;
			break;
		case 124:
			/* returnTopFromMethod */
			t2 = longAt(((((char *) theHomeContext)) + 4) + (0 << 2));
			t1 = longAt(localSP);
			/* begin returnValue:to: */
			goto commonReturn;
		l20:	/* end returnValue:to: */;
			break;
		case 125:
			/* returnTopFromBlock */
			t2 = longAt(((((char *) activeContext)) + 4) + (0 << 2));
			t1 = longAt(localSP);
			/* begin returnValue:to: */
			goto commonReturn;
		l24:	/* end returnValue:to: */;
			break;
		case 126:
		case 127:
			/* unknownBytecode */
			error("Unknown bytecode");
			break;
		case 128:
			/* extendedPushBytecode */
			t1 = byteAt(++localIP);
			t2 = (((unsigned) t1) >> 6) & 3;
			t3 = t1 & 63;
			if (t2 == 0) {
				/* begin pushReceiverVariable: */
				/* begin internalPush: */
				longAtput(localSP += 4, longAt(((((char *) receiver)) + 4) + (t3 << 2)));
				goto l25;
			}
			if (t2 == 1) {
				/* begin pushTemporaryVariable: */
				/* begin internalPush: */
				longAtput(localSP += 4, longAt(((((char *) theHomeContext)) + 4) + ((t3 + 6) << 2)));
				goto l25;
			}
			if (t2 == 2) {
				/* begin pushLiteralConstant: */
				/* begin internalPush: */
				longAtput(localSP += 4, longAt(((((char *) method)) + 4) + ((t3 + 1) << 2)));
				goto l25;
			}
			if (t2 == 3) {
				/* begin pushLiteralVariable: */
				/* begin internalPush: */
				longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + ((t3 + 1) << 2))))) + 4) + (1 << 2)));
				goto l25;
			}
		l25:	/* end case */;
			break;
		case 129:
			/* extendedStoreBytecode */
			t1 = byteAt(++localIP);
			t2 = (((unsigned) t1) >> 6) & 3;
			t3 = t1 & 63;
			if (t2 == 0) {
				/* begin storePointer:ofObject:withValue: */
				t5 = receiver;
				t6 = longAt(localSP);
				if (t5 < youngStart) {
					possibleRootStoreIntovalue(t5, t6);
				}
				longAtput(((((char *) t5)) + 4) + (t3 << 2), t6);
				goto l26;
			}
			if (t2 == 1) {
				longAtput(((((char *) theHomeContext)) + 4) + ((t3 + 6) << 2), longAt(localSP));
				goto l26;
			}
			if (t2 == 2) {
				error("illegal store");
			}
			if (t2 == 3) {
				t4 = longAt(((((char *) method)) + 4) + ((t3 + 1) << 2));
				/* begin storePointer:ofObject:withValue: */
				t7 = longAt(localSP);
				if (t4 < youngStart) {
					possibleRootStoreIntovalue(t4, t7);
				}
				longAtput(((((char *) t4)) + 4) + (1 << 2), t7);
				goto l26;
			}
		l26:	/* end case */;
			break;
		case 130:
			/* extendedStoreAndPopBytecode */
			/* begin extendedStoreBytecode */
			t1 = byteAt(++localIP);
			t2 = (((unsigned) t1) >> 6) & 3;
			t3 = t1 & 63;
			if (t2 == 0) {
				/* begin storePointer:ofObject:withValue: */
				t5 = receiver;
				t6 = longAt(localSP);
				if (t5 < youngStart) {
					possibleRootStoreIntovalue(t5, t6);
				}
				longAtput(((((char *) t5)) + 4) + (t3 << 2), t6);
				goto l27;
			}
			if (t2 == 1) {
				longAtput(((((char *) theHomeContext)) + 4) + ((t3 + 6) << 2), longAt(localSP));
				goto l27;
			}
			if (t2 == 2) {
				error("illegal store");
			}
			if (t2 == 3) {
				t4 = longAt(((((char *) method)) + 4) + ((t3 + 1) << 2));
				/* begin storePointer:ofObject:withValue: */
				t7 = longAt(localSP);
				if (t4 < youngStart) {
					possibleRootStoreIntovalue(t4, t7);
				}
				longAtput(((((char *) t4)) + 4) + (1 << 2), t7);
				goto l27;
			}
		l27:	/* end extendedStoreBytecode */;
			/* begin popStackBytecode */
			/* begin internalPop: */
			localSP -= 1 * 4;
			break;
		case 131:
			/* singleExtendedSendBytecode */
			t1 = byteAt(++localIP);
			messageSelector = longAt(((((char *) method)) + 4) + (((t1 & 31) + 1) << 2));
			argumentCount = ((unsigned) t1) >> 5;
			/* begin normalSend */
		commonSend:	/*  */;
			/* begin fetchClassOf: */
			if (((longAt(localSP - (argumentCount * 4))) & 1)) {
				t2 = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
				goto l30;
			}
			t8 = ((((unsigned) (longAt(longAt(localSP - (argumentCount * 4))))) >> 12) & 31) - 1;
			if (t8 < 0) {
				t2 = (longAt((longAt(localSP - (argumentCount * 4))) - 4)) & 4294967292U;
				goto l30;
			} else {
				t2 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (t8 << 2));
				goto l30;
			}
		l30:	/* end fetchClassOf: */;
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			/* begin sendSelectorToClass: */
			/* begin findNewMethodInClass: */
			/* begin lookupInMethodCacheSel:class: */
			t6 = ((unsigned) (messageSelector ^ t2)) >> 2;
			t4 = (t6 & 511) + 1;
			for (t5 = 1; t5 <= 3; t5 += 1) {
				if (((methodCache[t4]) == messageSelector) && ((methodCache[t4 + 512]) == t2)) {
					newMethod = methodCache[t4 + (512 * 2)];
					primitiveIndex = methodCache[t4 + (512 * 3)];
					t3 = true;
					goto l28;
				}
				t4 = ((((unsigned) t6) >> t5) & 511) + 1;
			}
			t3 = false;
		l28:	/* end lookupInMethodCacheSel:class: */;
			if (!(t3)) {
				lookupMethodInClass(t2);
				/* begin primitiveIndexOf: */
				t7 = (((unsigned) (longAt(((((char *) newMethod)) + 4) + (0 << 2)))) >> 1) & 805306879;
				if (t7 > 511) {
					primitiveIndex = (t7 & 511) + (((unsigned) t7) >> 19);
					goto l29;
				} else {
					primitiveIndex = t7;
					goto l29;
				}
			l29:	/* end primitiveIndexOf: */;
				addToMethodCacheSelclassmethodprimIndex(messageSelector, t2, newMethod, primitiveIndex);
			}
			/* begin executeNewMethod */
			if ((primitiveIndex == 0) || (!(primitiveResponse()))) {
				activateNewMethod();
				/* begin quickCheckForInterrupts */
				if ((interruptCheckCounter -= 1) <= 0) {
					checkForInterrupts();
				}
			}
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
			break;
		case 132:
			/* doubleExtendedDoAnythingBytecode */
			t1 = byteAt(++localIP);
			t2 = byteAt(++localIP);
			t4 = ((unsigned) t1) >> 5;
			if (t4 == 0) {
				messageSelector = longAt(((((char *) method)) + 4) + ((t2 + 1) << 2));
				argumentCount = t1 & 31;
				/* begin normalSend */
				goto commonSend;
			l34:	/* end fetchClassOf: */;
			l32:	/* end lookupInMethodCacheSel:class: */;
			}
			if (t4 == 1) {
				messageSelector = longAt(((((char *) method)) + 4) + ((t2 + 1) << 2));
				argumentCount = t1 & 31;
				/* begin superclassSend */
				goto commonSupersend;
			l35:	/* end lookupInMethodCacheSel:class: */;
			}
			if (t4 == 2) {
				/* begin pushReceiverVariable: */
				/* begin internalPush: */
				longAtput(localSP += 4, longAt(((((char *) receiver)) + 4) + (t2 << 2)));
				goto l31;
			}
			if (t4 == 3) {
				/* begin pushLiteralConstant: */
				/* begin internalPush: */
				longAtput(localSP += 4, longAt(((((char *) method)) + 4) + ((t2 + 1) << 2)));
				goto l31;
			}
			if (t4 == 4) {
				/* begin pushLiteralVariable: */
				/* begin internalPush: */
				longAtput(localSP += 4, longAt(((((char *) (longAt(((((char *) method)) + 4) + ((t2 + 1) << 2))))) + 4) + (1 << 2)));
				goto l31;
			}
			if (t4 == 5) {
				t3 = longAt(localSP);
				/* begin storePointer:ofObject:withValue: */
				t5 = receiver;
				if (t5 < youngStart) {
					possibleRootStoreIntovalue(t5, t3);
				}
				longAtput(((((char *) t5)) + 4) + (t2 << 2), t3);
				goto l31;
			}
			if (t4 == 6) {
				t3 = longAt(localSP);
				/* begin internalPop: */
				localSP -= 1 * 4;
				/* begin storePointer:ofObject:withValue: */
				t6 = receiver;
				if (t6 < youngStart) {
					possibleRootStoreIntovalue(t6, t3);
				}
				longAtput(((((char *) t6)) + 4) + (t2 << 2), t3);
				goto l31;
			}
			if (t4 == 7) {
				t3 = longAt(localSP);
				/* begin storePointer:ofObject:withValue: */
				t7 = longAt(((((char *) method)) + 4) + ((t2 + 1) << 2));
				if (t7 < youngStart) {
					possibleRootStoreIntovalue(t7, t3);
				}
				longAtput(((((char *) t7)) + 4) + (1 << 2), t3);
				goto l31;
			}
		l31:	/* end case */;
			break;
		case 133:
			/* singleExtendedSuperBytecode */
			t1 = byteAt(++localIP);
			messageSelector = longAt(((((char *) method)) + 4) + (((t1 & 31) + 1) << 2));
			argumentCount = ((unsigned) t1) >> 5;
			/* begin superclassSend */
		commonSupersend:	/*  */;
			/* begin superclassOf: */
			t3 = longAt(((((char *) (longAt(((((char *) method)) + 4) + (((((((unsigned) (longAt(((((char *) method)) + 4) + (0 << 2)))) >> 10) & 255) - 1) + 1) << 2))))) + 4) + (1 << 2));
			t2 = longAt(((((char *) t3)) + 4) + (0 << 2));
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			/* begin sendSelectorToClass: */
			/* begin findNewMethodInClass: */
			/* begin lookupInMethodCacheSel:class: */
			t7 = ((unsigned) (messageSelector ^ t2)) >> 2;
			t5 = (t7 & 511) + 1;
			for (t6 = 1; t6 <= 3; t6 += 1) {
				if (((methodCache[t5]) == messageSelector) && ((methodCache[t5 + 512]) == t2)) {
					newMethod = methodCache[t5 + (512 * 2)];
					primitiveIndex = methodCache[t5 + (512 * 3)];
					t4 = true;
					goto l37;
				}
				t5 = ((((unsigned) t7) >> t6) & 511) + 1;
			}
			t4 = false;
		l37:	/* end lookupInMethodCacheSel:class: */;
			if (!(t4)) {
				lookupMethodInClass(t2);
				/* begin primitiveIndexOf: */
				t8 = (((unsigned) (longAt(((((char *) newMethod)) + 4) + (0 << 2)))) >> 1) & 805306879;
				if (t8 > 511) {
					primitiveIndex = (t8 & 511) + (((unsigned) t8) >> 19);
					goto l38;
				} else {
					primitiveIndex = t8;
					goto l38;
				}
			l38:	/* end primitiveIndexOf: */;
				addToMethodCacheSelclassmethodprimIndex(messageSelector, t2, newMethod, primitiveIndex);
			}
			/* begin executeNewMethod */
			if ((primitiveIndex == 0) || (!(primitiveResponse()))) {
				activateNewMethod();
				/* begin quickCheckForInterrupts */
				if ((interruptCheckCounter -= 1) <= 0) {
					checkForInterrupts();
				}
			}
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
			break;
		case 134:
			/* secondExtendedSendBytecode */
			t1 = byteAt(++localIP);
			messageSelector = longAt(((((char *) method)) + 4) + (((t1 & 63) + 1) << 2));
			argumentCount = ((unsigned) t1) >> 6;
			/* begin normalSend */
			goto commonSend;
		l41:	/* end fetchClassOf: */;
		l39:	/* end lookupInMethodCacheSel:class: */;
			break;
		case 135:
			/* popStackBytecode */
			/* begin internalPop: */
			localSP -= 1 * 4;
			break;
		case 136:
			/* duplicateTopBytecode */
			/* begin internalPush: */
			t1 = longAt(localSP);
			longAtput(localSP += 4, t1);
			break;
		case 137:
			/* pushActiveContextBytecode */
			reclaimableContextCount = 0;
			/* begin internalPush: */
			longAtput(localSP += 4, activeContext);
			break;
		case 138:
		case 139:
		case 140:
		case 141:
		case 142:
		case 143:
			/* experimentalBytecode */
			t2 = longAt(((((char *) theHomeContext)) + 4) + (((currentBytecode - 138) + 6) << 2));
			t4 = byteAt(localIP + 1);
			t5 = byteAt(localIP + 2);
			t6 = byteAt(localIP + 3);
			if ((t2 & 1)) {
				t1 = (t2 >> 1);
			} else {
				/* begin internalPush: */
				longAtput(localSP += 4, t2);
				goto l42;
			}
			if (t4 < 32) {
				t3 = longAt(((((char *) theHomeContext)) + 4) + (((t4 & 15) + 6) << 2));
				if ((t3 & 1)) {
					t3 = (t3 >> 1);
				} else {
					/* begin internalPush: */
					longAtput(localSP += 4, t2);
					goto l42;
				}
			} else {
				if (t4 > 64) {
					t3 = 1;
				} else {
					t3 = longAt(((((char *) method)) + 4) + (((t4 & 31) + 1) << 2));
					if ((t3 & 1)) {
						t3 = (t3 >> 1);
					} else {
						/* begin internalPush: */
						longAtput(localSP += 4, t2);
						goto l42;
					}
				}
			}
			if (t5 < 178) {
				t8 = t1 + t3;
				if ((t8 ^ (t8 << 1)) >= 0) {
					if ((t6 > 103) && (t6 < 112)) {
						localIP += 3;
						longAtput(((((char *) theHomeContext)) + 4) + (((t6 & 7) + 6) << 2), ((t8 << 1) | 1));
					} else {
						localIP += 2;
						/* begin internalPush: */
						longAtput(localSP += 4, ((t8 << 1) | 1));
					}
				} else {
					/* begin internalPush: */
					longAtput(localSP += 4, t2);
					goto l42;
				}
			} else {
				t7 = byteAt(localIP + 4);
				if (t1 <= t3) {
					localIP = (localIP + 3) + 1;
				} else {
					localIP = ((localIP + 3) + 1) + t7;
				}
			}
		l42:	/* end case */;
			break;
		case 144:
			/* shortUnconditionalJump */
			/* begin jump: */
			localIP += (144 & 7) + 1;
			break;
		case 145:
			/* shortUnconditionalJump */
			/* begin jump: */
			localIP += (145 & 7) + 1;
			break;
		case 146:
			/* shortUnconditionalJump */
			/* begin jump: */
			localIP += (146 & 7) + 1;
			break;
		case 147:
			/* shortUnconditionalJump */
			/* begin jump: */
			localIP += (147 & 7) + 1;
			break;
		case 148:
			/* shortUnconditionalJump */
			/* begin jump: */
			localIP += (148 & 7) + 1;
			break;
		case 149:
			/* shortUnconditionalJump */
			/* begin jump: */
			localIP += (149 & 7) + 1;
			break;
		case 150:
			/* shortUnconditionalJump */
			/* begin jump: */
			localIP += (150 & 7) + 1;
			break;
		case 151:
			/* shortUnconditionalJump */
			/* begin jump: */
			localIP += (151 & 7) + 1;
			break;
		case 152:
		case 153:
		case 154:
		case 155:
		case 156:
		case 157:
		case 158:
		case 159:
			/* shortConditionalJump */
			/* begin jumplfFalseBy: */
			t1 = (currentBytecode & 7) + 1;
			t2 = longAt(localSP);
			if (t2 == falseObj) {
				/* begin jump: */
				localIP += t1;
			} else {
				if (!(t2 == trueObj)) {
					messageSelector = longAt(((((char *) specialObjectsOop)) + 4) + (25 << 2));
					argumentCount = 0;
					/* begin normalSend */
					goto commonSend;
				l46:	/* end fetchClassOf: */;
				l44:	/* end lookupInMethodCacheSel:class: */;
				}
			}
			/* begin internalPop: */
			localSP -= 1 * 4;
		l43:	/* end jumplfFalseBy: */;
			break;
		case 160:
		case 161:
		case 162:
		case 163:
		case 164:
		case 165:
		case 166:
		case 167:
			/* longUnconditionalJump */
			t1 = (((currentBytecode & 7) - 4) * 256) + (byteAt(++localIP));
			localIP += t1;
			if (t1 < 0) {
				/* begin internalQuickCheckForInterrupts */
				if ((interruptCheckCounter -= 1) <= 0) {
					/* begin externalizeIPandSP */
					instructionPointer = ((int) localIP);
					stackPointer = ((int) localSP);
					checkForInterrupts();
					/* begin internalizeIPandSP */
					localIP = ((char *) instructionPointer);
					localSP = ((char *) stackPointer);
				}
			}
			break;
		case 168:
		case 169:
		case 170:
		case 171:
			/* longJumpIfTrue */
			/* begin jumplfTrueBy: */
			t1 = ((currentBytecode & 3) * 256) + (byteAt(++localIP));
			t2 = longAt(localSP);
			if (t2 == trueObj) {
				/* begin jump: */
				localIP += t1;
			} else {
				if (!(t2 == falseObj)) {
					messageSelector = longAt(((((char *) specialObjectsOop)) + 4) + (25 << 2));
					argumentCount = 0;
					/* begin normalSend */
					goto commonSend;
				l50:	/* end fetchClassOf: */;
				l48:	/* end lookupInMethodCacheSel:class: */;
				}
			}
			/* begin internalPop: */
			localSP -= 1 * 4;
		l47:	/* end jumplfTrueBy: */;
			break;
		case 172:
		case 173:
		case 174:
		case 175:
			/* longJumpIfFalse */
			/* begin jumplfFalseBy: */
			t1 = ((currentBytecode & 3) * 256) + (byteAt(++localIP));
			t2 = longAt(localSP);
			if (t2 == falseObj) {
				/* begin jump: */
				localIP += t1;
			} else {
				if (!(t2 == trueObj)) {
					messageSelector = longAt(((((char *) specialObjectsOop)) + 4) + (25 << 2));
					argumentCount = 0;
					/* begin normalSend */
					goto commonSend;
				l54:	/* end fetchClassOf: */;
				l52:	/* end lookupInMethodCacheSel:class: */;
				}
			}
			/* begin internalPop: */
			localSP -= 1 * 4;
		l51:	/* end jumplfFalseBy: */;
			break;
		case 176:
			/* bytecodePrimAdd */
			t3 = longAt(localSP - (1 * 4));
			t1 = longAt(localSP - (0 * 4));
			if (((t3 & t1) & 1) != 0) {
				t2 = ((t3 >> 1)) + ((t1 >> 1));
				if ((t2 ^ (t2 << 1)) >= 0) {
					longAtput(localSP -= 4, ((t2 << 1) | 1));
					goto l55;
				}
			}
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			successFlag = true;
			primitiveFloatAdd();
			if (!(successFlag)) {
				successFlag = true;
				primitiveAdd();
			}
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
		l55:	/* end case */;
			break;
		case 177:
			/* bytecodePrimSubtract */
			t3 = longAt(localSP - (1 * 4));
			t1 = longAt(localSP - (0 * 4));
			if (((t3 & t1) & 1) != 0) {
				t2 = ((t3 >> 1)) - ((t1 >> 1));
				if ((t2 ^ (t2 << 1)) >= 0) {
					longAtput(localSP -= 4, ((t2 << 1) | 1));
					goto l56;
				}
			}
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			successFlag = true;
			primitiveFloatSubtract();
			if (!(successFlag)) {
				successFlag = true;
				primitiveSubtract();
			}
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
		l56:	/* end case */;
			break;
		case 178:
			/* bytecodePrimLessThan */
			t2 = longAt(localSP - (1 * 4));
			t1 = longAt(localSP - (0 * 4));
			if (((t2 & t1) & 1) != 0) {
				/* begin booleanCheat: */
				t3 = byteAt(++localIP);
				/* begin internalPop: */
				localSP -= 2 * 4;
				if ((t3 < 160) && (t3 > 151)) {
					if (t2 < t1) {
						goto l57;
					} else {
						/* begin jump: */
						localIP += t3 - 151;
						goto l57;
					}
				}
				if (t3 == 172) {
					t4 = byteAt(++localIP);
					if (t2 < t1) {
						goto l57;
					} else {
						/* begin jump: */
						localIP += t4;
						goto l57;
					}
				}
				localIP -= 1;
				if (t2 < t1) {
					/* begin internalPush: */
					longAtput(localSP += 4, trueObj);
				} else {
					/* begin internalPush: */
					longAtput(localSP += 4, falseObj);
				}
				goto l57;
			}
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			successFlag = true;
			primitiveFloatLessThan();
			if (!(successFlag)) {
				successFlag = true;
				primitiveLessThan();
			}
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
		l57:	/* end case */;
			break;
		case 179:
			/* bytecodePrimGreaterThan */
			t2 = longAt(localSP - (1 * 4));
			t1 = longAt(localSP - (0 * 4));
			if (((t2 & t1) & 1) != 0) {
				/* begin booleanCheat: */
				t3 = byteAt(++localIP);
				/* begin internalPop: */
				localSP -= 2 * 4;
				if ((t3 < 160) && (t3 > 151)) {
					if (t2 > t1) {
						goto l58;
					} else {
						/* begin jump: */
						localIP += t3 - 151;
						goto l58;
					}
				}
				if (t3 == 172) {
					t4 = byteAt(++localIP);
					if (t2 > t1) {
						goto l58;
					} else {
						/* begin jump: */
						localIP += t4;
						goto l58;
					}
				}
				localIP -= 1;
				if (t2 > t1) {
					/* begin internalPush: */
					longAtput(localSP += 4, trueObj);
				} else {
					/* begin internalPush: */
					longAtput(localSP += 4, falseObj);
				}
				goto l58;
			}
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			successFlag = true;
			primitiveFloatGreaterThan();
			if (!(successFlag)) {
				successFlag = true;
				primitiveGreaterThan();
			}
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
		l58:	/* end case */;
			break;
		case 180:
			/* bytecodePrimLessOrEqual */
			t2 = longAt(localSP - (1 * 4));
			t1 = longAt(localSP - (0 * 4));
			if (((t2 & t1) & 1) != 0) {
				/* begin booleanCheat: */
				t3 = byteAt(++localIP);
				/* begin internalPop: */
				localSP -= 2 * 4;
				if ((t3 < 160) && (t3 > 151)) {
					if (t2 <= t1) {
						goto l59;
					} else {
						/* begin jump: */
						localIP += t3 - 151;
						goto l59;
					}
				}
				if (t3 == 172) {
					t4 = byteAt(++localIP);
					if (t2 <= t1) {
						goto l59;
					} else {
						/* begin jump: */
						localIP += t4;
						goto l59;
					}
				}
				localIP -= 1;
				if (t2 <= t1) {
					/* begin internalPush: */
					longAtput(localSP += 4, trueObj);
				} else {
					/* begin internalPush: */
					longAtput(localSP += 4, falseObj);
				}
				goto l59;
			}
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			successFlag = true;
			primitiveFloatLessOrEqual();
			if (!(successFlag)) {
				successFlag = true;
				primitiveLessOrEqual();
			}
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
		l59:	/* end case */;
			break;
		case 181:
			/* bytecodePrimGreaterOrEqual */
			t2 = longAt(localSP - (1 * 4));
			t1 = longAt(localSP - (0 * 4));
			if (((t2 & t1) & 1) != 0) {
				/* begin booleanCheat: */
				t3 = byteAt(++localIP);
				/* begin internalPop: */
				localSP -= 2 * 4;
				if ((t3 < 160) && (t3 > 151)) {
					if (t2 >= t1) {
						goto l60;
					} else {
						/* begin jump: */
						localIP += t3 - 151;
						goto l60;
					}
				}
				if (t3 == 172) {
					t4 = byteAt(++localIP);
					if (t2 >= t1) {
						goto l60;
					} else {
						/* begin jump: */
						localIP += t4;
						goto l60;
					}
				}
				localIP -= 1;
				if (t2 >= t1) {
					/* begin internalPush: */
					longAtput(localSP += 4, trueObj);
				} else {
					/* begin internalPush: */
					longAtput(localSP += 4, falseObj);
				}
				goto l60;
			}
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			successFlag = true;
			primitiveFloatGreaterOrEqual();
			if (!(successFlag)) {
				successFlag = true;
				primitiveGreaterOrEqual();
			}
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
		l60:	/* end case */;
			break;
		case 182:
			/* bytecodePrimEqual */
			t2 = longAt(localSP - (1 * 4));
			t1 = longAt(localSP - (0 * 4));
			if (((t2 & t1) & 1) != 0) {
				/* begin booleanCheat: */
				t3 = byteAt(++localIP);
				/* begin internalPop: */
				localSP -= 2 * 4;
				if ((t3 < 160) && (t3 > 151)) {
					if (t2 == t1) {
						goto l61;
					} else {
						/* begin jump: */
						localIP += t3 - 151;
						goto l61;
					}
				}
				if (t3 == 172) {
					t4 = byteAt(++localIP);
					if (t2 == t1) {
						goto l61;
					} else {
						/* begin jump: */
						localIP += t4;
						goto l61;
					}
				}
				localIP -= 1;
				if (t2 == t1) {
					/* begin internalPush: */
					longAtput(localSP += 4, trueObj);
				} else {
					/* begin internalPush: */
					longAtput(localSP += 4, falseObj);
				}
				goto l61;
			}
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			successFlag = true;
			primitiveFloatEqual();
			if (!(successFlag)) {
				successFlag = true;
				primitiveEqual();
			}
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
		l61:	/* end case */;
			break;
		case 183:
			/* bytecodePrimNotEqual */
			t2 = longAt(localSP - (1 * 4));
			t1 = longAt(localSP - (0 * 4));
			if (((t2 & t1) & 1) != 0) {
				/* begin booleanCheat: */
				t3 = byteAt(++localIP);
				/* begin internalPop: */
				localSP -= 2 * 4;
				if ((t3 < 160) && (t3 > 151)) {
					if (t2 != t1) {
						goto l62;
					} else {
						/* begin jump: */
						localIP += t3 - 151;
						goto l62;
					}
				}
				if (t3 == 172) {
					t4 = byteAt(++localIP);
					if (t2 != t1) {
						goto l62;
					} else {
						/* begin jump: */
						localIP += t4;
						goto l62;
					}
				}
				localIP -= 1;
				if (t2 != t1) {
					/* begin internalPush: */
					longAtput(localSP += 4, trueObj);
				} else {
					/* begin internalPush: */
					longAtput(localSP += 4, falseObj);
				}
				goto l62;
			}
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			successFlag = true;
			primitiveFloatNotEqual();
			if (!(successFlag)) {
				successFlag = true;
				primitiveNotEqual();
			}
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
		l62:	/* end case */;
			break;
		case 184:
			/* bytecodePrimMultiply */
			t3 = longAt(localSP - (1 * 4));
			t1 = longAt(localSP - (0 * 4));
			if (((t3 & t1) & 1) != 0) {
				t3 = (t3 >> 1);
				t1 = (t1 >> 1);
				t2 = t3 * t1;
				if (((t1 == 0) || ((t2 / t1) == t3)) && ((t2 ^ (t2 << 1)) >= 0)) {
					longAtput(localSP -= 4, ((t2 << 1) | 1));
					goto l63;
				}
			}
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			successFlag = true;
			primitiveFloatMultiply();
			if (!(successFlag)) {
				successFlag = true;
				primitiveMultiply();
			}
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
		l63:	/* end case */;
			break;
		case 185:
			/* bytecodePrimDivide */
			t3 = longAt(localSP - (1 * 4));
			t1 = longAt(localSP - (0 * 4));
			if (((t3 & t1) & 1) != 0) {
				t3 = (t3 >> 1);
				t1 = (t1 >> 1);
				if ((t1 != 0) && ((t3 % t1) == 0)) {
					t2 = t3 / t1;
					if ((t2 ^ (t2 << 1)) >= 0) {
						longAtput(localSP -= 4, ((t2 << 1) | 1));
						goto l64;
					}
				}
			}
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			successFlag = true;
			primitiveFloatDivide();
			if (!(successFlag)) {
				successFlag = true;
				primitiveDivide();
			}
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
		l64:	/* end case */;
			break;
		case 186:
			/* bytecodePrimMod */
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			primitiveMod();
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
			break;
		case 187:
			/* bytecodePrimMakePoint */
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			primitiveMakePoint();
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
			break;
		case 188:
			/* bytecodePrimBitShift */
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			primitiveBitShift();
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
			break;
		case 189:
			/* bytecodePrimDiv */
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			primitiveDiv();
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
			break;
		case 190:
			/* bytecodePrimBitAnd */
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			primitiveBitAnd();
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
			break;
		case 191:
			/* bytecodePrimBitOr */
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			primitiveBitOr();
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
			break;
		case 192:
			/* bytecodePrimAt */
			t2 = longAt(localSP);
			t4 = longAt(localSP - (1 * 4));
			successFlag = (t2 & 1);
			if (successFlag) {
				/* begin fetchClassOf: */
				if ((t4 & 1)) {
					t5 = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
					goto l65;
				}
				t6 = ((((unsigned) (longAt(t4))) >> 12) & 31) - 1;
				if (t6 < 0) {
					t5 = (longAt(t4 - 4)) & 4294967292U;
					goto l65;
				} else {
					t5 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (t6 << 2));
					goto l65;
				}
			l65:	/* end fetchClassOf: */;
				t1 = t5 == (longAt(((((char *) specialObjectsOop)) + 4) + (6 << 2)));
				if (!(t1 || ((t5 == (longAt(((((char *) specialObjectsOop)) + 4) + (7 << 2)))) || ((t5 == (longAt(((((char *) specialObjectsOop)) + 4) + (4 << 2)))) || (t5 == (longAt(((((char *) specialObjectsOop)) + 4) + (26 << 2)))))))) {
					successFlag = false;
				}
			}
			if (successFlag) {
				t2 = (t2 >> 1);
				/* begin externalizeIPandSP */
				instructionPointer = ((int) localIP);
				stackPointer = ((int) localSP);
				t3 = stObjectat(t4, t2);
				/* begin internalizeIPandSP */
				localIP = ((char *) instructionPointer);
				localSP = ((char *) stackPointer);
				if (t1 && (successFlag)) {
					t3 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (24 << 2))))) + 4) + (((t3 >> 1)) << 2));
				}
			}
			if (successFlag) {
				/* begin internalPop:thenPush: */
				longAtput(localSP -= (2 - 1) * 4, t3);
			} else {
				messageSelector = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (23 << 2))))) + 4) + ((16 * 2) << 2));
				argumentCount = 1;
				/* begin normalSend */
				goto commonSend;
			l68:	/* end fetchClassOf: */;
			l66:	/* end lookupInMethodCacheSel:class: */;
			}
			break;
		case 193:
			/* bytecodePrimAtPut */
			t2 = t3 = longAt(localSP);
			t4 = longAt(localSP - (1 * 4));
			t5 = longAt(localSP - (2 * 4));
			successFlag = (t4 & 1);
			if (successFlag) {
				/* begin fetchClassOf: */
				if ((t5 & 1)) {
					t6 = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
					goto l69;
				}
				t7 = ((((unsigned) (longAt(t5))) >> 12) & 31) - 1;
				if (t7 < 0) {
					t6 = (longAt(t5 - 4)) & 4294967292U;
					goto l69;
				} else {
					t6 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (t7 << 2));
					goto l69;
				}
			l69:	/* end fetchClassOf: */;
				t1 = t6 == (longAt(((((char *) specialObjectsOop)) + 4) + (6 << 2)));
				if (!(t1 || ((t6 == (longAt(((((char *) specialObjectsOop)) + 4) + (7 << 2)))) || ((t6 == (longAt(((((char *) specialObjectsOop)) + 4) + (4 << 2)))) || (t6 == (longAt(((((char *) specialObjectsOop)) + 4) + (26 << 2)))))))) {
					successFlag = false;
				}
			}
			if (successFlag) {
				t4 = (t4 >> 1);
				if (t1) {
					t3 = asciiOfCharacter(t2);
				}
				stObjectatput(t5, t4, t3);
			}
			if (successFlag) {
				/* begin internalPop:thenPush: */
				longAtput(localSP -= (3 - 1) * 4, t2);
			} else {
				messageSelector = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (23 << 2))))) + 4) + ((17 * 2) << 2));
				argumentCount = 2;
				/* begin normalSend */
				goto commonSend;
			l72:	/* end fetchClassOf: */;
			l70:	/* end lookupInMethodCacheSel:class: */;
			}
			break;
		case 194:
			/* bytecodePrimSize */
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			successFlag = true;
			/* begin fetchClassOf: */
			if (((longAt(stackPointer - (0 * 4))) & 1)) {
				t1 = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
				goto l73;
			}
			t2 = ((((unsigned) (longAt(longAt(stackPointer - (0 * 4))))) >> 12) & 31) - 1;
			if (t2 < 0) {
				t1 = (longAt((longAt(stackPointer - (0 * 4))) - 4)) & 4294967292U;
				goto l73;
			} else {
				t1 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (t2 << 2));
				goto l73;
			}
		l73:	/* end fetchClassOf: */;
			if ((t1 == (longAt(((((char *) specialObjectsOop)) + 4) + (6 << 2)))) || ((t1 == (longAt(((((char *) specialObjectsOop)) + 4) + (7 << 2)))) || ((t1 == (longAt(((((char *) specialObjectsOop)) + 4) + (26 << 2)))) || (t1 == (longAt(((((char *) specialObjectsOop)) + 4) + (4 << 2))))))) {
				primitiveSize();
			} else {
				failSpecialPrim(0);
			}
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
			break;
		case 195:
			/* bytecodePrimNext */
			messageSelector = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (23 << 2))))) + 4) + ((19 * 2) << 2));
			argumentCount = 0;
			/* begin normalSend */
			goto commonSend;
		l76:	/* end fetchClassOf: */;
		l74:	/* end lookupInMethodCacheSel:class: */;
			break;
		case 196:
			/* bytecodePrimNextPut */
			messageSelector = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (23 << 2))))) + 4) + ((20 * 2) << 2));
			argumentCount = 1;
			/* begin normalSend */
			goto commonSend;
		l79:	/* end fetchClassOf: */;
		l77:	/* end lookupInMethodCacheSel:class: */;
			break;
		case 197:
			/* bytecodePrimAtEnd */
			messageSelector = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (23 << 2))))) + 4) + ((21 * 2) << 2));
			argumentCount = 0;
			/* begin normalSend */
			goto commonSend;
		l82:	/* end fetchClassOf: */;
		l80:	/* end lookupInMethodCacheSel:class: */;
			break;
		case 198:
			/* bytecodePrimEquivalent */
			t2 = longAt(localSP - (1 * 4));
			t1 = longAt(localSP - (0 * 4));
			/* begin booleanCheat: */
			t3 = byteAt(++localIP);
			/* begin internalPop: */
			localSP -= 2 * 4;
			if ((t3 < 160) && (t3 > 151)) {
				if (t2 == t1) {
					goto l83;
				} else {
					/* begin jump: */
					localIP += t3 - 151;
					goto l83;
				}
			}
			if (t3 == 172) {
				t4 = byteAt(++localIP);
				if (t2 == t1) {
					goto l83;
				} else {
					/* begin jump: */
					localIP += t4;
					goto l83;
				}
			}
			localIP -= 1;
			if (t2 == t1) {
				/* begin internalPush: */
				longAtput(localSP += 4, trueObj);
			} else {
				/* begin internalPush: */
				longAtput(localSP += 4, falseObj);
			}
		l83:	/* end booleanCheat: */;
			break;
		case 199:
			/* bytecodePrimClass */
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			primitiveClass();
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
			break;
		case 200:
			/* bytecodePrimBlockCopy */
			/* begin fetchClassOf: */
			if (((longAt(localSP - (1 * 4))) & 1)) {
				t1 = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
				goto l85;
			}
			t2 = ((((unsigned) (longAt(longAt(localSP - (1 * 4))))) >> 12) & 31) - 1;
			if (t2 < 0) {
				t1 = (longAt((longAt(localSP - (1 * 4))) - 4)) & 4294967292U;
				goto l85;
			} else {
				t1 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (t2 << 2));
				goto l85;
			}
		l85:	/* end fetchClassOf: */;
			successFlag = true;
			/* begin success: */
			t3 = (t1 == (longAt(((((char *) specialObjectsOop)) + 4) + (11 << 2)))) || (t1 == (longAt(((((char *) specialObjectsOop)) + 4) + (10 << 2))));
			successFlag = t3 && successFlag;
			if (successFlag) {
				/* begin externalizeIPandSP */
				instructionPointer = ((int) localIP);
				stackPointer = ((int) localSP);
				/* begin primitiveBlockCopy */
				t7 = longAt(stackPointer - (1 * 4));
				if (((longAt(((((char *) t7)) + 4) + (3 << 2))) & 1)) {
					t4 = longAt(((((char *) t7)) + 4) + (5 << 2));
				} else {
					t4 = t7;
				}
				/* begin sizeBitsOf: */
				t9 = longAt(t4);
				if ((t9 & 3) == 0) {
					t8 = (longAt(t4 - 8)) & 4294967292U;
					goto l86;
				} else {
					t8 = t9 & 252;
					goto l86;
				}
			l86:	/* end sizeBitsOf: */;
				t7 = null;
				/* begin pushRemappableOop: */
				remapBuffer[remapBufferCount += 1] = t4;
				t5 = instantiateSmallClasssizeInBytesfill(longAt(((((char *) specialObjectsOop)) + 4) + (11 << 2)), t8, nilObj);
				/* begin popRemappableOop */
				t10 = remapBuffer[remapBufferCount];
				remapBufferCount -= 1;
				t4 = t10;
				t6 = (((instructionPointer - method) << 1) | 1);
				longAtput(((((char *) t5)) + 4) + (4 << 2), t6);
				longAtput(((((char *) t5)) + 4) + (1 << 2), t6);
				/* begin storeStackPointerValue:inContext: */
				longAtput(((((char *) t5)) + 4) + (2 << 2), ((0 << 1) | 1));
				longAtput(((((char *) t5)) + 4) + (3 << 2), longAt(stackPointer - (0 * 4)));
				longAtput(((((char *) t5)) + 4) + (5 << 2), t4);
				/* begin pop: */
				stackPointer -= 2 * 4;
				/* begin push: */
				longAtput(t11 = stackPointer + 4, t5);
				stackPointer = t11;
				/* begin internalizeIPandSP */
				localIP = ((char *) instructionPointer);
				localSP = ((char *) stackPointer);
			}
			if (!(successFlag)) {
				messageSelector = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (23 << 2))))) + 4) + ((24 * 2) << 2));
				argumentCount = 1;
				/* begin normalSend */
				goto commonSend;
			l89:	/* end fetchClassOf: */;
			l87:	/* end lookupInMethodCacheSel:class: */;
			}
		l84:	/* end case */;
			break;
		case 201:
			/* bytecodePrimValue */
			t1 = longAt(localSP);
			successFlag = true;
			argumentCount = 0;
			/* begin assertClassOf:is: */
			if ((t1 & 1)) {
				successFlag = false;
				goto l91;
			}
			t2 = (((unsigned) (longAt(t1))) >> 12) & 31;
			if (t2 == 0) {
				t3 = (longAt(t1 - 4)) & 4294967292U;
			} else {
				t3 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((t2 - 1) << 2));
			}
			/* begin success: */
			successFlag = (t3 == (longAt(((((char *) specialObjectsOop)) + 4) + (11 << 2)))) && successFlag;
		l91:	/* end assertClassOf:is: */;
			if (successFlag) {
				/* begin externalizeIPandSP */
				instructionPointer = ((int) localIP);
				stackPointer = ((int) localSP);
				primitiveValue();
				/* begin internalizeIPandSP */
				localIP = ((char *) instructionPointer);
				localSP = ((char *) stackPointer);
			}
			if (!(successFlag)) {
				messageSelector = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (23 << 2))))) + 4) + ((25 * 2) << 2));
				argumentCount = 0;
				/* begin normalSend */
				goto commonSend;
			l94:	/* end fetchClassOf: */;
			l92:	/* end lookupInMethodCacheSel:class: */;
			}
		l90:	/* end case */;
			break;
		case 202:
			/* bytecodePrimValueWithArg */
			t1 = longAt(localSP - (1 * 4));
			successFlag = true;
			argumentCount = 1;
			/* begin assertClassOf:is: */
			if ((t1 & 1)) {
				successFlag = false;
				goto l96;
			}
			t2 = (((unsigned) (longAt(t1))) >> 12) & 31;
			if (t2 == 0) {
				t3 = (longAt(t1 - 4)) & 4294967292U;
			} else {
				t3 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((t2 - 1) << 2));
			}
			/* begin success: */
			successFlag = (t3 == (longAt(((((char *) specialObjectsOop)) + 4) + (11 << 2)))) && successFlag;
		l96:	/* end assertClassOf:is: */;
			if (successFlag) {
				/* begin externalizeIPandSP */
				instructionPointer = ((int) localIP);
				stackPointer = ((int) localSP);
				primitiveValue();
				/* begin internalizeIPandSP */
				localIP = ((char *) instructionPointer);
				localSP = ((char *) stackPointer);
			}
			if (!(successFlag)) {
				messageSelector = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (23 << 2))))) + 4) + ((26 * 2) << 2));
				argumentCount = 1;
				/* begin normalSend */
				goto commonSend;
			l99:	/* end fetchClassOf: */;
			l97:	/* end lookupInMethodCacheSel:class: */;
			}
		l95:	/* end case */;
			break;
		case 203:
			/* bytecodePrimDo */
			messageSelector = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (23 << 2))))) + 4) + ((27 * 2) << 2));
			argumentCount = 1;
			/* begin normalSend */
			goto commonSend;
		l102:	/* end fetchClassOf: */;
		l100:	/* end lookupInMethodCacheSel:class: */;
			break;
		case 204:
			/* bytecodePrimNew */
			messageSelector = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (23 << 2))))) + 4) + ((28 * 2) << 2));
			argumentCount = 0;
			/* begin normalSend */
			goto commonSend;
		l105:	/* end fetchClassOf: */;
		l103:	/* end lookupInMethodCacheSel:class: */;
			break;
		case 205:
			/* bytecodePrimNewWithArg */
			messageSelector = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (23 << 2))))) + 4) + ((29 * 2) << 2));
			argumentCount = 1;
			/* begin normalSend */
			goto commonSend;
		l108:	/* end fetchClassOf: */;
		l106:	/* end lookupInMethodCacheSel:class: */;
			break;
		case 206:
			/* bytecodePrimPointX */
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			/* begin primitivePointX */
			successFlag = true;
			/* begin popStack */
			t3 = longAt(stackPointer);
			stackPointer -= 4;
			t1 = t3;
			/* begin assertClassOf:is: */
			if ((t1 & 1)) {
				successFlag = false;
				goto l109;
			}
			t4 = (((unsigned) (longAt(t1))) >> 12) & 31;
			if (t4 == 0) {
				t5 = (longAt(t1 - 4)) & 4294967292U;
			} else {
				t5 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((t4 - 1) << 2));
			}
			/* begin success: */
			successFlag = (t5 == (longAt(((((char *) specialObjectsOop)) + 4) + (12 << 2)))) && successFlag;
		l109:	/* end assertClassOf:is: */;
			if (successFlag) {
				/* begin push: */
				longAtput(t2 = stackPointer + 4, longAt(((((char *) t1)) + 4) + (0 << 2)));
				stackPointer = t2;
			} else {
				/* begin unPop: */
				stackPointer += 1 * 4;
				failSpecialPrim(0);
			}
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
			break;
		case 207:
			/* bytecodePrimPointY */
			/* begin externalizeIPandSP */
			instructionPointer = ((int) localIP);
			stackPointer = ((int) localSP);
			/* begin primitivePointY */
			successFlag = true;
			/* begin popStack */
			t3 = longAt(stackPointer);
			stackPointer -= 4;
			t1 = t3;
			/* begin assertClassOf:is: */
			if ((t1 & 1)) {
				successFlag = false;
				goto l110;
			}
			t4 = (((unsigned) (longAt(t1))) >> 12) & 31;
			if (t4 == 0) {
				t5 = (longAt(t1 - 4)) & 4294967292U;
			} else {
				t5 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((t4 - 1) << 2));
			}
			/* begin success: */
			successFlag = (t5 == (longAt(((((char *) specialObjectsOop)) + 4) + (12 << 2)))) && successFlag;
		l110:	/* end assertClassOf:is: */;
			if (successFlag) {
				/* begin push: */
				longAtput(t2 = stackPointer + 4, longAt(((((char *) t1)) + 4) + (1 << 2)));
				stackPointer = t2;
			} else {
				/* begin unPop: */
				stackPointer += 1 * 4;
				failSpecialPrim(0);
			}
			/* begin internalizeIPandSP */
			localIP = ((char *) instructionPointer);
			localSP = ((char *) stackPointer);
			break;
		case 208:
		case 209:
		case 210:
		case 211:
		case 212:
		case 213:
		case 214:
		case 215:
		case 216:
		case 217:
		case 218:
		case 219:
		case 220:
		case 221:
		case 222:
		case 223:
		case 224:
		case 225:
		case 226:
		case 227:
		case 228:
		case 229:
		case 230:
		case 231:
		case 232:
		case 233:
		case 234:
		case 235:
		case 236:
		case 237:
		case 238:
		case 239:
		case 240:
		case 241:
		case 242:
		case 243:
		case 244:
		case 245:
		case 246:
		case 247:
		case 248:
		case 249:
		case 250:
		case 251:
		case 252:
		case 253:
		case 254:
		case 255:
			/* sendLiteralSelectorBytecode */
			/* begin literal: */
			t1 = currentBytecode & 15;
			messageSelector = longAt(((((char *) method)) + 4) + ((t1 + 1) << 2));
			argumentCount = ((((unsigned) currentBytecode) >> 4) & 3) - 1;
			/* begin normalSend */
			goto commonSend;
		l113:	/* end fetchClassOf: */;
		l111:	/* end lookupInMethodCacheSel:class: */;
			break;
		}
	}
	/* begin externalizeIPandSP */
	instructionPointer = ((int) localIP);
	stackPointer = ((int) localSP);
}

int isBytes(int oop) {
	return ((((unsigned) (longAt(oop))) >> 8) & 15) >= 8;
}

int isEmptyList(int aLinkedList) {
	return (longAt(((((char *) aLinkedList)) + 4) + (0 << 2))) == nilObj;
}

int isFreeObject(int oop) {
	return ((longAt(oop)) & 3) == 2;
}

int isIntegerObject(int objectPointer) {
	return (objectPointer & 1) > 0;
}

int isIntegerValue(int intValue) {
	return (intValue ^ (intValue << 1)) >= 0;
}

int isObjectForwarded(int oop) {
	return ((oop & 1) == 0) && (((longAt(oop)) & 2147483648U) != 0);
}

int isPointers(int oop) {
	return ((((unsigned) (longAt(oop))) >> 8) & 15) <= 4;
}

int isWords(int oop) {
	return ((((unsigned) (longAt(oop))) >> 8) & 15) == 6;
}

int isWordsOrBytes(int oop) {
    int fmt;

	fmt = (((unsigned) (longAt(oop))) >> 8) & 15;
	return (fmt == 6) || ((fmt >= 8) && (fmt <= 11));
}

int lastPointerOf(int objectPointer) {
    int methodHeader;
    int sz;
    int fmt;
    int header;
    int type;

	fmt = (((unsigned) (longAt(objectPointer))) >> 8) & 15;
	if (fmt < 4) {
		/* begin sizeBitsOfSafe: */
		header = longAt(objectPointer);
		/* begin rightType: */
		if ((header & 252) == 0) {
			type = 0;
			goto l1;
		} else {
			if ((header & 126976) == 0) {
				type = 1;
				goto l1;
			} else {
				type = 3;
				goto l1;
			}
		}
	l1:	/* end rightType: */;
		if (type == 0) {
			sz = (longAt(objectPointer - 8)) & 4294967292U;
			goto l2;
		} else {
			sz = header & 252;
			goto l2;
		}
	l2:	/* end sizeBitsOfSafe: */;
		return sz - 4;
	}
	if (fmt < 12) {
		return 0;
	}
	methodHeader = longAt(objectPointer + 4);
	return (((((unsigned) methodHeader) >> 10) & 255) * 4) + 4;
}

int lastPointerWhileForwarding(int oop) {
    int methodHeader;
    int size;
    int fwdBlock;
    int fmt;
    int header;

	header = longAt(oop);
	if ((header & 2147483648U) != 0) {
		fwdBlock = header & 2147483644;
		if (checkAssertions) {
			/* begin fwdBlockValidate: */
			if (!((fwdBlock > endOfMemory) && ((fwdBlock <= fwdTableNext) && ((fwdBlock & 3) == 0)))) {
				error("invalid fwd table entry");
			}
		}
		header = longAt(fwdBlock + 4);
	}
	fmt = (((unsigned) header) >> 8) & 15;
	if (fmt < 4) {
		if ((header & 3) == 0) {
			size = (longAt(oop - 8)) & 268435452;
		} else {
			size = header & 252;
		}
		return size - 4;
	}
	if (fmt < 12) {
		return 0;
	}
	methodHeader = longAt(oop + 4);
	return (((((unsigned) methodHeader) >> 10) & 255) * 4) + 4;
}

int lengthOf(int oop) {
    int sz;
    int header;
    int fmt;

	header = longAt(oop);
	if ((header & 3) == 0) {
		sz = (longAt(oop - 8)) & 4294967292U;
	} else {
		sz = header & 252;
	}
	fmt = (((unsigned) header) >> 8) & 15;
	if (fmt < 8) {
		return ((unsigned) (sz - 4)) >> 2;
	} else {
		return (sz - 4) - (fmt & 3);
	}
}

int lengthOfbaseHeaderformat(int oop, int hdr, int fmt) {
    int sz;

	if ((hdr & 3) == 0) {
		sz = (longAt(oop - 8)) & 4294967292U;
	} else {
		sz = hdr & 252;
	}
	if (fmt < 8) {
		return ((unsigned) (sz - 4)) >> 2;
	} else {
		return (sz - 4) - (fmt & 3);
	}
}

int literal(int offset) {
	return longAt(((((char *) method)) + 4) + ((offset + 1) << 2));
}

int literalofMethod(int offset, int methodPointer) {
	return longAt(((((char *) methodPointer)) + 4) + ((offset + 1) << 2));
}

int literalCountOf(int methodPointer) {
	return (((unsigned) (longAt(((((char *) methodPointer)) + 4) + (0 << 2)))) >> 10) & 255;
}

int literalCountOfHeader(int headerPointer) {
	return (((unsigned) headerPointer) >> 10) & 255;
}

int loadBitBltFrom(int bbObj) {
    int destBitsSize;
    int destWidth;
    int destHeight;
    int sourceBitsSize;
    int sourcePixPerWord;
    int halftoneBits;
    int cmSize;
    int sz;
    int header;
    int fmt;
    int sz1;
    int header1;
    int fmt1;

	bitBltOop = bbObj;
	combinationRule = fetchIntegerofObject(3, bitBltOop);
	if ((!successFlag) || ((combinationRule < 0) || (combinationRule > 33))) {
		return false;
	}
	if ((combinationRule >= 16) && (combinationRule <= 17)) {
		return false;
	}
	sourceForm = longAt(((((char *) bitBltOop)) + 4) + (1 << 2));
	/* begin ignoreSourceOrHalftone: */
	if (sourceForm == nilObj) {
		noSource = true;
		goto l3;
	}
	if (combinationRule == 0) {
		noSource = true;
		goto l3;
	}
	if (combinationRule == 5) {
		noSource = true;
		goto l3;
	}
	if (combinationRule == 10) {
		noSource = true;
		goto l3;
	}
	if (combinationRule == 15) {
		noSource = true;
		goto l3;
	}
	noSource = false;
l3:	/* end ignoreSourceOrHalftone: */;
	halftoneForm = longAt(((((char *) bitBltOop)) + 4) + (2 << 2));
	/* begin ignoreSourceOrHalftone: */
	if (halftoneForm == nilObj) {
		noHalftone = true;
		goto l4;
	}
	if (combinationRule == 0) {
		noHalftone = true;
		goto l4;
	}
	if (combinationRule == 5) {
		noHalftone = true;
		goto l4;
	}
	if (combinationRule == 10) {
		noHalftone = true;
		goto l4;
	}
	if (combinationRule == 15) {
		noHalftone = true;
		goto l4;
	}
	noHalftone = false;
l4:	/* end ignoreSourceOrHalftone: */;
	destForm = longAt(((((char *) bitBltOop)) + 4) + (0 << 2));
	if (!((((((unsigned) (longAt(destForm))) >> 8) & 15) <= 4) && ((lengthOf(destForm)) >= 4))) {
		return false;
	}
	destBits = longAt(((((char *) destForm)) + 4) + (0 << 2));
	destBitsSize = byteLengthOf(destBits);
	destWidth = fetchIntegerofObject(1, destForm);
	destHeight = fetchIntegerofObject(2, destForm);
	if (!((destWidth >= 0) && (destHeight >= 0))) {
		return false;
	}
	destPixSize = fetchIntegerofObject(3, destForm);
	pixPerWord = 32 / destPixSize;
	destRaster = (destWidth + (pixPerWord - 1)) / pixPerWord;
	if (!((isWordsOrBytes(destBits)) && (destBitsSize == ((destRaster * destHeight) * 4)))) {
		return false;
	}
	destX = fetchIntegerOrTruncFloatofObject(4, bitBltOop);
	destY = fetchIntegerOrTruncFloatofObject(5, bitBltOop);
	width = fetchIntegerOrTruncFloatofObject(6, bitBltOop);
	height = fetchIntegerOrTruncFloatofObject(7, bitBltOop);
	if (!successFlag) {
		return false;
	}
	if (noSource) {
		sourceX = sourceY = 0;
	} else {
		if (!((((((unsigned) (longAt(sourceForm))) >> 8) & 15) <= 4) && ((lengthOf(sourceForm)) >= 4))) {
			return false;
		}
		sourceBits = longAt(((((char *) sourceForm)) + 4) + (0 << 2));
		sourceBitsSize = byteLengthOf(sourceBits);
		srcWidth = fetchIntegerOrTruncFloatofObject(1, sourceForm);
		srcHeight = fetchIntegerOrTruncFloatofObject(2, sourceForm);
		if (!((srcWidth >= 0) && (srcHeight >= 0))) {
			return false;
		}
		sourcePixSize = fetchIntegerofObject(3, sourceForm);
		sourcePixPerWord = 32 / sourcePixSize;
		sourceRaster = (srcWidth + (sourcePixPerWord - 1)) / sourcePixPerWord;
		if (!((isWordsOrBytes(sourceBits)) && (sourceBitsSize == ((sourceRaster * srcHeight) * 4)))) {
			return false;
		}
		colorMap = longAt(((((char *) bitBltOop)) + 4) + (14 << 2));
		if (!(colorMap == nilObj)) {
			if (((((unsigned) (longAt(colorMap))) >> 8) & 15) == 6) {
				/* begin lengthOf: */
				header = longAt(colorMap);
				if ((header & 3) == 0) {
					sz = (longAt(colorMap - 8)) & 4294967292U;
				} else {
					sz = header & 252;
				}
				fmt = (((unsigned) header) >> 8) & 15;
				if (fmt < 8) {
					cmSize = ((unsigned) (sz - 4)) >> 2;
					goto l1;
				} else {
					cmSize = (sz - 4) - (fmt & 3);
					goto l1;
				}
			l1:	/* end lengthOf: */;
				cmBitsPerColor = 0;
				if (cmSize == 512) {
					cmBitsPerColor = 3;
				}
				if (cmSize == 4096) {
					cmBitsPerColor = 4;
				}
				if (cmSize == 32768) {
					cmBitsPerColor = 5;
				}
				if (primitiveIndex != 147) {
					if (sourcePixSize <= 8) {
						if (!(cmSize == (1 << sourcePixSize))) {
							return false;
						}
					} else {
						if (cmBitsPerColor == 0) {
							return false;
						}
					}
				}
			} else {
				return false;
			}
		}
		sourceX = fetchIntegerOrTruncFloatofObject(8, bitBltOop);
		sourceY = fetchIntegerOrTruncFloatofObject(9, bitBltOop);
	}
	if (!(noHalftone)) {
		if ((((((unsigned) (longAt(halftoneForm))) >> 8) & 15) <= 4) && ((lengthOf(halftoneForm)) >= 4)) {
			halftoneBits = longAt(((((char *) halftoneForm)) + 4) + (0 << 2));
			halftoneHeight = fetchIntegerofObject(2, halftoneForm);
			if (!(((((unsigned) (longAt(halftoneBits))) >> 8) & 15) == 6)) {
				noHalftone = true;
			}
		} else {
			if (!((!(((((unsigned) (longAt(halftoneForm))) >> 8) & 15) <= 4)) && (((((unsigned) (longAt(halftoneForm))) >> 8) & 15) == 6))) {
				return false;
			}
			halftoneBits = halftoneForm;
			/* begin lengthOf: */
			header1 = longAt(halftoneBits);
			if ((header1 & 3) == 0) {
				sz1 = (longAt(halftoneBits - 8)) & 4294967292U;
			} else {
				sz1 = header1 & 252;
			}
			fmt1 = (((unsigned) header1) >> 8) & 15;
			if (fmt1 < 8) {
				halftoneHeight = ((unsigned) (sz1 - 4)) >> 2;
				goto l2;
			} else {
				halftoneHeight = (sz1 - 4) - (fmt1 & 3);
				goto l2;
			}
		l2:	/* end lengthOf: */;
		}
		halftoneBase = halftoneBits + 4;
	}
	clipX = fetchIntegerOrTruncFloatofObject(10, bitBltOop);
	clipY = fetchIntegerOrTruncFloatofObject(11, bitBltOop);
	clipWidth = fetchIntegerOrTruncFloatofObject(12, bitBltOop);
	clipHeight = fetchIntegerOrTruncFloatofObject(13, bitBltOop);
	if (!successFlag) {
		return false;
	}
	if (clipX < 0) {
		clipWidth += clipX;
		clipX = 0;
	}
	if (clipY < 0) {
		clipHeight += clipY;
		clipY = 0;
	}
	if ((clipX + clipWidth) > destWidth) {
		clipWidth = destWidth - clipX;
	}
	if ((clipY + clipHeight) > destHeight) {
		clipHeight = destHeight - clipY;
	}
	return true;
}

int loadInitialContext(void) {
    int sched;
    int proc;
    int activeCntx;
    int tmp;

	sched = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (3 << 2))))) + 4) + (1 << 2));
	proc = longAt(((((char *) sched)) + 4) + (1 << 2));
	activeContext = longAt(((((char *) proc)) + 4) + (1 << 2));
	if (activeContext < youngStart) {
		beRootIfOld(activeContext);
	}
	/* begin fetchContextRegisters: */
	activeCntx = activeContext;
	tmp = longAt(((((char *) activeCntx)) + 4) + (3 << 2));
	if ((tmp & 1)) {
		tmp = longAt(((((char *) activeCntx)) + 4) + (5 << 2));
		if (tmp < youngStart) {
			beRootIfOld(tmp);
		}
	} else {
		tmp = activeCntx;
	}
	theHomeContext = tmp;
	receiver = longAt(((((char *) tmp)) + 4) + (5 << 2));
	method = longAt(((((char *) tmp)) + 4) + (3 << 2));
	tmp = ((longAt(((((char *) activeCntx)) + 4) + (1 << 2))) >> 1);
	instructionPointer = ((method + tmp) + 4) - 2;
	tmp = ((longAt(((((char *) activeCntx)) + 4) + (2 << 2))) >> 1);
	stackPointer = (activeCntx + 4) + (((6 + tmp) - 1) * 4);
	reclaimableContextCount = 0;
}

int loadScannerFromstartstopstringrightXstopArraydisplayFlag(int bbObj, int start, int stop, int string, int rightX, int stopArray, int displayFlag) {
    int successValue;
    int successValue1;
    int successValue2;

	scanStart = start;
	scanStop = stop;
	scanString = string;
	scanRightX = rightX;
	scanStopArray = stopArray;
	scanDisplayFlag = displayFlag;
	/* begin success: */
	successValue1 = (((((unsigned) (longAt(scanStopArray))) >> 8) & 15) <= 4) && ((lengthOf(scanStopArray)) >= 1);
	successFlag = successValue1 && successFlag;
	scanXTable = longAt(((((char *) bbObj)) + 4) + (16 << 2));
	/* begin success: */
	successValue2 = (((((unsigned) (longAt(scanXTable))) >> 8) & 15) <= 4) && ((lengthOf(scanXTable)) >= 1);
	successFlag = successValue2 && successFlag;
	/* begin storeInteger:ofObject:withValue: */
	if ((0 ^ (0 << 1)) >= 0) {
		longAtput(((((char *) bbObj)) + 4) + (6 << 2), ((0 << 1) | 1));
	} else {
		primitiveFail();
	}
	/* begin storeInteger:ofObject:withValue: */
	if ((0 ^ (0 << 1)) >= 0) {
		longAtput(((((char *) bbObj)) + 4) + (8 << 2), ((0 << 1) | 1));
	} else {
		primitiveFail();
	}
	if (scanDisplayFlag) {
		/* begin success: */
		successValue = loadBitBltFrom(bbObj);
		successFlag = successValue && successFlag;
	} else {
		bitBltOop = bbObj;
		destX = fetchIntegerOrTruncFloatofObject(4, bbObj);
	}
	return !(!successFlag);
}

int lookupInMethodCacheSelclass(int selector, int class) {
    int probe;
    int p;
    int hash;

	hash = ((unsigned) (selector ^ class)) >> 2;
	probe = (hash & 511) + 1;
	for (p = 1; p <= 3; p += 1) {
		if (((methodCache[probe]) == selector) && ((methodCache[probe + 512]) == class)) {
			newMethod = methodCache[probe + (512 * 2)];
			primitiveIndex = methodCache[probe + (512 * 3)];
			return true;
		}
		probe = ((((unsigned) hash) >> p) & 511) + 1;
	}
	return false;
}

int lookupMethodInClass(int class) {
    int dictionary;
    int currentClass;
    int found;
    int rclass;
    int oop;
    int argumentArray;
    int message;
    int oop1;
    int valuePointer;
    int toIndex;
    int fromIndex;
    int lastFrom;
    int sp;
    int methodArray;
    int mask;
    int wrapAround;
    int nextSelector;
    int index;
    int length;
    int sz;
    int primBits;
    int header;

	currentClass = class;
	while (currentClass != nilObj) {
		dictionary = longAt(((((char *) currentClass)) + 4) + (1 << 2));
		/* begin lookupMethodInDictionary: */
		/* begin fetchWordLengthOf: */
		/* begin sizeBitsOf: */
		header = longAt(dictionary);
		if ((header & 3) == 0) {
			sz = (longAt(dictionary - 8)) & 4294967292U;
			goto l2;
		} else {
			sz = header & 252;
			goto l2;
		}
	l2:	/* end sizeBitsOf: */;
		length = ((unsigned) (sz - 4)) >> 2;
		mask = (length - 2) - 1;
		if ((messageSelector & 1)) {
			index = (mask & ((messageSelector >> 1))) + 2;
		} else {
			index = (mask & ((((unsigned) (longAt(messageSelector))) >> 17) & 4095)) + 2;
		}
		wrapAround = false;
		while (true) {
			nextSelector = longAt(((((char *) dictionary)) + 4) + (index << 2));
			if (nextSelector == nilObj) {
				found = false;
				goto l3;
			}
			if (nextSelector == messageSelector) {
				methodArray = longAt(((((char *) dictionary)) + 4) + (1 << 2));
				newMethod = longAt(((((char *) methodArray)) + 4) + ((index - 2) << 2));
				/* begin primitiveIndexOf: */
				primBits = (((unsigned) (longAt(((((char *) newMethod)) + 4) + (0 << 2)))) >> 1) & 805306879;
				if (primBits > 511) {
					primitiveIndex = (primBits & 511) + (((unsigned) primBits) >> 19);
					goto l1;
				} else {
					primitiveIndex = primBits;
					goto l1;
				}
			l1:	/* end primitiveIndexOf: */;
				found = true;
				goto l3;
			}
			index += 1;
			if (index == length) {
				if (wrapAround) {
					found = false;
					goto l3;
				}
				wrapAround = true;
				index = 2;
			}
		}
	l3:	/* end lookupMethodInDictionary: */;
		if (found) {
			return currentClass;
		}
		currentClass = longAt(((((char *) currentClass)) + 4) + (0 << 2));
	}
	if (messageSelector == (longAt(((((char *) specialObjectsOop)) + 4) + (20 << 2)))) {
		error("Recursive not understood error encountered");
	}
	/* begin pushRemappableOop: */
	remapBuffer[remapBufferCount += 1] = class;
	/* begin createActualMessage */
	argumentArray = instantiateClassindexableSize(longAt(((((char *) specialObjectsOop)) + 4) + (7 << 2)), argumentCount);
	/* begin pushRemappableOop: */
	remapBuffer[remapBufferCount += 1] = argumentArray;
	message = instantiateClassindexableSize(longAt(((((char *) specialObjectsOop)) + 4) + (15 << 2)), 0);
	/* begin popRemappableOop */
	oop1 = remapBuffer[remapBufferCount];
	remapBufferCount -= 1;
	argumentArray = oop1;
	if (argumentArray < youngStart) {
		beRootIfOld(argumentArray);
	}
	/* begin storePointer:ofObject:withValue: */
	valuePointer = messageSelector;
	if (message < youngStart) {
		possibleRootStoreIntovalue(message, valuePointer);
	}
	longAtput(((((char *) message)) + 4) + (0 << 2), valuePointer);
	/* begin storePointer:ofObject:withValue: */
	if (message < youngStart) {
		possibleRootStoreIntovalue(message, argumentArray);
	}
	longAtput(((((char *) message)) + 4) + (1 << 2), argumentArray);
	/* begin transfer:fromIndex:ofObject:toIndex:ofObject: */
	fromIndex = activeContext + (((((unsigned) ((stackPointer - activeContext) - 4)) >> 2) - (argumentCount - 1)) * 4);
	toIndex = argumentArray + (0 * 4);
	lastFrom = fromIndex + (argumentCount * 4);
	while (fromIndex < lastFrom) {
		fromIndex += 4;
		toIndex += 4;
		longAtput(toIndex, longAt(fromIndex));
	}
	/* begin pop: */
	stackPointer -= argumentCount * 4;
	/* begin push: */
	longAtput(sp = stackPointer + 4, message);
	stackPointer = sp;
	argumentCount = 1;
	/* begin popRemappableOop */
	oop = remapBuffer[remapBufferCount];
	remapBufferCount -= 1;
	rclass = oop;
	messageSelector = longAt(((((char *) specialObjectsOop)) + 4) + (20 << 2));
	return lookupMethodInClass(rclass);
}

int lookupMethodInDictionary(int dictionary) {
    int methodArray;
    int mask;
    int wrapAround;
    int nextSelector;
    int index;
    int length;
    int sz;
    int primBits;
    int header;

	/* begin fetchWordLengthOf: */
	/* begin sizeBitsOf: */
	header = longAt(dictionary);
	if ((header & 3) == 0) {
		sz = (longAt(dictionary - 8)) & 4294967292U;
		goto l2;
	} else {
		sz = header & 252;
		goto l2;
	}
l2:	/* end sizeBitsOf: */;
	length = ((unsigned) (sz - 4)) >> 2;
	mask = (length - 2) - 1;
	if ((messageSelector & 1)) {
		index = (mask & ((messageSelector >> 1))) + 2;
	} else {
		index = (mask & ((((unsigned) (longAt(messageSelector))) >> 17) & 4095)) + 2;
	}
	wrapAround = false;
	while (true) {
		nextSelector = longAt(((((char *) dictionary)) + 4) + (index << 2));
		if (nextSelector == nilObj) {
			return false;
		}
		if (nextSelector == messageSelector) {
			methodArray = longAt(((((char *) dictionary)) + 4) + (1 << 2));
			newMethod = longAt(((((char *) methodArray)) + 4) + ((index - 2) << 2));
			/* begin primitiveIndexOf: */
			primBits = (((unsigned) (longAt(((((char *) newMethod)) + 4) + (0 << 2)))) >> 1) & 805306879;
			if (primBits > 511) {
				primitiveIndex = (primBits & 511) + (((unsigned) primBits) >> 19);
				goto l1;
			} else {
				primitiveIndex = primBits;
				goto l1;
			}
		l1:	/* end primitiveIndexOf: */;
			return true;
		}
		index += 1;
		if (index == length) {
			if (wrapAround) {
				return false;
			}
			wrapAround = true;
			index = 2;
		}
	}
}

int lowestFreeAfter(int chunk) {
    int oopHeader;
    int oop;
    int oopHeaderType;
    int oopSize;
    int extra;
    int extra1;
    int type;
    int extra2;
    int type1;
    int extra3;

	/* begin oopFromChunk: */
	/* begin extraHeaderBytes: */
	type1 = (longAt(chunk)) & 3;
	if (type1 > 1) {
		extra3 = 0;
	} else {
		if (type1 == 1) {
			extra3 = 4;
		} else {
			extra3 = 8;
		}
	}
	extra1 = extra3;
	oop = chunk + extra1;
	while (oop < endOfMemory) {
		oopHeader = longAt(oop);
		oopHeaderType = oopHeader & 3;
		if (oopHeaderType == 2) {
			return oop;
		} else {
			if (oopHeaderType == 0) {
				oopSize = (longAt(oop - 8)) & 4294967292U;
			} else {
				oopSize = oopHeader & 252;
			}
		}
		/* begin oopFromChunk: */
		/* begin extraHeaderBytes: */
		type = (longAt(oop + oopSize)) & 3;
		if (type > 1) {
			extra2 = 0;
		} else {
			if (type == 1) {
				extra2 = 4;
			} else {
				extra2 = 8;
			}
		}
		extra = extra2;
		oop = (oop + oopSize) + extra;
	}
	error("expected to find at least one free object");
}

int makeDirEntryNamesizecreateDatemodDateisDirfileSize(char *entryName, int entryNameSize, int createDate, int modifiedDate, int dirFlag, int fileSize) {
    int modDateOop;
    int i;
    int nameString;
    int createDateOop;
    int results;
    int valuePointer;
    int valuePointer1;
    int oop;
    int oop1;
    int oop2;
    int oop3;
    int oop4;
    int oop5;
    int oop6;
    int oop7;

	/* begin pushRemappableOop: */
	oop = instantiateClassindexableSize(longAt(((((char *) specialObjectsOop)) + 4) + (7 << 2)), 5);
	remapBuffer[remapBufferCount += 1] = oop;
	/* begin pushRemappableOop: */
	oop1 = instantiateClassindexableSize(longAt(((((char *) specialObjectsOop)) + 4) + (6 << 2)), entryNameSize);
	remapBuffer[remapBufferCount += 1] = oop1;
	/* begin pushRemappableOop: */
	oop2 = positive32BitIntegerFor(createDate);
	remapBuffer[remapBufferCount += 1] = oop2;
	/* begin pushRemappableOop: */
	oop3 = positive32BitIntegerFor(modifiedDate);
	remapBuffer[remapBufferCount += 1] = oop3;
	/* begin popRemappableOop */
	oop4 = remapBuffer[remapBufferCount];
	remapBufferCount -= 1;
	modDateOop = oop4;
	/* begin popRemappableOop */
	oop5 = remapBuffer[remapBufferCount];
	remapBufferCount -= 1;
	createDateOop = oop5;
	/* begin popRemappableOop */
	oop6 = remapBuffer[remapBufferCount];
	remapBufferCount -= 1;
	nameString = oop6;
	/* begin popRemappableOop */
	oop7 = remapBuffer[remapBufferCount];
	remapBufferCount -= 1;
	results = oop7;
	for (i = 0; i <= (entryNameSize - 1); i += 1) {
		byteAtput(((((char *) nameString)) + 4) + i, entryName[i]);
	}
	/* begin storePointer:ofObject:withValue: */
	if (results < youngStart) {
		possibleRootStoreIntovalue(results, nameString);
	}
	longAtput(((((char *) results)) + 4) + (0 << 2), nameString);
	/* begin storePointer:ofObject:withValue: */
	if (results < youngStart) {
		possibleRootStoreIntovalue(results, createDateOop);
	}
	longAtput(((((char *) results)) + 4) + (1 << 2), createDateOop);
	/* begin storePointer:ofObject:withValue: */
	if (results < youngStart) {
		possibleRootStoreIntovalue(results, modDateOop);
	}
	longAtput(((((char *) results)) + 4) + (2 << 2), modDateOop);
	if (dirFlag) {
		/* begin storePointer:ofObject:withValue: */
		valuePointer = trueObj;
		if (results < youngStart) {
			possibleRootStoreIntovalue(results, valuePointer);
		}
		longAtput(((((char *) results)) + 4) + (3 << 2), valuePointer);
	} else {
		/* begin storePointer:ofObject:withValue: */
		valuePointer1 = falseObj;
		if (results < youngStart) {
			possibleRootStoreIntovalue(results, valuePointer1);
		}
		longAtput(((((char *) results)) + 4) + (3 << 2), valuePointer1);
	}
	/* begin storePointer:ofObject:withValue: */
	if (results < youngStart) {
		possibleRootStoreIntovalue(results, ((fileSize << 1) | 1));
	}
	longAtput(((((char *) results)) + 4) + (4 << 2), ((fileSize << 1) | 1));
	return results;
}

int makePointwithxValueyValue(int xValue, int yValue) {
    int pointResult;

	pointResult = instantiateSmallClasssizeInBytesfill(longAt(((((char *) specialObjectsOop)) + 4) + (12 << 2)), 12, nilObj);
	/* begin storePointer:ofObject:withValue: */
	if (pointResult < youngStart) {
		possibleRootStoreIntovalue(pointResult, ((xValue << 1) | 1));
	}
	longAtput(((((char *) pointResult)) + 4) + (0 << 2), ((xValue << 1) | 1));
	/* begin storePointer:ofObject:withValue: */
	if (pointResult < youngStart) {
		possibleRootStoreIntovalue(pointResult, ((yValue << 1) | 1));
	}
	longAtput(((((char *) pointResult)) + 4) + (1 << 2), ((yValue << 1) | 1));
	return pointResult;
}

int mapInterpreterOops(void) {
    int i;
    int oop;
    int i1;

	nilObj = remap(nilObj);
	falseObj = remap(falseObj);
	trueObj = remap(trueObj);
	specialObjectsOop = remap(specialObjectsOop);
	stackPointer -= activeContext;
	activeContext = remap(activeContext);
	stackPointer += activeContext;
	theHomeContext = remap(theHomeContext);
	instructionPointer -= method;
	method = remap(method);
	instructionPointer += method;
	receiver = remap(receiver);
	messageSelector = remap(messageSelector);
	newMethod = remap(newMethod);
	for (i = 1; i <= remapBufferCount; i += 1) {
		oop = remapBuffer[i];
		if (!((oop & 1))) {
			remapBuffer[i] = (remap(oop));
		}
	}
	/* begin flushMethodCache */
	for (i1 = 1; i1 <= 2048; i1 += 1) {
		methodCache[i1] = 0;
	}
	mcProbe = 0;
}

int mapPointersInObjectsFromto(int memStart, int memEnd) {
    int oop;
    int i;
    int fwdBlock;
    int fieldOffset;
    int fieldOop;
    int newOop;
    int fwdBlock1;
    int fieldOffset1;
    int fieldOop1;
    int newOop1;
    int i2;
    int oop1;
    int i1;
    int extra;
    int type;
    int extra1;
    int methodHeader;
    int size;
    int fwdBlock2;
    int fmt;
    int header;
    int newClassOop;
    int fwdBlock3;
    int classHeader;
    int classOop;
    int newClassHeader;
    int methodHeader1;
    int size1;
    int fwdBlock4;
    int fmt1;
    int header1;
    int newClassOop1;
    int fwdBlock5;
    int classHeader1;
    int classOop1;
    int newClassHeader1;
    int sz;
    int fwdBlock6;
    int realHeader;
    int header2;
    int extra3;
    int type2;
    int extra12;
    int sz1;
    int header11;
    int extra2;
    int type1;
    int extra11;

	/* begin mapInterpreterOops */
	nilObj = remap(nilObj);
	falseObj = remap(falseObj);
	trueObj = remap(trueObj);
	specialObjectsOop = remap(specialObjectsOop);
	stackPointer -= activeContext;
	activeContext = remap(activeContext);
	stackPointer += activeContext;
	theHomeContext = remap(theHomeContext);
	instructionPointer -= method;
	method = remap(method);
	instructionPointer += method;
	receiver = remap(receiver);
	messageSelector = remap(messageSelector);
	newMethod = remap(newMethod);
	for (i2 = 1; i2 <= remapBufferCount; i2 += 1) {
		oop1 = remapBuffer[i2];
		if (!((oop1 & 1))) {
			remapBuffer[i2] = (remap(oop1));
		}
	}
	/* begin flushMethodCache */
	for (i1 = 1; i1 <= 2048; i1 += 1) {
		methodCache[i1] = 0;
	}
	mcProbe = 0;
	for (i = 1; i <= rootTableCount; i += 1) {
		oop = rootTable[i];
		if ((oop < memStart) || (oop >= memEnd)) {
			/* begin remapFieldsAndClassOf: */
			/* begin lastPointerWhileForwarding: */
			header = longAt(oop);
			if ((header & 2147483648U) != 0) {
				fwdBlock2 = header & 2147483644;
				if (checkAssertions) {
					/* begin fwdBlockValidate: */
					if (!((fwdBlock2 > endOfMemory) && ((fwdBlock2 <= fwdTableNext) && ((fwdBlock2 & 3) == 0)))) {
						error("invalid fwd table entry");
					}
				}
				header = longAt(fwdBlock2 + 4);
			}
			fmt = (((unsigned) header) >> 8) & 15;
			if (fmt < 4) {
				if ((header & 3) == 0) {
					size = (longAt(oop - 8)) & 268435452;
				} else {
					size = header & 252;
				}
				fieldOffset = size - 4;
				goto l1;
			}
			if (fmt < 12) {
				fieldOffset = 0;
				goto l1;
			}
			methodHeader = longAt(oop + 4);
			fieldOffset = (((((unsigned) methodHeader) >> 10) & 255) * 4) + 4;
		l1:	/* end lastPointerWhileForwarding: */;
			while (fieldOffset >= 4) {
				fieldOop = longAt(oop + fieldOffset);
				if (((fieldOop & 1) == 0) && (((longAt(fieldOop)) & 2147483648U) != 0)) {
					fwdBlock = (longAt(fieldOop)) & 2147483644;
					if (checkAssertions) {
						/* begin fwdBlockValidate: */
						if (!((fwdBlock > endOfMemory) && ((fwdBlock <= fwdTableNext) && ((fwdBlock & 3) == 0)))) {
							error("invalid fwd table entry");
						}
					}
					newOop = longAt(fwdBlock);
					longAtput(oop + fieldOffset, newOop);
					if ((oop < youngStart) && (newOop >= youngStart)) {
						beRootWhileForwarding(oop);
					}
				}
				fieldOffset -= 4;
			}
			/* begin remapClassOf: */
			if (((longAt(oop)) & 3) == 3) {
				goto l2;
			}
			classHeader = longAt(oop - 4);
			classOop = classHeader & 4294967292U;
			if (((classOop & 1) == 0) && (((longAt(classOop)) & 2147483648U) != 0)) {
				fwdBlock3 = (longAt(classOop)) & 2147483644;
				if (checkAssertions) {
					/* begin fwdBlockValidate: */
					if (!((fwdBlock3 > endOfMemory) && ((fwdBlock3 <= fwdTableNext) && ((fwdBlock3 & 3) == 0)))) {
						error("invalid fwd table entry");
					}
				}
				newClassOop = longAt(fwdBlock3);
				newClassHeader = newClassOop | (classHeader & 3);
				longAtput(oop - 4, newClassHeader);
				if ((oop < youngStart) && (newClassOop >= youngStart)) {
					beRootWhileForwarding(oop);
				}
			}
		l2:	/* end remapClassOf: */;
		}
	}
	/* begin oopFromChunk: */
	/* begin extraHeaderBytes: */
	type = (longAt(memStart)) & 3;
	if (type > 1) {
		extra1 = 0;
	} else {
		if (type == 1) {
			extra1 = 4;
		} else {
			extra1 = 8;
		}
	}
	extra = extra1;
	oop = memStart + extra;
	while (oop < memEnd) {
		if (!(((longAt(oop)) & 3) == 2)) {
			/* begin remapFieldsAndClassOf: */
			/* begin lastPointerWhileForwarding: */
			header1 = longAt(oop);
			if ((header1 & 2147483648U) != 0) {
				fwdBlock4 = header1 & 2147483644;
				if (checkAssertions) {
					/* begin fwdBlockValidate: */
					if (!((fwdBlock4 > endOfMemory) && ((fwdBlock4 <= fwdTableNext) && ((fwdBlock4 & 3) == 0)))) {
						error("invalid fwd table entry");
					}
				}
				header1 = longAt(fwdBlock4 + 4);
			}
			fmt1 = (((unsigned) header1) >> 8) & 15;
			if (fmt1 < 4) {
				if ((header1 & 3) == 0) {
					size1 = (longAt(oop - 8)) & 268435452;
				} else {
					size1 = header1 & 252;
				}
				fieldOffset1 = size1 - 4;
				goto l3;
			}
			if (fmt1 < 12) {
				fieldOffset1 = 0;
				goto l3;
			}
			methodHeader1 = longAt(oop + 4);
			fieldOffset1 = (((((unsigned) methodHeader1) >> 10) & 255) * 4) + 4;
		l3:	/* end lastPointerWhileForwarding: */;
			while (fieldOffset1 >= 4) {
				fieldOop1 = longAt(oop + fieldOffset1);
				if (((fieldOop1 & 1) == 0) && (((longAt(fieldOop1)) & 2147483648U) != 0)) {
					fwdBlock1 = (longAt(fieldOop1)) & 2147483644;
					if (checkAssertions) {
						/* begin fwdBlockValidate: */
						if (!((fwdBlock1 > endOfMemory) && ((fwdBlock1 <= fwdTableNext) && ((fwdBlock1 & 3) == 0)))) {
							error("invalid fwd table entry");
						}
					}
					newOop1 = longAt(fwdBlock1);
					longAtput(oop + fieldOffset1, newOop1);
					if ((oop < youngStart) && (newOop1 >= youngStart)) {
						beRootWhileForwarding(oop);
					}
				}
				fieldOffset1 -= 4;
			}
			/* begin remapClassOf: */
			if (((longAt(oop)) & 3) == 3) {
				goto l4;
			}
			classHeader1 = longAt(oop - 4);
			classOop1 = classHeader1 & 4294967292U;
			if (((classOop1 & 1) == 0) && (((longAt(classOop1)) & 2147483648U) != 0)) {
				fwdBlock5 = (longAt(classOop1)) & 2147483644;
				if (checkAssertions) {
					/* begin fwdBlockValidate: */
					if (!((fwdBlock5 > endOfMemory) && ((fwdBlock5 <= fwdTableNext) && ((fwdBlock5 & 3) == 0)))) {
						error("invalid fwd table entry");
					}
				}
				newClassOop1 = longAt(fwdBlock5);
				newClassHeader1 = newClassOop1 | (classHeader1 & 3);
				longAtput(oop - 4, newClassHeader1);
				if ((oop < youngStart) && (newClassOop1 >= youngStart)) {
					beRootWhileForwarding(oop);
				}
			}
		l4:	/* end remapClassOf: */;
		}
		/* begin objectAfterWhileForwarding: */
		header2 = longAt(oop);
		if ((header2 & 2147483648U) == 0) {
			/* begin objectAfter: */
			if (checkAssertions) {
				if (oop >= endOfMemory) {
					error("no objects after the end of memory");
				}
			}
			if (((longAt(oop)) & 3) == 2) {
				sz1 = (longAt(oop)) & 536870908;
			} else {
				/* begin sizeBitsOf: */
				header11 = longAt(oop);
				if ((header11 & 3) == 0) {
					sz1 = (longAt(oop - 8)) & 4294967292U;
					goto l5;
				} else {
					sz1 = header11 & 252;
					goto l5;
				}
			l5:	/* end sizeBitsOf: */;
			}
			/* begin oopFromChunk: */
			/* begin extraHeaderBytes: */
			type1 = (longAt(oop + sz1)) & 3;
			if (type1 > 1) {
				extra11 = 0;
			} else {
				if (type1 == 1) {
					extra11 = 4;
				} else {
					extra11 = 8;
				}
			}
			extra2 = extra11;
			oop = (oop + sz1) + extra2;
			goto l6;
		}
		fwdBlock6 = header2 & 2147483644;
		if (checkAssertions) {
			/* begin fwdBlockValidate: */
			if (!((fwdBlock6 > endOfMemory) && ((fwdBlock6 <= fwdTableNext) && ((fwdBlock6 & 3) == 0)))) {
				error("invalid fwd table entry");
			}
		}
		realHeader = longAt(fwdBlock6 + 4);
		if ((realHeader & 3) == 0) {
			sz = (longAt(oop - 8)) & 268435452;
		} else {
			sz = realHeader & 252;
		}
		/* begin oopFromChunk: */
		/* begin extraHeaderBytes: */
		type2 = (longAt(oop + sz)) & 3;
		if (type2 > 1) {
			extra12 = 0;
		} else {
			if (type2 == 1) {
				extra12 = 4;
			} else {
				extra12 = 8;
			}
		}
		extra3 = extra12;
		oop = (oop + sz) + extra3;
	l6:	/* end objectAfterWhileForwarding: */;
	}
}

int markAndTrace(int oop) {
    int action;
    int lastFieldOffset;
    int header;
    int header1;
    int type;
    int oop1;
    int lastFieldOffset1;
    int header2;
    int typeBits;
    int childType;
    int methodHeader;
    int sz;
    int fmt;
    int methodHeader1;
    int sz1;
    int fmt1;
    int header3;
    int type1;
    int header4;
    int type2;

	header = longAt(oop);
	header = (header & 4294967292U) | 2;
	if (oop >= youngStart) {
		header = header | 2147483648U;
	}
	longAtput(oop, header);
	parentField = 3;
	child = oop;
	/* begin lastPointerOf: */
	fmt1 = (((unsigned) (longAt(oop))) >> 8) & 15;
	if (fmt1 < 4) {
		/* begin sizeBitsOfSafe: */
		header3 = longAt(oop);
		/* begin rightType: */
		if ((header3 & 252) == 0) {
			type1 = 0;
			goto l9;
		} else {
			if ((header3 & 126976) == 0) {
				type1 = 1;
				goto l9;
			} else {
				type1 = 3;
				goto l9;
			}
		}
	l9:	/* end rightType: */;
		if (type1 == 0) {
			sz1 = (longAt(oop - 8)) & 4294967292U;
			goto l10;
		} else {
			sz1 = header3 & 252;
			goto l10;
		}
	l10:	/* end sizeBitsOfSafe: */;
		lastFieldOffset = sz1 - 4;
		goto l8;
	}
	if (fmt1 < 12) {
		lastFieldOffset = 0;
		goto l8;
	}
	methodHeader1 = longAt(oop + 4);
	lastFieldOffset = (((((unsigned) methodHeader1) >> 10) & 255) * 4) + 4;
l8:	/* end lastPointerOf: */;
	field = oop + lastFieldOffset;
	action = 1;
	while (!(action == 4)) {
		if (action == 1) {
			/* begin startField */
			child = longAt(field);
			typeBits = child & 3;
			if ((typeBits & 1) == 1) {
				field -= 4;
				action = 1;
				goto l6;
			}
			if (typeBits == 0) {
				longAtput(field, parentField);
				parentField = field;
				action = 2;
				goto l6;
			}
			if (typeBits == 2) {
				if ((child & 126976) != 0) {
					child = child & 4294967292U;
					/* begin rightType: */
					if ((child & 252) == 0) {
						childType = 0;
						goto l5;
					} else {
						if ((child & 126976) == 0) {
							childType = 1;
							goto l5;
						} else {
							childType = 3;
							goto l5;
						}
					}
				l5:	/* end rightType: */;
					longAtput(field, child | childType);
					action = 3;
					goto l6;
				} else {
					child = longAt(field - 4);
					child = child & 4294967292U;
					longAtput(field - 4, parentField);
					parentField = (field - 4) | 1;
					action = 2;
					goto l6;
				}
			}
		l6:	/* end startField */;
		}
		if (action == 2) {
			/* begin startObj */
			oop1 = child;
			if (oop1 < youngStart) {
				field = oop1;
				action = 3;
				goto l2;
			}
			header2 = longAt(oop1);
			if ((header2 & 2147483648U) == 0) {
				header2 = header2 & 4294967292U;
				header2 = (header2 | 2147483648U) | 2;
				longAtput(oop1, header2);
				/* begin lastPointerOf: */
				fmt = (((unsigned) (longAt(oop1))) >> 8) & 15;
				if (fmt < 4) {
					/* begin sizeBitsOfSafe: */
					header4 = longAt(oop1);
					/* begin rightType: */
					if ((header4 & 252) == 0) {
						type2 = 0;
						goto l11;
					} else {
						if ((header4 & 126976) == 0) {
							type2 = 1;
							goto l11;
						} else {
							type2 = 3;
							goto l11;
						}
					}
				l11:	/* end rightType: */;
					if (type2 == 0) {
						sz = (longAt(oop1 - 8)) & 4294967292U;
						goto l12;
					} else {
						sz = header4 & 252;
						goto l12;
					}
				l12:	/* end sizeBitsOfSafe: */;
					lastFieldOffset1 = sz - 4;
					goto l7;
				}
				if (fmt < 12) {
					lastFieldOffset1 = 0;
					goto l7;
				}
				methodHeader = longAt(oop1 + 4);
				lastFieldOffset1 = (((((unsigned) methodHeader) >> 10) & 255) * 4) + 4;
			l7:	/* end lastPointerOf: */;
				field = oop1 + lastFieldOffset1;
				action = 1;
				goto l2;
			} else {
				field = oop1;
				action = 3;
				goto l2;
			}
		l2:	/* end startObj */;
		}
		if (action == 3) {
			/* begin upward */
			if ((parentField & 1) == 1) {
				if (parentField == 3) {
					header1 = (longAt(field)) & 4294967292U;
					/* begin rightType: */
					if ((header1 & 252) == 0) {
						type = 0;
						goto l3;
					} else {
						if ((header1 & 126976) == 0) {
							type = 1;
							goto l3;
						} else {
							type = 3;
							goto l3;
						}
					}
				l3:	/* end rightType: */;
					longAtput(field, header1 + type);
					action = 4;
					goto l1;
				} else {
					child = field;
					field = parentField - 1;
					parentField = longAt(field);
					header1 = longAt(field + 4);
					/* begin rightType: */
					if ((header1 & 252) == 0) {
						type = 0;
						goto l4;
					} else {
						if ((header1 & 126976) == 0) {
							type = 1;
							goto l4;
						} else {
							type = 3;
							goto l4;
						}
					}
				l4:	/* end rightType: */;
					longAtput(field, child + type);
					field += 4;
					header1 = header1 & 4294967292U;
					longAtput(field, header1 + type);
					action = 3;
					goto l1;
				}
			} else {
				child = field;
				field = parentField;
				parentField = longAt(field);
				longAtput(field, child);
				field -= 4;
				action = 1;
				goto l1;
			}
		l1:	/* end upward */;
		}
	}
}

int markAndTraceInterpreterOops(void) {
    int i;
    int oop;

	markAndTrace(specialObjectsOop);
	markAndTrace(activeContext);
	markAndTrace(messageSelector);
	markAndTrace(newMethod);
	for (i = 1; i <= remapBufferCount; i += 1) {
		oop = remapBuffer[i];
		if (!((oop & 1))) {
			markAndTrace(oop);
		}
	}
}

int markPhase(void) {
    int oop;
    int i;
    int i1;
    int oop1;

	freeSmallContexts = 1;
	freeLargeContexts = 1;
	/* begin markAndTraceInterpreterOops */
	markAndTrace(specialObjectsOop);
	markAndTrace(activeContext);
	markAndTrace(messageSelector);
	markAndTrace(newMethod);
	for (i1 = 1; i1 <= remapBufferCount; i1 += 1) {
		oop1 = remapBuffer[i1];
		if (!((oop1 & 1))) {
			markAndTrace(oop1);
		}
	}
	for (i = 1; i <= rootTableCount; i += 1) {
		oop = rootTable[i];
		if (!((oop & 1))) {
			markAndTrace(oop);
		}
	}
}

int mergewith(int sourceWord, int destinationWord) {
    int (*mergeFnwith)(int, int);

	mergeFnwith = ((int (*)(int, int)) (opTable[combinationRule + 1]));
	mergeFnwith;
	return mergeFnwith(sourceWord, destinationWord);
}

int methodClassOf(int methodPointer) {
	return longAt(((((char *) (longAt(((((char *) methodPointer)) + 4) + (((((((unsigned) (longAt(((((char *) methodPointer)) + 4) + (0 << 2)))) >> 10) & 255) - 1) + 1) << 2))))) + 4) + (1 << 2));
}

int netAddressToInt(int oop) {
    int sz;
    int sz1;
    int header;
    int fmt;
    int ccIndex;
    int cl;

	/* begin assertClassOf:is: */
	if ((oop & 1)) {
		successFlag = false;
		goto l2;
	}
	ccIndex = (((unsigned) (longAt(oop))) >> 12) & 31;
	if (ccIndex == 0) {
		cl = (longAt(oop - 4)) & 4294967292U;
	} else {
		cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
	}
	/* begin success: */
	successFlag = (cl == (longAt(((((char *) specialObjectsOop)) + 4) + (26 << 2)))) && successFlag;
l2:	/* end assertClassOf:is: */;
	if (successFlag) {
		/* begin lengthOf: */
		header = longAt(oop);
		if ((header & 3) == 0) {
			sz1 = (longAt(oop - 8)) & 4294967292U;
		} else {
			sz1 = header & 252;
		}
		fmt = (((unsigned) header) >> 8) & 15;
		if (fmt < 8) {
			sz = ((unsigned) (sz1 - 4)) >> 2;
			goto l1;
		} else {
			sz = (sz1 - 4) - (fmt & 3);
			goto l1;
		}
	l1:	/* end lengthOf: */;
		if (!(sz == 4)) {
			return primitiveFail();
		}
	}
	if (successFlag) {
		return (((byteAt(((((char *) oop)) + 4) + 3)) + ((byteAt(((((char *) oop)) + 4) + 2)) << 8)) + ((byteAt(((((char *) oop)) + 4) + 1)) << 16)) + ((byteAt(((((char *) oop)) + 4) + 0)) << 24);
	}
}

int newActiveContext(int aContext) {
    int tmp;

	/* begin storeContextRegisters: */
	longAtput(((((char *) activeContext)) + 4) + (1 << 2), ((((instructionPointer - method) - (4 - 2)) << 1) | 1));
	longAtput(((((char *) activeContext)) + 4) + (2 << 2), (((((((unsigned) ((stackPointer - activeContext) - 4)) >> 2) - 6) + 1) << 1) | 1));
	if (aContext < youngStart) {
		beRootIfOld(aContext);
	}
	activeContext = aContext;
	/* begin fetchContextRegisters: */
	tmp = longAt(((((char *) aContext)) + 4) + (3 << 2));
	if ((tmp & 1)) {
		tmp = longAt(((((char *) aContext)) + 4) + (5 << 2));
		if (tmp < youngStart) {
			beRootIfOld(tmp);
		}
	} else {
		tmp = aContext;
	}
	theHomeContext = tmp;
	receiver = longAt(((((char *) tmp)) + 4) + (5 << 2));
	method = longAt(((((char *) tmp)) + 4) + (3 << 2));
	tmp = ((longAt(((((char *) aContext)) + 4) + (1 << 2))) >> 1);
	instructionPointer = ((method + tmp) + 4) - 2;
	tmp = ((longAt(((((char *) aContext)) + 4) + (2 << 2))) >> 1);
	stackPointer = (aContext + 4) + (((6 + tmp) - 1) * 4);
}

int newObjectHash(void) {
	lastHash = (13849 + (27181 * lastHash)) & 65535;
	return lastHash;
}

int nilObject(void) {
	return nilObj;
}

int objectAfter(int oop) {
    int sz;
    int header;
    int extra;
    int type;
    int extra1;

	if (checkAssertions) {
		if (oop >= endOfMemory) {
			error("no objects after the end of memory");
		}
	}
	if (((longAt(oop)) & 3) == 2) {
		sz = (longAt(oop)) & 536870908;
	} else {
		/* begin sizeBitsOf: */
		header = longAt(oop);
		if ((header & 3) == 0) {
			sz = (longAt(oop - 8)) & 4294967292U;
			goto l1;
		} else {
			sz = header & 252;
			goto l1;
		}
	l1:	/* end sizeBitsOf: */;
	}
	/* begin oopFromChunk: */
	/* begin extraHeaderBytes: */
	type = (longAt(oop + sz)) & 3;
	if (type > 1) {
		extra1 = 0;
	} else {
		if (type == 1) {
			extra1 = 4;
		} else {
			extra1 = 8;
		}
	}
	extra = extra1;
	return (oop + sz) + extra;
}

int objectAfterWhileForwarding(int oop) {
    int sz;
    int fwdBlock;
    int realHeader;
    int header;
    int extra;
    int type;
    int extra1;
    int sz1;
    int header1;
    int extra2;
    int type1;
    int extra11;

	header = longAt(oop);
	if ((header & 2147483648U) == 0) {
		/* begin objectAfter: */
		if (checkAssertions) {
			if (oop >= endOfMemory) {
				error("no objects after the end of memory");
			}
		}
		if (((longAt(oop)) & 3) == 2) {
			sz1 = (longAt(oop)) & 536870908;
		} else {
			/* begin sizeBitsOf: */
			header1 = longAt(oop);
			if ((header1 & 3) == 0) {
				sz1 = (longAt(oop - 8)) & 4294967292U;
				goto l1;
			} else {
				sz1 = header1 & 252;
				goto l1;
			}
		l1:	/* end sizeBitsOf: */;
		}
		/* begin oopFromChunk: */
		/* begin extraHeaderBytes: */
		type1 = (longAt(oop + sz1)) & 3;
		if (type1 > 1) {
			extra11 = 0;
		} else {
			if (type1 == 1) {
				extra11 = 4;
			} else {
				extra11 = 8;
			}
		}
		extra2 = extra11;
		return (oop + sz1) + extra2;
	}
	fwdBlock = header & 2147483644;
	if (checkAssertions) {
		/* begin fwdBlockValidate: */
		if (!((fwdBlock > endOfMemory) && ((fwdBlock <= fwdTableNext) && ((fwdBlock & 3) == 0)))) {
			error("invalid fwd table entry");
		}
	}
	realHeader = longAt(fwdBlock + 4);
	if ((realHeader & 3) == 0) {
		sz = (longAt(oop - 8)) & 268435452;
	} else {
		sz = realHeader & 252;
	}
	/* begin oopFromChunk: */
	/* begin extraHeaderBytes: */
	type = (longAt(oop + sz)) & 3;
	if (type > 1) {
		extra1 = 0;
	} else {
		if (type == 1) {
			extra1 = 4;
		} else {
			extra1 = 8;
		}
	}
	extra = extra1;
	return (oop + sz) + extra;
}

int okArrayClass(int cl) {
	return (cl == (longAt(((((char *) specialObjectsOop)) + 4) + (7 << 2)))) || ((cl == (longAt(((((char *) specialObjectsOop)) + 4) + (4 << 2)))) || (cl == (longAt(((((char *) specialObjectsOop)) + 4) + (26 << 2)))));
}

int okStreamArrayClass(int cl) {
	return (cl == (longAt(((((char *) specialObjectsOop)) + 4) + (6 << 2)))) || ((cl == (longAt(((((char *) specialObjectsOop)) + 4) + (7 << 2)))) || ((cl == (longAt(((((char *) specialObjectsOop)) + 4) + (26 << 2)))) || (cl == (longAt(((((char *) specialObjectsOop)) + 4) + (4 << 2))))));
}

int okayActiveProcessStack(void) {
    int cntxt;

	cntxt = activeContext;
	while (!(cntxt == nilObj)) {
		okayFields(cntxt);
		cntxt = longAt(((((char *) cntxt)) + 4) + (0 << 2));
	}
}

int okayFields(int oop) {
    int i;
    int fieldOop;

	if ((oop == null) || (oop == 0)) {
		return true;
	}
	if ((oop & 1)) {
		return true;
	}
	okayOop(oop);
	oopHasOkayClass(oop);
	if (!(((((unsigned) (longAt(oop))) >> 8) & 15) <= 4)) {
		return true;
	}
	i = (lengthOf(oop)) - 1;
	while (i >= 0) {
		fieldOop = longAt(((((char *) oop)) + 4) + (i << 2));
		if (!((fieldOop & 1))) {
			okayOop(fieldOop);
			oopHasOkayClass(fieldOop);
		}
		i -= 1;
	}
}

int okayInterpreterObjects(void) {
    int i;
    int oop;
    int oopOrZero;
    int cntxt;

	okayFields(nilObj);
	okayFields(falseObj);
	okayFields(trueObj);
	okayFields(specialObjectsOop);
	okayFields(activeContext);
	okayFields(method);
	okayFields(receiver);
	okayFields(theHomeContext);
	okayFields(messageSelector);
	okayFields(newMethod);
	for (i = 1; i <= 512; i += 1) {
		oopOrZero = methodCache[i];
		if (!(oopOrZero == 0)) {
			okayFields(methodCache[i]);
			okayFields(methodCache[i + 512]);
			okayFields(methodCache[i + (2 * 512)]);
		}
	}
	for (i = 1; i <= remapBufferCount; i += 1) {
		oop = remapBuffer[i];
		if (!((oop & 1))) {
			okayFields(oop);
		}
	}
	/* begin okayActiveProcessStack */
	cntxt = activeContext;
	while (!(cntxt == nilObj)) {
		okayFields(cntxt);
		cntxt = longAt(((((char *) cntxt)) + 4) + (0 << 2));
	}
}

int okayOop(int oop) {
    int sz;
    int type;
    int fmt;
    int header;

	if ((oop & 1)) {
		return true;
	}
	if (!((0 < oop) && (oop < endOfMemory))) {
		error("oop is not a valid address");
	}
	if (!((oop % 4) == 0)) {
		error("oop is not a word-aligned address");
	}
	/* begin sizeBitsOf: */
	header = longAt(oop);
	if ((header & 3) == 0) {
		sz = (longAt(oop - 8)) & 4294967292U;
		goto l1;
	} else {
		sz = header & 252;
		goto l1;
	}
l1:	/* end sizeBitsOf: */;
	if (!((oop + sz) < endOfMemory)) {
		error("oop size would make it extend beyond the end of memory");
	}
	type = (longAt(oop)) & 3;
	if (type == 2) {
		error("oop is a free chunk, not an object");
	}
	if (type == 3) {
		if (((((unsigned) (longAt(oop))) >> 12) & 31) == 0) {
			error("cannot have zero compact class field in a short header");
		}
	}
	if (type == 1) {
		if (!((oop >= 4) && (((longAt(oop - 4)) & 3) == type))) {
			error("class header word has wrong type");
		}
	}
	if (type == 0) {
		if (!((oop >= 8) && ((((longAt(oop - 8)) & 3) == type) && (((longAt(oop - 4)) & 3) == type)))) {
			error("class header word has wrong type");
		}
	}
	fmt = (((unsigned) (longAt(oop))) >> 8) & 15;
	if (((fmt == 4) || (fmt == 5)) || (fmt == 7)) {
		error("oop has an unknown format type");
	}
	if (!(((longAt(oop)) & 536870912) == 0)) {
		error("unused header bit 30 is set; should be zero");
	}
	if ((((longAt(oop)) & 1073741824) == 1) && (oop >= youngStart)) {
		error("root bit is set in a young object");
	}
	return true;
}

int oopFromChunk(int chunk) {
    int extra;
    int type;
    int extra1;

	/* begin extraHeaderBytes: */
	type = (longAt(chunk)) & 3;
	if (type > 1) {
		extra1 = 0;
	} else {
		if (type == 1) {
			extra1 = 4;
		} else {
			extra1 = 8;
		}
	}
	extra = extra1;
	return chunk + extra;
}

int oopHasOkayClass(int oop) {
    int behaviorFormatBits;
    int oopClass;
    int formatMask;
    int oopFormatBits;
    int ccIndex;

	okayOop(oop);
	/* begin fetchClassOf: */
	if ((oop & 1)) {
		oopClass = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
		goto l1;
	}
	ccIndex = ((((unsigned) (longAt(oop))) >> 12) & 31) - 1;
	if (ccIndex < 0) {
		oopClass = (longAt(oop - 4)) & 4294967292U;
		goto l1;
	} else {
		oopClass = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
		goto l1;
	}
l1:	/* end fetchClassOf: */;
	if ((oopClass & 1)) {
		error("a SmallInteger is not a valid class or behavior");
	}
	okayOop(oopClass);
	if (!((((((unsigned) (longAt(oopClass))) >> 8) & 15) <= 4) && ((lengthOf(oopClass)) >= 3))) {
		error("a class (behavior) must be a pointers object of size >= 3");
	}
	if (((((unsigned) (longAt(oop))) >> 8) & 15) >= 8) {
		formatMask = 3072;
	} else {
		formatMask = 3840;
	}
	behaviorFormatBits = ((longAt(((((char *) oopClass)) + 4) + (2 << 2))) - 1) & formatMask;
	oopFormatBits = (longAt(oop)) & formatMask;
	if (!(behaviorFormatBits == oopFormatBits)) {
		error("object and its class (behavior) formats differ");
	}
	return true;
}

int partitionedANDtonBitsnPartitions(int word1, int word2, int nBits, int nParts) {
    int mask;
    int i;
    int result;

	mask = (1 << nBits) - 1;
	result = 0;
	for (i = 1; i <= nParts; i += 1) {
		if ((word1 & mask) == mask) {
			result = result | (word2 & mask);
		}
		mask = mask << nBits;
	}
	return result;
}

int partitionedAddtonBitsnPartitions(int word1, int word2, int nBits, int nParts) {
    int mask;
    int sum;
    int i;
    int result;

	mask = (1 << nBits) - 1;
	result = 0;
	for (i = 1; i <= nParts; i += 1) {
		sum = (word1 & mask) + (word2 & mask);
		if (sum <= mask) {
			result = result | sum;
		} else {
			result = result | mask;
		}
		mask = mask << nBits;
	}
	return result;
}

int partitionedMaxwithnBitsnPartitions(int word1, int word2, int nBits, int nParts) {
    int mask;
    int i;
    int result;

	mask = (1 << nBits) - 1;
	result = 0;
	for (i = 1; i <= nParts; i += 1) {
		result = result | ((((word2 & mask) < (word1 & mask)) ? (word1 & mask) : (word2 & mask)));
		mask = mask << nBits;
	}
	return result;
}

int partitionedMinwithnBitsnPartitions(int word1, int word2, int nBits, int nParts) {
    int mask;
    int i;
    int result;

	mask = (1 << nBits) - 1;
	result = 0;
	for (i = 1; i <= nParts; i += 1) {
		result = result | ((((word2 & mask) < (word1 & mask)) ? (word2 & mask) : (word1 & mask)));
		mask = mask << nBits;
	}
	return result;
}

int partitionedSubfromnBitsnPartitions(int word1, int word2, int nBits, int nParts) {
    int mask;
    int i;
    int p1;
    int p2;
    int result;

	mask = (1 << nBits) - 1;
	result = 0;
	for (i = 1; i <= nParts; i += 1) {
		p1 = word1 & mask;
		p2 = word2 & mask;
		if (p1 < p2) {
			result = result | (p2 - p1);
		} else {
			result = result | (p1 - p2);
		}
		mask = mask << nBits;
	}
	return result;
}

int pickSourcePixelsnullMapsrcMaskdestMask(int nPix, int nullMap, int sourcePixMask, int destPixMask) {
	if (sourcePixSize >= 16) {
		return pickSourcePixelsRGBnullMapsrcMaskdestMask(nPix, nullMap, sourcePixMask, destPixMask);
	}
	if (nullMap) {
		return pickSourcePixelsNullMapsrcMaskdestMask(nPix, sourcePixMask, destPixMask);
	}
	return pickSourcePixelssrcMaskdestMask(nPix, sourcePixMask, destPixMask);
}

int pickSourcePixelssrcMaskdestMask(int nPix, int sourcePixMask, int destPixMask) {
    int sourceWord;
    int destWord;
    int sourcePix;
    int destPix;
    int i;

	sourceWord = longAt(sourceIndex);
	destWord = 0;
	for (i = 1; i <= nPix; i += 1) {
		sourcePix = (((unsigned) sourceWord) >> ((32 - sourcePixSize) - srcBitIndex)) & sourcePixMask;
		destPix = (longAt(((((char *) colorMap)) + 4) + (sourcePix << 2))) & destPixMask;
		destWord = (destWord << destPixSize) | destPix;
		if ((srcBitIndex += sourcePixSize) > 31) {
			srcBitIndex -= 32;
			sourceIndex += 4;
			sourceWord = longAt(sourceIndex);
		}
	}
	return destWord;
}

int pickSourcePixelsNullMapsrcMaskdestMask(int nPix, int sourcePixMask, int destPixMask) {
    int sourceWord;
    int destWord;
    int sourcePix;
    int i;

	sourceWord = longAt(sourceIndex);
	destWord = 0;
	for (i = 1; i <= nPix; i += 1) {
		sourcePix = (((unsigned) sourceWord) >> ((32 - sourcePixSize) - srcBitIndex)) & sourcePixMask;
		destWord = (destWord << destPixSize) | (sourcePix & destPixMask);
		if ((srcBitIndex += sourcePixSize) > 31) {
			srcBitIndex -= 32;
			sourceIndex += 4;
			sourceWord = longAt(sourceIndex);
		}
	}
	return destWord;
}

int pickSourcePixelsRGBnullMapsrcMaskdestMask(int nPix, int nullMap, int sourcePixMask, int destPixMask) {
    int sourceWord;
    int destWord;
    int sourcePix;
    int destPix;
    int i;
    int mask;
    int srcPix;
    int destPix1;
    int d;
    int mask3;
    int srcPix1;
    int destPix2;
    int d1;
    int mask4;
    int srcPix2;
    int destPix3;
    int d2;
    int mask5;
    int srcPix3;
    int destPix4;
    int d3;

	sourceWord = longAt(sourceIndex);
	destWord = 0;
	for (i = 1; i <= nPix; i += 1) {
		sourcePix = (((unsigned) sourceWord) >> ((32 - sourcePixSize) - srcBitIndex)) & sourcePixMask;
		if (nullMap) {
			if (sourcePixSize == 16) {
				/* begin rgbMap:from:to: */
				if ((d = 8 - 5) > 0) {
					mask = (1 << 5) - 1;
					srcPix = sourcePix << d;
					mask = mask << d;
					destPix1 = srcPix & mask;
					mask = mask << 8;
					srcPix = srcPix << d;
					destPix = (destPix1 + (srcPix & mask)) + ((srcPix << d) & (mask << 8));
					goto l1;
				} else {
					if (d == 0) {
						destPix = sourcePix;
						goto l1;
					}
					if (sourcePix == 0) {
						destPix = sourcePix;
						goto l1;
					}
					d = 5 - 8;
					mask = (1 << 8) - 1;
					srcPix = ((unsigned) sourcePix) >> d;
					destPix1 = srcPix & mask;
					mask = mask << 8;
					srcPix = ((unsigned) srcPix) >> d;
					destPix1 = (destPix1 + (srcPix & mask)) + ((((unsigned) srcPix) >> d) & (mask << 8));
					if (destPix1 == 0) {
						destPix = 1;
						goto l1;
					}
					destPix = destPix1;
					goto l1;
				}
			l1:	/* end rgbMap:from:to: */;
			} else {
				/* begin rgbMap:from:to: */
				if ((d1 = 5 - 8) > 0) {
					mask3 = (1 << 8) - 1;
					srcPix1 = sourcePix << d1;
					mask3 = mask3 << d1;
					destPix2 = srcPix1 & mask3;
					mask3 = mask3 << 5;
					srcPix1 = srcPix1 << d1;
					destPix = (destPix2 + (srcPix1 & mask3)) + ((srcPix1 << d1) & (mask3 << 5));
					goto l2;
				} else {
					if (d1 == 0) {
						destPix = sourcePix;
						goto l2;
					}
					if (sourcePix == 0) {
						destPix = sourcePix;
						goto l2;
					}
					d1 = 8 - 5;
					mask3 = (1 << 5) - 1;
					srcPix1 = ((unsigned) sourcePix) >> d1;
					destPix2 = srcPix1 & mask3;
					mask3 = mask3 << 5;
					srcPix1 = ((unsigned) srcPix1) >> d1;
					destPix2 = (destPix2 + (srcPix1 & mask3)) + ((((unsigned) srcPix1) >> d1) & (mask3 << 5));
					if (destPix2 == 0) {
						destPix = 1;
						goto l2;
					}
					destPix = destPix2;
					goto l2;
				}
			l2:	/* end rgbMap:from:to: */;
			}
		} else {
			if (sourcePixSize == 16) {
				/* begin rgbMap:from:to: */
				if ((d2 = cmBitsPerColor - 5) > 0) {
					mask4 = (1 << 5) - 1;
					srcPix2 = sourcePix << d2;
					mask4 = mask4 << d2;
					destPix3 = srcPix2 & mask4;
					mask4 = mask4 << cmBitsPerColor;
					srcPix2 = srcPix2 << d2;
					sourcePix = (destPix3 + (srcPix2 & mask4)) + ((srcPix2 << d2) & (mask4 << cmBitsPerColor));
					goto l3;
				} else {
					if (d2 == 0) {
						sourcePix = sourcePix;
						goto l3;
					}
					if (sourcePix == 0) {
						sourcePix = sourcePix;
						goto l3;
					}
					d2 = 5 - cmBitsPerColor;
					mask4 = (1 << cmBitsPerColor) - 1;
					srcPix2 = ((unsigned) sourcePix) >> d2;
					destPix3 = srcPix2 & mask4;
					mask4 = mask4 << cmBitsPerColor;
					srcPix2 = ((unsigned) srcPix2) >> d2;
					destPix3 = (destPix3 + (srcPix2 & mask4)) + ((((unsigned) srcPix2) >> d2) & (mask4 << cmBitsPerColor));
					if (destPix3 == 0) {
						sourcePix = 1;
						goto l3;
					}
					sourcePix = destPix3;
					goto l3;
				}
			l3:	/* end rgbMap:from:to: */;
			} else {
				/* begin rgbMap:from:to: */
				if ((d3 = cmBitsPerColor - 8) > 0) {
					mask5 = (1 << 8) - 1;
					srcPix3 = sourcePix << d3;
					mask5 = mask5 << d3;
					destPix4 = srcPix3 & mask5;
					mask5 = mask5 << cmBitsPerColor;
					srcPix3 = srcPix3 << d3;
					sourcePix = (destPix4 + (srcPix3 & mask5)) + ((srcPix3 << d3) & (mask5 << cmBitsPerColor));
					goto l4;
				} else {
					if (d3 == 0) {
						sourcePix = sourcePix;
						goto l4;
					}
					if (sourcePix == 0) {
						sourcePix = sourcePix;
						goto l4;
					}
					d3 = 8 - cmBitsPerColor;
					mask5 = (1 << cmBitsPerColor) - 1;
					srcPix3 = ((unsigned) sourcePix) >> d3;
					destPix4 = srcPix3 & mask5;
					mask5 = mask5 << cmBitsPerColor;
					srcPix3 = ((unsigned) srcPix3) >> d3;
					destPix4 = (destPix4 + (srcPix3 & mask5)) + ((((unsigned) srcPix3) >> d3) & (mask5 << cmBitsPerColor));
					if (destPix4 == 0) {
						sourcePix = 1;
						goto l4;
					}
					sourcePix = destPix4;
					goto l4;
				}
			l4:	/* end rgbMap:from:to: */;
			}
			destPix = (longAt(((((char *) colorMap)) + 4) + (sourcePix << 2))) & destPixMask;
		}
		destWord = (destWord << destPixSize) | destPix;
		if ((srcBitIndex += sourcePixSize) > 31) {
			srcBitIndex -= 32;
			sourceIndex += 4;
			sourceWord = longAt(sourceIndex);
		}
	}
	return destWord;
}

int pixMaskwith(int sourceWord, int destinationWord) {
    int mask;
    int i;
    int result;

	/* begin partitionedAND:to:nBits:nPartitions: */
	mask = (1 << destPixSize) - 1;
	result = 0;
	for (i = 1; i <= pixPerWord; i += 1) {
		if (((~sourceWord) & mask) == mask) {
			result = result | (destinationWord & mask);
		}
		mask = mask << destPixSize;
	}
	return result;
}

int pixPaintwith(int sourceWord, int destinationWord) {
	if (sourceWord == 0) {
		return destinationWord;
	}
	return sourceWord | (partitionedANDtonBitsnPartitions(~sourceWord, destinationWord, destPixSize, pixPerWord));
}

int pop(int nItems) {
	stackPointer -= nItems * 4;
}

int popthenPush(int nItems, int oop) {
    int sp;

	longAtput(sp = stackPointer - ((nItems - 1) * 4), oop);
	stackPointer = sp;
}

double popFloat(void) {
    int top;
    double result;
    int top1;
    int ccIndex;
    int cl;

	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	top = top1;
	/* begin assertClassOf:is: */
	if ((top & 1)) {
		successFlag = false;
		goto l1;
	}
	ccIndex = (((unsigned) (longAt(top))) >> 12) & 31;
	if (ccIndex == 0) {
		cl = (longAt(top - 4)) & 4294967292U;
	} else {
		cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
	}
	/* begin success: */
	successFlag = (cl == (longAt(((((char *) specialObjectsOop)) + 4) + (9 << 2)))) && successFlag;
l1:	/* end assertClassOf:is: */;
	if (successFlag) {
		fetchFloatAtinto(top + 4, result);
	}
	return result;
}

int popInteger(void) {
    int integerPointer;
    int top;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top;
	if ((integerPointer & 1)) {
		return (integerPointer >> 1);
	} else {
		successFlag = false;
		return 1;
	}
}

int popPos32BitInteger(void) {
    int top;
    int top1;

	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	top = top1;
	return positive32BitValueOf(top);
}

int popRemappableOop(void) {
    int oop;

	oop = remapBuffer[remapBufferCount];
	remapBufferCount -= 1;
	return oop;
}

int popStack(void) {
    int top;

	top = longAt(stackPointer);
	stackPointer -= 4;
	return top;
}

int positive32BitIntegerFor(int integerValue) {
    int newLargeInteger;

	if ((integerValue >= 0) && ((integerValue ^ (integerValue << 1)) >= 0)) {
		return ((integerValue << 1) | 1);
	}
	newLargeInteger = instantiateSmallClasssizeInBytesfill(longAt(((((char *) specialObjectsOop)) + 4) + (13 << 2)), 8, 0);
	byteAtput(((((char *) newLargeInteger)) + 4) + 3, (((unsigned) integerValue) >> 24) & 255);
	byteAtput(((((char *) newLargeInteger)) + 4) + 2, (((unsigned) integerValue) >> 16) & 255);
	byteAtput(((((char *) newLargeInteger)) + 4) + 1, (((unsigned) integerValue) >> 8) & 255);
	byteAtput(((((char *) newLargeInteger)) + 4) + 0, integerValue & 255);
	return newLargeInteger;
}

int positive32BitValueOf(int oop) {
    int sz;
    int value;
    int sz1;
    int header;
    int fmt;
    int ccIndex;
    int cl;

	if ((oop & 1)) {
		value = (oop >> 1);
		if (value < 0) {
			return primitiveFail();
		}
		return value;
	}
	/* begin assertClassOf:is: */
	if ((oop & 1)) {
		successFlag = false;
		goto l2;
	}
	ccIndex = (((unsigned) (longAt(oop))) >> 12) & 31;
	if (ccIndex == 0) {
		cl = (longAt(oop - 4)) & 4294967292U;
	} else {
		cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
	}
	/* begin success: */
	successFlag = (cl == (longAt(((((char *) specialObjectsOop)) + 4) + (13 << 2)))) && successFlag;
l2:	/* end assertClassOf:is: */;
	if (successFlag) {
		/* begin lengthOf: */
		header = longAt(oop);
		if ((header & 3) == 0) {
			sz1 = (longAt(oop - 8)) & 4294967292U;
		} else {
			sz1 = header & 252;
		}
		fmt = (((unsigned) header) >> 8) & 15;
		if (fmt < 8) {
			sz = ((unsigned) (sz1 - 4)) >> 2;
			goto l1;
		} else {
			sz = (sz1 - 4) - (fmt & 3);
			goto l1;
		}
	l1:	/* end lengthOf: */;
		if (!(sz == 4)) {
			return primitiveFail();
		}
	}
	if (successFlag) {
		return (((byteAt(((((char *) oop)) + 4) + 0)) + ((byteAt(((((char *) oop)) + 4) + 1)) << 8)) + ((byteAt(((((char *) oop)) + 4) + 2)) << 16)) + ((byteAt(((((char *) oop)) + 4) + 3)) << 24);
	}
}

int possibleRootStoreIntovalue(int oop, int valueObj) {
    int header;

	if ((valueObj >= youngStart) && (!((valueObj & 1)))) {
		header = longAt(oop);
		if ((header & 1073741824) == 0) {
			if (rootTableCount < 1000) {
				rootTableCount += 1;
				rootTable[rootTableCount] = oop;
				longAtput(oop, header | 1073741824);
			}
		}
	}
}

int postGCAction(void) {
	if (activeContext < youngStart) {
		beRootIfOld(activeContext);
	}
	if (theHomeContext < youngStart) {
		beRootIfOld(theHomeContext);
	}
}

int preGCAction(int fullGCFlag) {
}

int prepareForwardingTableForBecomingwith(int array1, int array2) {
    int entriesAvailable;
    int fwdBlock;
    int fieldOffset;
    int oop1;
    int oop2;
    int entriesNeeded;
    int originalHeader;
    int originalHeaderType;
    int originalHeader1;
    int originalHeaderType1;
    int methodHeader;
    int sz;
    int fmt;
    int header;
    int type;

	entriesNeeded = 2 * (((int) (lastPointerOf(array1)) >> 2));
	entriesAvailable = fwdTableInit();
	if (entriesAvailable < entriesNeeded) {
		initializeMemoryFirstFree(freeBlock);
		return false;
	}
	/* begin lastPointerOf: */
	fmt = (((unsigned) (longAt(array1))) >> 8) & 15;
	if (fmt < 4) {
		/* begin sizeBitsOfSafe: */
		header = longAt(array1);
		/* begin rightType: */
		if ((header & 252) == 0) {
			type = 0;
			goto l4;
		} else {
			if ((header & 126976) == 0) {
				type = 1;
				goto l4;
			} else {
				type = 3;
				goto l4;
			}
		}
	l4:	/* end rightType: */;
		if (type == 0) {
			sz = (longAt(array1 - 8)) & 4294967292U;
			goto l5;
		} else {
			sz = header & 252;
			goto l5;
		}
	l5:	/* end sizeBitsOfSafe: */;
		fieldOffset = sz - 4;
		goto l3;
	}
	if (fmt < 12) {
		fieldOffset = 0;
		goto l3;
	}
	methodHeader = longAt(array1 + 4);
	fieldOffset = (((((unsigned) methodHeader) >> 10) & 255) * 4) + 4;
l3:	/* end lastPointerOf: */;
	while (fieldOffset >= 4) {
		oop1 = longAt(array1 + fieldOffset);
		oop2 = longAt(array2 + fieldOffset);
		/* begin fwdBlockGet */
		fwdTableNext += 8;
		if (fwdTableNext <= fwdTableLast) {
			fwdBlock = fwdTableNext;
			goto l1;
		} else {
			fwdBlock = null;
			goto l1;
		}
	l1:	/* end fwdBlockGet */;
		/* begin initForwardBlock:mapping:to: */
		originalHeader = longAt(oop1);
		if (checkAssertions) {
			if (fwdBlock == null) {
				error("ran out of forwarding blocks in become");
			}
			if ((originalHeader & 2147483648U) != 0) {
				error("object already has a forwarding table entry");
			}
		}
		originalHeaderType = originalHeader & 3;
		longAtput(fwdBlock, oop2);
		longAtput(fwdBlock + 4, originalHeader);
		longAtput(oop1, fwdBlock | (2147483648U | originalHeaderType));
		/* begin fwdBlockGet */
		fwdTableNext += 8;
		if (fwdTableNext <= fwdTableLast) {
			fwdBlock = fwdTableNext;
			goto l2;
		} else {
			fwdBlock = null;
			goto l2;
		}
	l2:	/* end fwdBlockGet */;
		/* begin initForwardBlock:mapping:to: */
		originalHeader1 = longAt(oop2);
		if (checkAssertions) {
			if (fwdBlock == null) {
				error("ran out of forwarding blocks in become");
			}
			if ((originalHeader1 & 2147483648U) != 0) {
				error("object already has a forwarding table entry");
			}
		}
		originalHeaderType1 = originalHeader1 & 3;
		longAtput(fwdBlock, oop1);
		longAtput(fwdBlock + 4, originalHeader1);
		longAtput(oop2, fwdBlock | (2147483648U | originalHeaderType1));
		fieldOffset -= 4;
	}
	return true;
}

int primIndex(void) {
	return primitiveIndex;
}

int primitiveAdd(void) {
    int arg;
    int result;
    int rcvr;
    int sp;

	rcvr = longAt(stackPointer - (1 * 4));
	arg = longAt(stackPointer - (0 * 4));
	/* begin pop: */
	stackPointer -= 2 * 4;
	/* begin success: */
	successFlag = (((rcvr & arg) & 1) != 0) && successFlag;
	if (successFlag) {
		result = ((rcvr >> 1)) + ((arg >> 1));
	}
	/* begin checkIntegerResult:from: */
	if (successFlag && ((result ^ (result << 1)) >= 0)) {
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, ((result << 1) | 1));
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
		failSpecialPrim(1);
	}
}

int primitiveArctan(void) {
    double rcvr;

	rcvr = popFloat();
	if (successFlag) {
		pushFloat(atan(rcvr));
	} else {
		/* begin unPop: */
		stackPointer += 1 * 4;
	}
}

int primitiveArrayBecome(void) {
    int arg;
    int rcvr;
    int top;
    int successValue;
    int i;
    int fieldOffset;
    int oop1;
    int oop2;
    int hdr1;
    int hdr2;
    int fwdBlock;
    int fwdHeader;
    int fwdBlock1;
    int fwdHeader1;
    int methodHeader;
    int sz;
    int fmt;
    int header;
    int type;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	arg = top;
	rcvr = longAt(stackPointer);
	/* begin success: */
	/* begin become:with: */
	if (!((fetchClassOf(rcvr)) == (longAt(((((char *) specialObjectsOop)) + 4) + (7 << 2))))) {
		successValue = false;
		goto l4;
	}
	if (!((fetchClassOf(arg)) == (longAt(((((char *) specialObjectsOop)) + 4) + (7 << 2))))) {
		successValue = false;
		goto l4;
	}
	if (!((lastPointerOf(rcvr)) == (lastPointerOf(arg)))) {
		successValue = false;
		goto l4;
	}
	if (!(containOnlyOopsand(rcvr, arg))) {
		successValue = false;
		goto l4;
	}
	if (!(prepareForwardingTableForBecomingwith(rcvr, arg))) {
		successValue = false;
		goto l4;
	}
	if (allYoungand(rcvr, arg)) {
		mapPointersInObjectsFromto(youngStart, endOfMemory);
	} else {
		mapPointersInObjectsFromto(startOfMemory(), endOfMemory);
	}
	/* begin restoreHeadersAfterBecoming:with: */
	/* begin lastPointerOf: */
	fmt = (((unsigned) (longAt(rcvr))) >> 8) & 15;
	if (fmt < 4) {
		/* begin sizeBitsOfSafe: */
		header = longAt(rcvr);
		/* begin rightType: */
		if ((header & 252) == 0) {
			type = 0;
			goto l2;
		} else {
			if ((header & 126976) == 0) {
				type = 1;
				goto l2;
			} else {
				type = 3;
				goto l2;
			}
		}
	l2:	/* end rightType: */;
		if (type == 0) {
			sz = (longAt(rcvr - 8)) & 4294967292U;
			goto l3;
		} else {
			sz = header & 252;
			goto l3;
		}
	l3:	/* end sizeBitsOfSafe: */;
		fieldOffset = sz - 4;
		goto l1;
	}
	if (fmt < 12) {
		fieldOffset = 0;
		goto l1;
	}
	methodHeader = longAt(rcvr + 4);
	fieldOffset = (((((unsigned) methodHeader) >> 10) & 255) * 4) + 4;
l1:	/* end lastPointerOf: */;
	while (fieldOffset >= 4) {
		oop1 = longAt(rcvr + fieldOffset);
		oop2 = longAt(arg + fieldOffset);
		/* begin restoreHeaderOf: */
		fwdHeader = longAt(oop1);
		fwdBlock = fwdHeader & 2147483644;
		if (checkAssertions) {
			if ((fwdHeader & 2147483648U) == 0) {
				error("attempting to restore the header of an object that has no forwarding block");
			}
			/* begin fwdBlockValidate: */
			if (!((fwdBlock > endOfMemory) && ((fwdBlock <= fwdTableNext) && ((fwdBlock & 3) == 0)))) {
				error("invalid fwd table entry");
			}
		}
		longAtput(oop1, longAt(fwdBlock + 4));
		/* begin restoreHeaderOf: */
		fwdHeader1 = longAt(oop2);
		fwdBlock1 = fwdHeader1 & 2147483644;
		if (checkAssertions) {
			if ((fwdHeader1 & 2147483648U) == 0) {
				error("attempting to restore the header of an object that has no forwarding block");
			}
			/* begin fwdBlockValidate: */
			if (!((fwdBlock1 > endOfMemory) && ((fwdBlock1 <= fwdTableNext) && ((fwdBlock1 & 3) == 0)))) {
				error("invalid fwd table entry");
			}
		}
		longAtput(oop2, longAt(fwdBlock1 + 4));
		/* begin exchangeHashBits:with: */
		hdr1 = longAt(oop1);
		hdr2 = longAt(oop2);
		longAtput(oop1, (hdr1 & 3758227455U) | (hdr2 & 536739840));
		longAtput(oop2, (hdr2 & 3758227455U) | (hdr1 & 536739840));
		fieldOffset -= 4;
	}
	initializeMemoryFirstFree(freeBlock);
	successValue = true;
l4:	/* end become:with: */;
	successFlag = successValue && successFlag;
	/* begin flushMethodCache */
	for (i = 1; i <= 2048; i += 1) {
		methodCache[i] = 0;
	}
	mcProbe = 0;
	if (!(successFlag)) {
		/* begin unPop: */
		stackPointer += 1 * 4;
	}
}

int primitiveAsFloat(void) {
    int arg;
    int integerPointer;
    int top;

	/* begin popInteger */
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top;
	if ((integerPointer & 1)) {
		arg = (integerPointer >> 1);
		goto l1;
	} else {
		successFlag = false;
		arg = 1;
		goto l1;
	}
l1:	/* end popInteger */;
	if (successFlag) {
		pushFloat(((double) arg));
	} else {
		/* begin unPop: */
		stackPointer += 1 * 4;
	}
}

int primitiveAsOop(void) {
    int thisReceiver;
    int top;
    int sp;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	thisReceiver = top;
	/* begin success: */
	successFlag = (!((thisReceiver & 1))) && successFlag;
	if (successFlag) {
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, ((((((unsigned) (longAt(thisReceiver))) >> 17) & 4095) << 1) | 1));
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 1 * 4;
	}
}

int primitiveAsyncFileClose(void) {
    AsyncFile *f;

	f = asyncFileValueOf(longAt(stackPointer));
	if (successFlag) {
		asyncFileClose(f);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
	}
}

int primitiveAsyncFileOpen(void) {
    AsyncFile *f;
    int semaIndex;
    int writeFlag;
    int fileName;
    int fmt;
    int fileNameSize;
    int fOop;
    int sp;
    int integerPointer;
    int oop;
    int successValue;
    int sz;
    int header;
    int fmt1;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		semaIndex = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		semaIndex = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	/* begin booleanValueOf: */
	if ((longAt(stackPointer - (1 * 4))) == trueObj) {
		writeFlag = true;
		goto l2;
	}
	if ((longAt(stackPointer - (1 * 4))) == falseObj) {
		writeFlag = false;
		goto l2;
	}
	successFlag = false;
	writeFlag = null;
l2:	/* end booleanValueOf: */;
	/* begin stackObjectValue: */
	oop = longAt(stackPointer - (2 * 4));
	if ((oop & 1)) {
		primitiveFail();
		fileName = null;
		goto l3;
	}
	fileName = oop;
l3:	/* end stackObjectValue: */;
	if (!(successFlag)) {
		return null;
	}
	fmt = (((unsigned) (longAt(fileName))) >> 8) & 15;
	/* begin success: */
	successValue = (fmt >= 8) && (fmt <= 11);
	successFlag = successValue && successFlag;
	/* begin lengthOf: */
	header = longAt(fileName);
	if ((header & 3) == 0) {
		sz = (longAt(fileName - 8)) & 4294967292U;
	} else {
		sz = header & 252;
	}
	fmt1 = (((unsigned) header) >> 8) & 15;
	if (fmt1 < 8) {
		fileNameSize = ((unsigned) (sz - 4)) >> 2;
		goto l4;
	} else {
		fileNameSize = (sz - 4) - (fmt1 & 3);
		goto l4;
	}
l4:	/* end lengthOf: */;
	if (successFlag) {
		fOop = instantiateClassindexableSize(longAt(((((char *) specialObjectsOop)) + 4) + (26 << 2)), sizeof(AsyncFile));
		f = asyncFileValueOf(fOop);
	}
	if (successFlag) {
		asyncFileOpen(f, fileName + 4, fileNameSize, writeFlag, semaIndex);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 4 * 4;
		/* begin push: */
		longAtput(sp = stackPointer + 4, fOop);
		stackPointer = sp;
	}
}

int primitiveAsyncFileReadResult(void) {
    AsyncFile *f;
    int startIndex;
    int buffer;
    int bufferPtr;
    int bufferSize;
    int count;
    int fmt;
    int r;
    int integerPointer;
    int integerPointer1;
    int oop;
    int successValue;
    int successValue1;
    int sp;
    int sz;
    int header;
    int fmt1;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		count = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		count = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (1 * 4));
	if ((integerPointer1 & 1)) {
		startIndex = (integerPointer1 >> 1);
		goto l2;
	} else {
		primitiveFail();
		startIndex = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	/* begin stackObjectValue: */
	oop = longAt(stackPointer - (2 * 4));
	if ((oop & 1)) {
		primitiveFail();
		buffer = null;
		goto l3;
	}
	buffer = oop;
l3:	/* end stackObjectValue: */;
	f = asyncFileValueOf(longAt(stackPointer - (3 * 4)));
	if (!(successFlag)) {
		return null;
	}
	fmt = (((unsigned) (longAt(buffer))) >> 8) & 15;
	/* begin success: */
	successValue = (fmt == 6) || ((fmt >= 8) && (fmt <= 11));
	successFlag = successValue && successFlag;
	/* begin lengthOf: */
	header = longAt(buffer);
	if ((header & 3) == 0) {
		sz = (longAt(buffer - 8)) & 4294967292U;
	} else {
		sz = header & 252;
	}
	fmt1 = (((unsigned) header) >> 8) & 15;
	if (fmt1 < 8) {
		bufferSize = ((unsigned) (sz - 4)) >> 2;
		goto l4;
	} else {
		bufferSize = (sz - 4) - (fmt1 & 3);
		goto l4;
	}
l4:	/* end lengthOf: */;
	if (fmt == 6) {
		count = count * 4;
		startIndex = ((startIndex - 1) * 4) + 1;
		bufferSize = bufferSize * 4;
	}
	/* begin success: */
	successValue1 = (startIndex >= 1) && (((startIndex + count) - 1) <= bufferSize);
	successFlag = successValue1 && successFlag;
	bufferPtr = ((buffer + 4) + startIndex) - 1;
	if (successFlag) {
		r = asyncFileReadResult(f, bufferPtr, count);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 5 * 4;
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, ((r << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveAsyncFileReadStart(void) {
    AsyncFile *f;
    int fPosition;
    int count;
    int integerPointer;
    int integerPointer1;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		count = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		count = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (1 * 4));
	if ((integerPointer1 & 1)) {
		fPosition = (integerPointer1 >> 1);
		goto l2;
	} else {
		primitiveFail();
		fPosition = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	f = asyncFileValueOf(longAt(stackPointer - (2 * 4)));
	if (successFlag) {
		asyncFileReadStart(f, fPosition, count);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 3 * 4;
	}
}

int primitiveAsyncFileWriteResult(void) {
    AsyncFile *f;
    int r;
    int sp;

	f = asyncFileValueOf(longAt(stackPointer));
	if (successFlag) {
		r = asyncFileWriteResult(f);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 2 * 4;
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, ((r << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveAsyncFileWriteStart(void) {
    AsyncFile *f;
    int startIndex;
    int buffer;
    int bufferPtr;
    int bufferSize;
    int count;
    int fPosition;
    int fmt;
    int integerPointer;
    int integerPointer1;
    int oop;
    int integerPointer2;
    int successValue;
    int sz;
    int header;
    int fmt1;
    int successValue1;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		count = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		count = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (1 * 4));
	if ((integerPointer1 & 1)) {
		startIndex = (integerPointer1 >> 1);
		goto l2;
	} else {
		primitiveFail();
		startIndex = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	/* begin stackObjectValue: */
	oop = longAt(stackPointer - (2 * 4));
	if ((oop & 1)) {
		primitiveFail();
		buffer = null;
		goto l3;
	}
	buffer = oop;
l3:	/* end stackObjectValue: */;
	/* begin stackIntegerValue: */
	integerPointer2 = longAt(stackPointer - (3 * 4));
	if ((integerPointer2 & 1)) {
		fPosition = (integerPointer2 >> 1);
		goto l4;
	} else {
		primitiveFail();
		fPosition = 0;
		goto l4;
	}
l4:	/* end stackIntegerValue: */;
	f = asyncFileValueOf(longAt(stackPointer - (4 * 4)));
	if (!(successFlag)) {
		return null;
	}
	fmt = (((unsigned) (longAt(buffer))) >> 8) & 15;
	/* begin success: */
	successValue = (fmt == 6) || ((fmt >= 8) && (fmt <= 11));
	successFlag = successValue && successFlag;
	/* begin lengthOf: */
	header = longAt(buffer);
	if ((header & 3) == 0) {
		sz = (longAt(buffer - 8)) & 4294967292U;
	} else {
		sz = header & 252;
	}
	fmt1 = (((unsigned) header) >> 8) & 15;
	if (fmt1 < 8) {
		bufferSize = ((unsigned) (sz - 4)) >> 2;
		goto l5;
	} else {
		bufferSize = (sz - 4) - (fmt1 & 3);
		goto l5;
	}
l5:	/* end lengthOf: */;
	if (fmt == 6) {
		count = count * 4;
		startIndex = ((startIndex - 1) * 4) + 1;
		bufferSize = bufferSize * 4;
	}
	/* begin success: */
	successValue1 = (startIndex >= 1) && (((startIndex + count) - 1) <= bufferSize);
	successFlag = successValue1 && successFlag;
	bufferPtr = ((buffer + 4) + startIndex) - 1;
	if (successFlag) {
		asyncFileWriteStart(f, fPosition, bufferPtr, count);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 5 * 4;
	}
}

int primitiveAt(void) {
    int index;
    int result;
    int rcvr;
    int sp;

	/* begin commonAt: */
	index = longAt(stackPointer);
	rcvr = longAt(stackPointer - (1 * 4));
	if (((index & 1)) && (!((rcvr & 1)))) {
		index = (index >> 1);
		result = stObjectat(rcvr, index);
		if (false && (successFlag)) {
			result = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (24 << 2))))) + 4) + (((result >> 1)) << 2));
		}
	} else {
		successFlag = false;
	}
	if (successFlag) {
		/* begin pop:thenPush: */
		longAtput(sp = stackPointer - ((2 - 1) * 4), result);
		stackPointer = sp;
	} else {
		if (false) {
			failSpecialPrim(63);
		} else {
			failSpecialPrim(60);
		}
	}
}

int primitiveAtEnd(void) {
    int array;
    int stream;
    int arrayClass;
    int size;
    int index;
    int limit;
    int successValue;
    int sp;
    int sp1;
    int top;
    int ccIndex;
    int hdr;
    int totalLength;
    int fmt;
    int fixedFields;
    int sz;
    int classFormat;
    int class;
    int ccIndex1;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	stream = top;
	successFlag = (((((unsigned) (longAt(stream))) >> 8) & 15) <= 4) && ((lengthOf(stream)) >= (2 + 1));
	if (successFlag) {
		array = longAt(((((char *) stream)) + 4) + (0 << 2));
		index = fetchIntegerofObject(1, stream);
		limit = fetchIntegerofObject(2, stream);
		/* begin fetchClassOf: */
		if ((array & 1)) {
			arrayClass = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
			goto l1;
		}
		ccIndex = ((((unsigned) (longAt(array))) >> 12) & 31) - 1;
		if (ccIndex < 0) {
			arrayClass = (longAt(array - 4)) & 4294967292U;
			goto l1;
		} else {
			arrayClass = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
			goto l1;
		}
	l1:	/* end fetchClassOf: */;
		/* begin success: */
		successValue = (arrayClass == (longAt(((((char *) specialObjectsOop)) + 4) + (6 << 2)))) || ((arrayClass == (longAt(((((char *) specialObjectsOop)) + 4) + (7 << 2)))) || ((arrayClass == (longAt(((((char *) specialObjectsOop)) + 4) + (26 << 2)))) || (arrayClass == (longAt(((((char *) specialObjectsOop)) + 4) + (4 << 2))))));
		successFlag = successValue && successFlag;
		/* begin stSizeOf: */
		hdr = longAt(array);
		fmt = (((unsigned) hdr) >> 8) & 15;
		/* begin lengthOf:baseHeader:format: */
		if ((hdr & 3) == 0) {
			sz = (longAt(array - 8)) & 4294967292U;
		} else {
			sz = hdr & 252;
		}
		if (fmt < 8) {
			totalLength = ((unsigned) (sz - 4)) >> 2;
			goto l4;
		} else {
			totalLength = (sz - 4) - (fmt & 3);
			goto l4;
		}
	l4:	/* end lengthOf:baseHeader:format: */;
		/* begin fixedFieldsOf:format:length: */
		if ((fmt > 3) || (fmt == 2)) {
			fixedFields = 0;
			goto l2;
		}
		if (fmt < 2) {
			fixedFields = totalLength;
			goto l2;
		}
		/* begin fetchClassOf: */
		if ((array & 1)) {
			class = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
			goto l3;
		}
		ccIndex1 = ((((unsigned) (longAt(array))) >> 12) & 31) - 1;
		if (ccIndex1 < 0) {
			class = (longAt(array - 4)) & 4294967292U;
			goto l3;
		} else {
			class = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex1 << 2));
			goto l3;
		}
	l3:	/* end fetchClassOf: */;
		classFormat = (longAt(((((char *) class)) + 4) + (2 << 2))) - 1;
		fixedFields = (((((unsigned) classFormat) >> 11) & 192) + ((((unsigned) classFormat) >> 2) & 63)) - 1;
	l2:	/* end fixedFieldsOf:format:length: */;
		size = totalLength - fixedFields;
	}
	if (successFlag) {
		/* begin pushBool: */
		if ((index >= limit) || (index >= size)) {
			/* begin push: */
			longAtput(sp = stackPointer + 4, trueObj);
			stackPointer = sp;
		} else {
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, falseObj);
			stackPointer = sp1;
		}
	} else {
		/* begin unPop: */
		stackPointer += 1 * 4;
	}
}

int primitiveAtPut(void) {
    int value;
    int valToStore;
    int index;
    int rcvr;
    int sp;

	/* begin commonAtPut: */
	value = valToStore = longAt(stackPointer);
	index = longAt(stackPointer - (1 * 4));
	rcvr = longAt(stackPointer - (2 * 4));
	if (((index & 1)) && (!((rcvr & 1)))) {
		index = (index >> 1);
		if (false) {
			valToStore = asciiOfCharacter(value);
		}
		stObjectatput(rcvr, index, valToStore);
	} else {
		successFlag = false;
	}
	if (successFlag) {
		/* begin pop:thenPush: */
		longAtput(sp = stackPointer - ((3 - 1) * 4), value);
		stackPointer = sp;
	} else {
		if (false) {
			failSpecialPrim(64);
		} else {
			failSpecialPrim(61);
		}
	}
}

int primitiveBeCursor(void) {
    int maskObj;
    int maskBitsIndex;
    int depth;
    int bitsObj;
    int extentX;
    int extentY;
    int cursorObj;
    int offsetObj;
    int offsetX;
    int offsetY;
    int cursorBitsIndex;
    int successValue;
    int successValue1;
    int successValue2;
    int successValue3;
    int successValue4;
    int successValue5;
    int successValue6;
    int successValue7;
    int successValue8;

	if (argumentCount == 0) {
		cursorObj = longAt(stackPointer);
		maskBitsIndex = null;
	}
	if (argumentCount == 1) {
		cursorObj = longAt(stackPointer - (1 * 4));
		maskObj = longAt(stackPointer);
	}
	/* begin success: */
	successFlag = (argumentCount < 2) && successFlag;
	/* begin success: */
	successValue7 = (((((unsigned) (longAt(cursorObj))) >> 8) & 15) <= 4) && ((lengthOf(cursorObj)) >= 5);
	successFlag = successValue7 && successFlag;
	if (successFlag) {
		bitsObj = longAt(((((char *) cursorObj)) + 4) + (0 << 2));
		extentX = fetchIntegerofObject(1, cursorObj);
		extentY = fetchIntegerofObject(2, cursorObj);
		depth = fetchIntegerofObject(3, cursorObj);
		offsetObj = longAt(((((char *) cursorObj)) + 4) + (4 << 2));
	}
	/* begin success: */
	successValue8 = (((((unsigned) (longAt(offsetObj))) >> 8) & 15) <= 4) && ((lengthOf(offsetObj)) >= 2);
	successFlag = successValue8 && successFlag;
	if (successFlag) {
		offsetX = fetchIntegerofObject(0, offsetObj);
		offsetY = fetchIntegerofObject(1, offsetObj);
		/* begin success: */
		successValue = (extentX == 16) && ((extentY == 16) && (depth == 1));
		successFlag = successValue && successFlag;
		/* begin success: */
		successValue1 = (offsetX >= -16) && (offsetX <= 0);
		successFlag = successValue1 && successFlag;
		/* begin success: */
		successValue2 = (offsetY >= -16) && (offsetY <= 0);
		successFlag = successValue2 && successFlag;
		/* begin success: */
		successValue3 = (((((unsigned) (longAt(bitsObj))) >> 8) & 15) == 6) && ((lengthOf(bitsObj)) == 16);
		successFlag = successValue3 && successFlag;
		cursorBitsIndex = bitsObj + 4;
	}
	if (argumentCount == 1) {
		/* begin success: */
		successValue6 = (((((unsigned) (longAt(maskObj))) >> 8) & 15) <= 4) && ((lengthOf(maskObj)) >= 5);
		successFlag = successValue6 && successFlag;
		if (successFlag) {
			bitsObj = longAt(((((char *) maskObj)) + 4) + (0 << 2));
			extentX = fetchIntegerofObject(1, maskObj);
			extentY = fetchIntegerofObject(2, maskObj);
			depth = fetchIntegerofObject(3, maskObj);
		}
		if (successFlag) {
			/* begin success: */
			successValue4 = (extentX == 16) && ((extentY == 16) && (depth == 1));
			successFlag = successValue4 && successFlag;
			/* begin success: */
			successValue5 = (((((unsigned) (longAt(bitsObj))) >> 8) & 15) == 6) && ((lengthOf(bitsObj)) == 16);
			successFlag = successValue5 && successFlag;
			maskBitsIndex = bitsObj + 4;
		}
	}
	if (successFlag) {
		if (argumentCount == 0) {
			ioSetCursor(cursorBitsIndex, offsetX, offsetY);
		} else {
			ioSetCursorWithMask(cursorBitsIndex, maskBitsIndex, offsetX, offsetY);
		}
		/* begin pop: */
		stackPointer -= argumentCount * 4;
	}
}

int primitiveBeDisplay(void) {
    int rcvr;
    int oop;
    int successValue;

	rcvr = longAt(stackPointer);
	/* begin success: */
	successValue = (((((unsigned) (longAt(rcvr))) >> 8) & 15) <= 4) && ((lengthOf(rcvr)) >= 4);
	successFlag = successValue && successFlag;
	if (successFlag) {
		/* begin storePointer:ofObject:withValue: */
		oop = specialObjectsOop;
		if (oop < youngStart) {
			possibleRootStoreIntovalue(oop, rcvr);
		}
		longAtput(((((char *) oop)) + 4) + (14 << 2), rcvr);
	}
}

int primitiveBeep(void) {
	ioBeep();
}

int primitiveBitAnd(void) {
    int integerReceiver;
    int integerArgument;
    int object;
    int sp;
    int top;
    int top1;
    int top2;
    int top11;

	successFlag = true;
	/* begin popPos32BitInteger */
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	top = top1;
	integerArgument = positive32BitValueOf(top);
	/* begin popPos32BitInteger */
	/* begin popStack */
	top11 = longAt(stackPointer);
	stackPointer -= 4;
	top2 = top11;
	integerReceiver = positive32BitValueOf(top2);
	if (successFlag) {
		/* begin push: */
		object = positive32BitIntegerFor(integerReceiver & integerArgument);
		longAtput(sp = stackPointer + 4, object);
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
		failSpecialPrim(14);
	}
}

int primitiveBitOr(void) {
    int integerReceiver;
    int integerArgument;
    int object;
    int sp;
    int top;
    int top1;
    int top2;
    int top11;

	successFlag = true;
	/* begin popPos32BitInteger */
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	top = top1;
	integerArgument = positive32BitValueOf(top);
	/* begin popPos32BitInteger */
	/* begin popStack */
	top11 = longAt(stackPointer);
	stackPointer -= 4;
	top2 = top11;
	integerReceiver = positive32BitValueOf(top2);
	if (successFlag) {
		/* begin push: */
		object = positive32BitIntegerFor(integerReceiver | integerArgument);
		longAtput(sp = stackPointer + 4, object);
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
		failSpecialPrim(15);
	}
}

int primitiveBitShift(void) {
    int shifted;
    int integerReceiver;
    int integerArgument;
    int object;
    int sp;
    int integerPointer;
    int top;
    int top2;
    int top1;

	successFlag = true;
	/* begin popInteger */
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top;
	if ((integerPointer & 1)) {
		integerArgument = (integerPointer >> 1);
		goto l1;
	} else {
		successFlag = false;
		integerArgument = 1;
		goto l1;
	}
l1:	/* end popInteger */;
	/* begin popPos32BitInteger */
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	top2 = top1;
	integerReceiver = positive32BitValueOf(top2);
	if (successFlag) {
		if (integerArgument >= 0) {
			/* begin success: */
			successFlag = (integerArgument <= 31) && successFlag;
			shifted = integerReceiver << integerArgument;
			/* begin success: */
			successFlag = ((((unsigned) shifted) >> integerArgument) == integerReceiver) && successFlag;
		} else {
			/* begin success: */
			successFlag = (integerArgument >= -31) && successFlag;
			shifted = ((integerArgument < 0) ? ((unsigned) integerReceiver >> -integerArgument) : ((unsigned) integerReceiver << integerArgument));
		}
	}
	if (successFlag) {
		/* begin push: */
		object = positive32BitIntegerFor(shifted);
		longAtput(sp = stackPointer + 4, object);
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
		failSpecialPrim(17);
	}
}

int primitiveBitXor(void) {
    int integerReceiver;
    int integerArgument;
    int object;
    int sp;
    int top;
    int top1;
    int top2;
    int top11;

	/* begin popPos32BitInteger */
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	top = top1;
	integerArgument = positive32BitValueOf(top);
	/* begin popPos32BitInteger */
	/* begin popStack */
	top11 = longAt(stackPointer);
	stackPointer -= 4;
	top2 = top11;
	integerReceiver = positive32BitValueOf(top2);
	if (successFlag) {
		/* begin push: */
		object = positive32BitIntegerFor(integerReceiver ^ integerArgument);
		longAtput(sp = stackPointer + 4, object);
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
	}
}

int primitiveBlockCopy(void) {
    int methodContext;
    int newContext;
    int initialIP;
    int context;
    int contextSize;
    int header;
    int oop;
    int sp;

	context = longAt(stackPointer - (1 * 4));
	if (((longAt(((((char *) context)) + 4) + (3 << 2))) & 1)) {
		methodContext = longAt(((((char *) context)) + 4) + (5 << 2));
	} else {
		methodContext = context;
	}
	/* begin sizeBitsOf: */
	header = longAt(methodContext);
	if ((header & 3) == 0) {
		contextSize = (longAt(methodContext - 8)) & 4294967292U;
		goto l1;
	} else {
		contextSize = header & 252;
		goto l1;
	}
l1:	/* end sizeBitsOf: */;
	context = null;
	/* begin pushRemappableOop: */
	remapBuffer[remapBufferCount += 1] = methodContext;
	newContext = instantiateSmallClasssizeInBytesfill(longAt(((((char *) specialObjectsOop)) + 4) + (11 << 2)), contextSize, nilObj);
	/* begin popRemappableOop */
	oop = remapBuffer[remapBufferCount];
	remapBufferCount -= 1;
	methodContext = oop;
	initialIP = (((instructionPointer - method) << 1) | 1);
	longAtput(((((char *) newContext)) + 4) + (4 << 2), initialIP);
	longAtput(((((char *) newContext)) + 4) + (1 << 2), initialIP);
	/* begin storeStackPointerValue:inContext: */
	longAtput(((((char *) newContext)) + 4) + (2 << 2), ((0 << 1) | 1));
	longAtput(((((char *) newContext)) + 4) + (3 << 2), longAt(stackPointer - (0 * 4)));
	longAtput(((((char *) newContext)) + 4) + (5 << 2), methodContext);
	/* begin pop: */
	stackPointer -= 2 * 4;
	/* begin push: */
	longAtput(sp = stackPointer + 4, newContext);
	stackPointer = sp;
}

int primitiveBytesLeft(void) {
    int sp;

	/* begin pop: */
	stackPointer -= 1 * 4;
	/* begin pushInteger: */
	/* begin push: */
	longAtput(sp = stackPointer + 4, ((((longAt(freeBlock)) & 536870908) << 1) | 1));
	stackPointer = sp;
}

int primitiveClass(void) {
    int instance;
    int top;
    int object;
    int sp;
    int ccIndex;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	instance = top;
	/* begin push: */
	/* begin fetchClassOf: */
	if ((instance & 1)) {
		object = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
		goto l1;
	}
	ccIndex = ((((unsigned) (longAt(instance))) >> 12) & 31) - 1;
	if (ccIndex < 0) {
		object = (longAt(instance - 4)) & 4294967292U;
		goto l1;
	} else {
		object = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
		goto l1;
	}
l1:	/* end fetchClassOf: */;
	longAtput(sp = stackPointer + 4, object);
	stackPointer = sp;
}

int primitiveClipboardText(void) {
    int sz;
    int s;
    int sp;
    int ccIndex;
    int cl;
    int hdr;
    int totalLength;
    int fmt;
    int fixedFields;
    int sz1;
    int classFormat;
    int class;
    int ccIndex1;

	if (argumentCount == 1) {
		s = longAt(stackPointer);
		/* begin assertClassOf:is: */
		if ((s & 1)) {
			successFlag = false;
			goto l1;
		}
		ccIndex = (((unsigned) (longAt(s))) >> 12) & 31;
		if (ccIndex == 0) {
			cl = (longAt(s - 4)) & 4294967292U;
		} else {
			cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl == (longAt(((((char *) specialObjectsOop)) + 4) + (6 << 2)))) && successFlag;
	l1:	/* end assertClassOf:is: */;
		if (successFlag) {
			/* begin stSizeOf: */
			hdr = longAt(s);
			fmt = (((unsigned) hdr) >> 8) & 15;
			/* begin lengthOf:baseHeader:format: */
			if ((hdr & 3) == 0) {
				sz1 = (longAt(s - 8)) & 4294967292U;
			} else {
				sz1 = hdr & 252;
			}
			if (fmt < 8) {
				totalLength = ((unsigned) (sz1 - 4)) >> 2;
				goto l4;
			} else {
				totalLength = (sz1 - 4) - (fmt & 3);
				goto l4;
			}
		l4:	/* end lengthOf:baseHeader:format: */;
			/* begin fixedFieldsOf:format:length: */
			if ((fmt > 3) || (fmt == 2)) {
				fixedFields = 0;
				goto l2;
			}
			if (fmt < 2) {
				fixedFields = totalLength;
				goto l2;
			}
			/* begin fetchClassOf: */
			if ((s & 1)) {
				class = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
				goto l3;
			}
			ccIndex1 = ((((unsigned) (longAt(s))) >> 12) & 31) - 1;
			if (ccIndex1 < 0) {
				class = (longAt(s - 4)) & 4294967292U;
				goto l3;
			} else {
				class = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex1 << 2));
				goto l3;
			}
		l3:	/* end fetchClassOf: */;
			classFormat = (longAt(((((char *) class)) + 4) + (2 << 2))) - 1;
			fixedFields = (((((unsigned) classFormat) >> 11) & 192) + ((((unsigned) classFormat) >> 2) & 63)) - 1;
		l2:	/* end fixedFieldsOf:format:length: */;
			sz = totalLength - fixedFields;
			clipboardWriteFromAt(sz, s + 4, 0);
			/* begin pop: */
			stackPointer -= 1 * 4;
		}
	} else {
		sz = clipboardSize();
		s = instantiateClassindexableSize(longAt(((((char *) specialObjectsOop)) + 4) + (6 << 2)), sz);
		clipboardReadIntoAt(sz, s + 4, 0);
		/* begin pop: */
		stackPointer -= 1 * 4;
		/* begin push: */
		longAtput(sp = stackPointer + 4, s);
		stackPointer = sp;
	}
}

int primitiveClone(void) {
    int newCopy;
    int sp;

	newCopy = clone(longAt(stackPointer));
	/* begin pop:thenPush: */
	longAtput(sp = stackPointer - ((1 - 1) * 4), newCopy);
	stackPointer = sp;
}

int primitiveConstantFill(void) {
    int i;
    int end;
    int rcvrIsBytes;
    int fillValue;
    int rcvr;
    int successValue;
    int successValue1;
    int fmt;

	fillValue = positive32BitValueOf(longAt(stackPointer));
	rcvr = longAt(stackPointer - (1 * 4));
	/* begin success: */
	/* begin isWordsOrBytes: */
	fmt = (((unsigned) (longAt(rcvr))) >> 8) & 15;
	successValue1 = (fmt == 6) || ((fmt >= 8) && (fmt <= 11));
	successFlag = successValue1 && successFlag;
	rcvrIsBytes = ((((unsigned) (longAt(rcvr))) >> 8) & 15) >= 8;
	if (rcvrIsBytes) {
		/* begin success: */
		successValue = (fillValue >= 0) && (fillValue <= 255);
		successFlag = successValue && successFlag;
	}
	if (successFlag) {
		end = rcvr + (sizeBitsOf(rcvr));
		i = rcvr + 4;
		if (rcvrIsBytes) {
			while (i < end) {
				byteAtput(i, fillValue);
				i += 1;
			}
		} else {
			while (i < end) {
				longAtput(i, fillValue);
				i += 4;
			}
		}
		/* begin pop: */
		stackPointer -= 1 * 4;
	}
}

int primitiveCopyBits(void) {
    int rcvr;
    int successValue;

	rcvr = longAt(stackPointer - (argumentCount * 4));
	/* begin success: */
	successValue = loadBitBltFrom(rcvr);
	successFlag = successValue && successFlag;
	if (successFlag) {
		copyBits();
		showDisplayBits();
	}
}

int primitiveDeferDisplayUpdates(void) {
    int flag;

	flag = longAt(stackPointer);
	if (flag == trueObj) {
		deferDisplayUpdates = true;
	} else {
		if (flag == falseObj) {
			deferDisplayUpdates = false;
		} else {
			primitiveFail();
		}
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
	}
}

int primitiveDirectoryCreate(void) {
    int dirName;
    int dirNameIndex;
    int dirNameSize;
    int sz;
    int header;
    int fmt;

	dirName = longAt(stackPointer);
	/* begin success: */
	successFlag = (((((unsigned) (longAt(dirName))) >> 8) & 15) >= 8) && successFlag;
	if (successFlag) {
		dirNameIndex = dirName + 4;
		/* begin lengthOf: */
		header = longAt(dirName);
		if ((header & 3) == 0) {
			sz = (longAt(dirName - 8)) & 4294967292U;
		} else {
			sz = header & 252;
		}
		fmt = (((unsigned) header) >> 8) & 15;
		if (fmt < 8) {
			dirNameSize = ((unsigned) (sz - 4)) >> 2;
			goto l1;
		} else {
			dirNameSize = (sz - 4) - (fmt & 3);
			goto l1;
		}
	l1:	/* end lengthOf: */;
	}
	if (successFlag) {
		/* begin success: */
		successFlag = (dir_Create((char *) dirNameIndex, dirNameSize)) && successFlag;
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
	}
}

int primitiveDirectoryDelimitor(void) {
    int ascii;
    int sp;
    int successValue;

	ascii = asciiDirectoryDelimiter();
	/* begin success: */
	successValue = (ascii >= 0) && (ascii <= 255);
	successFlag = successValue && successFlag;
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
		/* begin push: */
		longAtput(sp = stackPointer + 4, longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (24 << 2))))) + 4) + (ascii << 2)));
		stackPointer = sp;
	}
}

int primitiveDirectoryLookup(void) {
    int dirFlag;
    int pathName;
    int pathNameIndex;
    int pathNameSize;
    int status;
    int modifiedDate;
    char entryName[256];
    int entryNameSize;
    int index;
    int createDate;
    int fileSize;
    int sz;
    int header;
    int fmt;
    int sp;
    int object;
    int sp1;
    int integerPointer;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		index = (integerPointer >> 1);
		goto l2;
	} else {
		primitiveFail();
		index = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	pathName = longAt(stackPointer - (1 * 4));
	/* begin success: */
	successFlag = (((((unsigned) (longAt(pathName))) >> 8) & 15) >= 8) && successFlag;
	if (successFlag) {
		pathNameIndex = pathName + 4;
		/* begin lengthOf: */
		header = longAt(pathName);
		if ((header & 3) == 0) {
			sz = (longAt(pathName - 8)) & 4294967292U;
		} else {
			sz = header & 252;
		}
		fmt = (((unsigned) header) >> 8) & 15;
		if (fmt < 8) {
			pathNameSize = ((unsigned) (sz - 4)) >> 2;
			goto l1;
		} else {
			pathNameSize = (sz - 4) - (fmt & 3);
			goto l1;
		}
	l1:	/* end lengthOf: */;
	}
	if (successFlag) {
		status = dir_Lookup(
				(char *) pathNameIndex, pathNameSize, index,
				entryName, &entryNameSize, &createDate, &modifiedDate,
				&dirFlag, &fileSize);
		if (status == 1) {
			/* begin pop: */
			stackPointer -= 3 * 4;
			/* begin push: */
			longAtput(sp = stackPointer + 4, nilObj);
			stackPointer = sp;
			return null;
		}
		if (status == 2) {
			return primitiveFail();
		}
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 3 * 4;
		/* begin push: */
		object = makeDirEntryNamesizecreateDatemodDateisDirfileSize(entryName, entryNameSize, createDate, modifiedDate, dirFlag, fileSize);
		longAtput(sp1 = stackPointer + 4, object);
		stackPointer = sp1;
	}
}

int primitiveDirectorySetMacTypeAndCreator(void) {
    int typeStringIndex;
    int typeString;
    int fileName;
    int creatorString;
    int creatorStringIndex;
    int fileNameIndex;
    int fileNameSize;
    int sz;
    int header;
    int fmt;
    int successValue;
    int successValue1;

	creatorString = longAt(stackPointer);
	typeString = longAt(stackPointer - (1 * 4));
	fileName = longAt(stackPointer - (2 * 4));
	/* begin success: */
	successValue = (((((unsigned) (longAt(creatorString))) >> 8) & 15) >= 8) && ((lengthOf(creatorString)) == 4);
	successFlag = successValue && successFlag;
	/* begin success: */
	successValue1 = (((((unsigned) (longAt(typeString))) >> 8) & 15) >= 8) && ((lengthOf(typeString)) == 4);
	successFlag = successValue1 && successFlag;
	/* begin success: */
	successFlag = (((((unsigned) (longAt(fileName))) >> 8) & 15) >= 8) && successFlag;
	if (successFlag) {
		creatorStringIndex = creatorString + 4;
		typeStringIndex = typeString + 4;
		fileNameIndex = fileName + 4;
		/* begin lengthOf: */
		header = longAt(fileName);
		if ((header & 3) == 0) {
			sz = (longAt(fileName - 8)) & 4294967292U;
		} else {
			sz = header & 252;
		}
		fmt = (((unsigned) header) >> 8) & 15;
		if (fmt < 8) {
			fileNameSize = ((unsigned) (sz - 4)) >> 2;
			goto l1;
		} else {
			fileNameSize = (sz - 4) - (fmt & 3);
			goto l1;
		}
	l1:	/* end lengthOf: */;
	}
	if (successFlag) {
		/* begin success: */
		successFlag = (dir_SetMacFileTypeAndCreator(
				(char *) fileNameIndex, fileNameSize,
				(char *) typeStringIndex, (char *) creatorStringIndex)) && successFlag;
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 3 * 4;
	}
}

int primitiveDiv(void) {
    int arg;
    int posArg;
    int posRcvr;
    int result;
    int rcvr;
    int integerPointer;
    int top;
    int integerPointer1;
    int top1;
    int sp;
    int sp1;

	successFlag = true;
	/* begin popInteger */
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top;
	if ((integerPointer & 1)) {
		arg = (integerPointer >> 1);
		goto l1;
	} else {
		successFlag = false;
		arg = 1;
		goto l1;
	}
l1:	/* end popInteger */;
	/* begin popInteger */
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer1 = top1;
	if ((integerPointer1 & 1)) {
		rcvr = (integerPointer1 >> 1);
		goto l2;
	} else {
		successFlag = false;
		rcvr = 1;
		goto l2;
	}
l2:	/* end popInteger */;
	/* begin success: */
	successFlag = (arg != 0) && successFlag;
	if (successFlag) {
		if (rcvr > 0) {
			if (arg > 0) {
				result = rcvr / arg;
			} else {
				posArg = 0 - arg;
				result = 0 - ((rcvr + (posArg - 1)) / posArg);
			}
		} else {
			posRcvr = 0 - rcvr;
			if (arg > 0) {
				result = 0 - ((posRcvr + (arg - 1)) / arg);
			} else {
				posArg = 0 - arg;
				result = posRcvr / posArg;
			}
		}
		/* begin checkIntegerResult:from: */
		if (successFlag && ((result ^ (result << 1)) >= 0)) {
			/* begin pushInteger: */
			/* begin push: */
			longAtput(sp = stackPointer + 4, ((result << 1) | 1));
			stackPointer = sp;
		} else {
			/* begin unPop: */
			stackPointer += 2 * 4;
			failSpecialPrim(12);
		}
	} else {
		/* begin checkIntegerResult:from: */
		if (successFlag && ((0 ^ (0 << 1)) >= 0)) {
			/* begin pushInteger: */
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, ((0 << 1) | 1));
			stackPointer = sp1;
		} else {
			/* begin unPop: */
			stackPointer += 2 * 4;
			failSpecialPrim(12);
		}
	}
}

int primitiveDivide(void) {
    int integerReceiver;
    int integerArgument;
    int integerPointer;
    int top;
    int integerPointer1;
    int top1;
    int sp;

	successFlag = true;
	/* begin popInteger */
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top;
	if ((integerPointer & 1)) {
		integerArgument = (integerPointer >> 1);
		goto l1;
	} else {
		successFlag = false;
		integerArgument = 1;
		goto l1;
	}
l1:	/* end popInteger */;
	/* begin popInteger */
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer1 = top1;
	if ((integerPointer1 & 1)) {
		integerReceiver = (integerPointer1 >> 1);
		goto l2;
	} else {
		successFlag = false;
		integerReceiver = 1;
		goto l2;
	}
l2:	/* end popInteger */;
	/* begin success: */
	successFlag = (integerArgument != 0) && successFlag;
	if (!(successFlag)) {
		integerArgument = 1;
	}
	/* begin success: */
	successFlag = ((integerReceiver % integerArgument) == 0) && successFlag;
	/* begin checkIntegerResult:from: */
	if (successFlag && (((integerReceiver / integerArgument) ^ ((integerReceiver / integerArgument) << 1)) >= 0)) {
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, (((integerReceiver / integerArgument) << 1) | 1));
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
		failSpecialPrim(10);
	}
}

int primitiveDoPrimitiveWithArgs(void) {
    int primIdx;
    int argumentArray;
    int arraySize;
    int index;
    int cntxSize;
    int sp;
    int sp1;
    int sp2;
    int sz;
    int objectPointer;
    int sz1;
    int integerPointer;
    int oop;
    int header;
    int header1;
    int ccIndex;
    int cl;

	argumentArray = longAt(stackPointer);
	/* begin fetchWordLengthOf: */
	/* begin sizeBitsOf: */
	header = longAt(argumentArray);
	if ((header & 3) == 0) {
		sz = (longAt(argumentArray - 8)) & 4294967292U;
		goto l2;
	} else {
		sz = header & 252;
		goto l2;
	}
l2:	/* end sizeBitsOf: */;
	arraySize = ((unsigned) (sz - 4)) >> 2;
	/* begin fetchWordLengthOf: */
	objectPointer = activeContext;
	/* begin sizeBitsOf: */
	header1 = longAt(objectPointer);
	if ((header1 & 3) == 0) {
		sz1 = (longAt(objectPointer - 8)) & 4294967292U;
		goto l3;
	} else {
		sz1 = header1 & 252;
		goto l3;
	}
l3:	/* end sizeBitsOf: */;
	cntxSize = ((unsigned) (sz1 - 4)) >> 2;
	/* begin success: */
	successFlag = (((((unsigned) ((stackPointer - activeContext) - 4)) >> 2) + arraySize) < cntxSize) && successFlag;
	/* begin assertClassOf:is: */
	if ((argumentArray & 1)) {
		successFlag = false;
		goto l4;
	}
	ccIndex = (((unsigned) (longAt(argumentArray))) >> 12) & 31;
	if (ccIndex == 0) {
		cl = (longAt(argumentArray - 4)) & 4294967292U;
	} else {
		cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
	}
	/* begin success: */
	successFlag = (cl == (longAt(((((char *) specialObjectsOop)) + 4) + (7 << 2)))) && successFlag;
l4:	/* end assertClassOf:is: */;
	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (1 * 4));
	if ((integerPointer & 1)) {
		primIdx = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		primIdx = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	if (!(successFlag)) {
		return primitiveFail();
	}
	/* begin pop: */
	stackPointer -= 2 * 4;
	primitiveIndex = primIdx;
	argumentCount = arraySize;
	index = 1;
	while (index <= argumentCount) {
		/* begin push: */
		longAtput(sp = stackPointer + 4, longAt(((((char *) argumentArray)) + 4) + ((index - 1) << 2)));
		stackPointer = sp;
		index += 1;
	}
	/* begin pushRemappableOop: */
	remapBuffer[remapBufferCount += 1] = argumentArray;
	primitiveResponse();
	/* begin popRemappableOop */
	oop = remapBuffer[remapBufferCount];
	remapBufferCount -= 1;
	argumentArray = oop;
	if (!(successFlag)) {
		/* begin pop: */
		stackPointer -= arraySize * 4;
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp1 = stackPointer + 4, ((primIdx << 1) | 1));
		stackPointer = sp1;
		/* begin push: */
		longAtput(sp2 = stackPointer + 4, argumentArray);
		stackPointer = sp2;
		argumentCount = 2;
	}
}

int primitiveDrawLoop(void) {
    int yDelta;
    int rcvr;
    int xDelta;
    int affL;
    int dx1;
    int dy1;
    int px;
    int py;
    int affR;
    int affT;
    int affB;
    int i;
    int P;
    int integerPointer;
    int integerPointer1;
    int successValue;
    int objectPointer;
    int integerValue;
    int objectPointer1;
    int integerValue1;

	rcvr = longAt(stackPointer - (2 * 4));
	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (1 * 4));
	if ((integerPointer & 1)) {
		xDelta = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		xDelta = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (0 * 4));
	if ((integerPointer1 & 1)) {
		yDelta = (integerPointer1 >> 1);
		goto l2;
	} else {
		primitiveFail();
		yDelta = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	/* begin success: */
	successValue = loadBitBltFrom(rcvr);
	successFlag = successValue && successFlag;
	if (successFlag) {
		/* begin drawLoopX:Y: */
		if (xDelta > 0) {
			dx1 = 1;
		} else {
			if (xDelta == 0) {
				dx1 = 0;
			} else {
				dx1 = -1;
			}
		}
		if (yDelta > 0) {
			dy1 = 1;
		} else {
			if (yDelta == 0) {
				dy1 = 0;
			} else {
				dy1 = -1;
			}
		}
		px = abs(yDelta);
		py = abs(xDelta);
		affL = affT = 9999;
		affR = affB = -9999;
		if (py > px) {
			P = ((int) py >> 1);
			for (i = 1; i <= py; i += 1) {
				destX += dx1;
				if ((P -= px) < 0) {
					destY += dy1;
					P += py;
				}
				if (i < py) {
					copyBits();
					if ((affectedL < affectedR) && (affectedT < affectedB)) {
						affL = ((affL < affectedL) ? affL : affectedL);
						affR = ((affR < affectedR) ? affectedR : affR);
						affT = ((affT < affectedT) ? affT : affectedT);
						affB = ((affB < affectedB) ? affectedB : affB);
						if (((affR - affL) * (affB - affT)) > 4000) {
							affectedL = affL;
							affectedR = affR;
							affectedT = affT;
							affectedB = affB;
							showDisplayBits();
							affL = affT = 9999;
							affR = affB = -9999;
						}
					}
				}
			}
		} else {
			P = ((int) px >> 1);
			for (i = 1; i <= px; i += 1) {
				destY += dy1;
				if ((P -= py) < 0) {
					destX += dx1;
					P += px;
				}
				if (i < px) {
					copyBits();
					if ((affectedL < affectedR) && (affectedT < affectedB)) {
						affL = ((affL < affectedL) ? affL : affectedL);
						affR = ((affR < affectedR) ? affectedR : affR);
						affT = ((affT < affectedT) ? affT : affectedT);
						affB = ((affB < affectedB) ? affectedB : affB);
						if (((affR - affL) * (affB - affT)) > 4000) {
							affectedL = affL;
							affectedR = affR;
							affectedT = affT;
							affectedB = affB;
							showDisplayBits();
							affL = affT = 9999;
							affR = affB = -9999;
						}
					}
				}
			}
		}
		affectedL = affL;
		affectedR = affR;
		affectedT = affT;
		affectedB = affB;
		/* begin storeInteger:ofObject:withValue: */
		objectPointer = bitBltOop;
		integerValue = destX;
		if ((integerValue ^ (integerValue << 1)) >= 0) {
			longAtput(((((char *) objectPointer)) + 4) + (4 << 2), ((integerValue << 1) | 1));
		} else {
			primitiveFail();
		}
		/* begin storeInteger:ofObject:withValue: */
		objectPointer1 = bitBltOop;
		integerValue1 = destY;
		if ((integerValue1 ^ (integerValue1 << 1)) >= 0) {
			longAtput(((((char *) objectPointer1)) + 4) + (5 << 2), ((integerValue1 << 1) | 1));
		} else {
			primitiveFail();
		}
		showDisplayBits();
		/* begin pop: */
		stackPointer -= 2 * 4;
	}
}

int primitiveEqual(void) {
    int integerReceiver;
    int integerArgument;
    int result;
    int top;
    int top1;
    int sp;
    int sp1;

	successFlag = true;
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	integerArgument = top;
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	integerReceiver = top1;
	/* begin compare31or32Bits:equal: */
	if (((integerReceiver & 1)) && ((integerArgument & 1))) {
		result = integerReceiver == integerArgument;
		goto l1;
	}
	result = (positive32BitValueOf(integerReceiver)) == (positive32BitValueOf(integerArgument));
l1:	/* end compare31or32Bits:equal: */;
	/* begin checkBooleanResult:from: */
	if (successFlag) {
		/* begin pushBool: */
		if (result) {
			/* begin push: */
			longAtput(sp = stackPointer + 4, trueObj);
			stackPointer = sp;
		} else {
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, falseObj);
			stackPointer = sp1;
		}
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
		failSpecialPrim(7);
	}
}

int primitiveEquivalent(void) {
    int thisObject;
    int otherObject;
    int top;
    int top1;
    int sp;
    int sp1;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	otherObject = top;
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	thisObject = top1;
	/* begin pushBool: */
	if (thisObject == otherObject) {
		/* begin push: */
		longAtput(sp = stackPointer + 4, trueObj);
		stackPointer = sp;
	} else {
		/* begin push: */
		longAtput(sp1 = stackPointer + 4, falseObj);
		stackPointer = sp1;
	}
}

int primitiveExitToDebugger(void) {
	error("Exit to debugger at user request");
}

int primitiveExp(void) {
    double rcvr;

	rcvr = popFloat();
	if (successFlag) {
		pushFloat(exp(rcvr));
	} else {
		/* begin unPop: */
		stackPointer += 1 * 4;
	}
}

int primitiveExponent(void) {
    int pwr;
    double frac;
    double rcvr;
    int sp;

	rcvr = popFloat();
	if (successFlag) {
		frac = frexp(rcvr, &pwr);
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, (((pwr - 1) << 1) | 1));
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 1 * 4;
	}
}

int primitiveFail(void) {
	successFlag = false;
}

int primitiveFileAtEnd(void) {
    int atEnd;
    SQFile *file;
    int sp;
    int sp1;

	file = fileValueOf(longAt(stackPointer));
	if (successFlag) {
		atEnd = sqFileAtEnd(file);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 2 * 4;
		/* begin pushBool: */
		if (atEnd) {
			/* begin push: */
			longAtput(sp = stackPointer + 4, trueObj);
			stackPointer = sp;
		} else {
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, falseObj);
			stackPointer = sp1;
		}
	}
}

int primitiveFileClose(void) {
    SQFile *file;

	file = fileValueOf(longAt(stackPointer));
	if (successFlag) {
		sqFileClose(file);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
	}
}

int primitiveFileDelete(void) {
    int nameIndex;
    int namePointer;
    int nameSize;
    int sz;
    int header;
    int fmt;

	namePointer = longAt(stackPointer);
	/* begin success: */
	successFlag = (((((unsigned) (longAt(namePointer))) >> 8) & 15) >= 8) && successFlag;
	if (successFlag) {
		nameIndex = namePointer + 4;
		/* begin lengthOf: */
		header = longAt(namePointer);
		if ((header & 3) == 0) {
			sz = (longAt(namePointer - 8)) & 4294967292U;
		} else {
			sz = header & 252;
		}
		fmt = (((unsigned) header) >> 8) & 15;
		if (fmt < 8) {
			nameSize = ((unsigned) (sz - 4)) >> 2;
			goto l1;
		} else {
			nameSize = (sz - 4) - (fmt & 3);
			goto l1;
		}
	l1:	/* end lengthOf: */;
	}
	if (successFlag) {
		sqFileDeleteNameSize(nameIndex, nameSize);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
	}
}

int primitiveFileGetPosition(void) {
    int position;
    SQFile *file;
    int sp;

	file = fileValueOf(longAt(stackPointer));
	if (successFlag) {
		position = sqFileGetPosition(file);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 2 * 4;
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, ((position << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveFileOpen(void) {
    int writeFlag;
    int nameIndex;
    int namePointer;
    int nameSize;
    int filePointer;
    SQFile *file;
    int sz;
    int header;
    int fmt;
    int sp;

	/* begin booleanValueOf: */
	if ((longAt(stackPointer)) == trueObj) {
		writeFlag = true;
		goto l2;
	}
	if ((longAt(stackPointer)) == falseObj) {
		writeFlag = false;
		goto l2;
	}
	successFlag = false;
	writeFlag = null;
l2:	/* end booleanValueOf: */;
	namePointer = longAt(stackPointer - (1 * 4));
	/* begin success: */
	successFlag = (((((unsigned) (longAt(namePointer))) >> 8) & 15) >= 8) && successFlag;
	if (successFlag) {
		filePointer = instantiateClassindexableSize(longAt(((((char *) specialObjectsOop)) + 4) + (26 << 2)), fileRecordSize());
		file = fileValueOf(filePointer);
		nameIndex = namePointer + 4;
		/* begin lengthOf: */
		header = longAt(namePointer);
		if ((header & 3) == 0) {
			sz = (longAt(namePointer - 8)) & 4294967292U;
		} else {
			sz = header & 252;
		}
		fmt = (((unsigned) header) >> 8) & 15;
		if (fmt < 8) {
			nameSize = ((unsigned) (sz - 4)) >> 2;
			goto l1;
		} else {
			nameSize = (sz - 4) - (fmt & 3);
			goto l1;
		}
	l1:	/* end lengthOf: */;
	}
	if (successFlag) {
		sqFileOpen(file, nameIndex, nameSize, writeFlag);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 3 * 4;
		/* begin push: */
		longAtput(sp = stackPointer + 4, filePointer);
		stackPointer = sp;
	}
}

int primitiveFileRead(void) {
    int array;
    int startIndex;
    int arrayIndex;
    int bytesRead;
    int byteSize;
    int count;
    SQFile *file;
    int sp;
    int integerPointer;
    int integerPointer1;
    int successValue;
    int successValue1;
    int fmt;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		count = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		count = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (1 * 4));
	if ((integerPointer1 & 1)) {
		startIndex = (integerPointer1 >> 1);
		goto l2;
	} else {
		primitiveFail();
		startIndex = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	array = longAt(stackPointer - (2 * 4));
	file = fileValueOf(longAt(stackPointer - (3 * 4)));
	/* begin success: */
	/* begin isWordsOrBytes: */
	fmt = (((unsigned) (longAt(array))) >> 8) & 15;
	successValue = (fmt == 6) || ((fmt >= 8) && (fmt <= 11));
	successFlag = successValue && successFlag;
	if (((((unsigned) (longAt(array))) >> 8) & 15) == 6) {
		byteSize = 4;
	} else {
		byteSize = 1;
	}
	/* begin success: */
	successValue1 = (startIndex >= 1) && (((startIndex + count) - 1) <= (lengthOf(array)));
	successFlag = successValue1 && successFlag;
	if (successFlag) {
		arrayIndex = array + 4;
		bytesRead = sqFileReadIntoAt(file, count * byteSize, arrayIndex, (startIndex - 1) * byteSize);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 5 * 4;
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, (((bytesRead / byteSize) << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveFileRename(void) {
    int newNameIndex;
    int newNamePointer;
    int newNameSize;
    int oldNamePointer;
    int oldNameIndex;
    int oldNameSize;
    int sz;
    int header;
    int fmt;
    int sz1;
    int header1;
    int fmt1;

	newNamePointer = longAt(stackPointer);
	oldNamePointer = longAt(stackPointer - (1 * 4));
	/* begin success: */
	successFlag = (((((unsigned) (longAt(newNamePointer))) >> 8) & 15) >= 8) && successFlag;
	/* begin success: */
	successFlag = (((((unsigned) (longAt(oldNamePointer))) >> 8) & 15) >= 8) && successFlag;
	if (successFlag) {
		newNameIndex = newNamePointer + 4;
		/* begin lengthOf: */
		header = longAt(newNamePointer);
		if ((header & 3) == 0) {
			sz = (longAt(newNamePointer - 8)) & 4294967292U;
		} else {
			sz = header & 252;
		}
		fmt = (((unsigned) header) >> 8) & 15;
		if (fmt < 8) {
			newNameSize = ((unsigned) (sz - 4)) >> 2;
			goto l1;
		} else {
			newNameSize = (sz - 4) - (fmt & 3);
			goto l1;
		}
	l1:	/* end lengthOf: */;
		oldNameIndex = oldNamePointer + 4;
		/* begin lengthOf: */
		header1 = longAt(oldNamePointer);
		if ((header1 & 3) == 0) {
			sz1 = (longAt(oldNamePointer - 8)) & 4294967292U;
		} else {
			sz1 = header1 & 252;
		}
		fmt1 = (((unsigned) header1) >> 8) & 15;
		if (fmt1 < 8) {
			oldNameSize = ((unsigned) (sz1 - 4)) >> 2;
			goto l2;
		} else {
			oldNameSize = (sz1 - 4) - (fmt1 & 3);
			goto l2;
		}
	l2:	/* end lengthOf: */;
	}
	if (successFlag) {
		sqFileRenameOldSizeNewSize(oldNameIndex, oldNameSize, newNameIndex, newNameSize);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 2 * 4;
	}
}

int primitiveFileSetPosition(void) {
    int newPosition;
    SQFile *file;
    int integerPointer;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		newPosition = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		newPosition = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	file = fileValueOf(longAt(stackPointer - (1 * 4)));
	if (successFlag) {
		sqFileSetPosition(file, newPosition);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 2 * 4;
	}
}

int primitiveFileSize(void) {
    int size;
    SQFile *file;
    int sp;

	file = fileValueOf(longAt(stackPointer));
	if (successFlag) {
		size = sqFileSize(file);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 2 * 4;
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, ((size << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveFileWrite(void) {
    int array;
    int startIndex;
    int arrayIndex;
    int bytesWritten;
    int byteSize;
    int count;
    SQFile *file;
    int sp;
    int integerPointer;
    int integerPointer1;
    int successValue;
    int successValue1;
    int fmt;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		count = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		count = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (1 * 4));
	if ((integerPointer1 & 1)) {
		startIndex = (integerPointer1 >> 1);
		goto l2;
	} else {
		primitiveFail();
		startIndex = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	array = longAt(stackPointer - (2 * 4));
	file = fileValueOf(longAt(stackPointer - (3 * 4)));
	/* begin success: */
	/* begin isWordsOrBytes: */
	fmt = (((unsigned) (longAt(array))) >> 8) & 15;
	successValue = (fmt == 6) || ((fmt >= 8) && (fmt <= 11));
	successFlag = successValue && successFlag;
	if (((((unsigned) (longAt(array))) >> 8) & 15) == 6) {
		byteSize = 4;
	} else {
		byteSize = 1;
	}
	/* begin success: */
	successValue1 = (startIndex >= 1) && (((startIndex + count) - 1) <= (lengthOf(array)));
	successFlag = successValue1 && successFlag;
	if (successFlag) {
		arrayIndex = array + 4;
		bytesWritten = sqFileWriteFromAt(file, count * byteSize, arrayIndex, (startIndex - 1) * byteSize);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 5 * 4;
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, (((bytesWritten / byteSize) << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveFloatAdd(void) {
    double arg;
    int argOop;
    int rcvrOop;
    double rcvr;
    double result;
    int resultOop;
    int sp;
    int floatClass;
    int ccIndex;
    int cl;
    int ccIndex1;
    int cl1;

	rcvrOop = longAt(stackPointer - (1 * 4));
	argOop = longAt(stackPointer);
	/* begin assertFloat:and: */
	if (((rcvrOop | argOop) & 1) != 0) {
		successFlag = false;
	} else {
		floatClass = longAt(((((char *) specialObjectsOop)) + 4) + (9 << 2));
		/* begin assertClassOf:is: */
		if ((rcvrOop & 1)) {
			successFlag = false;
			goto l1;
		}
		ccIndex = (((unsigned) (longAt(rcvrOop))) >> 12) & 31;
		if (ccIndex == 0) {
			cl = (longAt(rcvrOop - 4)) & 4294967292U;
		} else {
			cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl == floatClass) && successFlag;
	l1:	/* end assertClassOf:is: */;
		/* begin assertClassOf:is: */
		if ((argOop & 1)) {
			successFlag = false;
			goto l2;
		}
		ccIndex1 = (((unsigned) (longAt(argOop))) >> 12) & 31;
		if (ccIndex1 == 0) {
			cl1 = (longAt(argOop - 4)) & 4294967292U;
		} else {
			cl1 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex1 - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl1 == floatClass) && successFlag;
	l2:	/* end assertClassOf:is: */;
	}
	if (successFlag) {
		fetchFloatAtinto(rcvrOop + 4, rcvr);
		fetchFloatAtinto(argOop + 4, arg);
		result = rcvr + arg;
		resultOop = clone(rcvrOop);
		storeFloatAtfrom(resultOop + 4, result);
		/* begin pop:thenPush: */
		longAtput(sp = stackPointer - ((2 - 1) * 4), resultOop);
		stackPointer = sp;
	}
}

int primitiveFloatDivide(void) {
    double arg;
    int argOop;
    int rcvrOop;
    double rcvr;
    double result;
    int resultOop;
    int sp;
    int floatClass;
    int ccIndex;
    int cl;
    int ccIndex1;
    int cl1;

	rcvrOop = longAt(stackPointer - (1 * 4));
	argOop = longAt(stackPointer);
	/* begin assertFloat:and: */
	if (((rcvrOop | argOop) & 1) != 0) {
		successFlag = false;
	} else {
		floatClass = longAt(((((char *) specialObjectsOop)) + 4) + (9 << 2));
		/* begin assertClassOf:is: */
		if ((rcvrOop & 1)) {
			successFlag = false;
			goto l1;
		}
		ccIndex = (((unsigned) (longAt(rcvrOop))) >> 12) & 31;
		if (ccIndex == 0) {
			cl = (longAt(rcvrOop - 4)) & 4294967292U;
		} else {
			cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl == floatClass) && successFlag;
	l1:	/* end assertClassOf:is: */;
		/* begin assertClassOf:is: */
		if ((argOop & 1)) {
			successFlag = false;
			goto l2;
		}
		ccIndex1 = (((unsigned) (longAt(argOop))) >> 12) & 31;
		if (ccIndex1 == 0) {
			cl1 = (longAt(argOop - 4)) & 4294967292U;
		} else {
			cl1 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex1 - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl1 == floatClass) && successFlag;
	l2:	/* end assertClassOf:is: */;
	}
	if (successFlag) {
		fetchFloatAtinto(rcvrOop + 4, rcvr);
		fetchFloatAtinto(argOop + 4, arg);
		/* begin success: */
		successFlag = (arg != 0.0) && successFlag;
		if (successFlag) {
			result = rcvr / arg;
			resultOop = clone(rcvrOop);
			storeFloatAtfrom(resultOop + 4, result);
			/* begin pop:thenPush: */
			longAtput(sp = stackPointer - ((2 - 1) * 4), resultOop);
			stackPointer = sp;
		}
	}
}

int primitiveFloatEqual(void) {
    double arg;
    int argOop;
    int rcvrOop;
    double rcvr;
    int sp;
    int sp1;
    int floatClass;
    int ccIndex;
    int cl;
    int ccIndex1;
    int cl1;

	rcvrOop = longAt(stackPointer - (1 * 4));
	argOop = longAt(stackPointer);
	/* begin assertFloat:and: */
	if (((rcvrOop | argOop) & 1) != 0) {
		successFlag = false;
	} else {
		floatClass = longAt(((((char *) specialObjectsOop)) + 4) + (9 << 2));
		/* begin assertClassOf:is: */
		if ((rcvrOop & 1)) {
			successFlag = false;
			goto l1;
		}
		ccIndex = (((unsigned) (longAt(rcvrOop))) >> 12) & 31;
		if (ccIndex == 0) {
			cl = (longAt(rcvrOop - 4)) & 4294967292U;
		} else {
			cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl == floatClass) && successFlag;
	l1:	/* end assertClassOf:is: */;
		/* begin assertClassOf:is: */
		if ((argOop & 1)) {
			successFlag = false;
			goto l2;
		}
		ccIndex1 = (((unsigned) (longAt(argOop))) >> 12) & 31;
		if (ccIndex1 == 0) {
			cl1 = (longAt(argOop - 4)) & 4294967292U;
		} else {
			cl1 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex1 - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl1 == floatClass) && successFlag;
	l2:	/* end assertClassOf:is: */;
	}
	if (successFlag) {
		fetchFloatAtinto(rcvrOop + 4, rcvr);
		fetchFloatAtinto(argOop + 4, arg);
		/* begin pop: */
		stackPointer -= 2 * 4;
		/* begin pushBool: */
		if (rcvr == arg) {
			/* begin push: */
			longAtput(sp = stackPointer + 4, trueObj);
			stackPointer = sp;
		} else {
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, falseObj);
			stackPointer = sp1;
		}
	}
}

int primitiveFloatGreaterOrEqual(void) {
    double arg;
    int argOop;
    int rcvrOop;
    double rcvr;
    int sp;
    int sp1;
    int floatClass;
    int ccIndex;
    int cl;
    int ccIndex1;
    int cl1;

	rcvrOop = longAt(stackPointer - (1 * 4));
	argOop = longAt(stackPointer);
	/* begin assertFloat:and: */
	if (((rcvrOop | argOop) & 1) != 0) {
		successFlag = false;
	} else {
		floatClass = longAt(((((char *) specialObjectsOop)) + 4) + (9 << 2));
		/* begin assertClassOf:is: */
		if ((rcvrOop & 1)) {
			successFlag = false;
			goto l1;
		}
		ccIndex = (((unsigned) (longAt(rcvrOop))) >> 12) & 31;
		if (ccIndex == 0) {
			cl = (longAt(rcvrOop - 4)) & 4294967292U;
		} else {
			cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl == floatClass) && successFlag;
	l1:	/* end assertClassOf:is: */;
		/* begin assertClassOf:is: */
		if ((argOop & 1)) {
			successFlag = false;
			goto l2;
		}
		ccIndex1 = (((unsigned) (longAt(argOop))) >> 12) & 31;
		if (ccIndex1 == 0) {
			cl1 = (longAt(argOop - 4)) & 4294967292U;
		} else {
			cl1 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex1 - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl1 == floatClass) && successFlag;
	l2:	/* end assertClassOf:is: */;
	}
	if (successFlag) {
		fetchFloatAtinto(rcvrOop + 4, rcvr);
		fetchFloatAtinto(argOop + 4, arg);
		/* begin pop: */
		stackPointer -= 2 * 4;
		/* begin pushBool: */
		if (rcvr >= arg) {
			/* begin push: */
			longAtput(sp = stackPointer + 4, trueObj);
			stackPointer = sp;
		} else {
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, falseObj);
			stackPointer = sp1;
		}
	}
}

int primitiveFloatGreaterThan(void) {
    double arg;
    int argOop;
    int rcvrOop;
    double rcvr;
    int sp;
    int sp1;
    int floatClass;
    int ccIndex;
    int cl;
    int ccIndex1;
    int cl1;

	rcvrOop = longAt(stackPointer - (1 * 4));
	argOop = longAt(stackPointer);
	/* begin assertFloat:and: */
	if (((rcvrOop | argOop) & 1) != 0) {
		successFlag = false;
	} else {
		floatClass = longAt(((((char *) specialObjectsOop)) + 4) + (9 << 2));
		/* begin assertClassOf:is: */
		if ((rcvrOop & 1)) {
			successFlag = false;
			goto l1;
		}
		ccIndex = (((unsigned) (longAt(rcvrOop))) >> 12) & 31;
		if (ccIndex == 0) {
			cl = (longAt(rcvrOop - 4)) & 4294967292U;
		} else {
			cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl == floatClass) && successFlag;
	l1:	/* end assertClassOf:is: */;
		/* begin assertClassOf:is: */
		if ((argOop & 1)) {
			successFlag = false;
			goto l2;
		}
		ccIndex1 = (((unsigned) (longAt(argOop))) >> 12) & 31;
		if (ccIndex1 == 0) {
			cl1 = (longAt(argOop - 4)) & 4294967292U;
		} else {
			cl1 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex1 - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl1 == floatClass) && successFlag;
	l2:	/* end assertClassOf:is: */;
	}
	if (successFlag) {
		fetchFloatAtinto(rcvrOop + 4, rcvr);
		fetchFloatAtinto(argOop + 4, arg);
		/* begin pop: */
		stackPointer -= 2 * 4;
		/* begin pushBool: */
		if (rcvr > arg) {
			/* begin push: */
			longAtput(sp = stackPointer + 4, trueObj);
			stackPointer = sp;
		} else {
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, falseObj);
			stackPointer = sp1;
		}
	}
}

int primitiveFloatLessOrEqual(void) {
    double arg;
    int argOop;
    int rcvrOop;
    double rcvr;
    int sp;
    int sp1;
    int floatClass;
    int ccIndex;
    int cl;
    int ccIndex1;
    int cl1;

	rcvrOop = longAt(stackPointer - (1 * 4));
	argOop = longAt(stackPointer);
	/* begin assertFloat:and: */
	if (((rcvrOop | argOop) & 1) != 0) {
		successFlag = false;
	} else {
		floatClass = longAt(((((char *) specialObjectsOop)) + 4) + (9 << 2));
		/* begin assertClassOf:is: */
		if ((rcvrOop & 1)) {
			successFlag = false;
			goto l1;
		}
		ccIndex = (((unsigned) (longAt(rcvrOop))) >> 12) & 31;
		if (ccIndex == 0) {
			cl = (longAt(rcvrOop - 4)) & 4294967292U;
		} else {
			cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl == floatClass) && successFlag;
	l1:	/* end assertClassOf:is: */;
		/* begin assertClassOf:is: */
		if ((argOop & 1)) {
			successFlag = false;
			goto l2;
		}
		ccIndex1 = (((unsigned) (longAt(argOop))) >> 12) & 31;
		if (ccIndex1 == 0) {
			cl1 = (longAt(argOop - 4)) & 4294967292U;
		} else {
			cl1 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex1 - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl1 == floatClass) && successFlag;
	l2:	/* end assertClassOf:is: */;
	}
	if (successFlag) {
		fetchFloatAtinto(rcvrOop + 4, rcvr);
		fetchFloatAtinto(argOop + 4, arg);
		/* begin pop: */
		stackPointer -= 2 * 4;
		/* begin pushBool: */
		if (rcvr <= arg) {
			/* begin push: */
			longAtput(sp = stackPointer + 4, trueObj);
			stackPointer = sp;
		} else {
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, falseObj);
			stackPointer = sp1;
		}
	}
}

int primitiveFloatLessThan(void) {
    double arg;
    int argOop;
    int rcvrOop;
    double rcvr;
    int sp;
    int sp1;
    int floatClass;
    int ccIndex;
    int cl;
    int ccIndex1;
    int cl1;

	rcvrOop = longAt(stackPointer - (1 * 4));
	argOop = longAt(stackPointer);
	/* begin assertFloat:and: */
	if (((rcvrOop | argOop) & 1) != 0) {
		successFlag = false;
	} else {
		floatClass = longAt(((((char *) specialObjectsOop)) + 4) + (9 << 2));
		/* begin assertClassOf:is: */
		if ((rcvrOop & 1)) {
			successFlag = false;
			goto l1;
		}
		ccIndex = (((unsigned) (longAt(rcvrOop))) >> 12) & 31;
		if (ccIndex == 0) {
			cl = (longAt(rcvrOop - 4)) & 4294967292U;
		} else {
			cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl == floatClass) && successFlag;
	l1:	/* end assertClassOf:is: */;
		/* begin assertClassOf:is: */
		if ((argOop & 1)) {
			successFlag = false;
			goto l2;
		}
		ccIndex1 = (((unsigned) (longAt(argOop))) >> 12) & 31;
		if (ccIndex1 == 0) {
			cl1 = (longAt(argOop - 4)) & 4294967292U;
		} else {
			cl1 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex1 - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl1 == floatClass) && successFlag;
	l2:	/* end assertClassOf:is: */;
	}
	if (successFlag) {
		fetchFloatAtinto(rcvrOop + 4, rcvr);
		fetchFloatAtinto(argOop + 4, arg);
		/* begin pop: */
		stackPointer -= 2 * 4;
		/* begin pushBool: */
		if (rcvr < arg) {
			/* begin push: */
			longAtput(sp = stackPointer + 4, trueObj);
			stackPointer = sp;
		} else {
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, falseObj);
			stackPointer = sp1;
		}
	}
}

int primitiveFloatMultiply(void) {
    double arg;
    int argOop;
    int rcvrOop;
    double rcvr;
    double result;
    int resultOop;
    int sp;
    int floatClass;
    int ccIndex;
    int cl;
    int ccIndex1;
    int cl1;

	rcvrOop = longAt(stackPointer - (1 * 4));
	argOop = longAt(stackPointer);
	/* begin assertFloat:and: */
	if (((rcvrOop | argOop) & 1) != 0) {
		successFlag = false;
	} else {
		floatClass = longAt(((((char *) specialObjectsOop)) + 4) + (9 << 2));
		/* begin assertClassOf:is: */
		if ((rcvrOop & 1)) {
			successFlag = false;
			goto l1;
		}
		ccIndex = (((unsigned) (longAt(rcvrOop))) >> 12) & 31;
		if (ccIndex == 0) {
			cl = (longAt(rcvrOop - 4)) & 4294967292U;
		} else {
			cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl == floatClass) && successFlag;
	l1:	/* end assertClassOf:is: */;
		/* begin assertClassOf:is: */
		if ((argOop & 1)) {
			successFlag = false;
			goto l2;
		}
		ccIndex1 = (((unsigned) (longAt(argOop))) >> 12) & 31;
		if (ccIndex1 == 0) {
			cl1 = (longAt(argOop - 4)) & 4294967292U;
		} else {
			cl1 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex1 - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl1 == floatClass) && successFlag;
	l2:	/* end assertClassOf:is: */;
	}
	if (successFlag) {
		fetchFloatAtinto(rcvrOop + 4, rcvr);
		fetchFloatAtinto(argOop + 4, arg);
		result = rcvr * arg;
		resultOop = clone(rcvrOop);
		storeFloatAtfrom(resultOop + 4, result);
		/* begin pop:thenPush: */
		longAtput(sp = stackPointer - ((2 - 1) * 4), resultOop);
		stackPointer = sp;
	}
}

int primitiveFloatNotEqual(void) {
    double arg;
    int argOop;
    int rcvrOop;
    double rcvr;
    int sp;
    int sp1;
    int floatClass;
    int ccIndex;
    int cl;
    int ccIndex1;
    int cl1;

	rcvrOop = longAt(stackPointer - (1 * 4));
	argOop = longAt(stackPointer);
	/* begin assertFloat:and: */
	if (((rcvrOop | argOop) & 1) != 0) {
		successFlag = false;
	} else {
		floatClass = longAt(((((char *) specialObjectsOop)) + 4) + (9 << 2));
		/* begin assertClassOf:is: */
		if ((rcvrOop & 1)) {
			successFlag = false;
			goto l1;
		}
		ccIndex = (((unsigned) (longAt(rcvrOop))) >> 12) & 31;
		if (ccIndex == 0) {
			cl = (longAt(rcvrOop - 4)) & 4294967292U;
		} else {
			cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl == floatClass) && successFlag;
	l1:	/* end assertClassOf:is: */;
		/* begin assertClassOf:is: */
		if ((argOop & 1)) {
			successFlag = false;
			goto l2;
		}
		ccIndex1 = (((unsigned) (longAt(argOop))) >> 12) & 31;
		if (ccIndex1 == 0) {
			cl1 = (longAt(argOop - 4)) & 4294967292U;
		} else {
			cl1 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex1 - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl1 == floatClass) && successFlag;
	l2:	/* end assertClassOf:is: */;
	}
	if (successFlag) {
		fetchFloatAtinto(rcvrOop + 4, rcvr);
		fetchFloatAtinto(argOop + 4, arg);
		/* begin pop: */
		stackPointer -= 2 * 4;
		/* begin pushBool: */
		if (rcvr != arg) {
			/* begin push: */
			longAtput(sp = stackPointer + 4, trueObj);
			stackPointer = sp;
		} else {
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, falseObj);
			stackPointer = sp1;
		}
	}
}

int primitiveFloatSubtract(void) {
    double arg;
    int argOop;
    int rcvrOop;
    double rcvr;
    double result;
    int resultOop;
    int sp;
    int floatClass;
    int ccIndex;
    int cl;
    int ccIndex1;
    int cl1;

	rcvrOop = longAt(stackPointer - (1 * 4));
	argOop = longAt(stackPointer);
	/* begin assertFloat:and: */
	if (((rcvrOop | argOop) & 1) != 0) {
		successFlag = false;
	} else {
		floatClass = longAt(((((char *) specialObjectsOop)) + 4) + (9 << 2));
		/* begin assertClassOf:is: */
		if ((rcvrOop & 1)) {
			successFlag = false;
			goto l1;
		}
		ccIndex = (((unsigned) (longAt(rcvrOop))) >> 12) & 31;
		if (ccIndex == 0) {
			cl = (longAt(rcvrOop - 4)) & 4294967292U;
		} else {
			cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl == floatClass) && successFlag;
	l1:	/* end assertClassOf:is: */;
		/* begin assertClassOf:is: */
		if ((argOop & 1)) {
			successFlag = false;
			goto l2;
		}
		ccIndex1 = (((unsigned) (longAt(argOop))) >> 12) & 31;
		if (ccIndex1 == 0) {
			cl1 = (longAt(argOop - 4)) & 4294967292U;
		} else {
			cl1 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex1 - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl1 == floatClass) && successFlag;
	l2:	/* end assertClassOf:is: */;
	}
	if (successFlag) {
		fetchFloatAtinto(rcvrOop + 4, rcvr);
		fetchFloatAtinto(argOop + 4, arg);
		result = rcvr - arg;
		resultOop = clone(rcvrOop);
		storeFloatAtfrom(resultOop + 4, result);
		/* begin pop:thenPush: */
		longAtput(sp = stackPointer - ((2 - 1) * 4), resultOop);
		stackPointer = sp;
	}
}

int primitiveFlushCache(void) {
    int i;

	/* begin flushMethodCache */
	for (i = 1; i <= 2048; i += 1) {
		methodCache[i] = 0;
	}
	mcProbe = 0;
}

int primitiveFlushCacheSelective(void) {
    int selector;
    int i;
    int nCols;
    int col;

	selector = longAt(stackPointer);
	nCols = ((int) 2048 >> 9);
	for (i = 1; i <= 512; i += 1) {
		if ((methodCache[i]) == selector) {
			for (col = 0; col <= (nCols - 1); col += 1) {
				methodCache[i + (512 * col)] = 0;
			}
		}
	}
}

int primitiveForceDisplayUpdate(void) {
	ioForceDisplayUpdate();
}

int primitiveFormPrint(void) {
    double vScale;
    int depth;
    int pixelsPerWord;
    int bitsArray;
    double hScale;
    int wordsPerLine;
    int h;
    int w;
    int bitsArraySize;
    int landscapeFlag;
    int ok;
    int rcvr;

	/* begin booleanValueOf: */
	if ((longAt(stackPointer)) == trueObj) {
		landscapeFlag = true;
		goto l1;
	}
	if ((longAt(stackPointer)) == falseObj) {
		landscapeFlag = false;
		goto l1;
	}
	successFlag = false;
	landscapeFlag = null;
l1:	/* end booleanValueOf: */;
	vScale = floatValueOf(longAt(stackPointer - (1 * 4)));
	hScale = floatValueOf(longAt(stackPointer - (2 * 4)));
	rcvr = longAt(stackPointer - (3 * 4));
	if ((rcvr & 1)) {
		/* begin success: */
		successFlag = false && successFlag;
	}
	if (successFlag) {
		if (!((((((unsigned) (longAt(rcvr))) >> 8) & 15) <= 4) && ((lengthOf(rcvr)) >= 4))) {
			/* begin success: */
			successFlag = false && successFlag;
		}
	}
	if (successFlag) {
		bitsArray = longAt(((((char *) rcvr)) + 4) + (0 << 2));
		w = fetchIntegerofObject(1, rcvr);
		h = fetchIntegerofObject(2, rcvr);
		depth = fetchIntegerofObject(3, rcvr);
		if (!((w > 0) && (h > 0))) {
			/* begin success: */
			successFlag = false && successFlag;
		}
		pixelsPerWord = 32 / depth;
		wordsPerLine = (w + (pixelsPerWord - 1)) / pixelsPerWord;
		if ((!((rcvr & 1))) && (isWordsOrBytes(bitsArray))) {
			bitsArraySize = byteLengthOf(bitsArray);
			/* begin success: */
			successFlag = (bitsArraySize == ((wordsPerLine * h) * 4)) && successFlag;
		} else {
			/* begin success: */
			successFlag = false && successFlag;
		}
	}
	if (successFlag) {
		ok = ioFormPrint(bitsArray + 4, w, h, depth, hScale, vScale, landscapeFlag);
		/* begin success: */
		successFlag = ok && successFlag;
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 3 * 4;
	}
}

int primitiveFractionalPart(void) {
    double trunc;
    double frac;
    double rcvr;

	rcvr = popFloat();
	if (successFlag) {
		frac = modf(rcvr, &trunc);
		pushFloat(frac);
	} else {
		/* begin unPop: */
		stackPointer += 1 * 4;
	}
}

int primitiveFullGC(void) {
    int sp;

	/* begin pop: */
	stackPointer -= 1 * 4;
	incrementalGC();
	fullGC();
	/* begin pushInteger: */
	/* begin push: */
	longAtput(sp = stackPointer + 4, ((((longAt(freeBlock)) & 536870908) << 1) | 1));
	stackPointer = sp;
}

int primitiveGetAttribute(void) {
    int attr;
    int sz;
    int s;
    int sp;
    int integerPointer;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		attr = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		attr = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	if (successFlag) {
		sz = attributeSize(attr);
	}
	if (successFlag) {
		s = instantiateClassindexableSize(longAt(((((char *) specialObjectsOop)) + 4) + (6 << 2)), sz);
		getAttributeIntoLength(attr, s + 4, sz);
		/* begin pop: */
		stackPointer -= 2 * 4;
		/* begin push: */
		longAtput(sp = stackPointer + 4, s);
		stackPointer = sp;
	}
}

int primitiveGreaterOrEqual(void) {
    int integerReceiver;
    int integerArgument;
    int integerPointer;
    int top;
    int integerPointer1;
    int top1;
    int sp;
    int sp1;

	successFlag = true;
	/* begin popInteger */
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top;
	if ((integerPointer & 1)) {
		integerArgument = (integerPointer >> 1);
		goto l1;
	} else {
		successFlag = false;
		integerArgument = 1;
		goto l1;
	}
l1:	/* end popInteger */;
	/* begin popInteger */
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer1 = top1;
	if ((integerPointer1 & 1)) {
		integerReceiver = (integerPointer1 >> 1);
		goto l2;
	} else {
		successFlag = false;
		integerReceiver = 1;
		goto l2;
	}
l2:	/* end popInteger */;
	/* begin checkBooleanResult:from: */
	if (successFlag) {
		/* begin pushBool: */
		if (integerReceiver >= integerArgument) {
			/* begin push: */
			longAtput(sp = stackPointer + 4, trueObj);
			stackPointer = sp;
		} else {
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, falseObj);
			stackPointer = sp1;
		}
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
		failSpecialPrim(6);
	}
}

int primitiveGreaterThan(void) {
    int integerReceiver;
    int integerArgument;
    int integerPointer;
    int top;
    int integerPointer1;
    int top1;
    int sp;
    int sp1;

	successFlag = true;
	/* begin popInteger */
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top;
	if ((integerPointer & 1)) {
		integerArgument = (integerPointer >> 1);
		goto l1;
	} else {
		successFlag = false;
		integerArgument = 1;
		goto l1;
	}
l1:	/* end popInteger */;
	/* begin popInteger */
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer1 = top1;
	if ((integerPointer1 & 1)) {
		integerReceiver = (integerPointer1 >> 1);
		goto l2;
	} else {
		successFlag = false;
		integerReceiver = 1;
		goto l2;
	}
l2:	/* end popInteger */;
	/* begin checkBooleanResult:from: */
	if (successFlag) {
		/* begin pushBool: */
		if (integerReceiver > integerArgument) {
			/* begin push: */
			longAtput(sp = stackPointer + 4, trueObj);
			stackPointer = sp;
		} else {
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, falseObj);
			stackPointer = sp1;
		}
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
		failSpecialPrim(4);
	}
}

int primitiveImageName(void) {
    int sz;
    int s;
    int sp;
    int ccIndex;
    int cl;
    int hdr;
    int totalLength;
    int fmt;
    int fixedFields;
    int sz1;
    int classFormat;
    int class;
    int ccIndex1;

	if (argumentCount == 1) {
		s = longAt(stackPointer);
		/* begin assertClassOf:is: */
		if ((s & 1)) {
			successFlag = false;
			goto l1;
		}
		ccIndex = (((unsigned) (longAt(s))) >> 12) & 31;
		if (ccIndex == 0) {
			cl = (longAt(s - 4)) & 4294967292U;
		} else {
			cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
		}
		/* begin success: */
		successFlag = (cl == (longAt(((((char *) specialObjectsOop)) + 4) + (6 << 2)))) && successFlag;
	l1:	/* end assertClassOf:is: */;
		if (successFlag) {
			/* begin stSizeOf: */
			hdr = longAt(s);
			fmt = (((unsigned) hdr) >> 8) & 15;
			/* begin lengthOf:baseHeader:format: */
			if ((hdr & 3) == 0) {
				sz1 = (longAt(s - 8)) & 4294967292U;
			} else {
				sz1 = hdr & 252;
			}
			if (fmt < 8) {
				totalLength = ((unsigned) (sz1 - 4)) >> 2;
				goto l4;
			} else {
				totalLength = (sz1 - 4) - (fmt & 3);
				goto l4;
			}
		l4:	/* end lengthOf:baseHeader:format: */;
			/* begin fixedFieldsOf:format:length: */
			if ((fmt > 3) || (fmt == 2)) {
				fixedFields = 0;
				goto l2;
			}
			if (fmt < 2) {
				fixedFields = totalLength;
				goto l2;
			}
			/* begin fetchClassOf: */
			if ((s & 1)) {
				class = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
				goto l3;
			}
			ccIndex1 = ((((unsigned) (longAt(s))) >> 12) & 31) - 1;
			if (ccIndex1 < 0) {
				class = (longAt(s - 4)) & 4294967292U;
				goto l3;
			} else {
				class = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex1 << 2));
				goto l3;
			}
		l3:	/* end fetchClassOf: */;
			classFormat = (longAt(((((char *) class)) + 4) + (2 << 2))) - 1;
			fixedFields = (((((unsigned) classFormat) >> 11) & 192) + ((((unsigned) classFormat) >> 2) & 63)) - 1;
		l2:	/* end fixedFieldsOf:format:length: */;
			sz = totalLength - fixedFields;
			imageNamePutLength(s + 4, sz);
			/* begin pop: */
			stackPointer -= 1 * 4;
		}
	} else {
		sz = imageNameSize();
		s = instantiateClassindexableSize(longAt(((((char *) specialObjectsOop)) + 4) + (6 << 2)), sz);
		imageNameGetLength(s + 4, sz);
		/* begin pop: */
		stackPointer -= 1 * 4;
		/* begin push: */
		longAtput(sp = stackPointer + 4, s);
		stackPointer = sp;
	}
}

int primitiveIncrementalGC(void) {
    int sp;

	/* begin pop: */
	stackPointer -= 1 * 4;
	incrementalGC();
	/* begin pushInteger: */
	/* begin push: */
	longAtput(sp = stackPointer + 4, ((((longAt(freeBlock)) & 536870908) << 1) | 1));
	stackPointer = sp;
}

int primitiveIndexOf(int methodPointer) {
    int primBits;

	primBits = (((unsigned) (longAt(((((char *) methodPointer)) + 4) + (0 << 2)))) >> 1) & 805306879;
	if (primBits > 511) {
		return (primBits & 511) + (((unsigned) primBits) >> 19);
	} else {
		return primBits;
	}
}

int primitiveInitializeNetwork(void) {
    int err;
    int resolverSemaIndex;
    int integerPointer;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		resolverSemaIndex = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		resolverSemaIndex = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	if (successFlag) {
		err = sqNetworkInit(resolverSemaIndex);
		/* begin success: */
		successFlag = (err == 0) && successFlag;
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
	}
}

int primitiveInputSemaphore(void) {
    int arg;
    int oop;
    int oop1;
    int valuePointer;
    int top;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	arg = top;
	if ((fetchClassOf(arg)) == (longAt(((((char *) specialObjectsOop)) + 4) + (18 << 2)))) {
		/* begin storePointer:ofObject:withValue: */
		oop = specialObjectsOop;
		if (oop < youngStart) {
			possibleRootStoreIntovalue(oop, arg);
		}
		longAtput(((((char *) oop)) + 4) + (22 << 2), arg);
	} else {
		/* begin storePointer:ofObject:withValue: */
		oop1 = specialObjectsOop;
		valuePointer = nilObj;
		if (oop1 < youngStart) {
			possibleRootStoreIntovalue(oop1, valuePointer);
		}
		longAtput(((((char *) oop1)) + 4) + (22 << 2), valuePointer);
	}
}

int primitiveInputWord(void) {
    int sp;

	/* begin pop: */
	stackPointer -= 1 * 4;
	/* begin pushInteger: */
	/* begin push: */
	longAtput(sp = stackPointer + 4, ((0 << 1) | 1));
	stackPointer = sp;
}

int primitiveInstVarAt(void) {
    int value;
    int hdr;
    int totalLength;
    int index;
    int fmt;
    int rcvr;
    int fixedFields;
    int sz;
    int sp;
    int integerPointer;
    int top;
    int top1;
    int classFormat;
    int class;
    int ccIndex;

	/* begin popInteger */
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top;
	if ((integerPointer & 1)) {
		index = (integerPointer >> 1);
		goto l3;
	} else {
		successFlag = false;
		index = 1;
		goto l3;
	}
l3:	/* end popInteger */;
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	rcvr = top1;
	if (successFlag) {
		hdr = longAt(rcvr);
		fmt = (((unsigned) hdr) >> 8) & 15;
		/* begin lengthOf:baseHeader:format: */
		if ((hdr & 3) == 0) {
			sz = (longAt(rcvr - 8)) & 4294967292U;
		} else {
			sz = hdr & 252;
		}
		if (fmt < 8) {
			totalLength = ((unsigned) (sz - 4)) >> 2;
			goto l1;
		} else {
			totalLength = (sz - 4) - (fmt & 3);
			goto l1;
		}
	l1:	/* end lengthOf:baseHeader:format: */;
		/* begin fixedFieldsOf:format:length: */
		if ((fmt > 3) || (fmt == 2)) {
			fixedFields = 0;
			goto l4;
		}
		if (fmt < 2) {
			fixedFields = totalLength;
			goto l4;
		}
		/* begin fetchClassOf: */
		if ((rcvr & 1)) {
			class = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
			goto l5;
		}
		ccIndex = ((((unsigned) (longAt(rcvr))) >> 12) & 31) - 1;
		if (ccIndex < 0) {
			class = (longAt(rcvr - 4)) & 4294967292U;
			goto l5;
		} else {
			class = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
			goto l5;
		}
	l5:	/* end fetchClassOf: */;
		classFormat = (longAt(((((char *) class)) + 4) + (2 << 2))) - 1;
		fixedFields = (((((unsigned) classFormat) >> 11) & 192) + ((((unsigned) classFormat) >> 2) & 63)) - 1;
	l4:	/* end fixedFieldsOf:format:length: */;
		if (!((index >= 1) && (index <= fixedFields))) {
			successFlag = false;
		}
	}
	if (successFlag) {
		/* begin subscript:with:format: */
		if (fmt < 4) {
			value = longAt(((((char *) rcvr)) + 4) + ((index - 1) << 2));
			goto l2;
		}
		if (fmt < 8) {
			value = positive32BitIntegerFor(longAt(((((char *) rcvr)) + 4) + ((index - 1) << 2)));
			goto l2;
		} else {
			value = (((byteAt(((((char *) rcvr)) + 4) + (index - 1))) << 1) | 1);
			goto l2;
		}
	l2:	/* end subscript:with:format: */;
	}
	if (successFlag) {
		/* begin push: */
		longAtput(sp = stackPointer + 4, value);
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
	}
}

int primitiveInstVarAtPut(void) {
    int hdr;
    int newValue;
    int totalLength;
    int index;
    int fmt;
    int rcvr;
    int fixedFields;
    int sp;
    int top;
    int top1;
    int sz;
    int valueToStore;
    int integerPointer;
    int top2;
    int classFormat;
    int class;
    int ccIndex;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	newValue = top;
	/* begin popInteger */
	/* begin popStack */
	top2 = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top2;
	if ((integerPointer & 1)) {
		index = (integerPointer >> 1);
		goto l2;
	} else {
		successFlag = false;
		index = 1;
		goto l2;
	}
l2:	/* end popInteger */;
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	rcvr = top1;
	if (successFlag) {
		hdr = longAt(rcvr);
		fmt = (((unsigned) hdr) >> 8) & 15;
		/* begin lengthOf:baseHeader:format: */
		if ((hdr & 3) == 0) {
			sz = (longAt(rcvr - 8)) & 4294967292U;
		} else {
			sz = hdr & 252;
		}
		if (fmt < 8) {
			totalLength = ((unsigned) (sz - 4)) >> 2;
			goto l1;
		} else {
			totalLength = (sz - 4) - (fmt & 3);
			goto l1;
		}
	l1:	/* end lengthOf:baseHeader:format: */;
		/* begin fixedFieldsOf:format:length: */
		if ((fmt > 3) || (fmt == 2)) {
			fixedFields = 0;
			goto l3;
		}
		if (fmt < 2) {
			fixedFields = totalLength;
			goto l3;
		}
		/* begin fetchClassOf: */
		if ((rcvr & 1)) {
			class = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
			goto l4;
		}
		ccIndex = ((((unsigned) (longAt(rcvr))) >> 12) & 31) - 1;
		if (ccIndex < 0) {
			class = (longAt(rcvr - 4)) & 4294967292U;
			goto l4;
		} else {
			class = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
			goto l4;
		}
	l4:	/* end fetchClassOf: */;
		classFormat = (longAt(((((char *) class)) + 4) + (2 << 2))) - 1;
		fixedFields = (((((unsigned) classFormat) >> 11) & 192) + ((((unsigned) classFormat) >> 2) & 63)) - 1;
	l3:	/* end fixedFieldsOf:format:length: */;
		if (!((index >= 1) && (index <= fixedFields))) {
			successFlag = false;
		}
	}
	if (successFlag) {
		/* begin subscript:with:storing:format: */
		if (fmt < 4) {
			/* begin storePointer:ofObject:withValue: */
			if (rcvr < youngStart) {
				possibleRootStoreIntovalue(rcvr, newValue);
			}
			longAtput(((((char *) rcvr)) + 4) + ((index - 1) << 2), newValue);
		} else {
			if (fmt < 8) {
				valueToStore = positive32BitValueOf(newValue);
				if (successFlag) {
					longAtput(((((char *) rcvr)) + 4) + ((index - 1) << 2), valueToStore);
				}
			} else {
				if (!((newValue & 1))) {
					successFlag = false;
				}
				valueToStore = (newValue >> 1);
				if (!((valueToStore >= 0) && (valueToStore <= 255))) {
					successFlag = false;
				}
				if (successFlag) {
					byteAtput(((((char *) rcvr)) + 4) + (index - 1), valueToStore);
				}
			}
		}
	}
	if (successFlag) {
		/* begin push: */
		longAtput(sp = stackPointer + 4, newValue);
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 3 * 4;
	}
}

int primitiveInterruptSemaphore(void) {
    int arg;
    int oop;
    int oop1;
    int valuePointer;
    int top;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	arg = top;
	if ((fetchClassOf(arg)) == (longAt(((((char *) specialObjectsOop)) + 4) + (18 << 2)))) {
		/* begin storePointer:ofObject:withValue: */
		oop = specialObjectsOop;
		if (oop < youngStart) {
			possibleRootStoreIntovalue(oop, arg);
		}
		longAtput(((((char *) oop)) + 4) + (30 << 2), arg);
	} else {
		/* begin storePointer:ofObject:withValue: */
		oop1 = specialObjectsOop;
		valuePointer = nilObj;
		if (oop1 < youngStart) {
			possibleRootStoreIntovalue(oop1, valuePointer);
		}
		longAtput(((((char *) oop1)) + 4) + (30 << 2), valuePointer);
	}
}

int primitiveKbdNext(void) {
    int keystrokeWord;
    int sp;
    int sp1;

	/* begin pop: */
	stackPointer -= 1 * 4;
	keystrokeWord = ioGetKeystroke();
	if (keystrokeWord >= 0) {
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp1 = stackPointer + 4, ((keystrokeWord << 1) | 1));
		stackPointer = sp1;
	} else {
		/* begin push: */
		longAtput(sp = stackPointer + 4, nilObj);
		stackPointer = sp;
	}
}

int primitiveKbdPeek(void) {
    int keystrokeWord;
    int sp;
    int sp1;

	/* begin pop: */
	stackPointer -= 1 * 4;
	keystrokeWord = ioPeekKeystroke();
	if (keystrokeWord >= 0) {
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp1 = stackPointer + 4, ((keystrokeWord << 1) | 1));
		stackPointer = sp1;
	} else {
		/* begin push: */
		longAtput(sp = stackPointer + 4, nilObj);
		stackPointer = sp;
	}
}

int primitiveLessOrEqual(void) {
    int integerReceiver;
    int integerArgument;
    int integerPointer;
    int top;
    int integerPointer1;
    int top1;
    int sp;
    int sp1;

	successFlag = true;
	/* begin popInteger */
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top;
	if ((integerPointer & 1)) {
		integerArgument = (integerPointer >> 1);
		goto l1;
	} else {
		successFlag = false;
		integerArgument = 1;
		goto l1;
	}
l1:	/* end popInteger */;
	/* begin popInteger */
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer1 = top1;
	if ((integerPointer1 & 1)) {
		integerReceiver = (integerPointer1 >> 1);
		goto l2;
	} else {
		successFlag = false;
		integerReceiver = 1;
		goto l2;
	}
l2:	/* end popInteger */;
	/* begin checkBooleanResult:from: */
	if (successFlag) {
		/* begin pushBool: */
		if (integerReceiver <= integerArgument) {
			/* begin push: */
			longAtput(sp = stackPointer + 4, trueObj);
			stackPointer = sp;
		} else {
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, falseObj);
			stackPointer = sp1;
		}
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
		failSpecialPrim(5);
	}
}

int primitiveLessThan(void) {
    int integerReceiver;
    int integerArgument;
    int integerPointer;
    int top;
    int integerPointer1;
    int top1;
    int sp;
    int sp1;

	successFlag = true;
	/* begin popInteger */
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top;
	if ((integerPointer & 1)) {
		integerArgument = (integerPointer >> 1);
		goto l1;
	} else {
		successFlag = false;
		integerArgument = 1;
		goto l1;
	}
l1:	/* end popInteger */;
	/* begin popInteger */
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer1 = top1;
	if ((integerPointer1 & 1)) {
		integerReceiver = (integerPointer1 >> 1);
		goto l2;
	} else {
		successFlag = false;
		integerReceiver = 1;
		goto l2;
	}
l2:	/* end popInteger */;
	/* begin checkBooleanResult:from: */
	if (successFlag) {
		/* begin pushBool: */
		if (integerReceiver < integerArgument) {
			/* begin push: */
			longAtput(sp = stackPointer + 4, trueObj);
			stackPointer = sp;
		} else {
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, falseObj);
			stackPointer = sp1;
		}
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
		failSpecialPrim(3);
	}
}

int primitiveLoadInstVar(void) {
    int thisReceiver;
    int top;
    int sp;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	thisReceiver = top;
	/* begin push: */
	longAtput(sp = stackPointer + 4, longAt(((((char *) thisReceiver)) + 4) + ((primitiveIndex - 264) << 2)));
	stackPointer = sp;
}

int primitiveLogN(void) {
    double rcvr;

	rcvr = popFloat();
	if (successFlag) {
		pushFloat(log(rcvr));
	} else {
		/* begin unPop: */
		stackPointer += 1 * 4;
	}
}

int primitiveLowSpaceSemaphore(void) {
    int arg;
    int oop;
    int oop1;
    int valuePointer;
    int top;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	arg = top;
	if ((fetchClassOf(arg)) == (longAt(((((char *) specialObjectsOop)) + 4) + (18 << 2)))) {
		/* begin storePointer:ofObject:withValue: */
		oop = specialObjectsOop;
		if (oop < youngStart) {
			possibleRootStoreIntovalue(oop, arg);
		}
		longAtput(((((char *) oop)) + 4) + (17 << 2), arg);
	} else {
		/* begin storePointer:ofObject:withValue: */
		oop1 = specialObjectsOop;
		valuePointer = nilObj;
		if (oop1 < youngStart) {
			possibleRootStoreIntovalue(oop1, valuePointer);
		}
		longAtput(((((char *) oop1)) + 4) + (17 << 2), valuePointer);
	}
}

int primitiveMIDIClosePort(void) {
    int portNum;
    int integerPointer;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		portNum = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		portNum = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	if (successFlag) {
		sqMIDIClosePort(portNum);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
	}
}

int primitiveMIDIGetClock(void) {
    int clockValue;
    int sp;

	clockValue = (sqMIDIGetClock()) & 536870911;
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, ((clockValue << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveMIDIGetPortCount(void) {
    int n;
    int sp;

	n = sqMIDIGetPortCount();
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, ((n << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveMIDIGetPortDirectionality(void) {
    int dir;
    int portNum;
    int integerPointer;
    int sp;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		portNum = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		portNum = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	if (successFlag) {
		dir = sqMIDIGetPortDirectionality(portNum);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 2 * 4;
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, ((dir << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveMIDIGetPortName(void) {
    char portName[256];
    int portNum;
    int sz;
    int nameObj;
    int namePtr;
    int sp;
    int integerPointer;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		portNum = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		portNum = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	if (successFlag) {
		sz = sqMIDIGetPortName(portNum, (int) &portName, 255);
	}
	if (successFlag) {
		nameObj = instantiateClassindexableSize(longAt(((((char *) specialObjectsOop)) + 4) + (6 << 2)), sz);
		namePtr = nameObj + 4;
		memcpy((char *) namePtr, portName, sz);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 2 * 4;
		/* begin push: */
		longAtput(sp = stackPointer + 4, nameObj);
		stackPointer = sp;
	}
}

int primitiveMIDIOpenPort(void) {
    int semaIndex;
    int portNum;
    int clockRate;
    int integerPointer;
    int integerPointer1;
    int integerPointer2;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		clockRate = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		clockRate = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (1 * 4));
	if ((integerPointer1 & 1)) {
		semaIndex = (integerPointer1 >> 1);
		goto l2;
	} else {
		primitiveFail();
		semaIndex = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer2 = longAt(stackPointer - (2 * 4));
	if ((integerPointer2 & 1)) {
		portNum = (integerPointer2 >> 1);
		goto l3;
	} else {
		primitiveFail();
		portNum = 0;
		goto l3;
	}
l3:	/* end stackIntegerValue: */;
	if (successFlag) {
		sqMIDIOpenPort(portNum, semaIndex, clockRate);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 3 * 4;
	}
}

int primitiveMIDIParameterGetOrSet(void) {
    int whichParameter;
    int newValue;
    int currentValue;
    int sp;
    int integerPointer;
    int integerPointer1;
    int integerPointer2;

	if (argumentCount == 1) {
		/* begin stackIntegerValue: */
		integerPointer = longAt(stackPointer - (0 * 4));
		if ((integerPointer & 1)) {
			whichParameter = (integerPointer >> 1);
			goto l1;
		} else {
			primitiveFail();
			whichParameter = 0;
			goto l1;
		}
	l1:	/* end stackIntegerValue: */;
		if (!(successFlag)) {
			return null;
		}
		currentValue = sqMIDIParameter(whichParameter, false, 0);
		if (successFlag) {
			/* begin pop: */
			stackPointer -= 2 * 4;
			/* begin pushInteger: */
			/* begin push: */
			longAtput(sp = stackPointer + 4, ((currentValue << 1) | 1));
			stackPointer = sp;
		}
		return null;
	}
	if (argumentCount == 2) {
		/* begin stackIntegerValue: */
		integerPointer1 = longAt(stackPointer - (0 * 4));
		if ((integerPointer1 & 1)) {
			newValue = (integerPointer1 >> 1);
			goto l2;
		} else {
			primitiveFail();
			newValue = 0;
			goto l2;
		}
	l2:	/* end stackIntegerValue: */;
		/* begin stackIntegerValue: */
		integerPointer2 = longAt(stackPointer - (1 * 4));
		if ((integerPointer2 & 1)) {
			whichParameter = (integerPointer2 >> 1);
			goto l3;
		} else {
			primitiveFail();
			whichParameter = 0;
			goto l3;
		}
	l3:	/* end stackIntegerValue: */;
		if (!(successFlag)) {
			return null;
		}
		sqMIDIParameter(whichParameter, true, newValue);
		if (successFlag) {
			/* begin pop: */
			stackPointer -= 2 * 4;
		}
		return null;
	}
	primitiveFail();
}

int primitiveMIDIRead(void) {
    int array;
    int portNum;
    int arrayLength;
    int bytesRead;
    int fmt;
    int sz;
    int header;
    int fmt1;
    int sp;
    int integerPointer;
    int successValue;

	array = longAt(stackPointer - (0 * 4));
	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (1 * 4));
	if ((integerPointer & 1)) {
		portNum = (integerPointer >> 1);
		goto l2;
	} else {
		primitiveFail();
		portNum = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	fmt = (((unsigned) (longAt(array))) >> 8) & 15;
	/* begin success: */
	successValue = (fmt >= 8) && (fmt <= 11);
	successFlag = successValue && successFlag;
	if (successFlag) {
		/* begin lengthOf: */
		header = longAt(array);
		if ((header & 3) == 0) {
			sz = (longAt(array - 8)) & 4294967292U;
		} else {
			sz = header & 252;
		}
		fmt1 = (((unsigned) header) >> 8) & 15;
		if (fmt1 < 8) {
			arrayLength = ((unsigned) (sz - 4)) >> 2;
			goto l1;
		} else {
			arrayLength = (sz - 4) - (fmt1 & 3);
			goto l1;
		}
	l1:	/* end lengthOf: */;
		bytesRead = sqMIDIPortReadInto(portNum, arrayLength, array + 4);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 3 * 4;
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, ((bytesRead << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveMIDIWrite(void) {
    int array;
    int portNum;
    int arrayLength;
    int time;
    int bytesWritten;
    int fmt;
    int sz;
    int header;
    int fmt1;
    int sp;
    int integerPointer;
    int integerPointer1;
    int successValue;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		time = (integerPointer >> 1);
		goto l2;
	} else {
		primitiveFail();
		time = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	array = longAt(stackPointer - (1 * 4));
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (2 * 4));
	if ((integerPointer1 & 1)) {
		portNum = (integerPointer1 >> 1);
		goto l3;
	} else {
		primitiveFail();
		portNum = 0;
		goto l3;
	}
l3:	/* end stackIntegerValue: */;
	fmt = (((unsigned) (longAt(array))) >> 8) & 15;
	/* begin success: */
	successValue = (fmt >= 8) && (fmt <= 11);
	successFlag = successValue && successFlag;
	if (successFlag) {
		/* begin lengthOf: */
		header = longAt(array);
		if ((header & 3) == 0) {
			sz = (longAt(array - 8)) & 4294967292U;
		} else {
			sz = header & 252;
		}
		fmt1 = (((unsigned) header) >> 8) & 15;
		if (fmt1 < 8) {
			arrayLength = ((unsigned) (sz - 4)) >> 2;
			goto l1;
		} else {
			arrayLength = (sz - 4) - (fmt1 & 3);
			goto l1;
		}
	l1:	/* end lengthOf: */;
		bytesWritten = sqMIDIPortWriteFromAt(portNum, arrayLength, array + 4, time);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 4 * 4;
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, ((bytesWritten << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveMakePoint(void) {
    int integerReceiver;
    int integerArgument;
    int object;
    int sp;
    int integerPointer;
    int top;
    int integerPointer1;
    int top1;
    int pointResult;
    int sp1;

	successFlag = true;
	/* begin popInteger */
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top;
	if ((integerPointer & 1)) {
		integerArgument = (integerPointer >> 1);
		goto l1;
	} else {
		successFlag = false;
		integerArgument = 1;
		goto l1;
	}
l1:	/* end popInteger */;
	/* begin popInteger */
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer1 = top1;
	if ((integerPointer1 & 1)) {
		integerReceiver = (integerPointer1 >> 1);
		goto l2;
	} else {
		successFlag = false;
		integerReceiver = 1;
		goto l2;
	}
l2:	/* end popInteger */;
	if (successFlag) {
		/* begin push: */
		/* begin makePointwithxValue:yValue: */
		pointResult = instantiateSmallClasssizeInBytesfill(longAt(((((char *) specialObjectsOop)) + 4) + (12 << 2)), 12, nilObj);
		/* begin storePointer:ofObject:withValue: */
		if (pointResult < youngStart) {
			possibleRootStoreIntovalue(pointResult, ((integerReceiver << 1) | 1));
		}
		longAtput(((((char *) pointResult)) + 4) + (0 << 2), ((integerReceiver << 1) | 1));
		/* begin storePointer:ofObject:withValue: */
		if (pointResult < youngStart) {
			possibleRootStoreIntovalue(pointResult, ((integerArgument << 1) | 1));
		}
		longAtput(((((char *) pointResult)) + 4) + (1 << 2), ((integerArgument << 1) | 1));
		object = pointResult;
		longAtput(sp = stackPointer + 4, object);
		stackPointer = sp;
	} else {
		/* begin checkIntegerResult:from: */
		if (successFlag && ((0 ^ (0 << 1)) >= 0)) {
			/* begin pushInteger: */
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, ((0 << 1) | 1));
			stackPointer = sp1;
		} else {
			/* begin unPop: */
			stackPointer += 2 * 4;
			failSpecialPrim(18);
		}
	}
}

int primitiveMillisecondClock(void) {
    int object;
    int sp;

	/* begin pop: */
	stackPointer -= 1 * 4;
	/* begin push: */
	object = ((((ioMSecs()) & 536870911) << 1) | 1);
	longAtput(sp = stackPointer + 4, object);
	stackPointer = sp;
}

int primitiveMod(void) {
    int integerReceiver;
    int integerArgument;
    int integerResult;
    int integerPointer;
    int top;
    int integerPointer1;
    int top1;
    int sp;

	successFlag = true;
	/* begin popInteger */
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top;
	if ((integerPointer & 1)) {
		integerArgument = (integerPointer >> 1);
		goto l1;
	} else {
		successFlag = false;
		integerArgument = 1;
		goto l1;
	}
l1:	/* end popInteger */;
	/* begin popInteger */
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer1 = top1;
	if ((integerPointer1 & 1)) {
		integerReceiver = (integerPointer1 >> 1);
		goto l2;
	} else {
		successFlag = false;
		integerReceiver = 1;
		goto l2;
	}
l2:	/* end popInteger */;
	/* begin success: */
	successFlag = (integerArgument != 0) && successFlag;
	if (!(successFlag)) {
		integerArgument = 1;
	}
	integerResult = integerReceiver % integerArgument;
	if (integerArgument < 0) {
		if (integerResult > 0) {
			integerResult += integerArgument;
		}
	} else {
		if (integerResult < 0) {
			integerResult += integerArgument;
		}
	}
	/* begin checkIntegerResult:from: */
	if (successFlag && ((integerResult ^ (integerResult << 1)) >= 0)) {
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, ((integerResult << 1) | 1));
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
		failSpecialPrim(11);
	}
}

int primitiveMouseButtons(void) {
    int buttonWord;
    int sp;

	/* begin pop: */
	stackPointer -= 1 * 4;
	buttonWord = ioGetButtonState();
	/* begin pushInteger: */
	/* begin push: */
	longAtput(sp = stackPointer + 4, ((buttonWord << 1) | 1));
	stackPointer = sp;
}

int primitiveMousePoint(void) {
    int y;
    int pointWord;
    int x;
    int object;
    int sp;
    int pointResult;

	/* begin pop: */
	stackPointer -= 1 * 4;
	pointWord = ioMousePoint();
	/* begin signExtend16: */
	if ((((((unsigned) pointWord) >> 16) & 65535) & 32768) == 0) {
		x = (((unsigned) pointWord) >> 16) & 65535;
		goto l1;
	} else {
		x = ((((unsigned) pointWord) >> 16) & 65535) - 65536;
		goto l1;
	}
l1:	/* end signExtend16: */;
	/* begin signExtend16: */
	if (((pointWord & 65535) & 32768) == 0) {
		y = pointWord & 65535;
		goto l2;
	} else {
		y = (pointWord & 65535) - 65536;
		goto l2;
	}
l2:	/* end signExtend16: */;
	/* begin push: */
	/* begin makePointwithxValue:yValue: */
	pointResult = instantiateSmallClasssizeInBytesfill(longAt(((((char *) specialObjectsOop)) + 4) + (12 << 2)), 12, nilObj);
	/* begin storePointer:ofObject:withValue: */
	if (pointResult < youngStart) {
		possibleRootStoreIntovalue(pointResult, ((x << 1) | 1));
	}
	longAtput(((((char *) pointResult)) + 4) + (0 << 2), ((x << 1) | 1));
	/* begin storePointer:ofObject:withValue: */
	if (pointResult < youngStart) {
		possibleRootStoreIntovalue(pointResult, ((y << 1) | 1));
	}
	longAtput(((((char *) pointResult)) + 4) + (1 << 2), ((y << 1) | 1));
	object = pointResult;
	longAtput(sp = stackPointer + 4, object);
	stackPointer = sp;
}

int primitiveMultiply(void) {
    int arg;
    int result;
    int rcvr;
    int successValue;
    int sp;

	rcvr = longAt(stackPointer - (1 * 4));
	arg = longAt(stackPointer - (0 * 4));
	/* begin pop: */
	stackPointer -= 2 * 4;
	/* begin success: */
	successFlag = (((rcvr & arg) & 1) != 0) && successFlag;
	if (successFlag) {
		rcvr = (rcvr >> 1);
		arg = (arg >> 1);
		result = rcvr * arg;
		/* begin success: */
		successValue = (arg == 0) || ((result / arg) == rcvr);
		successFlag = successValue && successFlag;
	}
	/* begin checkIntegerResult:from: */
	if (successFlag && ((result ^ (result << 1)) >= 0)) {
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, ((result << 1) | 1));
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
		failSpecialPrim(9);
	}
}

int primitiveNew(void) {
    int spaceOkay;
    int class;
    int object;
    int sp;
    int top;
    int okay;
    int format;
    int minFree;
    int minFree1;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	class = top;
	/* begin sufficientSpaceToInstantiate:indexableSize: */
	format = (((unsigned) ((longAt(((((char *) class)) + 4) + (2 << 2))) - 1)) >> 8) & 15;
	if ((0 > 0) && (format < 2)) {
		spaceOkay = false;
		goto l3;
	}
	if (format < 8) {
		/* begin sufficientSpaceToAllocate: */
		minFree = (lowSpaceThreshold + (2500 + (0 * 4))) + 4;
		if (((longAt(freeBlock)) & 536870908) >= minFree) {
			okay = true;
			goto l1;
		} else {
			okay = sufficientSpaceAfterGC(minFree);
			goto l1;
		}
	l1:	/* end sufficientSpaceToAllocate: */;
	} else {
		/* begin sufficientSpaceToAllocate: */
		minFree1 = (lowSpaceThreshold + (2500 + 0)) + 4;
		if (((longAt(freeBlock)) & 536870908) >= minFree1) {
			okay = true;
			goto l2;
		} else {
			okay = sufficientSpaceAfterGC(minFree1);
			goto l2;
		}
	l2:	/* end sufficientSpaceToAllocate: */;
	}
	spaceOkay = okay;
l3:	/* end sufficientSpaceToInstantiate:indexableSize: */;
	/* begin success: */
	successFlag = spaceOkay && successFlag;
	if (successFlag) {
		/* begin push: */
		object = instantiateClassindexableSize(class, 0);
		longAtput(sp = stackPointer + 4, object);
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 1 * 4;
	}
}

int primitiveNewMethod(void) {
    int size;
    int i;
    int header;
    int theMethod;
    int bytecodeCount;
    int class;
    int literalCount;
    int valuePointer;
    int top;
    int top1;
    int sp;
    int integerPointer;
    int top2;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	header = top;
	/* begin popInteger */
	/* begin popStack */
	top2 = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top2;
	if ((integerPointer & 1)) {
		bytecodeCount = (integerPointer >> 1);
		goto l1;
	} else {
		successFlag = false;
		bytecodeCount = 1;
		goto l1;
	}
l1:	/* end popInteger */;
	/* begin success: */
	successFlag = ((header & 1)) && successFlag;
	if (!(successFlag)) {
		/* begin unPop: */
		stackPointer += 2 * 4;
	}
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	class = top1;
	size = ((((((unsigned) header) >> 10) & 255) + 1) * 4) + bytecodeCount;
	theMethod = instantiateClassindexableSize(class, size);
	/* begin storePointer:ofObject:withValue: */
	if (theMethod < youngStart) {
		possibleRootStoreIntovalue(theMethod, header);
	}
	longAtput(((((char *) theMethod)) + 4) + (0 << 2), header);
	literalCount = (((unsigned) header) >> 10) & 255;
	for (i = 1; i <= literalCount; i += 1) {
		/* begin storePointer:ofObject:withValue: */
		valuePointer = nilObj;
		if (theMethod < youngStart) {
			possibleRootStoreIntovalue(theMethod, valuePointer);
		}
		longAtput(((((char *) theMethod)) + 4) + (i << 2), valuePointer);
	}
	/* begin push: */
	longAtput(sp = stackPointer + 4, theMethod);
	stackPointer = sp;
}

int primitiveNewWithArg(void) {
    int spaceOkay;
    int size;
    int class;
    int top;
    int object;
    int sp;
    int integerPointer;
    int top1;
    int okay;
    int format;
    int minFree;
    int minFree1;

	/* begin popInteger */
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top1;
	if ((integerPointer & 1)) {
		size = (integerPointer >> 1);
		goto l1;
	} else {
		successFlag = false;
		size = 1;
		goto l1;
	}
l1:	/* end popInteger */;
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	class = top;
	/* begin success: */
	successFlag = (size >= 0) && successFlag;
	if (successFlag) {
		/* begin sufficientSpaceToInstantiate:indexableSize: */
		format = (((unsigned) ((longAt(((((char *) class)) + 4) + (2 << 2))) - 1)) >> 8) & 15;
		if ((size > 0) && (format < 2)) {
			spaceOkay = false;
			goto l4;
		}
		if (format < 8) {
			/* begin sufficientSpaceToAllocate: */
			minFree = (lowSpaceThreshold + (2500 + (size * 4))) + 4;
			if (((longAt(freeBlock)) & 536870908) >= minFree) {
				okay = true;
				goto l3;
			} else {
				okay = sufficientSpaceAfterGC(minFree);
				goto l3;
			}
		l3:	/* end sufficientSpaceToAllocate: */;
		} else {
			/* begin sufficientSpaceToAllocate: */
			minFree1 = (lowSpaceThreshold + (2500 + size)) + 4;
			if (((longAt(freeBlock)) & 536870908) >= minFree1) {
				okay = true;
				goto l2;
			} else {
				okay = sufficientSpaceAfterGC(minFree1);
				goto l2;
			}
		l2:	/* end sufficientSpaceToAllocate: */;
		}
		spaceOkay = okay;
	l4:	/* end sufficientSpaceToInstantiate:indexableSize: */;
		/* begin success: */
		successFlag = spaceOkay && successFlag;
	}
	if (successFlag) {
		/* begin push: */
		object = instantiateClassindexableSize(class, size);
		longAtput(sp = stackPointer + 4, object);
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
	}
}

int primitiveNext(void) {
    int array;
    int stream;
    int stringy;
    int arrayClass;
    int index;
    int limit;
    int result;
    int successValue;
    int ccIndex;
    int oop;
    int sp;
    int sp1;
    int top;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	stream = top;
	successFlag = (((((unsigned) (longAt(stream))) >> 8) & 15) <= 4) && ((lengthOf(stream)) >= (2 + 1));
	if (successFlag) {
		array = longAt(((((char *) stream)) + 4) + (0 << 2));
		index = fetchIntegerofObject(1, stream);
		limit = fetchIntegerofObject(2, stream);
		/* begin fetchClassOf: */
		if ((array & 1)) {
			arrayClass = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
			goto l1;
		}
		ccIndex = ((((unsigned) (longAt(array))) >> 12) & 31) - 1;
		if (ccIndex < 0) {
			arrayClass = (longAt(array - 4)) & 4294967292U;
			goto l1;
		} else {
			arrayClass = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
			goto l1;
		}
	l1:	/* end fetchClassOf: */;
		stringy = arrayClass == (longAt(((((char *) specialObjectsOop)) + 4) + (6 << 2)));
		if (!(stringy)) {
			/* begin success: */
			successValue = (arrayClass == (longAt(((((char *) specialObjectsOop)) + 4) + (6 << 2)))) || ((arrayClass == (longAt(((((char *) specialObjectsOop)) + 4) + (7 << 2)))) || ((arrayClass == (longAt(((((char *) specialObjectsOop)) + 4) + (26 << 2)))) || (arrayClass == (longAt(((((char *) specialObjectsOop)) + 4) + (4 << 2))))));
			successFlag = successValue && successFlag;
		}
		/* begin success: */
		successFlag = (index < limit) && successFlag;
	}
	if (successFlag) {
		index += 1;
		/* begin pushRemappableOop: */
		remapBuffer[remapBufferCount += 1] = stream;
		result = stObjectat(array, index);
		/* begin popRemappableOop */
		oop = remapBuffer[remapBufferCount];
		remapBufferCount -= 1;
		stream = oop;
	}
	if (successFlag) {
		/* begin storeInteger:ofObject:withValue: */
		if ((index ^ (index << 1)) >= 0) {
			longAtput(((((char *) stream)) + 4) + (1 << 2), ((index << 1) | 1));
		} else {
			primitiveFail();
		}
	}
	if (successFlag) {
		if (stringy) {
			/* begin push: */
			longAtput(sp = stackPointer + 4, longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (24 << 2))))) + 4) + (((result >> 1)) << 2)));
			stackPointer = sp;
		} else {
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, result);
			stackPointer = sp1;
		}
	} else {
		/* begin unPop: */
		stackPointer += 1 * 4;
	}
}

int primitiveNextInstance(void) {
    int object;
    int instance;
    int sp;
    int top;
    int thisClass;
    int classPointer;
    int thisObj;
    int ccIndex;
    int ccIndex1;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	object = top;
	/* begin instanceAfter: */
	/* begin fetchClassOf: */
	if ((object & 1)) {
		classPointer = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
		goto l3;
	}
	ccIndex1 = ((((unsigned) (longAt(object))) >> 12) & 31) - 1;
	if (ccIndex1 < 0) {
		classPointer = (longAt(object - 4)) & 4294967292U;
		goto l3;
	} else {
		classPointer = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex1 << 2));
		goto l3;
	}
l3:	/* end fetchClassOf: */;
	thisObj = accessibleObjectAfter(object);
	while (!(thisObj == null)) {
		/* begin fetchClassOf: */
		if ((thisObj & 1)) {
			thisClass = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
			goto l2;
		}
		ccIndex = ((((unsigned) (longAt(thisObj))) >> 12) & 31) - 1;
		if (ccIndex < 0) {
			thisClass = (longAt(thisObj - 4)) & 4294967292U;
			goto l2;
		} else {
			thisClass = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
			goto l2;
		}
	l2:	/* end fetchClassOf: */;
		if (thisClass == classPointer) {
			instance = thisObj;
			goto l1;
		}
		thisObj = accessibleObjectAfter(thisObj);
	}
	instance = nilObj;
l1:	/* end instanceAfter: */;
	if (instance == nilObj) {
		/* begin unPop: */
		stackPointer += 1 * 4;
		primitiveFail();
	} else {
		/* begin push: */
		longAtput(sp = stackPointer + 4, instance);
		stackPointer = sp;
	}
}

int primitiveNextObject(void) {
    int object;
    int instance;
    int sp;
    int top;
    int sp1;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	object = top;
	instance = accessibleObjectAfter(object);
	if (instance == null) {
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp1 = stackPointer + 4, ((0 << 1) | 1));
		stackPointer = sp1;
	} else {
		/* begin push: */
		longAtput(sp = stackPointer + 4, instance);
		stackPointer = sp;
	}
}

int primitiveNextPut(void) {
    int array;
    int stream;
    int storeVal;
    int value;
    int arrayClass;
    int index;
    int limit;
    int successValue;
    int sp;
    int top;
    int top1;
    int ccIndex;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	value = top;
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	stream = top1;
	successFlag = (((((unsigned) (longAt(stream))) >> 8) & 15) <= 4) && ((lengthOf(stream)) >= (3 + 1));
	if (successFlag) {
		array = longAt(((((char *) stream)) + 4) + (0 << 2));
		index = fetchIntegerofObject(1, stream);
		limit = fetchIntegerofObject(3, stream);
		/* begin fetchClassOf: */
		if ((array & 1)) {
			arrayClass = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
			goto l1;
		}
		ccIndex = ((((unsigned) (longAt(array))) >> 12) & 31) - 1;
		if (ccIndex < 0) {
			arrayClass = (longAt(array - 4)) & 4294967292U;
			goto l1;
		} else {
			arrayClass = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
			goto l1;
		}
	l1:	/* end fetchClassOf: */;
		/* begin success: */
		successValue = (arrayClass == (longAt(((((char *) specialObjectsOop)) + 4) + (6 << 2)))) || ((arrayClass == (longAt(((((char *) specialObjectsOop)) + 4) + (7 << 2)))) || ((arrayClass == (longAt(((((char *) specialObjectsOop)) + 4) + (26 << 2)))) || (arrayClass == (longAt(((((char *) specialObjectsOop)) + 4) + (4 << 2))))));
		successFlag = successValue && successFlag;
		/* begin success: */
		successFlag = (index < limit) && successFlag;
	}
	if (successFlag) {
		index += 1;
		if (arrayClass == (longAt(((((char *) specialObjectsOop)) + 4) + (6 << 2)))) {
			storeVal = asciiOfCharacter(value);
		} else {
			storeVal = value;
		}
		stObjectatput(array, index, storeVal);
	}
	if (successFlag) {
		/* begin storeInteger:ofObject:withValue: */
		if ((index ^ (index << 1)) >= 0) {
			longAtput(((((char *) stream)) + 4) + (1 << 2), ((index << 1) | 1));
		} else {
			primitiveFail();
		}
	}
	if (successFlag) {
		/* begin push: */
		longAtput(sp = stackPointer + 4, value);
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
	}
}

int primitiveNoop(void) {
	/* begin pop: */
	stackPointer -= argumentCount * 4;
}

int primitiveNotEqual(void) {
    int integerReceiver;
    int integerArgument;
    int result;
    int top;
    int top1;
    int sp;
    int sp1;

	successFlag = true;
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	integerArgument = top;
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	integerReceiver = top1;
	result = !(compare31or32Bitsequal(integerReceiver, integerArgument));
	/* begin checkBooleanResult:from: */
	if (successFlag) {
		/* begin pushBool: */
		if (result) {
			/* begin push: */
			longAtput(sp = stackPointer + 4, trueObj);
			stackPointer = sp;
		} else {
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, falseObj);
			stackPointer = sp1;
		}
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
		failSpecialPrim(8);
	}
}

int primitiveObjectAt(void) {
    int thisReceiver;
    int index;
    int sp;
    int integerPointer;
    int top;
    int top1;

	/* begin popInteger */
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top;
	if ((integerPointer & 1)) {
		index = (integerPointer >> 1);
		goto l1;
	} else {
		successFlag = false;
		index = 1;
		goto l1;
	}
l1:	/* end popInteger */;
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	thisReceiver = top1;
	/* begin success: */
	successFlag = (index > 0) && successFlag;
	/* begin success: */
	successFlag = (index <= (((((unsigned) (longAt(((((char *) thisReceiver)) + 4) + (0 << 2)))) >> 10) & 255) + 1)) && successFlag;
	if (successFlag) {
		/* begin push: */
		longAtput(sp = stackPointer + 4, longAt(((((char *) thisReceiver)) + 4) + ((index - 1) << 2)));
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
	}
}

int primitiveObjectAtPut(void) {
    int thisReceiver;
    int newValue;
    int index;
    int sp;
    int top;
    int integerPointer;
    int top1;
    int top2;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	newValue = top;
	/* begin popInteger */
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top1;
	if ((integerPointer & 1)) {
		index = (integerPointer >> 1);
		goto l1;
	} else {
		successFlag = false;
		index = 1;
		goto l1;
	}
l1:	/* end popInteger */;
	/* begin popStack */
	top2 = longAt(stackPointer);
	stackPointer -= 4;
	thisReceiver = top2;
	/* begin success: */
	successFlag = (index > 0) && successFlag;
	/* begin success: */
	successFlag = (index <= (((((unsigned) (longAt(((((char *) thisReceiver)) + 4) + (0 << 2)))) >> 10) & 255) + 1)) && successFlag;
	if (successFlag) {
		/* begin storePointer:ofObject:withValue: */
		if (thisReceiver < youngStart) {
			possibleRootStoreIntovalue(thisReceiver, newValue);
		}
		longAtput(((((char *) thisReceiver)) + 4) + ((index - 1) << 2), newValue);
		/* begin push: */
		longAtput(sp = stackPointer + 4, newValue);
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 3 * 4;
	}
}

int primitiveObjectPointsTo(void) {
    int i;
    int thang;
    int lastField;
    int rcvr;
    int top;
    int top1;
    int sp;
    int sp1;
    int sp2;
    int sp3;
    int sp4;
    int sp5;
    int methodHeader;
    int sz;
    int fmt;
    int header;
    int type;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	thang = top;
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	rcvr = top1;
	if ((rcvr & 1)) {
		/* begin pushBool: */
		if (false) {
			/* begin push: */
			longAtput(sp = stackPointer + 4, trueObj);
			stackPointer = sp;
		} else {
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, falseObj);
			stackPointer = sp1;
		}
		return null;
	}
	/* begin lastPointerOf: */
	fmt = (((unsigned) (longAt(rcvr))) >> 8) & 15;
	if (fmt < 4) {
		/* begin sizeBitsOfSafe: */
		header = longAt(rcvr);
		/* begin rightType: */
		if ((header & 252) == 0) {
			type = 0;
			goto l2;
		} else {
			if ((header & 126976) == 0) {
				type = 1;
				goto l2;
			} else {
				type = 3;
				goto l2;
			}
		}
	l2:	/* end rightType: */;
		if (type == 0) {
			sz = (longAt(rcvr - 8)) & 4294967292U;
			goto l3;
		} else {
			sz = header & 252;
			goto l3;
		}
	l3:	/* end sizeBitsOfSafe: */;
		lastField = sz - 4;
		goto l1;
	}
	if (fmt < 12) {
		lastField = 0;
		goto l1;
	}
	methodHeader = longAt(rcvr + 4);
	lastField = (((((unsigned) methodHeader) >> 10) & 255) * 4) + 4;
l1:	/* end lastPointerOf: */;
	for (i = 4; i <= lastField; i += 4) {
		if ((longAt(rcvr + i)) == thang) {
			/* begin pushBool: */
			if (true) {
				/* begin push: */
				longAtput(sp2 = stackPointer + 4, trueObj);
				stackPointer = sp2;
			} else {
				/* begin push: */
				longAtput(sp3 = stackPointer + 4, falseObj);
				stackPointer = sp3;
			}
			return null;
		}
	}
	/* begin pushBool: */
	if (false) {
		/* begin push: */
		longAtput(sp4 = stackPointer + 4, trueObj);
		stackPointer = sp4;
	} else {
		/* begin push: */
		longAtput(sp5 = stackPointer + 4, falseObj);
		stackPointer = sp5;
	}
}

int primitivePerform(void) {
    int performSelector;
    int selectorIndex;
    int newReceiver;
    int toIndex;
    int fromIndex;
    int lastFrom;

	performSelector = messageSelector;
	messageSelector = longAt(stackPointer - ((argumentCount - 1) * 4));
	newReceiver = longAt(stackPointer - (argumentCount * 4));
	argumentCount -= 1;
	lookupMethodInClass(fetchClassOf(newReceiver));
	/* begin success: */
	successFlag = (((((unsigned) (longAt(((((char *) newMethod)) + 4) + (0 << 2)))) >> 25) & 31) == argumentCount) && successFlag;
	if (successFlag) {
		selectorIndex = (((unsigned) ((stackPointer - activeContext) - 4)) >> 2) - argumentCount;
		/* begin transfer:fromIndex:ofObject:toIndex:ofObject: */
		fromIndex = activeContext + ((selectorIndex + 1) * 4);
		toIndex = activeContext + (selectorIndex * 4);
		lastFrom = fromIndex + (argumentCount * 4);
		while (fromIndex < lastFrom) {
			fromIndex += 4;
			toIndex += 4;
			longAtput(toIndex, longAt(fromIndex));
		}
		/* begin pop: */
		stackPointer -= 1 * 4;
		/* begin executeNewMethod */
		if ((primitiveIndex == 0) || (!(primitiveResponse()))) {
			activateNewMethod();
			/* begin quickCheckForInterrupts */
			if ((interruptCheckCounter -= 1) <= 0) {
				checkForInterrupts();
			}
		}
		successFlag = true;
	} else {
		argumentCount += 1;
		messageSelector = performSelector;
	}
}

int primitivePerformWithArgs(void) {
    int argumentArray;
    int performSelector;
    int arraySize;
    int thisReceiver;
    int index;
    int cntxSize;
    int sp;
    int sp1;
    int sp2;
    int top;
    int top1;
    int sz;
    int objectPointer;
    int sz1;
    int header;
    int header1;
    int ccIndex;
    int cl;

	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	argumentArray = top1;
	/* begin fetchWordLengthOf: */
	/* begin sizeBitsOf: */
	header = longAt(argumentArray);
	if ((header & 3) == 0) {
		sz = (longAt(argumentArray - 8)) & 4294967292U;
		goto l1;
	} else {
		sz = header & 252;
		goto l1;
	}
l1:	/* end sizeBitsOf: */;
	arraySize = ((unsigned) (sz - 4)) >> 2;
	/* begin fetchWordLengthOf: */
	objectPointer = activeContext;
	/* begin sizeBitsOf: */
	header1 = longAt(objectPointer);
	if ((header1 & 3) == 0) {
		sz1 = (longAt(objectPointer - 8)) & 4294967292U;
		goto l2;
	} else {
		sz1 = header1 & 252;
		goto l2;
	}
l2:	/* end sizeBitsOf: */;
	cntxSize = ((unsigned) (sz1 - 4)) >> 2;
	/* begin success: */
	successFlag = (((((unsigned) ((stackPointer - activeContext) - 4)) >> 2) + arraySize) < cntxSize) && successFlag;
	/* begin assertClassOf:is: */
	if ((argumentArray & 1)) {
		successFlag = false;
		goto l3;
	}
	ccIndex = (((unsigned) (longAt(argumentArray))) >> 12) & 31;
	if (ccIndex == 0) {
		cl = (longAt(argumentArray - 4)) & 4294967292U;
	} else {
		cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
	}
	/* begin success: */
	successFlag = (cl == (longAt(((((char *) specialObjectsOop)) + 4) + (7 << 2)))) && successFlag;
l3:	/* end assertClassOf:is: */;
	if (successFlag) {
		performSelector = messageSelector;
		/* begin popStack */
		top = longAt(stackPointer);
		stackPointer -= 4;
		messageSelector = top;
		thisReceiver = longAt(stackPointer);
		argumentCount = arraySize;
		index = 1;
		while (index <= argumentCount) {
			/* begin push: */
			longAtput(sp = stackPointer + 4, longAt(((((char *) argumentArray)) + 4) + ((index - 1) << 2)));
			stackPointer = sp;
			index += 1;
		}
		lookupMethodInClass(fetchClassOf(thisReceiver));
		/* begin success: */
		successFlag = (((((unsigned) (longAt(((((char *) newMethod)) + 4) + (0 << 2)))) >> 25) & 31) == argumentCount) && successFlag;
		if (successFlag) {
			/* begin executeNewMethod */
			if ((primitiveIndex == 0) || (!(primitiveResponse()))) {
				activateNewMethod();
				/* begin quickCheckForInterrupts */
				if ((interruptCheckCounter -= 1) <= 0) {
					checkForInterrupts();
				}
			}
			successFlag = true;
		} else {
			/* begin pop: */
			stackPointer -= argumentCount * 4;
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, messageSelector);
			stackPointer = sp1;
			/* begin push: */
			longAtput(sp2 = stackPointer + 4, argumentArray);
			stackPointer = sp2;
			argumentCount = 2;
			messageSelector = performSelector;
		}
	} else {
		/* begin unPop: */
		stackPointer += 1 * 4;
	}
}

int primitivePointX(void) {
    int rcvr;
    int sp;
    int top;
    int ccIndex;
    int cl;

	successFlag = true;
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	rcvr = top;
	/* begin assertClassOf:is: */
	if ((rcvr & 1)) {
		successFlag = false;
		goto l1;
	}
	ccIndex = (((unsigned) (longAt(rcvr))) >> 12) & 31;
	if (ccIndex == 0) {
		cl = (longAt(rcvr - 4)) & 4294967292U;
	} else {
		cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
	}
	/* begin success: */
	successFlag = (cl == (longAt(((((char *) specialObjectsOop)) + 4) + (12 << 2)))) && successFlag;
l1:	/* end assertClassOf:is: */;
	if (successFlag) {
		/* begin push: */
		longAtput(sp = stackPointer + 4, longAt(((((char *) rcvr)) + 4) + (0 << 2)));
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 1 * 4;
		failSpecialPrim(0);
	}
}

int primitivePointY(void) {
    int rcvr;
    int sp;
    int top;
    int ccIndex;
    int cl;

	successFlag = true;
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	rcvr = top;
	/* begin assertClassOf:is: */
	if ((rcvr & 1)) {
		successFlag = false;
		goto l1;
	}
	ccIndex = (((unsigned) (longAt(rcvr))) >> 12) & 31;
	if (ccIndex == 0) {
		cl = (longAt(rcvr - 4)) & 4294967292U;
	} else {
		cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
	}
	/* begin success: */
	successFlag = (cl == (longAt(((((char *) specialObjectsOop)) + 4) + (12 << 2)))) && successFlag;
l1:	/* end assertClassOf:is: */;
	if (successFlag) {
		/* begin push: */
		longAtput(sp = stackPointer + 4, longAt(((((char *) rcvr)) + 4) + (1 << 2)));
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 1 * 4;
		failSpecialPrim(0);
	}
}

int primitivePushFalse(void) {
    int top;
    int sp;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	/* begin push: */
	longAtput(sp = stackPointer + 4, falseObj);
	stackPointer = sp;
}

int primitivePushMinusOne(void) {
    int top;
    int sp;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	/* begin push: */
	longAtput(sp = stackPointer + 4, 4294967295U);
	stackPointer = sp;
}

int primitivePushNil(void) {
    int top;
    int sp;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	/* begin push: */
	longAtput(sp = stackPointer + 4, nilObj);
	stackPointer = sp;
}

int primitivePushOne(void) {
    int top;
    int sp;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	/* begin push: */
	longAtput(sp = stackPointer + 4, 3);
	stackPointer = sp;
}

int primitivePushSelf(void) {
}

int primitivePushTrue(void) {
    int top;
    int sp;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	/* begin push: */
	longAtput(sp = stackPointer + 4, trueObj);
	stackPointer = sp;
}

int primitivePushTwo(void) {
    int top;
    int sp;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	/* begin push: */
	longAtput(sp = stackPointer + 4, 5);
	stackPointer = sp;
}

int primitivePushZero(void) {
    int top;
    int sp;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	/* begin push: */
	longAtput(sp = stackPointer + 4, 1);
	stackPointer = sp;
}

int primitiveQuit(void) {
	ioExit();
}

int primitiveQuo(void) {
    int arg;
    int result;
    int rcvr;
    int sp;
    int integerPointer;
    int top;
    int integerPointer1;
    int top1;

	/* begin popInteger */
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top;
	if ((integerPointer & 1)) {
		arg = (integerPointer >> 1);
		goto l1;
	} else {
		successFlag = false;
		arg = 1;
		goto l1;
	}
l1:	/* end popInteger */;
	/* begin popInteger */
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer1 = top1;
	if ((integerPointer1 & 1)) {
		rcvr = (integerPointer1 >> 1);
		goto l2;
	} else {
		successFlag = false;
		rcvr = 1;
		goto l2;
	}
l2:	/* end popInteger */;
	/* begin success: */
	successFlag = (arg != 0) && successFlag;
	if (successFlag) {
		if (rcvr > 0) {
			if (arg > 0) {
				result = rcvr / arg;
			} else {
				result = 0 - (rcvr / (0 - arg));
			}
		} else {
			if (arg > 0) {
				result = 0 - ((0 - rcvr) / arg);
			} else {
				result = (0 - rcvr) / (0 - arg);
			}
		}
		/* begin success: */
		successFlag = ((result ^ (result << 1)) >= 0) && successFlag;
	}
	if (successFlag) {
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, ((result << 1) | 1));
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
	}
}

int primitiveReadJoystick(void) {
    int index;
    int object;
    int sp;
    int integerPointer;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		index = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		index = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 2 * 4;
		/* begin push: */
		object = positive32BitIntegerFor(joystickRead(index));
		longAtput(sp = stackPointer + 4, object);
		stackPointer = sp;
	}
}

int primitiveRelinquishProcessor(void) {
    int microSecs;
    int integerPointer;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		microSecs = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		microSecs = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	if (successFlag) {
		ioRelinquishProcessorForMicroseconds(microSecs);
		/* begin pop: */
		stackPointer -= 1 * 4;
	}
}

int primitiveResolverAbortLookup(void) {
	sqResolverAbort();
}

int primitiveResolverAddressLookupResult(void) {
    int sz;
    int s;
    int sp;

	sz = sqResolverAddrLookupResultSize();
	if (successFlag) {
		s = instantiateClassindexableSize(longAt(((((char *) specialObjectsOop)) + 4) + (6 << 2)), sz);
		sqResolverAddrLookupResult(((char *) (s + 4)), sz);
	}
	if (successFlag) {
		/* begin pop:thenPush: */
		longAtput(sp = stackPointer - ((1 - 1) * 4), s);
		stackPointer = sp;
	}
}

int primitiveResolverError(void) {
    int err;
    int sp;

	err = sqResolverError();
	if (successFlag) {
		/* begin pop:thenPush: */
		longAtput(sp = stackPointer - ((1 - 1) * 4), ((err << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveResolverLocalAddress(void) {
    int addr;
    int oop;
    int sp;

	addr = sqResolverLocalAddress();
	if (successFlag) {
		/* begin pop:thenPush: */
		oop = intToNetAddress(addr);
		longAtput(sp = stackPointer - ((1 - 1) * 4), oop);
		stackPointer = sp;
	}
}

int primitiveResolverNameLookupResult(void) {
    int addr;
    int oop;
    int sp;

	addr = sqResolverNameLookupResult();
	if (successFlag) {
		/* begin pop:thenPush: */
		oop = intToNetAddress(addr);
		longAtput(sp = stackPointer - ((1 - 1) * 4), oop);
		stackPointer = sp;
	}
}

int primitiveResolverStartAddressLookup(void) {
    int addr;

	addr = netAddressToInt(longAt(stackPointer));
	if (successFlag) {
		sqResolverStartAddrLookup(addr);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
	}
}

int primitiveResolverStartNameLookup(void) {
    int sz;
    int name;
    int sz1;
    int header;
    int fmt;
    int ccIndex;
    int cl;

	name = longAt(stackPointer);
	/* begin assertClassOf:is: */
	if ((name & 1)) {
		successFlag = false;
		goto l2;
	}
	ccIndex = (((unsigned) (longAt(name))) >> 12) & 31;
	if (ccIndex == 0) {
		cl = (longAt(name - 4)) & 4294967292U;
	} else {
		cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
	}
	/* begin success: */
	successFlag = (cl == (longAt(((((char *) specialObjectsOop)) + 4) + (6 << 2)))) && successFlag;
l2:	/* end assertClassOf:is: */;
	if (successFlag) {
		/* begin lengthOf: */
		header = longAt(name);
		if ((header & 3) == 0) {
			sz1 = (longAt(name - 8)) & 4294967292U;
		} else {
			sz1 = header & 252;
		}
		fmt = (((unsigned) header) >> 8) & 15;
		if (fmt < 8) {
			sz = ((unsigned) (sz1 - 4)) >> 2;
			goto l1;
		} else {
			sz = (sz1 - 4) - (fmt & 3);
			goto l1;
		}
	l1:	/* end lengthOf: */;
		sqResolverStartNameLookup(((char *) (name + 4)), sz);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
	}
}

int primitiveResolverStatus(void) {
    int status;
    int sp;

	status = sqResolverStatus();
	if (successFlag) {
		/* begin pop:thenPush: */
		longAtput(sp = stackPointer - ((1 - 1) * 4), ((status << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveResponse(void) {
    int startTime;

	if (primitiveIndex > 700) {
		return false;
	}
	if (nextWakeupTick != 0) {
		startTime = ioLowResMSecs();
	}
	successFlag = true;
	switch (primitiveIndex) {
	case 0:
		primitiveFail();
		break;
	case 1:
		primitiveAdd();
		break;
	case 2:
		primitiveSubtract();
		break;
	case 3:
		primitiveLessThan();
		break;
	case 4:
		primitiveGreaterThan();
		break;
	case 5:
		primitiveLessOrEqual();
		break;
	case 6:
		primitiveGreaterOrEqual();
		break;
	case 7:
		primitiveEqual();
		break;
	case 8:
		primitiveNotEqual();
		break;
	case 9:
		primitiveMultiply();
		break;
	case 10:
		primitiveDivide();
		break;
	case 11:
		primitiveMod();
		break;
	case 12:
		primitiveDiv();
		break;
	case 13:
		primitiveQuo();
		break;
	case 14:
		primitiveBitAnd();
		break;
	case 15:
		primitiveBitOr();
		break;
	case 16:
		primitiveBitXor();
		break;
	case 17:
		primitiveBitShift();
		break;
	case 18:
		primitiveMakePoint();
		break;
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
		primitiveFail();
		break;
	case 40:
		primitiveAsFloat();
		break;
	case 41:
		primitiveFloatAdd();
		break;
	case 42:
		primitiveFloatSubtract();
		break;
	case 43:
		primitiveFloatLessThan();
		break;
	case 44:
		primitiveFloatGreaterThan();
		break;
	case 45:
		primitiveFloatLessOrEqual();
		break;
	case 46:
		primitiveFloatGreaterOrEqual();
		break;
	case 47:
		primitiveFloatEqual();
		break;
	case 48:
		primitiveFloatNotEqual();
		break;
	case 49:
		primitiveFloatMultiply();
		break;
	case 50:
		primitiveFloatDivide();
		break;
	case 51:
		primitiveTruncated();
		break;
	case 52:
		primitiveFractionalPart();
		break;
	case 53:
		primitiveExponent();
		break;
	case 54:
		primitiveTimesTwoPower();
		break;
	case 55:
		primitiveSquareRoot();
		break;
	case 56:
		primitiveSine();
		break;
	case 57:
		primitiveArctan();
		break;
	case 58:
		primitiveLogN();
		break;
	case 59:
		primitiveExp();
		break;
	case 60:
		primitiveAt();
		break;
	case 61:
		primitiveAtPut();
		break;
	case 62:
		primitiveSize();
		break;
	case 63:
		primitiveStringAt();
		break;
	case 64:
		primitiveStringAtPut();
		break;
	case 65:
		primitiveNext();
		break;
	case 66:
		primitiveNextPut();
		break;
	case 67:
		primitiveAtEnd();
		break;
	case 68:
		primitiveObjectAt();
		break;
	case 69:
		primitiveObjectAtPut();
		break;
	case 70:
		primitiveNew();
		break;
	case 71:
		primitiveNewWithArg();
		break;
	case 72:
		primitiveFail();
		break;
	case 73:
		primitiveInstVarAt();
		break;
	case 74:
		primitiveInstVarAtPut();
		break;
	case 75:
		primitiveAsOop();
		break;
	case 76:
		primitiveFail();
		break;
	case 77:
		primitiveSomeInstance();
		break;
	case 78:
		primitiveNextInstance();
		break;
	case 79:
		primitiveNewMethod();
		break;
	case 80:
		primitiveFail();
		break;
	case 81:
		primitiveValue();
		break;
	case 82:
		primitiveValueWithArgs();
		break;
	case 83:
		primitivePerform();
		break;
	case 84:
		primitivePerformWithArgs();
		break;
	case 85:
		primitiveSignal();
		break;
	case 86:
		primitiveWait();
		break;
	case 87:
		primitiveResume();
		break;
	case 88:
		primitiveSuspend();
		break;
	case 89:
		primitiveFlushCache();
		break;
	case 90:
		primitiveMousePoint();
		break;
	case 91:
	case 92:
		primitiveFail();
		break;
	case 93:
		primitiveInputSemaphore();
		break;
	case 94:
		primitiveFail();
		break;
	case 95:
		primitiveInputWord();
		break;
	case 96:
		primitiveCopyBits();
		break;
	case 97:
		primitiveSnapshot();
		break;
	case 98:
	case 99:
	case 100:
		primitiveFail();
		break;
	case 101:
		primitiveBeCursor();
		break;
	case 102:
		primitiveBeDisplay();
		break;
	case 103:
		primitiveScanCharacters();
		break;
	case 104:
		primitiveDrawLoop();
		break;
	case 105:
		primitiveStringReplace();
		break;
	case 106:
		primitiveScreenSize();
		break;
	case 107:
		primitiveMouseButtons();
		break;
	case 108:
		primitiveKbdNext();
		break;
	case 109:
		primitiveKbdPeek();
		break;
	case 110:
		primitiveEquivalent();
		break;
	case 111:
		primitiveClass();
		break;
	case 112:
		primitiveBytesLeft();
		break;
	case 113:
		primitiveQuit();
		break;
	case 114:
		primitiveExitToDebugger();
		break;
	case 115:
	case 116:
	case 117:
		primitiveFail();
		break;
	case 118:
		primitiveDoPrimitiveWithArgs();
		break;
	case 119:
		primitiveFlushCacheSelective();
		break;
	case 120:
		primitiveFail();
		break;
	case 121:
		primitiveImageName();
		break;
	case 122:
		primitiveNoop();
		break;
	case 123:
		primitiveFail();
		break;
	case 124:
		primitiveLowSpaceSemaphore();
		break;
	case 125:
		primitiveSignalAtBytesLeft();
		break;
	case 126:
		primitiveDeferDisplayUpdates();
		break;
	case 127:
		primitiveShowDisplayRect();
		break;
	case 128:
		primitiveArrayBecome();
		break;
	case 129:
		primitiveSpecialObjectsOop();
		break;
	case 130:
		primitiveFullGC();
		break;
	case 131:
		primitiveIncrementalGC();
		break;
	case 132:
		primitiveObjectPointsTo();
		break;
	case 133:
		primitiveSetInterruptKey();
		break;
	case 134:
		primitiveInterruptSemaphore();
		break;
	case 135:
		primitiveMillisecondClock();
		break;
	case 136:
		primitiveSignalAtMilliseconds();
		break;
	case 137:
		primitiveSecondsClock();
		break;
	case 138:
		primitiveSomeObject();
		break;
	case 139:
		primitiveNextObject();
		break;
	case 140:
		primitiveBeep();
		break;
	case 141:
		primitiveClipboardText();
		break;
	case 142:
		primitiveVMPath();
		break;
	case 143:
		primitiveShortAt();
		break;
	case 144:
		primitiveShortAtPut();
		break;
	case 145:
		primitiveConstantFill();
		break;
	case 146:
		primitiveReadJoystick();
		break;
	case 147:
		primitiveWarpBits();
		break;
	case 148:
		primitiveClone();
		break;
	case 149:
		primitiveGetAttribute();
		break;
	case 150:
		primitiveFileAtEnd();
		break;
	case 151:
		primitiveFileClose();
		break;
	case 152:
		primitiveFileGetPosition();
		break;
	case 153:
		primitiveFileOpen();
		break;
	case 154:
		primitiveFileRead();
		break;
	case 155:
		primitiveFileSetPosition();
		break;
	case 156:
		primitiveFileDelete();
		break;
	case 157:
		primitiveFileSize();
		break;
	case 158:
		primitiveFileWrite();
		break;
	case 159:
		primitiveFileRename();
		break;
	case 160:
		primitiveDirectoryCreate();
		break;
	case 161:
		primitiveDirectoryDelimitor();
		break;
	case 162:
		primitiveDirectoryLookup();
		break;
	case 163:
	case 164:
	case 165:
	case 166:
	case 167:
	case 168:
		primitiveFail();
		break;
	case 169:
		primitiveDirectorySetMacTypeAndCreator();
		break;
	case 170:
		primitiveSoundStart();
		break;
	case 171:
		primitiveSoundStartWithSemaphore();
		break;
	case 172:
		primitiveSoundStop();
		break;
	case 173:
		primitiveSoundAvailableSpace();
		break;
	case 174:
		primitiveSoundPlaySamples();
		break;
	case 175:
		primitiveSoundPlaySilence();
		break;
	case 176:
		primWaveTableSoundmixSampleCountintostartingAtpan();
		break;
	case 177:
		primFMSoundmixSampleCountintostartingAtpan();
		break;
	case 178:
		primPluckedSoundmixSampleCountintostartingAtpan();
		break;
	case 179:
		primSampledSoundmixSampleCountintostartingAtpan();
		break;
	case 180:
		primFMSoundmixSampleCountintostartingAtleftVolrightVol();
		break;
	case 181:
		primPluckedSoundmixSampleCountintostartingAtleftVolrightVol();
		break;
	case 182:
		primSampledSoundmixSampleCountintostartingAtleftVolrightVol();
		break;
	case 183:
		primReverbSoundapplyReverbTostartingAtcount();
		break;
	case 184:
		primLoopedSampledSoundmixSampleCountintostartingAtleftVolrightVol();
		break;
	case 185:
	case 186:
	case 187:
	case 188:
		primitiveFail();
		break;
	case 189:
		primitiveSoundInsertSamples();
		break;
	case 190:
		primitiveSoundStartRecording();
		break;
	case 191:
		primitiveSoundStopRecording();
		break;
	case 192:
		primitiveSoundGetRecordingSampleRate();
		break;
	case 193:
		primitiveSoundRecordSamples();
		break;
	case 194:
		primitiveSoundSetRecordLevel();
		break;
	case 195:
	case 196:
	case 197:
	case 198:
	case 199:
		primitiveFail();
		break;
	case 200:
		primitiveInitializeNetwork();
		break;
	case 201:
		primitiveResolverStartNameLookup();
		break;
	case 202:
		primitiveResolverNameLookupResult();
		break;
	case 203:
		primitiveResolverStartAddressLookup();
		break;
	case 204:
		primitiveResolverAddressLookupResult();
		break;
	case 205:
		primitiveResolverAbortLookup();
		break;
	case 206:
		primitiveResolverLocalAddress();
		break;
	case 207:
		primitiveResolverStatus();
		break;
	case 208:
		primitiveResolverError();
		break;
	case 209:
		primitiveSocketCreate();
		break;
	case 210:
		primitiveSocketDestroy();
		break;
	case 211:
		primitiveSocketConnectionStatus();
		break;
	case 212:
		primitiveSocketError();
		break;
	case 213:
		primitiveSocketLocalAddress();
		break;
	case 214:
		primitiveSocketLocalPort();
		break;
	case 215:
		primitiveSocketRemoteAddress();
		break;
	case 216:
		primitiveSocketRemotePort();
		break;
	case 217:
		primitiveSocketConnectToPort();
		break;
	case 218:
		primitiveSocketListenOnPort();
		break;
	case 219:
		primitiveSocketCloseConnection();
		break;
	case 220:
		primitiveSocketAbortConnection();
		break;
	case 221:
		primitiveSocketReceiveDataBufCount();
		break;
	case 222:
		primitiveSocketReceiveDataAvailable();
		break;
	case 223:
		primitiveSocketSendDataBufCount();
		break;
	case 224:
		primitiveSocketSendDone();
		break;
	case 225:
	case 226:
	case 227:
	case 228:
	case 229:
		primitiveFail();
		break;
	case 230:
		primitiveRelinquishProcessor();
		break;
	case 231:
		primitiveForceDisplayUpdate();
		break;
	case 232:
		primitiveFormPrint();
		break;
	case 233:
		primitiveSetFullScreen();
		break;
	case 234:
		primBitmapdecompressfromByteArrayat();
		break;
	case 235:
		primStringcomparewithcollated();
		break;
	case 236:
		primSampledSoundconvert8bitSignedFromto16Bit();
		break;
	case 237:
		primBitmapcompresstoByteArray();
		break;
	case 238:
		primitiveSerialPortOpen();
		break;
	case 239:
		primitiveSerialPortClose();
		break;
	case 240:
		primitiveSerialPortWrite();
		break;
	case 241:
		primitiveSerialPortRead();
		break;
	case 242:
		primitiveFail();
		break;
	case 243:
		primStringtranslatefromtotable();
		break;
	case 244:
		primStringfindFirstInStringinSetstartingAt();
		break;
	case 245:
		primStringindexOfAsciiinStringstartingAt();
		break;
	case 246:
	case 247:
	case 248:
	case 249:
		primitiveFail();
		break;
	case 250:
		clearProfile();
		break;
	case 251:
		dumpProfile();
		break;
	case 252:
		startProfiling();
		break;
	case 253:
		stopProfiling();
		break;
	case 254:
		primitiveVMParameter();
		break;
	case 255:
		primitiveFail();
		break;
	case 256:
		primitivePushSelf();
		break;
	case 257:
		primitivePushTrue();
		break;
	case 258:
		primitivePushFalse();
		break;
	case 259:
		primitivePushNil();
		break;
	case 260:
		primitivePushMinusOne();
		break;
	case 261:
		primitivePushZero();
		break;
	case 262:
		primitivePushOne();
		break;
	case 263:
		primitivePushTwo();
		break;
	case 264:
	case 265:
	case 266:
	case 267:
	case 268:
	case 269:
	case 270:
	case 271:
	case 272:
	case 273:
	case 274:
	case 275:
	case 276:
	case 277:
	case 278:
	case 279:
	case 280:
	case 281:
	case 282:
	case 283:
	case 284:
	case 285:
	case 286:
	case 287:
	case 288:
	case 289:
	case 290:
	case 291:
	case 292:
	case 293:
	case 294:
	case 295:
	case 296:
	case 297:
	case 298:
	case 299:
	case 300:
	case 301:
	case 302:
	case 303:
	case 304:
	case 305:
	case 306:
	case 307:
	case 308:
	case 309:
	case 310:
	case 311:
	case 312:
	case 313:
	case 314:
	case 315:
	case 316:
	case 317:
	case 318:
	case 319:
	case 320:
	case 321:
	case 322:
	case 323:
	case 324:
	case 325:
	case 326:
	case 327:
	case 328:
	case 329:
	case 330:
	case 331:
	case 332:
	case 333:
	case 334:
	case 335:
	case 336:
	case 337:
	case 338:
	case 339:
	case 340:
	case 341:
	case 342:
	case 343:
	case 344:
	case 345:
	case 346:
	case 347:
	case 348:
	case 349:
	case 350:
	case 351:
	case 352:
	case 353:
	case 354:
	case 355:
	case 356:
	case 357:
	case 358:
	case 359:
	case 360:
	case 361:
	case 362:
	case 363:
	case 364:
	case 365:
	case 366:
	case 367:
	case 368:
	case 369:
	case 370:
	case 371:
	case 372:
	case 373:
	case 374:
	case 375:
	case 376:
	case 377:
	case 378:
	case 379:
	case 380:
	case 381:
	case 382:
	case 383:
	case 384:
	case 385:
	case 386:
	case 387:
	case 388:
	case 389:
	case 390:
	case 391:
	case 392:
	case 393:
	case 394:
	case 395:
	case 396:
	case 397:
	case 398:
	case 399:
	case 400:
	case 401:
	case 402:
	case 403:
	case 404:
	case 405:
	case 406:
	case 407:
	case 408:
	case 409:
	case 410:
	case 411:
	case 412:
	case 413:
	case 414:
	case 415:
	case 416:
	case 417:
	case 418:
	case 419:
	case 420:
	case 421:
	case 422:
	case 423:
	case 424:
	case 425:
	case 426:
	case 427:
	case 428:
	case 429:
	case 430:
	case 431:
	case 432:
	case 433:
	case 434:
	case 435:
	case 436:
	case 437:
	case 438:
	case 439:
	case 440:
	case 441:
	case 442:
	case 443:
	case 444:
	case 445:
	case 446:
	case 447:
	case 448:
	case 449:
	case 450:
	case 451:
	case 452:
	case 453:
	case 454:
	case 455:
	case 456:
	case 457:
	case 458:
	case 459:
	case 460:
	case 461:
	case 462:
	case 463:
	case 464:
	case 465:
	case 466:
	case 467:
	case 468:
	case 469:
	case 470:
	case 471:
	case 472:
	case 473:
	case 474:
	case 475:
	case 476:
	case 477:
	case 478:
	case 479:
	case 480:
	case 481:
	case 482:
	case 483:
	case 484:
	case 485:
	case 486:
	case 487:
	case 488:
	case 489:
	case 490:
	case 491:
	case 492:
	case 493:
	case 494:
	case 495:
	case 496:
	case 497:
	case 498:
	case 499:
	case 500:
	case 501:
	case 502:
	case 503:
	case 504:
	case 505:
	case 506:
	case 507:
	case 508:
	case 509:
	case 510:
	case 511:
	case 512:
	case 513:
	case 514:
	case 515:
	case 516:
	case 517:
	case 518:
	case 519:
		primitiveLoadInstVar();
		break;
	case 520:
		primitiveFail();
		break;
	case 521:
		primitiveMIDIClosePort();
		break;
	case 522:
		primitiveMIDIGetClock();
		break;
	case 523:
		primitiveMIDIGetPortCount();
		break;
	case 524:
		primitiveMIDIGetPortDirectionality();
		break;
	case 525:
		primitiveMIDIGetPortName();
		break;
	case 526:
		primitiveMIDIOpenPort();
		break;
	case 527:
		primitiveMIDIParameterGetOrSet();
		break;
	case 528:
		primitiveMIDIRead();
		break;
	case 529:
		primitiveMIDIWrite();
		break;
	case 530:
	case 531:
	case 532:
	case 533:
	case 534:
	case 535:
	case 536:
	case 537:
	case 538:
	case 539:
		primitiveFail();
		break;
	case 540:
		primitiveAsyncFileClose();
		break;
	case 541:
		primitiveAsyncFileOpen();
		break;
	case 542:
		primitiveAsyncFileReadResult();
		break;
	case 543:
		primitiveAsyncFileReadStart();
		break;
	case 544:
		primitiveAsyncFileWriteResult();
		break;
	case 545:
		primitiveAsyncFileWriteStart();
		break;
	case 546:
	case 547:
	case 548:
	case 549:
	case 550:
	case 551:
	case 552:
	case 553:
	case 554:
	case 555:
	case 556:
	case 557:
	case 558:
	case 559:
	case 560:
	case 561:
	case 562:
	case 563:
	case 564:
	case 565:
	case 566:
	case 567:
	case 568:
	case 569:
	case 570:
	case 571:
	case 572:
	case 573:
	case 574:
	case 575:
	case 576:
	case 577:
	case 578:
	case 579:
	case 580:
	case 581:
	case 582:
	case 583:
	case 584:
	case 585:
	case 586:
	case 587:
	case 588:
	case 589:
	case 590:
	case 591:
	case 592:
	case 593:
	case 594:
	case 595:
	case 596:
	case 597:
	case 598:
	case 599:
	case 600:
	case 601:
	case 602:
	case 603:
	case 604:
	case 605:
	case 606:
	case 607:
	case 608:
	case 609:
	case 610:
	case 611:
	case 612:
	case 613:
	case 614:
	case 615:
	case 616:
	case 617:
	case 618:
	case 619:
	case 620:
	case 621:
	case 622:
	case 623:
	case 624:
	case 625:
	case 626:
	case 627:
	case 628:
	case 629:
	case 630:
	case 631:
	case 632:
	case 633:
	case 634:
	case 635:
	case 636:
	case 637:
	case 638:
	case 639:
	case 640:
	case 641:
	case 642:
	case 643:
	case 644:
	case 645:
	case 646:
	case 647:
	case 648:
	case 649:
	case 650:
	case 651:
	case 652:
	case 653:
	case 654:
	case 655:
	case 656:
	case 657:
	case 658:
	case 659:
	case 660:
	case 661:
	case 662:
	case 663:
	case 664:
	case 665:
	case 666:
	case 667:
	case 668:
	case 669:
	case 670:
	case 671:
	case 672:
	case 673:
	case 674:
	case 675:
	case 676:
	case 677:
	case 678:
	case 679:
	case 680:
	case 681:
	case 682:
	case 683:
	case 684:
	case 685:
	case 686:
	case 687:
	case 688:
	case 689:
	case 690:
	case 691:
	case 692:
	case 693:
	case 694:
	case 695:
	case 696:
	case 697:
	case 698:
	case 699:
	case 700:
		primitiveFail();
		break;
	}
	if ((nextWakeupTick != 0) && ((ioLowResMSecs()) != startTime)) {
		if (((ioMSecs()) & 536870911) >= nextWakeupTick) {
			if (successFlag) {
				checkForInterrupts();
			} else {
				interruptCheckCounter = 0;
			}
		}
	}
	return successFlag;
}

int primitiveResume(void) {
    int proc;

	proc = longAt(stackPointer);
	if (successFlag) {
		resume(proc);
	}
}

int primitiveScanCharacters(void) {
    int stopArray;
    int displayFlag;
    int start;
    int stop;
    int string;
    int rcvr;
    int rightX;
    int sp;
    int integerPointer;
    int integerPointer1;
    int integerPointer2;
    int successValue;
    int sourceX2;
    int ascii;
    int top;
    int nextDestX;
    int charVal;
    int left;
    int lastIndex;
    int objectPointer;
    int integerValue;
    int lastIndex1;
    int objectPointer1;
    int objectPointer2;
    int objectPointer3;

	rcvr = longAt(stackPointer - (6 * 4));
	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (5 * 4));
	if ((integerPointer & 1)) {
		start = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		start = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (4 * 4));
	if ((integerPointer1 & 1)) {
		stop = (integerPointer1 >> 1);
		goto l2;
	} else {
		primitiveFail();
		stop = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	string = longAt(stackPointer - (3 * 4));
	/* begin stackIntegerValue: */
	integerPointer2 = longAt(stackPointer - (2 * 4));
	if ((integerPointer2 & 1)) {
		rightX = (integerPointer2 >> 1);
		goto l3;
	} else {
		primitiveFail();
		rightX = 0;
		goto l3;
	}
l3:	/* end stackIntegerValue: */;
	stopArray = longAt(stackPointer - (1 * 4));
	/* begin booleanValueOf: */
	if ((longAt(stackPointer - (0 * 4))) == trueObj) {
		displayFlag = true;
		goto l4;
	}
	if ((longAt(stackPointer - (0 * 4))) == falseObj) {
		displayFlag = false;
		goto l4;
	}
	successFlag = false;
	displayFlag = null;
l4:	/* end booleanValueOf: */;
	if (!(successFlag)) {
		return null;
	}
	/* begin success: */
	successValue = loadScannerFromstartstopstringrightXstopArraydisplayFlag(rcvr, start, stop, string, rightX, stopArray, displayFlag);
	successFlag = successValue && successFlag;
	if (successFlag) {
		/* begin scanCharacters */
		if (scanDisplayFlag) {
			clipRange();
			left = dx;
			top = dy;
		}
		lastIndex = scanStart;
		while (lastIndex <= scanStop) {
			charVal = stObjectat(scanString, lastIndex);
			ascii = (charVal >> 1);
			if (!successFlag) {
				goto l6;
			}
			stopCode = stObjectat(scanStopArray, ascii + 1);
			if (!successFlag) {
				goto l6;
			}
			if (!(stopCode == nilObj)) {
				/* begin returnAt:lastIndex:left:top: */
				stopCode = stObjectat(scanStopArray, ascii + 1);
				if (!successFlag) {
					goto l6;
				}
				/* begin storeInteger:ofObject:withValue: */
				objectPointer1 = bitBltOop;
				if ((lastIndex ^ (lastIndex << 1)) >= 0) {
					longAtput(((((char *) objectPointer1)) + 4) + (15 << 2), ((lastIndex << 1) | 1));
				} else {
					primitiveFail();
				}
				if (scanDisplayFlag) {
					affectedL = left;
					affectedR = bbW + dx;
					affectedT = top;
					affectedB = bbH + dy;
				}
				goto l6;
			}
			sourceX = stObjectat(scanXTable, ascii + 1);
			sourceX2 = stObjectat(scanXTable, ascii + 2);
			if (!successFlag) {
				goto l6;
			}
			if (((sourceX & 1)) && ((sourceX2 & 1))) {
				sourceX = (sourceX >> 1);
				sourceX2 = (sourceX2 >> 1);
			} else {
				primitiveFail();
				goto l6;
			}
			nextDestX = destX + (width = sourceX2 - sourceX);
			if (nextDestX > scanRightX) {
				/* begin returnAt:lastIndex:left:top: */
				stopCode = stObjectat(scanStopArray, 258);
				if (!successFlag) {
					goto l6;
				}
				/* begin storeInteger:ofObject:withValue: */
				objectPointer2 = bitBltOop;
				if ((lastIndex ^ (lastIndex << 1)) >= 0) {
					longAtput(((((char *) objectPointer2)) + 4) + (15 << 2), ((lastIndex << 1) | 1));
				} else {
					primitiveFail();
				}
				if (scanDisplayFlag) {
					affectedL = left;
					affectedR = bbW + dx;
					affectedT = top;
					affectedB = bbH + dy;
				}
				goto l6;
			}
			if (scanDisplayFlag) {
				copyBits();
			}
			destX = nextDestX;
			/* begin storeInteger:ofObject:withValue: */
			objectPointer = bitBltOop;
			integerValue = destX;
			if ((integerValue ^ (integerValue << 1)) >= 0) {
				longAtput(((((char *) objectPointer)) + 4) + (4 << 2), ((integerValue << 1) | 1));
			} else {
				primitiveFail();
			}
			lastIndex += 1;
		}
		/* begin returnAt:lastIndex:left:top: */
		lastIndex1 = scanStop;
		stopCode = stObjectat(scanStopArray, 257);
		if (!successFlag) {
			goto l5;
		}
		/* begin storeInteger:ofObject:withValue: */
		objectPointer3 = bitBltOop;
		if ((lastIndex1 ^ (lastIndex1 << 1)) >= 0) {
			longAtput(((((char *) objectPointer3)) + 4) + (15 << 2), ((lastIndex1 << 1) | 1));
		} else {
			primitiveFail();
		}
		if (scanDisplayFlag) {
			affectedL = left;
			affectedR = bbW + dx;
			affectedT = top;
			affectedB = bbH + dy;
		}
	l5:	/* end returnAt:lastIndex:left:top: */;
	l6:	/* end scanCharacters */;
	}
	if (successFlag) {
		if (displayFlag) {
			showDisplayBits();
		}
		/* begin pop: */
		stackPointer -= 7 * 4;
		/* begin push: */
		longAtput(sp = stackPointer + 4, stopCode);
		stackPointer = sp;
	}
}

int primitiveScreenSize(void) {
    int pointWord;
    int object;
    int sp;
    int pointResult;

	/* begin pop: */
	stackPointer -= 1 * 4;
	pointWord = ioScreenSize();
	/* begin push: */
	/* begin makePointwithxValue:yValue: */
	pointResult = instantiateSmallClasssizeInBytesfill(longAt(((((char *) specialObjectsOop)) + 4) + (12 << 2)), 12, nilObj);
	/* begin storePointer:ofObject:withValue: */
	if (pointResult < youngStart) {
		possibleRootStoreIntovalue(pointResult, ((((((unsigned) pointWord) >> 16) & 65535) << 1) | 1));
	}
	longAtput(((((char *) pointResult)) + 4) + (0 << 2), ((((((unsigned) pointWord) >> 16) & 65535) << 1) | 1));
	/* begin storePointer:ofObject:withValue: */
	if (pointResult < youngStart) {
		possibleRootStoreIntovalue(pointResult, (((pointWord & 65535) << 1) | 1));
	}
	longAtput(((((char *) pointResult)) + 4) + (1 << 2), (((pointWord & 65535) << 1) | 1));
	object = pointResult;
	longAtput(sp = stackPointer + 4, object);
	stackPointer = sp;
}

int primitiveSecondsClock(void) {
    int object;
    int sp;

	/* begin pop: */
	stackPointer -= 1 * 4;
	/* begin push: */
	object = positive32BitIntegerFor(ioSeconds());
	longAtput(sp = stackPointer + 4, object);
	stackPointer = sp;
}

int primitiveSerialPortClose(void) {
    int portNum;
    int integerPointer;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		portNum = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		portNum = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	if (successFlag) {
		serialPortClose(portNum);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
	}
}

int primitiveSerialPortOpen(void) {
    int dataBits;
    int parityType;
    int stopBitsType;
    int portNum;
    int baudRate;
    int xOnChar;
    int xOffChar;
    int inFlowControl;
    int outFlowControl;
    int integerPointer;
    int integerPointer1;
    int integerPointer2;
    int integerPointer3;
    int integerPointer4;
    int integerPointer5;
    int integerPointer6;
    int integerPointer7;
    int integerPointer8;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		xOffChar = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		xOffChar = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (1 * 4));
	if ((integerPointer1 & 1)) {
		xOnChar = (integerPointer1 >> 1);
		goto l2;
	} else {
		primitiveFail();
		xOnChar = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer2 = longAt(stackPointer - (2 * 4));
	if ((integerPointer2 & 1)) {
		outFlowControl = (integerPointer2 >> 1);
		goto l3;
	} else {
		primitiveFail();
		outFlowControl = 0;
		goto l3;
	}
l3:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer3 = longAt(stackPointer - (3 * 4));
	if ((integerPointer3 & 1)) {
		inFlowControl = (integerPointer3 >> 1);
		goto l4;
	} else {
		primitiveFail();
		inFlowControl = 0;
		goto l4;
	}
l4:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer4 = longAt(stackPointer - (4 * 4));
	if ((integerPointer4 & 1)) {
		dataBits = (integerPointer4 >> 1);
		goto l5;
	} else {
		primitiveFail();
		dataBits = 0;
		goto l5;
	}
l5:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer5 = longAt(stackPointer - (5 * 4));
	if ((integerPointer5 & 1)) {
		parityType = (integerPointer5 >> 1);
		goto l6;
	} else {
		primitiveFail();
		parityType = 0;
		goto l6;
	}
l6:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer6 = longAt(stackPointer - (6 * 4));
	if ((integerPointer6 & 1)) {
		stopBitsType = (integerPointer6 >> 1);
		goto l7;
	} else {
		primitiveFail();
		stopBitsType = 0;
		goto l7;
	}
l7:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer7 = longAt(stackPointer - (7 * 4));
	if ((integerPointer7 & 1)) {
		baudRate = (integerPointer7 >> 1);
		goto l8;
	} else {
		primitiveFail();
		baudRate = 0;
		goto l8;
	}
l8:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer8 = longAt(stackPointer - (8 * 4));
	if ((integerPointer8 & 1)) {
		portNum = (integerPointer8 >> 1);
		goto l9;
	} else {
		primitiveFail();
		portNum = 0;
		goto l9;
	}
l9:	/* end stackIntegerValue: */;
	if (successFlag) {
		serialPortOpen(
			portNum, baudRate, stopBitsType, parityType, dataBits,
			inFlowControl, outFlowControl, xOnChar, xOffChar);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 9 * 4;
	}
}

int primitiveSerialPortRead(void) {
    int array;
    int startIndex;
    int portNum;
    int bytesRead;
    int count;
    int fmt;
    int sp;
    int integerPointer;
    int integerPointer1;
    int integerPointer2;
    int successValue;
    int successValue1;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		count = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		count = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (1 * 4));
	if ((integerPointer1 & 1)) {
		startIndex = (integerPointer1 >> 1);
		goto l2;
	} else {
		primitiveFail();
		startIndex = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	array = longAt(stackPointer - (2 * 4));
	/* begin stackIntegerValue: */
	integerPointer2 = longAt(stackPointer - (3 * 4));
	if ((integerPointer2 & 1)) {
		portNum = (integerPointer2 >> 1);
		goto l3;
	} else {
		primitiveFail();
		portNum = 0;
		goto l3;
	}
l3:	/* end stackIntegerValue: */;
	fmt = (((unsigned) (longAt(array))) >> 8) & 15;
	/* begin success: */
	successValue = (fmt >= 8) && (fmt <= 11);
	successFlag = successValue && successFlag;
	/* begin success: */
	successValue1 = (startIndex >= 1) && (((startIndex + count) - 1) <= (lengthOf(array)));
	successFlag = successValue1 && successFlag;
	if (successFlag) {
		bytesRead = serialPortReadInto(portNum, count, ((array + 4) + startIndex) - 1);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 5 * 4;
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, ((bytesRead << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveSerialPortWrite(void) {
    int array;
    int startIndex;
    int portNum;
    int bytesWritten;
    int count;
    int fmt;
    int integerPointer;
    int integerPointer1;
    int integerPointer2;
    int successValue;
    int successValue1;
    int sp;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		count = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		count = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (1 * 4));
	if ((integerPointer1 & 1)) {
		startIndex = (integerPointer1 >> 1);
		goto l2;
	} else {
		primitiveFail();
		startIndex = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	array = longAt(stackPointer - (2 * 4));
	/* begin stackIntegerValue: */
	integerPointer2 = longAt(stackPointer - (3 * 4));
	if ((integerPointer2 & 1)) {
		portNum = (integerPointer2 >> 1);
		goto l3;
	} else {
		primitiveFail();
		portNum = 0;
		goto l3;
	}
l3:	/* end stackIntegerValue: */;
	fmt = (((unsigned) (longAt(array))) >> 8) & 15;
	/* begin success: */
	successValue = (fmt >= 8) && (fmt <= 11);
	successFlag = successValue && successFlag;
	/* begin success: */
	successValue1 = (startIndex >= 1) && (((startIndex + count) - 1) <= (lengthOf(array)));
	successFlag = successValue1 && successFlag;
	if (successFlag) {
		bytesWritten = serialPortWriteFrom(portNum, count, ((array + 4) + startIndex) - 1);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 5 * 4;
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, ((bytesWritten << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveSetFullScreen(void) {
    int argOop;

	argOop = longAt(stackPointer);
	if (argOop == trueObj) {
		ioSetFullScreen(true);
	} else {
		if (argOop == falseObj) {
			ioSetFullScreen(false);
		} else {
			primitiveFail();
		}
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
	}
}

int primitiveSetInterruptKey(void) {
    int keycode;
    int integerPointer;
    int top;

	/* begin popInteger */
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top;
	if ((integerPointer & 1)) {
		keycode = (integerPointer >> 1);
		goto l1;
	} else {
		successFlag = false;
		keycode = 1;
		goto l1;
	}
l1:	/* end popInteger */;
	if (successFlag) {
		interruptKeycode = keycode;
	} else {
		/* begin unPop: */
		stackPointer += 1 * 4;
	}
}

int primitiveShortAt(void) {
    int addr;
    int sz;
    int value;
    int index;
    int rcvr;
    int integerPointer;
    int successValue;
    int successValue1;
    int sp;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		index = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		index = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	rcvr = longAt(stackPointer - (1 * 4));
	/* begin success: */
	successValue = (!((rcvr & 1))) && (isWordsOrBytes(rcvr));
	successFlag = successValue && successFlag;
	if (!(successFlag)) {
		return null;
	}
	sz = ((int) ((sizeBitsOf(rcvr)) - 4) >> 1);
	/* begin success: */
	successValue1 = (index >= 1) && (index <= sz);
	successFlag = successValue1 && successFlag;
	if (successFlag) {
		addr = (rcvr + 4) + (2 * (index - 1));
		value = *((short int *) addr);
		/* begin pop: */
		stackPointer -= 2 * 4;
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, ((value << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveShortAtPut(void) {
    int addr;
    int sz;
    int value;
    int index;
    int rcvr;
    int integerPointer;
    int integerPointer1;
    int successValue;
    int successValue1;
    int successValue2;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		value = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		value = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (1 * 4));
	if ((integerPointer1 & 1)) {
		index = (integerPointer1 >> 1);
		goto l2;
	} else {
		primitiveFail();
		index = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	rcvr = longAt(stackPointer - (2 * 4));
	/* begin success: */
	successValue = (!((rcvr & 1))) && (isWordsOrBytes(rcvr));
	successFlag = successValue && successFlag;
	if (!(successFlag)) {
		return null;
	}
	sz = ((int) ((sizeBitsOf(rcvr)) - 4) >> 1);
	/* begin success: */
	successValue1 = (index >= 1) && (index <= sz);
	successFlag = successValue1 && successFlag;
	/* begin success: */
	successValue2 = (value >= -32768) && (value <= 32767);
	successFlag = successValue2 && successFlag;
	if (successFlag) {
		addr = (rcvr + 4) + (2 * (index - 1));
		*((short int *) addr) = value;
		/* begin pop: */
		stackPointer -= 2 * 4;
	}
}

int primitiveShowDisplayRect(void) {
    int displayObj;
    int dispBits;
    int dispBitsPtr;
    int top;
    int bottom;
    int h;
    int w;
    int d;
    int right;
    int left;
    int integerPointer;
    int integerPointer1;
    int integerPointer2;
    int integerPointer3;
    int successValue;
    int successValue1;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		bottom = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		bottom = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (1 * 4));
	if ((integerPointer1 & 1)) {
		top = (integerPointer1 >> 1);
		goto l2;
	} else {
		primitiveFail();
		top = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer2 = longAt(stackPointer - (2 * 4));
	if ((integerPointer2 & 1)) {
		right = (integerPointer2 >> 1);
		goto l3;
	} else {
		primitiveFail();
		right = 0;
		goto l3;
	}
l3:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer3 = longAt(stackPointer - (3 * 4));
	if ((integerPointer3 & 1)) {
		left = (integerPointer3 >> 1);
		goto l4;
	} else {
		primitiveFail();
		left = 0;
		goto l4;
	}
l4:	/* end stackIntegerValue: */;
	displayObj = longAt(((((char *) specialObjectsOop)) + 4) + (14 << 2));
	/* begin success: */
	successValue = (((((unsigned) (longAt(displayObj))) >> 8) & 15) <= 4) && ((lengthOf(displayObj)) >= 4);
	successFlag = successValue && successFlag;
	if (successFlag) {
		dispBits = longAt(((((char *) displayObj)) + 4) + (0 << 2));
		w = fetchIntegerofObject(1, displayObj);
		h = fetchIntegerofObject(2, displayObj);
		d = fetchIntegerofObject(3, displayObj);
	}
	if (left < 0) {
		left = 0;
	}
	if (right > w) {
		right = w;
	}
	if (top < 0) {
		top = 0;
	}
	if (bottom > h) {
		bottom = h;
	}
	/* begin success: */
	successValue1 = (left <= right) && (top <= bottom);
	successFlag = successValue1 && successFlag;
	if (successFlag) {
		dispBitsPtr = dispBits + 4;
		ioShowDisplay(dispBitsPtr, w, h, d, left, right, top, bottom);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 4 * 4;
	}
}

int primitiveSignal(void) {
    int sema;
    int ccIndex;
    int cl;

	sema = longAt(stackPointer);
	/* begin assertClassOf:is: */
	if ((sema & 1)) {
		successFlag = false;
		goto l1;
	}
	ccIndex = (((unsigned) (longAt(sema))) >> 12) & 31;
	if (ccIndex == 0) {
		cl = (longAt(sema - 4)) & 4294967292U;
	} else {
		cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
	}
	/* begin success: */
	successFlag = (cl == (longAt(((((char *) specialObjectsOop)) + 4) + (18 << 2)))) && successFlag;
l1:	/* end assertClassOf:is: */;
	if (successFlag) {
		synchronousSignal(sema);
	}
}

int primitiveSignalAtBytesLeft(void) {
    int bytes;
    int integerPointer;
    int top;

	/* begin popInteger */
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top;
	if ((integerPointer & 1)) {
		bytes = (integerPointer >> 1);
		goto l1;
	} else {
		successFlag = false;
		bytes = 1;
		goto l1;
	}
l1:	/* end popInteger */;
	if (successFlag) {
		lowSpaceThreshold = bytes;
	} else {
		lowSpaceThreshold = 0;
		/* begin unPop: */
		stackPointer += 1 * 4;
	}
}

int primitiveSignalAtMilliseconds(void) {
    int sema;
    int tick;
    int oop;
    int oop1;
    int valuePointer;
    int integerPointer;
    int top;
    int top1;

	/* begin popInteger */
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top;
	if ((integerPointer & 1)) {
		tick = (integerPointer >> 1);
		goto l1;
	} else {
		successFlag = false;
		tick = 1;
		goto l1;
	}
l1:	/* end popInteger */;
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	sema = top1;
	if (successFlag) {
		if ((fetchClassOf(sema)) == (longAt(((((char *) specialObjectsOop)) + 4) + (18 << 2)))) {
			/* begin storePointer:ofObject:withValue: */
			oop = specialObjectsOop;
			if (oop < youngStart) {
				possibleRootStoreIntovalue(oop, sema);
			}
			longAtput(((((char *) oop)) + 4) + (29 << 2), sema);
			nextWakeupTick = tick;
		} else {
			/* begin storePointer:ofObject:withValue: */
			oop1 = specialObjectsOop;
			valuePointer = nilObj;
			if (oop1 < youngStart) {
				possibleRootStoreIntovalue(oop1, valuePointer);
			}
			longAtput(((((char *) oop1)) + 4) + (29 << 2), valuePointer);
			nextWakeupTick = 0;
		}
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
	}
}

int primitiveSine(void) {
    double rcvr;

	rcvr = popFloat();
	if (successFlag) {
		pushFloat(sin(rcvr));
	} else {
		/* begin unPop: */
		stackPointer += 1 * 4;
	}
}

int primitiveSize(void) {
    int sz;
    int rcvr;
    int sp;
    int hdr;
    int totalLength;
    int fmt;
    int fixedFields;
    int sz1;
    int classFormat;
    int class;
    int ccIndex;

	rcvr = longAt(stackPointer);
	if ((rcvr & 1)) {
		sz = 0;
	} else {
		/* begin stSizeOf: */
		hdr = longAt(rcvr);
		fmt = (((unsigned) hdr) >> 8) & 15;
		/* begin lengthOf:baseHeader:format: */
		if ((hdr & 3) == 0) {
			sz1 = (longAt(rcvr - 8)) & 4294967292U;
		} else {
			sz1 = hdr & 252;
		}
		if (fmt < 8) {
			totalLength = ((unsigned) (sz1 - 4)) >> 2;
			goto l1;
		} else {
			totalLength = (sz1 - 4) - (fmt & 3);
			goto l1;
		}
	l1:	/* end lengthOf:baseHeader:format: */;
		/* begin fixedFieldsOf:format:length: */
		if ((fmt > 3) || (fmt == 2)) {
			fixedFields = 0;
			goto l2;
		}
		if (fmt < 2) {
			fixedFields = totalLength;
			goto l2;
		}
		/* begin fetchClassOf: */
		if ((rcvr & 1)) {
			class = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
			goto l3;
		}
		ccIndex = ((((unsigned) (longAt(rcvr))) >> 12) & 31) - 1;
		if (ccIndex < 0) {
			class = (longAt(rcvr - 4)) & 4294967292U;
			goto l3;
		} else {
			class = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
			goto l3;
		}
	l3:	/* end fetchClassOf: */;
		classFormat = (longAt(((((char *) class)) + 4) + (2 << 2))) - 1;
		fixedFields = (((((unsigned) classFormat) >> 11) & 192) + ((((unsigned) classFormat) >> 2) & 63)) - 1;
	l2:	/* end fixedFieldsOf:format:length: */;
		sz = totalLength - fixedFields;
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, ((sz << 1) | 1));
		stackPointer = sp;
	} else {
		failSpecialPrim(62);
	}
}

int primitiveSnapshot(void) {
    int activeProc;
    int dataSize;
    int rcvr;
    int top;
    int sp;
    int sp1;
    int sp2;
    int valuePointer;

	/* begin storeContextRegisters: */
	longAtput(((((char *) activeContext)) + 4) + (1 << 2), ((((instructionPointer - method) - (4 - 2)) << 1) | 1));
	longAtput(((((char *) activeContext)) + 4) + (2 << 2), (((((((unsigned) ((stackPointer - activeContext) - 4)) >> 2) - 6) + 1) << 1) | 1));
	activeProc = longAt(((((char *) (longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (3 << 2))))) + 4) + (1 << 2))))) + 4) + (1 << 2));
	/* begin storePointer:ofObject:withValue: */
	valuePointer = activeContext;
	if (activeProc < youngStart) {
		possibleRootStoreIntovalue(activeProc, valuePointer);
	}
	longAtput(((((char *) activeProc)) + 4) + (1 << 2), valuePointer);
	incrementalGC();
	fullGC();
	dataSize = freeBlock - (startOfMemory());
	if (successFlag) {
		/* begin popStack */
		top = longAt(stackPointer);
		stackPointer -= 4;
		rcvr = top;
		/* begin push: */
		longAtput(sp = stackPointer + 4, trueObj);
		stackPointer = sp;
		writeImageFile(dataSize);
		/* begin pop: */
		stackPointer -= 1 * 4;
	}
	if (successFlag) {
		/* begin push: */
		longAtput(sp1 = stackPointer + 4, falseObj);
		stackPointer = sp1;
	} else {
		/* begin push: */
		longAtput(sp2 = stackPointer + 4, rcvr);
		stackPointer = sp2;
	}
}

int primitiveSocketAbortConnection(void) {
    SocketPtr s;

	s = socketValueOf(longAt(stackPointer));
	if (successFlag) {
		sqSocketAbortConnection(s);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
	}
}

int primitiveSocketCloseConnection(void) {
    SocketPtr s;

	s = socketValueOf(longAt(stackPointer));
	if (successFlag) {
		sqSocketCloseConnection(s);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
	}
}

int primitiveSocketConnectToPort(void) {
    int addr;
    int port;
    SocketPtr s;
    int integerPointer;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		port = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		port = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	addr = netAddressToInt(longAt(stackPointer - (1 * 4)));
	s = socketValueOf(longAt(stackPointer - (2 * 4)));
	if (successFlag) {
		sqSocketConnectToPort(s, addr, port);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 3 * 4;
	}
}

int primitiveSocketConnectionStatus(void) {
    int status;
    SocketPtr s;
    int sp;

	s = socketValueOf(longAt(stackPointer));
	if (successFlag) {
		status = sqSocketConnectionStatus(s);
	}
	if (successFlag) {
		/* begin pop:thenPush: */
		longAtput(sp = stackPointer - ((2 - 1) * 4), ((status << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveSocketCreate(void) {
    int semaIndex;
    int socketType;
    int sendBufSize;
    int socketOop;
    int netType;
    SocketPtr s;
    int recvBufSize;
    int sp;
    int integerPointer;
    int integerPointer1;
    int integerPointer2;
    int integerPointer3;
    int integerPointer4;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		semaIndex = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		semaIndex = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (1 * 4));
	if ((integerPointer1 & 1)) {
		sendBufSize = (integerPointer1 >> 1);
		goto l2;
	} else {
		primitiveFail();
		sendBufSize = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer2 = longAt(stackPointer - (2 * 4));
	if ((integerPointer2 & 1)) {
		recvBufSize = (integerPointer2 >> 1);
		goto l3;
	} else {
		primitiveFail();
		recvBufSize = 0;
		goto l3;
	}
l3:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer3 = longAt(stackPointer - (3 * 4));
	if ((integerPointer3 & 1)) {
		socketType = (integerPointer3 >> 1);
		goto l4;
	} else {
		primitiveFail();
		socketType = 0;
		goto l4;
	}
l4:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer4 = longAt(stackPointer - (4 * 4));
	if ((integerPointer4 & 1)) {
		netType = (integerPointer4 >> 1);
		goto l5;
	} else {
		primitiveFail();
		netType = 0;
		goto l5;
	}
l5:	/* end stackIntegerValue: */;
	if (successFlag) {
		socketOop = instantiateClassindexableSize(longAt(((((char *) specialObjectsOop)) + 4) + (26 << 2)), socketRecordSize());
		s = socketValueOf(socketOop);
		sqSocketCreateNetTypeSocketTypeRecvBytesSendBytesSemaID(s, netType, socketType, recvBufSize, sendBufSize, semaIndex);
		if (successFlag) {
			/* begin pop:thenPush: */
			longAtput(sp = stackPointer - ((6 - 1) * 4), socketOop);
			stackPointer = sp;
		}
	}
}

int primitiveSocketDestroy(void) {
    SocketPtr s;

	s = socketValueOf(longAt(stackPointer));
	if (successFlag) {
		sqSocketDestroy(s);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
	}
}

int primitiveSocketError(void) {
    int err;
    SocketPtr s;
    int sp;

	s = socketValueOf(longAt(stackPointer));
	if (successFlag) {
		err = sqSocketError(s);
	}
	if (successFlag) {
		/* begin pop:thenPush: */
		longAtput(sp = stackPointer - ((2 - 1) * 4), ((err << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveSocketListenOnPort(void) {
    int port;
    SocketPtr s;
    int integerPointer;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		port = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		port = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	s = socketValueOf(longAt(stackPointer - (1 * 4)));
	if (successFlag) {
		sqSocketListenOnPort(s, port);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 2 * 4;
	}
}

int primitiveSocketLocalAddress(void) {
    int addr;
    SocketPtr s;
    int oop;
    int sp;

	s = socketValueOf(longAt(stackPointer));
	if (successFlag) {
		addr = sqSocketLocalAddress(s);
	}
	if (successFlag) {
		/* begin pop:thenPush: */
		oop = intToNetAddress(addr);
		longAtput(sp = stackPointer - ((2 - 1) * 4), oop);
		stackPointer = sp;
	}
}

int primitiveSocketLocalPort(void) {
    int port;
    SocketPtr s;
    int sp;

	s = socketValueOf(longAt(stackPointer));
	if (successFlag) {
		port = sqSocketLocalPort(s);
	}
	if (successFlag) {
		/* begin pop:thenPush: */
		longAtput(sp = stackPointer - ((2 - 1) * 4), ((port << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveSocketReceiveDataAvailable(void) {
    int dataIsAvailable;
    SocketPtr s;
    int sp;
    int sp1;

	s = socketValueOf(longAt(stackPointer));
	if (successFlag) {
		dataIsAvailable = sqSocketReceiveDataAvailable(s);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 2 * 4;
		/* begin pushBool: */
		if (dataIsAvailable) {
			/* begin push: */
			longAtput(sp = stackPointer + 4, trueObj);
			stackPointer = sp;
		} else {
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, falseObj);
			stackPointer = sp1;
		}
	}
}

int primitiveSocketReceiveDataBufCount(void) {
    int array;
    int startIndex;
    int arrayBase;
    int bytesReceived;
    int bufStart;
    int byteSize;
    SocketPtr s;
    int count;
    int sp;
    int integerPointer;
    int integerPointer1;
    int successValue;
    int successValue1;
    int fmt;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		count = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		count = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (1 * 4));
	if ((integerPointer1 & 1)) {
		startIndex = (integerPointer1 >> 1);
		goto l2;
	} else {
		primitiveFail();
		startIndex = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	array = longAt(stackPointer - (2 * 4));
	s = socketValueOf(longAt(stackPointer - (3 * 4)));
	/* begin success: */
	/* begin isWordsOrBytes: */
	fmt = (((unsigned) (longAt(array))) >> 8) & 15;
	successValue = (fmt == 6) || ((fmt >= 8) && (fmt <= 11));
	successFlag = successValue && successFlag;
	if (((((unsigned) (longAt(array))) >> 8) & 15) == 6) {
		byteSize = 4;
	} else {
		byteSize = 1;
	}
	/* begin success: */
	successValue1 = (startIndex >= 1) && ((count >= 0) && (((startIndex + count) - 1) <= (lengthOf(array))));
	successFlag = successValue1 && successFlag;
	if (successFlag) {
		arrayBase = array + 4;
		bufStart = arrayBase + ((startIndex - 1) * byteSize);
		bytesReceived = sqSocketReceiveDataBufCount(s, bufStart, count * byteSize);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 5 * 4;
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, (((bytesReceived / byteSize) << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveSocketRemoteAddress(void) {
    int addr;
    SocketPtr s;
    int oop;
    int sp;

	s = socketValueOf(longAt(stackPointer));
	if (successFlag) {
		addr = sqSocketRemoteAddress(s);
	}
	if (successFlag) {
		/* begin pop:thenPush: */
		oop = intToNetAddress(addr);
		longAtput(sp = stackPointer - ((2 - 1) * 4), oop);
		stackPointer = sp;
	}
}

int primitiveSocketRemotePort(void) {
    int port;
    SocketPtr s;
    int sp;

	s = socketValueOf(longAt(stackPointer));
	if (successFlag) {
		port = sqSocketRemotePort(s);
	}
	if (successFlag) {
		/* begin pop:thenPush: */
		longAtput(sp = stackPointer - ((2 - 1) * 4), ((port << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveSocketSendDataBufCount(void) {
    int array;
    int startIndex;
    int arrayBase;
    int bytesSent;
    int bufStart;
    int byteSize;
    SocketPtr s;
    int count;
    int sp;
    int integerPointer;
    int integerPointer1;
    int successValue;
    int successValue1;
    int fmt;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		count = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		count = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (1 * 4));
	if ((integerPointer1 & 1)) {
		startIndex = (integerPointer1 >> 1);
		goto l2;
	} else {
		primitiveFail();
		startIndex = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	array = longAt(stackPointer - (2 * 4));
	s = socketValueOf(longAt(stackPointer - (3 * 4)));
	/* begin success: */
	/* begin isWordsOrBytes: */
	fmt = (((unsigned) (longAt(array))) >> 8) & 15;
	successValue = (fmt == 6) || ((fmt >= 8) && (fmt <= 11));
	successFlag = successValue && successFlag;
	if (((((unsigned) (longAt(array))) >> 8) & 15) == 6) {
		byteSize = 4;
	} else {
		byteSize = 1;
	}
	/* begin success: */
	successValue1 = (startIndex >= 1) && ((count >= 0) && (((startIndex + count) - 1) <= (lengthOf(array))));
	successFlag = successValue1 && successFlag;
	if (successFlag) {
		arrayBase = array + 4;
		bufStart = arrayBase + ((startIndex - 1) * byteSize);
		bytesSent = sqSocketSendDataBufCount(s, bufStart, count * byteSize);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 5 * 4;
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, (((bytesSent / byteSize) << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveSocketSendDone(void) {
    int done;
    SocketPtr s;
    int sp;
    int sp1;

	s = socketValueOf(longAt(stackPointer));
	if (successFlag) {
		done = sqSocketSendDone(s);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 2 * 4;
		/* begin pushBool: */
		if (done) {
			/* begin push: */
			longAtput(sp = stackPointer + 4, trueObj);
			stackPointer = sp;
		} else {
			/* begin push: */
			longAtput(sp1 = stackPointer + 4, falseObj);
			stackPointer = sp1;
		}
	}
}

int primitiveSomeInstance(void) {
    int instance;
    int class;
    int sp;
    int top;
    int thisClass;
    int thisObj;
    int ccIndex;
    int obj;
    int chunk;
    int extra;
    int type;
    int extra1;
    int sz;
    int header;
    int extra2;
    int type1;
    int extra11;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	class = top;
	/* begin initialInstanceOf: */
	/* begin firstAccessibleObject */
	/* begin oopFromChunk: */
	chunk = startOfMemory();
	/* begin extraHeaderBytes: */
	type = (longAt(chunk)) & 3;
	if (type > 1) {
		extra1 = 0;
	} else {
		if (type == 1) {
			extra1 = 4;
		} else {
			extra1 = 8;
		}
	}
	extra = extra1;
	obj = chunk + extra;
	while (obj < endOfMemory) {
		if (!(((longAt(obj)) & 3) == 2)) {
			thisObj = obj;
			goto l4;
		}
		/* begin objectAfter: */
		if (checkAssertions) {
			if (obj >= endOfMemory) {
				error("no objects after the end of memory");
			}
		}
		if (((longAt(obj)) & 3) == 2) {
			sz = (longAt(obj)) & 536870908;
		} else {
			/* begin sizeBitsOf: */
			header = longAt(obj);
			if ((header & 3) == 0) {
				sz = (longAt(obj - 8)) & 4294967292U;
				goto l3;
			} else {
				sz = header & 252;
				goto l3;
			}
		l3:	/* end sizeBitsOf: */;
		}
		/* begin oopFromChunk: */
		/* begin extraHeaderBytes: */
		type1 = (longAt(obj + sz)) & 3;
		if (type1 > 1) {
			extra11 = 0;
		} else {
			if (type1 == 1) {
				extra11 = 4;
			} else {
				extra11 = 8;
			}
		}
		extra2 = extra11;
		obj = (obj + sz) + extra2;
	}
	error("heap is empty");
l4:	/* end firstAccessibleObject */;
	while (!(thisObj == null)) {
		/* begin fetchClassOf: */
		if ((thisObj & 1)) {
			thisClass = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
			goto l2;
		}
		ccIndex = ((((unsigned) (longAt(thisObj))) >> 12) & 31) - 1;
		if (ccIndex < 0) {
			thisClass = (longAt(thisObj - 4)) & 4294967292U;
			goto l2;
		} else {
			thisClass = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
			goto l2;
		}
	l2:	/* end fetchClassOf: */;
		if (thisClass == class) {
			instance = thisObj;
			goto l1;
		}
		thisObj = accessibleObjectAfter(thisObj);
	}
	instance = nilObj;
l1:	/* end initialInstanceOf: */;
	if (instance == nilObj) {
		/* begin unPop: */
		stackPointer += 1 * 4;
		primitiveFail();
	} else {
		/* begin push: */
		longAtput(sp = stackPointer + 4, instance);
		stackPointer = sp;
	}
}

int primitiveSomeObject(void) {
    int object;
    int sp;
    int obj;
    int chunk;
    int extra;
    int type;
    int extra1;
    int sz;
    int header;
    int extra2;
    int type1;
    int extra11;

	/* begin pop: */
	stackPointer -= 1 * 4;
	/* begin push: */
	/* begin firstAccessibleObject */
	/* begin oopFromChunk: */
	chunk = startOfMemory();
	/* begin extraHeaderBytes: */
	type = (longAt(chunk)) & 3;
	if (type > 1) {
		extra1 = 0;
	} else {
		if (type == 1) {
			extra1 = 4;
		} else {
			extra1 = 8;
		}
	}
	extra = extra1;
	obj = chunk + extra;
	while (obj < endOfMemory) {
		if (!(((longAt(obj)) & 3) == 2)) {
			object = obj;
			goto l2;
		}
		/* begin objectAfter: */
		if (checkAssertions) {
			if (obj >= endOfMemory) {
				error("no objects after the end of memory");
			}
		}
		if (((longAt(obj)) & 3) == 2) {
			sz = (longAt(obj)) & 536870908;
		} else {
			/* begin sizeBitsOf: */
			header = longAt(obj);
			if ((header & 3) == 0) {
				sz = (longAt(obj - 8)) & 4294967292U;
				goto l1;
			} else {
				sz = header & 252;
				goto l1;
			}
		l1:	/* end sizeBitsOf: */;
		}
		/* begin oopFromChunk: */
		/* begin extraHeaderBytes: */
		type1 = (longAt(obj + sz)) & 3;
		if (type1 > 1) {
			extra11 = 0;
		} else {
			if (type1 == 1) {
				extra11 = 4;
			} else {
				extra11 = 8;
			}
		}
		extra2 = extra11;
		obj = (obj + sz) + extra2;
	}
	error("heap is empty");
l2:	/* end firstAccessibleObject */;
	longAtput(sp = stackPointer + 4, object);
	stackPointer = sp;
}

int primitiveSoundAvailableSpace(void) {
    int frames;
    int object;
    int sp;

	frames = snd_AvailableSpace();
	/* begin success: */
	successFlag = (frames >= 0) && successFlag;
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
		/* begin push: */
		object = positive32BitIntegerFor(frames);
		longAtput(sp = stackPointer + 4, object);
		stackPointer = sp;
	}
}

int primitiveSoundGetRecordingSampleRate(void) {
    double rate;

	rate = snd_GetRecordingSampleRate();
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
		pushFloat(rate);
	}
}

int primitiveSoundInsertSamples(void) {
    int buf;
    int leadTime;
    int frameCount;
    int framesPlayed;
    int object;
    int sp;
    int integerPointer;
    int integerPointer1;
    int successValue;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		leadTime = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		leadTime = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	buf = longAt(stackPointer - (1 * 4));
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (2 * 4));
	if ((integerPointer1 & 1)) {
		frameCount = (integerPointer1 >> 1);
		goto l2;
	} else {
		primitiveFail();
		frameCount = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	/* begin success: */
	successFlag = (((((unsigned) (longAt(buf))) >> 8) & 15) == 6) && successFlag;
	/* begin success: */
	successValue = frameCount <= (lengthOf(buf));
	successFlag = successValue && successFlag;
	if (successFlag) {
		framesPlayed = snd_InsertSamplesFromLeadTime(frameCount, buf + 4, leadTime);
		/* begin success: */
		successFlag = (framesPlayed >= 0) && successFlag;
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 4 * 4;
		/* begin push: */
		object = positive32BitIntegerFor(framesPlayed);
		longAtput(sp = stackPointer + 4, object);
		stackPointer = sp;
	}
}

int primitiveSoundPlaySamples(void) {
    int startIndex;
    int buf;
    int frameCount;
    int framesPlayed;
    int object;
    int sp;
    int integerPointer;
    int integerPointer1;
    int successValue;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		startIndex = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		startIndex = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	buf = longAt(stackPointer - (1 * 4));
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (2 * 4));
	if ((integerPointer1 & 1)) {
		frameCount = (integerPointer1 >> 1);
		goto l2;
	} else {
		primitiveFail();
		frameCount = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	/* begin success: */
	successFlag = (((((unsigned) (longAt(buf))) >> 8) & 15) == 6) && successFlag;
	/* begin success: */
	successValue = (startIndex >= 1) && (((startIndex + frameCount) - 1) <= (lengthOf(buf)));
	successFlag = successValue && successFlag;
	if (successFlag) {
		framesPlayed = snd_PlaySamplesFromAtLength(frameCount, buf + 4, startIndex - 1);
		/* begin success: */
		successFlag = (framesPlayed >= 0) && successFlag;
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 4 * 4;
		/* begin push: */
		object = positive32BitIntegerFor(framesPlayed);
		longAtput(sp = stackPointer + 4, object);
		stackPointer = sp;
	}
}

int primitiveSoundPlaySilence(void) {
    int framesPlayed;
    int object;
    int sp;

	framesPlayed = snd_PlaySilence();
	/* begin success: */
	successFlag = (framesPlayed >= 0) && successFlag;
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
		/* begin push: */
		object = positive32BitIntegerFor(framesPlayed);
		longAtput(sp = stackPointer + 4, object);
		stackPointer = sp;
	}
}

int primitiveSoundRecordSamples(void) {
    int startWordIndex;
    int samplesRecorded;
    int bufSizeInBytes;
    int buf;
    int successValue;
    int sp;
    int integerPointer;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		startWordIndex = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		startWordIndex = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	buf = longAt(stackPointer - (1 * 4));
	/* begin success: */
	successFlag = (((((unsigned) (longAt(buf))) >> 8) & 15) == 6) && successFlag;
	if (successFlag) {
		bufSizeInBytes = (lengthOf(buf)) * 4;
		/* begin success: */
		successValue = (startWordIndex >= 1) && (((startWordIndex - 1) * 2) < bufSizeInBytes);
		successFlag = successValue && successFlag;
	}
	if (successFlag) {
		samplesRecorded = snd_RecordSamplesIntoAtLength(buf + 4, startWordIndex - 1, bufSizeInBytes);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 3 * 4;
		/* begin push: */
		longAtput(sp = stackPointer + 4, ((samplesRecorded << 1) | 1));
		stackPointer = sp;
	}
}

int primitiveSoundSetRecordLevel(void) {
    int level;
    int integerPointer;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		level = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		level = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	if (successFlag) {
		snd_SetRecordLevel(level);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
	}
}

int primitiveSoundStart(void) {
    int stereoFlag;
    int samplesPerSec;
    int bufFrames;
    int integerPointer;
    int integerPointer1;

	/* begin booleanValueOf: */
	if ((longAt(stackPointer - (0 * 4))) == trueObj) {
		stereoFlag = true;
		goto l1;
	}
	if ((longAt(stackPointer - (0 * 4))) == falseObj) {
		stereoFlag = false;
		goto l1;
	}
	successFlag = false;
	stereoFlag = null;
l1:	/* end booleanValueOf: */;
	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (1 * 4));
	if ((integerPointer & 1)) {
		samplesPerSec = (integerPointer >> 1);
		goto l2;
	} else {
		primitiveFail();
		samplesPerSec = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (2 * 4));
	if ((integerPointer1 & 1)) {
		bufFrames = (integerPointer1 >> 1);
		goto l3;
	} else {
		primitiveFail();
		bufFrames = 0;
		goto l3;
	}
l3:	/* end stackIntegerValue: */;
	if (successFlag) {
		/* begin success: */
		successFlag = (snd_Start(bufFrames, samplesPerSec, stereoFlag, 0)) && successFlag;
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 3 * 4;
	}
}

int primitiveSoundStartRecording(void) {
    int stereoFlag;
    int semaIndex;
    int desiredSamplesPerSec;
    int integerPointer;
    int integerPointer1;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		semaIndex = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		semaIndex = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	/* begin booleanValueOf: */
	if ((longAt(stackPointer - (1 * 4))) == trueObj) {
		stereoFlag = true;
		goto l2;
	}
	if ((longAt(stackPointer - (1 * 4))) == falseObj) {
		stereoFlag = false;
		goto l2;
	}
	successFlag = false;
	stereoFlag = null;
l2:	/* end booleanValueOf: */;
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (2 * 4));
	if ((integerPointer1 & 1)) {
		desiredSamplesPerSec = (integerPointer1 >> 1);
		goto l3;
	} else {
		primitiveFail();
		desiredSamplesPerSec = 0;
		goto l3;
	}
l3:	/* end stackIntegerValue: */;
	if (successFlag) {
		snd_StartRecording(desiredSamplesPerSec, stereoFlag, semaIndex);
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 3 * 4;
	}
}

int primitiveSoundStartWithSemaphore(void) {
    int stereoFlag;
    int semaIndex;
    int samplesPerSec;
    int bufFrames;
    int integerPointer;
    int integerPointer1;
    int integerPointer2;

	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (0 * 4));
	if ((integerPointer & 1)) {
		semaIndex = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		semaIndex = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	/* begin booleanValueOf: */
	if ((longAt(stackPointer - (1 * 4))) == trueObj) {
		stereoFlag = true;
		goto l2;
	}
	if ((longAt(stackPointer - (1 * 4))) == falseObj) {
		stereoFlag = false;
		goto l2;
	}
	successFlag = false;
	stereoFlag = null;
l2:	/* end booleanValueOf: */;
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (2 * 4));
	if ((integerPointer1 & 1)) {
		samplesPerSec = (integerPointer1 >> 1);
		goto l3;
	} else {
		primitiveFail();
		samplesPerSec = 0;
		goto l3;
	}
l3:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer2 = longAt(stackPointer - (3 * 4));
	if ((integerPointer2 & 1)) {
		bufFrames = (integerPointer2 >> 1);
		goto l4;
	} else {
		primitiveFail();
		bufFrames = 0;
		goto l4;
	}
l4:	/* end stackIntegerValue: */;
	if (successFlag) {
		/* begin success: */
		successFlag = (snd_Start(bufFrames, samplesPerSec, stereoFlag, semaIndex)) && successFlag;
	}
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 4 * 4;
	}
}

int primitiveSoundStop(void) {
	snd_Stop();
}

int primitiveSoundStopRecording(void) {
	snd_StopRecording();
}

int primitiveSpecialObjectsOop(void) {
    int sp;

	/* begin pop: */
	stackPointer -= 1 * 4;
	/* begin push: */
	longAtput(sp = stackPointer + 4, specialObjectsOop);
	stackPointer = sp;
}

int primitiveSquareRoot(void) {
    double rcvr;

	rcvr = popFloat();
	/* begin success: */
	successFlag = (rcvr >= 0.0) && successFlag;
	if (successFlag) {
		pushFloat(sqrt(rcvr));
	} else {
		/* begin unPop: */
		stackPointer += 1 * 4;
	}
}

int primitiveStringAt(void) {
    int index;
    int result;
    int rcvr;
    int sp;

	/* begin commonAt: */
	index = longAt(stackPointer);
	rcvr = longAt(stackPointer - (1 * 4));
	if (((index & 1)) && (!((rcvr & 1)))) {
		index = (index >> 1);
		result = stObjectat(rcvr, index);
		if (true && (successFlag)) {
			result = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (24 << 2))))) + 4) + (((result >> 1)) << 2));
		}
	} else {
		successFlag = false;
	}
	if (successFlag) {
		/* begin pop:thenPush: */
		longAtput(sp = stackPointer - ((2 - 1) * 4), result);
		stackPointer = sp;
	} else {
		if (true) {
			failSpecialPrim(63);
		} else {
			failSpecialPrim(60);
		}
	}
}

int primitiveStringAtPut(void) {
    int value;
    int valToStore;
    int index;
    int rcvr;
    int sp;

	/* begin commonAtPut: */
	value = valToStore = longAt(stackPointer);
	index = longAt(stackPointer - (1 * 4));
	rcvr = longAt(stackPointer - (2 * 4));
	if (((index & 1)) && (!((rcvr & 1)))) {
		index = (index >> 1);
		if (true) {
			valToStore = asciiOfCharacter(value);
		}
		stObjectatput(rcvr, index, valToStore);
	} else {
		successFlag = false;
	}
	if (successFlag) {
		/* begin pop:thenPush: */
		longAtput(sp = stackPointer - ((3 - 1) * 4), value);
		stackPointer = sp;
	} else {
		if (true) {
			failSpecialPrim(64);
		} else {
			failSpecialPrim(61);
		}
	}
}

int primitiveStringReplace(void) {
    int array;
    int srcIndex;
    int start;
    int stop;
    int arrayFmt;
    int arrayInstSize;
    int i;
    int hdr;
    int totalLength;
    int repl;
    int replStart;
    int replFmt;
    int replInstSize;
    int integerPointer;
    int integerPointer1;
    int integerPointer2;
    int sz;
    int classFormat;
    int class;
    int sz1;
    int classFormat1;
    int class1;
    int ccIndex;
    int ccIndex1;

	array = longAt(stackPointer - (4 * 4));
	/* begin stackIntegerValue: */
	integerPointer = longAt(stackPointer - (3 * 4));
	if ((integerPointer & 1)) {
		start = (integerPointer >> 1);
		goto l1;
	} else {
		primitiveFail();
		start = 0;
		goto l1;
	}
l1:	/* end stackIntegerValue: */;
	/* begin stackIntegerValue: */
	integerPointer1 = longAt(stackPointer - (2 * 4));
	if ((integerPointer1 & 1)) {
		stop = (integerPointer1 >> 1);
		goto l2;
	} else {
		primitiveFail();
		stop = 0;
		goto l2;
	}
l2:	/* end stackIntegerValue: */;
	repl = longAt(stackPointer - (1 * 4));
	/* begin stackIntegerValue: */
	integerPointer2 = longAt(stackPointer - (0 * 4));
	if ((integerPointer2 & 1)) {
		replStart = (integerPointer2 >> 1);
		goto l3;
	} else {
		primitiveFail();
		replStart = 0;
		goto l3;
	}
l3:	/* end stackIntegerValue: */;
	if (!(successFlag)) {
		return primitiveFail();
	}
	if ((repl & 1)) {
		return primitiveFail();
	}
	hdr = longAt(array);
	arrayFmt = (((unsigned) hdr) >> 8) & 15;
	/* begin lengthOf:baseHeader:format: */
	if ((hdr & 3) == 0) {
		sz = (longAt(array - 8)) & 4294967292U;
	} else {
		sz = hdr & 252;
	}
	if (arrayFmt < 8) {
		totalLength = ((unsigned) (sz - 4)) >> 2;
		goto l4;
	} else {
		totalLength = (sz - 4) - (arrayFmt & 3);
		goto l4;
	}
l4:	/* end lengthOf:baseHeader:format: */;
	/* begin fixedFieldsOf:format:length: */
	if ((arrayFmt > 3) || (arrayFmt == 2)) {
		arrayInstSize = 0;
		goto l5;
	}
	if (arrayFmt < 2) {
		arrayInstSize = totalLength;
		goto l5;
	}
	/* begin fetchClassOf: */
	if ((array & 1)) {
		class = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
		goto l8;
	}
	ccIndex = ((((unsigned) (longAt(array))) >> 12) & 31) - 1;
	if (ccIndex < 0) {
		class = (longAt(array - 4)) & 4294967292U;
		goto l8;
	} else {
		class = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
		goto l8;
	}
l8:	/* end fetchClassOf: */;
	classFormat = (longAt(((((char *) class)) + 4) + (2 << 2))) - 1;
	arrayInstSize = (((((unsigned) classFormat) >> 11) & 192) + ((((unsigned) classFormat) >> 2) & 63)) - 1;
l5:	/* end fixedFieldsOf:format:length: */;
	if (!((start >= 1) && ((start <= stop) && ((stop + arrayInstSize) <= totalLength)))) {
		return primitiveFail();
	}
	hdr = longAt(repl);
	replFmt = (((unsigned) hdr) >> 8) & 15;
	/* begin lengthOf:baseHeader:format: */
	if ((hdr & 3) == 0) {
		sz1 = (longAt(repl - 8)) & 4294967292U;
	} else {
		sz1 = hdr & 252;
	}
	if (replFmt < 8) {
		totalLength = ((unsigned) (sz1 - 4)) >> 2;
		goto l6;
	} else {
		totalLength = (sz1 - 4) - (replFmt & 3);
		goto l6;
	}
l6:	/* end lengthOf:baseHeader:format: */;
	/* begin fixedFieldsOf:format:length: */
	if ((replFmt > 3) || (replFmt == 2)) {
		replInstSize = 0;
		goto l7;
	}
	if (replFmt < 2) {
		replInstSize = totalLength;
		goto l7;
	}
	/* begin fetchClassOf: */
	if ((repl & 1)) {
		class1 = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
		goto l9;
	}
	ccIndex1 = ((((unsigned) (longAt(repl))) >> 12) & 31) - 1;
	if (ccIndex1 < 0) {
		class1 = (longAt(repl - 4)) & 4294967292U;
		goto l9;
	} else {
		class1 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex1 << 2));
		goto l9;
	}
l9:	/* end fetchClassOf: */;
	classFormat1 = (longAt(((((char *) class1)) + 4) + (2 << 2))) - 1;
	replInstSize = (((((unsigned) classFormat1) >> 11) & 192) + ((((unsigned) classFormat1) >> 2) & 63)) - 1;
l7:	/* end fixedFieldsOf:format:length: */;
	if (!((replStart >= 1) && ((((stop - start) + replStart) + replInstSize) <= totalLength))) {
		return primitiveFail();
	}
	if (arrayFmt < 8) {
		if (!(arrayFmt == replFmt)) {
			return primitiveFail();
		}
	} else {
		if (!((arrayFmt & 12) == (replFmt & 12))) {
			return primitiveFail();
		}
	}
	srcIndex = (replStart + replInstSize) - 1;
	if (arrayFmt < 4) {
		for (i = ((start + arrayInstSize) - 1); i <= ((stop + arrayInstSize) - 1); i += 1) {
			/* begin storePointer:ofObject:withValue: */
			if (array < youngStart) {
				possibleRootStoreIntovalue(array, longAt(((((char *) repl)) + 4) + (srcIndex << 2)));
			}
			longAtput(((((char *) array)) + 4) + (i << 2), longAt(((((char *) repl)) + 4) + (srcIndex << 2)));
			srcIndex += 1;
		}
	} else {
		if (arrayFmt < 8) {
			for (i = ((start + arrayInstSize) - 1); i <= ((stop + arrayInstSize) - 1); i += 1) {
				longAtput(((((char *) array)) + 4) + (i << 2), longAt(((((char *) repl)) + 4) + (srcIndex << 2)));
				srcIndex += 1;
			}
		} else {
			for (i = ((start + arrayInstSize) - 1); i <= ((stop + arrayInstSize) - 1); i += 1) {
				byteAtput(((((char *) array)) + 4) + i, byteAt(((((char *) repl)) + 4) + srcIndex));
				srcIndex += 1;
			}
		}
	}
	/* begin pop: */
	stackPointer -= 4 * 4;
}

int primitiveSubtract(void) {
    int integerReceiver;
    int integerArgument;
    int integerPointer;
    int top;
    int integerPointer1;
    int top1;
    int sp;

	successFlag = true;
	/* begin popInteger */
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top;
	if ((integerPointer & 1)) {
		integerArgument = (integerPointer >> 1);
		goto l1;
	} else {
		successFlag = false;
		integerArgument = 1;
		goto l1;
	}
l1:	/* end popInteger */;
	/* begin popInteger */
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer1 = top1;
	if ((integerPointer1 & 1)) {
		integerReceiver = (integerPointer1 >> 1);
		goto l2;
	} else {
		successFlag = false;
		integerReceiver = 1;
		goto l2;
	}
l2:	/* end popInteger */;
	/* begin checkIntegerResult:from: */
	if (successFlag && (((integerReceiver - integerArgument) ^ ((integerReceiver - integerArgument) << 1)) >= 0)) {
		/* begin pushInteger: */
		/* begin push: */
		longAtput(sp = stackPointer + 4, (((integerReceiver - integerArgument) << 1) | 1));
		stackPointer = sp;
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
		failSpecialPrim(2);
	}
}

int primitiveSuspend(void) {
    int activeProc;
    int sp;
    int newProc;
    int sched;
    int oldProc;
    int valuePointer;
    int tmp;

	activeProc = longAt(((((char *) (longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (3 << 2))))) + 4) + (1 << 2))))) + 4) + (1 << 2));
	/* begin success: */
	successFlag = ((longAt(stackPointer)) == activeProc) && successFlag;
	if (successFlag) {
		/* begin pop: */
		stackPointer -= 1 * 4;
		/* begin push: */
		longAtput(sp = stackPointer + 4, nilObj);
		stackPointer = sp;
		/* begin transferTo: */
		newProc = wakeHighestPriority();
		sched = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (3 << 2))))) + 4) + (1 << 2));
		oldProc = longAt(((((char *) sched)) + 4) + (1 << 2));
		/* begin storePointer:ofObject:withValue: */
		valuePointer = activeContext;
		if (oldProc < youngStart) {
			possibleRootStoreIntovalue(oldProc, valuePointer);
		}
		longAtput(((((char *) oldProc)) + 4) + (1 << 2), valuePointer);
		/* begin storePointer:ofObject:withValue: */
		if (sched < youngStart) {
			possibleRootStoreIntovalue(sched, newProc);
		}
		longAtput(((((char *) sched)) + 4) + (1 << 2), newProc);
		/* begin newActiveContext: */
		/* begin storeContextRegisters: */
		longAtput(((((char *) activeContext)) + 4) + (1 << 2), ((((instructionPointer - method) - (4 - 2)) << 1) | 1));
		longAtput(((((char *) activeContext)) + 4) + (2 << 2), (((((((unsigned) ((stackPointer - activeContext) - 4)) >> 2) - 6) + 1) << 1) | 1));
		if ((longAt(((((char *) newProc)) + 4) + (1 << 2))) < youngStart) {
			beRootIfOld(longAt(((((char *) newProc)) + 4) + (1 << 2)));
		}
		activeContext = longAt(((((char *) newProc)) + 4) + (1 << 2));
		/* begin fetchContextRegisters: */
		tmp = longAt(((((char *) (longAt(((((char *) newProc)) + 4) + (1 << 2))))) + 4) + (3 << 2));
		if ((tmp & 1)) {
			tmp = longAt(((((char *) (longAt(((((char *) newProc)) + 4) + (1 << 2))))) + 4) + (5 << 2));
			if (tmp < youngStart) {
				beRootIfOld(tmp);
			}
		} else {
			tmp = longAt(((((char *) newProc)) + 4) + (1 << 2));
		}
		theHomeContext = tmp;
		receiver = longAt(((((char *) tmp)) + 4) + (5 << 2));
		method = longAt(((((char *) tmp)) + 4) + (3 << 2));
		tmp = ((longAt(((((char *) (longAt(((((char *) newProc)) + 4) + (1 << 2))))) + 4) + (1 << 2))) >> 1);
		instructionPointer = ((method + tmp) + 4) - 2;
		tmp = ((longAt(((((char *) (longAt(((((char *) newProc)) + 4) + (1 << 2))))) + 4) + (2 << 2))) >> 1);
		stackPointer = ((longAt(((((char *) newProc)) + 4) + (1 << 2))) + 4) + (((6 + tmp) - 1) * 4);
		reclaimableContextCount = 0;
	}
}

int primitiveTimesTwoPower(void) {
    int arg;
    double rcvr;
    int integerPointer;
    int top;

	/* begin popInteger */
	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	integerPointer = top;
	if ((integerPointer & 1)) {
		arg = (integerPointer >> 1);
		goto l1;
	} else {
		successFlag = false;
		arg = 1;
		goto l1;
	}
l1:	/* end popInteger */;
	rcvr = popFloat();
	if (successFlag) {
		pushFloat(ldexp(rcvr, arg));
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
	}
}

int primitiveTruncated(void) {
    double trunc;
    double frac;
    double rcvr;

	rcvr = popFloat();
	if (successFlag) {
		frac = modf(rcvr, &trunc);
		success((-1073741824.0 <= trunc) && (trunc <= 1073741823.0));
	}
	if (successFlag) {
		pushInteger((int) trunc);
	} else {
		/* begin unPop: */
		stackPointer += 1 * 4;
	}
}

int primitiveVMParameter(void) {
    int mem;
    int arg;
    int paramsArraySize;
    int i;
    int index;
    int result;
    int sp;
    int sp1;
    int sp2;

	mem = ((int) memory);
	if (argumentCount == 0) {
		paramsArraySize = 22;
		result = instantiateClassindexableSize(longAt(((((char *) specialObjectsOop)) + 4) + (7 << 2)), paramsArraySize);
		for (i = 0; i <= (paramsArraySize - 1); i += 1) {
			longAtput(((((char *) result)) + 4) + (i << 2), ((0 << 1) | 1));
		}
		longAtput(((((char *) result)) + 4) + (0 << 2), (((youngStart - mem) << 1) | 1));
		longAtput(((((char *) result)) + 4) + (1 << 2), (((freeBlock - mem) << 1) | 1));
		longAtput(((((char *) result)) + 4) + (2 << 2), (((endOfMemory - mem) << 1) | 1));
		longAtput(((((char *) result)) + 4) + (3 << 2), ((allocationCount << 1) | 1));
		longAtput(((((char *) result)) + 4) + (4 << 2), ((allocationsBetweenGCs << 1) | 1));
		longAtput(((((char *) result)) + 4) + (5 << 2), ((tenuringThreshold << 1) | 1));
		longAtput(((((char *) result)) + 4) + (6 << 2), ((statFullGCs << 1) | 1));
		longAtput(((((char *) result)) + 4) + (7 << 2), ((statFullGCMSecs << 1) | 1));
		longAtput(((((char *) result)) + 4) + (8 << 2), ((statIncrGCs << 1) | 1));
		longAtput(((((char *) result)) + 4) + (9 << 2), ((statIncrGCMSecs << 1) | 1));
		longAtput(((((char *) result)) + 4) + (10 << 2), ((statTenures << 1) | 1));
		longAtput(((((char *) result)) + 4) + (20 << 2), ((rootTableCount << 1) | 1));
		longAtput(((((char *) result)) + 4) + (21 << 2), ((statRootTableOverflows << 1) | 1));
		/* begin pop:thenPush: */
		longAtput(sp = stackPointer - ((1 - 1) * 4), result);
		stackPointer = sp;
		return null;
	}
	arg = longAt(stackPointer);
	if (!((arg & 1))) {
		return primitiveFail();
	}
	arg = (arg >> 1);
	if (argumentCount == 1) {
		if ((arg < 1) || (arg > 22)) {
			return primitiveFail();
		}
		if (arg == 1) {
			result = youngStart - mem;
		}
		if (arg == 2) {
			result = freeBlock - mem;
		}
		if (arg == 3) {
			result = endOfMemory - mem;
		}
		if (arg == 4) {
			result = allocationCount;
		}
		if (arg == 5) {
			result = allocationsBetweenGCs;
		}
		if (arg == 6) {
			result = tenuringThreshold;
		}
		if (arg == 7) {
			result = statFullGCs;
		}
		if (arg == 8) {
			result = statFullGCMSecs;
		}
		if (arg == 9) {
			result = statIncrGCs;
		}
		if (arg == 10) {
			result = statIncrGCMSecs;
		}
		if (arg == 11) {
			result = statTenures;
		}
		if ((arg >= 12) && (arg <= 20)) {
			result = 0;
		}
		if (arg == 21) {
			result = rootTableCount;
		}
		if (arg == 22) {
			result = statRootTableOverflows;
		}
		/* begin pop:thenPush: */
		longAtput(sp1 = stackPointer - ((2 - 1) * 4), ((result << 1) | 1));
		stackPointer = sp1;
		return null;
	}
	if (!(argumentCount == 2)) {
		return primitiveFail();
	}
	index = longAt(stackPointer - (1 * 4));
	if (!((index & 1))) {
		return primitiveFail();
	}
	index = (index >> 1);
	if (index <= 0) {
		return primitiveFail();
	}
	successFlag = false;
	if (index == 5) {
		result = allocationsBetweenGCs;
		allocationsBetweenGCs = arg;
		successFlag = true;
	}
	if (index == 6) {
		result = tenuringThreshold;
		tenuringThreshold = arg;
		successFlag = true;
	}
	if (successFlag) {
		/* begin pop:thenPush: */
		longAtput(sp2 = stackPointer - ((3 - 1) * 4), ((result << 1) | 1));
		stackPointer = sp2;
		return null;
	}
	primitiveFail();
}

int primitiveVMPath(void) {
    int sz;
    int s;
    int sp;

	sz = vmPathSize();
	s = instantiateClassindexableSize(longAt(((((char *) specialObjectsOop)) + 4) + (6 << 2)), sz);
	vmPathGetLength(s + 4, sz);
	/* begin pop: */
	stackPointer -= 1 * 4;
	/* begin push: */
	longAtput(sp = stackPointer + 4, s);
	stackPointer = sp;
}

int primitiveValue(void) {
    int blockArgumentCount;
    int initialIP;
    int blockContext;
    int toIndex;
    int fromIndex;
    int lastFrom;
    int successValue;
    int tmp;
    int argCount;

	blockContext = longAt(stackPointer - (argumentCount * 4));
	/* begin argumentCountOfBlock: */
	argCount = longAt(((((char *) blockContext)) + 4) + (3 << 2));
	if ((argCount & 1)) {
		blockArgumentCount = (argCount >> 1);
		goto l1;
	} else {
		primitiveFail();
		blockArgumentCount = 0;
		goto l1;
	}
l1:	/* end argumentCountOfBlock: */;
	/* begin success: */
	successValue = (argumentCount == blockArgumentCount) && ((longAt(((((char *) blockContext)) + 4) + (0 << 2))) == nilObj);
	successFlag = successValue && successFlag;
	if (successFlag) {
		/* begin transfer:fromIndex:ofObject:toIndex:ofObject: */
		fromIndex = activeContext + ((((((unsigned) ((stackPointer - activeContext) - 4)) >> 2) - argumentCount) + 1) * 4);
		toIndex = blockContext + (6 * 4);
		lastFrom = fromIndex + (argumentCount * 4);
		while (fromIndex < lastFrom) {
			fromIndex += 4;
			toIndex += 4;
			longAtput(toIndex, longAt(fromIndex));
		}
		/* begin pop: */
		stackPointer -= (argumentCount + 1) * 4;
		initialIP = longAt(((((char *) blockContext)) + 4) + (4 << 2));
		longAtput(((((char *) blockContext)) + 4) + (1 << 2), initialIP);
		/* begin storeStackPointerValue:inContext: */
		longAtput(((((char *) blockContext)) + 4) + (2 << 2), ((argumentCount << 1) | 1));
		longAtput(((((char *) blockContext)) + 4) + (0 << 2), activeContext);
		/* begin newActiveContext: */
		/* begin storeContextRegisters: */
		longAtput(((((char *) activeContext)) + 4) + (1 << 2), ((((instructionPointer - method) - (4 - 2)) << 1) | 1));
		longAtput(((((char *) activeContext)) + 4) + (2 << 2), (((((((unsigned) ((stackPointer - activeContext) - 4)) >> 2) - 6) + 1) << 1) | 1));
		if (blockContext < youngStart) {
			beRootIfOld(blockContext);
		}
		activeContext = blockContext;
		/* begin fetchContextRegisters: */
		tmp = longAt(((((char *) blockContext)) + 4) + (3 << 2));
		if ((tmp & 1)) {
			tmp = longAt(((((char *) blockContext)) + 4) + (5 << 2));
			if (tmp < youngStart) {
				beRootIfOld(tmp);
			}
		} else {
			tmp = blockContext;
		}
		theHomeContext = tmp;
		receiver = longAt(((((char *) tmp)) + 4) + (5 << 2));
		method = longAt(((((char *) tmp)) + 4) + (3 << 2));
		tmp = ((longAt(((((char *) blockContext)) + 4) + (1 << 2))) >> 1);
		instructionPointer = ((method + tmp) + 4) - 2;
		tmp = ((longAt(((((char *) blockContext)) + 4) + (2 << 2))) >> 1);
		stackPointer = (blockContext + 4) + (((6 + tmp) - 1) * 4);
	}
}

int primitiveValueWithArgs(void) {
    int argumentArray;
    int arrayArgumentCount;
    int blockArgumentCount;
    int initialIP;
    int blockContext;
    int sz;
    int successValue;
    int toIndex;
    int fromIndex;
    int lastFrom;
    int top;
    int top1;
    int header;
    int tmp;
    int argCount;
    int ccIndex;
    int cl;

	/* begin popStack */
	top = longAt(stackPointer);
	stackPointer -= 4;
	argumentArray = top;
	/* begin popStack */
	top1 = longAt(stackPointer);
	stackPointer -= 4;
	blockContext = top1;
	/* begin argumentCountOfBlock: */
	argCount = longAt(((((char *) blockContext)) + 4) + (3 << 2));
	if ((argCount & 1)) {
		blockArgumentCount = (argCount >> 1);
		goto l2;
	} else {
		primitiveFail();
		blockArgumentCount = 0;
		goto l2;
	}
l2:	/* end argumentCountOfBlock: */;
	/* begin assertClassOf:is: */
	if ((argumentArray & 1)) {
		successFlag = false;
		goto l3;
	}
	ccIndex = (((unsigned) (longAt(argumentArray))) >> 12) & 31;
	if (ccIndex == 0) {
		cl = (longAt(argumentArray - 4)) & 4294967292U;
	} else {
		cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
	}
	/* begin success: */
	successFlag = (cl == (longAt(((((char *) specialObjectsOop)) + 4) + (7 << 2)))) && successFlag;
l3:	/* end assertClassOf:is: */;
	if (successFlag) {
		/* begin fetchWordLengthOf: */
		/* begin sizeBitsOf: */
		header = longAt(argumentArray);
		if ((header & 3) == 0) {
			sz = (longAt(argumentArray - 8)) & 4294967292U;
			goto l1;
		} else {
			sz = header & 252;
			goto l1;
		}
	l1:	/* end sizeBitsOf: */;
		arrayArgumentCount = ((unsigned) (sz - 4)) >> 2;
		/* begin success: */
		successValue = (arrayArgumentCount == blockArgumentCount) && ((longAt(((((char *) blockContext)) + 4) + (0 << 2))) == nilObj);
		successFlag = successValue && successFlag;
	}
	if (successFlag) {
		/* begin transfer:fromIndex:ofObject:toIndex:ofObject: */
		fromIndex = argumentArray + (0 * 4);
		toIndex = blockContext + (6 * 4);
		lastFrom = fromIndex + (arrayArgumentCount * 4);
		while (fromIndex < lastFrom) {
			fromIndex += 4;
			toIndex += 4;
			longAtput(toIndex, longAt(fromIndex));
		}
		initialIP = longAt(((((char *) blockContext)) + 4) + (4 << 2));
		longAtput(((((char *) blockContext)) + 4) + (1 << 2), initialIP);
		/* begin storeStackPointerValue:inContext: */
		longAtput(((((char *) blockContext)) + 4) + (2 << 2), ((arrayArgumentCount << 1) | 1));
		longAtput(((((char *) blockContext)) + 4) + (0 << 2), activeContext);
		/* begin newActiveContext: */
		/* begin storeContextRegisters: */
		longAtput(((((char *) activeContext)) + 4) + (1 << 2), ((((instructionPointer - method) - (4 - 2)) << 1) | 1));
		longAtput(((((char *) activeContext)) + 4) + (2 << 2), (((((((unsigned) ((stackPointer - activeContext) - 4)) >> 2) - 6) + 1) << 1) | 1));
		if (blockContext < youngStart) {
			beRootIfOld(blockContext);
		}
		activeContext = blockContext;
		/* begin fetchContextRegisters: */
		tmp = longAt(((((char *) blockContext)) + 4) + (3 << 2));
		if ((tmp & 1)) {
			tmp = longAt(((((char *) blockContext)) + 4) + (5 << 2));
			if (tmp < youngStart) {
				beRootIfOld(tmp);
			}
		} else {
			tmp = blockContext;
		}
		theHomeContext = tmp;
		receiver = longAt(((((char *) tmp)) + 4) + (5 << 2));
		method = longAt(((((char *) tmp)) + 4) + (3 << 2));
		tmp = ((longAt(((((char *) blockContext)) + 4) + (1 << 2))) >> 1);
		instructionPointer = ((method + tmp) + 4) - 2;
		tmp = ((longAt(((((char *) blockContext)) + 4) + (2 << 2))) >> 1);
		stackPointer = (blockContext + 4) + (((6 + tmp) - 1) * 4);
	} else {
		/* begin unPop: */
		stackPointer += 2 * 4;
	}
}

int primitiveWait(void) {
    int sema;
    int activeProc;
    int excessSignals;
    int lastLink;
    int newProc;
    int sched;
    int oldProc;
    int valuePointer;
    int tmp;
    int ccIndex;
    int cl;

	sema = longAt(stackPointer);
	/* begin assertClassOf:is: */
	if ((sema & 1)) {
		successFlag = false;
		goto l1;
	}
	ccIndex = (((unsigned) (longAt(sema))) >> 12) & 31;
	if (ccIndex == 0) {
		cl = (longAt(sema - 4)) & 4294967292U;
	} else {
		cl = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + ((ccIndex - 1) << 2));
	}
	/* begin success: */
	successFlag = (cl == (longAt(((((char *) specialObjectsOop)) + 4) + (18 << 2)))) && successFlag;
l1:	/* end assertClassOf:is: */;
	if (successFlag) {
		excessSignals = fetchIntegerofObject(2, sema);
		if (excessSignals > 0) {
			/* begin storeInteger:ofObject:withValue: */
			if (((excessSignals - 1) ^ ((excessSignals - 1) << 1)) >= 0) {
				longAtput(((((char *) sema)) + 4) + (2 << 2), (((excessSignals - 1) << 1) | 1));
			} else {
				primitiveFail();
			}
		} else {
			activeProc = longAt(((((char *) (longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (3 << 2))))) + 4) + (1 << 2))))) + 4) + (1 << 2));
			/* begin addLastLink:toList: */
			if ((longAt(((((char *) sema)) + 4) + (0 << 2))) == nilObj) {
				/* begin storePointer:ofObject:withValue: */
				if (sema < youngStart) {
					possibleRootStoreIntovalue(sema, activeProc);
				}
				longAtput(((((char *) sema)) + 4) + (0 << 2), activeProc);
			} else {
				lastLink = longAt(((((char *) sema)) + 4) + (1 << 2));
				/* begin storePointer:ofObject:withValue: */
				if (lastLink < youngStart) {
					possibleRootStoreIntovalue(lastLink, activeProc);
				}
				longAtput(((((char *) lastLink)) + 4) + (0 << 2), activeProc);
			}
			/* begin storePointer:ofObject:withValue: */
			if (sema < youngStart) {
				possibleRootStoreIntovalue(sema, activeProc);
			}
			longAtput(((((char *) sema)) + 4) + (1 << 2), activeProc);
			/* begin storePointer:ofObject:withValue: */
			if (activeProc < youngStart) {
				possibleRootStoreIntovalue(activeProc, sema);
			}
			longAtput(((((char *) activeProc)) + 4) + (3 << 2), sema);
			/* begin transferTo: */
			newProc = wakeHighestPriority();
			sched = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (3 << 2))))) + 4) + (1 << 2));
			oldProc = longAt(((((char *) sched)) + 4) + (1 << 2));
			/* begin storePointer:ofObject:withValue: */
			valuePointer = activeContext;
			if (oldProc < youngStart) {
				possibleRootStoreIntovalue(oldProc, valuePointer);
			}
			longAtput(((((char *) oldProc)) + 4) + (1 << 2), valuePointer);
			/* begin storePointer:ofObject:withValue: */
			if (sched < youngStart) {
				possibleRootStoreIntovalue(sched, newProc);
			}
			longAtput(((((char *) sched)) + 4) + (1 << 2), newProc);
			/* begin newActiveContext: */
			/* begin storeContextRegisters: */
			longAtput(((((char *) activeContext)) + 4) + (1 << 2), ((((instructionPointer - method) - (4 - 2)) << 1) | 1));
			longAtput(((((char *) activeContext)) + 4) + (2 << 2), (((((((unsigned) ((stackPointer - activeContext) - 4)) >> 2) - 6) + 1) << 1) | 1));
			if ((longAt(((((char *) newProc)) + 4) + (1 << 2))) < youngStart) {
				beRootIfOld(longAt(((((char *) newProc)) + 4) + (1 << 2)));
			}
			activeContext = longAt(((((char *) newProc)) + 4) + (1 << 2));
			/* begin fetchContextRegisters: */
			tmp = longAt(((((char *) (longAt(((((char *) newProc)) + 4) + (1 << 2))))) + 4) + (3 << 2));
			if ((tmp & 1)) {
				tmp = longAt(((((char *) (longAt(((((char *) newProc)) + 4) + (1 << 2))))) + 4) + (5 << 2));
				if (tmp < youngStart) {
					beRootIfOld(tmp);
				}
			} else {
				tmp = longAt(((((char *) newProc)) + 4) + (1 << 2));
			}
			theHomeContext = tmp;
			receiver = longAt(((((char *) tmp)) + 4) + (5 << 2));
			method = longAt(((((char *) tmp)) + 4) + (3 << 2));
			tmp = ((longAt(((((char *) (longAt(((((char *) newProc)) + 4) + (1 << 2))))) + 4) + (1 << 2))) >> 1);
			instructionPointer = ((method + tmp) + 4) - 2;
			tmp = ((longAt(((((char *) (longAt(((((char *) newProc)) + 4) + (1 << 2))))) + 4) + (2 << 2))) >> 1);
			stackPointer = ((longAt(((((char *) newProc)) + 4) + (1 << 2))) + 4) + (((6 + tmp) - 1) * 4);
			reclaimableContextCount = 0;
		}
	}
}

int primitiveWarpBits(void) {
    int rcvr;
    int ns;
    int successValue;
    int skewWord;
    int mergeWord;
    int startBits;
    int yDelta;
    int smoothingCount;
    int sourceMapOop;
    int t;
    int i;
    int nSteps;
    int word;
    int halftoneWord;
    int deltaP12x;
    int deltaP12y;
    int deltaP43x;
    int deltaP43y;
    int pAx;
    int pAy;
    int pBx;
    int xDelta;
    int pBy;
    int integerPointer;

	rcvr = longAt(stackPointer - (argumentCount * 4));
	/* begin success: */
	successValue = loadBitBltFrom(rcvr);
	successFlag = successValue && successFlag;
	if (successFlag) {
		/* begin warpBits */
		ns = noSource;
		noSource = true;
		clipRange();
		noSource = ns;
		if (noSource || ((bbW <= 0) || (bbH <= 0))) {
			affectedL = affectedR = affectedT = affectedB = 0;
			goto l1;
		}
		destMaskAndPointerInit();
		/* begin warpLoop */
		if (!((fetchWordLengthOf(bitBltOop)) >= (15 + 12))) {
			primitiveFail();
			goto l3;
		}
		nSteps = height - 1;
		if (nSteps <= 0) {
			nSteps = 1;
		}
		pAx = fetchIntegerOrTruncFloatofObject(15, bitBltOop);
		t = fetchIntegerOrTruncFloatofObject(15 + 3, bitBltOop);
		deltaP12x = deltaFromtonSteps(pAx, t, nSteps);
		if (deltaP12x < 0) {
			pAx = t - (nSteps * deltaP12x);
		}
		pAy = fetchIntegerOrTruncFloatofObject(15 + 1, bitBltOop);
		t = fetchIntegerOrTruncFloatofObject(15 + 4, bitBltOop);
		deltaP12y = deltaFromtonSteps(pAy, t, nSteps);
		if (deltaP12y < 0) {
			pAy = t - (nSteps * deltaP12y);
		}
		pBx = fetchIntegerOrTruncFloatofObject(15 + 9, bitBltOop);
		t = fetchIntegerOrTruncFloatofObject(15 + 6, bitBltOop);
		deltaP43x = deltaFromtonSteps(pBx, t, nSteps);
		if (deltaP43x < 0) {
			pBx = t - (nSteps * deltaP43x);
		}
		pBy = fetchIntegerOrTruncFloatofObject(15 + 10, bitBltOop);
		t = fetchIntegerOrTruncFloatofObject(15 + 7, bitBltOop);
		deltaP43y = deltaFromtonSteps(pBy, t, nSteps);
		if (deltaP43y < 0) {
			pBy = t - (nSteps * deltaP43y);
		}
		if (!successFlag) {
			goto l3;
		}
		if (argumentCount == 2) {
			/* begin stackIntegerValue: */
			integerPointer = longAt(stackPointer - (1 * 4));
			if ((integerPointer & 1)) {
				smoothingCount = (integerPointer >> 1);
				goto l2;
			} else {
				primitiveFail();
				smoothingCount = 0;
				goto l2;
			}
		l2:	/* end stackIntegerValue: */;
			sourceMapOop = longAt(stackPointer - (0 * 4));
			if (sourceMapOop == nilObj) {
				if (sourcePixSize < 16) {
					primitiveFail();
					goto l3;
				}
			} else {
				if ((fetchWordLengthOf(sourceMapOop)) < (1 << sourcePixSize)) {
					primitiveFail();
					goto l3;
				}
			}
		} else {
			smoothingCount = 1;
			sourceMapOop = nilObj;
		}
		startBits = pixPerWord - (dx & (pixPerWord - 1));
		nSteps = width - 1;
		if (nSteps <= 0) {
			nSteps = 1;
		}
		for (i = destY; i <= (clipY - 1); i += 1) {
			pAx += deltaP12x;
			pAy += deltaP12y;
			pBx += deltaP43x;
			pBy += deltaP43y;
		}
		for (i = 1; i <= bbH; i += 1) {
			xDelta = deltaFromtonSteps(pAx, pBx, nSteps);
			if (xDelta >= 0) {
				sx = pAx;
			} else {
				sx = pBx - (nSteps * xDelta);
			}
			yDelta = deltaFromtonSteps(pAy, pBy, nSteps);
			if (yDelta >= 0) {
				sy = pAy;
			} else {
				sy = pBy - (nSteps * yDelta);
			}
			for (word = destX; word <= (clipX - 1); word += 1) {
				sx += xDelta;
				sy += yDelta;
			}
			if (noHalftone) {
				halftoneWord = 4294967295U;
			} else {
				halftoneWord = longAt(halftoneBase + ((((dy + i) - 1) % halftoneHeight) * 4));
			}
			destMask = mask1;
			if (bbW < startBits) {
				skewWord = warpSourcePixelsxDeltahyDeltahxDeltavyDeltavsmoothingsourceMap(bbW, xDelta, yDelta, deltaP12x, deltaP12y, smoothingCount, sourceMapOop);
				skewWord = ((((startBits - bbW) * destPixSize) < 0) ? ((unsigned) skewWord >> -((startBits - bbW) * destPixSize)) : ((unsigned) skewWord << ((startBits - bbW) * destPixSize)));
			} else {
				skewWord = warpSourcePixelsxDeltahyDeltahxDeltavyDeltavsmoothingsourceMap(startBits, xDelta, yDelta, deltaP12x, deltaP12y, smoothingCount, sourceMapOop);
			}
			for (word = 1; word <= nWords; word += 1) {
				mergeWord = mergewith(skewWord & halftoneWord, (longAt(destIndex)) & destMask);
				longAtput(destIndex, (destMask & mergeWord) | ((~destMask) & (longAt(destIndex))));
				destIndex += 4;
				if (word >= (nWords - 1)) {
					if (!(word == nWords)) {
						destMask = mask2;
						skewWord = warpSourcePixelsxDeltahyDeltahxDeltavyDeltavsmoothingsourceMap(pixPerWord, xDelta, yDelta, deltaP12x, deltaP12y, smoothingCount, sourceMapOop);
					}
				} else {
					destMask = 4294967295U;
					skewWord = warpSourcePixelsxDeltahyDeltahxDeltavyDeltavsmoothingsourceMap(pixPerWord, xDelta, yDelta, deltaP12x, deltaP12y, smoothingCount, sourceMapOop);
				}
			}
			pAx += deltaP12x;
			pAy += deltaP12y;
			pBx += deltaP43x;
			pBy += deltaP43y;
			destIndex += destDelta;
		}
	l3:	/* end warpLoop */;
		if (hDir > 0) {
			affectedL = dx;
			affectedR = dx + bbW;
		} else {
			affectedL = (dx - bbW) + 1;
			affectedR = dx + 1;
		}
		if (vDir > 0) {
			affectedT = dy;
			affectedB = dy + bbH;
		} else {
			affectedT = (dy - bbH) + 1;
			affectedB = dy + 1;
		}
	l1:	/* end warpBits */;
		showDisplayBits();
	}
}

int print(char *s) {
	printf("%s", s);
}

int printCallStack(void) {
    int methodSel;
    int methodClass;
    int home;
    int ctxt;
    int methodArray;
    int done;
    int i;
    int classDict;
    int currClass;
    int classDictSize;
    int sz;
    int header;
    int ccIndex;
    int methodArray1;
    int done1;
    int i1;
    int classDict1;
    int currClass1;
    int classDictSize1;
    int sz1;
    int header1;
    int ccIndex2;
    int ccIndex1;

	ctxt = activeContext;
	while (!(ctxt == nilObj)) {
		if ((fetchClassOf(ctxt)) == (longAt(((((char *) specialObjectsOop)) + 4) + (11 << 2)))) {
			home = longAt(((((char *) ctxt)) + 4) + (5 << 2));
		} else {
			home = ctxt;
		}
		/* begin findClassOfMethod:forReceiver: */
		/* begin fetchClassOf: */
		if (((longAt(((((char *) home)) + 4) + (5 << 2))) & 1)) {
			currClass1 = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
			goto l5;
		}
		ccIndex2 = ((((unsigned) (longAt(longAt(((((char *) home)) + 4) + (5 << 2))))) >> 12) & 31) - 1;
		if (ccIndex2 < 0) {
			currClass1 = (longAt((longAt(((((char *) home)) + 4) + (5 << 2))) - 4)) & 4294967292U;
			goto l5;
		} else {
			currClass1 = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex2 << 2));
			goto l5;
		}
	l5:	/* end fetchClassOf: */;
		done1 = false;
		while (!(done1)) {
			classDict1 = longAt(((((char *) currClass1)) + 4) + (1 << 2));
			/* begin fetchWordLengthOf: */
			/* begin sizeBitsOf: */
			header1 = longAt(classDict1);
			if ((header1 & 3) == 0) {
				sz1 = (longAt(classDict1 - 8)) & 4294967292U;
				goto l4;
			} else {
				sz1 = header1 & 252;
				goto l4;
			}
		l4:	/* end sizeBitsOf: */;
			classDictSize1 = ((unsigned) (sz1 - 4)) >> 2;
			methodArray1 = longAt(((((char *) classDict1)) + 4) + (1 << 2));
			i1 = 0;
			while (i1 < (classDictSize1 - 2)) {
				if ((longAt(((((char *) home)) + 4) + (3 << 2))) == (longAt(((((char *) methodArray1)) + 4) + (i1 << 2)))) {
					methodClass = currClass1;
					goto l6;
				}
				i1 += 1;
			}
			currClass1 = longAt(((((char *) currClass1)) + 4) + (0 << 2));
			done1 = currClass1 == nilObj;
		}
		/* begin fetchClassOf: */
		if (((longAt(((((char *) home)) + 4) + (5 << 2))) & 1)) {
			methodClass = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
			goto l6;
		}
		ccIndex1 = ((((unsigned) (longAt(longAt(((((char *) home)) + 4) + (5 << 2))))) >> 12) & 31) - 1;
		if (ccIndex1 < 0) {
			methodClass = (longAt((longAt(((((char *) home)) + 4) + (5 << 2))) - 4)) & 4294967292U;
			goto l6;
		} else {
			methodClass = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex1 << 2));
			goto l6;
		}
		methodClass = null;
	l6:	/* end findClassOfMethod:forReceiver: */;
		/* begin findSelectorOfMethod:forReceiver: */
		/* begin fetchClassOf: */
		if (((longAt(((((char *) home)) + 4) + (5 << 2))) & 1)) {
			currClass = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
			goto l2;
		}
		ccIndex = ((((unsigned) (longAt(longAt(((((char *) home)) + 4) + (5 << 2))))) >> 12) & 31) - 1;
		if (ccIndex < 0) {
			currClass = (longAt((longAt(((((char *) home)) + 4) + (5 << 2))) - 4)) & 4294967292U;
			goto l2;
		} else {
			currClass = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
			goto l2;
		}
	l2:	/* end fetchClassOf: */;
		done = false;
		while (!(done)) {
			classDict = longAt(((((char *) currClass)) + 4) + (1 << 2));
			/* begin fetchWordLengthOf: */
			/* begin sizeBitsOf: */
			header = longAt(classDict);
			if ((header & 3) == 0) {
				sz = (longAt(classDict - 8)) & 4294967292U;
				goto l1;
			} else {
				sz = header & 252;
				goto l1;
			}
		l1:	/* end sizeBitsOf: */;
			classDictSize = ((unsigned) (sz - 4)) >> 2;
			methodArray = longAt(((((char *) classDict)) + 4) + (1 << 2));
			i = 0;
			while (i <= (classDictSize - 2)) {
				if ((longAt(((((char *) home)) + 4) + (3 << 2))) == (longAt(((((char *) methodArray)) + 4) + (i << 2)))) {
					methodSel = longAt(((((char *) classDict)) + 4) + ((i + 2) << 2));
					goto l3;
				}
				i += 1;
			}
			currClass = longAt(((((char *) currClass)) + 4) + (0 << 2));
			done = currClass == nilObj;
		}
		methodSel = longAt(((((char *) specialObjectsOop)) + 4) + (20 << 2));
	l3:	/* end findSelectorOfMethod:forReceiver: */;
		printNum(ctxt);
		print(" ");
		if (!(ctxt == home)) {
			print("[] in ");
		}
		printNameOfClasscount(methodClass, 5);
		print(">");
		printStringOf(methodSel);
		/* begin cr */
		printf("\n");
		ctxt = longAt(((((char *) ctxt)) + 4) + (0 << 2));
	}
}

int printChar(int aByte) {
	putchar(aByte);
}

int printNameOfClasscount(int classOop, int cnt) {
	if (cnt <= 0) {
		return print("bad class");
	}
	if ((sizeBitsOf(classOop)) == 32) {
		printNameOfClasscount(longAt(((((char *) classOop)) + 4) + (6 << 2)), cnt - 1);
		print(" class");
	} else {
		printStringOf(longAt(((((char *) classOop)) + 4) + (6 << 2)));
	}
}

int printNum(int n) {
	printf("%ld", (long) n);
}

int printStringOf(int oop) {
    int i;
    int fmt;
    int cnt;

	fmt = (((unsigned) (longAt(oop))) >> 8) & 15;
	if (fmt < 8) {
		return null;
	}
	cnt = ((100 < (lengthOf(oop))) ? 100 : (lengthOf(oop)));
	i = 0;
	while (i < cnt) {
		/* begin printChar: */
		putchar(byteAt(((((char *) oop)) + 4) + i));
		i += 1;
	}
}

int push(int object) {
    int sp;

	longAtput(sp = stackPointer + 4, object);
	stackPointer = sp;
}

int pushBool(int trueOrFalse) {
    int sp;
    int sp1;

	if (trueOrFalse) {
		/* begin push: */
		longAtput(sp = stackPointer + 4, trueObj);
		stackPointer = sp;
	} else {
		/* begin push: */
		longAtput(sp1 = stackPointer + 4, falseObj);
		stackPointer = sp1;
	}
}

int pushFloat(double f) {
    int newFloatObj;
    int sp;

	newFloatObj = instantiateSmallClasssizeInBytesfill(longAt(((((char *) specialObjectsOop)) + 4) + (9 << 2)), 12, 0);
	storeFloatAtfrom(newFloatObj + 4, f);
	/* begin push: */
	longAtput(sp = stackPointer + 4, newFloatObj);
	stackPointer = sp;
}

int pushInteger(int integerValue) {
    int sp;

	/* begin push: */
	longAtput(sp = stackPointer + 4, ((integerValue << 1) | 1));
	stackPointer = sp;
}

int pushRemappableOop(int oop) {
	remapBuffer[remapBufferCount += 1] = oop;
}

int putLongtoFile(int n, sqImageFile f) {
    int wordsWritten;

	wordsWritten = sqImageFileWrite(&n, sizeof(int), 1, f);
	/* begin success: */
	successFlag = (wordsWritten == 1) && successFlag;
}

int putToSleep(int aProcess) {
    int priority;
    int processLists;
    int processList;
    int lastLink;

	priority = ((longAt(((((char *) aProcess)) + 4) + (2 << 2))) >> 1);
	processLists = longAt(((((char *) (longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (3 << 2))))) + 4) + (1 << 2))))) + 4) + (0 << 2));
	processList = longAt(((((char *) processLists)) + 4) + ((priority - 1) << 2));
	/* begin addLastLink:toList: */
	if ((longAt(((((char *) processList)) + 4) + (0 << 2))) == nilObj) {
		/* begin storePointer:ofObject:withValue: */
		if (processList < youngStart) {
			possibleRootStoreIntovalue(processList, aProcess);
		}
		longAtput(((((char *) processList)) + 4) + (0 << 2), aProcess);
	} else {
		lastLink = longAt(((((char *) processList)) + 4) + (1 << 2));
		/* begin storePointer:ofObject:withValue: */
		if (lastLink < youngStart) {
			possibleRootStoreIntovalue(lastLink, aProcess);
		}
		longAtput(((((char *) lastLink)) + 4) + (0 << 2), aProcess);
	}
	/* begin storePointer:ofObject:withValue: */
	if (processList < youngStart) {
		possibleRootStoreIntovalue(processList, aProcess);
	}
	longAtput(((((char *) processList)) + 4) + (1 << 2), aProcess);
	/* begin storePointer:ofObject:withValue: */
	if (aProcess < youngStart) {
		possibleRootStoreIntovalue(aProcess, processList);
	}
	longAtput(((((char *) aProcess)) + 4) + (3 << 2), processList);
}

int quickCheckForInterrupts(void) {
	if ((interruptCheckCounter -= 1) <= 0) {
		checkForInterrupts();
	}
}

int quickFetchIntegerofObject(int fieldIndex, int objectPointer) {
	return ((longAt(((((char *) objectPointer)) + 4) + (fieldIndex << 2))) >> 1);
}

int readImageFromFileHeapSize(sqImageFile f, int desiredHeapSize) {
    int swapBytes;
    int dataSize;
    int minimumMemory;
    int memStart;
    int bytesRead;
    int bytesToShift;
    int headerStart;
    int headerSize;
    int oldBaseAddr;
    int startAddr;
    int addr;
    int i;
    int sched;
    int proc;
    int activeCntx;
    int tmp;
    int methodHeader;
    int wordAddr;
    int oop;
    int fmt;
    int stopAddr;
    int addr1;
    int chunk;
    int extra;
    int type;
    int extra1;
    int sz;
    int header;
    int extra2;
    int type1;
    int extra11;

	swapBytes = checkImageVersionFrom(f);
	headerStart = (sqImageFilePosition(f)) - 4;
	headerSize = getLongFromFileswap(f, swapBytes);
	dataSize = getLongFromFileswap(f, swapBytes);
	oldBaseAddr = getLongFromFileswap(f, swapBytes);
	specialObjectsOop = getLongFromFileswap(f, swapBytes);
	lastHash = getLongFromFileswap(f, swapBytes);
	savedWindowSize = getLongFromFileswap(f, swapBytes);
	fullScreenFlag = getLongFromFileswap(f, swapBytes);
	if (lastHash == 0) {
		lastHash = 999;
	}
	minimumMemory = dataSize + 80000;
	if (desiredHeapSize < minimumMemory) {
		error("Insufficient memory for this image");
	}
	memory = (unsigned char *) sqAllocateMemory(minimumMemory, desiredHeapSize);
	if (memory == null) {
		error("Failed to allocate memory for the heap");
	}
	memStart = startOfMemory();
	memoryLimit = (memStart + desiredHeapSize) - 24;
	endOfMemory = memStart + dataSize;
	sqImageFileSeek(f, headerStart + headerSize);
	bytesRead = sqImageFileRead(memory, sizeof(unsigned char), dataSize, f);
	if (bytesRead != dataSize) {
		error("Read failed or premature end of image file");
	}
	if (swapBytes) {
		/* begin reverseBytesInImage */
		/* begin reverseBytesFrom:to: */
		startAddr = startOfMemory();
		addr = startAddr;
		while (addr < endOfMemory) {
			longAtput(addr, ((((((unsigned) (longAt(addr)) >> 24)) & 255) + ((((unsigned) (longAt(addr)) >> 8)) & 65280)) + ((((unsigned) (longAt(addr)) << 8)) & 16711680)) + ((((unsigned) (longAt(addr)) << 24)) & 4278190080U));
			addr += 4;
		}
		/* begin byteSwapByteObjects */
		/* begin oopFromChunk: */
		chunk = startOfMemory();
		/* begin extraHeaderBytes: */
		type = (longAt(chunk)) & 3;
		if (type > 1) {
			extra1 = 0;
		} else {
			if (type == 1) {
				extra1 = 4;
			} else {
				extra1 = 8;
			}
		}
		extra = extra1;
		oop = chunk + extra;
		while (oop < endOfMemory) {
			if (!(((longAt(oop)) & 3) == 2)) {
				fmt = (((unsigned) (longAt(oop))) >> 8) & 15;
				if (fmt >= 8) {
					wordAddr = oop + 4;
					if (fmt >= 12) {
						methodHeader = longAt(oop + 4);
						wordAddr = (wordAddr + 4) + (((((unsigned) methodHeader) >> 10) & 255) * 4);
					}
					/* begin reverseBytesFrom:to: */
					stopAddr = oop + (sizeBitsOf(oop));
					addr1 = wordAddr;
					while (addr1 < stopAddr) {
						longAtput(addr1, ((((((unsigned) (longAt(addr1)) >> 24)) & 255) + ((((unsigned) (longAt(addr1)) >> 8)) & 65280)) + ((((unsigned) (longAt(addr1)) << 8)) & 16711680)) + ((((unsigned) (longAt(addr1)) << 24)) & 4278190080U));
						addr1 += 4;
					}
				}
			}
			/* begin objectAfter: */
			if (checkAssertions) {
				if (oop >= endOfMemory) {
					error("no objects after the end of memory");
				}
			}
			if (((longAt(oop)) & 3) == 2) {
				sz = (longAt(oop)) & 536870908;
			} else {
				/* begin sizeBitsOf: */
				header = longAt(oop);
				if ((header & 3) == 0) {
					sz = (longAt(oop - 8)) & 4294967292U;
					goto l1;
				} else {
					sz = header & 252;
					goto l1;
				}
			l1:	/* end sizeBitsOf: */;
			}
			/* begin oopFromChunk: */
			/* begin extraHeaderBytes: */
			type1 = (longAt(oop + sz)) & 3;
			if (type1 > 1) {
				extra11 = 0;
			} else {
				if (type1 == 1) {
					extra11 = 4;
				} else {
					extra11 = 8;
				}
			}
			extra2 = extra11;
			oop = (oop + sz) + extra2;
		}
	}
	bytesToShift = memStart - oldBaseAddr;
	/* begin initializeInterpreter: */
	initializeObjectMemory(bytesToShift);
	initBBOpTable();
	activeContext = nilObj;
	theHomeContext = nilObj;
	method = nilObj;
	receiver = nilObj;
	messageSelector = nilObj;
	newMethod = nilObj;
	/* begin flushMethodCache */
	for (i = 1; i <= 2048; i += 1) {
		methodCache[i] = 0;
	}
	mcProbe = 0;
	/* begin loadInitialContext */
	sched = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (3 << 2))))) + 4) + (1 << 2));
	proc = longAt(((((char *) sched)) + 4) + (1 << 2));
	activeContext = longAt(((((char *) proc)) + 4) + (1 << 2));
	if (activeContext < youngStart) {
		beRootIfOld(activeContext);
	}
	/* begin fetchContextRegisters: */
	activeCntx = activeContext;
	tmp = longAt(((((char *) activeCntx)) + 4) + (3 << 2));
	if ((tmp & 1)) {
		tmp = longAt(((((char *) activeCntx)) + 4) + (5 << 2));
		if (tmp < youngStart) {
			beRootIfOld(tmp);
		}
	} else {
		tmp = activeCntx;
	}
	theHomeContext = tmp;
	receiver = longAt(((((char *) tmp)) + 4) + (5 << 2));
	method = longAt(((((char *) tmp)) + 4) + (3 << 2));
	tmp = ((longAt(((((char *) activeCntx)) + 4) + (1 << 2))) >> 1);
	instructionPointer = ((method + tmp) + 4) - 2;
	tmp = ((longAt(((((char *) activeCntx)) + 4) + (2 << 2))) >> 1);
	stackPointer = (activeCntx + 4) + (((6 + tmp) - 1) * 4);
	reclaimableContextCount = 0;
	interruptCheckCounter = 0;
	nextPollTick = 0;
	nextWakeupTick = 0;
	lastTick = 0;
	interruptKeycode = 2094;
	interruptPending = false;
	semaphoresToSignalCount = 0;
	deferDisplayUpdates = false;
	return dataSize;
}

int recycleContextIfPossiblemethodContextClass(int cntxOop, int methodCntxClass) {
    int cntxHeader;
    int ccField;
    int isMethodCntx;

	if (cntxOop >= youngStart) {
		cntxHeader = longAt(cntxOop);
		ccField = cntxHeader & 126976;
		if (ccField == 0) {
			isMethodCntx = ((longAt(cntxOop - 4)) & 4294967292U) == methodCntxClass;
		} else {
			isMethodCntx = ccField == (((longAt(((((char *) methodCntxClass)) + 4) + (2 << 2))) - 1) & 126976);
		}
		if (isMethodCntx) {
			if ((cntxHeader & 252) == 76) {
				longAtput(((((char *) cntxOop)) + 4) + (0 << 2), freeSmallContexts);
				freeSmallContexts = cntxOop;
			} else {
				longAtput(((((char *) cntxOop)) + 4) + (0 << 2), freeLargeContexts);
				freeLargeContexts = cntxOop;
			}
		}
	}
}

int remap(int oop) {
    int fwdBlock;

	if (((oop & 1) == 0) && (((longAt(oop)) & 2147483648U) != 0)) {
		fwdBlock = (longAt(oop)) & 2147483644;
		if (checkAssertions) {
			/* begin fwdBlockValidate: */
			if (!((fwdBlock > endOfMemory) && ((fwdBlock <= fwdTableNext) && ((fwdBlock & 3) == 0)))) {
				error("invalid fwd table entry");
			}
		}
		return longAt(fwdBlock);
	}
	return oop;
}

int remapClassOf(int oop) {
    int newClassOop;
    int fwdBlock;
    int classHeader;
    int classOop;
    int newClassHeader;

	if (((longAt(oop)) & 3) == 3) {
		return null;
	}
	classHeader = longAt(oop - 4);
	classOop = classHeader & 4294967292U;
	if (((classOop & 1) == 0) && (((longAt(classOop)) & 2147483648U) != 0)) {
		fwdBlock = (longAt(classOop)) & 2147483644;
		if (checkAssertions) {
			/* begin fwdBlockValidate: */
			if (!((fwdBlock > endOfMemory) && ((fwdBlock <= fwdTableNext) && ((fwdBlock & 3) == 0)))) {
				error("invalid fwd table entry");
			}
		}
		newClassOop = longAt(fwdBlock);
		newClassHeader = newClassOop | (classHeader & 3);
		longAtput(oop - 4, newClassHeader);
		if ((oop < youngStart) && (newClassOop >= youngStart)) {
			beRootWhileForwarding(oop);
		}
	}
}

int remapFieldsAndClassOf(int oop) {
    int fwdBlock;
    int fieldOffset;
    int fieldOop;
    int newOop;
    int methodHeader;
    int size;
    int fwdBlock1;
    int fmt;
    int header;
    int newClassOop;
    int fwdBlock2;
    int classHeader;
    int classOop;
    int newClassHeader;

	/* begin lastPointerWhileForwarding: */
	header = longAt(oop);
	if ((header & 2147483648U) != 0) {
		fwdBlock1 = header & 2147483644;
		if (checkAssertions) {
			/* begin fwdBlockValidate: */
			if (!((fwdBlock1 > endOfMemory) && ((fwdBlock1 <= fwdTableNext) && ((fwdBlock1 & 3) == 0)))) {
				error("invalid fwd table entry");
			}
		}
		header = longAt(fwdBlock1 + 4);
	}
	fmt = (((unsigned) header) >> 8) & 15;
	if (fmt < 4) {
		if ((header & 3) == 0) {
			size = (longAt(oop - 8)) & 268435452;
		} else {
			size = header & 252;
		}
		fieldOffset = size - 4;
		goto l1;
	}
	if (fmt < 12) {
		fieldOffset = 0;
		goto l1;
	}
	methodHeader = longAt(oop + 4);
	fieldOffset = (((((unsigned) methodHeader) >> 10) & 255) * 4) + 4;
l1:	/* end lastPointerWhileForwarding: */;
	while (fieldOffset >= 4) {
		fieldOop = longAt(oop + fieldOffset);
		if (((fieldOop & 1) == 0) && (((longAt(fieldOop)) & 2147483648U) != 0)) {
			fwdBlock = (longAt(fieldOop)) & 2147483644;
			if (checkAssertions) {
				/* begin fwdBlockValidate: */
				if (!((fwdBlock > endOfMemory) && ((fwdBlock <= fwdTableNext) && ((fwdBlock & 3) == 0)))) {
					error("invalid fwd table entry");
				}
			}
			newOop = longAt(fwdBlock);
			longAtput(oop + fieldOffset, newOop);
			if ((oop < youngStart) && (newOop >= youngStart)) {
				beRootWhileForwarding(oop);
			}
		}
		fieldOffset -= 4;
	}
	/* begin remapClassOf: */
	if (((longAt(oop)) & 3) == 3) {
		goto l2;
	}
	classHeader = longAt(oop - 4);
	classOop = classHeader & 4294967292U;
	if (((classOop & 1) == 0) && (((longAt(classOop)) & 2147483648U) != 0)) {
		fwdBlock2 = (longAt(classOop)) & 2147483644;
		if (checkAssertions) {
			/* begin fwdBlockValidate: */
			if (!((fwdBlock2 > endOfMemory) && ((fwdBlock2 <= fwdTableNext) && ((fwdBlock2 & 3) == 0)))) {
				error("invalid fwd table entry");
			}
		}
		newClassOop = longAt(fwdBlock2);
		newClassHeader = newClassOop | (classHeader & 3);
		longAtput(oop - 4, newClassHeader);
		if ((oop < youngStart) && (newClassOop >= youngStart)) {
			beRootWhileForwarding(oop);
		}
	}
l2:	/* end remapClassOf: */;
}

int removeFirstLinkOfList(int aList) {
    int next;
    int first;
    int last;
    int valuePointer;
    int valuePointer1;
    int valuePointer2;

	first = longAt(((((char *) aList)) + 4) + (0 << 2));
	last = longAt(((((char *) aList)) + 4) + (1 << 2));
	if (first == last) {
		/* begin storePointer:ofObject:withValue: */
		valuePointer = nilObj;
		if (aList < youngStart) {
			possibleRootStoreIntovalue(aList, valuePointer);
		}
		longAtput(((((char *) aList)) + 4) + (0 << 2), valuePointer);
		/* begin storePointer:ofObject:withValue: */
		valuePointer1 = nilObj;
		if (aList < youngStart) {
			possibleRootStoreIntovalue(aList, valuePointer1);
		}
		longAtput(((((char *) aList)) + 4) + (1 << 2), valuePointer1);
	} else {
		next = longAt(((((char *) first)) + 4) + (0 << 2));
		/* begin storePointer:ofObject:withValue: */
		if (aList < youngStart) {
			possibleRootStoreIntovalue(aList, next);
		}
		longAtput(((((char *) aList)) + 4) + (0 << 2), next);
	}
	/* begin storePointer:ofObject:withValue: */
	valuePointer2 = nilObj;
	if (first < youngStart) {
		possibleRootStoreIntovalue(first, valuePointer2);
	}
	longAtput(((((char *) first)) + 4) + (0 << 2), valuePointer2);
	return first;
}

int reportContexts(void) {
    int small;
    int big;
    int cntxt;

	big = 0;
	cntxt = freeLargeContexts;
	while (!(cntxt == 1)) {
		big += 1;
		cntxt = longAt(((((char *) cntxt)) + 4) + (0 << 2));
	}
	small = 0;
	cntxt = freeSmallContexts;
	while (!(cntxt == 1)) {
		small += 1;
		cntxt = longAt(((((char *) cntxt)) + 4) + (0 << 2));
	}
	print("Recycled contexts: ");
	printNum(small);
	print(" small, ");
	printNum(big);
	print(" large (");
	printNum((big * 156) + (small * 76));
	print(" bytes)");
	/* begin cr */
	printf("\n");
}

int restoreHeaderOf(int oop) {
    int fwdBlock;
    int fwdHeader;

	fwdHeader = longAt(oop);
	fwdBlock = fwdHeader & 2147483644;
	if (checkAssertions) {
		if ((fwdHeader & 2147483648U) == 0) {
			error("attempting to restore the header of an object that has no forwarding block");
		}
		/* begin fwdBlockValidate: */
		if (!((fwdBlock > endOfMemory) && ((fwdBlock <= fwdTableNext) && ((fwdBlock & 3) == 0)))) {
			error("invalid fwd table entry");
		}
	}
	longAtput(oop, longAt(fwdBlock + 4));
}

int restoreHeadersAfterBecomingwith(int list1, int list2) {
    int fieldOffset;
    int oop1;
    int oop2;
    int hdr1;
    int hdr2;
    int fwdBlock;
    int fwdHeader;
    int fwdBlock1;
    int fwdHeader1;
    int methodHeader;
    int sz;
    int fmt;
    int header;
    int type;

	/* begin lastPointerOf: */
	fmt = (((unsigned) (longAt(list1))) >> 8) & 15;
	if (fmt < 4) {
		/* begin sizeBitsOfSafe: */
		header = longAt(list1);
		/* begin rightType: */
		if ((header & 252) == 0) {
			type = 0;
			goto l2;
		} else {
			if ((header & 126976) == 0) {
				type = 1;
				goto l2;
			} else {
				type = 3;
				goto l2;
			}
		}
	l2:	/* end rightType: */;
		if (type == 0) {
			sz = (longAt(list1 - 8)) & 4294967292U;
			goto l3;
		} else {
			sz = header & 252;
			goto l3;
		}
	l3:	/* end sizeBitsOfSafe: */;
		fieldOffset = sz - 4;
		goto l1;
	}
	if (fmt < 12) {
		fieldOffset = 0;
		goto l1;
	}
	methodHeader = longAt(list1 + 4);
	fieldOffset = (((((unsigned) methodHeader) >> 10) & 255) * 4) + 4;
l1:	/* end lastPointerOf: */;
	while (fieldOffset >= 4) {
		oop1 = longAt(list1 + fieldOffset);
		oop2 = longAt(list2 + fieldOffset);
		/* begin restoreHeaderOf: */
		fwdHeader = longAt(oop1);
		fwdBlock = fwdHeader & 2147483644;
		if (checkAssertions) {
			if ((fwdHeader & 2147483648U) == 0) {
				error("attempting to restore the header of an object that has no forwarding block");
			}
			/* begin fwdBlockValidate: */
			if (!((fwdBlock > endOfMemory) && ((fwdBlock <= fwdTableNext) && ((fwdBlock & 3) == 0)))) {
				error("invalid fwd table entry");
			}
		}
		longAtput(oop1, longAt(fwdBlock + 4));
		/* begin restoreHeaderOf: */
		fwdHeader1 = longAt(oop2);
		fwdBlock1 = fwdHeader1 & 2147483644;
		if (checkAssertions) {
			if ((fwdHeader1 & 2147483648U) == 0) {
				error("attempting to restore the header of an object that has no forwarding block");
			}
			/* begin fwdBlockValidate: */
			if (!((fwdBlock1 > endOfMemory) && ((fwdBlock1 <= fwdTableNext) && ((fwdBlock1 & 3) == 0)))) {
				error("invalid fwd table entry");
			}
		}
		longAtput(oop2, longAt(fwdBlock1 + 4));
		/* begin exchangeHashBits:with: */
		hdr1 = longAt(oop1);
		hdr2 = longAt(oop2);
		longAtput(oop1, (hdr1 & 3758227455U) | (hdr2 & 536739840));
		longAtput(oop2, (hdr2 & 3758227455U) | (hdr1 & 536739840));
		fieldOffset -= 4;
	}
}

int resume(int aProcess) {
    int activeProc;
    int activePriority;
    int newPriority;
    int sched;
    int oldProc;
    int valuePointer;
    int tmp;
    int priority;
    int processLists;
    int processList;
    int lastLink;
    int priority1;
    int processLists1;
    int processList1;
    int lastLink1;

	activeProc = longAt(((((char *) (longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (3 << 2))))) + 4) + (1 << 2))))) + 4) + (1 << 2));
	activePriority = ((longAt(((((char *) activeProc)) + 4) + (2 << 2))) >> 1);
	newPriority = ((longAt(((((char *) aProcess)) + 4) + (2 << 2))) >> 1);
	if (newPriority > activePriority) {
		/* begin putToSleep: */
		priority = ((longAt(((((char *) activeProc)) + 4) + (2 << 2))) >> 1);
		processLists = longAt(((((char *) (longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (3 << 2))))) + 4) + (1 << 2))))) + 4) + (0 << 2));
		processList = longAt(((((char *) processLists)) + 4) + ((priority - 1) << 2));
		/* begin addLastLink:toList: */
		if ((longAt(((((char *) processList)) + 4) + (0 << 2))) == nilObj) {
			/* begin storePointer:ofObject:withValue: */
			if (processList < youngStart) {
				possibleRootStoreIntovalue(processList, activeProc);
			}
			longAtput(((((char *) processList)) + 4) + (0 << 2), activeProc);
		} else {
			lastLink = longAt(((((char *) processList)) + 4) + (1 << 2));
			/* begin storePointer:ofObject:withValue: */
			if (lastLink < youngStart) {
				possibleRootStoreIntovalue(lastLink, activeProc);
			}
			longAtput(((((char *) lastLink)) + 4) + (0 << 2), activeProc);
		}
		/* begin storePointer:ofObject:withValue: */
		if (processList < youngStart) {
			possibleRootStoreIntovalue(processList, activeProc);
		}
		longAtput(((((char *) processList)) + 4) + (1 << 2), activeProc);
		/* begin storePointer:ofObject:withValue: */
		if (activeProc < youngStart) {
			possibleRootStoreIntovalue(activeProc, processList);
		}
		longAtput(((((char *) activeProc)) + 4) + (3 << 2), processList);
		/* begin transferTo: */
		sched = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (3 << 2))))) + 4) + (1 << 2));
		oldProc = longAt(((((char *) sched)) + 4) + (1 << 2));
		/* begin storePointer:ofObject:withValue: */
		valuePointer = activeContext;
		if (oldProc < youngStart) {
			possibleRootStoreIntovalue(oldProc, valuePointer);
		}
		longAtput(((((char *) oldProc)) + 4) + (1 << 2), valuePointer);
		/* begin storePointer:ofObject:withValue: */
		if (sched < youngStart) {
			possibleRootStoreIntovalue(sched, aProcess);
		}
		longAtput(((((char *) sched)) + 4) + (1 << 2), aProcess);
		/* begin newActiveContext: */
		/* begin storeContextRegisters: */
		longAtput(((((char *) activeContext)) + 4) + (1 << 2), ((((instructionPointer - method) - (4 - 2)) << 1) | 1));
		longAtput(((((char *) activeContext)) + 4) + (2 << 2), (((((((unsigned) ((stackPointer - activeContext) - 4)) >> 2) - 6) + 1) << 1) | 1));
		if ((longAt(((((char *) aProcess)) + 4) + (1 << 2))) < youngStart) {
			beRootIfOld(longAt(((((char *) aProcess)) + 4) + (1 << 2)));
		}
		activeContext = longAt(((((char *) aProcess)) + 4) + (1 << 2));
		/* begin fetchContextRegisters: */
		tmp = longAt(((((char *) (longAt(((((char *) aProcess)) + 4) + (1 << 2))))) + 4) + (3 << 2));
		if ((tmp & 1)) {
			tmp = longAt(((((char *) (longAt(((((char *) aProcess)) + 4) + (1 << 2))))) + 4) + (5 << 2));
			if (tmp < youngStart) {
				beRootIfOld(tmp);
			}
		} else {
			tmp = longAt(((((char *) aProcess)) + 4) + (1 << 2));
		}
		theHomeContext = tmp;
		receiver = longAt(((((char *) tmp)) + 4) + (5 << 2));
		method = longAt(((((char *) tmp)) + 4) + (3 << 2));
		tmp = ((longAt(((((char *) (longAt(((((char *) aProcess)) + 4) + (1 << 2))))) + 4) + (1 << 2))) >> 1);
		instructionPointer = ((method + tmp) + 4) - 2;
		tmp = ((longAt(((((char *) (longAt(((((char *) aProcess)) + 4) + (1 << 2))))) + 4) + (2 << 2))) >> 1);
		stackPointer = ((longAt(((((char *) aProcess)) + 4) + (1 << 2))) + 4) + (((6 + tmp) - 1) * 4);
		reclaimableContextCount = 0;
	} else {
		/* begin putToSleep: */
		priority1 = ((longAt(((((char *) aProcess)) + 4) + (2 << 2))) >> 1);
		processLists1 = longAt(((((char *) (longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (3 << 2))))) + 4) + (1 << 2))))) + 4) + (0 << 2));
		processList1 = longAt(((((char *) processLists1)) + 4) + ((priority1 - 1) << 2));
		/* begin addLastLink:toList: */
		if ((longAt(((((char *) processList1)) + 4) + (0 << 2))) == nilObj) {
			/* begin storePointer:ofObject:withValue: */
			if (processList1 < youngStart) {
				possibleRootStoreIntovalue(processList1, aProcess);
			}
			longAtput(((((char *) processList1)) + 4) + (0 << 2), aProcess);
		} else {
			lastLink1 = longAt(((((char *) processList1)) + 4) + (1 << 2));
			/* begin storePointer:ofObject:withValue: */
			if (lastLink1 < youngStart) {
				possibleRootStoreIntovalue(lastLink1, aProcess);
			}
			longAtput(((((char *) lastLink1)) + 4) + (0 << 2), aProcess);
		}
		/* begin storePointer:ofObject:withValue: */
		if (processList1 < youngStart) {
			possibleRootStoreIntovalue(processList1, aProcess);
		}
		longAtput(((((char *) processList1)) + 4) + (1 << 2), aProcess);
		/* begin storePointer:ofObject:withValue: */
		if (aProcess < youngStart) {
			possibleRootStoreIntovalue(aProcess, processList1);
		}
		longAtput(((((char *) aProcess)) + 4) + (3 << 2), processList1);
	}
}

int returnAtlastIndexlefttop(int stopIndex, int lastIndex, int left, int top) {
    int objectPointer;

	stopCode = stObjectat(scanStopArray, stopIndex);
	if (!successFlag) {
		return null;
	}
	/* begin storeInteger:ofObject:withValue: */
	objectPointer = bitBltOop;
	if ((lastIndex ^ (lastIndex << 1)) >= 0) {
		longAtput(((((char *) objectPointer)) + 4) + (15 << 2), ((lastIndex << 1) | 1));
	} else {
		primitiveFail();
	}
	if (scanDisplayFlag) {
		affectedL = left;
		affectedR = bbW + dx;
		affectedT = top;
		affectedB = bbH + dy;
	}
}

int reverseBytesFromto(int startAddr, int stopAddr) {
    int addr;

	addr = startAddr;
	while (addr < stopAddr) {
		longAtput(addr, ((((((unsigned) (longAt(addr)) >> 24)) & 255) + ((((unsigned) (longAt(addr)) >> 8)) & 65280)) + ((((unsigned) (longAt(addr)) << 8)) & 16711680)) + ((((unsigned) (longAt(addr)) << 24)) & 4278190080U));
		addr += 4;
	}
}

int reverseBytesInImage(void) {
    int startAddr;
    int addr;
    int methodHeader;
    int wordAddr;
    int oop;
    int fmt;
    int stopAddr;
    int addr1;
    int chunk;
    int extra;
    int type;
    int extra1;
    int sz;
    int header;
    int extra2;
    int type1;
    int extra11;

	/* begin reverseBytesFrom:to: */
	startAddr = startOfMemory();
	addr = startAddr;
	while (addr < endOfMemory) {
		longAtput(addr, ((((((unsigned) (longAt(addr)) >> 24)) & 255) + ((((unsigned) (longAt(addr)) >> 8)) & 65280)) + ((((unsigned) (longAt(addr)) << 8)) & 16711680)) + ((((unsigned) (longAt(addr)) << 24)) & 4278190080U));
		addr += 4;
	}
	/* begin byteSwapByteObjects */
	/* begin oopFromChunk: */
	chunk = startOfMemory();
	/* begin extraHeaderBytes: */
	type = (longAt(chunk)) & 3;
	if (type > 1) {
		extra1 = 0;
	} else {
		if (type == 1) {
			extra1 = 4;
		} else {
			extra1 = 8;
		}
	}
	extra = extra1;
	oop = chunk + extra;
	while (oop < endOfMemory) {
		if (!(((longAt(oop)) & 3) == 2)) {
			fmt = (((unsigned) (longAt(oop))) >> 8) & 15;
			if (fmt >= 8) {
				wordAddr = oop + 4;
				if (fmt >= 12) {
					methodHeader = longAt(oop + 4);
					wordAddr = (wordAddr + 4) + (((((unsigned) methodHeader) >> 10) & 255) * 4);
				}
				/* begin reverseBytesFrom:to: */
				stopAddr = oop + (sizeBitsOf(oop));
				addr1 = wordAddr;
				while (addr1 < stopAddr) {
					longAtput(addr1, ((((((unsigned) (longAt(addr1)) >> 24)) & 255) + ((((unsigned) (longAt(addr1)) >> 8)) & 65280)) + ((((unsigned) (longAt(addr1)) << 8)) & 16711680)) + ((((unsigned) (longAt(addr1)) << 24)) & 4278190080U));
					addr1 += 4;
				}
			}
		}
		/* begin objectAfter: */
		if (checkAssertions) {
			if (oop >= endOfMemory) {
				error("no objects after the end of memory");
			}
		}
		if (((longAt(oop)) & 3) == 2) {
			sz = (longAt(oop)) & 536870908;
		} else {
			/* begin sizeBitsOf: */
			header = longAt(oop);
			if ((header & 3) == 0) {
				sz = (longAt(oop - 8)) & 4294967292U;
				goto l1;
			} else {
				sz = header & 252;
				goto l1;
			}
		l1:	/* end sizeBitsOf: */;
		}
		/* begin oopFromChunk: */
		/* begin extraHeaderBytes: */
		type1 = (longAt(oop + sz)) & 3;
		if (type1 > 1) {
			extra11 = 0;
		} else {
			if (type1 == 1) {
				extra11 = 4;
			} else {
				extra11 = 8;
			}
		}
		extra2 = extra11;
		oop = (oop + sz) + extra2;
	}
}

int rgbAddwith(int sourceWord, int destinationWord) {
	if (destPixSize < 16) {
		return partitionedAddtonBitsnPartitions(sourceWord, destinationWord, destPixSize, pixPerWord);
	}
	if (destPixSize == 16) {
		return (partitionedAddtonBitsnPartitions(sourceWord, destinationWord, 5, 3)) + ((partitionedAddtonBitsnPartitions(((unsigned) sourceWord) >> 16, ((unsigned) destinationWord) >> 16, 5, 3)) << 16);
	} else {
		return partitionedAddtonBitsnPartitions(sourceWord, destinationWord, 8, 3);
	}
}

int rgbDiffwith(int sourceWord, int destinationWord) {
    int destPixVal;
    int pixMask;
    int destShifted;
    int sourceShifted;
    int sourcePixVal;
    int diff;
    int maskShifted;
    int i;
    int bitsPerColor;
    int rgbMask;

	pixMask = (1 << destPixSize) - 1;
	if (destPixSize == 16) {
		bitsPerColor = 5;
		rgbMask = 31;
	} else {
		bitsPerColor = 8;
		rgbMask = 255;
	}
	maskShifted = destMask;
	destShifted = destinationWord;
	sourceShifted = sourceWord;
	for (i = 1; i <= pixPerWord; i += 1) {
		if ((maskShifted & pixMask) > 0) {
			destPixVal = destShifted & pixMask;
			sourcePixVal = sourceShifted & pixMask;
			if (destPixSize < 16) {
				if (sourcePixVal == destPixVal) {
					diff = 0;
				} else {
					diff = 1;
				}
			} else {
				diff = partitionedSubfromnBitsnPartitions(sourcePixVal, destPixVal, bitsPerColor, 3);
				diff = ((diff & rgbMask) + ((((unsigned) diff) >> bitsPerColor) & rgbMask)) + ((((unsigned) (((unsigned) diff) >> bitsPerColor)) >> bitsPerColor) & rgbMask);
			}
			bitCount += diff;
		}
		maskShifted = ((unsigned) maskShifted) >> destPixSize;
		sourceShifted = ((unsigned) sourceShifted) >> destPixSize;
		destShifted = ((unsigned) destShifted) >> destPixSize;
	}
	return destinationWord;
}

int rgbMapfromto(int sourcePixel, int nBitsIn, int nBitsOut) {
    int mask;
    int srcPix;
    int destPix;
    int d;

	if ((d = nBitsOut - nBitsIn) > 0) {
		mask = (1 << nBitsIn) - 1;
		srcPix = sourcePixel << d;
		mask = mask << d;
		destPix = srcPix & mask;
		mask = mask << nBitsOut;
		srcPix = srcPix << d;
		return (destPix + (srcPix & mask)) + ((srcPix << d) & (mask << nBitsOut));
	} else {
		if (d == 0) {
			return sourcePixel;
		}
		if (sourcePixel == 0) {
			return sourcePixel;
		}
		d = nBitsIn - nBitsOut;
		mask = (1 << nBitsOut) - 1;
		srcPix = ((unsigned) sourcePixel) >> d;
		destPix = srcPix & mask;
		mask = mask << nBitsOut;
		srcPix = ((unsigned) srcPix) >> d;
		destPix = (destPix + (srcPix & mask)) + ((((unsigned) srcPix) >> d) & (mask << nBitsOut));
		if (destPix == 0) {
			return 1;
		}
		return destPix;
	}
}

int rgbMaxwith(int sourceWord, int destinationWord) {
    int mask;
    int i;
    int result;
    int mask3;
    int i1;
    int result1;

	if (destPixSize < 16) {
		/* begin partitionedMax:with:nBits:nPartitions: */
		mask = (1 << destPixSize) - 1;
		result = 0;
		for (i = 1; i <= pixPerWord; i += 1) {
			result = result | ((((destinationWord & mask) < (sourceWord & mask)) ? (sourceWord & mask) : (destinationWord & mask)));
			mask = mask << destPixSize;
		}
		return result;
	}
	if (destPixSize == 16) {
		return (partitionedMaxwithnBitsnPartitions(sourceWord, destinationWord, 5, 3)) + ((partitionedMaxwithnBitsnPartitions(((unsigned) sourceWord) >> 16, ((unsigned) destinationWord) >> 16, 5, 3)) << 16);
	} else {
		/* begin partitionedMax:with:nBits:nPartitions: */
		mask3 = (1 << 8) - 1;
		result1 = 0;
		for (i1 = 1; i1 <= 3; i1 += 1) {
			result1 = result1 | ((((destinationWord & mask3) < (sourceWord & mask3)) ? (sourceWord & mask3) : (destinationWord & mask3)));
			mask3 = mask3 << 8;
		}
		return result1;
	}
}

int rgbMinwith(int sourceWord, int destinationWord) {
    int mask;
    int i;
    int result;
    int mask3;
    int i1;
    int result1;

	if (destPixSize < 16) {
		/* begin partitionedMin:with:nBits:nPartitions: */
		mask = (1 << destPixSize) - 1;
		result = 0;
		for (i = 1; i <= pixPerWord; i += 1) {
			result = result | ((((destinationWord & mask) < (sourceWord & mask)) ? (destinationWord & mask) : (sourceWord & mask)));
			mask = mask << destPixSize;
		}
		return result;
	}
	if (destPixSize == 16) {
		return (partitionedMinwithnBitsnPartitions(sourceWord, destinationWord, 5, 3)) + ((partitionedMinwithnBitsnPartitions(((unsigned) sourceWord) >> 16, ((unsigned) destinationWord) >> 16, 5, 3)) << 16);
	} else {
		/* begin partitionedMin:with:nBits:nPartitions: */
		mask3 = (1 << 8) - 1;
		result1 = 0;
		for (i1 = 1; i1 <= 3; i1 += 1) {
			result1 = result1 | ((((destinationWord & mask3) < (sourceWord & mask3)) ? (destinationWord & mask3) : (sourceWord & mask3)));
			mask3 = mask3 << 8;
		}
		return result1;
	}
}

int rgbMinInvertwith(int wordToInvert, int destinationWord) {
    int sourceWord;
    int mask;
    int i;
    int result;
    int mask3;
    int i1;
    int result1;

	sourceWord = ~wordToInvert;
	if (destPixSize < 16) {
		/* begin partitionedMin:with:nBits:nPartitions: */
		mask = (1 << destPixSize) - 1;
		result = 0;
		for (i = 1; i <= pixPerWord; i += 1) {
			result = result | ((((destinationWord & mask) < (sourceWord & mask)) ? (destinationWord & mask) : (sourceWord & mask)));
			mask = mask << destPixSize;
		}
		return result;
	}
	if (destPixSize == 16) {
		return (partitionedMinwithnBitsnPartitions(sourceWord, destinationWord, 5, 3)) + ((partitionedMinwithnBitsnPartitions(((unsigned) sourceWord) >> 16, ((unsigned) destinationWord) >> 16, 5, 3)) << 16);
	} else {
		/* begin partitionedMin:with:nBits:nPartitions: */
		mask3 = (1 << 8) - 1;
		result1 = 0;
		for (i1 = 1; i1 <= 3; i1 += 1) {
			result1 = result1 | ((((destinationWord & mask3) < (sourceWord & mask3)) ? (destinationWord & mask3) : (sourceWord & mask3)));
			mask3 = mask3 << 8;
		}
		return result1;
	}
}

int rgbSubwith(int sourceWord, int destinationWord) {
	if (destPixSize < 16) {
		return partitionedSubfromnBitsnPartitions(sourceWord, destinationWord, destPixSize, pixPerWord);
	}
	if (destPixSize == 16) {
		return (partitionedSubfromnBitsnPartitions(sourceWord, destinationWord, 5, 3)) + ((partitionedSubfromnBitsnPartitions(((unsigned) sourceWord) >> 16, ((unsigned) destinationWord) >> 16, 5, 3)) << 16);
	} else {
		return partitionedSubfromnBitsnPartitions(sourceWord, destinationWord, 8, 3);
	}
}

int rightType(int headerWord) {
	if ((headerWord & 252) == 0) {
		return 0;
	} else {
		if ((headerWord & 126976) == 0) {
			return 1;
		} else {
			return 3;
		}
	}
}

int scanCharacters(void) {
    int sourceX2;
    int ascii;
    int top;
    int nextDestX;
    int charVal;
    int left;
    int lastIndex;
    int objectPointer;
    int integerValue;
    int lastIndex1;
    int objectPointer1;
    int objectPointer2;
    int objectPointer3;

	if (scanDisplayFlag) {
		clipRange();
		left = dx;
		top = dy;
	}
	lastIndex = scanStart;
	while (lastIndex <= scanStop) {
		charVal = stObjectat(scanString, lastIndex);
		ascii = (charVal >> 1);
		if (!successFlag) {
			return null;
		}
		stopCode = stObjectat(scanStopArray, ascii + 1);
		if (!successFlag) {
			return null;
		}
		if (!(stopCode == nilObj)) {
			/* begin returnAt:lastIndex:left:top: */
			stopCode = stObjectat(scanStopArray, ascii + 1);
			if (!successFlag) {
				return null;
			}
			/* begin storeInteger:ofObject:withValue: */
			objectPointer1 = bitBltOop;
			if ((lastIndex ^ (lastIndex << 1)) >= 0) {
				longAtput(((((char *) objectPointer1)) + 4) + (15 << 2), ((lastIndex << 1) | 1));
			} else {
				primitiveFail();
			}
			if (scanDisplayFlag) {
				affectedL = left;
				affectedR = bbW + dx;
				affectedT = top;
				affectedB = bbH + dy;
			}
			return null;
		}
		sourceX = stObjectat(scanXTable, ascii + 1);
		sourceX2 = stObjectat(scanXTable, ascii + 2);
		if (!successFlag) {
			return null;
		}
		if (((sourceX & 1)) && ((sourceX2 & 1))) {
			sourceX = (sourceX >> 1);
			sourceX2 = (sourceX2 >> 1);
		} else {
			primitiveFail();
			return null;
		}
		nextDestX = destX + (width = sourceX2 - sourceX);
		if (nextDestX > scanRightX) {
			/* begin returnAt:lastIndex:left:top: */
			stopCode = stObjectat(scanStopArray, 258);
			if (!successFlag) {
				return null;
			}
			/* begin storeInteger:ofObject:withValue: */
			objectPointer2 = bitBltOop;
			if ((lastIndex ^ (lastIndex << 1)) >= 0) {
				longAtput(((((char *) objectPointer2)) + 4) + (15 << 2), ((lastIndex << 1) | 1));
			} else {
				primitiveFail();
			}
			if (scanDisplayFlag) {
				affectedL = left;
				affectedR = bbW + dx;
				affectedT = top;
				affectedB = bbH + dy;
			}
			return null;
		}
		if (scanDisplayFlag) {
			copyBits();
		}
		destX = nextDestX;
		/* begin storeInteger:ofObject:withValue: */
		objectPointer = bitBltOop;
		integerValue = destX;
		if ((integerValue ^ (integerValue << 1)) >= 0) {
			longAtput(((((char *) objectPointer)) + 4) + (4 << 2), ((integerValue << 1) | 1));
		} else {
			primitiveFail();
		}
		lastIndex += 1;
	}
	/* begin returnAt:lastIndex:left:top: */
	lastIndex1 = scanStop;
	stopCode = stObjectat(scanStopArray, 257);
	if (!successFlag) {
		goto l1;
	}
	/* begin storeInteger:ofObject:withValue: */
	objectPointer3 = bitBltOop;
	if ((lastIndex1 ^ (lastIndex1 << 1)) >= 0) {
		longAtput(((((char *) objectPointer3)) + 4) + (15 << 2), ((lastIndex1 << 1) | 1));
	} else {
		primitiveFail();
	}
	if (scanDisplayFlag) {
		affectedL = left;
		affectedR = bbW + dx;
		affectedT = top;
		affectedB = bbH + dy;
	}
l1:	/* end returnAt:lastIndex:left:top: */;
}

int schedulerPointer(void) {
	return longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (3 << 2))))) + 4) + (1 << 2));
}

int sendSelectorToClass(int classPointer) {
    int ok;
    int probe;
    int p;
    int hash;
    int primBits;

	/* begin findNewMethodInClass: */
	/* begin lookupInMethodCacheSel:class: */
	hash = ((unsigned) (messageSelector ^ classPointer)) >> 2;
	probe = (hash & 511) + 1;
	for (p = 1; p <= 3; p += 1) {
		if (((methodCache[probe]) == messageSelector) && ((methodCache[probe + 512]) == classPointer)) {
			newMethod = methodCache[probe + (512 * 2)];
			primitiveIndex = methodCache[probe + (512 * 3)];
			ok = true;
			goto l1;
		}
		probe = ((((unsigned) hash) >> p) & 511) + 1;
	}
	ok = false;
l1:	/* end lookupInMethodCacheSel:class: */;
	if (!(ok)) {
		lookupMethodInClass(classPointer);
		/* begin primitiveIndexOf: */
		primBits = (((unsigned) (longAt(((((char *) newMethod)) + 4) + (0 << 2)))) >> 1) & 805306879;
		if (primBits > 511) {
			primitiveIndex = (primBits & 511) + (((unsigned) primBits) >> 19);
			goto l2;
		} else {
			primitiveIndex = primBits;
			goto l2;
		}
	l2:	/* end primitiveIndexOf: */;
		addToMethodCacheSelclassmethodprimIndex(messageSelector, classPointer, newMethod, primitiveIndex);
	}
	/* begin executeNewMethod */
	if ((primitiveIndex == 0) || (!(primitiveResponse()))) {
		activateNewMethod();
		/* begin quickCheckForInterrupts */
		if ((interruptCheckCounter -= 1) <= 0) {
			checkForInterrupts();
		}
	}
}

int sender(void) {
	return longAt(((((char *) theHomeContext)) + 4) + (0 << 2));
}

int setInterpreter(int anInterpreter) {
	interpreterProxy = anInterpreter;
}

int setSizeOfFreeto(int chunk, int byteSize) {
	longAtput(chunk, (byteSize & 536870908) | 2);
}

int showDisplayBits(void) {
    int displayObj;
    int dispBits;
    int affectedRectL;
    int affectedRectR;
    int affectedRectT;
    int affectedRectB;
    int dispBitsIndex;
    int h;
    int w;
    int d;
    int successValue;

	if (deferDisplayUpdates) {
		return null;
	}
	displayObj = longAt(((((char *) specialObjectsOop)) + 4) + (14 << 2));
	if (!(destForm == displayObj)) {
		return null;
	}
	/* begin success: */
	successValue = (((((unsigned) (longAt(displayObj))) >> 8) & 15) <= 4) && ((lengthOf(displayObj)) >= 4);
	successFlag = successValue && successFlag;
	if (successFlag) {
		dispBits = longAt(((((char *) displayObj)) + 4) + (0 << 2));
		w = fetchIntegerofObject(1, displayObj);
		h = fetchIntegerofObject(2, displayObj);
		d = fetchIntegerofObject(3, displayObj);
	}
	if (successFlag) {
		affectedRectL = affectedL;
		affectedRectR = affectedR;
		affectedRectT = affectedT;
		affectedRectB = affectedB;
		dispBitsIndex = dispBits + 4;
		ioShowDisplay(dispBitsIndex, w, h, d, affectedRectL, affectedRectR, affectedRectT, affectedRectB);
	}
}

int signExtend16(int int16) {
	if ((int16 & 32768) == 0) {
		return int16;
	} else {
		return int16 - 65536;
	}
}

int signalSemaphoreWithIndex(int index) {
    int i;

	if (index <= 0) {
		return null;
	}
	interruptCheckCounter = 0;
	for (i = 1; i <= semaphoresToSignalCount; i += 1) {
		if ((semaphoresToSignal[i]) == index) {
			return null;
		}
	}
	if (semaphoresToSignalCount < 25) {
		semaphoresToSignalCount += 1;
		semaphoresToSignal[semaphoresToSignalCount] = index;
	}
}

int sizeBitsOf(int oop) {
    int header;

	header = longAt(oop);
	if ((header & 3) == 0) {
		return (longAt(oop - 8)) & 4294967292U;
	} else {
		return header & 252;
	}
}

int sizeBitsOfSafe(int oop) {
    int header;
    int type;

	header = longAt(oop);
	/* begin rightType: */
	if ((header & 252) == 0) {
		type = 0;
		goto l1;
	} else {
		if ((header & 126976) == 0) {
			type = 1;
			goto l1;
		} else {
			type = 3;
			goto l1;
		}
	}
l1:	/* end rightType: */;
	if (type == 0) {
		return (longAt(oop - 8)) & 4294967292U;
	} else {
		return header & 252;
	}
}

int sizeHeader(int oop) {
	return longAt(oop - 8);
}

int sizeOfFree(int oop) {
	return (longAt(oop)) & 536870908;
}

int sizeOfSTArrayFromCPrimitive(void *cPtr) {
    int oop;
    int sz;
    int header;
    int fmt;

	oop = ((int) cPtr) - 4;
	if (!(isWordsOrBytes(oop))) {
		primitiveFail();
		return 0;
	}
	/* begin lengthOf: */
	header = longAt(oop);
	if ((header & 3) == 0) {
		sz = (longAt(oop - 8)) & 4294967292U;
	} else {
		sz = header & 252;
	}
	fmt = (((unsigned) header) >> 8) & 15;
	if (fmt < 8) {
		return ((unsigned) (sz - 4)) >> 2;
	} else {
		return (sz - 4) - (fmt & 3);
	}
	return null;
}

int smoothPixatXfyfdxhdyhdxvdyvpixPerWordpixelMasksourceMap(int n, int xf, int yf, int dxh, int dyh, int dxv, int dyv, int srcPixPerWord, int sourcePixMask, int sourceMap) {
    int j;
    int sourcePix;
    int b;
    int x;
    int y;
    int bitsPerColor;
    int nPix;
    int maxPix;
    int i;
    int d;
    int rgb;
    int g;
    int r;
    int mask;
    int srcPix;
    int destPix;
    int d1;

	r = g = b = 0;
	maxPix = n * n;
	x = xf;
	y = yf;
	nPix = 0;
	for (i = 0; i <= (n - 1); i += 1) {
		for (j = 0; j <= (n - 1); j += 1) {
			sourcePix = (sourcePixAtXypixPerWord(((unsigned) ((x + (dxh * i)) + (dxv * j))) >> 14, ((unsigned) ((y + (dyh * i)) + (dyv * j))) >> 14, srcPixPerWord)) & sourcePixMask;
			if (!((combinationRule == 25) && (sourcePix == 0))) {
				nPix += 1;
				if (sourcePixSize < 16) {
					rgb = (longAt(((((char *) sourceMap)) + 4) + (sourcePix << 2))) & 16777215;
				} else {
					if (sourcePixSize == 32) {
						rgb = sourcePix & 16777215;
					} else {
						/* begin rgbMap:from:to: */
						if ((d1 = 8 - 5) > 0) {
							mask = (1 << 5) - 1;
							srcPix = sourcePix << d1;
							mask = mask << d1;
							destPix = srcPix & mask;
							mask = mask << 8;
							srcPix = srcPix << d1;
							rgb = (destPix + (srcPix & mask)) + ((srcPix << d1) & (mask << 8));
							goto l1;
						} else {
							if (d1 == 0) {
								rgb = sourcePix;
								goto l1;
							}
							if (sourcePix == 0) {
								rgb = sourcePix;
								goto l1;
							}
							d1 = 5 - 8;
							mask = (1 << 8) - 1;
							srcPix = ((unsigned) sourcePix) >> d1;
							destPix = srcPix & mask;
							mask = mask << 8;
							srcPix = ((unsigned) srcPix) >> d1;
							destPix = (destPix + (srcPix & mask)) + ((((unsigned) srcPix) >> d1) & (mask << 8));
							if (destPix == 0) {
								rgb = 1;
								goto l1;
							}
							rgb = destPix;
							goto l1;
						}
					l1:	/* end rgbMap:from:to: */;
					}
				}
				r += (((unsigned) rgb) >> 16) & 255;
				g += (((unsigned) rgb) >> 8) & 255;
				b += rgb & 255;
			}
		}
	}
	if ((nPix == 0) || ((combinationRule == 25) && (nPix < (((int) maxPix >> 1))))) {
		return 0;
	}
	if (colorMap != nilObj) {
		bitsPerColor = cmBitsPerColor;
	} else {
		if (destPixSize == 16) {
			bitsPerColor = 5;
		}
		if (destPixSize == 32) {
			bitsPerColor = 8;
		}
	}
	d = 8 - bitsPerColor;
	rgb = (((((unsigned) (r / nPix)) >> d) << (bitsPerColor * 2)) + ((((unsigned) (g / nPix)) >> d) << bitsPerColor)) + (((unsigned) (b / nPix)) >> d);
	if (rgb == 0) {
		if (((r + g) + b) > 0) {
			rgb = 1;
		}
	}
	if (colorMap != nilObj) {
		return longAt(((((char *) colorMap)) + 4) + (rgb << 2));
	} else {
		return rgb;
	}
}

int socketRecordSize(void) {
	return sizeof(SQSocket);
}

SQSocket * socketValueOf(int socketOop) {
    int socketIndex;
    int successValue;

	/* begin success: */
	successValue = (((((unsigned) (longAt(socketOop))) >> 8) & 15) >= 8) && ((lengthOf(socketOop)) == (socketRecordSize()));
	successFlag = successValue && successFlag;
	if (successFlag) {
		socketIndex = socketOop + 4;
		return (SQSocket *) socketIndex;
	} else {
		return null;
	}
}

int sourcePixAtXypixPerWord(int x, int y, int srcPixPerWord) {
    int sourceWord;
    int index;

	if ((x < 0) || (x >= srcWidth)) {
		return 0;
	}
	if ((y < 0) || (y >= srcHeight)) {
		return 0;
	}
	index = ((y * sourceRaster) + (x / srcPixPerWord)) * 4;
	sourceWord = longAt((sourceBits + 4) + index);
	return ((unsigned) sourceWord) >> ((32 - sourcePixSize) - ((x % srcPixPerWord) * sourcePixSize));
}

int sourceSkewAndPointerInit(void) {
    int dWid;
    int sxLowBits;
    int dxLowBits;
    int pixPerM1;

	pixPerM1 = pixPerWord - 1;
	sxLowBits = sx & pixPerM1;
	dxLowBits = dx & pixPerM1;
	if (hDir > 0) {
		dWid = ((bbW < (pixPerWord - dxLowBits)) ? bbW : (pixPerWord - dxLowBits));
		preload = (sxLowBits + dWid) > pixPerM1;
	} else {
		dWid = ((bbW < (dxLowBits + 1)) ? bbW : (dxLowBits + 1));
		preload = ((sxLowBits - dWid) + 1) < 0;
	}
	skew = (sxLowBits - dxLowBits) * destPixSize;
	if (preload) {
		if (skew < 0) {
			skew += 32;
		} else {
			skew -= 32;
		}
	}
	sourceIndex = (sourceBits + 4) + (((sy * sourceRaster) + (sx / (32 / sourcePixSize))) * 4);
	sourceDelta = 4 * ((sourceRaster * vDir) - (nWords * hDir));
	if (preload) {
		sourceDelta -= 4 * hDir;
	}
}

int sourceWordwith(int sourceWord, int destinationWord) {
	return sourceWord;
}

int specialSelector(int index) {
	return longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (23 << 2))))) + 4) + ((index * 2) << 2));
}

int splObj(int index) {
	return longAt(((((char *) specialObjectsOop)) + 4) + (index << 2));
}

int stObjectat(int array, int index) {
    int hdr;
    int totalLength;
    int fmt;
    int fixedFields;
    int sz;
    int classFormat;
    int class;
    int ccIndex;

	hdr = longAt(array);
	fmt = (((unsigned) hdr) >> 8) & 15;
	/* begin lengthOf:baseHeader:format: */
	if ((hdr & 3) == 0) {
		sz = (longAt(array - 8)) & 4294967292U;
	} else {
		sz = hdr & 252;
	}
	if (fmt < 8) {
		totalLength = ((unsigned) (sz - 4)) >> 2;
		goto l1;
	} else {
		totalLength = (sz - 4) - (fmt & 3);
		goto l1;
	}
l1:	/* end lengthOf:baseHeader:format: */;
	/* begin fixedFieldsOf:format:length: */
	if ((fmt > 3) || (fmt == 2)) {
		fixedFields = 0;
		goto l2;
	}
	if (fmt < 2) {
		fixedFields = totalLength;
		goto l2;
	}
	/* begin fetchClassOf: */
	if ((array & 1)) {
		class = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
		goto l3;
	}
	ccIndex = ((((unsigned) (longAt(array))) >> 12) & 31) - 1;
	if (ccIndex < 0) {
		class = (longAt(array - 4)) & 4294967292U;
		goto l3;
	} else {
		class = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
		goto l3;
	}
l3:	/* end fetchClassOf: */;
	classFormat = (longAt(((((char *) class)) + 4) + (2 << 2))) - 1;
	fixedFields = (((((unsigned) classFormat) >> 11) & 192) + ((((unsigned) classFormat) >> 2) & 63)) - 1;
l2:	/* end fixedFieldsOf:format:length: */;
	if (!((index >= 1) && (index <= (totalLength - fixedFields)))) {
		successFlag = false;
	}
	if (successFlag) {
		/* begin subscript:with:format: */
		if (fmt < 4) {
			return longAt(((((char *) array)) + 4) + (((index + fixedFields) - 1) << 2));
		}
		if (fmt < 8) {
			return positive32BitIntegerFor(longAt(((((char *) array)) + 4) + (((index + fixedFields) - 1) << 2)));
		} else {
			return (((byteAt(((((char *) array)) + 4) + ((index + fixedFields) - 1))) << 1) | 1);
		}
		return null;
	} else {
		return 0;
	}
}

int stObjectatput(int array, int index, int value) {
    int hdr;
    int totalLength;
    int fmt;
    int fixedFields;
    int valueToStore;
    int sz;
    int classFormat;
    int class;
    int ccIndex;

	hdr = longAt(array);
	fmt = (((unsigned) hdr) >> 8) & 15;
	/* begin lengthOf:baseHeader:format: */
	if ((hdr & 3) == 0) {
		sz = (longAt(array - 8)) & 4294967292U;
	} else {
		sz = hdr & 252;
	}
	if (fmt < 8) {
		totalLength = ((unsigned) (sz - 4)) >> 2;
		goto l1;
	} else {
		totalLength = (sz - 4) - (fmt & 3);
		goto l1;
	}
l1:	/* end lengthOf:baseHeader:format: */;
	/* begin fixedFieldsOf:format:length: */
	if ((fmt > 3) || (fmt == 2)) {
		fixedFields = 0;
		goto l2;
	}
	if (fmt < 2) {
		fixedFields = totalLength;
		goto l2;
	}
	/* begin fetchClassOf: */
	if ((array & 1)) {
		class = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
		goto l3;
	}
	ccIndex = ((((unsigned) (longAt(array))) >> 12) & 31) - 1;
	if (ccIndex < 0) {
		class = (longAt(array - 4)) & 4294967292U;
		goto l3;
	} else {
		class = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
		goto l3;
	}
l3:	/* end fetchClassOf: */;
	classFormat = (longAt(((((char *) class)) + 4) + (2 << 2))) - 1;
	fixedFields = (((((unsigned) classFormat) >> 11) & 192) + ((((unsigned) classFormat) >> 2) & 63)) - 1;
l2:	/* end fixedFieldsOf:format:length: */;
	if (!((index >= 1) && (index <= (totalLength - fixedFields)))) {
		successFlag = false;
	}
	if (successFlag) {
		/* begin subscript:with:storing:format: */
		if (fmt < 4) {
			/* begin storePointer:ofObject:withValue: */
			if (array < youngStart) {
				possibleRootStoreIntovalue(array, value);
			}
			longAtput(((((char *) array)) + 4) + (((index + fixedFields) - 1) << 2), value);
		} else {
			if (fmt < 8) {
				valueToStore = positive32BitValueOf(value);
				if (successFlag) {
					longAtput(((((char *) array)) + 4) + (((index + fixedFields) - 1) << 2), valueToStore);
				}
			} else {
				if (!((value & 1))) {
					successFlag = false;
				}
				valueToStore = (value >> 1);
				if (!((valueToStore >= 0) && (valueToStore <= 255))) {
					successFlag = false;
				}
				if (successFlag) {
					byteAtput(((((char *) array)) + 4) + ((index + fixedFields) - 1), valueToStore);
				}
			}
		}
	}
}

int stSizeOf(int oop) {
    int hdr;
    int totalLength;
    int fmt;
    int fixedFields;
    int sz;
    int classFormat;
    int class;
    int ccIndex;

	hdr = longAt(oop);
	fmt = (((unsigned) hdr) >> 8) & 15;
	/* begin lengthOf:baseHeader:format: */
	if ((hdr & 3) == 0) {
		sz = (longAt(oop - 8)) & 4294967292U;
	} else {
		sz = hdr & 252;
	}
	if (fmt < 8) {
		totalLength = ((unsigned) (sz - 4)) >> 2;
		goto l1;
	} else {
		totalLength = (sz - 4) - (fmt & 3);
		goto l1;
	}
l1:	/* end lengthOf:baseHeader:format: */;
	/* begin fixedFieldsOf:format:length: */
	if ((fmt > 3) || (fmt == 2)) {
		fixedFields = 0;
		goto l2;
	}
	if (fmt < 2) {
		fixedFields = totalLength;
		goto l2;
	}
	/* begin fetchClassOf: */
	if ((oop & 1)) {
		class = longAt(((((char *) specialObjectsOop)) + 4) + (5 << 2));
		goto l3;
	}
	ccIndex = ((((unsigned) (longAt(oop))) >> 12) & 31) - 1;
	if (ccIndex < 0) {
		class = (longAt(oop - 4)) & 4294967292U;
		goto l3;
	} else {
		class = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (28 << 2))))) + 4) + (ccIndex << 2));
		goto l3;
	}
l3:	/* end fetchClassOf: */;
	classFormat = (longAt(((((char *) class)) + 4) + (2 << 2))) - 1;
	fixedFields = (((((unsigned) classFormat) >> 11) & 192) + ((((unsigned) classFormat) >> 2) & 63)) - 1;
l2:	/* end fixedFieldsOf:format:length: */;
	return totalLength - fixedFields;
}

int stackIntegerValue(int offset) {
    int integerPointer;

	integerPointer = longAt(stackPointer - (offset * 4));
	if ((integerPointer & 1)) {
		return (integerPointer >> 1);
	} else {
		primitiveFail();
		return 0;
	}
}

int stackObjectValue(int offset) {
    int oop;

	oop = longAt(stackPointer - (offset * 4));
	if ((oop & 1)) {
		primitiveFail();
		return null;
	}
	return oop;
}

int stackPointerIndex(void) {
	return ((unsigned) ((stackPointer - activeContext) - 4)) >> 2;
}

int stackTop(void) {
	return longAt(stackPointer);
}

int stackValue(int offset) {
	return longAt(stackPointer - (offset * 4));
}

int startField(void) {
    int typeBits;
    int childType;

	child = longAt(field);
	typeBits = child & 3;
	if ((typeBits & 1) == 1) {
		field -= 4;
		return 1;
	}
	if (typeBits == 0) {
		longAtput(field, parentField);
		parentField = field;
		return 2;
	}
	if (typeBits == 2) {
		if ((child & 126976) != 0) {
			child = child & 4294967292U;
			/* begin rightType: */
			if ((child & 252) == 0) {
				childType = 0;
				goto l1;
			} else {
				if ((child & 126976) == 0) {
					childType = 1;
					goto l1;
				} else {
					childType = 3;
					goto l1;
				}
			}
		l1:	/* end rightType: */;
			longAtput(field, child | childType);
			return 3;
		} else {
			child = longAt(field - 4);
			child = child & 4294967292U;
			longAtput(field - 4, parentField);
			parentField = (field - 4) | 1;
			return 2;
		}
	}
}

int startObj(void) {
    int oop;
    int lastFieldOffset;
    int header;
    int methodHeader;
    int sz;
    int fmt;
    int header1;
    int type;

	oop = child;
	if (oop < youngStart) {
		field = oop;
		return 3;
	}
	header = longAt(oop);
	if ((header & 2147483648U) == 0) {
		header = header & 4294967292U;
		header = (header | 2147483648U) | 2;
		longAtput(oop, header);
		/* begin lastPointerOf: */
		fmt = (((unsigned) (longAt(oop))) >> 8) & 15;
		if (fmt < 4) {
			/* begin sizeBitsOfSafe: */
			header1 = longAt(oop);
			/* begin rightType: */
			if ((header1 & 252) == 0) {
				type = 0;
				goto l2;
			} else {
				if ((header1 & 126976) == 0) {
					type = 1;
					goto l2;
				} else {
					type = 3;
					goto l2;
				}
			}
		l2:	/* end rightType: */;
			if (type == 0) {
				sz = (longAt(oop - 8)) & 4294967292U;
				goto l3;
			} else {
				sz = header1 & 252;
				goto l3;
			}
		l3:	/* end sizeBitsOfSafe: */;
			lastFieldOffset = sz - 4;
			goto l1;
		}
		if (fmt < 12) {
			lastFieldOffset = 0;
			goto l1;
		}
		methodHeader = longAt(oop + 4);
		lastFieldOffset = (((((unsigned) methodHeader) >> 10) & 255) * 4) + 4;
	l1:	/* end lastPointerOf: */;
		field = oop + lastFieldOffset;
		return 1;
	} else {
		field = oop;
		return 3;
	}
}

int startOfMemory(void) {
	return (int) memory;
}

int stopReason(void) {
	return stopCode;
}

int storeByteofObjectwithValue(int byteIndex, int oop, int valueByte) {
	return byteAtput(((((char *) oop)) + 4) + byteIndex, valueByte);
}

int storeContextRegisters(int activeCntx) {
	longAtput(((((char *) activeCntx)) + 4) + (1 << 2), ((((instructionPointer - method) - (4 - 2)) << 1) | 1));
	longAtput(((((char *) activeCntx)) + 4) + (2 << 2), (((((((unsigned) ((stackPointer - activeContext) - 4)) >> 2) - 6) + 1) << 1) | 1));
}

int storeInstructionPointerValueinContext(int value, int contextPointer) {
	longAtput(((((char *) contextPointer)) + 4) + (1 << 2), ((value << 1) | 1));
}

int storeIntegerofObjectwithValue(int fieldIndex, int objectPointer, int integerValue) {
	if ((integerValue ^ (integerValue << 1)) >= 0) {
		longAtput(((((char *) objectPointer)) + 4) + (fieldIndex << 2), ((integerValue << 1) | 1));
	} else {
		primitiveFail();
	}
}

int storePointerofObjectwithValue(int fieldIndex, int oop, int valuePointer) {
	if (oop < youngStart) {
		possibleRootStoreIntovalue(oop, valuePointer);
	}
	return longAtput(((((char *) oop)) + 4) + (fieldIndex << 2), valuePointer);
}

int storePointerUncheckedofObjectwithValue(int fieldIndex, int oop, int valuePointer) {
	return longAtput(((((char *) oop)) + 4) + (fieldIndex << 2), valuePointer);
}

int storeStackPointerValueinContext(int value, int contextPointer) {
	longAtput(((((char *) contextPointer)) + 4) + (2 << 2), ((value << 1) | 1));
}

int storeWordofObjectwithValue(int fieldIndex, int oop, int valueWord) {
	return longAtput(((((char *) oop)) + 4) + (fieldIndex << 2), valueWord);
}

int subWordwith(int sourceWord, int destinationWord) {
	return sourceWord - destinationWord;
}

int subscriptwithformat(int array, int index, int fmt) {
	if (fmt < 4) {
		return longAt(((((char *) array)) + 4) + ((index - 1) << 2));
	}
	if (fmt < 8) {
		return positive32BitIntegerFor(longAt(((((char *) array)) + 4) + ((index - 1) << 2)));
	} else {
		return (((byteAt(((((char *) array)) + 4) + (index - 1))) << 1) | 1);
	}
}

int subscriptwithstoringformat(int array, int index, int oopToStore, int fmt) {
    int valueToStore;

	if (fmt < 4) {
		/* begin storePointer:ofObject:withValue: */
		if (array < youngStart) {
			possibleRootStoreIntovalue(array, oopToStore);
		}
		longAtput(((((char *) array)) + 4) + ((index - 1) << 2), oopToStore);
	} else {
		if (fmt < 8) {
			valueToStore = positive32BitValueOf(oopToStore);
			if (successFlag) {
				longAtput(((((char *) array)) + 4) + ((index - 1) << 2), valueToStore);
			}
		} else {
			if (!((oopToStore & 1))) {
				successFlag = false;
			}
			valueToStore = (oopToStore >> 1);
			if (!((valueToStore >= 0) && (valueToStore <= 255))) {
				successFlag = false;
			}
			if (successFlag) {
				byteAtput(((((char *) array)) + 4) + (index - 1), valueToStore);
			}
		}
	}
}

int success(int successValue) {
	successFlag = successValue && successFlag;
}

int sufficientSpaceAfterGC(int minFree) {
	incrementalGC();
	if (((longAt(freeBlock)) & 536870908) < minFree) {
		if (signalLowSpace) {
			return false;
		}
		fullGC();
		if (((longAt(freeBlock)) & 536870908) < (minFree + 15000)) {
			return false;
		}
	}
	return true;
}

int sufficientSpaceToAllocate(int bytes) {
    int minFree;

	minFree = (lowSpaceThreshold + bytes) + 4;
	if (((longAt(freeBlock)) & 536870908) >= minFree) {
		return true;
	} else {
		return sufficientSpaceAfterGC(minFree);
	}
}

int sufficientSpaceToInstantiateindexableSize(int classOop, int size) {
    int okay;
    int format;
    int minFree;
    int minFree1;

	format = (((unsigned) ((longAt(((((char *) classOop)) + 4) + (2 << 2))) - 1)) >> 8) & 15;
	if ((size > 0) && (format < 2)) {
		return false;
	}
	if (format < 8) {
		/* begin sufficientSpaceToAllocate: */
		minFree = (lowSpaceThreshold + (2500 + (size * 4))) + 4;
		if (((longAt(freeBlock)) & 536870908) >= minFree) {
			okay = true;
			goto l1;
		} else {
			okay = sufficientSpaceAfterGC(minFree);
			goto l1;
		}
	l1:	/* end sufficientSpaceToAllocate: */;
	} else {
		/* begin sufficientSpaceToAllocate: */
		minFree1 = (lowSpaceThreshold + (2500 + size)) + 4;
		if (((longAt(freeBlock)) & 536870908) >= minFree1) {
			okay = true;
			goto l2;
		} else {
			okay = sufficientSpaceAfterGC(minFree1);
			goto l2;
		}
	l2:	/* end sufficientSpaceToAllocate: */;
	}
	return okay;
}

int superclassOf(int classPointer) {
	return longAt(((((char *) classPointer)) + 4) + (0 << 2));
}

int sweepPhase(void) {
    int entriesAvailable;
    int survivors;
    int firstFree;
    int oopHeader;
    int oop;
    int freeChunk;
    int oopHeaderType;
    int hdrBytes;
    int oopSize;
    int freeChunkSize;
    int extra;
    int chunk;
    int extra1;
    int type;
    int extra2;
    int type1;
    int extra3;

	entriesAvailable = fwdTableInit();
	survivors = 0;
	freeChunk = null;
	firstFree = null;
	/* begin oopFromChunk: */
	chunk = youngStart;
	/* begin extraHeaderBytes: */
	type1 = (longAt(chunk)) & 3;
	if (type1 > 1) {
		extra3 = 0;
	} else {
		if (type1 == 1) {
			extra3 = 4;
		} else {
			extra3 = 8;
		}
	}
	extra1 = extra3;
	oop = chunk + extra1;
	while (oop < endOfMemory) {
		oopHeader = longAt(oop);
		oopHeaderType = oopHeader & 3;
		if (oopHeaderType == 3) {
			oopSize = oopHeader & 252;
			hdrBytes = 0;
		} else {
			if (oopHeaderType == 1) {
				oopSize = oopHeader & 252;
				hdrBytes = 4;
			} else {
				if (oopHeaderType == 0) {
					oopSize = (longAt(oop - 8)) & 4294967292U;
					hdrBytes = 8;
				} else {
					oopSize = oopHeader & 536870908;
					hdrBytes = 0;
				}
			}
		}
		if ((oopHeader & 2147483648U) == 0) {
			if (freeChunk != null) {
				freeChunkSize = (freeChunkSize + oopSize) + hdrBytes;
			} else {
				freeChunk = oop - hdrBytes;
				freeChunkSize = oopSize + (oop - freeChunk);
				if (firstFree == null) {
					firstFree = freeChunk;
				}
			}
		} else {
			longAtput(oop, oopHeader & 2147483647U);
			if (entriesAvailable > 0) {
				entriesAvailable -= 1;
			} else {
				firstFree = freeChunk;
			}
			if (freeChunk != null) {
				longAtput(freeChunk, (freeChunkSize & 536870908) | 2);
			}
			freeChunk = null;
			survivors += 1;
		}
		/* begin oopFromChunk: */
		/* begin extraHeaderBytes: */
		type = (longAt(oop + oopSize)) & 3;
		if (type > 1) {
			extra2 = 0;
		} else {
			if (type == 1) {
				extra2 = 4;
			} else {
				extra2 = 8;
			}
		}
		extra = extra2;
		oop = (oop + oopSize) + extra;
	}
	if (freeChunk != null) {
		longAtput(freeChunk, (freeChunkSize & 536870908) | 2);
	}
	if (!(oop == endOfMemory)) {
		error("sweep failed to find exact end of memory");
	}
	if (firstFree == null) {
		error("expected to find at least one free object");
	} else {
		compStart = firstFree;
	}
	if (!(displayBits == 0)) {
		oopHeader = longAt(displayBits);
		longAtput(displayBits, oopHeader & 2147483647U);
	}
	return survivors;
}

int synchronousSignal(int aSemaphore) {
    int excessSignals;

	if ((longAt(((((char *) aSemaphore)) + 4) + (0 << 2))) == nilObj) {
		excessSignals = fetchIntegerofObject(2, aSemaphore);
		/* begin storeInteger:ofObject:withValue: */
		if (((excessSignals + 1) ^ ((excessSignals + 1) << 1)) >= 0) {
			longAtput(((((char *) aSemaphore)) + 4) + (2 << 2), (((excessSignals + 1) << 1) | 1));
		} else {
			primitiveFail();
		}
	} else {
		resume(removeFirstLinkOfList(aSemaphore));
	}
}

int tallyIntoMapwith(int sourceWord, int destinationWord) {
    int pixVal;
    int mapIndex;
    int pixMask;
    int destShifted;
    int maskShifted;
    int i;
    int mask;
    int srcPix;
    int destPix;
    int d;
    int mask3;
    int srcPix1;
    int destPix1;
    int d1;

	if (colorMap == nilObj) {
		return destinationWord;
	}
	pixMask = (1 << destPixSize) - 1;
	destShifted = destinationWord;
	maskShifted = destMask;
	for (i = 1; i <= pixPerWord; i += 1) {
		if ((maskShifted & pixMask) > 0) {
			pixVal = destShifted & pixMask;
			if (destPixSize < 16) {
				mapIndex = pixVal;
			} else {
				if (destPixSize == 16) {
					/* begin rgbMap:from:to: */
					if ((d = cmBitsPerColor - 5) > 0) {
						mask = (1 << 5) - 1;
						srcPix = pixVal << d;
						mask = mask << d;
						destPix = srcPix & mask;
						mask = mask << cmBitsPerColor;
						srcPix = srcPix << d;
						mapIndex = (destPix + (srcPix & mask)) + ((srcPix << d) & (mask << cmBitsPerColor));
						goto l1;
					} else {
						if (d == 0) {
							mapIndex = pixVal;
							goto l1;
						}
						if (pixVal == 0) {
							mapIndex = pixVal;
							goto l1;
						}
						d = 5 - cmBitsPerColor;
						mask = (1 << cmBitsPerColor) - 1;
						srcPix = ((unsigned) pixVal) >> d;
						destPix = srcPix & mask;
						mask = mask << cmBitsPerColor;
						srcPix = ((unsigned) srcPix) >> d;
						destPix = (destPix + (srcPix & mask)) + ((((unsigned) srcPix) >> d) & (mask << cmBitsPerColor));
						if (destPix == 0) {
							mapIndex = 1;
							goto l1;
						}
						mapIndex = destPix;
						goto l1;
					}
				l1:	/* end rgbMap:from:to: */;
				} else {
					/* begin rgbMap:from:to: */
					if ((d1 = cmBitsPerColor - 8) > 0) {
						mask3 = (1 << 8) - 1;
						srcPix1 = pixVal << d1;
						mask3 = mask3 << d1;
						destPix1 = srcPix1 & mask3;
						mask3 = mask3 << cmBitsPerColor;
						srcPix1 = srcPix1 << d1;
						mapIndex = (destPix1 + (srcPix1 & mask3)) + ((srcPix1 << d1) & (mask3 << cmBitsPerColor));
						goto l2;
					} else {
						if (d1 == 0) {
							mapIndex = pixVal;
							goto l2;
						}
						if (pixVal == 0) {
							mapIndex = pixVal;
							goto l2;
						}
						d1 = 8 - cmBitsPerColor;
						mask3 = (1 << cmBitsPerColor) - 1;
						srcPix1 = ((unsigned) pixVal) >> d1;
						destPix1 = srcPix1 & mask3;
						mask3 = mask3 << cmBitsPerColor;
						srcPix1 = ((unsigned) srcPix1) >> d1;
						destPix1 = (destPix1 + (srcPix1 & mask3)) + ((((unsigned) srcPix1) >> d1) & (mask3 << cmBitsPerColor));
						if (destPix1 == 0) {
							mapIndex = 1;
							goto l2;
						}
						mapIndex = destPix1;
						goto l2;
					}
				l2:	/* end rgbMap:from:to: */;
				}
			}
			longAtput(((((char *) colorMap)) + 4) + (mapIndex << 2), (longAt(((((char *) colorMap)) + 4) + (mapIndex << 2))) + 1);
		}
		maskShifted = ((unsigned) maskShifted) >> destPixSize;
		destShifted = ((unsigned) destShifted) >> destPixSize;
	}
	return destinationWord;
}

int targetForm(void) {
	return destForm;
}

int temporary(int offset) {
	return longAt(((((char *) theHomeContext)) + 4) + ((offset + 6) << 2));
}

int transferfromIndexofObjecttoIndexofObject(int count, int firstFrom, int fromOop, int firstTo, int toOop) {
    int toIndex;
    int fromIndex;
    int lastFrom;

	fromIndex = fromOop + (firstFrom * 4);
	toIndex = toOop + (firstTo * 4);
	lastFrom = fromIndex + (count * 4);
	while (fromIndex < lastFrom) {
		fromIndex += 4;
		toIndex += 4;
		longAtput(toIndex, longAt(fromIndex));
	}
}

int transferTo(int newProc) {
    int sched;
    int oldProc;
    int valuePointer;
    int tmp;

	sched = longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (3 << 2))))) + 4) + (1 << 2));
	oldProc = longAt(((((char *) sched)) + 4) + (1 << 2));
	/* begin storePointer:ofObject:withValue: */
	valuePointer = activeContext;
	if (oldProc < youngStart) {
		possibleRootStoreIntovalue(oldProc, valuePointer);
	}
	longAtput(((((char *) oldProc)) + 4) + (1 << 2), valuePointer);
	/* begin storePointer:ofObject:withValue: */
	if (sched < youngStart) {
		possibleRootStoreIntovalue(sched, newProc);
	}
	longAtput(((((char *) sched)) + 4) + (1 << 2), newProc);
	/* begin newActiveContext: */
	/* begin storeContextRegisters: */
	longAtput(((((char *) activeContext)) + 4) + (1 << 2), ((((instructionPointer - method) - (4 - 2)) << 1) | 1));
	longAtput(((((char *) activeContext)) + 4) + (2 << 2), (((((((unsigned) ((stackPointer - activeContext) - 4)) >> 2) - 6) + 1) << 1) | 1));
	if ((longAt(((((char *) newProc)) + 4) + (1 << 2))) < youngStart) {
		beRootIfOld(longAt(((((char *) newProc)) + 4) + (1 << 2)));
	}
	activeContext = longAt(((((char *) newProc)) + 4) + (1 << 2));
	/* begin fetchContextRegisters: */
	tmp = longAt(((((char *) (longAt(((((char *) newProc)) + 4) + (1 << 2))))) + 4) + (3 << 2));
	if ((tmp & 1)) {
		tmp = longAt(((((char *) (longAt(((((char *) newProc)) + 4) + (1 << 2))))) + 4) + (5 << 2));
		if (tmp < youngStart) {
			beRootIfOld(tmp);
		}
	} else {
		tmp = longAt(((((char *) newProc)) + 4) + (1 << 2));
	}
	theHomeContext = tmp;
	receiver = longAt(((((char *) tmp)) + 4) + (5 << 2));
	method = longAt(((((char *) tmp)) + 4) + (3 << 2));
	tmp = ((longAt(((((char *) (longAt(((((char *) newProc)) + 4) + (1 << 2))))) + 4) + (1 << 2))) >> 1);
	instructionPointer = ((method + tmp) + 4) - 2;
	tmp = ((longAt(((((char *) (longAt(((((char *) newProc)) + 4) + (1 << 2))))) + 4) + (2 << 2))) >> 1);
	stackPointer = ((longAt(((((char *) newProc)) + 4) + (1 << 2))) + 4) + (((6 + tmp) - 1) * 4);
	reclaimableContextCount = 0;
}

int unPop(int nItems) {
	stackPointer += nItems * 4;
}

int unknownBytecode(void) {
	error("Unknown bytecode");
}

int upward(void) {
    int header;
    int type;

	if ((parentField & 1) == 1) {
		if (parentField == 3) {
			header = (longAt(field)) & 4294967292U;
			/* begin rightType: */
			if ((header & 252) == 0) {
				type = 0;
				goto l1;
			} else {
				if ((header & 126976) == 0) {
					type = 1;
					goto l1;
				} else {
					type = 3;
					goto l1;
				}
			}
		l1:	/* end rightType: */;
			longAtput(field, header + type);
			return 4;
		} else {
			child = field;
			field = parentField - 1;
			parentField = longAt(field);
			header = longAt(field + 4);
			/* begin rightType: */
			if ((header & 252) == 0) {
				type = 0;
				goto l2;
			} else {
				if ((header & 126976) == 0) {
					type = 1;
					goto l2;
				} else {
					type = 3;
					goto l2;
				}
			}
		l2:	/* end rightType: */;
			longAtput(field, child + type);
			field += 4;
			header = header & 4294967292U;
			longAtput(field, header + type);
			return 3;
		}
	} else {
		child = field;
		field = parentField;
		parentField = longAt(field);
		longAtput(field, child);
		field -= 4;
		return 1;
	}
}

int wakeHighestPriority(void) {
    int schedLists;
    int processList;
    int p;
    int sz;
    int header;

	schedLists = longAt(((((char *) (longAt(((((char *) (longAt(((((char *) specialObjectsOop)) + 4) + (3 << 2))))) + 4) + (1 << 2))))) + 4) + (0 << 2));
	/* begin fetchWordLengthOf: */
	/* begin sizeBitsOf: */
	header = longAt(schedLists);
	if ((header & 3) == 0) {
		sz = (longAt(schedLists - 8)) & 4294967292U;
		goto l1;
	} else {
		sz = header & 252;
		goto l1;
	}
l1:	/* end sizeBitsOf: */;
	p = ((unsigned) (sz - 4)) >> 2;
	p -= 1;
	processList = longAt(((((char *) schedLists)) + 4) + (p << 2));
	while ((longAt(((((char *) processList)) + 4) + (0 << 2))) == nilObj) {
		p -= 1;
		if (p < 0) {
			error("scheduler could not find a runnable process");
		}
		processList = longAt(((((char *) schedLists)) + 4) + (p << 2));
	}
	return removeFirstLinkOfList(processList);
}

int warpBits(void) {
    int ns;
    int skewWord;
    int mergeWord;
    int startBits;
    int yDelta;
    int smoothingCount;
    int sourceMapOop;
    int t;
    int i;
    int nSteps;
    int word;
    int halftoneWord;
    int deltaP12x;
    int deltaP12y;
    int deltaP43x;
    int deltaP43y;
    int pAx;
    int pAy;
    int pBx;
    int xDelta;
    int pBy;
    int integerPointer;

	ns = noSource;
	noSource = true;
	clipRange();
	noSource = ns;
	if (noSource || ((bbW <= 0) || (bbH <= 0))) {
		affectedL = affectedR = affectedT = affectedB = 0;
		return null;
	}
	destMaskAndPointerInit();
	/* begin warpLoop */
	if (!((fetchWordLengthOf(bitBltOop)) >= (15 + 12))) {
		primitiveFail();
		goto l2;
	}
	nSteps = height - 1;
	if (nSteps <= 0) {
		nSteps = 1;
	}
	pAx = fetchIntegerOrTruncFloatofObject(15, bitBltOop);
	t = fetchIntegerOrTruncFloatofObject(15 + 3, bitBltOop);
	deltaP12x = deltaFromtonSteps(pAx, t, nSteps);
	if (deltaP12x < 0) {
		pAx = t - (nSteps * deltaP12x);
	}
	pAy = fetchIntegerOrTruncFloatofObject(15 + 1, bitBltOop);
	t = fetchIntegerOrTruncFloatofObject(15 + 4, bitBltOop);
	deltaP12y = deltaFromtonSteps(pAy, t, nSteps);
	if (deltaP12y < 0) {
		pAy = t - (nSteps * deltaP12y);
	}
	pBx = fetchIntegerOrTruncFloatofObject(15 + 9, bitBltOop);
	t = fetchIntegerOrTruncFloatofObject(15 + 6, bitBltOop);
	deltaP43x = deltaFromtonSteps(pBx, t, nSteps);
	if (deltaP43x < 0) {
		pBx = t - (nSteps * deltaP43x);
	}
	pBy = fetchIntegerOrTruncFloatofObject(15 + 10, bitBltOop);
	t = fetchIntegerOrTruncFloatofObject(15 + 7, bitBltOop);
	deltaP43y = deltaFromtonSteps(pBy, t, nSteps);
	if (deltaP43y < 0) {
		pBy = t - (nSteps * deltaP43y);
	}
	if (!successFlag) {
		goto l2;
	}
	if (argumentCount == 2) {
		/* begin stackIntegerValue: */
		integerPointer = longAt(stackPointer - (1 * 4));
		if ((integerPointer & 1)) {
			smoothingCount = (integerPointer >> 1);
			goto l1;
		} else {
			primitiveFail();
			smoothingCount = 0;
			goto l1;
		}
	l1:	/* end stackIntegerValue: */;
		sourceMapOop = longAt(stackPointer - (0 * 4));
		if (sourceMapOop == nilObj) {
			if (sourcePixSize < 16) {
				primitiveFail();
				goto l2;
			}
		} else {
			if ((fetchWordLengthOf(sourceMapOop)) < (1 << sourcePixSize)) {
				primitiveFail();
				goto l2;
			}
		}
	} else {
		smoothingCount = 1;
		sourceMapOop = nilObj;
	}
	startBits = pixPerWord - (dx & (pixPerWord - 1));
	nSteps = width - 1;
	if (nSteps <= 0) {
		nSteps = 1;
	}
	for (i = destY; i <= (clipY - 1); i += 1) {
		pAx += deltaP12x;
		pAy += deltaP12y;
		pBx += deltaP43x;
		pBy += deltaP43y;
	}
	for (i = 1; i <= bbH; i += 1) {
		xDelta = deltaFromtonSteps(pAx, pBx, nSteps);
		if (xDelta >= 0) {
			sx = pAx;
		} else {
			sx = pBx - (nSteps * xDelta);
		}
		yDelta = deltaFromtonSteps(pAy, pBy, nSteps);
		if (yDelta >= 0) {
			sy = pAy;
		} else {
			sy = pBy - (nSteps * yDelta);
		}
		for (word = destX; word <= (clipX - 1); word += 1) {
			sx += xDelta;
			sy += yDelta;
		}
		if (noHalftone) {
			halftoneWord = 4294967295U;
		} else {
			halftoneWord = longAt(halftoneBase + ((((dy + i) - 1) % halftoneHeight) * 4));
		}
		destMask = mask1;
		if (bbW < startBits) {
			skewWord = warpSourcePixelsxDeltahyDeltahxDeltavyDeltavsmoothingsourceMap(bbW, xDelta, yDelta, deltaP12x, deltaP12y, smoothingCount, sourceMapOop);
			skewWord = ((((startBits - bbW) * destPixSize) < 0) ? ((unsigned) skewWord >> -((startBits - bbW) * destPixSize)) : ((unsigned) skewWord << ((startBits - bbW) * destPixSize)));
		} else {
			skewWord = warpSourcePixelsxDeltahyDeltahxDeltavyDeltavsmoothingsourceMap(startBits, xDelta, yDelta, deltaP12x, deltaP12y, smoothingCount, sourceMapOop);
		}
		for (word = 1; word <= nWords; word += 1) {
			mergeWord = mergewith(skewWord & halftoneWord, (longAt(destIndex)) & destMask);
			longAtput(destIndex, (destMask & mergeWord) | ((~destMask) & (longAt(destIndex))));
			destIndex += 4;
			if (word >= (nWords - 1)) {
				if (!(word == nWords)) {
					destMask = mask2;
					skewWord = warpSourcePixelsxDeltahyDeltahxDeltavyDeltavsmoothingsourceMap(pixPerWord, xDelta, yDelta, deltaP12x, deltaP12y, smoothingCount, sourceMapOop);
				}
			} else {
				destMask = 4294967295U;
				skewWord = warpSourcePixelsxDeltahyDeltahxDeltavyDeltavsmoothingsourceMap(pixPerWord, xDelta, yDelta, deltaP12x, deltaP12y, smoothingCount, sourceMapOop);
			}
		}
		pAx += deltaP12x;
		pAy += deltaP12y;
		pBx += deltaP43x;
		pBy += deltaP43y;
		destIndex += destDelta;
	}
l2:	/* end warpLoop */;
	if (hDir > 0) {
		affectedL = dx;
		affectedR = dx + bbW;
	} else {
		affectedL = (dx - bbW) + 1;
		affectedR = dx + 1;
	}
	if (vDir > 0) {
		affectedT = dy;
		affectedB = dy + bbH;
	} else {
		affectedT = (dy - bbH) + 1;
		affectedB = dy + 1;
	}
}

int warpLoop(void) {
    int skewWord;
    int mergeWord;
    int startBits;
    int yDelta;
    int smoothingCount;
    int sourceMapOop;
    int t;
    int i;
    int nSteps;
    int word;
    int halftoneWord;
    int deltaP12x;
    int deltaP12y;
    int deltaP43x;
    int deltaP43y;
    int pAx;
    int pAy;
    int pBx;
    int xDelta;
    int pBy;
    int integerPointer;

	if (!((fetchWordLengthOf(bitBltOop)) >= (15 + 12))) {
		return primitiveFail();
	}
	nSteps = height - 1;
	if (nSteps <= 0) {
		nSteps = 1;
	}
	pAx = fetchIntegerOrTruncFloatofObject(15, bitBltOop);
	t = fetchIntegerOrTruncFloatofObject(15 + 3, bitBltOop);
	deltaP12x = deltaFromtonSteps(pAx, t, nSteps);
	if (deltaP12x < 0) {
		pAx = t - (nSteps * deltaP12x);
	}
	pAy = fetchIntegerOrTruncFloatofObject(15 + 1, bitBltOop);
	t = fetchIntegerOrTruncFloatofObject(15 + 4, bitBltOop);
	deltaP12y = deltaFromtonSteps(pAy, t, nSteps);
	if (deltaP12y < 0) {
		pAy = t - (nSteps * deltaP12y);
	}
	pBx = fetchIntegerOrTruncFloatofObject(15 + 9, bitBltOop);
	t = fetchIntegerOrTruncFloatofObject(15 + 6, bitBltOop);
	deltaP43x = deltaFromtonSteps(pBx, t, nSteps);
	if (deltaP43x < 0) {
		pBx = t - (nSteps * deltaP43x);
	}
	pBy = fetchIntegerOrTruncFloatofObject(15 + 10, bitBltOop);
	t = fetchIntegerOrTruncFloatofObject(15 + 7, bitBltOop);
	deltaP43y = deltaFromtonSteps(pBy, t, nSteps);
	if (deltaP43y < 0) {
		pBy = t - (nSteps * deltaP43y);
	}
	if (!successFlag) {
		return false;
	}
	if (argumentCount == 2) {
		/* begin stackIntegerValue: */
		integerPointer = longAt(stackPointer - (1 * 4));
		if ((integerPointer & 1)) {
			smoothingCount = (integerPointer >> 1);
			goto l1;
		} else {
			primitiveFail();
			smoothingCount = 0;
			goto l1;
		}
	l1:	/* end stackIntegerValue: */;
		sourceMapOop = longAt(stackPointer - (0 * 4));
		if (sourceMapOop == nilObj) {
			if (sourcePixSize < 16) {
				return primitiveFail();
			}
		} else {
			if ((fetchWordLengthOf(sourceMapOop)) < (1 << sourcePixSize)) {
				return primitiveFail();
			}
		}
	} else {
		smoothingCount = 1;
		sourceMapOop = nilObj;
	}
	startBits = pixPerWord - (dx & (pixPerWord - 1));
	nSteps = width - 1;
	if (nSteps <= 0) {
		nSteps = 1;
	}
	for (i = destY; i <= (clipY - 1); i += 1) {
		pAx += deltaP12x;
		pAy += deltaP12y;
		pBx += deltaP43x;
		pBy += deltaP43y;
	}
	for (i = 1; i <= bbH; i += 1) {
		xDelta = deltaFromtonSteps(pAx, pBx, nSteps);
		if (xDelta >= 0) {
			sx = pAx;
		} else {
			sx = pBx - (nSteps * xDelta);
		}
		yDelta = deltaFromtonSteps(pAy, pBy, nSteps);
		if (yDelta >= 0) {
			sy = pAy;
		} else {
			sy = pBy - (nSteps * yDelta);
		}
		for (word = destX; word <= (clipX - 1); word += 1) {
			sx += xDelta;
			sy += yDelta;
		}
		if (noHalftone) {
			halftoneWord = 4294967295U;
		} else {
			halftoneWord = longAt(halftoneBase + ((((dy + i) - 1) % halftoneHeight) * 4));
		}
		destMask = mask1;
		if (bbW < startBits) {
			skewWord = warpSourcePixelsxDeltahyDeltahxDeltavyDeltavsmoothingsourceMap(bbW, xDelta, yDelta, deltaP12x, deltaP12y, smoothingCount, sourceMapOop);
			skewWord = ((((startBits - bbW) * destPixSize) < 0) ? ((unsigned) skewWord >> -((startBits - bbW) * destPixSize)) : ((unsigned) skewWord << ((startBits - bbW) * destPixSize)));
		} else {
			skewWord = warpSourcePixelsxDeltahyDeltahxDeltavyDeltavsmoothingsourceMap(startBits, xDelta, yDelta, deltaP12x, deltaP12y, smoothingCount, sourceMapOop);
		}
		for (word = 1; word <= nWords; word += 1) {
			mergeWord = mergewith(skewWord & halftoneWord, (longAt(destIndex)) & destMask);
			longAtput(destIndex, (destMask & mergeWord) | ((~destMask) & (longAt(destIndex))));
			destIndex += 4;
			if (word >= (nWords - 1)) {
				if (!(word == nWords)) {
					destMask = mask2;
					skewWord = warpSourcePixelsxDeltahyDeltahxDeltavyDeltavsmoothingsourceMap(pixPerWord, xDelta, yDelta, deltaP12x, deltaP12y, smoothingCount, sourceMapOop);
				}
			} else {
				destMask = 4294967295U;
				skewWord = warpSourcePixelsxDeltahyDeltahxDeltavyDeltavsmoothingsourceMap(pixPerWord, xDelta, yDelta, deltaP12x, deltaP12y, smoothingCount, sourceMapOop);
			}
		}
		pAx += deltaP12x;
		pAy += deltaP12y;
		pBx += deltaP43x;
		pBy += deltaP43y;
		destIndex += destDelta;
	}
}

int warpSourcePixelsxDeltahyDeltahxDeltavyDeltavsmoothingsourceMap(int nPix, int xDeltah, int yDeltah, int xDeltav, int yDeltav, int n, int sourceMapOop) {
    int destWord;
    int sourcePix;
    int sourcePixMask;
    int destPixMask;
    int srcPixPerWord;
    int destPix;
    int i;
    int mask;
    int srcPix;
    int destPix1;
    int d;
    int mask3;
    int srcPix1;
    int destPix2;
    int d1;
    int mask4;
    int srcPix2;
    int destPix3;
    int d2;
    int mask5;
    int srcPix3;
    int destPix4;
    int d3;

	if (sourcePixSize == 32) {
		sourcePixMask = -1;
	} else {
		sourcePixMask = (1 << sourcePixSize) - 1;
	}
	if (destPixSize == 32) {
		destPixMask = -1;
	} else {
		destPixMask = (1 << destPixSize) - 1;
	}
	srcPixPerWord = 32 / sourcePixSize;
	destWord = 0;
	for (i = 1; i <= nPix; i += 1) {
		if (n > 1) {
			destPix = (smoothPixatXfyfdxhdyhdxvdyvpixPerWordpixelMasksourceMap(n, sx, sy, xDeltah / n, yDeltah / n, xDeltav / n, yDeltav / n, srcPixPerWord, sourcePixMask, sourceMapOop)) & destPixMask;
		} else {
			sourcePix = (sourcePixAtXypixPerWord(((unsigned) sx) >> 14, ((unsigned) sy) >> 14, srcPixPerWord)) & sourcePixMask;
			if (colorMap == nilObj) {
				if (destPixSize == sourcePixSize) {
					destPix = sourcePix;
				} else {
					if (sourcePixSize >= 16) {
						if (sourcePixSize == 16) {
							/* begin rgbMap:from:to: */
							if ((d = 8 - 5) > 0) {
								mask = (1 << 5) - 1;
								srcPix = sourcePix << d;
								mask = mask << d;
								destPix1 = srcPix & mask;
								mask = mask << 8;
								srcPix = srcPix << d;
								destPix = (destPix1 + (srcPix & mask)) + ((srcPix << d) & (mask << 8));
								goto l1;
							} else {
								if (d == 0) {
									destPix = sourcePix;
									goto l1;
								}
								if (sourcePix == 0) {
									destPix = sourcePix;
									goto l1;
								}
								d = 5 - 8;
								mask = (1 << 8) - 1;
								srcPix = ((unsigned) sourcePix) >> d;
								destPix1 = srcPix & mask;
								mask = mask << 8;
								srcPix = ((unsigned) srcPix) >> d;
								destPix1 = (destPix1 + (srcPix & mask)) + ((((unsigned) srcPix) >> d) & (mask << 8));
								if (destPix1 == 0) {
									destPix = 1;
									goto l1;
								}
								destPix = destPix1;
								goto l1;
							}
						l1:	/* end rgbMap:from:to: */;
						} else {
							/* begin rgbMap:from:to: */
							if ((d1 = 5 - 8) > 0) {
								mask3 = (1 << 8) - 1;
								srcPix1 = sourcePix << d1;
								mask3 = mask3 << d1;
								destPix2 = srcPix1 & mask3;
								mask3 = mask3 << 5;
								srcPix1 = srcPix1 << d1;
								destPix = (destPix2 + (srcPix1 & mask3)) + ((srcPix1 << d1) & (mask3 << 5));
								goto l2;
							} else {
								if (d1 == 0) {
									destPix = sourcePix;
									goto l2;
								}
								if (sourcePix == 0) {
									destPix = sourcePix;
									goto l2;
								}
								d1 = 8 - 5;
								mask3 = (1 << 5) - 1;
								srcPix1 = ((unsigned) sourcePix) >> d1;
								destPix2 = srcPix1 & mask3;
								mask3 = mask3 << 5;
								srcPix1 = ((unsigned) srcPix1) >> d1;
								destPix2 = (destPix2 + (srcPix1 & mask3)) + ((((unsigned) srcPix1) >> d1) & (mask3 << 5));
								if (destPix2 == 0) {
									destPix = 1;
									goto l2;
								}
								destPix = destPix2;
								goto l2;
							}
						l2:	/* end rgbMap:from:to: */;
						}
					} else {
						destPix = sourcePix & destPixMask;
					}
				}
			} else {
				if (sourcePixSize >= 16) {
					if (sourcePixSize == 16) {
						/* begin rgbMap:from:to: */
						if ((d2 = cmBitsPerColor - 5) > 0) {
							mask4 = (1 << 5) - 1;
							srcPix2 = sourcePix << d2;
							mask4 = mask4 << d2;
							destPix3 = srcPix2 & mask4;
							mask4 = mask4 << cmBitsPerColor;
							srcPix2 = srcPix2 << d2;
							sourcePix = (destPix3 + (srcPix2 & mask4)) + ((srcPix2 << d2) & (mask4 << cmBitsPerColor));
							goto l3;
						} else {
							if (d2 == 0) {
								sourcePix = sourcePix;
								goto l3;
							}
							if (sourcePix == 0) {
								sourcePix = sourcePix;
								goto l3;
							}
							d2 = 5 - cmBitsPerColor;
							mask4 = (1 << cmBitsPerColor) - 1;
							srcPix2 = ((unsigned) sourcePix) >> d2;
							destPix3 = srcPix2 & mask4;
							mask4 = mask4 << cmBitsPerColor;
							srcPix2 = ((unsigned) srcPix2) >> d2;
							destPix3 = (destPix3 + (srcPix2 & mask4)) + ((((unsigned) srcPix2) >> d2) & (mask4 << cmBitsPerColor));
							if (destPix3 == 0) {
								sourcePix = 1;
								goto l3;
							}
							sourcePix = destPix3;
							goto l3;
						}
					l3:	/* end rgbMap:from:to: */;
					} else {
						/* begin rgbMap:from:to: */
						if ((d3 = cmBitsPerColor - 8) > 0) {
							mask5 = (1 << 8) - 1;
							srcPix3 = sourcePix << d3;
							mask5 = mask5 << d3;
							destPix4 = srcPix3 & mask5;
							mask5 = mask5 << cmBitsPerColor;
							srcPix3 = srcPix3 << d3;
							sourcePix = (destPix4 + (srcPix3 & mask5)) + ((srcPix3 << d3) & (mask5 << cmBitsPerColor));
							goto l4;
						} else {
							if (d3 == 0) {
								sourcePix = sourcePix;
								goto l4;
							}
							if (sourcePix == 0) {
								sourcePix = sourcePix;
								goto l4;
							}
							d3 = 8 - cmBitsPerColor;
							mask5 = (1 << cmBitsPerColor) - 1;
							srcPix3 = ((unsigned) sourcePix) >> d3;
							destPix4 = srcPix3 & mask5;
							mask5 = mask5 << cmBitsPerColor;
							srcPix3 = ((unsigned) srcPix3) >> d3;
							destPix4 = (destPix4 + (srcPix3 & mask5)) + ((((unsigned) srcPix3) >> d3) & (mask5 << cmBitsPerColor));
							if (destPix4 == 0) {
								sourcePix = 1;
								goto l4;
							}
							sourcePix = destPix4;
							goto l4;
						}
					l4:	/* end rgbMap:from:to: */;
					}
				}
				destPix = (longAt(((((char *) colorMap)) + 4) + (sourcePix << 2))) & destPixMask;
			}
		}
		destWord = (destWord << destPixSize) | destPix;
		sx += xDeltah;
		sy += yDeltah;
	}
	return destWord;
}

int writeImageFile(int imageBytes) {
    sqImageFile f;
    int i;
    int bytesWritten;
    int headerStart;
    int headerSize;

	headerStart = 0;
	headerSize = 64;
	f = sqImageFileOpen(imageName, "wb");
	if (f == null) {
		/* begin success: */
		successFlag = false && successFlag;
		return null;
	}
	/* Note: on Unix systems one could put an exec command here, padded to 512 bytes */;
	sqImageFileSeek(f, headerStart);
	putLongtoFile(6502, f);
	putLongtoFile(headerSize, f);
	putLongtoFile(imageBytes, f);
	putLongtoFile(startOfMemory(), f);
	putLongtoFile(specialObjectsOop, f);
	putLongtoFile(lastHash, f);
	putLongtoFile(ioScreenSize(), f);
	putLongtoFile(fullScreenFlag, f);
	for (i = 1; i <= 8; i += 1) {
		putLongtoFile(0, f);
	}
	if (!(successFlag)) {
		sqImageFileClose(f);
		return null;
	}
	sqImageFileSeek(f, headerStart + headerSize);
	bytesWritten = sqImageFileWrite(memory, sizeof(unsigned char), imageBytes, f);
	/* begin success: */
	successFlag = (bytesWritten == imageBytes) && successFlag;
	sqImageFileClose(f);
	dir_SetMacFileTypeAndCreator(imageName, strlen(imageName), "STim", "FAST");
}
