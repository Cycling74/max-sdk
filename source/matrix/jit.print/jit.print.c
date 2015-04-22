/*
	jit.print
	Copyright 2001-2005 - Cycling '74
	Jeremy Bernstein jeremy@bootsquad.com
*/

#include "jit.common.h"

#define ROW_DELIM '\r'
#define COL_DELIM ','
#define PLANE_DELIM 32 // space
#define DIM_DELIM '<'
//#define MATRIX_DELIM undefined

// we need a flag to scale or not scale incoming matrices for char.
//everything is treated as a float, so there's no way to distinguish...

#define BYTE_WRITE_COUNT 1024

typedef struct _jit_print
{
	t_object		ob;
	t_symbol		*rowdelim;
	t_symbol		*coldelim;
	t_symbol		*planedelim;
	t_symbol		*dimdelim;
	t_symbol		*matrixdelim;
	t_symbol		*title;
	char			precision;
	char			fieldwidth;
	char			mode;
	char			zeropad;
	char			info; // 0 - body no info, 1 - body + info, 2 - info no body
	t_bool			write_cherry;
	t_bool			read_cherry;
} t_jit_print;

t_jit_print *jit_print_new(void);
void jit_print_free(t_jit_print *x);
t_jit_err jit_print_init(void);

// matrix to print functions
t_jit_err jit_print_matrix_calc(t_jit_print *x, void *in_matrix);
t_jit_err jit_print_packtext_char(t_jit_print *x, long *dim, t_jit_matrix_info *info, char *bip);
t_jit_err jit_print_packtext_long(t_jit_print *x, long *dim, t_jit_matrix_info *info, char *bip);
t_jit_err jit_print_packtext_float32(t_jit_print *x, long *dim, t_jit_matrix_info *info, char *bip);
t_jit_err jit_print_packtext_float64(t_jit_print *x, long *dim, t_jit_matrix_info *info, char *bip);
t_jit_err jit_print_write_print_ndim(t_jit_print *x, long dimcount, long *dim, t_jit_matrix_info *info, char *bip);

void jit_print_planedelim_set(t_jit_print *x, t_symbol *s, long ac, t_atom *av);
t_jit_err jit_print_planedelim_get(t_jit_print *x, void *attr, long *ac, t_atom **av);
void jit_print_coldelim_set(t_jit_print *x, t_symbol *s, long ac, t_atom *av);
t_jit_err jit_print_coldelim_get(t_jit_print *x, void *attr, long *ac, t_atom **av);
void jit_print_rowdelim_set(t_jit_print *x, t_symbol *s, long ac, t_atom *av);
t_jit_err jit_print_rowdelim_get(t_jit_print *x, void *attr, long *ac, t_atom **av);

void *_jit_print_class;
t_symbol *ps_null;
t_symbol *ps_tab;
t_symbol *ps_cr;
t_symbol *ps_space;

