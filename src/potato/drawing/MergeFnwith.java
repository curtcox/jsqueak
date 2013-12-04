/*
This work is a derivative of JSqueak (http://research.sun.com/projects/JSqueak). 

Copyright (c) 2008  Daniel H. H. Ingalls, Sun Microsystems, Inc.  All rights reserved.
 
Portions copyright Frank Feinbube, Robert Wierschke.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/*
Portions of the software are derived from classes of the VMMaker-Package 3.8b3.
The Smalltalk code is still annotated as comments.
 */

package potato.drawing;

/**
 * @author Daniel Ingalls
 *  
 * @author Frank Feinbube
 * @author Robert Wierschke
 */
public class MergeFnwith {
    BitBlt bitBlt;
    
    public MergeFnwith(BitBlt bitBlt){
        this.bitBlt = bitBlt;
    }
    
    /*
    initBBOpTable
	self cCode: 'opTable[0+1] = (int)clearWordwith'.
	self cCode: 'opTable[1+1] = (int)bitAndwith'.
	self cCode: 'opTable[2+1] = (int)bitAndInvertwith'.
	self cCode: 'opTable[3+1] = (int)sourceWordwith'.
	self cCode: 'opTable[4+1] = (int)bitInvertAndwith'.
	self cCode: 'opTable[5+1] = (int)destinationWordwith'.
	self cCode: 'opTable[6+1] = (int)bitXorwith'.
	self cCode: 'opTable[7+1] = (int)bitOrwith'.
	self cCode: 'opTable[8+1] = (int)bitInvertAndInvertwith'.
	self cCode: 'opTable[9+1] = (int)bitInvertXorwith'.
	self cCode: 'opTable[10+1] = (int)bitInvertDestinationwith'.
	self cCode: 'opTable[11+1] = (int)bitOrInvertwith'.
	self cCode: 'opTable[12+1] = (int)bitInvertSourcewith'.
	self cCode: 'opTable[13+1] = (int)bitInvertOrwith'.
	self cCode: 'opTable[14+1] = (int)bitInvertOrInvertwith'.
	self cCode: 'opTable[15+1] = (int)destinationWordwith'.
	self cCode: 'opTable[16+1] = (int)destinationWordwith'.
	self cCode: 'opTable[17+1] = (int)destinationWordwith'.
	self cCode: 'opTable[18+1] = (int)addWordwith'.
	self cCode: 'opTable[19+1] = (int)subWordwith'.
	self cCode: 'opTable[20+1] = (int)rgbAddwith'.
	self cCode: 'opTable[21+1] = (int)rgbSubwith'.
	self cCode: 'opTable[22+1] = (int)OLDrgbDiffwith'.
	self cCode: 'opTable[23+1] = (int)OLDtallyIntoMapwith'.
	self cCode: 'opTable[24+1] = (int)alphaBlendwith'.
	self cCode: 'opTable[25+1] = (int)pixPaintwith'.
	self cCode: 'opTable[26+1] = (int)pixMaskwith'.
	self cCode: 'opTable[27+1] = (int)rgbMaxwith'.
	self cCode: 'opTable[28+1] = (int)rgbMinwith'.
	self cCode: 'opTable[29+1] = (int)rgbMinInvertwith'.
	self cCode: 'opTable[30+1] = (int)alphaBlendConstwith'.
	self cCode: 'opTable[31+1] = (int)alphaPaintConstwith'.
	self cCode: 'opTable[32+1] = (int)rgbDiffwith'.
	self cCode: 'opTable[33+1] = (int)tallyIntoMapwith'.
	self cCode: 'opTable[34+1] = (int)alphaBlendScaledwith'.
	self cCode: 'opTable[35+1] = (int)alphaBlendScaledwith'.
	self cCode: 'opTable[36+1] = (int)alphaBlendScaledwith'.	
	self cCode: 'opTable[37+1] = (int)rgbMulwith'.
	self cCode: 'opTable[38+1] = (int)pixSwapwith'.
	self cCode: 'opTable[39+1] = (int)pixClearwith'.
	self cCode: 'opTable[40+1] = (int)fixAlphawith'.
     */ 
    public int mergeFnwith(int sourceWord, int destinationWord) {
        switch (bitBlt.combinationRule+1) {
            // clearWord: source with: destination
            // ^ 0
            case 1:
                return 0;
                
            // bitAnd: sourceWord with: destinationWord
            // ^sourceWord bitAnd: destinationWord
            case 2: 
                return sourceWord & destinationWord;
                
            // bitAndInvert: sourceWord with: destinationWord
            // ^sourceWord bitAnd: destinationWord bitInvert32
            case 3:
                return sourceWord & (~destinationWord);
                
            // sourceWord: sourceWord with: destinationWord
            // ^sourceWord
            case 4:
                return sourceWord;
                
            // bitInvertAnd: sourceWord with: destinationWord
            // ^sourceWord bitInvert32 bitAnd: destinationWord
            case 5:
                return (~sourceWord) & destinationWord;
                
            // destinationWord: sourceWord with: destinationWord
            // ^destinationWord    
            case 6:
                return destinationWord;
                
            // bitXor: sourceWord with: destinationWord
            // ^sourceWord bitXor: destinationWord
            case 7:
                return sourceWord ^ destinationWord;
            
            // bitOr: sourceWord with: destinationWord
            // ^sourceWord bitOr: destinationWord
            case 8:
                return sourceWord | destinationWord;
                
            // bitInvertAndInvert: sourceWord with: destinationWord
            // ^sourceWord bitInvert32 bitAnd: destinationWord bitInvert32    
            case 9:
                return (~sourceWord) & (~destinationWord);
                
            // bitInvertXor: sourceWord with: destinationWord
            // ^sourceWord bitInvert32 bitXor: destinationWord    
            case 10:
                return (~sourceWord) ^ destinationWord;
                
            // bitInvertDestination: sourceWord with: destinationWord
            // ^destinationWord bitInvert32    
            case 11:
                return ~destinationWord;
                
            // bitOrInvert: sourceWord with: destinationWord
            // ^sourceWord bitOr: destinationWord bitInvert32
            case 12:
                return sourceWord | (~destinationWord);
                
            // bitInvertSource: sourceWord with: destinationWord
            // ^sourceWord bitInvert32
            case 13:
                return ~sourceWord;
                
            // bitInvertOr: sourceWord with: destinationWord
            // ^sourceWord bitInvert32 bitOr: destinationWord    
            case 14:
                return (~sourceWord) | destinationWord;
            
            // bitInvertOrInvert: sourceWord with: destinationWord
            // ^sourceWord bitInvert32 bitOr: destinationWord bitInvert32
            case 15:
                return (~sourceWord) | (~destinationWord);
                
            // destinationWord: sourceWord with: destinationWord
            // ^destinationWord
            case 16:
            case 17:
            case 18:
                return destinationWord;
                
            // addWord: sourceWord with: destinationWord
            // ^sourceWord + destinationWord
            case 19:
                return sourceWord + destinationWord;
            
            // subWord: sourceWord with: destinationWord
            // ^sourceWord - destinationWord    
            case 20:
                return sourceWord - destinationWord;
                
            case 21:
                return rgbAddwith(sourceWord, destinationWord);
                
            case 22:
                return rgbSubwith(sourceWord, destinationWord);
                
            case 23:
                return OLDrgbDiffwith(sourceWord, destinationWord);
                
            case 24:
                return OLDtallyIntoMapwith(sourceWord, destinationWord);
                
            case 25:
                return alphaBlendwith(sourceWord, destinationWord);
                
            // pixPaint: sourceWord with: destinationWord
            // self inline: false.
	    // sourceWord = 0 ifTrue: [^ destinationWord].
	    // ^ sourceWord bitOr: (self partitionedAND: sourceWord bitInvert32 to: destinationWord nBits: destDepth nPartitions: destPPW)    
            case 26:                
                if (sourceWord == 0) {
                    return destinationWord;
                }
                return sourceWord | (partitionedANDtonBitsnPartitions(~sourceWord, destinationWord, bitBlt.dest.depth, bitBlt.dest.pixPerWord));

            // pixMask: sourceWord with: destinationWord
            // self inline: false.
            // ^ self partitionedAND: sourceWord bitInvert32 to: destinationWord nBits: destDepth nPartitions: destPPW
            case 27:
                return partitionedANDtonBitsnPartitions(~sourceWord, destinationWord, bitBlt.dest.depth, bitBlt.dest.pixPerWord);
                
            case 28:
                return rgbMaxwith(sourceWord, destinationWord);
                
            case 29:
                return rgbMinwith(sourceWord, destinationWord);
            
            /* LEFT TO IMPLEMENT:
            	case 29+1: return rgbMinInvertwith(sourceWord, destinationWord);
                case 30+1: return alphaBlendConstwith(sourceWord, destinationWord);
                case 31+1: return alphaPaintConstwith(sourceWord, destinationWord);
                case 32+1: return rgbDiffwith(sourceWord, destinationWord);
                case 33+1: return tallyIntoMapwith(sourceWord, destinationWord);
                case 34+1: return alphaBlendScaledwith(sourceWord, destinationWord);
                case 35+1: return alphaBlendScaledwith(sourceWord, destinationWord);
                case 36+1: return alphaBlendScaledwith(sourceWord, destinationWord);	
                case 37+1: return rgbMulwith(sourceWord, destinationWord);
                case 38+1: return pixSwapwith(sourceWord, destinationWord);
                case 39+1: return pixClearwith(sourceWord, destinationWord);
                case 40+1: return fixAlphawith(sourceWord, destinationWord);
             */ 
                
            default:
                System.out.println("This should never happen! MergeFnwith.mergefnwith()");
                System.out.println("Please implement combination rule " + bitBlt.combinationRule + ".");
                return sourceWord;
        }
    }

