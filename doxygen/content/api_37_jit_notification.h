/**
	@page chapter_jit_notification Jitter Object Registration and Notification

In Jitter, matrices are passed around as named references between Max objects. This named reference is created since Jitter registers these matrices with the corresponding name using the jit_object_register() function. Object registration is useful for a few reasons. First, registered matrices can be resolved by name using the jit_object_findregistered() function. Secondly, registered objects can sent event notification to clients who have attached to them using jit_object_attach(). Lastly, under certain circumstances, the object registration process can be used to have multiple external references to a single instance of an object as is the case with jit.matrix.


@section chapter_jit_notification_reg Registering Named Objects

To register an object, one can use the jit_object_register() function, which is equivalent to the Max object_register() function in the namespace associated with gensym("jitter"). Traditionally in Jitter, we bind jit_object_register() to the "register" method for an object and use jit_object_method() to call this method. For example, from the jit.notify SDK example:

@code
// allocate the Jitter object
if (o=jit_object_new(gensym("jit_notify"))) {
   ...
   // generate a unique name
   x->servername = jit_symbol_unique();

   // register the object with the given name
   jit_object_method(o,_jit_sym_register,x->servername);
   ...
}
@endcode

If not using a specific name, it is good to use the jit_symbol_unique() function as above to generate a unique name which is slated for re-use once a registered object is freed. This prevents excess memory usage by the symbol table as associated with these unique names.

If you wish the object to have multiple references to a single instance with some name, as is common with the jit.matrix object, it is essential to use the return value of jit_object_register() in any instance where the object pointer is saved after registration. This is because if the registered object with the same class already exists, the object attempting to be registered will be freed, and the already registered object of the same class will be returned, its reference count having been incremented. This is not typically an issue outside of registering jit.matrix objects, although you may have a need for this type of implementation in other situations. Most other situations in which object registration is used within Jitter only expects and/or permits a single instance to be registered. In the above example, we know that this is safe to do, as we are using jit_symbol_unique() to generate a unique name.

It is also possible to unregister named objects, with the jit_object_unregister() function, but typically this is handled for you when your object is freed, or if your object is registered again with a different name. This is not often used in the Jitter code base except within these contexts.


@section chapter_jit_notification_lookup Looking Up an Object by Name

Registered objects can be found by name using the jit_object_findregistered() function. For example named matrices are resolved using this function. Most Matrix Operator objects have this done for them by the default MOP code, but for example any MOP which has its own jit_matrix method, such as the jit.pack SDK example will make use of jit_object_findregistered() inside its jit_matrix method:

@code
// get our matrix name from the atom arguments provided
matrixname = jit_atom_getsym(argv);

// look up based on name
matrix = jit_object_findregistered(matrixname);

// make sure that it is a valid pointer and has a "class_jit_matrix" method which returns 1
if (matrix&&jit_object_method(matrix, _jit_sym_class_jit_matrix)) {
   ...
}
@endcode


@section chapter_jit_notification_attach Attaching to Named Objects

Once an object has been registered, it can be considered a server to which clients attach to be notified of various events. To attach to a named object, use the the jit_object_attach() function. Similarly to detach from a named object, use the jit_object_detach() function. It is typical to detach from a server in your object's destructor, or any time your object is switching which server it is attached to. For your client object to receive any notification from the server object, it is important for your object to have defined a "notify" method which will receive the notification from all objects it is attached to.

Below is the jit.notify SDK example's max wrapper object's notify method, which receives some atom values from its internal Jitter object instance. Since this object is a Matrix Operator, it is important in the following example that jit.notify calls the max_jit_classex_mop_wrap() function with the #MAX_JIT_MOP_FLAGS_OWN_NOTIFY flag to override the default MOP notify method, and that we pass on all other messages to the standard max_jit_mop_notify() method so that the default MOP code is informed of any changes to the input and output matrices.

@code
// s is the servername, msg is the message, ob is the server object pointer,
// and data is extra data the server might provide for a given message
void max_jit_notify_notify(t_max_jit_notify *x, t_symbol *s, t_symbol *msg, void *ob, void *data)
{
   if (msg==gensym("splat")) {
      post("notify: server=%s message=%s",s->s_name,msg->s_name);
      if (!data) {
         error("splat message NULL pointer");
         return;
      }
      // here's where we output using the rightmost outlet
      // we just happen to know that "data" points to a t_atom[3]
      // alternately you could use max_jit_obex_dumpout_get just to get
      // the outlet pointer
      max_jit_obex_dumpout(x,msg,3,(t_atom *)data);
   } else {
      // since we are a MOP, we are also attached to all the matrices for each input/output
      // so we need to deal with this by calling the default mop notify method
      // (this is how mops handle their matrices getting new names/freed/modified)
      max_jit_mop_notify(x,s,msg);
   }
}
@endcode


@section chapter_jit_notification_notify Notifying Clients

If you are making an object which is to be registered, and wish to send custom notification to clients in addition to the default notification that attributes send to all clients when the attribute is modified, and the default object free notification, then you will want to use the jit_object_notify() function. This function lets you determine a message name to use for notification and optionally specify additional, but untyped data to all clients. If you choose to send additional data to clients, it is necessary for all client code to know how to unpack this information. Below is the example from the jit.notify SDK example which uses the notification mechanism to send some data to its max wrapper object:

@code
	t_atom foo[3];

	jit_atom_setlong(&foo[0],1);
	jit_atom_setlong(&foo[1],2);
	jit_atom_setlong(&foo[2],3);
	jit_object_notify(x,gensym("splat"), foo);
@endcode

*/
