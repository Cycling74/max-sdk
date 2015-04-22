#ifndef JIT_VECMATH_H
#define JIT_VECMATH_H

/*
 * jit.vecmath.h
 *
 * Copyright 2001-2005 - Cycling '74
 * Derek Gerstmann - derek@cycling74.com
 *
 * Basic vector math operations for floating point datatypes.
 *
 * All functions were designed to use the first function parameter
 * as the assigned/return value (eg):
 *
 * 		// C = A + B
 *		jit_vec3_add(c, a, b);
 *
 * With the notable exception of all "_to_array" & "_to_coord" methods:
 *
 *		// matrix -> array
 *		jit_mat4_to_array(m, a);
 *
 * and jit_quat_to_axes and jit_quat_to_angleaxis
 *
 */
 
#include "jit.common.h"
#include "jit.math.h"
#include "float.h"

#ifdef __cplusplus
extern "C" {
#endif

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

// ----------------------------------------------------------------------------

// vector math macros for untyped evaluation
#define JIT_VEC2_ADD(c,a,b)   { (c)[0] = (a)[0] + (b)[0]; (c)[1] = (a)[1] + (b)[1]; }
#define JIT_VEC2_SUB(c,a,b)   { (c)[0] = (a)[0] - (b)[0]; (c)[1] = (a)[1] - (b)[1]; }
#define JIT_VEC2_MULT(c,a,b)  { (c)[0] = (a)[0] * (b)[0]; (c)[1] = (a)[1] * (b)[1]; }
#define JIT_VEC2_DIV(c,a,b)   { (c)[0] = (a)[0] / (b)[0]; (c)[1] = (a)[1] / (b)[1]; }
#define JIT_VEC2_INC(c,a)     { (c)[0] += (a)[0]; (c)[1] += (a)[1]; }
#define JIT_VEC2_DEC(c,a)     { (c)[0] -= (a)[0]; (c)[1] -= (a)[1]; }
#define JIT_VEC2_ADDC(c,a,b)  { (c)[0] = (a)[0] + (b); (c)[1] = (a)[1] + (b); }
#define JIT_VEC2_SUBC(c,a,b)  { (c)[0] = (a)[0] - (b); (c)[1] = (a)[1] - (b); }
#define JIT_VEC2_MULTC(c,a,b) { (c)[0] = (a)[0] * (b); (c)[1] = (a)[1] * (b); }
#define JIT_VEC2_DIVC(c,a,b)  { (c)[0] = (a)[0] / (b); (c)[1] = (a)[1] / (b); }
#define JIT_VEC2_COPY(b,a)    { (b)[0] = (a)[0]; (b)[1] = (a)[1]; }
#define JIT_VEC2_COPYC(b,a)   { (b)[0] = (a); (b)[1] = (a); }
#define JIT_VEC2_DOT(p1, p2)  ((p1)[0] * (p2)[0] + (p1)[1] * (p2)[1])

#define JIT_VEC2_NORMALIZE(v) { \
	double s = JIT_MATH_F64_EPS; \
	double m = (v)[0]*(v)[0] + (v)[1]*(v)[1]; \
	if (m > JIT_MATH_F64_EPS) \
	{ \
		s = jit_math_sqrt(m); \
		(v)[0] /= s; \
		(v)[1] /= s; \
	} \
	else \
	{ \
		(v)[0] = s; \
		(v)[1] = s; \
	} \
}

#define JIT_VEC3_ADD(c,a,b)   { (c)[0] = (a)[0] + (b)[0]; (c)[1] = (a)[1] + (b)[1];\
                           (c)[2] = (a)[2] + (b)[2];}
#define JIT_VEC3_SUB(c,a,b)   { (c)[0] = (a)[0] - (b)[0]; (c)[1] = (a)[1] - (b)[1]; \
                           (c)[2] = (a)[2] - (b)[2];}
#define JIT_VEC3_MULT(c,a,b)  { (c)[0] = (a)[0] * (b)[0]; (c)[1] = (a)[1] * (b)[1]; \
                           (c)[2] = (a)[2] * (b)[2];}
