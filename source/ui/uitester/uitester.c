/**
	@file
	uitester - demonstrate the drawing of various objects using jgraphics

	@ingroup	examples
*/

#include "ext.h"
#include "ext_obex.h"
#include "jpatcher_api.h"
#include "jgraphics.h"


/**********************************************************************/
// Data Structures

typedef struct _color_stop {
	double offset;
	t_jrgba color;
} t_color_stop;


typedef struct _uitester {
	t_jbox				j_box;
	long				j_whichmouse;
	long				j_mode;
	double				j_param1;			// generic params to hook to various tests
	double				j_param2;
	double				j_param3;
	double				j_param4;
	t_jmatrix			j_matrix;
	t_jpattern			*j_bgpattern;		// solid, gradient, or image
	t_jmatrix			j_pattern_matrix;
	t_jsurface			*j_image;			// for testing image drawing
	t_jsvg				*j_svg;				// svg, of course
	double				j_x0;
	double				j_y0;
	double				j_r0;
	double				j_x1;
	double				j_y1;
	double				j_r1;
	long				j_isradial;
	long				j_num_color_stops;
	t_color_stop		*j_color_stops;
	long				j_autoscale;		// set scale so box goes from 0 to 1 on each dim
} t_uitester;


/**********************************************************************/
// Prototypes

void uitester_initclass();
t_uitester *uitester_new(t_symbol *s, short argc, t_atom *argv);
void uitester_free(t_uitester *x);

void uitester_setmouse(t_uitester *x, long which);
void uitester_mouseenter(t_uitester *x, t_object *patcherview, t_pt pt, long modifiers);

void uitester_paint(t_uitester *x, t_object *view);
void uitester_read(t_uitester *x, t_symbol *s, short argc, t_atom *argv);
void uitester_doread(t_uitester *x, t_symbol *s, short argc, t_atom *argv);
void uitester_identity(t_uitester *x);
void uitester_translate(t_uitester *x, double tx, double ty);
void uitester_rotate(t_uitester *x, t_symbol *s, short argc, t_atom *argv);
void uitester_scale(t_uitester *x, double sx, double sy);
void uitester_pattern_identity(t_uitester *x);
void uitester_pattern_translate(t_uitester *x, double tx, double ty);
void uitester_pattern_rotate(t_uitester *x, double degrees);
void uitester_pattern_scale(t_uitester *x, double sx, double sy);
void uitester_setpattern(t_uitester *x, t_symbol *s, short argc, t_atom *argv);
void uitester_addcolorstop(t_uitester *x, t_symbol *s, short argc, t_atom *argv);
void uitester_clearcolorstops(t_uitester *x);
void uitester_setupgradient(t_uitester *x);
void uitester_autoscale(t_uitester *x, long way);
void uitester_size(t_uitester *x, long width, long height);
void uitester_param1(t_uitester *x, double value);
void uitester_param2(t_uitester *x, double value);
void uitester_param3(t_uitester *x, double value);
void uitester_param4(t_uitester *x, double value);

// various painting tests
void uitester_int(t_uitester *x, long which);
void uitester_rectangle(t_jgraphics *g, double width, double height);
void uitester_image(t_uitester *x, t_jgraphics *g, double width, double height);
void uitester_svg(t_uitester *x, t_jgraphics *g, double width, double height);

void snippet_normalize(t_jgraphics *g, double width, double height);
void snippet_arc(t_jgraphics *cr, double width, double height);
void snippet_arc_negative(t_jgraphics *cr, double width, double height);
void snippet_curve_rectangle(t_jgraphics *cr, double width, double height);
void snippet_curve_to(t_jgraphics *cr, double width, double height);
void snippet_fill_and_stroke2(t_jgraphics *cr, double width, double height);
void snippet_fill_and_stroke(t_jgraphics *cr, double width, double height);
void snippet_gradient(t_jgraphics *cr, double width, double height);
void snippet_path(t_jgraphics *cr, double width, double height);
void snippet_set_line_cap(t_jgraphics *cr, double width, double height);
void snippet_set_line_join(t_jgraphics *cr, double width, double height);
void snippet_dash(t_jgraphics *cr, double width, double height);
void snippet_long_lines(t_jgraphics *cr, double width, double height);
void snippet_multi_segment_caps(t_jgraphics *cr, double width, double height);
void snippet_self_intersect(t_jgraphics *cr, double width, double height);
void snippet_clock(t_jgraphics *cr, double width, double height);
void snippet_offscreen(t_jgraphics *cr, double width, double height);
void snippet_doughnut(t_jgraphics *cr, double width, double height);

void uitester_fill_path_with_surface(t_jgraphics *g, double width, double height);
void uitester_antialiased_lines(t_jgraphics *g, double width, double height);

void uitester_image_surface_draw(t_jgraphics *g, double width, double height);

void uitester_textlayout(t_jgraphics *g, double width, double height);
void uitester_scroll(t_jgraphics *g, double width, double height);
void uitester_showtext(t_jgraphics *g, double width, double height);

void uitester_strokeroundedrect(t_jgraphics *g, double width, double height);

void uitester_textlayouttransformed(t_jgraphics *g, double width, double height);


/**********************************************************************/
// Globals and Statics

static t_class *s_uitester_class = NULL;


/**********************************************************************/
// Class Definition and Life Cycle

void ext_main(void *r)
{
	t_class *c;

	c = class_new("uitester",
				  (method)uitester_new,
				  (method)uitester_free,
				  sizeof(t_uitester),
				  (method)NULL,
				  A_GIMME,
				  0L);

	jbox_initclass(c, 0);

	class_addmethod(c, (method) uitester_setmouse,			"setmouse", A_LONG, 0);
	class_addmethod(c, (method) uitester_mouseenter,		"mouseenter", A_CANT, 0);
	class_addmethod(c, (method) uitester_read,				"read", A_GIMME, 0);
	class_addmethod(c, (method) uitester_paint,				"paint", A_CANT, 0);
	class_addmethod(c, (method) uitester_identity,			"identity", 0);
	class_addmethod(c, (method) uitester_translate,			"translate", A_FLOAT, A_FLOAT, 0);
	class_addmethod(c, (method) uitester_rotate,			"rotate", A_GIMME, 0);
	class_addmethod(c, (method) uitester_scale,				"scale", A_FLOAT, A_FLOAT, 0);
	class_addmethod(c, (method) uitester_pattern_identity,	"patternidentity", 0);
	class_addmethod(c, (method) uitester_pattern_translate,	"patterntranslate", A_FLOAT, A_FLOAT, 0);
	class_addmethod(c, (method) uitester_pattern_rotate,	"patternrotate", A_FLOAT, 0);
	class_addmethod(c, (method) uitester_pattern_scale,		"patternscale", A_FLOAT, A_FLOAT, 0);
	class_addmethod(c, (method) uitester_setpattern,		"setpattern", A_GIMME, 0);
	class_addmethod(c, (method) uitester_addcolorstop,		"addcolorstop", A_GIMME, 0);
	class_addmethod(c, (method) uitester_autoscale,			"autoscale", A_LONG, 0);
	class_addmethod(c, (method) uitester_size,				"size", A_LONG, A_LONG, 0);
	class_addmethod(c, (method) uitester_clearcolorstops,	"clearcolorstops", 0);
	class_addmethod(c, (method) uitester_param1,			"param1", A_FLOAT, 0);
	class_addmethod(c, (method) uitester_param2,			"param2", A_FLOAT, 0);
	class_addmethod(c, (method) uitester_param3,			"param3", A_FLOAT, 0);
	class_addmethod(c, (method) uitester_param4,			"param4", A_FLOAT, 0);
	class_addmethod(c, (method) uitester_int,				"int", A_LONG, 0);

	CLASS_ATTR_DEFAULT(c, "rect", 0, "0. 0. 128. 128.");

	class_register(CLASS_BOX, c);
	s_uitester_class = c;
}


