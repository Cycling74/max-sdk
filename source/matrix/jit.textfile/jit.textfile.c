/*
	jit.textfile
	Copyright 2001 - Cycling '74
	Jeremy Bernstein jeremy@bootsquad.com
*/

#include "jit.common.h"
#include "ext_path.h"

#define LB_MAC		0
#define LB_DOS		1
#define LB_UNIX		2

#define IS_LBCHAR(text)	(((text)[0]=='\r')||((text)[0]=='\n'))
#define IS_LBPAIR(text)	(((text)[0]=='\r')&&((text)[1]=='\n'))


typedef struct _jit_textfile
{
	t_object		ob;
	char			autoclear;
	long			text_local;
	long			line;
	t_symbol		*linebreak;
} t_jit_textfile;

t_jit_textfile *jit_textfile_new(void);
void jit_textfile_free(t_jit_textfile *x);
t_jit_err jit_textfile_init(void);
t_jit_err jit_textfile_matrix_calc(t_jit_textfile *x, void *inputs, void *outputs);

// textfile to matrix functions
t_jit_err jit_textfile_tomatrix_adapt(t_jit_textfile *x, void *in_matrix, void *out_matrix);
t_jit_err jit_textfile_tomatrix_nonadapt(t_jit_textfile *x, void *in_matrix, void *out_matrix);
t_jit_err jit_textfile_tomatrix_line(t_jit_textfile *x, void *inputs, void *outputs);

void jit_textfile_packmatrix(t_jit_textfile *x, long dimcount, long *dim,
							 t_jit_matrix_info *info, char *bop);
void jit_textfile_read_char(t_jit_textfile *x, long *dim,
							t_jit_matrix_info *info, char *bop);

// matrix to textfile functions
void jit_textfile_write_char(t_jit_textfile *x, long *dim, t_jit_matrix_info *info, char *bip);
void jit_textfile_write_textfile_ndim(t_jit_textfile *x, long dimcount, long *dim, t_jit_matrix_info *info, char *bip);

void *_jit_textfile_class;
t_symbol *ps_mac,*ps_dos,*ps_unix;

t_jit_err jit_textfile_init(void)
{
	long attrflags=0;
	t_jit_object *attr, *mop;

	_jit_textfile_class = jit_class_new("jit_textfile",(method)jit_textfile_new,(method)jit_textfile_free,
										sizeof(t_jit_textfile),0L);

	mop = jit_object_new(_jit_sym_jit_mop, 1, 2);
	jit_mop_single_type(mop,_jit_sym_char);
	jit_mop_single_planecount(mop,1);
	jit_class_addadornment(_jit_textfile_class, mop);

	jit_class_addmethod(_jit_textfile_class, (method)jit_textfile_matrix_calc, "matrix_calc", A_CANT, 0L);

	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"autoclear",_jit_sym_char,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_textfile,autoclear));
	jit_class_addattr(_jit_textfile_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Auto Clear\"");

	attrflags = JIT_ATTR_GET_OPAQUE_USER | JIT_ATTR_SET_OPAQUE_USER;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"texthandle",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_textfile,text_local));
	jit_class_addattr(_jit_textfile_class,attr);
	attr = jit_object_new(_jit_sym_jit_attr_offset,"jline",_jit_sym_long,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_textfile,line));
	jit_class_addattr(_jit_textfile_class,attr);
	attr = jit_object_new(_jit_sym_jit_attr_offset,"linebreak",_jit_sym_symbol,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_textfile,linebreak));
	jit_class_addattr(_jit_textfile_class,attr);

	//add methods

	jit_class_register(_jit_textfile_class);

	ps_mac = gensym("mac");
	ps_dos = gensym("dos");
	ps_unix = gensym("unix");

	return JIT_ERR_NONE;
}