#define JIT_VEC3_DIV(c,a,b)   { (c)[0] = (a)[0] / (b)[0]; (c)[1] = (a)[1] / (b)[1]; \
                           (c)[2] = (a)[2] / (b)[2];}
#define JIT_VEC3_INC(c,a)     { (c)[0] += (a)[0]; (c)[1] += (a)[1];\
                           (c)[2] += (a)[2];}
#define JIT_VEC3_DEC(c,a)     { (c)[0] -= (a)[0]; (c)[1] -= (a)[1];\
                           (c)[2] -= (a)[2];}
#define JIT_VEC3_ADDC(c,a,b)  { (c)[0] = (a)[0] + (b); (c)[1] = (a)[1] + (b);\
                           (c)[2] = (a)[2] + (b);}
#define JIT_VEC3_SUBC(c,a,b)  { (c)[0] = (a)[0] - (b); (c)[1] = (a)[1] - (b); \
                           (c)[2] = (a)[2] - (b);}
#define JIT_VEC3_MULTC(c,a,b) { (c)[0] = (a)[0] * (b); (c)[1] = (a)[1] * (b);\
                           (c)[2] = (a)[2] * (b);}
#define JIT_VEC3_DIVC(c,a,b)  { (c)[0] = (a)[0] / (b); (c)[1] = (a)[1] / (b);\
                           (c)[2] = (a)[2] / (b);}
#define JIT_VEC3_COPY(b,a)    { (b)[0] = (a)[0]; (b)[1] = (a)[1]; (b)[2] = (a)[2]; }

#define JIT_VEC3_COPYC(b,a)   { (b)[0] = (a); (b)[1] = (a); (b)[2] = (a); }

#define JIT_VEC3_DOT(p1, p2)  ((p1)[0] * (p2)[0] + (p1)[1] * (p2)[1] + (p1)[2] * (p2)[2])

#define JIT_VEC3_CROSS(c,a,b) { (c)[0] = (a)[1] * (b)[2] - (a)[2] * (b)[1]; \
			   (c)[1] = (a)[2] * (b)[0] - (a)[0] * (b)[2]; \
			   (c)[2] = (a)[0] * (b)[1] - (a)[1] * (b)[0]; }

#define JIT_VEC3_NORMALIZE(v) { \
	double s = JIT_MATH_F64_EPS; \
	double m = (v)[0]*(v)[0] + (v)[1]*(v)[1] + (v)[2]*(v)[2]; \
	if (m > JIT_MATH_F64_EPS) \
	{ \
		s = jit_math_sqrt(m); \
		(v)[0] /= s; \
		(v)[1] /= s; \
		(v)[2] /= s; \
	} \
	else \
	{ \
		(v)[0] = s; \
		(v)[1] = s; \
		(v)[2] = s; \
	} \
}

// ----------------------------------------------------------------------------

// vector math typedefs
typedef union _jit_vec2
{
    struct {
        float x,y;
    };
    struct {
        float s,t;
    };
    float vals[2];

} t_jit_vec2;

typedef union _jit_vec3
{
    struct {
        float x,y,z;
    };
    struct {
        float s,t,r;
    };
    float vals[3];

} t_jit_vec3;

typedef union _jit_vec4
{
    struct {
        float x,y,z,w;
    };
    struct {
        float s,t,r,q;
    };
    float vals[4];

} t_jit_vec4;

typedef union _jit_quat
{
    struct {
        float x,y,z,w;
    };
    float vals[4];

} t_jit_quat;

typedef union _jit_mat3
{
	struct {
		float v00, v10, v20;
		float v01, v11, v21;
		float v02, v12, v22;
	};
	float vals[9];

} t_jit_mat3;

typedef union _jit_mat4 {
	struct {
		float v00, v10, v20, v30;
		float v01, v11, v21, v31;
		float v02, v12, v22, v32;
		float v03, v13, v23, v33;
	};
	union {
		struct {
			float b00, b10, b20, p;
			float b01, b11, b21, q;
			float b02, b12, b22, r;
			float x, y, z, w;       
		};
	};
	float vals[16];
	
} t_jit_mat4;