    /*
     rgbAdd: sourceWord with: destinationWord
	self inline: false.
	destDepth < 16 ifTrue:
		["Add each pixel separately"
		^ self partitionedAdd: sourceWord to: destinationWord
						nBits: destDepth nPartitions: destPPW].
	destDepth = 16 ifTrue:
		["Add RGB components of each pixel separately"
		^ (self partitionedAdd: sourceWord to: destinationWord
						nBits: 5 nPartitions: 3)
		+ ((self partitionedAdd: sourceWord>>16 to: destinationWord>>16
						nBits: 5 nPartitions: 3) << 16)]
	ifFalse:
		["Add RGB components of the pixel separately"
		^ self partitionedAdd: sourceWord to: destinationWord
						nBits: 8 nPartitions: 3] 
     */ 
    int rgbAddwith(int sourceWord, int destinationWord){
        if(bitBlt.dest.depth < 16){ // destDepth < 16 ifTrue: // ["Add each pixel separately"
            // ^ self partitionedAdd: sourceWord to: destinationWord nBits: destDepth nPartitions: destPPW].
            return partitionedAddtonBitsnPartitions(sourceWord, destinationWord, bitBlt.dest.depth, bitBlt.dest.pixPerWord); 
        } 
        if(bitBlt.dest.depth == 16){ // destDepth = 16 ifTrue: // ["Add RGB components of each pixel separately"
            // ^ (self partitionedAdd: sourceWord to: destinationWord nBits: 5 nPartitions: 3) 
            //      + ((self partitionedAdd: sourceWord>>16 to: destinationWord>>16 nBits: 5 nPartitions: 3) << 16)]
            return partitionedAddtonBitsnPartitions(sourceWord, destinationWord, 5, 3) 
                    + (partitionedAddtonBitsnPartitions(sourceWord>>16, destinationWord>>16, 5, 3)<<16);
        }
        else{ // ifFalse: // ["Add RGB components of the pixel separately"
            // ^ self partitionedAdd: sourceWord to: destinationWord nBits: 8 nPartitions: 3] 
            return partitionedAddtonBitsnPartitions(sourceWord, destinationWord, 8, 3);
        }
    }

