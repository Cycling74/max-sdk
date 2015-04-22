#ifndef _JPATCHER_API_H_
#define _JPATCHER_API_H_

#include "jpatcher_syms.h"

BEGIN_USING_C_LINKAGE

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif


#define JPATCHER_API_CURRENT_FILE_VERSION 1


// ddz changed enum below to a mask so it can be returned by clipboard_datatypes()

typedef enum _clipboard_datatype {
	JCLIPBOARD_TYPE_TEXT = 1,
	JCLIPBOARD_TYPE_BINBUF = 2,
	JCLIPBOARD_TYPE_JSON = 4,
	JCLIPBOARD_TYPE_IMAGE = 8,
	JCLIPBOARD_TYPE_JSON_ATTRIBUTES = 16,
	JCLIPBOARD_TYPE_UNKNOWN = 256
} t_clipboard_datatype; 



t_symbol *fontmap_getmapping(t_symbol *from, char *mapped);
double fontinfo_getsize(short oldsize);		// tranlsate max 4.6 font size to max 5 font size
t_symbol *fontinfo_getname(short number);
short fontinfo_getnumber(t_symbol *s);


// Core structs

/**
	Coordinates for specifying a rectangular region.
	@ingroup 	datatypes
	@see		t_pt
	@see		t_size		*/
typedef struct _rect
{
	double x;				///< The horizontal origin
	double y;				///< The vertical origin
	double width;			///< The width
	double height;			///< The height
} t_rect;


/**
	Coordinates for specifying a point.
	@ingroup 	datatypes
	@see		t_rect
	@see		t_size		*/
typedef struct _pt
{
	double x;				///< The horizontal coordinate
	double y;				///< The vertical coordinate
} t_pt;


/**
	Coordinates for specifying the size of a region.
	@ingroup 	datatypes
	@see		t_rect
	@see		t_pt		*/
typedef struct _size
{
	double width;			///< The width
	double height;			///< The height
} t_size;


/**	A color composed of red, green, and blue components.
	Typically such a color is assumed to be completely opaque (with no transparency).
	@ingroup	color
	@see		t_jrgba		*/
typedef struct _jrgb {
	double red;				///< Red component in the range [0.0, 1.0]
	double green;			///< Green component in the range [0.0, 1.0]
	double blue;			///< Blue component in the range [0.0, 1.0]
} t_jrgb;


/**	A color composed of red, green, blue, and alpha components.
	@ingroup color			*/
typedef struct _jrgba {
	double red;				///< Red component in the range [0.0, 1.0]
	double green;			///< Green component in the range [0.0, 1.0]
	double blue;	
	double alpha;			///< Alpha (transparency) component in the range [0.0, 1.0]
} t_jrgba;


/** 
	The t_jboxdrawparams structure. This struct is provided for debugging convenience, 
	but should be considered opaque and is subject to change without notice. 

	@ingroup jbox
*/
typedef struct _jboxdrawparams {
	float		d_inletheight; 
	float		d_inletvoffset;
	float		d_outletheight;
	float		d_outletvoffset; 
	float		d_reserved1;			// was d_inletinset.  unused and can chop but will require rebuild all so for now I'm renaming
	float		d_cornersize;			// how rounded is the box
	float		d_borderthickness;	
	t_jrgba		d_bordercolor; 
	t_jrgba		d_boxfillcolor;
} t_jboxdrawparams; 

#define JBOX_SPOOL_CONTENTS		1
#define JBOX_SPOOL_WHOLEBOX		2

#define JBOX_RELINE_DEFER
#define JBOX_FLAG_READY			0x01
#define JBOX_FLAG_FIRST_PAINT	0x02

/** The t_jbox struct provides the header for a Max user-interface object. 
	This struct should be considered opaque and is subject to change without notice.
	Do not access it's members directly any code.
	
	@ingroup patcher
*/
typedef struct _jbox
{
	t_object 	b_ob;
	void 		*obex;
	t_object	*b_patcher;
	t_rect		b_patching_rect;
	t_rect		b_presentation_rect;
	t_symbol	*b_name;
	t_symbol	*b_id;			// immutable box ID
	t_object	*b_firstin;		// the object, could be the box
	t_object	*b_textfield;	// optional text field. 
	t_symbol	*b_fontname; 
	double		b_fontsize; 
	char*		b_hint; 
	t_jrgba		b_color; 
	double		b_unused;		// we can chop this or make it do something different
	void		*b_binbuf;      // really an atombuf  :)
	long		b_temp;
	char		b_spooled; 
	char		b_hidden;
	char		b_hilitable;
	char		b_background;
	char		b_ignoreclick;
	char		b_bogus;
	char		b_drawfirstin;
	char		b_outline;
	char		b_growy;
	char		b_growboth;
	char		b_nogrow;
	char		b_drawinlast;
	char		b_paintoverchildren;
	char		b_mousedragdelta;		// hide mouse during drag, and send mousedragdelta instead of mousedrag for infinite scrolling
	char		b_presentation;
	char		b_drawiolocked;
	char		b_dragactive; 
	char		b_drawbackground;		
	char		b_hinttrack;
	char		b_fontface;
	char		*b_annotation;
	char		b_opaque;
	char		b_useimagebuffer; 
	char		b_noinspectfirstin;	
	char		b_editactive;			// editing via inspector 
	t_symbol	*b_prototypename;
	char		b_commasupport;
	char		b_reserved1;            // this is actually used and should be renamed!
	char		b_textjustification;
	char		b_reserved3;
	void		*b_ptemp;
} t_jbox;


// selection information -- private
typedef struct _pvselinfo
{
	long nboxselect;
	long nlineselect;
	long nselboxhidden;		// how many of the selected boxes are hidden
	long nsellinehidden;	// how many of the selected lines are hidden
	long ncanignoreclick;		// how many of the selected items could accept the ingore click command
	long ncanrespondtoclick;// how many of the selected items could accept the respond to click command
	long nbg;				// how many of the selected items are in the background
	long nboxcolorable;		// how many respond to the color message
	long nselboxbg;			// how many of the selected boxes are in the background
	long nboxinfo;			// how many of the selected boxes respond to the info message
	long nboxfixwidth;		// how many of the selected boxes respond to the fixwidth message
	long nboxpatcher;		// how many of the selected boxes are patchers
	long nboxpresent;		// how many of the selected boxes are in the presentation
	long nwiretaplines;		// how many of the selected lines have wiretaps (breakpoint, watchpoint, enabled or not)
	long nwatchpointlines;	// how many of the selected lines have watchpoints enabled
	long nbreakpointlines;	// how many of the selected lines have breakpoints enabled
	long nenabledwiretaplines;	// how many of the selected lines are enabled
	long sameclass;		// are all selected items of the same class (true for one object, N patchlines, or N boxes of the same class)
	long editbox;			// is a text box currently being edited
	long nlineswithsegments;// how many of the selected lines have at least one segment
	long nlinesdisabled;	// how many of the selected lines are disabled 
} t_pvselinfo;


// jpatcher interface

/**	Gets the value of a #t_rect attribute, given its parent object and name. 
	Do not use this on a jbox object -- use jbox_get_rect_for_view() instead!

	@ingroup attr
	@param 	o		The attribute's parent object
	@param 	name	The attribute's name
	@param 	rect	The address of a valid #t_rect whose values will be filled-in from the attribute.
	
	@return 		This function returns the error code #MAX_ERR_NONE if successful, 
	 				or one of the other error codes defined in #e_max_errorcodes if unsuccessful.	*/
t_max_err object_attr_get_rect(t_object *o, t_symbol *name, t_rect *rect);

/**	Sets the value of a #t_rect attribute, given its parent object and name. 
	Do not use this on a jbox object -- use jbox_get_rect_for_view() instead!

	@ingroup attr
	@param 	o		The attribute's parent object
	@param 	name	The attribute's name
	@param 	rect	The address of a valid #t_rect whose values will be used to set the attribute.
	
	@return 		This function returns the error code #MAX_ERR_NONE if successful, 
	 				or one of the other error codes defined in #e_max_errorcodes if unsuccessful.	*/
t_max_err object_attr_set_rect(t_object *o, t_symbol *name, t_rect *rect);


/**	Sets the value of a #t_rect attribute, given its parent object and name.
	Do not use this on a jbox object -- use jbox_get_rect_for_view() instead!

	@ingroup attr
	@param 	o		The attribute's parent object
	@param 	attr	The attribute's name
	@param 	x		A double containing the new x position.
	@param 	y		A double containing the new y position.
	@param 	w		A double containing the new width.
	@param 	h		A double containing the new height.

	@return 		This function returns the error code #MAX_ERR_NONE if successful,
	or one of the other error codes defined in #e_max_errorcodes if unsuccessful.	
*/
void object_attr_set_xywh(t_object *o, t_symbol *attr, double x, double y, double w, double h);


/**	Gets the value of a #t_pt attribute, given its parent object and name.

	@ingroup attr
	@param 	o		The attribute's parent object
	@param 	name	The attribute's name
	@param 	pt		The address of a valid #t_pt whose values will be filled-in from the attribute.
	
	@return 		This function returns the error code #MAX_ERR_NONE if successful, 
	 				or one of the other error codes defined in #e_max_errorcodes if unsuccessful.	
*/
t_max_err object_attr_getpt(t_object *o, t_symbol *name, t_pt *pt);


/**	Sets the value of a #t_pt attribute, given its parent object and name. 

	@ingroup attr
	@param 	o		The attribute's parent object
	@param 	name	The attribute's name
	@param 	pt		The address of a valid #t_pt whose values will be used to set the attribute.
	
	@return 		This function returns the error code #MAX_ERR_NONE if successful, 
	 				or one of the other error codes defined in #e_max_errorcodes if unsuccessful.	*/
t_max_err object_attr_setpt(t_object *o, t_symbol *name, t_pt *pt); 


/**	Gets the value of a #t_size attribute, given its parent object and name. 

	@ingroup attr
	@param 	o		The attribute's parent object
	@param 	name	The attribute's name
	@param 	size	The address of a valid #t_size whose values will be filled-in from the attribute.
	
	@return 		This function returns the error code #MAX_ERR_NONE if successful, 
	 				or one of the other error codes defined in #e_max_errorcodes if unsuccessful.	*/
t_max_err object_attr_getsize(t_object *o, t_symbol *name, t_size *size);

/**	Sets the value of a #t_size attribute, given its parent object and name. 

	@ingroup attr
	@param 	o		The attribute's parent object
	@param 	name	The attribute's name
	@param 	size	The address of a valid #t_size whose values will be used to set the attribute.
	
	@return 		This function returns the error code #MAX_ERR_NONE if successful, 
	 				or one of the other error codes defined in #e_max_errorcodes if unsuccessful.	*/
