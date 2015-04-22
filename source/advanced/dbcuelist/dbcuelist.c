/**
	@file
	dbcuelist - demonstrate use of a sqlite database

	This is a very simple example of a cue list:
	- an event is simply an array of atom values
	- a cue is simply a collection of events with a name

	This object itself has a name.
	All objects with the same name share the same database (and thus the same cues).

	For the syntax of the SQL commands, refer to http://sqlite.org
	For the information on the Max database API, refer to the ext_database.h header file.

	@ingroup	examples

	Copyright 2009 - Cycling '74
	Timothy Place, tim@cycling74.com
*/

#include "ext.h"
#include "ext_obex.h"
#include "ext_database.h"


// Data Structures
typedef struct _dbcuelist {
	t_object	d_obj;
	void		*d_outlet;
	t_symbol	*d_name;
	t_database	*d_db;
} t_dbcuelist;


// Prototypes
t_dbcuelist	*dbcuelist_new(t_symbol *s, short argc, t_atom *argv);
void			dbcuelist_free(t_dbcuelist *x);
void			dbcuelist_cue_create(t_dbcuelist *x, t_symbol *s);
void			dbcuelist_cue_destroy(t_dbcuelist *x, t_symbol *s);
void			dbcuelist_cue_rename(t_dbcuelist *x, t_symbol *s1, t_symbol *s2);
void			dbcuelist_cue_do(t_dbcuelist *x, t_symbol *s);
void			dbcuelist_event_create(t_dbcuelist *x, t_symbol *s, long argc, t_atom *argv);
void			dbcuelist_event_destroy(t_dbcuelist *x, long event_id);
t_max_err		dbcuelist_attr_name_set(t_dbcuelist *x, void *attr, long argc, t_atom *argv);


// Globals and Statics
static t_class	*s_dbcuelist_class = NULL;
static t_symbol	*ps_event = NULL;

/**********************************************************************/
// Class Definition and Life Cycle

void ext_main(void *r)
{
	t_class *c;

	c = class_new("dbcuelist",
				  (method)dbcuelist_new,
				  (method)dbcuelist_free,
				  sizeof(t_dbcuelist),
				  (method)NULL,
				  A_GIMME,
				  0L);

	class_addmethod(c, (method)dbcuelist_cue_create,	"cue.create",		A_SYM, 0);
	class_addmethod(c, (method)dbcuelist_cue_destroy,	"cue.destroy",		A_SYM, 0);
	class_addmethod(c, (method)dbcuelist_cue_rename,	"cue.rename",		A_SYM, A_SYM, 0);
	class_addmethod(c, (method)dbcuelist_cue_do,		"cue.do",			A_SYM, 0);

	class_addmethod(c, (method)dbcuelist_event_create,	"event.create",		A_GIMME, 0);
	class_addmethod(c, (method)dbcuelist_event_destroy,	"event.destroy",	A_LONG, 0);

	CLASS_ATTR_SYM(c,		"name",	0,	t_dbcuelist, d_name);
	CLASS_ATTR_ACCESSORS(c,	"name",	NULL,	dbcuelist_attr_name_set);

	class_register(CLASS_BOX, c);
	s_dbcuelist_class = c;
	ps_event = gensym("event");
}


t_dbcuelist *dbcuelist_new(t_symbol *s, short argc, t_atom *argv)
{
	t_dbcuelist *x;

	x = (t_dbcuelist *)object_alloc(s_dbcuelist_class);
	if (x) {
		x->d_outlet = outlet_new(x, 0L);
		attr_args_process(x, argc, argv);
	}
	return x;
}


void dbcuelist_free(t_dbcuelist *x)
{
	db_close(&x->d_db);
}


/**********************************************************************/
// Methods

void dbcuelist_cue_create(t_dbcuelist *x, t_symbol *s)
{
	t_max_err	err = MAX_ERR_NONE;

	err = db_query(x->d_db, NULL, "INSERT INTO cues ( 'name' ) VALUES ( \"%s\" )", s->s_name);
	if(err)
		object_error((t_object *)x, "error creating event");
}