typedef struct _jit_line {
	t_jit_vec3	start;
	t_jit_vec3	end;
} t_jit_line;

typedef struct _jit_ray {
	t_jit_vec3	origin;
	t_jit_vec3	direction;
} t_jit_ray;

typedef struct _jit_plane {
	t_jit_vec3	origin;
	t_jit_vec3	normal;
	//float		distance;
} t_jit_plane;

typedef struct _jit_sphere {
	t_jit_vec3	center;
	float		radius;	
} t_jit_sphere;

typedef struct _jit_aabb {
	t_jit_vec3	min;
	t_jit_vec3	max;
} t_jit_aabb;

JIT_EX_DATA t_jit_vec3 vec3_zero;
JIT_EX_DATA t_jit_vec3 vec3_identity;
JIT_EX_DATA t_jit_vec3 vec3_unit_x;
JIT_EX_DATA t_jit_vec3 vec3_unit_y;
JIT_EX_DATA t_jit_vec3 vec3_unit_z;
JIT_EX_DATA t_jit_vec3 vec3_neg_unit_x;
JIT_EX_DATA t_jit_vec3 vec3_neg_unit_y;
JIT_EX_DATA t_jit_vec3 vec3_neg_unit_z;

t_jit_err jit_vecmath_init(void);

// ----------------------------------------------------------------------------

void jit_vec2_fill(t_jit_vec2 *u, float x);
void jit_vec2_assign(t_jit_vec2 *u, t_jit_vec2 *v);
void jit_vec2_from_array(t_jit_vec2 *u, float *xy);
void jit_vec2_from_coords(t_jit_vec2 *u, float x, float y);
void jit_vec2_to_array(t_jit_vec2 *u, float *xy);
void jit_vec2_to_coords(t_jit_vec2 *u, float *x, float *y);
long jit_vec2_equal(t_jit_vec2 *u, t_jit_vec2 *v);
long jit_vec2_not_equal(t_jit_vec2 *u, t_jit_vec2 *v);
void jit_vec2_mult( t_jit_vec2 *u,  t_jit_vec2 *a,  t_jit_vec2 *b);
void jit_vec2_scale( t_jit_vec2 *u,  t_jit_vec2 *a, float s);
void jit_vec2_accum_scale( t_jit_vec2 *u,  float s);
void jit_vec2_div( t_jit_vec2 *u,  t_jit_vec2 *a, float s);
void jit_vec2_sub( t_jit_vec2 *u,  t_jit_vec2 *a,  t_jit_vec2 *b);
void jit_vec2_accum_sub(t_jit_vec2 *u, t_jit_vec2 *v); 
void jit_vec2_add( t_jit_vec2 *u,  t_jit_vec2 *a,  t_jit_vec2 *b);
void jit_vec2_accum_add(t_jit_vec2 *u, t_jit_vec2 *v); 
float jit_vec2_get_coord(t_jit_vec2 *u, long i); 
float jit_vec2_mag_sqr(t_jit_vec2 *u);
float jit_vec2_mag(t_jit_vec2 *u);
void jit_vec2_negate(t_jit_vec2 *u);
void jit_vec2_max(t_jit_vec2 *r,  t_jit_vec2 *a,  t_jit_vec2 *b);
void jit_vec2_min(t_jit_vec2 *r,  t_jit_vec2 *a,  t_jit_vec2 *b);
void jit_vec2_lerp(t_jit_vec2 *w,  float t,  t_jit_vec2 *u,  t_jit_vec2 *v);
long jit_vec2_is_valid( t_jit_vec2 *v);

// ----------------------------------------------------------------------------