t_max_err object_attr_setsize(t_object *o, t_symbol *name, t_size *size); 


/**	Gets the value of a #t_jrgba attribute, given its parent object and name. 

	@ingroup attr
	@param 	b			The attribute's parent object
	@param 	attrname	The attribute's name
	@param 	prgba		The address of a valid #t_jrgba whose values will be filled-in from the attribute.
	
	@return 			This function returns the error code #MAX_ERR_NONE if successful, 
	 					or one of the other error codes defined in #e_max_errorcodes if unsuccessful.	*/
t_max_err object_attr_getcolor(t_object *b, t_symbol *attrname, t_jrgba *prgba);

/**	Sets the value of a #t_jrgba attribute, given its parent object and name. 

	@ingroup attr
	@param 	b			The attribute's parent object
	@param 	attrname	The attribute's name
	@param 	prgba		The address of a valid #t_jrgba whose values will be used to set the attribute.
	
	@return 			This function returns the error code #MAX_ERR_NONE if successful, 
	 					or one of the other error codes defined in #e_max_errorcodes if unsuccessful.	*/
t_max_err object_attr_setcolor(t_object *b, t_symbol *attrname, t_jrgba *prgba);


/**	Get the value of a #t_jrgba struct, returned as an array of atoms with the values for each component.

	@ingroup color
	@param 	jrgba	The color struct whose color will be retrieved.
	@param 	argc	The address of a variable that will be set with the number of atoms in the argv array.  
					The returned value should be 4.  
					The value of the int should be set to 0 prior to calling this function.
	@param 	argv	The address of a #t_atom pointer that will receive the a new array of atoms set to the values of the jrgba struct.
					The pointer should be set to NULL prior to calling this function.
					There should be 4 atoms returned, representing alpha, red, green, and blue components.
					When you are done using the atoms, you are responsible for freeing the pointer using sysmem_freeptr().
	@return 		This function returns the error code #MAX_ERR_NONE if successful, 
	 				or one of the other error codes defined in #e_max_errorcodes if unsuccessful.	*/
t_max_err jrgba_attr_get(t_jrgba *jrgba, long *argc, t_atom **argv);

/**	Set the value of a #t_jrgba struct, given an array of atoms with the values to use.

	@ingroup color
	@param 	jrgba	The color struct whose color will be set.
	@param 	argc	The number of atoms in the array.  This must be 4.
	@param 	argv	The address of the first of the atoms in the array.  
					There must be 4 atoms, representing alpha, red, green, and blue components.
	
	@return 		This function returns the error code #MAX_ERR_NONE if successful, 
	 				or one of the other error codes defined in #e_max_errorcodes if unsuccessful.	*/
t_max_err jrgba_attr_set(t_jrgba *jrgba, long argc, t_atom *argv);




// various utilities
void set_jrgba_from_palette_index(short index, t_jrgba *jrgba); 
void set_jrgba_from_boxcolor_index(short index, t_jrgba *jrgba); 
short get_boxcolor_index_from_jrgba(t_jrgba *jrgba); 
void jgraphics_clip_rgba(t_jrgba *rgba); 


/**	Open the help patcher for a given instance of an object.
	@ingroup	obj
	@param	x	The object instance for which to open the help patcher.		*/
void object_openhelp(t_object *x);

/**	Open the reference page for a given instance of an object.
	@ingroup	obj
	@param	x	The object instance for which to open the reference page.	*/
void object_openrefpage(t_object *x);

/**	Open a search in the file browser for files with the name of the given object.
	@ingroup	obj
	@param	x	The object instance for which to query.						*/
void object_openquery(t_object *x);


/**	Open the help patcher for a given object class name.
	@ingroup			obj
	@param	classname	The class name for which to open the help patcher.	*/
void classname_openhelp(char *classname);

/**	Open the reference page for a given object class name.
	@ingroup			obj
	@param	classname	The class name for which to open the reference page.*/
void classname_openrefpage(char *classname);

/**	Open a search in the file browser for files with the name of the given class.
	@ingroup			obj
	@param	classname	The class name for which to query.					*/
void classname_openquery(char *classname); 


/**	Find a patcherview at the given screen coords.
	@ingroup	jpatcherview
	@param	x	The horizontal coordinate at which to find a patcherview.
	@param	y	The vertical coordinate at which to find a patcherview.
	@return		A pointer to the patcherview at the specified location, 
				or NULL if no patcherview exists at that location.			*/
t_object* patcherview_findpatcherview(int x, int y);


// private (initialize object palette -- separated so it can be moved to optimize startup experience)
void patcherview_makepalette(void);


// Utilities to get/set patcher attributes

/**	Determine of a #t_object* is a patcher object.
	@ingroup	jpatcher
	@param	p	The object pointer to test.
	@return		Returns true if the object is a patcher, otherwise returns non-zero.	*/
int jpatcher_is_patcher(t_object *p);

/**	If a patcher is inside a box, return its box.
 	@ingroup	jpatcher
	@param	p	The patcher to be queried.
	@return		A pointer to the box containing the patcher, otherwise NULL.	*/
t_object* jpatcher_get_box(t_object *p);

/**	Determine the number of boxes in a patcher.
	@ingroup	jpatcher
	@param	p	The patcher to be queried.
	@return		The number of boxes in the patcher.	*/
long jpatcher_get_count(t_object *p);


/**	To determine whether a patcher is currently in a locked state, 
	you should actually query the patcherview using patcherview_get_locked().
	This is because, for any given patcher, there may be multiple views with differing locked states.
	
	@param	p	The patcher to be queried.
	@return		True if the patcher is locked, otherwise false.
	@see		patcherview_get_locked()	*/
char jpatcher_get_locked(t_object *p); 

/**	Lock or unlock a patcher.
	@ingroup	jpatcher
	@param	p	The patcher whose locked state will be changed.
	@param	c	Pass true to lock a patcher, otherwise pass false.
	@return		A Max error code.	*/
t_max_err jpatcher_set_locked(t_object *p, char c);


/**	Determine whether a patcher is currently in presentation mode.
	@ingroup	jpatcher
	@param	p	The patcher to be queried.
	@return		True if the patcher is in presentation mode, otherwise false.	*/
char jpatcher_get_presentation(t_object *p);

/**	Set a patcher to presentation mode.
	@ingroup	jpatcher
	@param	p	The patcher whose locked state will be changed.
	@param	c	Pass true to switch the patcher to presentation mode, otherwise pass false.
	@return		A Max error code.	*/
t_max_err jpatcher_set_presentation(t_object *p, char c);


/**	Get the first box in a patcher.
	All boxes in a patcher are maintained internally in a #t_linklist.
	Use this function together with jbox_get_nextobject() to traverse a patcher. 	
	@ingroup	jpatcher
	@param	p	The patcher to be queried.
	@return		The first box in a patcher.
	@see		jbox_get_prevobject()
				jbox_get_nextobject()
				jpatcher_get_lastobject()			*/
t_object* jpatcher_get_firstobject(t_object *p);

/**	Get the last box in a patcher.
	All boxes in a patcher are maintained internally in a #t_linklist.
	Use this function together with jbox_get_prevobject() to traverse a patcher. 	
	@ingroup	jpatcher
	@param	p	The patcher to be queried.
	@return		The last box in a patcher.
	@see		jbox_get_prevobject()
				jbox_get_nextobject()
				jpatcher_get_firstobject()			*/
t_object* jpatcher_get_lastobject(t_object *p);


/**	Get the first line (patch-cord) in a patcher.
	All lines in a patcher are maintained internally in a #t_linklist.
	Use this function to begin traversing a patcher's lines. 	
	@ingroup	jpatcher
	@param	p	The patcher to be queried.
	@return		The first jpatchline in a patcher.	*/
t_object* jpatcher_get_firstline(t_object *p);

/**	Get the first view (jpatcherview) for a given patcher.
	All views of a patcher are maintained internally as a #t_linklist.
	Use this function to begin traversing a patcher's views. 	
	@ingroup	jpatcher
	@param	p	The patcher to be queried.
	@return		The first view of a patcher.		*/
t_object* jpatcher_get_firstview(t_object *p);


/**	Retrieve a patcher's title.
	@ingroup	jpatcher
	@param	p	The patcher to be queried.
	@return		The patcher's title.				*/
t_symbol* jpatcher_get_title(t_object *p);

/**	Set a patcher's title.
	@ingroup	jpatcher
	@param	p	The patcher whose locked state will be changed.
	@param	ps	The new title for the patcher.
	@return		A Max error code.	*/
t_max_err jpatcher_set_title(t_object *p, t_symbol *ps);


/**	Retrieve a patcher's name.
	@ingroup	jpatcher
	@param	p	The patcher to be queried.
	@return		The patcher's name.					*/
t_symbol* jpatcher_get_name(t_object *p);

/**	Retrieve a patcher's file path.
	@ingroup	jpatcher
	@param	p	The patcher to be queried.
	@return		The patcher's file path.			*/
t_symbol* jpatcher_get_filepath(t_object *p);

/**	Retrieve a patcher's file name.
	@ingroup	jpatcher
	@param	p	The patcher to be queried.
	@return		The patcher's file name.			*/
t_symbol* jpatcher_get_filename(t_object *p);


/**	Determine whether a patcher's dirty bit has been set.
	@ingroup	jpatcher
	@param	p	The patcher to be queried.
	@return		True if the patcher is dirty, otherwise false.	*/
char jpatcher_get_dirty(t_object *p);

/**	Set a patcher's dirty bit.
	@ingroup	jpatcher
	@param	p	The patcher whose dirty bit will be set.
	@param	c	The new value for the patcher's dirty bit (pass true or false).
	@return		A Max error code.	*/
t_max_err jpatcher_set_dirty(t_object *p, char c);


/**	Determine whether a patcher's background layer is locked.
	@ingroup	jpatcher
	@param	p	The patcher to be queried.
	@return		True if the background layer is locked, otherwise false.	*/
char jpatcher_get_bglocked(t_object *p);

/**	Set whether a patcher's background layer is locked.
	@ingroup	jpatcher
	@param	p	The patcher whose dirty bit will be set.
	@param	c	Pass true to lock the patcher's background layer, otherwise pass false.
	@return		A Max error code.	*/
t_max_err jpatcher_set_bglocked(t_object *p, char c);


/**	Determine whether a patcher's background layer is hidden.
	@ingroup	jpatcher
	@param	p	The patcher to be queried.
	@return		True if the background layer is hidden, otherwise false.	*/
char jpatcher_get_bghidden(t_object *p);

/**	Set whether a patcher's background layer is hidden.
	@ingroup	jpatcher
	@param	p	The patcher whose dirty bit will be set.
	@param	c	Pass true to hide the patcher's background layer, otherwise pass false.
	@return		A Max error code.	*/