    /*
    partitionedAdd: word1 to: word2 nBits: nBits nPartitions: nParts
	"Add word1 to word2 as nParts partitions of nBits each.
	This is useful for packed pixels, or packed colors"
	| mask sum result |
	mask := maskTable at: nBits.  "partition mask starts at the right"
	result := 0.
	1 to: nParts do:
		[:i |
		sum := (word1 bitAnd: mask) + (word2 bitAnd: mask).
		sum <= mask  "result must not carry out of partition"
			ifTrue: [result := result bitOr: sum]
			ifFalse: [result := result bitOr: mask].
		mask := mask << nBits  "slide left to next partition"].
	^ result
    */ 
    int partitionedAddtonBitsnPartitions(int word1, int word2, int nBits, int nParts){
        int mask = BitBlt.maskTable[nBits]; // mask := maskTable at: nBits.  "partition mask starts at the right"
        int sum;
        int result = 0; // result := 0.
        
        for( int i=1; i<= nParts; i++){ // 1 to: nParts do: // [:i |
            sum = (word1 & mask) + (word2 & mask); // sum := (word1 bitAnd: mask) + (word2 bitAnd: mask).
            if( sum <= mask){ // sum <= mask  "result must not carry out of partition"
                result |= sum; // ifTrue: [result := result bitOr: sum]
            } else { 
                result |= mask; // ifFalse: [result := result bitOr: mask].
            }
            mask = mask << nBits; // mask := mask << nBits  "slide left to next partition"].
        }
        
        return result; // ^ result
    }

    /*
    rgbSub: sourceWord with: destinationWord
	self inline: false.
	destDepth < 16 ifTrue:
		["Sub each pixel separately"
		^ self partitionedSub: sourceWord from: destinationWord
						nBits: destDepth nPartitions: destPPW].
	destDepth = 16 ifTrue:
		["Sub RGB components of each pixel separately"
		^ (self partitionedSub: sourceWord from: destinationWord
						nBits: 5 nPartitions: 3)
		+ ((self partitionedSub: sourceWord>>16 from: destinationWord>>16
						nBits: 5 nPartitions: 3) << 16)]
	ifFalse:
		["Sub RGB components of the pixel separately"
		^ self partitionedSub: sourceWord from: destinationWord
						nBits: 8 nPartitions: 3]
     */ 
    int rgbSubwith(int sourceWord, int destinationWord){
        if(bitBlt.dest.depth < 16){ // destDepth < 16 ifTrue: // ["Sub each pixel separately"
            // ^ self partitionedSub: sourceWord from: destinationWord nBits: destDepth nPartitions: destPPW].
            return partitionedSubfromnBitsnPartitions(sourceWord, destinationWord, bitBlt.dest.depth, bitBlt.dest.pixPerWord); 
        } 
        if(bitBlt.dest.depth == 16){ // destDepth = 16 ifTrue: // ["Sub RGB components of each pixel separately"
            // ^ (self partitionedSub: sourceWord from: destinationWord nBits: 5 nPartitions: 3)
            //      + ((self partitionedSub: sourceWord>>16 from: destinationWord>>16 nBits: 5 nPartitions: 3) << 16)]
            return partitionedSubfromnBitsnPartitions(sourceWord, destinationWord, 5, 3) 
                    + (partitionedSubfromnBitsnPartitions(sourceWord>>16, destinationWord>>16, 5, 3)<<16);
        }
        else{ // ifFalse: // ["Sub RGB components of the pixel separately"
            // ^ self partitionedSub: sourceWord from: destinationWord nBits: 8 nPartitions: 3]
            return partitionedSubfromnBitsnPartitions(sourceWord, destinationWord, 8, 3);
        }
    }
    
    /*
    partitionedSub: word1 from: word2 nBits: nBits nPartitions: nParts
	"Subtract word1 from word2 as nParts partitions of nBits each.
	This is useful for packed pixels, or packed colors"
	| mask result p1 p2 |
	mask := maskTable at: nBits.  "partition mask starts at the right"
	result := 0.
	1 to: nParts do:
		[:i |
		p1 := word1 bitAnd: mask.
		p2 := word2 bitAnd: mask.
		p1 < p2  "result is really abs value of thedifference"
			ifTrue: [result := result bitOr: p2 - p1]
			ifFalse: [result := result bitOr: p1 - p2].
		mask := mask << nBits  "slide left to next partition"].
	^ result
     */ 
    int partitionedSubfromnBitsnPartitions(int word1, int word2, int nBits, int nParts){
        int mask = BitBlt.maskTable[nBits]; // mask := maskTable at: nBits.  "partition mask starts at the right"
        int result = 0; // result := 0.
        int p1;
        int p2;
        
        for( int i=1; i<= nParts; i++){ // 1 to: nParts do: // [:i |
            p1 = word1 & mask; // p1 := word1 bitAnd: mask.
            p2 = word2 & mask; // p2 := word2 bitAnd: mask.
            if( p1 < p2 ){ // p1 < p2  "result is really abs value of thedifference"
                result |= p2-p1; // ifTrue: [result := result bitOr: p2 - p1]
            } else { 
                result |= p1-p2; // ifFalse: [result := result bitOr: p1 - p2].
            }
            mask = mask << nBits; // mask := mask << nBits  "slide left to next partition"].
        }
        
        return result; // ^ result
    }
    