void jit_vec3_fill(t_jit_vec3 *u, float x);
void jit_vec3_assign(t_jit_vec3 *u, t_jit_vec3 *v);
void jit_vec3_from_array(t_jit_vec3 *u, float *xyz);
void jit_vec3_from_coords(t_jit_vec3 *u, float x, float y, float z);
void jit_vec3_to_array(t_jit_vec3 *u, float *xyz);
void jit_vec3_to_coords(t_jit_vec3 *u, float *x, float *y, float *z);
long jit_vec3_equal(t_jit_vec3 *u, t_jit_vec3 *v);
long jit_vec3_not_equal(t_jit_vec3 *u, t_jit_vec3 *v);
long jit_vec3_less(t_jit_vec3 *u, t_jit_vec3 *v);
long jit_vec3_greater(t_jit_vec3 *u, t_jit_vec3 *v);
void jit_vec3_mult( t_jit_vec3 *u,  t_jit_vec3 *a,  t_jit_vec3 *b);
void jit_vec3_scale( t_jit_vec3 *u,  t_jit_vec3 *a, float s);
void jit_vec3_accum_scale( t_jit_vec3 *u,  float s);
void jit_vec3_div( t_jit_vec3 *u,  t_jit_vec3 *a, float s);
void jit_vec3_sub( t_jit_vec3 *u,  t_jit_vec3 *a,  t_jit_vec3 *b);
void jit_vec3_accum_sub(t_jit_vec3 *u, t_jit_vec3 *v); 
void jit_vec3_add( t_jit_vec3 *u,  t_jit_vec3 *a,  t_jit_vec3 *b);
void jit_vec3_accum_add(t_jit_vec3 *u, t_jit_vec3 *v); 
void jit_vec3_madd(t_jit_vec3 *u,  t_jit_vec3 *v,  float s);
float jit_vec3_get_coord( t_jit_vec3 *u, long i); 
float jit_vec3_mag_sqr(t_jit_vec3 *u);
float jit_vec3_mag(t_jit_vec3 *u);
void jit_vec3_negate(t_jit_vec3 *u);
void jit_vec3_cross(t_jit_vec3 *u,  t_jit_vec3 *a,  t_jit_vec3 *b);
float jit_vec3_dot(t_jit_vec3 *u,  t_jit_vec3 *v);
void jit_vec3_reflect(t_jit_vec3 *r,  t_jit_vec3 *n,  t_jit_vec3 *l);
float jit_vec3_normalize( t_jit_vec3 *u );
void jit_vec3_orthogonalize( t_jit_vec3 *u, t_jit_vec3 *v );
void jit_vec3_orthonormalize( t_jit_vec3 *u, t_jit_vec3 *v );
void jit_vec3_max(t_jit_vec3 *r,  t_jit_vec3 *a,  t_jit_vec3 *b);
void jit_vec3_min(t_jit_vec3 *r,  t_jit_vec3 *a,  t_jit_vec3 *b);
void jit_vec3_lerp(t_jit_vec3 *w,  float t,  t_jit_vec3 *u,  t_jit_vec3 *v);
void jit_vec3_cubemap_normal(t_jit_vec3 *v, int i, int x, int y, int cubesize);
long jit_vec3_is_valid( t_jit_vec3 *v);

// ----------------------------------------------------------------------------