t_max_err jpatcher_set_bghidden(t_object *p, char c);


/**	Determine whether a patcher's foreground layer is hidden.
	@ingroup	jpatcher
	@param	p	The patcher to be queried.
	@return		True if the foreground layer is hidden, otherwise false.	*/
char jpatcher_get_fghidden(t_object *p);

/**	Set whether a patcher's foreground layer is hidden.
	@ingroup	jpatcher
	@param	p	The patcher whose dirty bit will be set.
	@param	c	Pass true to hide the patcher's foreground layer, otherwise pass false.
	@return		A Max error code.	*/
t_max_err jpatcher_set_fghidden(t_object *p, char c);


// TODO: unused?
// t_object* jpatcher_get_font(t_object *p);


/**	Retrieve a patcher's editing background color.
	@ingroup		jpatcher
	@param	p		The patcher to be queried.
	@param	prgba	The address of a valid #t_jrgba struct that will be filled-in with the current patcher color values.
	@return			A Max error code.			*/
t_max_err jpatcher_get_editing_bgcolor(t_object *p, t_jrgba *prgba);

/**	Set a patcher's editing background color.
	@ingroup		jpatcher
	@param	p		The patcher to be queried.
	@param	prgba	The address of a #t_jrgba struct containing the new color to use.
	@return			A Max error code.			*/
t_max_err jpatcher_set_editing_bgcolor(t_object *p, t_jrgba *prgba);


/**	Retrieve a patcher's unlocked background color.
	@ingroup		jpatcher
	@param	p		The patcher to be queried.
	@param	prgba	The address of a valid #t_jrgba struct that will be filled-in with the current patcher color values.
	@return			A Max error code.			*/
t_max_err jpatcher_get_bgcolor(t_object *p, t_jrgba *prgba);

/**	Retrieve a patcher's locked background color.
	@ingroup		jpatcher
	@param	p		The patcher to be queried.
	@param	prgba	The address of a valid #t_jrgba struct that will be filled-in with the current patcher color values.
	@return			A Max error code.			*/
t_max_err jpatcher_get_locked_bgcolor(t_object *p, t_jrgba *prgba);

/**	Set a patcher's unlocked background color.
	@ingroup		jpatcher
	@param	p		The patcher to be queried.
	@param	prgba	The address of a #t_jrgba struct containing the new color to use.
	@return			A Max error code.			*/
t_max_err jpatcher_set_bgcolor(t_object *p, t_jrgba *prgba);

/**	Set a patcher's locked background color.
	@ingroup		jpatcher
	@param	p		The patcher to be queried.
	@param	prgba	The address of a #t_jrgba struct containing the new color to use.
	@return			A Max error code.			*/
t_max_err jpatcher_set_locked_bgcolor(t_object *p, t_jrgba *prgba);


/**	Retrieve a patcher's grid size.
	@ingroup			jpatcher
	@param	p			The patcher to be queried.
	@param	gridsizeX	The address of a double that will be set to the current horizontal grid spacing for the patcher.
	@param	gridsizeY	The address of a double that will be set to the current vertical grid spacing for the patcher.
	@return				A Max error code.			*/
t_max_err jpatcher_get_gridsize(t_object *p, double *gridsizeX, double *gridsizeY);

/**	Set a patcher's grid size.
	@ingroup			jpatcher
	@param	p			The patcher to be queried.
	@param	gridsizeX	The new horizontal grid spacing for the patcher.
	@param	gridsizeY	The new vertical grid spacing for the patcher.
	@return				A Max error code.			*/
t_max_err jpatcher_set_gridsize(t_object *p, double gridsizeX, double gridsizeY);


// private
t_object* jpatcher_get_controller(t_object *p);


/**	Delete an object that is in a patcher.
	@ingroup			jpatcher
	@param	p			The patcher.
	@param	b			The object box to delete.	*/
void jpatcher_deleteobj(t_object *p, t_jbox *b);


/**	Given a patcher, return its parent patcher.	
	@ingroup	jpatcher
	@param	p	The patcher to be queried.
	@return		The patcher's parent patcher, if there is one.  
				If there is no parent patcher (this is a top-level patcher) then NULL is returned. */
t_object* jpatcher_get_parentpatcher(t_object *p);

/**	Given a patcher, return the top-level patcher for the tree in which it exists.
	@ingroup	jpatcher
	@param	p	The patcher to be queried.
	@return		The patcher's top-level parent patcher.   */
t_object* jpatcher_get_toppatcher(t_object *p);

/**	Given a patcher, return the patcher that will be responsible for holding the parameter hub.
 @ingroup	jpatcher
 @param	p	The patcher to be queried.
 @return	The patcher's parameter hub holder.   */
t_object* jpatcher_get_hubholder(t_object *p);

// unused
t_symbol* jpatcher_get_maxclass(t_object *p);
t_symbol* jpatcher_get_parentclass(t_object *p); 


/**	Query a patcher to determine its location and size.
	@ingroup	jpatcher
	@param	p	A pointer to a patcher instance.
	@param	pr	The address of valid #t_rect whose values will be filled-in upon return.
	@return		A Max error code.	*/
t_max_err jpatcher_get_rect(t_object *p, t_rect *pr);

/**	Set a patcher's location and size.
	@ingroup	jpatcher
	@param	p	A pointer to a patcher instance.
	@param	pr	The address of a #t_rect with the new position and size.
	@return		A Max error code.	*/
t_max_err jpatcher_set_rect(t_object *p, t_rect *pr);


/**	Query a patcher to determine the location and dimensions of its window when initially opened.
	@ingroup	jpatcher
	@param	p	A pointer to a patcher instance.
	@param	pr	The address of valid #t_rect whose values will be filled-in upon return.
	@return		A Max error code.	*/
t_max_err jpatcher_get_defrect(t_object *p, t_rect *pr);

/**	Set a patcher's default location and size.
	@ingroup	jpatcher
	@param	p	A pointer to a patcher instance.
	@param	pr	The address of a #t_rect with the new position and size.
	@return		A Max error code.	*/
t_max_err jpatcher_set_defrect(t_object *p, t_rect *pr);


// private
char jpatcher_get_noedit(t_object *p); 
t_object *jpatcher_get_collective(t_object *p); 
char jpatcher_get_cansave(t_object *p); 


/**	Generate a unique name for a box in patcher.  
	@ingroup			jpatcher
	@param	p			A pointer to a patcher instance.
	@param	classname	The name of an object's class.
	@return				The newly-generated unique name.
	@remark				This is the function used by pattr to assign names to objects in a patcher.	*/
t_symbol *jpatcher_uniqueboxname(t_object *p, t_symbol *classname);


// private
short jpatcher_getboxfont(t_object *p, short fnum, double *fsize, t_symbol **fontname);


/**	Return the name of the default font used for new objects in a patcher.
	@ingroup			jpatcher
	@param	p			A pointer to a patcher instance.
	@return				The name of the default font used for new objects in a patcher.
*/
t_symbol *jpatcher_get_default_fontname(t_object *p);


/**	Return the size of the default font used for new objects in a patcher.
	@ingroup			jpatcher
	@param	p			A pointer to a patcher instance.
	@return				The size of the default font used for new objects in a patcher.
*/
float jpatcher_get_default_fontsize(t_object *p);


/**	Return the index of the default font face used for new objects in a patcher.
	@ingroup			jpatcher
	@param	p			A pointer to a patcher instance.
	@return				The index of the default font face used for new objects in a patcher.
*/
long jpatcher_get_default_fontface(t_object *p);


// private
t_max_err jpatcher_set_imprint(t_object *p, char c);
char jpatcher_get_imprint(t_object *p);

// private (only used by jdatatest)
void jpatcher_addboxlistener(t_object *p, t_object *listener);
void jpatcher_removeboxlistener(t_object *p, t_object *listener);


/**	Return the file version of the patcher.
	@ingroup	jpatcher
	@param	p	A pointer to the patcher whose version number is desired.
	@return		The file version number.	*/
long jpatcher_get_fileversion(t_object *p);

/**	Return the file version for any new patchers, e.g. the current version created by Max.
	@ingroup	jpatcher
	@return		The file version number.	*/
long jpatcher_get_currentfileversion(void);




// Utilities to get/set box attributes

/**	Find the rect for a box in a given patcherview.
	@ingroup			jbox
	@param	box			The box whose rect will be fetched.
	@param	patcherview	A patcherview in which the box exists.
	@param	rect		The address of a valid #t_rect whose members will be filled in by this function.
	@return				A Max error code.		*/
t_max_err jbox_get_rect_for_view(t_object *box, t_object *patcherview, t_rect *rect);

/**	Change the rect for a box in a given patcherview.
	@ingroup			jbox
	@param	box			The box whose rect will be changed.
	@param	patcherview	A patcherview in which the box exists.
	@param	rect		The address of a valid #t_rect that will replace the current values used by the box in the given view.
	@return				A Max error code.		*/
t_max_err jbox_set_rect_for_view(t_object *box, t_object *patcherview, t_rect *rect);

/**	Find the rect for a box with a given attribute name.
	@ingroup			jbox
	@param	box			The box whose rect will be fetched.
	@param	which		The name of the rect attribute to be fetched, for example <tt>_sym_presentation_rect</tt> or <tt>_sym_patching_rect</tt>.
	@param	pr			The address of a valid #t_rect whose members will be filled in by this function.
	@return				A Max error code.		*/
t_max_err jbox_get_rect_for_sym(t_object *box, t_symbol *which, t_rect *pr);

/**	Change the rect for a box with a given attribute name.
	@ingroup			jbox
	@param	box			The box whose rect will be changed.
	@param	which		The name of the rect attribute to be changed, for example <tt>_sym_presentation_rect</tt> or <tt>_sym_patching_rect</tt>.
	@param	pr			The address of a valid #t_rect that will replace the current values used by the box.
	@return				A Max error code.		*/
t_max_err jbox_set_rect_for_sym(t_object *box, t_symbol *which, t_rect *pr);


/**	Set both the presentation rect and the patching rect.
	@ingroup		jbox
	@param	box		The box whose rect will be changed.
	@param	pr		The address of a #t_rect with the new rect values.
 	@return			A Max error code.	*/
t_max_err jbox_set_rect(t_object *box, t_rect *pr);

/**	Retrieve the patching rect of a box.
	@ingroup		jbox
	@param	box		The box whose rect values will be retrieved.
	@param	pr		The address of a valid #t_rect whose values will be filled in.
 	@return			A Max error code.	*/
t_max_err jbox_get_patching_rect(t_object *box, t_rect *pr);		 