    /*
     OLDrgbDiff: sourceWord with: destinationWord
	"Subract the pixels in the source and destination, color by color,
	and return the sum of the absolute value of all the differences.
	For non-rgb, XOR the two and return the number of differing pixels.
	Note that the region is not clipped to bit boundaries, but only to the
	nearest (enclosing) word.  This is because copyLoop does not do
	pre-merge masking.  For accurate results, you must subtract the
	values obtained from the left and right fringes."
	| diff pixMask |
	self inline: false.
	destDepth < 16 ifTrue:
		["Just xor and count differing bits if not RGB"
		diff := sourceWord bitXor: destinationWord.
		pixMask := maskTable at: destDepth.
		[diff = 0] whileFalse:
			[(diff bitAnd: pixMask) ~= 0 ifTrue: [bitCount := bitCount + 1].
			diff := diff >> destDepth].
		^ destinationWord "for no effect"].
 	destDepth = 16
		ifTrue:
		[diff := (self partitionedSub: sourceWord from: destinationWord
						nBits: 5 nPartitions: 3).
		bitCount := bitCount + (diff bitAnd: 16r1F)
							+ (diff>>5 bitAnd: 16r1F)
							+ (diff>>10 bitAnd: 16r1F).
		diff := (self partitionedSub: sourceWord>>16 from: destinationWord>>16
						nBits: 5 nPartitions: 3).
		bitCount := bitCount + (diff bitAnd: 16r1F)
							+ (diff>>5 bitAnd: 16r1F)
							+ (diff>>10 bitAnd: 16r1F)]
		ifFalse:
		[diff := (self partitionedSub: sourceWord from: destinationWord
						nBits: 8 nPartitions: 3).
		bitCount := bitCount + (diff bitAnd: 16rFF)
							+ (diff>>8 bitAnd: 16rFF)
							+ (diff>>16 bitAnd: 16rFF)].
	^ destinationWord  "For no effect on dest"
     */ 
    int OLDrgbDiffwith(int sourceWord, int destinationWord){
        int diff;
        int pixMask;
        
        if(bitBlt.dest.depth < 16 ){ // destDepth < 16 ifTrue: // ["Just xor and count differing bits if not RGB"
            diff = sourceWord ^ destinationWord; // diff := sourceWord bitXor: destinationWord.
            pixMask = BitBlt.maskTable[bitBlt.dest.depth]; // pixMask := maskTable at: destDepth.
            
            while(diff != 0){ // [diff = 0] whileFalse:
                if((diff & pixMask) != 0){ // [(diff bitAnd: pixMask) ~= 0 ifTrue: [bitCount := bitCount + 1].
                    bitBlt.bitCount++;
                }
		diff = diff >> bitBlt.dest.depth; // diff := diff >> destDepth].
            }
            return destinationWord; // ^ destinationWord "for no effect"].
        }
        if(bitBlt.dest.depth == 16) { // destDepth = 16 // ifTrue:
            // [diff := (self partitionedSub: sourceWord from: destinationWord nBits: 5 nPartitions: 3).
            diff = partitionedSubfromnBitsnPartitions(sourceWord, destinationWord, 5, 3);
            // bitCount := bitCount + (diff bitAnd: 16r1F) + (diff>>5 bitAnd: 16r1F) + (diff>>10 bitAnd: 16r1F).
            bitBlt.bitCount += (diff & 0x1F) + (diff>>5 & 0x1F) + (diff>>10 & 0x1F); 
            
            // diff := (self partitionedSub: sourceWord>>16 from: destinationWord>>16 nBits: 5 nPartitions: 3).
            diff = partitionedSubfromnBitsnPartitions(sourceWord>>16, destinationWord>>16, 5, 3);
            // bitCount := bitCount + (diff bitAnd: 16r1F) + (diff>>5 bitAnd: 16r1F) + (diff>>10 bitAnd: 16r1F)]
            bitBlt.bitCount += (diff & 0x1F) + (diff>>5 & 0x1F) + (diff>>10 & 0x1F); 
        }
        else // ifFalse:
        {
            // [diff := (self partitionedSub: sourceWord from: destinationWord nBits: 8 nPartitions: 3).
            diff = partitionedSubfromnBitsnPartitions(sourceWord, destinationWord, 8, 3);
            // bitCount := bitCount + (diff bitAnd: 16rFF) + (diff>>8 bitAnd: 16rFF) + (diff>>16 bitAnd: 16rFF)].
             bitBlt.bitCount += (diff & 0xFF) + (diff>>8 & 0xFF) + (diff>>16 & 0xFF);
        }
        
        return destinationWord; // ^ destinationWord  "For no effect on dest"
    }
    
