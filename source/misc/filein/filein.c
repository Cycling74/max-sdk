/**
 @file
 filein - read in a file of binary data and output the data at various points in the file

 updated 3/22/09 ajm: new API

 @ingroup	examples
 */

#include "ext.h"
#include "ext_obex.h"
#include "ext_path.h"

void *filein_class;

typedef struct filein {
	t_object f_ob;
	t_filehandle f_fh;
	short f_open;			/* spool flag */
	short f_spool;
	t_handle f_data;			/* read in data */
	t_ptr_size f_size;
	void *f_out;
	void *f_eof;
	void *f_readdone;
} t_filein;

t_symbol *ps_nothing,*ps_spool,*ps_int,*ps_in1,*ps_in2;

void filein_access(t_filein *x, t_symbol *s, long ac, t_atom *av);
void filein_int(t_filein *x, t_atom_long n);
void filein_in1(t_filein *x, t_atom_long n);
void filein_in2(t_filein *x, t_atom_long n);
void filein_close(t_filein *x);
void filein_open(t_filein *x, char *name);
void filein_doread(t_filein *x, t_symbol *s);
void filein_spool(t_filein *x, t_symbol *s);
void filein_read(t_filein *x, t_symbol *s);
void filein_free(t_filein *x);
void filein_assist(t_filein *x, void *b, long m, long a, char *s);
void *filein_new(t_symbol *fn, t_symbol *spoolFlag);

C74_EXPORT void ext_main(void *r)
{
	t_class *c;

	c = class_new("filein", (method)filein_new, (method)filein_free, (short)sizeof(t_filein),
				  0L, A_DEFSYM, A_DEFSYM, 0);
	class_addmethod(c, (method)filein_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)filein_in1,		"in1",		A_LONG, 0);
	class_addmethod(c, (method)filein_in2,		"in2",		A_LONG, 0);
	class_addmethod(c, (method)filein_close,	"fclose",	0);
	class_addmethod(c, (method)filein_spool,	"spool",	A_DEFSYM,0);
	class_addmethod(c, (method)filein_read,		"read",		A_DEFSYM,0);
	class_addmethod(c, (method)filein_assist,	"assist",	A_CANT,0);
	class_register(CLASS_BOX, c);
	filein_class = c;

	ps_nothing = gensym("");
	ps_spool = gensym("spool");
	ps_int = gensym("int");
	ps_in1 = gensym("in1");
	ps_in2 = gensym("in2");

	return;
}

static t_atom_long get_value_for_data(const char* data, t_symbol *s)
{
	t_atom_long value;
	if (s == ps_int) {
		const t_uint8 *pd = (const t_uint8*) data;
		value = *pd;
	}
	else if (s == ps_in1) {
		const t_uint16 *pd = (const t_uint16*) data;
		value = *pd;
	}
	else if (s == ps_in2) {
		const t_uint32 *pd = (const t_uint32*) data;
		value = *pd;
	}
	else {
		C74_ASSERT(false);
		value = 0;
	}
	return value;
}

static int get_data_size_for_symbol(t_symbol *s)
{
	if (s == ps_int) {
		return 1;
	}
	else if (s == ps_in1) {
		return 2;
	}
	else if (s == ps_in2) {
		return 4;
	}
	C74_ASSERT(false);
	return 0;
}

void filein_access(t_filein *x, t_symbol *s, long ac, t_atom *av)
{
	t_atom_long n = atom_getlong(av);
	const t_ptr_size datasize = get_data_size_for_symbol(s);

	if (x->f_open) {
		if (systhread_istimerthread()) {
			defer(x, (method) filein_access, s, ac, av);
		} else {
			t_max_err err = sysfile_setpos(x->f_fh,SYSFILE_FROMSTART,n);
			if (err)
				object_error((t_object *)x, "seek err %d",err);
			else {
				char data[8] = { 0 };
				t_ptr_size count = datasize;
				sysfile_read(x->f_fh, &count, data);
				if (count < datasize) {
					outlet_bang(x->f_eof);
				}
				else {
					t_atom_long value = get_value_for_data(data, s);
					outlet_int(x->f_out, value);
				}
			}
		}
	} else if (x->f_data) {
		if (n < 0)
			object_error((t_object *)x, "access out of range");
		else if (n+datasize > x->f_size)
			outlet_bang(x->f_eof);
		else {
			const char* pd = (*(x->f_data)) + n;
			t_atom_long value = get_value_for_data(pd, s);
			outlet_int(x->f_out, value);
		}
	}
}

