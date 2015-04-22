#include "jit.common.h"
#include "jit.str.op.h"

void jit_str_op_strcat (long n, t_jit_str_op_vecdata *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out)//, long *outlong)
{
	char *s1, *s2, *os;
	long in1_len, in2_len;

	vecdata->outputtype = 0;
	s1 = in1->p;
	s2 = in2->p;
	os = out->p;
	in1_len = vecdata->in1_len;
	in2_len = vecdata->in2_len;

	while (in1_len-- && n--) {
		if (!(*os++ = *s1++))
			goto boot;
	}
	while (in2_len-- && n--) {
		if (!(*os++ = *s2++))
			goto boot;
	}

	if (n)
		*os = 0;
	return;

boot:
	error("jit.str.op: there was a problem reading a string");
}

void jit_str_op_slice (long n, t_jit_str_op_vecdata *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out)//, long *outlong)
{
	char *s1, *os;
	long start, end, i;

	start = vecdata->start;
	end = vecdata->end;
	vecdata->outputtype = 0;
	s1 = in1->p;
	os = out->p;

	if (end - start == 0 && n--) {
		*os++ = *(s1 + start);
	}
	else if (end - start > 0) {
		for (i = start; i <= end && n--; i++)
			*os++ = *(s1 + i);
	}
	else {
		for (i = start; i >= end && n--; i--)
			*os++ = *(s1 + i);
	}

	if (n)
		*os = 0;
}

void jit_str_op_strrev(long n, t_jit_str_op_vecdata *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out)//, long *outlong)
{
	char *s1, *os;
	long start, end, i;

	start = vecdata->in1_len - 1;
	vecdata->outputtype = 0;
	s1 = in1->p;
	os = out->p;

	for (i = start; i >= 0 && n--; i--)
		*os++ = *(s1 + i);

	if (n)
		*os = 0;
}

void jit_str_op_strcmp(long n, t_jit_str_op_vecdata *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out)//, long *outlong)
{
	char c1, c2, dif;
	char *s1, *s2;
	long len, i;

	vecdata->outputtype = 2;
	s1 = in1->p;
	s2 = in2->p;
	len = MIN(vecdata->in1_len, vecdata->in2_len);

	for (i = 0; i < len; i++) {
		if (s1[i] == s2[i]) {
			if (s1[i] == 0) {
				vecdata->outlong[0] = 0;
//				*outlong = 0;
				goto out;
			}
		}
		else {
			vecdata->outlong[0] = s1[i] - s2[i];
//			*outlong = s1[i] - s2[i];
			goto out;
		}
	}

	if (vecdata->in1_len == vecdata->in2_len)
		vecdata->outlong[0] = 0;
//		*outlong = 0;
	else if (vecdata->in1_len > vecdata->in2_len)
		vecdata->outlong[0] = s1[i];
//		*outlong = s1[i];
	else
		vecdata->outlong[0] = -(s2[i]);
//		*outlong = -(s2[i]);

out:
	vecdata->outlong[1] = i;
}

void jit_str_op_strlen (long n, t_jit_str_op_vecdata *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out)//, long *outlong)
{
	char *s1;
	long i=0;

	vecdata->outputtype = 1;
	s1 = in1->p;
	vecdata->outlong[0] = vecdata->in1_len;
//	*outlong = vecdata->in1_len;
}

void jit_str_op_toupper (long n, t_jit_str_op_vecdata *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out)//, long *outlong)
{
	char *s, *os;

	vecdata->outputtype = 0;

	s = in1->p;
	os = out->p;

	while (n--) {
		if ((*s >= 97) && (*s <= 122))
			*os++ = *s++ - 32;
		else {
			if (*os++ = *s++) ;
			else break;
		}
	}

	if (n)
		*os = 0;
}


void jit_str_op_tolower (long n, t_jit_str_op_vecdata *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out)//, long *outlong)
{
	char *s, *os;

	vecdata->outputtype = 0;

	s = in1->p;
	os = out->p;

	while (n--) {
		if ((*s >= 65) && (*s <= 90))
			*os++ = *s++ + 32;
		else {
			if (*os++ = *s++) ;
			else break;
		}
	}

	if (n)
		*os = 0;
}

void jit_str_op_thru (long n, t_jit_str_op_vecdata *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out)//, long *outlong)
{
	char *s, *os;
	long len;

	vecdata->outputtype = 0;
	len = vecdata->in1_len;

	s = in1->p;
	os = out->p;

	while (len-- && n--)
		*os++ = *s++;

	if (n)
		*os = 0;
}
/*
void jit_str_op_delim(long n, t_jit_str_op_vecdata *vecdata, t_jit_op_info *in1, t_jit_op_info *in2, t_jit_op_info *out, long *outlong)
{
	char *s, *os;
	long len;

	vecdata->outputtype = 1;
	len = vecdata->in1_len;



} */