t_jit_err jit_print_init(void)
{
	long attrflags=0;
	t_jit_object *attr;
	t_jit_object *mop;

	_jit_print_class = jit_class_new("jit_print",(method)jit_print_new,(method)jit_print_free,
									 sizeof(t_jit_print),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,1,1);
	jit_class_addadornment(_jit_print_class,mop);
	//add methods
	jit_class_addmethod(_jit_print_class, (method)jit_print_matrix_calc, "matrix_calc", A_CANT, 0L);

	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"precision",_jit_sym_char,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_print,precision));
	jit_attr_addfilterset_clip(attr,0,0,TRUE,FALSE);	//clip to 0-x
	jit_class_addattr(_jit_print_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Precision");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"fieldwidth",_jit_sym_char,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_print,fieldwidth));
	jit_attr_addfilterset_clip(attr,0,0,TRUE,FALSE);	//clip to 0-x
	jit_class_addattr(_jit_print_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Field Width\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"mode",_jit_sym_char,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_print,mode));
	jit_attr_addfilterset_clip(attr,0,2,TRUE,TRUE);	//clip to 0-2
	jit_class_addattr(_jit_print_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Mode");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"zeropad",_jit_sym_char,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_print,zeropad));
	jit_attr_addfilterset_clip(attr,0,1,TRUE,TRUE);	//clip to 0-1
	jit_class_addattr(_jit_print_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Zero Pad\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"planedelim",_jit_sym_symbol,attrflags,
						  (method)jit_print_planedelim_get,(method)jit_print_planedelim_set,0L);
	jit_class_addattr(_jit_print_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Plane Delimiter\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"coldelim",_jit_sym_symbol,attrflags,
						  (method)jit_print_coldelim_get,(method)jit_print_coldelim_set,0L);
	jit_class_addattr(_jit_print_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Column Delimiter\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"rowdelim",_jit_sym_symbol,attrflags,
						  (method)jit_print_rowdelim_get,(method)jit_print_rowdelim_set,0L);
	jit_class_addattr(_jit_print_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Row Delimiter\"");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"title",_jit_sym_symbol,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_print, title));
	jit_class_addattr(_jit_print_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Title");
	
	attr = jit_object_new(_jit_sym_jit_attr_offset,"info",_jit_sym_char,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_print, info));
	jit_attr_addfilterset_clip(attr,0,2,TRUE,TRUE);	//clip to 0-1
	jit_class_addattr(_jit_print_class,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Info");
	

	jit_class_register(_jit_print_class);
	ps_null = gensym("");
	ps_tab = gensym("tab");
	ps_cr = gensym("cr");
	ps_space = gensym("space");

	return JIT_ERR_NONE;
}

void jit_print_rowdelim_set(t_jit_print *x, t_symbol *s, long ac, t_atom *av)
{
	t_symbol *tempsym;
	char str[2];

	if (ac) {
		tempsym = jit_atom_getsym(av);
		if (tempsym->s_name[0] == '-' || tempsym->s_name[0] == '.' || tempsym->s_name[0] == '\0') {
			jit_object_post((t_object *)x,"illegal delimiter");
			return;
		}

		if (tempsym == ps_tab)
			str[0] = '\t';
		else if (tempsym == ps_cr)
			str[0] = '\r';
		else if (tempsym == ps_space)
			str[0] = 32;
		else
			str[0] = tempsym->s_name[0];

		str[1] = 0;
		x->rowdelim = gensym(str);
	}
}

t_jit_err jit_print_rowdelim_get(t_jit_print *x, void *attr, long *ac, t_atom **av)
{
	char temp[2] = "";
	char *tmp = temp;
	t_symbol *tempsym;

	if ((*ac)&&(*av)) {
		;
	} else {
		*ac = 1;
		if (!(*av=jit_getbytes(sizeof(t_atom) * (*ac)))) {
			*ac = 0;
			return JIT_ERR_OUT_OF_MEM;
		}
	}

	temp[0] = x->rowdelim->s_name[0];

	if (temp[0] == '\t')
		tempsym = ps_tab;
	else if (temp[0] == '\r')
		tempsym = ps_cr;
	else if (temp[0] == 32)
		tempsym = ps_space;
	else
		tempsym = gensym(tmp);

	jit_atom_setsym(*av, tempsym);
	return JIT_ERR_NONE;
}

void jit_print_coldelim_set(t_jit_print *x, t_symbol *s, long ac, t_atom *av)
{
	t_symbol *tempsym;
	char str[2];

	if (ac) {
		tempsym = jit_atom_getsym(av);
		if (tempsym->s_name[0] == '-' || tempsym->s_name[0] == '.' || tempsym->s_name[0] == '\0') {
			jit_object_post((t_object *)x,"illegal delimiter");
			return;
		}

		if (tempsym == ps_tab)
			str[0] = '\t';
		else if (tempsym == ps_cr)
			str[0] = '\r';
		else if (tempsym == ps_space)
			str[0] = 32;
		else
			str[0] = tempsym->s_name[0];

		str[1] = 0;
		x->coldelim = gensym(str);
	}
}