    /*
    OLDtallyIntoMap: sourceWord with: destinationWord
	"Tally pixels into the color map.  Note that the source should be 
	specified = destination, in order for the proper color map checks 
	to be performed at setup.
	Note that the region is not clipped to bit boundaries, but only to the
	nearest (enclosing) word.  This is because copyLoop does not do
	pre-merge masking.  For accurate results, you must subtract the
	values obtained from the left and right fringes."
	| mapIndex pixMask shiftWord |
	(cmFlags bitAnd: (ColorMapPresent bitOr: ColorMapIndexedPart)) =
		(ColorMapPresent bitOr: ColorMapIndexedPart)
			ifFalse: [^ destinationWord "no op"].
	destDepth < 16 ifTrue:
		["loop through all packed pixels."
		pixMask := (maskTable at: destDepth) bitAnd: cmMask.
		shiftWord := destinationWord.
		1 to: destPPW do:
			[:i |
			mapIndex := shiftWord bitAnd: pixMask.
			self tallyMapAt: mapIndex put: (self tallyMapAt: mapIndex) + 1.
			shiftWord := shiftWord >> destDepth].
		^ destinationWord].
	destDepth = 16 ifTrue:
		["Two pixels  Tally the right half..."
		mapIndex := self rgbMap: (destinationWord bitAnd: 16rFFFF) from: 5 to: cmBitsPerColor.
		self tallyMapAt: mapIndex put: (self tallyMapAt: mapIndex) + 1.
		"... and then left half"
		mapIndex := self rgbMap: destinationWord>>16 from: 5 to: cmBitsPerColor.
		self tallyMapAt: mapIndex put: (self tallyMapAt: mapIndex) + 1]
	ifFalse:
		["Just one pixel."
		mapIndex := self rgbMap: destinationWord from: 8 to: cmBitsPerColor.
		self tallyMapAt: mapIndex put: (self tallyMapAt: mapIndex) + 1].
	^ destinationWord  "For no effect on dest"
     */ 
    int OLDtallyIntoMapwith(int sourceWord, int destinationWord){
        int mapIndex;
        int pixMask;
        int shiftWord;
                
        //(cmFlags bitAnd: (ColorMapPresent bitOr: ColorMapIndexedPart)) = (ColorMapPresent bitOr: ColorMapIndexedPart) 
        if( !((bitBlt.cmFlags & (BitBlt.ColorMapPresent | BitBlt.ColorMapIndexedPart))== (BitBlt.ColorMapPresent | BitBlt.ColorMapIndexedPart)))
            return destinationWord; // ifFalse: [^ destinationWord "no op"].
        
        if(bitBlt.dest.depth < 16 ){ // destDepth < 16 ifTrue: // ["loop through all packed pixels."
            pixMask = BitBlt.maskTable[bitBlt.dest.depth] & bitBlt.cmMask; // pixMask := (maskTable at: destDepth) bitAnd: cmMask.
            shiftWord = destinationWord; // shiftWord := destinationWord.
            for(int i=1; i<=bitBlt.dest.pixPerWord; i++) { // 1 to: destPPW do: // [:i |
                mapIndex = shiftWord & pixMask; // mapIndex := shiftWord bitAnd: pixMask.
                tallyMapAtput(mapIndex, tallyMapAt(mapIndex)+1); // self tallyMapAt: mapIndex put: (self tallyMapAt: mapIndex) + 1.
		shiftWord = shiftWord>>bitBlt.dest.depth; // shiftWord := shiftWord >> destDepth].
            }
			
            return destinationWord; // ^ destinationWord].
        }
        if(bitBlt.dest.depth == 16) { // destDepth = 16 ifTrue: // ["Two pixels  Tally the right half..."
            mapIndex = rgbMapfromto(destinationWord & 0xFFFF, 5, bitBlt.cmBitsPerColor); // mapIndex := self rgbMap: (destinationWord bitAnd: 16rFFFF) from: 5 to: cmBitsPerColor.
            tallyMapAtput(mapIndex, tallyMapAt(mapIndex)+1); // self tallyMapAt: mapIndex put: (self tallyMapAt: mapIndex) + 1.
            
            // "... and then left half"
            mapIndex = rgbMapfromto(destinationWord>>16, 5, bitBlt.cmBitsPerColor); // mapIndex := self rgbMap: destinationWord>>16 from: 5 to: cmBitsPerColor.
            tallyMapAtput(mapIndex, tallyMapAt(mapIndex)+1); // self tallyMapAt: mapIndex put: (self tallyMapAt: mapIndex) + 1]
        }
        else { // ifFalse: // ["Just one pixel."
            mapIndex = rgbMapfromto(destinationWord, 8, bitBlt.cmBitsPerColor); // mapIndex := self rgbMap: destinationWord from: 8 to: cmBitsPerColor.
            tallyMapAtput(mapIndex, tallyMapAt(mapIndex)+1); // self tallyMapAt: mapIndex put: (self tallyMapAt: mapIndex) + 1].
        }
        
        return destinationWord; // ^ destinationWord  "For no effect on dest"
    }
    
    /*
    tallyMapAt: idx
	"Return the word at position idx from the colorMap"
	^cmLookupTable at: (idx bitAnd: cmMask)
     */ 
    int tallyMapAt(int idx){
        return bitBlt.cmLookupTable[idx & bitBlt.cmMask];
    }
    
    /*
    tallyMapAt: idx put: value
	"Store the word at position idx in the colorMap"
	^cmLookupTable at: (idx bitAnd: cmMask) put: value
     */ 
    void tallyMapAtput(int idx, int value){
        bitBlt.cmLookupTable[idx & bitBlt.cmMask] = value; 
    }
    
