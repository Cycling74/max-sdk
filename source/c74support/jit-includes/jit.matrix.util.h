#ifndef _JIT_MATRIX_UTIL_H_
#define _JIT_MATRIX_UTIL_H_

#include "jit.common.h"


#ifdef __cplusplus
extern "C" {
#endif

t_jit_err jit_matrix_list_get_matrices(void *list, long n, void **matrices);
t_jit_err jit_matrix_array_lock(void **matrices, long n, long *savelock);
t_jit_err jit_matrix_array_unlock(void **matrices, long n, long *savelock);
t_jit_err jit_matrix_array_get_matrix_info(void **matrices, long n, t_jit_matrix_info *matrix_info);
t_jit_err jit_matrix_array_get_data(void **matrices, long n, char **data);
t_jit_err jit_matrix_info_equal_matrix_structure(t_jit_matrix_info *minfo1, t_jit_matrix_info *minfo2);
t_jit_err jit_matrix_info_uniform_planecount(t_jit_matrix_info *matrix_info, long n, t_jit_matrix_info *info_list);
t_jit_err jit_matrix_info_uniform_type(t_jit_matrix_info *matrix_info, long n, t_jit_matrix_info *info_list);
t_jit_err jit_matrix_info_uniform_dim(t_jit_matrix_info *matrix_info, long n, t_jit_matrix_info *info_list);


#ifdef __cplusplus
}
#endif

#endif // _JIT_MATRIX_UTIL_H_