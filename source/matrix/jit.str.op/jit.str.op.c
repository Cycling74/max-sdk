/*
	Copyright 2001 - Cycling '74
	Adam Florin
	Jeremy Bernstein jeremy@cycling74.com
*/

#include "jit.common.h"
#include "jit.str.op.h"
#include "ext_strings.h"

#include "jit.str.op.func.c"

#define CR_MAC '\n'

t_jit_str_op *jit_str_op_new(void);
void jit_str_op_free(t_jit_str_op *x);
t_jit_err jit_str_op_init(void);

void *_jit_str_op_class;

t_symbol *ps_strcat, *ps_slice, *ps_strrev, *ps_strcmp, *ps_strlen, *ps_toupper, *ps_tolower, *ps_thru;

t_jit_err jit_str_op_init(void)
{
	long attrflags=0;
	t_jit_object *attr;
	t_jit_object *mop, *o;

	_jit_str_op_class = jit_class_new("jit_str_op",(method)jit_str_op_new,(method)jit_str_op_free,
									  sizeof(t_jit_str_op),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,2,1);
	jit_mop_single_type(mop,_jit_sym_char);
	jit_mop_single_planecount(mop,1);
	jit_mop_input_nolink(mop,2);
//	jit_mop_output_nolink(mop,1);
	o = jit_object_method(mop,_jit_sym_getinput,2);
	jit_object_method(o,_jit_sym_ioproc,jit_mop_ioproc_copy_adapt); //in2 should adapt, out no
//	jit_object_method(o,_jit_sym_ioproc,jit_mop_ioproc_copy_trunc_zero);
	jit_attr_setlong(o,_jit_sym_mindimcount,1);
	jit_attr_setlong(o,_jit_sym_maxdimcount,2);
	o = jit_object_method(mop,_jit_sym_getoutput,1);
	jit_attr_setlong(o,_jit_sym_mindimcount,1);
	jit_attr_setlong(o,_jit_sym_maxdimcount,2);
	jit_class_addadornment(_jit_str_op_class,mop);
	//add methods
	jit_class_addmethod(_jit_str_op_class, (method)jit_str_op_matrix_calc, "matrix_calc", A_CANT, 0L);

	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"op",_jit_sym_symbol,attrflags,
						  (method)0,(method)0L,calcoffset(t_jit_str_op,opsym));
	jit_class_addattr(_jit_str_op_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Op");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"start",_jit_sym_long,2,attrflags,
						  (method)0,(method)jit_str_op_start_set,calcoffset(t_jit_str_op, startcount),calcoffset(t_jit_str_op,start));
	jit_class_addattr(_jit_str_op_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Start");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"end",_jit_sym_long,2,attrflags,
						  (method)0,(method)jit_str_op_end_set,calcoffset(t_jit_str_op, endcount),calcoffset(t_jit_str_op,end));
	jit_class_addattr(_jit_str_op_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"End");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"multiline_in",_jit_sym_char,attrflags,
						  (method)0,(method)0L,calcoffset(t_jit_str_op,multiline_in));
	jit_class_addattr(_jit_str_op_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Multiline In\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"multiline_out",_jit_sym_char,attrflags,
						  (method)0,(method)0L,calcoffset(t_jit_str_op,multiline_out));
	jit_class_addattr(_jit_str_op_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Multiline Out\"");

	attrflags = JIT_ATTR_GET_OPAQUE_USER | JIT_ATTR_SET_OPAQUE_USER;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"adaptflag",_jit_sym_long,attrflags,
						  (method)0,(method)0L,calcoffset(t_jit_str_op,adaptflag));
	jit_class_addattr(_jit_str_op_class,attr);
	attr = jit_object_new(_jit_sym_jit_attr_offset,"outlong",_jit_sym_long,attrflags,
						  (method)0,(method)0L,calcoffset(t_jit_str_op,outlong));
	jit_class_addattr(_jit_str_op_class,attr);
	attr = jit_object_new(_jit_sym_jit_attr_offset,"outlong2",_jit_sym_long,attrflags,
						  (method)0,(method)0L,calcoffset(t_jit_str_op,outlong2));
	jit_class_addattr(_jit_str_op_class,attr);
	attr = jit_object_new(_jit_sym_jit_attr_offset,"outmode",_jit_sym_long,attrflags,
						  (method)0,(method)0L,calcoffset(t_jit_str_op,outmode));
	jit_class_addattr(_jit_str_op_class,attr);
	jit_class_register(_jit_str_op_class);

	ps_strcat		= gensym("strcat");
	ps_slice		= gensym("slice");
	ps_strrev		= gensym("strrev");
	ps_strcmp		= gensym("strcmp");
	ps_strlen		= gensym("strlen");
	ps_toupper		= gensym("toupper");
	ps_tolower		= gensym("tolower");
	ps_thru			= gensym("thru");

	return JIT_ERR_NONE;
}

