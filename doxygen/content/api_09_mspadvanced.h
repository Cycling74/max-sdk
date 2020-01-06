/**
	@page chapter_msp_advanced Advanced Signal Object Topics

	Here are some techniques for implementing additional features found in most signal objects.

	@section chapter_msp_advanced_internal_state Saving Internal State

	To implement unit generators such as filters and ramp generators, you need to save internal state between calls to your object's perform routine. Here is a very simple low-pass filter (it just averages successive samples) that saves the value of the last sample in a vector to be averaged with the first sample of the next vector. First we add a field to our data structure to hold the value:

@code
	typedef struct _myfilter
	{
		t_pxobject f_obj;
		double     f_sample;
	} t_myfilter;
@endcode

	Then, in our dsp method, we pass a pointer to the object as one of the DSP chain arguments.
	The dsp method also initializes the value of the internal state, to avoid any noise when the audio starts.

@code
	void myfilter_dsp64(t_myfilter *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
	{
		object_method(dsp64, gensym("dsp_add64"), x, myfilter_perform64, 0, NULL);
		x->f_sample = 0.0;
	}
@endcode

	Here is the perform routine, which obtains the internal state before entering the processing loop, then stores the most recent value after the loop is finished.

@code
	void myfilter_perform64(t_myfilter *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
	{
		double    *in = ins[0];        // first inlet
		double    *out = outs[0];      // first outlet
		int       n = sampleframes;    // vector size
		double    samp = x->f_sample;  // read from internal state
		double    val;

		while (n--) {
			val = *in++;
			*out++ = (val + samp) * 0.5;
			samp = val;
		}
		x->f_sample = samp;            // save to internal state
	}
@endcode


	@section chapter_msp_advanced_connections Using Connection Information

	The third argument to the dsp method is an array of numbers that enumerate the number of objects connected to each of your objects inputs and outputs.
	More advanced dsp methods can use this information for optimization purposes.
	For example, if you find that your object has no inputs or outputs, you could avoid calling 'dsp_add64' altogether.
	The MSP signal operator objects (such as +~ and *~) use this to implement a basic polymorphism:
	they look at the connections count to determine whether the perform routine should use scalar or signal inputs.
	For example, if the right input has no connected signals, the user can add a scalar value sent to the right inlet.

	To implement this behavior, you have a few different options.
	The first option is to write two different perform methods, one which handles the two-signal case, and one which handles the scalar case.
	The dsp method looks at the <code>count</code> array and passes a different function to dsp_add64.

@code
		if (count[1])	// signal connected to second inlet
			object_method(dsp64, gensym("dsp_add64"), x, mydspobject_twosigperform64, 0, NULL);
		else
			object_method(dsp64, gensym("dsp_add64"), x, mydspobject_scalarperform64, 0, NULL);
@endcode


	The second option is to store the value of the count array for a particular signal in your object's struct.
	Then the perform method can make the decision whether to use the signal value or a scalar value that has been stored by the object.
	In this case, many objects use a single sample value from the signal as a substitute for the scalar.
	Using the first sample (i.e., the value at index 0) is a technique that works for any vector size, since vector sizes could be as small as a single sample.
	Here is an example of this technique for an object that has two inputs and one output.
	The connection count for the right input signal is stored in a struct member named m_count:

@code
		x->m_count = count[1];
		object_method(dsp64, gensym("dsp_add64"), x, mydspobject_perform64, 0, NULL);
@endcode

	Here is a perform routine that uses the connection count information as passed in the format shown above:

@code
	void mydspobject_perform64(t_mydspobject *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
	{
		t_mydspobject *x = (t_mydspobject *)w[1];
		int           connected = x->m_count;
		double        *in = ins[0];
		double        *in2 = ins[1];
		double        *out = outs[0];
		int           n = sampleframes;
		double        in2value;

		// get scalar sample or use signal depending on whether signal is connected
		in2value = connected ? *in2 : x->m_scalarvalue;

		// do calculation here
		// ...
	}
@endcode


@section chapter_msp_advanced_buffers Working with Buffer Objects

	To access a named buffer~ object for either reading or writing sample values,
	refer to the @ref buffers reference.

*/