t_uitester *uitester_new(t_symbol *s, short argc, t_atom *argv)
{
	t_uitester *x = (t_uitester *)object_alloc(s_uitester_class);

	if (x) {
		long flags;
		flags = 0
				| JBOX_DRAWFIRSTIN
				//		| JBOX_NODRAWBOX
				//		| JBOX_DRAWINLAST
				| JBOX_TRANSPARENT
				//		| JBOX_NOGROW
				//		| JBOX_GROWY
				| JBOX_GROWBOTH
				//		| JBOX_IGNORELOCKCLICK
				| JBOX_HILITE
				//		| JBOX_BACKGROUND
				//		| JBOX_NOFLOATINSPECTOR
				//		| JBOX_TEXTFIELD
				;

		jbox_new(&x->j_box, flags, argc, argv);
		x->j_box.b_firstin = (t_object *) x;

		x->j_whichmouse = -1;  // none set
		x->j_param1 = 0;
		x->j_param2 = 0;
		x->j_param3 = 0;
		x->j_param4 = 0;
		jgraphics_matrix_init_identity(&x->j_matrix);
		x->j_bgpattern = NULL;
		x->j_image = NULL;
		x->j_svg = NULL;
		jgraphics_matrix_init_identity(&x->j_pattern_matrix);
		x->j_num_color_stops = 0;
		x->j_color_stops = NULL;
		x->j_x0 = x->j_y0 = x->j_r0 = 0;
		x->j_x1 = x->j_y1 = x->j_r1 = 0;
		x->j_isradial = 0;
		x->j_autoscale = 0;

		jbox_ready(&x->j_box);
	}
	return x;
}


void uitester_free(t_uitester *x)
{
	jbox_free(&x->j_box);
	if (x->j_bgpattern) {
		jgraphics_pattern_destroy(x->j_bgpattern);
		x->j_bgpattern = NULL;
	}
	if (x->j_image) {
		jgraphics_surface_destroy(x->j_image);
		x->j_image = NULL;
	}
	if (x->j_svg) {
		jsvg_destroy(x->j_svg);
		x->j_svg = NULL;
	}
}


/**********************************************************************/
// Methods

void uitester_identity(t_uitester *x)
{
	jgraphics_matrix_init_identity(&x->j_matrix);
	jbox_redraw(&x->j_box);
}


void uitester_translate(t_uitester *x, double tx, double ty)
{
	jgraphics_matrix_translate(&x->j_matrix, tx, ty);
	jbox_redraw(&x->j_box);
}


void uitester_rotate(t_uitester *x, t_symbol *s, short argc, t_atom *argv)
{
	double degrees = 0;
	double cx=0, cy=0;
	if (argc--)
		degrees = atom_getfloat(argv++);
	if (argc--)
		cx = atom_getfloat(argv++);
	if (argc--)
		cy = atom_getfloat(argv++);
	jgraphics_matrix_translate(&x->j_matrix, -cx, -cy);
	jgraphics_matrix_rotate(&x->j_matrix, degrees * JGRAPHICS_PI * (1./180.));
	jgraphics_matrix_translate(&x->j_matrix, cx, cy);
	jbox_redraw(&x->j_box);
}


void uitester_scale(t_uitester *x, double sx, double sy)
{
	jgraphics_matrix_scale(&x->j_matrix, sx, sy);
	jbox_redraw(&x->j_box);
}


void uitester_pattern_identity(t_uitester *x)
{
	jgraphics_matrix_init_identity(&x->j_pattern_matrix);
	jbox_redraw(&x->j_box);
}


void uitester_pattern_translate(t_uitester *x, double tx, double ty)
{
	jgraphics_matrix_translate(&x->j_pattern_matrix, tx, ty);
	jbox_redraw(&x->j_box);
}


void uitester_pattern_rotate(t_uitester *x, double degrees)  // degrees are more convenient from a max message
{
	jgraphics_matrix_rotate(&x->j_pattern_matrix, degrees * JGRAPHICS_PI * (1./180.));
	jbox_redraw(&x->j_box);
}


void uitester_pattern_scale(t_uitester *x, double sx, double sy)
{
	jgraphics_matrix_scale(&x->j_pattern_matrix, sx, sy);
	jbox_redraw(&x->j_box);
}


void uitester_setpattern(t_uitester *x, t_symbol *s, short argc, t_atom *argv)
{
	if (!argc)
		return;
	if (x->j_bgpattern) {
		jgraphics_pattern_destroy(x->j_bgpattern);
		x->j_bgpattern = NULL;
	}
	if (argv->a_type == A_FLOAT) {
		double red=0, green=0, blue=0, alpha=1;
		if (argc--)
			red = atom_getfloat(argv++);
		if (argc--)
			green = atom_getfloat(argv++);
		if (argc--)
			blue = atom_getfloat(argv++);
		if (argc--)
			alpha = atom_getfloat(argv++);
		x->j_bgpattern = jgraphics_pattern_create_rgba(red, green, blue, alpha);
	}
	else if (argv->a_type == A_SYM) {
		t_symbol *s = argv->a_w.w_sym;
		argc--, argv++;
		if (s == gensym("image")) {

		}
		else if (s == gensym("linear")) {
			double x0 = 0, y0 = 0, x1 = 0, y1 = 0;
			if (argc--)
				x0 = atom_getfloat(argv++);
			if (argc--)
				y0 = atom_getfloat(argv++);
			if (argc--)
				x1 = atom_getfloat(argv++);
			if (argc--)
				y1 = atom_getfloat(argv++);
			x->j_x0 = x0;
			x->j_y0 = y0;
			x->j_x1 = x1;
			x->j_y1 = y1;
			x->j_isradial = 0;
			uitester_setupgradient(x);
		}
		else if (s == gensym("radial")) {
			double cx0=0, cy0=0, r0=1, cx1=0, cy1=0, r1=1;
			if (argc--)
				cx0 = atom_getfloat(argv++);
			if (argc--)
				cy0 = atom_getfloat(argv++);
			if (argc--)
				r0 = atom_getfloat(argv++);
			if (argc--)
				cx1 = atom_getfloat(argv++);
			if (argc--)
				cy1 = atom_getfloat(argv++);
			if (argc--)
				r1 = atom_getfloat(argv++);
			x->j_x0 = cx0;
			x->j_y0 = cy0;
			x->j_r0 = r0;
			x->j_x1 = cx1;
			x->j_y1 = cy1;
			x->j_r1 = r1;
			x->j_isradial = 1;
			uitester_setupgradient(x);
		}
	}
	jbox_redraw(&x->j_box);
}