void jit_str_op_start_set(t_jit_str_op *x, void *attr, long ac, t_atom *av)
{
	if (ac && av) {
		switch(ac) {
		case 1:
			x->start[0] = jit_atom_getlong(av);
			x->start[1] = 0;
			x->startcount = 1;
			break;
		case 2:
		default:
			x->start[0] = jit_atom_getlong(av++);
			x->start[1] = jit_atom_getlong(av);
			x->startcount = 1;
			break;
		}
	}
	else {
		x->start[0] = 0;
		x->start[1] = 0;
		x->startcount = 1;
	}
}

void jit_str_op_end_set(t_jit_str_op *x, void *attr, long ac, t_atom *av)
{
	if (ac && av) {
		switch(ac) {
		case 1:
			x->end[0] = jit_atom_getlong(av);
			x->end[1] = 0;
			x->endcount = 1;
			break;
		case 2:
		default:
			x->end[0] = jit_atom_getlong(av++);
			x->end[1] = jit_atom_getlong(av);
			x->endcount = 1;
			break;
		}
	}
	else {
		x->end[0] = 0;
		x->end[1] = 0;
		x->endcount = 1;
	}
}

void jit_str_op_vector_ignore(long n, void *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out)
{
	//nada
}

method jit_str_op_sym2fn(t_symbol *opsym) {
	if (opsym == ps_strcat)
		return jit_str_op_strcat;
	else if (opsym == ps_strrev)
		return jit_str_op_strrev;
	else if (opsym == ps_slice)
		return jit_str_op_slice;
	else if (opsym == ps_strcmp)
		return jit_str_op_strcmp;
	else if (opsym == ps_strlen)
		return jit_str_op_strlen;
	else if (opsym == ps_toupper)
		return jit_str_op_toupper;
	else if (opsym == ps_tolower)
		return jit_str_op_tolower;
	else if (opsym == ps_thru)
		return jit_str_op_thru;
	else
		return jit_str_op_vector_ignore;
}

