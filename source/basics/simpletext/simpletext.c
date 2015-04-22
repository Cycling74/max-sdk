/**
	@file
	simpletext - show use of text reading and editing

	@ingroup	examples
*/

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object


////////////////////////// object struct
typedef struct _simpletext
{
	t_object ob;			// the object itself (must be first)
	t_object *t_editor;
	char **t_text;
	long t_size;
} t_simpletext;

///////////////////////// function prototypes
//// standard set
void *simpletext_new(t_symbol *s, long argc, t_atom *argv);
void simpletext_free(t_simpletext *x);
void simpletext_assist(t_simpletext *x, void *b, long m, long a, char *s);
void simpletext_read(t_simpletext *x, t_symbol *s);
void simpletext_doread(t_simpletext *x, t_symbol *s, long argc, t_atom *argv);
void simpletext_dblclick(t_simpletext *x);
void simpletext_edclose(t_simpletext *x, char **text, long size);
//////////////////////// global class pointer variable
void *simpletext_class;


void ext_main(void *r)
{
	t_class *c;

	c = class_new("simpletext", (method)simpletext_new, (method)simpletext_free, (long)sizeof(t_simpletext),
				  0L, A_GIMME, 0);

	class_addmethod(c, (method)simpletext_read,			"read",		A_DEFSYM, 0);
	class_addmethod(c, (method)simpletext_dblclick,		"dblclick",	A_CANT, 0);
	class_addmethod(c, (method)simpletext_edclose,		"edclose",	A_CANT, 0);

	class_register(CLASS_BOX, c);
	simpletext_class = c;
}

void simpletext_assist(t_simpletext *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
		sprintf(s, "Message In");
}

void simpletext_free(t_simpletext *x)
{
	if (x->t_text)
		sysmem_freehandle(x->t_text);
}

void simpletext_read(t_simpletext *x, t_symbol *s)
{
	defer((t_object *)x, (method)simpletext_doread, s, 0, NULL);
}

void simpletext_dblclick(t_simpletext *x)
{
	if (x->t_editor)
		object_attr_setchar(x->t_editor, gensym("visible"), 1);
	else {
		x->t_editor = object_new(CLASS_NOBOX, gensym("jed"), x, 0);
		object_method(x->t_editor, gensym("settext"), *x->t_text, gensym("utf-8"));
		object_attr_setchar(x->t_editor, gensym("scratch"), 1);
		object_attr_setsym(x->t_editor, gensym("title"), gensym("simpletext"));
	}
}

void simpletext_doread(t_simpletext *x, t_symbol *s, long argc, t_atom *argv)
{
	char filename[MAX_PATH_CHARS];
	short path;
	t_fourcc type = FOUR_CHAR_CODE('TEXT');
	long err;
	t_filehandle fh;

	if (s == gensym("")) {
		filename[0] = 0;

		if (open_dialog(filename, &path, &type, &type, 1))
			return;
	} else {
		strcpy(filename,s->s_name);
		if (locatefile_extended(filename,&path,&type,&type,1)) {
			object_error((t_object *)x, "can't find file %s",filename);
			return;
		}
	}
// success

	err = path_opensysfile(filename, path, &fh, READ_PERM);
	if (!err) {
		sysfile_readtextfile(fh, x->t_text, 0, TEXT_LB_UNIX | TEXT_NULL_TERMINATE);
		sysfile_close(fh);
		x->t_size = sysmem_handlesize(x->t_text);
	}
}

void simpletext_edclose(t_simpletext *x, char **text, long size)
{
	if (x->t_text)
		sysmem_freehandle(x->t_text);

	x->t_text = sysmem_newhandleclear(size+1);
	sysmem_copyptr((char *)*text, *x->t_text, size);
	x->t_size = size+1;
	x->t_editor = NULL;
}

void *simpletext_new(t_symbol *s, long argc, t_atom *argv)
{
	t_simpletext *x = NULL;

	x = (t_simpletext *)object_alloc(simpletext_class);

	x->t_text = sysmem_newhandle(0);
	x->t_size = 0;
	x->t_editor = NULL;
	return x;
}
