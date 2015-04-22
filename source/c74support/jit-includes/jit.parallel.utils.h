
#ifndef _JIT_PARALLEL_UTILS_H_
#define _JIT_PARALLEL_UTILS_H_

#define JIT_PARALLEL_NDIM_MAX_IO				32
#define JIT_PARALLEL_NDIM_FLAGS_FULL_MATRIX		0x00000001

#ifdef __cplusplus
extern "C" {
#endif

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

typedef struct _jit_parallel_ndim_io
{
	long				flags;
	t_jit_matrix_info 	*minfo;
	char		 		*bp;
} t_jit_parallel_ndim_io;

typedef struct _jit_parallel_ndim
{
	long flags;
	void *data;
	long dimcount;
	long *dim;
	long planecount;
	long iocount;
	t_jit_parallel_ndim_io	io[JIT_PARALLEL_NDIM_MAX_IO];
	method fn;
} t_jit_parallel_ndim;

typedef struct _jit_parallel_ndim_worker
{
	t_jit_parallel_ndim 	*paralleldata;
	long					workercount;
	long					workerid;
	long					offset[2];	
	long					extent[2];	
} t_jit_parallel_ndim_worker;


void jit_parallel_utils_init(void);
void jit_parallel_ndim_calc(t_jit_parallel_ndim *p);
void jit_parallel_ndim_simplecalc1(method fn, void *data, long dimcount, long *dim, long planecount, t_jit_matrix_info *minfo1, char *bp1, long flags1);
void jit_parallel_ndim_simplecalc2(method fn, void *data, long dimcount, long *dim, long planecount, t_jit_matrix_info *minfo1, char *bp1, 
	t_jit_matrix_info *minfo2, char *bp2, long flags1, long flags2);
void jit_parallel_ndim_simplecalc3(method fn, void *data, long dimcount, long *dim, long planecount, t_jit_matrix_info *minfo1, char *bp1, 
	t_jit_matrix_info *minfo2, char *bp2, t_jit_matrix_info *minfo3, char *bp3, long flags1, long flags2, long flags3);
void jit_parallel_ndim_simplecalc4(method fn, void *data, long dimcount, long *dim, long planecount, t_jit_matrix_info *minfo1, char *bp1, 
	t_jit_matrix_info *minfo2, char *bp2, t_jit_matrix_info *minfo3, char *bp3, t_jit_matrix_info *minfo4, char *bp4, 
	long flags1, long flags2, long flags3, long flags4);

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif //_JIT_PARALLEL_UTILS_H_
