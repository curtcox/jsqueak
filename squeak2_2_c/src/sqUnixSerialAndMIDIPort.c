/* Placeholders for Unix serial/MIDI port stuff.  See termio(4) [termios(3)
   on Linux] for clues about what will eventually be required. */

#include <termios.h>

#include "sq.h"

/*** Imported Variables ***/
extern int successFlag;

/*** Public Functions ***/

int serialPortClose(int portNum) {
  success(false);
  return 0;
}

int serialPortOpen(
  int portNum, int baudRate, int stopBitsType, int parityType, int dataBits,
  int inFlowCtrl, int outFlowCtrl, int xOnChar, int xOffChar) {
/* Open the given serial port using the given settings. The baud rate can be
   any number between about 224 and 57600; the driver will pick a clock
   divisor that will generate the closest available baud rate. */
  success(false);
  return 0;
}

int serialPortMidiClockRate(int portNum, int interfaceClockRate) {
/* Put the given port into MIDI mode, which uses a clock supplied
   by an external MIDI interface adaptor to determine the baud rate.
   Possible external clock rates: 31.25 KHz, 0.5 MHz, 1 MHz, or 2 MHz. */
  success(false);
  return 0;
}

int serialPortReadInto(int portNum, int count, int startPtr) {
/* Read up to count bytes from the given serial port into the given byte array.
   Read only up to the number of bytes in the port's input buffer; if fewer bytes
   than count have been received, do not wait for additional data to arrive.
   Return zero if no data is available. */
  success(false);
  return 0;
}

int serialPortWriteFrom(int portNum, int count, int startPtr) {
/* Write count bytes from the given byte array to the given serial port's
   output buffer. Return the number of bytes written. This implementation is
   synchronous: it doesn't return until the data has been sent. However, other
   implementations may return before transmission is complete. */
  success(false);
  return 0;
}





int sqMIDIClosePort(int portNum) {
/* Close the given MIDI port. Do nothing if the port is not open.
   Fail if there is no port of the given number.*/
  success(false);
  return 0;
}

int sqMIDIGetClock(void) {
/* Return the current value of the clock used to schedule MIDI events.
   The MIDI clock is assumed to wrap at or before half the maximum
   positive SmallInteger value. This allows events to be scheduled
   into the future without overflowing into LargePositiveIntegers. 
   This implementation does not support event scheduling, so it
   just returns the value of the Squeak millisecond clock. */
  success(false);
  return 0;
}

int sqMIDIGetPortCount(void) {
/* Return the number of available MIDI interfaces, including both
   hardware ports and software entities that act like ports. Ports
   are numbered from 0 to N-1, where N is the number returned by this
   primitive. */
  success(false);
  return 0;
}

int sqMIDIGetPortDirectionality(int portNum) {
/* Return an integer indicating the directionality of the given
   port where: 1 = input, 2 = output, 3 = bidirectional. Fail if
   there is no port of the given number. */
  success(false);
  return 0;
}

int sqMIDIGetPortName(int portNum, int namePtr, int length) {
/* Copy the name of the given MIDI port into the string at the given
   address. Copy at most length characters, and return the number of
   characters copied. Fail if there is no port of the given number.*/
  success(false);
  return 0;
}

int sqMIDIOpenPort(int portNum, int readSemaIndex, int interfaceClockRate) {
/* Open the given port, if possible. If non-zero, readSemaphoreIndex
   specifies the index in the external objects array of a semaphore
   to be signalled when incoming MIDI data is available. Note that
   not all implementations support read semaphores (this one does
   not); see sqMIDICanUseSemaphore. The interfaceClockRate parameter
   specifies the clock speed for an external MIDI interface
   adaptor on platforms that use such adaptors (e.g., Macintosh).
   Fail if there is no port of the given number.*/
  success(false);
  return 0;
}

int sqMIDIParameter(int whichParameter, int modify, int newValue) {
/* Read or write the given MIDI driver parameter. If modify is 0,
   then newValue is ignored and the current value of the specified
   parameter is returned. If modify is non-zero, then the specified
   parameter is set to newValue. Note that many MIDI driver parameters
   are read-only; attempting to set one of these parameters fails.
   For boolean parameters, true = 1, false = 0. */
  success(false);
  return 0;
}

int sqMIDIPortReadInto(int portNum, int count, int bufferPtr) {
/* bufferPtr is the address of the first byte of a Smalltalk
   ByteArray of the given length. Copy up to (length - 4) bytes
   of incoming MIDI data into that buffer, preceded by a 4-byte
   timestamp in the units of the MIDI clock, most significant byte
   first. Implementations that do not support timestamping of
   incoming data as it arrives (see sqMIDIHasInputClock) simply
   set the timestamp to the value of the MIDI clock when this
   function is called. Return the total number of bytes read,
   including the timestamp bytes. Return zero if no data is
   available. Fail if the buffer is shorter than five bytes,
   since there must be enough room for the timestamp plus at
   least one data byte. */
  success(false);
  return 0;
}

int sqMIDIPortWriteFromAt(int portNum, int count, int bufferPtr, int time) {
/* bufferPtr is the address of the first byte of a Smalltalk
   ByteArray of the given length. Send its contents to the given
   port when the MIDI clock reaches the given time. If time equals
   zero, then send the data immediately. Implementations that do
   not support a timestamped output queue, such as this one, always
   send the data immediately; see sqMIDIHasBuffer. */
  success(false);
  return 0;
}