/**	Change the patching rect of a box.
	@ingroup		jbox
	@param	box		The box whose rect will be changed.
	@param	pr		The address of a #t_rect with the new rect values.
 	@return			A Max error code.	*/
t_max_err jbox_set_patching_rect(t_object *box, t_rect *pr);		 

/**	Retrieve the presentation rect of a box.
	@ingroup		jbox
	@param	box		The box whose rect values will be retrieved.
	@param	pr		The address of a valid #t_rect whose values will be filled in.
 	@return			A Max error code.	*/
t_max_err jbox_get_presentation_rect(t_object *box, t_rect *pr); 

/**	Change the presentation rect of a box.
	@ingroup		jbox
	@param	box		The box whose rect will be changed.
	@param	pr		The address of a #t_rect with the new rect values.
 	@return			A Max error code.	*/
t_max_err jbox_set_presentation_rect(t_object *box, t_rect *pr); 


/**	Set the position of a box for both the presentation and patching views.
	@ingroup		jbox
	@param	box		The box whose position will be changed.
	@param	pos		The address of a #t_pt with the new x and y values.
 	@return			A Max error code.	*/
t_max_err jbox_set_position(t_object *box, t_pt *pos);

/**	Fetch the position of a box for the patching view.
	@ingroup		jbox
	@param	box		The box whose position will be retrieved.
	@param	pos		The address of a valid #t_pt whose x and y values will be filled in.
 	@return			A Max error code.	*/
t_max_err jbox_get_patching_position(t_object *box, t_pt *pos);	 

/**	Set the position of a box for the patching view.
	@ingroup		jbox
	@param	box		The box whose positon will be changed.
	@param	pos		The address of a #t_pt with the new x and y values.
 	@return			A Max error code.	*/
t_max_err jbox_set_patching_position(t_object *box, t_pt *pos);		 

/**	Fetch the position of a box for the presentation view.
	@ingroup		jbox
	@param	box		The box whose position will be retrieved.
	@param	pos		The address of a valid #t_pt whose x and y values will be filled in.
 	@return			A Max error code.	*/
t_max_err jbox_get_presentation_position(t_object *box, t_pt *pos); 

/**	Set the position of a box for the presentation view.
	@ingroup		jbox
	@param	box		The box whose rect will be changed.
	@param	pos		The address of a #t_pt with the new x and y values.
 	@return			A Max error code.	*/
t_max_err jbox_set_presentation_position(t_object *box, t_pt *pos); 


/**	Set the size of a box for both the presentation and patching views.
	@ingroup		jbox
	@param	box		The box whose size will be changed.
	@param	size	The address of a #t_size with the new size values.
 	@return			A Max error code.	*/
t_max_err jbox_set_size(t_object *box, t_size *size);

/**	Fetch the size of a box for the patching view.
	@ingroup		jbox
	@param	box		The box whose size will be retrieved.
	@param	size	The address of a valid #t_size whose width and height values will be filled in.
 	@return			A Max error code.	*/
t_max_err jbox_get_patching_size(t_object *box, t_size *size);	

/**	Set the size of a box for the patching view.
	@ingroup		jbox
	@param	box		The box whose size will be changed.
	@param	size	The address of a #t_size with the new width and height values.
 	@return			A Max error code.	*/
t_max_err jbox_set_patching_size(t_object *box, t_size *size);		 

/**	Fetch the size of a box for the presentation view.
	@ingroup		jbox
	@param	box		The box whose size will be retrieved.
	@param	size	The address of a valid #t_size whose width and height values will be filled in.
 	@return			A Max error code.	*/
t_max_err jbox_get_presentation_size(t_object *box, t_size *size); 

/**	Set the size of a box for the presentation view.
	@ingroup		jbox
	@param	box		The box whose size will be changed.
	@param	size	The address of a #t_size with the new width and height values.
 	@return			A Max error code.	*/
t_max_err jbox_set_presentation_size(t_object *box, t_size *size); 




/** Retrieve the name of the class of the box's object.
	@ingroup		jbox
	@param	b		The box to query.
	@return			The name of the class of the box's object.		*/
t_symbol* jbox_get_maxclass(t_object *b);

/** Retrieve a pointer to the box's object.
	@ingroup		jbox
	@param	b		The box to query.
	@return			A pointer to the box's object.		*/
t_object* jbox_get_object(t_object *b);

/** Retrieve a box's patcher.
	@ingroup		jbox
	@param	b		The box to query.
	@return			If the box has a patcher, the patcher's pointer is returned.  
					Otherwise NULL is returned.		*/
t_object* jbox_get_patcher(t_object *b); 


/** Retrieve a box's 'hidden' attribute.
	@ingroup		jbox
	@param	b		The box to query.
	@return			True if the box is hidden, otherwise false.		*/
char jbox_get_hidden(t_object *b);

/** Set a box's 'hidden' attribute.
	@ingroup		jbox
	@param	b		The box to query.
	@param	c		Set to true to hide the box, otherwise false.
	@return			A Max error code.		*/
t_max_err jbox_set_hidden(t_object *b, char c);


/** Retrieve a box's 'fontname' attribute.
	@ingroup		jbox
	@param	b		The box to query.
	@return			The font name.		*/
t_symbol* jbox_get_fontname(t_object *b);

/** Set a box's 'fontname' attribute.
	@ingroup		jbox
	@param	b		The box to query.
	@param	ps		The font name.  Note that the font name may be case-sensitive.
	@return			A Max error code.		*/
t_max_err jbox_set_fontname(t_object *b, t_symbol *ps); 


/** Retrieve a box's 'fontsize' attribute.
	@ingroup		jbox
	@param	b		The box to query.
	@return			The font size in points.		*/
double jbox_get_fontsize(t_object *b);

/** Set a box's 'fontsize' attribute.
	@ingroup		jbox
	@param	b		The box to query.
	@param	d		The fontsize in points.
	@return			A Max error code.		*/
t_max_err jbox_set_fontsize(t_object *b, double d); 


/** Retrieve a box's 'color' attribute.
	@ingroup		jbox
	@param	b		The box to query.
	@param	prgba	The address of a valid #t_rect whose values will be filled-in upon return.
	@return			A Max error code.		*/
t_max_err jbox_get_color(t_object *b, t_jrgba *prgba);

/** Set a box's 'color' attribute.
	@ingroup		jbox
	@param	b		The box to query.
	@param	prgba	The address of a #t_rect containing the desired color for the box/object.
	@return			A Max error code.		*/
t_max_err jbox_set_color(t_object *b, t_jrgba *prgba); 


/**	Retrieve a box's hint text as a symbol.
	@ingroup	jbox
	@param	b	The box to query.
	@return		The box's hint text.		*/
t_symbol *jbox_get_hint(t_object *b); 

/**	Set a box's hint text using a symbol.
	@ingroup	jbox
	@param	b	The box to query.
	@param	s	The new text to use for the box's hint.
	@return		A Max error code.			*/
t_max_err jbox_set_hint(t_object *b, t_symbol *s); 


/**	Retrieve a box's hint text as a C-string.
	@ingroup	jbox
	@param	bb	The box to query.
	@return		The box's hint text.		*/
char *jbox_get_hintstring(t_object *bb);

/**	Set a box's hint text using a C-string.
	@ingroup	jbox
	@param	bb	The box to query.
	@param	s	The new text to use for the box's hint.
	@return		A Max error code.			*/
void jbox_set_hintstring(t_object *bb, char *s);


char jbox_get_hinttrack(t_object *b); 
t_max_err jbox_set_hinttrack(t_object *b, char h); 


/** Retrieve a box's annotation string, if the user has given it an annotation.
	@ingroup	jbox
	@param	bb	The box to query.
	@return		The user-created annotation string for a box, or NULL if no string exists.		*/
char *jbox_get_annotation(t_object *bb);

/** Set a box's annotation string.
	@ingroup	jbox
	@param	bb	The box to query.
	@param	s	The annotation string for the box.
	@return		A Max error code.		*/
void jbox_set_annotation(t_object *bb, char *s);


/** The next box in the patcher's (linked) list of boxes.
	@ingroup	jbox
	@param	b	The box to query.
	@return		The next box in the list.		*/
t_object* jbox_get_nextobject(t_object *b);

/** The previous box in the patcher's (linked) list of boxes.
	@ingroup	jbox
	@param	b	The box to query.
	@return		The next box in the list.		*/
t_object* jbox_get_prevobject(t_object *b);


// not implemented?
// t_symbol* jbox_get_f(t_object *b);


/** Retrieve a box's scripting name.
	@ingroup	jbox
	@param	b	The box to query.
	@return		The box's scripting name.		*/
t_symbol* jbox_get_varname(t_object *b);

/** Set a box's scripting name.
	@ingroup	jbox
	@param	b	The box to query.
	@param	ps	The new scripting name for the box.
	@return		A Max error code.		*/
t_max_err jbox_set_varname(t_object *b, t_symbol *ps);


/** Retrieve a boxes unique id.
	@ingroup	jbox
	@param	b	The box to query.
	@return		The unique id of the object.  This is a symbol that is referenced, for example, by patchlines.		*/
t_symbol* jbox_get_id(t_object *b);


/** Retrieve a box flag value from a box.
	@ingroup	jbox
	@param	b	The box to query.
	@return		The value of the canhilite bit in the box's flags.		*/
char jbox_get_canhilite(t_object *b);


/** Determine whether a box is located in the patcher's background layer.
	@ingroup	jbox
	@param	b	The box to query.
	@return		Zero if the object is in the foreground, otherwise non-zero.		*/
char jbox_get_background(t_object *b);

/** Set whether a box should be in the background or foreground layer of a patcher.
	@ingroup	jbox
	@param	b	The box to query.
	@param	c	Pass zero to tell the box to appear in the foreground, or non-zero to indicate that the box should be in the background layer.
	@return		A Max error code.		*/
t_max_err jbox_set_background(t_object *b, char c);


/** Determine whether a box ignores clicks.
	@ingroup	jbox
	@param	b	The box to query.
	@return		Zero if the object responds to clicks, otherwise non-zero.		*/
char jbox_get_ignoreclick(t_object *b);

/** Set whether a box ignores clicks.
	@ingroup	jbox
	@param	b	The box to query.
	@param	c	Pass zero to tell the box to respond to clicks, or non-zero to indicate that the box should ignore clicks.
	@return		A Max error code.		*/
t_max_err jbox_set_ignoreclick(t_object *b, char c);


/** Determine whether a box draws its first inlet.
	@ingroup	jbox
	@param	b	The box to query.
	@return		Zero if the inlet is not drawn, otherwise non-zero.		*/
char jbox_get_drawfirstin(t_object *b);


