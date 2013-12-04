/* This file is a total rewrite of the file "sqMacSound.c".
 *
 * Modifications by: Ian Piumarta (ian.piumarta@inria.fr)
 *
 * The original version of this file can be regenerated from the Squeak
 * image by executing:
 *
 * 	InterpreterSupportCode writeMacSourceFiles
 *
 * $Log: sqUnixSound.c,v $
 * Revision 1.2  1996/11/15  17:34:38  piumarta
 * Added initial code for Sun audio support.
 *
 * Revision 1.1  1996/10/24  13:21:38  piumarta
 * Initial revision
 *
 */

static char rcsid[]=
  "$Id: sqUnixSound.c,v 1.2 1996/11/15 17:34:38 piumarta Exp piumarta $";

#include "sq.h"

#define FAIL(X) { return X; }

/* sound output */

int snd_AvailableSpace(void)
     FAIL(8192)
int snd_InsertSamplesFromLeadTime(int frameCount, int srcBufPtr, int samplesOfLeadTime)
     FAIL(frameCount)
int snd_PlaySamplesFromAtLength(int frameCount, int arrayIndex, int startIndex)
     FAIL(8192)
int snd_PlaySilence(void)
     FAIL(8192)
int snd_Start(int frameCount, int samplesPerSec, int stereo, int semaIndex)
     FAIL(1)
int snd_Stop(void)
     FAIL(0)

/* sound input */

int snd_SetRecordLevel(int level)
     FAIL(0)
int snd_StartRecording(int desiredSamplesPerSec, int stereo, int semaIndex)
     FAIL(0)
int snd_StopRecording(void)
     FAIL(0)
double snd_GetRecordingSampleRate(void)
     FAIL(0)
int snd_RecordSamplesIntoAtLength(int buf, int startSliceIndex, int bufferSizeInBytes)
     FAIL(0)