t_jit_err jit_textfile_matrix_calc(t_jit_textfile *x, void *inputs, void *outputs)
{
	long err = JIT_ERR_NONE;
	long i;
	t_jit_matrix_info info;
	long dimcount, dim[JIT_MATRIX_MAX_DIMCOUNT];
	char *bip;
	long savelock;
	void *in_matrix;

	in_matrix = jit_object_method(inputs,_jit_sym_getindex,0);

	if (x&&in_matrix) {
		savelock = (long) jit_object_method(in_matrix,_jit_sym_lock,1);
		jit_object_method(in_matrix,_jit_sym_getinfo, &info);
		jit_object_method(in_matrix, _jit_sym_getdata, &bip);
		if (!bip) { err=JIT_ERR_INVALID_INPUT; goto out;}

		for (i = 0; i < info.dimcount; i++) {
			dim[i] = info.dim[i];
		}
		dimcount = info.dimcount;

		jit_textfile_write_textfile_ndim(x, dimcount, dim, &info, bip);
	}
	else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	jit_object_method(in_matrix, _jit_sym_lock, savelock);
	return err;
}

void jit_textfile_write_textfile_ndim(t_jit_textfile *x, long dimcount, long *dim, t_jit_matrix_info *info, char *bip)
{
	uchar *ip;
	long i;

	if (dimcount<1) return; //safety

	switch(dimcount) {
	case 1:
		dim[1]=1;
	case 2:
		if (info->type == _jit_sym_char)
			jit_textfile_write_char(x, dim, info, bip);
		break;
	default:
		for	(i = 0; i < dim[dimcount-1]; i++) {
			ip = (uchar *)(bip + i * info->dimstride[dimcount-1]);
			jit_textfile_write_textfile_ndim(x, dimcount-1, dim, info, (char *)ip);
		}
	}
}

void jit_textfile_write_char(t_jit_textfile *x, long *dim, t_jit_matrix_info *info, char *bip)
{
	long i, j, k, width, height, planecount;
	char *ip;
	long size;
	t_handle th;
	char *text;
	long lb;
	long crsize=1;
	char *tmp;
	long len;

	if (x->linebreak==ps_dos)
		lb = LB_DOS;
	else if (x->linebreak==ps_unix)
		lb = LB_UNIX;
	else if (x->linebreak==ps_mac)
		lb = LB_MAC;
	else
#ifdef WIN_VERSION
		lb = LB_DOS;
#else
		lb = LB_MAC;
#endif

	if (lb==LB_DOS)
		crsize = 2;

	width = dim[0];
	height = dim[1];
	planecount = info->planecount;
	th = (t_handle)jit_attr_getlong(x, gensym("texthandle"));
	size = (width * planecount * height) + height*crsize; // extra per row for cr

	// 24.7.2005 jb changed this to write to a temp pointer, get the length of the string
	// resize the handle to the exact size and then copy the data. MLTE doesn't care about
	// terminating 0s and we were getting a lot of garbage displayed in the window.

	if (!th)
		return;
	else
		tmp = sysmem_newptr(size + 1);

	*tmp = '\0';
	text = tmp;

	for (i = 0; i < height; i++) {
		ip = bip + i * info->dimstride[1];
		for (j = 0; j < width; j++) {
			for (k = 0; k < planecount; k++) {
				if (!(*ip)) { // is there a faster way?
					j = width;
					break;
				}
				else
					*text++ = *ip++;
			}
		}
		switch(lb) {
		case LB_MAC:
			*text++ = '\r';
			break;
		case LB_DOS:
			*text++ = '\r';
			*text++ = '\n';
			break;
		case LB_UNIX:
			*text++ = '\n';
			break;
		}
	}
	*text = '\0';

	len = strlen(tmp) + 1;
	sysmem_resizehandle(th, len);
	sysmem_lockhandle(th, 1);
	sysmem_copyptr(tmp, *th, len);
	sysmem_lockhandle(th, 0);
	sysmem_freeptr(tmp);
	x->text_local = (long)th;
}

