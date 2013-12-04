/* sqXWindow.c -- support for the X Window System.
 *
 * Author: Ian Piumarta (ian.piumarta@inria.fr)
 *
 * Last edited: Wed Oct  7 13:48:46 1998 by piumarta (Ian Piumarta) on lebrac
 *
 * Code to support displays deeper than 8 bits contributed by: Kazuki YASUMATSU
 *	(kyasu@crl.fujixerox.co.jp, Kazuki.Yasumatsu@fujixerox.co.jp)
 *
 * Support for cursor and keypad editing keys based on code contributed by:
 *	Stefan Matthias Aust (sma@kiel.netsurf.de)
 *
 * BUGS: this file is too long; it should be split into two.
 *
 * $Log: sqXWindow.c,v $
 * Revision 1.5  1997/08/02 01:33:28  piumarta
 * Fixed colourmap initialisation to match new image.
 * (My desktop was YELLOW! ;-)
 *
 * Revision 1.4  1996/11/15  17:34:38  piumarta
 * Added support for 16-, 24-, and 32-bit displays.
 *
 * Revision 1.3  1996/11/05  22:54:07  piumarta
 * Added support for using the X selection as the Squeak clipboard.
 *
 * Revision 1.2  1996/11/04  15:01:55  piumarta
 * Added code to find an 8-bit PseudoColor visual, and use it.
 *
 * Revision 1.1  1996/10/24  13:25:40  piumarta
 * Initial revision
 */

static char *rcsid=
  "$Id: sqXWindow.c,v 1.5 1997/08/02 01:33:28 piumarta Exp piumarta $";

/* enable use of X Shared Memory extensions
   except on HP-UX which (as usual) can't cope */
#if !defined(hpux) && !defined (__hpux)
# define USE_XSHM
#endif

#include "sq.h"

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/param.h>
#include <unistd.h>
#include <errno.h>

#ifdef NEED_SELECT
# include <sys/select.h>
#endif

#ifndef HEADLESS
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <X11/Xatom.h>
# define XK_MISCELLANY
# include <X11/keysymdef.h>
# ifdef USE_XSHM
#   include <sys/ipc.h>
#   include <sys/shm.h>
#   include <X11/extensions/XShm.h>
# endif
#endif

/*** Variables -- Imported from Virtual Machine ***/
extern unsigned char *memory;
extern int interruptKeycode;
extern int interruptPending;
extern int interruptCheckCounter;
#ifdef CCACHE
extern int contextCacheEntries;
extern int stackCacheEntries;
#endif

/*** Variables -- image and path names ***/
#define IMAGE_NAME_SIZE MAXPATHLEN

char imageName[MAXPATHLEN+1];		/* full path to image */
char shortImageName[MAXPATHLEN+1];	/* just the base name */
char vmPath[MAXPATHLEN+1];		/* full path to interpreter's directory */

int initialHeapSize;			/* 5 megabytes by default */

int    initialArgc;
char **initialArgv;

#ifndef HEADLESS
/*** Variables -- X11 Related ***/

/* name of Squeak windows in Xrm and the WM */
#define xClassName	"Squeak"

char		*displayName= 0;	/* name of display, or 0 for $DISPLAY */
Display		*stDisplay= null;	/* Squeak display */
int		 stXfd= 0;		/* X connection file descriptor */
Window		 stWindow= null;	/* Squeak window */
Visual		*stVisual;		/* the default visual */
GC		 stGC;			/* graphics context used for rendering */
Colormap	 stColormap= null;	/* Squeak color map */
int		 stDisplayBitsIndex= 0;	/* last known oop of the VM's Display */
XImage		*stImage= 0;		/* ...and it's client-side pixmap */
char		*stPrimarySelection;	/* buffer holding selection */
char		*stEmptySelection= "";	/* immutable "empty string" value */
int		 stPrimarySelectionSize;/* size of buffer holding selection */
int		 stOwnsSelection= 0;	/* true if we own the X selection */
XColor		 stColorBlack;		/* black pixel value in stColormap */
XColor		 stColorWhite;		/* white pixel value in stColormap */
int		 savedWindowSize= 0;	/* initial size of window */
int		 savedWindowOrigin= -1;	/* initial origin of window */
XPoint		 mousePosition;		/* position at last PointerMotion event */
Time		 stButtonTime;		/* time of last ButtonRelease (for SetSeln) */
# ifdef USE_XSHM
XShmSegmentInfo  stShmInfo;		/* shared memory descriptor */
int		 completions= 0;	/* outstanding completion events */
int		 completionType;	/* the type of XShmCompletionEvent */
int		 useXshm= 0;		/* 1 if shared memory is in use */
int		 asyncUpdate= 0;	/* 1 for asynchronous screen updates */
# endif
int		 stDepth;
int		 stBitsPerPixel= 0;
unsigned int	 stColors[256];
unsigned int	 stDownGradingColors[256];
int		 stHasSameRGBMask16;
int		 stHasSameRGBMask32;
int		 stRNMask, stGNMask, stBNMask;
int		 stRShift, stGShift, stBShift;
char		*stDisplayBitmap= 0;
#endif

int		 sleepWhenUnmapped= 0;
int		 noTitle= 0;
int		 fullScreen= 0;
struct timeval	 startUpTime;

/* maximum input polling frequency */
#define	MAXPOLLSPERSEC	33

#ifndef HEADLESS
/* we are interested in these events */
#define	EVENTMASK	ButtonPressMask | ButtonReleaseMask | \
			KeyPressMask | PointerMotionMask | \
			ExposureMask | StructureNotifyMask

/* largest X selection that we will attempt to handle (bytes) */
#define MAX_SELECTION_SIZE	100*1024

/* longest we're prepared to wait for the selection owner to convert it (seconds) */
#define SELECTION_TIMEOUT	3


/*** Variables -- Event Recording ***/
#define KEYBUF_SIZE 64

int keyBuf[KEYBUF_SIZE];	/* circular buffer */
int keyBufGet= 0;		/* index of next item of keyBuf to read */
int keyBufPut= 0;		/* index of next item of keyBuf to write */
int keyBufOverflows= 0;		/* number of characters dropped */

int buttonState= 0;		/* mouse button and modifier state when mouse
				   button went down or 0 if not pressed */

/* This table maps the X modifier key bits to 4 Squeak modifier
   bits.  (The X caps lock key is mapped as shift, meta is
   mapped to command, and ctrl+meta is mapped to option.
	X bits:		<meta><control><shift-lock><shift>
	Squeak bits:	<command><option><control><shift>
*/
char modifierMap[16]= {
  0, 1, 1, 0, 2, 3, 3, 2, 8, 9, 9, 8, 4, 5, 5, 4
};

/* masks for the XButtonEvent modifier state */
#define MOD_SHIFT	1
#define MOD_CONTROL	4
#define MOD_META	8
#endif

/*** Functions ***/

#ifdef ioMSecs
# undef ioMSecs
#endif

int  HandleEvents(void);
void RecordFullPathForImageName(char *localImageName);
void SetUpTimers(void);
void usage(void);
void imageNotFound(char *imageName);
void ParseArguments(int argc, char **argv);
void segv(int ignored);
#ifndef HEADLESS
void SetColorEntry(int index, int red, int green, int blue);
void SetUpClipboard(void);
void SetUpPixmap(void);
void SetUpWindow(char *displayName);
void SetWindowSize(void);
void getMaskbit(unsigned long ul, int *nmask, int *shift);
void setupDownGradingColors(void);
void copyReverseImageBytes(int *fromImageData, int *toImageData,
			   int depth, int width, int height,
			   int affectedL, int affectedT, int affectedR, int affectedB);
void copyReverseImageWords(int *fromImageData, int *toImageData,
			   int depth, int width, int height,
			   int affectedL, int affectedT, int affectedR, int affectedB);
# define declareCopyFunction(NAME) \
  void NAME (int *fromImageData, int *toImageData, \
	     int width, int height, \
	     int affectedL, int affectedT, int affectedR, int affectedB)
declareCopyFunction(copyImage8To8);
declareCopyFunction(copyImage8To16);
declareCopyFunction(copyImage16To8);
declareCopyFunction(copyImage8To32);
declareCopyFunction(copyImage32To8);
declareCopyFunction(copyImage16To32);
declareCopyFunction(copyImage32To16);
declareCopyFunction(copyImage16To16);
declareCopyFunction(copyImage32To32);
# undef declareCopyFunction
void ux2st(char *string);
void st2ux(char *string);
void claimSelection(void);
void sendSelection(XSelectionRequestEvent *requestEv);
char *getSelection(void);
static void redrawDisplay(int l, int r, int t, int b);
static int translateCode(KeySym symbolic);
void recordKeystroke(XKeyEvent *theEvent);
void recordMouseDown(XButtonEvent *theEvent);
void recordModifierButtons(XButtonEvent *theEvent);
# ifdef USE_XSHM
int XShmGetEventBase(Display *);
# endif
int ioMSecs(void);
#endif !HEADLESS

int strtobkm(char *str);

extern void aioPollForIO(int, int);	/* see sqUnixNetwork.c */


/*** VM Home Directory Path ***/

int vmPathSize(void)
{
  return strlen(vmPath);
}

int vmPathGetLength(int sqVMPathIndex, int length)
{
  char *stVMPath= (char *)sqVMPathIndex;
  int count, i;

  count= strlen(vmPath);
  count= (length < count) ? length : count;

  /* copy the file name into the Squeak string */
  for (i= 0; i < count; i++)
    stVMPath[i]= vmPath[i];

  return count;
}

#ifndef HEADLESS
/*** line-end conventions (mainly for converting the X selection) ***/

void st2ux(char *string)
{
  if (!string) return;
  while (*string)
    {
      if (*string == '\r')
	*string= '\n';
      string++;
    }
}

void ux2st(char *string)
{
  if (!string) return;
  while (*string)
    {
      if (*string == '\n')
	*string= '\r';
      string++;
    }
}

/*** X-related Functions ***/

void claimSelection(void)
{
  XSetSelectionOwner(stDisplay, XA_PRIMARY, stWindow, CurrentTime);
  stOwnsSelection= (XGetSelectionOwner(stDisplay, XA_PRIMARY) == stWindow);
}

void sendSelection(XSelectionRequestEvent *requestEv)
{
  XSelectionEvent notifyEv;

  /* this should REFUSE the selection if the target type isn't XA_STRING */

  st2ux(stPrimarySelection);

  XChangeProperty(requestEv->display,
		  requestEv->requestor,
		  (requestEv->property == None
		     ? requestEv->target
		     : requestEv->property),
		  requestEv->target,
		  8, PropModeReplace, stPrimarySelection,
		  (stPrimarySelection ? strlen(stPrimarySelection) : 0));

  ux2st(stPrimarySelection);

  notifyEv.type= SelectionNotify;
  notifyEv.display= requestEv->display;
  notifyEv.requestor= requestEv->requestor;
  notifyEv.selection= requestEv->selection;
  notifyEv.target= requestEv->target;
  notifyEv.time= requestEv->time;
  notifyEv.property= (requestEv->property == None)
    ? requestEv->target
    : requestEv->property;

  XSendEvent(requestEv->display, requestEv->requestor,
	     False, 0, (XEvent *)&notifyEv);

  XFlush(stDisplay);
}

