/*
	Copyright 2001 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
*/

#include "jit.common.h"

typedef struct _max_jit_hello
{
	t_object 		ob;
	void			*obex;
} t_max_jit_hello;

t_messlist *class_max_jit_hello;

void max_jit_hello_assist(t_max_jit_hello *x, void *b, long m, long a, char *s);
void *max_jit_hello_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_hello_free(t_max_jit_hello *x);

//from jit.hello.c
t_jit_err jit_hello_init(void);

void ext_main(void *r)
{
	void *p,*q,*attr;
	long attrflags;

	jit_hello_init();
	setup(&class_max_jit_hello, max_jit_hello_new, (method)max_jit_hello_free, (short)sizeof(t_max_jit_hello),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_hello,obex));
	q = jit_class_findbyname(gensym("jit_hello"));
	max_jit_classex_standard_wrap(p,q,0);
	addmess((method)max_jit_hello_assist,		"assist",		A_CANT,0);
}

void max_jit_hello_assist(t_max_jit_hello *x, void *b, long m, long a, char *s)
{
	//nada for now
}

void max_jit_hello_free(t_max_jit_hello *x)
{
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_jit_hello_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_hello *x;
	long attrstart;
	t_symbol *text=gensym("Hello World!");
	void *o;

	if (x = (t_max_jit_hello *)max_jit_obex_new(class_max_jit_hello,gensym("jit_hello"))) {
		max_jit_obex_dumpout_set(x, outlet_new(x,0L)); //general purpose outlet(rightmost)

		//get normal args
		attrstart = max_jit_attr_args_offset(argc,argv);
		if (attrstart&&argv) {
			jit_atom_arg_getsym(&text, 0, attrstart, argv);
		}
		if (o=jit_object_new(gensym("jit_hello"),text)) {
			max_jit_obex_jitob_set(x,o);
		} else {
			freeobject((void *)x);
			x = NULL;
			jit_object_error((t_object *)x,"jit.hello: out of memory");
			goto out;
		}
	}

out:
	return (x);
}

