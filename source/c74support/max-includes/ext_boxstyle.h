#ifndef _EXT_BOXSTYLE_H_
#define _EXT_BOXSTYLE_H_

BEGIN_USING_C_LINKAGE


/**	Add an attribute to the current style.
	@ingroup styles

	@param	c	The class whose attribute will be added to the style.
	@param	s	The name of the attribute to be added to the style.
	@see The 'uitextfield' example project in the SDK.
*/
void class_attr_setstyle(t_class *c, const char *s);


/**	Add an alias to the current style.
	This is used for backward compatibility where an attribute using an old name will want a style applied to it from a different name.
	Typically you will use one of the macros such as #CLASS_ATTR_STYLE_ALIAS_NOSAVE rather than using this function directly.
	@ingroup styles

	@param	c			The class for whom the alias will be created.
	@param	name		The name of the attribute of the style.
	@param	aliasname	The name of the alias.
	@param	legacy		Always pass 0 for this argument.
	@see	#CLASS_ATTR_STYLE_ALIAS_NOSAVE
	@see 	The 'jslider' project in the SDK.
*/
void class_attr_style_alias(t_class *c, const char *name, const char *aliasname, long legacy);


/**	Flag indicating we want this fill attribute saved (creates attrs).
	@ingroup styles
	@see class_attr_setfill()
	@see The 'uitextfield' example project in the SDK.
*/
#define FILL_ATTR_SAVE 1 


/**	Specify that an attr requires a fill.
	@ingroup styles

	@param	c		The class whose attribute is a fill.
	@param	name	The name of the attribute.
	@param	flags	0 for none, or #FILL_ATTR_SAVE.
	@see The 'uitextfield' example project in the SDK.
*/
void class_attr_setfill(t_class *c, const char *name, long flags);


/**	Fill using the current value of a named style color that exists either in the object or the defined style.
	Abdridged example from the 'attrui' object:
	@code
		long is_fill = object_attr_getfill(destination, x->j_attr);

		if (is_fill) {
			jgraphics_attr_fillrect((t_object *)destination, g, x->j_attr, rect);
			jgraphics_rectangle(g, rect->x, rect->y, rect->width, rect->height);	// ready to be stroked
		} 
		else {
			object_attr_getjrgba(destination, x->j_attr, &color);
			jgraphics_set_source_jrgba(g, &color);
			jgraphics_rectangle(g, rect->x, rect->y, rect->width, rect->height);
			jgraphics_fill_preserve(g);
		}

		jgraphics_set_source_jrgba(g, &bordercolor);
		jgraphics_stroke(g);
	@endcode

	@ingroup styles

	@param	b			The instance of your object.
	@param	g			The jgraphics context.
	@param	attrname	The name of the attribute whose fill style you want.
	@param	area		The rect area to be filled.
*/
void jgraphics_attr_fillrect(t_object *b, t_jgraphics *g, t_symbol *attrname, t_rect *area);


/**	Fill using the current value of a named style color that exists either in the object or the defined style.
	Example from the 'panel' object:
	@code
		t_rect r;
		
		r.x = r.y = thick * 0.5;
		r.width = rect->width - thick;
		r.height = rect->height - thick;
		
		pat = jgraphics_attr_setfill((t_object *)x, g, ps_bgfillcolor, &r);
		jgraphics_rectangle_rounded(g, r.x, r.y, r.width, r.height, round, round);
		jgraphics_fill_preserve(g);
		jgraphics_pattern_destroy(pat);
		
		object_attr_getjrgba(x, ps_bordercolor, &color);
		jgraphics_set_source_jrgba(g, &color);
		jgraphics_set_line_width(g, thick);
		jgraphics_stroke(g);
	@endcode

	@ingroup styles

	@param	b			The instance of your object.
	@param	g			The jgraphics context.
	@param	attrname	The name of the attribute whose fill style you want.
	@param	area		The rect area to be filled.
	@return				The pattern.
*/
t_jpattern *jgraphics_attr_setfill(t_object *b, t_jgraphics *g, t_symbol *attrname, t_rect *area);


