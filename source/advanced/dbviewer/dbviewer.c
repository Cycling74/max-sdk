/**
	@file
	dbviewer - demonstrate use of database views for sqlite and jdataview

	@ingroup	examples

	Copyright 2009 - Cycling '74
	Timothy Place, tim@cycling74.com
*/

#include "ext.h"
#include "ext_obex.h"
#include "ext_strings.h"
#include "ext_common.h"
#include "ext_symobject.h"
#include "ext_database.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "indexmap.h"
#include "jdataview.h"


enum {
	kOutletParameterNames = 0,
	kOutletParameterValues,
	kOutletPresetNames,
	kOutletPluginNames,
	kNumContolOutlets
};


typedef struct _dbviewer {
	t_jbox		d_box;
	t_object	*d_dataview;	///< The dataview object
	t_hashtab	*d_columns;		///< The dataview columns:  column name -> column index
	t_object	*d_view;		///< The dbview object that we need to display in a dataview
	t_symbol	*d_query;		///< Attribute
	t_symbol	*d_database;	///< Attribute
	t_object	*d_db;			///< the actual database object
} t_dbviewer;



// general prototypes
void		*dbviewer_new(t_symbol *s, short argc, t_atom *argv);
void		dbviewer_initdataview(t_dbviewer *x);
void		dbviewer_free(t_dbviewer *x);
void		dbviewer_newpatcherview(t_dbviewer *x, t_object *patcherview);
void		dbviewer_freepatcherview(t_dbviewer *x, t_object *patcherview);
t_max_err	dbviewer_notify(t_dbviewer *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void		dbviewer_assist(t_dbviewer *x, void *b, long m, long a, char *s);
void		dbviewer_bang(t_dbviewer *x);
void		dbviewer_getcelltext(t_dbviewer *x, t_symbol *colname, long index, char *text, long maxlen);
t_max_err	dbviewer_set_query(t_dbviewer *x, void *attr, long argc, t_atom *argv);
t_max_err	dbviewer_set_database(t_dbviewer *x, void *attr, long argc, t_atom *argv);


static t_class	*s_dbviewer_class = NULL;
static t_symbol	*ps_dbview_update = NULL;
static t_symbol	*ps_dbview_query_changed = NULL;

/************************************************************************************/

void ext_main(void *r)
{
	t_class	*c;
	long	flags;

	common_symbols_init();
	c = class_new("dbviewer", (method)dbviewer_new, (method)dbviewer_free, sizeof(t_dbviewer), (method)0L, A_GIMME, 0);
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	flags = JBOX_COLOR;
	jbox_initclass(c, flags);

	class_addmethod(c, (method)dbviewer_bang,				"bang",				0);			// refresh
	class_addmethod(c, (method)dbviewer_getcelltext,		"getcelltext",		A_CANT, 0);
	class_addmethod(c, (method)dbviewer_newpatcherview,		"newpatcherview",	A_CANT, 0);
	class_addmethod(c, (method)dbviewer_freepatcherview,	"freepatcherview",	A_CANT, 0);
	class_addmethod(c, (method)dbviewer_notify,				"notify",			A_CANT,	0);
	class_addmethod(c, (method)dbviewer_assist,				"assist",			A_CANT, 0);
	class_addmethod(c, (method)stdinletinfo,				"inletinfo",		A_CANT, 0);
	class_addmethod(c, (method)object_obex_dumpout,			"dumpout",			A_CANT, 0);

	CLASS_ATTR_SYM(c,			"query",			ATTR_SET_DEFER,	t_dbviewer, d_query);
	CLASS_ATTR_ACCESSORS(c,		"query",			NULL, dbviewer_set_query);
	CLASS_ATTR_SAVE(c,			"query",			0);

	CLASS_ATTR_SYM(c,			"database",			ATTR_SET_DEFER,	t_dbviewer, d_database);
	CLASS_ATTR_ACCESSORS(c,		"database",			NULL, dbviewer_set_database);
	CLASS_ATTR_SAVE(c,			"database",			0);

	class_register(CLASS_BOX, c);
	s_dbviewer_class = c;

	ps_dbview_update = gensym("dbview_update");
	ps_dbview_query_changed = gensym("dbview_query_changed");
}


/************************************************************************************/
// Object Creation Method

void *dbviewer_new(t_symbol *s, short argc, t_atom *argv)
{
	t_dbviewer		*x;
	long			flags;
	t_dictionary	*d = NULL;

	if (!(d=object_dictionaryarg(argc, argv)))
		return NULL;

	x = (t_dbviewer *)object_alloc(s_dbviewer_class);
	if (x) {
		flags = 0
				| JBOX_DRAWFIRSTIN
				| JBOX_NODRAWBOX
				| JBOX_DRAWINLAST
				//		| JBOX_TRANSPARENT
				//		| JBOX_NOGROW
				//		| JBOX_GROWY
				| JBOX_GROWBOTH
				//		| JBOX_IGNORELOCKCLICK
				| JBOX_HILITE
				//		| JBOX_BACKGROUND
				//		| JBOX_NOFLOATINSPECTOR
				//		| JBOX_TEXTFIELD
				;

		jbox_new(&x->d_box, flags, argc, argv);
		x->d_box.b_firstin = (t_object *)x;
		object_obex_store((void *)x, _sym_dumpout, (t_object *)outlet_new(x, NULL));

		x->d_columns = hashtab_new(13);
		hashtab_flags(x->d_columns, OBJ_FLAG_DATA);
		x->d_query = _sym_nothing;

		dbviewer_initdataview(x);
		attr_dictionary_process(x, d);

		jbox_ready(&x->d_box);
//		object_notify(x->d_view, ps_dbview_update, NULL);
	}
	return(x);
}


void dbviewer_initdataview(t_dbviewer *x)
{
	x->d_dataview = (t_object *)jdataview_new();
	jdataview_setclient(x->d_dataview, (t_object *)x);
	jdataview_setcolumnheaderheight(x->d_dataview, 40);
	jdataview_setheight(x->d_dataview, 16.0);
}


// Memory Deallocation
void dbviewer_free(t_dbviewer *x)
{
	db_view_remove(x->d_db, &x->d_view);
	db_close(&x->d_db);
	jbox_free(&x->d_box);
}


void dbviewer_newpatcherview(t_dbviewer *x, t_object *patcherview)
{
	jdataview_patchervis(x->d_dataview, patcherview, (t_object *)x);
}

void dbviewer_freepatcherview(t_dbviewer *x, t_object *patcherview)
{
	jdataview_patcherinvis(x->d_dataview, patcherview);
}


t_max_err dbviewer_notify(t_dbviewer *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (sender == x->d_view) {
		if (msg == ps_dbview_update) {
			dbviewer_bang(x);
		}
		else if (msg == ps_dbview_query_changed) {	// dump all of the columns
			t_object	*column = NULL;
			t_symbol	**column_names = NULL;
			long		numcolumns = 0;
			long		i;

			hashtab_getkeys(x->d_columns, &numcolumns, &column_names);
			if (column_names) {
				for (i=0; i<numcolumns; i++) {
					column = jdataview_getnamedcolumn(x->d_dataview, column_names[i]);
					if (column)
						jdataview_deletecolumn(x->d_dataview, column);
				}
				sysmem_freeptr(column_names);
			}
			hashtab_clear(x->d_columns);
		}
		else if (msg == _sym_free) {
			object_detach_byptr((t_object *)x, x->d_view);
			x->d_view = NULL;
		}
	}
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}


/************************************************************************************/
// Methods bound to input/inlets

// Method for Assistance Messages
void dbviewer_assist(t_dbviewer *x, void *b, long msg, long arg, char *dst)
{
	if (msg==1) { 	// Inlets
		switch (arg) {
		case 0: strcpy(dst, "(signal, control) Audio Input and Control Messages"); break;
		default: strcpy(dst, "(signal) Audio Input"); break;
		}
	}
	else if (msg==2) { // Outlets
		if (arg == 0)
			strcpy(dst, "(signal) Audio Output");
		else if (arg == 1)
			strcpy(dst, "(symbol) Parameter Name Dump");
		else
			strcpy(dst, "dumpout");
	}
}


void dbviewer_bang(t_dbviewer *x)
{
	t_object	*result = NULL;
	long		numrecords;
	long		numfields;
	long		i;
	char		*fieldname = NULL;
	t_symbol	*sfieldname = NULL;
	t_object	*column;
	t_atom_long	column_index;
	t_rowref	*rowrefs = NULL;
	t_max_err	err;

	db_view_getresult(x->d_view, &result);
	jdataview_clear(x->d_dataview);
	if (!result)
		return;

	numrecords = (long)object_method(result, _sym_numrecords);
	if (numrecords) {
		numfields = (long)object_method(result, _sym_numfields);
		for (i = 0; i < numfields; i++) {
			fieldname = (char *)object_method(result, _sym_fieldnamebyindex, i);
			if (fieldname) {
				sfieldname = gensym(fieldname);
				err = hashtab_lookuplong(x->d_columns, sfieldname, &column_index);
				if (!err) {
					; // column already exists, so we leave it alone
				}
				else {
					column = jdataview_addcolumn(x->d_dataview, sfieldname, NULL, true);
					jcolumn_setlabel(column, sfieldname);
					jcolumn_setwidth(column, 110);
					jcolumn_setmaxwidth(column, 300);
					hashtab_store(x->d_columns, sfieldname, (t_object *)i);
				}
			}
		}

		rowrefs = (t_rowref *)malloc(sizeof(t_rowref) * numrecords);
		for (i = 0; i < numrecords; i++)
			rowrefs[i] = (t_rowref *)(i+1);
		jdataview_addrows(x->d_dataview, numrecords, rowrefs);
		free(rowrefs);
	}
}


void dbviewer_getcelltext(t_dbviewer *x, t_symbol *colname, long index, char *text, long maxlen)
{
	t_object	*result = (t_object *)object_method(x->d_view, gensym("getresult"));
	char		*itemtext;
	t_atom_long	column_index;
	t_max_err	err;

	if (!result)
		return;

	err = hashtab_lookuplong(x->d_columns, colname, &column_index);
	if (!err) {
		itemtext = (char *)object_method(result, _sym_valuebyindex, index-1, column_index);

		if (itemtext && itemtext[0]) {
			if (strstr(colname->s_name, "date")) {
				t_datetime td;
				sysdateformat_strftimetodatetime(itemtext, &td);
				sysdateformat_formatdatetime(&td, SYSDATEFORMAT_RELATIVE, 0, text, maxlen-1);
			}
			else
				strncpy_zero(text, itemtext, maxlen-1);
		}
	}
}


t_max_err dbviewer_set_query(t_dbviewer *x, void *attr, long argc, t_atom *argv)
{
	if (argc && argv) {
		x->d_query = atom_getsym(argv);
		object_attr_setsym(x->d_view, _sym_query, x->d_query);
		if (x->d_db && x->d_query) {
			db_view_create(x->d_db, x->d_query->s_name, &x->d_view);
			object_attach_byptr_register(x, x->d_view, _sym_nobox);
		}
	}
	return MAX_ERR_NONE;
}


t_max_err dbviewer_set_database(t_dbviewer *x, void *attr, long argc, t_atom *argv)
{
	t_max_err err;

	if (argc && argv) {
		db_view_remove(x->d_db, &x->d_view);
		db_close(&x->d_db);

		x->d_database = atom_getsym(argv);
		err = db_open(x->d_database, NULL, &x->d_db);
		if (!err && x->d_db && x->d_query) {
			db_view_create(x->d_db, x->d_query->s_name, &x->d_view);
			object_attach_byptr_register(x, x->d_view, _sym_nobox);
		}
	}
	return MAX_ERR_NONE;
}