char *getSelection(void)
{
  XEvent  ev;
  fd_set  fdMask;
  char	 *data;

  /* request the selection */
  XConvertSelection(stDisplay, XA_PRIMARY, XA_STRING, XA_STRING, stWindow, CurrentTime);

  /* wait for selection notification, ignoring (most) other events. */
  FD_ZERO(&fdMask);
  FD_SET(stXfd, &fdMask);

  do {
    if (XPending(stDisplay) == 0)
      {
	int status;
	struct timeval timeout= {SELECTION_TIMEOUT, 0};

	while ((status= select(FD_SETSIZE, &fdMask, 0, 0, &timeout)) < 0
	       && errno == EINTR);
	if (status < 0)
	  {
	    perror("select(stDisplay)");
	    return stEmptySelection;
	  }
	if (status == 0)
	  {
	    XBell(stDisplay, 0);
	    return stEmptySelection;
	  }
      }
    XNextEvent(stDisplay, &ev);
    /* this is necessary so that we can supply our own selection when we
       are the requestor -- this could (should) be optimised to return the
       stored selection value instead! */
    if (ev.type == SelectionRequest) sendSelection(&ev.xselectionrequest);
# ifdef USE_XSHM
    if (ev.type == completionType) --completions;
# endif
  } while (ev.type != SelectionNotify);

  /* check if the selection was refused */
  if (ev.xselection.property == None)
    {
      XBell(stDisplay, 0);
      return stEmptySelection;
    }

  /* get the value of the selection from the containing property */
  {
    Atom type;
    int format;
    unsigned long nitems, bytesAfter;

    XGetWindowProperty(stDisplay, ev.xselection.requestor, ev.xselection.property,
		       (long)0, (long)(MAX_SELECTION_SIZE/4),
		       False, AnyPropertyType,
		       &type, &format, &nitems, &bytesAfter,
		       (unsigned char **)&data);
    if (bytesAfter > 0)
      XBell(stDisplay, 0);
  }

  /* return the selection -- which must be XFreed() when no longer needed! */

  return data;
}


/* a modified copy of fullDisplayUpdate() that redraws
   only the damaged parts of the window according to each
   expose event on the queue.
   Note: if the format of Form or Bitmap changes, or if
   the special object index of Display is changed, this
   version of the code WILL FAIL!  Otherwise it is to be
   preferred.
*/
static void redrawDisplay(int l, int r, int t, int b)
{
  extern int specialObjectsOop;
  extern int lengthOf(int);
# define longAt(i) (*((int *) (i)))
  int displayObj= longAt((specialObjectsOop + 4) + (14 * 4));
  if ((((((unsigned)(longAt(displayObj))) >> 8) & 15) <= 4) &&
      ((lengthOf(displayObj)) >= 4))
    {
      int dispBits= longAt((displayObj + 4) + (0 * 4));
      int w= fetchIntegerofObject(1, displayObj);
      int h= fetchIntegerofObject(2, displayObj);
      int d= fetchIntegerofObject(3, displayObj);
      int dispBitsIndex= dispBits + 4;
      ioShowDisplay(dispBitsIndex, w, h, d, l, r, t, b);
    }
# undef longAt
}

#endif !HEADLESS


int HandleEvents(void)
{
#ifdef HEADLESS
  /* quick check for asynchronous socket i/o */
  aioPollForIO(0, 0);
  return 0;
#else !HEADLESS
  XEvent theEvent;
  int ok;

  /* quick check for asynchronous socket i/o */
  aioPollForIO(0, stXfd);

  ok= (XPending(stDisplay) > 0);
  if (ok)
    {
      XNextEvent(stDisplay, &theEvent);
      
      switch (theEvent.type)
	{
	case MotionNotify:
	  mousePosition.x= ((XMotionEvent *)&theEvent)->x;
	  mousePosition.y= ((XMotionEvent *)&theEvent)->y;
	  break;

	case ButtonPress:
	  recordMouseDown((XButtonEvent *)&theEvent);
	  return false;
	  break;

	case ButtonRelease:
	  recordModifierButtons((XButtonEvent *)&theEvent);
	  /* button up on "paste" causes a selection retrieval:
	     record the event time in case we need it later */
	  stButtonTime= ((XButtonEvent *)&theEvent)->time;
	  return false;
	  break;

	case KeyPress:
	  recordModifierButtons((XButtonEvent *)&theEvent);
	  recordKeystroke((XKeyEvent *)&theEvent);
	  /* a key bound to the paste operation causes a selection
	     retrieval: record the event time in case we need it later */
	  break;

	case SelectionClear:
	  stOwnsSelection= 0;
	  break;

	case SelectionRequest:
	  sendSelection(&theEvent.xselectionrequest);
	  break;

	case Expose:
	  {
	    XExposeEvent *ex= (XExposeEvent *)&theEvent;
# if defined(USE_XSHM)
	    if (asyncUpdate) {
	      /* wait for pending updates */
	      while (completions) HandleEvents();
	    }
# endif
# ifdef FULL_UPDATE_ON_EXPOSE
	    /* ignore it if there are other exposures upstream */
	    if (ex->count == 0)
	      fullDisplayUpdate();  /* this makes VM call ioShowDisplay */
# else
	    redrawDisplay(ex->x, ex->x + ex->width, ex->y, ex->y + ex->height);
# endif !FULL_UPDATE_ON_EXPOSE
	  }
	  break;

	case UnmapNotify:
	  {
	    if (sleepWhenUnmapped)
	      do {
		XNextEvent(stDisplay, &theEvent);
		switch (theEvent.type) {
		case SelectionClear:
		  stOwnsSelection= 0;
		  break;
		case SelectionRequest:
		  sendSelection(&theEvent.xselectionrequest);
		  break;
		}
	      } while (theEvent.type != MapNotify);
	  }
	  break;

	  /* with the right hook in the VM we could also treat
	     StructureNotify here to automatically restore the
	     Display when the window size changes */

# ifdef USE_XSHM
	default:
	  if (theEvent.type == completionType) --completions;
	  break;
# endif
	}
    }

  return ok;
#endif !HEADLESS
}

#ifndef HEADLESS
void getMaskbit(unsigned long ul, int *nmask, int *shift)
{
  int i;
  unsigned long hb;

  *nmask= *shift= 0;
  hb= 0x8000;  hb= (hb<<16);  /* hb = 0x80000000UL */
  for (i= 31; ((ul & hb) == 0) && i >= 0; --i, ul<<= 1)
    ;
  for (; ((ul & hb) != 0) && i >= 0; --i, ul<<= 1)
    (*nmask)++;
  *shift= i+1;
}

void setupDownGradingColors(void)
{
  int r, g, b, i;

  for (r= 0; r < 0x8; r++)
    {
      for (g= 0; g < 0x8; g++)
	{
	  for (b= 0; b < 0x4; b++)
	    {
	      int mindiff= 0x7*0x7 + 0x7*0x7 + 0x3*0x3 + 1;
	      for (i= 0; i < 256; i++)
		{
		  int rdiff, gdiff, bdiff, diff;

		  rdiff= r - ((stColors[i]>>5) & 0x7);
		  gdiff= g - ((stColors[i]>>2) & 0x7);
		  bdiff= b -  (stColors[i] & 0x3);
		  diff= rdiff*rdiff + gdiff*gdiff + bdiff*bdiff;
		  if (diff < mindiff)
		    {
		      mindiff= diff;
		      stDownGradingColors[(r << 5) + (g << 2) + b] = i;
		    }
		}
	    }
	}
    }
}

void SetColorEntry(int index, int red, int green, int blue)
{
  if (index >= 256)
    return;

  if (stVisual->class == TrueColor || stVisual->class == DirectColor)
    {
      unsigned int r, g, b;
      r= red;
      g= green;
      b= blue;

      stColors[index]= (((r>>(16-stRNMask))<<stRShift) |
			((g>>(16-stGNMask))<<stGShift) |
			((b>>(16-stBNMask))<<stBShift));
    }
  else
    {
      XColor color;
      color.pixel= index;
      color.red= red;
      color.green= green;
      color.blue= blue;
      color.flags= DoRed|DoGreen|DoBlue;
      XStoreColor(stDisplay, stColormap, &color);
      /* map rgb weight=332 */
      stColors[index] = ((((unsigned int)red  >>(16-3))<<5) |
			 (((unsigned int)green>>(16-3))<<2) |
			 ((unsigned int)blue >>(16-2)));
    }
}