void uitester_addcolorstop(t_uitester *x, t_symbol *s, short argc, t_atom *argv)
{
	double offset=0, r=0, g=0, b=0, a=1;
	if (!x->j_color_stops) {
		x->j_color_stops = (t_color_stop *) sysmem_newptr(sizeof(t_color_stop));
	}
	else {
		x->j_color_stops = (t_color_stop *) sysmem_resizeptr(x->j_color_stops, sizeof(t_color_stop) * (x->j_num_color_stops+1));
	}
	x->j_num_color_stops++;
	if (argc--)
		offset = atom_getfloat(argv++);
	if (argc--)
		r = atom_getfloat(argv++);
	if (argc--)
		g = atom_getfloat(argv++);
	if (argc--)
		b = atom_getfloat(argv++);
	if (argc--)
		a = atom_getfloat(argv++);
	x->j_color_stops[x->j_num_color_stops-1].offset = offset;
	x->j_color_stops[x->j_num_color_stops-1].color.red = r;
	x->j_color_stops[x->j_num_color_stops-1].color.green = g;
	x->j_color_stops[x->j_num_color_stops-1].color.blue = b;
	x->j_color_stops[x->j_num_color_stops-1].color.alpha = a;
	uitester_setupgradient(x);
}


void uitester_clearcolorstops(t_uitester *x)
{
	if (x->j_color_stops) {
		sysmem_freeptr(x->j_color_stops);
		x->j_color_stops = NULL;
	}
	x->j_num_color_stops = 0;
	if (x->j_bgpattern) {
		t_jgraphics_pattern_type type;
		type = jgraphics_pattern_get_type(x->j_bgpattern);
		if (type == JGRAPHICS_PATTERN_TYPE_LINEAR || type == JGRAPHICS_PATTERN_TYPE_RADIAL) {
			uitester_setupgradient(x);
		}
	}
}


void uitester_setupgradient(t_uitester *x)
{
	if (x->j_bgpattern) {
		jgraphics_pattern_destroy(x->j_bgpattern);
		x->j_bgpattern = NULL;
	}
	if (x->j_num_color_stops < 2)
		return; // can't make it yet
	if (!x->j_isradial) {
		x->j_bgpattern = jgraphics_pattern_create_linear(x->j_x0, x->j_y0, x->j_x1, x->j_y1);
	}
	else {
		x->j_bgpattern = jgraphics_pattern_create_radial(x->j_x0, x->j_y0, x->j_r0, x->j_x1, x->j_y1, x->j_r1);
	}
	if (x->j_bgpattern) {
		int i;
		for (i=0; i < x->j_num_color_stops; i++) {
			t_color_stop *cs;
			cs = &x->j_color_stops[i];
			jgraphics_pattern_add_color_stop_rgba(x->j_bgpattern, cs->offset,
												  cs->color.red, cs->color.green, cs->color.blue, cs->color.alpha);
		}
	}
	jbox_redraw(&x->j_box);
}


void uitester_autoscale(t_uitester *x, long way)
{
	x->j_autoscale = way;
	jbox_redraw(&x->j_box);
}


void uitester_size(t_uitester *x, long width, long height)
{
	t_size size;
	size.width = (double) width;
	size.height = (double) height;
	jbox_set_size((t_object *) x, &size);
}


void uitester_param1(t_uitester *x, double value)
{
	x->j_param1 = value;
	jbox_redraw(&x->j_box);
}


void uitester_param2(t_uitester *x, double value)
{
	x->j_param2 = value;
	jbox_redraw(&x->j_box);
}


void uitester_param3(t_uitester *x, double value)
{
	x->j_param3 = value;
	jbox_redraw(&x->j_box);
}


void uitester_param4(t_uitester *x, double value)
{
	x->j_param4 = value;
	jbox_redraw(&x->j_box);
}


void uitester_setmouse(t_uitester *x, long which)
{
	x->j_whichmouse = which;
}


void uitester_mouseenter(t_uitester *x, t_object *patcherview, t_pt pt, long modifiers)
{
	// to set the mouse you need to have a view, thus we do it in the mouseenter
	if (x->j_whichmouse >= 0) {
		jmouse_setcursor(patcherview, (t_object *) x, (t_jmouse_cursortype) x->j_whichmouse);
	}
	else if (x->j_whichmouse == -2) {
		// let's try drawing a cursor
		t_jgraphics *g;
		t_jsurface *s;
		s = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, 32, 32);
		g = jgraphics_create(s);

		jgraphics_arc(g, 16., 16., 15., 0, JGRAPHICS_PI * 2);
		jgraphics_close_path(g);
		jgraphics_set_line_width(g, 1.);
		jgraphics_set_source_rgba(g, .8, .1, .1, .5);
		jgraphics_fill_preserve(g);
		jgraphics_set_source_rgba(g, 0, 0, 0, 1);
		jgraphics_stroke(g);

		jmouse_setcursor_surface(patcherview, (t_object *) x, s, 16, 16);

		jgraphics_destroy(g);
		jgraphics_surface_destroy(s);
	}
}


void uitester_paint(t_uitester *x, t_object *view)
{
	// paint the box grey
	t_rect rect;
	t_jgraphics *g;
	t_jmatrix autoscalematrix;
	double width, height;

	g = (t_jgraphics *) patcherview_get_jgraphics(view);

	// set up matrix
	jbox_get_rect_for_view((t_object *) x, view, &rect);
	if (x->j_autoscale) {
		jgraphics_matrix_init_scale(&autoscalematrix, rect.width, rect.height);
		jgraphics_matrix_multiply(&autoscalematrix, &autoscalematrix, &x->j_matrix);
		jgraphics_set_matrix(g, &autoscalematrix);
	}
	else {
		jgraphics_set_matrix(g, &x->j_matrix);
	}

	// set up pattern
	if (x->j_bgpattern) {
		jgraphics_pattern_set_matrix(x->j_bgpattern, &x->j_pattern_matrix);
		jgraphics_set_source(g, x->j_bgpattern);
		jgraphics_paint(g);		// fill bg with pattern
	}

	// call paint method, if non-null
	if (x->j_autoscale) {
		width = 1;
		height = 1;
	}
	else {
		width = rect.width;
		height = rect.height;
	}
	jgraphics_set_source_rgba(g, 0, 0, 0, 1);

	switch (x->j_mode) {
	case 0: uitester_rectangle(g, width, height); break;
	case 1: snippet_arc(g, width, height); break;
	case 2: snippet_arc_negative(g, width, height); break;
	case 3: snippet_curve_rectangle(g, width, height); break;
	case 4: snippet_curve_to(g, width, height); break;
	case 5: snippet_fill_and_stroke2(g, width, height); break;
	case 6: snippet_fill_and_stroke(g, width, height); break;
	case 7: snippet_gradient(g, width, height); break;
	case 8: snippet_path(g, width, height); break;
	case 9: snippet_set_line_cap(g, width, height); break;
	case 10: snippet_set_line_join(g, width, height); break;
	case 11: snippet_dash(g, width, height); break;
	case 12: snippet_long_lines(g, width, height); break;
	case 13: snippet_multi_segment_caps(g, width, height); break;
	case 14: snippet_self_intersect(g, width, height); break;
	case 15: snippet_clock(g, width, height); break;
	case 16: snippet_offscreen(g, width, height); break;
	case 17: snippet_doughnut(g, width, height); break;
	case 18: uitester_fill_path_with_surface(g, width, height); break;
	case 19: uitester_antialiased_lines(g, width, height); break;
	case 20: uitester_image_surface_draw(g, width, height); break;
	case 21: uitester_textlayout(g, width, height); break;
	case 22: uitester_scroll(g, width, height); break;
	case 23: uitester_showtext(g, width, height); break;
	case 24: uitester_strokeroundedrect(g, width, height); break;
	case 25: uitester_textlayouttransformed(g, width, height); break;
	case 26: uitester_svg(x, g, width, height); break;
	case 27: uitester_image(x, g, width, height); break;
	}
}


