#ifndef _EXT_SYSSEM_H_
#define _EXT_SYSSEM_H_

BEGIN_USING_C_LINKAGE

// syssem is a platform independent way of using named semaphores 
// that can be used to synchronize multiple processes

typedef void * t_syssem; 

t_max_err syssem_create(t_syssem *x, const char *name, long flags, unsigned int value);
t_max_err syssem_open(t_syssem *x, const char *name, long flags); 
t_max_err syssem_close(t_syssem x);
t_max_err syssem_wait(t_syssem x);
t_max_err syssem_trywait(t_syssem x);
t_max_err syssem_post(t_syssem x);

END_USING_C_LINKAGE

#endif // #ifndef _EXT_SYSSEM_H_