void filein_int(t_filein *x, t_atom_long n)		/* byte access */
{
	t_atom a;
	
	atom_setlong(&a, n);
	filein_access(x, ps_int, 1, &a);
}

void filein_in1(t_filein *x, t_atom_long n)		/* int access */
{
	t_atom a;
	
	atom_setlong(&a, n);
	filein_access(x, ps_in1, 1, &a);
}

void filein_in2(t_filein *x, t_atom_long n)		/* long access */
{
	t_atom a;
	
	atom_setlong(&a, n);
	filein_access(x, ps_in2, 1, &a);
}

void filein_close(t_filein *x)
{
	if (x->f_open) {
		sysfile_close(x->f_fh);
		x->f_fh = 0;
		x->f_open = FALSE;
	}
	if (x->f_data) {
		sysmem_lockhandle(x->f_data,0);
		sysmem_freehandle(x->f_data);
		x->f_data = 0;
	}
}

void filein_open(t_filein *x, char *name)
{
	t_ptr_size size;

	if (x->f_spool)
		x->f_open = TRUE;
	else {
		sysfile_geteof(x->f_fh,&size);
		if (!(x->f_data = sysmem_newhandle(size)))
			object_error((t_object *)x, "%s too big to read",name);
		else {
			sysmem_lockhandle(x->f_data,1);
			sysfile_read(x->f_fh,&size,*x->f_data);
			x->f_size = size;
		}
		sysfile_close(x->f_fh);
	}
	x->f_spool = FALSE;
}

void filein_doread(t_filein *x, t_symbol *s)
{
	short vol,err;
	char ps[MAX_PATH_CHARS];
	t_fourcc type;

	filein_close(x);
	if (s==ps_nothing) {
		if (open_dialog(ps,&vol,&type,0L,0))
			return;
	} else {
		strcpy(ps,s->s_name);
		if (locatefile_extended(ps,&vol,&type,&type,0)) {
			object_error((t_object *)x, "%s: can't find file",ps);
			return;
		}
	}
	err = path_opensysfile(ps,vol,&x->f_fh,READ_PERM);
	if (err) {
		object_error((t_object *)x, "%s: error %d opening file",ps,err);
		return;
	}
	filein_open(x,ps);
	outlet_bang(x->f_readdone);
}

void filein_spool(t_filein *x, t_symbol *s)
{
	x->f_spool = TRUE;
	defer(x,(method)filein_doread,s,0,0L);
}

void filein_read(t_filein *x, t_symbol *s)
{
	x->f_spool = FALSE;
	defer(x,(method)filein_doread,s,0,0L);
}

void filein_free(t_filein *x)
{
	filein_close(x);
}

void filein_assist(t_filein *x, void *b, long m, long a, char *s)
{
	// this system eliminates the need for a STR# resource
	if (m==1) {
		switch (a) {
		case 0: sprintf(s,"Read 8 bit unsigned integer from File"); break;
		case 1: sprintf(s,"Read 16 bit unsigned integer from File"); break;
		case 2: sprintf(s,"Read 32 bit unsigned integer from File"); break;
		}
	}
	else if (m==2) {
		switch (a) {
		case 0: sprintf(s,"File Data Output"); break;
		case 1: sprintf(s,"bang On End of File"); break;
		case 2: sprintf(s,"bang When Read/Spool Finished"); break;
		}
	}
}


void *filein_new(t_symbol *fn, t_symbol *spoolFlag)
{
	t_filein *x;

	x = object_alloc(filein_class);
	x->f_readdone = bangout(x);
	x->f_eof = bangout(x);
	x->f_out = intout(x);
	intin(x,2);
	intin(x,1);
	x->f_open = FALSE;
	x->f_fh = 0;
	x->f_spool = 0;
	x->f_data = 0;
	if (fn != ps_nothing) {
		if (spoolFlag==ps_spool)
			x->f_spool = TRUE;
		else
			x->f_spool = FALSE;
		filein_doread(x,fn);
	}
	return (x);
}
