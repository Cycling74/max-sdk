// jdataview.h copyright 2007 cycling '74 all rights reserved


#ifndef _JDATAVIEW_H_
#define _JDATAVIEW_H_

#include "indexmap.h"
#include "jpatcher_api.h"
#include "jgraphics.h"

// symbols used 

BEGIN_USING_C_LINKAGE

extern t_symbol *ps_jdv_update;

// a jdataview has columns

// constants

#define JDATAVIEW_CELLMAX MAX_PATH_CHARS	// maximum number of chars in a cell, do not try to write more than 
											// this number to the text buffer supplied by the 'getcelltext' functions

#define JCOLUMN_DEFAULT_WIDTH 50
#define JCOLUMN_DEFAULT_MINWIDTH 50
#define JCOLUMN_DEFAULT_MAXWIDTH 100

#define JCOLUMN_DEFAULT_FONTSIZE 10

#define JCOLUMN_DEFAULT_MAXTEXTLEN 256

// values for c_alignment

enum {
	JCOLUMN_ALIGN_LEFT = 1,
	JCOLUMN_ALIGN_CENTER,
	JCOLUMN_ALIGN_RIGHT
};

enum {
	JCOLUMN_STYLE_PLAIN = 0,
	JCOLUMN_STYLE_BOLD = 1,
	JCOLUMN_STYLE_ITALIC = 2
};

enum {
	JCOLUMN_MOUSE_ENTER = 0,
	JCOLUMN_MOUSE_MOVE = 1,
	JCOLUMN_MOUSE_EXIT = 2
};

enum {
	JCOLUMN_SORTDIRECTION_FORWARD = 1,
	JCOLUMN_SORTDIRECTION_BACKWARD = 0
};

enum {
	JCOLUMN_INITIALLYSORTED_NONE = 0,
	JCOLUMN_INITIALLYSORTED_FORWARDS = 1,
	JCOLUMN_INITIALLYSORTED_BACKWARDS = 2
};

// kinds of JUCE component style columns (or cells within columns)

enum {
	JCOLUMN_COMPONENT_NONE = 0,
	JCOLUMN_COMPONENT_CHECKBOX = 1,
	JCOLUMN_COMPONENT_TEXTEDITOR = 2,		// eventually alphanumeric and numeric variants
	JCOLUMN_COMPONENT_SLIDER = 3,
	JCOLUMN_COMPONENT_COLOR = 4,
	JCOLUMN_COMPONENT_MENU = 5
};

enum {
	JCOLUMN_MENU_INDEX = 1,					// report index chosen instead of value of item
	JCOLUMN_MENU_FONTMENU = 2,				// flag for showing a font menu
	JCOLUMN_MENU_PAINT = 4,					// cell is drawn with client paint method
	JCOLUMN_MENU_SELECT = 8,					// row is selected on mouse down
	JCOLUMN_MENU_NOPANEL = 16,				// for font menu, don't include the show fonts item
	JCOLUMN_MENU_CLEARITEM = 32,				// for font menu, include a clear item
	JCOLUMN_MENU_STYLEMENU = 64				// show a menu of all current styles
};

enum {
	JCOLUMN_TEXT_ONESYMBOL = 1,
	JCOLUMN_TEXT_COMMASEPARATED = 2,
	JCOLUMN_TEXT_ICON = 4,
	JCOLUMN_TEXT_HASBUTTON = 8,
	JCOLUMN_TEXT_FILECHOOSEBUTTON = 16,
	JCOLUMN_TEXT_VIEWBUTTON = 32,
	JCOLUMN_TEXT_EDITBUTTON = 64,
	JCOLUMN_TEXT_TIME = 128,
	JCOLUMN_TEXT_FLOAT = 256,
	JCOLUMN_TEXT_INT = 512,
	JCOLUMN_TEXT_CANTEDIT = 1024,
	JCOLUMN_TEXT_FONTSIZE = 2048,
	// 4096 is JCOLUMN_DISABLED -- do not use
	JCOLUMN_TEXT_FILTERED = 8192,
	JCOLUMN_TEXT_STRINGOBJECT = 16384,
	JCOLUMN_TEXT_PITCH = 32768,
	JCOLUMN_TEXT_FILECLEARBUTTON = 65536
};

enum {
	JCOLUMN_SLIDER_NOTEXTBOX = 1,
	JCOLUMN_SLIDER_ZERO_TO_ONE = 2
};

#define JCOLUMN_DISABLED 0x1000


/**	A dataview cell description.
	@ingroup	jdataview	*/
typedef struct _celldesc
{
	long row;
	long col;
	void *section;
	long data;
} t_celldesc;


/**	A dataview column.
	Columns for a given dataview are stored in a #t_hashtab and accessed by name.
	@ingroup	jdataview	*/
