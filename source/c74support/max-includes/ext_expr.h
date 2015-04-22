/* ext_expr.h -- header file for writing expressions */

#ifndef _EXT_EXPR_H_
#define _EXT_EXPR_H_

BEGIN_USING_C_LINKAGE

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif
	
#define	EXPR_MAX_VARS	9

	/**	Defines for ex_type.
	We treat parenthesis and brackets special to keep a pointer to their match in the content.
	@ingroup expr
*/
typedef enum {
	ET_INT =	0x1,    ///< an int
	ET_FLT =	0x2,    ///< a float
	ET_OP =		0x3,    ///< operator
	ET_STR =	0x4,    ///< string
	ET_TBL = 	0x5,    ///< a table, the content is a pointer
	ET_FUNC =	0x6,    ///< a function
	ET_SYM =	0x7,    ///< symbol ("string")
	ET_VSYM =	0x8,    ///< variable symbol ("$s?")
	ET_LP =		0x9,	///< left parenthesis
	ET_LB =		0x10,	///< left bracket
	ET_II =		0x11,	///< and integer inlet
	ET_FI =		0x12,	///< float inlet
	ET_SI =		0x13	///< string inlet
} e_max_expr_types;

/**	ex_ex.
	@ingroup expr
*/
typedef struct ex_ex {
	union {
		long v_int;
		double v_flt;
		long op;
		char **ptr;
	} ex_cont;			///< content
	long ex_type;		///< type of the node
} t_ex_ex;	


/**	Struct for an instance of expr.
	@ingroup expr
*/
typedef struct expr {
	t_object exp_ob;
	void *exp_outlet;
	t_ex_ex *exp_stack;
	t_ex_ex exp_var[EXPR_MAX_VARS];
	t_ex_ex exp_res;		///< the result of last evaluation
} t_expr;

/**	Create a new expr object.
	@ingroup expr
	
	@param	argc	Count of arguments in argv. 
	@param	argv	Arguments that are used to create the expr. See the example below for details.
	@param	types	A pre-existing array of nine t_atoms, that will hold the 
					types of any variable arguments created in the expr. 
					The types are returned in the a_type field of each 
					#t_atom. If an argument was not present, #A_NOTHING is returned. 
	@return			expr_new() creates an expr object from the arguments in argv and 
					returns the type of any expr-style arguments contained in argv (i.e.
					$i1, etc.) in atoms in an array pointed to by types.

	@remark			types should already exist as an array of nine t_atom values, all of which will be filled in by 
					expr_new(). If an argument was not present, it will set to type 
					#A_NOTHING. For example, suppose argv pointed to the following atoms: 
	@code
	$i1 (A_SYM) 
	+ (A_SYM) 
	$f3 (A_SYM) 
	+ (A_SYM) 
	3 (A_LONG) 
	@endcode
	
	After calling expr_new, types would contain the following: 
	@code
	Index	Argument	Type		Value 
	0	1 ($i1)		A_LONG		0 
	1	2		A_NOTHING	0 
	2	3 ($f3)		A_FLOAT		0.0 
	3	4		A_NOTHING	0 
	4	5		A_NOTHING	0 
	5	6		A_NOTHING	0 
	6	7		A_NOTHING	0 
	7	8		A_NOTHING	0 
	8	9		A_NOTHING	0
	@endcode
*/
void *expr_new(long argc, t_atom *argv, t_atom *types);


/**	Evaluate an expression in an expr object.
	@ingroup expr
	
	@param	x		The expr object to evaluate.
	@param	argc	Count of arguments in argv.
	@param	argv	Array of nine t_atom values that will be substituted for 
					variable arguments (such as $i1) in the expression. 
					Unused arguments should be of type #A_NOTHING.
	@param	result	A pre-existing t_atom that will hold the type and value 
					of the result of evaluating the expression.
	@return			.
	
	@remark			Evaluates the expression in an expr object with arguments in argv and 
					returns the type and value of the evaluated expression as a t_atom in 
					result. result need only point to a single #t_atom, but argv should 
					contain at least argc t_atom values. If, as in the example shown above under 
					expr_new(), there are “gaps” between arguments, they should be filled 
					in with t_atom of type #A_NOTHING.
*/
short expr_eval(t_expr *x, long argc, t_atom *argv, t_atom *result);


void expr_install(method fun, const char *buf, long argc);



#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

END_USING_C_LINKAGE

#endif // _EXT_EXPR_H_