/** Determine whether a box draws an outline.
	@ingroup	jbox
	@param	b	The box to query.
	@return		Zero if the outline is not drawn, otherwise non-zero.		*/
char jbox_get_outline(t_object *b);

/** Set whether a box draws an outline.
	@ingroup	jbox
	@param	b	The box to query.
	@param	c	Pass zero to hide the outline, or non-zero to indicate that the box should draw the outline.
	@return		A Max error code.		*/
t_max_err jbox_set_outline(t_object *b, char c);


/** Retrieve a box flag value from a box.
	@ingroup	jbox
	@param	b	The box to query.
	@return		The value of the growy bit in the box's flags.		*/
char jbox_get_growy(t_object *b);

/** Retrieve a box flag value from a box.
	@ingroup	jbox
	@param	b	The box to query.
	@return		The value of the growboth bit in the box's flags.	*/
char jbox_get_growboth(t_object *b);

/** Retrieve a box flag value from a box.
	@ingroup	jbox
	@param	b	The box to query.
	@return		The value of the nogrow bit in the box's flags.		*/
char jbox_get_nogrow(t_object *b);

/**	Retrieve a box flag value from a box.
	@ingroup	jbox
	@param	b	The box to query.
	@return		The value of the drawinlast bit in the box's flags.	*/
char jbox_get_drawinlast(t_object *b);


// private?
char jbox_get_mousedragdelta(t_object *b);
t_max_err jbox_set_mousedragdelta(t_object *b, char c);


/**	Retrieve a pointer to a box's textfield.
	@ingroup	jbox
	@param	b	The box to query.
	@return		The textfield for the box, assuming it has one.  
				If the box does not own a textfield then NULL is returned. */
t_object* jbox_get_textfield(t_object *b);


// private
long jbox_get_understanding(t_object *b, t_symbol *msg);


/**	Determine if a box is included in the presentation view.
	@ingroup	jbox
	@param	b	The box to query.
	@return		Non-zero if in presentation mode, otherwise zero.		*/
char jbox_get_presentation(t_object *b);

/**	Determine if a box is included in the presentation view.
	@ingroup	jbox
	@param	b	The box to query.
	@param	c	Pass zero to remove a box from the presention view, or non-zero to add it to the presentation view.
	@return		Non-zero if in presentation mode, otherwise zero.		*/
t_max_err jbox_set_presentation(t_object *b, char c);


// private
t_object *jbox_get_autocompletion(t_object *b);
t_symbol *jbox_get_prototypename(t_object *b);
void jbox_set_prototypename(t_object *b, t_symbol *name);
t_atom_long jclipboard_datatypes(void);
void jbox_validaterects(t_jbox *b);



// utilities to get/set patchline attributes

typedef enum _patchline_updatetype {
	JPATCHLINE_DISCONNECT=0,
	JPATCHLINE_CONNECT=1,
	JPATCHLINE_ORDER=2
} t_patchline_updatetype;
	
/**	Retrieve a patchline's starting point.
	@ingroup	jpatchline
	@param	l	A pointer to the patchline's instance.
	@param	x	The address of a variable to hold the x-coordinate of the starting point's position upon return.
	@param	y	The address of a variable to hold the y-coordinate of the starting point's position upon return.
	@return		A Max error code.	*/
t_max_err jpatchline_get_startpoint(t_object *l, double *x, double *y);

/**	Retrieve a patchline's ending point.
	@ingroup	jpatchline
	@param	l	A pointer to the patchline's instance.
	@param	x	The address of a variable to hold the x-coordinate of the ending point's position upon return.
	@param	y	The address of a variable to hold the y-coordinate of the ending point's position upon return.
	@return		A Max error code.	*/
t_max_err jpatchline_get_endpoint(t_object *l, double *x, double *y);

/**	Determine the number of midpoints (segments) in a patchline.
	@ingroup	jpatchline
	@param	l	A pointer to the patchline's instance.
	@return		The number of midpoints in the patchline.	*/
long jpatchline_get_nummidpoints(t_object *l); 

char jpatchline_get_pending(t_object *l); 


/**	Return the object box from which a patchline originates.
	@ingroup	jpatchline
	@param	l	A pointer to the patchline's instance.
	@return		The object box from which the patchline originates.	*/
t_object* jpatchline_get_box1(t_object *l); 

/**	Return the outlet number of the originating object box from which a patchline begins.
	@ingroup	jpatchline
	@param	l	A pointer to the patchline's instance.
	@return		The outlet number.	*/
long jpatchline_get_outletnum(t_object *l);


/**	Return the destination object box for a patchline.
	@ingroup	jpatchline
	@param	l	A pointer to the patchline's instance.
	@return		The destination object box for a patchline.	*/
t_object* jpatchline_get_box2(t_object *l); 

/**	Return the inlet number of the destination object box to which a patchline is connected.
	@ingroup	jpatchline
	@param	l	A pointer to the patchline's instance.
	@return		The inlet number.	*/
long jpatchline_get_inletnum(t_object *l);


// private?
double jpatchline_get_straightthresh(t_object *l);
t_max_err jpatchline_set_straightthresh(t_object *l, double d);

// private?
char jpatchline_get_straightstart(t_object *l); 
char jpatchline_get_straightend(t_object *l); 

// private?
t_max_err jpatchline_set_straightstart(t_object *l, char c); 
t_max_err jpatchline_set_straightend(t_object *l, char c);


/**	Given a patchline, traverse to the next patchline in the (linked) list.
	@ingroup		jpatchline
	@param	b		A patchline instance.
	@return			The next patchline.
					If the current patchline is at the end (tail) of the list, then NULL is returned.
*/
t_object* jpatchline_get_nextline(t_object *b);


/**	Determine if a patch line is hidden.
	@ingroup		jpatchline
	@param	l		A patchline instance.
	@return			Zero if the patchline is visible, non-zero if it is hidden.
*/
char jpatchline_get_hidden(t_object *l); 

/**	Set a patchline's visibility.
	@ingroup		jpatchline
	@param	l		A patchline instance.
	@param	c		Pass 0 to make a patchline visible, or non-zero to hide it.
	@return			An error code.
*/
t_max_err jpatchline_set_hidden(t_object *l, char c); 


/**	Get the color of a patch line.
	@ingroup		jpatchline
	@param	l		A patchline instance.
	@param	prgba	The address of a valid #t_jrgba struct that will be filled with the color values of the patch line.
	@return			An error code.
*/
t_max_err jpatchline_get_color(t_object *l, t_jrgba *prgba); 

/**	Set the color of a patch line.
	@ingroup		jpatchline
	@param	l		A patchline instance.
	@param	prgba	The address of a valid #t_jrgba struct containing the color to use.
	@return			An error code.
*/
t_max_err jpatchline_set_color(t_object *l, t_jrgba *prgba);


// private
t_object *jpatchline_get_wiretap(t_object *l);
long wiretap_get_id(t_object *w);
long wiretap_get_flags(t_object *w);
void wiretap_set_flags(t_object *w, long n);




// utilities to get/set patcherview attributes

/**	Query a patcherview to determine whether it is visible.
	@ingroup	jpatcherview
	@param	pv	The patcherview instance to query.
	@return		Returns zero if the patcherview is invisible, otherwise returns non-zero.	*/
char patcherview_get_visible(t_object *pv); 

/**	Set the 'visible' attribute of a patcherview.
	@ingroup	jpatcherview
	@param	pv	The patcherview instance whose attribute will be set.
	@param	c	Whether or not the patcherview should be made visible.
	@return		An error code.		*/
t_max_err patcherview_set_visible(t_object *pv, char c); 


/**	Get the value of the rect attribute for a patcherview.
	@ingroup	jpatcherview
	@param	pv	The patcherview instance whose attribute value will be fetched.
	@param	pr	The address of a valid #t_rect struct, whose contents will be filled upon return.
	@return		An error code.		*/
t_max_err patcherview_get_rect(t_object *pv, t_rect *pr);

/**	Set the value of the rect attribute for a patcherview.
	@ingroup	jpatcherview
	@param	pv	The patcherview instance whose attribute value will be set.
	@param	pr	The address of a valid #t_rect struct.
	@return		An error code.		*/
t_max_err patcherview_set_rect(t_object *pv, t_rect *pr);

/** Convert the point cx, cy in canvas coordinates to screen coordinates.
    @ingroup	jpatcherview
	@param	pv  The patcherview instance the canvas coords are relative to.
	@param	cx	The x dimension of the canvas coordinate relative to the patcherview.
	@param	cy  The y dimension of the canvas coordinate relative to the patcherview.
	@param	sx	A pointer to a long to receive the screen coordinate x dimension.
	@param	sy	A pointer to a long to receive the screen coordinate y dimension.   
*/
void patcherview_canvas_to_screen(t_object *pv, double cx, double cy, long *sx, long *sy); 

/** Convert the point cx, cy in canvas coordinates to screen coordinates.
 @ingroup	jpatcherview
 @param	pv  The patcherview instance the canvas coords are relative to.
 @param	sx	The screen position x coordinate.
 @param	sy	The screen position y coordinate
 @param	cx	A pointer to a double to receive the canvas coordinate for the given screen x position.
 @param	cy  A pointer to a double to receive the canvas coordinate for the given screen y position.
 */
void patcherview_screen_to_canvas(t_object *pv, long sx, long sy, double *cx, double *cy);

/**	Find out if a patcherview is locked.
	@ingroup	jpatcherview
	@param	p	The patcherview instance whose attribute value will be fetched.
	@return		Returns 0 if unlocked, otherwise returns non-zero.		*/
char patcherview_get_locked(t_object *p); 

/**	Lock or unlock a patcherview.
	@ingroup	jpatcherview
	@param	p	The patcherview instance whose attribute value will be set.
	@param	c	Set this value to zero to unlock the patcherview, otherwise pass a non-zero value.
	@return		An error code.		*/
t_max_err patcherview_set_locked(t_object *p, char c); 


/**	Find out if a patcherview is a presentation view.
	@ingroup	jpatcherview
	@param	pv	The patcherview instance whose attribute value will be fetched.
	@return		Returns 0 if the view is not a presentation view, otherwise returns non-zero.	*/
char patcherview_get_presentation(t_object *pv);

/**	Set whether or not a patcherview is a presentation view.
	@ingroup	jpatcherview
	@param	p	The patcherview instance whose attribute value will be set.
	@param	c	Set this value to non-zero to make the patcherview a presentation view, otherwise pass zero.
	@return		An error code.		*/
t_max_err patcherview_set_presentation(t_object *p, char c);


/**	Fetch the zoom-factor of a patcherview.
	@ingroup	jpatcherview
	@param	pv	The patcherview instance whose attribute value will be fetched.
	@return		The factor by which the view is zoomed.		*/