void SetUpPixmap(void)
{
  int count;
  XPixmapFormatValues *xpv;

  stVisual= DefaultVisual(stDisplay, DefaultScreen(stDisplay));
  stDepth= DefaultDepth(stDisplay, DefaultScreen(stDisplay));
  xpv= XListPixmapFormats(stDisplay, &count);

  if (xpv)
    {
      while(--count >= 0)
	{
	  if (stDepth == xpv[count].depth)
	    stBitsPerPixel= xpv[count].bits_per_pixel;
	}
      XFree((void*)xpv);
    }
  if (stBitsPerPixel == 0)
    stBitsPerPixel= stDepth;

  switch (stVisual->class)
    {
    case PseudoColor:
      if (stBitsPerPixel == 8)
	break;
      else
	{
	  fprintf(stderr, "This visual class is not supported\n");
	  exit(1);
	  return;
	}
    case TrueColor:
    case DirectColor:
      getMaskbit(stVisual->red_mask,   &stRNMask, &stRShift);
      getMaskbit(stVisual->green_mask, &stGNMask, &stGShift);
      getMaskbit(stVisual->blue_mask,  &stBNMask, &stBShift);
      if (stBitsPerPixel == 16)
	{
	  stHasSameRGBMask16= (stVisual->red_mask   == (0x1f << 10) &&
			       stVisual->green_mask == (0x1f << 5) &&
			       stVisual->blue_mask  == (0x1f));
	  break;
	}
      else if (stBitsPerPixel == 32)
	{
	  stHasSameRGBMask32= (stVisual->red_mask   == (0xff << 16) &&
			       stVisual->green_mask == (0xff << 8) &&
			       stVisual->blue_mask  == (0xff));
	  break;
	}
      else
	{
	  fprintf(stderr, "This visual class is not supported\n");
	  exit(1);
	  return;
	}
    case GrayScale:
    case StaticColor:
    case StaticGray:
    default:
      fprintf(stderr, "This visual class is not supported\n");
      exit(1);
      return;
    }

  if (stVisual->class == PseudoColor)
    stColormap= XCreateColormap(stDisplay,
				stWindow,
				DefaultVisual(stDisplay, DefaultScreen(stDisplay)),
				AllocAll);



  /* 1-bit colors (monochrome) */
  SetColorEntry(0, 65535, 65535, 65535);	/* white or transparent */
  SetColorEntry(1,     0,     0,     0);	/* black */

	/* additional colors for 2-bit color */
  SetColorEntry(2, 65535, 65535, 65535);	/* opaque white */
  SetColorEntry(3, 32768, 32768, 32768);	/* 1/2 gray */

	/* additional colors for 4-bit color */
  SetColorEntry( 4, 65535,     0,     0);	/* red */
  SetColorEntry( 5,     0, 65535,     0);	/* green */
  SetColorEntry( 6,     0,     0, 65535);	/* blue */
  SetColorEntry( 7,     0, 65535, 65535);	/* cyan */
  SetColorEntry( 8, 65535, 65535,     0);	/* yellow */
  SetColorEntry( 9, 65535,     0, 65535);	/* magenta */
  SetColorEntry(10,  8192,  8192,  8192);	/* 1/8 gray */
  SetColorEntry(11, 16384, 16384, 16384);	/* 2/8 gray */
  SetColorEntry(12, 24576, 24576, 24576);	/* 3/8 gray */
  SetColorEntry(13, 40959, 40959, 40959);	/* 5/8 gray */
  SetColorEntry(14, 49151, 49151, 49151);	/* 6/8 gray */
  SetColorEntry(15, 57343, 57343, 57343);	/* 7/8 gray */

	/* additional colors for 8-bit color */
	/* 24 more shades of gray (does not repeat 1/8th increments) */
  SetColorEntry(16,  2048,  2048,  2048);	/*  1/32 gray */
  SetColorEntry(17,  4096,  4096,  4096);	/*  2/32 gray */
  SetColorEntry(18,  6144,  6144,  6144);	/*  3/32 gray */
  SetColorEntry(19, 10240, 10240, 10240);	/*  5/32 gray */
  SetColorEntry(20, 12288, 12288, 12288);	/*  6/32 gray */
  SetColorEntry(21, 14336, 14336, 14336);	/*  7/32 gray */
  SetColorEntry(22, 18432, 18432, 18432);	/*  9/32 gray */
  SetColorEntry(23, 20480, 20480, 20480);	/* 10/32 gray */
  SetColorEntry(24, 22528, 22528, 22528);	/* 11/32 gray */
  SetColorEntry(25, 26624, 26624, 26624);	/* 13/32 gray */
  SetColorEntry(26, 28672, 28672, 28672);	/* 14/32 gray */
  SetColorEntry(27, 30720, 30720, 30720);	/* 15/32 gray */
  SetColorEntry(28, 34815, 34815, 34815);	/* 17/32 gray */
  SetColorEntry(29, 36863, 36863, 36863);	/* 18/32 gray */
  SetColorEntry(30, 38911, 38911, 38911);	/* 19/32 gray */
  SetColorEntry(31, 43007, 43007, 43007);	/* 21/32 gray */
  SetColorEntry(32, 45055, 45055, 45055);	/* 22/32 gray */
  SetColorEntry(33, 47103, 47103, 47103);	/* 23/32 gray */
  SetColorEntry(34, 51199, 51199, 51199);	/* 25/32 gray */
  SetColorEntry(35, 53247, 53247, 53247);	/* 26/32 gray */
  SetColorEntry(36, 55295, 55295, 55295);	/* 27/32 gray */
  SetColorEntry(37, 59391, 59391, 59391);	/* 29/32 gray */
  SetColorEntry(38, 61439, 61439, 61439);	/* 30/32 gray */
  SetColorEntry(39, 63487, 63487, 63487);	/* 31/32 gray */

  /* The remainder of color table defines a color cube with six steps
     for each primary color. Note that the corners of this cube repeat
     previous colors, but simplifies the mapping between RGB colors and
     color map indices. This color cube spans indices 40 through 255.
     */
  {
    int r, g, b;

    for (r= 0; r < 6; r++)
      for (g= 0; g < 6; g++)
	for (b= 0; b < 6; b++)
	  {
	    int i= 40 + ((36 * r) + (6 * b) + g);
	    if (i > 255) error("index out of range in color table compuation");
	    SetColorEntry(i, (r * 65535) / 5, (g * 65535) / 5, (b * 65535) / 5);
	  }
  }

  if (stVisual->class == PseudoColor)
    {
      XSetWindowColormap(stDisplay, stWindow, stColormap);

      /* initialise the black and white color values for cursor creation */
      stColorWhite.red= stColorWhite.green= stColorWhite.blue= 65535;
      if (XAllocColor(stDisplay, stColormap, &stColorWhite))
	fprintf(stderr, "failed to find white pixel in Squeak colormap\n");

      stColorBlack.red= stColorBlack.green= stColorBlack.blue= 0;
      if (XAllocColor(stDisplay, stColormap, &stColorBlack))
	fprintf(stderr, "failed to find black pixel in Squeak colormap\n");

      setupDownGradingColors();
    }
}


void SetUpWindow(char *displayName)
{
  XRectangle windowBounds= { 0, 0, 640, 480 };  /* default window bounds */

  int right, bottom;

  stDisplay= XOpenDisplay(displayName);
  if (!stDisplay)
    {
      fprintf(stderr, "Could not open display '%s'.\n", displayName);
      exit(1);
    }

  stXfd= ConnectionNumber(stDisplay);

  if (savedWindowSize != 0)
    {
      right=  windowBounds.x + ((unsigned) savedWindowSize >> 16);
      bottom= windowBounds.y + (savedWindowSize & 0xFFFF);
    }
  else
    {
      right= windowBounds.x + windowBounds.width;
      bottom= windowBounds.y + windowBounds.height;
    }

  /* minimum size is 64 x 64 */
  right= ( right > (windowBounds.x + 64)) ?  right : (windowBounds.x + 64);
  bottom= (bottom > (windowBounds.y + 64)) ? bottom : (windowBounds.y + 64);

  /* maximum bottom-right is screen bottom-right */
  right=  ( right <= DisplayWidth(stDisplay, DefaultScreen(stDisplay)))
    ?  right : (DisplayWidth(stDisplay, DefaultScreen(stDisplay))  - 8);
  bottom= (bottom <= DisplayHeight(stDisplay, DefaultScreen(stDisplay)))
    ? bottom : (DisplayHeight(stDisplay, DefaultScreen(stDisplay)) - 8);

  windowBounds.width= right - windowBounds.x;
  windowBounds.height= bottom - windowBounds.y;

  stWindow= XCreateSimpleWindow(stDisplay,
				DefaultRootWindow(stDisplay),
				windowBounds.x, windowBounds.y,
				windowBounds.width, windowBounds.height,
				1,
				BlackPixel(stDisplay, DefaultScreen(stDisplay)),
				BlackPixel(stDisplay, DefaultScreen(stDisplay)));

  /* accept the interesting events */
  {
    XSetWindowAttributes attributes;

    attributes.event_mask= EVENTMASK;
    attributes.backing_store= Always;
    XChangeWindowAttributes(stDisplay, stWindow,
			    CWEventMask | CWBackingStore,
			    &attributes);
  }

  /* set the window title and resource/class names */
  {
    XClassHint *classHints= XAllocClassHint();
    classHints->res_name= classHints->res_class= xClassName;
    XSetClassHint(stDisplay, stWindow, classHints);
    XStoreName(stDisplay, stWindow, shortImageName);
    XFree(classHints);
  }

  /* tell the WM that we can't be bothered managing focus for ourselves */
  {
    XWMHints *wmHints= XAllocWMHints();
    wmHints->input= True;
    wmHints->initial_state= NormalState;
    wmHints->flags= InputHint|StateHint;
    XSetWMHints(stDisplay, stWindow, wmHints);
    XFree((void *)wmHints);
  }

  /* create a suitable graphics context */
  {
    XGCValues gcValues;

    gcValues.function= GXcopy;
    gcValues.plane_mask= -1;
    gcValues.subwindow_mode= IncludeInferiors;
    gcValues.clip_x_origin= 0;
    gcValues.clip_y_origin= 0;
    gcValues.clip_mask= None;
    gcValues.foreground= BlackPixel(stDisplay, DefaultScreen(stDisplay));
    gcValues.background= WhitePixel(stDisplay, DefaultScreen(stDisplay));
    stGC= XCreateGC(stDisplay,
		    stWindow,
		    GCFunction | GCPlaneMask | GCSubwindowMode |
		    GCClipXOrigin | GCClipYOrigin | GCClipMask |
		    GCForeground | GCBackground,
		    &gcValues);
  }

  if (noTitle || fullScreen)
    /* naughty, but effective */
    XSetTransientForHint(stDisplay, stWindow, DefaultRootWindow(stDisplay));

# ifdef USE_XSHM
  completionType= XShmGetEventBase(stDisplay) + ShmCompletion;
# endif
}


void SetWindowSize(void)
{
  int width, height, maxWidth, maxHeight;

  if (savedWindowSize != 0)
    {
      width=  (unsigned)savedWindowSize >> 16;
      height= savedWindowSize & 0xFFFF;
    }
  else
    {
      width=  640;
      height= 480;
    }

  /* minimum size is 64 x 64 */
  width=  ( width > 64) ?   width : 64;
  height= (height > 64) ?  height : 64;

  /* maximum size is screen size */
  maxWidth=  (DisplayWidth(stDisplay, DefaultScreen(stDisplay)));
  maxHeight= (DisplayHeight(stDisplay, DefaultScreen(stDisplay)));
  width=  ( width <= maxWidth)  ?  width : maxWidth;
  height= (height <= maxHeight) ? height : maxHeight;

  if (fullScreen) {
    width= maxWidth;
    height= maxHeight;
  }

  XResizeWindow(stDisplay, stWindow, width, height);
}


/*** Event Recording Functions ***/


static int translateCode(KeySym symbolic)
{
# define ALT (8<<8)
  switch (symbolic)
    {
    case XK_Left:	return 28;
    case XK_Up:		return 30;
    case XK_Right:	return 29;
    case XK_Down:	return 31;
    case XK_Insert:	return  5;
    case XK_Prior:	return 11;	/* page up */
    case XK_Next:	return 12;	/* page down */
    case XK_Home:	return  1;
    case XK_End:	return  4;

    /* "aliases" for Sun keyboards */
    case XK_R9:		return 11;	/* page up */
    case XK_R15:	return 12;	/* page down */
    case XK_R7:		return  1;	/* home */
    case XK_R13:	return  4;	/* end */
    case XK_L1:		return ALT+'.';	/* stop */
    case XK_L2:		return ALT+'j';	/* again */
    case XK_L4:		return ALT+'z';	/* undo */
    case XK_L6:		return ALT+'c';	/* copy */
    case XK_L8:		return ALT+'v';	/* paste */
    case XK_L9:		return ALT+'f';	/* find */
    case XK_L10:	return ALT+'x';	/* cut */

    default:		return -1;
    }
  /*NOTREACHED*/
# undef ALT
}