typedef struct _col 
{
	t_object c_obj;
	void *obex;
	t_symbol *c_name;			///< column name (hash)
	t_object *c_dv;				///< parent dataview
	int c_id;					///< id in DataViewComponent
	long c_width;				///< column width in pixels
	long c_maxwidth;			///< max column width
	long c_minwidth;			///< min column width
	char c_autosize;			///< determine width of text column automatically (true/false)
	char c_alignment;			///< display of text, left, right, center
	t_symbol *c_font;			///< name of font
	long c_fontsize;			///< font size (points?)
	t_symbol *c_label;			///< heading of column
	char c_separator;			///< separator mode
	char c_button;				///< column has a button (true/false)
	t_symbol *c_buttonlabel;	///< text in a button
	t_symbol *c_customsort;		///< message sent to sort this column -- if none, default sorting is used based on value c_numeric
	char c_overridesort;		///< if true only the sortdata method is called, not the sort method (true/false)
	t_symbol *c_custompaint;	///< send this msg name to client to paint this column
	t_symbol *c_valuemsg;		///< message sent when a component mode cell's value changes
	t_symbol *c_beginmsg;		///< message sent when a component mode cell's value is about to start changing
	t_symbol *c_endmsg;			///< message sent when a component mode cell's value is finished changing
	t_symbol *c_rowcomponentmsg;///< message sent to determine what kind of component should be created for each cell in a column
	t_symbol *c_custommenuset;	///< message to set a menu (for a readonly or custompaint column)
	t_symbol *c_custommenuresult;	///< message sent when an item is chosen from a custom menu
	char c_editable;			///< can you edit the data in a cell in this column
	char c_selectable;			///< can select the data in a cell in this column (possibly without being able to edit)
	char c_multiselectable;		///< can you select more than one cell in this column
	char c_sortable;			///< can you click on a column heading to sort the data
	long c_initiallysorted;		///< if this is set to JCOLUMN_INITIALLYSORTED_FORWARDS the column is displayed with the sort triangle
	long c_maxtextlen;			///< maximum text length: this is used to allocate a buffer to pass to gettext (but there is also a constant)
	long c_sortdirection;		///< 0 for ascending, 1 for descending
	long c_component;			///< enum of components (check box etc.)
	char c_canselect;			///< can select entire column
	char c_cancut;				///< can cut/clear entire column
	char c_cancopy;				///< can copy entire column
	char c_cancutcells;			///< can cut a single cell (assumes "editable" or "selectable") (probably won't be implemented)
	char c_cancopycells;		///< can copy a single cell
	char c_canpastecells;		///< can paste into a single cell
	char c_hideable;			///< can the column be hidden
	char c_hidden;				///< is the column hidden (set/get)
	char c_numeric;				///< is the data numeric (i.e., is getcellvalue implemented)
	char c_draggable;			///< can drag the column to rearrange it
	char c_casesensitive;		///< use case sensitive sorting (applies only to default text sorting)
	char c_showinfo;			///< show info button for cell clue on mouse over
	void *c_reference;			///< reference for the use of the client
	double c_indentspacing;		///< amount of space (in pixels) for one indent level
	t_symbol *c_insertbefore;	///< name of column before which this one should have been inserted (used only once)
	t_symbol *c_cellcluemsg;	///< message to send requesting clue text for a cell
	t_symbol *c_celltextcolormsg;	///< message to get the cell's text color
	t_symbol *c_celltextstylemsg;	///< message to get the cell's style and alignment
	t_symbol *c_cellentermsg;	///< message for cell enter
	t_symbol *c_cellexitmsg;	///< message for cell exit
	t_symbol *c_cellmovedmsg;	///< message for cell mouse move
	t_symbol *c_cellclickmsg;	///< message for custom cell click action
} t_jcolumn;


/**	The dataview object.
	@ingroup	jdataview	*/
