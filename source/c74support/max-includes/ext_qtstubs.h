#ifndef __XQT_STUBS_H__
#define __XQT_STUBS_H__

#include "ext.h"

#ifdef C74_USING_QUICKTIME

#ifdef MAC_VERSION

#include <CoreFoundation/CFString.h>

#endif

#ifdef WIN_VERSION

#include <QTML.h>
#include <Movies.h>
#include <Sound.h>
#include <CFString.h>

#endif

#ifdef MAC_VERSION
#define XQT_PathStyle kQTPOSIXPathStyle
#endif

#ifdef WIN_VERSION
#define XQT_PathStyle kQTWindowsPathStyle
#endif

// for max 5 we will rid the kernel of XQT stuff and just have things call directly
// by linking with qtmlClient.lib as appropriate. 
#ifndef USE_ALTURA

#define XQT_OpenMovieFilePathSpec			OpenMovieFile
#define XQT_patcher_setport					patcher_setport
#define XQT_patcher_restoreport				MacSetPort
#define XQT_wind_setport					wind_setport
#ifdef TARGET_API_MAC_CARBON
#define XQT_wind_getport(x)					(GetWindowPort(wind_syswind(x)))
#else
#define XQT_wind_getport(x)					(wind_syswind(x))
#endif
#define XQT_box_nodraw						box_nodraw
#define XQT_box_enddraw						box_enddraw
#define XQT_GetPortBitMapForCopyBits		GetPortBitMapForCopyBits

// MacToolbox Functions as exposed by Quicktime
#define	XQT_Gestalt							Gestalt
#define	XQT_NewHandle						NewHandle
#define XQT_GetHandleSize					GetHandleSize
#define	XQT_DisposeHandle					DisposeHandle
#define	XQT_HLock							HLock
#define	XQT_HUnlock							HUnlock
#define	XQT_NewGWorld						NewGWorld
#define XQT_QTNewGWorld						QTNewGWorld
#define	XQT_DisposeGWorld					DisposeGWorld
#define	XQT_GetGWorldPixMap					GetGWorldPixMap
#define	XQT_GetPixBaseAddr					GetPixBaseAddr
#ifdef MAC_VERSION
#define	XQT_GetPixRowBytes					GetPixRowBytes
#endif
#ifdef WIN_VERSION
#define XQT_GetPixRowBytes					QTGetPixMapHandleRowBytes
#endif
#define	XQT_LockPixels						LockPixels
#define	XQT_UnlockPixels					UnlockPixels
#define	XQT_GetPortBounds					GetPortBounds
#define	XQT_SetPort							SetPort
#define	XQT_GetPort							GetPort
#define	XQT_SetPortWindowPort				SetPortWindowPort
#define	XQT_GetWindowFromPort				GetWindowFromPort
#define XQT_NewRgn							NewRgn
#define XQT_DisposeRgn						DisposeRgn
#define XQT_CopyRgn							CopyRgn
#define XQT_RectRgn							RectRgn
#define XQT_SectRgn							SectRgn
#define XQT_EqualRgn						EqualRgn
#define XQT_GetRegionBounds					GetRegionBounds
#define XQT_TickCount						TickCount
#define XQT_GetFNum							GetFNum
#define XQT_TextFont						TextFont
#define XQT_TextSize						TextSize