double patcherview_get_zoomfactor(t_object *pv);

/**	Set the zoom-factor of a patcherview.
	@ingroup	jpatcherview
	@param	pv	The patcherview instance whose attribute value will be set.
	@param	d	The zoom-factor at which the patcherview should display the patcher.
	@return		An error code.		*/
t_max_err patcherview_set_zoomfactor(t_object *pv, double d); 


/**	Given a patcherview, find the next patcherview.
	The views of a patcher are maintained internally as a #t_linklist, 
	and so the views can be traversed should you need to perform operations on all of a patcher's patcherviews.
	@ingroup	jpatcherview
	@param	pv	The patcherview instance from which to find the next patcherview.
	@return		The next patcherview in the list, or NULL if the patcherview passed in pv is the tail.	*/
t_object* patcherview_get_nextview(t_object *pv);


/**	Given a patcherview, return the #t_jgraphics context for that view.
	@ingroup	jpatcherview
	@param	pv	The patcherview instance.
	@return		The #t_jgraphics context for the view.	*/
t_object* patcherview_get_jgraphics(t_object *pv);

// private
t_max_err patcherview_set_jgraphics(t_object *pv, t_object *po);


/**	Given a patcherview, return its patcher.
	@ingroup	jpatcherview
	@param	pv	The patcherview instance for which to fetch the patcher.
	@return		The patcher.	*/
t_object* patcherview_get_patcher(t_object *pv); 

/** Given a patcherview, return the top patcherview (possibly itself). 
    If the patcherview is inside a bpatcher which is in a patcher then
	this will give you the view the bpatcher view is inside of. 
	@ingroup	jpatcherview
	@param  pv	The patcherview instance whose top view you want to get.
	@return		The top patcherview.    */
t_object* patcherview_get_topview(t_object *pv);


// utilities to get/set textfield attributes

/**	Return the object that owns a particular textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@return			A pointer to the owning object.		*/
t_object* textfield_get_owner(t_object *tf);


/**	Retrieve the color of the text in a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@param	prgba	The address of a valid #t_jrgba whose values will be filled-in upon return.
	@return			A Max error code.	*/
t_max_err textfield_get_textcolor(t_object *tf, t_jrgba *prgba); 

/**	Set the color of the text in a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@param	prgba	The address of a #t_jrgba containing the new color to use.
	@return			A Max error code.	*/
t_max_err textfield_set_textcolor(t_object *tf, t_jrgba *prgba); 


/**	Retrieve the background color of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@param	prgba	The address of a valid #t_jrgba whose values will be filled-in upon return.
	@return			A Max error code.	*/
t_max_err textfield_get_bgcolor(t_object *tf, t_jrgba *prgba); 

/**	Set the background color of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@param	prgba	The address of a #t_jrgba containing the new color to use.
	@return			A Max error code.	*/
t_max_err textfield_set_bgcolor(t_object *tf, t_jrgba *prgba); 


/**	Retrieve the margins from the edge of the textfield to the text itself in a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@param	pleft	The address of a variable to hold the value of the left margin upon return.
	@param	ptop	The address of a variable to hold the value of the top margin upon return.
	@param	pright	The address of a variable to hold the value of the right margin upon return.
	@param	pbottom	The address of a variable to hold the value of the bottom margin upon return.
	@return			A Max error code.	*/
t_max_err textfield_get_textmargins(t_object *tf, double *pleft, double *ptop, double *pright, double *pbottom);

/**	Set the margins from the edge of the textfield to the text itself in a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@param	left	The new value for the left margin.
	@param	top		The new value for the top margin.
	@param	right	The new value for the right margin.
	@param	bottom	The new value for the bottom margin.
	@return			A Max error code.	*/
t_max_err textfield_set_textmargins(t_object *tf, double left, double top, double right, double bottom); 


/**	Return the value of the 'editonclick' attribute of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@return			A value of the attribute.		*/
char textfield_get_editonclick(t_object *tf);

/**	Set the 'editonclick' attribute of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@param	c		The new value for the attribute.
	@return			A Max error code.		*/
t_max_err textfield_set_editonclick(t_object *tf, char c); 


/**	Return the value of the 'selectallonedit' attribute of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@return			A value of the attribute.		*/
char textfield_get_selectallonedit(t_object *tf);

/**	Set the 'selectallonedit' attribute of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@param	c		The new value for the attribute.
	@return			A Max error code.		*/
t_max_err textfield_set_selectallonedit(t_object *tf, char c); 


/**	Return the value of the 'noactivate' attribute of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@return			A value of the attribute.		*/
char textfield_get_noactivate(t_object *tf);

/**	Set the 'noactivate' attribute of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@param	c		The new value for the attribute.
	@return			A Max error code.		*/
t_max_err textfield_set_noactivate(t_object *tf, char c); 


/**	Return the value of the 'readonly' attribute of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@return			A value of the attribute.		*/
char textfield_get_readonly(t_object *tf);

/**	Set the 'readonly' attribute of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@param	c		The new value for the attribute.
	@return			A Max error code.		*/
t_max_err textfield_set_readonly(t_object *tf, char c); 


/**	Return the value of the 'wordwrap' attribute of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@return			A value of the attribute.		*/
char textfield_get_wordwrap(t_object *tf);

/**	Set the 'wordwrap' attribute of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@param	c		The new value for the attribute.
	@return			A Max error code.		*/
t_max_err textfield_set_wordwrap(t_object *tf, char c); 


/**	Return the value of the 'useellipsis' attribute of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@return			A value of the attribute.		*/
char textfield_get_useellipsis(t_object *tf);

/**	Set the 'useellipsis' attribute of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@param	c		The new value for the attribute.
	@return			A Max error code.		*/
t_max_err textfield_set_useellipsis(t_object *tf, char c); 


/**	Return the value of the 'autoscroll' attribute of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@return			A value of the attribute.		*/
char textfield_get_autoscroll(t_object *tf);

/**	Set the 'autoscroll' attribute of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@param	c		The new value for the attribute.
	@return			A Max error code.		*/
t_max_err textfield_set_autoscroll(t_object *tf, char c); 


/**	Return the value of the 'wantsreturn' attribute of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@return			A value of the attribute.		*/
char textfield_get_wantsreturn(t_object *tf);

/**	Set the 'wantsreturn' attribute of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@param	c		The new value for the attribute.
	@return			A Max error code.		*/
t_max_err textfield_set_wantsreturn(t_object *tf, char c); 


/**	Return the value of the 'wantstab' attribute of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@return			A value of the attribute.		*/
char textfield_get_wantstab(t_object *tf);

/**	Set the 'wantstab' attribute of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@param	c		The new value for the attribute.
	@return			A Max error code.		*/
t_max_err textfield_set_wantstab(t_object *tf, char c); 


/**	Return the value of the 'underline' attribute of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@return			A value of the attribute.		*/
char textfield_get_underline(t_object *tf);

/**	Set the 'underline' attribute of a textfield.
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@param	c		The new value for the attribute.
	@return			A Max error code.		*/
t_max_err textfield_set_underline(t_object *tf, char c);


// private
char textfield_get_justification(t_object *tf);
t_max_err textfield_set_justification(t_object *tf, char c);
char textfield_get_autofixwidth(t_object *tf);
t_max_err textfield_set_autofixwidth(t_object *tf, char c); 


/**	Set the 'empty' text of a textfield.
	The empty text is the text that is displayed in the textfield when no text is present.
	By default this is gensym("").
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@param	txt		A symbol containing the new text to display when the textfield has no content.
	@return			A Max error code.	*/
t_max_err textfield_set_emptytext(t_object *tf, t_symbol *txt);

/**	Retrieve the 'empty' text of a textfield.
	The empty text is the text that is displayed in the textfield when no text is present.
	By default this is gensym("").
	@ingroup		textfield
	@param	tf		The textfield instance pointer.
	@return			The current text used as the empty text.	*/
t_symbol *textfield_get_emptytext(t_object *tf);

// textfield constants

#define TEXTFIELD_DEF_LEFTMARGIN  (4)	///< textfield default left margin
#define TEXTFIELD_DEF_TOPMARGIN  (3)	///< textfield default top margin
#define TEXTFIELD_DEF_RIGHTMARGIN (4)	///< textfield default right margin
#define TEXTFIELD_DEF_BOTTOMMARGIN (3)	///< textfield default bottom margin


// jbox flags
// flags passed to box_new

// The following flags affect how the boxes are drawn 
#define JBOX_DRAWFIRSTIN            (1<<0)			///< draw first inlet												@ingroup jbox
#define JBOX_NODRAWBOX              (1<<1)			///< don't draw the frame  											@ingroup jbox
#define JBOX_DRAWINLAST             (1<<2)			///< draw inlets after update method 								@ingroup jbox

// JBOX_TRANSPARENT is unused -- box is always transparent by default
#define JBOX_TRANSPARENT            (1<<3)			///< don't make transparent unless you need it (for efficiency)		@ingroup jbox

// Box growing: nogrow is clear -- box is not sizable. 
// Default (none of following three flags) means box width is only sizable.
// JBOX_GROWY means that X and Y are sizable and the aspect ratio is fixed (or maybe it has to be square, like dial?).  
// JBOX_GROWBOTH means that X and Y are independently sizable.  
#define JBOX_NOGROW                 (1<<4)			///< don't even draw grow thingie 				@ingroup jbox
#define JBOX_GROWY                  (1<<5)			///< can grow in y direction by dragging		@ingroup jbox
#define JBOX_GROWBOTH               (1<<6)			///< can grow independently in both x and y 	@ingroup jbox

// Box interaction
#define JBOX_IGNORELOCKCLICK        (1<<7)			///< box should ignore a click if patcher is locked 	@ingroup jbox
#define JBOX_HILITE                 (1<<8)			///< flag passed to jbox_new() to tell max that the UI object can receive the focus when clicked on -- may be replaced by JBOX_FOCUS in the future 		@ingroup jbox
#define JBOX_BACKGROUND             (1<<9)			///< immediately set box into the background			@ingroup jbox
#define JBOX_NOFLOATINSPECTOR       (1<<10)			///< no floating inspector window						@ingroup jbox

// textfield: give this flag for automatic textfield support
#define JBOX_TEXTFIELD              (1<<11)			///< save/load text from textfield, unless JBOX_BINBUF flag is set				@ingroup jbox
#define JBOX_FIXWIDTH               (1<<19)			///< give the box a textfield based fix-width (bfixwidth) method				@ingroup jbox
#define JBOX_FONTATTR               (1<<18)			///< if you want font related attribute you must add this to jbox_initclass()	@ingroup jbox
#define JBOX_TEXTJUSTIFICATIONATTR  (1<<21)         ///< give your object a textjustification attr to control textfield             @ingroup jbox
#define JBOX_BINBUF                 (1<<14)			///< save/load text from b_binbuf												@ingroup jbox