typedef struct _jdataview
{
	t_object d_obj;
	void *obex;
	t_linklist *d_components;	///< list of DataViewComponents showing this dataview
	t_object *d_client;			///< object that will be sent messages to get data to display
	t_hashtab *d_columns;		///< columns -- point to t_jcolumn objects
	t_hashtab *d_id2columns;	///< columns from column IDs
	t_linklist *d_colorder;		///< current order of columns
	void *d_rowmap_obsolete;	///< no longer used
	long d_numcols;				///< number of columns
	double d_rowheight;			///< fixed height of a row in pixels
	char d_autoheight;			///< height determined by font
	char d_hierarchical;		///< does it allow hierarchical disclosure (true / false) -- not implemented yet
	t_jrgba d_rowcolor1;		///< odd row color (striped)
	t_jrgba d_rowcolor2;		///< even row color
	t_jrgba d_selectcolor;		///< color when rows are selected
	t_jrgba d_bordercolor;		///< border color
	char d_bordercolorset;		///< was border color set? if not, use JUCE default
	char d_canselectmultiple;	///< multiple rows are selectable
	char d_cancopy;				///< copy enabled
	char d_cancut;				///< cut / clear enabled
	char d_canpaste;			///< paste enabled
	char d_canrearrangerows;	///< rows can be dragged to rearrange -- may not be implemented yet
	char d_canrearrangecolumns;	///< columns can be dragged to rearrange
	long d_viscount;			///< number of visible views of this dataview
	long d_inset;				///< inset for table inside containing component in pixels
	char d_autosizeright;		///< right side autosizes when top-level component changes
	char d_autosizebottom;		///< bottom autosizes when top-level component changes
	char d_dragenabled;			///< enabled for dragging (as in drag and drop)
	t_symbol *d_fontname;		///< font name
	double d_fontsize;			///< font size
	t_symbol *d_colheadercluemsg;	///< message to send requesting clue text for the column headers
	char d_autosizerightcolumn;	///< right column should stretch to remaining width of the dataview, regardless of column width
	char d_customselectcolor;		///< send getcellcolor message to draw selected cell, don't use select color
	void *d_qelem;				///< defer updating
	double d_colheaderheight;
	char d_drawgrid;
	long d_top_inset;			///< vertical inset for row background (default 0)
	long d_bottom_inset;		///< vertical inset for row background (default 0)
	long d_borderthickness;		///< border line thickness default 0 for no border
	char d_keyfocusable;		///< notify component to grab some keys
	char d_enabledeletekey;		///< delete key will delete selected rows
	char d_usegradient;			///< color rows with gradient between rowcolor1 (top) and rowcolor2 (bottom)
	char d_inchange;			///< in change flag for inspector end-change protection system
	char d_horizscrollvisible;	///< is horizontal scroll bar visible
	char d_vertscrollvisible;	///< is vertical scroll bar visible
	char d_scrollvisset;		///< has the scroll visibility ever been changed since the dv was created?
	char d_overridefocus;		///< override default focus behavior where ListBox is focused when assigning focus to the dataview
	char d_usesystemfont;		///< use system font (true by default)
	t_object *d_searchcolumn;	///< column we ask for celltext in order to navigate the selection via the keyboard
	t_object *d_returnkeycolumn;///< column that is sent the return key when a given row is selected
	void *d_navcache;			///< sorted list of column strings for key navigation
	char d_usecharheight;		///< use font specified in points rather than pixels (default is pixels)
	t_linklist *d_sections;		///< list of sections
	char d_paintcellseparator;	///< should paint a line below a cell (grayish)
	t_object *d_sortset;		///< sort col saved when dv is invisible
	char d_solidheadercolor;
	t_jrgba d_headerbgcolor;
	t_jrgba d_headertextcolor;
	void *d_context;
} t_jdataview;


// private -- used to notify a component of a jdataview change
typedef struct _jdv_notifier
{
	t_jdataview *n_dataview;
	t_symbol *n_what;
	void *n_data;
} t_jdv_notifier;


/** used to pass data to a client sort function 
	@ingroup	jdataview	*/
typedef struct _privatesortrec
{
	t_jcolumn *p_col;		///< column object to sort
	char p_fwd;				///< 1 if sorting "forwards"
	t_object *p_client;		///< pointer to the client object
	t_jdataview *p_dv;		///< pointer to the dataview
} t_privatesortrec;

typedef struct _jsection
{
	t_symbol *s_name;		// section name
	char s_open;			// is section disclosed?
	char s_headervisible;	// is header visible?
	t_indexmap *s_rowmap;	// map of rowrefs to row indices
	void *s_data;			// some data (not used yet)
	t_jsurface *s_icon;		// associated icon to display in header
	t_jrgba s_bgcolor;		// background color
	char s_solidcolor;		// uses solid color, not gradient
} t_jsection;

// private
void jdataview_initclass(void);


/** Create a dataview.  
	You should free it with object_free().
	@ingroup	jdataview
	@return		A pointer to the new instance.	*/
void *jdataview_new(void);


/** Set a dataview's client.
	The client is the object to which the dataview will send messages to get data,
	notify of changes to cells, etc.
	Typically this is the object in which you are creating the dataview.
	@ingroup		jdataview
	@param	dv		The dataview instance.
	@param	client	The object to be assigned as the dataview's client.	*/
void jdataview_setclient(t_object *dv, t_object *client);

/** Get a pointer to a dataview's client.
	The client is the object to which the dataview will send messages to get data,
	notify of changes to cells, etc.
	@ingroup		jdataview
	@param	dv		The dataview instance.
	@return			A pointer to the dataview's client object.	*/
t_object *jdataview_getclient(t_object *dv);

// section support

void *jdataview_newsection(t_object *dv, char *name, void *assoc, t_jsurface *icon, char initiallyopen, char headervisible);
int jdataview_numsections(t_object *dv);
void *jdataview_getnthsection(t_object *dv, long index);
int jdataview_section_getnumrows(t_object *dv, void *section);
long jdataview_section_isopen(t_object *dv, void *section);
void jdataview_section_setopen(t_object *dv, void *section, long way);
void jdataview_getsectionopenness(t_object *dv, char **state);
void jdataview_setsectionopenness(t_object *dv, char *state);
long jdataview_section_headervisible(t_object *dv, void *section);
void jdataview_section_setheadervisible(t_object *dv, void *section, long way);
t_symbol *jdataview_section_getname(t_object *dv, void *section);
t_jsurface *jdataview_section_geticon(t_object *dv, void *section);


