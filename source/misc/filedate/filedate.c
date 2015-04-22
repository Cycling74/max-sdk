/**
 @file
 filedate - manage search paths
 Accesses a file on disk and outputs a given byte of the file's data.
 Note that we use the "open" message, not "read", because we're not loading the file into memory.

 updated 3/22/09 ajm: new API

 @ingroup	examples
 */

#include "ext.h"
#include "ext_obex.h"
#include "ext_path.h"
#include "ext_strings.h"


typedef struct filedate
{
	t_object f_ob;
} t_filedate;

void *filedate_class;

void filedate_assist(t_filedate *x, void *b, long m, long a, char *s);
void filedate_doanything(t_filedate *x, t_symbol *s, short argc, t_atom *argv);
void filedate_out(t_filedate *x, t_ptr_uint date);
void filedate_anything(t_filedate *x, t_symbol *s, short argc, t_atom *argv);
void *filedate_new(void);

t_symbol *ps_nothing, *ps_list;

void ext_main(void *r)
{
	t_class *c;

	c = class_new("filedate", (method)filedate_new,0L, (short)sizeof(t_filedate), 0L, 0);
	class_addmethod(c, (method)filedate_anything, "anything", A_GIMME, 0);
	class_addmethod(c, (method)filedate_assist,"assist",A_CANT,0);
	class_register(CLASS_BOX, c);
	filedate_class = c;

	ps_nothing = gensym("");
	ps_list = gensym("list");

	return (0);
}

void filedate_assist(t_filedate *x, void *b, long m, long a, char *s)
{
	if (m==1) {
		switch (a) {
		case 0: sprintf(s,"File/Folder to Check Modification Date"); break;
		}
	}
	else if (m==2) {
		switch (a) {
		case 0: sprintf(s,"Mod Date (Month/Day/Year/Hour/Min/Sec)"); break;
		}
	}
}

void filedate_anything(t_filedate *x, t_symbol *s, short argc, t_atom *argv)
{
	defer(x,(method)filedate_doanything,s,argc,argv);
}

void filedate_doanything(t_filedate *x, t_symbol *s, short argc, t_atom *argv)
{
	char filename[MAX_PATH_CHARS];
	short vol,err;
	t_fourcc type;
	t_ptr_uint date;

	if (s == ps_nothing)
		return;
	strcpy(filename,s->s_name);
	if (!locatefile_extended(filename,&vol,&type,&type,0)) {	// look for all files
		err = path_getfilemoddate(filename,vol,&date);			// find the date of the file
		if (err) {
			object_error((t_object *)x, "%s: error %d getting date",s->s_name,err);
			return;
		}
		filedate_out(x,date);
	} else {		// now check for a folder, you need to copy the name again
		// since locatefile_extended may have changed it
		strcpy(filename,s->s_name);
		if (!path_resolvefile(filename,0,&vol)) {	// returns false if it found a file or folder
			// the logic here is that a folder, which wouldn't be
			// found by locatefile_extended would be the
			// only thing found here
			err = path_getmoddate(vol,&date);		// find the date of the path, not the file
			if (!err) {
				filedate_out(x,date);
				return;
			} else {
				object_error((t_object *)x, "%s: error %d getting date",s->s_name,err);
				return;
			}
		}
		object_error((t_object *)x, "%s: can't find",s->s_name);
	}
}

void filedate_out(t_filedate *x, t_ptr_uint date)
{
	t_datetime dtr;
	t_atom list[16];

	systime_secondstodate(date,&dtr);	// convert the date to a readable record
	atom_setlong(list,dtr.month);
	atom_setlong(list+1,dtr.day);
	atom_setlong(list+2,dtr.year);
	atom_setlong(list+3,dtr.hour);
	atom_setlong(list+4,dtr.minute);
	atom_setlong(list+5,dtr.second);
	outlet_list(x->f_ob.o_outlet,ps_list,6,list);
}

void *filedate_new(void)
{
	t_filedate *x;

	x = object_alloc(filedate_class);
	outlet_new((t_object *)x,0);
	return x;
}