    /*
    rgbMap: sourcePixel from: nBitsIn to: nBitsOut
	"Convert the given pixel value with nBitsIn bits for each color component to a pixel value with nBitsOut bits for each color component. Typical values for nBitsIn/nBitsOut are 3, 5, or 8."
	| mask d srcPix destPix |
	self inline: true.
	(d := nBitsOut - nBitsIn) > 0
		ifTrue:
			["Expand to more bits by zero-fill"
			mask := (1 << nBitsIn) - 1.  "Transfer mask"
			srcPix := sourcePixel << d.
			mask := mask << d.
			destPix := srcPix bitAnd: mask.
			mask := mask << nBitsOut.
			srcPix := srcPix << d.
			^ destPix + (srcPix bitAnd: mask)
				 	+ (srcPix << d bitAnd: mask << nBitsOut)]
		ifFalse:
			["Compress to fewer bits by truncation"
			d = 0 ifTrue:
				[nBitsIn = 5 ifTrue:
					["Sometimes called with 16 bits, though pixel is 15,
					but we must never return more than 15."
					^ sourcePixel bitAnd: 16r7FFF].
				nBitsIn = 8 ifTrue:
					["Sometimes called with 32 bits, though pixel is 24,
					but we must never return more than 24."
					^ sourcePixel bitAnd: 16rFFFFFF].
				^ sourcePixel].  "no compression"
			sourcePixel = 0 ifTrue: [^ sourcePixel].  "always map 0 (transparent) to 0"
			d := nBitsIn - nBitsOut.
			mask := (1 << nBitsOut) - 1.  "Transfer mask"
			srcPix := sourcePixel >> d.
			destPix := srcPix bitAnd: mask.
			mask := mask << nBitsOut.
			srcPix := srcPix >> d.
			destPix := destPix + (srcPix bitAnd: mask)
					+ (srcPix >> d bitAnd: mask << nBitsOut).
			destPix = 0 ifTrue: [^ 1].  "Dont fall into transparent by truncation"
			^ destPix]
     */ 
    int rgbMapfromto(int sourcePixel, int nBitsIn, int nBitsOut){
        int mask;
        int d;
        int srcPix;
        int destPix;
        
        if((d = nBitsOut - nBitsIn) > 0){ // (d := nBitsOut - nBitsIn) > 0 // ifTrue:
            // ["Expand to more bits by zero-fill"
            mask = (1 << nBitsIn) - 1; // mask := (1 << nBitsIn) - 1.  "Transfer mask"
            srcPix = sourcePixel << d; // srcPix := sourcePixel << d.
            mask = mask << d; // mask := mask << d.
            destPix = srcPix & mask; // destPix := srcPix bitAnd: mask.
            mask = mask <<nBitsOut; // mask := mask << nBitsOut.
            srcPix = srcPix << d; // srcPix := srcPix << d.
            return destPix + (srcPix & mask) + ((srcPix << d)&(mask << nBitsOut)); // ^ destPix + (srcPix bitAnd: mask) + (srcPix << d bitAnd: mask << nBitsOut)]
        } else { // ifFalse:
            // ["Compress to fewer bits by truncation"
            if(d==0){ // d = 0 ifTrue:
                if( nBitsIn == 5){ // [nBitsIn = 5 ifTrue:
                    // ["Sometimes called with 16 bits, though pixel is 15, but we must never return more than 15."
                    return sourcePixel & 0x7FFF; // ^ sourcePixel bitAnd: 16r7FFF].
                }
                if( nBitsIn == 8){ // nBitsIn = 8 ifTrue:
                    // ["Sometimes called with 32 bits, though pixel is 24, but we must never return more than 24."
                    return sourcePixel & 0xFFFFFF; // ^ sourcePixel bitAnd: 16rFFFFFF].
                }
		return sourcePixel; // ^ sourcePixel].  "no compression"
            }
            if (sourcePixel == 0) { // sourcePixel = 0 ifTrue: [^ sourcePixel].  "always map 0 (transparent) to 0"
                return sourcePixel;
            }
            d = nBitsIn - nBitsOut; // d := nBitsIn - nBitsOut.
            mask = (1<<nBitsOut) -1; // mask := (1 << nBitsOut) - 1.  "Transfer mask"
            srcPix = sourcePixel >> d; // srcPix := sourcePixel >> d.
            destPix = srcPix & mask; // destPix := srcPix bitAnd: mask.
            mask = mask << nBitsOut; // mask := mask << nBitsOut.
            srcPix = srcPix >> d; // srcPix := srcPix >> d.
            destPix += (srcPix & mask) + ((srcPix >> d) & (mask << nBitsOut)); // destPix := destPix + (srcPix bitAnd: mask) + (srcPix >> d bitAnd: mask << nBitsOut).
            if( destPix == 0) // destPix = 0 ifTrue: [^ 1].  "Dont fall into transparent by truncation"
                return 1;
            
            return destPix; // ^ destPix]
        }
    }
    