t_jit_err jit_textfile_tomatrix_nonadapt(t_jit_textfile *x, void *inputs, void *outputs)
{
	long 				err = JIT_ERR_NONE;
	char 				*out_bp;
	long 				savelock, i;
	long 				dim[JIT_MATRIX_MAX_DIMCOUNT], dimcount = 0;
	t_jit_matrix_info 	info;
	void				*out_matrix;

	out_matrix = jit_object_method(outputs,_jit_sym_getindex,0);

	if (x && out_matrix) {

		savelock = (long) jit_object_method(out_matrix,_jit_sym_lock,1);
		jit_object_method(out_matrix,_jit_sym_getinfo,&info);
		jit_object_method(out_matrix,_jit_sym_getdata,&out_bp);
		if (!out_bp) { err=JIT_ERR_INVALID_OUTPUT; goto out;}

		for (i = 0; i < JIT_MATRIX_MAX_DIMCOUNT; i++)
			dim[i] = info.dim[i];

		dimcount = info.dimcount;

		if (x->autoclear)
			jit_object_method(out_matrix, _jit_sym_clear);

		jit_textfile_packmatrix(x, dimcount, dim, &info, out_bp);

out:
		jit_object_method(out_matrix, _jit_sym_lock, savelock);
		return err;
	}
	else return JIT_ERR_INVALID_PTR;
}

t_jit_err jit_textfile_tomatrix_adapt(t_jit_textfile *x, void *inputs, void *outputs)
{
	long 				err = JIT_ERR_NONE;
	char 				*out_bp;
	long 				savelock;
	long 				dim[JIT_MATRIX_MAX_DIMCOUNT], dimcount = 0;
	t_jit_matrix_info 	info;
	void				*out_matrix;
	long				crcount, longline;

	out_matrix = jit_object_method(outputs,_jit_sym_getindex,0);

	if (x && out_matrix) {
		jit_object_method(out_matrix,_jit_sym_getinfo,&info);

		{
			long size;
			long n, loc;
			t_handle th = (t_handle)x->text_local;
			char *text;

			if (!th) return JIT_ERR_NONE;
			text = *th;
			size = sysmem_handlesize((t_handle)x->text_local);

			loc = 0;
			crcount = 0;
			longline = 0;

			for (n = 0; *text && n < size; n++) {
				if (IS_LBCHAR(text)) {
					if (loc > longline)
						longline = loc;
					loc = 0;
					crcount++;
					if (IS_LBPAIR(text))
						text++;
				}
				else {
					loc++;
				}
				text++;
			}
			if (!IS_LBCHAR(text)) { // in case last line not cr terminated
				if (loc > longline)
					longline = loc;
				crcount++;
			}
		}

		if (longline || crcount) {
			dim[0] = info.dim[0] = longline;
			dim[1] = info.dim[1] = crcount;
			dimcount = info.dimcount = 2;
			info.planecount = 1;
			info.type = _jit_sym_char;

			jit_object_method(out_matrix, _jit_sym_setinfo, &info);

			jit_object_method(out_matrix, _jit_sym_getinfo, &info); // this is necessary for some reason

			savelock = (long) jit_object_method(out_matrix,_jit_sym_lock,1);
			jit_object_method(out_matrix,_jit_sym_getdata,&out_bp);
			if (!out_bp) {
				err=JIT_ERR_INVALID_OUTPUT;
				goto oot;
			}

			if (x->autoclear)
				jit_object_method(out_matrix, _jit_sym_clear);
			jit_textfile_packmatrix(x, dimcount, dim, &info, out_bp);

oot:
			jit_object_method(out_matrix, _jit_sym_lock, savelock);
		}
		return err;
	}
	else return JIT_ERR_INVALID_PTR;
}

void jit_textfile_packmatrix(t_jit_textfile *x, long dimcount, long *dim,  t_jit_matrix_info *info, char *bop)
{
	long i;
	char *op;

	if (dimcount<1) return; //safety

	switch(dimcount) {
	case 1:
		dim[1]=1;
	case 2:
		if (info->type == _jit_sym_char)
			jit_textfile_read_char(x, dim, info, bop);
		break;
	default:
		for	(i = 0; i < dim[dimcount-1]; i++) {
			op = bop + i * info->dimstride[dimcount-1];
			jit_textfile_packmatrix(x, dimcount-1, dim, info, op);
		}
	}
}

