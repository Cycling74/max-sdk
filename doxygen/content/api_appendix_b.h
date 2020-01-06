/**
	@page chapter_appendix_b Appendix: Providing Icons for UI Objects

	If you are writing user interface objects for Max, it is recommended that you provide an icon for your object.
	Providing an icon will allow users to create an instance of your class from the object palette, and improve the user's experience in other interactions with Max including the Object Defaults inspector.


	@section appendix_b_svg Object SVG Icon

	To see the icons provided by Cycling '74 for objects included in Max, look in the <b>Cycling '74/object-icons</b> folder installed by Max.
	You will find a variety of SVG (scalable vector graphics) files for the objects.
	The files are named with the same name of the class (as it is defined in your <code>ext_main()</code> function) with which they are associated.

	<em>
		SVG files can be edited in a variety of software applications such as InkScape or Adobe Illustrator.
		You can also export SVG files from OmniGraffle on the Mac, which is how the Max's object icons were created.
	</em>

	It is recommended that you distribute your object as a Max Package (see @ref chapter_appendix_f).
	Within this package you shoulo place your svg in the 'interfaces' folder.


	@section appendix_b_icon Quick Lookup Definition

	Adding the svg file will make the icon available to Max for use in some ways.
	To make your icon appear in Max's Object Explorer, however, you must create a quick-lookup (or qlookup) entry for your object.
	If you look in the <b>Cycling '74/interfaces</b> folder,
	you should notice some files with names like "obj-qlookup.json" and "doc-qlookup.json".
	For your object, you should create a similar qlookup file.

	For the following example we will assume you have created an object called 'littleuifoo'.
	For this object we will create a qlookup called 'littleuifoo-obj-qlookup.json'.
	The contents of this file will look like this:

<pre>
{
  "littleuifoo": {
    "digest": "Little UI Object that does Foo",
    "module": "max",
    "category": [
      "U/I"
    ],
    "palette": {
      "category": [
        "Interface"
      ],
      "action": "littleuifoo",
      "pic": "littleuifoo.svg"
    }
  }
}
</pre>

*/