void uitester_read(t_uitester *x, t_symbol *s, short argc, t_atom *argv)
{
	defer(x,(method)uitester_doread,s,argc,argv);
}


void uitester_doread(t_uitester *x, t_symbol *s, short argc, t_atom *argv)
{
	char		filename[MAX_PATH_CHARS];
	short		vol = 0;
	t_fourcc	*type = NULL;
	t_fourcc	outtype;
	long		ntype = 0;

	if (!argc) {
		if (open_dialog(filename, &vol, &outtype, type, ntype))
			goto out;
	}
	else {
		strcpy(filename,argv->a_w.w_sym->s_name);
		if (!locatefile_extended(filename,&vol,&outtype,type,ntype)) {
			//continue
		}
		else
			goto out;
	}

	if (filename && filename[0]) {
		long len;
		len = strlen(filename);
		if ((len > 4) && (strcmp_case_insensitive(filename+len-4, ".svg") == 0)) {
			// if it ends in .svg we try to load an svg file
			t_jsvg *svg;
			svg = jsvg_create_from_file(filename, vol);
			if (svg) {
				if (x->j_svg) {
					jsvg_destroy(x->j_svg);
				}
				x->j_svg = svg;
				x->j_mode = 30;
			}
		}
		else {
			// otherwise we try to load an image
			t_jsurface *surface;
			surface = jgraphics_image_surface_create_from_file(filename, vol);
			if (surface) {
				if (x->j_image) {
					jgraphics_surface_destroy(x->j_image);
				}
				x->j_image = surface;
				x->j_mode = 31;
			}
		}
	}

	jbox_redraw(&x->j_box);

out:
	return;
}


void uitester_int(t_uitester *x, long which)
{
	x->j_mode = which;
	jbox_redraw(&x->j_box);
}


void uitester_image(t_uitester *x, t_jgraphics *g, double width, double height)
{
	if (x && x->j_image) {
		int iw, ih;
		snippet_normalize (g, width, height);

		iw = jgraphics_image_surface_get_width(x->j_image);
		ih = jgraphics_image_surface_get_height(x->j_image);
		jgraphics_scale(g, 1./iw, 1./ih);
		jgraphics_set_source_surface(g, x->j_image, 0, 0);
		jgraphics_paint(g);
	}
}

void uitester_svg(t_uitester *x, t_jgraphics *g, double width, double height)
{
	if (x && x->j_svg) {
		double sw, sh;
		int count, i;
		snippet_normalize(g, height, height);
		jsvg_get_size(x->j_svg, &sw, &sh);
		jgraphics_scale(g, 1./sw, 1./sh);
		count = width / (height+5) + 1;
		for (i=0; i < count; i++) {
			jsvg_render(x->j_svg, g);
			jgraphics_translate(g, sw+5, 0);
		}
	}
}

void uitester_rectangle(t_jgraphics *g, double width, double height)
{
	snippet_normalize (g, width, height);
	jgraphics_rectangle(g, -.5, -.5, 1., 1.);
	jgraphics_set_source_rgba(g, 0, 0, 0, 1);
	jgraphics_stroke(g);
}

void snippet_normalize(t_jgraphics *g, double width, double height)
{
	jgraphics_scale(g, width, height);
	jgraphics_set_line_width(g, .04);
}

void snippet_arc(t_jgraphics *cr, double width, double height)
{
	double xc = 0.5;
	double yc = 0.5;
	double radius = 0.4;
	double angle1 = 45.0  * (JGRAPHICS_PI/180.0);  /* angles are specified */
	double angle2 = 180.0 * (JGRAPHICS_PI/180.0);  /* in radians           */

	snippet_normalize (cr, width, height);

	jgraphics_arc (cr, xc, yc, radius, angle1, angle2);
	jgraphics_stroke (cr);

	/* draw helping lines */
	jgraphics_set_source_rgba (cr, 1,0.2,0.2,0.6);
	jgraphics_arc (cr, xc, yc, 0.05, 0, 2*JGRAPHICS_PI);
	jgraphics_fill (cr);
	jgraphics_set_line_width (cr, 0.03);
	jgraphics_arc (cr, xc, yc, radius, angle1, angle1);
	jgraphics_line_to (cr, xc, yc);
	jgraphics_arc (cr, xc, yc, radius, angle2, angle2);
	jgraphics_line_to (cr, xc, yc);
	jgraphics_stroke (cr);
}

double xc = 0.5;
double yc = 0.5;
double radius = 0.4;
double angle1 = 45.0  * (JGRAPHICS_PI/180.0);  /* angles are specified */
double angle2 = 180.0 * (JGRAPHICS_PI/180.0);  /* in radians           */

void snippet_arc_negative(t_jgraphics *cr, double width, double height)
{
	snippet_normalize (cr, width, height);

	jgraphics_arc_negative (cr, xc, yc, radius, angle1, angle2);
	jgraphics_stroke (cr);

	/* draw helping lines */
	jgraphics_set_source_rgba (cr, 1,0.2,0.2,0.6);
	jgraphics_arc (cr, xc, yc, 0.05, 0, 2*JGRAPHICS_PI);
	jgraphics_fill (cr);
	jgraphics_set_line_width (cr, 0.03);
	jgraphics_arc (cr, xc, yc, radius, angle1, angle1);
	jgraphics_line_to (cr, xc, yc);
	jgraphics_arc (cr, xc, yc, radius, angle2, angle2);
	jgraphics_line_to (cr, xc, yc);
	jgraphics_stroke (cr);
}