// Quicktime Functions
#define	XQT_InitializeQTML					InitializeQTML
#define	XQT_TerminateQTML					TerminateQTML
#define	XQT_MCGetIndMovie					MCGetIndMovie
#define	XQT_SetIdentityMatrix				SetIdentityMatrix
#define	XQT_CreatePortAssociation			CreatePortAssociation
#define	XQT_DestroyPortAssociation			DestroyPortAssociation
#define	XQT_CloseMovieFile					CloseMovieFile
#define	XQT_DisposeMovie					DisposeMovie
#define	XQT_DisposeMovieController			DisposeMovieController
#define	XQT_DisposeTimeBase					DisposeTimeBase
#define	XQT_EnterMovies						EnterMovies
#define	XQT_ExitMovies						ExitMovies
#define	XQT_GetMediaDuration				GetMediaDuration
#define	XQT_GetMediaSampleDescription		GetMediaSampleDescription
#define	XQT_GetMediaTimeScale				GetMediaTimeScale
#define	XQT_GetMoviePict					GetMoviePict
#define	XQT_GetMovieBox						GetMovieBox
#define	XQT_GetMovieDisplayClipRgn			GetMovieDisplayClipRgn
#define	XQT_GetMovieDuration				GetMovieDuration
#define	XQT_GetMovieGWorld					GetMovieGWorld
#define	XQT_GetMovieIndTrackType			GetMovieIndTrackType
#define	XQT_GetMovieMatrix					GetMovieMatrix
#define	XQT_GetMovieRate					GetMovieRate
#define	XQT_GetMoviesError					GetMoviesError
#define	XQT_GetMovieTime					GetMovieTime
#define	XQT_GetMovieTimeBase				GetMovieTimeBase
#define	XQT_GetMovieTimeScale				GetMovieTimeScale
#define	XQT_GetNativeWindowPort				GetNativeWindowPort
#define	XQT_GetSoundHeaderOffset			GetSoundHeaderOffset
#define	XQT_GetTimeBaseFlags				GetTimeBaseFlags
#define	XQT_GetTrackDuration				GetTrackDuration
#define	XQT_GetTrackMedia					GetTrackMedia
#define	XQT_IsMovieDone						IsMovieDone
#define	XQT_LoadMovieIntoRam				LoadMovieIntoRam
#define	XQT_MCClick							MCClick
#define	XQT_MCDoAction						MCDoAction
#define	XQT_MCDraw							MCDraw
#define	XQT_MCGetClip						MCGetClip
#define	XQT_MCIdle							MCIdle
#define	XQT_MCSetActionFilterWithRefCon		MCSetActionFilterWithRefCon
#define	XQT_MCSetClip						MCSetClip
#define	XQT_MCSetControllerAttached			MCSetControllerAttached
#define	XQT_MCSetControllerBoundsRect		MCSetControllerBoundsRect
#define	XQT_MCSetControllerPort				MCSetControllerPort
#define XQT_MCGetControllerPort				MCGetControllerPort
#define	XQT_MCSetMovie						MCSetMovie
#define	XQT_MCSetVisible					MCSetVisible
#define	XQT_MoviesTask						MoviesTask
#define	XQT_NativePathNameToFSSpec			NativePathNameToFSSpec
#define	XQT_NewMovieFromFile				NewMovieFromFile
#define	XQT_OpenDefaultComponent			OpenDefaultComponent
#define	XQT_PutMovieIntoTypedHandle			PutMovieIntoTypedHandle
#define	XQT_SetMovieActive					SetMovieActive
#define	XQT_SetMovieBox						SetMovieBox
#define	XQT_SetMovieDisplayClipRgn			SetMovieDisplayClipRgn
#define	XQT_SetMovieGWorld					SetMovieGWorld
#define	XQT_SetMovieMatrix					SetMovieMatrix
#define	XQT_SetMoviePlayHints				SetMoviePlayHints
#define	XQT_SetMovieRate					SetMovieRate
#define	XQT_SetMovieTimeValue				SetMovieTimeValue
#define	XQT_SetMovieVolume					SetMovieVolume
#define	XQT_SetTimeBaseFlags				SetTimeBaseFlags
#define	XQT_SetTimeBaseStartTime			SetTimeBaseStartTime
#define	XQT_SetTimeBaseStopTime				SetTimeBaseStopTime
#define	XQT_SetupAIFFHeader					SetupAIFFHeader
#define	XQT_StartMovie						StartMovie
#define	XQT_UpdateMovie						UpdateMovie

#define XQT_GetMovieNaturalBoundsRect		GetMovieNaturalBoundsRect
#define XQT_SetMovieDrawingCompleteProc		SetMovieDrawingCompleteProc

#define XQT_FixRatio						FixRatio
	
#endif // #ifndef USE_ALTURA

#ifdef USE_ALTURA

#define XQT_EXTERN_API(x)	x

// carbon style macros

#define XQT_GetPortBitMapForCopyBits(x)		((BitMap *)*((CGrafPtr)(x))->portPixMap)