// make it visible

void jdataview_patchervis(t_object *dv, t_object *pv, t_object *box);
void jdataview_patcherinvis(t_object *dv, t_object *pv);
void jdataview_obscuring(t_object *dv, t_object *pv);


// set global attributes

void jdataview_setheight(t_object *dv, long height);
long jdataview_getheight(t_object *dv);

void jdataview_setautoheight(t_object *dv, long way);
short jdataview_getautoheight(t_object *dv);

void jdataview_setcolumnheaderheight(t_object *dv, double height);
double jdataview_getcolumnheaderheight(t_object *dv);

void jdataview_setrowcolor1(t_object *dv, t_jrgba *c);
void jdataview_getrowcolor1(t_object *dv, t_jrgba *c);
void jdataview_setrowcolor2(t_object *dv, t_jrgba *c);
void jdataview_getrowcolor2(t_object *dv, t_jrgba *c);

void jdataview_getselectcolor(t_object *dv, t_jrgba *c);
void jdataview_setselectcolor(t_object *dv, t_jrgba *c);

void jdataview_setusegradient(t_object *dv, long way);
long jdataview_getusegradient(t_object *dv);

void jdataview_setcanselectmultiple(t_object *dv, long way);
short jdataview_getcanselectmultiple(t_object *dv);

void jdataview_setcancopy(t_object *dv, long way);
short jdataview_getcancopy(t_object *dv);

void jdataview_setcanpaste(t_object *dv, long way);
short jdataview_getcanpaste(t_object *dv);

void jdataview_setinset(t_object *dv, long inset);
long jdataview_getinset(t_object *dv);

void jdataview_setautosizeright(t_object *dv, long way);
long jdataview_getautosizeright(t_object *dv);

void jdataview_setautosizebottom(t_object *dv, long way);
long jdataview_getautosizebottom(t_object *dv);

void jdataview_setautosizerightcolumn(t_object *dv, long way);
long jdataview_getautosizerightcolumn(t_object *dv);

void jdataview_setusecharheightfont(t_object *dv, long way);

// standard containersizechange method for objects to use
// i.e., class_addmethod(c, jdataview_containersizechange, "containersizechange", A_CANT, 0);

typedef long (*t_containersizechange_fun)(t_object *x, double cw, double ch, double *width, double *height, int asr, int asb); 

t_atom_long jdataview_containersizechange(t_object *x, double cw, double ch, double *width, double *height, int asr, int asb);

t_max_err jdataview_gethorizscrollvalues(t_object *x, double *min, double *max, double *start, double *size);
void jdataview_sethorizscrollvalues(t_object *x, double start, double size);

t_max_err jdataview_getvertscrollvalues(t_object *x, double *min, double *max, double *start, double *size);
void jdataview_setvertscrollvalues(t_object *x, double start, double size);

t_max_err jdataview_setscrollvisible(t_object *x, long vbar, long hbar);

void jdataview_setborderthickness(t_object *dv, long val);
long jdataview_getborderthickness(t_object *dv);

void jdataview_setkeyfocusable(t_object *x, long val);
long jdataview_getkeyfocusable(t_object *x);

void jdataview_setenabledeletekey(t_object *dv, long way); 
long jdataview_getenabledeletekey(t_object *dv); 

void jdataview_setfontname(t_object *dv, t_symbol *fontname);
t_symbol *jdataview_getfontname(t_object *dv);
void jdataview_setfontsize(t_object *dv, double fsize);
double jdataview_getfontsize(t_object *dv);

double jdataview_getclientfontsize(t_object *dv);

void jdataview_columnheadermouse(t_object *dv, t_object *col, long msg);

int jdataview_getdragenabled(t_object *dv);
void jdataview_setdragenabled(t_object *dv, long way);

void jdataview_setcolumnheadercluemsg(t_object *dv, t_symbol *msg);
t_symbol *jdataview_getcolumnheadercluemsg(t_object *dv);

int jdataview_getdrawgrid(t_object *dv);
void jdataview_setdrawgrid(t_object *dv, int way);
void jdataview_setrowinset(t_object *dv, long top, long bottom);
void jdataview_getrowinset(t_object *dv, long *top, long *bottom);

t_object *jdataview_getsearchcolumn(t_object *dv);
void jdataview_setsearchcolumn(t_object *dv, t_object *col);
void jdataview_setoverridefocus(t_object *dv, long way);
long jdataview_getoverridefocus(t_object *dv);

void jdataview_setreturnkeycolumn(t_object *dv, t_object *col);
t_object *jdataview_getreturnkeycolumn(t_object *dv);

int jdataview_keynavigate(t_object *dv, char *buffer);

// header color

void jdataview_setheaderbgcolor(t_object *dv, t_jrgba *c);
void jdataview_setheadertextcolor(t_object *dv, t_jrgba *c);
void jdataview_getheaderbgcolor(t_object *dv, t_jrgba *c);
void jdataview_getheadertextcolor(t_object *dv, t_jrgba *c);
long jdataview_getheadersolidcolor(t_object *dv);
void jdataview_setheadersolidcolor(t_object *dv, long way);

