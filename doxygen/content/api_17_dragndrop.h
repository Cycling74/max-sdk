/**
	@page chapter_dragndrop Drag'n'Drop

	The Max file browser permits you to drag files to a patcher window or onto objects to perform file operations. Your object can specify the file types accepted as well as a message that will be sent when the user releases the mouse button with the file on top of the object. UI and non-UI objects use the same interface to drag'n'drop.

	Example UI object: <i>pictmeter~</i>. Example non-UI: TBD.

	Messages to support:
@code
	acceptsdrag_locked (A_CANT)
@endcode

	Sent to an object during a drag when the mouse is over the object in an unlocked patcher.
@code
	acceptsdrag_unlocked (A_CANT)
@endcode

	Sent to an object during a drag when the mouse is over the object in a locked patcher.


	@section chapter_dragndrop_discussion Discussion

	Why two different scenarios? acceptsdrag_unlocked() can be thought of as an "editing" operation. For example, objects such as pictslider accept new image files for changing their appearance when the patcher is unlocked, but not when the patcher is locked. By contrast, sfplay~ can accept audio files for playback in either locked or unlocked patchers, since that is something you can do with a message (rather than an editing operation that changes the patcher).

	Message handler definitions:
@code
	long myobject_acceptsdrag_unlocked(t_myobject *x, t_object *drag, t_object *view);
	long myobject_acceptsdrag_locked(t_myobject *x, t_object *drag, t_object *view);
@endcode

	The handlers return true if the file(s) contained in the drag can be used in some way by the object. To test the filetypes, use jdrag_matchdragrole() passing in the drag object and a symbol for the file type. Here is list of pre-defined file types:

	- audiofile
	- imagefile
	- moviefile
	- patcher
	- helpfile
	- textfile

	or to accept all files, use file

	If jdrag_matchdragrole() returns true, you then describe the messages your object receives when the drag completes using jdrag_object_add(). You can add as many messages as you wish. If you are only adding a single message, use jdrag_object_add(). For more control over the process, and for adding more than one message, jdrag_add() can be used. If you add more than one message, the user can use the option key to specify the desired action. By default, the first one you add is used. If there are two actions, the option key will cause the second one to be picked. If there are more than two, a pop-up menu appears with descriptions of the actions (as passed to jdrag_add()), and the selected action is used.

	Example:

	This code shows how to respond to an audiofile being dropped on your object by having the read message sent.
@code
		if (jdrag_matchdragrole(drag, gensym("audiofile"), 0)) {
			jdrag_object_add(drag, (t_object *)x, gensym("read"));
			return true;
		}
		return false;
@endcode

	Your acceptsdrag handler can test for multiple types of files and add different messages.


*/