t_jit_err jit_print_coldelim_get(t_jit_print *x, void *attr, long *ac, t_atom **av)
{
	char temp[2] = "";
	char *tmp = temp;
	t_symbol *tempsym;

	if ((*ac)&&(*av)) {
		;
	} else {
		*ac = 1;
		if (!(*av=jit_getbytes(sizeof(t_atom) * (*ac)))) {
			*ac = 0;
			return JIT_ERR_OUT_OF_MEM;
		}
	}

	temp[0] = x->coldelim->s_name[0];

	if (temp[0] == '\t')
		tempsym = ps_tab;
	else if (temp[0] == '\r')
		tempsym = ps_cr;
	else if (temp[0] == 32)
		tempsym = ps_space;
	else
		tempsym = gensym(tmp);

	jit_atom_setsym(*av, tempsym);
	return JIT_ERR_NONE;
}

void jit_print_planedelim_set(t_jit_print *x, t_symbol *s, long ac, t_atom *av)
{
	t_symbol *tempsym;
	char str[2];

	if (ac) {
		tempsym = jit_atom_getsym(av);
		if (tempsym->s_name[0] == '-' || tempsym->s_name[0] == '.' || tempsym->s_name[0] == '\0') {
			jit_object_post((t_object *)x,"illegal delimiter");
			return;
		}

		if (tempsym == ps_tab)
			str[0] = '\t';
		else if (tempsym == ps_cr)
			str[0] = '\r';
		else if (tempsym == ps_space)
			str[0] = 32;
		else
			str[0] = tempsym->s_name[0];

		str[1] = 0;
		x->planedelim = gensym(str);
	}
}

t_jit_err jit_print_planedelim_get(t_jit_print *x, void *attr, long *ac, t_atom **av)
{
	char temp[2] = "";
	char *tmp = temp;
	t_symbol *tempsym;

	if ((*ac)&&(*av)) {
		;
	} else {
		*ac = 1;
		if (!(*av=jit_getbytes(sizeof(t_atom) * (*ac)))) {
			*ac = 0;
			return JIT_ERR_OUT_OF_MEM;
		}
	}

	temp[0] = x->planedelim->s_name[0];

	if (temp[0] == '\t')
		tempsym = ps_tab;
	else if (temp[0] == '\r')
		tempsym = ps_cr;
	else if (temp[0] == 32)
		tempsym = ps_space;
	else
		tempsym = gensym(tmp);

	jit_atom_setsym(*av, tempsym);
	return JIT_ERR_NONE;
}

t_jit_err jit_print_matrix_calc(t_jit_print *x, void *in_matrix)
{
	long err = JIT_ERR_NONE, i;
	t_jit_matrix_info info;
	long dimcount, dim[JIT_MATRIX_MAX_DIMCOUNT];
	char *bip;
	long savelock;
	char titleblock[BYTE_WRITE_COUNT] = "";
	char *titleptr = titleblock;
	char appendblock[BYTE_WRITE_COUNT] = "";
	char *appendptr = appendblock;

	if (x && in_matrix) {
		savelock = (long) jit_object_method(in_matrix, _jit_sym_lock, 1);
		jit_object_method(in_matrix, _jit_sym_getinfo, &info);
		jit_object_method(in_matrix, _jit_sym_getdata, &bip);

		if (!bip) { err=JIT_ERR_INVALID_INPUT; goto out;}

		for (i = 0; i < info.dimcount; i++) {
			dim[i] = info.dim[i];
		}
		dimcount = info.dimcount;

		if (x->title != ps_null && x->info) {
			sprintf(titleptr, "%s - %d %s %d", x->title->s_name, info.planecount, info.type->s_name, dim[0]);
			for (i = 1; i < dimcount; i++) {
				sprintf(appendptr, "x%d", dim[i]);
				if (strlen(titleptr) + strlen(appendptr) < BYTE_WRITE_COUNT)
					strcat(titleptr, appendptr);
			}
			jit_object_post((t_object *)x,"%s", titleptr);
		}
		else if (x->info) {
			sprintf(titleptr, "%d %s %d", info.planecount, info.type->s_name, dim[0]);
			for (i = 1; i < dimcount; i++) {
				sprintf(appendptr, "x%d", dim[i]);
				if (strlen(titleptr) + strlen(appendptr) < BYTE_WRITE_COUNT)
					strcat(titleptr, appendptr);
			}
			jit_object_post((t_object *)x,"%s", titleptr);
		}
		else if (x->title != ps_null) {
			sprintf(titleptr, "%s", x->title->s_name);
			jit_object_post((t_object *)x,"%s", titleptr);
		}

		if (x->info != 2) {
			x->write_cherry = true;
			if (err = jit_print_write_print_ndim(x, dimcount, dim, &info, bip))
				jit_object_post((t_object *)x,"error %d printing to Max window", err);
		}
		jit_object_post((t_object *)x,"");

out:
		jit_object_method(in_matrix, _jit_sym_lock, savelock);
	}
	else {
		err = JIT_ERR_INVALID_PTR;
	}
	return err;
}