void snippet_curve_rectangle(t_jgraphics *cr, double width, double height)
{
	/* a custom shape, that could be wrapped in a function */
	double x0	   = 0.1,   /*< parameters like jgraphics_rectangle */
			 y0	   = 0.1,
			  rect_width  = 0.8,
			  rect_height = 0.8,
			  radius = 0.4;   /*< and an approximate curvature radius */

	double x1,y1;

	snippet_normalize (cr, width, height);

	x1=x0+rect_width;
	y1=y0+rect_height;
	if (!rect_width || !rect_height)
		return;
	if (rect_width/2<radius) {
		if (rect_height/2<radius) {
			jgraphics_move_to  (cr, x0, (y0 + y1)/2);
			jgraphics_curve_to (cr, x0 ,y0, x0, y0, (x0 + x1)/2, y0);
			jgraphics_curve_to (cr, x1, y0, x1, y0, x1, (y0 + y1)/2);
			jgraphics_curve_to (cr, x1, y1, x1, y1, (x1 + x0)/2, y1);
			jgraphics_curve_to (cr, x0, y1, x0, y1, x0, (y0 + y1)/2);
		} else {
			jgraphics_move_to  (cr, x0, y0 + radius);
			jgraphics_curve_to (cr, x0 ,y0, x0, y0, (x0 + x1)/2, y0);
			jgraphics_curve_to (cr, x1, y0, x1, y0, x1, y0 + radius);
			jgraphics_line_to (cr, x1 , y1 - radius);
			jgraphics_curve_to (cr, x1, y1, x1, y1, (x1 + x0)/2, y1);
			jgraphics_curve_to (cr, x0, y1, x0, y1, x0, y1- radius);
		}
	} else {
		if (rect_height/2<radius) {
			jgraphics_move_to  (cr, x0, (y0 + y1)/2);
			jgraphics_curve_to (cr, x0 , y0, x0 , y0, x0 + radius, y0);
			jgraphics_line_to (cr, x1 - radius, y0);
			jgraphics_curve_to (cr, x1, y0, x1, y0, x1, (y0 + y1)/2);
			jgraphics_curve_to (cr, x1, y1, x1, y1, x1 - radius, y1);
			jgraphics_line_to (cr, x0 + radius, y1);
			jgraphics_curve_to (cr, x0, y1, x0, y1, x0, (y0 + y1)/2);
		} else {
			jgraphics_move_to  (cr, x0, y0 + radius);
			jgraphics_curve_to (cr, x0 , y0, x0 , y0, x0 + radius, y0);
			jgraphics_line_to (cr, x1 - radius, y0);
			jgraphics_curve_to (cr, x1, y0, x1, y0, x1, y0 + radius);
			jgraphics_line_to (cr, x1 , y1 - radius);
			jgraphics_curve_to (cr, x1, y1, x1, y1, x1 - radius, y1);
			jgraphics_line_to (cr, x0 + radius, y1);
			jgraphics_curve_to (cr, x0, y1, x0, y1, x0, y1- radius);
		}
	}
	jgraphics_close_path (cr);

	jgraphics_set_source_rgb (cr, 0.5,0.5,1);
	jgraphics_fill_preserve (cr);
	jgraphics_set_source_rgba (cr, 0.5, 0, 0, 0.5);
	jgraphics_stroke (cr);
}

void snippet_curve_to(t_jgraphics *cr, double width, double height)
{
	double x=0.1,  y=0.5;
	double x1=0.4, y1=0.9,
		   x2=0.6, y2=0.1,
		   x3=0.9, y3=0.5;
	snippet_normalize (cr, width, height);

	jgraphics_move_to (cr,  x, y);
	jgraphics_curve_to (cr, x1, y1, x2, y2, x3, y3);

	jgraphics_stroke (cr);

	jgraphics_set_source_rgba (cr, 1,0.2,0.2,0.6);
	jgraphics_set_line_width (cr, 0.03);
	jgraphics_move_to (cr,x,y);   jgraphics_line_to (cr,x1,y1);
	jgraphics_move_to (cr,x2,y2); jgraphics_line_to (cr,x3,y3);
	jgraphics_stroke (cr);
}

void snippet_fill_and_stroke2(t_jgraphics *cr, double width, double height)
{
	snippet_normalize (cr, width, height);

	jgraphics_move_to (cr, 0.5, 0.1);
	jgraphics_line_to (cr, 0.9, 0.9);
	jgraphics_rel_line_to (cr, -0.4, 0.0);
	jgraphics_curve_to (cr, 0.2, 0.9, 0.2, 0.5, 0.5, 0.5);
	jgraphics_close_path (cr);

	jgraphics_move_to (cr, 0.25, 0.1);
	jgraphics_rel_line_to (cr, 0.2, 0.2);
	jgraphics_rel_line_to (cr, -0.2, 0.2);
	jgraphics_rel_line_to (cr, -0.2, -0.2);
	jgraphics_close_path (cr);

	jgraphics_set_source_rgb (cr, 0, 0, 1);
	jgraphics_fill_preserve (cr);
	jgraphics_set_source_rgb (cr, 0, 0, 0);
	jgraphics_stroke (cr);
}

void snippet_fill_and_stroke(t_jgraphics *cr, double width, double height)
{
	snippet_normalize (cr, width, height);

	jgraphics_move_to (cr, 0.5, 0.1);
	jgraphics_line_to (cr, 0.9, 0.9);
	jgraphics_rel_line_to (cr, -0.4, 0.0);
	jgraphics_curve_to (cr, 0.2, 0.9, 0.2, 0.5, 0.5, 0.5);
	jgraphics_close_path (cr);

	jgraphics_set_source_rgb (cr, 0, 0, 1);
	jgraphics_fill_preserve (cr);
	jgraphics_set_source_rgb (cr, 0, 0, 0);
	jgraphics_stroke (cr);
}

void snippet_gradient(t_jgraphics *cr, double width, double height)
{
	t_jpattern *pat;

	snippet_normalize (cr, width, height);

	pat = jgraphics_pattern_create_linear (0.0, 0.0,  0.0, 1.0);
	jgraphics_pattern_add_color_stop_rgba (pat, 1, 0, 0, 0, 1);
	jgraphics_pattern_add_color_stop_rgba (pat, 0, 1, 1, 1, 1);
	jgraphics_rectangle (cr, 0, 0, 1, 1);
	jgraphics_set_source (cr, pat);
	jgraphics_fill (cr);
	jgraphics_pattern_destroy (pat);

	pat = jgraphics_pattern_create_radial (0.45, 0.4, 0.1,
										   0.4,  0.4, 0.5);
	jgraphics_pattern_add_color_stop_rgba (pat, 0, 1, 1, 1, 1);
	jgraphics_pattern_add_color_stop_rgba (pat, 1, 0, 0, 0, 1);
	jgraphics_set_source (cr, pat);
	jgraphics_arc (cr, 0.5, 0.5, 0.3, 0, 2 * JGRAPHICS_PI);
	jgraphics_fill (cr);
	jgraphics_pattern_destroy (pat);
}

void snippet_path(t_jgraphics *cr, double width, double height)
{
	snippet_normalize (cr, width, height);
	jgraphics_move_to (cr, 0.5, 0.1);
	jgraphics_line_to (cr, 0.9, 0.9);
	jgraphics_rel_line_to (cr, -0.4, 0.0);
	jgraphics_curve_to (cr, 0.2, 0.9, 0.2, 0.5, 0.5, 0.5);

	jgraphics_stroke (cr);
}

