/**
	@page chapter_jit_sched Scheduler and Low Priority Queue Issues

In Max, there are a few threads of execution. The details of these threads are highlighted in the Max documentation and the article, "Event Priority in Max (Scheduler vs. Queue)". In this chapter, we won't cover all these details and restrict our discussion to the scheduler (which when overdrive is on runs in a separate and high priority thread) and the low priority queue (which always runs in the main application thread). As far as Jitter is concerned, we won't consider the real time audio thread or the case of scheduler in audio interrupt, where the scheduler runs in this real time audio thread.

By default, Jitter performs all drawing and matrix processing in the main application thread, with events serviced from the low priority queue. The reason for this low priority processing is to prevent high timing events such as note triggering or audio DSP from suffering timing problems due to visual processing. Jitter also exploits the low priority queue as a mechanism for graceful temporal downsampling of the visual stream in the instance that the processing requested is too demanding to be calculated in real-time. This results in dropped frames in the output when the demands cant be met. With audio, it's not sufficient to just drop frames of samples, since there will be an audible click, but with images, the last image will persist if a new one isn't generated at some fixed sampling rate.


@section chapter_jit_sched_usurp Defer and Usurp

The mechanisms which enforce execution of Jitter drawing and matrix processing from within the low priority queue we will call "defer" and "usurp". The defer mechanism will take any high priority events and create a corresponding low priority event at the end of the low priority queue. The defer mechanism ensures that the events will not be executed from the high priority scheduler thread, but does not prevent scheduler backlog with the temporal downsampling mentioned above. To accomplish this, the usurp mechanism mush be used. The usurp mechanism will use no more than one low priority queue element for the task requested (either a method call or attribute setter). The way usurp works is that if there is no pending event for the method or attribute call, a new event is placed at the end of the low priority queue. If there is already an event pending, the usurp mechanism will not place a new event on the end of the low priority queue, but rather "usurp" the arguments for the event waiting to being passed to the method or attribute call. This way, if a high priority metronome is rapidly sending values to set an attribute, while the initial low priority event is waiting to be processed, the value to be set is constantly being updated ("usurped") and only the value at the time of servicing the event will be used.

It is important to note that the defer and usurp mechanisms only work as called from within the Max patcher. For any methods which are called from a text based programming language, such as C, Java, or JavaScript, the defer and usurp mechanisms are bypassed. This may be something you need to pay attention to and handle yourself if you are making such calls from a text based programming language and need the defer or usurp behavior.


@section chapter_jit_sched_using Using Defer and Usurp in Jitter Object Methods

When defining a method in Jitter, there is the possibility to define a type signature for the method just as one would do in Max. Typical type signatures include typical atom elements such as #A_LONG, #A_FLOAT, and #A_SYM; or the corresponding default value versions #A_DEFLONG, #A_DEFFLOAT, #A_DEFSYM; or the variable argument version #A_GIMME which provides a list of atoms and the number of atoms provided; or the private and untyped status of #A_CANT used for methods which are not exposed to the patcher and require additional C function prototype information in order to call. While these type signatures can be used within Jitter objects, most methods exposed to the patcher interface make use of either the defer or usurp mechanism as defined by two new type signatures #A_DEFER_LOW or #A_USURP_LOW. Methods defined with the #A_DEFER_LOW, or #A_USURP_LOW type signatures should conform to the same variable argument prototype as #A_GIMME methods, but behind the scenes, Jitter will make use of the defer and usurp mechanism to enforce the appropriate behavior.

An example of two methods from jit.gl.videoplane which use these mechanisms is below:

@code
// add a usurping jit_matrix method
jit_class_addmethod(_jit_gl_videoplane_class, (method)jit_gl_videoplane_jit_matrix,   "jit_matrix", A_USURP_LOW, 0);

// add a deferred sendtexture method
jit_class_addmethod(_jit_gl_videoplane_class, (method)jit_gl_videoplane_sendtexture,   "sendtexture",  A_DEFER_LOW, 0);

The implementation of these methods is below:

void jit_gl_videoplane_jit_matrix(t_jit_gl_videoplane *x, t_symbol *s, int argc, t_atom *argv)
{
   t_symbol *name;
   void *m;
   t_jit_matrix_info info;
   long dim[2];

   if ((name=jit_atom_getsym(argv)) != _jit_sym_nothing) {
      m = jit_object_findregistered(name);
      if (!m) {
         error("jit.gl.videoplane: couldn't get matrix object!");
         return;
      }
   }

   if (x->texture) {
      jit_object_method(m, _jit_sym_getinfo, &info);
      jit_attr_getlong_array(x->texture,_jit_sym_dim,2,dim);
      jit_object_method(x->texture,s,s,argc,argv);
      jit_attr_setsym(x,ps_texture,x->texturename);
   }
}

void jit_gl_videoplane_sendtexture(t_jit_gl_videoplane *x, t_symbol *s, int argc, t_atom *argv)
{
   if (x->texture) {
      s = jit_atom_getsym(argv);
      argc--;
      if (argc)
         argv++;
      else
         argv = NULL;
      object_method_typed(x->texture,s,argc,argv,NULL);
   }
}
@endcode

From inspecting the header files, you may note that there are also #A_DEFER and #A_USURP type signatures, but these should be considered obsolete, as they make use of the problematic deferral strategy of placing the event at the front of the low priority queue and have the potential of reversing message sequencing.


@section chapter_jit_sched_attrs Using Defer and Usurp in Jitter Object Attributes

Unlike methods, attributes do not make use of type signatures for their getter and setter accessor methods. Instead they should always be prototyped similar to #A_GIMME, but with an attribute object being passed in place of the traditional method symbol pointer of the #A_GIMME signature. So the way you can specify to use the defer and usurp mechanisms for attribute accessors are through the attribute flags argument to the attribute constructor. For the getter accessor method, you can use #JIT_ATTR_GET_DEFER_LOW or #JIT_ATTR_GET_USURP_LOW flags. For the setter accessor method, you can use #JIT_ATTR_SET_DEFER_LOW or #JIT_ATTR_SET_USURP_LOW flags.

An example attribute definition from jit.gl.videoplane is below:

@code
attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
attr = jit_object_new(_jit_sym_jit_attr_offset,"displaylist",_jit_sym_char,attrflags,
   (method)0L,(method)jit_gl_videoplane_displaylist,calcoffset(t_jit_gl_videoplane, displaylist));
jit_class_addattr(_jit_gl_videoplane_class,attr);
@endcode

You may have noticed that like previous code example, all Jitter object attributes which are not private have been defined with getter accessors which use the defer mechanism (#JIT_ATTR_GET_DEFER_LOW) and setter accessors which use the usurp mechanism (#JIT_ATTR_SET_USURP_LOW). This is the recommended style of exposing Jitter object attributes to the patcher, since there are many cases where at high priority an attribute is set repeatedly and we want both the latest high priority value when the next calculation is made at low priority and no low priority queue backlog from generating more events at high priority than can be processed at low priority. The defer mechanism is used for getter accessor methods so that every attribute query results in a corresponding output message out the dump outlet. Otherwise certain patcher logic could easily become confused. If a different behavior is required by the Max programmer, they can make use of the jit.qball object to force either the defer or usurp mechanisms to be used for their message stream.


@section chapter_jit_sched_wrapper Using Defer and Usurp in the Max Wrapper Object

Most of the above is also true when declaring methods and attributes in the Max wrapper object, however the function calls which are used are slightly different. You must use the special max object function calls max_addmethod_defer_low() and max_addmethod_usurp_low() for methods, and max_jit_classex_addattr() for attributes. Below are examples from jit.matrixset. Note that there is no type signature provided for either max_addmethod_defer_low() or max_addmethod_usurp_low().

@code
// add a deferred "exportmovie" method
max_addmethod_defer_low((method)max_jit_matrixset_export_movie, "exportmovie");

// add a usurped outputmatrix method
max_addmethod_usurp_low((method)max_jit_matrixset_outputmatrix,    "outputmatrix");

// add index attribute
attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW ;
attr = jit_object_new(_jit_sym_jit_attr_offset,"index",_jit_sym_long,attrflags,
      (method)0L,(method)0L,calcoffset(t_max_jit_matrixset,index));
max_jit_classex_addattr(p,attr);
@endcode


@section chapter_jit_sched_justsayno When Not to Use the Usurp Mechanism

The bang method for Jitter MOP objects uses the usurp mechanism to drop frames when the number of bang messages cannot be handled in real time. However, jit.gl.render's bang method does not behave this way, and instead uses the defer mechanism. At first this might seem counterintuitive, however, because rendering in OpenGL with jit.gl.render uses a group of messages to perform erasing, any non automatic drawing of objects, and then a drawing of automatic clients and a swap to the screen with the bang method, it is not an atomic action (i.e. requires a sequence of different events rather than a single event). Since the usurp mechanism is method or attribute specific with regard to the events which are being usurped, it only works for atomic actions. For this reason, it is important for users to perform some drop framing behavior before triggering the message sequence, typically accomplished with qmetro or jit.qball. If your object has some operation which requires a sequence of events in a similar fashion as jit.gl.render, then it would be best to use the defer mechanism rather than the usurp mechanism for relevant methods.


@section chapter_jit_sched_override Overriding Defer and Usurp

There are instances where the user does not wish to be limited to processing Jitter matrices at low priority, such as when Jitter matrices are used for tasks other than realtime image processing--for example, parameter interpolation or matrices containing audio data. For these tasks, the jit.qfaker object is provided for advanced users which are aware of the potential problems involved in bypassing these low priority mechanisms. As mentioned above, when programming in a text based language, these mechanisms aren't used and all method and attribute accessor calls are synchronous. Therefore there typically isn't a need to consider overriding this behavior from a text based language. However, for certain externals which wish to simulate the jit.qfaker behavior, we expose the max_jit_queuestate() function to override Jitter's detection of queue state for the defer and usurp mechanisms. It is also possible to query what jitter believes the queue state to be with the max_jit_getqueuestate() function. This is the function employed by the defer and usurp mechanisms. The source code for these functions is below for reference.

@code
long max_jit_queuestate(long state)
{
   long rv=_max_jit_queuestate;

   _max_jit_queuestate = (state!=0);

   return rv;
}

long max_jit_getqueuestate(void)
{
   // always return true if faking
   if (_max_jit_queuestate) return 1;

   return !sched_isinpoll();
}
@endcode
*/