void jit_vec4_fill(t_jit_vec4 *u, float x);
void jit_vec4_assign(t_jit_vec4 *u, t_jit_vec4 *v);
void jit_vec4_from_array(t_jit_vec4 *u, float *xyzw);
void jit_vec4_from_coords(t_jit_vec4 *u, float x, float y, float z, float w);
void jit_vec4_to_array(t_jit_vec4 *u, float *xyzw);
void jit_vec4_to_coords(t_jit_vec4 *u, float *x, float *y, float *z, float *w);
long jit_vec4_equal(t_jit_vec4 *u, t_jit_vec4 *v);
long jit_vec4_not_equal(t_jit_vec4 *u, t_jit_vec4 *v);
void jit_vec4_mult( t_jit_vec4 *u,  t_jit_vec4 *a,  t_jit_vec4 *b);
void jit_vec4_scale( t_jit_vec4 *u,  t_jit_vec4 *a, float s);
void jit_vec4_accum_scale( t_jit_vec4 *u,  float s);
void jit_vec4_div( t_jit_vec4 *u,  t_jit_vec4 *a, float s);
void jit_vec4_sub( t_jit_vec4 *u,  t_jit_vec4 *a,  t_jit_vec4 *b);
void jit_vec4_accum_sub(t_jit_vec4 *u, t_jit_vec4 *v); 
void jit_vec4_add( t_jit_vec4 *u,  t_jit_vec4 *a,  t_jit_vec4 *b);
void jit_vec4_accum_add(t_jit_vec4 *u, t_jit_vec4 *v); 
float jit_vec4_get_coord(t_jit_vec4 *u, long i); 
float jit_vec4_mag_sqr(t_jit_vec4 *u);
float jit_vec4_mag(t_jit_vec4 *u);
void jit_vec4_negate(t_jit_vec4 *u);
float jit_vec4_dot(t_jit_vec4 *u,  t_jit_vec4 *w);
float jit_vec4_normalize( t_jit_vec4 *u );
void jit_vec4_max(t_jit_vec4 *r,  t_jit_vec4 *a,  t_jit_vec4 *b);
void jit_vec4_min(t_jit_vec4 *r,  t_jit_vec4 *a,  t_jit_vec4 *b);
void jit_vec4_lerp(t_jit_vec4 *w,  float t,  t_jit_vec4 *u,  t_jit_vec4 *v);
long jit_vec4_is_valid( t_jit_vec4 *v);

// ----------------------------------------------------------------------------

void jit_quat_fill(t_jit_quat *u, float x);
void jit_quat_assign(t_jit_quat *u, t_jit_quat *v);
void jit_quat_from_array(t_jit_quat *u, float *xyzw);
void jit_quat_from_coords(t_jit_quat *u, float x, float y, float z, float w);
void jit_quat_to_array(t_jit_quat *u, float *xyzw);
void jit_quat_to_coords(t_jit_quat *u, float *x, float *y, float *z, float *w);
long jit_quat_equal(t_jit_quat *u, t_jit_quat *v);
long jit_quat_not_equal(t_jit_quat *u, t_jit_quat *v);
void jit_quat_scale( t_jit_quat *u,  t_jit_quat *a, float s);
void jit_quat_accum_scale( t_jit_quat *u,  float s);
void jit_quat_div( t_jit_quat *u,  t_jit_quat *a, float s);
void jit_quat_add(t_jit_quat * r,  t_jit_quat * q1,  t_jit_quat * q2);
void jit_quat_sub(t_jit_quat * r,  t_jit_quat * q1,  t_jit_quat * q2);
void jit_quat_mult( t_jit_quat *r, t_jit_quat * p,  t_jit_quat * q);
void jit_quat_inverse( t_jit_quat * r,  t_jit_quat * p);
void jit_quat_log( t_jit_quat * r,  t_jit_quat * p);
void jit_quat_exp( t_jit_quat * r,  t_jit_quat * p);
float jit_quat_dot(t_jit_quat * q1,  t_jit_quat * q2);
float jit_quat_get_coord( t_jit_quat *u, long i);
float jit_quat_mag_sqr( t_jit_quat *u);
float jit_quat_mag( t_jit_quat *u);
void jit_quat_negate(t_jit_quat *u);
float jit_quat_normalize( t_jit_quat *u );
void jit_quat_max(t_jit_quat *r,  t_jit_quat *a,  t_jit_quat *b);
void jit_quat_min(t_jit_quat *r,  t_jit_quat *a,  t_jit_quat *b);
void jit_quat_from_mat3( t_jit_quat *q, t_jit_mat3 *m);
void jit_mat3_from_quat(t_jit_mat3 *mat, t_jit_quat *q);
void jit_quat_from_mat4(t_jit_quat * q,  t_jit_mat4 *m);
void jit_quat_from_axisangle(t_jit_quat * q,  t_jit_vec3 *a,  float angle);
void jit_quat_to_axisangle(t_jit_quat *q, t_jit_vec3 *a, float *angle);
void jit_quat_from_xyz(t_jit_quat *q, float *xyz);
void jit_quat_to_xyz(t_jit_quat *q, float *xyz);
void jit_quat_mult_vec3(t_jit_vec3 *r, t_jit_quat *q, t_jit_vec3 *v);
void jit_quat_from_axes(t_jit_quat *q, t_jit_vec3 *x, t_jit_vec3 *y, t_jit_vec3 *z);
void jit_quat_to_axes(t_jit_quat *q, t_jit_vec3 *x, t_jit_vec3 *y, t_jit_vec3 *z);
void jit_quat_shortest_arc(t_jit_quat *q, t_jit_vec3 *a, t_jit_vec3 *b);
void jit_quat_conj(t_jit_quat * p);
void jit_quat_get_conj(t_jit_quat * p,  t_jit_quat * q);
void jit_quat_lerp(t_jit_quat *r, float s,  t_jit_quat * q1,  t_jit_quat * q2, long shortest);
void jit_quat_slerp(t_jit_quat *r, float s,  t_jit_quat * q1,  t_jit_quat * q2);
void jit_quat_slerp_shortest(t_jit_quat *r, float s,  t_jit_quat * q1,  t_jit_quat * q2);
void jit_quat_squad(t_jit_quat *r, float s,  t_jit_quat * p,  t_jit_quat * a,
	t_jit_quat * b,  t_jit_quat * q, int shortestpath);