void snippet_set_line_cap(t_jgraphics *cr, double width, double height)
{
	snippet_normalize (cr, width, height);
	jgraphics_set_line_width (cr, 0.12);
	jgraphics_set_line_cap  (cr, JGRAPHICS_LINE_CAP_BUTT); /* default */
	jgraphics_move_to (cr, 0.25, 0.2); jgraphics_line_to (cr, 0.25, 0.8);
	jgraphics_stroke (cr);
	jgraphics_set_line_cap  (cr, JGRAPHICS_LINE_CAP_ROUND);
	jgraphics_move_to (cr, 0.5, 0.2); jgraphics_line_to (cr, 0.5, 0.8);
	jgraphics_stroke (cr);
	jgraphics_set_line_cap  (cr, JGRAPHICS_LINE_CAP_SQUARE);
	jgraphics_move_to (cr, 0.75, 0.2); jgraphics_line_to (cr, 0.75, 0.8);
	jgraphics_stroke (cr);

	/* draw helping lines */
	jgraphics_set_source_rgb (cr, 1,0.2,0.2);
	jgraphics_set_line_width (cr, 0.01);
	jgraphics_move_to (cr, 0.25, 0.2); jgraphics_line_to (cr, 0.25, 0.8);
	jgraphics_move_to (cr, 0.5, 0.2);  jgraphics_line_to (cr, 0.5, 0.8);
	jgraphics_move_to (cr, 0.75, 0.2); jgraphics_line_to (cr, 0.75, 0.8);
	jgraphics_stroke (cr);
}

void snippet_set_line_join(t_jgraphics *cr, double width, double height)
{
	snippet_normalize (cr, width, height);
	jgraphics_set_line_width (cr, 0.16);
	jgraphics_move_to (cr, 0.3, 0.33);
	jgraphics_rel_line_to (cr, 0.2, -0.2);
	jgraphics_rel_line_to (cr, 0.2, 0.2);
	jgraphics_set_line_join (cr, JGRAPHICS_LINE_JOIN_MITER); /* default */
	jgraphics_stroke (cr);

	jgraphics_move_to (cr, 0.3, 0.63);
	jgraphics_rel_line_to (cr, 0.2, -0.2);
	jgraphics_rel_line_to (cr, 0.2, 0.2);
	jgraphics_set_line_join (cr, JGRAPHICS_LINE_JOIN_BEVEL);
	jgraphics_stroke (cr);

	jgraphics_move_to (cr, 0.3, 0.93);
	jgraphics_rel_line_to (cr, 0.2, -0.2);
	jgraphics_rel_line_to (cr, 0.2, 0.2);
	jgraphics_set_line_join (cr, JGRAPHICS_LINE_JOIN_ROUND);
	jgraphics_stroke (cr);
}

void snippet_dash(t_jgraphics *cr, double width, double height)
{
	double dashes[] = {0.20,  /* ink */
					   0.05,  /* skip */
					   0.05,  /* ink */
					   0.05   /* skip*/
					  };
	int    ndash  = sizeof (dashes)/sizeof(dashes[0]);
	//	double offset = -0.2;
	double offset = 0;

	snippet_normalize (cr, width, height);

	jgraphics_set_dash (cr, dashes, ndash, offset);

	jgraphics_move_to (cr, 0.5, 0.1);
	jgraphics_line_to (cr, 0.9, 0.9);
	jgraphics_rel_line_to (cr, -0.4, 0.0);
	jgraphics_curve_to (cr, 0.2, 0.9, 0.2, 0.5, 0.5, 0.5);

	jgraphics_stroke (cr);
}

void snippet_long_lines(t_jgraphics *cr, double width, double height)
{
	snippet_normalize (cr, width, height);

	jgraphics_move_to (cr, 0.1, -50);
	jgraphics_line_to (cr, 0.1,  50);
	jgraphics_set_source_rgb (cr, 1, 0 ,0);
	jgraphics_stroke (cr);

	jgraphics_move_to (cr, 0.2, -60);
	jgraphics_line_to (cr, 0.2,  60);
	jgraphics_set_source_rgb (cr, 1, 1 ,0);
	jgraphics_stroke (cr);

	jgraphics_move_to (cr, 0.3, -70);
	jgraphics_line_to (cr, 0.3,  70);
	jgraphics_set_source_rgb (cr, 0, 1 ,0);
	jgraphics_stroke (cr);

	jgraphics_move_to (cr, 0.4, -80);
	jgraphics_line_to (cr, 0.4,  80);
	jgraphics_set_source_rgb (cr, 0, 0 ,1);
	jgraphics_stroke (cr);
}

void snippet_multi_segment_caps(t_jgraphics *cr, double width, double height)
{
	snippet_normalize (cr, width, height);

	jgraphics_move_to (cr, 0.2, 0.3);
	jgraphics_line_to (cr, 0.8, 0.3);

	jgraphics_move_to (cr, 0.2, 0.5);
	jgraphics_line_to (cr, 0.8, 0.5);

	jgraphics_move_to (cr, 0.2, 0.7);
	jgraphics_line_to (cr, 0.8, 0.7);

	jgraphics_set_line_width (cr, 0.12);
	jgraphics_set_line_cap  (cr, JGRAPHICS_LINE_CAP_ROUND);
	jgraphics_stroke (cr);
}

void snippet_self_intersect(t_jgraphics *cr, double width, double height)
{
	snippet_normalize (cr, width, height);

	jgraphics_move_to (cr, 0.3, 0.3);
	jgraphics_line_to (cr, 0.7, 0.3);

	jgraphics_line_to (cr, 0.5, 0.3);
	jgraphics_line_to (cr, 0.5, 0.7);

	jgraphics_set_line_width (cr, 0.22);
	jgraphics_set_line_cap  (cr, JGRAPHICS_LINE_CAP_ROUND);
	jgraphics_set_line_join  (cr, JGRAPHICS_LINE_JOIN_ROUND);
	jgraphics_stroke (cr);
}

void snippet_clock(t_jgraphics *cr, double width, double height)
{
	/* store the current time */
	//	time_t rawtime;
	//	time(&rawtime);
	//	struct tm * timeinfo;
	/* In newer versions of Visual Studio localtime(..) is deprecated. Use localtime_s instead. See MSDN. */
	//	timeinfo = localtime(&rawtime);

	/* compute the angles of the indicators of our clock */
	//	double minutes = timeinfo->tm_min * M_PI / 30;
	//	double hours = timeinfo->tm_hour * M_PI / 6;
	//	double seconds= timeinfo->tm_sec * M_PI / 30;
	double minutes = 50. * JGRAPHICS_PI / 30;
	double hours = 2.8 * JGRAPHICS_PI / 6;
	double seconds = 30. * JGRAPHICS_PI / 30;

	/* Normalize our context to a (width, height) of (1.0, 1.0) by scaling by our window width and height. */
	jgraphics_scale (cr, width, height);

	/* draw the entire context white. */
	jgraphics_set_source_rgba (cr, 1, 1, 1, 1);
	jgraphics_paint(cr);

	/* who doesn't want all those nice line settings :) */
	jgraphics_set_line_cap  (cr, JGRAPHICS_LINE_CAP_ROUND);
	jgraphics_set_line_width(cr, 0.1);

	/* translate to the center of the rendering context and draw a black clock outline */
	jgraphics_set_source_rgba (cr, 0, 0, 0, 1);
	jgraphics_translate(cr, 0.5, 0.5);
	jgraphics_arc(cr, 0, 0, 0.4, 0, JGRAPHICS_PI * 2);
	jgraphics_stroke(cr);

	/* draw a white dot on the current second. */
	jgraphics_set_source_rgba (cr, 1, 1, 1, 0.6);
	jgraphics_arc(cr, sin(seconds) * 0.4, -cos(seconds) * 0.4, 0.05, 0, JGRAPHICS_PI * 2);
	jgraphics_fill(cr);

	/* draw the minutes indicator */
	jgraphics_set_source_rgba (cr, 0.2, 0.2, 1, 0.6);
	jgraphics_move_to(cr, 0, 0);
	jgraphics_line_to(cr, sin(minutes) * 0.4, -cos(minutes) * 0.4);
	jgraphics_stroke (cr);

	/* draw the hours indicator      */
	jgraphics_move_to(cr, 0, 0);
	jgraphics_line_to(cr, sin(hours) * 0.2, -cos(hours) * 0.2);
	jgraphics_stroke (cr);
}

