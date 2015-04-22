/*
	Copyright 2001-2005 - Cycling '74
	Jeremy Bernstein jeremy@bootsquad.com
*/

//adapt

#include "jit.common.h"
#include "ext_obex.h"
#include "max.jit.mop.h"
#include "ext_path.h"

#define MAC_CR '\r'
#define UNIX_CR '\n'

typedef struct _max_jit_textfile
{
	t_object			ob;
	void				*obex;
	t_filehandle		fh_write;
	t_filehandle		fh_read;
	short				path;
	t_object			*editor;
	t_handle			text;
	t_symbol			*title;
	char				convert;
} t_max_jit_textfile;

t_jit_err jit_textfile_init(void);

void *max_jit_textfile_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_textfile_free(t_max_jit_textfile *x);
void max_jit_textfile_mproc(t_max_jit_textfile *x, void *mop);

void max_jit_textfile_title_set(t_max_jit_textfile *x, void *attr, long ac, t_atom *av);
t_jit_err max_jit_textfile_title_get(t_max_jit_textfile *x, void *attr, long *ac, t_atom **av);

void max_jit_textfile_opentextfile_write(t_max_jit_textfile *x, t_symbol *s, long ac, t_atom *av);
void max_jit_textfile_opentextfile_read(t_max_jit_textfile *x, t_symbol *s, long ac, t_atom *av);
t_jit_err max_jit_textfile_closetextfile_write(t_max_jit_textfile *x);
t_jit_err max_jit_textfile_closetextfile_read(t_max_jit_textfile *x);
void max_jit_textfile_defaultdir_set(t_max_jit_textfile *x, t_symbol *s, long ac, t_atom *av);
t_jit_err max_jit_textfile_defaultdir_get(t_max_jit_textfile *x, void *attr, long *ac, t_atom **av);
t_jit_err max_jit_textfile_read(t_max_jit_textfile *x);

void max_jit_textfile_bang(t_max_jit_textfile *x);
void max_jit_textfile_dblclick(t_max_jit_textfile *x);
void max_jit_textfile_wclose(t_max_jit_textfile *x);
void max_jit_textfile_edclose(t_max_jit_textfile *x, char **text, long size);
void *max_jit_textfile_edsave(t_max_jit_textfile *x, char **text, long size, char *filename, short vol);
void max_jit_textfile_okclose(t_max_jit_textfile *x, char *prompt, short *result);
void max_jit_textfile_erase(t_max_jit_textfile *x);

t_jit_err max_jit_textfile_outputline(void *x);
t_jit_err max_jit_textfile_outputmatrix(void *x);
void max_jit_textfile_line(t_max_jit_textfile *x, t_symbol *s, long ac, t_atom *av);

t_jit_err max_jit_textfile_tobuffer(t_max_jit_textfile *x);
void max_jit_textfile_frombuffer(t_max_jit_textfile *x);
void max_jit_textfile_convert_breaks(t_max_jit_textfile *x);

void jit_textfile_tomatrix_nonadapt(void *x, void *inputs, void *outputs);
void jit_textfile_tomatrix_adapt(void *x, void *inputs, void *outputs);
t_jit_err jit_textfile_tomatrix_line(void *x, void *inputs, void *outputs);

void *max_jit_textfile_class;