t_jit_err jit_print_write_print_ndim(t_jit_print *x, long dimcount, long *dim, t_jit_matrix_info *info, char *bip)
{
	uchar *ip;
	long i;
	char tmp_string[256] = ""; // large in case of mutability in the future
	char *tmp = tmp_string;
	t_jit_err err = JIT_ERR_NONE;

	if (dimcount<1) return err; //safety

	if (!x->write_cherry) {
		sprintf(tmp, "<DIM %d>\r", dimcount);
		jit_object_post((t_object *)x,"%s", tmp);
	}
	switch(dimcount) {
	case 1:
		dim[1]=1;
	case 2:
		if (info->type == _jit_sym_char) // these functions located in m2t.c
			err = jit_print_packtext_char(x, dim, info, bip);
		else if (info->type == _jit_sym_long)
			err = jit_print_packtext_long(x, dim, info, bip);
		else if (info->type == _jit_sym_float32)
			err = jit_print_packtext_float32(x, dim, info, bip);
		else if (info->type == _jit_sym_float64)
			err = jit_print_packtext_float64(x, dim, info, bip);
		break;
	default:
		for	(i = 0; i < dim[dimcount-1]; i++) {
			ip = bip + i * info->dimstride[dimcount-1];
			jit_print_write_print_ndim(x, dimcount-1, dim, info, ip);
		}
	}
	return err;
}

