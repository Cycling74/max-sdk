/**
	@defgroup ui User Interface




	@defgroup jgraphics JGraphics
	@ingroup ui

	JGraphics is the API for creating user interface objects introduced with Max 5.

	It includes functions for drawing vector-based shapes, managing pop-up menus, rendering text, and importing graphics resources.  The API design is inspired by and analogous to the <a href="http://cairographics.org">Cairo</a> API, though the underlying implementation is actually drawn using <a href="http://rawmaterialsoftware.com/juce">JUCE</a> (JUCE functions, however, cannot be called directly).


	@defgroup jsurface JSurface
	@ingroup jgraphics

	A surface is an abstract base class for something you render to.
	An image surface is a concrete instance that renders to an image in memory, essentially an offscreen bitmap.



	@defgroup jsvg Scalable Vector Graphics
	@ingroup jgraphics


	@defgroup jfont JFont
	@ingroup jgraphics


	@defgroup jmatrix JGraphics Matrix Transformations
	@ingroup jgraphics

	The #t_jmatrix is one way to represent a transformation.
	You can use the #t_jmatrix in the call to jgraphics_transform(), jgraphics_setmatrix(), and jgraphics_pattern_set_matrix
	for specifying transformations.



	@defgroup jpattern JPattern
	@ingroup jgraphics

	A pattern is like a brush that is used to fill a path with.
	It could be a solid color but it could also be an image.
	You can draw to a surface and then from that surface create a pattern that can be used to fill another surface.
	For example, jgraphics_patter_create_for_surface().
	There are also gradients: see jgraphics_pattern_create_linear() and jgraphics_pattern_create_radial().



	@defgroup color Colors
	@ingroup jgraphics


	@defgroup styles Styles
	@ingroup jgraphics

	Styles provide a means by which to inherit attribute values from a patcher that are consistently used across many objects.



	@defgroup textfield TextField
	@ingroup jgraphics

	The textfield is a high-level text display object that may be used by a UI object to represent text in a patcher.
	It is built on the lower-level @ref textlayout


	@defgroup textlayout TextLayout
	@ingroup jgraphics

	A textlayout is lower-level text rendering object used by higher-level entities such as @ref textfield.


	@defgroup jpopupmenu Popup Menus
	@ingroup jgraphics

	Popup menu API so externals can create popup menus that can also be drawn into.


	@defgroup boxlayer Box Layer
	@ingroup jgraphics

	The boxlayer functions provide way to make it easier to use cached offscreen images (layers) in your drawing.
	The general idea is to do something like this:

	@code
	t_jgraphics *g;
	g = jbox_start_layer(box, view, layername, width, height);
	if (g) {
		// draw to your new offscreen context here
		// the second time you call jbox_start_layer() it will return NULL
		// since you already drew it -- you don't have to do drawing the second time
		jbox_end_layer(box, view, layername);
	}
	jbox_paint_layer(box, view, layername, xpos, ypos);
	@endcode

	Then, if something changes where you would need to redraw the layer you invalidate it:
	@code
	jbox_invalidate_layer(box, view, layername);
	@endcode
	or
	@code
	jbox_invalidate_layer(box, NULL, layername); // to invalidate for all views
	@endcode

	Each view has its own layer stored since if a patcher has multiple views each could be at a different zoom level.



	@defgroup jdataview DataView
	@ingroup ui

	The jdataview object provides a mechanism to display data in a tabular format.
	In Max this is used internally for the implementation of the inspectors, file browser, preferences, and jit.cellblock object, among others.

	A jdataview object does not contain the information that it presents.
	The object you create will maintain the data and then make the data available to the dataview using the provided api.

*/

