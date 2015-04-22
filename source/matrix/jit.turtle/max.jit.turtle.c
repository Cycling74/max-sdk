/*
	Copyright 2002-2005 - Cycling '74
	R. Luke DuBois luke@cycling74.com
*/

/*	jit.turtle emulates simple LOGO-style graphics.  it interprets single char values in its inlet as ASCII letters
 *  that describe turtle graphics commands.  a valid ASCII input will generate appropriate drawing commands for use with
 *  either the Max LCD object or the jit.lcd object (it potentially works with udraw and 242.qd as well).
 *
 *  jit.turtle supports branching (via the '[' and ']' symbols) up to a maximum stack size of 1024 nested branches.  while
 *  this is kind of neat by itself, it is most useful when used with automatic string generators (either Max patches or objects
 *  such as jit.linden).  ASCII codes which don't make any sense to jit.turtle are ignored.  symbols which the user wishes to
 *  bypass can be filtered out by placing a 'select' or 'route' object with the appropriate ASCII numbers between the
 *  source of the commands and the jit.turtle object.
 *
 *  while jit.turtle doesn't use jit matrices to store and generate data, it uses the jit attribute system to set and poll
 *  its internal state (origin, angle, scale, and clearmode are all jit attributes).  an ordinary 'turtle' Max object,
 *  which doesn't require jit to run, could be ported from this code with a minimum of fuss.
 *
 *  turtle graphics packages are fairly ubiquitous and some have conflicting syntaxes.  the turtle syntax used in this object
 *  is optimized for the visualization of Lindenmayer Systems (or L-systems), which tend to use the same bunch of commands.
 *  if the turtle you're used to has a different symbol table (e.g. penup/pendown independent of motion) or contains additional
 *  commands, you should be able to add them under the max_jit_turtle_int() function easily.  things like additional algorithmic
 *  support of variable angles and scaling (size of the steps in the 'forward' commands), polygon support (some turtle systems
 *  have automatic polygon generation using 'G', 'g', '{', and '}'), and QuickDraw colors would be kind of fun, i think.
 *
 */

/*
 *  if you were never subjected to turtle graphics in school (or elsewhere), the basic idea is this:
 *
 *  you are a turtle.  as if that weren't bad enough, you are also inhibited by only being able to turn and go forward in
 *  discrete amounts (you can also turn around).  however, to make up for this your creator has given you two very cool
 *  genetic advantages over the average reptile:
 *
 *  1) you have a limitless supply of ink which secretes from your tail (which is usually referred to as the PEN).  by dragging
 *  your tail along the floor as you move and turn you can therefore tell the entire world (or, at least, anyone who looks) all
 *  about how much it sucks to be a turtle.
 *
 *  2) you can make quantum jumps back and forth to geographical positions and bearings where you've been before (though, to be
 *  fair, you don't really know anything about those positions until you get there).  this is called BRANCHING, and it lets you,
 *  a mere turtle, draw some incredibly complex images.
 *
 *  as a turtle, your basic instruction set is the following (at least this is how i've implemented it):
 *
 *	you can...
 *
 *  - move forward a discrete amount with your tail down (drawing a line) -- the command for this is 'F'.
 *  - move forward a discrete amount with your tail up (changing your position without drawing ('f').
 *  - turn right ('+'), left ('-'), or around ('|').
 *  - press harder ('#') or lighter ('!') with your tail, creating a thicker or thinner line.
 *  - start ('[') or end (']') a branch, which lets you remember a position and angle and then magically return to it later.
 *
 *  your starting position and quantifiable attributes (such as how many steps you take when you move forward and how many
 *  degrees you turn at a time) can be changed as you go by the Max patch in which you live.  good luck.
 *
 */

#include "jit.common.h"
#include "math.h" // necessary for the polar->cartesian stuff in the drawing routines

#define PI2 6.2831853

#define MAXSTACK 512 // maximum number of branches... you can change this if you want to roll your own

typedef struct _max_jit_turtle
{
	t_object		ob;
	void			*obex; // we don't really need this, but whatever
	void 			*turtleout;
	// turtle attributes -- feel free to add your own here.
	long			command;
	long			clearmode;
	long			origin[2];
	long			origincount;
	long			angle;
	long			scale;
	double			thisangle[MAXSTACK];
	long			curstack;
	long			stacknew;
	long			pensize[MAXSTACK];
	long			stack_x[MAXSTACK], stack_y[MAXSTACK];

} t_max_jit_turtle;