void ext_main(void *r)
{
	long attrflags;
	void *p,*q,*attr;

	jit_textfile_init();
	setup((t_messlist **)&max_jit_textfile_class, (method)max_jit_textfile_new, (method)max_jit_textfile_free, (short)sizeof(t_max_jit_textfile),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_textfile,obex));
	q = jit_class_findbyname(gensym("jit_textfile"));
	max_jit_classex_mop_wrap(p,q,MAX_JIT_MOP_FLAGS_OWN_BANG | MAX_JIT_MOP_FLAGS_OWN_OUTPUTMATRIX);//MAX_JIT_MOP_FLAGS_OWN_ADAPT); //custom bang/outputmatrix
	max_jit_classex_mop_mproc(p,q,max_jit_textfile_mproc); 	//custom mproc
	max_jit_classex_standard_wrap(p,q,0);

	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"defaultdir",_jit_sym_symbol,attrflags,
						  (method)max_jit_textfile_defaultdir_get,(method)max_jit_textfile_defaultdir_set,0L);
	max_jit_classex_addattr(p,attr);
	attr = jit_object_new(_jit_sym_jit_attr_offset,"title",_jit_sym_symbol,attrflags,
						  (method)max_jit_textfile_title_get,(method)max_jit_textfile_title_set,0L);
	max_jit_classex_addattr(p,attr);
	attr = jit_object_new(_jit_sym_jit_attr_offset,"convert",_jit_sym_char,attrflags,
						  (method)0L,(method)0L,calcoffset(t_max_jit_textfile, convert));
	max_jit_classex_addattr(p,attr);

	addmess((method)max_jit_mop_assist,						"assist",	A_CANT,0);

	addbang((method)max_jit_textfile_bang);
	addmess((method)max_jit_textfile_okclose,				"okclose",	A_CANT,0);
	addmess((method)max_jit_textfile_dblclick,				"dblclick",	A_CANT,0);
	addmess((method)max_jit_textfile_edsave,				"edsave",	A_CANT,0);
	addmess((method)max_jit_textfile_edclose,				"edclose",	A_CANT,0);
	addmess((method)max_jit_textfile_opentextfile_read,		"read",		A_GIMME,0);
	addmess((method)max_jit_textfile_opentextfile_write,	"write",	A_GIMME,0);
	addmess((method)max_jit_textfile_dblclick,				"open",		0);
	addmess((method)max_jit_textfile_erase,					"erase",	0);
	addmess((method)max_jit_textfile_wclose,				"wclose",	0);

	max_addmethod_usurp_low((method)max_jit_textfile_outputline,	"outputline");
	max_addmethod_usurp_low((method)max_jit_textfile_outputmatrix,	"outputmatrix");
	max_addmethod_defer_low((method)max_jit_textfile_line,			"line");

	return 0;
}

t_jit_err max_jit_textfile_outputline(void *x)
{
	t_atom a;
	void *mop,*p,*o;
	long outputmode;

	if (!(mop=max_jit_obex_adornment_get(x,_jit_sym_jit_mop)))
		return JIT_ERR_GENERIC;

//	outcount   = jit_attr_getlong(mop,_jit_sym_outputcount);
	outputmode = jit_attr_getlong(mop,_jit_sym_outputmode);

	if (outputmode) { //always output unless output mode is none
		if ((p=jit_object_method(mop,_jit_sym_getoutput, 2)) &&
				(o=max_jit_mop_io_getoutlet(p)))
		{
			jit_atom_setsym(&a,jit_attr_getsym(p,_jit_sym_matrixname));
			outlet_anything(o,_jit_sym_jit_matrix,1,&a);
		}
	}

	return JIT_ERR_NONE;
}

t_jit_err max_jit_textfile_outputmatrix(void *x)
{
	t_atom a;
	void *mop,*p,*o;
	long outputmode;

	if (!(mop=max_jit_obex_adornment_get(x,_jit_sym_jit_mop)))
		return JIT_ERR_GENERIC;

//	outcount   = jit_attr_getlong(mop,_jit_sym_outputcount);
	outputmode = jit_attr_getlong(mop,_jit_sym_outputmode);

	if (outputmode) { //always output unless output mode is none
		if ((p=jit_object_method(mop,_jit_sym_getoutput, 1)) &&
				(o=max_jit_mop_io_getoutlet(p)))
		{
			jit_atom_setsym(&a,jit_attr_getsym(p,_jit_sym_matrixname));
			outlet_anything(o,_jit_sym_jit_matrix,1,&a);
		}
	}

	return JIT_ERR_NONE;
}

void max_jit_textfile_line(t_max_jit_textfile *x, t_symbol *s, long ac, t_atom *av)
{
	void *mop;

	if (ac && av) {
		jit_attr_setlong(max_jit_obex_jitob_get(x), gensym("jline"), jit_atom_getlong(av));
		jit_attr_setlong(max_jit_obex_jitob_get(x), gensym("texthandle"), (long)x->text);

		mop = max_jit_obex_adornment_get(x, _jit_sym_jit_mop);

		if (jit_textfile_tomatrix_line(max_jit_obex_jitob_get(x),
									   jit_object_method(mop, _jit_sym_getinputlist),
									   jit_object_method(mop, _jit_sym_getoutputlist)))
			jit_object_error((t_object *)x,"jit.textfile: bad line");
		else
			typedmess((t_object *)x, gensym("outputline"),0,0L);
	}
}

t_jit_err max_jit_textfile_title_get(t_max_jit_textfile *x, void *attr, long *ac, t_atom **av)
{
	if (x) {
		if ((*ac)&&(*av)) {
			//memory passed in, use it
		} else {
			//otherwise allocate memory
			*ac = 0;
			if (!(*av = jit_getbytes(sizeof(t_atom))))
				return JIT_ERR_OUT_OF_MEM;
		}
		*ac = 1;

		if (x->title)
			jit_atom_setsym(*av, x->title);
		else
			jit_atom_setsym(*av, gensym("<none>"));

		return JIT_ERR_NONE;
	}
	return JIT_ERR_INVALID_PTR;
}

