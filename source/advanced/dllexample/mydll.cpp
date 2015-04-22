/**
	@file
	mydll - a DLL instance shared by several external objects

	@ingroup	examples

	Copyright 2013 - Cycling '74
	Timothy Place, tim@cycling74.com
*/

#include "mydll.h"


static int s_initialized = false;
static int s_count = 0;


void mydll_init(void)
{
	if (!s_initialized) {
		post("initialized mydll");
		s_initialized = true;
	}
}


void mydll_inc(void)
{
	s_count++;
}


int mydll_getcount(void)
{
	return s_count;
}