// context

void jdataview_setcontext(t_object *dv, void *context);
void *jdataview_getcontext(t_object *dv);

// columns access

t_object *jdataview_addcolumn(t_object *dv, t_symbol *name, t_symbol *before, short unused);
t_object *jdataview_addcolumn_hidden(t_object *dv, t_symbol *name, t_symbol *before, short unused);
void *jcolumn_new(void);
void jcolumn_setdataview(t_object *c, t_object *dv);

void jdataview_colname_delete(t_object *dv, t_symbol *name);
void jdataview_deletecolumn(t_object *dv, t_object *col);
t_object *jdataview_getnamedcolumn(t_object *dv, t_symbol *name);
t_object *jdataview_getnthcolumn(t_object *dv, long index);
int jdataview_colname2index(t_object *dv, t_symbol *name);
void jdataview_colname_setvisible(t_object *dv, t_symbol *name, long way);
short jdataview_colname_getvisible(t_object *dv, t_symbol *name);
int jdataview_getnumcolumns(t_object *dv);

// column

int jcolumn_getwidth(t_object *col);
void jcolumn_setwidth(t_object *col, long width);
int jcolumn_getmaxwidth(t_object *col);
void jcolumn_setmaxwidth(t_object *col, long width);
int jcolumn_getminwidth(t_object *col);
void jcolumn_setminwidth(t_object *col, long width);
long jcolumn_getid(t_object *col);
int jcolumn_getautosize(t_object *col);
void jcolumn_setdataview(t_object *col, t_object *dv);
t_symbol *jcolumn_getname(t_object *col);
void jcolumn_setname(t_object *col, t_symbol *name);
void jcolumn_setlabel(t_object *col, t_symbol *label);
t_symbol *jcolumn_getlabel(t_object *col);
void jcolumn_setinsertbefore(t_object *col, t_symbol *before);
t_symbol *jcolumn_getinsertbefore(t_object *col);
void jcolumn_setnumeric(t_object *col, long way);
int jcolumn_getnumeric(t_object *col);
void jcolumn_setcustomsort(t_object *col, t_symbol *msg);
t_symbol *jcolumn_getcustomsort(t_object *col);
void jcolumn_setoverridesort(t_object *col, char val);
char jcolumn_getoverridesort(t_object *col);
void jcolumn_setcustompaint(t_object *col, t_symbol *msg);
t_symbol *jcolumn_getcustompaint(t_object *col);
void jcolumn_setcustommenu(t_object *col, t_symbol *setmsg, t_symbol *resultmsg);
t_symbol *jcolumn_getcustommenu_setmsg(t_object *col);
t_symbol *jcolumn_getcustommenu_resultmsg(t_object *col);
void jcolumn_setsortable(t_object *col, long way);
int jcolumn_getsortable(t_object *col);
void jcolumn_setdraggable(t_object *col, long way);
int jcolumn_getdraggable(t_object *col);
void jcolumn_setinitiallysorted(t_object *col, long way);
int jcolumn_getinitiallysorted(t_object *col);
void jcolumn_sethideable(t_object *col, long way);
int jcolumn_gethideable(t_object *col);
void jcolumn_setvisible(t_object *col, long way);
int jcolumn_getvisible(t_object *col);
void jcolumn_setcasesensitive(t_object *col, long way);
int jcolumn_getcasesensitive(t_object *col);
void jcolumn_setreference(t_object *col, void *ref);
void *jcolumn_getreference(t_object *col);
void jcolumn_setcheckbox(t_object *col, t_symbol *msg);
void jcolumn_setvaluemsg(t_object *col, t_symbol *msg, t_symbol *beginmsg, t_symbol *endmsg);
t_symbol *jcolumn_getvaluemsg(t_object *col);
t_symbol *jcolumn_getbeginchangemsg(t_object *col);
t_symbol *jcolumn_getendchangemsg(t_object *col);
int jcolumn_getcomponent(t_object *col);
void jcolumn_setrowcomponentmsg(t_object *col, t_symbol *msg);
t_symbol *jcolumn_getrowcomponentmsg(t_object *col);
double jcolumn_getindentspacing(t_object *col);
void jcolumn_setindentspacing(t_object *col, double spacing);

void jcolumn_setcellcluemsg(t_object *col, t_symbol *msg);
t_symbol *jcolumn_getcellcluemsg(t_object *col);
t_symbol *jcolumn_getcelltextcolormsg(t_object *col);
void jcolumn_setcelltextcolormsg(t_object *col, t_symbol *msg);
t_symbol *jcolumn_getcelltextstylemsg(t_object *col);
void jcolumn_setcelltextstylemsg(t_object *col, t_symbol *msg);

void jcolumn_setcellentermsg(t_object *col, t_symbol *msg);
void jcolumn_setcellexitmsg(t_object *col, t_symbol *msg);
void jcolumn_setcellmovedmsg(t_object *col, t_symbol *msg);
void jcolumn_setcellclickmsg(t_object *col, t_symbol *msg);

