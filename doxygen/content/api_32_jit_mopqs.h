/**
	@page chapter_jit_mopqs Matrix Operator QuickStart

The purpose of this chapter is to give a quick and high level overview of how to develop a simple Matrix Operator (MOP), which can process the matrix type most commonly used for video streams—i.e. 4 plane char data. For this task, we will use the jit.scalebias SDK example. More details such as how to make a Matrix Operator which deals with multiple types, plane count, dimensionality, inputs, outputs, etc. will appear in the following chapter. This chapter assumes familiarity with Jitter's multi-dimensional matrix representation and Matrix Operators used from the Max patcher, as discussed in the Jitter Tutorial, and as well as the preceding chapters on the Jitter object model and Max wrapper classes.


@section chapter_jit_mopqs_classes Defining the MOP Jitter Class

In the Jitter class definition, we introduce a few new concepts for Matrix Operators. In addition to the standard method and attribute definitions discussed in the Jitter object model chapter, you will want to define things like how many inputs and outputs the operator has, and what type, plane count, and dimension restrictions the operator has. These are accomplished by creating an instance of the jit_mop class, setting some state for the jit_mop object and adding this object as an adornment to your Jitter class. The following code segment references the jit.scalebias SDK example.

@code
   // create a new instance of jit_mop with 1 input, and 1 output
   mop = jit_object_new(_jit_sym_jit_mop,1,1);

   // enforce a single type for all inputs and outputs
   jit_mop_single_type(mop,_jit_sym_char);

   // enforce a single plane count for all inputs and outputs
   jit_mop_single_planecount(mop,4);

   // add the jit_mop object as an adornment to the class
   jit_class_addadornment(_jit_scalebias_class,mop);
@endcode

You create your jit_mop instance in a similar fashion to creating your attribute instances, using jit_object_new(). The jit_mop constructor has two integer arguments for inputs and outputs, respectively. By default, each MOP input and output is unrestricted in plane count, type, and dimension, and also are linked to the plane count, type, and dimensions of the first (i.e. leftmost) input. This default behavior can be overridden, and this simple 4 plane, char type, jit.scalebias example enforces the corresponding type and plane count restrictions via the jit_mop_single_type() and jit_mop_single_planecount() utility functions. For more information on the jit_mop class, please see the following chapter on MOP details and the Jitter API reference.

Once you have created your jit_mop instance, and configured it according to the needs of your object, you add it as an adornment to your Jitter class with the jit_class_add_adornment() function. Adornments are one way for Jitter objects to have additional information, and in some instances behavior, tacked onto an existing class. Adornments will be discussed in detail in a later chapter.

You also want to define your matrix calculation method, where most of the work of a Matrix Operator occurs, with the jit_class_addmethod() function as a private, untyped method bound to the symbol matrix_calc.

@code
   jit_class_addmethod(_jit_scalebias_class,
      (method)jit_scalebias_matrix_calc,
      "matrix_calc", A_CANT, 0L);
@endcode


@section chapter_jit_mopqs_ctordtor The Jitter Class Constructor/Destructor

You don't need to add anything special to your Matrix Operator's constructor or destructor, aside from the standard initialization and cleanup any Jitter object would need to do. Any internal matrices for input and outputs are maintained, and only required, by the Max wrapper's asynchronous interface. The Jitter MOP contains no matrices for inputs and outputs, but rather expects that the matrix calculation method is called with all inputs and outputs synchronously. When used from languages like C, Java, and JavaScript, it is up to the programmer to maintain and provide any matrices which are being passed into the matrix calculation method.


@section chapter_jit_mopqs_calc The Matrix Calculation Method

The most important method for Matrix Operators, and the one in which the most work typically occurs is in the matrix calculation, or "matrix_calc" method, which should be defined as a private, untyped method with the #A_CANT type signature, and bound to the symbol "matrix_calc". In this method your object receives a list of input matrices and output matrices to use in its calculation. You need to lock access to these matrices, inquire about important attributes, and ensure that any requirements with respect to type, plane count, or dimensionality for the inputs are met before actually processing the data, unlocking access to the matrices and returning. It should be defined as in the following example.

@code
t_jit_err jit_scalebias_matrix_calc(t_jit_scalebias *x,
   void *inputs, void *outputs)
{
   t_jit_err err=JIT_ERR_NONE;
   long in_savelock,out_savelock;
   t_jit_matrix_info in_minfo,out_minfo;
   char *in_bp,*out_bp;
   long i,dimcount,planecount,dim[JIT_MATRIX_MAX_DIMCOUNT];
   void *in_matrix,*out_matrix;

   // get the zeroth index input and output from
   // the corresponding input and output lists
   in_matrix    = jit_object_method(inputs,_jit_sym_getindex,0);
   out_matrix    = jit_object_method(outputs,_jit_sym_getindex,0);

   // if the object and both input and output matrices
   // are valid, then process, else return an error
   if (x&&in_matrix&&out_matrix)
   {
      // lock input and output matrices
      in_savelock =
         (long) jit_object_method(in_matrix,_jit_sym_lock,1);
      out_savelock =
         (long) jit_object_method(out_matrix,_jit_sym_lock,1);

      // fill out matrix info structs for input and output
      jit_object_method(in_matrix,_jit_sym_getinfo,&in_minfo);
      jit_object_method(out_matrix,_jit_sym_getinfo,&out_minfo);

      // get matrix data pointers
      jit_object_method(in_matrix,_jit_sym_getdata,&in_bp);
      jit_object_method(out_matrix,_jit_sym_getdata,&out_bp);

      // if data pointers are invalid, set error, and cleanup
      if (!in_bp) { err=JIT_ERR_INVALID_INPUT; goto out;}
      if (!out_bp) { err=JIT_ERR_INVALID_OUTPUT; goto out;}

      // enforce compatible types
      if ((in_minfo.type!=_jit_sym_char) ||
         (in_minfo.type!=out_minfo.type))
      {
         err=JIT_ERR_MISMATCH_TYPE;
         goto out;
      }

      // enforce compatible planecount
      if ((in_minfo.planecount!=4) ||
         (out_minfo.planecount!=4))
      {
         err=JIT_ERR_MISMATCH_PLANE;
         goto out;
      }

      // get dimensions/planecount
      dimcount   = out_minfo.dimcount;
      planecount = out_minfo.planecount;
      for (i=0;i<dimcount;i++)
      {
         // if input and output are not matched in
         // size, use the intersection of the two
         dim[i] = MIN(in_minfo.dim[i],out_minfo.dim[i]);
      }

      // calculate, using the parallel utility function to
      // call the calculate_ndim function in multiple
      // threads if there are multiple processors available
      jit_parallel_ndim_simplecalc2(
         (method)jit_scalebias_calculate_ndim,
         x, dimcount, dim, planecount,
         &in_minfo, in_bp, &out_minfo, out_bp,
         0, 0);
   } else {
      return JIT_ERR_INVALID_PTR;
   }

out:
   // restore matrix lock state to previous value
   jit_object_method(out_matrix,_jit_sym_lock,out_savelock);
   jit_object_method(in_matrix,_jit_sym_lock,in_savelock);
   return err;
}
@endcode


@section chapter_jit_mopqs_ndim Processing N-Dimensional Matrices

Since Jitter supports the processing of N-dimensional matrices where N can be any number from 1 to 32, most Matrix Operators are designed with a recursive function that will process the data in some lower dimensional slice, most often 2 dimensional. The recursive function that does this is typically named myobject_calculate_ndim(), and is called by your matrix_calc method either directly or via one of the parallel processing utility functions, which are discussed in a future chapter.

It is out of the scope of this documentation to provide a detailed tutorial on fixed point or pointer arithmetic, both of which are used in this example. The code increments a pointer through the matrix data, scaling each planar element of each matrix cell by some factor and adding some bias amount. This is done with fixed point arithmetic (assuming an 8bit fractional component), since a conversion from integer to floating point data and back is an expensive operation. The jit.scalebias object also has two modes, one which sums the planes together, and one which processes each plane independently. You can improve performance by case handling on a per row, rather than per cell basis, and reduce your code somewhat by case handling on a per row, rather than per matrix basis. While a slight performance increase could be made by handling on a per matrix basis, per row is usually a decent point at which to make such an optimization trade off.

@code
// recursive function to handle higher dimension matrices,
// by processing 2D sections at a time
void jit_scalebias_calculate_ndim(t_jit_scalebias *x,
   long dimcount, long *dim, long planecount,
   t_jit_matrix_info *in_minfo, char *bip,
   t_jit_matrix_info *out_minfo, char *bop)
{
   long i,j,width,height;
   uchar *ip,*op;
   long ascale,rscale,gscale,bscale;
   long abias,rbias,gbias,bbias,sumbias;
   long tmp;

   if (dimcount<1) return; //safety

   switch(dimcount)
   {
   case 1:
      // if only 1D, interpret as 2D, falling through to 2D case
      dim[1]=1;
   case 2:
      // convert floating point scale factors to a fixed point int
      ascale = x->ascale*256.;
      rscale = x->rscale*256.;
      gscale = x->gscale*256.;
      bscale = x->bscale*256.;

      // convert floating point bias values to a fixed point int
      abias  = x->abias*256.;
      rbias  = x->rbias*256.;
      gbias  = x->gbias*256.;
      bbias  = x->bbias*256.;

      // for efficiency in sum mode (1), make a single bias value
      sumbias = (x->abias+x->rbias+x->gbias+x->bbias)*256.;

      width  = dim[0];
      height = dim[1];

      // for each row
      for (i=0;i<height;i++)
      {
         // increment data pointers according to byte stride
         ip = bip + i*in_minfo->dimstride[1];
         op = bop + i*out_minfo->dimstride[1];

         switch (x->mode) {
         case 1:
            // sum together, clamping to the range 0-255
            // and set all output planes
            for (j=0;j<width;j++) {
               tmp  = (long)(*ip++)*ascale;
               tmp += (long)(*ip++)*rscale;
               tmp += (long)(*ip++)*gscale;
               tmp += (long)(*ip++)*bscale;
               tmp  = (tmp>>8L) + sumbias;
               tmp  = (tmp>255)?255:((tmp<0)?0:tmp);
               *op++ = tmp;
               *op++ = tmp;
               *op++ = tmp;
               *op++ = tmp;
            }
            break;
         default:
            // apply to each plane individually
            // clamping to the range 0-255
            for (j=0;j<width;j++) {
               tmp = (((long)(*ip++)*ascale)>>8L)+abias;
               *op++ = (tmp>255)?255:((tmp<0)?0:tmp);
               tmp = (((long)(*ip++)*rscale)>>8L)+rbias;
               *op++ = (tmp>255)?255:((tmp<0)?0:tmp);
               tmp = (((long)(*ip++)*gscale)>>8L)+gbias;
               *op++ = (tmp>255)?255:((tmp<0)?0:tmp);
               tmp = (((long)(*ip++)*bscale)>>8L)+bbias;
               *op++ = (tmp>255)?255:((tmp<0)?0:tmp);
            }
            break;
         }
      }
      break;
   default:
      // if processing higher dimension than 2D,
      // for each lower dimensioned slice, set
      // base pointer and recursively call this function
      // with decremented dimcount and new base pointers
      for   (i=0;i<dim[dimcount-1];i++)
      {
         ip = bip + i*in_minfo->dimstride[dimcount-1];
         op = bop + i*out_minfo->dimstride[dimcount-1];
         jit_scalebias_calculate_ndim(x,dimcount1,
            dim,planecount,in_minfo,ip,out_minfo,op);
      }
   }
}
@endcode

Rather than using multidimensional arrays, Jitter matrix data is packed in a single dimensional array, with defined byte strides for each dimension for greatest flexibility. This permits matrices to reference subregions of larger matrices, as well as support data that is not tightly packed. Therefore, rather than using multidimensional array syntax, this code uses pointer arithmetic to access each plane of each cell of the matrix, adding the corresponding byte strides to the base pointer for each dimension across which it is iterating. These byte strides are stored in the dimstride entry of the #t_jit_matrix_info struct. Note that Jitter requires that planes within a cell, and cells across the first dimension (dim[0]) are tightly packed. The above code assumes that this is the case, using a simple pointer increment for each plane and cell, rather than looking up byte strides for dim[0].


@section chapter_jit_mopqs_wrapperdef Defining the MOP Max Wrapper Class

In order to use the MOP class in a Max patcher you need to make a Max wrapper class. In addition to the standard methods used to wrap any Jitter class, MOPs need to add special methods and information to the Max class. One of the things that needs to happen is that the Max wrapper class needs to allocate and maintain instances of jit.matrix for each matrix input and output other than the leftmost input, to accommodate Max's asynchronous event model. In order to perform this maintenance, the Max wrapper class must have special methods and attributes for setting the type, plane count, dimensions, adaptability, and named references for the internal matrices. All of these messages are exclusive to the Max wrapper implementation, and are not used by the C, Java, or JavaScript usage of Matrix Operators. There are also common methods and attributes for the matrix output mode, and the jit_matrix and bang messages, all of which are specific to the MOP's Max wrapper. These special attributes and methods are added by the max_jit_classex_mop_wrap() function, which should be called inside your Max external's ext_main() function, after calling max_jit_classex_setup() and jit_class_findbyname(), and before calling max_jit_classex_standard_wrap(). Several default methods and attributes can be overridden using the various flags that can be combined for the flags argument to max_jit_classex_mop_wrap(). These flags, which for most simple MOPs won't be necessary, are listed below.

@code
#define MAX_JIT_MOP_FLAGS_OWN_ALL           0xFFFFFFFF
#define MAX_JIT_MOP_FLAGS_OWN_JIT_MATRIX    0x00000001
#define MAX_JIT_MOP_FLAGS_OWN_BANG          0x00000002
#define MAX_JIT_MOP_FLAGS_OWN_OUTPUTMATRIX  0x00000004
#define MAX_JIT_MOP_FLAGS_OWN_NAME          0x00000008
#define MAX_JIT_MOP_FLAGS_OWN_TYPE          0x00000010
#define MAX_JIT_MOP_FLAGS_OWN_DIM           0x00000020
#define MAX_JIT_MOP_FLAGS_OWN_PLANECOUNT    0x00000040
#define MAX_JIT_MOP_FLAGS_OWN_CLEAR         0x00000080
#define MAX_JIT_MOP_FLAGS_OWN_NOTIFY        0x00000100
#define MAX_JIT_MOP_FLAGS_OWN_ADAPT         0x00000200
#define MAX_JIT_MOP_FLAGS_OWN_OUTPUTMODE    0x00000400
@endcode


@section chapter_jit_mopqs_maxctordtor The Max Class Constructor/Destructor

Inside your Max class' constructor you need to allocate the matrices necessary for the MOP inputs and outputs, the corresponding matrix inlets and outlets, process matrix arguments and other MOP setup. The max_jit_mop_setup_simple() function takes care of these functions and some of the other necessary tasks of wrapping your Jitter instance. As such, the use of this function simplifies your Jitter class wrapping even further for the simple case where no special behavior, incompatible with max_jit_mop_setup_simple() is required. Here is the constructor for the Max class of the jit.scalebias object.

@code
void *max_jit_scalebias_new(t_symbol *s, long argc, t_atom *argv)
{
   t_max_jit_scalebias *x;
   void *o;

   if (x = (t_max_jit_scalebias *)
      max_jit_obex_new(
      max_jit_scalebias_class,
      gensym("jit_scalebias")))
   {
      // instantiate Jitter object
      if (o=jit_object_new(gensym("jit_scalebias")))
      {
         // handle standard MOP max wrapper setup tasks
         max_jit_mop_setup_simple(x,o,argc,argv);

         // process attribute arguments
         max_jit_attr_args(x,argc,argv);
      }
      else
      {
         error("jit.scalebias: could not allocate object");
         freeobject(x);
      }
   }
   return (x);
}
@endcode

Below is the listing of the max_jit_mop_setup_simple() function, demonstrating the smaller pieces, it manages for you. If your object has special requirements, you can use whatever subset of the following function as necessary.

@code
t_jit_err max_jit_mop_setup_simple(void *x, void *o, long argc, t_atom *argv)
{
   max_jit_obex_jitob_set(x,o);
   max_jit_obex_dumpout_set(x,outlet_new(x,NULL));
   max_jit_mop_setup(x);
   max_jit_mop_inputs(x);
   max_jit_mop_outputs(x);
   max_jit_mop_matrix_args(x,argc,argv);

   return JIT_ERR_NONE;
}
@endcode

In your Max class' destructor, you need to free the resources allocated for your MOP. This is accomplished with the max_jit_mop_free() function, which should be called before you free your internal Jitter instance, and your Max class' obex data. As an example, the jit.scalebias destructor is listed below.

@code
void max_jit_scalebias_free(t_max_jit_scalebias *x)
{
   // free MOP max wrapper resources
   max_jit_mop_free(x);

   // lookup internal Jitter object instance and free
   jit_object_free(max_jit_obex_jitob_get(x));


   // free resources associated with obex entry
   max_jit_obex_free(x);
}
@endcode

*/