    /*
    alphaBlend: sourceWord with: destinationWord
	"Blend sourceWord with destinationWord, assuming both are 32-bit pixels.
	The source is assumed to have 255*alpha in the high 8 bits of each pixel,
	while the high 8 bits of the destinationWord will be ignored.
	The blend produced is alpha*source + (1-alpha)*dest, with
	the computation being performed independently on each color
	component.  The high byte of the result will be 0."
	| alpha unAlpha colorMask result blend shift |
	self inline: false.
	alpha := sourceWord >> 24.  "High 8 bits of source pixel"
	alpha = 0 ifTrue: [ ^ destinationWord ].
	alpha = 255 ifTrue: [ ^ sourceWord ].
	unAlpha := 255 - alpha.
	colorMask := 16rFF.
	result := 0.

	"red"
	shift := 0.
	blend := ((sourceWord >> shift bitAnd: colorMask) * alpha) +
				((destinationWord>>shift bitAnd: colorMask) * unAlpha)
			 	+ 254 // 255 bitAnd: colorMask.
	result := result bitOr: blend << shift.
	"green"
	shift := 8.
	blend := ((sourceWord >> shift bitAnd: colorMask) * alpha) +
				((destinationWord>>shift bitAnd: colorMask) * unAlpha)
			 	+ 254 // 255 bitAnd: colorMask.
	result := result bitOr: blend << shift.
	"blue"
	shift := 16.
	blend := ((sourceWord >> shift bitAnd: colorMask) * alpha) +
				((destinationWord>>shift bitAnd: colorMask) * unAlpha)
			 	+ 254 // 255 bitAnd: colorMask.
	result := result bitOr: blend << shift.
	"alpha (pre-multiplied)"
	shift := 24.
	blend := (alpha * 255) +
				((destinationWord>>shift bitAnd: colorMask) * unAlpha)
			 	+ 254 // 255 bitAnd: colorMask.
	result := result bitOr: blend << shift.
	^ result
     */ 
    int alphaBlendwith(int sourceWord, int destinationWord){
        int alpha, unAlpha, colorMask, result, blend, shift;
        alpha = sourceWord >> 24; // alpha := sourceWord >> 24.  "High 8 bits of source pixel"
        if(alpha == 0) { // alpha = 0 ifTrue: [ ^ destinationWord ].
            return destinationWord;
        }
        if( alpha == 255){ // alpha = 255 ifTrue: [ ^ sourceWord ].
            return sourceWord;
        }
        
        unAlpha = 255 - alpha; // unAlpha := 255 - alpha.
        colorMask = 0xFF; // colorMask := 16rFF.
        result = 0; // result := 0.
	
	// "red"
        shift = 0; // shift := 0.
        // blend := ((sourceWord >> shift bitAnd: colorMask) * alpha) + ((destinationWord>>shift bitAnd: colorMask) * unAlpha) + 254 // 255 bitAnd: colorMask.
        blend = (((sourceWord >> shift) & colorMask)*alpha) + (((destinationWord >> shift) & colorMask)*unAlpha) + 254;
	result |= blend << shift; // result := result bitOr: blend << shift.

        // "green"
	shift = 8; // shift := 8.
        // blend := ((sourceWord >> shift bitAnd: colorMask) * alpha) + ((destinationWord>>shift bitAnd: colorMask) * unAlpha) + 254 // 255 bitAnd: colorMask.
        blend = (((sourceWord >> shift) & colorMask)*alpha) + (((destinationWord >> shift) & colorMask)*unAlpha) + 254;
	result |= blend << shift; // result := result bitOr: blend << shift.
        
	// "blue"
	shift = 16; //shift := 16.
	// blend := ((sourceWord >> shift bitAnd: colorMask) * alpha) + ((destinationWord>>shift bitAnd: colorMask) * unAlpha) + 254 // 255 bitAnd: colorMask.
        blend = (((sourceWord >> shift) & colorMask)*alpha) + (((destinationWord >> shift) & colorMask)*unAlpha) + 254;
	result |= blend << shift; // result := result bitOr: blend << shift.
	
        // "alpha (pre-multiplied)"
	shift = 24; //shift := 24.
	// blend := (alpha * 255) + ((destinationWord>>shift bitAnd: colorMask) * unAlpha) + 254 // 255 bitAnd: colorMask.
        blend = (alpha * 255) + (((destinationWord>>shift) & colorMask)*unAlpha) + 254;
	result |= blend << shift; // result := result bitOr: blend << shift.
	
        return result;
    }
    
    /*
    partitionedAND: word1 to: word2 nBits: nBits nPartitions: nParts
	"AND word1 to word2 as nParts partitions of nBits each.
	Any field of word1 not all-ones is treated as all-zeroes.
	Used for erasing, eg, brush shapes prior to ORing in a color"
	| mask result |
	mask := maskTable at: nBits.  "partition mask starts at the right"
	result := 0.
	1 to: nParts do:
		[:i |
		(word1 bitAnd: mask) = mask
			ifTrue: [result := result bitOr: (word2 bitAnd: mask)].
		mask := mask << nBits  "slide left to next partition"].
	^ result
     */ 
    int partitionedANDtonBitsnPartitions(int word1, int word2, int nBits, int nParts) {
        int mask;
        int result;
        
        mask = BitBlt.maskTable[nBits]; // mask := maskTable at: nBits.  "partition mask starts at the right"
        result = 0; // result := 0.
        for (int i = 1; i <= nParts; i ++) { // 1 to: nParts do: // [:i |
            if ((word1 & mask) == mask) { // (word1 bitAnd: mask) = mask
                result |= (word2 & mask); // ifTrue: [result := result bitOr: (word2 bitAnd: mask)].
            }
            mask = mask << nBits; // mask := mask << nBits  "slide left to next partition"].
        }
        return result; // ^ result
    }
    