void jcolumn_setshowinfobutton(t_object *col, long way);
long jcolumn_getshowinfobutton(t_object *col);

t_symbol *jcolumn_getcellentermsg(t_object *col);
t_symbol *jcolumn_getcellexitmsg(t_object *col);
t_symbol *jcolumn_getcellmovedmsg(t_object *col);
t_symbol *jcolumn_getcellclickmsg(t_object *col);

// visual update of a change to a column

void jcolumn_update(t_object *col, t_symbol *msg);

// define a column based on a dictionary

t_object *jdataview_addcolumnfromdictionary(t_object *dv, t_object *d);

// adding rows

// a row reference is a way of distinguishing a row to the owning object. This is up to the object whose data is being displayed.
// for example, it could be a pointer to an entry in a database
// or if you are displaying attributes it could be a symbol

typedef void *t_rowref;

void jdataview_addrowtosection(t_object *dv, void *section, t_rowref rr);
void jdataview_addrow(t_object *dv, t_rowref rr);
void jdataview_addrowstosection(t_object *dv, void *section, long count, t_rowref *rrs);
void jdataview_addrows(t_object *dv, long count, t_rowref *rrs);
void jdataview_deleterowfromsection(t_object *dv, void *section, t_rowref rr);
void jdataview_deleterow(t_object *dv, t_rowref rr);
void jdataview_deleterowsfromsection(t_object *dv, void *section, long count, t_rowref *rrs);
void jdataview_deleterows(t_object *dv, long count, t_rowref *rrs);
void jdataview_deleteselectedrows(t_object *dv); 
void jdataview_deleteselectedrowsforview(t_object *dv, t_object *patcherview);
void jdataview_clear(t_object *dv);
int jdataview_getnumrows(t_object *dv);
void jdataview_gettextinrows(t_object *dv, t_rowref *rows, char *cellsep, char **text);
int jdataview_selectedrowcountforview(t_object *dv, t_object *patcherview);
int jdataview_selectedrowcount(t_object *dv);
t_rowref *jdataview_getallrows(t_object *dv);
t_rowref *jdataview_section_getallrows(t_object *dv, void *section, long *count);
t_rowref *jdataview_getselectedrowsforview(t_object *dv, t_object *patcherview);
t_rowref *jdataview_getselectedrows(t_object *dv);
void jdataview_applytoselectedrows(t_object *dv, t_symbol *msg, long bycell);
void jdataview_applytorows(t_object *dv, t_symbol *msg, long bycell, t_rowref *srs);

void jdataview_enablerow(t_object *dv, t_rowref rr, long way);

void jdataview_selectall(t_object *dv);
void jdataview_selectallforview(t_object *dv, t_object *patcherview);
void jdataview_selectnone(t_object *dv);
void jdataview_selectnoneforview(t_object *dv, t_object *patcherview);

// row and column conversion (used by DataViewComponent mostly)

t_object *jdataview_id2column(t_object *dv, int id);
t_symbol *jdataview_id2colname(t_object *dv, int id);
int jdataview_colname2id(t_object *dv, t_symbol *name);
int jdataview_column2id(t_object *dv, t_object *col);
int jdataview_row2id(t_object *dv, t_rowref rr, void **section);
t_rowref jdataview_id2row(t_object *dv, void *section, int id);

void jdataview_showrow(t_object *dv, t_rowref rr);

// cells

void jdataview_celldesc(t_jdataview *x, t_symbol *colname, t_rowref rr, t_celldesc *desc);
void jdataview_selectcellinview(t_object *dv, t_object *pv, t_symbol *colname, t_rowref rr);
void jdataview_selectcell(t_object *dv, t_symbol *colname, t_rowref rr);
int jdataview_getcelltextlength(t_object *dv, t_symbol *colname, t_rowref rr, long *length);
int jdataview_getcelltext(t_object *dv, t_symbol *colname, t_rowref rr, char *text, long maxlen);
int jdataview_getcellunits(t_object *dv, t_symbol *colname, t_rowref rr, char *text, long maxlen);
int jdataview_setcellunits(t_object *dv, t_symbol *colname, t_rowref rr, t_symbol *val);
int jdataview_getcellunitsyms(t_object *dv, t_symbol *colname, t_rowref rr, long *argc, t_atom **argv);
int jdataview_getcelldescription(t_object *dv, t_symbol *colname, t_rowref rr, char *text);
int jdataview_getcellvalue(t_object *dv, t_symbol *colname, t_rowref rr, long *argc, t_atom *argv);
void jdataview_getcelltextcolor(t_object *dv, t_symbol *colname, t_rowref rr, t_jrgba *color);
void jdataview_getcelltextstyle(t_object *dv, t_symbol *colname, t_rowref rr, long *style, long *align);
int jdataview_getcellmenu(t_object *dv, t_symbol *colname, t_rowref rr, long *argc, t_atom *argv, char **enabled, long *currentitemindex);
int jdataview_getcelltooltip(t_object *dv, t_symbol *colname, t_rowref rr, t_rect *cellrect, char *text, long maxlen); 
void jdataview_setcellvalue(t_object *dv, t_symbol *colname, t_rowref rr, long argc, t_atom *argv);
void jdataview_editcell(t_object *dv, t_symbol *colname, t_rowref rr);
int jdataview_iscelltextselected(t_object *dv, char justfocused);
void jdataview_cellclear(t_object *dv);
void jdataview_cellcut(t_object *dv);
void jdataview_cellcopy(t_object *dv);
void jdataview_cellpaste(t_object *dv);