t_jit_err jit_print_packtext_char(t_jit_print *x, long *dim, t_jit_matrix_info *info, char *bip)
{
	long i, j, k, width, height, planecount;
	char rowdelim = x->rowdelim->s_name[0];
	char coldelim = x->coldelim->s_name[0];
	char planedelim = x->planedelim->s_name[0];
	char dimdelim = x->dimdelim->s_name[0];
	char delimchar;
	uchar *ip;
	long tmp, err = 0;
	char tmp1_string[BYTE_WRITE_COUNT + 1] = "";
	char tmp2_string[BYTE_WRITE_COUNT + 1] = "";
	char *tmp1;
	char *tmp2;
	char fieldwidth = x->fieldwidth;

	width = dim[0];
	height = dim[1];
	planecount = info->planecount;

	tmp1 = tmp1_string;
	tmp2 = tmp2_string;

	x->write_cherry = false;

	for (i = 0; i < height; i++) {
		ip = (uchar *)(bip + i * info->dimstride[1]);
		for (j = 0; j < width; j++) {
			delimchar = planedelim;
			for (k = 0; k < planecount - 1; k++) {
				tmp = *ip;
				if (!k) {
					switch(x->mode) {
					case 1: // hex
						if (x->zeropad)
							sprintf(tmp2, " %0*X%c", fieldwidth, tmp, delimchar);
						else
							sprintf(tmp2, " %*X%c", fieldwidth, tmp, delimchar);
						break;
					case 2: // char
						sprintf(tmp2, " %c%c", tmp, delimchar);
						break;
					case 0: // normal
					default:
						if (x->zeropad)
							sprintf(tmp2, " %0*ld%c", fieldwidth, tmp, delimchar);
						else
							sprintf(tmp2, " %*ld%c", fieldwidth, tmp, delimchar);
						break;
					}
				}
				else {
					switch(x->mode) {
					case 1:
						if (x->zeropad)
							sprintf(tmp2, "%0*X%c", fieldwidth, tmp, delimchar);
						else
							sprintf(tmp2, "%*X%c", fieldwidth, tmp, delimchar);
						break;
					case 2:
						sprintf(tmp2, "%c%c", tmp, delimchar);
						break;
					case 0:
					default:
						if (x->zeropad)
							sprintf(tmp2, "%0*ld%c", fieldwidth, tmp, delimchar);
						else
							sprintf(tmp2, "%*ld%c", fieldwidth, tmp, delimchar);
						break;
					}
				}
				if (strlen(tmp2) + strlen(tmp1) < BYTE_WRITE_COUNT) { // leave room for dim term
					tmp1 = strcat(tmp1, tmp2);
					ip++;
				}
				else {
					jit_object_post((t_object *)x,"%s", tmp1);
					jit_object_post((t_object *)x,"(line truncated)");
					tmp1_string[0] = '\0';
					tmp2_string[0] = '\0';
					goto bah;
				}
			}
			if (j < width - 1)
				delimchar = coldelim;
			else delimchar = rowdelim;
			tmp = *ip;
			switch (x->mode) {
			case 1:
				if (x->zeropad)
					sprintf(tmp2, "%0*X%c", fieldwidth, tmp, delimchar);
				else
					sprintf(tmp2, "%*X%c", fieldwidth, tmp, delimchar);
				break;
			case 2:
				sprintf(tmp2, "%c%c", tmp, delimchar);
				break;
			case 0:
			default:
				if (x->zeropad)
					sprintf(tmp2, "%0*ld%c", fieldwidth, tmp, delimchar);
				else
					sprintf(tmp2, "%*ld%c", fieldwidth, tmp, delimchar);
				break;
			}
			if (strlen(tmp2) + strlen(tmp1) < BYTE_WRITE_COUNT) {
				tmp1 = strcat(tmp1, tmp2);
				ip++;
			}
			else {
				jit_object_post((t_object *)x,"%s", tmp1);
				jit_object_post((t_object *)x,"(line truncated)");
				tmp1_string[0] = '\0';
				tmp2_string[0] = '\0';
				goto bah;
			}
		}
		jit_object_post((t_object *)x,"%s", tmp1);
		tmp1_string[0] = '\0';
		tmp2_string[0] = '\0';
bah:
		;
	}
	return err;
}

