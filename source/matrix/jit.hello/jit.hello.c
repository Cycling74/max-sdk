/*
	Copyright 2001 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"

typedef struct _jit_hello
{
	t_jit_object	ob;
	t_symbol		*text;
} t_jit_hello;

void *_jit_hello_class;

t_jit_err jit_hello_init(void);
void jit_hello_free(t_jit_hello *x);
t_jit_hello *jit_hello_new(t_symbol *s);

t_jit_err jit_hello_init(void)
{
	long attrflags=0;
	t_jit_object *attr;

	_jit_hello_class = jit_class_new("jit_hello",(method)jit_hello_new,(method)jit_hello_free,
									 sizeof(t_jit_hello),0L);

	//add attributes
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	attr = jit_object_new(_jit_sym_jit_attr_offset,"text",_jit_sym_symbol,attrflags,
						  (method)0L,(method)0L,calcoffset(t_jit_hello,text));
	jit_class_addattr(_jit_hello_class,attr);

	jit_class_register(_jit_hello_class);

	return JIT_ERR_NONE;
}

void jit_hello_free(t_jit_hello *x)
{
	//nada
}

t_jit_hello *jit_hello_new(t_symbol *s)
{
	t_jit_hello *x;

	if (x = (t_jit_hello *)jit_object_alloc(_jit_hello_class)) {
		x->text = s;
	}

	return x;
}
