/**
	@page chapter_ui_anatomy Anatomy of a UI Object

	Max user interface objects are more complex than normal non-user-interface objects. If you have nothing in particular to display, or do not need to create a unique interface for user interaction or editing, it would be better to avoid writing one. However, if you want the details, we have them for you!

	In order to create a user interface object, you'll need to be familiar with @ref attr, as they are used extensively. If you examine a toggle object in the inspector in Max, you will see a few attributes that have been defined as belonging to the toggle class, namely:

	- Background Color
	- Check Color
	- Border Color

	We'll show how attributes are defined and described so that the inspector can edit them properly.

	In addition to attributes, user interface objects draw in a box and respond to user events such as mouse clicks and keyboard events. We'll show how to implement drawing an object's paint method as well user interaction in the mousedown, mousedrag, and mouseup methods.

	This chapter only covers basic drawing of lines and filled rectangles. But you can take advantage of a complete graphics API called jgraphics, intended to be used in a user interface object's paint method. We discuss @ref jgraphics in more detail in a separate chapter. You may also find the jgraphics.h header file descriptions of the set of functions helpful.

	The SDK examples contain two user interface projects -- the one we'll discuss in this chapter is called <i>uisimp</i> and is a version of the toggle object with a more complicated check box and user interaction. The second project is called <a href="pictmeter~_8c-source.html">pictmeter~</a>, a more advanced object that uses audio as well as image files.

	The uisimp object differs from the toggle object in a couple of ways:

	- it tracks the mouse even when it isn't down and "looks excited" when the mouse passes over it
	- it tracks the mouse while the user is holding the mouse down to show a sort of "depressed" appearance when turning the toggle on
	- the new toggle state value is sent out when the mouse is released rather than when the mouse is down. In addition, the uisimp object tracks the mouse and does not change the state if the mouse is released outside of the object's box
	- it doesn't have rounded corners
	- it has a solid square for a "checked state" instead of an X

	Otherwise, it acts largely as the toggle does.

	The first thing we suggest you do is build the uisimp object and test it out. Once the object is properly building, type "uisimp" into an object box and you can try it out.


	@section chapter_ui_anatomy_headers Required Headers

	UI objects require that you include two header files, jpatcher_api.h and jgraphics.h:

@code
	#include "jpatcher_api.h"
	#include "jgraphics.h"
@endcode

	The header file jpatcher_api.h includes data structures and accessor functions required by UI objects. The header file jgraphics.h includes data structures and functions for drawing.


	@section chapter_ui_anatomy_struct UI Object Data Structure

	The first part of a UI object is a #t_jbox, not a #t_object. You should generally avoid direct access to fields of a #t_jbox, particularly when changing values, and use the accessor functions defined in jpatcher_api.h. For example, if you change the rectangle of a box without using the accessor function jbox_set_rect(), the patcher will not be notified properly and the screen will not update.

	Following the #t_jbox, you can add other fields for storing the internal state of your object. In particular, if you are going to be drawing something using color, you will want to create attributes that reference fields holding colors in your object. We'll show you how to do this below. Here is the declaration of the t_uisimp data structure.

@code
	typedef struct _uisimp
	{
		t_jbox u_box;						// header for UI objects
		void *u_out;						// outlet pointer
		long u_state;						// state (1 or 0)
		char u_mouseover;					// is mouse over the object
		char u_mousedowninside;				// is mouse down within the object
		char u_trackmouse;					// if non-zero, track mouse when button not down
		t_jrgba u_outline;					// outline color
		t_jrgba u_check;					// check (square) color
		t_jrgba u_background;				// background color
		t_jrgba u_hilite;					// highlight color (when mouse is over and when clicking to check box)
	} t_uisimp;
@endcode

	The #t_jrgba structure defines a color with four doubles for red, green, blue, and alpha. Each component ranges from 0-1. When red, green, and blue are all 0, the color is black; when red, green, and blue are 1, the color is white. By defining color attributes using #t_jrgba structures, you will permit the user to use the standard color picker from the inspector to configure colors for your object.

	The structure members u_mouseover and u_mousedowninside are used to signal the code that paints the toggle from the code that handles mouse interaction. We'll discuss this more in the "interaction strategy" section below.


	@section chapter_ui_anatomy_init Initialization Routine for UI Objects

	Once you've declared your object's struct, you'll write your initialization ( ext_main() ) routine to set up the class, declaring methods and attributes used by UI objects.

	The first addition to the class initialization of a normal Max object you need to make is a call to jbox_initclass(). This adds standard methods and attributes common to all UI objects. Here's how you should to it:

@code
	c = class_new("uisimp", (method)uisimp_new, (method)uisimp_free, sizeof(t_uisimp), 0L, A_GIMME, 0);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_FIXWIDTH | JBOX_COLOR);
@endcode

	The line c->c_flags |= #CLASS_FLAG_NEWDICTIONARY is required, but the flags passed to jbox_initclass -- #JBOX_FIXWIDTH and #JBOX_COLOR -- are optional. #JBOX_FIXWIDTH means that when your object is selected in a patcher, the Fix Width menu item will be enabled to resize your object to its class's default dimensions. We'll specify the default dimensions in a moment. #JBOX_COLOR means that your object will be given a color attribute so that it can be edited with the color picked shown by the Color... menu item. This is a way to edit a "basic" color of your object without opening the inspector. If neither of these behaviors apply to your object, feel free to pass 0 for the flags argument to jbox_initclass().


	@section chapter_ui_anatomy_methods UI Object Methods

	Next we need to bind a few standard methods. The only required method for UI objects is paint, which draws the your object's content when its box is visible and needs to be redrawn.

@code
	class_addmethod(c, (method)uisimp_paint,		"paint",	A_CANT, 0);
@endcode

	We'll discuss the paint method in detail below. It makes use of the @ref jgraphics API, which is described in more detail in its own chapter.

	Our uisimp toggle will respond to mouse gestures, so we will define a set of mouse handling methods.

@code
	class_addmethod(c, (method)uisimp_mousedown,	"mousedown",	A_CANT, 0);
	class_addmethod(c, (method)uisimp_mousedrag,	"mousedrag",	A_CANT, 0);
	class_addmethod(c, (method)uisimp_mouseup,		"mouseup",		A_CANT, 0);
	class_addmethod(c, (method)uisimp_mouseenter,	"mouseenter",	A_CANT, 0);
	class_addmethod(c, (method)uisimp_mouseleave,	"mouseleave",	A_CANT, 0);
	class_addmethod(c, (method)uisimp_mousemove,	"mousemove",	A_CANT, 0);
	class_addmethod(c, (method)uisimp_mousewheel,	"mousewheel",	A_CANT, 0);
@endcode

	mousedown is sent to your object when the user clicks on your object -- in other words, when the mouse is moved over the object and the primary mouse button is depressed. mousedrag is sent after an initial mousedown when the mouse moves and the button is still held down from the click. mouseup is sent when the mouse button is released after a mousedown is sent. mouseenter is sent when the mouse button is not down and the mouse moves into your object's box. mousemove is sent -- after a mouseenter -- when the mouse button is not down but the mouse position changes inside your object's box. mouseleave is sent when the mouse button is not down and the mouse position moves from being over your object's box to being outside of it.  mousewheel is sent when information about the scrollwheel on the mouse (or scrolling from another source such as a trackpad) is transmitted while the cursor is hovering over your object.

	You are not obligated to respond to any of these messages. You could, for example, only respond to mousedown and ignore the other messages.

	It might be helpful to summarize mouse messages in the following "rules" (although normally it's not necessary to think about them explicitly):

	- mousedown will always be followed by mouseup, but not necessarily by mousedrag if the button press is rapid and there is no movement while the mouse button is pressed.
	- mouseenter will always be followed by mouseleave, but
	- mouseenter will always precede mousemove
	- mouseleave will be sent only after a mouseenter is sent
	- You cannot count on any particular relationship between the mousedown / mousedrag / mouseup sequence and the mouseenter / mousemove / mouseleave sequence.

	We'll look at the actual implementation of mouse handling methods below.


	@section chapter_ui_anatomy_attributes Defining Attributes

	After the declaration of standard methods, your object will define its own attributes. By using what we call "attribute attributes" you can further describe attributes so that they can be appropriately displayed and edited in the inspector as well as saved in a patcher (or not). You can also set default values for attributes that are automatically copied to your object when it is instantiated, and mark an attribute so that your object is redrawn when its value changes.

	As a convenience, we've defined a series of macros in ext_obex_util.h (which is included when your object includes ext_obex.h) that reduce the amount of typing needed to define attributes and attribute attributes.

	Most UI object attributes are offset attributes; that is, they reference a location in your object's data structure by offset and size. As an example, uisimp has a char offset attribute called trackmouse that specifies whether the object will change the object's appearance when the mouse moves over it. Here's how this is defined:

@code
	CLASS_ATTR_CHAR(c, "trackmouse", 0, t_uisimp, u_trackmouse);
	CLASS_ATTR_STYLE_LABEL(c, "trackmouse", 0, "onoff", "Track Mouse");
	CLASS_ATTR_SAVE(c, "trackmouse", 0);
@endcode

	The first line, #CLASS_ATTR_CHAR, defines a char-sized offset attribute. If you look at the declaration of t_uisimp, you can see that the u_trackmouse field is declared to be a char. The #CLASS_ATTR_CHAR macro take five arguments.

	- The first argument is the class for which the attribute is being declared.
	- The second argument is the name of the attribute. You can use send a message to your object with this name and a value and set the attribute.
	- The third argument is a collection of attribute flags. For the attributes (and attribute attributes) we'll be defining in the uisimp object, the flags will be 0, but you can use them to make attributes read-only with #ATTR_SET_OPAQUE_USER.
	- The fourth argument is the name of your object's structure containing the field you want to use for the attribute
	- The fifth argument is the field name you want to use for the attribute

	The fourth and fifth arguments are used to calculate the offset of the beginning of the field from the beginning of the structure. This allows the attribute to read and write the memory occupied by the field directly.

	The second line, #CLASS_ATTR_STYLE_LABEL, defines some attribute attributes for the trackmouse attribute. THis macro takes five arguments as well:

	- The first argument is the class for which the attribute attributes are being declared.
	- The second argument is the name of the attribute, which should have already been defined by a #CLASS_ATTR_CHAR or similar attribute declaration
	- The third argument is usually 0 -- it is an attribute flags argument for the attribute attributes
	- The fourth argument is the style of the attribute. "onoff" is used here for a setting in your object that will be a toggle. By using the onoff style the trackmouse attribute will appear with a checkbox in the inspector window. Effectively, this macro defines an attribute called "style" that is attached to the "trackmouse" attribute and set its value to the symbol "onoff" in one step.
	- The fifth argument is a string used as a descriptive label for the attribute that appears in the inspector and other places in the Max user interface. If you don't supply a label, the attribute name will be shown. The string is used as the value of a newly created "label" attribute attribute.

	The category attribute attribute is used to organize your object's attributes in the inspector window. For the trackmouse attribute, we use the "Behavior" category, and for the color attributes discussed below, we use "Color" -- look at the inspector category tabs for a few UI objects that come with Max for suggested standard category names. You're free to create your own.

	To define a category for a single attribute, you can use the #CLASS_ATTR_CATEGORY macro:

@code
	CLASS_ATTR_CATEGORY(c, "trackmouse", 0, "Behavior");
@endcode

	To define a category for a series of attributes, you can use #CLASS_STICKY_ATTR, which applies the current value of a specified attribute attribute to any attributes subsequently defined, until a #CLASS_STICKY_ATTR_CLEAR is set for an attribute attribute name. #CLASS_STICKY_ATTR is used in uisimp to apply the "Color" category to a set of three color attributes.

@code
	CLASS_STICKY_ATTR(c, "category", 0, "Color");
@endcode

	Color attributes are defined using #CLASS_ATTR_RGBA. The uisimp object defines four color attributes. Here is the first, called bgcolor:

@code
	CLASS_ATTR_RGBA(c, "bgcolor", 0, t_uisimp, u_background);
	CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c, "bgcolor", 0, "1. 1. 1. 1.");
	CLASS_ATTR_STYLE_LABEL(c,"bgcolor",0,"rgba","Background Color");
@endcode

	The difference between #CLASS_ATTR_RGBA and #CLASS_ATTR_CHAR for defining an attribute is that #CLASS_ATTR_RGBA expects the name of a structure member declared of type #t_jrgba rather than type char. When set, the attribute will assign values to the four doubles that make up the components of the color.

	The next line uses the #CLASS_ATTR_DEFAULTNAME_SAVE_PAINT macro. This sets three things about the bgcolor attribute. First it says that the color attribute bgcolor can be assigned a default value via the object defaults window. So, if you don't like the standard white defined by the object, you can assign you own color for the background color of all newly created uisimp objects. The four values 1 1 1 1 supplied as the last argument to #CLASS_ATTR_DEFAULTNAME_SAVE_PAINT specify the "standard" default value that will be used for the bgcolor attribute in the absence of any overrides from the user.

	The SAVE aspect of this macro specifies that this attribute's values should be saved with the object in a patcher. A patcher file saves an object's class, location and connections, but it can also save the object's appearance or any other attribute value you specify, by using the "save" attribute attribute.

	The PAINT aspect of this macro provides the ability to have your object redrawn whenever this attribute (bgcolor) changes. However, to implement auto-repainting on attribute changes, you'll need to add the following code when initializing your class:

@code
	class_addmethod(c, (method)jbox_notify, "notify", A_CANT, 0);
@endcode

	The function jbox_notify() will determine whether an attribute that has caused a change notification to be sent has its paint attribute attribute set, and if so, will call jbox_redraw(). If you write your own notify method because you want to respond to changes in attributes or other environment changes, you *must* call jbox_notify() inside of it.

	@subsection chapter_ui_anatomy_attributes_color Standard Color Attribute

	At the beginning of our initialization routine, we passed #JBOX_COLOR as a flag to jbox_initclass(). This adds an attribute to our object called color, which uses storage provided in the #t_jbox to keep track of a color for us. The color attribute is a standard name for the "most basic" color your object uses, and if you define it, the Color menu item in the Object menu will be enabled when your object is selected, permitting the user to change the color without opening the inspector.

	If you use #JBOX_COLOR, you don't need to define the color attribute using #CLASS_ATTR_RGBA -- jbox_initclass() will do it for you. However, the color attribute comes unadorned, so you are free to enhance it with attribute attributes. Here's what uisimp does:

@code
	CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c, "color", 0, "0. 0. 0. 1.");
	CLASS_ATTR_STYLE_LABEL(c,"color",0,"rgba","Check Color");
@endcode


	@subsection chapter_ui_anatomy_attributes_size Setting a Default Size

	Another attribute defined for your object by jbox_initclass() is called patching_rect. It holds the dimensions of your object's box. If you want to set a standard size for new instances of your object, you can give the patching_rect a set of default values. Use 0 0 for the first two values (x and y position) and use the next two values to define the width and height. We want a small square to be the default size for uisimp, so we use #CLASS_ATTR_DEFAULT to assign a default value to the patching_rect attribute as follows:

@code
	CLASS_ATTR_DEFAULT(c,"patching_rect",0, "0. 0. 20. 20.");
@endcode



	@section chapter_ui_anatomy_new New Instance Routine

	The UI object new instance routine is more complicated than that of a normal Max object. Each UI object is passed a #t_dictionary (a hierarchically structured collection of data accessed by symbolic names) containing the information needed to instantiate an instance. For UI objects, data elements in the dictionary correspond to attribute values. For example, if your object saved an attribute called "bgcolor" you will be able to access the saved value in your new instance routine from the dictionary using the same name bgcolor.

	If the instance is being created from the object palette or by the typing the name of your object into an object box, the dictionary will be filled in with default values. If the object is being created by reading a patcher file, the dictionary will be filled in with the saved attributes stored in the file. In most cases, you don't need to work with the dictionary directly, unless you've added proprietary non-attribute information to your object's dictionary that you want to look for and extract. However, you do need to pass the dictionary to some standard routines, and initialize everything in the right order.

	Let's take a look at the pattern you should follow for your object's new instance routine.

	First, the new instance routine is declared as follows:

@code
	void *uisimp_new(t_symbol *s, long argc, t_atom *argv);
@endcode

	We will get the dictionary that defines the object out of the arguments passed in argc, argv. (The symbol argument s is the name of the object.) If obtaining the dictionary fails, we should return NULL to indicate we didn't make an instance.

@code
	void *uisimp_new(t_symbol *s, long argc, t_atom *argv);
	{
		t_uisimp *x = NULL;
	 	t_dictionary *d = NULL;
		long boxflags;

		if (!(d = object_dictionaryarg(argc,argv)))
			return NULL;
@endcode

	Next, we allocate a new instance of the object's class:

@code
	x = (t_uisimp *)object_alloc(s_uisimp_class);
@endcode

	Then we need to initialize the options for our box. Our object uses the options that are not commented out.

@code
	boxflags = 0
			| JBOX_DRAWFIRSTIN
			| JBOX_NODRAWBOX
			| JBOX_DRAWINLAST
			| JBOX_TRANSPARENT
	//		| JBOX_NOGROW
			| JBOX_GROWY
	//		| JBOX_GROWBOTH
	//		| JBOX_HILITE
	//		| JBOX_BACKGROUND
			| JBOX_DRAWBACKGROUND
	//		| JBOX_NOFLOATINSPECTOR
	//		| JBOX_MOUSEDRAGDELTA
	//		| JBOX_TEXTFIELD
			;
@endcode

	Here is some more detail about each of the box flags.

	We pass the flags along with a pointer to our newly created instance and the argc, argv arguments to jbox_new(). The name is a little misleading. jbox_new() does not instantiate your box. As we explained above, your UI object has a #t_jbox at the beginning. jbox_new() just initializes the #t_jbox for you. jbox_new() doesn't know about the other stuff in your object's data structure that comes after the #t_jbox. You'll have to initialize the extra items yourself.

@code
	jbox_new((t_jbox *)x, boxflags, argc, argv);
@endcode

	Once jbox_new() has been called, you then assign the b_firstin pointer of your #t_jbox header to point to your object. Essentially this assigns the object that will receive messages from objects connected to your leftmost inlet (as well as other inlets via inlets or proxies you create). This step is easily forgotten and will cause most things not to work until you remember it. jbox_new() will obtain the attributes common to all boxes such as the patching_rect, and assign them to your object for you.

@code
	x->u_box.b_firstin = (void *)x;
@endcode

	Next, you are free to initialize any members of your object's data structure, as well as declare inlets. These steps are the same for UI objects as for non-UI objects.

@code
	x->u_mousedowninside = x->u_mouseover = x->u_state = 0;
	x->u_out = intout((t_object *)x);
@endcode

	Once your object is in a safe initialized state, call attr_dictionary_process() if you've defined any attributes. This will find the attributes in the dictionary your object received, then set them to the values stored in the dictionary. There is no way to guarantee the order in which the attributes will be set. If this a problem, you can obtain the attribute values "by hand" and assign them to your object.

	Note that you do not need to call attr_dictionary_process() if you have not defined any attributes. jbox_new() will take care of setting all attributes common to all UI objects.

@code
		attr_dictionary_process(x,d);
@endcode

	As the last thing to do before returning your newly created UI object, and more specifically after you've initialized everything to finalize the appearance of your object, call jbox_ready(). jbox_ready() will paint your object, calculate the positions of the inlets and outlets, and perform other initialization tasks to ensure that your box is a proper member of the visible patcher.

	If your object does not appear when you instantiate it, you should check whether you do not have a jbox_ready() call.

@code
		jbox_ready((t_jbox *)x);
@endcode

	Finally, as with any instance creation routine, the newly created object will be returned.

@code
	return x;
@endcode


	@section chapter_ui_anatomy_updating Dynamic Updating

	Drawing anything to the screen must be limited to your paint method (this was not the case with the previous UI object API in Max). If you want to redraw something, you need to call jbox_redraw() to cause the screen to be redrawn. This is necessary because your object is part of a compositing user interface that must be managed by the patcher as a whole to avoid screen artifacts. The jbox_redraw() routine calculates the area of the screen that needs to be redrawn, then informs the Mac or Windows "window manager" to mark this area as invalid. At some later point in time, the OS will invoke the patcher's paint routine, which will dispatch to all of the boxes inside the invalid area according to the current Z-order of all the boxes. Boxes that are in the background are drawn first, so that any transparent or semi-transparent boxes can be drawn on top of them. In addition, unless you specify otherwise, the last drawn image of a box is cached in a buffer, so that your paint method will only be called when you explicitly invalidate your object's content with jbox_redraw(). In other words, you can't count on "global patcher drawing" to invoke your paint method.

	The basic strategy you'll want to use in thinking about redrawing is that you will set internal state in other methods, then call jbox_redraw(). The paint method will read the internal state and adjust its drawing appropriately. You'll see this strategy used in the uisimp object as it tracks the mouse.


	@section chapter_ui_anatomy_paint The Paint Method

	Your object's paint method uses the jgraphics API to draw. The header file, jgraphics.h, provides a description of each of the routines in the API. Here we will only discuss general principles and features of drawing with uisimp's relatively simple paint method. There is also a jgraphics example UI object that contains a number of functions showing how various drawing tasks can be performed.

	Drawing in Max is resolution-independent. The "size" of your object's rectangle is always the pixel size when the patcher is scaled to 100% regardless of the zoom level, and any magnification or size reduction to the actual screen is automatically handled by matrix transforms. Another thing that is handled automatically for you is drawing to multiple views. If a patcher is invisible (i.e., a subpatcher that has not been double-clicked), it does not have any views. But if it is visible, a patcher can have many patcherviews. If your UI object box is in a patcher with multiple views open, your paint method will be called once for each view, and will be passed different a patcherview object each time. For most objects, this will pose few problems, but for objects to work properly when there are anywhere from zero to ten views open, they cannot change their internal state in the paint method, they can only read it. As an example, if your object had a boolean "painted" field in its structure that would be set when the paint method had finished, it would not work properly in the cases where the box was invisible or where it was shown in multiple patcher views, because it would either be set zero or more than once.

	The first step for any paint method is to obtain the #t_jgraphics object from the patcherview object passed to the paint method. The patcherview is an opaque #t_object that you will use to access information about your box's rectangle and its graphics context. A patcherview is not the same thing as a patcher; as mentioned above, there could be more than one patcherview for a patcher if it has multiple views open.

@code
	void uisimp_paint(t_uisimp *x, t_object *patcherview)
	{
		t_rect rect;

		t_jgraphics *g = (t_jgraphics*) patcherview_get_jgraphics(patcherview);		// obtain graphics context
@endcode

	After obtaining the #t_jgraphics object, the next thing that you'll need to do is determine the rectangle of your box. A view of a patcher may be in either patching or presentation mode. Since each mode can have its own rectangle, it is necessary to use the patcherview to obtain the rectangle for your object.

@code
	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
@endcode

	The #t_rect structure specifies a rectangle using the x and y coordinates of the top left corner, along with the width and height. However, the coordinates of the #t_jgraphics you'll be using to draw into always begin at 0 for the top left corner, so you'll only care about the width and height, at least for drawing.

	The first thing we'll draw is just an outline of our box using the value of the outline color attribute. First we'll set the color we want to use, then make a rectangular path, then finally we'll stroke the path we've made.

	With calls such as jgraphics_rectangle(), the rectangular shape is added to the existing path. The initial path is empty, and after calling jgraphics_stroke() or jgraphics_fill(), the path is again cleared. (If you want to retain the path, you can use the jgraphics_stroke_preserve() and jgraphics_fill_preserve variants().)

@code
	jgraphics_set_source_jrgba(g, &x->u_outline);
	jgraphics_set_line_width(g, 1.);
	jgraphics_rectangle(g, 0., 0., rect.width, rect.height);
	jgraphics_stroke(g);
@endcode

	You do not need to destroy the path before your paint method is finished. This will be done for you, but the fact that the path does not survive after the paint method is finished means you can't make a path and then store it without copying it first. Such a strategy is not recommended in any case, since your object's rectangle might change unpredictably from one paint method invocation to the next, which will likely cause your path to be the wrong shape or size.

	The next feature of the paint method is to draw an inner outline if the mouse is moved over the box. Detecting the mouse's presence over the box happens in the mouseenter / mouseleave methods described below -- but essentially, we know that the mouse is over our object if the u_mouseover has been set by these mouse tracking methods.

	To draw a rectangle that is inset by one pixel from the box rectangle, we use the rectangle starting at 1, 1 with a width of the box width - 2 and a height of the box height - 2.

@code
	// paint "inner highlight" to indicate mouseover
	if (x->u_mouseover && !x->u_mousedowninside) {
		jgraphics_set_source_jrgba(g, &x->u_hilite);
		jgraphics_set_line_width(g, 1.);
		jgraphics_rectangle(g, 1., 1., rect.width - 2, rect.height - 2);
		jgraphics_stroke(g);
	}
@endcode

	Some similar code provides the ability to show the highlight color when the user is about to check (turn on) the toggle:

@code
	if (x->u_mousedowninside && !x->u_state) {		// paint hilite color
		jgraphics_set_source_jrgba(g, &x->u_hilite);
		jgraphics_rectangle(g, 1., 1., rect.width - 2, rect.height - 2);
		jgraphics_fill(g);
	}
@endcode

	Finally, we paint a square in the middle of the object if the toggle state is non-zero to indicate that the box has been checked. Here we are filling a path instead of stroking it. Note also that we use the call jbox_get_color() to get the "standard" color of our object that is stored inside the #t_jbox. As we've specified by using the #JBOX_COLOR flag for jbox_initclass() in our initialization routine, the color obtained by jbox_get_color() for the "check" (really just a square of solid color) is the one the user can change with the Color... item in the Object menu.

@code
	if (x->u_state) {
		t_jrgba col;

		jbox_get_color((t_object *)x, &col);
		jgraphics_set_source_jrgba(g, &col);
		if (x->u_mousedowninside)		// make rect bigger if mouse is down and we are unchecking
			jgraphics_rectangle(g, 3., 3., rect.width - 6, rect.height - 6);
		else
			jgraphics_rectangle(g, 4., 4., rect.width - 8, rect.height - 8);
		jgraphics_fill(g);
	}
@endcode

	Clearly, a quick perusal of the jgraphics.h header file will demonstrate that there is much more to drawing than we've discussed here. But the main purpose of the uisimp paint method is to show how to implement "dynamic" graphics that follow the mouse. Now we'll see the mouse tracking side of the story.



	@section chapter_ui_anatomy_mouse Handling Mouse Gestures

	When the mouse is clicked, dragged, released, or moved inside its box, your object will receive messages. In the uisimp example we've defined methods for most of the mouse gesture messages available, and we've implemented them to change internal state in the object, then call jbox_redraw() to repaint the object to reflect the new state. This strategy produces a "dynamic" appearance of a gadget users associate with a typical graphical interface -- in this case a toggle checkbox.

	All mouse gesture methods are declared in the same way:

@code
	void myobect_mouse(t_myobject *x, t_object *patcherview, t_pt pt, long modifiers);
@endcode

	Let's first look at the most commonly implemented mouse gesture handler, the mousedown method that responds to an initial click on the object. As you can see, it is very simple; it merely sets u_mousedowninside to true, then calls jbox_redraw(), causing the box to be repainted. We've defined this toggle not to change the actual state until the mouse is released (unlike the standard Max toggle object), but we do want to give the user some feedback on the initial mouse down that something is going to happen. If you look back at the paint method, you can see that u_mousedowninside is used to change the way the object is painted to give it a "pending state change" appearance that will be finalized when the mouse is released inside the box.

@code
	void uisimp_mousedown(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers)
	{
		x->u_mousedowninside = true;	// wouldn't get a click unless it was inside the box
		jbox_redraw((t_jbox *)x);
	}
@endcode


	If we test the mouse position to ensure that it is inside the box when it is released, we provide the opportunity for the user to cancel the act of toggling the state of the object by moving the cursor outside of the box before releasing the button. To provide feedback to the user that this is going to happen, we've implemented a mousedrag method that performs this test and redraws the object if the "mouse inside" condition has changed from its previous state. The mousedrag message will be sent to your object as long as the mouse button is still down after an initial click and the cursor has moved, even if the cursor moves outside of the boundaries of your object's box.

	Note that, as with the paint method, we use the patcherview to get the current box rectangle. We can then test the point we are given to see if it is inside or outside the box.

@code
	void uisimp_mousedrag(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers)
	{
		t_rect rect;

		// test to see if mouse is still inside the object
		jbox_get_rect_for_view((t_object *)x, patcherview, &rect);

		// redraw if changed
		if (pt.x >= 0 && pt.x <= rect.width && pt.y >= 0 && pt.y <= rect.height) {
			if (!x->u_mousedowninside) {
				x->u_mousedowninside = true;
				jbox_redraw((t_jbox *)x);
			}
		} else {
			if (x->u_mousedowninside) {
				x->u_mousedowninside = false;
				jbox_redraw((t_jbox *)x);
			}
		}
	}
@endcode


	Our mouseup method uses the last value of u_mousedowninside as the determining factor for whether to toggle the object's internal state. If u_mousedowninside is false, no state change happens. But if it is true, the state changes and the new state value is sent out the object's outlet (inside uisimp_bang()).

@code
	if (x->u_mousedowninside) {
		x->u_state = !x->u_state;
		uisimp_bang(x);
		x->u_mousedowninside = false;
		jbox_redraw((t_jbox *)x);
	}
@endcode

	Finally, we've implemented mouseenter, mousemove, and mouseleave methods to provide another level of "mouse over" style highlighting for the object. Rather than changing u_mousedowninside, a u_mouseover field is set when the mouseenter message is received, and cleared when the mouseleave method is received. And again, after this variable is manipulated, we repaint the box with jbox_redraw().

@code
	void uisimp_mouseenter(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers)
	{
		x->u_mouseover = true;
		jbox_redraw((t_jbox *)x);
	}

	void uisimp_mouseleave(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers)
	{
		x->u_mouseover = false;
		jbox_redraw((t_jbox *)x);
	}
@endcode


	@section chapter_ui_anatomy_freeing Freeing a UI Object

	If your object has created any clocks or otherwise allocated memory that should be freed when the object goes away, you should handle this in the free routine. But, most importantly, you must call the function jbox_free(). If your UI object doesn't need to do anything special in its free routine, you can pass jbox_free() as the free routine argument to class_new() in your initialization routine. We chose not to do this, since having an actual function permits easy modification should some memory need to be freed at some point in the future evolution of the object.

@code
	void uisimp_free(t_uisimp *x)
	{
		jbox_free((t_jbox *)x);
	}
@endcode


*/