t_jit_err jit_str_op_matrix_calc(t_jit_str_op *x, void *inputs, void *outputs) {
	t_jit_err err=JIT_ERR_NONE;
	long in1_savelock,in2_savelock,out_savelock;
	t_jit_matrix_info in1_minfo,in2_minfo,out_minfo;
	char *in1_bp,*in2_bp,*out_bp;
	long i,dimcount,planecount,dim[JIT_MATRIX_MAX_DIMCOUNT];
	t_jit_str_op_vecdata	vecdata;
	t_jit_op_info in1_opinfo,in2_opinfo,out_opinfo;
	void *in1_matrix, *in2_matrix, *out_matrix;
	long outlong = 0, n;
	char *string = NULL, *string2 = NULL;

	in1_matrix 	= jit_object_method(inputs,_jit_sym_getindex,0);
	in2_matrix 	= jit_object_method(inputs,_jit_sym_getindex,1);
	out_matrix 	= jit_object_method(outputs,_jit_sym_getindex,0);

	if (x&&in1_matrix&&in2_matrix&&out_matrix) {
		vecdata.opfn = jit_str_op_sym2fn(x->opsym); // set the opfn

		in1_savelock = (long) jit_object_method(in1_matrix,_jit_sym_lock,1);
		in2_savelock = (long) jit_object_method(in2_matrix,_jit_sym_lock,1);
		jit_object_method(in1_matrix,_jit_sym_getdata,&in1_bp);
		jit_object_method(in2_matrix,_jit_sym_getdata,&in2_bp);
		if (!in1_bp) { err=JIT_ERR_INVALID_INPUT; goto out;}
		if (!in2_bp) { err=JIT_ERR_INVALID_INPUT; goto out;}

		jit_object_method(in1_matrix,_jit_sym_getinfo,&in1_minfo);
		jit_object_method(in2_matrix,_jit_sym_getinfo,&in2_minfo);
		jit_object_method(out_matrix,_jit_sym_getinfo,&out_minfo);
		//this matrix-checking might be excessive, but what the hell....
		if ((in1_minfo.type!=_jit_sym_char) || (in2_minfo.type!=_jit_sym_char)|| (out_minfo.type!=_jit_sym_char)) {
			err = JIT_ERR_MISMATCH_TYPE;
			goto out;
		}
		if ((in1_minfo.planecount!=1) || (in2_minfo.planecount!=1) || (out_minfo.planecount!=1)) {
			err = JIT_ERR_MISMATCH_PLANE;
			goto out;
		}

		if (in1_minfo.dimcount > 2) {
			err = JIT_ERR_MISMATCH_DIM;
			goto out;
		}
		else if (in1_minfo.dimcount == 2 && in1_minfo.dim[1] > 1 && x->multiline_in) { // we need to collapse the matrix
			long dim[2]; // limit to 2D at the moment;
			long rowstride;
			t_bool slice = (x->opsym == ps_slice) ? true : false;
			t_bool flag = slice;

			dim[0] = in1_minfo.dim[0];
			dim[1] = in1_minfo.dim[1];
			rowstride = in1_minfo.dimstride[1];
			if (string = jit_str_op_tostring(x, in1_minfo.dimcount, dim, rowstride, in1_bp, &flag)) {
				in1_opinfo.stride = 1;
				in1_opinfo.p = string;
				vecdata.in1_len = strlen(string);
				if (slice) {
					if (flag)
						vecdata.opfn = jit_str_op_strrev;
					else
						vecdata.opfn = jit_str_op_thru; // it's sliced. just output it.
				}
			}
			else goto out;
		}
		else {
			in1_opinfo.stride = 1;
			in1_opinfo.p = in1_bp;
			vecdata.in1_len = jit_str_op_checklen(in1_minfo.dim[0], &in1_opinfo.p);
		}

		// we only make an in2_string if we need it
		if ((x->opsym == ps_strcat || x->opsym == ps_strcmp) && in2_minfo.dimcount == 2 && in2_minfo.dim[1] > 1 && x->multiline_in) { // collapse this one, too
			long dim[2];
			long rowstride;

			dim[0] = in2_minfo.dim[0];
			dim[1] = in2_minfo.dim[1];
			rowstride = in2_minfo.dimstride[1];
			if (string2 = jit_str_op_tostring(x, in2_minfo.dimcount, dim, rowstride, in2_bp, false)) {
				in2_opinfo.stride = 1;
				in2_opinfo.p = string2;
				vecdata.in2_len = strlen(string2);
			}
			else goto out;
		}
		else {
			in2_opinfo.stride = 1;
			in2_opinfo.p = in2_bp;
			vecdata.in2_len = jit_str_op_checklen(in2_minfo.dim[0], &in2_opinfo.p);
		}

		n = out_minfo.dim[0];
//		n = CLAMP(out_minfo.dim[0], 1, MAX_STRING_LENGTH);
		vecdata.outlong[0] = 0;
		vecdata.outlong[1] = 0;

		if (vecdata.opfn == jit_str_op_strcat) {
			if (x->adaptflag) {
				n = out_minfo.dim[0] = vecdata.in1_len + vecdata.in2_len;// + 1;
				jit_object_method(out_matrix, _jit_sym_setinfo, &out_minfo);
			}
		}
		else if (vecdata.opfn == jit_str_op_slice) {
			long start = x->start[0], end = x->end[0];
			if (x->start[1] != 0) {
				jit_object_error((t_object *)x,"jit.str.op: bad start point for 1D slice");
				err = JIT_ERR_SUPPRESS_OUTPUT;
				goto out;
			}
			else if (x->end[1] != 0)
				end = vecdata.in1_len - 1;

			vecdata.start = (start < 0) ? 0 : (start > vecdata.in1_len - 1) ? vecdata.in1_len - 1 : start;
			vecdata.end = (end < 0) ? 0 : (end > vecdata.in1_len - 1) ? vecdata.in1_len - 1 : end;
			if (x->adaptflag) {
				n = out_minfo.dim[0] = ABS(vecdata.end - vecdata.start) + 1; // + 1 for the char//, + 1 for the 0
				jit_object_method(out_matrix, _jit_sym_setinfo, &out_minfo);
			}
		}
		else if (vecdata.opfn == jit_str_op_strrev) {
			vecdata.start = vecdata.in1_len - 1;
			vecdata.end = 0;
			if (x->adaptflag) {
				n = out_minfo.dim[0] = (vecdata.start - vecdata.end) + 1; // + 1 for the char//, +1 for the 0
				jit_object_method(out_matrix, _jit_sym_setinfo, &out_minfo);
			}
		}
		else {
			if (x->adaptflag) {
				n = out_minfo.dim[0] = vecdata.in1_len;// + 1; // add the 0
				jit_object_method(out_matrix, _jit_sym_setinfo, &out_minfo);
			}
		}

//		outlong = 0;
//		outlong2 = 0;
		out_savelock = (long) jit_object_method(out_matrix,_jit_sym_lock,1);
		jit_object_method(out_matrix,_jit_sym_getdata,&out_bp);
		if (!out_bp) {
			err=JIT_ERR_INVALID_OUTPUT;
			jit_object_method(out_matrix,_jit_sym_lock,out_savelock);
			goto out;
		}

		out_opinfo.stride = 1;
		out_opinfo.p = out_bp;
		(*(vecdata.opfn))(n, &vecdata, &in1_opinfo, &in2_opinfo, &out_opinfo);//, &outlong);
		x->outmode = vecdata.outputtype;
		x->outlong = vecdata.outlong[0];
		x->outlong2 = vecdata.outlong[1];
		jit_object_method(out_matrix,_jit_sym_lock,out_savelock);

		if (x->multiline_out) { // we have to expand the matrix
			if (string)
				jit_disposeptr(string);
			string = jit_newptr(out_minfo.dim[0] + 1);
			jit_copy_bytes(string, out_bp, out_minfo.dim[0]);
			string[out_minfo.dim[0]] = 0;
			jit_str_op_expand(x, out_matrix, (const char *)string);
		}
	}
	else {
		return JIT_ERR_INVALID_PTR;
	}

out:
	jit_object_method(in2_matrix,_jit_sym_lock,in2_savelock);
	jit_object_method(in1_matrix,_jit_sym_lock,in1_savelock);
	if (string) jit_disposeptr(string);
	if (string2) jit_disposeptr(string2);
	return err;
}

