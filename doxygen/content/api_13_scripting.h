/**
	@page chapter_scripting Scripting the Patcher

	Your object can use scripting capabilities of the patcher to learn things about its context, such as the patcher's name, hierarchy, or the peer objects to your object in its patcher.

	You can also modify a patcher, although any actions your object takes are not undoable and may not work in the runtime version.


	@section chapter_scripting_knowing Knowing the Patcher

	To obtain the patcher object containing your object, you can use the obex hash table. The obex (for "object extensions") is, more generally, a way to store and recall data in your object. In this case, however, we are just using it in a read-only fashion.

	Note that unlike the technique discussed in previous versions of the SDK, using the obex to find the patcher works at any time, not just in the new instance routine.

@code
	void myobject_getmypatcher(t_myobject *x)
	{
		t_object *mypatcher;

		object_obex_lookup(x, gensym("#P"), &mypatcher);
		post("my patcher is at address %lx",mypatcher);
	}
@endcode

	The patcher is an opaque Max object. To access data in a patcher, you'll use attributes and methods.


	@subsection chapter_scripting_knowing_name Patcher Name and File Path

	To obtain the name of the patcher and its file path (if any), obtain attribute values as shown below.
@code
		t_symbol *name = object_attr_getsym(patcher, gensym("name"));
		t_symbol *path = object_attr_getsym(patcher, gensym("filepath"));
@endcode

	These attributes may return NULL or empty symbols.


	@subsection chapter_scripting_knowing_heirarchy Patcher Hierarchy

	To determine the patcher hierarchy above the patcher containing your object, you can use jpatcher_get_parentpatcher(). A patcher whose parent is NULL is a top-level patcher. Here is a loop that prints the name of each parent patcher as you ascend the hierarchy.

@code
		t_object *parent, *patcher;
		t_symbol *name;

		object_obex_lookup(x, gensym("#P"), &patcher);
		parent = patcher;
		do {
			parent = jpatcher_get_parentpatcher(parent);
			if (parent) {
				name = object_attr_getsym(parent, gensym("name"));
				if (name)
					post("%s",name->s_name)
			}
		} while (parent != NULL);
@endcode


	@subsection chapter_scripting_knowing_objects Getting Objects in a Patcher

	To obtain the first object in a patcher, you can use jpatcher_get_firstobject(). Subsequent objects are available with jbox_get_nextobject().

	If you haven't read the @ref chapter_ui_anatomy, we'll mention that the patcher does not keep a list of non-UI objects directly. Instead it keeps a list of UI objects called boxes, and the box that holds non-UI objects is called a newobj. The "objects" you obtain with calls such as jpatcher_get_firstobject() are boxes. The jbox_get_object() routine can be used to get the pointer to the actual object, whether the box is a UI object or a newobj containing a non-UI object. In the case of UI objects such as dials and sliders, the pointer returned by jbox_get_object() will be the same as the box. But for non-UI objects, it will be different.

	Here is a function that prints the class of every object (in a box) in a patcher containing an object.
@code
	void myobject_printpeers(t_myobject *x)
	{
		t_object *patcher, *box, *obj;

		object_obex_lookup(x, gensym("#P"), &patcher);

		for (box = jpatcher_get_firstobject(patcher); box; box = jbox_get_nextobject(box)) {
			obj = jbox_get_object(box);
			if (obj)
				post("%s",object_classname(obj)->s_name);
			else
				post("box with NULL object");
		}
	}
@endcode


	@subsection chapter_scripting_knowing_iteration Iteration Using Callbacks

	As an alternative to the technique shown above, you can write a callback function for use with the patcher's iteration service. The advantage of using iteration is that you can descend into the patcher hierarchy without needing to know the details of the various objects that may contain subpatchers (patcher, poly~, bpatcher, etc.). If you want to iterate only at one level of a patcher hierarchy, you can do that too.

	Your iteration function is defined as follows. It will be called on every box in a patcher (and, if you specify, the patcher's subpatchers).
@code
	 long myobject_iterator(t_myobject *x, t_object *b);
@endcode

	The function returns 0 if iteration should continue, or 1 if it should stop. This permits you to use an iterator as a way to search for a specific object.

	Here is an example of using an iterator function:

@code
		t_object *patcher;
		long result = 0;
		t_max_err err;

		err = object_obex_lookup(x, gensym("#P"), &patcher);

		object_method(patcher, gensym("iterate"), myobject_iterator, (void *)x, PI_WANTBOX | PI_DEEP, &result);
@endcode

	The #PI_WANTBOX flag tells the patcher iterator that it should pass your iterator function the box, rather than the object contained in the box. The #PI_DEEP flag means that the iteration will descend, depth first, into subpatchers. The result parameter returns the last value returned by the iterator. For example, if the iterator terminates early by returning a non-zero value, it will contain that value. If the iterator function does not terminate early, result will be 0.

	Assuming the iterator function receives boxes, here is an example iterator that prints out the class and scripting name (if any) of all of the objects in a patcher. Note that the scripting name is an attribute of the box, while the class we would like to know is of the object associated with the box.

@code
	long myobject_iterator(t_myobject *x, t_object *b)
	{
		t_symbol *name = object_attr_getsym(b, gensym("varname"));
		t_symbol *cls = object_classname(jbox_get_object(b));

		if (name)
			post("%s (%s)",cls->s_name, name->s_name);
		else
			post("%s", cls->s_name);
		return 0;
	}
@endcode


	@section chapter_scripting_objects Creating Objects

	Much of the Max user interface is implemented using patcher scripting. For example, the inspectors are patchers in which an inspector object has been created. The file browser window has four or five separate scripted objects in it. Even the debug window is a dynamically scripted patcher. We point this out just to inform you that creating objects in a patcher actually works (if you get all the details right). The xxx example object shows how to use patcher scripting to create an "editing window" similar to the ones you see when double-clicking on a table or buffer~ object.

	Creating objects in a patcher generally requires the use of a @ref dictionary (see discussion of UI objects above), but there is a convenience function newobject_sprintf() that can be used to avoid some of the complexity.

	To create an object, your task is to set some attributes. In the absence of any specific values, an object's attributes will be set to some default, but you'll probably care, at the very least, about specifying the object's location. Here is an example that creates a toggle and metro object using a combination of attribute parse syntax and sprintf. If you're interested in creating objects with newobject_sprintf(), it may help to examine a Max document to see some of the attribute name - value pairs used to specify objects.

@code
		t_object *patcher, *toggle, *metro;
		t_max_err err;

		err = object_obex_lookup(x, gensym("#P"), &patcher);

		toggle = newobject_sprintf(patcher, "@maxclass toggle
			@patching_position %.2f %.2f",
			x->togxpos, x-> togxpos);

		metro = newobject_sprintf(patcher, "@maxclass newobj @text \"metro 400\"
			@patching_position %.2f %.2f",
			x->metxpos, x->metypos);
@endcode

	Note that to create a non-UI object, you use set the maxclass attribute to newobj and the text attribute to the contents of the object box. Attributes can be specified in any order. Using the patching_position attribute permits you to specify only the top-left corner and use the object's default size. For text objects, the default size is based on the default font for the patcher.

	Finally, note that newobject_sprintf() returns a pointer to the newly created box, not the newly created object inside the box. To get the object inside the box, use jbox_get_object().


	@subsection chapter_scripting_objects_connecting Connecting Objects

	If you'd like to script the connections between two objects, you can do so via a message to the patcher. Assuming you have the patcher, toggle, and metro objects above, you'll create an array of atoms to send the message using object_method_typed().

@code
		t_atom msg[4], rv;

		atom_setobj(msg, toggle);		// source
		atom_setlong(msg + 1, 0);		// outlet number (0 is leftmost)
		atom_setobj(msg + 2, metro);	// destination
		atom_setlong(msg + 3, 0);		// inlet number (0 is leftmost)

		object_method_typed(patcher, gensym("connect"), 4, msg, &rv);
@endcode

	If you want to have a hidden connection, pass an optional fifth argument that is any negative number.


	@section chapter_scripting_objects_deleting Deleting Objects

	To delete an object in a patcher you call object_free() on the box.
	As of Max 5.0.6 this will properly redraw the patcher and remove any connected patch cords.


	@section chapter_scripting_attrs Obtaining and Changing Patcher and Object Attributes

	You can use object attribute functions to modify the appearance and behavior of objects in a patcher or the patcher itself. Note that only a few of these attributes can be modified by the user. The C level access to attributes is much more extensive.

	Attributes whose type is object can be accessed via object_attr_getobj() / object_attr_setobj(). Attributes whose type is char can be accessed with object_attr_getchar() / object_attr_setchar(). Attributes whose type is long can be accessed with object_attr_getlong() / object_attr_setlong(). Attributes whose type is symbol can be accessed via object_attr_getsym() / object_attr_setsym(). For attributes that are arrays, such as colors and rectangles, use object_attr_getvalueof() / object_attr_setvalueof().


	@subsection chapter_scripting_attrs_patcher Patcher Attributes

<table>
	<tr><td>Name							   </td><td>Type				</td><td>Settable					</td><td>Description</td></tr>
	<tr><td>box									</td><td>object			</td><td>No											</td><td>The box containing the patcher (NULL for top-level patcher)            </td></tr>
	<tr><td>locked							</td><td>char				</td><td>Yes (not in runtime)		</td><td>Locked state of the patcher                                            </td></tr>
	<tr><td>presentation				</td><td>char				</td><td>Yes			 								</td><td>Presentation mode of the patcher                                       </td></tr>
	<tr><td>openinpresentation	</td><td>char				</td><td>Yes			 								</td><td>Will patcher open in presentation mode?                                </td></tr>
	<tr><td>count								</td><td>long				</td><td>No			 								</td><td>Number of objects in a patcher                                         </td></tr>
	<tr><td>fgcount							</td><td>long				</td><td>No			 								</td><td>Number of objects in the patcher's foreground layer                    </td></tr>
	<tr><td>bgcount							</td><td>long				</td><td>No			 								</td><td>Number of objects in the patcher's background layer                    </td></tr>
	<tr><td>numvews							</td><td>long				</td><td>No			 								</td><td>Number of currently open views of the patcher                          </td></tr>
	<tr><td>numwindowviews			</td><td>long				</td><td>No			 								</td><td>Number of currently open window-based views of the patcher             </td></tr>
	<tr><td>firstobject					</td><td>object			</td><td>No			 								</td><td>First box in the patcher                                               </td></tr>
	<tr><td>lastobject					</td><td>object			</td><td>No			 								</td><td>Last box in the patcher                                                </td></tr>
	<tr><td>firstline						</td><td>object			</td><td>No			 								</td><td>First patch cord in the patcher                                        </td></tr>
	<tr><td>firstview						</td><td>object			</td><td>No			 								</td><td>First view object in the patcher                                       </td></tr>
	<tr><td>title								</td><td>symbol			</td><td>Yes			 								</td><td>Window title                                                           </td></tr>
	<tr><td>fulltitle						</td><td>symbol			</td><td>No			 								</td><td>Complete title including "unlocked" etc.                               </td></tr>
	<tr><td>name								</td><td>symbol			</td><td>No			 								</td><td>Name (could be different from title)                                   </td></tr>
	<tr><td>filename						</td><td>symbol			</td><td>No			 								</td><td>Filename                                                               </td></tr>
	<tr><td>filepath						</td><td>symbol			</td><td>No			 								</td><td>File path (platform-independent file path syntax)                      </td></tr>
	<tr><td>fileversion					</td><td>long				</td><td>No			 								</td><td>File version                                                           </td></tr>
	<tr><td>noedit							</td><td>char				</td><td>No			 								</td><td>Whether patcher can be unlocked                                        </td></tr>
	<tr><td>collective					</td><td>object			</td><td>No			 								</td><td>Collective object, if patcher is inside a collective                   </td></tr>
	<tr><td>cansave							</td><td>char				</td><td>No											</td><td>Whether patcher can be saved                                           </td></tr>
	<tr><td>dirty								</td><td>char				</td><td>Yes (not in runtime)		</td><td>Whether patcher is modified                                            </td></tr>
	<tr><td>bglocked						</td><td>char				</td><td>Yes			 								</td><td>Whether background is locked                                           </td></tr>
	<tr><td>rect								</td><td>double[4]		</td><td>Yes			 								</td><td>Patcher's rect (left, top, width, height)                              </td></tr>
	<tr><td>defrect							</td><td>double[4]		</td><td>Yes			 								</td><td>Patcher's default rect (used when opening the first view)              </td></tr>
	<tr><td>openrect						</td><td>double[4]		</td><td>Yes			 								</td><td>Fixed initial window location                                          </td></tr>
	<tr><td>parentpatcher				</td><td>object			</td><td>No			 								</td><td>Immediate parent patcher (NULL for toplevel patchers)                  </td></tr>
	<tr><td>toppatcher					</td><td>object			</td><td>No			 								</td><td>Topmost parent patcher (NULL for toplevel patchers)                    </td></tr>
	<tr><td>parentclass					</td><td>object			</td><td>No			 								</td><td>Class object of parent (patcher, poly~, bpatcher etc.)                 </td></tr>
	<tr><td>bgcolor							</td><td>double[4]		</td><td>Yes			 								</td><td>Locked background color (RGBA)                                         </td></tr>
	<tr><td>editing_bgcolor			</td><td>double[4]		</td><td>Yes			 								</td><td>Unlocked background color (RGBA)                                       </td></tr>
	<tr><td>edit_framecolor			</td><td>double[4]		</td><td>Yes			 								</td><td>Text editing frame color                                               </td></tr>
	<tr><td>locked_iocolor			</td><td>double[4]		</td><td>Yes			 								</td><td>Locked inlet/outlet color                                              </td></tr>
	<tr><td>unlocked_iocolor		</td><td>double[4]		</td><td>Yes			 								</td><td>Unlocked inlet/outlet color                                            </td></tr>
	<tr><td>boguscolor					</td><td>double[4]		</td><td>Yes			 								</td><td>Color of uninitialized (bogus) objects                                 </td></tr>
	<tr><td>gridsize						</td><td>double[2]		</td><td>Yes			 								</td><td>Editing grid size                                                      </td></tr>
	<tr><td>gridonopen					</td><td>char				</td><td>Yes			 								</td><td>Show grid on open                                                      </td></tr>
	<tr><td>gridsnapopen				</td><td>char				</td><td>Yes			 								</td><td>Snap to grid on open                                                   </td></tr>
	<tr><td>imprint							</td><td>char				</td><td>Yes			 								</td><td>Save default-valued object attributes                                  </td></tr>
	<tr><td>defaultfocusbox			</td><td>symbol			</td><td>Yes			 								</td><td>Default focus box (varname)                                            </td></tr>
	<tr><td>enablehscroll				</td><td>char				</td><td>Yes			 								</td><td>Show horizontal scrollbar                                              </td></tr>
	<tr><td>enablevscroll				</td><td>char				</td><td>Yes			 								</td><td>Show vertical scrollbar                                                </td></tr>
	<tr><td>boxanimatetime			</td><td>long				</td><td>Yes			 								</td><td>Box animation time                                                     </td></tr>
	<tr><td>default_fontname		</td><td>symbol			</td><td>Yes			 								</td><td>Default font name                                                      </td></tr>
	<tr><td>default_fontface		</td><td>long				</td><td>Yes			 								</td><td>Default "fake" font face (0 plain, 1, bold, 2 italic, 3 bold italic)   </td></tr>
	<tr><td>default_fontsize		</td><td>long				</td><td>Yes			 								</td><td>Default font size in points                                            </td></tr>
	<tr><td>toolbarvisible			</td><td>char				</td><td>Yes			 								</td><td>Show toolbar on open                                                   </td></tr>
	<tr><td>toolbarheight				</td><td>long				</td><td>Yes			 								</td><td>Height of toolbar (can use 0 for invisible)                            </td></tr>
	<tr><td>toolbarid						</td><td>symbol			</td><td>Yes			 								</td><td>Name (in maxinterface.json) of toolbar, none = empty symbol            </td></tr>
</table>


	@subsection chapter_scripting_attrs_box Box Attributes

<table>
	<tr><td>Name							   </td><td>Type				</td><td>Settable					</td><td>Description</td></tr>
	<tr><td>rect								 </td><td>double[4]		</td><td>Settable only		</td><td>Changes both patching_rect and presentation_rect                </td></tr>
	<tr><td>presentation_rect		 </td><td>double[4]		</td><td>Yes							</td><td>Presentation mode rect                                          </td></tr>
	<tr><td>patching_rect				 </td><td>double[4]		</td><td>Yes							</td><td>Patching mode rect                                              </td></tr>
	<tr><td>position						 </td><td>double[2]		</td><td>Settable only		</td><td>Changes both patching_position and presentation_position        </td></tr>
	<tr><td>size								 </td><td>double[2]		</td><td>Settable only		</td><td>Changes both patching_size and presentation_size                </td></tr>
	<tr><td>patching_position		 </td><td>double[2]		</td><td>Yes							</td><td>Patching mode position (top, left corner)                       </td></tr>
	<tr><td>presentation_position</td><td>d[2]				</td><td>Yes							</td><td>Presentation mode position                                      </td></tr>
	<tr><td>patching_size				 </td><td>double[2]		</td><td>Yes							</td><td>Patching mode size (width, height)                              </td></tr>
	<tr><td>presentation_size		 </td><td>double[2]		</td><td>Yes							</td><td>Presentation mode size                                          </td></tr>
	<tr><td>maxclass						 </td><td>symbol			</td><td>No							</td><td>Name of Max class (newobj for non-UI objects)                   </td></tr>
	<tr><td>object							 </td><td>object			</td><td>No							</td><td>Associated object (equivalent to jbox_get_object)               </td></tr>
	<tr><td>patcher							 </td><td>object			</td><td>No							</td><td>Containing patcher                                              </td></tr>
	<tr><td>hidden							 </td><td>char				</td><td>Yes							</td><td>Is box hidden on lock?                                          </td></tr>
	<tr><td>fontname						 </td><td>symbol			</td><td>Yes			 				</td><td>Font name (if box has font attributes or a text field)          </td></tr>
	<tr><td>fontface						 </td><td>long				</td><td>Yes			 				</td><td>"Fake" font face (if box has font attribute or a text field)    </td></tr>
	<tr><td>fontsize						 </td><td>long				</td><td>Yes			 				</td><td>Font size (if box has font attributes or a text field)          </td></tr>
	<tr><td>textcolor						 </td><td>double[4]		</td><td>Yes			 				</td><td>Text color (if box has font attributes or a text field)         </td></tr>
	<tr><td>hint								 </td><td>symbol			</td><td>Yes			 				</td><td>Associated hint                                                 </td></tr>
	<tr><td>color								 </td><td>double[4]		</td><td>Yes			 				</td><td>Standard color attribute (may not be present in all objects)    </td></tr>
	<tr><td>nextobject					 </td><td>object			</td><td>No			 				</td><td>Next object in the patcher's list                               </td></tr>
	<tr><td>prevobject					 </td><td>object			</td><td>No			 				</td><td>Previous object in the patcher's list                           </td></tr>
	<tr><td>varname							 </td><td>symbol			</td><td>Yes			 				</td><td>Scripting name                                                  </td></tr>
	<tr><td>id									 </td><td>symbol			</td><td>No			 				</td><td>Immutable object ID (stored in files)                           </td></tr>
	<tr><td>canhilite						 </td><td>char				</td><td>No			 				</td><td>Does this object accept focus?                                  </td></tr>
	<tr><td>background					 </td><td>char				</td><td>Yes			 				</td><td>Include in background                                           </td></tr>
	<tr><td>ignoreclick					 </td><td>char				</td><td>Yes			 				</td><td>Ignores clicks                                                  </td></tr>
	<tr><td>maxfilename					 </td><td>symbol			</td><td>No			 				</td><td>Filename if class is external                                   </td></tr>
	<tr><td>description					 </td><td>symbol			</td><td>No			 				</td><td>Description used by assistance                                  </td></tr>
	<tr><td>drawfirstin					 </td><td>char				</td><td>No			 				</td><td>Is leftmost inlet drawn?                                        </td></tr>
	<tr><td>growy								 </td><td>char				</td><td>No			 				</td><td>Can object grow with fixed aspect ratio?                        </td></tr>
	<tr><td>growboth						 </td><td>char				</td><td>No			 				</td><td>Can object grow independently in width and height?              </td></tr>
	<tr><td>nogrow							 </td><td>char				</td><td>No			 				</td><td>Is object fixed size?                                           </td></tr>
	<tr><td>mousedragdelta			 </td><td>char				</td><td>No			 				</td><td>Does object use hidden-mouse drag tracking (number box)         </td></tr>
	<tr><td>textfield						 </td><td>object			</td><td>No			 				</td><td>Textfield object associated with this box if any                </td></tr>
	<tr><td>editactive					 </td><td>char				</td><td>No			 				</td><td>Is object the currently focused box in an unlocked patcher?     </td></tr>
	<tr><td>prototypename				 </td><td>symbol			</td><td>No			 				</td><td>Name of the prototype file used to create this object           </td></tr>
	<tr><td>presentation				 </td><td>char				</td><td>Yes			 				</td><td>Is object included in the presentation?                         </td></tr>
	<tr><td>annotation					 </td><td>symbol			</td><td>Yes			 				</td><td>Text shown in clue window when mouse is over the object         </td></tr>
	<tr><td>numinlets						 </td><td>long				</td><td>No			 				</td><td>Number of inlets visible                                        </td></tr>
	<tr><td>numoutlets					 </td><td>long				</td><td>No			 				</td><td>Number of outlets visible                                       </td></tr>
	<tr><td>outlettype					 </td><td>symbol[]		</td><td>No			 				</td><td>Array of symbols with outlet types ("signal" etc.)              </td></tr>
</table>

	To access an attribute of a non-UI object, use jbox_get_object() on the box to obtain the non-UI object first.


*/