#define JBOX_MOUSEDRAGDELTA         (1<<12)			///< hides mouse cursor in drag and sends mousedragdelta instead of mousedrag (for infinite scrolling like number)	@ingroup jbox

#define JBOX_COLOR                  (1<<13)			///< support the "color" method for color customization												@ingroup jbox
#define JBOX_DRAWIOLOCKED           (1<<15)			///< draw inlets and outlets when locked (default is not to draw them)								@ingroup jbox
#define JBOX_DRAWBACKGROUND         (1<<16)			///< set to have box bg filled in for you based on getdrawparams method or brgba attribute			@ingroup jbox
#define JBOX_NOINSPECTFIRSTIN       (1<<17)			///< flag for objects such as bpatcher that have a different b_firstin,
                                                    ///< but the attrs of the b_firstin should not be shown in the inspector							@ingroup jbox

// JBOX_DEFAULTNAMES is unused -- box is attached automatically if needed
// Since JBOX_DEFAULTNAMES was unused and used a conflicting flag bit with JBOX_FONTATTR it is being removed.
// Just remove from your code if you have a compile error about JBOX_DEFAULTNAMES missing.
//#define JBOX_DEFAULTNAMES			(1<<18)			///< flag instructing jbox_new to attach object to the defaults object for live defaults updating	@ingroup jbox

#define JBOX_FOCUS					(1<<20)			///< more advanced focus support (passed to jbox_initclass() to add "nextfocus" and "prevfocus" attributes to the UI object).  Not implemented as of 2009-05-11   @ingroup jbox
#define JBOX_BOXVIEW				(1<<23)			///< enable jboxview methods   @ingroup jbox

#define JBOX_LEGACYCOLOR			(1<<22)			///< add undocumented color N message to objects from Max 4 that used it   @ingroup jbox
#define JBOX_COPYLEGACYDEFAULT		(1<<24)			///< if there is a legacy default, copy it instead of the regular default   @ingroup jbox
#define JBOX_NOLEGACYDEFAULT		(1<<25)			///< if there is a legacy default, don't copy any default   @ingroup jbox


/** actual numerical values of the b_fontface attribute; use jbox_fontface() to weight 
	@ingroup	jbox		*/
enum {
	JBOX_FONTFACE_REGULAR = 0,		///< normal
	JBOX_FONTFACE_BOLD = 1,			///< bold
	JBOX_FONTFACE_ITALIC = 2,		///< italic
	JBOX_FONTFACE_BOLDITALIC = 3	///< bold and italic
};

// The following two are not needed in the new world. 
// #define JBOX_MOVING				8			// object invalidates outside its defined clipping region		
// #define JBOX_SAVVY				2048		// calls box_enddraw after box_nodraw returns false

/** enumerations used for box decorators 
	@ingroup	jbox	*/
typedef enum _HitTestResult {
	HitNothing = 0,		///< a hole in the box
	HitBox = 1,			///< the body of the box
	HitInlet = 2,		///< an inlet
	HitOutlet = 3,		///< an outlet
	HitGrowBox = 4,		///< the grow handle
	HitLine = 5,		///< a line
	HitLineLocked = 6	///< a line in a locked patcher (for probing)
} HitTestResult;

// private
typedef enum _DecoratorPaintFlags {
	BoxSelected = 1 << 0,
	DrawFirstIn = 1 << 1,
	NoGrow = 1 << 2,
	Outline = 1 << 3, 
	Locked = 1 << 4,
	InletHighlighted = 1 << 5,			// value tells index of highlighted inlet
	OutletHighlighted = 1 << 6			// value tells index of highlighted outlet  (only one can be highlighted)
} DecoratorPaintFlags;



// UI object functions for implementing your own UI objects

// private
void jbox_initclass(t_class *c, long flags);  

/**	Set up your UI object's #t_jbox member.
	This should be called from your UI object's free method.
	@ingroup		jbox
	@param	b		The address of your UI object's #t_jbox member (which should be the first member of the object's struct).
	@param	flags	Flags to set the box's behavior, such as #JBOX_NODRAWBOX.
	@param	argc	The count of atoms in the argv parameter.
	@param	argv	The address of the first in an array of atoms to be passed to the box constructor.
					Typically these are simply the argument passed to your object when it is created.
	@return			A Max error code.		*/
t_max_err jbox_new(t_jbox *b, long flags, long argc, t_atom *argv);

/**	Tear down your UI object's #t_jbox member.
 	This should be called from your UI object's free method.
	@ingroup		jbox
	@param	b		The address of your object's #t_jbox member (which should be the first member of the object's struct).	*/
void jbox_free(t_jbox *b);

/**	Mark the box ready to be accessed and drawn by Max.
	This should typically be called at the end of your UI object's new method.
	@ingroup		jbox
	@param	b		The address of your object's #t_jbox member.		*/
void jbox_ready(t_jbox *b);


/**	Request that your object/box be re-drawn by Max.
	@ingroup		jbox
	@param	b		The address of your object's #t_jbox member.		*/
void jbox_redraw(t_jbox *b);

// private
void jbox_redrawcontents(t_jbox *b); 
void *jbox_getoutlet(t_jbox *x, long index);
void *jbox_getinlet(t_jbox *x, long index);
void jbox_updatetextfield(t_jbox *b);

// fills in all missing legacy defaults if one is present

#define LEGACYDEFAULTS_FLAGS_FORCE 1 // forces it to happen

void jbox_processlegacydefaults(t_jbox *b, t_dictionary *d, long flags);

/**	Send a notification to a box.  This is the same as calling object_notify() for a box.
	@ingroup		jbox
	@param	b		The address of your object's #t_jbox member.
	@param	s		The name of the send object.
	@param	msg		The notification name.
	@param	sender	The sending object's address.
	@param	data	A pointer to some data passed to the box's notify method.
	@return			A Max error code.
*/
t_max_err jbox_notify(t_jbox *b, t_symbol *s, t_symbol *msg, void *sender, void *data);

// private
t_max_err jbox_set_to_defaultsize(t_jbox *b, t_symbol *s, short argc, t_atom *argv);


/**	Grab the keyboard focus for your box.  
	Calling this method should be considered exceptional, and its use is discouraged.
	@param	b		The address of your object's #t_jbox member.	*/
void jbox_grabfocus(t_jbox *b); 

// private
void jbox_redrawpeers(t_jbox *b);
long jbox_getinletindex(t_jbox *b, void *inlet);
long jbox_getoutletindex(t_jbox *b, void *outlet);


void jbox_show_caption(t_jbox *b);
void jbox_hide_caption(t_jbox *b);


// dictionary stuff
#define DICT_JRGBA 1	// convert RGB to jrgba when storing/retrieving from dictionary
t_max_err dictionary_appendjrgba(t_dictionary *d, t_symbol *key, t_jrgba *jc);

t_max_err dictionary_getdefjrgba(t_dictionary *d, t_symbol *key, t_jrgba *jc, t_jrgba *def);

t_max_err dictionary_gettrect(t_dictionary *d, t_symbol *key, t_rect *rect);
t_max_err dictionary_appendtrect(t_dictionary *d, t_symbol *key, t_rect *rect);

t_max_err dictionary_gettpt(t_dictionary *d, t_symbol *key, t_pt *pt);
t_max_err dictionary_appendtpt(t_dictionary *d, t_symbol *key, t_pt *pt);

void atomstojrgba(long argc, t_atom *argv, t_jrgba *dest);
void jrgbatoatoms(t_jrgba *src, t_atom *argv);

/**	Read the specified JSON file and return a #t_dictionary object.
	You are responsible for freeing the dictionary with object_free(),
	subject to the caveats explained in @ref when_to_free_a_dictionary.
	@ingroup			dictionary
	@param	filename	The name of the file.
	@param	path		The path of the file.
	@param	d			The address of a #t_dictionary pointer that will be set to the newly created dictionary.
	@return				A Max error code
*/
t_max_err dictionary_read(char *filename, short path, t_dictionary **d);

/**	Serialize the specified #t_dictionary object to a JSON file.
	@ingroup			dictionary
	@param	d			The dictionary to serialize into JSON format and write to disk.
	@param	filename	The name of the file to write.
	@param	path		The path to which the file should be written.
	@return				A Max error code.
*/
t_max_err dictionary_write(t_dictionary *d, char *filename, short path);

/**	Read the specified YAML file and return a #t_dictionary object.
	You are responsible for freeing the dictionary with object_free(),
	subject to the caveats explained in @ref when_to_free_a_dictionary.
	@ingroup			dictionary
	@param	filename	The name of the file.
	@param	path		The path of the file.
	@param	d			The address of a #t_dictionary pointer that will be set to the newly created dictionary.
	@return				A Max error code
 */

t_max_err dictionary_read_yaml(const char *filename, const short path, t_dictionary **d);

/**	Serialize the specified #t_dictionary object to a YAML file.
	@ingroup			dictionary
	@param	d			The dictionary to serialize into YAML format and write to disk.
	@param	filename	The name of the file to write.
	@param	path		The path to which the file should be written.
	@return				A Max error code.
 */
t_max_err dictionary_write_yaml(const t_dictionary *d, const char *filename, const short path);


// convenience for object-making

#define newobject_fromdictionary_delete(p,d) newobject_fromdictionary(p,d), freeobject((t_object *)d)

#ifdef MAC_VERSION
#define strcmp_case_insensitive strcasecmp
#endif
#ifdef WIN_VERSION
#if _MSC_VER < 1400
#define strcmp_case_insensitive strcmpi
#else
#define strcmp_case_insensitive _strcmpi
#endif
#endif


/**	Bit mask values for various meta-key presses on the keyboard.
	@ingroup	jmouse	*/
typedef enum _modifiers {
	eCommandKey = 1,		///< Command Key
	eShiftKey = 2,			///< Shift Key
	eControlKey = 4,		///< Control Key
	eAltKey = 8,			///< Alt Key
	eLeftButton = 16,		///< Left mouse button
	eRightButton = 32,		///< Right mouse button
	eMiddleButton = 64,		///< Middle mouse button
	ePopupMenu = 128,		///< Popup Menu (contextual menu requested)
	eCapsLock = 256,		///< Caps lock
	eAutoRepeat = 512		///< Key is generated by key press auto-repeat
} t_modifiers;

/**	Return the last known combination of modifier keys being held by the user.
	@ingroup	jmouse
	@return		The current modifier keys that are activated.	*/
t_modifiers jkeyboard_getcurrentmodifiers(); 

/**	Return the current combination of modifier keys being held by the user.
	@ingroup	jmouse
	@return		The current modifier keys that are activated.	*/