t_jit_err jit_print_packtext_long(t_jit_print *x, long *dim, t_jit_matrix_info *info, char *bip)
{
	long i, j, k, width, height, planecount;
	char rowdelim = x->rowdelim->s_name[0];
	char coldelim = x->coldelim->s_name[0];
	char planedelim = x->planedelim->s_name[0];
	char dimdelim = x->dimdelim->s_name[0];
	char delimchar;
	t_int32 *ip;
	long tmp, err = 0;
	char tmp1_string[BYTE_WRITE_COUNT + 1] = "";
	char tmp2_string[BYTE_WRITE_COUNT + 1] = "";
	char *tmp1;
	char *tmp2;
	char fieldwidth = x->fieldwidth;

	width = dim[0];
	height = dim[1];
	planecount = info->planecount;

	tmp1 = tmp1_string;
	tmp2 = tmp2_string;

	x->write_cherry = false;

	for (i = 0; i < height; i++) {
		ip = (t_int32 *)(bip + i * info->dimstride[1]);
		for (j = 0; j < width; j++) {
			delimchar = planedelim;
			for (k = 0; k < planecount - 1; k++) {
				tmp = *ip;
				if (!k) {
					if (x->mode) {
						if (x->zeropad)
							sprintf(tmp2, " %0*X%c", fieldwidth, tmp, delimchar);
						else
							sprintf(tmp2, " %*X%c", fieldwidth, tmp, delimchar);
					}
					else {
						if (x->zeropad)
							sprintf(tmp2, " %0*ld%c", fieldwidth, tmp, delimchar);
						else
							sprintf(tmp2, " %*ld%c", fieldwidth, tmp, delimchar);
					}
				}
				else {
					if (x->mode) {
						if (x->zeropad)
							sprintf(tmp2, "%0*X%c", fieldwidth, tmp, delimchar);
						else
							sprintf(tmp2, "%*X%c", fieldwidth, tmp, delimchar);
					}
					else {
						if (x->zeropad)
							sprintf(tmp2, "%0*ld%c", fieldwidth, tmp, delimchar);
						else
							sprintf(tmp2, "%*ld%c", fieldwidth, tmp, delimchar);
					}
				}
				if (strlen(tmp2) + strlen(tmp1) < BYTE_WRITE_COUNT) { // leave room for dim term
					tmp1 = strcat(tmp1, tmp2);
					ip++;
				}
				else {
					jit_object_post((t_object *)x,"%s", tmp1);
					jit_object_post((t_object *)x,"(line truncated)");
					tmp1_string[0] = '\0';
					tmp2_string[0] = '\0';
					break;
				}
			}
			if (j < width - 1)
				delimchar = coldelim;
			else delimchar = rowdelim;
			tmp = *ip;
			if (x->mode) {
				if (x->zeropad)
					sprintf(tmp2, "%0*X%c", fieldwidth, tmp, delimchar);
				else
					sprintf(tmp2, "%*X%c", fieldwidth, tmp, delimchar);
			}
			else {
				if (x->zeropad)
					sprintf(tmp2, "%0*ld%c", fieldwidth, tmp, delimchar);
				else
					sprintf(tmp2, "%*ld%c", fieldwidth, tmp, delimchar);
			}
			if (strlen(tmp2) + strlen(tmp1) < BYTE_WRITE_COUNT) {
				tmp1 = strcat(tmp1, tmp2);
				ip++;
			}
			else {
				jit_object_post((t_object *)x,"%s", tmp1);
				jit_object_post((t_object *)x,"(line truncated)");
				tmp1_string[0] = '\0';
				tmp2_string[0] = '\0';
				continue;
			}
		}
		jit_object_post((t_object *)x,"%s", tmp1);
		tmp1_string[0] = '\0';
		tmp2_string[0] = '\0';
	}
	return err;
}

t_jit_err jit_print_packtext_float32(t_jit_print *x, long *dim, t_jit_matrix_info *info, char *bip)
{
	long i, j, k, width, height, planecount;
	char rowdelim = x->rowdelim->s_name[0];
	char coldelim = x->coldelim->s_name[0];
	char planedelim = x->planedelim->s_name[0];
	char dimdelim = x->dimdelim->s_name[0];
	char delimchar;
	float *ip;
	double tmp;
	long err = 0;
	char tmp1_string[BYTE_WRITE_COUNT + 1] = "";
	char tmp2_string[BYTE_WRITE_COUNT + 1] = "";
	char *tmp1;
	char *tmp2;
	char precision = x->precision;
	char fieldwidth = x->fieldwidth;

	width = dim[0];
	height = dim[1];
	planecount = info->planecount;

	tmp1 = tmp1_string;
	tmp2 = tmp2_string;

	x->write_cherry = false;

	for (i = 0; i < height; i++) {
		ip = (float *)(bip + i * info->dimstride[1]);
		for (j = 0; j < width; j++) {
			delimchar = planedelim;
			for (k = 0; k < planecount - 1; k++) {
				tmp = (double)*ip;
				if (!k)
					sprintf(tmp2, "% *.*f%c", fieldwidth, precision, tmp, delimchar);
				else
					sprintf(tmp2, "%*.*f%c", fieldwidth, precision, tmp, delimchar);
				if (strlen(tmp2) + strlen(tmp1) < BYTE_WRITE_COUNT) { // leave room for dim term
					tmp1 = strcat(tmp1, tmp2);
					ip++;
				}
				else {
					jit_object_post((t_object *)x,"%s", tmp1);
					jit_object_post((t_object *)x,"(line truncated)");
					tmp1_string[0] = '\0';
					tmp2_string[0] = '\0';
					break;
				}
			}
			if (j < width - 1)
				delimchar = coldelim;
			else delimchar = rowdelim;
			tmp = (double)*ip;
			sprintf(tmp2, "%*.*f%c", fieldwidth, precision, tmp, delimchar);
			if (strlen(tmp2) + strlen(tmp1) < BYTE_WRITE_COUNT) {
				tmp1 = strcat(tmp1, tmp2);
				ip++;
			}
			else {
				jit_object_post((t_object *)x,"%s", tmp1);
				jit_object_post((t_object *)x,"(line truncated)");
				tmp1_string[0] = '\0';
				tmp2_string[0] = '\0';
				continue;
			}
		}
		jit_object_post((t_object *)x,"%s", tmp1);
		tmp1_string[0] = '\0';
		tmp2_string[0] = '\0';
	}
	return err;
}