void dbcuelist_cue_destroy(t_dbcuelist *x, t_symbol *s)
{
	t_max_err	err = MAX_ERR_NONE;

	err = db_query(x->d_db, NULL, "DELETE FROM cues WHERE name = \"%s\" ", s->s_name);
	if(err)
		object_error((t_object *)x, "error deleting cue");
}


void dbcuelist_cue_rename(t_dbcuelist *x, t_symbol *s1, t_symbol *s2)
{
	t_max_err	err = MAX_ERR_NONE;

	err = db_query(x->d_db, NULL, "UPDATE cues SET name = \"%s\" WHERE name = \"%s\" ", s2->s_name, s1->s_name);
	if(err)
		object_error((t_object *)x, "error deleting cue");
}


void dbcuelist_cue_do(t_dbcuelist *x, t_symbol *s)
{
	t_max_err	err = MAX_ERR_NONE;
	t_db_result	*result = NULL;
	char		*str = NULL;
	int			i;
	int			numrecords;

	err = db_query(x->d_db, &result, "SELECT value FROM events WHERE cue_id_ext = \
									  (SELECT cue_id FROM cues WHERE name = \"%s\") ", s->s_name);
	if(err) {
		object_error((t_object *)x, "invalid cue specified for 'do'");
		return;
	}

	numrecords = db_result_numrecords(result);
	for(i=0; i<numrecords; i++) {
		t_atom	*av = NULL;
		long	ac = 0;

		str = db_result_string(result, i, 0);
		atom_setparse(&ac, &av, str);
		if(ac && av) {
			outlet_anything(x->d_outlet, ps_event, ac, av);
			sysmem_freeptr(av);
		}
	}
}


void dbcuelist_event_create(t_dbcuelist *x, t_symbol *s, long argc, t_atom *argv)
{
	t_symbol	*name = atom_getsym(argv);
	char		*text = NULL;
	long		textsize = 0;
	t_max_err	err = MAX_ERR_NONE;

	if(argc < 2) {
		object_error((t_object *)x, "at least two arguments required to create an event");
		return;
	}

	atom_gettext(argc-1, argv+1, &textsize, &text, 0);
	if(text && textsize) {
		err = db_query(x->d_db, NULL, "INSERT INTO events ( 'cue_id_ext' , 'value' ) \
				 VALUES ( (SELECT cue_id FROM cues WHERE name = \"%s\") , \"%s\") ",
					   name->s_name, text);
		if(err)
			object_error((t_object *)x, "error creating event");
	}
}


void dbcuelist_event_destroy(t_dbcuelist *x, long event_id)
{
	t_max_err	err = MAX_ERR_NONE;

	err = db_query(x->d_db, NULL, "DELETE FROM events WHERE event_id = %ld", event_id);
	if(err)
		object_error((t_object *)x, "error deleting event");
}


/**********************************************************************/
// Attribute Accessors

t_max_err dbcuelist_attr_name_set(t_dbcuelist *x, void *attr, long argc, t_atom *argv)
{
	t_symbol	*newname = atom_getsym(argv);
	t_max_err	err = MAX_ERR_NONE;

	if(newname == x->d_name)
		return MAX_ERR_NONE;

	// close the old database (if needed) and open the new one
	x->d_name = newname;
	db_close(&x->d_db);
	db_open(x->d_name, NULL, &x->d_db);

	// by passing NULL for the second parameter to db_open() we are specifying that
	// the db exist solely in memory.
	// if you wish for it to be persistent (stored on disk),
	// this is left as an exersize for the reader...

	// set up the tables in the database
	err = db_query_table_new(x->d_db, "cues");
	err = db_query_table_addcolumn(x->d_db, "cues", "name", "VARCHAR(256)", 0);

	err = db_query_table_new(x->d_db, "events");
	err = db_query_table_addcolumn(x->d_db, "events", "cue_id_ext",	"INTEGER", 0);
	err = db_query_table_addcolumn(x->d_db, "events", "value",		"TEXT", 0);

	// The above will return error codes if the tables or columns already exist.
	// This is okay, so we will always return MAX_ERR_NONE.
	return MAX_ERR_NONE;
}

