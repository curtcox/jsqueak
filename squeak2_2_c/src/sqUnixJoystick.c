/* This file is a heavily modified version of the file "sqMacJoystick.c".
 *
 * Modifications by: Ian Piumarta (ian.piumarta@inria.fr)
 *
 * The original version of this file can be regenerated from the Squeak
 * image by executing:
 *
 * 	InterpreterSupportCode writeMacSourceFiles
 *
 * $Log: sqUnixJoystick.c,v $
 * Revision 1.1  1996/10/24  13:21:38  piumarta
 * Initial revision
 *
 */

static char rcsid[]=
  "$Id: sqUnixJoystick.c,v 1.1 1996/10/24 13:21:38 piumarta Exp piumarta $";

#include "sq.h"

/* we don't have any joysticks */

void *joySticks= 0;

int joystickRead(int index)	{ return 0; }
int joystickInit(void)		{ return 0; }