int jdataview_getcellcomponent(t_object *dv, t_symbol *colname, t_rowref rr, long *options, t_symbol **label);
int jdataview_getcellfiletypes(t_object *dv, t_symbol *colname, t_rowref rr, long *count, t_fourcc **types, char *alloc);
t_symbol *jdataview_getcellfilterval(t_object *dv, t_symbol *colname, t_rowref rr);
void jdataview_redrawcell(t_object *dv, t_symbol *colname, t_rowref rr);
void jdataview_begincellchange(t_object *dv, t_symbol *colname, t_rowref rr);
void jdataview_endcellchange(t_object *dv, t_symbol *colname, t_rowref rr);
void jdataview_selected(t_object *dv, t_symbol *colname, t_rowref rr);
void jdataview_selectedrow(t_object *dv, t_rowref rr);
void jdataview_doubleclick(t_object *dv, t_symbol *colname, t_rowref rr);
void jdataview_contextualclick(t_object *dv, t_symbol *colname, t_rowref rr);
void jdataview_getcellicon(t_object *dv, t_symbol *colname, t_rowref rr, t_jsurface **surf);
void jdataview_getrowcolor(t_object *dv, t_rowref rr, long isoddrow, t_jrgba *c);
int jdataview_colorbycell(t_object *dv);
void jdataview_getcellcolor(t_object *dv, t_symbol *colname, t_rowref rr, long isoddrow, t_jrgba *c);
int jdataview_getcustomselectcolor(t_object *dv);
void jdataview_setcustomselectcolor(t_object *dv, int way);
double jdataview_getcellindent(t_object *dv, t_symbol *colname, t_rowref rr);
void jdataview_cellenter(t_object *dv, t_symbol *colname, t_rowref rr, int px, int py);
void jdataview_cellexit(t_object *dv, t_symbol *colname, t_rowref rr, int px, int py);
void jdataview_cellmove(t_object *dv, t_symbol *colname, t_rowref rr, int px, int py);

t_atom_long jdataview_getcelleditable(t_object *dv, t_symbol *colname, t_rowref rr);

long jdataview_getbordercolor(t_object *dv, t_jrgba *c);	// returns non-zero if border color set
void jdataview_setbordercolor(t_object *dv, t_jrgba *c);

long jdataview_getusesystemfont(t_object *dv);
void jdataview_setusesystemfont(t_object *dv, long way);

void jdataview_enablecell(t_object *dv, t_symbol *colname, t_rowref rr, long way);
void jdataview_forcecellvisible(t_object *x, t_symbol *colname, t_rowref rr);
void jdataview_scrolltosection(t_object *dv, void *section);
void jdataview_scrolltotop(t_object *dv);

int jdataview_getpaintcellseparator(t_object *dv);
void jdataview_setpaintcellseparator(t_object *dv, int way);

void jdataview_getcellclue(t_object *dv, t_symbol *colname, t_rowref rr, char **str);


// DataViewComponent calls this for a custom paint method for a column

void jdataview_clientpaintcell(t_object *dv, t_symbol *msg, t_object *pv, t_symbol *colname, t_rowref rr, int width, int height, int rowIsSelected, int rowNumber);

// custom paint method should be declared as:
// void myobject_paint(t_myobject *x, t_object *patcherview, t_symbol *colname, t_rowref rr, int width, int height, int rowIsSelected)
// to obtain the graphics context call patcherview_getjgraphics() on the patcherview arg
// use jcolumn_setcustompaint to set the message symbol for this method for a column

// the jdataview doesn't hold data. It just sends messages to an owning object to display it
// the messages may be cached for speed. The first level interface just defines a textual
// display. Eventually there will be a custom component for a row.

// sorting: columns can be textual (c_numeric == 0) or numeric or they can define a custom sort
// method by calling jcolumn_setcustomsort to a symbol. This symbol names a method that will be
// called to sort the data for this column. It is of the form:
// long myobject_sort(t_rowref a, t_rowref b) -- which will be passed two rowrefs. In addition,
// custom sort clients need to implement the sortdata message, which is passed a pointer to
// a t_privatesortrec. It needs to store this statically as it is sent before the custom sort message is
// received.
void jdataview_getcolumnmenuforcell(t_object *dv, t_symbol *colname, t_rowref rr, long *argc, t_atom **argv, char **enabled);
void jdataview_cellcolumnmenuresult(t_object *dv, t_symbol *colname, t_rowref rr, long result);

