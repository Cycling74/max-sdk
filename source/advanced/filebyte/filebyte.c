/**
 @file
 filebyte - similar to filein.
 Accesses a file on disk and outputs a given byte of the file's data.
 Note that we use the "open" message, not "read", because we're not loading the file into memory.

 updated 3/22/09 ajm: new API

 @ingroup	examples
 */

#include "ext.h"
#include "ext_obex.h"
#include "ext_path.h"

#ifdef MAC_VERSION
#include "ext_strings.h"
#endif

#ifndef MAC_VERSION
// if defined, use windows calls, otherwise use max's cross platform "sysfile" API
#define FILEBYTE_WINDOWS_SPECIFIC
#endif

#ifdef WIN_VERSION
typedef char Byte;
#endif

void *filebyte_class;

typedef struct filebyte {
	t_object f_ob;
#ifdef FILEBYTE_WINDOWS_SPECIFIC
	HANDLE f_fh;
#else // cross platform sysfile calls
	t_filehandle f_fh;
#endif
	short f_open;
	void *f_out;
} t_filebyte;

t_symbol *ps_nothing;

void filebyte_doint(t_filebyte *x, long n);
void filebyte_int(t_filebyte *x, long n);
void filebyte_close(t_filebyte *x);
void filebyte_doopen(t_filebyte *x, t_symbol *s);
void filebyte_open(t_filebyte *x, t_symbol *s);
void filebyte_free(t_filebyte *x);
void filebyte_assist(t_filebyte *x, void *b, long m, long a, char *s);
void *filebyte_new(t_symbol *fn);

void ext_main(void *r)
{
	t_class *c;

	c = class_new("filebyte", (method)filebyte_new, (method)filebyte_free, (short)sizeof(t_filebyte), 0L, A_DEFSYM, 0);
	class_addmethod(c, (method)filebyte_int,	"int",		A_LONG, 0);
	class_addmethod(c, (method)filebyte_close,	"fclose",	0);
	class_addmethod(c, (method)filebyte_open,	"open",		A_DEFSYM,0);
	class_addmethod(c, (method)filebyte_assist,	"assist",	A_CANT,0);
	class_register(CLASS_BOX, c);
	filebyte_class = c;

	ps_nothing = gensym("");
}

void filebyte_doint(t_filebyte *x, long n)		// byte access
{
	Byte		data;
	t_ptr_size	count;
	long		err;

	if (x->f_open) {
#ifdef FILEBYTE_WINDOWS_SPECIFIC
		if (INVALID_SET_FILE_POINTER!=SetFilePointer(x->f_fh,n,NULL,FILE_BEGIN))
			err = 0;
		else
			err = GetLastError();
#else // cross platform sysfile calls
		err = sysfile_setpos(x->f_fh,SYSFILE_FROMSTART,n);
#endif
		if (err)
			object_error((t_object *)x, "seek err %d",err);
		else {
			count = 1;
#ifdef FILEBYTE_WINDOWS_SPECIFIC
			if (ReadFile(x->f_fh,&data,count,(LPDWORD)&count,NULL))
				err = 0;
			else
				err = GetLastError();
#else // cross platform sysfile calls
			err = sysfile_read(x->f_fh,&count,&data);
#endif
			if (err)
				object_error((t_object *)x, "filebyte: read err %d",err);
			else {
				outlet_int(x->f_out,data);
			}
		}
	} else {
		object_error((t_object *)x, "filebyte: no open file");
	}
}

void filebyte_int(t_filebyte *x, long n)
{
	defer_low(x,(method)filebyte_doint,(t_symbol *)n,0,0L); // trick. passing int as symbol
}

void filebyte_close(t_filebyte *x)
{
	if (x->f_open) {
#ifdef FILEBYTE_WINDOWS_SPECIFIC
		CloseHandle(x->f_fh);
#else // cross platform sysfile calls
		sysfile_close(x->f_fh);
#endif
		x->f_fh = 0;
		x->f_open = FALSE;
	}
}

void filebyte_doopen(t_filebyte *x, t_symbol *s)
{
	short		path;
	char		ps[MAX_PATH_CHARS];
#ifdef FILEBYTE_WINDOWS_SPECIFIC
	char	 	ps2[MAX_PATH_CHARS];
#endif
	t_fourcc	type;
	t_max_err	err;

	filebyte_close(x);
	if (s==ps_nothing) {
		if (open_dialog(ps,&path,&type,0L,0))
			return;
	} else {
		strcpy(ps,s->s_name);
		if (locatefile_extended(ps,&path,&type,&type,0)) {
			object_error((t_object *)x, "%s: can't find file",ps);
			return;
		}
	}
#ifdef FILEBYTE_WINDOWS_SPECIFIC
	// convert path + name to pathname
	path_topathname(path,ps,ps2);
	// convert max style pathname to native pathname
	path_nameconform(ps2,ps,PATH_STYLE_NATIVE,PATH_TYPE_ABSOLUTE);
	// open file
	x->f_fh = CreateFile(ps,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
	if (x->f_fh==INVALID_HANDLE_VALUE) {
		x->f_fh = 0;
		err = GetLastError();
	} else {
		err = 0;
	}
#else // cross platform sysfile calls
	err = path_opensysfile(ps,path,&x->f_fh,READ_PERM);
#endif
	if (err) {
		x->f_fh = 0;
		object_error((t_object *)x, "%s: error %d opening file",ps,err);
		return;
	}
	x->f_open = TRUE;
}

void filebyte_open(t_filebyte *x, t_symbol *s)
{
	defer_low(x,(method)filebyte_doopen,s,0,0L);
}

void filebyte_free(t_filebyte *x)
{
	filebyte_close(x);
}

void filebyte_assist(t_filebyte *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)	// inlet
		sprintf(s,"(int) byte in file");
	else	// outlet
		sprintf(s,"(int) byte in file output");
}

void *filebyte_new(t_symbol *fn)
{
	t_filebyte *x;

	x = object_alloc(filebyte_class);
	x->f_out = intout(x);
	x->f_open = FALSE;
	x->f_fh = 0;
	if (fn != ps_nothing) {
		filebyte_doopen(x,fn);
	}
	return (x);
}