void jit_quat_trackball(t_jit_quat * q, t_jit_vec2 *p1, t_jit_vec2 *p2, float radius);
long jit_quat_is_valid( t_jit_quat *v);

// ----------------------------------------------------------------------------

void jit_mat3_assign( t_jit_mat3 *m, t_jit_mat3 *a );
void jit_mat3_from_array( t_jit_mat3 *m, float *v );
void jit_mat3_from_array3x3( t_jit_mat3 *m, float **v );
void jit_mat3_from_coords( t_jit_mat3 *m,  
	float f0,   float f1,   float f2,  
	float f3,   float f4,   float f5,  
	float f6,   float f7,   float f8 );
void jit_mat3_to_array( t_jit_mat3 *m, float *v );
void jit_mat3_to_array3x3( t_jit_mat3 *m, float **v );
void jit_mat3_to_coords( t_jit_mat3 *m,  
	float *f0,   float *f1,   float *f2,  
	float *f3,   float *f4,   float *f5,  
	float *f6,   float *f7,   float *f8 );
void jit_mat3_get_row( t_jit_vec3 *v, long i, t_jit_mat3 *m );
void jit_mat3_set_row( t_jit_mat3 *m, long i,  t_jit_vec3 *v );
void jit_mat3_get_col( t_jit_vec3 *v, long i, t_jit_mat3 *m );
void jit_mat3_set_col( t_jit_mat3 *m, long i,  t_jit_vec3 *v);
float jit_mat3_get_coord(t_jit_mat3 *m, long r, long c );
void jit_mat3_add(t_jit_mat3 *c,  t_jit_mat3 *a,  t_jit_mat3 *b);
void jit_mat3_accum_add(t_jit_mat3 *a,  t_jit_mat3 *b);
void jit_mat3_accum_scale( t_jit_mat3 *m, float s);
void jit_mat3_accum_sub( t_jit_mat3 *m, t_jit_mat3 *a );
void jit_mat3_mult(t_jit_mat3 *c, t_jit_mat3 *a, t_jit_mat3 *b);
void jit_mat3_get_transpose(t_jit_mat3 *b, t_jit_mat3 *a);
void jit_mat3_transpose(t_jit_mat3 *a);
void jit_mat3_mult_vec3( t_jit_vec3 *r, t_jit_mat3 *m, t_jit_vec3 *v );
void jit_vec3_mult_mat3( t_jit_vec3 *r, t_jit_vec3 *v, t_jit_mat3 *m );
void jit_mat3_from_axisangle( t_jit_mat3 *m, t_jit_vec3 *v, float theta );
void jit_mat3_from_uv( t_jit_mat3 *m, t_jit_vec3 *u,  t_jit_vec3 *v );
float jit_mat3_determinant( t_jit_mat3 *m);
void jit_mat3_get_inverse(t_jit_mat3 *b,  t_jit_mat3 *a);
void jit_mat3_negate( t_jit_mat3 *m );
void jit_mat3_tangent_basis(t_jit_mat3 *basis,
	t_jit_vec3 *v0, t_jit_vec3 *v1, t_jit_vec3 *v2,
	t_jit_vec2 *t0, t_jit_vec2 *t1, t_jit_vec2 *t2,  
	t_jit_vec3 *n);
	
