/**
	@page chapter_msp_anatomy Anatomy of a MSP Object

	An MSP object that handles audio signals is a regular Max object with a few extras. Refer to the simplemsp~ example project source as we detail these additions. simplemsp~ is simply an object that adds a number to a signal, identical in function to the regular MSP +~ object if you were to give it an argument of 1.

	Here is an enumeration of the basic tasks:


	@section chapter_msp_anatomy_headers Additional Header Files

	After including ext.h and ext_obex.h, include z_dsp.h
@code
	#include "z_dsp.h"
@endcode


	@section chapter_msp_anatomy_struct C Structure Declaration

	The C structure declaration must begin with a #t_pxobject, not a #t_object:
@code
	typedef struct _mydspobject
	{
		t_pxobject m_obj;
		// rest of the structure's fields
	} t_mydspobject;
@endcode


	@section chapter_msp_anatomy_init Initialization Routine

	When creating the class with class_new(), you must have a free function. If you have nothing special to do, use dsp_free(), which is defined for this purpose. If you write your own free function, the first thing it should do is call dsp_free(). This is essential to avoid crashes when freeing your object when audio processing is turned on.
@code
		c = class_new("mydspobject", (method)mydspobject_new, (method)dsp_free, sizeof(t_mydspobject), NULL, 0);
@endcode

	After creating your class with class_new(), you must call class_dspinit(), which will add some standard method handlers for internal messages used by all signal objects.
@code
		class_dspinit(c);
@endcode

	Your signal object needs a method that is bound to the symbol "dsp" -- we'll detail what this method does below, but the following line needs to be added while initializing the class:
@code
		class_addmethod(c, (method)mydspobject_dsp64, "dsp64", A_CANT, 0);
@endcode


	@section chapter_msp_anatomy_new New Instance Routine

	The new instance routine must call dsp_setup(), passing a pointer to the newly allocated object pointer plus a number of signal inlets the object will have. If the object has no signal inlets, you may pass 0. The simplemsp~ object (as an example) has a single signal inlet:
@code
		dsp_setup((t_pxobject *)x, 1);
@endcode

	dsp_setup() will make the signal inlets (as proxies) so you need not make them yourself.

	If your object will have audio signal outputs, they need to be created in the new instance routine with outlet_new(). However, you will never access them directly, so you don't need to store pointers to them as you do with regular outlets. Here is an example of creating two signal outlets:
@code
		outlet_new((t_object *)x, "signal");
		outlet_new((t_object *)x, "signal");
@endcode


	@section chapter_msp_anatomy_dsp The DSP Method and Perform Routine

	The dsp64 method specifies the signal processing function your object defines along with its arguments.
	Your object's dsp64 method will be called when the MSP signal compiler is building a sequence of operations (known as the DSP Chain) that will be performed on each set of audio samples.
	The operation sequence consists of a pointers to functions (called perform routines) followed by arguments to those functions.

	The dsp64 method is declared as follows:
@code
	void mydspobject_dsp64(t_mydspobject *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
@endcode




	To add an entry to the DSP chain, your dsp64 method uses the "dsp_add64" method of the DSP chain.
	The dsp_add64 method is passed an a pointer to your object, a pointer to a perform64 routine that calculates the samples,
	an optional flag which may alter behavior, and a generic pointer which will be passed on to your perform routine.

@code
	object_method(dsp64, gensym("dsp_add64"), x, mydspobject_perform64, 0, NULL);
@endcode



	The perform routine is not a "method" in the traditional sense.
	It will be called within the callback of an audio driver, which,
	unless the user is employing the Non-Real Time audio driver, will typically be in a high-priority thread.
	Thread protection inside the perform routine is minimal.
	You can use a clock, but you cannot use qelems or outlets.

	Here is a perform routine that adds a constant of 1 to any incoming signal:

@code
	void mydspobject_perform64(t_mydspobject *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
	{
		double    *in = ins[0];     // first inlet
		double    *out = outs[0];   // first outlet
		int       n = sampleframes; // vector size
		t_double  value;

		while (n--) {               // perform calculation on all samples
			value = *in++;
			*out++ = value + 1.0;
		}
	}
@endcode


	@section chapter_msp_anatomy_free Free Function

	The free function for the class must either be dsp_free() or it must be written to call dsp_free() as shown in the example below:

@code
	void mydspobject_free(t_mydspobject *x)
	{
		dsp_free((t_pxobject *)x);

		// can do other stuff here
	}
@endcode

*/
