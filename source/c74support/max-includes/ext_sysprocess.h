#ifndef _SYSPROCESS_H_
#define _SYSPROCESS_H_

BEGIN_USING_C_LINKAGE

// returns non-zero if process is still running
long sysprocess_isrunning(long id);   

// returns process id or 0 on error
long sysprocess_launch(const char *utf8path, const char *utf8commandline);  

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

#endif // _SYSPROCESS_H_
