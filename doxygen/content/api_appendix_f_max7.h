/**
	@page chapter_appendix_f Appendix: SDK changes for Max 7


	@section chapter_appendix_f_main Using ext_main for Entry Point
	
	Prior to Max 7 the entry point for externals was the main() function exported from the dynamic library you create.
	Beginning with Max 7 the entry point for externals is called ext_main().
	This addresses compatibility problems with various newer compilers and frees us from the constraints enforced for main() as the standard entry point for programs.

	Objects that do no not define ext_main() will still be loaded using the older main().
	Support for ext_main() is also present in Max 6.1.9.


	@section chapter_appendix_f_styles Support for Max 7 UI Object Styles

	Max 7 introduces the concept of styles which determine the appearance of UI objects.
	For attributes of your UI object to map to colors or attributes of a style you need to add the required attribute properties in your class definition.
	
	See the section on @ref styles for more information.
**/