void max_jit_textfile_title_set(t_max_jit_textfile *x, void *attr, long ac, t_atom *av)
{
	if (ac && av)
		x->title = jit_atom_getsym(av);
	else
		x->title = NULL;
}

void max_jit_textfile_bang(t_max_jit_textfile *x)
{
	void *mop;
	long adapt;

	mop = max_jit_obex_adornment_get(x,_jit_sym_jit_mop);

	jit_attr_setlong(max_jit_obex_jitob_get(x), gensym("texthandle"), (long)x->text);

//	jit_object_post((t_object *)x,"pointer %x, size %d", *(x->text), x->textsize);
	adapt = (long)jit_attr_getlong(mop, gensym("adapt"));

//	jit_attr_setlong(max_jit_obex_jitob_get(x), gensym("adaptflag"), adapt);

	if (adapt) {
		jit_textfile_tomatrix_adapt(max_jit_obex_jitob_get(x),
									jit_object_method(mop,_jit_sym_getinputlist),
									jit_object_method(mop,_jit_sym_getoutputlist));
	}
	else {
		jit_textfile_tomatrix_nonadapt(max_jit_obex_jitob_get(x),
									   jit_object_method(mop,_jit_sym_getinputlist),
									   jit_object_method(mop,_jit_sym_getoutputlist));
	}

	max_jit_mop_bang(x);
}

void max_jit_textfile_mproc(t_max_jit_textfile *x, void *mop)
{
	t_jit_err err;

	if (!x->text)
		x->text = sysmem_newhandle(0);

	jit_attr_setlong(max_jit_obex_jitob_get(x), gensym("texthandle"), (long)x->text);

	if (err=(t_jit_err) jit_object_method(
				max_jit_obex_jitob_get(x),
				_jit_sym_matrix_calc,
				jit_object_method(mop,_jit_sym_getinputlist),
				jit_object_method(mop,_jit_sym_getoutputlist)))
	{
		jit_error_code(x,err);
	}

	x->text = (t_handle)jit_attr_getlong(max_jit_obex_jitob_get(x), gensym("texthandle"));
}

void max_jit_textfile_okclose(t_max_jit_textfile *x, char *prompt, short *result)
{
	*result = 3;
}



void max_jit_textfile_edclose(t_max_jit_textfile *x, char **text, long size)
{
	if (x->text)
		sysmem_resizehandle(x->text, size);
	else
		x->text = sysmem_newhandle(size);

	sysmem_lockhandle(x->text, 1);
	jit_copy_bytes(*(x->text), *text, size);
	sysmem_lockhandle(x->text, 0);

	x->editor = 0;
}


void *max_jit_textfile_edsave(t_max_jit_textfile *x, char **text, long size, char *filename, short vol)
{
	return 0;
}


void max_jit_textfile_wclose(t_max_jit_textfile *x)
{
	if (x->editor)
		object_method(x->editor, gensym("wclose"));
}

void max_jit_textfile_dblclick(t_max_jit_textfile *x)
{
	if (x->editor) {
		object_attr_setchar(x->editor, gensym("visible"), 1);
	}
	else {
		x->editor = object_new(CLASS_NOBOX, gensym("jed"), x, 0);
		if (!x->editor)
			return;
	}

	if (x->title)
		object_attr_setsym(x->editor, gensym("title"), x->title);

	if (x->text) {
		object_attr_setchar(x->editor, gensym("scratch"), 1); // what does this do?
		sysmem_nullterminatehandle(x->text);
		object_method(x->editor, gensym("settext"), *(x->text), gensym("utf-8"));
	}
}

void max_jit_textfile_erase(t_max_jit_textfile *x)
{
	if (x->text) {
		sysmem_freehandle(x->text);
		x->text = NULL;
	}
}

void max_jit_textfile_opentextfile_write(t_max_jit_textfile *x, t_symbol *s, long ac, t_atom *av)
{
	char filename[MAX_PATH_CHARS] = "matrixtextfile.txt";
	char tempname[MAX_PATH_CHARS];
	short path=0, err;
	t_fourcc type = FOUR_CHAR_CODE('TEXT');
	t_filehandle fh_write;
	t_symbol *name;

	if (av && ac) {
		name = jit_atom_getsym(av);
		strcpy(tempname,name->s_name);
		if (path_frompotentialpathname(tempname, &path, filename)) {
			strcpy(filename,name->s_name);
			path = x->path;
		}
	}
	else if (saveasdialog_extended(filename, &path, &type, &type, 1))
		return;

	if (err = path_createsysfile(filename, path, type, &fh_write)) {
		jit_object_error((t_object *)x,"jit.textfile: %s: error %d creating file", filename, err);
		return;
	}

	x->path = path;
	x->fh_write = fh_write;

	max_jit_textfile_frombuffer(x);
	max_jit_textfile_closetextfile_write(x);
}