void jit_str_op_expand(t_jit_str_op *x, void *out_matrix, const char *buf)
{
	long loc, crcount, longline;
	t_jit_matrix_info info;
	long n;
	char *out_bp;
	char *text = (char *)buf;
	long dim[JIT_MATRIX_MAX_DIMCOUNT], dimcount = 0;
	long size;
	long err;

	loc = 0;
	crcount = 0;
	longline = 0;

	if (out_matrix) {
		jit_object_method(out_matrix, _jit_sym_getinfo, &info);

		size = strlen(text);
		for (n = 0; n < size; n++) {
			if (*text++ == CR_MAC) {
				if (loc > longline)
					longline = loc;
				loc = 0;
				crcount++;
			}
			else {
				loc++;
			}
		}
		if (*(--text) != CR_MAC) { // in case last line not cr terminated
			if (loc > longline)
				longline = loc;
			crcount++;
		}

		if (longline || crcount) {
			long lock;

			dim[0] = info.dim[0] = longline;
			dim[1] = info.dim[1] = crcount;
			dimcount = info.dimcount = 2;
			info.planecount = 1;
			info.type = _jit_sym_char;

			jit_object_method(out_matrix, _jit_sym_setinfo, &info);
			jit_object_method(out_matrix, _jit_sym_getinfo, &info);

			lock = (long) jit_object_method(out_matrix,_jit_sym_lock,1);
			jit_object_method(out_matrix,_jit_sym_getdata,&out_bp);
			if (!out_bp) {
				err=JIT_ERR_INVALID_OUTPUT;
				goto oot;
			}
			jit_str_op_packmatrix(x, dimcount, dim, &info, out_bp, buf);
oot:
			jit_object_method(out_matrix,_jit_sym_lock, lock);
		}
	}

}