void recordKeystroke(XKeyEvent *theEvent)
{
  int keystate;
  unsigned char buf[32];
  int nConv;
  KeySym symbolic;

  nConv= XLookupString(theEvent, buf, sizeof(buf), &symbolic, 0);

  keystate= buf[0];

  if (nConv == 0 && (keystate= translateCode(symbolic)) < 0)
    return;	/* unknown key */

  if (keystate == 127) keystate= 8;	/* DEL --> BS */

  keystate|= (modifierMap[(theEvent->state) & 0xF] << 8);

  if (keystate == interruptKeycode)
    {
      /* Note: interrupt key is "meta"; it not reported as a keystroke */
      interruptPending= true;
      interruptCheckCounter= 0;
    }
  else
    {
      /* bug: this should be rewritten to cope with nConv > 1 */
      keyBuf[keyBufPut]= keystate;
      keyBufPut= (keyBufPut + 1) % KEYBUF_SIZE;
      if (keyBufGet == keyBufPut)
	{
	  /* buffer overflow; drop the last character */
	  keyBufGet= (keyBufGet + 1) % KEYBUF_SIZE;
	  keyBufOverflows++;
	}
    }
}

void recordMouseDown(XButtonEvent *theEvent)
{
  int stButtons= 0;

  switch (theEvent->button)
    {
    case 1: stButtons= 4; break;
    case 2: stButtons= 2; break;
    case 3: stButtons= 1; break;
    default: ioBeep(); break;
    }

  if (stButtons == 4)	/* red button honours the modifiers */
    {
      if (theEvent->state & MOD_CONTROL)
	stButtons= 2;	/* yellow button if CTRL down */
      else if (theEvent->state & MOD_META)
	stButtons= 1;	/* blue button if META down */
    }
  /* button state: low three bits are mouse buttons; next 4 bits are modifier bits */
  buttonState= (modifierMap[(theEvent->state) & 0xF] << 3) | (stButtons & 0x7);
}

/* both button and key events have the state member in the same place */
void recordModifierButtons(XButtonEvent *theEvent)
{
  int stButtons= 0;

  if (theEvent->type == ButtonPress)
    stButtons= buttonState & 0x7;
  else
    stButtons= 0;
  /* button state: low three bits are mouse buttons; next 4 bits are modifier bits */
  buttonState= (modifierMap[(theEvent->state) & 0xF] << 3) | (stButtons & 0x7);
}

#endif !HEADLESS


/*** I/O Primitives ***/


int ioFormPrint(int bitsAddr, int width, int height, int depth,
		double hScale, double vScale, int landscapeFlag)
{
#ifdef HEADLESS

  fprintf(stderr,
	  "Sorry, a headless VM cannot print Forms.  If you\n"
	  "*really* need this then let me know, since there\n"
	  "is a (rather painful to implement) solution.\n");
  return false;

#else !HEADLESS

  /* Write the form as a PPM (Portable PixMap) file, from which it can
     be converted into almost any existing graphical format (including
     PostScript).  See the "netpbm" utilities for a huge collection of
     image manipulation tools that understand the PPM format.
     Note that "xv" can also read, convert, and do image processing on
     PPM files.
     The output filename is defined in "sqPlatformSpecific.h". */

  FILE *ppm;
  int ok= true;

  if ((ppm= fopen(SQ_FORM_FILENAME, "wb")) == 0) return false;
  /* PPM magic number and pixmap header */
  fprintf(ppm, "P3\n%d %d 65535\n", width, height);

  switch (depth) {
  case 8: {
    unsigned char *bits= (unsigned char *) bitsAddr;
    int ppw= 32 / depth;
    int raster= ((width + ppw - 1) / ppw) * 4;
    /* stColors[] is too approximate: query the real colormap */
    XColor colors[256];
    int i;
    for (i= 0; i < 256; ++i) colors[i].pixel= i;
    /* all colors in one query reduces server traffic */
    XQueryColors(stDisplay, stColormap, colors, 256);
    /* write the pixmap */
    {
      int y;
      for (y= 0; y < height; ++y) {
	int x;
	for (x= 0; x < width; ++x) {
	  /* everything is backwards (as usual ;) */
	  int index= y * raster + x;
	  int byte= 3 - (index & 0x00000003);
	  int word= index & -4;
	  int pixel= bits[word + byte];
	  fprintf(ppm, "%d %d %d\n",
		  colors[pixel].red, colors[pixel].green, colors[pixel].blue);
	}
      }
    }
    break;
  } /* case 8 */
  default:
    fprintf(stderr,
	    "Depth %d pixmaps are not yet supported.  If you *really*\n"
	    "need this then bribe me with something (a 24-bit Macintosh\n"
	    "PCI video card would certainly do the trick ;).\n");
    ok= false;
    break;
  } /* switch */

  fclose(ppm);
  return ok;

#endif !HEADLESS
}


int ioBeep(void)
{
#ifndef HEADLESS
  XBell(stDisplay, 0);	/* ring at default volume */
#endif
  return 0;
}


int ioGetButtonState(void)
{
  ioProcessEvents();  /* process all pending events */
#ifndef HEADLESS
  return buttonState;
#else
  return 0;
#endif
}

int ioGetKeystroke(void)
{
  int keystate;

  ioProcessEvents();  /* process all pending events */
#ifdef HEADLESS
  return -1;  /* keystroke buffer is empty */
#else
  if (keyBufGet == keyBufPut)
    return -1;  /* keystroke buffer is empty */

  keystate= keyBuf[keyBufGet];
  keyBufGet= (keyBufGet + 1) % KEYBUF_SIZE;
  /* set modifer bits in buttonState to reflect the last keystroke fetched */
  buttonState= ((keystate >> 5) & 0xF8) | (buttonState & 0x7);

  return keystate;
#endif
}

int ioMSecs(void)
{
  struct timeval now;
  gettimeofday(&now, 0);
  if ((now.tv_usec -= startUpTime.tv_usec) < 0) {
    now.tv_usec += 1000000;
    now.tv_sec -= 1;
  }
  now.tv_sec -= startUpTime.tv_sec;
  return (now.tv_usec / 1000 + now.tv_sec * 1000) & 0x1fffffff;
}

int ioMicroMSecs()
{
  /* already have millisecond resolution */
  return ioMSecs();
}

int ioRelinquishProcessorForMicroseconds(int microSeconds)
{
  /* sleep in select() for immediate response to socket i/o */
#ifdef HEADLESS
  aioPollForIO(microSeconds, 0);
#else
  aioPollForIO(microSeconds, stXfd);
#endif
  return microSeconds;
}

int ioMousePoint(void)
{
  ioProcessEvents();  /* process all pending events */
  /* x is high 16 bits; y is low 16 bits */
#ifndef HEADLESS
  return (mousePosition.x << 16) | (mousePosition.y);
#else
  return 0;
#endif
}

int ioPeekKeystroke(void)
{
#ifdef HEADLESS
  ioProcessEvents();  /* process all pending events */
  return -1;  /* keystroke buffer is empty */
#else
  int keystate;

  ioProcessEvents();  /* process all pending events */

  if (keyBufGet == keyBufPut)
    return -1;  /* keystroke buffer is empty */

  keystate= keyBuf[keyBufGet];
  /* set modifer bits in buttonState to reflect the last keystroke peeked at */
  buttonState= ((keystate >> 5) & 0xF8) | (buttonState & 0x7);
  return keystate;
#endif
}

/* this should be rewritten to use SIGIO and/or the interval timers */
int ioProcessEvents(void)
{
  static unsigned long nextPollTick= 0;

  if ((unsigned long)ioMSecs() > nextPollTick)
    {
      /* time to process events! */
      while (HandleEvents())
	{
	  /* process all pending events */
	}
    /* wait a while before trying again */
      nextPollTick= ioMSecs() + (1000 / MAXPOLLSPERSEC);
    }
  return 0;
}

/* returns the size of the Squeak window */
int ioScreenSize(void)
{
#ifdef HEADLESS
  int w= 64, h= 64;
#else
  int w= 10, h= 10;

  if (stWindow != null)
    {
      Window root;
      int x, y, b, d;
      XGetGeometry(stDisplay, stWindow, &root, &x, &y, &w, &h, &b, &d);
    }

  /* width must be a multiple of sizeof(void *), or X[Shm]PutImage goes gaga */
  if (w % sizeof(void *))
    {
      w= (w / sizeof(void *)) * sizeof(void *);
      XResizeWindow(stDisplay, stWindow, w, h);
    }
#endif
  return (w << 16) | (h & 0xFFFF);  /* w is high 16 bits; h is low 16 bits */
}

/* returns the local wall clock time */
int ioSeconds(void)
{
  extern int convertToSqueakTime(int unixTime);
  struct timeval tv;

  gettimeofday(&tv, 0);
#ifdef HAS_TIMEZONE
  return convertToSqueakTime(tv.tv_sec - timezone);
#else
  return convertToSqueakTime(tv.tv_sec + localtime(&tv.tv_sec)->tm_gmtoff);
#endif
}

#ifndef HEADLESS
static unsigned char swapBits(unsigned char in)
{
  unsigned char out= 0;
  int i;
  for (i= 0; i < 8; i++)
    {
      out= (out << 1) + (in & 1);
      in >>= 1;
    }
  return out;
}
#endif