void max_jit_textfile_frombuffer(t_max_jit_textfile *x)
{
	long err;
	t_ptr_size size;

	if (x && x->fh_write) {

		if (x->convert) {
			err = sysfile_writetextfile(x->fh_write, x->text, TEXT_LB_NATIVE);
			if (err)
				jit_object_error((t_object *)x,"jit.textfile: error reading from file: %d", err);
		} else {
			size = sysmem_handlesize(x->text);

			err = sysfile_write(x->fh_write, &size, *(x->text));
			if (err)
				jit_object_error((t_object *)x,"jit.textfile: error writing to file: %d", err);

			if (size != sysmem_handlesize(x->text))
				jit_object_error((t_object *)x,"jit.textfile: could not write entire file");
		}
	}
}

t_jit_err max_jit_textfile_closetextfile_write(t_max_jit_textfile *x)
{
	long err = 0;
	t_ptr_size position;
	t_atom a[2];

	sysfile_getpos(x->fh_write, &position);
	sysfile_seteof(x->fh_write, position);
	if (err = sysfile_close(x->fh_write)) {
		jit_atom_setlong(&a[0], 0);
		jit_atom_setlong(&a[1], err);
		max_jit_obex_dumpout(x, gensym("write"), 2, a);
	} else {
		jit_atom_setlong(&a[0], 1);
		jit_atom_setlong(&a[1], position);
		max_jit_obex_dumpout(x, gensym("write"), 2, a);
//		jit_object_post((t_object *)x,"jit.textfile: file closed, %d bytes written", position);
	}
	return err;
}

void max_jit_textfile_defaultdir_set(t_max_jit_textfile *x, t_symbol *s, long ac, t_atom *av)
{
	char 		filename[256] = "press save to choose directory";
	short 		path;
	t_symbol 	*temp;
	t_fourcc	tmptype = 0L;

	if (ac && av) {
		temp = jit_atom_getsym(av);
		if (path_frompathname(temp->s_name, &path, filename)) {
			jit_object_error((t_object *)x,"jit.uldl: could not set directory to %s", temp->s_name);
			return;
		}
	}
	else {
		if (saveasdialog_extended(filename, &path, &tmptype, &tmptype, 0))
			return;
	}

	x->path = path;
}

t_jit_err max_jit_textfile_defaultdir_get(t_max_jit_textfile *x, void *attr, long *ac, t_atom **av)
{
	char outputstring[MAX_PATH_CHARS] = "";

	if (x) {
		if ((*ac)&&(*av)) {
			//memory passed in, use it
		} else {
			//otherwise allocate memory
			*ac = 0;
			if (!(*av = jit_getbytes(sizeof(t_atom))))
				return JIT_ERR_OUT_OF_MEM;
		}
		*ac = 1;

		if (path_topathname(x->path, "", outputstring)) {
			jit_object_error((t_object *)x,"jit.textfile: could not get default directory");
			return JIT_ERR_GENERIC;		// $rbs$ -- warning fix
		}

		jit_atom_setsym(*av,gensym(outputstring));

		return JIT_ERR_NONE;
	}
	return JIT_ERR_INVALID_PTR;
}

void max_jit_textfile_opentextfile_read(t_max_jit_textfile *x, t_symbol *s, long ac, t_atom *av)
{
	char 				inputstring[MAX_PATH_CHARS] = "";
	char 				filename[MAX_PATH_CHARS] = "matrixtextfile.txt";
	short 				path, err;
	t_fourcc 			type = FOUR_CHAR_CODE('TEXT'), outtype;
	t_filehandle 		fh_read;
	t_symbol			*insym;
	t_atom				a[2];
	long				rv = 1;

	if (av && ac) {
		insym = jit_atom_getsym(av);
		strcpy(inputstring, insym->s_name);
		if (path_frompathname(inputstring, &path, filename)) {
			strcpy(filename, inputstring);
			if (locatefile_extended(filename, &path, &outtype, &type, 1)) {
				jit_object_error((t_object *)x,"jit.textfile: file not found");
				rv = 0;
				goto out;
			}
		}
	}
	else if (open_dialog(filename, &path, &outtype, &type, 1)) {
		strcpy(filename, "<none>");
		rv =  0;
		goto out;
	}

	if (err = path_opensysfile(filename, path, &fh_read, READ_PERM)) {
		jit_object_error((t_object *)x,"%s: error %d opening file", filename, err);
		rv = 0;
		goto out;
	}

	x->fh_read = fh_read;

	if (max_jit_textfile_read(x) != JIT_ERR_NONE)
		rv = 0;

out:
	atom_setsym(a, gensym(filename));
	atom_setlong(a+1, rv);
	max_jit_obex_dumpout(x, gensym("read"), 2, a);
}