void *max_jit_turtle_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_turtle_free(t_max_jit_turtle *x);
void max_jit_turtle_assist(t_max_jit_turtle *x, void *b, long m, long a, char *s);
void max_jit_turtle_bang(t_max_jit_turtle *x); // does nothing
void max_jit_turtle_int(t_max_jit_turtle *x, long n); // this is where the QD stuff is interpreted
void max_jit_turtle_reset(t_max_jit_turtle *x); // resets the turtle's state

t_messlist *max_jit_turtle_class;

void ext_main(void *r)
{
	long attrflags;
	void *p,*attr;

	setup(&max_jit_turtle_class, max_jit_turtle_new, (method)max_jit_turtle_free, (short)sizeof(t_max_jit_turtle),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_turtle,obex));

	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW ;

	// origin -- where to start drawing from (or reset to with a 'reset' message)
	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"origin",_jit_sym_long,2,attrflags,
						  (method)0,(method)0,calcoffset(t_max_jit_turtle,origincount),calcoffset(t_max_jit_turtle,origin));
	max_jit_classex_addattr(p,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Origin");

	// angle -- angle factor for turning the turtle
	attr = jit_object_new(_jit_sym_jit_attr_offset,"angle",_jit_sym_long,attrflags,
						  (method)0,(method)0,calcoffset(t_max_jit_turtle,angle));
	max_jit_classex_addattr(p,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Angle");

	// scale -- stepsize for moving the turtle
	attr = jit_object_new(_jit_sym_jit_attr_offset,"scale",_jit_sym_long,attrflags,
						  (method)0,(method)0,calcoffset(t_max_jit_turtle,scale));
	max_jit_classex_addattr(p,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"Scale");
	
	// clearmode -- send a clear on reset or not
	attr = jit_object_new(_jit_sym_jit_attr_offset,"clearmode",_jit_sym_long,attrflags,
						  (method)0,(method)0,calcoffset(t_max_jit_turtle,clearmode));
	max_jit_classex_addattr(p,attr);
	object_addattr_parse(attr,"label",_jit_sym_symbol,0,"\"Clear Mode\"");

	addmess((method)max_jit_turtle_reset, "reset", A_GIMME,0);

	max_jit_classex_standard_wrap(p,NULL,0);
	addmess((method)max_jit_turtle_assist, "assist", A_CANT,0);
// 	addbang((method)max_jit_turtle_bang);
	addint((method)max_jit_turtle_int);

	max_jit_class_addmethods(jit_class_findbyname(gensym("jit_turtle")));
}

void max_jit_turtle_bang(t_max_jit_turtle *x)
{
	// pontificate here...
	jit_object_post((t_object *)x,"HEY, YOU! STOP BANGING THE TURTLE!!!");
}

void max_jit_turtle_int(t_max_jit_turtle *x, long n)
{
	t_atom a[16];
	double tempangle;
	double temp_x, temp_y;
	long dest_x, dest_y;
	long curstack = x->curstack;

	x->command = n; // why do we do this?  i can't remember...

	// check to see if the integer received matches the ASCII code for one of these commands.
	// if so, compute the appropriate QuickDraw response and pass it out the outlet as a Max message.
	switch(n) {
	case (35): // '#' - increase pen size
		x->pensize[curstack] = x->pensize[curstack]+1;
		jit_atom_setlong(&a[0],x->pensize[curstack]);
		jit_atom_setlong(&a[1],x->pensize[curstack]);
		outlet_anything(x->turtleout, gensym("pensize"), 2, a);
		break;
	case (33): // '!' - decrease pen size
		if(x->pensize[curstack]>1) x->pensize[curstack] = x->pensize[curstack]-1;
		jit_atom_setlong(&a[0],x->pensize[curstack]);
		jit_atom_setlong(&a[1],x->pensize[curstack]);
		outlet_anything(x->turtleout, gensym("pensize"), 2, a);
		break;
	case (70): // 'F' - move forward and draw
		if(x->stacknew) {
			x->stack_x[curstack] = x->origin[0];
			x->stack_y[curstack] = x->origin[1];
			x->stacknew=0;
		}
		temp_x = (double)x->scale*jit_math_cos(x->thisangle[curstack]);
		temp_y = (double)x->scale*jit_math_sin(x->thisangle[curstack]);
		dest_x = x->stack_x[curstack]+temp_x+0.5;
		dest_y = x->stack_y[curstack]+temp_y+0.5;
		jit_atom_setlong(&a[0],x->stack_x[curstack]);
		jit_atom_setlong(&a[1],x->stack_y[curstack]);
		jit_atom_setlong(&a[2],dest_x);
		jit_atom_setlong(&a[3],dest_y);
		outlet_anything(x->turtleout, gensym("linesegment"), 4, a);
		x->stack_x[curstack] = dest_x;
		x->stack_y[curstack] = dest_y;
		break;
	case (102): // 'f' - move forward and don't draw
		if(x->stacknew) {
			x->stack_x[curstack] = x->origin[0];
			x->stack_y[curstack] = x->origin[1];
			x->stacknew=0;
		}
		temp_x = (double)x->scale*jit_math_cos(x->thisangle[curstack]);
		temp_y = (double)x->scale*jit_math_sin(x->thisangle[curstack]);
		dest_x = x->stack_x[curstack]+temp_x+0.5;
		dest_y = x->stack_y[curstack]+temp_y+0.5;
		x->stack_x[curstack] = dest_x;
		x->stack_y[curstack] = dest_y;
		break;
	case (91): // '[' - start a branch
		if(x->curstack>(MAXSTACK-2)) { // you can uncomment this jit_object_post((t_object *)x,) if you prefer... it's kind of annoying, IMHO.
			// jit_object_post((t_object *)x,"out of stack range -- not branching");
		}
		else {
			// copy current coords and angle to next branch and increment the stack
			x->stack_x[curstack+1] = x->stack_x[curstack];
			x->stack_y[curstack+1] = x->stack_y[curstack];
			x->thisangle[curstack+1] = x->thisangle[curstack];
			x->curstack++;
		}
		break;
	case (93): // ']' - end a branch and decrement the stack
		if(curstack>0) x->curstack--;
		break;
	case (43): // '+' - turn right
		x->thisangle[curstack]+=((x->angle/360.)*PI2);
		break;
	case (45): // '-' - turn left
		x->thisangle[curstack]-=((x->angle/360.)*PI2);
		break;
	case (124): // '|' - turn around
		x->thisangle[curstack]+=(0.5*PI2);
		break;
	default: // no match, don't do anything
		break;
	}
}

void max_jit_turtle_reset(t_max_jit_turtle *x)
{
	t_atom a[16];
	short i;

	x->curstack = 0;
	x->stacknew = 1;

	for(i=0; i<MAXSTACK; i++) {
		x->thisangle[i] = -PI2/4.; // start facing north (upwards, towards your menubar).
		x->stack_x[i] = x->origin[0];
		x->stack_y[i] = x->origin[1];
		x->pensize[i]=1;
	}

	jit_atom_setlong(&a[0],x->pensize[x->curstack]);
	jit_atom_setlong(&a[1],x->pensize[x->curstack]);
	outlet_anything(x->turtleout, gensym("pensize"), 2, a);

	// if the 'clearmode' attribute is set have jit.turtle tell the QuickDraw object downstream to clear itself.
	if(x->clearmode) outlet_anything(x->turtleout, gensym("clear"),0,0L);

}



void max_jit_turtle_assist(t_max_jit_turtle *x, void *b, long m, long a, char *s)
{
	if (m == 1) {
		sprintf(s, "(matrix) in");
	}
	else {
		if (a == 1)
			sprintf(s, "dumpout");
		else
			sprintf(s, "(matrix) out");
	}
}


void max_jit_turtle_free(t_max_jit_turtle *x)
{
	//only max object, no jit object
	max_jit_obex_free(x);

}

void *max_jit_turtle_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_turtle *x;
	t_jit_matrix_info info;
	long attrstart,i,j;
	jit_matrix_info_default(&info);

	if (x = (t_max_jit_turtle *)max_jit_obex_new(max_jit_turtle_class,gensym("jit_turtle"))) {
		max_jit_obex_dumpout_set(x, outlet_new(x,0L)); //general purpose outlet(rightmost)
		x->turtleout = outlet_new(x,0L); // outlet for the LCD commands

		x->clearmode = 1;

		x->scale = 10;
		x->angle = 30;
		x->origin[0] = 80; // kind of arbitrary, but i think the default jit.lcd matrix size is 160x120.
		x->origin[1] = 120;
		x->origincount = 2;
		x->curstack=0;
		x->stacknew=1;
		for(i=0; i<MAXSTACK; i++) {
			x->thisangle[i] = -PI2/4.; // start facing north (upwards)
			x->stack_x[i] = x->origin[0];
			x->stack_y[i] = x->origin[1];
			x->pensize[i] = 1;
		}

		max_jit_attr_args(x,argc,argv); //handle attribute args
	}
	return (x);
}
