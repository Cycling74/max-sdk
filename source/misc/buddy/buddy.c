#include "ext.h"
#include "ext_obex.h"

/**
	@file
	buddy.c --- data flow management object

	updated 3/15/09 ajm: new API
	updated 5/18/92 ddz: to use proxies,
	event num synchonization, and any
	number of inlets

	@ingroup	examples
*/

typedef struct {
	void *m_proxy;
	void *m_out;
	short m_argc;
	t_atom m_argv[128];
	short m_on;
} t_member;

typedef struct {
	t_object b_ob;
	long b_num;
	t_member *b_mem;
	long b_id;
} t_buddy;

void buddy_bang(t_buddy *x);
void buddy_anything(t_buddy *x, t_symbol *s, short argc, t_atom *argv);
void buddy_float(t_buddy *x,double f);
void buddy_int(t_buddy *x,long n);
void buddy_list(t_buddy *x, t_symbol *s, short argc, t_atom *argv);
void buddy_atom(t_buddy *x, t_atom *a);
short buddy_all(t_buddy *x);
void buddy_off(t_buddy *x);
void buddy_out(t_buddy *x);
void outlet_member(void *out, short argc, t_atom *argv);
void buddy_assist(t_buddy *x, void *b, long m, long a, char *s);
void buddy_inletinfo(t_buddy *x, void *b, long a, char *t);
void buddy_free(t_buddy *x);
void *buddy_new(long num);
void buddy_clear(t_buddy *x);

void *buddy_class;
t_symbol *ps_list;

void ext_main(void *r)
{
	t_class *c;

	c = class_new("buddy", (method)buddy_new, (method)buddy_free, sizeof(t_buddy), 0L, A_DEFLONG, 0);

	class_addmethod(c, (method)buddy_bang,		"bang",		0);
	class_addmethod(c, (method)buddy_int,		"int",		A_LONG, 0);
	class_addmethod(c, (method)buddy_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)buddy_list,		"list",		A_GIMME, 0);
	class_addmethod(c, (method)buddy_clear,		"clear",	0);
	class_addmethod(c, (method)buddy_anything,	"anything", A_GIMME, 0);
	class_addmethod(c, (method)buddy_assist,	"assist",	A_CANT, 0);
	class_addmethod(c, (method)buddy_inletinfo,	"inletinfo",A_CANT, 0);

	class_register(CLASS_BOX, c);
	buddy_class = c;

	ps_list = gensym("list");

	return 0;
}

void buddy_bang(t_buddy *x)
{
	buddy_int(x,0L);
}

void buddy_clear(t_buddy *x)
{
	buddy_off(x);
}

void buddy_anything(t_buddy *x, t_symbol *s, short argc, t_atom *argv)
{
	t_member *m;
	long in = proxy_getinlet((t_object *)x);

	m = x->b_mem + in;
	m->m_on = TRUE;
	atom_setsym(&m->m_argv[0], s);
	if (argc > 127)
		argc = 127;
	m->m_argc = argc + 1;
	sysmem_copyptr(argv,m->m_argv+1,argc * sizeof(t_atom));
	if (buddy_all(x)) {
		buddy_off(x);
		buddy_out(x);
	}
}

void buddy_list(t_buddy *x, t_symbol *s, short argc, t_atom *argv)
{
	buddy_anything(x,ps_list,argc,argv);
}

void buddy_float(t_buddy *x, double f)
{
	t_atom a;
	atom_setfloat(&a, f);
	buddy_atom(x,&a);
}

void buddy_int(t_buddy *x, long n)
{
	t_atom a;
	atom_setlong(&a, n);
	buddy_atom(x,&a);
}

void buddy_atom(t_buddy *x, t_atom *a)
{
	t_member *m;
	long in = proxy_getinlet((t_object *)x);

	m = x->b_mem + in;
	m->m_on = true;
	m->m_argc = 1;
	m->m_argv[0] = *a;
	if (buddy_all(x)) {
		buddy_off(x);
		buddy_out(x);
	}
}

short buddy_all(t_buddy *x)
{
	short i;
	t_member *m;

	for (i=0,m = x->b_mem; i < x->b_num; i++,m++)
		if (!m->m_on)
			return false;
	return true;
}

void buddy_off(t_buddy *x)
{
	short i;
	t_member *m;

	for (i=0,m = x->b_mem; i < x->b_num; i++,m++)
		m->m_on = 0;
}

void buddy_out(t_buddy *x)
{
	short i;
	t_member *m;

	for (i=x->b_num-1,m = x->b_mem+i; i >= 0; i--,m--)
		outlet_member(m->m_out,m->m_argc,m->m_argv);
}

void outlet_member(void *out, short argc, t_atom *argv)
{
	if (argc == 1) {
		switch (atom_gettype(argv)) {
		case A_LONG:
			outlet_int(out,atom_getlong(argv));
			break;
		case A_FLOAT:
			outlet_float(out,atom_getfloat(argv));
			break;
		case A_SYM:
			outlet_anything(out,atom_getsym(argv),0,0L);
			break;
		}
	} else if (atom_getsym(argv) == ps_list)
		outlet_list(out,ps_list,argc-1,argv+1);
	else
		outlet_anything(out,atom_getsym(argv),argc-1,argv+1);
}

void buddy_assist(t_buddy *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
		sprintf(s,"Input to be Synchronized");
	else
		sprintf(s,"Synchronized Output of Inlet %ld", a+1);
}

void buddy_inletinfo(t_buddy *x, void *b, long a, char *t)
{
	/*
	 *	red if every  input - 1 has been set and you're looking to the one which will trigger
	 */
	long i, count;
	t_member *m, *m2;

	for (i = count = 0, m = x->b_mem; i < x->b_num; i++, m++) {
		if (i == a)
			m2 = m;
		if (m->m_on)
			count++;
	}

	if (count >= (x->b_num - 1) && ! m2->m_on)
		*t = 0;
	else
		*t = 1;
}

void buddy_free(t_buddy *x)
{
	short i;

	for (i=1; i < x->b_num; i++)
		object_free(x->b_mem[i].m_proxy);
	sysmem_freeptr(x->b_mem);
}

void *buddy_new(long num)
{
	t_buddy *x;
	short i;
	t_member *m;

	x = (t_buddy *)object_alloc(buddy_class);
	if (num < 2)
		num = 2;
	x->b_num = num;
	x->b_id = 0;
	x->b_mem = (t_member *)sysmem_newptr((unsigned short)(num * sizeof(t_member)));
	for (i=num-1,m = x->b_mem + i; i >= 0; i--,m--) {
		if (i)
			m->m_proxy = proxy_new(x,(long)i,&x->b_id);
		m->m_out = outlet_new(x,0L);
		m->m_on = 0;
		m->m_argc = 1;
		atom_setlong(&m->m_argv[0], 0);
	}
	return x;
}