void jit_str_op_packmatrix(t_jit_str_op *x, long dimcount, long *dim,  t_jit_matrix_info *info, char *bop, const char *buf)
{
	long i;
	char *op;

	if (dimcount<1) return; //safety

	switch(dimcount) {
	case 1:
		dim[1]=1;
	case 2:
		if (info->type == _jit_sym_char)
			jit_str_op_read_char(x, dim, info, bop, buf);
		break;
	default:
		for	(i = 0; i < dim[dimcount-1]; i++) {
			op = bop + i * info->dimstride[dimcount-1];
			jit_str_op_packmatrix(x, dimcount-1, dim, info, op, buf);
		}
	}
}

void jit_str_op_read_char(t_jit_str_op *x, long *dim, t_jit_matrix_info *info, char *bop, const char *buf)
{
	long i, j, k;
	uchar *op;
	long width, height, planecount, bytecount;
	long size, err = 0, pos;
	long n, loc, crloc;
	char *text = (char *)buf;


	width = dim[0];
	height = dim[1];
	planecount = info->planecount;
	bytecount = sizeof(char) * width * planecount;

	size = strlen(text);

	if (size) {
		for (i = 0; i < height && size > 0; i++) {
			op = (uchar *)(bop + i * info->dimstride[1]);

			for (j = 0; j < width && size > 0; j++) {
				for (k = 0; k < planecount && size > 0; k++) {
					if (*text != CR_MAC) {
						*op++ = *text++;
						size--;
					}
					else {
						text++; //advance past cr if found, and the start new row
						size--;
						goto cont;
					}
				}
			}
			while (*text != CR_MAC && size) { //advance past next cr
				text++;
				size--;
			}
			text++;
			size--;

cont:
			;
		}
	}
}