#ifdef __cplusplus
extern "C" {
#endif

// Max-specific functions

XQT_EXTERN_API( long )
XQT_GetQuickTimeVersion( void );

XQT_EXTERN_API( long )
XQT_CheckFunPtr( FARPROC *ppfn, const char *name );

//XQT_EXTERN_API( OSErr )
//XQT_OpenMovieFilePathSpec( const PATH_SPEC* pathSpec, short* resRefNum, SInt8 permission );

//XQT_EXTERN_API( long )
//XQT_QT2MaxSpecCopy(FSSpec *qt_spec, PATH_SPEC *max_spec);

//XQT_EXTERN_API( long )
//XQT_Max2QTSpecCopy(PATH_SPEC *max_spec, FSSpec *qt_spec);

XQT_EXTERN_API( long )
XQT_QT2MaxGWorldCopy(GWorldPtr qt_src, GWorldPtr max_dst);

XQT_EXTERN_API( long )
XQT_Max2QTGWorldCopy(GWorldPtr max_src, GWorldPtr qt_dst);

XQT_EXTERN_API( void )
XQT_QTGWorldClear(GWorldPtr gp, long c);

XQT_EXTERN_API( RgnHandle )
XQT_hwnd_qtclip(HWND hwnd);

XQT_EXTERN_API( GrafPtr )
XQT_hwnd_setport(HWND hWnd);

XQT_EXTERN_API( GrafPtr )
XQT_hwnd_getport(HWND hWnd);

XQT_EXTERN_API( GrafPtr )
XQT_patcher_setport(struct patcher *p);

XQT_EXTERN_API( GrafPtr )
XQT_patcher_getport(struct patcher *p);

XQT_EXTERN_API( void )
XQT_patcher_restoreport(GrafPtr gp);

XQT_EXTERN_API( GrafPtr )
XQT_wind_setport(struct wind *x);

XQT_EXTERN_API( GrafPtr )
XQT_wind_getport(struct wind *x);

XQT_EXTERN_API( short )
XQT_box_nodraw(struct box *x);

XQT_EXTERN_API( void )
XQT_box_enddraw(struct box *x);

// Mac Toolbox functions from QT on windows

XQT_EXTERN_API( OSErr )
XQT_Gestalt( OSType selector, long *response );

XQT_EXTERN_API( Handle )
XQT_NewHandle( Size byteCount );

XQT_EXTERN_API(void)
XQT_DisposeHandle(Handle h);

XQT_EXTERN_API( Size )
XQT_GetHandleSize( Handle h );

XQT_EXTERN_API( void )
XQT_HLock(Handle h);

XQT_EXTERN_API( void)
XQT_HUnlock(Handle h);

XQT_EXTERN_API( QDErr )
XQT_NewGWorld( GWorldPtr *offscreenGWorld, short PixelDepth, const Rect *boundsRect, 
				  CTabHandle cTable, GDHandle aGDevice, GWorldFlags flags );

XQT_EXTERN_API( OSErr )
XQT_QTNewGWorld(
  GWorldPtr *   offscreenGWorld,
  OSType        PixelFormat,
  const Rect *  boundsRect,
  CTabHandle    cTable,
  GDHandle      aGDevice,
  GWorldFlags   flags);

XQT_EXTERN_API( void )
XQT_DisposeGWorld( GWorldPtr offscreenGWorld ); 

XQT_EXTERN_API( PixMapHandle )
XQT_GetGWorldPixMap(GWorldPtr offscreenGWorld);

XQT_EXTERN_API( Ptr )
XQT_GetPixBaseAddr(PixMapHandle pm);

XQT_EXTERN_API( long )
XQT_GetPixRowBytes(PixMapHandle pm);

XQT_EXTERN_API( void )
XQT_LockPixels(PixMapHandle h);

XQT_EXTERN_API( void)
XQT_UnlockPixels(PixMapHandle h);

XQT_EXTERN_API( Rect * )
XQT_GetPortBounds(CGrafPtr port, Rect *rect);

XQT_EXTERN_API( void )
XQT_SetPort(GrafPtr port);

XQT_EXTERN_API( void )
XQT_GetPort(GrafPtr *port);

XQT_EXTERN_API( void )
XQT_SetPortWindowPort(WindowRef window);

XQT_EXTERN_API( WindowRef )
XQT_GetWindowFromPort (CGrafPtr port);

XQT_EXTERN_API( void )
XQT_SetClip(RgnHandle rgn);

XQT_EXTERN_API( void )
XQT_GetClip(RgnHandle rgn);

XQT_EXTERN_API( RgnHandle )
XQT_NewRgn (void);

XQT_EXTERN_API( void )
XQT_DisposeRgn (RgnHandle rgn);

XQT_EXTERN_API( void )
XQT_CopyRgn (RgnHandle srcRgn, RgnHandle dstRgn);

XQT_EXTERN_API( void )
XQT_RectRgn (RgnHandle rgn, const Rect *r);

XQT_EXTERN_API( void )
XQT_SectRgn (RgnHandle srcRgnA, RgnHandle srcRgnB, RgnHandle dstRgn);

XQT_EXTERN_API( Boolean )
XQT_EqualRgn (RgnHandle rgnA, RgnHandle rgnB);

XQT_EXTERN_API( Rect *)
XQT_GetRegionBounds (RgnHandle region, Rect *bounds);

XQT_EXTERN_API( UInt32 )
XQT_TickCount (void);

XQT_EXTERN_API( void )
XQT_GetFNum( ConstStr255Param name, short *familyID);

XQT_EXTERN_API( void )
XQT_TextFont(short font);

XQT_EXTERN_API( void )
XQT_TextSize(short size);


// QuickTime functions

XQT_EXTERN_API( OSErr ) 
XQT_InitializeQTML( long flag );

XQT_EXTERN_API( OSErr ) 
XQT_TerminateQTML( void );

XQT_EXTERN_API( Movie )
XQT_MCGetIndMovie( MovieController mc, short index );

XQT_EXTERN_API( void )
XQT_SetIdentityMatrix( MatrixRecord* matrix );

XQT_EXTERN_API(GrafPtr)
XQT_CreatePortAssociation( void* theWnd, Ptr storage, long flags );

XQT_EXTERN_API( void )
XQT_DestroyPortAssociation( CGrafPtr cgp );

XQT_EXTERN_API( OSErr )
XQT_CloseMovieFile( short resRefNum );

XQT_EXTERN_API( void )
XQT_DisposeMovie( Movie theMovie );

XQT_EXTERN_API( void )
XQT_DisposeMovieController( ComponentInstance mc );

XQT_EXTERN_API( void )
XQT_DisposeTimeBase( TimeBase tb );

XQT_EXTERN_API( OSErr )
XQT_EnterMovies( void );

XQT_EXTERN_API( void )
XQT_ExitMovies( void );

XQT_EXTERN_API( TimeValue )
XQT_GetMediaDuration( Media theMedia );

XQT_EXTERN_API( void )
XQT_GetMediaSampleDescription( Media theMedia, long index, SampleDescriptionHandle descH );

XQT_EXTERN_API( TimeScale )
XQT_GetMediaTimeScale( Media theMedia );

XQT_EXTERN_API( PicHandle )
XQT_GetMoviePict( Movie theMovie, TimeValue time );

XQT_EXTERN_API( void )
XQT_GetMovieBox( Movie theMovie, Rect* boxRect );

XQT_EXTERN_API( RgnHandle )
XQT_GetMovieDisplayClipRgn( Movie theMovie );

XQT_EXTERN_API( TimeValue )
XQT_GetMovieDuration( Movie theMovie );

XQT_EXTERN_API( void )
XQT_GetMovieGWorld( Movie theMovie, CGrafPtr* port, GDHandle* gdh );

XQT_EXTERN_API( Track )
XQT_GetMovieIndTrackType( Movie theMovie, long index, OSType trackType, long flags );

XQT_EXTERN_API( void )
XQT_GetMovieMatrix( Movie theMovie, MatrixRecord* matrix );

XQT_EXTERN_API( Fixed )
XQT_GetMovieRate( Movie theMovie );

XQT_EXTERN_API( OSErr )
XQT_GetMoviesError( void );

XQT_EXTERN_API( TimeValue )
XQT_GetMovieTime( Movie theMovie, TimeRecord* __currentTime );

XQT_EXTERN_API( TimeBase )
XQT_GetMovieTimeBase( Movie theMovie );

XQT_EXTERN_API( TimeScale )
XQT_GetMovieTimeScale( Movie theMovie );

XQT_EXTERN_API( GrafPtr )
XQT_GetNativeWindowPort( void* nativeWindow );

XQT_EXTERN_API( OSErr )
XQT_GetSoundHeaderOffset( SndListHandle sndHandle, long* offset );

XQT_EXTERN_API( long )
XQT_GetTimeBaseFlags( TimeBase tb );

XQT_EXTERN_API( TimeValue )
XQT_GetTrackDuration( Track theTrack );

XQT_EXTERN_API( Media )
XQT_GetTrackMedia( Track theTrack );

XQT_EXTERN_API( Boolean )
XQT_IsMovieDone( Movie theMovie );

XQT_EXTERN_API( OSErr )
XQT_LoadMovieIntoRam( Movie theMovie, TimeValue time, TimeValue duration, long flags );

XQT_EXTERN_API( ComponentResult )
XQT_MCClick( MovieController mc, WindowRef w, Point where, long when, long modifiers );

XQT_EXTERN_API( ComponentResult )
XQT_MCDoAction( MovieController mc, short action, void* params );

XQT_EXTERN_API( ComponentResult )
XQT_MCDraw( MovieController mc, WindowRef w );

XQT_EXTERN_API( ComponentResult )
XQT_MCGetClip( MovieController mc, MacRegion*** theClip, MacRegion*** movieClip );

XQT_EXTERN_API( ComponentResult )
XQT_MCIdle( MovieController mc );

XQT_EXTERN_API( ComponentResult )
XQT_MCSetActionFilterWithRefCon( MovieController mc, MCActionFilterWithRefConUPP blob, long refCon );

XQT_EXTERN_API( ComponentResult )
XQT_MCSetClip( MovieController mc, MacRegion** theClip, MacRegion** movieClip );

XQT_EXTERN_API( ComponentResult )
XQT_MCSetControllerAttached( MovieController mc, Boolean attach );

XQT_EXTERN_API( ComponentResult )
XQT_MCSetControllerBoundsRect( MovieController mc, const Rect* bounds );

XQT_EXTERN_API( ComponentResult )
XQT_MCSetControllerPort( MovieController mc, CGrafPtr gp );

XQT_EXTERN_API( CGrafPtr )
XQT_MCGetControllerPort(MovieController mc);

XQT_EXTERN_API( ComponentResult )
XQT_MCSetMovie( MovieController mc, Movie theMovie, WindowRef movieWindow, Point where );

XQT_EXTERN_API( ComponentResult )
XQT_MCSetVisible( MovieController mc, Boolean visible );

XQT_EXTERN_API( void )
XQT_MoviesTask( Movie theMovie, long maxMilliSecToUse );

XQT_EXTERN_API(OSErr)
XQT_NativePathNameToFSSpec( char* inName, FSSpec* outFile, long flags );

XQT_EXTERN_API( OSErr )
XQT_FSSpecToNativePathName( const FSSpec *inFile, char *outName, unsigned long outLen, long flags);

XQT_EXTERN_API( OSErr )
XQT_NewMovieFromFile( Movie* theMovie, short resRefNum, short* resId, StringPtr resName, short newMovieFlags, Boolean* dataRefWasChanged );

XQT_EXTERN_API( ComponentInstance )
XQT_OpenDefaultComponent( OSType type, OSType subType );

// should change the following to require an external translation from pathspec to QT spec - jkc
XQT_EXTERN_API( OSErr )
XQT_OpenMovieFile( const FSSpec* fileSpec, short* resRefNum, SInt8 permission );

XQT_EXTERN_API( OSErr )
XQT_PutMovieIntoTypedHandle(Movie theMovie, Track targetTrack, OSType handleType, Handle publicMovie, 
							TimeValue start, TimeValue dur, long flags, ComponentInstance userComp);

XQT_EXTERN_API( void )
XQT_SetMovieActive( Movie theMovie, Boolean active );

XQT_EXTERN_API( void )
XQT_SetMovieBox( Movie theMovie, const Rect* boxRect );

XQT_EXTERN_API( void )
XQT_SetMovieDisplayClipRgn( Movie theMovie, MacRegion** theClip );

XQT_EXTERN_API( void )
XQT_SetMovieGWorld( Movie theMovie, CGrafPtr port, GDHandle gdh );

XQT_EXTERN_API( void )
XQT_SetMovieMatrix( Movie theMovie, const MatrixRecord* matrix );

XQT_EXTERN_API( void )
XQT_SetMoviePlayHints( Movie theMovie, long flags, long flagsMask );

XQT_EXTERN_API( void )
XQT_SetMovieRate( Movie theMovie, Fixed rate );

XQT_EXTERN_API( void )
XQT_SetMovieTimeValue( Movie theMovie, TimeValue newtime );

XQT_EXTERN_API( void )
XQT_SetMovieVolume( Movie theMovie, short volume );

XQT_EXTERN_API( void )
XQT_SetTimeBaseFlags( TimeBase tb, long timeBaseFlags );

XQT_EXTERN_API( void )
XQT_SetTimeBaseStartTime( TimeBase tb, const TimeRecord* tr );

XQT_EXTERN_API( void )
XQT_SetTimeBaseStopTime( TimeBase tb, const TimeRecord* tr );

XQT_EXTERN_API( OSErr )
XQT_SetupAIFFHeader( short fRefNum, short numChannels, UnsignedFixed sampleRate, short sampleSize, 
					  OSType compressionType, unsigned long numBytes, unsigned long numFrames);

XQT_EXTERN_API( void )
XQT_StartMovie( Movie theMovie );

XQT_EXTERN_API( OSErr )
XQT_UpdateMovie( Movie theMovie );

// QT Windows utility functions

XQT_EXTERN_API( RgnHandle )
XQT_NativeRegionToMacRegion( void *nativeRegion );

XQT_EXTERN_API( void * )
XQT_MacRegionToNativeRegion( RgnHandle macRegion );

XQT_EXTERN_API( void )
XQT_GetMovieNaturalBoundsRect(
  Movie   theMovie,
  Rect *  naturalBounds);

XQT_EXTERN_API( void )
XQT_SetMovieDrawingCompleteProc(
  Movie                     theMovie,
  long                      flags,
  MovieDrawingCompleteUPP   proc,
  long                      refCon);

XQT_EXTERN_API( Fixed )
XQT_FixRatio(short numer, short denom);

#ifdef __cplusplus
}
#endif