void jit_textfile_read_char(t_jit_textfile *x, long *dim, t_jit_matrix_info *info, char *bop)
{
	long i, j, k;
	uchar *op;
	long width, height, planecount, bytecount;
	long size;
	uchar *text;
	t_handle th = (t_handle)x->text_local;

	if (!th) return;

	width = dim[0];
	height = dim[1];
	planecount = info->planecount;
	bytecount = sizeof(char) * width * planecount;

	size = sysmem_handlesize(th);
	text = (uchar *)*th;

	if (size) {
		for (i = 0; i < height && size > 0; i++) {
			op = (uchar *)(bop + i * info->dimstride[1]);

			for (j = 0; j < width && size > 0; j++) {
				for (k = 0; k < planecount && size > 0; k++) {
					if (!IS_LBCHAR(text)) {
						*op++ = *text++;
						size--;
					}
					else {
						if (IS_LBPAIR(text)) {
							text++;
							size--;
						}
						text++; //advance past cr if found, and the start new row
						size--;
						goto cont;
					}
				}
			}
			while ((!IS_LBCHAR(text)) && size) { //advance past next cr
				text++;
				size--;
			}
			if (IS_LBPAIR(text)) {
				text++;
				size--;
			}
			text++;
			size--;

cont:
			;
		}
	}
}

t_jit_err jit_textfile_tomatrix_line(t_jit_textfile *x, void *inputs, void *outputs)
{
	long 				err = JIT_ERR_NONE;
	char 				*out_bp;
	long 				savelock, i;
	long 				dim[JIT_MATRIX_MAX_DIMCOUNT], dimcount = 0;
	t_jit_matrix_info 	info;
	void				*out_matrix;
	long				crcount, longline;
	long 				size;
	long 				n, loc;
	long 				linecount = 0;
	char 				*text, *p;
	long				line = x->line;
	t_handle				th;

	if (line < 0)
		return 1;

	out_matrix = jit_object_method(outputs,_jit_sym_getindex,1); //2nd outlet

	if (x && out_matrix) {
		jit_object_method(out_matrix,_jit_sym_getinfo,&info);

		th = (t_handle)x->text_local;
		if (!th) return JIT_ERR_NONE;
		text = *th;
		size = sysmem_handlesize(th);

		n = 0;
		loc = 0;
		crcount = 0;
		longline = 0;

		if (line) {	// cue up to start of line
			for (n = 0; crcount < line && n < size; n++) {
				if (IS_LBCHAR(text)) {
					crcount++;
					if (IS_LBPAIR(text))
						text++;
				}
				text++;
			}
		}

		if (crcount < line)
			return 1; // error - bad line

		p = text;

		while ((!IS_LBCHAR(p)) && *p != '\0' && n++ < size) {
			p++;
			linecount++;
		}
//		linecount++; // add the 0;

		dim[0] = info.dim[0] = linecount;
		dimcount = info.dimcount = 1;
		info.planecount = 1;
		info.type = _jit_sym_char;

		jit_object_method(out_matrix, _jit_sym_setinfo, &info);
		jit_object_method(out_matrix, _jit_sym_getinfo, &info); // this is necessary for some reason

		savelock = (long) jit_object_method(out_matrix,_jit_sym_lock,1);
		jit_object_method(out_matrix,_jit_sym_getdata,&out_bp);
		if (!out_bp) {
			err=JIT_ERR_INVALID_OUTPUT;
			goto oot;
		}

		for (i = 0; i < linecount; i++)
			*out_bp++ = *text++;
//		*out_bp = '\0';

oot:
		jit_object_method(out_matrix, _jit_sym_lock, savelock);
		return err;
	}
	else return JIT_ERR_INVALID_PTR;
}

t_jit_textfile *jit_textfile_new(void)
{
	t_jit_textfile *x;

	if (x=(t_jit_textfile *)jit_object_alloc(_jit_textfile_class)) {
		x->autoclear = 1;
		x->text_local = 0L;
#ifdef WIN_VERSION
		x->linebreak = ps_dos;
#else
		x->linebreak = ps_mac;
#endif

	} else {
		x = NULL;
	}
	return x;
}

void jit_textfile_free(t_jit_textfile *x)
{
	//nada
}