t_bool jit_mat3_to_eulerxyz(t_jit_mat3 *m, float *xyz);
t_bool jit_mat3_to_eulerxzy(t_jit_mat3 *m, float *xyz);
t_bool jit_mat3_to_euleryxz(t_jit_mat3 *m, float *xyz);
t_bool jit_mat3_to_euleryzx(t_jit_mat3 *m, float *xyz);
t_bool jit_mat3_to_eulerzxy(t_jit_mat3 *m, float *xyz);
t_bool jit_mat3_to_eulerzyx(t_jit_mat3 *m, float *xyz);
void jit_mat3_from_eulerxyz(t_jit_mat3 *m, double fYAngle, double fPAngle, double fRAngle);
void jit_mat3_from_eulerxzy(t_jit_mat3 *m, double fYAngle, double fPAngle, double fRAngle);
void jit_mat3_from_euleryxz(t_jit_mat3 *m, double fYAngle, double fPAngle, double fRAngle);
void jit_mat3_from_euleryzx(t_jit_mat3 *m, double fYAngle, double fPAngle, double fRAngle);
void jit_mat3_from_eulerzxy(t_jit_mat3 *m, double fYAngle, double fPAngle, double fRAngle);
void jit_mat3_from_eulerzyx(t_jit_mat3 *m, double fYAngle, double fPAngle, double fRAngle);

void jit_vec3_mult_mat4_pos(t_jit_vec3 *u,  t_jit_vec3 *v,  t_jit_mat4 *m);
void jit_mat4_mult_vec3_pos(t_jit_vec3 *u,  t_jit_mat4 *m,  t_jit_vec3 *v);
void jit_vec3_mult_mat4_dir(t_jit_vec3 *u,  t_jit_vec3 *v,  t_jit_mat4 *m);
void jit_mat4_mult_vec3_dir(t_jit_vec3 *u,  t_jit_mat4 *m,  t_jit_vec3 *v);
void jit_vec3_mult_mat4(t_jit_vec3 *u,  t_jit_vec3 *v,  t_jit_mat4 *m);
void jit_mat4_mult_vec3(t_jit_vec3 *u,  t_jit_mat4 *m,  t_jit_vec3 *v);

// ----------------------------------------------------------------------------

void jit_mat4_assign( t_jit_mat4 *m, t_jit_mat4 *a );
void jit_mat4_from_array( t_jit_mat4 *m, float *v );
void jit_mat4_from_array4x4( t_jit_mat4 *m, float **v );
void jit_mat4_from_coords( t_jit_mat4 *m, 
	float f0,   float f1,   float f2,   float f3,
	float f4,   float f5,   float f6,   float f7,
	float f8,   float f9,   float f10,  float f11,
	float f12,  float f13,  float f14,  float f15 );
void jit_mat4_to_array( t_jit_mat4 *m, float *v );
void jit_mat4_to_array4x4( t_jit_mat4 *m, float **v );
void jit_mat4_to_coords( t_jit_mat4 *m, 
	float *f0,   float *f1,   float *f2,   float *f3,
	float *f4,   float *f5,   float *f6,   float *f7,
	float *f8,   float *f9,   float *f10,  float *f11,
	float *f12,  float *f13,  float *f14,  float *f15 );