void snippet_offscreen(t_jgraphics *cr, double width, double height)
{
	t_jsurface	*surface;
	t_jpattern	*pattern;
	t_jmatrix	matrix;
	t_jgraphics	*g;

	snippet_normalize(cr, width, height);

	jgraphics_set_source_rgb(cr, 1,0,0);
	jgraphics_paint(cr);

	surface = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, width, height);
	g = jgraphics_create(surface);
	snippet_normalize(g, width, height);

	jgraphics_set_source_rgb(g, 0, 1, 0);
	jgraphics_rectangle(g, .2, .2, .6, .6);
	jgraphics_fill_preserve(g);
	jgraphics_set_source_rgb(g, 0, 0, 1);
	jgraphics_stroke(g);

	pattern = jgraphics_pattern_create_for_surface(surface);
	jgraphics_get_matrix(cr, &matrix);
	jgraphics_pattern_set_matrix(pattern, &matrix);
	jgraphics_set_source(cr, pattern);

	jgraphics_paint_with_alpha(cr, .5);

	jgraphics_pattern_destroy(pattern);
	jgraphics_surface_destroy(surface);
	jgraphics_destroy(g);
}


void snippet_doughnut(t_jgraphics *cr, double width, double height)
{
	// How do you draw a doughnut (shape with a hole in it)?
	// Here is one way.
	jgraphics_set_source_rgb(cr, .2, .8, 0);
#if 0
	// Here's one way
	jgraphics_arc(cr, width*.5, height*.5, width*.5, 0, JGRAPHICS_2PI);
	jgraphics_arc_negative(cr, width*.5, height*.5, width*.25, JGRAPHICS_2PI, 0);
	jgraphics_close_path(cr);
#elif 0
	// Or, setting the winding to even/odd seems to work with this
	jgraphics_set_fill_rule(cr, JGRAPHICS_FILL_RULE_EVEN_ODD);
	jgraphics_arc(cr, width*.5, height*.5, width*.5, 0, JGRAPHICS_2PI);
	jgraphics_arc(cr, width*.5, height*.5, width*.25, 0, JGRAPHICS_2PI);
	jgraphics_close_path(cr);
#elif 0
	// Or, setting the winding to even/odd seems to work with this
	jgraphics_set_fill_rule(cr, JGRAPHICS_FILL_RULE_EVEN_ODD);
	jgraphics_ovalarc(cr, width*.5, height*.5, width*.5, height*.5, 0, JGRAPHICS_2PI);
	jgraphics_arc(cr, width*.666, height*.6, width*.25, 0, JGRAPHICS_2PI);
	jgraphics_close_path(cr);
#elif 0
	// Ah, but this works too, and is much simpler.  The key is the EVEN_ODD winding rule.
	jgraphics_set_fill_rule(cr, JGRAPHICS_FILL_RULE_EVEN_ODD);
	jgraphics_rectangle(cr, 0, 0, width, height);
	jgraphics_rectangle(cr, width*.25, height*.25, width*.5, height*.5);
#elif 0
	jgraphics_set_fill_rule(cr, JGRAPHICS_FILL_RULE_EVEN_ODD);
	jgraphics_ellipse(cr, 0, 0, width, height);
	jgraphics_ellipse(cr, width*.25, height*.5, height*.4, height*.4);
#else	//  this demonstrates it better
	jgraphics_set_fill_rule(cr, JGRAPHICS_FILL_RULE_EVEN_ODD);
	jgraphics_rectangle(cr, 0., 0., 100., 100.);
	jgraphics_rectangle(cr, width-100., height-100., 100., 100.);
#endif
	jgraphics_fill(cr);
}

void uitester_fill_path_with_surface(t_jgraphics *g, double width, double height)
{
	t_jgraphics *gs;
	t_jsurface *s;
	double i,ratio,r2,r3,inc;
	double pixels = 5;
	double y=0;

	s = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, width, height);
	gs = jgraphics_create(s);

	jgraphics_scale(gs,width,width);
	inc = pixels / width;
	jgraphics_set_line_width(gs, inc);
	i = 0.;
	ratio = height / width;
	r2 = ratio * 2;
	r3 = (width / height) * 2;
	if (r3 > r2)
		r2 = r3;
	while (i < r2) {
		jgraphics_move_to(gs,i,y);
		jgraphics_rel_line_to(gs, -ratio, ratio);

		jgraphics_stroke(gs);
		i += (inc * 2.5);
	}

	jgraphics_set_source_surface(g, s, 0, 0);
	jgraphics_rectangle_rounded(g, 0, 0, width, height, width, height);
	jgraphics_fill_preserve(g);
	jgraphics_set_source_rgba(g, 0, 0, 0, 1.);
	jgraphics_set_line_width(g, 2.);
	jgraphics_stroke(g);

	jgraphics_destroy(gs);
	jgraphics_surface_destroy(s);
}

void uitester_antialiased_lines(t_jgraphics *g, double width, double height)
{
	// snippet_normalize(g, width, height);
	jgraphics_set_source_rgb(g, 0, 0, 0);
	jgraphics_set_line_width(g, 1.);
	jgraphics_move_to(g, width * .5 + .5, 0);
	jgraphics_line_to(g, width * .5 + .5, height);
	jgraphics_stroke(g);
	jgraphics_move_to(g, width * .5 + 10, 0);
	jgraphics_line_to(g, width * .5 + 10, height);
	jgraphics_stroke(g);
	jgraphics_move_to(g, width * .5 + 10, 0);
	jgraphics_line_to(g, width * .5 + 100, height);
	jgraphics_stroke(g);
	jgraphics_move_to(g, width * .5 - .5 - 10, 0);
	jgraphics_line_to(g, width * .5 - .5 - 100, height);
	jgraphics_stroke(g);
}

