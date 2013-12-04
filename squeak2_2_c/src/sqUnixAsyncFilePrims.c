/*
  Experimental support for asynchronous file reading and writing.

  When a read or write operation is initiated, control is returned to Squeak
  immediately.  A semaphore is signaled when the operation completes, at which
  time the client can find out how many bytes were actually read or written
  and copy the results of the read operation from the file buffer into a Squeak
  buffer.  Only one operation may be in progress on a given file at a given time,
  but operations on different files may be done in parallel.

  The semaphore is signalled once for each transfer operation that is successfully
  started, even if that operation later fails.  Write operations always write
  their entire buffer if they succeed, but read operations may transfer less than
  their buffer size if they are started less than a buffer's size from the end
  of the file.
  
  The state of a file is kept in the following structure, which is stored directly
  in a Squeak ByteArray object:

    typedef struct {
	  int				sessionID;
	  AsyncFileState	*state;
    } AsyncFile;

  The session ID is used to detect stale files--files that were open
  when the image was saved.  The state pointer of such files is meaningless.
  Async file handles use the same session ID as ordinary file handles.

  Note: These primitives are experimental!  They need not be implemented on
  every platform, and they may be withdrawn or replaced in a future release.
*/

#include "sq.h"

#define FAIL(X) { return X; }

int asyncFileClose(AsyncFile *f)
     FAIL(0)

int asyncFileOpen(AsyncFile *f, int fileNamePtr, int fileNameSize,
		  int writeFlag, int semaIndex)
     FAIL(0)

int asyncFileRecordSize()
     FAIL(0)

int asyncFileReadResult(AsyncFile *f, int bufferPtr, int bufferSize)
     FAIL(0)

int asyncFileReadStart(AsyncFile *f, int fPosition, int count)
     FAIL(0)

int asyncFileWriteResult(AsyncFile *f)
     FAIL(0)

int asyncFileWriteStart(AsyncFile *f, int fPosition, int bufferPtr, int bufferSize)
     FAIL(0)
