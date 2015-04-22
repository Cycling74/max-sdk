/* 
	commonsyms.c

	Copyright 2001-2008 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com
	
*/

#include "ext.h"
#include "commonsyms.h"

t_common_symbols_table *_common_symbols=NULL;

void common_symbols_init(void) 
{
	_common_symbols = common_symbols_gettable();
}