int ioSetCursorWithMask(int cursorBitsIndex, int cursorMaskIndex,
			int offsetX, int offsetY)
{
#ifndef HEADLESS
  unsigned char data[32], mask[32];	/* cursors are always 16x16 */
  int i;
  Cursor cursor;
  Pixmap dataPixmap, maskPixmap;

  if (cursorMaskIndex == null) {
    for (i= 0; i < 16; i++)
      {
	data[i*2+0]= ((unsigned)checkedLongAt(cursorBitsIndex + (4 * i)) >> 24) & 0xFF;
	data[i*2+1]= ((unsigned)checkedLongAt(cursorBitsIndex + (4 * i)) >> 16) & 0xFF;
	mask[i*2+0]= ((unsigned)checkedLongAt(cursorBitsIndex + (4 * i)) >> 24) & 0xFF;
	mask[i*2+1]= ((unsigned)checkedLongAt(cursorBitsIndex + (4 * i)) >> 16) & 0xFF;
      }
  } else {
    for (i= 0; i < 16; i++)
      {
	data[i*2+0]= ((unsigned)checkedLongAt(cursorBitsIndex + (4 * i)) >> 24) & 0xFF;
	data[i*2+1]= ((unsigned)checkedLongAt(cursorBitsIndex + (4 * i)) >> 16) & 0xFF;
	mask[i*2+0]= ((unsigned)checkedLongAt(cursorMaskIndex + (4 * i)) >> 24) & 0xFF;
	mask[i*2+1]= ((unsigned)checkedLongAt(cursorMaskIndex + (4 * i)) >> 16) & 0xFF;
      }
  }

  /*  if (BitmapBitOrder(stDisplay) == LSBFirst)*/
    {
      /* the bytes are always in the right order: swap only bits within bytes */
      char *dp= (char *)data;
      char *mp= (char *)mask;
      for (i= 0; i < 32; i++)
	{
	  dp[i]= swapBits(dp[i]);
	  mp[i]= swapBits(mp[i]);
	}
    }

  dataPixmap= XCreateBitmapFromData(stDisplay,
				    DefaultRootWindow(stDisplay),
				    (char *)data, 16, 16);

  maskPixmap= XCreateBitmapFromData(stDisplay,
				    DefaultRootWindow(stDisplay),
				    (char *)mask, 16, 16);

  cursor= XCreatePixmapCursor(stDisplay, dataPixmap, maskPixmap,
			      &stColorBlack, &stColorWhite,
			      -offsetX, -offsetY);

  XFreePixmap(stDisplay, dataPixmap);
  XFreePixmap(stDisplay, maskPixmap);

  if (cursor != None)
    XDefineCursor(stDisplay, stWindow, cursor);
#endif
  return 0;
}


int ioSetCursor(int cursorBitsIndex, int offsetX, int offsetY)
{
  /* Deprecated: forward to new version with explicit mask. */
  ioSetCursorWithMask(cursorBitsIndex, null, offsetX, offsetY);
}


int ioSetFullScreen(int fullScreen)
{
#ifndef HEADLESS
  int winX, winY, winW, winH, winB, scrW, scrH;

  /* get screen size */
  scrW= (DisplayWidth(stDisplay, DefaultScreen(stDisplay)));
  scrH= (DisplayHeight(stDisplay, DefaultScreen(stDisplay)));

  if (fullScreen) {
    /* setting full-screen mode */
    if (savedWindowOrigin == -1) {
      /* EITHER: no previous call, OR: previous call disabled full-screen mode */
      {
	/* current origin and extent of Squeak window */
	Window root;
	int depth;
	XGetGeometry(stDisplay, stWindow, &root,
		     &winX, &winY, &winW, &winH, &winB, &depth);
      }
      /* width must be a multiple of sizeof(void *), or X[Shm]PutImage goes gaga */
      if ((winW % sizeof(void *)) != 0)
	winW= (winW / sizeof(void *)) * sizeof(void *);
      savedWindowSize= (winW << 16) + (winH & 0xFFFF);
      savedWindowOrigin= (winX << 16) + (winY & 0xFFFF);
      if ((scrW % sizeof(void *)) != 0)
	scrW= (scrW / sizeof(void *)) * sizeof(void *);
      XMoveResizeWindow(stDisplay, stWindow, 0, 0, scrW, scrH);
      /* sync avoids race with ioScreenSize() reading geometry before resize event */
      XSync(stDisplay, False);
    }
  } else {
    /* reverting to sub-screen mode */
    if (savedWindowOrigin != -1) { /* previous call enabled full-screen mode */
      /* get old window size */
      winW= (unsigned) savedWindowSize >> 16;
      winH= savedWindowSize & 0xFFFF;
      /* minimum size is 64 x 64 */
      winW= (winW > 64) ? winW : 64;
      winH= (winH > 64) ? winH : 64;
      /* old origin */
      winX= savedWindowOrigin >> 16;
      winY= savedWindowOrigin & 0xFFFF;
      savedWindowOrigin= -1; /* prevents consecutive full-screen disables */
      XMoveResizeWindow(stDisplay, stWindow, winX, winY, winW, winH);
      /* sync avoids race with ioScreenSize() reading geometry before resize event */
      XSync(stDisplay, False);
    }
  }
#endif !HEADLESS
  return 0;
}


#ifndef HEADLESS

/* shared-memory stuff */

static void *stMalloc(size_t lbs)
{
#ifdef USE_XSHM
  if (!useXshm)
#endif
    return (void *)malloc(lbs);
#ifdef USE_XSHM
  if ((stShmInfo.shmid= shmget(IPC_PRIVATE, lbs, IPC_CREAT|0777)) == -1) {
    perror("shmget");
    exit(1);
  }
  if ((int)(stShmInfo.shmaddr= (char *)shmat(stShmInfo.shmid, 0, 0)) == -1) {
    perror("shmat");
    exit(1);
  }
  stShmInfo.readOnly= False;
  if (!XShmAttach(stDisplay, &stShmInfo)) {
    fprintf(stderr, "XShmAttach: operation failed\n");
    abort();
  }
  return stShmInfo.shmaddr;
#endif
}

static void stFree(void *addr)
{
#ifdef USE_XSHM
  if (!useXshm)
#endif
    {
      free(addr);
      return;
    }
#ifdef USE_XSHM
  shmctl(stShmInfo.shmid, IPC_RMID, 0);
  shmdt(stShmInfo.shmaddr);
#endif
}

#ifdef USE_XSHM
static void shmExit(void)
{
  if (stDisplayBitmap && useXshm)
    stFree(stDisplayBitmap);
}
#endif

static XImage *stXCreateImage(Display *display, Visual *visual,
			      int depth, int format, int flags, char *data,
			      int width, int height, int bpp, int pad)
{
#ifdef USE_XSHM
  if (!useXshm)
#endif
    return XCreateImage(display, visual, depth, format, flags,
			data, width, height, bpp, pad);
#ifdef USE_XSHM
  return XShmCreateImage(display, visual, depth, format, data,
			 &stShmInfo, width, height);
#endif
}

static void stXPutImage(Display *display, Window window, GC gc, XImage *image,
			int src_x, int src_y, int dst_x, int dst_y, int w, int h)
{
#ifdef USE_XSHM
  if (!useXshm)
#endif
    {
      XPutImage(display, window, gc, image, src_x, src_y, dst_x, dst_y, w, h);
      return;
    }
#ifdef USE_XSHM
  XShmPutImage(display, window, gc, image, src_x, src_y, dst_x, dst_y, w, h, True);
  ++completions;
  if (!asyncUpdate)
    do {
      HandleEvents();
    } while (completions);
#endif
}

static void stXDestroyImage(XImage *image)
{
#ifdef USE_XSHM
  if (useXshm)
    XShmDetach(stDisplay, &stShmInfo);
#endif
  XDestroyImage(image);
}


#define bytesPerLine(width, depth)	((((width)*(depth) + 31) >> 5) << 2)
#define bytesPerLineRD(width, depth)	((((width)*(depth)) >> 5) << 2)

#endif !HEADLESS

int ioForceDisplayUpdate(void)
{
#if !defined(HEADLESS) && defined(USE_XSHM)
  if (asyncUpdate) {
    XFlush(stDisplay);
    do {
      HandleEvents();
    } while (completions);
  }
#endif
  return 0;
}

int ioShowDisplay(int dispBitsIndex, int width, int height, int depth,
		  int affectedL, int affectedR, int affectedT, int affectedB)
{
#ifndef HEADLESS
  if (stWindow == 0)
    return 0;

  if(affectedR <= affectedL || affectedT >= affectedB)
    return 1;

  if (!(depth == 8 || depth == 16 || depth == 32))
  {
    fprintf(stderr, "depth %d is not supported\n", depth);
    exit(1);
    return 0;
  }

  if (stDisplayBitsIndex != dispBitsIndex)
    {
#if defined(USE_XSHM)
      if (asyncUpdate) {
	/* wait for pending updates to complete before freeing the XImage */
	while (completions) HandleEvents();
      }
#endif
      stDisplayBitsIndex= dispBitsIndex;
      if (stImage)
	{
	  stImage->data= 0; /* don't you dare free() Display's Bitmap! */
	  stXDestroyImage(stImage);
	  if (stDisplayBitmap)
	    {
	      stFree(stDisplayBitmap);
	      stDisplayBitmap = 0;
	    }
	}

#ifndef USE_XSHM
# define useXshm 0
#endif

#ifdef HAS_LSB_FIRST
      if (!useXshm && depth == stBitsPerPixel && depth == 32 && stHasSameRGBMask32)
#else
      if (!useXshm && depth == stBitsPerPixel &&
	  (depth != 16 || stHasSameRGBMask16) &&
	  (depth != 32 || stHasSameRGBMask32))
#endif
	{
	  stDisplayBitmap= 0;
	}
      else
	{
	  stDisplayBitmap= stMalloc(bytesPerLine(width, stBitsPerPixel) * height);
	}

#ifndef USE_XSHM
# undef useXshm
#endif

      stImage= stXCreateImage(stDisplay,
			      DefaultVisual(stDisplay, DefaultScreen(stDisplay)),
			      stDepth,
			      ZPixmap,
			      0,
			      (stDisplayBitmap
			         ? stDisplayBitmap
			         : (char *)stDisplayBitsIndex),
			      width,
			      height,
			      32,
			      0);
      /* Xlib ignores the following */
#ifdef HAS_LSB_FIRST
      stImage->byte_order = LSBFirst;
      stImage->bitmap_bit_order = LSBFirst;
#else
      stImage->byte_order = MSBFirst;
      stImage->bitmap_bit_order = MSBFirst;
#endif
      /* not really required (since we never call Get/PutPixel), but what the hey */
      /*
      if (!XInitImage(stImage))
	fprintf(stderr, "XInitImage failed (but we don't care)\n");
      */
    }

  /* this can happen after resizing the window */
  if (affectedR > width) affectedR= width;
  if (affectedB > height) affectedB= height;

  if (depth != stBitsPerPixel)
    {
      if (depth == 8)
	{
	  if (stBitsPerPixel == 16)
	    {
	      copyImage8To16((int *)dispBitsIndex, (int *)stDisplayBitmap,
			     width, height,
			     affectedL, affectedT, affectedR, affectedB);
	    }
	  else /* stBitsPerPixel == 32 */
	    {
	      copyImage8To32((int *)dispBitsIndex, (int *)stDisplayBitmap,
			     width, height,
			     affectedL, affectedT, affectedR, affectedB);
	    }
	}
      else if (depth == 16)
	{
	  if (stBitsPerPixel == 8)
	    {
	      copyImage16To8((int *)dispBitsIndex, (int *)stDisplayBitmap,
			     width, height,
			     affectedL, affectedT, affectedR, affectedB);
	    }
	  else /* stBitsPerPixel == 32 */
	    {
	      copyImage16To32((int *)dispBitsIndex, (int *)stDisplayBitmap,
			      width, height,
			      affectedL, affectedT, affectedR, affectedB);
	    }
	}
      else /* depth == 32 */
	{
	  if (stBitsPerPixel == 8)
	    {
	      copyImage32To8((int *)dispBitsIndex, (int *)stDisplayBitmap,
			     width, height,
			     affectedL, affectedT, affectedR, affectedB);
	    }
	  else /* stBitsPerPixel == 16 */
	    {
	      copyImage32To16((int *)dispBitsIndex, (int *)stDisplayBitmap,
			      width, height,
			      affectedL, affectedT, affectedR, affectedB);
	    }
	}
    }
  else /* depth == stBitsPerPixel */
    {
      if (depth == 16 && !stHasSameRGBMask16)
	{
	  copyImage16To16((int *)dispBitsIndex, (int *)stDisplayBitmap,
			  width, height,
			  affectedL, affectedT, affectedR, affectedB);
	}
      else if (depth == 32 && !stHasSameRGBMask32)
	{
	  copyImage32To32((int *)dispBitsIndex, (int *)stDisplayBitmap,
			  width, height,
			  affectedL, affectedT, affectedR, affectedB);
	}
#ifdef HAS_LSB_FIRST
      else if (depth == 8)
	{
	  copyReverseImageBytes((int *)dispBitsIndex, (int *)stDisplayBitmap,
				depth, width, height,
				affectedL, affectedT, affectedR, affectedB);
	}
      else if (depth == 16)
	{
	  copyReverseImageWords((int *)dispBitsIndex, (int *)stDisplayBitmap,
				depth, width, height,
				affectedL, affectedT, affectedR, affectedB);
	}
#else
# ifdef USE_XSHM
      else if (useXshm)	{
	if (depth == 8) {
	  copyImage8To8((int *)dispBitsIndex, (int *)stDisplayBitmap,
			width, height,affectedL, affectedT, affectedR, affectedB);
	} else {
	  fprintf(stderr, "shared memory not supported for this depth/byte-order\n");
	  exit(1);
	}
      }
# endif
#endif
    }

  stXPutImage(stDisplay, stWindow, stGC, stImage,
	      affectedL, affectedT,	/* src_x, src_y */
	      affectedL, affectedT,	/* dst_x, dst_y */
	      affectedR-affectedL,	/* width */
	      affectedB-affectedT);	/* height */
#endif
  return 0;
}