#endif // #ifdef USE_ALTURA

#define XQT_NewDataReferenceFromMaxPath(path,name,ref,reftype,err) \
{ \
CFStringRef cfs; \
char tmpname[MAX_PATH_CHARS]; \
char pathname[MAX_PATH_CHARS]; \
(*(err)) = -1; \
(*(ref)) = NULL; \
if (!path_topotentialname(path,name,tmpname,FALSE)) { \
	if (!path_nameconform(tmpname,pathname,PATH_STYLE_NATIVE,PATH_TYPE_PATH)) { \
		cfs = CFStringCreateWithCString(kCFAllocatorDefault,pathname,kCFStringEncodingUTF8);\
		if (cfs) { \
			(*(err)) = QTNewDataReferenceFromFullPathCFString(cfs,XQT_PathStyle,0,ref,reftype); \
			if (*(err)) (*(ref))=NULL; \
			CFRelease(cfs); \
		} \
	} \
} \
}

#define XQT_MaxPathFromDataReference(ref,reftype,path,name,err) \
{ \
CFStringRef cfs; \
char tmpname[MAX_PATH_CHARS]; \
(*(err)) = -1; \
(*(path)) = 0; \
if (!((*(err)) = QTGetDataReferenceFullPathCFString(ref,reftype,XQT_PathStyle,&cfs))) { \
	if (CFStringGetCString(cfs,tmpname,MAX_PATH_CHARS,kCFStringEncodingUTF8)) \
		(*(err)) = path_frompathname(tmpname,path,name); \
	else (*(err)) = -1; \
	CFRelease(cfs); \
} \
}

#ifdef WIN_VERSION
#define SetRect		MacSetRect
#define EqualRect	MacEqualRect
#define FrameRect	MacFrameRect
#define OffsetRect	MacOffsetRect
#endif

#endif // #ifdef C74_USING_QUICKTIME

#endif // #ifndef __XQT_STUBS_H__

