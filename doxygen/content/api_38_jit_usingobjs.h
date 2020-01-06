/**
	@page chapter_jit_usingobjs Using Jitter Objects in C

When developing for Jitter in C, the functionality of pre-existing Jitter objects can be used. In this chapter, we'll briefly examine instantation and incorporation of the features of the jit.movie and jit.qt.record objects from your C code.


@section chapter_jit_usingobjs_ex1 Example 1: the t_jit_qt_movie object

Using an object like t_jit_qt_movie from your own code is fairly straightforward. Since it's a standard Jitter object, we can use jit_object_new() and jit_object_free() for instantiation and freeing, jit_object_method() for sending messages, and jit_attr_get... and jit_attr_set... for getting and setting attributes.

For instance, in the following code snippet, we'll create a t_jit_qt_movie object, read a pre-specified movie from disk, and decompress its first frame into a matrix, set to the native size of the movie.

@code
void jit_foo_read_first_movie_frame(
   t_jit_foo *x, t_symbol *s, long ac, t_atom *av)
{
   void *qtmovie;

   // create the t_jit_qt_movie object, sized to 1x1
   qtmovie = jit_object_new(gensym("jit_qt_movie"), 1, 1);
   if (qtmovie) {
      t_atom rv; // will contain rvarr, with any return values
                 // from our "read" call
      t_object *rvarr; // the t_atomarray with the actual
                       // return values

      // turn off autostart
      jit_attr_setlong(qtmovie, gensym("autostart"), 0);
      // read the movie, just pass in the args to our function
      object_method_typed(qtmovie, gensym("read"), ac, av, &rv);

      // check the return value & verify that the movie loaded
      if (rvarr = jit_atom_getobj(&rv)) {
         long rvac = 0;
         t_atom *rvav = NULL;

         object_getvalueof(rvarr, &rvac, &rvav);
         if (rvac && rvav) {
            // just as in Max, we get a list: "filename success";
            // success of 1 means the read was successful
            if (rvac > 1 && jit_atom_getlong(rvav + 1)) {
               long dim[2];
               void *matrix;
               t_jit_matrix_info info;

               // get our movie's native dims
               jit_attr_getlong_array(qtmovie, gensym("movie_dim"),
                  2, dim);
               // set the t_jit_qt_movie's dim to match
               jit_object_method(qtmovie,_jit_sym_dim,dim[0],dim[1]);
               // set our matrix up to match
               jit_matrix_info_default(&info);
               info.type = _jit_sym_char;
               info.planecount = 4;
               info.dimcount = 2;
               info.dim[0] = dim[0];
               info.dim[1] = dim[1];
               matrix = jit_object_new(_jit_sym_jit_matrix, &info);
               if (matrix) {
                  // call the t_jit_qt_movie's matrix_calc method
                  // with our matrix as an argument
                  err = (t_jit_err)jit_object_method(qtmovie,
                     _jit_sym_matrix_calc, NULL, matrix);
                  if (err != JIT_ERR_NONE) {
                     error("something went wrong");
                  }
                  // do something with the matrix

                  // free the matrix
                  jit_object_free(matrix);
               }
            }
            freebytes(rvav, sizeof(t_atom) * rvac);
         }
         freeobject(rvarr);
      }
      jit_object_free(qtmovie);
   }
}
@endcode

Naturally, we could also set the t_jit_qt_movie object's time attribute, or call its or frame method, to recall an arbitrary point in time. In fact, nearly every documented method and attribute of the jit.movie object, as it functions in the Max interface, is available from C. The exceptions are those functions implemented in the Max wrapper object, such as framedump.

*/
