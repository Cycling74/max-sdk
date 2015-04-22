/**
 @file
 folder - list the files in a specific folder

 updated 3/22/09 ajm: new API

 @ingroup	examples
 */

#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "ext_strings.h"


void *folder_class;

/* first argument is folder name : is subdir of Max, otherwise starts with disk.
	subsequent arguments are file types to search for (default is TEXT and maxb)
*/

#define MAXTYPES 128

typedef struct _folder {
	t_object f_ob;
	short f_path;
	t_symbol *f_input;
	t_fourcc f_types[MAXTYPES];
	long f_numtypes;
	void *f_countout;
	long f_outcount;
} t_folder;

void folder_bang(t_folder *x);
void folder_types(t_folder *x, t_symbol *s, short ac, t_atom *av);
void folder_anything(t_folder *x, t_symbol *s, short ac, t_atom *av);
void folder_assist(t_folder *x,void *b,long m,long a,char *s);
void *folder_new(t_symbol *s, short ac, t_atom *av);
void folder_lookup(t_folder *x);
void folder_enumerate(t_folder *x);
void folder_action(t_folder *x);

t_symbol *ps_clear,*ps_append;
long debug;

void ext_main(void *r)
{
	t_class *c;

	c = class_new("folder", (method)folder_new, 0L, (short)sizeof(t_folder), 0L, A_GIMME, 0);
	class_addmethod(c, (method)folder_bang,			"int", A_LONG, 0);
	class_addmethod(c, (method)folder_bang,			"bang", 0);
	class_addmethod(c, (method)folder_anything,		"anything",	A_GIMME, 0);
	class_addmethod(c, (method)folder_anything,		"symbol",	A_SYM, 0);
	class_addmethod(c, (method)folder_types,		"types",	A_GIMME, 0);
	class_addmethod(c, (method)folder_assist,		"assist",	A_CANT, 0);
	class_register(CLASS_BOX, c);
	folder_class = c;

	ps_clear = gensym("clear");
	ps_append = gensym("append");
	debug = 0;

	return 0;
}

void folder_action(t_folder *x)
{
	x->f_outcount = 0;
	if (x->f_path == 0) {
		folder_lookup(x);
		if (x->f_path == 0)
			goto bag;
	}
	folder_enumerate(x);
bag:
	outlet_int(x->f_countout,x->f_outcount);
}

void folder_bang(t_folder *x)
{
	defer(x,(method)folder_action,0L,0,0L);
}

void folder_assist(t_folder *x,void *b,long m,long a,char *s)
{
	if (m==1) {
		switch (a) {
		case 0: sprintf(s,"Path Name of Folder to List"); break;
		}
	}
	else if (m==2) {
		switch (a) {
		case 0: sprintf(s,"File Name List, Connect to Menu"); break;
		case 1: sprintf(s,"Count of Items Listed"); break;
		}
	}
}

void folder_lookup(t_folder *x)
{
	short path,err;
	char sourcename[512],filename[256];

	if (x->f_input) {
		strcpy(sourcename,x->f_input->s_name);
		err = path_frompathname(sourcename, &path, filename);
		if (err || filename[0]) {
			object_error((t_object *)x, "%s: not a folder",x->f_input->s_name);
			x->f_path = 0;
		}
		else {
			x->f_path = path;
		}
	}
}

void folder_anything(t_folder *x, t_symbol *s, short ac, t_atom *av)
{
	x->f_input = s;
	x->f_path = 0;
	folder_bang(x);
}

void folder_types(t_folder *x, t_symbol *s, short ac, t_atom *av)
{
	t_uint8 type[4];
	long len=0,i;

	x->f_numtypes = 0;
	while (ac--) {
		if (atom_gettype(av) == A_SYM) {
			len = strlen(atom_getsym(av)->s_name);
			for (i=0; i<4; i++) {
				type[i] = (i>=len) ? ' ' : atom_getsym(av)->s_name[i];
			}
			STR_TO_FOURCC(*((t_fourcc *)type));
			sysmem_copyptr(type,&x->f_types[x->f_numtypes++],4L);
		}
		av++;
	}
}

void *folder_new(t_symbol *s, short ac, t_atom *av)
{
	t_folder *x;

	x = object_alloc(folder_class);
	x->f_countout = intout((t_object *)x);
	outlet_new((t_object *)x,0);
	x->f_input = 0;
	x->f_numtypes = 0;
	x->f_path = 0;
	x->f_outcount = 0;
	if (ac) {
		if (atom_gettype(av) == A_SYM)
		{
			x->f_input = atom_getsym(av);
		}
		if (ac > 1) {
			av++;
			folder_types(x,s,ac-1,av); // ddz 06/27/05 ac -> ac-1 bug fix
		}
	}
	if (!x->f_numtypes) {
		short numtypes;

		typelist_make(x->f_types, TYPELIST_MAXFILES | TYPELIST_MAXFORLIVE, &numtypes);
		x->f_numtypes = numtypes;
	}
	if (x->f_input)
		folder_lookup(x);
	return x;
}

void folder_enumerate(t_folder *x)
{
	void *fold;
	t_bool cleared = false, match;
	t_atom a;
	t_fourcc type;
	long i;
	char name[256];
	t_fileinfo info;

	if (!x->f_path)
		return;
	fold = path_openfolder(x->f_path);
	if (!fold)
		return;

	while (path_foldernextfile(fold,&type,name,false)) {
		if (x->f_numtypes==0)
			match = true;
		else {
			match = false;
			if (!type) {
				if (!path_extendedfileinfo(name,x->f_path,&info,x->f_types,x->f_numtypes,true))
					type = info.type;
			}
			for (i = 0; i < x->f_numtypes; i++) {
				if (type == x->f_types[i]) {
					match = true;
					break;
				}
			}
		}
		if (match) {
			if (!cleared) {
				outlet_anything(x->f_ob.o_outlet,ps_clear,0,0);
				cleared = true;
			}
			atom_setsym(&a, gensym(name));
			outlet_anything(x->f_ob.o_outlet,ps_append,1,&a);
			x->f_outcount++;
		}
	}
	path_closefolder(fold);

}