#ifndef HEADLESS
void copyReverseImageBytes(int *fromImageData, int *toImageData,
			   int depth, int width, int height,
			   int affectedL, int affectedT, int affectedR, int affectedB)
{
  register int scanLine, firstWord, lastWord;
  register int line;

  scanLine= bytesPerLine(width, depth);
  firstWord= scanLine*affectedT + bytesPerLineRD(affectedL, depth);
  lastWord= scanLine*affectedT + bytesPerLine(affectedR, depth);

  for (line= affectedT; line < affectedB; line++)
  {
    register unsigned char *from= (unsigned char *)((int)fromImageData+firstWord);
    register unsigned char *limit= (unsigned char *)((int)fromImageData+lastWord);
    register unsigned char *to= (unsigned char *)((int)toImageData+firstWord);
    while (from < limit)
      {
	to[0]= from[3];
	to[1]= from[2];
	to[2]= from[1];
	to[3]= from[0];
	from+= 4;
	to+= 4;
      }
    firstWord+= scanLine;
    lastWord+= scanLine;
  }
}

void copyReverseImageWords(int *fromImageData, int *toImageData,
			   int depth, int width, int height,
			   int affectedL, int affectedT, int affectedR, int affectedB)
{
  register int scanLine, firstWord, lastWord;
  register int line;

  scanLine= bytesPerLine(width, depth);
  firstWord= scanLine*affectedT + bytesPerLineRD(affectedL, depth);
  lastWord= scanLine*affectedT + bytesPerLine(affectedR, depth);

  for (line= affectedT; line < affectedB; line++)
    {
      register unsigned short *from= (unsigned short *)((int)fromImageData+firstWord);
      register unsigned short *limit= (unsigned short *)((int)fromImageData+lastWord);
      register unsigned short *to= (unsigned short *)((int)toImageData+firstWord);
      while (from < limit)
	{
	  to[0]= from[1];
	  to[1]= from[0];
	  from+= 2;
	  to+= 2;
	}
      firstWord+= scanLine;
      lastWord+= scanLine;
    }
}

void copyImage8To8(int *fromImageData, int *toImageData,
		   int width, int height,
		   int affectedL, int affectedT, int affectedR, int affectedB)
{
  register int scanLine, firstWord, lastWord;
  register int line;

  scanLine= bytesPerLine(width, 8);
  firstWord= scanLine*affectedT + bytesPerLineRD(affectedL, 8);
  lastWord= scanLine*affectedT + bytesPerLine(affectedR, 8);

  for (line= affectedT; line < affectedB; line++) {
    register unsigned int *from= (unsigned int *)((int)fromImageData+firstWord);
    register unsigned int *limit= (unsigned int *)((int)fromImageData+lastWord);
    register unsigned int *to= (unsigned int *)((int)toImageData+firstWord);
    while (from < limit)
      *to++= *from++;
    firstWord+= scanLine;
    lastWord+= scanLine;
  }
}

void copyImage8To16(int *fromImageData, int *toImageData,
		    int width, int height,
		    int affectedL, int affectedT, int affectedR, int affectedB)
{
  int scanLine8, firstWord8, lastWord8;
  int scanLine16, firstWord16, lastWord16;
  register int line;

  scanLine8= bytesPerLine(width, 8);
  firstWord8= scanLine8*affectedT + bytesPerLineRD(affectedL, 8);
  lastWord8= scanLine8*affectedT + bytesPerLine(affectedR, 8);
  scanLine16= bytesPerLine(width, 16);
  firstWord16= scanLine16*affectedT + (bytesPerLineRD(affectedL, 8) << 1);
  lastWord16= scanLine16*affectedT + (bytesPerLine(affectedR, 8) << 1);

  for (line= affectedT; line < affectedB; line++)
    {
      register unsigned char *from= (unsigned char *)((int)fromImageData+firstWord8);
      register unsigned char *limit= (unsigned char *)((int)fromImageData+lastWord8);
      register unsigned short *to= (unsigned short *)((int)toImageData+firstWord16);
      while (from < limit)
	{
#ifdef HAS_LSB_FIRST
	  to[0]= stColors[from[3]];
	  to[1]= stColors[from[2]];
	  to[2]= stColors[from[1]];
	  to[3]= stColors[from[0]];
#else
	  to[0]= stColors[from[0]];
	  to[1]= stColors[from[1]];
	  to[2]= stColors[from[2]];
	  to[3]= stColors[from[3]];
#endif
	  from+= 4;
	  to+= 4;
	}
      firstWord8+= scanLine8;
      lastWord8+= scanLine8;
      firstWord16+= scanLine16;
      lastWord16+= scanLine16;
    }
}

void copyImage16To8(int *fromImageData, int *toImageData,
		    int width, int height,
		    int affectedL, int affectedT, int affectedR, int affectedB)
{
  int scanLine16, firstWord16, lastWord16;
  int scanLine8, firstWord8, lastWord8;
  int line;

#define map16To8(w) (col= (w), stDownGradingColors[ \
  (((col >> (10+(5-3))) & 0x7) << 5) | \
  (((col >> (5+(5-3)))  & 0x7) << 2) | \
   ((col >> (0+(5-2)))  & 0x7)])

  scanLine16= bytesPerLine(width, 16);
  firstWord16= scanLine16*affectedT + bytesPerLineRD(affectedL, 16);
  lastWord16= scanLine16*affectedT + bytesPerLine(affectedR, 16);
  scanLine8= bytesPerLine(width, 8);
  firstWord8= scanLine8*affectedT + (bytesPerLineRD(affectedL, 16) >> 1);
  lastWord8= scanLine8*affectedT + (bytesPerLine(affectedR, 16) >> 1);

  for (line= affectedT; line < affectedB; line++)
    {
      register int col;
      register unsigned short *from= (unsigned short *)((int)fromImageData+firstWord16);
      register unsigned short *limit= (unsigned short *)((int)fromImageData+lastWord16);
      register unsigned char *to= (unsigned char *)((int)toImageData+firstWord8);

      while (from < limit)
	{
#ifdef HAS_LSB_FIRST
	  to[0]= map16To8(from[1]);
	  to[1]= map16To8(from[0]);
#else
	  to[0]= map16To8(from[0]);
	  to[1]= map16To8(from[1]);
#endif
	  from+= 2;
	  to+= 2;
	}
      firstWord16+= scanLine16;
      lastWord16+= scanLine16;
      firstWord8+= scanLine8;
      lastWord8+= scanLine8;
    }
#undef map16To8
}

void copyImage8To32(int *fromImageData, int *toImageData,
		    int width, int height,
		    int affectedL, int affectedT, int affectedR, int affectedB)
{
  int scanLine8, firstWord8, lastWord8;
  int scanLine32, firstWord32, lastWord32;
  int line;

  scanLine8= bytesPerLine(width, 8);
  firstWord8= scanLine8*affectedT + bytesPerLineRD(affectedL, 8);
  lastWord8= scanLine8*affectedT + bytesPerLine(affectedR, 8);
  scanLine32= bytesPerLine(width, 32);
  firstWord32= scanLine32*affectedT + (bytesPerLineRD(affectedL, 8) << 2);
  lastWord32= scanLine32*affectedT + (bytesPerLine(affectedR, 8) << 2);

  for (line= affectedT; line < affectedB; line++)
    {
      register unsigned char *from= (unsigned char *)((int)fromImageData+firstWord8);
      register unsigned char *limit= (unsigned char *)((int)fromImageData+lastWord8);
      register unsigned int *to= (unsigned int *)((int)toImageData+firstWord32);
      while (from < limit)
	{
#ifdef HAS_LSB_FIRST
	  to[0]= stColors[from[3]];
	  to[1]= stColors[from[2]];
	  to[2]= stColors[from[1]];
	  to[3]= stColors[from[0]];
#else
	  to[0]= stColors[from[0]];
	  to[1]= stColors[from[1]];
	  to[2]= stColors[from[2]];
	  to[3]= stColors[from[3]];
#endif
	  from+= 4;
	  to+= 4;
	}
      firstWord8+= scanLine8;
      lastWord8+= scanLine8;
      firstWord32+= scanLine32;
      lastWord32+= scanLine32;
    }
}