t_jit_err max_jit_textfile_closetextfile_read(t_max_jit_textfile *x)
{
	long err = 0;

	if (err = sysfile_close(x->fh_read)) {
		jit_object_error((t_object *)x,"jit.textfile: error closing file: %d", err);
	}

	return err;
}

t_jit_err max_jit_textfile_read(t_max_jit_textfile *x)
{
	t_jit_err rv;

	rv = max_jit_textfile_tobuffer(x);
	// we don't care about closing errors for outlet reporting
	max_jit_textfile_closetextfile_read(x);
	return rv;
}

t_jit_err max_jit_textfile_tobuffer(t_max_jit_textfile *x)
{
	t_ptr_size count;
	long err;
	t_ptr_size eof;

	if (x && x->fh_read) {
		sysfile_geteof(x->fh_read, &eof);

		if (x->text)
			sysmem_resizehandle(x->text, eof);
		else
			x->text = sysmem_newhandle(eof);

		if (x->convert) {
			err = sysfile_readtextfile(x->fh_read, x->text, 0, TEXT_LB_NATIVE);
			if (err)
				jit_object_error((t_object *)x,"jit.textfile: error reading from file: %d", err);
		} else {
			sysfile_geteof(x->fh_read, &eof);
			count = eof;
			sysmem_lockhandle(x->text, 1);
			err = sysfile_read(x->fh_read, &count, *(x->text));
			if (err)
				jit_object_error((t_object *)x,"jit.textfile: error reading from file: %d", err);

			if (count != eof)
				jit_object_error((t_object *)x,"jit.textfile: could not read entire file");
			sysmem_lockhandle(x->text, 0);
		}
	}
	return (err ? JIT_ERR_GENERIC : JIT_ERR_NONE);
}

/*
void max_jit_textfile_convert_breaks(t_max_jit_textfile *x)
{
	long i, j, textsize;
	char *text, *tmp;

	if (x && x->text && (textsize = jit_handle_size_get(x->text))) {
		jit_handle_lock(x->text, 1);
		text = *(x->text); // gets incremented
		tmp = *(x->text); // doesn't

		for (i = 0; i < textsize; i++) {
			if (*text == MAC_CR) {
				if (*(text + 1) == UNIX_CR) { // it's a DOS CR
					text++; // move past the mac_cr
					for (j = i + 1; j < textsize - 1; j++)
						tmp[j] = tmp[j + 1]; // shift chars over
					textsize--; // decrement textsize
				}
			}
			else if (*text == UNIX_CR)
				*text++ = MAC_CR;
			else
				text++;
		}
		jit_handle_lock(x->text, 0);
		if (textsize != jit_handle_size_get(x->text)) // DOS CRs were replaced
			jit_handle_size_set(x->text, textsize);
	}
}
*/

void max_jit_textfile_free(t_max_jit_textfile *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	if (x->editor)
		object_free(x->editor);
	if (x->text) {
		sysmem_freehandle(x->text);
		x->text = NULL;
	}
	max_jit_obex_free(x);
}

void *max_jit_textfile_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_textfile *x;
	void *o;

	if (x=(t_max_jit_textfile *)max_jit_obex_new(max_jit_textfile_class,gensym("jit_textfile"))) {
		x->editor = NULL;
		x->text = NULL;
		if (o=jit_object_new(gensym("jit_textfile"))) {
			max_jit_mop_setup_simple(x,o,argc,argv);
			//add additional non-matrix outputs
			x->fh_write = 0;
			x->fh_read = 0;
			x->path = path_getdefault();
			x->editor = 0;
			x->title = NULL;
			x->convert = 1;
			x->text = NULL;
			max_jit_attr_args(x,argc,argv);
		} else {
			jit_object_error((t_object *)x,"jit.textfile: could not allocate object");
			freeobject((t_object *)x);
			x = NULL;
		}
	}
	return (x);
}