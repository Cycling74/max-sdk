#ifndef _EXT_SYSPROCESS_H_
#define _EXT_SYSPROCESS_H_

#include "ext_prefix.h"
#include "ext_mess.h"

BEGIN_USING_C_LINKAGE

enum {
	SYSPROCESS_LAUNCHFLAGS_NONE = 0,
	SYSPROCESS_LAUNCHFLAGS_NOWINDOW					= 0x01,
	SYSPROCESS_LAUNCHFLAGS_NOWINDOW_ALLOWDIALOGS	= 0x02
};

// returns process id or 0 on error
long sysprocess_launch(const char *utf8path, const char *utf8commandline);

// returns process id or 0 on error
long sysprocess_launch_withflags(const char *utf8path, const char *utf8commandline, long flags);

// returns non-zero if process is still running
long sysprocess_isrunning(long id);

// returns non-zero if process is still running, optional non-running process return value in 'retval' argument
// note that return value will only work reliably the first time the function is called on a terminated process
long sysprocess_isrunning_with_returnvalue(long id, long *retval);

// kill a running process (SIGKILL), returns 0 if successful
long sysprocess_kill(long id);

// returns 0 if successful
long sysprocess_activate(long id);

// returns 0 if process isn't running
long sysprocess_getid(const char *utf8path);  // find the process id for a given app

// returns the id of the currently running process
long sysprocess_getcurrentid(void); 

// given process ID returns path as utf8 string
// note: you must free the returned memory with sysmem_freeptr()
long sysprocess_getpath(long id, char **utf8path);

// sysprocesswatcher: monitors process with given id and if process quits calls given method with arg.
// note: method is called on a separate thread so you can possibly free a stalled main thread.
// If you are done then free the sysprocesswatcher with object_free() and the monitoring thread will be killed.  
t_object* sysprocesswatcher_new(long id, method m, void *arg);

// determines if the architecture of the named process (x64 or i386) fits the current one
long sysprocess_fitsarch(long id);

END_USING_C_LINKAGE

#endif // _EXT_SYSPROCESS_H_