char *jit_str_op_tostring(t_jit_str_op *x, long dimcount, long *dim, long rowstride, char *bip, t_bool *flag)
{
	long i, j;
	char *ip;
	char *string, *ssi;
	long size = 0;
	long line_length;

	size = (dim[0] * dim[1]) + dim[1]; // gross estimate, adding endlines

	if (size) {
		string = jit_newptr(size);
		ssi = string;

		if (*flag) {
			long start[2], end[2];

			if (x->start[1] > x->end[1]) {
				start[0] = x->end[0];
				end[0] = x->start[0];
				start[1] = x->end[1];
				end[1] = x->start[1];
				*flag = true;
			}
			else if (x->start[1] < x->end[1]) {
				start[0] = x->start[0];
				end[0] = x->end[0];
				start[1] = x->start[1];
				end[1] = x->end[1];
				*flag = false;
			}
			else {
				if (x->start[0] > x->end[0]) {
					start[0] = x->end[0];
					end[0] = x->start[0];
					*flag = true;
				}
				else {
					start[0] = x->start[0];
					end[0] = x->end[0];
					*flag = false;
				}
				start[1] = x->start[1];
				end[1] = x->end[1];
			}

			start[0] = MIN(dim[0] - 1, MAX(0, start[0]));
			end[0] = MIN(dim[0] - 1, MAX(0, end[0]));
			start[1] = MIN(dim[1] - 1, MAX(0, start[1]));
			end[1] = MIN(dim[1] - 1, MAX(0, end[1]));
			// first row
			i = start[1];
			if (i < end[1]) {
				ip = (char *)(bip + i * rowstride + start[0]);
				line_length = start[0];
				for (j = start[0]; j < dim[0]; j++) {
					if (*ssi++ = *ip++)
						;
					else {
						if (i + 1 < dim[0]) {
							*(--ssi) = CR_MAC;
							ssi++;
							j = dim[0]; // force next line
							continue;
						}
						else {
							--ssi;
							j = dim[0];
							line_length--;
						}
					}
					line_length++;
					if (line_length == dim[0] && i + 1 <= end[1]) {
						*ssi++ = CR_MAC;
						line_length++;
					}
				}
				i++;
			}
			for ( ; i < end[1]; i++) {
				ip = (char *)(bip + i * rowstride);
				line_length = 0;
				for (j = 0; j < dim[0]; j++) {
					if (*ssi++ = *ip++)
						;
					else {
						if (i + 1 <= end[1]) {
							*(--ssi) = CR_MAC;
							ssi++;
							j = dim[0]; // force next line
							continue;
						}
						else {
							--ssi;
							j = dim[0];
							line_length--;
						}
					}
					line_length++;
					if (line_length == dim[0] && i + 1 <= end[1]) {
						*ssi++ = CR_MAC;
						line_length++;
					}
				}
			}
			// last row through
			if (i == start[1]) {
				ip = (char *)(bip + i * rowstride + start[0]);
				j = start[0];
			}
			else {
				ip = (char *)(bip + i * rowstride);
				j = 0;
			}
			for ( ; j <= end[0]; j++) {
				if (*ssi++ = *ip++)
					;
				else {
					--ssi;
					break;
				}
			}
		}
		else {
			for (i = 0; i < dim[1]; i++) {
				ip = (char *)(bip + i * rowstride);
				line_length = 0;
				for (j = 0; j < dim[0]; j++) {
					if (*ssi++ = *ip++)
						;
					else {
						if (i + 1 < dim[1]) {
							*(--ssi) = CR_MAC;
							ssi++;
							j = dim[0]; // force next line
						}
						else {
							--ssi;
							j = dim[0];
							line_length--;
						}
					}
					line_length++;
					if (line_length == dim[0] && i + 1 < dim[1]) {
						*ssi++ = CR_MAC;
						line_length++;
					}
				}
			}
		}
		*ssi = '\0';
		return string;
	}
//	jit_object_post((t_object *)x,"got to end. how did that happen?");
	return NULL;
}

long jit_str_op_checklen(long n, t_jit_op_info *in1)
{
	char *s1;
	long i;

	s1 = in1->p;

	for (i = 0; i < n; i++) {
		if (!*s1++) break;
	}

	return i;
}

t_jit_str_op *jit_str_op_new(void)
{
	t_jit_str_op *x;

	if (x=(t_jit_str_op *)jit_object_alloc(_jit_str_op_class)) {
		x->opsym = gensym("strcat");
		x->outmode = 0;
		x->outlong = 0;
		x->adaptflag = 1;
		x->start[0] = 0;
		x->start[1] = 0;
		x->end[0] = 0;
		x->end[1] = 0;
		x->startcount = 1;
		x->endcount = 1;
		x->multiline_in = 1;
		x->multiline_out = 0;
	} else {
		x = NULL;
	}
	return x;
}

void jit_str_op_free(t_jit_str_op *x)
{
	//nada
}