t_jit_err jit_print_packtext_float64(t_jit_print *x, long *dim, t_jit_matrix_info *info, char *bip)
{
	long i, j, k, width, height, planecount;
	char rowdelim = x->rowdelim->s_name[0];
	char coldelim = x->coldelim->s_name[0];
	char planedelim = x->planedelim->s_name[0];
	char dimdelim = x->dimdelim->s_name[0];
	char delimchar;
	double *ip;
	double tmp;
	long err = 0;
	char tmp1_string[BYTE_WRITE_COUNT + 1] = "";
	char tmp2_string[BYTE_WRITE_COUNT + 1] = "";
	char *tmp1;
	char *tmp2;
	char precision = x->precision;
	char fieldwidth = x->fieldwidth;

	width = dim[0];
	height = dim[1];
	planecount = info->planecount;

	tmp1 = tmp1_string;
	tmp2 = tmp2_string;

	x->write_cherry = false;

	for (i = 0; i < height; i++) {
		ip = (double *)(bip + i * info->dimstride[1]);
		for (j = 0; j < width; j++) {
			delimchar = planedelim;
			for (k = 0; k < planecount - 1; k++) {
				tmp = (double)*ip;
				if (!k)
					sprintf(tmp2, "% *.*f%c", fieldwidth, precision, tmp, delimchar);
				else
					sprintf(tmp2, "%*.*f%c", fieldwidth, precision, tmp, delimchar);
				if (strlen(tmp2) + strlen(tmp1) < BYTE_WRITE_COUNT) { // leave room for dim term
					tmp1 = strcat(tmp1, tmp2);
					ip++;
				}
				else {
					jit_object_post((t_object *)x,"%s", tmp1);
					jit_object_post((t_object *)x,"(line truncated)");
					tmp1_string[0] = '\0';
					tmp2_string[0] = '\0';
					break;
				}
			}
			if (j < width - 1)
				delimchar = coldelim;
			else delimchar = rowdelim;
			tmp = (double)*ip;
			sprintf(tmp2, "%*.*f%c", fieldwidth, precision, tmp, delimchar);
			if (strlen(tmp2) + strlen(tmp1) < BYTE_WRITE_COUNT) {
				tmp1 = strcat(tmp1, tmp2);
				ip++;
			}
			else {
				jit_object_post((t_object *)x,"%s", tmp1);
				jit_object_post((t_object *)x,"(line truncated)");
				tmp1_string[0] = '\0';
				tmp2_string[0] = '\0';
				continue;
			}
		}
		jit_object_post((t_object *)x,"%s", tmp1);
		tmp1_string[0] = '\0';
		tmp2_string[0] = '\0';
	}
	return err;
}


t_jit_print *jit_print_new(void)
{
	t_jit_print *x;
	char tmpstr[2] = "";
	char *tmpptr = tmpstr;

	if (x=(t_jit_print *)jit_object_alloc(_jit_print_class)) {
		x->write_cherry = true;
		tmpstr[0] = PLANE_DELIM;
		x->planedelim = gensym(tmpptr);
		tmpstr[0] = ROW_DELIM;
		x->rowdelim = gensym(tmpptr);
		tmpstr[0] = COL_DELIM;
		x->coldelim = gensym(tmpptr);
		tmpstr[0] = DIM_DELIM;
		x->dimdelim = gensym(tmpptr);

		x->precision = 3;
		x->fieldwidth = 3;
		x->mode = 0;
		x->zeropad = 0;

		x->info = 0;
		x->title = ps_null;

	} else {
		x = NULL;
	}
	return x;
}

void jit_print_free(t_jit_print *x)
{
	//nada
}