void copyImage32To8(int *fromImageData, int *toImageData,
		    int width, int height,
		    int affectedL, int affectedT, int affectedR, int affectedB)
{
  int scanLine32, firstWord32, lastWord32;
  int scanLine8, firstWord8, lastWord8;
  int line;

#define map32To8(w) (col= (w), stDownGradingColors[\
  (((col >> (16+(8-3))) & 0x7) << 5) | \
  (((col >> (8+(8-3)))  & 0x7) << 2) | \
   ((col >> (0+(8-2)))  & 0x7)])

  scanLine32= bytesPerLine(width, 32);
  firstWord32= scanLine32*affectedT + bytesPerLineRD(affectedL, 32);
  lastWord32= scanLine32*affectedT + bytesPerLine(affectedR, 32);
  scanLine8= bytesPerLine(width, 8);
  firstWord8= scanLine8*affectedT + (bytesPerLineRD(affectedL, 32) >> 2);
  lastWord8= scanLine8*affectedT + (bytesPerLine(affectedR, 32) >> 2);

  for (line= affectedT; line < affectedB; line++)
  {
    register int col;
    register unsigned int *from= (unsigned int *)((int)fromImageData+firstWord32);
    register unsigned int *limit= (unsigned int *)((int)fromImageData+lastWord32);
    register unsigned char *to= (unsigned char *)((int)toImageData+firstWord8);
    while (from < limit)
    {
      to[0]= map32To8(from[0]);
      from++;
      to++;
    }
    firstWord32+= scanLine32;
    lastWord32+= scanLine32;
    firstWord8+= scanLine8;
    lastWord8+= scanLine8;
  }
#undef map32To8
}

void copyImage16To32(int *fromImageData, int *toImageData,
		     int width, int height,
		     int affectedL, int affectedT, int affectedR, int affectedB)
{
  int scanLine16, firstWord16, lastWord16;
  int scanLine32, firstWord32, lastWord32;
  int line;
  int rshift, gshift, bshift;
  register unsigned int col;

  rshift= stRNMask-5 + stRShift;
  gshift= stGNMask-5 + stGShift;
  bshift= stBNMask-5 + stBShift;

#define map16To32(w) (col = (w), \
  (((col >> 10) & 0x1f) << rshift) | \
  (((col >> 5)  & 0x1f) << gshift) | \
   ((col & 0x1f) << bshift))

  scanLine16= bytesPerLine(width, 16);
  firstWord16= scanLine16*affectedT + bytesPerLineRD(affectedL, 16);
  lastWord16= scanLine16*affectedT + bytesPerLine(affectedR, 16);
  scanLine32= bytesPerLine(width, 32);
  firstWord32= scanLine32*affectedT + (bytesPerLineRD(affectedL, 16) << 1);
  lastWord32= scanLine32*affectedT + (bytesPerLine(affectedR, 16) << 1);

  for (line= affectedT; line < affectedB; line++)
    {
      register unsigned short *from= (unsigned short *)((int)fromImageData+firstWord16);
      register unsigned short *limit= (unsigned short *)((int)fromImageData+lastWord16);
      register unsigned int *to= (unsigned int *)((int)toImageData+firstWord32);
      while (from < limit)
	{
#ifdef HAS_LSB_FIRST
	  to[0]= map16To32(from[1]);
	  to[1]= map16To32(from[0]);
#else
	  to[0]= map16To32(from[0]);
	  to[1]= map16To32(from[1]);
#endif
	  from+= 2;
	  to+= 2;
	}
      firstWord16+= scanLine16;
      lastWord16+= scanLine16;
      firstWord32+= scanLine32;
      lastWord32+= scanLine32;
    }
#undef map16To32
}

void copyImage32To16(int *fromImageData, int *toImageData,
		     int width, int height,
		     int affectedL, int affectedT, int affectedR, int affectedB)
{
  int scanLine32, firstWord32, lastWord32;
  int scanLine16, firstWord16, lastWord16;
  int line;
  int rshift, gshift, bshift;
  register unsigned int col;

  rshift= stRNMask-5 + stRShift;
  gshift= stGNMask-5 + stGShift;
  bshift= stBNMask-5 + stBShift;

#define map32To16(w) (col = (w), \
  (((col >> 16) & 0xff) << rshift) | \
  (((col >> 8)  & 0xff) << gshift) | \
   ((col & 0xff) << bshift))

  scanLine32= bytesPerLine(width, 32);
  firstWord32= scanLine32*affectedT + bytesPerLineRD(affectedL, 32);
  lastWord32= scanLine32*affectedT + bytesPerLine(affectedR, 32);
  scanLine16= bytesPerLine(width, 16);
  firstWord16= scanLine16*affectedT + (bytesPerLineRD(affectedL, 32) >> 1);
  lastWord16= scanLine16*affectedT + (bytesPerLine(affectedR, 32) >> 1);

  for (line= affectedT; line < affectedB; line++)
    {
      register unsigned int *from= (unsigned int *)((int)fromImageData+firstWord32);
      register unsigned int *limit= (unsigned int *)((int)fromImageData+lastWord32);
      register unsigned short *to= (unsigned short *)((int)toImageData+firstWord16);
      while (from < limit)
	{
	  to[0]= map32To16(from[1]);
	  from++;
	  to++;
	}
      firstWord32+= scanLine32;
      lastWord32+= scanLine32;
      firstWord16+= scanLine16;
      lastWord16+= scanLine16;
    }
#undef map32To16
}

void copyImage16To16(int *fromImageData, int *toImageData,
		     int width, int height,
		     int affectedL, int affectedT, int affectedR, int affectedB)
{
  int scanLine16, firstWord16, lastWord16;
  int line;
  int rshift, gshift, bshift;
  register unsigned int col;

  rshift= stRNMask-5 + stRShift;
  gshift= stGNMask-5 + stGShift;
  bshift= stBNMask-5 + stBShift;

#define map16To16(w) (col = (w), \
  (((col >> 10) & 0x1f) << rshift) | \
  (((col >> 5)  & 0x1f) << gshift) | \
   ((col & 0x1f) << bshift))

  scanLine16= bytesPerLine(width, 16);
  firstWord16= scanLine16*affectedT + bytesPerLineRD(affectedL, 16);
  lastWord16= scanLine16*affectedT + bytesPerLine(affectedR, 16);

  for (line= affectedT; line < affectedB; line++)
    {
      register unsigned short *from= (unsigned short *)((int)fromImageData+firstWord16);
      register unsigned short *limit= (unsigned short *)((int)fromImageData+lastWord16);
      register unsigned short *to= (unsigned short *)((int)toImageData+firstWord16);
      while (from < limit)
	{
#ifdef HAS_LSB_FIRST
	  to[0]= map16To16(from[1]);
	  to[1]= map16To16(from[0]);
#else
	  to[0]= map16To16(from[0]);
	  to[1]= map16To16(from[1]);
#endif
	  from+= 2;
	  to+= 2;
	}
      firstWord16+= scanLine16;
      lastWord16+= scanLine16;
    }
#undef map16To16
}

void copyImage32To32(int *fromImageData, int *toImageData,
		     int width, int height,
		     int affectedL, int affectedT, int affectedR, int affectedB)
{
  int scanLine32, firstWord32, lastWord32;
  int line;
  int rshift, gshift, bshift;
  register unsigned int col;

  rshift= stRNMask-8 + stRShift;
  gshift= stGNMask-8 + stGShift;
  bshift= stBNMask-8 + stBShift;

#define map32To32(w) (col = (w), \
  (((col >> 16) & 0xff) << rshift) | \
  (((col >> 8)  & 0xff) << gshift) | \
   ((col & 0xff) << bshift))

  scanLine32= bytesPerLine(width, 32);
  firstWord32= scanLine32*affectedT + bytesPerLineRD(affectedL, 32);
  lastWord32= scanLine32*affectedT + bytesPerLine(affectedR, 32);

  for (line= affectedT; line < affectedB; line++)
    {
      register unsigned int *from= (unsigned int *)((int)fromImageData+firstWord32);
      register unsigned int *limit= (unsigned int *)((int)fromImageData+lastWord32);
      register unsigned int *to= (unsigned int *)((int)toImageData+firstWord32);
      while (from < limit)
	{
	  *to= map32To32(*from);
	  from++;
	  to++;
	}
      firstWord32+= scanLine32;
      lastWord32+= scanLine32;
    }
#undef map32To32
}
#endif


/*** Image File Naming ***/

void RecordFullPathForImageName(char *localImageName)
{
  int i;
  /* get canonical path to image */
  if (!realpath(localImageName, vmPath))
    imageNotFound(localImageName);
  strcpy(imageName, vmPath);
  /* truncate vmPath to dirname */
  for (i= strlen(vmPath); i >= 0; i--)
    if ('/' == vmPath[i])
      {
	vmPath[i+1]= '\0';
	return;
      }
  /* this might just work in an emergency... */
  strcpy(imageName, vmPath);
}

int imageNameSize(void)
{
  return strlen(imageName);
}

int imageNameGetLength(int sqImageNameIndex, int length)
{
  char *sqImageName= (char *)sqImageNameIndex;
  int count, i;

  count= strlen(imageName);
  count= (length < count) ? length : count;

  /* copy the file name into the Squeak string */
  for (i= 0; i < count; i++)
    sqImageName[i]= imageName[i];

  return count;
}

int imageNamePutLength(int sqImageNameIndex, int length)
{
  char *sqImageName= (char *)sqImageNameIndex;
  int count, i;

  count= (IMAGE_NAME_SIZE < length) ? IMAGE_NAME_SIZE : length;

  /* copy the file name into a null-terminated C string */
  for (i= 0; i < count; i++) imageName[i]= sqImageName[i];
  imageName[count]= 0;

#ifndef HEADLESS
  /* update the window title */
  XStoreName(stDisplay, stWindow, imageName);
#endif

  return count;
}

/*** Timing support ***/

void SetUpTimers(void)
{
  gettimeofday(&startUpTime, 0);
}

/*** X selection handling ***/

#ifndef HEADLESS
void SetUpClipboard(void)
{
  stPrimarySelection= 0;
  stPrimarySelectionSize= 0;
  stOwnsSelection= 0;
}
#endif

int clipboardSize(void)
{
#ifndef HEADLESS
  if (stOwnsSelection)
    return stPrimarySelection ? strlen(stPrimarySelection) : 0;
  return strlen(getSelection());
#else
  return 0;
#endif
}

#ifndef HEADLESS
static void allocateSelectionBuffer(int count)
{
  if (count+1 > stPrimarySelectionSize)
    {
      if (stPrimarySelection)
	{
	  free(stPrimarySelection);
	  stPrimarySelection= 0;
	  stPrimarySelectionSize= 0;
	}
      if (!(stPrimarySelection= (char *)malloc(count+1)))
	{
	  fprintf(stderr, "failed to allocate X selection buffer\n");
	  return;
	}
      stPrimarySelectionSize= count;
    }
}
#endif

/* claim ownership of the X selection, providing the given string to requestors */
int clipboardWriteFromAt(int count, int byteArrayIndex, int startIndex)
{
#ifndef HEADLESS
  char *srcPtr, *dstPtr, *end;

  allocateSelectionBuffer(count);

  srcPtr= (char *)byteArrayIndex + startIndex;
  dstPtr= stPrimarySelection;
  end= srcPtr + count;
  while (srcPtr < end)
    *dstPtr++= *srcPtr++;

  *dstPtr= '\0';

  claimSelection();
#endif
  return 0;
}

