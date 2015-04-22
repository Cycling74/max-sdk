
/* 
	jit.file.h
	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com

	- platform independent file calls
*/

#ifndef _JIT_FILE_H_
#define _JIT_FILE_H_

typedef long t_jit_fileref;

#ifdef __cplusplus
extern "C" {
#endif

t_jit_err jit_file_fsclose(t_jit_fileref refnum);
t_jit_err jit_file_fsread(t_jit_fileref refnum, long *count, void *bufptr);
t_jit_err jit_file_fswrite(t_jit_fileref refnum, long *count, const void *bufptr);
t_jit_err jit_file_seteof(t_jit_fileref refnum, long logeof);
t_jit_err jit_file_geteof(t_jit_fileref refnum, long *logeof);
t_jit_err jit_file_setfpos(t_jit_fileref refnum, long mode, long offset);
t_jit_err jit_file_getfpos(t_jit_fileref refnum, long *filepos);


#ifdef __cplusplus
}
#endif

#endif /* _JIT_FILE_H_ */
