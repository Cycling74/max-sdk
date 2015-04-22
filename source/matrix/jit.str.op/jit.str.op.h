#ifndef _jit_str_op_H_
#define _jit_str_op_H_

#include "jit.op.h"


#define JIT_STRING_MAX_LENGTH 2048
#define MAX_STRING_LENGTH 2048


typedef struct _jit_str_op
{
	t_object	ob;
	t_symbol	*opsym;
	long		outlong;
	long		outlong2;
	long		outmode;
	long		adaptflag;
	long		start[2]; // for slice
	long		startcount;
	long		end[2];
	long		endcount;
	char		multiline_in;
	char		multiline_out;
} t_jit_str_op;

typedef struct _jit_str_op_vecdata
{
	t_jit_op_fn	opfn;
	char		outputtype;
	long		in1_len;
	long		in2_len;
	long		start;
	long		end;
	long		outlong[2];
} t_jit_str_op_vecdata;

t_jit_err jit_str_op_matrix_calc(t_jit_str_op *x, void *inputs, void *outputs);

void jit_str_op_strcat (long n, t_jit_str_op_vecdata *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out);//, long *outlong);
void jit_str_op_slice (long n, t_jit_str_op_vecdata *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out);//, long *outlong);
void jit_str_op_strrev(long n, t_jit_str_op_vecdata *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out);//, long *outlong);
void jit_str_op_strcmp (long n, t_jit_str_op_vecdata *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out);//, long *outlong);
void jit_str_op_strlen (long n, t_jit_str_op_vecdata *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out);//, long *outlong);
void jit_str_op_toupper (long n, t_jit_str_op_vecdata *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out);//, long *outlong);
void jit_str_op_tolower (long n, t_jit_str_op_vecdata *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out);//, long *outlong);
void jit_str_op_thru (long n, t_jit_str_op_vecdata *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out);//, long *outlong);
void jit_str_op_expand(t_jit_str_op *x, void *out_matrix, const char *buf);
void jit_str_op_packmatrix(t_jit_str_op *x, long dimcount, long *dim,  t_jit_matrix_info *info, char *bop, const char *buf);
void jit_str_op_read_char(t_jit_str_op *x, long *dim, t_jit_matrix_info *info, char *bop, const char *buf);
char *jit_str_op_tostring(t_jit_str_op *x, long dimcount, long *dim, long rowstride, char *bip, t_bool *slice);
void jit_str_op_start_set(t_jit_str_op *x, void *attr, long ac, t_atom *av);
void jit_str_op_end_set(t_jit_str_op *x, void *attr, long ac, t_atom *av);


long jit_str_op_checklen(long n, t_jit_op_info *in1);
void jit_str_op_vector_ignore(long n, void *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out);
method jit_str_op_sym2fn(t_symbol *opsym);

#endif