void uitester_image_surface_draw(t_jgraphics *g, double width, double height)
{
	t_jsurface	*surf;
	t_jgraphics	*og;
	t_rect		srcRect;
	t_rect		destRect;
	int			i,j;

	surf = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, 256, 256);
	og = jgraphics_create(surf);

	for (i=0; i<256; i++) {
		for (j=0; j<256; j++) {
			t_jrgba myjrgba;
			myjrgba.red = myjrgba.green = 0.1;
			myjrgba.blue = myjrgba.alpha = 1.;

			jgraphics_image_surface_set_pixel(surf, j, i, myjrgba);
		}
	}

	jgraphics_destroy(og);

	srcRect.x = destRect.x = srcRect.y = destRect.y = 0;
	srcRect.width = srcRect.height = 256;
	destRect.width = width;
	destRect.height = height;
	jgraphics_image_surface_draw(g, surf, srcRect, destRect);
}

void uitester_textlayout(t_jgraphics *g, double width, double height)
{
	t_jtextlayout	*mytxt;
	t_jfont	*myfont;
	t_jrgba rgba;

	const char *text = "testing the textlayout stuff";
	double boxwidth = width / 3.;
	double boxheight = height / 3.;

	double xpos[9] = { 0., 0., 0., 1./3., 1./3., 1./3., 2./3., 2./3., 2./3. };
	double ypos[9] = { 0., 1./3., 2./3., 0., 1./3., 2./3., 0., 1./3., 2./3. };
	int i;

	t_jgraphics_text_justification justification[9] =
	{
		(t_jgraphics_text_justification) (JGRAPHICS_TEXT_JUSTIFICATION_LEFT | JGRAPHICS_TEXT_JUSTIFICATION_TOP),
		(t_jgraphics_text_justification) (JGRAPHICS_TEXT_JUSTIFICATION_LEFT | JGRAPHICS_TEXT_JUSTIFICATION_VCENTERED),
		(t_jgraphics_text_justification) (JGRAPHICS_TEXT_JUSTIFICATION_LEFT | JGRAPHICS_TEXT_JUSTIFICATION_BOTTOM),
		(t_jgraphics_text_justification) (JGRAPHICS_TEXT_JUSTIFICATION_HCENTERED | JGRAPHICS_TEXT_JUSTIFICATION_TOP),
		(t_jgraphics_text_justification) (JGRAPHICS_TEXT_JUSTIFICATION_HCENTERED | JGRAPHICS_TEXT_JUSTIFICATION_VCENTERED),
		(t_jgraphics_text_justification) (JGRAPHICS_TEXT_JUSTIFICATION_HCENTERED | JGRAPHICS_TEXT_JUSTIFICATION_BOTTOM),
		(t_jgraphics_text_justification) (JGRAPHICS_TEXT_JUSTIFICATION_RIGHT | JGRAPHICS_TEXT_JUSTIFICATION_TOP),
		(t_jgraphics_text_justification) (JGRAPHICS_TEXT_JUSTIFICATION_RIGHT | JGRAPHICS_TEXT_JUSTIFICATION_VCENTERED),
		(t_jgraphics_text_justification) (JGRAPHICS_TEXT_JUSTIFICATION_RIGHT | JGRAPHICS_TEXT_JUSTIFICATION_BOTTOM)
	};

	t_jgraphics_textlayout_flags flags = (t_jgraphics_textlayout_flags) (0);

	mytxt = jtextlayout_create();
	myfont = jfont_create("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, 16.);

	for (i=0; i < 9; i++)
	{
		jtextlayout_set(mytxt, text, myfont, xpos[i] * width, ypos[i] * height, boxwidth, boxheight, justification[i], flags);
		rgba.red = 0.;
		rgba.green = 0.;
		rgba.blue = 0.;
		rgba.alpha = 1.;

		jgraphics_rectangle(g, xpos[i] * width, ypos[i] * height, boxwidth, boxheight);
		jgraphics_set_source_rgb(g, 0., 0., 0.);
		jgraphics_stroke(g);

		jtextlayout_settextcolor(mytxt, &rgba);
		jtextlayout_draw(mytxt, g);
	}

	jtextlayout_destroy(mytxt);
	jfont_destroy(myfont);
}

void uitester_scroll(t_jgraphics *g, double width, double height)
{
	static t_jsurface *surf = NULL,*surf2;
	t_jgraphics *og;
	static long begin = 1;
	static long count = 0;
	t_rect src, dst;

	if (!surf) {
		surf = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, width, height);
		surf2 = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, width, height);
	}
	og = jgraphics_create(surf);
	jgraphics_set_source_rgba(og,0.7,0.7,0.7,1.);
	if (begin) {
		begin = 0;
		jgraphics_rectangle_fill_fast(og,0,0,width,height);
	}
	jgraphics_image_surface_scroll(surf,0, 0, width, height, 1, 0, NULL);

	jgraphics_set_source_rgba(og, 0.9, 0.9, 0.9, 1.);
	jgraphics_rectangle_fill_fast(og, 0, 0, 1, height);
	jgraphics_set_source_rgba(og, 0.3, 0.3, 0.3, 1.);
	jgraphics_rectangle_fill_fast(og, 0, count++, 1, 1);

	src.x = src.y = 0;
	src.width = width;
	src.height = height;
	dst = src;
	jgraphics_image_surface_draw(g, surf, src, dst);
	jgraphics_destroy(og);
}

void uitester_showtext(t_jgraphics *g, double width, double height)
{
	jgraphics_set_source_rgb(g, 0.7, 0.7, 0.7);
	jgraphics_set_line_width(g, 2.0);
	jgraphics_move_to(g, 5.0, 13.0);
	jgraphics_select_font_face(g, "Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_BOLD);
	jgraphics_set_font_size(g, 8.0);
	jgraphics_show_text(g, "f");
}

void uitester_strokeroundedrect(t_jgraphics *g, double width, double height)
{
	const int roundedness = 10;
	const int linewidth = 50;

	jgraphics_set_source_rgb(g, 0., 0., 0.);
	jgraphics_rectangle_rounded(g, linewidth, linewidth, width - linewidth*2, height - linewidth*2, roundedness, roundedness);
	jgraphics_set_line_width(g, linewidth);
	jgraphics_stroke(g);
}

void uitester_textlayouttransformed(t_jgraphics *g, double width, double height)
{
	t_jtextlayout	*mytxt;
	t_jfont	*myfont;
	t_jrgba rgba;

	const char *text = "herding cats";
	double boxwidth = width;
	double boxheight = height / 2.;
	t_jgraphics_text_justification justification =  JGRAPHICS_TEXT_JUSTIFICATION_CENTERED;
	mytxt = jtextlayout_create();
	myfont = jfont_create("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, 16.);

	jtextlayout_set(mytxt, text, myfont, 0, 0, boxwidth, boxheight, justification, (t_jgraphics_textlayout_flags) 0);
	rgba.red = 0.;
	rgba.green = 0.;
	rgba.blue = 0.;
	rgba.alpha = 1.;

	jtextlayout_settextcolor(mytxt, &rgba);
	jtextlayout_draw(mytxt, g);

	//jgraphics_scale(g, 0, boxheight);
	jgraphics_translate(g, 0, boxheight);
	jtextlayout_draw(mytxt, g);

	jtextlayout_destroy(mytxt);
	jfont_destroy(myfont);
}
