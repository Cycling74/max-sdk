/**
	@page chapter_appendix_a Appendix: Messages sent to Objects

	When writing objects for Max, you typically think of creating methods which are called when a message is sent to your object through the object's inlet.
	However, your object may receive messages directly from Max rather than using the inlet.

	One common example is the "assist" message, which is sent to your object when a user's mouse cursor hovers over one of your object's inlets or outlets.
	If your object binds a method to the "assist" message then you will be able to customize the message that is shown.

	This appendix serves as a quick reference for messages that are commonly sent to objects by Max, should they be implemented by the given object.
	Where possible, the prototypes given are actual prototypes from example objects in the SDK rather than abstractions to assist in finding the context for these calls.



	@section appendix_a_all Messages for All Objects

	<table>
		<tr><td>acceptsdrag_locked		</td><td>long pictmeter_acceptsdrag_unlocked(t_pictmeter *x, t_object *drag, t_object *view);</td><td></td></tr>
		<tr><td>acceptsdrag_unlocked	</td><td>long pictmeter_acceptsdrag_unlocked(t_pictmeter *x, t_object *drag, t_object *view);</td><td></td></tr>
		<tr><td>assist					</td><td>void pictmeter_assist(t_pictmeter *x, void *b, long m, long a, char *s);</td><td></td></tr>
		<tr><td>dumpout					</td><td>																	</td><td>bind this message to object_obex_dumpout() rather than defining your own method.</td></tr>
		<tr><td>inletinfo				</td><td>void my_obj(t_object *x, void *b, long a, char *t)					</td><td>you may bind to stdinletinfo() or define your own inletinfo method. <br><br>
																															The 'b' parameter can be ignored, the 'a' parameter is the inlet number,
																															and 1 or 0 should set the value of '*t' upon return.</td></tr>
		<tr><td>notify					</td><td>t_max_err dbviewer_notify(t_dbviewer *x, t_symbol *s, t_symbol *msg, void *sender, void *data);</td><td></td></tr>
		<tr><td>stdargs					</td><td>t_max_err my_obj(t_dictionary *d, t_symbol *s, long argc, t_atom *argv)</td><td>when loading an old (Max 3 or 4) patcher, this will be called prior to your new method.
																															You can then fill in the dictionary with key/value pairs from your previous args.</td></tr>
		<tr><td>quickref				</td><td> 																	</td><td>obsolete, this is provided automatically now</td></tr>
	</table>


	@section appendix_a_nonui Messages for Non-UI Objects

	<table>
		<tr><td>dblclick					</td><td>void scripto_dblclick(t_scripto *x);</td><td></td></tr>
	</table>



	@section appendix_a_ui Messages for User Interface Objects

	<table>
		<tr><td>getdrawparams				</td><td>void uisimp_getdrawparams(t_uisimp *x, t_object *patcherview, t_jboxdrawparams *params);</td><td></td></tr>
		<tr><td>mousedown					</td><td>void scripto_ui_mousedown(t_scripto_ui *x, t_object *patcherview, t_pt pt, long modifiers);</td><td></td></tr>
		<tr><td>mouseup						</td><td>void uisimp_mouseup(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers);</td><td></td></tr>
		<tr><td>mousedrag					</td><td>void scripto_ui_mousedrag(t_scripto_ui *x, t_object *patcherview, t_pt pt, long modifiers);</td><td></td></tr>
		<tr><td>mouseenter					</td><td>void uisimp_mouseenter(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers);</td><td></td></tr>
		<tr><td>mouseleave					</td><td>void uisimp_mouseleave(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers);</td><td></td></tr>
		<tr><td>mousemove					</td><td>void uisimp_mousemove(t_uisimp *x, t_object *patcherview, t_pt pt, long modifiers);</td><td></td></tr>
		<tr><td>paint						</td><td>void pictmeter_paint(t_pictmeter *x, t_object *patcherview);</td><td></td></tr>
	</table>



	@section appendix_a_audio Message for Audio Objects

	<table>
		<tr><td>dsp							</td><td>void plus_dsp(t_plus *x, t_signal **sp, short *count);</td><td></td></tr>
		<tr><td>dspstate					</td><td>plus_dspstate(t_plus *x, long n);</td><td></td></tr>
	</table>



	@section appendix_a_textedit Messages for Objects Containing Text Fields

	<table>
		<tr><td>key							</td><td>long uitextfield_key(t_uitextfield *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);</td><td></td></tr>
		<tr><td>keyfilter					</td><td>long uitextfield_keyfilter(t_uitextfield *x, t_object *patcherview, long *keycode, long *modifiers, long *textcharacter);</td><td></td></tr>
		<tr><td>enter						</td><td>void uitextfield_enter(t_uitextfield *x);</td><td></td></tr>
		<tr><td>select						</td><td>void uitextfield_select(t_uitextfield *x);</td><td></td></tr>
	</table>



	@section appendix_a_ed Messages for Objects with Text Editor Windows

	<table>
		<tr><td>edclose						</td><td>void simpletext_edclose(t_simpletext *x, char **text, long size);</td><td></td></tr>
	</table>



	@section appendix_a_dataview Messages for Dataview Client Objects

	<table>
		<tr><td>getcelltext					</td><td>void dbviewer_getcelltext(t_dbviewer *x, t_symbol *colname, long index, char *text, long maxlen);</td><td></td></tr>
		<tr><td>newpatcherview				</td><td>void dbviewer_newpatcherview(t_dbviewer *x, t_object *patcherview);</td><td></td></tr>
		<tr><td>freepatcherview				</td><td>void dbviewer_freepatcherview(t_dbviewer *x, t_object *patcherview);</td><td></td></tr>
	</table>




*/