/* transfer the X selection into the given byte array; optimise local requests */
int clipboardReadIntoAt(int count, int byteArrayIndex, int startIndex)
{
#ifndef HEADLESS
  long clipSize, charsToMove;
  char *srcPtr, *dstPtr, *end;

  if (!stOwnsSelection)
    {
      char *newSelection;
      int newSize;

      /* need to keep a separate selection buffer, or we wouldn't know if it
	 was allocated by us or by X */
      newSelection= getSelection();	/* not necessarily allocated by X... */
      newSize= strlen(newSelection);
      allocateSelectionBuffer(newSize);
      strcpy(stPrimarySelection, newSelection);
      if (newSelection != stEmptySelection) /* ...so we only *sometimes*... */
	XFree(newSelection);		/* ...need to XFree() it! */
      ux2st(stPrimarySelection);
    }

  clipSize= clipboardSize();
  charsToMove= (count < clipSize) ? count : clipSize;

  srcPtr= (char *)stPrimarySelection;
  dstPtr= (char *)byteArrayIndex + startIndex;
  end= srcPtr + charsToMove;
  while (srcPtr < end)
    *dstPtr++= *srcPtr++;

  return charsToMove;
#else
  return 0;
#endif
}

/*** Profiling ***/

int clearProfile(void) { return 0; }
int dumpProfile(void) { return 0; }
int startProfiling(void) { return 0; }
int stopProfiling(void) { return 0; }

/*** Access to system attributes and command-line arguments ***/

static char *getSpecialAttribute(int id)
{
  static char buf[256];
  switch (id) {
  case 1:	/* Squeak PID */
    sprintf(buf, "%d", getpid());
    return buf;
  }
  buf[0]= '\0';
  return buf;
}

int attributeSize(int id)
{
  if (id + 1 >= initialArgc) return 0;
  if (id < 0)
    return strlen(getSpecialAttribute(-id));
  else
    return strlen(initialArgv[id + 1]);
}

int getAttributeIntoLength(int id, int byteArrayIndex, int length)
{
  char *attrIndex= (char *)byteArrayIndex;
  char *arg;
  if (id + 1>= initialArgc) return 0;
  if (id < 0)
    arg= getSpecialAttribute(-id);
  else
    arg= initialArgv[id + 1];
  while (length--)
    *attrIndex++= *arg++;
  return 0;
}

/*** Command line ***/

static char *progName;

void usage()
{
  printf("Usage: %s [<options>] [<imageName>]\n\n", progName);
  printf("<options> are:\n");
  printf("  -display <dpy>       display on <dpy> (default: $DISPLAY)\n");
#ifdef USE_XSHM
  printf("  -xshm                enable X shared memory extensions\n");
#endif
  printf("  -notitle             turn off the Squeak window title bar\n");
  printf("  -fullscreen          occupy the entire screen\n");
  printf("  -lazy                go to sleep when main window unmapped\n");
  printf("  -memory <size>[mk]   set initial memory size (default: 5m)\n");
#ifdef CCACHE
  printf("  -ccache <size>       set context cache size (default: 16)\n");
#endif
  printf("  -version             print version information, then exit\n");
  printf("\nNotes:\n");
  printf("  <imageName> defaults to 'squeak.image'.\n");
  printf("  Using 'unix:0' for <dpy> may improve local display performance.\n");
  printf("  -xshm only works when Squeak is running on the X server host.\n");
  exit(1);
}

void imageNotFound(char *imageName)
{
  /* image file is not found */
  fprintf(stderr, "Could not open the Squeak image file '%s'.\n\n", imageName);
  fprintf(stderr, "There are two ways to open a Squeak image file.  You can:\n");
  fprintf(stderr, "  1. Put the name of the image file on the command line\n");
  fprintf(stderr, "     when you run Squeak (use '-help' for more information).\n");
  fprintf(stderr, "  2. Save an image (from inside Squeak) with the name 'clone'\n");
  fprintf(stderr, "     and run Squeak from the directory containing it.\n");
  exit(1);
}

int strtobkm(char *str) {
  char *suffix;
  int value= strtol(str, &suffix, 10);
  switch (*suffix) {
  case 'k': case 'K':
    value*= 1024;
    break;
  case 'm': case 'M':
    value*= 1024*1024;
    break;
  }
  return value;
}

void ParseArguments(int argc, char **argv)
{
  char *ev;

  initialArgv= argv;
  initialArgc= 0;

  /* defaults */

  if ((ev= getenv("SQUEAK_IMAGE")))
    strcpy(shortImageName, ev);
  else
    strcpy(shortImageName, "squeak.image");

  if ((ev= getenv("SQUEAK_MEMORY")))
    initialHeapSize= strtobkm(ev);
  else
    initialHeapSize= 5*1024*1024;	/* 5 megabytes by default */

  if (getenv("SQUEAK_LAZY"))
    sleepWhenUnmapped= 1;
  else
    sleepWhenUnmapped= 0;

  if (getenv("SQUEAK_NOTITLE"))
    noTitle= 1;
  else
    noTitle= 0;

  if (getenv("SQUEAK_FULLSCREEN"))
    fullScreen= 1;
  else
    fullScreen= 0;

#if defined(USE_XSHM) && !defined(HEADLESS)
  if (getenv("SQUEAK_XSHM"))
    useXshm= 1;
  else
    useXshm= 0;

  if (getenv("SQUEAK_XASYNC"))
    asyncUpdate= 1;
  else
    asyncUpdate= 0;
#endif

#ifdef CCACHE
  if (ev= getenv("SQUEAK_CCACHE"))
    stackCacheEntries= atoi(ev);
  else
    stackCacheEntries= 0;
  contextCacheEntries= stackCacheEntries;
#endif

  argc--;
  argv++;	/* skip VM name */

  while (argc && **argv == '-')	/* more options to parse */
    {
      if (!strcmp(*argv, "-help"))
	usage();

#ifndef HEADLESS
      if (!strcmp(*argv, "-display"))
	{
	  argc--;	/* skip -display */
	  argv++;
	  if (!argc) usage();
	  displayName= *argv++;
	  argc--;
	  continue;
	}
#endif

      if (!strcmp(*argv, "-memory"))
	{
	  argc--;	/* skip -memory */
	  argv++;
	  if (!argc) usage();
	  initialHeapSize= strtobkm(*argv++);
	  argc--;
	  continue;
	}

#ifdef CCACHE
      if (!strcmp(*argv, "-ccache"))
	{
	  argc--;	/* skip -ccache */
	  argv++;
	  if (!argc) usage();
	  stackCacheEntries= contextCacheEntries= atoi(*argv++);
	  argc--;
	  if (contextCacheEntries < 2)
	    {
	      fprintf(stderr, "context cache size must be at least 2\n");
	      exit(1);
	    }
	  continue;
	}
#endif

#if defined(USE_XSHM) && !defined(HEADLESS)
      if (!strcmp(*argv, "-xshm"))
	{
	  argc--;	/* skip -xshm */
	  argv++;
	  useXshm= 1;
	  continue;
	}

      if (!strcmp(*argv, "-xasync"))
	{
	  argc--;	/* skip -xasync */
	  argv++;
	  asyncUpdate= 1;
	  continue;
	}
#endif

      if (!strcmp(*argv, "-lazy"))
	{
	  argc--;	/* skip -lazy */
	  argv++;
	  sleepWhenUnmapped= 1;
	  continue;
	}

      if (!strcmp(*argv, "-notitle"))
	{
	  argc--;	/* skip -notitle */
	  argv++;
	  noTitle= 1;
	  continue;
	}

      if (!strcmp(*argv, "-fullscreen"))
	{
	  argc--;	/* skip -fullscreen */
	  argv++;
	  fullScreen= 1;
	  continue;
	}

      if (!strcmp(*argv, "-version"))
	{
	  extern int vm_serial;
	  extern char *vm_date, *vm_version, *cc_version, *ux_version;
	  extern char *up_version;
	  fprintf(stderr, "%s/%d #%d %s%s %s\n%s\n%s\n",
		  vm_version, CURRENT_VERSION, vm_serial,
#ifdef USE_XSHM
		  "XShm ",
#else
		  " ",
#endif
		  vm_date, cc_version, ux_version, up_version);
	  exit(0);
	}

      /* assume the argument is meant for Squeak, and silently ignore it */
      initialArgv[initialArgc++]= *argv++;
      --argc;
    }

  if (argc)
    {
      strcpy(shortImageName, *argv);
      initialArgv[initialArgc++]= *argv++;
      --argc;
    }
  initialArgv[initialArgc]= (char *)0;
}

/*** Segmentation fault handler ***/

#include <signal.h>

void segv(int ignore)
{
  error("Segmentation fault");
}

#ifdef __alpha__
/* headers for setsysinfo (see below) */
# include <sys/sysinfo.h>
# include <sys/proc.h>
#endif

int main(int argc, char **argv)
{
  signal(SIGSEGV, segv);

  /* initialisation */

#ifdef __alpha__
  /* disable printing of unaligned access exceptions */
  {
    int buf[2]= { SSIN_UACPROC, UAC_NOPRINT };
    if (setsysinfo(SSI_NVPAIRS, buf, 1, 0, 0, 0) < 0) {
      perror("setsysinfo(UAC_NOPRINT)");
    }
  }
#endif

  progName= argv[0];
  ParseArguments(argc, argv);
  SetUpTimers();

#ifndef HEADLESS
# ifdef USE_XSHM
#   ifdef HAS_ON_EXIT
      on_exit(shmExit);
#   else
      atexit(shmExit);
#   endif
# endif
#endif

  sqFileInit();
  joystickInit();

#ifdef NEED_TZSET
  tzset();	/* should _not_ be necessary! */
#endif

  RecordFullPathForImageName(shortImageName);

  /* check the interpreter's size assumptions for basic data types */
  if (sizeof(int) != 4)    error("This C compiler's integers are not 32 bits.");
  if (sizeof(double) != 8) error("This C compiler's floats are not 64 bits.");
  if (sizeof(time_t) != 4) error("This C compiler's time_t's are not 32 bits.");

  /* read the image file and allocate memory for Squeak heap */
  {
    FILE *f= fopen(imageName, "r");

    if (f == NULL)
      imageNotFound(imageName);
    readImageFromFileHeapSize(f, initialHeapSize);
    fclose(f);
  }

#ifndef HEADLESS
  /* open the Squeak window. */
  SetUpClipboard();
  SetUpWindow(displayName);
  SetUpPixmap();
  SetWindowSize();
  XMapWindow(stDisplay, stWindow);
#endif

  /* run Squeak */
  interpret();

  return 0;
}


int ioExit(void)
{
  exit(0);
}