    /*
     rgbMax: sourceWord with: destinationWord
	self inline: false.
	destDepth < 16 ifTrue:
		["Max each pixel separately"
		^ self partitionedMax: sourceWord with: destinationWord
						nBits: destDepth nPartitions: destPPW].
	destDepth = 16 ifTrue:
		["Max RGB components of each pixel separately"
		^ (self partitionedMax: sourceWord with: destinationWord
						nBits: 5 nPartitions: 3)
		+ ((self partitionedMax: sourceWord>>16 with: destinationWord>>16
						nBits: 5 nPartitions: 3) << 16)]
	ifFalse:
		["Max RGB components of the pixel separately"
		^ self partitionedMax: sourceWord with: destinationWord
						nBits: 8 nPartitions: 3]
     */ 
    int rgbMaxwith(int sourceWord, int destinationWord){
        if(bitBlt.dest.depth < 16) { // destDepth < 16 ifTrue: // ["Max each pixel separately"
            // ^ self partitionedMax: sourceWord with: destinationWord nBits: destDepth nPartitions: destPPW].
            return partitionedMaxwithnBitsnPartitions(sourceWord, destinationWord, bitBlt.dest.depth, bitBlt.dest.pixPerWord); 
        }
        if(bitBlt.dest.depth == 16){ // destDepth = 16 ifTrue: // ["Max RGB components of each pixel separately"
            // ^ (self partitionedMax: sourceWord with: destinationWord nBits: 5 nPartitions: 3) 
            //      + ((self partitionedMax: sourceWord>>16 with: destinationWord>>16 nBits: 5 nPartitions: 3) << 16)]
            return partitionedMaxwithnBitsnPartitions(sourceWord, destinationWord, 5, 3)
                    + (partitionedMaxwithnBitsnPartitions(sourceWord>>16, destinationWord>>16, 5, 3)<<16);
        } else { // ifFalse: // ["Max RGB components of the pixel separately"
            // ^ self partitionedMax: sourceWord with: destinationWord nBits: 8 nPartitions: 3]
            return partitionedMaxwithnBitsnPartitions(sourceWord, destinationWord, 8, 3); 
        }
    }
    
    /*
    partitionedMax: word1 with: word2 nBits: nBits nPartitions: nParts
	"Max word1 to word2 as nParts partitions of nBits each"
	| mask result |
	mask := maskTable at: nBits.  "partition mask starts at the right"
	result := 0.
	1 to: nParts do:
		[:i |
		result := result bitOr: ((word2 bitAnd: mask) max: (word1 bitAnd: mask)).
		mask := mask << nBits  "slide left to next partition"].
	^ result
     */ 
    int partitionedMaxwithnBitsnPartitions(int word1, int word2, int nBits, int nParts){
        int mask, result;
        
        mask = BitBlt.maskTable[nBits]; // mask := maskTable at: nBits.  "partition mask starts at the right"
        result = 0; // result := 0.
        for (int i = 1; i <= nParts; i ++) { // 1 to: nParts do: // [:i |
            result |= Math.max(word2 & mask, word1 & mask); // result := result bitOr: ((word2 bitAnd: mask) max: (word1 bitAnd: mask)).
            mask = mask << nBits; // mask := mask << nBits  "slide left to next partition"].
        }
        return result; // ^ result
    }
    
    /*
    rgbMin: sourceWord with: destinationWord
	self inline: false.
	destDepth < 16 ifTrue:
		["Min each pixel separately"
		^ self partitionedMin: sourceWord with: destinationWord
						nBits: destDepth nPartitions: destPPW].
	destDepth = 16 ifTrue:
		["Min RGB components of each pixel separately"
		^ (self partitionedMin: sourceWord with: destinationWord
						nBits: 5 nPartitions: 3)
		+ ((self partitionedMin: sourceWord>>16 with: destinationWord>>16
						nBits: 5 nPartitions: 3) << 16)]
	ifFalse:
		["Min RGB components of the pixel separately"
		^ self partitionedMin: sourceWord with: destinationWord
						nBits: 8 nPartitions: 3]
     */ 
    int rgbMinwith(int sourceWord, int destinationWord){
        if(bitBlt.dest.depth < 16) { // destDepth < 16 ifTrue: // ["Min each pixel separately"
            // ^ self partitionedMin: sourceWord with: destinationWord nBits: destDepth nPartitions: destPPW].
            return partitionedMinwithnBitsnPartitions(sourceWord, destinationWord, bitBlt.dest.depth, bitBlt.dest.pixPerWord); 
        }
        if(bitBlt.dest.depth == 16){ // destDepth = 16 ifTrue: // ["Min RGB components of each pixel separately"
            // ^ (self partitionedMin: sourceWord with: destinationWord nBits: 5 nPartitions: 3)
            //      + ((self partitionedMin: sourceWord>>16 with: destinationWord>>16 nBits: 5 nPartitions: 3) << 16)]
            return partitionedMinwithnBitsnPartitions(sourceWord, destinationWord, 5, 3)
                    + (partitionedMinwithnBitsnPartitions(sourceWord>>16, destinationWord>>16, 5, 3)<<16);
        } else { // ifFalse: // ["Min RGB components of the pixel separately"
            // ^ self partitionedMin: sourceWord with: destinationWord nBits: 8 nPartitions: 3]
            return partitionedMinwithnBitsnPartitions(sourceWord, destinationWord, 8, 3); 
        }
    }
        
    /*
    partitionedMin: word1 with: word2 nBits: nBits nPartitions: nParts
	"Min word1 to word2 as nParts partitions of nBits each"
	| mask result |
	mask := maskTable at: nBits.  "partition mask starts at the right"
	result := 0.
	1 to: nParts do:
		[:i |
		result := result bitOr: ((word2 bitAnd: mask) min: (word1 bitAnd: mask)).
		mask := mask << nBits  "slide left to next partition"].
	^ result
     */ 
    int partitionedMinwithnBitsnPartitions(int word1, int word2, int nBits, int nParts){
        int mask, result;
        
        mask = BitBlt.maskTable[nBits]; // mask := maskTable at: nBits.  "partition mask starts at the right"
        result = 0; // result := 0.
        for (int i = 1; i <= nParts; i ++) { // 1 to: nParts do: // [:i |
            result |= Math.min(word2 & mask, word1 & mask); // result := result bitOr: ((word2 bitAnd: mask) min: (word1 bitAnd: mask)).
            mask = mask << nBits; // mask := mask << nBits  "slide left to next partition"].
        }
        return result; // ^ result
    }
}
