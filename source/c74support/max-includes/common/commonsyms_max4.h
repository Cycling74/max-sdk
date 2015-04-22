/* 
	commonsyms.h
		
*/

#ifndef __COMMON_SYMBOLS_H__
#define __COMMON_SYMBOLS_H__

#ifdef __cplusplus
	extern "C" {
#endif // __cplusplus

void common_symbols_init(void);

extern t_symbol *_sym_nothing;
extern t_symbol *_sym_new;
extern t_symbol *_sym_free;
extern t_symbol *_sym_classname;
extern t_symbol *_sym_getname;
extern t_symbol *_sym_getmethod;
extern t_symbol *_sym_get;
extern t_symbol *_sym_set;
extern t_symbol *_sym_unset;
extern t_symbol *_sym_register;
extern t_symbol *_sym_char;
extern t_symbol *_sym_long;
extern t_symbol *_sym_float32;
extern t_symbol *_sym_float64;
extern t_symbol *_sym_symbol;
extern t_symbol *_sym_pointer;
extern t_symbol *_sym_object;
extern t_symbol *_sym_atom;
extern t_symbol *_sym_list;
extern t_symbol *_sym_type;
extern t_symbol *_sym_dim;
extern t_symbol *_sym_planecount;
extern t_symbol *_sym_val;
extern t_symbol *_sym_plane;
extern t_symbol *_sym_cell;
extern t_symbol *_sym_jit_matrix;
extern t_symbol *_sym_class_jit_matrix;
extern t_symbol *_sym_togworld;
extern t_symbol *_sym_fromgworld;
extern t_symbol *_sym_frommatrix;
extern t_symbol *_sym_class_jit_attribute;
extern t_symbol *_sym_jit_attribute;
extern t_symbol *_sym_jit_attr_offset;
extern t_symbol *_sym_jit_attr_offset_array;
extern t_symbol *_sym_rebuilding;
extern t_symbol *_sym_modified;
extern t_symbol *_sym_lock;
extern t_symbol *_sym_setinfo;
extern t_symbol *_sym_setinfo_ex;
extern t_symbol *_sym_getinfo;
extern t_symbol *_sym_data;
extern t_symbol *_sym_getdata;
extern t_symbol *_sym_outputmatrix;
extern t_symbol *_sym_clear;
extern t_symbol *_sym_err_calculate;
extern t_symbol *_sym_max_jit_classex;
extern t_symbol *_sym_setall;
extern t_symbol *_sym_chuck;
extern t_symbol *_sym_getsize;
extern t_symbol *_sym_getindex;
extern t_symbol *_sym_objptr2index;
extern t_symbol *_sym_append;
extern t_symbol *_sym_insertindex;
extern t_symbol *_sym_deleteindex;
extern t_symbol *_sym_chuckindex;
extern t_symbol *_sym_makearray;
extern t_symbol *_sym_reverse;
extern t_symbol *_sym_rotate;
extern t_symbol *_sym_shuffle;
extern t_symbol *_sym_swap;
extern t_symbol *_sym_findfirst;
extern t_symbol *_sym_findall;
extern t_symbol *_sym_methodall;
extern t_symbol *_sym_methodindex;
extern t_symbol *_sym_sort;
extern t_symbol *_sym_matrix_calc;
extern t_symbol *_sym_genframe;
extern t_symbol *_sym_filter;
extern t_symbol *_sym_jit_mop;
extern t_symbol *_sym_newcopy;
extern t_symbol *_sym_jit_linklist;
extern t_symbol *_sym_inputcount;
extern t_symbol *_sym_outputcount;
extern t_symbol *_sym_getinput;
extern t_symbol *_sym_getoutput;
extern t_symbol *_sym_getinputlist;
extern t_symbol *_sym_getoutputlist;
extern t_symbol *_sym_ioname;
extern t_symbol *_sym_matrixname;
extern t_symbol *_sym_outputmode;
extern t_symbol *_sym_matrix;
extern t_symbol *_sym_getmatrix;
extern t_symbol *_sym_typelink;
extern t_symbol *_sym_dimlink;
extern t_symbol *_sym_planelink;
extern t_symbol *_sym_restrict_type;
extern t_symbol *_sym_restrict_planecount;
extern t_symbol *_sym_restrict_dim;
extern t_symbol *_sym_special;
extern t_symbol *_sym_getspecial;
extern t_symbol *_sym_adapt;
extern t_symbol *_sym_decorator;
extern t_symbol *_sym_frommatrix_trunc;
extern t_symbol *_sym_ioproc;
extern t_symbol *_sym_getioproc;
extern t_symbol *_sym_name;
extern t_symbol *_sym_types;
extern t_symbol *_sym_minplanecount;
extern t_symbol *_sym_maxplanecount;
extern t_symbol *_sym_mindim;
extern t_symbol *_sym_maxdim;
extern t_symbol *_sym_gl_points;
extern t_symbol *_sym_gl_lines;
extern t_symbol *_sym_gl_line_strip;
extern t_symbol *_sym_gl_line_loop;
extern t_symbol *_sym_gl_triangles;
extern t_symbol *_sym_gl_tri_strip;
extern t_symbol *_sym_gl_tri_fan;
extern t_symbol *_sym_gl_quads;
extern t_symbol *_sym_gl_quad_strip;
extern t_symbol *_sym_gl_polygon;
extern t_symbol *_sym_gl_tri_grid;
extern t_symbol *_sym_gl_quad_grid;
extern t_symbol *_sym_err_lockout_stack;
extern t_symbol *_sym_class_jit_namespace;
extern t_symbol *_sym_jit_namespace;
extern t_symbol *_sym_findsize;
extern t_symbol *_sym_attach;
extern t_symbol *_sym_detach;
extern t_symbol *_sym_add;
extern t_symbol *_sym_replace;
extern t_symbol *_sym_gettype;
extern t_symbol *_sym_ob_sym;
extern t_symbol *_sym_resolve_name;
extern t_symbol *_sym_resolve_raw;
extern t_symbol *_sym_notifyall;
extern t_symbol *_sym_anything;
extern t_symbol *_sym_usercanset;
extern t_symbol *_sym_usercanget;
extern t_symbol *_sym_notify;
extern t_symbol *_sym_getvalueof;
extern t_symbol *_sym_setvalueof;
extern t_symbol *_sym_dumpout;
extern t_symbol *_sym_attributes;
extern t_symbol *_sym_adornments;
extern t_symbol *_sym_attr_getnames;
extern t_symbol *_sym_attr_get;
extern t_symbol *_sym_float;
extern t_symbol *_sym_int;
extern t_symbol *_sym_bang;
extern t_symbol *_sym_parent;
extern t_symbol *_sym_global;
extern t_symbol *_sym_arguments;
extern t_symbol *_sym_args;
extern t_symbol *_sym_attr_modified;
extern t_symbol *_sym_hashtab_entry_new;
extern t_symbol *_sym_hashtab_entry_free;
extern t_symbol *_sym_hashtab_free;

#ifdef __cplusplus
}
#endif // __cplusplus


#endif // __COMMON_SYMBOLS_H__
