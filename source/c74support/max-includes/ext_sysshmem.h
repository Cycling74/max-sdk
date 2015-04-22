#ifndef _EXT_SYSSHMEM_H_
#define _EXT_SYSSHMEM_H_

BEGIN_USING_C_LINKAGE

// sysshmem is a platform independent interface to shared memory

typedef void *t_sysshmem; 

#define SYSSHMEM_FLAGS_READONLY				(0x00000001)

t_max_err sysshmem_alloc(t_sysshmem *x, const char *name, long size, long flags);	// allocate memory that can be shared
t_max_err sysshmem_open(t_sysshmem *x, const char *name, long flags);				// open memory allocated elsewhere
t_max_err sysshmem_close(t_sysshmem x);		// after this call t_sysshmem handle is no longer valid

unsigned long sysshmem_getsize(t_sysshmem x);		// number of bytes in shared memory block
void* sysshmem_getptr(t_sysshmem x);				// pointer to actual memory

END_USING_C_LINKAGE

#endif // #ifndef _EXT_SYSSHMEM_H_
