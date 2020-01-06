/**
	@page chapter_jit_mopdetails Matrix Operator Details

The purpose of this chapter is to fill in the details of what a Matrix Operator is and how it works. Matrix data in Jitter is typically considered raw data without respect to what the data represents. This permits simple fundamental operations to be applied to different sorts of data without needing to know any special information. For this reason most MOPs are general purpose. The jit.scalebias example from the preceding chapter could be considered video specific in its terminology, and type and plane count restrictions, but fundamentally it is just calculating a product and sum on each plane of an incoming matrix. In this chapter, we'll cover the details of how to configure MOP inputs and outputs, any attribute restrictions or linking for those inputs and outputs, what you must do in your matrix_calc method and how you expose your MOP to the Max environment, overriding default behavior if necessary.


@section chapter_jit_mopdetails_classes Defining the MOP Jitter Class

As discussed in the Matrix Operator Quick Start, for MOPs you must create an instance of jit_mop with the jit_object_new() function and add it to your Jitter class as an adornment with the jit_class_addadornment() function. The jit_mop object holds information such as how many inputs and outputs the object has, what types, plane count, and dimension counts are supported, and how inputs should respond to incoming matrices. This information is only relevant to wrappers of the Jitter object which actually maintain additional matrices for inputs and outputs, as is the case with the MOP Max wrapper class. When used from C, Java, or JavaScript, it is the the programmer's responsibility to pass in matrices that conform to any restrictions imposed by the MOP. An example of instantiating and adding the jit_mop object is below.

@code
   // create a new instance of jit_mop with 1 input, and 1 output
   mop = jit_object_new(_jit_sym_jit_mop,1,1);

   // add jit_mop object as an adornment to the class
   jit_class_addadornment(_jit_your_class,mop);
@endcode


@section chapter_jit_mopdetails_io The jit_mop_io Object

Each instance of jit_mop contains some number of inputs and outputs, specified by the input and output arguments to the constructor. For each of these inputs and outputs there is an instance of jit_mop_io which records information specific to that input or output, such as type, plane count, and dimension restrictions. You can access the input or output objects by calling the getinput or getoutput methods with an integer index argument as below:

@code
   input = jit_object_method(mop,_jit_sym_getinput,1);
   output = jit_object_method(mop,_jit_sym_getoutput,1);
@endcode

Once you have obtained references to these inputs or outputs, you may query or set the jit_mop_io attributes. The attributes typically configured are: types, which is a list of symbols of permitted types, the first of which being the default; mindim and maxdim, which are the minimum and maximum permitted sizes for each dimension; mindimcount and maxdimcount, which are the minimum and maximum permitted number of dimensions permitted; minplanecount and maxplanecount, which are the minimum and maximum number of planes permitted; typelink, which is the flag that determines if the I/O should change its type to whatever the leftmost incoming matrix is; dimlink, which is the flag that determines if the I/O should change its dimensions to whatever the leftmost incoming matrix is; and planelink, which is the flag that determines if the I/O should change its plane count to whatever the leftmost incoming matrix is.


@section chapter_jit_mopdetails_restrictingattrs Restricting Input/Output Attributes

By default, all types, dimensions and plane count are permitted, and all linking is enabled. If you wish your MOP to have some specific restrictions, or difference in linking behaviors for any input or output in particular, you can set the corresponding attributes. For example, to set the plane count to always be four planes, you would set both the minplanecount and maxplanecount attributes to 4, as below:

@code
   output = jit_object_method(mop,_jit_sym_getoutput,1);
   jit_attr_setlong(output,_jit_sym_minplanecount,4);
   jit_attr_setlong(output,_jit_sym_maxplanecount,4);
@endcode

The jit.scalebias example could have set the planecount using the minplanecount and maxplanecount attributes rather than calling the utility function jit_mop_single_planecount(), which internally sets these attributes. A similar thing could be done to restrict type and dimensions. As for linking, if you wish to develop an object where the right hand input does not adapt to the size of the leftmost input, as is the case with jit.convolve, you would turn off the dimlink attribute, as below:

@code
   input2 = jit_object_method(mop,_jit_sym_getinput,2);
   jit_attr_setlong(input2,_jit_sym_dimlink,0);
@endcode

Similar could be done to remove type and planecount linking, and the utility functions jit_mop_input_nolink() and jit_mop_output_nolink() set all of these link attributes to false (zero).


@section chapter_jit_mopdetails_ioproc The ioproc Function

For right hand matrix inputs, incoming data is typically copied by the MOP Max wrapper class. When an incoming matrix is received by the MOP Max wrapper class, a function called the ioproc is called, and the default ioproc copies the data, using the current input attributes (which might be linked to the lefthand input). The default ioproc can be overridden by calling the ioproc method followed by a function with the signature as listed below in the jit_mop_ioproc_copy_adapt() function. The jit_mop_ioproc_copy_adapt() function will always adapt to that inlet's incoming matrix attributes, as long as they don't conflict with any restrictions. The SDK project for jit.concat demonstrates the use of the jit_mop_ioproc_copy_adapt() function.

@code
t_jit_err jit_mop_ioproc_copy_adapt(void *mop, void *mop_io, void *matrix)
{
   void *m; // destination matrix
   t_jit_matrix_info info;

   // look up destination matrix from mop_io
   if (matrix&&(m=jit_object_method(mop_io,_jit_sym_getmatrix)))
   {
      // retrieve incoming matrix info
      jit_object_method(matrix,_jit_sym_getinfo,&info);

      //restrict matrix info based on mop_io attribtues
      jit_object_method(mop_io,_jit_sym_restrict_type,&info);
      jit_object_method(mop_io,_jit_sym_restrict_dim,&info);
      jit_object_method(mop_io,_jit_sym_restrict_planecount,&info);

      // set destination matrix info
      jit_object_method(m,_jit_sym_setinfo,&info);

      // copy the data with the frommatrix method
      jit_object_method(m,_jit_sym_frommatrix,matrix,NULL);
   }

   return JIT_ERR_NONE;
}
@endcode


@section chapter_jit_mopdetails_vario Variable Inputs/Outputs

You can specify variable input/output MOPs with a negative argument for input and/or outputs when constructing your jit_mop object. When the using variable inputs and/or outputs, there is not a jit_mop_io for each input and/or output within your class definition, and therefore the template type, dim, planecount, and linking attributes are not settable. If anything but the default behavior is required, you must accomplished it in another way — for example, either by overriding the jit_matrix method of the MOP Max wrapper class, or defining an mproc method to be called from within the standard jit_matrix method of the MOP Max wrapper class. The jit.pack, jit.unpack, jit.scissors, and jit.glue objects are a few SDK examples of MOPs with variable inputs and outputs. More information on overriding the jit_matrix, mproc, and other default methods of the MOP Max wrapper class is covered later in this chapter.


@section chapter_jit_mopdetails_adorn Adding jit_mop as a Class Adornment

Once you have configured all of the inputs and outputs of your jit_mop object, you must add your jit_mop object to your Jitter class with the jit_class_addadornment() function. Adorments can be queried from the Jitter class at any time by calling jit_class_adornment_get() with the Jitter class pointer and the class name of the adornment object, as demonstrated below.

@code
   // add jit_mop object as an adornment to the class
   jit_class_addadornment(_jit_your_class,mop);

   // look up jit_mop adornment
   mop = jit_class_adornment_get(_jit_your_class,_jit_sym_jit_mop);
@endcode

@section chapter_jit_mopdetails_calc The Matrix Calculation Method

The entry point of the MOP Jitter class is the matrix_calc method, which is passed a list of matrices for the input, and a list of matrices for the output. It is not the responsibility of the matrix_calc method to perform any copying and adaptation behavior, but rather simply ensure that the matrices are valid, compatible, and if so, process. Certain objects may modify the dim, type, or planecount of the output matrices — e.g. the SDK project, jit.thin. However, it is the calling party's responsibility to perform any copying and conformance to MOP I/O restrictions as defined by the jit_mop_io objects—i.e. either the Max wrapper class, or the C, Java, or Javascript code which calls the matrix_calc method.


@section chapter_jit_mopdetails_access Accessing the Input and Output Lists

The input and output lists passed as arguments to your matrix_calc method are Jitter objects, and pointers to the individual inputs and outputs are acquired by calling the getindex method with an integer argument specifying the zero based list index. The return values should be tested to make sure they are not null. For example:

@code
   // get the zeroth index input and output from
   // the corresponding input and output lists
   in_matrix    = jit_object_method(inputs,_jit_sym_getindex,0);
   out_matrix	= jit_object_method(outputs,_jit_sym_getindex,0);

   // if the object and both input and output matrices
   // are valid, then process, else return an error
   if (x&&in_matrix&&out_matrix)
   {
      // ... process data ...

   } else {
      return JIT_ERR_INVALID_PTR;
   }
@endcode

Technically, you can also pass in an instance of jit_matrix in place of a list for the input or output arguments, since jit_matrix has a getindex method which returns the jit_matrix instance. This is an example of dynamic binding at work. Another example of dynamic binding inside the matrix_calc method is that the list elements might be instances of jit_mop_io, rather than instances of jit_matrix. However, since Jitter uses dynamic binding and the jit_mop_io object is a "decorator" class for jit_matrix, all corresponding methods are passed on to the jit_matrix referenced by the jit_mop_io. In fact, any Jitter objects which respond to the standard interface for jit_matrix could be passed as inputs or outputs. If this seems confusing, you need not think about the underlying implementation further, but instead can assume that what is being passed in is simply an instance of jit_matrix. After all it should behave like one, even if it is not.


@section chapter_jit_mopdetails_locking Locking and Unlocking Matrices

Prior to working with a matrix, it is necessary to "lock" it so that the data and attributes will not be changed across the duration of the operation. This is accomplished by calling the jit_matrix instance's lock method with an integer argument of 1 (true) to lock the matrix. You should store the current lock state to restore when you're done processing. The lock operation should be the first thing to do after ensuring that the matrix objects are not NULL. For example

@code
   // lock input and output matrices
   in_savelock = (long) jit_object_method(in_matrix,_jit_sym_lock,1);
   out_savelock = (long) jit_object_method(out_matrix,_jit_sym_lock,1);

   // ... process data ...

out:
   // restore matrix lock state to previous value
   jit_object_method(out_matrix,_jit_sym_lock,out_savelock);
   jit_object_method(in_matrix,_jit_sym_lock,in_savelock);
@endcode


@section chapter_jit_mopdetails_info Retrieving Matrix Information

Once you have locked the matrices, you are ready to find out some information about them. This is accomplished by calling the getinfo method with a pointer to an instance of the #t_jit_matrix_info struct. The #t_jit_matrix_info struct contains several common attributes of the matrix and data organization of the matrix data, and is a useful way to obtain this information in one call, rather than querying each attribute individually. This information is typically tested to verify compatibility with any assumptions the matrix_calc method needs to make (since this method might be called from C, Java, or Javascript, you cannot assume that the MOP Max wrapper will have enforced these assumptions). It is also used to perform the appropriate pointer arithmetic based on type, plane count, dimensions, and the byte stride of those dimensions, since higher dimensions may not be tightly packed. The #t_jit_matrix_info struct is listed below:

@code
typedef struct _jit_matrix_info
{
   long      size;         // in bytes (0xFFFFFFFF=UNKNOWN)
   t_symbol   *type;         // primitive type
   long      flags;         // matrix flags: my data?, handle?
   long      dimcount;      // # of dimensions
   long      dim[JIT_MATRIX_MAX_DIMCOUNT]; // dimension sizes
   long      dimstride[JIT_MATRIX_MAX_DIMCOUNT]; // in bytes
   long      planecount;      // # of planes
} t_jit_matrix_info;
@endcode

And here is an example of calling the getinfo method to fill out the #t_jit_matrix_info struct:
@code
   // fill out matrix info structs for input and output
   jit_object_method(in_matrix,_jit_sym_getinfo,&in_minfo);
   jit_object_method(out_matrix,_jit_sym_getinfo,&out_minfo);
@endcode


@section chapter_jit_mopdetails_data Retrieving the Data Pointer

The #t_jit_matrix_info struct is the meta data, but the actual matrix data can be accessed by acquiring the data pointer. You accomplish this by calling the matrix's getdata method, passing in a pointer to a pointer. This pointer can be any type, but it is typically a char (or byte) pointer since you may need to perform bytewise pointer arithmetic depending on the type and dimstride of your matrix. It is essential to verify that this pointer is valid before attempting to operate on the data, as demonstrated below.

@code
   // get matrix data pointers
   jit_object_method(in_matrix,_jit_sym_getdata,&in_bp);
   jit_object_method(out_matrix,_jit_sym_getdata,&out_bp);

   // if data pointers are invalid, set error, and cleanup
   if (!in_bp) { err=JIT_ERR_INVALID_INPUT; goto out;}
   if (!out_bp) { err=JIT_ERR_INVALID_OUTPUT; goto out;}
@endcode


@section chapter_jit_mopdetails_dataproc Processing the Data

While it is possible to incorporate the data processing code inside the matrix_calc method, it is typical to rely on other routines to accomplish the N dimensional processing through recursion, potentially dispatching to multiple processors. The N-dimensional recursive processing function (typically named myobject_calculate_ndim) is discussed in the next section. You should pass in to the calculate_ndim function your object pointer, the overall dimension count, dimension sizes, planecount to consider in your calculation, together with the necessary matrix info structs and data pointers for each input and output. You can call this method directly as is the case in the following code:

@code
   // call calculate_ndim function directly in current thread
   jit_scalebias_calculate_ndim(x, dimcount, dim, planecount,
      &in_minfo, in_bp, &out_minfo, out_bp);
@endcode

Or you can call this method with the parallel processing utility functions provided with Jitter 1.5 to automatically dispatch the processing of large matrices across multiple processors when available. This figure illustrates the dispatching and calculating of the parallel processing utility:

<img src="figures/parallel-processing.jpg">

The parallel processing is accomplished by breaking up the matrix into smaller matrices that each reference subregions of the original inputs and outputs. No new objects are created, but rather just additional #t_jit_matrix_info structs and offset data pointers. Jitter 1.5 maintains a pool of worker threads for this purpose, so there is no thread creation overhead, but rather only some small thread synchronization overhead. Jitter 1.5 only dispatches across multiple threads when the data count is large enough to justify this thread synchronization overhead.

An important thing worth noting is that if your object performs some kind of spatial operation (e.g. convolution, rotation, scaling, etc.), you will either need to account for the matrix segmentation used by the parallel utilities or avoid using parallel processing and call directly in the current thread. Since the jit.scalebias example only processes one pixel at a time (i.e. a pointwise operation), it is inherently parallelizable, so it takes advantage of multiple processors as below:

@code
   // calculate, using the parallel utility function to
   // call the calculate_ndim function in multiple
   // threads if there are multiple processors available
   jit_parallel_ndim_simplecalc2(
      (method)jit_scalebias_calculate_ndim,
      x, dimcount, dim, planecount,
      &in_minfo, in_bp, &out_minfo, out_bp,
      0, 0 );
@endcode

Important Note: If you aren't sure if your object is a pointwise operator, or don't fully understand how to make your algorithm parallelizable, you shouldn't use the parallel utility functions in your object. You should simply call the function directly.


@section chapter_jit_mopdetails_ndim Processing N-Dimensional Matrices

In the Matrix Operator Quick Start chapter, we discussed how to define a recursive function to process N-dimensional data in 2D slices, using the jit.scalebias object as an example. This example was restricted to processing four plane char data, but many Jitter objects work with any type of data and any plane count. In order to support all types and plane counts, there needs to be some case handling to know how to step through the data, and what type data to interpret as so that you can perform the appropriate operations. There are a number of ways to approach this logic, and decisions to make with respect to optimization. All this case handling can be a bit cumbersome, so when initially developing objects, it probably makes sense for you to focus on a single type and plane count, and only after you've adequately defined your operation, attempt to make your code robust to process any type of data and consider optimization of certain cases. The use of C macros, or C++ templates might be useful things to explore for better code re-use. As for code optimization, typically a decent atomic element to try and optimize is the "innermost" loop, avoiding branch conditions where possible.

This function is at the heart of the logic you will add in your own custom object. Since there is no "right way" to process this data, we won't cover any more code listings for the recursive N-dimensional processing function. However, the SDK projects that are good examples include: jit.clip, which performs a planar independent, pointwise operation (limiting numbers to some specified range); jit.rgb2luma, which performs a planar dependent, pointwise operation (converting RGB color to luminance); and jit.transpose, which performs a planar independent, spatial operation (rows become columns). For more ideas about N-dimensional matrix processing, we would recommend reading one of the several books available on 2D signal processing and/or image processing. Most of these concepts are easily generalized to higher dimensions.


@section chapter_jit_mopdetails_mopwrapdef Defining the MOP Max Wrapper Class

MOP Max wrapper classes typically have a large amount of default behavior, as setup through the max_jit_classex_mop_wrap function, based on the jit_mop Jitter class adornment, and user specified flags. You can either override all of the default behavior or just specific features. If you wish to override all of the default behavior, you can use the flag #MAX_JIT_MOP_FLAGS_OWN_ALL, when calling the max_jit_classex_mop_wrap() function. If you need to make use of the jit_mop adornment(), the jit_mop can be looked up by calling the jit_class_adornment_get() method on the Jitter class. The jit_mop_io inputs and outputs can be queried and their attributes inspected, similar to how they were set in the MOP Jitter class definition, described earlier in this chapter. Here is an example of how to look up the jit_mop adornment of the jit.scalebias object:

@code
   // look up jitter class by name
   jclass = jit_class_findbyname(gensym("jit_scalebias"));
   // look up jit_mop adornment
   mop = jit_class_adornment_get(jclass,_jit_sym_jit_mop);
@endcode


@section chapter_jit_mopdetails_override Overriding the jit_matrix Method

By default, a jit_matrix method is added which automatically manages matrix copying and calculation based on the incoming data. Most typical MOPs simply use the default jit_matrix method. However there are instances where it is necessary to override the default MOP method to get special behavior, such as recording which matrix input data is being input to as is the case for the jit.op SDK example, or to do something other than standard copying and adaptation as is the case for the jit.pack or jit.str.op SDK examples, or to prevent any jit_matrix method at all, as is the case for the jit.noise SDK example. To prevent the default jit_matrix method from being defined, you can use the flag #MAX_JIT_MOP_FLAGS_OWN_JIT_MATRIX, when calling the max_jit_classex_mop_wrap() function. To define your own jit_matrix method, you can add an #A_GIMME method bound to the symbol jit_matrix, in your ext_main() function. Here's an example from jit.op:

@code
   // add custom jit_matrix method in ext_main()
   addmess((method)max_jit_op_jit_matrix, "jit_matrix", A_GIMME, 0);

   void max_jit_op_jit_matrix(t_max_jit_op *x, t_symbol *s, short argc,
               t_atom *argv)
   {
      if (max_jit_obex_inletnumber_get(x))
      {
         // if matrix is received in right input,
         // record to override float or int input
         x->last = OP_LAST_MATRIX;
      }

      // now pass on to the default jit_matrix method
      max_jit_mop_jit_matrix(x,s,argc,argv);
   }
@endcode

The jit.pack and jit.str.op examples are a bit more involved and also better illustrate the kinds of tasks the default jit_matrix method performs.


@section chapter_jit_mopdetails_overridebang Overriding the bang and outputmatrix Methods

A MOP Max wrapper class typically has a bang and outputmatrix method. These two methods are typically equivalent, and by default, both send out the most recently calcuated matrix output. Certain objects that don't have a matrix output, like the jit.3m SDK example, typcially override these messages with their own bang and sometimes outputmatrix method. These methods can be overridden by using the #MAX_JIT_MOP_FLAGS_OWN_BANG and #MAX_JIT_MOP_FLAGS_OWN_OUTPUTMATRIX flags when calling the max_jit_classex_mop_wrap() function. These flags are typically both passed in together.


@section chapter_jit_mopdetails_overridemore Overriding the name, type, dim, and planecount Attributes

For each input and output, other than the leftmost input, there is, by default, an attribute added to query and set that input or output's matrix attributes, including name, type, dim, and planecount. While overriding the default attribute behavior is conceivably necessary to perform very specialized behavior, it is not used by any of the SDK examples. To prevent the addition of the default attributes for name, type, dim, and planecount, you can use the #MAX_JIT_MOP_FLAGS_OWN_NAME, #MAX_JIT_MOP_FLAGS_OWN_TYPE, #MAX_JIT_MOP_FLAGS_OWN_DIM, and #MAX_JIT_MOP_FLAGS_OWN_PLANECOUNT flags when calling the max_jit_classex_mop_wrap() function. To define your own attributes, you would follow the same means of defining any attributes for a Max wrapper class with the appropriate attribute name you wish to override.


@section chapter_jit_mopdetails_overrideclear Overriding the clear and notify Methods

By default, a clear and a notify method are added. The default clear method clears each of the input and output matrices. The default notify method, max_jit_mop_notify(), is called whenever any of the matrices maintained by the MOP are changed. If it is necessary to respond to additional notifications, it is important to call the max_jit_mop_notify function so that the MOP can perform any necessary maintenance with respect to input and output matrices, as demonstrated by the jit.notify SDK example. These methods can be overridden using the #MAX_JIT_MOP_FLAGS_OWN_CLEAR and #MAX_JIT_MOP_FLAGS_OWN_NOTIFY flags, respectively, when calling the max_jit_classex_mop_wrap() function. Object registration and notification is covered in detail in a future chapter, but the jit.notify notify method is provided as an example.

@code
// s is the servername, msg is the message, ob is the server object pointer,
// and data is extra data the server might provide for a given message
void max_jit_notify_notify(
   t_max_jit_notify *x, t_symbol *s, t_symbol *msg, void *ob, void *data)
{
   if (msg==gensym("splat")) {
      post("notify: server=%s message=%s",s->s_name,msg->s_name);
      if (!data) {
         error("splat message NULL pointer");
         return;
      }
      // here's where we output using the rightmost outlet
      // we just happen to know that "data" points to a t_atom[3]
      max_jit_obex_dumpout(x,msg,3,(t_atom *)data);
   } else {
      // pass on to the default Max MOP notification method
      max_jit_mop_notify(x,s,msg);
   }
}
@endcode


@section chapter_jit_mopdetails_overrideadapt Overriding the adapt and outputmode Attributes

By default, adapt and outputmode attributes are added to the MOP Max Wrapper. These attributes determine whether or not to adapt to incoming matrix attributes, and whether or not the output should calculate a new output matrix, output the last calculated matrix (freeze), pass on the input matrix (bypass). To prevent the addition of the default attributes for adapt and outputmode, you can use the #MAX_JIT_MOP_FLAGS_OWN_ADAPT, and #MAX_JIT_MOP_FLAGS_OWN_OUTPUTMODE flags when calling the max_jit_classex_mop_wrap() function. To define your own attributes, you would follow the same means of defining any attributes for a Max wrapper class with the appropriate attribute name you wish to override.


@section chapter_jit_mopdetails_mproc Defining an mproc Method

For many types of operations, it's not required to fully override the default jit_matrix method and any adaptation. If your object simply needs to override the way in which the Jitter class' matrix_calc method and outlet functions are called, you can do so by defining an mproc method, which will be called instead of the default behavior. The jit.3m SDK project is an example where after it calls the Jitter class' matrix_calc method, it queries the Jitter class' attributes and outputs max messages rather than the default jit_matrix message output.

@code
void max_jit_3m_mproc(t_max_jit_3m *x, void *mop)
{
   t_jit_err err;

   // call internal Jitter object's matrix_calc method
   if (err=(t_jit_err) jit_object_method(
      max_jit_obex_jitob_get(x),
      _jit_sym_matrix_calc,
      jit_object_method(mop,_jit_sym_getinputlist),
      jit_object_method(mop,_jit_sym_getoutputlist)))
   {
      // report error if present
      jit_error_code(x,err);
   } else {
      // query Jitter class and makes outlet calls
      max_jit_3m_bang(x);
   }
}
@endcode

@section chapter_jit_mopdetails_maxclassctor The Max Class Constructor/Destructor

As we discussed in the Matrix Operator Quick Start, inside your Max class' constructor you need to allocate the matrices necessary for the MOP inputs and outputs, the corresponding matrix inlets and outlets, process matrix arguments and other MOP setup. And in your destructor, you need to free oup MOP resources. Typically you would accomplish this all with the standard max_jit_mop_setup_simple() and max_jit_mop_free() functions, however there are some instances where you may need to introduce custom behavior.


@subsection chapter_jit_mopdetails_maxclassctor_vario Variable Inputs/Outputs

The max_jit_mop_setup_simple() function calls max_jit_mop_inputs() and max_jit_mop_outputs() to define any necessary proxy inlets, outlets, and internal matrices. The listing for these functions are provided below to illustrate the default behavior, and a few SDK projects we recommend investigating further are jit.scissors, jit.glue, jit.pack, and jit.unpack.

@code
t_jit_err max_jit_mop_inputs(void *x)
{
   void *mop,*p,*m;
   long i,incount;
   t_jit_matrix_info info;
   t_symbol *name;

   // look up object's MOP adornment
   if (x&&(mop=max_jit_obex_adornment_get(x,_jit_sym_jit_mop)))
   {
      incount  = jit_attr_getlong(mop,_jit_sym_inputcount);

      // add proxy inlet and internal matrix for
      // all inputs except leftmost inlet
      for (i=2;i<=incount;i++) {
         max_jit_obex_proxy_new(x,(incount+1)-i); // right to left
         if (p=jit_object_method(mop,_jit_sym_getinput,i)) {
            jit_matrix_info_default(&info);
            max_jit_mop_restrict_info(x,p,&info);
            name = jit_symbol_unique();
            m = jit_object_new(_jit_sym_jit_matrix,&info);
            m = jit_object_register(m,name);
            jit_attr_setsym(p,_jit_sym_matrixname,name);
            jit_object_method(p,_jit_sym_matrix,m);
            jit_object_attach(name, x);
         }
      }
      return JIT_ERR_NONE;
   }
   return JIT_ERR_INVALID_PTR;
}

t_jit_err max_jit_mop_outputs(void *x)
{
   void *mop,*p,*m;
   long i,outcount;
   t_jit_matrix_info info;
   t_symbol *name;

   if (x&&(mop=max_jit_obex_adornment_get(x,_jit_sym_jit_mop)))
   {
      outcount = jit_attr_getlong(mop,_jit_sym_outputcount);

      // add outlet and internal matrix for all outputs
      for (i=1;i<=outcount;i++) {
         max_jit_mop_matrixout_new(x,(outcount)-i);// right to left
         if (p=jit_object_method(mop,_jit_sym_getoutput,i)) {
            jit_matrix_info_default(&info);
            max_jit_mop_restrict_info(x,p,&info);
            name = jit_symbol_unique();
            m = jit_object_new(_jit_sym_jit_matrix,&info);
            m = jit_object_register(m,name);
            jit_attr_setsym(p,_jit_sym_matrixname,name);
            jit_object_method(p,_jit_sym_matrix,m);
            jit_object_attach(name, x);
         }
      }

      return JIT_ERR_NONE;
   }
   return JIT_ERR_INVALID_PTR;
}
@endcode

@subsection chapter_jit_mopdetails_maxclassctor_matargs Matrix Arguments

The max_jit_mop_setup_simple() function calls max_jit_mop_matrix_args() to read any matrix arguments, and if present send them to any linked inputs/outputs and disable the adapt attribute. The listing is provided below to illustrate the default behavior.

@code
t_jit_err max_jit_mop_matrix_args(void *x, long argc, t_atom *argv)
{
   void *mop,*p,*m;
   long incount,outcount,attrstart,i,j;
   t_jit_matrix_info info,info2;

   if (!(mop=max_jit_obex_adornment_get(x,_jit_sym_jit_mop)))
      return JIT_ERR_GENERIC;

   incount  = jit_attr_getlong(mop,_jit_sym_inputcount);
   outcount = jit_attr_getlong(mop,_jit_sym_outputcount);

   jit_matrix_info_default(&info);

   attrstart = max_jit_attr_args_offset(argc,argv);
   if (attrstart&&argv) {
      jit_atom_arg_getlong(&info.planecount, 0, attrstart, argv);
      jit_atom_arg_getsym(&info.type, 1, attrstart, argv);
      i=2; j=0;
      while (i<attrstart) { //dimensions
         jit_atom_arg_getlong(&(info.dim[j]), i, attrstart, argv);
         i++; j++;
      }
      if (j) info.dimcount=j;

      jit_attr_setlong(mop,_jit_sym_adapt,0); //adapt off
   }

   jit_attr_setlong(mop,_jit_sym_outputmode,1);

   for (i=2;i<=incount;i++) {
      if ((p=jit_object_method(mop,_jit_sym_getinput,i)) &&
         (m=jit_object_method(p,_jit_sym_getmatrix)))
      {
         jit_object_method(m,_jit_sym_getinfo,&info2);
         if (jit_attr_getlong(p,_jit_sym_typelink)) {
            info2.type = info.type;
         }
         if (jit_attr_getlong(p,_jit_sym_planelink)) {
            info2.planecount = info.planecount;
         }
         if (jit_attr_getlong(p,_jit_sym_dimlink)) {
            info2.dimcount = info.dimcount;
            for (j=0;j<info2.dimcount;j++) {
               info2.dim[j] = info.dim[j];
            }
         }
         max_jit_mop_restrict_info(x,p,&info2);
         jit_object_method(m,_jit_sym_setinfo,&info2);
      }
   }

   for (i=1;i<=outcount;i++) {
      if ((p=jit_object_method(mop,_jit_sym_getoutput,i)) &&
         (m=jit_object_method(p,_jit_sym_getmatrix)))
      {
         jit_object_method(m,_jit_sym_getinfo,&info2);
         if (jit_attr_getlong(p,_jit_sym_typelink)) {
            info2.type = info.type;
         }
         if (jit_attr_getlong(p,_jit_sym_planelink)) {
            info2.planecount = info.planecount;
         }
         if (jit_attr_getlong(p,_jit_sym_dimlink)) {
            info2.dimcount = info.dimcount;
            for (j=0;j<info2.dimcount;j++) {
               info2.dim[j] = info.dim[j];
            }
         }
         max_jit_mop_restrict_info(x,p,&info2);
         jit_object_method(m,_jit_sym_setinfo,&info2);
      }
   }

   return JIT_ERR_NONE;
}
@endcode

*/