void jit_mat4_get_row( t_jit_vec4 *v, long i, t_jit_mat4 *m );
void jit_mat4_set_row( t_jit_mat4 *m, long i,  t_jit_vec4 *v );
void jit_mat4_get_col( t_jit_vec4 *v, long i, t_jit_mat4 *m );
void jit_mat4_set_col( t_jit_mat4 *m, long i,  t_jit_vec4 *v);
float jit_mat4_get_coord(t_jit_mat4 *m, long r, long c );
void jit_mat4_mult_vec4(t_jit_vec4 *u,  t_jit_mat4 *m,  t_jit_vec4 *v);
void jit_vec4_mult_mat4(t_jit_vec4 *u,  t_jit_vec4 *v,  t_jit_mat4 *m);
void jit_mat4_accum_add(t_jit_mat4 *a,  t_jit_mat4 *b);
void jit_mat4_add(t_jit_mat4 *c, t_jit_mat4 *a, t_jit_mat4 *b);
void jit_mat4_mult(t_jit_mat4 *c,  t_jit_mat4 *a,  t_jit_mat4 *b);
void jit_mat4_transpose(t_jit_mat4 *m);
void jit_mat4_get_transpose(t_jit_mat4 *b,  t_jit_mat4 *a);
void jit_mat4_get_inverse(t_jit_mat4 *b,  t_jit_mat4 *a);
void jit_mat4_get_inverse_rot_trans(t_jit_mat4 *b,  t_jit_mat4 *a);
void jit_mat4_identity(t_jit_mat4 *m);
void jit_mat4_look_at(t_jit_mat4 *m,  t_jit_vec3 *eye,  t_jit_vec3 *center,  t_jit_vec3 *up);
void jit_mat4_frustum(t_jit_mat4 *m, float left, float right, float bottom, float top, float near,  float far);
void jit_mat4_perspective(t_jit_mat4 *m,  float fovy,  float aspect,  float near,  float far);
void jit_mat4_ortho(t_jit_mat4 *m, float left, float right,	float bottom, float top, float near, float far);
void jit_mat4_ortho_view(t_jit_mat4 *m, float lens_angle, float aspect, float n, float f);
void jit_mat4_from_quat( t_jit_mat4 *m, t_jit_quat * q);
void jit_mat4_from_axisangle( t_jit_mat4 *m,  t_jit_vec3 *v, float theta); 
void jit_mat4_from_uv( t_jit_mat4 *m, t_jit_vec3 *u,  t_jit_vec3 *v);
void jit_mat4_from_mat3( t_jit_mat4 *m, t_jit_mat3 *r);
void jit_mat3_from_mat4(t_jit_mat3 *r, t_jit_mat4 *m); 
void jit_mat4_set_scale( t_jit_mat4 *m, t_jit_vec3 *s);
void jit_mat4_get_scale(t_jit_vec3 *s, t_jit_mat4 *m);
void jit_mat4_set_translation(t_jit_mat4 *m, t_jit_vec3 *t);
void jit_mat4_get_translation(t_jit_vec3 *t, t_jit_mat4 *m); 
void jit_mat4_negate(t_jit_mat4 *m);

// ----------------------------------------------------------------------------

float jit_tri_area( t_jit_vec3 *v1,  t_jit_vec3 *v2,  t_jit_vec3 *v3);
float jit_tri_perimeter( t_jit_vec3 *v1,  t_jit_vec3 *v2,  t_jit_vec3 *v3);
float jit_tri_find_in_circle(t_jit_vec3 *center,  t_jit_vec3 *v1,  t_jit_vec3 *v2,  t_jit_vec3 *v3);
float jit_tri_find_circ_circle( t_jit_vec3 *center,  t_jit_vec3 *v1,  t_jit_vec3 *v2,  t_jit_vec3 *v3);

// ----------------------------------------------------------------------------

void jit_ray_get_point(t_jit_vec3 *p, t_jit_ray *ray, float t);
long jit_ray_intersects_plane(float *d, t_jit_ray *ray, t_jit_plane *plane);
long jit_ray_intersects_sphere(float *d, t_jit_ray *ray, t_jit_sphere *sphere, long discard_inside);
long jit_ray_intersects_box(float *d, t_jit_ray *ray, t_jit_aabb *box);
long jit_line_intersects_sphere(t_jit_vec3 *p1, t_jit_line *line, t_jit_sphere *sphere);
void jit_line_closest_sphere(t_jit_vec3 *p1, t_jit_line *line, t_jit_sphere *sphere);

// ----------------------------------------------------------------------------

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}

#endif

#endif