/**	Determine the color at a given position in a fill.
	@ingroup	styles
	@param		b			The instance of your object.
	@param		attrname	The name of the attribute to query.
	@param		pos			The position in a range of [0.0, 1.0].
	@param		c			A valid #t_jrgba whose members will be filled-in upon return.
	@return 				true if the object is a fill, otherwise false.
*/
void object_attr_getfillcolor_atposition(t_object *b, const char *attrname, double pos, t_jrgba *c);


/**	Determine if an attribute is a fill.
	@ingroup	styles
	@param		obj			The instance of your object.
	@param		attrname	The name of the attribute to query.
	@return 				true if the object is a fill, otherwise false.
*/
long object_attr_getfill(t_object *obj, t_symbol *attrname);

void object_style_setfillattribute(t_object *x, t_symbol *fillattr, t_symbol *entry, long argc, t_atom *argv);


/**	Associate the name of an attribute of your class with the name of an attribute of a style.
	@ingroup	styles
	@param		c			The class whose attribute will be added to the style.
	@param		attrname	The name of the attribute of your class.
	@param		mapname		The name of the attribute from the style.
	@see		'jslider' example project in the SDK.
*/
void class_attr_stylemap(t_class *c, char *attrname, char *mapname);

t_symbol *object_attr_attrname_forstylemap(t_object *x, t_symbol *mapname);		// internal use only
t_symbol *object_attr_stylemapname(t_object *x, t_symbol *attrname);		 	// internal use only


// menus of named styles

t_jpopupmenu *style_getmenu(t_object *context, t_symbol *current, long mask, long *selecteditem, long *headercount);		// internal use only
void style_handlemenu(t_object *context, long itemindex, t_symbol **current);												// internal use only


// Attribute Macros for simple and maintainable style attribute definitions

// CLASS_ATTR_STYLE_RGBA defines an RGBA style attribute with standard settings
// and replaces RGBA style definitions of the following pattern, with and without "preview" and saving:
/*
 CLASS_ATTR_RGBA(c,"accentcolor",0, t_jnumber, j_tricolor);
 CLASS_ATTR_SAVE(c, "accentcolor", 0);
 CLASS_ATTR_PAINT(c, "accentcolor", 0);
 CLASS_ATTR_STYLE_LABEL(c, "accentcolor", 0 , "rgba", "Triangle Color");
 class_attr_setstyle(c, "accentcolor");
 CLASS_ATTR_ATTR_PARSE(c, "accentcolor", "preview", USESYM(symbol), 0, "triangle_fill");
 */

/**	Define an RGBA style attribute with standard settings.
	@ingroup	styles
	@param		c				The class whose attribute will be added to the style.
	@param		attrname		The name of the attribute of your class.
	@param		flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param		structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param		structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param		label			A human-friendly label for the Max inspector.
	@see						#CLASS_ATTR_STYLE_RGBA is a variant that saves the state with the patcher.
	@see						#CLASS_ATTR_STYLE_RGBA_PREVIEW is a variant that provides a style preview.
	@see						class_attr_setstyle() is the lower level function used to provide the style part of the attribute definition.
*/
#define CLASS_ATTR_STYLE_RGBA_NOSAVE(c,attrname,flags,structname,structmember,label) \
{	CLASS_ATTR_DOUBLE_ARRAY(c,attrname,flags,structname,structmember,4); \
	CLASS_ATTR_ACCESSORS(c,attrname,NULL,jgraphics_attr_setrgba); \
	CLASS_ATTR_PAINT(c,attrname,0); \
	CLASS_ATTR_STYLE_LABEL(c,attrname,0,"rgba",label); \
	class_attr_setstyle(c,attrname); }