t_modifiers jkeyboard_getcurrentmodifiers_realtime(); 

// key codes
// key/keyup objects fourth outlet and key message to objects uses 
// the following values for keycodes
typedef enum _keycode {
	// keycode is ascii value with modifiers stripped
	// a-z keys thus report lowercase keycode regardless of shift key or capslock state
	JKEY_NONE		        = -1,
	JKEY_SPACEBAR           = -2,
	JKEY_ESC				= -3,
	JKEY_RETURN             = -4,
	JKEY_ENTER				= -4,  // same as JKEY_RETURN
	JKEY_TAB                = -5,
	JKEY_DELETE             = -6,
	JKEY_BACKSPACE          = -7,
	JKEY_INSERT             = -8,
	JKEY_UPARROW            = -9,
	JKEY_DOWNARROW          = -10,
	JKEY_LEFTARROW          = -11,
	JKEY_RIGHTARROW         = -12,
	JKEY_PAGEUP             = -13,
	JKEY_PAGEDOWN           = -14,
	JKEY_HOME               = -15,
	JKEY_END                = -16,
	JKEY_F1                 = -17,
	JKEY_F2                 = -18,
	JKEY_F3                 = -19,
	JKEY_F4                 = -20,
	JKEY_F5                 = -21,
	JKEY_F6                 = -22,
	JKEY_F7                 = -23,
	JKEY_F8                 = -24,
	JKEY_F9                 = -25,
	JKEY_F10                = -26,
	JKEY_F11                = -27,
	JKEY_F12                = -28,
	JKEY_F13                = -29,
	JKEY_F14                = -30,
	JKEY_F15                = -31,
	JKEY_F16                = -32,
	JKEY_NUMPAD0            = -33,
	JKEY_NUMPAD1            = -34,
	JKEY_NUMPAD2            = -35,
	JKEY_NUMPAD3            = -36,
	JKEY_NUMPAD4            = -37,
	JKEY_NUMPAD5            = -38,
	JKEY_NUMPAD6            = -39,
	JKEY_NUMPAD7            = -40,
	JKEY_NUMPAD8            = -41,
	JKEY_NUMPAD9            = -42,
	JKEY_NUMPADADD          = -43,
	JKEY_NUMPADSUBTRACT     = -44,
	JKEY_NUMPADMULTIPLY     = -45,
	JKEY_NUMPADDIVIDE       = -46,
	JKEY_NUMPADSEPARATOR    = -47,
	JKEY_NUMPADDECIMALPOINT = -48,
	JKEY_NUMPADEQUALS       = -49,
	JKEY_NUMPADDELETE       = -50,
	JKEY_PLAYPAUSE			= -51,
	JKEY_STOP				= -52,
	JKEY_NEXTTRACK			= -53,
	JKEY_PREVTRACK			= -54,
	JKEY_HELP				= -55
} t_keycode;

// mouse cursor stuff

/**	Get the position of the mouse cursor in screen coordinates.
	@ingroup			jmouse
	@param	x			The address of a variable to hold the x-coordinate upon return.
	@param	y			The address of a variable to hold the y-coordinate upon return.	*/
void jmouse_getposition_global(int *x, int *y);

/**	Set the position of the mouse cursor in screen coordinates.
	@ingroup			jmouse
	@param	x			The new x-coordinate of the mouse cursor position.
	@param	y			The new y-coordinate of the mouse cursor position.	*/
void jmouse_setposition_global(int x, int y);

/**	Set the position of the mouse cursor relative to the patcher canvas coordinates.
	@ingroup			jmouse
	@param	patcherview	The patcherview upon which the mouse coordinates are based.
	@param	cx			The new x-coordinate of the mouse cursor position.
	@param	cy			The new y-coordinate of the mouse cursor position.	*/
void jmouse_setposition_view(t_object *patcherview, double cx, double cy);

/**	Set the position of the mouse cursor relative to a box within the patcher canvas coordinates.
	@ingroup			jmouse
	@param	patcherview	The patcherview containing the box upon which the mouse coordinates are based.
	@param	box			The box upon which the mouse coordinates are based.
	@param	bx			The new x-coordinate of the mouse cursor position.
	@param	by			The new y-coordinate of the mouse cursor position.	*/
void jmouse_setposition_box(t_object *patcherview, t_object *box, double bx, double by);

void *jmouse_getobject();

/**	Mouse cursor types.
	@ingroup jmouse			*/
typedef enum _jmouse_cursortype {
	JMOUSE_CURSOR_NONE, 						///< None
	JMOUSE_CURSOR_ARROW, 						///< Arrow
	JMOUSE_CURSOR_WAIT, 						///< Wait
	JMOUSE_CURSOR_IBEAM, 						///< I-Beam
	JMOUSE_CURSOR_CROSSHAIR, 					///< Crosshair
	JMOUSE_CURSOR_COPYING,						///< Copying
	JMOUSE_CURSOR_POINTINGHAND,					///< Pointing Hand
	JMOUSE_CURSOR_DRAGGINGHAND,					///< Dragging Hand
	JMOUSE_CURSOR_RESIZE_LEFTRIGHT,				///< Left-Right
	JMOUSE_CURSOR_RESIZE_UPDOWN,				///< Up-Down
	JMOUSE_CURSOR_RESIZE_FOURWAY,				///< Four Way
	JMOUSE_CURSOR_RESIZE_TOPEDGE,				///< Top Edge
	JMOUSE_CURSOR_RESIZE_BOTTOMEDGE,			///< Bottom Edge
	JMOUSE_CURSOR_RESIZE_LEFTEDGE,				///< Left Edge
	JMOUSE_CURSOR_RESIZE_RIGHTEDGE,				///< Right Edge
	JMOUSE_CURSOR_RESIZE_TOPLEFTCORNER,			///< Top-Left Corner
	JMOUSE_CURSOR_RESIZE_TOPRIGHTCORNER,		///< Top-Right Corner
	JMOUSE_CURSOR_RESIZE_BOTTOMLEFTCORNER,		///< Bottom-Left Corner
	JMOUSE_CURSOR_RESIZE_BOTTOMRIGHTCORNER		///< Bottom-Right Corner
} t_jmouse_cursortype; 


/**	Set the mouse cursor.
	@ingroup			jmouse
	@param	patcherview	The patcherview for which the cursor should be applied.
	@param	box			The box for which the cursor should be applied.
	@param	type		The type of cursor for the mouse to use.		*/
void jmouse_setcursor(t_object *patcherview, t_object *box, t_jmouse_cursortype type);




/**	Get the current window, if any.
	@ingroup	jwind
	@return		A pointer to the current window, if there is one.  Otherwise returns NULL.	*/
t_object* jwind_getactive(void);

/**	Determine how many windows exist.
	@ingroup	jwind
	@return		The number of windows.	*/
long jwind_getcount(void);

/**	Return a pointer to the window with a given index.
	@ingroup		jwind
	@param	index	Get window at index (0 to count-1).
	@return			A pointer to a window object.	*/
t_object* jwind_getat(long index);

// functions to enumerate displays

/**	Return the number of monitors on which can be displayed.
	@ingroup	jmonitor
	@return		The number of monitors.		*/
long jmonitor_getnumdisplays();

/**	Return the #t_rect for a given display.
	@ingroup				jmonitor
	@param	workarea		Set workarea non-zero to clip out things like dock / task bar.
	@param	displayindex	The index number for a monitor.  The primary monitor has an index of 0.
	@param	rect			The address of a valid #t_rect whose values will be filled-in upon return.		*/
void jmonitor_getdisplayrect(long workarea, long displayindex, t_rect *rect);

/**	Return a union of all display rects.
	@ingroup				jmonitor
	@param	workarea		Set workarea non-zero to clip out things like dock / task bar.
	@param	rect			The address of a valid #t_rect whose values will be filled-in upon return.		*/
void jmonitor_getdisplayrect_foralldisplays(long workarea, t_rect *rect);			// get union of all display rects

/**	Return the #t_rect for the display on which a point exists.
	@ingroup				jmonitor
	@param	workarea		Set workarea non-zero to clip out things like dock / task bar.
	@param	pt				A point, for which the monitor will be determined and the rect recturned.
	@param	rect			The address of a valid #t_rect whose values will be filled-in upon return.		*/
void jmonitor_getdisplayrect_forpoint(long workarea, t_pt pt, t_rect *rect);


// color support -- private
void swatches_init(void);
void swatches_shutdown(void);

void *jpatcher_load(char *name, short volume, short ac, t_atom *av);
void *jpatcher_load_frombuffer(char *name, short vol, const char *json, long len, short ac, t_atom *av);
void *jpatcher_load_fromdictionary(char *name, short vol, t_object *rd, short ac, t_atom *av);

void *jpatcher_load_namespace(char *name, short volume, short ac, t_atom *av, t_symbol *classnamespace);
void *jpatcher_load_frombuffer_namespace(char *name, short vol, const char *json, long len, short ac, t_atom *av, t_symbol *classnamespace);
void *jpatcher_load_fromdictionary_namespace(char *name, short vol, t_object *rd, short ac, t_atom *av, t_symbol *classnamespace);

/**	Show the refpage for a given class.
	@ingroup				misc
	@param	classnamespace	The namespace for the class, e.g. "box".
	@param	classname		The name of the class.
*/
void classname_openrefpage_ext(t_symbol *classnamespace, char *classname);

long jpatcher_is_box_namespace(t_object *p);
t_object *jbox_get_dragtarget(t_jbox *b, char locked);

// private -- internal use only
long jpatcher_inc_maxsendcontext();

// private -- internal use only
long jbox_is_selected_in_view(t_object *box, t_object *view);

// private -- internal use only
t_atom_long jpatcher_dictionary_modernui(t_dictionary *d);
t_atom_long jpatcher_dictionary_version();
t_dictionary *jpatcher_fallback_version();
long jbox_isdefaultattribute(t_jbox *x, t_symbol *attrname);


/**	Retrieve the name of Max's system font.
	@ingroup	jfont
	@return		The name of Max's system font.
*/
const char *systemfontname();

/**	Retrieve the name of Max's bold system font.
	@ingroup	jfont
	@return		The name of Max's bold system font.
*/
const char *systemfontname_bold();

/**	Retrieve the name of Max's light system font.
	@ingroup	jfont
	@return		The name of Max's light system font.
*/
const char *systemfontname_light();

/**	Retrieve the name of Max's system font as a symbol.
	@ingroup	jfont
	@return		The name of Max's system font.
*/
t_symbol *systemfontsym();


#define JPATCHER_DEFAULT_EXTENSION ".maxpat"

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

END_USING_C_LINKAGE

#endif // #ifndef _JPATCHER_API_H_