void jdataview_sortcolumn(t_object *x, t_symbol *colname, int fwd);
void jdataview_sort(t_object *x, t_symbol *colname, int fwd);
void jdataview_resort(t_object *x);
long jdataview_getsortcolumn(t_object *x);

// selection

void jdataview_selectcell(t_object *dv, t_symbol *colname, t_rowref rr);
void jdataview_selectrow(t_jdataview *x, t_rowref rr);
void jdataview_selectcolumn(t_jdataview *x, t_symbol *colname);
void jdataview_selectallrows(t_jdataview *x);

long jdataview_iscellselected(t_jdataview *x, t_symbol *colname, t_rowref rr);
long jdataview_isrowselected(t_jdataview *x, t_rowref rr);
long jdataview_iscolumnselected(t_jdataview *x, t_symbol *colname);

void jdataview_savecolumnwidths(t_object *dv, t_dictionary **d);
void jdataview_restorecolumnwidths(t_object *dv, t_dictionary *d);

void jdataview_updatefontpanelforclient(t_object *dv, long show);

// utilities for painting

void jdataview_redrawrow(t_object *dv, t_rowref rr);




#ifdef CUSTOMPAINT
void jdataview_getcellrect(t_jdataview *x, t_symbol *colname, t_rowref rr, t_rect *r);
t_max_err jdataview_jgraphics_from_paintcontext(t_jdataview *x, void *ctx, t_jgraphics **g);
#endif

// handle resizing

long jdataview_containersize(t_object *dv, t_object *box, double cw, double ch, double *width, double *height);

void jdataview_forcecellvisible(t_object *x, t_symbol *colname, t_rowref rr);


// messages to the owner

t_object *jdataview_getrowobject(t_object *dv, t_rowref rr);	// return object associated with the row, if any (used for dragging)

void jdataview_entermodalstate(t_object *dv, long way);

void *jdataview_getdragreceiver(t_object *dv);

/*

-- "columncreated": notification of a column being created

void myobject_columncreated(t_myobject *x, t_symbol *colname);

-- "rowadded" / "rowdeleted": notification of a row being added / deleted

void myobject_rowadded(t_myobject *x, t_rowref rr);
void myobject_rowdeleted(t_myobject *x, t_rowref rr);

-- "sortstarted": notification of a sort starting (will get sort messages)

void myobject_sortstarted(t_myobject *x, t_symbol *colname, long direction);

-- "compare": sort the data according to column / direction, return 1 if r1 > r2, -1 if r2 > r1

long myobject_compare(t_myobject *x, t_symbol *colname, long direction, t_rowref r1, t_rowref r2);

-- "gettext": get string to show in a cell

void myobject_gettext(t_myobject *x, t_symbol *colname, t_rowref rr, char *text);

-- "editstarted": notification that editing is starting in a cell

void myobject_editstarted(t_myobject *x, t_symbol *colname, t_rowref rr);

-- "editentered": editing has finished and here is some new text for a cell

void myobject_editenter(t_myobject *x, t_symbol *colname, t_rowref rr, char *newtext);

// plus, a message specific to a button clicked in a cell (this allows for multiple buttons per column)

void myobject_buttonmessage(t_myobject *x, t_symbol *colname, t_rowref rr, t_symbol *msg);

// editing operations, "cutcell", "copycell", "pastecell", "clearcell"

void myobject_cutcell(t_myobject *x, t_symbol *colname, t_rowref rr);
void myobject_copycell(t_myobject *x, t_symbol *colname, t_rowref rr);
void myobject_pastecell(t_myobject *x, t_symbol *colname, t_rowref rr);
void myobject_clearcell(t_myobject *x, t_symbol *colname, t_rowref rr);

// "cutcolumn", "copycolumn", "pastecolumn", "clearcolumn"

void myobject_cutcolumn(t_myobject *x, t_symbol *colname);
void myobject_copycolumn(t_myobject *x, t_symbol *colname);
void myobject_pastecolumn(t_myobject *x, t_symbol *colname);
void myobject_clearcolumn(t_myobject *x, t_symbol *colname);

// "cutrow", "copyrow", "pasterow", "clearrow", "deleterow"

void myobject_cutrow(t_myobject *x, t_rowref rr);
void myobject_copyrow(t_myobject *x, t_rowref rr);
void myobject_pasterow(t_myobject *x, t_rowref rr);
void myobject_clearrow(t_myobject *x, t_rowref rr);
void myobject_deleterow(t_myobject *x, t_rowref rr);

// customization: an object can have a paintcell method instead of displaying text

void myobject_paintcell(t_myobject *x, t_symbol *colname, t_rowref rr, void *ctx);

// implementation notes:

JUCE refreshComponentForCell needs to have the ability to create a custom component given a
class name. How can that be done, with templates? 

Yes you can use template argument passed to new, i.e.,

template<class T>
blah<T>::blah
{
	foo (which could be a member of blah?) = new T;
}

*/

END_USING_C_LINKAGE

#endif // _JDATAVIEW_H_