/**	Define an RGBA style attribute with standard settings.
	@ingroup	styles
	@param		c				The class whose attribute will be added to the style.
	@param		attrname		The name of the attribute of your class.
	@param		flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param		structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param		structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param		label			A human-friendly label for the Max inspector.
	@see						#CLASS_ATTR_STYLE_RGBA_NOSAVE is a variant that does not save the state with the patcher.
	@see						#CLASS_ATTR_STYLE_RGBA_PREVIEW is a variant that provides a style preview.
	@see						class_attr_setstyle() is the lower level function used to provide the style part of the attribute definition.
*/
#define CLASS_ATTR_STYLE_RGBA(c,attrname,flags,structname,structmember,label) \
{	CLASS_ATTR_STYLE_RGBA_NOSAVE(c,attrname,flags,structname,structmember,label) \
	CLASS_ATTR_SAVE(c,attrname,0); }


/**	Define an RGBA style attribute with standard settings.
	@ingroup	styles
	@param		c				The class whose attribute will be added to the style.
	@param		attrname		The name of the attribute of your class.
	@param		flags			Any flags you wish to declare for this attribute, as defined in #e_max_attrflags.
	@param		structname		The C identifier for the struct (containing a valid #t_object header) representing an instance of this class.
	@param		structmember	The C identifier of the member in the struct that holds the value of this attribute.
	@param		label			A human-friendly label for the Max inspector.
	@param		previewtype		Type of preview to use in the style bar, e.g. "triangle_fill"
	@see						#CLASS_ATTR_STYLE_RGBA_NOSAVE is a variant that does not save the state with the patcher.
	@see						#CLASS_ATTR_STYLE_RGBA is a variant that saves the state with the patcher but does not provide the preview.
	@see						class_attr_setstyle() is the lower level function used to provide the style part of the attribute definition.
*/
#define CLASS_ATTR_STYLE_RGBA_PREVIEW(c,attrname,flags,structname,structmember,label,previewtype) \
{	CLASS_ATTR_STYLE_RGBA(c,attrname,flags,structname,structmember,label); \
	CLASS_ATTR_ATTR_PARSE(c,attrname,"preview",USESYM(symbol),0,previewtype); }


/**	Define an unsaved alias.
	@ingroup 	styles
	@param		c			The class whose attribute will be added to the style.
	@param		attrname	The name of the attribute of your class.
	@param		aliasname	The name of the alias.
	@see 'jslider' example project in the SDK.
*/
#define CLASS_ATTR_STYLE_ALIAS_NOSAVE(c,attrname,aliasname) \
{	class_attr_style_alias(c,attrname,aliasname,false); \
    CLASS_ATTR_INVISIBLE(c,aliasname,0); \
    CLASS_ATTR_PAINT(c,aliasname,0); }


/**	Define a Max 5/6 saved compatibility alias
	@ingroup 	styles
	@param		c			The class whose attribute will be added to the style.
	@param		attrname	The name of the attribute of your class.
	@param		aliasname	The name of the alias.
*/
#define CLASS_ATTR_STYLE_ALIAS_COMPATIBILITY(c,attrname,aliasname) \
{	class_attr_style_alias(c,attrname,aliasname,false); \
	CLASS_ATTR_INVISIBLE(c,aliasname,0); \
	CLASS_ATTR_SAVE(c,aliasname,0); \
	CLASS_ATTR_PAINT(c,aliasname,0); }


/**	Define a Max 4 legacy RGB attribute alias
	@ingroup 	styles
	@param		c			The class whose attribute will be added to the style.
	@param		attrname	The name of the attribute of your class.
	@param		aliasname	The name of the alias.
	@see 'jslider' example project in the SDK.
*/
#define CLASS_ATTR_STYLE_ALIAS_RGBA_LEGACY(c,attrname,aliasname) \
{	class_attr_style_alias(c,attrname,aliasname,false); \
	CLASS_ATTR_INVISIBLE(c,aliasname,0); \
	CLASS_ATTR_PAINT(c,aliasname,0); \
	CLASS_ATTR_ACCESSORS(c,aliasname,NULL,jgraphics_attr_setrgb_alias); }


END_USING_C_LINKAGE

#endif // _EXT_BOXSTYLE_H
