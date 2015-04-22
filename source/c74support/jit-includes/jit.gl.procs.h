#ifndef _JIT_GL_PROCS_H_
#define _JIT_GL_PROCS_H_

/*
** GLprocs utility for getting function addresses for OpenGL(R) 1.2, 
** OpenGL 1.3, OpenGL 1.4, OpenGL 1.5 and OpenGL extension functions.
**
** Version:  1.1
**
** License Applicability. Except to the extent portions of this file are
** made subject to an alternative license as permitted in the SGI Free
** Software License B, Version 1.1 (the "License"), the contents of this
** file are subject only to the provisions of the License. You may not use
** this file except in compliance with the License. You may obtain a copy
** of the License at Silicon Graphics, Inc., attn: Legal Services, 1600
** Amphitheatre Parkway, Mountain View, CA 94043-1351, or at:
** 
** http://oss.sgi.com/projects/FreeB
** 
** Note that, as provided in the License, the Software is distributed on an
** "AS IS" basis, with ALL EXPRESS AND IMPLIED WARRANTIES AND CONDITIONS
** DISCLAIMED, INCLUDING, WITHOUT LIMITATION, ANY IMPLIED WARRANTIES AND
** CONDITIONS OF MERCHANTABILITY, SATISFACTORY QUALITY, FITNESS FOR A
** PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
** 
** Original Code. The Original Code is: OpenGL Sample Implementation,
** Version 1.2.1, released January 26, 2000, developed by Silicon Graphics,
** Inc. The Original Code is Copyright (c) 1991-2000 Silicon Graphics, Inc.
** Copyright in any portions created by third parties is as indicated
** elsewhere herein. All Rights Reserved.
** 
** Additional Notice Provisions: This software was created using the
** OpenGL(R) version 1.2.1 Sample Implementation published by SGI, but has
** not been independently verified as being compliant with the OpenGL(R)
** version 1.2.1 Specification.
**
** Initial version of glprocs.{c,h} contributed by Intel(R) Corporation.
*/

#ifndef WIN_VERSION
  #ifndef APIENTRY
    #define APIENTRY
  #endif
  #ifdef __GNUC__
    #define _inline __inline__
  #else
    #define _inline
  #endif
#endif

#if defined(MAC_VERSION) && !TARGET_RT_MAC_MACHO
	typedef void* AGLPbuffer;
#endif

/****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

/****************************************************************************/

t_jit_err jit_gl_procs_init();

/* Structure of all OpenGL {1.2, 1.3, 1.4, 1.5}, GL extension procs.*/
typedef struct {
  void (APIENTRY *BlendColor) (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
  void (APIENTRY *BlendEquation) (GLenum mode);
  void (APIENTRY *DrawRangeElements) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);
  void (APIENTRY *ColorTable) (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *table);
  void (APIENTRY *ColorTableParameterfv) (GLenum target, GLenum pname, const GLfloat *params);
  void (APIENTRY *ColorTableParameteriv) (GLenum target, GLenum pname, const GLint *params);
  void (APIENTRY *CopyColorTable) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
  void (APIENTRY *GetColorTable) (GLenum target, GLenum format, GLenum type, GLvoid *table);
  void (APIENTRY *GetColorTableParameterfv) (GLenum target, GLenum pname, GLfloat *params);
  void (APIENTRY *GetColorTableParameteriv) (GLenum target, GLenum pname, GLint *params);
  void (APIENTRY *ColorSubTable) (GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid *data);
  void (APIENTRY *CopyColorSubTable) (GLenum target, GLsizei start, GLint x, GLint y, GLsizei width);
  void (APIENTRY *ConvolutionFilter1D) (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *image);
  void (APIENTRY *ConvolutionFilter2D) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *image);
  void (APIENTRY *ConvolutionParameterf) (GLenum target, GLenum pname, GLfloat params);
  void (APIENTRY *ConvolutionParameterfv) (GLenum target, GLenum pname, const GLfloat *params);
  void (APIENTRY *ConvolutionParameteri) (GLenum target, GLenum pname, GLint params);
  void (APIENTRY *ConvolutionParameteriv) (GLenum target, GLenum pname, const GLint *params);
  void (APIENTRY *CopyConvolutionFilter1D) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
  void (APIENTRY *CopyConvolutionFilter2D) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height);
  void (APIENTRY *GetConvolutionFilter) (GLenum target, GLenum format, GLenum type, GLvoid *image);
  void (APIENTRY *GetConvolutionParameterfv) (GLenum target, GLenum pname, GLfloat *params);
  void (APIENTRY *GetConvolutionParameteriv) (GLenum target, GLenum pname, GLint *params);
  void (APIENTRY *GetSeparableFilter) (GLenum target, GLenum format, GLenum type, GLvoid *row, GLvoid *column, GLvoid *span);
  void (APIENTRY *SeparableFilter2D) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *row, const GLvoid *column);
  void (APIENTRY *GetHistogram) (GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values);
  void (APIENTRY *GetHistogramParameterfv) (GLenum target, GLenum pname, GLfloat *params);
  void (APIENTRY *GetHistogramParameteriv) (GLenum target, GLenum pname, GLint *params);
  void (APIENTRY *GetMinmax) (GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values);
  void (APIENTRY *GetMinmaxParameterfv) (GLenum target, GLenum pname, GLfloat *params);
  void (APIENTRY *GetMinmaxParameteriv) (GLenum target, GLenum pname, GLint *params);
  void (APIENTRY *Histogram) (GLenum target, GLsizei width, GLenum internalformat, GLboolean sink);
  void (APIENTRY *Minmax) (GLenum target, GLenum internalformat, GLboolean sink);
  void (APIENTRY *ResetHistogram) (GLenum target);
  void (APIENTRY *ResetMinmax) (GLenum target);
  void (APIENTRY *TexImage3D) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
  void (APIENTRY *TexSubImage3D) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels);
  void (APIENTRY *CopyTexSubImage3D) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
  void (APIENTRY *ActiveTexture) (GLenum texture);
  void (APIENTRY *ClientActiveTexture) (GLenum texture);
  void (APIENTRY *MultiTexCoord1d) (GLenum target, GLdouble s);
  void (APIENTRY *MultiTexCoord1dv) (GLenum target, const GLdouble *v);
  void (APIENTRY *MultiTexCoord1f) (GLenum target, GLfloat s);
  void (APIENTRY *MultiTexCoord1fv) (GLenum target, const GLfloat *v);
  void (APIENTRY *MultiTexCoord1i) (GLenum target, GLint s);
  void (APIENTRY *MultiTexCoord1iv) (GLenum target, const GLint *v);
  void (APIENTRY *MultiTexCoord1s) (GLenum target, GLshort s);
  void (APIENTRY *MultiTexCoord1sv) (GLenum target, const GLshort *v);
  void (APIENTRY *MultiTexCoord2d) (GLenum target, GLdouble s, GLdouble t);
  void (APIENTRY *MultiTexCoord2dv) (GLenum target, const GLdouble *v);
  void (APIENTRY *MultiTexCoord2f) (GLenum target, GLfloat s, GLfloat t);
  void (APIENTRY *MultiTexCoord2fv) (GLenum target, const GLfloat *v);
  void (APIENTRY *MultiTexCoord2i) (GLenum target, GLint s, GLint t);
  void (APIENTRY *MultiTexCoord2iv) (GLenum target, const GLint *v);
  void (APIENTRY *MultiTexCoord2s) (GLenum target, GLshort s, GLshort t);
  void (APIENTRY *MultiTexCoord2sv) (GLenum target, const GLshort *v);
  void (APIENTRY *MultiTexCoord3d) (GLenum target, GLdouble s, GLdouble t, GLdouble r);
  void (APIENTRY *MultiTexCoord3dv) (GLenum target, const GLdouble *v);
  void (APIENTRY *MultiTexCoord3f) (GLenum target, GLfloat s, GLfloat t, GLfloat r);
  void (APIENTRY *MultiTexCoord3fv) (GLenum target, const GLfloat *v);
  void (APIENTRY *MultiTexCoord3i) (GLenum target, GLint s, GLint t, GLint r);
  void (APIENTRY *MultiTexCoord3iv) (GLenum target, const GLint *v);
  void (APIENTRY *MultiTexCoord3s) (GLenum target, GLshort s, GLshort t, GLshort r);
  void (APIENTRY *MultiTexCoord3sv) (GLenum target, const GLshort *v);
  void (APIENTRY *MultiTexCoord4d) (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
  void (APIENTRY *MultiTexCoord4dv) (GLenum target, const GLdouble *v);
  void (APIENTRY *MultiTexCoord4f) (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
  void (APIENTRY *MultiTexCoord4fv) (GLenum target, const GLfloat *v);
  void (APIENTRY *MultiTexCoord4i) (GLenum target, GLint s, GLint t, GLint r, GLint q);
  void (APIENTRY *MultiTexCoord4iv) (GLenum target, const GLint *v);
  void (APIENTRY *MultiTexCoord4s) (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
  void (APIENTRY *MultiTexCoord4sv) (GLenum target, const GLshort *v);
  void (APIENTRY *LoadTransposeMatrixf) (const GLfloat *m);
  void (APIENTRY *LoadTransposeMatrixd) (const GLdouble *m);
  void (APIENTRY *MultTransposeMatrixf) (const GLfloat *m);
  void (APIENTRY *MultTransposeMatrixd) (const GLdouble *m);
  void (APIENTRY *SampleCoverage) (GLclampf value, GLboolean invert);
  void (APIENTRY *CompressedTexImage3D) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data);
  void (APIENTRY *CompressedTexImage2D) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
  void (APIENTRY *CompressedTexImage1D) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data);
  void (APIENTRY *CompressedTexSubImage3D) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data);
  void (APIENTRY *CompressedTexSubImage2D) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
  void (APIENTRY *CompressedTexSubImage1D) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data);
  void (APIENTRY *GetCompressedTexImage) (GLenum target, GLint level, GLvoid *img);
  void (APIENTRY *BlendFuncSeparate) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
  void (APIENTRY *FogCoordf) (GLfloat coord);
  void (APIENTRY *FogCoordfv) (const GLfloat *coord);
  void (APIENTRY *FogCoordd) (GLdouble coord);
  void (APIENTRY *FogCoorddv) (const GLdouble *coord);
  void (APIENTRY *FogCoordPointer) (GLenum type, GLsizei stride, const GLvoid *pointer);
  void (APIENTRY *MultiDrawArrays) (GLenum mode, GLint *first, GLsizei *count, GLsizei primcount);
  void (APIENTRY *MultiDrawElements) (GLenum mode, const GLsizei *count, GLenum type, const GLvoid* *indices, GLsizei primcount);
  void (APIENTRY *PointParameterf) (GLenum pname, GLfloat param);
  void (APIENTRY *PointParameterfv) (GLenum pname, const GLfloat *params);
  void (APIENTRY *PointParameteri) (GLenum pname, GLint param);
  void (APIENTRY *PointParameteriv) (GLenum pname, const GLint *params);
  void (APIENTRY *SecondaryColor3b) (GLbyte red, GLbyte green, GLbyte blue);
  void (APIENTRY *SecondaryColor3bv) (const GLbyte *v);
  void (APIENTRY *SecondaryColor3d) (GLdouble red, GLdouble green, GLdouble blue);
  void (APIENTRY *SecondaryColor3dv) (const GLdouble *v);
  void (APIENTRY *SecondaryColor3f) (GLfloat red, GLfloat green, GLfloat blue);
  void (APIENTRY *SecondaryColor3fv) (const GLfloat *v);
  void (APIENTRY *SecondaryColor3i) (GLint red, GLint green, GLint blue);
  void (APIENTRY *SecondaryColor3iv) (const GLint *v);
  void (APIENTRY *SecondaryColor3s) (GLshort red, GLshort green, GLshort blue);
  void (APIENTRY *SecondaryColor3sv) (const GLshort *v);
  void (APIENTRY *SecondaryColor3ub) (GLubyte red, GLubyte green, GLubyte blue);
  void (APIENTRY *SecondaryColor3ubv) (const GLubyte *v);
  void (APIENTRY *SecondaryColor3ui) (GLuint red, GLuint green, GLuint blue);
  void (APIENTRY *SecondaryColor3uiv) (const GLuint *v);
  void (APIENTRY *SecondaryColor3us) (GLushort red, GLushort green, GLushort blue);
  void (APIENTRY *SecondaryColor3usv) (const GLushort *v);
  void (APIENTRY *SecondaryColorPointer) (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
  void (APIENTRY *WindowPos2d) (GLdouble x, GLdouble y);
  void (APIENTRY *WindowPos2dv) (const GLdouble *v);
  void (APIENTRY *WindowPos2f) (GLfloat x, GLfloat y);
  void (APIENTRY *WindowPos2fv) (const GLfloat *v);
  void (APIENTRY *WindowPos2i) (GLint x, GLint y);
  void (APIENTRY *WindowPos2iv) (const GLint *v);
  void (APIENTRY *WindowPos2s) (GLshort x, GLshort y);
  void (APIENTRY *WindowPos2sv) (const GLshort *v);
  void (APIENTRY *WindowPos3d) (GLdouble x, GLdouble y, GLdouble z);
  void (APIENTRY *WindowPos3dv) (const GLdouble *v);
  void (APIENTRY *WindowPos3f) (GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *WindowPos3fv) (const GLfloat *v);
  void (APIENTRY *WindowPos3i) (GLint x, GLint y, GLint z);
  void (APIENTRY *WindowPos3iv) (const GLint *v);
  void (APIENTRY *WindowPos3s) (GLshort x, GLshort y, GLshort z);
  void (APIENTRY *WindowPos3sv) (const GLshort *v);
  void (APIENTRY *GenQueries) (GLsizei n, GLuint *ids);
  void (APIENTRY *DeleteQueries) (GLsizei n, const GLuint *ids);
  GLboolean (APIENTRY *IsQuery) (GLuint id);
  void (APIENTRY *BeginQuery) (GLenum target, GLuint id);
  void (APIENTRY *EndQuery) (GLenum target);
  void (APIENTRY *GetQueryiv) (GLenum target, GLenum pname, GLint *params);
  void (APIENTRY *GetQueryObjectiv) (GLuint id, GLenum pname, GLint *params);
  void (APIENTRY *GetQueryObjectuiv) (GLuint id, GLenum pname, GLuint *params);
  void (APIENTRY *BindBuffer) (GLenum target, GLuint buffer);
  void (APIENTRY *DeleteBuffers) (GLsizei n, const GLuint *buffers);
  void (APIENTRY *GenBuffers) (GLsizei n, GLuint *buffers);
  GLboolean (APIENTRY *IsBuffer) (GLuint buffer);
  void (APIENTRY *BufferData) (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
  void (APIENTRY *BufferSubData) (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data);
  void (APIENTRY *GetBufferSubData) (GLenum target, GLintptr offset, GLsizeiptr size, GLvoid *data);
  GLvoid* (APIENTRY *MapBuffer) (GLenum target, GLenum access);
  GLboolean (APIENTRY *UnmapBuffer) (GLenum target);
  void (APIENTRY *GetBufferParameteriv) (GLenum target, GLenum pname, GLint *params);
  void (APIENTRY *GetBufferPointerv) (GLenum target, GLenum pname, GLvoid* *params);
  void (APIENTRY *ActiveTextureARB) (GLenum texture);
  void (APIENTRY *ClientActiveTextureARB) (GLenum texture);
  void (APIENTRY *MultiTexCoord1dARB) (GLenum target, GLdouble s);
  void (APIENTRY *MultiTexCoord1dvARB) (GLenum target, const GLdouble *v);
  void (APIENTRY *MultiTexCoord1fARB) (GLenum target, GLfloat s);
  void (APIENTRY *MultiTexCoord1fvARB) (GLenum target, const GLfloat *v);
  void (APIENTRY *MultiTexCoord1iARB) (GLenum target, GLint s);
  void (APIENTRY *MultiTexCoord1ivARB) (GLenum target, const GLint *v);
  void (APIENTRY *MultiTexCoord1sARB) (GLenum target, GLshort s);
  void (APIENTRY *MultiTexCoord1svARB) (GLenum target, const GLshort *v);
  void (APIENTRY *MultiTexCoord2dARB) (GLenum target, GLdouble s, GLdouble t);
  void (APIENTRY *MultiTexCoord2dvARB) (GLenum target, const GLdouble *v);
  void (APIENTRY *MultiTexCoord2fARB) (GLenum target, GLfloat s, GLfloat t);
  void (APIENTRY *MultiTexCoord2fvARB) (GLenum target, const GLfloat *v);
  void (APIENTRY *MultiTexCoord2iARB) (GLenum target, GLint s, GLint t);
  void (APIENTRY *MultiTexCoord2ivARB) (GLenum target, const GLint *v);
  void (APIENTRY *MultiTexCoord2sARB) (GLenum target, GLshort s, GLshort t);
  void (APIENTRY *MultiTexCoord2svARB) (GLenum target, const GLshort *v);
  void (APIENTRY *MultiTexCoord3dARB) (GLenum target, GLdouble s, GLdouble t, GLdouble r);
  void (APIENTRY *MultiTexCoord3dvARB) (GLenum target, const GLdouble *v);
  void (APIENTRY *MultiTexCoord3fARB) (GLenum target, GLfloat s, GLfloat t, GLfloat r);
  void (APIENTRY *MultiTexCoord3fvARB) (GLenum target, const GLfloat *v);
  void (APIENTRY *MultiTexCoord3iARB) (GLenum target, GLint s, GLint t, GLint r);
  void (APIENTRY *MultiTexCoord3ivARB) (GLenum target, const GLint *v);
  void (APIENTRY *MultiTexCoord3sARB) (GLenum target, GLshort s, GLshort t, GLshort r);
  void (APIENTRY *MultiTexCoord3svARB) (GLenum target, const GLshort *v);
  void (APIENTRY *MultiTexCoord4dARB) (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
  void (APIENTRY *MultiTexCoord4dvARB) (GLenum target, const GLdouble *v);
  void (APIENTRY *MultiTexCoord4fARB) (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
  void (APIENTRY *MultiTexCoord4fvARB) (GLenum target, const GLfloat *v);
  void (APIENTRY *MultiTexCoord4iARB) (GLenum target, GLint s, GLint t, GLint r, GLint q);
  void (APIENTRY *MultiTexCoord4ivARB) (GLenum target, const GLint *v);
  void (APIENTRY *MultiTexCoord4sARB) (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
  void (APIENTRY *MultiTexCoord4svARB) (GLenum target, const GLshort *v);
  void (APIENTRY *LoadTransposeMatrixfARB) (const GLfloat *m);
  void (APIENTRY *LoadTransposeMatrixdARB) (const GLdouble *m);
  void (APIENTRY *MultTransposeMatrixfARB) (const GLfloat *m);
  void (APIENTRY *MultTransposeMatrixdARB) (const GLdouble *m);
  void (APIENTRY *SampleCoverageARB) (GLclampf value, GLboolean invert);
  void (APIENTRY *CompressedTexImage3DARB) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data);
  void (APIENTRY *CompressedTexImage2DARB) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
  void (APIENTRY *CompressedTexImage1DARB) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data);
  void (APIENTRY *CompressedTexSubImage3DARB) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data);
  void (APIENTRY *CompressedTexSubImage2DARB) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
  void (APIENTRY *CompressedTexSubImage1DARB) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data);
  void (APIENTRY *GetCompressedTexImageARB) (GLenum target, GLint level, GLvoid *img);
  void (APIENTRY *PointParameterfARB) (GLenum pname, GLfloat param);
  void (APIENTRY *PointParameterfvARB) (GLenum pname, const GLfloat *params);
  void (APIENTRY *WeightbvARB) (GLint size, const GLbyte *weights);
  void (APIENTRY *WeightsvARB) (GLint size, const GLshort *weights);
  void (APIENTRY *WeightivARB) (GLint size, const GLint *weights);
  void (APIENTRY *WeightfvARB) (GLint size, const GLfloat *weights);
  void (APIENTRY *WeightdvARB) (GLint size, const GLdouble *weights);
  void (APIENTRY *WeightubvARB) (GLint size, const GLubyte *weights);
  void (APIENTRY *WeightusvARB) (GLint size, const GLushort *weights);
  void (APIENTRY *WeightuivARB) (GLint size, const GLuint *weights);
  void (APIENTRY *WeightPointerARB) (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
  void (APIENTRY *VertexBlendARB) (GLint count);
  void (APIENTRY *CurrentPaletteMatrixARB) (GLint index);
  void (APIENTRY *MatrixIndexubvARB) (GLint size, const GLubyte *indices);
  void (APIENTRY *MatrixIndexusvARB) (GLint size, const GLushort *indices);
  void (APIENTRY *MatrixIndexuivARB) (GLint size, const GLuint *indices);
  void (APIENTRY *MatrixIndexPointerARB) (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
  void (APIENTRY *WindowPos2dARB) (GLdouble x, GLdouble y);
  void (APIENTRY *WindowPos2dvARB) (const GLdouble *v);
  void (APIENTRY *WindowPos2fARB) (GLfloat x, GLfloat y);
  void (APIENTRY *WindowPos2fvARB) (const GLfloat *v);
  void (APIENTRY *WindowPos2iARB) (GLint x, GLint y);
  void (APIENTRY *WindowPos2ivARB) (const GLint *v);
  void (APIENTRY *WindowPos2sARB) (GLshort x, GLshort y);
  void (APIENTRY *WindowPos2svARB) (const GLshort *v);
  void (APIENTRY *WindowPos3dARB) (GLdouble x, GLdouble y, GLdouble z);
  void (APIENTRY *WindowPos3dvARB) (const GLdouble *v);
  void (APIENTRY *WindowPos3fARB) (GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *WindowPos3fvARB) (const GLfloat *v);
  void (APIENTRY *WindowPos3iARB) (GLint x, GLint y, GLint z);
  void (APIENTRY *WindowPos3ivARB) (const GLint *v);
  void (APIENTRY *WindowPos3sARB) (GLshort x, GLshort y, GLshort z);
  void (APIENTRY *WindowPos3svARB) (const GLshort *v);
  void (APIENTRY *VertexAttrib1dARB) (GLuint index, GLdouble x);
  void (APIENTRY *VertexAttrib1dvARB) (GLuint index, const GLdouble *v);
  void (APIENTRY *VertexAttrib1fARB) (GLuint index, GLfloat x);
  void (APIENTRY *VertexAttrib1fvARB) (GLuint index, const GLfloat *v);
  void (APIENTRY *VertexAttrib1sARB) (GLuint index, GLshort x);
  void (APIENTRY *VertexAttrib1svARB) (GLuint index, const GLshort *v);
  void (APIENTRY *VertexAttrib2dARB) (GLuint index, GLdouble x, GLdouble y);
  void (APIENTRY *VertexAttrib2dvARB) (GLuint index, const GLdouble *v);
  void (APIENTRY *VertexAttrib2fARB) (GLuint index, GLfloat x, GLfloat y);
  void (APIENTRY *VertexAttrib2fvARB) (GLuint index, const GLfloat *v);
  void (APIENTRY *VertexAttrib2sARB) (GLuint index, GLshort x, GLshort y);
  void (APIENTRY *VertexAttrib2svARB) (GLuint index, const GLshort *v);
  void (APIENTRY *VertexAttrib3dARB) (GLuint index, GLdouble x, GLdouble y, GLdouble z);
  void (APIENTRY *VertexAttrib3dvARB) (GLuint index, const GLdouble *v);
  void (APIENTRY *VertexAttrib3fARB) (GLuint index, GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *VertexAttrib3fvARB) (GLuint index, const GLfloat *v);
  void (APIENTRY *VertexAttrib3sARB) (GLuint index, GLshort x, GLshort y, GLshort z);
  void (APIENTRY *VertexAttrib3svARB) (GLuint index, const GLshort *v);
  void (APIENTRY *VertexAttrib4NbvARB) (GLuint index, const GLbyte *v);
  void (APIENTRY *VertexAttrib4NivARB) (GLuint index, const GLint *v);
  void (APIENTRY *VertexAttrib4NsvARB) (GLuint index, const GLshort *v);
  void (APIENTRY *VertexAttrib4NubARB) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
  void (APIENTRY *VertexAttrib4NubvARB) (GLuint index, const GLubyte *v);
  void (APIENTRY *VertexAttrib4NuivARB) (GLuint index, const GLuint *v);
  void (APIENTRY *VertexAttrib4NusvARB) (GLuint index, const GLushort *v);
  void (APIENTRY *VertexAttrib4bvARB) (GLuint index, const GLbyte *v);
  void (APIENTRY *VertexAttrib4dARB) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
  void (APIENTRY *VertexAttrib4dvARB) (GLuint index, const GLdouble *v);
  void (APIENTRY *VertexAttrib4fARB) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
  void (APIENTRY *VertexAttrib4fvARB) (GLuint index, const GLfloat *v);
  void (APIENTRY *VertexAttrib4ivARB) (GLuint index, const GLint *v);
  void (APIENTRY *VertexAttrib4sARB) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
  void (APIENTRY *VertexAttrib4svARB) (GLuint index, const GLshort *v);
  void (APIENTRY *VertexAttrib4ubvARB) (GLuint index, const GLubyte *v);
  void (APIENTRY *VertexAttrib4uivARB) (GLuint index, const GLuint *v);
  void (APIENTRY *VertexAttrib4usvARB) (GLuint index, const GLushort *v);
  void (APIENTRY *VertexAttribPointerARB) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);
  void (APIENTRY *EnableVertexAttribArrayARB) (GLuint index);
  void (APIENTRY *DisableVertexAttribArrayARB) (GLuint index);
  void (APIENTRY *ProgramStringARB) (GLenum target, GLenum format, GLsizei len, const GLvoid *string);
  void (APIENTRY *BindProgramARB) (GLenum target, GLuint program);
  void (APIENTRY *DeleteProgramsARB) (GLsizei n, const GLuint *programs);
  void (APIENTRY *GenProgramsARB) (GLsizei n, GLuint *programs);
  void (APIENTRY *ProgramEnvParameter4dARB) (GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
  void (APIENTRY *ProgramEnvParameter4dvARB) (GLenum target, GLuint index, const GLdouble *params);
  void (APIENTRY *ProgramEnvParameter4fARB) (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
  void (APIENTRY *ProgramEnvParameter4fvARB) (GLenum target, GLuint index, const GLfloat *params);
  void (APIENTRY *ProgramLocalParameter4dARB) (GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
  void (APIENTRY *ProgramLocalParameter4dvARB) (GLenum target, GLuint index, const GLdouble *params);
  void (APIENTRY *ProgramLocalParameter4fARB) (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
  void (APIENTRY *ProgramLocalParameter4fvARB) (GLenum target, GLuint index, const GLfloat *params);
  void (APIENTRY *GetProgramEnvParameterdvARB) (GLenum target, GLuint index, GLdouble *params);
  void (APIENTRY *GetProgramEnvParameterfvARB) (GLenum target, GLuint index, GLfloat *params);
  void (APIENTRY *GetProgramLocalParameterdvARB) (GLenum target, GLuint index, GLdouble *params);
  void (APIENTRY *GetProgramLocalParameterfvARB) (GLenum target, GLuint index, GLfloat *params);
  void (APIENTRY *GetProgramivARB) (GLenum target, GLenum pname, GLint *params);
  void (APIENTRY *GetProgramStringARB) (GLenum target, GLenum pname, GLvoid *string);
  void (APIENTRY *GetVertexAttribdvARB) (GLuint index, GLenum pname, GLdouble *params);
  void (APIENTRY *GetVertexAttribfvARB) (GLuint index, GLenum pname, GLfloat *params);
  void (APIENTRY *GetVertexAttribivARB) (GLuint index, GLenum pname, GLint *params);
  void (APIENTRY *GetVertexAttribPointervARB) (GLuint index, GLenum pname, GLvoid* *pointer);
  GLboolean (APIENTRY *IsProgramARB) (GLuint program);
  void (APIENTRY *BindBufferARB) (GLenum target, GLuint buffer);
  void (APIENTRY *DeleteBuffersARB) (GLsizei n, const GLuint *buffers);
  void (APIENTRY *GenBuffersARB) (GLsizei n, GLuint *buffers);
  GLboolean (APIENTRY *IsBufferARB) (GLuint buffer);
  void (APIENTRY *BufferDataARB) (GLenum target, GLsizeiptrARB size, const GLvoid *data, GLenum usage);
  void (APIENTRY *BufferSubDataARB) (GLenum target, GLintptrARB offset, GLsizeiptrARB size, const GLvoid *data);
  void (APIENTRY *GetBufferSubDataARB) (GLenum target, GLintptrARB offset, GLsizeiptrARB size, GLvoid *data);
  GLvoid* (APIENTRY *MapBufferARB) (GLenum target, GLenum access);
  GLboolean (APIENTRY *UnmapBufferARB) (GLenum target);
  void (APIENTRY *GetBufferParameterivARB) (GLenum target, GLenum pname, GLint *params);
  void (APIENTRY *GetBufferPointervARB) (GLenum target, GLenum pname, GLvoid* *params);
  void (APIENTRY *GenQueriesARB) (GLsizei n, GLuint *ids);
  void (APIENTRY *DeleteQueriesARB) (GLsizei n, const GLuint *ids);
  GLboolean (APIENTRY *IsQueryARB) (GLuint id);
  void (APIENTRY *BeginQueryARB) (GLenum target, GLuint id);
  void (APIENTRY *EndQueryARB) (GLenum target);
  void (APIENTRY *GetQueryivARB) (GLenum target, GLenum pname, GLint *params);
  void (APIENTRY *GetQueryObjectivARB) (GLuint id, GLenum pname, GLint *params);
  void (APIENTRY *GetQueryObjectuivARB) (GLuint id, GLenum pname, GLuint *params);
  void (APIENTRY *DeleteObjectARB) (GLhandleARB obj);
  GLhandleARB (APIENTRY *GetHandleARB) (GLenum pname);
  void (APIENTRY *DetachObjectARB) (GLhandleARB containerObj, GLhandleARB attachedObj);
  GLhandleARB (APIENTRY *CreateShaderObjectARB) (GLenum shaderType);
  void (APIENTRY *ShaderSourceARB) (GLhandleARB shaderObj, GLsizei count, const GLcharARB* *string, const GLint *length);
  void (APIENTRY *CompileShaderARB) (GLhandleARB shaderObj);
  GLhandleARB (APIENTRY *CreateProgramObjectARB) (void);
  void (APIENTRY *AttachObjectARB) (GLhandleARB containerObj, GLhandleARB obj);
  void (APIENTRY *LinkProgramARB) (GLhandleARB programObj);
  void (APIENTRY *UseProgramObjectARB) (GLhandleARB programObj);
  void (APIENTRY *ValidateProgramARB) (GLhandleARB programObj);
  void (APIENTRY *Uniform1fARB) (GLint location, GLfloat v0);
  void (APIENTRY *Uniform2fARB) (GLint location, GLfloat v0, GLfloat v1);
  void (APIENTRY *Uniform3fARB) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
  void (APIENTRY *Uniform4fARB) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
  void (APIENTRY *Uniform1iARB) (GLint location, GLint v0);
  void (APIENTRY *Uniform2iARB) (GLint location, GLint v0, GLint v1);
  void (APIENTRY *Uniform3iARB) (GLint location, GLint v0, GLint v1, GLint v2);
  void (APIENTRY *Uniform4iARB) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
  void (APIENTRY *Uniform1fvARB) (GLint location, GLsizei count, const GLfloat *value);
  void (APIENTRY *Uniform2fvARB) (GLint location, GLsizei count, const GLfloat *value);
  void (APIENTRY *Uniform3fvARB) (GLint location, GLsizei count, const GLfloat *value);
  void (APIENTRY *Uniform4fvARB) (GLint location, GLsizei count, const GLfloat *value);
  void (APIENTRY *Uniform1ivARB) (GLint location, GLsizei count, const GLint *value);
  void (APIENTRY *Uniform2ivARB) (GLint location, GLsizei count, const GLint *value);
  void (APIENTRY *Uniform3ivARB) (GLint location, GLsizei count, const GLint *value);
  void (APIENTRY *Uniform4ivARB) (GLint location, GLsizei count, const GLint *value);
  void (APIENTRY *UniformMatrix2fvARB) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
  void (APIENTRY *UniformMatrix3fvARB) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
  void (APIENTRY *UniformMatrix4fvARB) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
  void (APIENTRY *GetObjectParameterfvARB) (GLhandleARB obj, GLenum pname, GLfloat *params);
  void (APIENTRY *GetObjectParameterivARB) (GLhandleARB obj, GLenum pname, GLint *params);
  void (APIENTRY *GetInfoLogARB) (GLhandleARB obj, GLsizei maxLength, GLsizei *length, GLcharARB *infoLog);
  void (APIENTRY *GetAttachedObjectsARB) (GLhandleARB containerObj, GLsizei maxCount, GLsizei *count, GLhandleARB *obj);
  GLint (APIENTRY *GetUniformLocationARB) (GLhandleARB programObj, const GLcharARB *name);
  void (APIENTRY *GetActiveUniformARB) (GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei *length, GLint *size, GLenum *type, GLcharARB *name);
  void (APIENTRY *GetUniformfvARB) (GLhandleARB programObj, GLint location, GLfloat *params);
  void (APIENTRY *GetUniformivARB) (GLhandleARB programObj, GLint location, GLint *params);
  void (APIENTRY *GetShaderSourceARB) (GLhandleARB obj, GLsizei maxLength, GLsizei *length, GLcharARB *source);
  void (APIENTRY *BindAttribLocationARB) (GLhandleARB programObj, GLuint index, const GLcharARB *name);
  void (APIENTRY *GetActiveAttribARB) (GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei *length, GLint *size, GLenum *type, GLcharARB *name);
  GLint (APIENTRY *GetAttribLocationARB) (GLhandleARB programObj, const GLcharARB *name);
  void (APIENTRY *BlendColorEXT) (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
  void (APIENTRY *PolygonOffsetEXT) (GLfloat factor, GLfloat bias);
  void (APIENTRY *TexImage3DEXT) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
  void (APIENTRY *TexSubImage3DEXT) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels);
  void (APIENTRY *GetTexFilterFuncSGIS) (GLenum target, GLenum filter, GLfloat *weights);
  void (APIENTRY *TexFilterFuncSGIS) (GLenum target, GLenum filter, GLsizei n, const GLfloat *weights);
  void (APIENTRY *TexSubImage1DEXT) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
  void (APIENTRY *TexSubImage2DEXT) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
  void (APIENTRY *CopyTexImage1DEXT) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
  void (APIENTRY *CopyTexImage2DEXT) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
  void (APIENTRY *CopyTexSubImage1DEXT) (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
  void (APIENTRY *CopyTexSubImage2DEXT) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
  void (APIENTRY *CopyTexSubImage3DEXT) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
  void (APIENTRY *GetHistogramEXT) (GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values);
  void (APIENTRY *GetHistogramParameterfvEXT) (GLenum target, GLenum pname, GLfloat *params);
  void (APIENTRY *GetHistogramParameterivEXT) (GLenum target, GLenum pname, GLint *params);
  void (APIENTRY *GetMinmaxEXT) (GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values);
  void (APIENTRY *GetMinmaxParameterfvEXT) (GLenum target, GLenum pname, GLfloat *params);
  void (APIENTRY *GetMinmaxParameterivEXT) (GLenum target, GLenum pname, GLint *params);
  void (APIENTRY *HistogramEXT) (GLenum target, GLsizei width, GLenum internalformat, GLboolean sink);
  void (APIENTRY *MinmaxEXT) (GLenum target, GLenum internalformat, GLboolean sink);
  void (APIENTRY *ResetHistogramEXT) (GLenum target);
  void (APIENTRY *ResetMinmaxEXT) (GLenum target);
  void (APIENTRY *ConvolutionFilter1DEXT) (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *image);
  void (APIENTRY *ConvolutionFilter2DEXT) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *image);
  void (APIENTRY *ConvolutionParameterfEXT) (GLenum target, GLenum pname, GLfloat params);
  void (APIENTRY *ConvolutionParameterfvEXT) (GLenum target, GLenum pname, const GLfloat *params);
  void (APIENTRY *ConvolutionParameteriEXT) (GLenum target, GLenum pname, GLint params);
  void (APIENTRY *ConvolutionParameterivEXT) (GLenum target, GLenum pname, const GLint *params);
  void (APIENTRY *CopyConvolutionFilter1DEXT) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
  void (APIENTRY *CopyConvolutionFilter2DEXT) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height);
  void (APIENTRY *GetConvolutionFilterEXT) (GLenum target, GLenum format, GLenum type, GLvoid *image);
  void (APIENTRY *GetConvolutionParameterfvEXT) (GLenum target, GLenum pname, GLfloat *params);
  void (APIENTRY *GetConvolutionParameterivEXT) (GLenum target, GLenum pname, GLint *params);
  void (APIENTRY *GetSeparableFilterEXT) (GLenum target, GLenum format, GLenum type, GLvoid *row, GLvoid *column, GLvoid *span);
  void (APIENTRY *SeparableFilter2DEXT) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *row, const GLvoid *column);
  void (APIENTRY *ColorTableSGI) (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *table);
  void (APIENTRY *ColorTableParameterfvSGI) (GLenum target, GLenum pname, const GLfloat *params);
  void (APIENTRY *ColorTableParameterivSGI) (GLenum target, GLenum pname, const GLint *params);
  void (APIENTRY *CopyColorTableSGI) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
  void (APIENTRY *GetColorTableSGI) (GLenum target, GLenum format, GLenum type, GLvoid *table);
  void (APIENTRY *GetColorTableParameterfvSGI) (GLenum target, GLenum pname, GLfloat *params);
  void (APIENTRY *GetColorTableParameterivSGI) (GLenum target, GLenum pname, GLint *params);
  void (APIENTRY *PixelTexGenSGIX) (GLenum mode);
  void (APIENTRY *PixelTexGenParameteriSGIS) (GLenum pname, GLint param);
  void (APIENTRY *PixelTexGenParameterivSGIS) (GLenum pname, const GLint *params);
  void (APIENTRY *PixelTexGenParameterfSGIS) (GLenum pname, GLfloat param);
  void (APIENTRY *PixelTexGenParameterfvSGIS) (GLenum pname, const GLfloat *params);
  void (APIENTRY *GetPixelTexGenParameterivSGIS) (GLenum pname, GLint *params);
  void (APIENTRY *GetPixelTexGenParameterfvSGIS) (GLenum pname, GLfloat *params);
  void (APIENTRY *TexImage4DSGIS) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
  void (APIENTRY *TexSubImage4DSGIS) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint woffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLenum format, GLenum type, const GLvoid *pixels);
  GLboolean (APIENTRY *AreTexturesResidentEXT) (GLsizei n, const GLuint *textures, GLboolean *residences);
  void (APIENTRY *BindTextureEXT) (GLenum target, GLuint texture);
  void (APIENTRY *DeleteTexturesEXT) (GLsizei n, const GLuint *textures);
  void (APIENTRY *GenTexturesEXT) (GLsizei n, GLuint *textures);
  GLboolean (APIENTRY *IsTextureEXT) (GLuint texture);
  void (APIENTRY *PrioritizeTexturesEXT) (GLsizei n, const GLuint *textures, const GLclampf *priorities);
  void (APIENTRY *DetailTexFuncSGIS) (GLenum target, GLsizei n, const GLfloat *points);
  void (APIENTRY *GetDetailTexFuncSGIS) (GLenum target, GLfloat *points);
  void (APIENTRY *SharpenTexFuncSGIS) (GLenum target, GLsizei n, const GLfloat *points);
  void (APIENTRY *GetSharpenTexFuncSGIS) (GLenum target, GLfloat *points);
  void (APIENTRY *SampleMaskSGIS) (GLclampf value, GLboolean invert);
  void (APIENTRY *SamplePatternSGIS) (GLenum pattern);
  void (APIENTRY *ArrayElementEXT) (GLint i);
  void (APIENTRY *ColorPointerEXT) (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
  void (APIENTRY *DrawArraysEXT) (GLenum mode, GLint first, GLsizei count);
  void (APIENTRY *EdgeFlagPointerEXT) (GLsizei stride, GLsizei count, const GLboolean *pointer);
  void (APIENTRY *GetPointervEXT) (GLenum pname, GLvoid* *params);
  void (APIENTRY *IndexPointerEXT) (GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
  void (APIENTRY *NormalPointerEXT) (GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
  void (APIENTRY *TexCoordPointerEXT) (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
  void (APIENTRY *VertexPointerEXT) (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
  void (APIENTRY *BlendEquationEXT) (GLenum mode);
  void (APIENTRY *SpriteParameterfSGIX) (GLenum pname, GLfloat param);
  void (APIENTRY *SpriteParameterfvSGIX) (GLenum pname, const GLfloat *params);
  void (APIENTRY *SpriteParameteriSGIX) (GLenum pname, GLint param);
  void (APIENTRY *SpriteParameterivSGIX) (GLenum pname, const GLint *params);
  void (APIENTRY *PointParameterfEXT) (GLenum pname, GLfloat param);
  void (APIENTRY *PointParameterfvEXT) (GLenum pname, const GLfloat *params);
  void (APIENTRY *PointParameterfSGIS) (GLenum pname, GLfloat param);
  void (APIENTRY *PointParameterfvSGIS) (GLenum pname, const GLfloat *params);
  GLint (APIENTRY *GetInstrumentsSGIX) (void);
  void (APIENTRY *InstrumentsBufferSGIX) (GLsizei size, GLint *buffer);
  GLint (APIENTRY *PollInstrumentsSGIX) (GLint *marker_p);
  void (APIENTRY *ReadInstrumentsSGIX) (GLint marker);
  void (APIENTRY *StartInstrumentsSGIX) (void);
  void (APIENTRY *StopInstrumentsSGIX) (GLint marker);
  void (APIENTRY *FrameZoomSGIX) (GLint factor);
  void (APIENTRY *TagSampleBufferSGIX) (void);
  void (APIENTRY *DeformationMap3dSGIX) (GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, GLdouble w1, GLdouble w2, GLint wstride, GLint worder, const GLdouble *points);
  void (APIENTRY *DeformationMap3fSGIX) (GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, GLfloat w1, GLfloat w2, GLint wstride, GLint worder, const GLfloat *points);
  void (APIENTRY *DeformSGIX) (GLbitfield mask);
  void (APIENTRY *LoadIdentityDeformationMapSGIX) (GLbitfield mask);
  void (APIENTRY *ReferencePlaneSGIX) (const GLdouble *equation);
  void (APIENTRY *FlushRasterSGIX) (void);
  void (APIENTRY *FogFuncSGIS) (GLsizei n, const GLfloat *points);
  void (APIENTRY *GetFogFuncSGIS) (GLfloat *points);
  void (APIENTRY *ImageTransformParameteriHP) (GLenum target, GLenum pname, GLint param);
  void (APIENTRY *ImageTransformParameterfHP) (GLenum target, GLenum pname, GLfloat param);
  void (APIENTRY *ImageTransformParameterivHP) (GLenum target, GLenum pname, const GLint *params);
  void (APIENTRY *ImageTransformParameterfvHP) (GLenum target, GLenum pname, const GLfloat *params);
  void (APIENTRY *GetImageTransformParameterivHP) (GLenum target, GLenum pname, GLint *params);
  void (APIENTRY *GetImageTransformParameterfvHP) (GLenum target, GLenum pname, GLfloat *params);
  void (APIENTRY *ColorSubTableEXT) (GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid *data);
  void (APIENTRY *CopyColorSubTableEXT) (GLenum target, GLsizei start, GLint x, GLint y, GLsizei width);
  void (APIENTRY *HintPGI) (GLenum target, GLint mode);
  void (APIENTRY *ColorTableEXT) (GLenum target, GLenum internalFormat, GLsizei width, GLenum format, GLenum type, const GLvoid *table);
  void (APIENTRY *GetColorTableEXT) (GLenum target, GLenum format, GLenum type, GLvoid *data);
  void (APIENTRY *GetColorTableParameterivEXT) (GLenum target, GLenum pname, GLint *params);
  void (APIENTRY *GetColorTableParameterfvEXT) (GLenum target, GLenum pname, GLfloat *params);
  void (APIENTRY *GetListParameterfvSGIX) (GLuint list, GLenum pname, GLfloat *params);
  void (APIENTRY *GetListParameterivSGIX) (GLuint list, GLenum pname, GLint *params);
  void (APIENTRY *ListParameterfSGIX) (GLuint list, GLenum pname, GLfloat param);
  void (APIENTRY *ListParameterfvSGIX) (GLuint list, GLenum pname, const GLfloat *params);
  void (APIENTRY *ListParameteriSGIX) (GLuint list, GLenum pname, GLint param);
  void (APIENTRY *ListParameterivSGIX) (GLuint list, GLenum pname, const GLint *params);
  void (APIENTRY *IndexMaterialEXT) (GLenum face, GLenum mode);
  void (APIENTRY *IndexFuncEXT) (GLenum func, GLclampf ref);
  void (APIENTRY *LockArraysEXT) (GLint first, GLsizei count);
  void (APIENTRY *UnlockArraysEXT) (void);
  void (APIENTRY *CullParameterdvEXT) (GLenum pname, GLdouble *params);
  void (APIENTRY *CullParameterfvEXT) (GLenum pname, GLfloat *params);
  void (APIENTRY *FragmentColorMaterialSGIX) (GLenum face, GLenum mode);
  void (APIENTRY *FragmentLightfSGIX) (GLenum light, GLenum pname, GLfloat param);
  void (APIENTRY *FragmentLightfvSGIX) (GLenum light, GLenum pname, const GLfloat *params);
  void (APIENTRY *FragmentLightiSGIX) (GLenum light, GLenum pname, GLint param);
  void (APIENTRY *FragmentLightivSGIX) (GLenum light, GLenum pname, const GLint *params);
  void (APIENTRY *FragmentLightModelfSGIX) (GLenum pname, GLfloat param);
  void (APIENTRY *FragmentLightModelfvSGIX) (GLenum pname, const GLfloat *params);
  void (APIENTRY *FragmentLightModeliSGIX) (GLenum pname, GLint param);
  void (APIENTRY *FragmentLightModelivSGIX) (GLenum pname, const GLint *params);
  void (APIENTRY *FragmentMaterialfSGIX) (GLenum face, GLenum pname, GLfloat param);
  void (APIENTRY *FragmentMaterialfvSGIX) (GLenum face, GLenum pname, const GLfloat *params);
  void (APIENTRY *FragmentMaterialiSGIX) (GLenum face, GLenum pname, GLint param);
  void (APIENTRY *FragmentMaterialivSGIX) (GLenum face, GLenum pname, const GLint *params);
  void (APIENTRY *GetFragmentLightfvSGIX) (GLenum light, GLenum pname, GLfloat *params);
  void (APIENTRY *GetFragmentLightivSGIX) (GLenum light, GLenum pname, GLint *params);
  void (APIENTRY *GetFragmentMaterialfvSGIX) (GLenum face, GLenum pname, GLfloat *params);
  void (APIENTRY *GetFragmentMaterialivSGIX) (GLenum face, GLenum pname, GLint *params);
  void (APIENTRY *LightEnviSGIX) (GLenum pname, GLint param);
  void (APIENTRY *DrawRangeElementsEXT) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);
  void (APIENTRY *ApplyTextureEXT) (GLenum mode);
  void (APIENTRY *TextureLightEXT) (GLenum pname);
  void (APIENTRY *TextureMaterialEXT) (GLenum face, GLenum mode);
  void (APIENTRY *AsyncMarkerSGIX) (GLuint marker);
  GLint (APIENTRY *FinishAsyncSGIX) (GLuint *markerp);
  GLint (APIENTRY *PollAsyncSGIX) (GLuint *markerp);
  GLuint (APIENTRY *GenAsyncMarkersSGIX) (GLsizei range);
  void (APIENTRY *DeleteAsyncMarkersSGIX) (GLuint marker, GLsizei range);
  GLboolean (APIENTRY *IsAsyncMarkerSGIX) (GLuint marker);
  void (APIENTRY *VertexPointervINTEL) (GLint size, GLenum type, const GLvoid* *pointer);
  void (APIENTRY *NormalPointervINTEL) (GLenum type, const GLvoid* *pointer);
  void (APIENTRY *ColorPointervINTEL) (GLint size, GLenum type, const GLvoid* *pointer);
  void (APIENTRY *TexCoordPointervINTEL) (GLint size, GLenum type, const GLvoid* *pointer);
  void (APIENTRY *PixelTransformParameteriEXT) (GLenum target, GLenum pname, GLint param);
  void (APIENTRY *PixelTransformParameterfEXT) (GLenum target, GLenum pname, GLfloat param);
  void (APIENTRY *PixelTransformParameterivEXT) (GLenum target, GLenum pname, const GLint *params);
  void (APIENTRY *PixelTransformParameterfvEXT) (GLenum target, GLenum pname, const GLfloat *params);
  void (APIENTRY *SecondaryColor3bEXT) (GLbyte red, GLbyte green, GLbyte blue);
  void (APIENTRY *SecondaryColor3bvEXT) (const GLbyte *v);
  void (APIENTRY *SecondaryColor3dEXT) (GLdouble red, GLdouble green, GLdouble blue);
  void (APIENTRY *SecondaryColor3dvEXT) (const GLdouble *v);
  void (APIENTRY *SecondaryColor3fEXT) (GLfloat red, GLfloat green, GLfloat blue);
  void (APIENTRY *SecondaryColor3fvEXT) (const GLfloat *v);
  void (APIENTRY *SecondaryColor3iEXT) (GLint red, GLint green, GLint blue);
  void (APIENTRY *SecondaryColor3ivEXT) (const GLint *v);
  void (APIENTRY *SecondaryColor3sEXT) (GLshort red, GLshort green, GLshort blue);
  void (APIENTRY *SecondaryColor3svEXT) (const GLshort *v);
  void (APIENTRY *SecondaryColor3ubEXT) (GLubyte red, GLubyte green, GLubyte blue);
  void (APIENTRY *SecondaryColor3ubvEXT) (const GLubyte *v);
  void (APIENTRY *SecondaryColor3uiEXT) (GLuint red, GLuint green, GLuint blue);
  void (APIENTRY *SecondaryColor3uivEXT) (const GLuint *v);
  void (APIENTRY *SecondaryColor3usEXT) (GLushort red, GLushort green, GLushort blue);
  void (APIENTRY *SecondaryColor3usvEXT) (const GLushort *v);
  void (APIENTRY *SecondaryColorPointerEXT) (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
  void (APIENTRY *TextureNormalEXT) (GLenum mode);
  void (APIENTRY *MultiDrawArraysEXT) (GLenum mode, GLint *first, GLsizei *count, GLsizei primcount);
  void (APIENTRY *MultiDrawElementsEXT) (GLenum mode, const GLsizei *count, GLenum type, const GLvoid* *indices, GLsizei primcount);
  void (APIENTRY *FogCoordfEXT) (GLfloat coord);
  void (APIENTRY *FogCoordfvEXT) (const GLfloat *coord);
  void (APIENTRY *FogCoorddEXT) (GLdouble coord);
  void (APIENTRY *FogCoorddvEXT) (const GLdouble *coord);
  void (APIENTRY *FogCoordPointerEXT) (GLenum type, GLsizei stride, const GLvoid *pointer);
  void (APIENTRY *Tangent3bEXT) (GLbyte tx, GLbyte ty, GLbyte tz);
  void (APIENTRY *Tangent3bvEXT) (const GLbyte *v);
  void (APIENTRY *Tangent3dEXT) (GLdouble tx, GLdouble ty, GLdouble tz);
  void (APIENTRY *Tangent3dvEXT) (const GLdouble *v);
  void (APIENTRY *Tangent3fEXT) (GLfloat tx, GLfloat ty, GLfloat tz);
  void (APIENTRY *Tangent3fvEXT) (const GLfloat *v);
  void (APIENTRY *Tangent3iEXT) (GLint tx, GLint ty, GLint tz);
  void (APIENTRY *Tangent3ivEXT) (const GLint *v);
  void (APIENTRY *Tangent3sEXT) (GLshort tx, GLshort ty, GLshort tz);
  void (APIENTRY *Tangent3svEXT) (const GLshort *v);
  void (APIENTRY *Binormal3bEXT) (GLbyte bx, GLbyte by, GLbyte bz);
  void (APIENTRY *Binormal3bvEXT) (const GLbyte *v);
  void (APIENTRY *Binormal3dEXT) (GLdouble bx, GLdouble by, GLdouble bz);
  void (APIENTRY *Binormal3dvEXT) (const GLdouble *v);
  void (APIENTRY *Binormal3fEXT) (GLfloat bx, GLfloat by, GLfloat bz);
  void (APIENTRY *Binormal3fvEXT) (const GLfloat *v);
  void (APIENTRY *Binormal3iEXT) (GLint bx, GLint by, GLint bz);
  void (APIENTRY *Binormal3ivEXT) (const GLint *v);
  void (APIENTRY *Binormal3sEXT) (GLshort bx, GLshort by, GLshort bz);
  void (APIENTRY *Binormal3svEXT) (const GLshort *v);
  void (APIENTRY *TangentPointerEXT) (GLenum type, GLsizei stride, const GLvoid *pointer);
  void (APIENTRY *BinormalPointerEXT) (GLenum type, GLsizei stride, const GLvoid *pointer);
  void (APIENTRY *FinishTextureSUNX) (void);
  void (APIENTRY *GlobalAlphaFactorbSUN) (GLbyte factor);
  void (APIENTRY *GlobalAlphaFactorsSUN) (GLshort factor);
  void (APIENTRY *GlobalAlphaFactoriSUN) (GLint factor);
  void (APIENTRY *GlobalAlphaFactorfSUN) (GLfloat factor);
  void (APIENTRY *GlobalAlphaFactordSUN) (GLdouble factor);
  void (APIENTRY *GlobalAlphaFactorubSUN) (GLubyte factor);
  void (APIENTRY *GlobalAlphaFactorusSUN) (GLushort factor);
  void (APIENTRY *GlobalAlphaFactoruiSUN) (GLuint factor);
  void (APIENTRY *ReplacementCodeuiSUN) (GLuint code);
  void (APIENTRY *ReplacementCodeusSUN) (GLushort code);
  void (APIENTRY *ReplacementCodeubSUN) (GLubyte code);
  void (APIENTRY *ReplacementCodeuivSUN) (const GLuint *code);
  void (APIENTRY *ReplacementCodeusvSUN) (const GLushort *code);
  void (APIENTRY *ReplacementCodeubvSUN) (const GLubyte *code);
  void (APIENTRY *ReplacementCodePointerSUN) (GLenum type, GLsizei stride, const GLvoid* *pointer);
  void (APIENTRY *Color4ubVertex2fSUN) (GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y);
  void (APIENTRY *Color4ubVertex2fvSUN) (const GLubyte *c, const GLfloat *v);
  void (APIENTRY *Color4ubVertex3fSUN) (GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *Color4ubVertex3fvSUN) (const GLubyte *c, const GLfloat *v);
  void (APIENTRY *Color3fVertex3fSUN) (GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *Color3fVertex3fvSUN) (const GLfloat *c, const GLfloat *v);
  void (APIENTRY *Normal3fVertex3fSUN) (GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *Normal3fVertex3fvSUN) (const GLfloat *n, const GLfloat *v);
  void (APIENTRY *Color4fNormal3fVertex3fSUN) (GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *Color4fNormal3fVertex3fvSUN) (const GLfloat *c, const GLfloat *n, const GLfloat *v);
  void (APIENTRY *TexCoord2fVertex3fSUN) (GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *TexCoord2fVertex3fvSUN) (const GLfloat *tc, const GLfloat *v);
  void (APIENTRY *TexCoord4fVertex4fSUN) (GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
  void (APIENTRY *TexCoord4fVertex4fvSUN) (const GLfloat *tc, const GLfloat *v);
  void (APIENTRY *TexCoord2fColor4ubVertex3fSUN) (GLfloat s, GLfloat t, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *TexCoord2fColor4ubVertex3fvSUN) (const GLfloat *tc, const GLubyte *c, const GLfloat *v);
  void (APIENTRY *TexCoord2fColor3fVertex3fSUN) (GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *TexCoord2fColor3fVertex3fvSUN) (const GLfloat *tc, const GLfloat *c, const GLfloat *v);
  void (APIENTRY *TexCoord2fNormal3fVertex3fSUN) (GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *TexCoord2fNormal3fVertex3fvSUN) (const GLfloat *tc, const GLfloat *n, const GLfloat *v);
  void (APIENTRY *TexCoord2fColor4fNormal3fVertex3fSUN) (GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *TexCoord2fColor4fNormal3fVertex3fvSUN) (const GLfloat *tc, const GLfloat *c, const GLfloat *n, const GLfloat *v);
  void (APIENTRY *TexCoord4fColor4fNormal3fVertex4fSUN) (GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
  void (APIENTRY *TexCoord4fColor4fNormal3fVertex4fvSUN) (const GLfloat *tc, const GLfloat *c, const GLfloat *n, const GLfloat *v);
  void (APIENTRY *ReplacementCodeuiVertex3fSUN) (GLuint rc, GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *ReplacementCodeuiVertex3fvSUN) (const GLuint *rc, const GLfloat *v);
  void (APIENTRY *ReplacementCodeuiColor4ubVertex3fSUN) (GLuint rc, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *ReplacementCodeuiColor4ubVertex3fvSUN) (const GLuint *rc, const GLubyte *c, const GLfloat *v);
  void (APIENTRY *ReplacementCodeuiColor3fVertex3fSUN) (GLuint rc, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *ReplacementCodeuiColor3fVertex3fvSUN) (const GLuint *rc, const GLfloat *c, const GLfloat *v);
  void (APIENTRY *ReplacementCodeuiNormal3fVertex3fSUN) (GLuint rc, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *ReplacementCodeuiNormal3fVertex3fvSUN) (const GLuint *rc, const GLfloat *n, const GLfloat *v);
  void (APIENTRY *ReplacementCodeuiColor4fNormal3fVertex3fSUN) (GLuint rc, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *ReplacementCodeuiColor4fNormal3fVertex3fvSUN) (const GLuint *rc, const GLfloat *c, const GLfloat *n, const GLfloat *v);
  void (APIENTRY *ReplacementCodeuiTexCoord2fVertex3fSUN) (GLuint rc, GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *ReplacementCodeuiTexCoord2fVertex3fvSUN) (const GLuint *rc, const GLfloat *tc, const GLfloat *v);
  void (APIENTRY *ReplacementCodeuiTexCoord2fNormal3fVertex3fSUN) (GLuint rc, GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *ReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN) (const GLuint *rc, const GLfloat *tc, const GLfloat *n, const GLfloat *v);
  void (APIENTRY *ReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN) (GLuint rc, GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *ReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN) (const GLuint *rc, const GLfloat *tc, const GLfloat *c, const GLfloat *n, const GLfloat *v);
  void (APIENTRY *BlendFuncSeparateEXT) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
  void (APIENTRY *BlendFuncSeparateINGR) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
  void (APIENTRY *VertexWeightfEXT) (GLfloat weight);
  void (APIENTRY *VertexWeightfvEXT) (const GLfloat *weight);
  void (APIENTRY *VertexWeightPointerEXT) (GLsizei size, GLenum type, GLsizei stride, const GLvoid *pointer);
  void (APIENTRY *FlushVertexArrayRangeNV) (void);
  void (APIENTRY *VertexArrayRangeNV) (GLsizei length, const GLvoid *pointer);
  void (APIENTRY *CombinerParameterfvNV) (GLenum pname, const GLfloat *params);
  void (APIENTRY *CombinerParameterfNV) (GLenum pname, GLfloat param);
  void (APIENTRY *CombinerParameterivNV) (GLenum pname, const GLint *params);
  void (APIENTRY *CombinerParameteriNV) (GLenum pname, GLint param);
  void (APIENTRY *CombinerInputNV) (GLenum stage, GLenum portion, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage);
  void (APIENTRY *CombinerOutputNV) (GLenum stage, GLenum portion, GLenum abOutput, GLenum cdOutput, GLenum sumOutput, GLenum scale, GLenum bias, GLboolean abDotProduct, GLboolean cdDotProduct, GLboolean muxSum);
  void (APIENTRY *FinalCombinerInputNV) (GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage);
  void (APIENTRY *GetCombinerInputParameterfvNV) (GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLfloat *params);
  void (APIENTRY *GetCombinerInputParameterivNV) (GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLint *params);
  void (APIENTRY *GetCombinerOutputParameterfvNV) (GLenum stage, GLenum portion, GLenum pname, GLfloat *params);
  void (APIENTRY *GetCombinerOutputParameterivNV) (GLenum stage, GLenum portion, GLenum pname, GLint *params);
  void (APIENTRY *GetFinalCombinerInputParameterfvNV) (GLenum variable, GLenum pname, GLfloat *params);
  void (APIENTRY *GetFinalCombinerInputParameterivNV) (GLenum variable, GLenum pname, GLint *params);
  void (APIENTRY *ResizeBuffersMESA) (void);
  void (APIENTRY *WindowPos2dMESA) (GLdouble x, GLdouble y);
  void (APIENTRY *WindowPos2dvMESA) (const GLdouble *v);
  void (APIENTRY *WindowPos2fMESA) (GLfloat x, GLfloat y);
  void (APIENTRY *WindowPos2fvMESA) (const GLfloat *v);
  void (APIENTRY *WindowPos2iMESA) (GLint x, GLint y);
  void (APIENTRY *WindowPos2ivMESA) (const GLint *v);
  void (APIENTRY *WindowPos2sMESA) (GLshort x, GLshort y);
  void (APIENTRY *WindowPos2svMESA) (const GLshort *v);
  void (APIENTRY *WindowPos3dMESA) (GLdouble x, GLdouble y, GLdouble z);
  void (APIENTRY *WindowPos3dvMESA) (const GLdouble *v);
  void (APIENTRY *WindowPos3fMESA) (GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *WindowPos3fvMESA) (const GLfloat *v);
  void (APIENTRY *WindowPos3iMESA) (GLint x, GLint y, GLint z);
  void (APIENTRY *WindowPos3ivMESA) (const GLint *v);
  void (APIENTRY *WindowPos3sMESA) (GLshort x, GLshort y, GLshort z);
  void (APIENTRY *WindowPos3svMESA) (const GLshort *v);
  void (APIENTRY *WindowPos4dMESA) (GLdouble x, GLdouble y, GLdouble z, GLdouble w);
  void (APIENTRY *WindowPos4dvMESA) (const GLdouble *v);
  void (APIENTRY *WindowPos4fMESA) (GLfloat x, GLfloat y, GLfloat z, GLfloat w);
  void (APIENTRY *WindowPos4fvMESA) (const GLfloat *v);
  void (APIENTRY *WindowPos4iMESA) (GLint x, GLint y, GLint z, GLint w);
  void (APIENTRY *WindowPos4ivMESA) (const GLint *v);
  void (APIENTRY *WindowPos4sMESA) (GLshort x, GLshort y, GLshort z, GLshort w);
  void (APIENTRY *WindowPos4svMESA) (const GLshort *v);
  void (APIENTRY *MultiModeDrawArraysIBM) (const GLenum *mode, const GLint *first, const GLsizei *count, GLsizei primcount, GLint modestride);
  void (APIENTRY *MultiModeDrawElementsIBM) (const GLenum *mode, const GLsizei *count, GLenum type, const GLvoid* const *indices, GLsizei primcount, GLint modestride);
  void (APIENTRY *ColorPointerListIBM) (GLint size, GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride);
  void (APIENTRY *SecondaryColorPointerListIBM) (GLint size, GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride);
  void (APIENTRY *EdgeFlagPointerListIBM) (GLint stride, const GLboolean* *pointer, GLint ptrstride);
  void (APIENTRY *FogCoordPointerListIBM) (GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride);
  void (APIENTRY *IndexPointerListIBM) (GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride);
  void (APIENTRY *NormalPointerListIBM) (GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride);
  void (APIENTRY *TexCoordPointerListIBM) (GLint size, GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride);
  void (APIENTRY *VertexPointerListIBM) (GLint size, GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride);
  void (APIENTRY *TbufferMask3DFX) (GLuint mask);
  void (APIENTRY *SampleMaskEXT) (GLclampf value, GLboolean invert);
  void (APIENTRY *SamplePatternEXT) (GLenum pattern);
  void (APIENTRY *TextureColorMaskSGIS) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
  void (APIENTRY *IglooInterfaceSGIX) (GLenum pname, const GLvoid *params);
  void (APIENTRY *DeleteFencesNV) (GLsizei n, const GLuint *fences);
  void (APIENTRY *GenFencesNV) (GLsizei n, GLuint *fences);
  GLboolean (APIENTRY *IsFenceNV) (GLuint fence);
  GLboolean (APIENTRY *TestFenceNV) (GLuint fence);
  void (APIENTRY *GetFenceivNV) (GLuint fence, GLenum pname, GLint *params);
  void (APIENTRY *FinishFenceNV) (GLuint fence);
  void (APIENTRY *SetFenceNV) (GLuint fence, GLenum condition);
  void (APIENTRY *MapControlPointsNV) (GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLint uorder, GLint vorder, GLboolean packed, const GLvoid *points);
  void (APIENTRY *MapParameterivNV) (GLenum target, GLenum pname, const GLint *params);
  void (APIENTRY *MapParameterfvNV) (GLenum target, GLenum pname, const GLfloat *params);
  void (APIENTRY *GetMapControlPointsNV) (GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLboolean packed, GLvoid *points);
  void (APIENTRY *GetMapParameterivNV) (GLenum target, GLenum pname, GLint *params);
  void (APIENTRY *GetMapParameterfvNV) (GLenum target, GLenum pname, GLfloat *params);
  void (APIENTRY *GetMapAttribParameterivNV) (GLenum target, GLuint index, GLenum pname, GLint *params);
  void (APIENTRY *GetMapAttribParameterfvNV) (GLenum target, GLuint index, GLenum pname, GLfloat *params);
  void (APIENTRY *EvalMapsNV) (GLenum target, GLenum mode);
  void (APIENTRY *CombinerStageParameterfvNV) (GLenum stage, GLenum pname, const GLfloat *params);
  void (APIENTRY *GetCombinerStageParameterfvNV) (GLenum stage, GLenum pname, GLfloat *params);
  GLboolean (APIENTRY *AreProgramsResidentNV) (GLsizei n, const GLuint *programs, GLboolean *residences);
  void (APIENTRY *BindProgramNV) (GLenum target, GLuint id);
  void (APIENTRY *DeleteProgramsNV) (GLsizei n, const GLuint *programs);
  void (APIENTRY *ExecuteProgramNV) (GLenum target, GLuint id, const GLfloat *params);
  void (APIENTRY *GenProgramsNV) (GLsizei n, GLuint *programs);
  void (APIENTRY *GetProgramParameterdvNV) (GLenum target, GLuint index, GLenum pname, GLdouble *params);
  void (APIENTRY *GetProgramParameterfvNV) (GLenum target, GLuint index, GLenum pname, GLfloat *params);
  void (APIENTRY *GetProgramivNV) (GLuint id, GLenum pname, GLint *params);
  void (APIENTRY *GetProgramStringNV) (GLuint id, GLenum pname, GLubyte *program);
  void (APIENTRY *GetTrackMatrixivNV) (GLenum target, GLuint address, GLenum pname, GLint *params);
  void (APIENTRY *GetVertexAttribdvNV) (GLuint index, GLenum pname, GLdouble *params);
  void (APIENTRY *GetVertexAttribfvNV) (GLuint index, GLenum pname, GLfloat *params);
  void (APIENTRY *GetVertexAttribivNV) (GLuint index, GLenum pname, GLint *params);
  void (APIENTRY *GetVertexAttribPointervNV) (GLuint index, GLenum pname, GLvoid* *pointer);
  GLboolean (APIENTRY *IsProgramNV) (GLuint id);
  void (APIENTRY *LoadProgramNV) (GLenum target, GLuint id, GLsizei len, const GLubyte *program);
  void (APIENTRY *ProgramParameter4dNV) (GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
  void (APIENTRY *ProgramParameter4dvNV) (GLenum target, GLuint index, const GLdouble *v);
  void (APIENTRY *ProgramParameter4fNV) (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
  void (APIENTRY *ProgramParameter4fvNV) (GLenum target, GLuint index, const GLfloat *v);
  void (APIENTRY *ProgramParameters4dvNV) (GLenum target, GLuint index, GLuint count, const GLdouble *v);
  void (APIENTRY *ProgramParameters4fvNV) (GLenum target, GLuint index, GLuint count, const GLfloat *v);
  void (APIENTRY *RequestResidentProgramsNV) (GLsizei n, const GLuint *programs);
  void (APIENTRY *TrackMatrixNV) (GLenum target, GLuint address, GLenum matrix, GLenum transform);
  void (APIENTRY *VertexAttribPointerNV) (GLuint index, GLint fsize, GLenum type, GLsizei stride, const GLvoid *pointer);
  void (APIENTRY *VertexAttrib1dNV) (GLuint index, GLdouble x);
  void (APIENTRY *VertexAttrib1dvNV) (GLuint index, const GLdouble *v);
  void (APIENTRY *VertexAttrib1fNV) (GLuint index, GLfloat x);
  void (APIENTRY *VertexAttrib1fvNV) (GLuint index, const GLfloat *v);
  void (APIENTRY *VertexAttrib1sNV) (GLuint index, GLshort x);
  void (APIENTRY *VertexAttrib1svNV) (GLuint index, const GLshort *v);
  void (APIENTRY *VertexAttrib2dNV) (GLuint index, GLdouble x, GLdouble y);
  void (APIENTRY *VertexAttrib2dvNV) (GLuint index, const GLdouble *v);
  void (APIENTRY *VertexAttrib2fNV) (GLuint index, GLfloat x, GLfloat y);
  void (APIENTRY *VertexAttrib2fvNV) (GLuint index, const GLfloat *v);
  void (APIENTRY *VertexAttrib2sNV) (GLuint index, GLshort x, GLshort y);
  void (APIENTRY *VertexAttrib2svNV) (GLuint index, const GLshort *v);
  void (APIENTRY *VertexAttrib3dNV) (GLuint index, GLdouble x, GLdouble y, GLdouble z);
  void (APIENTRY *VertexAttrib3dvNV) (GLuint index, const GLdouble *v);
  void (APIENTRY *VertexAttrib3fNV) (GLuint index, GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *VertexAttrib3fvNV) (GLuint index, const GLfloat *v);
  void (APIENTRY *VertexAttrib3sNV) (GLuint index, GLshort x, GLshort y, GLshort z);
  void (APIENTRY *VertexAttrib3svNV) (GLuint index, const GLshort *v);
  void (APIENTRY *VertexAttrib4dNV) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
  void (APIENTRY *VertexAttrib4dvNV) (GLuint index, const GLdouble *v);
  void (APIENTRY *VertexAttrib4fNV) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
  void (APIENTRY *VertexAttrib4fvNV) (GLuint index, const GLfloat *v);
  void (APIENTRY *VertexAttrib4sNV) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
  void (APIENTRY *VertexAttrib4svNV) (GLuint index, const GLshort *v);
  void (APIENTRY *VertexAttrib4ubNV) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
  void (APIENTRY *VertexAttrib4ubvNV) (GLuint index, const GLubyte *v);
  void (APIENTRY *VertexAttribs1dvNV) (GLuint index, GLsizei count, const GLdouble *v);
  void (APIENTRY *VertexAttribs1fvNV) (GLuint index, GLsizei count, const GLfloat *v);
  void (APIENTRY *VertexAttribs1svNV) (GLuint index, GLsizei count, const GLshort *v);
  void (APIENTRY *VertexAttribs2dvNV) (GLuint index, GLsizei count, const GLdouble *v);
  void (APIENTRY *VertexAttribs2fvNV) (GLuint index, GLsizei count, const GLfloat *v);
  void (APIENTRY *VertexAttribs2svNV) (GLuint index, GLsizei count, const GLshort *v);
  void (APIENTRY *VertexAttribs3dvNV) (GLuint index, GLsizei count, const GLdouble *v);
  void (APIENTRY *VertexAttribs3fvNV) (GLuint index, GLsizei count, const GLfloat *v);
  void (APIENTRY *VertexAttribs3svNV) (GLuint index, GLsizei count, const GLshort *v);
  void (APIENTRY *VertexAttribs4dvNV) (GLuint index, GLsizei count, const GLdouble *v);
  void (APIENTRY *VertexAttribs4fvNV) (GLuint index, GLsizei count, const GLfloat *v);
  void (APIENTRY *VertexAttribs4svNV) (GLuint index, GLsizei count, const GLshort *v);
  void (APIENTRY *VertexAttribs4ubvNV) (GLuint index, GLsizei count, const GLubyte *v);
  void (APIENTRY *TexBumpParameterivATI) (GLenum pname, const GLint *param);
  void (APIENTRY *TexBumpParameterfvATI) (GLenum pname, const GLfloat *param);
  void (APIENTRY *GetTexBumpParameterivATI) (GLenum pname, GLint *param);
  void (APIENTRY *GetTexBumpParameterfvATI) (GLenum pname, GLfloat *param);
  GLuint (APIENTRY *GenFragmentShadersATI) (GLuint range);
  void (APIENTRY *BindFragmentShaderATI) (GLuint id);
  void (APIENTRY *DeleteFragmentShaderATI) (GLuint id);
  void (APIENTRY *BeginFragmentShaderATI) (void);
  void (APIENTRY *EndFragmentShaderATI) (void);
  void (APIENTRY *PassTexCoordATI) (GLuint dst, GLuint coord, GLenum swizzle);
  void (APIENTRY *SampleMapATI) (GLuint dst, GLuint interp, GLenum swizzle);
  void (APIENTRY *ColorFragmentOp1ATI) (GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod);
  void (APIENTRY *ColorFragmentOp2ATI) (GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod);
  void (APIENTRY *ColorFragmentOp3ATI) (GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod);
  void (APIENTRY *AlphaFragmentOp1ATI) (GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod);
  void (APIENTRY *AlphaFragmentOp2ATI) (GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod);
  void (APIENTRY *AlphaFragmentOp3ATI) (GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod);
  void (APIENTRY *SetFragmentShaderConstantATI) (GLuint dst, const GLfloat *value);
  void (APIENTRY *PNTrianglesiATI) (GLenum pname, GLint param);
  void (APIENTRY *PNTrianglesfATI) (GLenum pname, GLfloat param);
  GLuint (APIENTRY *NewObjectBufferATI) (GLsizei size, const GLvoid *pointer, GLenum usage);
  GLboolean (APIENTRY *IsObjectBufferATI) (GLuint buffer);
  void (APIENTRY *UpdateObjectBufferATI) (GLuint buffer, GLuint offset, GLsizei size, const GLvoid *pointer, GLenum preserve);
  void (APIENTRY *GetObjectBufferfvATI) (GLuint buffer, GLenum pname, GLfloat *params);
  void (APIENTRY *GetObjectBufferivATI) (GLuint buffer, GLenum pname, GLint *params);
  void (APIENTRY *FreeObjectBufferATI) (GLuint buffer);
  void (APIENTRY *ArrayObjectATI) (GLenum array, GLint size, GLenum type, GLsizei stride, GLuint buffer, GLuint offset);
  void (APIENTRY *GetArrayObjectfvATI) (GLenum array, GLenum pname, GLfloat *params);
  void (APIENTRY *GetArrayObjectivATI) (GLenum array, GLenum pname, GLint *params);
  void (APIENTRY *VariantArrayObjectATI) (GLuint id, GLenum type, GLsizei stride, GLuint buffer, GLuint offset);
  void (APIENTRY *GetVariantArrayObjectfvATI) (GLuint id, GLenum pname, GLfloat *params);
  void (APIENTRY *GetVariantArrayObjectivATI) (GLuint id, GLenum pname, GLint *params);
  void (APIENTRY *BeginVertexShaderEXT) (void);
  void (APIENTRY *EndVertexShaderEXT) (void);
  void (APIENTRY *BindVertexShaderEXT) (GLuint id);
  GLuint (APIENTRY *GenVertexShadersEXT) (GLuint range);
  void (APIENTRY *DeleteVertexShaderEXT) (GLuint id);
  void (APIENTRY *ShaderOp1EXT) (GLenum op, GLuint res, GLuint arg1);
  void (APIENTRY *ShaderOp2EXT) (GLenum op, GLuint res, GLuint arg1, GLuint arg2);
  void (APIENTRY *ShaderOp3EXT) (GLenum op, GLuint res, GLuint arg1, GLuint arg2, GLuint arg3);
  void (APIENTRY *SwizzleEXT) (GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW);
  void (APIENTRY *WriteMaskEXT) (GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW);
  void (APIENTRY *InsertComponentEXT) (GLuint res, GLuint src, GLuint num);
  void (APIENTRY *ExtractComponentEXT) (GLuint res, GLuint src, GLuint num);
  GLuint (APIENTRY *GenSymbolsEXT) (GLenum datatype, GLenum storagetype, GLenum range, GLuint components);
  void (APIENTRY *SetInvariantEXT) (GLuint id, GLenum type, const GLvoid *addr);
  void (APIENTRY *SetLocalConstantEXT) (GLuint id, GLenum type, const GLvoid *addr);
  void (APIENTRY *VariantbvEXT) (GLuint id, const GLbyte *addr);
  void (APIENTRY *VariantsvEXT) (GLuint id, const GLshort *addr);
  void (APIENTRY *VariantivEXT) (GLuint id, const GLint *addr);
  void (APIENTRY *VariantfvEXT) (GLuint id, const GLfloat *addr);
  void (APIENTRY *VariantdvEXT) (GLuint id, const GLdouble *addr);
  void (APIENTRY *VariantubvEXT) (GLuint id, const GLubyte *addr);
  void (APIENTRY *VariantusvEXT) (GLuint id, const GLushort *addr);
  void (APIENTRY *VariantuivEXT) (GLuint id, const GLuint *addr);
  void (APIENTRY *VariantPointerEXT) (GLuint id, GLenum type, GLuint stride, const GLvoid *addr);
  void (APIENTRY *EnableVariantClientStateEXT) (GLuint id);
  void (APIENTRY *DisableVariantClientStateEXT) (GLuint id);
  GLuint (APIENTRY *BindLightParameterEXT) (GLenum light, GLenum value);
  GLuint (APIENTRY *BindMaterialParameterEXT) (GLenum face, GLenum value);
  GLuint (APIENTRY *BindTexGenParameterEXT) (GLenum unit, GLenum coord, GLenum value);
  GLuint (APIENTRY *BindTextureUnitParameterEXT) (GLenum unit, GLenum value);
  GLuint (APIENTRY *BindParameterEXT) (GLenum value);
  GLboolean (APIENTRY *IsVariantEnabledEXT) (GLuint id, GLenum cap);
  void (APIENTRY *GetVariantBooleanvEXT) (GLuint id, GLenum value, GLboolean *data);
  void (APIENTRY *GetVariantIntegervEXT) (GLuint id, GLenum value, GLint *data);
  void (APIENTRY *GetVariantFloatvEXT) (GLuint id, GLenum value, GLfloat *data);
  void (APIENTRY *GetVariantPointervEXT) (GLuint id, GLenum value, GLvoid* *data);
  void (APIENTRY *GetInvariantBooleanvEXT) (GLuint id, GLenum value, GLboolean *data);
  void (APIENTRY *GetInvariantIntegervEXT) (GLuint id, GLenum value, GLint *data);
  void (APIENTRY *GetInvariantFloatvEXT) (GLuint id, GLenum value, GLfloat *data);
  void (APIENTRY *GetLocalConstantBooleanvEXT) (GLuint id, GLenum value, GLboolean *data);
  void (APIENTRY *GetLocalConstantIntegervEXT) (GLuint id, GLenum value, GLint *data);
  void (APIENTRY *GetLocalConstantFloatvEXT) (GLuint id, GLenum value, GLfloat *data);
  void (APIENTRY *VertexStream1sATI) (GLenum stream, GLshort x);
  void (APIENTRY *VertexStream1svATI) (GLenum stream, const GLshort *coords);
  void (APIENTRY *VertexStream1iATI) (GLenum stream, GLint x);
  void (APIENTRY *VertexStream1ivATI) (GLenum stream, const GLint *coords);
  void (APIENTRY *VertexStream1fATI) (GLenum stream, GLfloat x);
  void (APIENTRY *VertexStream1fvATI) (GLenum stream, const GLfloat *coords);
  void (APIENTRY *VertexStream1dATI) (GLenum stream, GLdouble x);
  void (APIENTRY *VertexStream1dvATI) (GLenum stream, const GLdouble *coords);
  void (APIENTRY *VertexStream2sATI) (GLenum stream, GLshort x, GLshort y);
  void (APIENTRY *VertexStream2svATI) (GLenum stream, const GLshort *coords);
  void (APIENTRY *VertexStream2iATI) (GLenum stream, GLint x, GLint y);
  void (APIENTRY *VertexStream2ivATI) (GLenum stream, const GLint *coords);
  void (APIENTRY *VertexStream2fATI) (GLenum stream, GLfloat x, GLfloat y);
  void (APIENTRY *VertexStream2fvATI) (GLenum stream, const GLfloat *coords);
  void (APIENTRY *VertexStream2dATI) (GLenum stream, GLdouble x, GLdouble y);
  void (APIENTRY *VertexStream2dvATI) (GLenum stream, const GLdouble *coords);
  void (APIENTRY *VertexStream3sATI) (GLenum stream, GLshort x, GLshort y, GLshort z);
  void (APIENTRY *VertexStream3svATI) (GLenum stream, const GLshort *coords);
  void (APIENTRY *VertexStream3iATI) (GLenum stream, GLint x, GLint y, GLint z);
  void (APIENTRY *VertexStream3ivATI) (GLenum stream, const GLint *coords);
  void (APIENTRY *VertexStream3fATI) (GLenum stream, GLfloat x, GLfloat y, GLfloat z);
  void (APIENTRY *VertexStream3fvATI) (GLenum stream, const GLfloat *coords);
  void (APIENTRY *VertexStream3dATI) (GLenum stream, GLdouble x, GLdouble y, GLdouble z);
  void (APIENTRY *VertexStream3dvATI) (GLenum stream, const GLdouble *coords);
  void (APIENTRY *VertexStream4sATI) (GLenum stream, GLshort x, GLshort y, GLshort z, GLshort w);
  void (APIENTRY *VertexStream4svATI) (GLenum stream, const GLshort *coords);
  void (APIENTRY *VertexStream4iATI) (GLenum stream, GLint x, GLint y, GLint z, GLint w);
  void (APIENTRY *VertexStream4ivATI) (GLenum stream, const GLint *coords);
  void (APIENTRY *VertexStream4fATI) (GLenum stream, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
  void (APIENTRY *VertexStream4fvATI) (GLenum stream, const GLfloat *coords);
  void (APIENTRY *VertexStream4dATI) (GLenum stream, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
  void (APIENTRY *VertexStream4dvATI) (GLenum stream, const GLdouble *coords);
  void (APIENTRY *NormalStream3bATI) (GLenum stream, GLbyte nx, GLbyte ny, GLbyte nz);
  void (APIENTRY *NormalStream3bvATI) (GLenum stream, const GLbyte *coords);
  void (APIENTRY *NormalStream3sATI) (GLenum stream, GLshort nx, GLshort ny, GLshort nz);
  void (APIENTRY *NormalStream3svATI) (GLenum stream, const GLshort *coords);
  void (APIENTRY *NormalStream3iATI) (GLenum stream, GLint nx, GLint ny, GLint nz);
  void (APIENTRY *NormalStream3ivATI) (GLenum stream, const GLint *coords);
  void (APIENTRY *NormalStream3fATI) (GLenum stream, GLfloat nx, GLfloat ny, GLfloat nz);
  void (APIENTRY *NormalStream3fvATI) (GLenum stream, const GLfloat *coords);
  void (APIENTRY *NormalStream3dATI) (GLenum stream, GLdouble nx, GLdouble ny, GLdouble nz);
  void (APIENTRY *NormalStream3dvATI) (GLenum stream, const GLdouble *coords);
  void (APIENTRY *ClientActiveVertexStreamATI) (GLenum stream);
  void (APIENTRY *VertexBlendEnviATI) (GLenum pname, GLint param);
  void (APIENTRY *VertexBlendEnvfATI) (GLenum pname, GLfloat param);
  void (APIENTRY *ElementPointerATI) (GLenum type, const GLvoid *pointer);
  void (APIENTRY *DrawElementArrayATI) (GLenum mode, GLsizei count);
  void (APIENTRY *DrawRangeElementArrayATI) (GLenum mode, GLuint start, GLuint end, GLsizei count);
  void (APIENTRY *DrawMeshArraysSUN) (GLenum mode, GLint first, GLsizei count, GLsizei width);
  void (APIENTRY *GenOcclusionQueriesNV) (GLsizei n, GLuint *ids);
  void (APIENTRY *DeleteOcclusionQueriesNV) (GLsizei n, const GLuint *ids);
  GLboolean (APIENTRY *IsOcclusionQueryNV) (GLuint id);
  void (APIENTRY *BeginOcclusionQueryNV) (GLuint id);
  void (APIENTRY *EndOcclusionQueryNV) (void);
  void (APIENTRY *GetOcclusionQueryivNV) (GLuint id, GLenum pname, GLint *params);
  void (APIENTRY *GetOcclusionQueryuivNV) (GLuint id, GLenum pname, GLuint *params);
  void (APIENTRY *PointParameteriNV) (GLenum pname, GLint param);
  void (APIENTRY *PointParameterivNV) (GLenum pname, const GLint *params);
  void (APIENTRY *ActiveStencilFaceEXT) (GLenum face);
  void (APIENTRY *DrawBuffersATI) (GLsizei n, const GLenum *bufs);
  void (APIENTRY *ProgramNamedParameter4fNV) (GLuint id, GLsizei len, const GLubyte *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
  void (APIENTRY *ProgramNamedParameter4dNV) (GLuint id, GLsizei len, const GLubyte *name, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
  void (APIENTRY *ProgramNamedParameter4fvNV) (GLuint id, GLsizei len, const GLubyte *name, const GLfloat *v);
  void (APIENTRY *ProgramNamedParameter4dvNV) (GLuint id, GLsizei len, const GLubyte *name, const GLdouble *v);
  void (APIENTRY *GetProgramNamedParameterfvNV) (GLuint id, GLsizei len, const GLubyte *name, GLfloat *params);
  void (APIENTRY *GetProgramNamedParameterdvNV) (GLuint id, GLsizei len, const GLubyte *name, GLdouble *params);
  void (APIENTRY *Vertex2hNV) (GLhalfNV x, GLhalfNV y);
  void (APIENTRY *Vertex2hvNV) (const GLhalfNV *v);
  void (APIENTRY *Vertex3hNV) (GLhalfNV x, GLhalfNV y, GLhalfNV z);
  void (APIENTRY *Vertex3hvNV) (const GLhalfNV *v);
  void (APIENTRY *Vertex4hNV) (GLhalfNV x, GLhalfNV y, GLhalfNV z, GLhalfNV w);
  void (APIENTRY *Vertex4hvNV) (const GLhalfNV *v);
  void (APIENTRY *Normal3hNV) (GLhalfNV nx, GLhalfNV ny, GLhalfNV nz);
  void (APIENTRY *Normal3hvNV) (const GLhalfNV *v);
  void (APIENTRY *Color3hNV) (GLhalfNV red, GLhalfNV green, GLhalfNV blue);
  void (APIENTRY *Color3hvNV) (const GLhalfNV *v);
  void (APIENTRY *Color4hNV) (GLhalfNV red, GLhalfNV green, GLhalfNV blue, GLhalfNV alpha);
  void (APIENTRY *Color4hvNV) (const GLhalfNV *v);
  void (APIENTRY *TexCoord1hNV) (GLhalfNV s);
  void (APIENTRY *TexCoord1hvNV) (const GLhalfNV *v);
  void (APIENTRY *TexCoord2hNV) (GLhalfNV s, GLhalfNV t);
  void (APIENTRY *TexCoord2hvNV) (const GLhalfNV *v);
  void (APIENTRY *TexCoord3hNV) (GLhalfNV s, GLhalfNV t, GLhalfNV r);
  void (APIENTRY *TexCoord3hvNV) (const GLhalfNV *v);
  void (APIENTRY *TexCoord4hNV) (GLhalfNV s, GLhalfNV t, GLhalfNV r, GLhalfNV q);
  void (APIENTRY *TexCoord4hvNV) (const GLhalfNV *v);
  void (APIENTRY *MultiTexCoord1hNV) (GLenum target, GLhalfNV s);
  void (APIENTRY *MultiTexCoord1hvNV) (GLenum target, const GLhalfNV *v);
  void (APIENTRY *MultiTexCoord2hNV) (GLenum target, GLhalfNV s, GLhalfNV t);
  void (APIENTRY *MultiTexCoord2hvNV) (GLenum target, const GLhalfNV *v);
  void (APIENTRY *MultiTexCoord3hNV) (GLenum target, GLhalfNV s, GLhalfNV t, GLhalfNV r);
  void (APIENTRY *MultiTexCoord3hvNV) (GLenum target, const GLhalfNV *v);
  void (APIENTRY *MultiTexCoord4hNV) (GLenum target, GLhalfNV s, GLhalfNV t, GLhalfNV r, GLhalfNV q);
  void (APIENTRY *MultiTexCoord4hvNV) (GLenum target, const GLhalfNV *v);
  void (APIENTRY *FogCoordhNV) (GLhalfNV fog);
  void (APIENTRY *FogCoordhvNV) (const GLhalfNV *fog);
  void (APIENTRY *SecondaryColor3hNV) (GLhalfNV red, GLhalfNV green, GLhalfNV blue);
  void (APIENTRY *SecondaryColor3hvNV) (const GLhalfNV *v);
  void (APIENTRY *VertexWeighthNV) (GLhalfNV weight);
  void (APIENTRY *VertexWeighthvNV) (const GLhalfNV *weight);
  void (APIENTRY *VertexAttrib1hNV) (GLuint index, GLhalfNV x);
  void (APIENTRY *VertexAttrib1hvNV) (GLuint index, const GLhalfNV *v);
  void (APIENTRY *VertexAttrib2hNV) (GLuint index, GLhalfNV x, GLhalfNV y);
  void (APIENTRY *VertexAttrib2hvNV) (GLuint index, const GLhalfNV *v);
  void (APIENTRY *VertexAttrib3hNV) (GLuint index, GLhalfNV x, GLhalfNV y, GLhalfNV z);
  void (APIENTRY *VertexAttrib3hvNV) (GLuint index, const GLhalfNV *v);
  void (APIENTRY *VertexAttrib4hNV) (GLuint index, GLhalfNV x, GLhalfNV y, GLhalfNV z, GLhalfNV w);
  void (APIENTRY *VertexAttrib4hvNV) (GLuint index, const GLhalfNV *v);
  void (APIENTRY *VertexAttribs1hvNV) (GLuint index, GLsizei n, const GLhalfNV *v);
  void (APIENTRY *VertexAttribs2hvNV) (GLuint index, GLsizei n, const GLhalfNV *v);
  void (APIENTRY *VertexAttribs3hvNV) (GLuint index, GLsizei n, const GLhalfNV *v);
  void (APIENTRY *VertexAttribs4hvNV) (GLuint index, GLsizei n, const GLhalfNV *v);
  void (APIENTRY *PixelDataRangeNV) (GLenum target, GLsizei length, GLvoid *pointer);
  void (APIENTRY *FlushPixelDataRangeNV) (GLenum target);
  void (APIENTRY *PrimitiveRestartNV) (void);
  void (APIENTRY *PrimitiveRestartIndexNV) (GLuint index);
  GLvoid* (APIENTRY *MapObjectBufferATI) (GLuint buffer);
  void (APIENTRY *UnmapObjectBufferATI) (GLuint buffer);
  void (APIENTRY *StencilOpSeparateATI) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
  void (APIENTRY *StencilFuncSeparateATI) (GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask);
  void (APIENTRY *VertexAttribArrayObjectATI) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLuint buffer, GLuint offset);
  void (APIENTRY *GetVertexAttribArrayObjectfvATI) (GLuint index, GLenum pname, GLfloat *params);
  void (APIENTRY *GetVertexAttribArrayObjectivATI) (GLuint index, GLenum pname, GLint *params);
  void (APIENTRY *DepthBoundsEXT) (GLclampd zmin, GLclampd zmax);
  void (APIENTRY *BlendEquationSeparateEXT) (GLenum modeRGB, GLenum modeAlpha);
  void (APIENTRY *AddSwapHintRectWIN) (GLint x, GLint y, GLsizei width, GLsizei height);
  
  void (APIENTRY *BindFramebufferEXT) (GLenum target, GLuint framebuffer);
  void (APIENTRY *BindRenderbufferEXT) (GLenum target, GLuint renderbuffer);
  GLenum (APIENTRY *CheckFramebufferStatusEXT) (GLenum target);
  void (APIENTRY *DeleteFramebuffersEXT) (GLsizei n, const GLuint* framebuffers);
  void (APIENTRY *DeleteRenderbuffersEXT) (GLsizei n, const GLuint* renderbuffers);
  void (APIENTRY *FramebufferRenderbufferEXT) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
  void (APIENTRY *FramebufferTexture1DEXT) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
  void (APIENTRY *FramebufferTexture2DEXT) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
  void (APIENTRY *FramebufferTexture3DEXT) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
  void (APIENTRY *GenFramebuffersEXT) (GLsizei n, GLuint* framebuffers);
  void (APIENTRY *GenRenderbuffersEXT) (GLsizei n, GLuint* renderbuffers);
  void (APIENTRY *GenerateMipmapEXT) (GLenum target);
  void (APIENTRY *GetFramebufferAttachmentParameterivEXT) (GLenum target, GLenum attachment, GLenum pname, GLint* params);
  void (APIENTRY *GetRenderbufferParameterivEXT) (GLenum target, GLenum pname, GLint* params);
  GLboolean (APIENTRY *IsFramebufferEXT) (GLuint framebuffer);
  GLboolean (APIENTRY *IsRenderbufferEXT) (GLuint renderbuffer);
  void (APIENTRY *RenderbufferStorageEXT) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);

  void (APIENTRY *ProgramParameteriEXT) (GLuint program, GLenum pname, GLint value);
  void (APIENTRY *FramebufferTextureEXT) (GLenum target, GLenum attachment, GLuint texture, GLint level);
  void (APIENTRY *FramebufferTextureLayerEXT) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
  void (APIENTRY *FramebufferTextureFaceEXT) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face);
  void (APIENTRY *DrawBuffersARB) (GLsizei n, const GLenum *bufs);
  
#ifdef MAC_VERSION
  void (APIENTRY *ElementPointerAPPLE) (GLenum type, const GLvoid *pointer);
  void (APIENTRY *DrawElementArrayAPPLE) (GLenum mode, GLint first, GLsizei count);
  void (APIENTRY *DrawRangeElementArrayAPPLE) (GLenum mode, GLuint start, GLuint end, GLint first, GLsizei count);
  void (APIENTRY *MultiDrawElementArrayAPPLE) (GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount);
  void (APIENTRY *MultiDrawRangeElementArrayAPPLE) (GLenum mode, GLuint start, GLuint end, const GLint *first, const GLsizei *count, GLsizei primcount);
  void (APIENTRY *GenFencesAPPLE) (GLsizei n, GLuint *fences);
  void (APIENTRY *DeleteFencesAPPLE) (GLsizei n, const GLuint *fences);
  void (APIENTRY *SetFenceAPPLE) (GLuint fence);
  GLboolean (APIENTRY *IsFenceAPPLE) (GLuint fence);
  GLboolean (APIENTRY *TestFenceAPPLE) (GLuint fence);
  void (APIENTRY *FinishFenceAPPLE) (GLuint fence);
  GLboolean (APIENTRY *TestObjectAPPLE) (GLenum object, GLuint name);
  void (APIENTRY *FinishObjectAPPLE) (GLenum object, GLint name);
  void (APIENTRY *BindVertexArrayAPPLE) (GLuint array);
  void (APIENTRY *DeleteVertexArraysAPPLE) (GLsizei n, const GLuint *arrays);
  void (APIENTRY *GenVertexArraysAPPLE) (GLsizei n, const GLuint *arrays);
  GLboolean (APIENTRY *IsVertexArrayAPPLE) (GLuint array);
  void (APIENTRY *VertexArrayRangeAPPLE) (GLsizei length, GLvoid *pointer);
  void (APIENTRY *FlushVertexArrayRangeAPPLE) (GLsizei length, GLvoid *pointer);
  void (APIENTRY *VertexArrayParameteriAPPLE) (GLenum pname, GLint param);
  void (APIENTRY *TextureRangeAPPLE) (GLenum target, GLsizei length, GLvoid *pointer);
  void (APIENTRY *GetTexParameterPointervAPPLE) (GLenum target, GLenum pname, GLvoid **params);
#ifdef JIT_GL_AGL
  GLboolean (APIENTRY *CreatePBuffer) (GLint width, GLint height, GLenum target, GLenum internalFormat, long max_level, AGLPbuffer *pbuffer);
  GLboolean (APIENTRY *DescribePBuffer) (AGLPbuffer pbuffer, GLint *width, GLint *height, GLenum *target, GLenum *internalFormat, GLint *max_level );
  GLboolean (APIENTRY *DestroyPBuffer) ( AGLPbuffer pbuffer );
  GLboolean (APIENTRY *GetPBuffer) (AGLContext ctx, AGLPbuffer *pbuffer, GLint *face, GLint *level, GLint *screen );
  GLboolean (APIENTRY *SetPBuffer) (AGLContext ctx, AGLPbuffer pbuffer, GLint face, GLint level, GLint screen );
  GLboolean (APIENTRY *TexImagePBuffer) (AGLContext ctx, AGLPbuffer pbuffer, GLint source );
  GLboolean (APIENTRY *SurfaceTexture) (AGLContext context, GLenum target, GLenum internalformat, AGLContext surfacecontext );
#endif  
#endif
#ifdef _WIN32
  HANDLE (WINAPI *CreateBufferRegionARB) (HDC hDC, int iLayerPlane, UINT uType);
  VOID (WINAPI *DeleteBufferRegionARB) (HANDLE hRegion);
  BOOL (WINAPI *SaveBufferRegionARB) (HANDLE hRegion, int x, int y, int width, int height);
  BOOL (WINAPI *RestoreBufferRegionARB) (HANDLE hRegion, int x, int y, int width, int height, int xSrc, int ySrc);
  const char* (WINAPI *GetExtensionsStringARB) (HDC hdc);
  BOOL (WINAPI *GetPixelFormatAttribivARB) (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, int *piValues);
  BOOL (WINAPI *GetPixelFormatAttribfvARB) (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, FLOAT *pfValues);
  BOOL (WINAPI *ChoosePixelFormatARB) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
  BOOL (WINAPI *MakeContextCurrentARB) (HDC hDrawDC, HDC hReadDC, HGLRC hglrc);
  HDC (WINAPI *GetCurrentReadDCARB) (void);
  HPBUFFERARB (WINAPI *CreatePbufferARB) (HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int *piAttribList);
  HDC (WINAPI *GetPbufferDCARB) (HPBUFFERARB hPbuffer);
  int (WINAPI *ReleasePbufferDCARB) (HPBUFFERARB hPbuffer, HDC hDC);
  BOOL (WINAPI *DestroyPbufferARB) (HPBUFFERARB hPbuffer);
  BOOL (WINAPI *QueryPbufferARB) (HPBUFFERARB hPbuffer, int iAttribute, int *piValue);
  BOOL (WINAPI *BindTexImageARB) (HPBUFFERARB hPbuffer, int iBuffer);
  BOOL (WINAPI *ReleaseTexImageARB) (HPBUFFERARB hPbuffer, int iBuffer);
  BOOL (WINAPI *SetPbufferAttribARB) (HPBUFFERARB hPbuffer, const int *piAttribList);
  GLboolean (WINAPI *CreateDisplayColorTableEXT) (GLushort id);
  GLboolean (WINAPI *LoadDisplayColorTableEXT) (const GLushort *table, GLuint length);
  GLboolean (WINAPI *BindDisplayColorTableEXT) (GLushort id);
  VOID (WINAPI *DestroyDisplayColorTableEXT) (GLushort id);
  const char* (WINAPI *GetExtensionsStringEXT) (void);
  BOOL (WINAPI *MakeContextCurrentEXT) (HDC hDrawDC, HDC hReadDC, HGLRC hglrc);
  HDC (WINAPI *GetCurrentReadDCEXT) (void);
  HPBUFFEREXT (WINAPI *CreatePbufferEXT) (HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int *piAttribList);
  HDC (WINAPI *GetPbufferDCEXT) (HPBUFFEREXT hPbuffer);
  int (WINAPI *ReleasePbufferDCEXT) (HPBUFFEREXT hPbuffer, HDC hDC);
  BOOL (WINAPI *DestroyPbufferEXT) (HPBUFFEREXT hPbuffer);
  BOOL (WINAPI *QueryPbufferEXT) (HPBUFFEREXT hPbuffer, int iAttribute, int *piValue);
  BOOL (WINAPI *GetPixelFormatAttribivEXT) (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, int *piAttributes, int *piValues);
  BOOL (WINAPI *GetPixelFormatAttribfvEXT) (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, int *piAttributes, FLOAT *pfValues);
  BOOL (WINAPI *ChoosePixelFormatEXT) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
  BOOL (WINAPI *SwapIntervalEXT) (int interval);
  int (WINAPI *GetSwapIntervalEXT) (void);
  void* (WINAPI *AllocateMemoryNV) (GLsizei size, GLfloat readfreq, GLfloat writefreq, GLfloat priority);
  void (WINAPI *FreeMemoryNV) (void);
  BOOL (WINAPI *GetSyncValuesOML) (HDC hdc, INT64 *ust, INT64 *msc, INT64 *sbc);
  BOOL (WINAPI *GetMscRateOML) (HDC hdc, INT32 *numerator, INT32 *denominator);
  INT64 (WINAPI *SwapBuffersMscOML) (HDC hdc, INT64 target_msc, INT64 divisor, INT64 remainder);
  INT64 (WINAPI *SwapLayerBuffersMscOML) (HDC hdc, int fuPlanes, INT64 target_msc, INT64 divisor, INT64 remainder);
  BOOL (WINAPI *WaitForMscOML) (HDC hdc, INT64 target_msc, INT64 divisor, INT64 remainder, INT64 *ust, INT64 *msc, INT64 *sbc);
  BOOL (WINAPI *WaitForSbcOML) (HDC hdc, INT64 target_sbc, INT64 *ust, INT64 *msc, INT64 *sbc);
  BOOL (WINAPI *GetDigitalVideoParametersI3D) (HDC hDC, int iAttribute, int *piValue);
  BOOL (WINAPI *SetDigitalVideoParametersI3D) (HDC hDC, int iAttribute, const int *piValue);
  BOOL (WINAPI *GetGammaTableParametersI3D) (HDC hDC, int iAttribute, int *piValue);
  BOOL (WINAPI *SetGammaTableParametersI3D) (HDC hDC, int iAttribute, const int *piValue);
  BOOL (WINAPI *GetGammaTableI3D) (HDC hDC, int iEntries, USHORT *puRed, USHORT *puGreen, USHORT *puBlue);
  BOOL (WINAPI *SetGammaTableI3D) (HDC hDC, int iEntries, const USHORT *puRed, const USHORT *puGreen, const USHORT *puBlue);
  BOOL (WINAPI *EnableGenlockI3D) (HDC hDC);
  BOOL (WINAPI *DisableGenlockI3D) (HDC hDC);
  BOOL (WINAPI *IsEnabledGenlockI3D) (HDC hDC, BOOL *pFlag);
  BOOL (WINAPI *GenlockSourceI3D) (HDC hDC, UINT uSource);
  BOOL (WINAPI *GetGenlockSourceI3D) (HDC hDC, UINT *uSource);
  BOOL (WINAPI *GenlockSourceEdgeI3D) (HDC hDC, UINT uEdge);
  BOOL (WINAPI *GetGenlockSourceEdgeI3D) (HDC hDC, UINT *uEdge);
  BOOL (WINAPI *GenlockSampleRateI3D) (HDC hDC, UINT uRate);
  BOOL (WINAPI *GetGenlockSampleRateI3D) (HDC hDC, UINT *uRate);
  BOOL (WINAPI *GenlockSourceDelayI3D) (HDC hDC, UINT uDelay);
  BOOL (WINAPI *GetGenlockSourceDelayI3D) (HDC hDC, UINT *uDelay);
  BOOL (WINAPI *QueryGenlockMaxSourceDelayI3D) (HDC hDC, UINT *uMaxLineDelay, UINT *uMaxPixelDelay);
  LPVOID (WINAPI *CreateImageBufferI3D) (HDC hDC, DWORD dwSize, UINT uFlags);
  BOOL (WINAPI *DestroyImageBufferI3D) (HDC hDC, LPVOID pAddress);
  BOOL (WINAPI *AssociateImageBufferEventsI3D) (HDC hDC, const HANDLE *pEvent, const LPVOID *pAddress, const DWORD *pSize, UINT count);
  BOOL (WINAPI *ReleaseImageBufferEventsI3D) (HDC hDC, const LPVOID *pAddress, UINT count);
  BOOL (WINAPI *EnableFrameLockI3D) (void);
  BOOL (WINAPI *DisableFrameLockI3D) (void);
  BOOL (WINAPI *IsEnabledFrameLockI3D) (BOOL *pFlag);
  BOOL (WINAPI *QueryFrameLockMasterI3D) (BOOL *pFlag);
  BOOL (WINAPI *GetFrameUsageI3D) (float *pUsage);
  BOOL (WINAPI *BeginFrameTrackingI3D) (void);
  BOOL (WINAPI *EndFrameTrackingI3D) (void);
  BOOL (WINAPI *QueryFrameTrackingI3D) (DWORD *pFrameCount, DWORD *pMissedFrames, float *pLastMissedUsage);
#endif /* _WIN32 */
} t_jit_gl_extprocs;

#define glBlendColor                     (_jit_gl_get_proctable()->BlendColor)
#define glBlendEquation                  (_jit_gl_get_proctable()->BlendEquation)
#define glDrawRangeElements              (_jit_gl_get_proctable()->DrawRangeElements)
#define glColorTable                     (_jit_gl_get_proctable()->ColorTable)
#define glColorTableParameterfv          (_jit_gl_get_proctable()->ColorTableParameterfv)
#define glColorTableParameteriv          (_jit_gl_get_proctable()->ColorTableParameteriv)
#define glCopyColorTable                 (_jit_gl_get_proctable()->CopyColorTable)
#define glGetColorTable                  (_jit_gl_get_proctable()->GetColorTable)
#define glGetColorTableParameterfv       (_jit_gl_get_proctable()->GetColorTableParameterfv)
#define glGetColorTableParameteriv       (_jit_gl_get_proctable()->GetColorTableParameteriv)
#define glColorSubTable                  (_jit_gl_get_proctable()->ColorSubTable)
#define glCopyColorSubTable              (_jit_gl_get_proctable()->CopyColorSubTable)
#define glConvolutionFilter1D            (_jit_gl_get_proctable()->ConvolutionFilter1D)
#define glConvolutionFilter2D            (_jit_gl_get_proctable()->ConvolutionFilter2D)
#define glConvolutionParameterf          (_jit_gl_get_proctable()->ConvolutionParameterf)
#define glConvolutionParameterfv         (_jit_gl_get_proctable()->ConvolutionParameterfv)
#define glConvolutionParameteri          (_jit_gl_get_proctable()->ConvolutionParameteri)
#define glConvolutionParameteriv         (_jit_gl_get_proctable()->ConvolutionParameteriv)
#define glCopyConvolutionFilter1D        (_jit_gl_get_proctable()->CopyConvolutionFilter1D)
#define glCopyConvolutionFilter2D        (_jit_gl_get_proctable()->CopyConvolutionFilter2D)
#define glGetConvolutionFilter           (_jit_gl_get_proctable()->GetConvolutionFilter)
#define glGetConvolutionParameterfv      (_jit_gl_get_proctable()->GetConvolutionParameterfv)
#define glGetConvolutionParameteriv      (_jit_gl_get_proctable()->GetConvolutionParameteriv)
#define glGetSeparableFilter             (_jit_gl_get_proctable()->GetSeparableFilter)
#define glSeparableFilter2D              (_jit_gl_get_proctable()->SeparableFilter2D)
#define glGetHistogram                   (_jit_gl_get_proctable()->GetHistogram)
#define glGetHistogramParameterfv        (_jit_gl_get_proctable()->GetHistogramParameterfv)
#define glGetHistogramParameteriv        (_jit_gl_get_proctable()->GetHistogramParameteriv)
#define glGetMinmax                      (_jit_gl_get_proctable()->GetMinmax)
#define glGetMinmaxParameterfv           (_jit_gl_get_proctable()->GetMinmaxParameterfv)
#define glGetMinmaxParameteriv           (_jit_gl_get_proctable()->GetMinmaxParameteriv)
#define glHistogram                      (_jit_gl_get_proctable()->Histogram)
#define glMinmax                         (_jit_gl_get_proctable()->Minmax)
#define glResetHistogram                 (_jit_gl_get_proctable()->ResetHistogram)
#define glResetMinmax                    (_jit_gl_get_proctable()->ResetMinmax)
#define glTexImage3D                     (_jit_gl_get_proctable()->TexImage3D)
#define glTexSubImage3D                  (_jit_gl_get_proctable()->TexSubImage3D)
#define glCopyTexSubImage3D              (_jit_gl_get_proctable()->CopyTexSubImage3D)
#define glActiveTexture                  (_jit_gl_get_proctable()->ActiveTexture)
#define glClientActiveTexture            (_jit_gl_get_proctable()->ClientActiveTexture)
#define glMultiTexCoord1d                (_jit_gl_get_proctable()->MultiTexCoord1d)
#define glMultiTexCoord1dv               (_jit_gl_get_proctable()->MultiTexCoord1dv)
#define glMultiTexCoord1f                (_jit_gl_get_proctable()->MultiTexCoord1f)
#define glMultiTexCoord1fv               (_jit_gl_get_proctable()->MultiTexCoord1fv)
#define glMultiTexCoord1i                (_jit_gl_get_proctable()->MultiTexCoord1i)
#define glMultiTexCoord1iv               (_jit_gl_get_proctable()->MultiTexCoord1iv)
#define glMultiTexCoord1s                (_jit_gl_get_proctable()->MultiTexCoord1s)
#define glMultiTexCoord1sv               (_jit_gl_get_proctable()->MultiTexCoord1sv)
#define glMultiTexCoord2d                (_jit_gl_get_proctable()->MultiTexCoord2d)
#define glMultiTexCoord2dv               (_jit_gl_get_proctable()->MultiTexCoord2dv)
#define glMultiTexCoord2f                (_jit_gl_get_proctable()->MultiTexCoord2f)
#define glMultiTexCoord2fv               (_jit_gl_get_proctable()->MultiTexCoord2fv)
#define glMultiTexCoord2i                (_jit_gl_get_proctable()->MultiTexCoord2i)
#define glMultiTexCoord2iv               (_jit_gl_get_proctable()->MultiTexCoord2iv)
#define glMultiTexCoord2s                (_jit_gl_get_proctable()->MultiTexCoord2s)
#define glMultiTexCoord2sv               (_jit_gl_get_proctable()->MultiTexCoord2sv)
#define glMultiTexCoord3d                (_jit_gl_get_proctable()->MultiTexCoord3d)
#define glMultiTexCoord3dv               (_jit_gl_get_proctable()->MultiTexCoord3dv)
#define glMultiTexCoord3f                (_jit_gl_get_proctable()->MultiTexCoord3f)
#define glMultiTexCoord3fv               (_jit_gl_get_proctable()->MultiTexCoord3fv)
#define glMultiTexCoord3i                (_jit_gl_get_proctable()->MultiTexCoord3i)
#define glMultiTexCoord3iv               (_jit_gl_get_proctable()->MultiTexCoord3iv)
#define glMultiTexCoord3s                (_jit_gl_get_proctable()->MultiTexCoord3s)
#define glMultiTexCoord3sv               (_jit_gl_get_proctable()->MultiTexCoord3sv)
#define glMultiTexCoord4d                (_jit_gl_get_proctable()->MultiTexCoord4d)
#define glMultiTexCoord4dv               (_jit_gl_get_proctable()->MultiTexCoord4dv)
#define glMultiTexCoord4f                (_jit_gl_get_proctable()->MultiTexCoord4f)
#define glMultiTexCoord4fv               (_jit_gl_get_proctable()->MultiTexCoord4fv)
#define glMultiTexCoord4i                (_jit_gl_get_proctable()->MultiTexCoord4i)
#define glMultiTexCoord4iv               (_jit_gl_get_proctable()->MultiTexCoord4iv)
#define glMultiTexCoord4s                (_jit_gl_get_proctable()->MultiTexCoord4s)
#define glMultiTexCoord4sv               (_jit_gl_get_proctable()->MultiTexCoord4sv)
#define glLoadTransposeMatrixf           (_jit_gl_get_proctable()->LoadTransposeMatrixf)
#define glLoadTransposeMatrixd           (_jit_gl_get_proctable()->LoadTransposeMatrixd)
#define glMultTransposeMatrixf           (_jit_gl_get_proctable()->MultTransposeMatrixf)
#define glMultTransposeMatrixd           (_jit_gl_get_proctable()->MultTransposeMatrixd)
#define glSampleCoverage                 (_jit_gl_get_proctable()->SampleCoverage)
#define glCompressedTexImage3D           (_jit_gl_get_proctable()->CompressedTexImage3D)
#define glCompressedTexImage2D           (_jit_gl_get_proctable()->CompressedTexImage2D)
#define glCompressedTexImage1D           (_jit_gl_get_proctable()->CompressedTexImage1D)
#define glCompressedTexSubImage3D        (_jit_gl_get_proctable()->CompressedTexSubImage3D)
#define glCompressedTexSubImage2D        (_jit_gl_get_proctable()->CompressedTexSubImage2D)
#define glCompressedTexSubImage1D        (_jit_gl_get_proctable()->CompressedTexSubImage1D)
#define glGetCompressedTexImage          (_jit_gl_get_proctable()->GetCompressedTexImage)
#define glBlendFuncSeparate              (_jit_gl_get_proctable()->BlendFuncSeparate)
#define glFogCoordf                      (_jit_gl_get_proctable()->FogCoordf)
#define glFogCoordfv                     (_jit_gl_get_proctable()->FogCoordfv)
#define glFogCoordd                      (_jit_gl_get_proctable()->FogCoordd)
#define glFogCoorddv                     (_jit_gl_get_proctable()->FogCoorddv)
#define glFogCoordPointer                (_jit_gl_get_proctable()->FogCoordPointer)
#define glMultiDrawArrays                (_jit_gl_get_proctable()->MultiDrawArrays)
#define glMultiDrawElements              (_jit_gl_get_proctable()->MultiDrawElements)
#define glPointParameterf                (_jit_gl_get_proctable()->PointParameterf)
#define glPointParameterfv               (_jit_gl_get_proctable()->PointParameterfv)
#define glPointParameteri                (_jit_gl_get_proctable()->PointParameteri)
#define glPointParameteriv               (_jit_gl_get_proctable()->PointParameteriv)
#define glSecondaryColor3b               (_jit_gl_get_proctable()->SecondaryColor3b)
#define glSecondaryColor3bv              (_jit_gl_get_proctable()->SecondaryColor3bv)
#define glSecondaryColor3d               (_jit_gl_get_proctable()->SecondaryColor3d)
#define glSecondaryColor3dv              (_jit_gl_get_proctable()->SecondaryColor3dv)
#define glSecondaryColor3f               (_jit_gl_get_proctable()->SecondaryColor3f)
#define glSecondaryColor3fv              (_jit_gl_get_proctable()->SecondaryColor3fv)
#define glSecondaryColor3i               (_jit_gl_get_proctable()->SecondaryColor3i)
#define glSecondaryColor3iv              (_jit_gl_get_proctable()->SecondaryColor3iv)
#define glSecondaryColor3s               (_jit_gl_get_proctable()->SecondaryColor3s)
#define glSecondaryColor3sv              (_jit_gl_get_proctable()->SecondaryColor3sv)
#define glSecondaryColor3ub              (_jit_gl_get_proctable()->SecondaryColor3ub)
#define glSecondaryColor3ubv             (_jit_gl_get_proctable()->SecondaryColor3ubv)
#define glSecondaryColor3ui              (_jit_gl_get_proctable()->SecondaryColor3ui)
#define glSecondaryColor3uiv             (_jit_gl_get_proctable()->SecondaryColor3uiv)
#define glSecondaryColor3us              (_jit_gl_get_proctable()->SecondaryColor3us)
#define glSecondaryColor3usv             (_jit_gl_get_proctable()->SecondaryColor3usv)
#define glSecondaryColorPointer          (_jit_gl_get_proctable()->SecondaryColorPointer)
#define glWindowPos2d                    (_jit_gl_get_proctable()->WindowPos2d)
#define glWindowPos2dv                   (_jit_gl_get_proctable()->WindowPos2dv)
#define glWindowPos2f                    (_jit_gl_get_proctable()->WindowPos2f)
#define glWindowPos2fv                   (_jit_gl_get_proctable()->WindowPos2fv)
#define glWindowPos2i                    (_jit_gl_get_proctable()->WindowPos2i)
#define glWindowPos2iv                   (_jit_gl_get_proctable()->WindowPos2iv)
#define glWindowPos2s                    (_jit_gl_get_proctable()->WindowPos2s)
#define glWindowPos2sv                   (_jit_gl_get_proctable()->WindowPos2sv)
#define glWindowPos3d                    (_jit_gl_get_proctable()->WindowPos3d)
#define glWindowPos3dv                   (_jit_gl_get_proctable()->WindowPos3dv)
#define glWindowPos3f                    (_jit_gl_get_proctable()->WindowPos3f)
#define glWindowPos3fv                   (_jit_gl_get_proctable()->WindowPos3fv)
#define glWindowPos3i                    (_jit_gl_get_proctable()->WindowPos3i)
#define glWindowPos3iv                   (_jit_gl_get_proctable()->WindowPos3iv)
#define glWindowPos3s                    (_jit_gl_get_proctable()->WindowPos3s)
#define glWindowPos3sv                   (_jit_gl_get_proctable()->WindowPos3sv)
#define glGenQueries                     (_jit_gl_get_proctable()->GenQueries)
#define glDeleteQueries                  (_jit_gl_get_proctable()->DeleteQueries)
#define glIsQuery                        (_jit_gl_get_proctable()->IsQuery)
#define glBeginQuery                     (_jit_gl_get_proctable()->BeginQuery)
#define glEndQuery                       (_jit_gl_get_proctable()->EndQuery)
#define glGetQueryiv                     (_jit_gl_get_proctable()->GetQueryiv)
#define glGetQueryObjectiv               (_jit_gl_get_proctable()->GetQueryObjectiv)
#define glGetQueryObjectuiv              (_jit_gl_get_proctable()->GetQueryObjectuiv)
#define glBindBuffer                     (_jit_gl_get_proctable()->BindBuffer)
#define glDeleteBuffers                  (_jit_gl_get_proctable()->DeleteBuffers)
#define glGenBuffers                     (_jit_gl_get_proctable()->GenBuffers)
#define glIsBuffer                       (_jit_gl_get_proctable()->IsBuffer)
#define glBufferData                     (_jit_gl_get_proctable()->BufferData)
#define glBufferSubData                  (_jit_gl_get_proctable()->BufferSubData)
#define glGetBufferSubData               (_jit_gl_get_proctable()->GetBufferSubData)
#define glMapBuffer                      (_jit_gl_get_proctable()->MapBuffer)
#define glUnmapBuffer                    (_jit_gl_get_proctable()->UnmapBuffer)
#define glGetBufferParameteriv           (_jit_gl_get_proctable()->GetBufferParameteriv)
#define glGetBufferPointerv              (_jit_gl_get_proctable()->GetBufferPointerv)
#define glActiveTextureARB               (_jit_gl_get_proctable()->ActiveTextureARB)
#define glClientActiveTextureARB         (_jit_gl_get_proctable()->ClientActiveTextureARB)
#define glMultiTexCoord1dARB             (_jit_gl_get_proctable()->MultiTexCoord1dARB)
#define glMultiTexCoord1dvARB            (_jit_gl_get_proctable()->MultiTexCoord1dvARB)
#define glMultiTexCoord1fARB             (_jit_gl_get_proctable()->MultiTexCoord1fARB)
#define glMultiTexCoord1fvARB            (_jit_gl_get_proctable()->MultiTexCoord1fvARB)
#define glMultiTexCoord1iARB             (_jit_gl_get_proctable()->MultiTexCoord1iARB)
#define glMultiTexCoord1ivARB            (_jit_gl_get_proctable()->MultiTexCoord1ivARB)
#define glMultiTexCoord1sARB             (_jit_gl_get_proctable()->MultiTexCoord1sARB)
#define glMultiTexCoord1svARB            (_jit_gl_get_proctable()->MultiTexCoord1svARB)
#define glMultiTexCoord2dARB             (_jit_gl_get_proctable()->MultiTexCoord2dARB)
#define glMultiTexCoord2dvARB            (_jit_gl_get_proctable()->MultiTexCoord2dvARB)
#define glMultiTexCoord2fARB             (_jit_gl_get_proctable()->MultiTexCoord2fARB)
#define glMultiTexCoord2fvARB            (_jit_gl_get_proctable()->MultiTexCoord2fvARB)
#define glMultiTexCoord2iARB             (_jit_gl_get_proctable()->MultiTexCoord2iARB)
#define glMultiTexCoord2ivARB            (_jit_gl_get_proctable()->MultiTexCoord2ivARB)
#define glMultiTexCoord2sARB             (_jit_gl_get_proctable()->MultiTexCoord2sARB)
#define glMultiTexCoord2svARB            (_jit_gl_get_proctable()->MultiTexCoord2svARB)
#define glMultiTexCoord3dARB             (_jit_gl_get_proctable()->MultiTexCoord3dARB)
#define glMultiTexCoord3dvARB            (_jit_gl_get_proctable()->MultiTexCoord3dvARB)
#define glMultiTexCoord3fARB             (_jit_gl_get_proctable()->MultiTexCoord3fARB)
#define glMultiTexCoord3fvARB            (_jit_gl_get_proctable()->MultiTexCoord3fvARB)
#define glMultiTexCoord3iARB             (_jit_gl_get_proctable()->MultiTexCoord3iARB)
#define glMultiTexCoord3ivARB            (_jit_gl_get_proctable()->MultiTexCoord3ivARB)
#define glMultiTexCoord3sARB             (_jit_gl_get_proctable()->MultiTexCoord3sARB)
#define glMultiTexCoord3svARB            (_jit_gl_get_proctable()->MultiTexCoord3svARB)
#define glMultiTexCoord4dARB             (_jit_gl_get_proctable()->MultiTexCoord4dARB)
#define glMultiTexCoord4dvARB            (_jit_gl_get_proctable()->MultiTexCoord4dvARB)
#define glMultiTexCoord4fARB             (_jit_gl_get_proctable()->MultiTexCoord4fARB)
#define glMultiTexCoord4fvARB            (_jit_gl_get_proctable()->MultiTexCoord4fvARB)
#define glMultiTexCoord4iARB             (_jit_gl_get_proctable()->MultiTexCoord4iARB)
#define glMultiTexCoord4ivARB            (_jit_gl_get_proctable()->MultiTexCoord4ivARB)
#define glMultiTexCoord4sARB             (_jit_gl_get_proctable()->MultiTexCoord4sARB)
#define glMultiTexCoord4svARB            (_jit_gl_get_proctable()->MultiTexCoord4svARB)
#define glLoadTransposeMatrixfARB        (_jit_gl_get_proctable()->LoadTransposeMatrixfARB)
#define glLoadTransposeMatrixdARB        (_jit_gl_get_proctable()->LoadTransposeMatrixdARB)
#define glMultTransposeMatrixfARB        (_jit_gl_get_proctable()->MultTransposeMatrixfARB)
#define glMultTransposeMatrixdARB        (_jit_gl_get_proctable()->MultTransposeMatrixdARB)
#define glSampleCoverageARB              (_jit_gl_get_proctable()->SampleCoverageARB)
#define glCompressedTexImage3DARB        (_jit_gl_get_proctable()->CompressedTexImage3DARB)
#define glCompressedTexImage2DARB        (_jit_gl_get_proctable()->CompressedTexImage2DARB)
#define glCompressedTexImage1DARB        (_jit_gl_get_proctable()->CompressedTexImage1DARB)
#define glCompressedTexSubImage3DARB     (_jit_gl_get_proctable()->CompressedTexSubImage3DARB)
#define glCompressedTexSubImage2DARB     (_jit_gl_get_proctable()->CompressedTexSubImage2DARB)
#define glCompressedTexSubImage1DARB     (_jit_gl_get_proctable()->CompressedTexSubImage1DARB)
#define glGetCompressedTexImageARB       (_jit_gl_get_proctable()->GetCompressedTexImageARB)
#define glPointParameterfARB             (_jit_gl_get_proctable()->PointParameterfARB)
#define glPointParameterfvARB            (_jit_gl_get_proctable()->PointParameterfvARB)
#define glWeightbvARB                    (_jit_gl_get_proctable()->WeightbvARB)
#define glWeightsvARB                    (_jit_gl_get_proctable()->WeightsvARB)
#define glWeightivARB                    (_jit_gl_get_proctable()->WeightivARB)
#define glWeightfvARB                    (_jit_gl_get_proctable()->WeightfvARB)
#define glWeightdvARB                    (_jit_gl_get_proctable()->WeightdvARB)
#define glWeightubvARB                   (_jit_gl_get_proctable()->WeightubvARB)
#define glWeightusvARB                   (_jit_gl_get_proctable()->WeightusvARB)
#define glWeightuivARB                   (_jit_gl_get_proctable()->WeightuivARB)
#define glWeightPointerARB               (_jit_gl_get_proctable()->WeightPointerARB)
#define glVertexBlendARB                 (_jit_gl_get_proctable()->VertexBlendARB)
#define glCurrentPaletteMatrixARB        (_jit_gl_get_proctable()->CurrentPaletteMatrixARB)
#define glMatrixIndexubvARB              (_jit_gl_get_proctable()->MatrixIndexubvARB)
#define glMatrixIndexusvARB              (_jit_gl_get_proctable()->MatrixIndexusvARB)
#define glMatrixIndexuivARB              (_jit_gl_get_proctable()->MatrixIndexuivARB)
#define glMatrixIndexPointerARB          (_jit_gl_get_proctable()->MatrixIndexPointerARB)
#define glWindowPos2dARB                 (_jit_gl_get_proctable()->WindowPos2dARB)
#define glWindowPos2dvARB                (_jit_gl_get_proctable()->WindowPos2dvARB)
#define glWindowPos2fARB                 (_jit_gl_get_proctable()->WindowPos2fARB)
#define glWindowPos2fvARB                (_jit_gl_get_proctable()->WindowPos2fvARB)
#define glWindowPos2iARB                 (_jit_gl_get_proctable()->WindowPos2iARB)
#define glWindowPos2ivARB                (_jit_gl_get_proctable()->WindowPos2ivARB)
#define glWindowPos2sARB                 (_jit_gl_get_proctable()->WindowPos2sARB)
#define glWindowPos2svARB                (_jit_gl_get_proctable()->WindowPos2svARB)
#define glWindowPos3dARB                 (_jit_gl_get_proctable()->WindowPos3dARB)
#define glWindowPos3dvARB                (_jit_gl_get_proctable()->WindowPos3dvARB)
#define glWindowPos3fARB                 (_jit_gl_get_proctable()->WindowPos3fARB)
#define glWindowPos3fvARB                (_jit_gl_get_proctable()->WindowPos3fvARB)
#define glWindowPos3iARB                 (_jit_gl_get_proctable()->WindowPos3iARB)
#define glWindowPos3ivARB                (_jit_gl_get_proctable()->WindowPos3ivARB)
#define glWindowPos3sARB                 (_jit_gl_get_proctable()->WindowPos3sARB)
#define glWindowPos3svARB                (_jit_gl_get_proctable()->WindowPos3svARB)
#define glVertexAttrib1dARB              (_jit_gl_get_proctable()->VertexAttrib1dARB)
#define glVertexAttrib1dvARB             (_jit_gl_get_proctable()->VertexAttrib1dvARB)
#define glVertexAttrib1fARB              (_jit_gl_get_proctable()->VertexAttrib1fARB)
#define glVertexAttrib1fvARB             (_jit_gl_get_proctable()->VertexAttrib1fvARB)
#define glVertexAttrib1sARB              (_jit_gl_get_proctable()->VertexAttrib1sARB)
#define glVertexAttrib1svARB             (_jit_gl_get_proctable()->VertexAttrib1svARB)
#define glVertexAttrib2dARB              (_jit_gl_get_proctable()->VertexAttrib2dARB)
#define glVertexAttrib2dvARB             (_jit_gl_get_proctable()->VertexAttrib2dvARB)
#define glVertexAttrib2fARB              (_jit_gl_get_proctable()->VertexAttrib2fARB)
#define glVertexAttrib2fvARB             (_jit_gl_get_proctable()->VertexAttrib2fvARB)
#define glVertexAttrib2sARB              (_jit_gl_get_proctable()->VertexAttrib2sARB)
#define glVertexAttrib2svARB             (_jit_gl_get_proctable()->VertexAttrib2svARB)
#define glVertexAttrib3dARB              (_jit_gl_get_proctable()->VertexAttrib3dARB)
#define glVertexAttrib3dvARB             (_jit_gl_get_proctable()->VertexAttrib3dvARB)
#define glVertexAttrib3fARB              (_jit_gl_get_proctable()->VertexAttrib3fARB)
#define glVertexAttrib3fvARB             (_jit_gl_get_proctable()->VertexAttrib3fvARB)
#define glVertexAttrib3sARB              (_jit_gl_get_proctable()->VertexAttrib3sARB)
#define glVertexAttrib3svARB             (_jit_gl_get_proctable()->VertexAttrib3svARB)
#define glVertexAttrib4NbvARB            (_jit_gl_get_proctable()->VertexAttrib4NbvARB)
#define glVertexAttrib4NivARB            (_jit_gl_get_proctable()->VertexAttrib4NivARB)
#define glVertexAttrib4NsvARB            (_jit_gl_get_proctable()->VertexAttrib4NsvARB)
#define glVertexAttrib4NubARB            (_jit_gl_get_proctable()->VertexAttrib4NubARB)
#define glVertexAttrib4NubvARB           (_jit_gl_get_proctable()->VertexAttrib4NubvARB)
#define glVertexAttrib4NuivARB           (_jit_gl_get_proctable()->VertexAttrib4NuivARB)
#define glVertexAttrib4NusvARB           (_jit_gl_get_proctable()->VertexAttrib4NusvARB)
#define glVertexAttrib4bvARB             (_jit_gl_get_proctable()->VertexAttrib4bvARB)
#define glVertexAttrib4dARB              (_jit_gl_get_proctable()->VertexAttrib4dARB)
#define glVertexAttrib4dvARB             (_jit_gl_get_proctable()->VertexAttrib4dvARB)
#define glVertexAttrib4fARB              (_jit_gl_get_proctable()->VertexAttrib4fARB)
#define glVertexAttrib4fvARB             (_jit_gl_get_proctable()->VertexAttrib4fvARB)
#define glVertexAttrib4ivARB             (_jit_gl_get_proctable()->VertexAttrib4ivARB)
#define glVertexAttrib4sARB              (_jit_gl_get_proctable()->VertexAttrib4sARB)
#define glVertexAttrib4svARB             (_jit_gl_get_proctable()->VertexAttrib4svARB)
#define glVertexAttrib4ubvARB            (_jit_gl_get_proctable()->VertexAttrib4ubvARB)
#define glVertexAttrib4uivARB            (_jit_gl_get_proctable()->VertexAttrib4uivARB)
#define glVertexAttrib4usvARB            (_jit_gl_get_proctable()->VertexAttrib4usvARB)
#define glVertexAttribPointerARB         (_jit_gl_get_proctable()->VertexAttribPointerARB)
#define glEnableVertexAttribArrayARB     (_jit_gl_get_proctable()->EnableVertexAttribArrayARB)
#define glDisableVertexAttribArrayARB    (_jit_gl_get_proctable()->DisableVertexAttribArrayARB)
#define glProgramStringARB               (_jit_gl_get_proctable()->ProgramStringARB)
#define glBindProgramARB                 (_jit_gl_get_proctable()->BindProgramARB)
#define glDeleteProgramsARB              (_jit_gl_get_proctable()->DeleteProgramsARB)
#define glGenProgramsARB                 (_jit_gl_get_proctable()->GenProgramsARB)
#define glProgramEnvParameter4dARB       (_jit_gl_get_proctable()->ProgramEnvParameter4dARB)
#define glProgramEnvParameter4dvARB      (_jit_gl_get_proctable()->ProgramEnvParameter4dvARB)
#define glProgramEnvParameter4fARB       (_jit_gl_get_proctable()->ProgramEnvParameter4fARB)
#define glProgramEnvParameter4fvARB      (_jit_gl_get_proctable()->ProgramEnvParameter4fvARB)
#define glProgramLocalParameter4dARB     (_jit_gl_get_proctable()->ProgramLocalParameter4dARB)
#define glProgramLocalParameter4dvARB    (_jit_gl_get_proctable()->ProgramLocalParameter4dvARB)
#define glProgramLocalParameter4fARB     (_jit_gl_get_proctable()->ProgramLocalParameter4fARB)
#define glProgramLocalParameter4fvARB    (_jit_gl_get_proctable()->ProgramLocalParameter4fvARB)
#define glGetProgramEnvParameterdvARB    (_jit_gl_get_proctable()->GetProgramEnvParameterdvARB)
#define glGetProgramEnvParameterfvARB    (_jit_gl_get_proctable()->GetProgramEnvParameterfvARB)
#define glGetProgramLocalParameterdvARB  (_jit_gl_get_proctable()->GetProgramLocalParameterdvARB)
#define glGetProgramLocalParameterfvARB  (_jit_gl_get_proctable()->GetProgramLocalParameterfvARB)
#define glGetProgramivARB                (_jit_gl_get_proctable()->GetProgramivARB)
#define glGetProgramStringARB            (_jit_gl_get_proctable()->GetProgramStringARB)
#define glGetVertexAttribdvARB           (_jit_gl_get_proctable()->GetVertexAttribdvARB)
#define glGetVertexAttribfvARB           (_jit_gl_get_proctable()->GetVertexAttribfvARB)
#define glGetVertexAttribivARB           (_jit_gl_get_proctable()->GetVertexAttribivARB)
#define glGetVertexAttribPointervARB     (_jit_gl_get_proctable()->GetVertexAttribPointervARB)
#define glIsProgramARB                   (_jit_gl_get_proctable()->IsProgramARB)
#define glBindBufferARB                  (_jit_gl_get_proctable()->BindBufferARB)
#define glDeleteBuffersARB               (_jit_gl_get_proctable()->DeleteBuffersARB)
#define glGenBuffersARB                  (_jit_gl_get_proctable()->GenBuffersARB)
#define glIsBufferARB                    (_jit_gl_get_proctable()->IsBufferARB)
#define glBufferDataARB                  (_jit_gl_get_proctable()->BufferDataARB)
#define glBufferSubDataARB               (_jit_gl_get_proctable()->BufferSubDataARB)
#define glGetBufferSubDataARB            (_jit_gl_get_proctable()->GetBufferSubDataARB)
#define glMapBufferARB                   (_jit_gl_get_proctable()->MapBufferARB)
#define glUnmapBufferARB                 (_jit_gl_get_proctable()->UnmapBufferARB)
#define glGetBufferParameterivARB        (_jit_gl_get_proctable()->GetBufferParameterivARB)
#define glGetBufferPointervARB           (_jit_gl_get_proctable()->GetBufferPointervARB)
#define glGenQueriesARB                  (_jit_gl_get_proctable()->GenQueriesARB)
#define glDeleteQueriesARB               (_jit_gl_get_proctable()->DeleteQueriesARB)
#define glIsQueryARB                     (_jit_gl_get_proctable()->IsQueryARB)
#define glBeginQueryARB                  (_jit_gl_get_proctable()->BeginQueryARB)
#define glEndQueryARB                    (_jit_gl_get_proctable()->EndQueryARB)
#define glGetQueryivARB                  (_jit_gl_get_proctable()->GetQueryivARB)
#define glGetQueryObjectivARB            (_jit_gl_get_proctable()->GetQueryObjectivARB)
#define glGetQueryObjectuivARB           (_jit_gl_get_proctable()->GetQueryObjectuivARB)
#define glDeleteObjectARB                (_jit_gl_get_proctable()->DeleteObjectARB)
#define glGetHandleARB                   (_jit_gl_get_proctable()->GetHandleARB)
#define glDetachObjectARB                (_jit_gl_get_proctable()->DetachObjectARB)
#define glCreateShaderObjectARB          (_jit_gl_get_proctable()->CreateShaderObjectARB)
#define glShaderSourceARB                (_jit_gl_get_proctable()->ShaderSourceARB)
#define glCompileShaderARB               (_jit_gl_get_proctable()->CompileShaderARB)
#define glCreateProgramObjectARB         (_jit_gl_get_proctable()->CreateProgramObjectARB)
#define glAttachObjectARB                (_jit_gl_get_proctable()->AttachObjectARB)
#define glLinkProgramARB                 (_jit_gl_get_proctable()->LinkProgramARB)
#define glUseProgramObjectARB            (_jit_gl_get_proctable()->UseProgramObjectARB)
#define glValidateProgramARB             (_jit_gl_get_proctable()->ValidateProgramARB)
#define glUniform1fARB                   (_jit_gl_get_proctable()->Uniform1fARB)
#define glUniform2fARB                   (_jit_gl_get_proctable()->Uniform2fARB)
#define glUniform3fARB                   (_jit_gl_get_proctable()->Uniform3fARB)
#define glUniform4fARB                   (_jit_gl_get_proctable()->Uniform4fARB)
#define glUniform1iARB                   (_jit_gl_get_proctable()->Uniform1iARB)
#define glUniform2iARB                   (_jit_gl_get_proctable()->Uniform2iARB)
#define glUniform3iARB                   (_jit_gl_get_proctable()->Uniform3iARB)
#define glUniform4iARB                   (_jit_gl_get_proctable()->Uniform4iARB)
#define glUniform1fvARB                  (_jit_gl_get_proctable()->Uniform1fvARB)
#define glUniform2fvARB                  (_jit_gl_get_proctable()->Uniform2fvARB)
#define glUniform3fvARB                  (_jit_gl_get_proctable()->Uniform3fvARB)
#define glUniform4fvARB                  (_jit_gl_get_proctable()->Uniform4fvARB)
#define glUniform1ivARB                  (_jit_gl_get_proctable()->Uniform1ivARB)
#define glUniform2ivARB                  (_jit_gl_get_proctable()->Uniform2ivARB)
#define glUniform3ivARB                  (_jit_gl_get_proctable()->Uniform3ivARB)
#define glUniform4ivARB                  (_jit_gl_get_proctable()->Uniform4ivARB)
#define glUniformMatrix2fvARB            (_jit_gl_get_proctable()->UniformMatrix2fvARB)
#define glUniformMatrix3fvARB            (_jit_gl_get_proctable()->UniformMatrix3fvARB)
#define glUniformMatrix4fvARB            (_jit_gl_get_proctable()->UniformMatrix4fvARB)
#define glGetObjectParameterfvARB        (_jit_gl_get_proctable()->GetObjectParameterfvARB)
#define glGetObjectParameterivARB        (_jit_gl_get_proctable()->GetObjectParameterivARB)
#define glGetInfoLogARB                  (_jit_gl_get_proctable()->GetInfoLogARB)
#define glGetAttachedObjectsARB          (_jit_gl_get_proctable()->GetAttachedObjectsARB)
#define glGetUniformLocationARB          (_jit_gl_get_proctable()->GetUniformLocationARB)
#define glGetActiveUniformARB            (_jit_gl_get_proctable()->GetActiveUniformARB)
#define glGetUniformfvARB                (_jit_gl_get_proctable()->GetUniformfvARB)
#define glGetUniformivARB                (_jit_gl_get_proctable()->GetUniformivARB)
#define glGetShaderSourceARB             (_jit_gl_get_proctable()->GetShaderSourceARB)
#define glBindAttribLocationARB          (_jit_gl_get_proctable()->BindAttribLocationARB)
#define glGetActiveAttribARB             (_jit_gl_get_proctable()->GetActiveAttribARB)
#define glGetAttribLocationARB           (_jit_gl_get_proctable()->GetAttribLocationARB)
#define glBlendColorEXT                  (_jit_gl_get_proctable()->BlendColorEXT)
#define glPolygonOffsetEXT               (_jit_gl_get_proctable()->PolygonOffsetEXT)
#define glTexImage3DEXT                  (_jit_gl_get_proctable()->TexImage3DEXT)
#define glTexSubImage3DEXT               (_jit_gl_get_proctable()->TexSubImage3DEXT)
#define glGetTexFilterFuncSGIS           (_jit_gl_get_proctable()->GetTexFilterFuncSGIS)
#define glTexFilterFuncSGIS              (_jit_gl_get_proctable()->TexFilterFuncSGIS)
#define glTexSubImage1DEXT               (_jit_gl_get_proctable()->TexSubImage1DEXT)
#define glTexSubImage2DEXT               (_jit_gl_get_proctable()->TexSubImage2DEXT)
#define glCopyTexImage1DEXT              (_jit_gl_get_proctable()->CopyTexImage1DEXT)
#define glCopyTexImage2DEXT              (_jit_gl_get_proctable()->CopyTexImage2DEXT)
#define glCopyTexSubImage1DEXT           (_jit_gl_get_proctable()->CopyTexSubImage1DEXT)
#define glCopyTexSubImage2DEXT           (_jit_gl_get_proctable()->CopyTexSubImage2DEXT)
#define glCopyTexSubImage3DEXT           (_jit_gl_get_proctable()->CopyTexSubImage3DEXT)
#define glGetHistogramEXT                (_jit_gl_get_proctable()->GetHistogramEXT)
#define glGetHistogramParameterfvEXT     (_jit_gl_get_proctable()->GetHistogramParameterfvEXT)
#define glGetHistogramParameterivEXT     (_jit_gl_get_proctable()->GetHistogramParameterivEXT)
#define glGetMinmaxEXT                   (_jit_gl_get_proctable()->GetMinmaxEXT)
#define glGetMinmaxParameterfvEXT        (_jit_gl_get_proctable()->GetMinmaxParameterfvEXT)
#define glGetMinmaxParameterivEXT        (_jit_gl_get_proctable()->GetMinmaxParameterivEXT)
#define glHistogramEXT                   (_jit_gl_get_proctable()->HistogramEXT)
#define glMinmaxEXT                      (_jit_gl_get_proctable()->MinmaxEXT)
#define glResetHistogramEXT              (_jit_gl_get_proctable()->ResetHistogramEXT)
#define glResetMinmaxEXT                 (_jit_gl_get_proctable()->ResetMinmaxEXT)
#define glConvolutionFilter1DEXT         (_jit_gl_get_proctable()->ConvolutionFilter1DEXT)
#define glConvolutionFilter2DEXT         (_jit_gl_get_proctable()->ConvolutionFilter2DEXT)
#define glConvolutionParameterfEXT       (_jit_gl_get_proctable()->ConvolutionParameterfEXT)
#define glConvolutionParameterfvEXT      (_jit_gl_get_proctable()->ConvolutionParameterfvEXT)
#define glConvolutionParameteriEXT       (_jit_gl_get_proctable()->ConvolutionParameteriEXT)
#define glConvolutionParameterivEXT      (_jit_gl_get_proctable()->ConvolutionParameterivEXT)
#define glCopyConvolutionFilter1DEXT     (_jit_gl_get_proctable()->CopyConvolutionFilter1DEXT)
#define glCopyConvolutionFilter2DEXT     (_jit_gl_get_proctable()->CopyConvolutionFilter2DEXT)
#define glGetConvolutionFilterEXT        (_jit_gl_get_proctable()->GetConvolutionFilterEXT)
#define glGetConvolutionParameterfvEXT   (_jit_gl_get_proctable()->GetConvolutionParameterfvEXT)
#define glGetConvolutionParameterivEXT   (_jit_gl_get_proctable()->GetConvolutionParameterivEXT)
#define glGetSeparableFilterEXT          (_jit_gl_get_proctable()->GetSeparableFilterEXT)
#define glSeparableFilter2DEXT           (_jit_gl_get_proctable()->SeparableFilter2DEXT)
#define glColorTableSGI                  (_jit_gl_get_proctable()->ColorTableSGI)
#define glColorTableParameterfvSGI       (_jit_gl_get_proctable()->ColorTableParameterfvSGI)
#define glColorTableParameterivSGI       (_jit_gl_get_proctable()->ColorTableParameterivSGI)
#define glCopyColorTableSGI              (_jit_gl_get_proctable()->CopyColorTableSGI)
#define glGetColorTableSGI               (_jit_gl_get_proctable()->GetColorTableSGI)
#define glGetColorTableParameterfvSGI    (_jit_gl_get_proctable()->GetColorTableParameterfvSGI)
#define glGetColorTableParameterivSGI    (_jit_gl_get_proctable()->GetColorTableParameterivSGI)
#define glPixelTexGenSGIX                (_jit_gl_get_proctable()->PixelTexGenSGIX)
#define glPixelTexGenParameteriSGIS      (_jit_gl_get_proctable()->PixelTexGenParameteriSGIS)
#define glPixelTexGenParameterivSGIS     (_jit_gl_get_proctable()->PixelTexGenParameterivSGIS)
#define glPixelTexGenParameterfSGIS      (_jit_gl_get_proctable()->PixelTexGenParameterfSGIS)
#define glPixelTexGenParameterfvSGIS     (_jit_gl_get_proctable()->PixelTexGenParameterfvSGIS)
#define glGetPixelTexGenParameterivSGIS  (_jit_gl_get_proctable()->GetPixelTexGenParameterivSGIS)
#define glGetPixelTexGenParameterfvSGIS  (_jit_gl_get_proctable()->GetPixelTexGenParameterfvSGIS)
#define glTexImage4DSGIS                 (_jit_gl_get_proctable()->TexImage4DSGIS)
#define glTexSubImage4DSGIS              (_jit_gl_get_proctable()->TexSubImage4DSGIS)
#define glAreTexturesResidentEXT         (_jit_gl_get_proctable()->AreTexturesResidentEXT)
#define glBindTextureEXT                 (_jit_gl_get_proctable()->BindTextureEXT)
#define glDeleteTexturesEXT              (_jit_gl_get_proctable()->DeleteTexturesEXT)
#define glGenTexturesEXT                 (_jit_gl_get_proctable()->GenTexturesEXT)
#define glIsTextureEXT                   (_jit_gl_get_proctable()->IsTextureEXT)
#define glPrioritizeTexturesEXT          (_jit_gl_get_proctable()->PrioritizeTexturesEXT)
#define glDetailTexFuncSGIS              (_jit_gl_get_proctable()->DetailTexFuncSGIS)
#define glGetDetailTexFuncSGIS           (_jit_gl_get_proctable()->GetDetailTexFuncSGIS)
#define glSharpenTexFuncSGIS             (_jit_gl_get_proctable()->SharpenTexFuncSGIS)
#define glGetSharpenTexFuncSGIS          (_jit_gl_get_proctable()->GetSharpenTexFuncSGIS)
#define glSampleMaskSGIS                 (_jit_gl_get_proctable()->SampleMaskSGIS)
#define glSamplePatternSGIS              (_jit_gl_get_proctable()->SamplePatternSGIS)
#define glArrayElementEXT                (_jit_gl_get_proctable()->ArrayElementEXT)
#define glColorPointerEXT                (_jit_gl_get_proctable()->ColorPointerEXT)
#define glDrawArraysEXT                  (_jit_gl_get_proctable()->DrawArraysEXT)
#define glEdgeFlagPointerEXT             (_jit_gl_get_proctable()->EdgeFlagPointerEXT)
#define glGetPointervEXT                 (_jit_gl_get_proctable()->GetPointervEXT)
#define glIndexPointerEXT                (_jit_gl_get_proctable()->IndexPointerEXT)
#define glNormalPointerEXT               (_jit_gl_get_proctable()->NormalPointerEXT)
#define glTexCoordPointerEXT             (_jit_gl_get_proctable()->TexCoordPointerEXT)
#define glVertexPointerEXT               (_jit_gl_get_proctable()->VertexPointerEXT)
#define glBlendEquationEXT               (_jit_gl_get_proctable()->BlendEquationEXT)
#define glSpriteParameterfSGIX           (_jit_gl_get_proctable()->SpriteParameterfSGIX)
#define glSpriteParameterfvSGIX          (_jit_gl_get_proctable()->SpriteParameterfvSGIX)
#define glSpriteParameteriSGIX           (_jit_gl_get_proctable()->SpriteParameteriSGIX)
#define glSpriteParameterivSGIX          (_jit_gl_get_proctable()->SpriteParameterivSGIX)
#define glPointParameterfEXT             (_jit_gl_get_proctable()->PointParameterfEXT)
#define glPointParameterfvEXT            (_jit_gl_get_proctable()->PointParameterfvEXT)
#define glPointParameterfSGIS            (_jit_gl_get_proctable()->PointParameterfSGIS)
#define glPointParameterfvSGIS           (_jit_gl_get_proctable()->PointParameterfvSGIS)
#define glGetInstrumentsSGIX             (_jit_gl_get_proctable()->GetInstrumentsSGIX)
#define glInstrumentsBufferSGIX          (_jit_gl_get_proctable()->InstrumentsBufferSGIX)
#define glPollInstrumentsSGIX            (_jit_gl_get_proctable()->PollInstrumentsSGIX)
#define glReadInstrumentsSGIX            (_jit_gl_get_proctable()->ReadInstrumentsSGIX)
#define glStartInstrumentsSGIX           (_jit_gl_get_proctable()->StartInstrumentsSGIX)
#define glStopInstrumentsSGIX            (_jit_gl_get_proctable()->StopInstrumentsSGIX)
#define glFrameZoomSGIX                  (_jit_gl_get_proctable()->FrameZoomSGIX)
#define glTagSampleBufferSGIX            (_jit_gl_get_proctable()->TagSampleBufferSGIX)
#define glDeformationMap3dSGIX           (_jit_gl_get_proctable()->DeformationMap3dSGIX)
#define glDeformationMap3fSGIX           (_jit_gl_get_proctable()->DeformationMap3fSGIX)
#define glDeformSGIX                     (_jit_gl_get_proctable()->DeformSGIX)
#define glLoadIdentityDeformationMapSGIX (_jit_gl_get_proctable()->LoadIdentityDeformationMapSGIX)
#define glReferencePlaneSGIX             (_jit_gl_get_proctable()->ReferencePlaneSGIX)
#define glFlushRasterSGIX                (_jit_gl_get_proctable()->FlushRasterSGIX)
#define glFogFuncSGIS                    (_jit_gl_get_proctable()->FogFuncSGIS)
#define glGetFogFuncSGIS                 (_jit_gl_get_proctable()->GetFogFuncSGIS)
#define glImageTransformParameteriHP     (_jit_gl_get_proctable()->ImageTransformParameteriHP)
#define glImageTransformParameterfHP     (_jit_gl_get_proctable()->ImageTransformParameterfHP)
#define glImageTransformParameterivHP    (_jit_gl_get_proctable()->ImageTransformParameterivHP)
#define glImageTransformParameterfvHP    (_jit_gl_get_proctable()->ImageTransformParameterfvHP)
#define glGetImageTransformParameterivHP (_jit_gl_get_proctable()->GetImageTransformParameterivHP)
#define glGetImageTransformParameterfvHP (_jit_gl_get_proctable()->GetImageTransformParameterfvHP)
#define glColorSubTableEXT               (_jit_gl_get_proctable()->ColorSubTableEXT)
#define glCopyColorSubTableEXT           (_jit_gl_get_proctable()->CopyColorSubTableEXT)
#define glHintPGI                        (_jit_gl_get_proctable()->HintPGI)
#define glColorTableEXT                  (_jit_gl_get_proctable()->ColorTableEXT)
#define glGetColorTableEXT               (_jit_gl_get_proctable()->GetColorTableEXT)
#define glGetColorTableParameterivEXT    (_jit_gl_get_proctable()->GetColorTableParameterivEXT)
#define glGetColorTableParameterfvEXT    (_jit_gl_get_proctable()->GetColorTableParameterfvEXT)
#define glGetListParameterfvSGIX         (_jit_gl_get_proctable()->GetListParameterfvSGIX)
#define glGetListParameterivSGIX         (_jit_gl_get_proctable()->GetListParameterivSGIX)
#define glListParameterfSGIX             (_jit_gl_get_proctable()->ListParameterfSGIX)
#define glListParameterfvSGIX            (_jit_gl_get_proctable()->ListParameterfvSGIX)
#define glListParameteriSGIX             (_jit_gl_get_proctable()->ListParameteriSGIX)
#define glListParameterivSGIX            (_jit_gl_get_proctable()->ListParameterivSGIX)
#define glIndexMaterialEXT               (_jit_gl_get_proctable()->IndexMaterialEXT)
#define glIndexFuncEXT                   (_jit_gl_get_proctable()->IndexFuncEXT)
#define glLockArraysEXT                  (_jit_gl_get_proctable()->LockArraysEXT)
#define glUnlockArraysEXT                (_jit_gl_get_proctable()->UnlockArraysEXT)
#define glCullParameterdvEXT             (_jit_gl_get_proctable()->CullParameterdvEXT)
#define glCullParameterfvEXT             (_jit_gl_get_proctable()->CullParameterfvEXT)
#define glFragmentColorMaterialSGIX      (_jit_gl_get_proctable()->FragmentColorMaterialSGIX)
#define glFragmentLightfSGIX             (_jit_gl_get_proctable()->FragmentLightfSGIX)
#define glFragmentLightfvSGIX            (_jit_gl_get_proctable()->FragmentLightfvSGIX)
#define glFragmentLightiSGIX             (_jit_gl_get_proctable()->FragmentLightiSGIX)
#define glFragmentLightivSGIX            (_jit_gl_get_proctable()->FragmentLightivSGIX)
#define glFragmentLightModelfSGIX        (_jit_gl_get_proctable()->FragmentLightModelfSGIX)
#define glFragmentLightModelfvSGIX       (_jit_gl_get_proctable()->FragmentLightModelfvSGIX)
#define glFragmentLightModeliSGIX        (_jit_gl_get_proctable()->FragmentLightModeliSGIX)
#define glFragmentLightModelivSGIX       (_jit_gl_get_proctable()->FragmentLightModelivSGIX)
#define glFragmentMaterialfSGIX          (_jit_gl_get_proctable()->FragmentMaterialfSGIX)
#define glFragmentMaterialfvSGIX         (_jit_gl_get_proctable()->FragmentMaterialfvSGIX)
#define glFragmentMaterialiSGIX          (_jit_gl_get_proctable()->FragmentMaterialiSGIX)
#define glFragmentMaterialivSGIX         (_jit_gl_get_proctable()->FragmentMaterialivSGIX)
#define glGetFragmentLightfvSGIX         (_jit_gl_get_proctable()->GetFragmentLightfvSGIX)
#define glGetFragmentLightivSGIX         (_jit_gl_get_proctable()->GetFragmentLightivSGIX)
#define glGetFragmentMaterialfvSGIX      (_jit_gl_get_proctable()->GetFragmentMaterialfvSGIX)
#define glGetFragmentMaterialivSGIX      (_jit_gl_get_proctable()->GetFragmentMaterialivSGIX)
#define glLightEnviSGIX                  (_jit_gl_get_proctable()->LightEnviSGIX)
#define glDrawRangeElementsEXT           (_jit_gl_get_proctable()->DrawRangeElementsEXT)
#define glApplyTextureEXT                (_jit_gl_get_proctable()->ApplyTextureEXT)
#define glTextureLightEXT                (_jit_gl_get_proctable()->TextureLightEXT)
#define glTextureMaterialEXT             (_jit_gl_get_proctable()->TextureMaterialEXT)
#define glAsyncMarkerSGIX                (_jit_gl_get_proctable()->AsyncMarkerSGIX)
#define glFinishAsyncSGIX                (_jit_gl_get_proctable()->FinishAsyncSGIX)
#define glPollAsyncSGIX                  (_jit_gl_get_proctable()->PollAsyncSGIX)
#define glGenAsyncMarkersSGIX            (_jit_gl_get_proctable()->GenAsyncMarkersSGIX)
#define glDeleteAsyncMarkersSGIX         (_jit_gl_get_proctable()->DeleteAsyncMarkersSGIX)
#define glIsAsyncMarkerSGIX              (_jit_gl_get_proctable()->IsAsyncMarkerSGIX)
#define glVertexPointervINTEL            (_jit_gl_get_proctable()->VertexPointervINTEL)
#define glNormalPointervINTEL            (_jit_gl_get_proctable()->NormalPointervINTEL)
#define glColorPointervINTEL             (_jit_gl_get_proctable()->ColorPointervINTEL)
#define glTexCoordPointervINTEL          (_jit_gl_get_proctable()->TexCoordPointervINTEL)
#define glPixelTransformParameteriEXT    (_jit_gl_get_proctable()->PixelTransformParameteriEXT)
#define glPixelTransformParameterfEXT    (_jit_gl_get_proctable()->PixelTransformParameterfEXT)
#define glPixelTransformParameterivEXT   (_jit_gl_get_proctable()->PixelTransformParameterivEXT)
#define glPixelTransformParameterfvEXT   (_jit_gl_get_proctable()->PixelTransformParameterfvEXT)
#define glSecondaryColor3bEXT            (_jit_gl_get_proctable()->SecondaryColor3bEXT)
#define glSecondaryColor3bvEXT           (_jit_gl_get_proctable()->SecondaryColor3bvEXT)
#define glSecondaryColor3dEXT            (_jit_gl_get_proctable()->SecondaryColor3dEXT)
#define glSecondaryColor3dvEXT           (_jit_gl_get_proctable()->SecondaryColor3dvEXT)
#define glSecondaryColor3fEXT            (_jit_gl_get_proctable()->SecondaryColor3fEXT)
#define glSecondaryColor3fvEXT           (_jit_gl_get_proctable()->SecondaryColor3fvEXT)
#define glSecondaryColor3iEXT            (_jit_gl_get_proctable()->SecondaryColor3iEXT)
#define glSecondaryColor3ivEXT           (_jit_gl_get_proctable()->SecondaryColor3ivEXT)
#define glSecondaryColor3sEXT            (_jit_gl_get_proctable()->SecondaryColor3sEXT)
#define glSecondaryColor3svEXT           (_jit_gl_get_proctable()->SecondaryColor3svEXT)
#define glSecondaryColor3ubEXT           (_jit_gl_get_proctable()->SecondaryColor3ubEXT)
#define glSecondaryColor3ubvEXT          (_jit_gl_get_proctable()->SecondaryColor3ubvEXT)
#define glSecondaryColor3uiEXT           (_jit_gl_get_proctable()->SecondaryColor3uiEXT)
#define glSecondaryColor3uivEXT          (_jit_gl_get_proctable()->SecondaryColor3uivEXT)
#define glSecondaryColor3usEXT           (_jit_gl_get_proctable()->SecondaryColor3usEXT)
#define glSecondaryColor3usvEXT          (_jit_gl_get_proctable()->SecondaryColor3usvEXT)
#define glSecondaryColorPointerEXT       (_jit_gl_get_proctable()->SecondaryColorPointerEXT)
#define glTextureNormalEXT               (_jit_gl_get_proctable()->TextureNormalEXT)
#define glMultiDrawArraysEXT             (_jit_gl_get_proctable()->MultiDrawArraysEXT)
#define glMultiDrawElementsEXT           (_jit_gl_get_proctable()->MultiDrawElementsEXT)
#define glFogCoordfEXT                   (_jit_gl_get_proctable()->FogCoordfEXT)
#define glFogCoordfvEXT                  (_jit_gl_get_proctable()->FogCoordfvEXT)
#define glFogCoorddEXT                   (_jit_gl_get_proctable()->FogCoorddEXT)
#define glFogCoorddvEXT                  (_jit_gl_get_proctable()->FogCoorddvEXT)
#define glFogCoordPointerEXT             (_jit_gl_get_proctable()->FogCoordPointerEXT)
#define glTangent3bEXT                   (_jit_gl_get_proctable()->Tangent3bEXT)
#define glTangent3bvEXT                  (_jit_gl_get_proctable()->Tangent3bvEXT)
#define glTangent3dEXT                   (_jit_gl_get_proctable()->Tangent3dEXT)
#define glTangent3dvEXT                  (_jit_gl_get_proctable()->Tangent3dvEXT)
#define glTangent3fEXT                   (_jit_gl_get_proctable()->Tangent3fEXT)
#define glTangent3fvEXT                  (_jit_gl_get_proctable()->Tangent3fvEXT)
#define glTangent3iEXT                   (_jit_gl_get_proctable()->Tangent3iEXT)
#define glTangent3ivEXT                  (_jit_gl_get_proctable()->Tangent3ivEXT)
#define glTangent3sEXT                   (_jit_gl_get_proctable()->Tangent3sEXT)
#define glTangent3svEXT                  (_jit_gl_get_proctable()->Tangent3svEXT)
#define glBinormal3bEXT                  (_jit_gl_get_proctable()->Binormal3bEXT)
#define glBinormal3bvEXT                 (_jit_gl_get_proctable()->Binormal3bvEXT)
#define glBinormal3dEXT                  (_jit_gl_get_proctable()->Binormal3dEXT)
#define glBinormal3dvEXT                 (_jit_gl_get_proctable()->Binormal3dvEXT)
#define glBinormal3fEXT                  (_jit_gl_get_proctable()->Binormal3fEXT)
#define glBinormal3fvEXT                 (_jit_gl_get_proctable()->Binormal3fvEXT)
#define glBinormal3iEXT                  (_jit_gl_get_proctable()->Binormal3iEXT)
#define glBinormal3ivEXT                 (_jit_gl_get_proctable()->Binormal3ivEXT)
#define glBinormal3sEXT                  (_jit_gl_get_proctable()->Binormal3sEXT)
#define glBinormal3svEXT                 (_jit_gl_get_proctable()->Binormal3svEXT)
#define glTangentPointerEXT              (_jit_gl_get_proctable()->TangentPointerEXT)
#define glBinormalPointerEXT             (_jit_gl_get_proctable()->BinormalPointerEXT)
#define glFinishTextureSUNX              (_jit_gl_get_proctable()->FinishTextureSUNX)
#define glGlobalAlphaFactorbSUN          (_jit_gl_get_proctable()->GlobalAlphaFactorbSUN)
#define glGlobalAlphaFactorsSUN          (_jit_gl_get_proctable()->GlobalAlphaFactorsSUN)
#define glGlobalAlphaFactoriSUN          (_jit_gl_get_proctable()->GlobalAlphaFactoriSUN)
#define glGlobalAlphaFactorfSUN          (_jit_gl_get_proctable()->GlobalAlphaFactorfSUN)
#define glGlobalAlphaFactordSUN          (_jit_gl_get_proctable()->GlobalAlphaFactordSUN)
#define glGlobalAlphaFactorubSUN         (_jit_gl_get_proctable()->GlobalAlphaFactorubSUN)
#define glGlobalAlphaFactorusSUN         (_jit_gl_get_proctable()->GlobalAlphaFactorusSUN)
#define glGlobalAlphaFactoruiSUN         (_jit_gl_get_proctable()->GlobalAlphaFactoruiSUN)
#define glReplacementCodeuiSUN           (_jit_gl_get_proctable()->ReplacementCodeuiSUN)
#define glReplacementCodeusSUN           (_jit_gl_get_proctable()->ReplacementCodeusSUN)
#define glReplacementCodeubSUN           (_jit_gl_get_proctable()->ReplacementCodeubSUN)
#define glReplacementCodeuivSUN          (_jit_gl_get_proctable()->ReplacementCodeuivSUN)
#define glReplacementCodeusvSUN          (_jit_gl_get_proctable()->ReplacementCodeusvSUN)
#define glReplacementCodeubvSUN          (_jit_gl_get_proctable()->ReplacementCodeubvSUN)
#define glReplacementCodePointerSUN      (_jit_gl_get_proctable()->ReplacementCodePointerSUN)
#define glColor4ubVertex2fSUN            (_jit_gl_get_proctable()->Color4ubVertex2fSUN)
#define glColor4ubVertex2fvSUN           (_jit_gl_get_proctable()->Color4ubVertex2fvSUN)
#define glColor4ubVertex3fSUN            (_jit_gl_get_proctable()->Color4ubVertex3fSUN)
#define glColor4ubVertex3fvSUN           (_jit_gl_get_proctable()->Color4ubVertex3fvSUN)
#define glColor3fVertex3fSUN             (_jit_gl_get_proctable()->Color3fVertex3fSUN)
#define glColor3fVertex3fvSUN            (_jit_gl_get_proctable()->Color3fVertex3fvSUN)
#define glNormal3fVertex3fSUN            (_jit_gl_get_proctable()->Normal3fVertex3fSUN)
#define glNormal3fVertex3fvSUN           (_jit_gl_get_proctable()->Normal3fVertex3fvSUN)
#define glColor4fNormal3fVertex3fSUN     (_jit_gl_get_proctable()->Color4fNormal3fVertex3fSUN)
#define glColor4fNormal3fVertex3fvSUN    (_jit_gl_get_proctable()->Color4fNormal3fVertex3fvSUN)
#define glTexCoord2fVertex3fSUN          (_jit_gl_get_proctable()->TexCoord2fVertex3fSUN)
#define glTexCoord2fVertex3fvSUN         (_jit_gl_get_proctable()->TexCoord2fVertex3fvSUN)
#define glTexCoord4fVertex4fSUN          (_jit_gl_get_proctable()->TexCoord4fVertex4fSUN)
#define glTexCoord4fVertex4fvSUN         (_jit_gl_get_proctable()->TexCoord4fVertex4fvSUN)
#define glTexCoord2fColor4ubVertex3fSUN  (_jit_gl_get_proctable()->TexCoord2fColor4ubVertex3fSUN)
#define glTexCoord2fColor4ubVertex3fvSUN (_jit_gl_get_proctable()->TexCoord2fColor4ubVertex3fvSUN)
#define glTexCoord2fColor3fVertex3fSUN   (_jit_gl_get_proctable()->TexCoord2fColor3fVertex3fSUN)
#define glTexCoord2fColor3fVertex3fvSUN  (_jit_gl_get_proctable()->TexCoord2fColor3fVertex3fvSUN)
#define glTexCoord2fNormal3fVertex3fSUN  (_jit_gl_get_proctable()->TexCoord2fNormal3fVertex3fSUN)
#define glTexCoord2fNormal3fVertex3fvSUN (_jit_gl_get_proctable()->TexCoord2fNormal3fVertex3fvSUN)
#define glTexCoord2fColor4fNormal3fVertex3fSUN (_jit_gl_get_proctable()->TexCoord2fColor4fNormal3fVertex3fSUN)
#define glTexCoord2fColor4fNormal3fVertex3fvSUN (_jit_gl_get_proctable()->TexCoord2fColor4fNormal3fVertex3fvSUN)
#define glTexCoord4fColor4fNormal3fVertex4fSUN (_jit_gl_get_proctable()->TexCoord4fColor4fNormal3fVertex4fSUN)
#define glTexCoord4fColor4fNormal3fVertex4fvSUN (_jit_gl_get_proctable()->TexCoord4fColor4fNormal3fVertex4fvSUN)
#define glReplacementCodeuiVertex3fSUN   (_jit_gl_get_proctable()->ReplacementCodeuiVertex3fSUN)
#define glReplacementCodeuiVertex3fvSUN  (_jit_gl_get_proctable()->ReplacementCodeuiVertex3fvSUN)
#define glReplacementCodeuiColor4ubVertex3fSUN (_jit_gl_get_proctable()->ReplacementCodeuiColor4ubVertex3fSUN)
#define glReplacementCodeuiColor4ubVertex3fvSUN (_jit_gl_get_proctable()->ReplacementCodeuiColor4ubVertex3fvSUN)
#define glReplacementCodeuiColor3fVertex3fSUN (_jit_gl_get_proctable()->ReplacementCodeuiColor3fVertex3fSUN)
#define glReplacementCodeuiColor3fVertex3fvSUN (_jit_gl_get_proctable()->ReplacementCodeuiColor3fVertex3fvSUN)
#define glReplacementCodeuiNormal3fVertex3fSUN (_jit_gl_get_proctable()->ReplacementCodeuiNormal3fVertex3fSUN)
#define glReplacementCodeuiNormal3fVertex3fvSUN (_jit_gl_get_proctable()->ReplacementCodeuiNormal3fVertex3fvSUN)
#define glReplacementCodeuiColor4fNormal3fVertex3fSUN (_jit_gl_get_proctable()->ReplacementCodeuiColor4fNormal3fVertex3fSUN)
#define glReplacementCodeuiColor4fNormal3fVertex3fvSUN (_jit_gl_get_proctable()->ReplacementCodeuiColor4fNormal3fVertex3fvSUN)
#define glReplacementCodeuiTexCoord2fVertex3fSUN (_jit_gl_get_proctable()->ReplacementCodeuiTexCoord2fVertex3fSUN)
#define glReplacementCodeuiTexCoord2fVertex3fvSUN (_jit_gl_get_proctable()->ReplacementCodeuiTexCoord2fVertex3fvSUN)
#define glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN (_jit_gl_get_proctable()->ReplacementCodeuiTexCoord2fNormal3fVertex3fSUN)
#define glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN (_jit_gl_get_proctable()->ReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN)
#define glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN (_jit_gl_get_proctable()->ReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN)
#define glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN (_jit_gl_get_proctable()->ReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN)
#define glBlendFuncSeparateEXT           (_jit_gl_get_proctable()->BlendFuncSeparateEXT)
#define glBlendFuncSeparateINGR          (_jit_gl_get_proctable()->BlendFuncSeparateINGR)
#define glVertexWeightfEXT               (_jit_gl_get_proctable()->VertexWeightfEXT)
#define glVertexWeightfvEXT              (_jit_gl_get_proctable()->VertexWeightfvEXT)
#define glVertexWeightPointerEXT         (_jit_gl_get_proctable()->VertexWeightPointerEXT)
#define glFlushVertexArrayRangeNV        (_jit_gl_get_proctable()->FlushVertexArrayRangeNV)
#define glVertexArrayRangeNV             (_jit_gl_get_proctable()->VertexArrayRangeNV)
#define glCombinerParameterfvNV          (_jit_gl_get_proctable()->CombinerParameterfvNV)
#define glCombinerParameterfNV           (_jit_gl_get_proctable()->CombinerParameterfNV)
#define glCombinerParameterivNV          (_jit_gl_get_proctable()->CombinerParameterivNV)
#define glCombinerParameteriNV           (_jit_gl_get_proctable()->CombinerParameteriNV)
#define glCombinerInputNV                (_jit_gl_get_proctable()->CombinerInputNV)
#define glCombinerOutputNV               (_jit_gl_get_proctable()->CombinerOutputNV)
#define glFinalCombinerInputNV           (_jit_gl_get_proctable()->FinalCombinerInputNV)
#define glGetCombinerInputParameterfvNV  (_jit_gl_get_proctable()->GetCombinerInputParameterfvNV)
#define glGetCombinerInputParameterivNV  (_jit_gl_get_proctable()->GetCombinerInputParameterivNV)
#define glGetCombinerOutputParameterfvNV (_jit_gl_get_proctable()->GetCombinerOutputParameterfvNV)
#define glGetCombinerOutputParameterivNV (_jit_gl_get_proctable()->GetCombinerOutputParameterivNV)
#define glGetFinalCombinerInputParameterfvNV (_jit_gl_get_proctable()->GetFinalCombinerInputParameterfvNV)
#define glGetFinalCombinerInputParameterivNV (_jit_gl_get_proctable()->GetFinalCombinerInputParameterivNV)
#define glResizeBuffersMESA              (_jit_gl_get_proctable()->ResizeBuffersMESA)
#define glWindowPos2dMESA                (_jit_gl_get_proctable()->WindowPos2dMESA)
#define glWindowPos2dvMESA               (_jit_gl_get_proctable()->WindowPos2dvMESA)
#define glWindowPos2fMESA                (_jit_gl_get_proctable()->WindowPos2fMESA)
#define glWindowPos2fvMESA               (_jit_gl_get_proctable()->WindowPos2fvMESA)
#define glWindowPos2iMESA                (_jit_gl_get_proctable()->WindowPos2iMESA)
#define glWindowPos2ivMESA               (_jit_gl_get_proctable()->WindowPos2ivMESA)
#define glWindowPos2sMESA                (_jit_gl_get_proctable()->WindowPos2sMESA)
#define glWindowPos2svMESA               (_jit_gl_get_proctable()->WindowPos2svMESA)
#define glWindowPos3dMESA                (_jit_gl_get_proctable()->WindowPos3dMESA)
#define glWindowPos3dvMESA               (_jit_gl_get_proctable()->WindowPos3dvMESA)
#define glWindowPos3fMESA                (_jit_gl_get_proctable()->WindowPos3fMESA)
#define glWindowPos3fvMESA               (_jit_gl_get_proctable()->WindowPos3fvMESA)
#define glWindowPos3iMESA                (_jit_gl_get_proctable()->WindowPos3iMESA)
#define glWindowPos3ivMESA               (_jit_gl_get_proctable()->WindowPos3ivMESA)
#define glWindowPos3sMESA                (_jit_gl_get_proctable()->WindowPos3sMESA)
#define glWindowPos3svMESA               (_jit_gl_get_proctable()->WindowPos3svMESA)
#define glWindowPos4dMESA                (_jit_gl_get_proctable()->WindowPos4dMESA)
#define glWindowPos4dvMESA               (_jit_gl_get_proctable()->WindowPos4dvMESA)
#define glWindowPos4fMESA                (_jit_gl_get_proctable()->WindowPos4fMESA)
#define glWindowPos4fvMESA               (_jit_gl_get_proctable()->WindowPos4fvMESA)
#define glWindowPos4iMESA                (_jit_gl_get_proctable()->WindowPos4iMESA)
#define glWindowPos4ivMESA               (_jit_gl_get_proctable()->WindowPos4ivMESA)
#define glWindowPos4sMESA                (_jit_gl_get_proctable()->WindowPos4sMESA)
#define glWindowPos4svMESA               (_jit_gl_get_proctable()->WindowPos4svMESA)
#define glMultiModeDrawArraysIBM         (_jit_gl_get_proctable()->MultiModeDrawArraysIBM)
#define glMultiModeDrawElementsIBM       (_jit_gl_get_proctable()->MultiModeDrawElementsIBM)
#define glColorPointerListIBM            (_jit_gl_get_proctable()->ColorPointerListIBM)
#define glSecondaryColorPointerListIBM   (_jit_gl_get_proctable()->SecondaryColorPointerListIBM)
#define glEdgeFlagPointerListIBM         (_jit_gl_get_proctable()->EdgeFlagPointerListIBM)
#define glFogCoordPointerListIBM         (_jit_gl_get_proctable()->FogCoordPointerListIBM)
#define glIndexPointerListIBM            (_jit_gl_get_proctable()->IndexPointerListIBM)
#define glNormalPointerListIBM           (_jit_gl_get_proctable()->NormalPointerListIBM)
#define glTexCoordPointerListIBM         (_jit_gl_get_proctable()->TexCoordPointerListIBM)
#define glVertexPointerListIBM           (_jit_gl_get_proctable()->VertexPointerListIBM)
#define glTbufferMask3DFX                (_jit_gl_get_proctable()->TbufferMask3DFX)
#define glSampleMaskEXT                  (_jit_gl_get_proctable()->SampleMaskEXT)
#define glSamplePatternEXT               (_jit_gl_get_proctable()->SamplePatternEXT)
#define glTextureColorMaskSGIS           (_jit_gl_get_proctable()->TextureColorMaskSGIS)
#define glIglooInterfaceSGIX             (_jit_gl_get_proctable()->IglooInterfaceSGIX)
#define glDeleteFencesNV                 (_jit_gl_get_proctable()->DeleteFencesNV)
#define glGenFencesNV                    (_jit_gl_get_proctable()->GenFencesNV)
#define glIsFenceNV                      (_jit_gl_get_proctable()->IsFenceNV)
#define glTestFenceNV                    (_jit_gl_get_proctable()->TestFenceNV)
#define glGetFenceivNV                   (_jit_gl_get_proctable()->GetFenceivNV)
#define glFinishFenceNV                  (_jit_gl_get_proctable()->FinishFenceNV)
#define glSetFenceNV                     (_jit_gl_get_proctable()->SetFenceNV)
#define glMapControlPointsNV             (_jit_gl_get_proctable()->MapControlPointsNV)
#define glMapParameterivNV               (_jit_gl_get_proctable()->MapParameterivNV)
#define glMapParameterfvNV               (_jit_gl_get_proctable()->MapParameterfvNV)
#define glGetMapControlPointsNV          (_jit_gl_get_proctable()->GetMapControlPointsNV)
#define glGetMapParameterivNV            (_jit_gl_get_proctable()->GetMapParameterivNV)
#define glGetMapParameterfvNV            (_jit_gl_get_proctable()->GetMapParameterfvNV)
#define glGetMapAttribParameterivNV      (_jit_gl_get_proctable()->GetMapAttribParameterivNV)
#define glGetMapAttribParameterfvNV      (_jit_gl_get_proctable()->GetMapAttribParameterfvNV)
#define glEvalMapsNV                     (_jit_gl_get_proctable()->EvalMapsNV)
#define glCombinerStageParameterfvNV     (_jit_gl_get_proctable()->CombinerStageParameterfvNV)
#define glGetCombinerStageParameterfvNV  (_jit_gl_get_proctable()->GetCombinerStageParameterfvNV)
#define glAreProgramsResidentNV          (_jit_gl_get_proctable()->AreProgramsResidentNV)
#define glBindProgramNV                  (_jit_gl_get_proctable()->BindProgramNV)
#define glDeleteProgramsNV               (_jit_gl_get_proctable()->DeleteProgramsNV)
#define glExecuteProgramNV               (_jit_gl_get_proctable()->ExecuteProgramNV)
#define glGenProgramsNV                  (_jit_gl_get_proctable()->GenProgramsNV)
#define glGetProgramParameterdvNV        (_jit_gl_get_proctable()->GetProgramParameterdvNV)
#define glGetProgramParameterfvNV        (_jit_gl_get_proctable()->GetProgramParameterfvNV)
#define glGetProgramivNV                 (_jit_gl_get_proctable()->GetProgramivNV)
#define glGetProgramStringNV             (_jit_gl_get_proctable()->GetProgramStringNV)
#define glGetTrackMatrixivNV             (_jit_gl_get_proctable()->GetTrackMatrixivNV)
#define glGetVertexAttribdvNV            (_jit_gl_get_proctable()->GetVertexAttribdvNV)
#define glGetVertexAttribfvNV            (_jit_gl_get_proctable()->GetVertexAttribfvNV)
#define glGetVertexAttribivNV            (_jit_gl_get_proctable()->GetVertexAttribivNV)
#define glGetVertexAttribPointervNV      (_jit_gl_get_proctable()->GetVertexAttribPointervNV)
#define glIsProgramNV                    (_jit_gl_get_proctable()->IsProgramNV)
#define glLoadProgramNV                  (_jit_gl_get_proctable()->LoadProgramNV)
#define glProgramParameter4dNV           (_jit_gl_get_proctable()->ProgramParameter4dNV)
#define glProgramParameter4dvNV          (_jit_gl_get_proctable()->ProgramParameter4dvNV)
#define glProgramParameter4fNV           (_jit_gl_get_proctable()->ProgramParameter4fNV)
#define glProgramParameter4fvNV          (_jit_gl_get_proctable()->ProgramParameter4fvNV)
#define glProgramParameters4dvNV         (_jit_gl_get_proctable()->ProgramParameters4dvNV)
#define glProgramParameters4fvNV         (_jit_gl_get_proctable()->ProgramParameters4fvNV)
#define glRequestResidentProgramsNV      (_jit_gl_get_proctable()->RequestResidentProgramsNV)
#define glTrackMatrixNV                  (_jit_gl_get_proctable()->TrackMatrixNV)
#define glVertexAttribPointerNV          (_jit_gl_get_proctable()->VertexAttribPointerNV)
#define glVertexAttrib1dNV               (_jit_gl_get_proctable()->VertexAttrib1dNV)
#define glVertexAttrib1dvNV              (_jit_gl_get_proctable()->VertexAttrib1dvNV)
#define glVertexAttrib1fNV               (_jit_gl_get_proctable()->VertexAttrib1fNV)
#define glVertexAttrib1fvNV              (_jit_gl_get_proctable()->VertexAttrib1fvNV)
#define glVertexAttrib1sNV               (_jit_gl_get_proctable()->VertexAttrib1sNV)
#define glVertexAttrib1svNV              (_jit_gl_get_proctable()->VertexAttrib1svNV)
#define glVertexAttrib2dNV               (_jit_gl_get_proctable()->VertexAttrib2dNV)
#define glVertexAttrib2dvNV              (_jit_gl_get_proctable()->VertexAttrib2dvNV)
#define glVertexAttrib2fNV               (_jit_gl_get_proctable()->VertexAttrib2fNV)
#define glVertexAttrib2fvNV              (_jit_gl_get_proctable()->VertexAttrib2fvNV)
#define glVertexAttrib2sNV               (_jit_gl_get_proctable()->VertexAttrib2sNV)
#define glVertexAttrib2svNV              (_jit_gl_get_proctable()->VertexAttrib2svNV)
#define glVertexAttrib3dNV               (_jit_gl_get_proctable()->VertexAttrib3dNV)
#define glVertexAttrib3dvNV              (_jit_gl_get_proctable()->VertexAttrib3dvNV)
#define glVertexAttrib3fNV               (_jit_gl_get_proctable()->VertexAttrib3fNV)
#define glVertexAttrib3fvNV              (_jit_gl_get_proctable()->VertexAttrib3fvNV)
#define glVertexAttrib3sNV               (_jit_gl_get_proctable()->VertexAttrib3sNV)
#define glVertexAttrib3svNV              (_jit_gl_get_proctable()->VertexAttrib3svNV)
#define glVertexAttrib4dNV               (_jit_gl_get_proctable()->VertexAttrib4dNV)
#define glVertexAttrib4dvNV              (_jit_gl_get_proctable()->VertexAttrib4dvNV)
#define glVertexAttrib4fNV               (_jit_gl_get_proctable()->VertexAttrib4fNV)
#define glVertexAttrib4fvNV              (_jit_gl_get_proctable()->VertexAttrib4fvNV)
#define glVertexAttrib4sNV               (_jit_gl_get_proctable()->VertexAttrib4sNV)
#define glVertexAttrib4svNV              (_jit_gl_get_proctable()->VertexAttrib4svNV)
#define glVertexAttrib4ubNV              (_jit_gl_get_proctable()->VertexAttrib4ubNV)
#define glVertexAttrib4ubvNV             (_jit_gl_get_proctable()->VertexAttrib4ubvNV)
#define glVertexAttribs1dvNV             (_jit_gl_get_proctable()->VertexAttribs1dvNV)
#define glVertexAttribs1fvNV             (_jit_gl_get_proctable()->VertexAttribs1fvNV)
#define glVertexAttribs1svNV             (_jit_gl_get_proctable()->VertexAttribs1svNV)
#define glVertexAttribs2dvNV             (_jit_gl_get_proctable()->VertexAttribs2dvNV)
#define glVertexAttribs2fvNV             (_jit_gl_get_proctable()->VertexAttribs2fvNV)
#define glVertexAttribs2svNV             (_jit_gl_get_proctable()->VertexAttribs2svNV)
#define glVertexAttribs3dvNV             (_jit_gl_get_proctable()->VertexAttribs3dvNV)
#define glVertexAttribs3fvNV             (_jit_gl_get_proctable()->VertexAttribs3fvNV)
#define glVertexAttribs3svNV             (_jit_gl_get_proctable()->VertexAttribs3svNV)
#define glVertexAttribs4dvNV             (_jit_gl_get_proctable()->VertexAttribs4dvNV)
#define glVertexAttribs4fvNV             (_jit_gl_get_proctable()->VertexAttribs4fvNV)
#define glVertexAttribs4svNV             (_jit_gl_get_proctable()->VertexAttribs4svNV)
#define glVertexAttribs4ubvNV            (_jit_gl_get_proctable()->VertexAttribs4ubvNV)
#define glTexBumpParameterivATI          (_jit_gl_get_proctable()->TexBumpParameterivATI)
#define glTexBumpParameterfvATI          (_jit_gl_get_proctable()->TexBumpParameterfvATI)
#define glGetTexBumpParameterivATI       (_jit_gl_get_proctable()->GetTexBumpParameterivATI)
#define glGetTexBumpParameterfvATI       (_jit_gl_get_proctable()->GetTexBumpParameterfvATI)
#define glGenFragmentShadersATI          (_jit_gl_get_proctable()->GenFragmentShadersATI)
#define glBindFragmentShaderATI          (_jit_gl_get_proctable()->BindFragmentShaderATI)
#define glDeleteFragmentShaderATI        (_jit_gl_get_proctable()->DeleteFragmentShaderATI)
#define glBeginFragmentShaderATI         (_jit_gl_get_proctable()->BeginFragmentShaderATI)
#define glEndFragmentShaderATI           (_jit_gl_get_proctable()->EndFragmentShaderATI)
#define glPassTexCoordATI                (_jit_gl_get_proctable()->PassTexCoordATI)
#define glSampleMapATI                   (_jit_gl_get_proctable()->SampleMapATI)
#define glColorFragmentOp1ATI            (_jit_gl_get_proctable()->ColorFragmentOp1ATI)
#define glColorFragmentOp2ATI            (_jit_gl_get_proctable()->ColorFragmentOp2ATI)
#define glColorFragmentOp3ATI            (_jit_gl_get_proctable()->ColorFragmentOp3ATI)
#define glAlphaFragmentOp1ATI            (_jit_gl_get_proctable()->AlphaFragmentOp1ATI)
#define glAlphaFragmentOp2ATI            (_jit_gl_get_proctable()->AlphaFragmentOp2ATI)
#define glAlphaFragmentOp3ATI            (_jit_gl_get_proctable()->AlphaFragmentOp3ATI)
#define glSetFragmentShaderConstantATI   (_jit_gl_get_proctable()->SetFragmentShaderConstantATI)
#define glPNTrianglesiATI                (_jit_gl_get_proctable()->PNTrianglesiATI)
#define glPNTrianglesfATI                (_jit_gl_get_proctable()->PNTrianglesfATI)
#define glNewObjectBufferATI             (_jit_gl_get_proctable()->NewObjectBufferATI)
#define glIsObjectBufferATI              (_jit_gl_get_proctable()->IsObjectBufferATI)
#define glUpdateObjectBufferATI          (_jit_gl_get_proctable()->UpdateObjectBufferATI)
#define glGetObjectBufferfvATI           (_jit_gl_get_proctable()->GetObjectBufferfvATI)
#define glGetObjectBufferivATI           (_jit_gl_get_proctable()->GetObjectBufferivATI)
#define glFreeObjectBufferATI            (_jit_gl_get_proctable()->FreeObjectBufferATI)
#define glArrayObjectATI                 (_jit_gl_get_proctable()->ArrayObjectATI)
#define glGetArrayObjectfvATI            (_jit_gl_get_proctable()->GetArrayObjectfvATI)
#define glGetArrayObjectivATI            (_jit_gl_get_proctable()->GetArrayObjectivATI)
#define glVariantArrayObjectATI          (_jit_gl_get_proctable()->VariantArrayObjectATI)
#define glGetVariantArrayObjectfvATI     (_jit_gl_get_proctable()->GetVariantArrayObjectfvATI)
#define glGetVariantArrayObjectivATI     (_jit_gl_get_proctable()->GetVariantArrayObjectivATI)
#define glBeginVertexShaderEXT           (_jit_gl_get_proctable()->BeginVertexShaderEXT)
#define glEndVertexShaderEXT             (_jit_gl_get_proctable()->EndVertexShaderEXT)
#define glBindVertexShaderEXT            (_jit_gl_get_proctable()->BindVertexShaderEXT)
#define glGenVertexShadersEXT            (_jit_gl_get_proctable()->GenVertexShadersEXT)
#define glDeleteVertexShaderEXT          (_jit_gl_get_proctable()->DeleteVertexShaderEXT)
#define glShaderOp1EXT                   (_jit_gl_get_proctable()->ShaderOp1EXT)
#define glShaderOp2EXT                   (_jit_gl_get_proctable()->ShaderOp2EXT)
#define glShaderOp3EXT                   (_jit_gl_get_proctable()->ShaderOp3EXT)
#define glSwizzleEXT                     (_jit_gl_get_proctable()->SwizzleEXT)
#define glWriteMaskEXT                   (_jit_gl_get_proctable()->WriteMaskEXT)
#define glInsertComponentEXT             (_jit_gl_get_proctable()->InsertComponentEXT)
#define glExtractComponentEXT            (_jit_gl_get_proctable()->ExtractComponentEXT)
#define glGenSymbolsEXT                  (_jit_gl_get_proctable()->GenSymbolsEXT)
#define glSetInvariantEXT                (_jit_gl_get_proctable()->SetInvariantEXT)
#define glSetLocalConstantEXT            (_jit_gl_get_proctable()->SetLocalConstantEXT)
#define glVariantbvEXT                   (_jit_gl_get_proctable()->VariantbvEXT)
#define glVariantsvEXT                   (_jit_gl_get_proctable()->VariantsvEXT)
#define glVariantivEXT                   (_jit_gl_get_proctable()->VariantivEXT)
#define glVariantfvEXT                   (_jit_gl_get_proctable()->VariantfvEXT)
#define glVariantdvEXT                   (_jit_gl_get_proctable()->VariantdvEXT)
#define glVariantubvEXT                  (_jit_gl_get_proctable()->VariantubvEXT)
#define glVariantusvEXT                  (_jit_gl_get_proctable()->VariantusvEXT)
#define glVariantuivEXT                  (_jit_gl_get_proctable()->VariantuivEXT)
#define glVariantPointerEXT              (_jit_gl_get_proctable()->VariantPointerEXT)
#define glEnableVariantClientStateEXT    (_jit_gl_get_proctable()->EnableVariantClientStateEXT)
#define glDisableVariantClientStateEXT   (_jit_gl_get_proctable()->DisableVariantClientStateEXT)
#define glBindLightParameterEXT          (_jit_gl_get_proctable()->BindLightParameterEXT)
#define glBindMaterialParameterEXT       (_jit_gl_get_proctable()->BindMaterialParameterEXT)
#define glBindTexGenParameterEXT         (_jit_gl_get_proctable()->BindTexGenParameterEXT)
#define glBindTextureUnitParameterEXT    (_jit_gl_get_proctable()->BindTextureUnitParameterEXT)
#define glBindParameterEXT               (_jit_gl_get_proctable()->BindParameterEXT)
#define glIsVariantEnabledEXT            (_jit_gl_get_proctable()->IsVariantEnabledEXT)
#define glGetVariantBooleanvEXT          (_jit_gl_get_proctable()->GetVariantBooleanvEXT)
#define glGetVariantIntegervEXT          (_jit_gl_get_proctable()->GetVariantIntegervEXT)
#define glGetVariantFloatvEXT            (_jit_gl_get_proctable()->GetVariantFloatvEXT)
#define glGetVariantPointervEXT          (_jit_gl_get_proctable()->GetVariantPointervEXT)
#define glGetInvariantBooleanvEXT        (_jit_gl_get_proctable()->GetInvariantBooleanvEXT)
#define glGetInvariantIntegervEXT        (_jit_gl_get_proctable()->GetInvariantIntegervEXT)
#define glGetInvariantFloatvEXT          (_jit_gl_get_proctable()->GetInvariantFloatvEXT)
#define glGetLocalConstantBooleanvEXT    (_jit_gl_get_proctable()->GetLocalConstantBooleanvEXT)
#define glGetLocalConstantIntegervEXT    (_jit_gl_get_proctable()->GetLocalConstantIntegervEXT)
#define glGetLocalConstantFloatvEXT      (_jit_gl_get_proctable()->GetLocalConstantFloatvEXT)
#define glVertexStream1sATI              (_jit_gl_get_proctable()->VertexStream1sATI)
#define glVertexStream1svATI             (_jit_gl_get_proctable()->VertexStream1svATI)
#define glVertexStream1iATI              (_jit_gl_get_proctable()->VertexStream1iATI)
#define glVertexStream1ivATI             (_jit_gl_get_proctable()->VertexStream1ivATI)
#define glVertexStream1fATI              (_jit_gl_get_proctable()->VertexStream1fATI)
#define glVertexStream1fvATI             (_jit_gl_get_proctable()->VertexStream1fvATI)
#define glVertexStream1dATI              (_jit_gl_get_proctable()->VertexStream1dATI)
#define glVertexStream1dvATI             (_jit_gl_get_proctable()->VertexStream1dvATI)
#define glVertexStream2sATI              (_jit_gl_get_proctable()->VertexStream2sATI)
#define glVertexStream2svATI             (_jit_gl_get_proctable()->VertexStream2svATI)
#define glVertexStream2iATI              (_jit_gl_get_proctable()->VertexStream2iATI)
#define glVertexStream2ivATI             (_jit_gl_get_proctable()->VertexStream2ivATI)
#define glVertexStream2fATI              (_jit_gl_get_proctable()->VertexStream2fATI)
#define glVertexStream2fvATI             (_jit_gl_get_proctable()->VertexStream2fvATI)
#define glVertexStream2dATI              (_jit_gl_get_proctable()->VertexStream2dATI)
#define glVertexStream2dvATI             (_jit_gl_get_proctable()->VertexStream2dvATI)
#define glVertexStream3sATI              (_jit_gl_get_proctable()->VertexStream3sATI)
#define glVertexStream3svATI             (_jit_gl_get_proctable()->VertexStream3svATI)
#define glVertexStream3iATI              (_jit_gl_get_proctable()->VertexStream3iATI)
#define glVertexStream3ivATI             (_jit_gl_get_proctable()->VertexStream3ivATI)
#define glVertexStream3fATI              (_jit_gl_get_proctable()->VertexStream3fATI)
#define glVertexStream3fvATI             (_jit_gl_get_proctable()->VertexStream3fvATI)
#define glVertexStream3dATI              (_jit_gl_get_proctable()->VertexStream3dATI)
#define glVertexStream3dvATI             (_jit_gl_get_proctable()->VertexStream3dvATI)
#define glVertexStream4sATI              (_jit_gl_get_proctable()->VertexStream4sATI)
#define glVertexStream4svATI             (_jit_gl_get_proctable()->VertexStream4svATI)
#define glVertexStream4iATI              (_jit_gl_get_proctable()->VertexStream4iATI)
#define glVertexStream4ivATI             (_jit_gl_get_proctable()->VertexStream4ivATI)
#define glVertexStream4fATI              (_jit_gl_get_proctable()->VertexStream4fATI)
#define glVertexStream4fvATI             (_jit_gl_get_proctable()->VertexStream4fvATI)
#define glVertexStream4dATI              (_jit_gl_get_proctable()->VertexStream4dATI)
#define glVertexStream4dvATI             (_jit_gl_get_proctable()->VertexStream4dvATI)
#define glNormalStream3bATI              (_jit_gl_get_proctable()->NormalStream3bATI)
#define glNormalStream3bvATI             (_jit_gl_get_proctable()->NormalStream3bvATI)
#define glNormalStream3sATI              (_jit_gl_get_proctable()->NormalStream3sATI)
#define glNormalStream3svATI             (_jit_gl_get_proctable()->NormalStream3svATI)
#define glNormalStream3iATI              (_jit_gl_get_proctable()->NormalStream3iATI)
#define glNormalStream3ivATI             (_jit_gl_get_proctable()->NormalStream3ivATI)
#define glNormalStream3fATI              (_jit_gl_get_proctable()->NormalStream3fATI)
#define glNormalStream3fvATI             (_jit_gl_get_proctable()->NormalStream3fvATI)
#define glNormalStream3dATI              (_jit_gl_get_proctable()->NormalStream3dATI)
#define glNormalStream3dvATI             (_jit_gl_get_proctable()->NormalStream3dvATI)
#define glClientActiveVertexStreamATI    (_jit_gl_get_proctable()->ClientActiveVertexStreamATI)
#define glVertexBlendEnviATI             (_jit_gl_get_proctable()->VertexBlendEnviATI)
#define glVertexBlendEnvfATI             (_jit_gl_get_proctable()->VertexBlendEnvfATI)
#define glElementPointerATI              (_jit_gl_get_proctable()->ElementPointerATI)
#define glDrawElementArrayATI            (_jit_gl_get_proctable()->DrawElementArrayATI)
#define glDrawRangeElementArrayATI       (_jit_gl_get_proctable()->DrawRangeElementArrayATI)
#define glDrawMeshArraysSUN              (_jit_gl_get_proctable()->DrawMeshArraysSUN)
#define glGenOcclusionQueriesNV          (_jit_gl_get_proctable()->GenOcclusionQueriesNV)
#define glDeleteOcclusionQueriesNV       (_jit_gl_get_proctable()->DeleteOcclusionQueriesNV)
#define glIsOcclusionQueryNV             (_jit_gl_get_proctable()->IsOcclusionQueryNV)
#define glBeginOcclusionQueryNV          (_jit_gl_get_proctable()->BeginOcclusionQueryNV)
#define glEndOcclusionQueryNV            (_jit_gl_get_proctable()->EndOcclusionQueryNV)
#define glGetOcclusionQueryivNV          (_jit_gl_get_proctable()->GetOcclusionQueryivNV)
#define glGetOcclusionQueryuivNV         (_jit_gl_get_proctable()->GetOcclusionQueryuivNV)
#define glPointParameteriNV              (_jit_gl_get_proctable()->PointParameteriNV)
#define glPointParameterivNV             (_jit_gl_get_proctable()->PointParameterivNV)
#define glActiveStencilFaceEXT           (_jit_gl_get_proctable()->ActiveStencilFaceEXT)
#define glDrawBuffersATI                 (_jit_gl_get_proctable()->DrawBuffersATI)
#define glProgramNamedParameter4fNV      (_jit_gl_get_proctable()->ProgramNamedParameter4fNV)
#define glProgramNamedParameter4dNV      (_jit_gl_get_proctable()->ProgramNamedParameter4dNV)
#define glProgramNamedParameter4fvNV     (_jit_gl_get_proctable()->ProgramNamedParameter4fvNV)
#define glProgramNamedParameter4dvNV     (_jit_gl_get_proctable()->ProgramNamedParameter4dvNV)
#define glGetProgramNamedParameterfvNV   (_jit_gl_get_proctable()->GetProgramNamedParameterfvNV)
#define glGetProgramNamedParameterdvNV   (_jit_gl_get_proctable()->GetProgramNamedParameterdvNV)
#define glVertex2hNV                     (_jit_gl_get_proctable()->Vertex2hNV)
#define glVertex2hvNV                    (_jit_gl_get_proctable()->Vertex2hvNV)
#define glVertex3hNV                     (_jit_gl_get_proctable()->Vertex3hNV)
#define glVertex3hvNV                    (_jit_gl_get_proctable()->Vertex3hvNV)
#define glVertex4hNV                     (_jit_gl_get_proctable()->Vertex4hNV)
#define glVertex4hvNV                    (_jit_gl_get_proctable()->Vertex4hvNV)
#define glNormal3hNV                     (_jit_gl_get_proctable()->Normal3hNV)
#define glNormal3hvNV                    (_jit_gl_get_proctable()->Normal3hvNV)
#define glColor3hNV                      (_jit_gl_get_proctable()->Color3hNV)
#define glColor3hvNV                     (_jit_gl_get_proctable()->Color3hvNV)
#define glColor4hNV                      (_jit_gl_get_proctable()->Color4hNV)
#define glColor4hvNV                     (_jit_gl_get_proctable()->Color4hvNV)
#define glTexCoord1hNV                   (_jit_gl_get_proctable()->TexCoord1hNV)
#define glTexCoord1hvNV                  (_jit_gl_get_proctable()->TexCoord1hvNV)
#define glTexCoord2hNV                   (_jit_gl_get_proctable()->TexCoord2hNV)
#define glTexCoord2hvNV                  (_jit_gl_get_proctable()->TexCoord2hvNV)
#define glTexCoord3hNV                   (_jit_gl_get_proctable()->TexCoord3hNV)
#define glTexCoord3hvNV                  (_jit_gl_get_proctable()->TexCoord3hvNV)
#define glTexCoord4hNV                   (_jit_gl_get_proctable()->TexCoord4hNV)
#define glTexCoord4hvNV                  (_jit_gl_get_proctable()->TexCoord4hvNV)
#define glMultiTexCoord1hNV              (_jit_gl_get_proctable()->MultiTexCoord1hNV)
#define glMultiTexCoord1hvNV             (_jit_gl_get_proctable()->MultiTexCoord1hvNV)
#define glMultiTexCoord2hNV              (_jit_gl_get_proctable()->MultiTexCoord2hNV)
#define glMultiTexCoord2hvNV             (_jit_gl_get_proctable()->MultiTexCoord2hvNV)
#define glMultiTexCoord3hNV              (_jit_gl_get_proctable()->MultiTexCoord3hNV)
#define glMultiTexCoord3hvNV             (_jit_gl_get_proctable()->MultiTexCoord3hvNV)
#define glMultiTexCoord4hNV              (_jit_gl_get_proctable()->MultiTexCoord4hNV)
#define glMultiTexCoord4hvNV             (_jit_gl_get_proctable()->MultiTexCoord4hvNV)
#define glFogCoordhNV                    (_jit_gl_get_proctable()->FogCoordhNV)
#define glFogCoordhvNV                   (_jit_gl_get_proctable()->FogCoordhvNV)
#define glSecondaryColor3hNV             (_jit_gl_get_proctable()->SecondaryColor3hNV)
#define glSecondaryColor3hvNV            (_jit_gl_get_proctable()->SecondaryColor3hvNV)
#define glVertexWeighthNV                (_jit_gl_get_proctable()->VertexWeighthNV)
#define glVertexWeighthvNV               (_jit_gl_get_proctable()->VertexWeighthvNV)
#define glVertexAttrib1hNV               (_jit_gl_get_proctable()->VertexAttrib1hNV)
#define glVertexAttrib1hvNV              (_jit_gl_get_proctable()->VertexAttrib1hvNV)
#define glVertexAttrib2hNV               (_jit_gl_get_proctable()->VertexAttrib2hNV)
#define glVertexAttrib2hvNV              (_jit_gl_get_proctable()->VertexAttrib2hvNV)
#define glVertexAttrib3hNV               (_jit_gl_get_proctable()->VertexAttrib3hNV)
#define glVertexAttrib3hvNV              (_jit_gl_get_proctable()->VertexAttrib3hvNV)
#define glVertexAttrib4hNV               (_jit_gl_get_proctable()->VertexAttrib4hNV)
#define glVertexAttrib4hvNV              (_jit_gl_get_proctable()->VertexAttrib4hvNV)
#define glVertexAttribs1hvNV             (_jit_gl_get_proctable()->VertexAttribs1hvNV)
#define glVertexAttribs2hvNV             (_jit_gl_get_proctable()->VertexAttribs2hvNV)
#define glVertexAttribs3hvNV             (_jit_gl_get_proctable()->VertexAttribs3hvNV)
#define glVertexAttribs4hvNV             (_jit_gl_get_proctable()->VertexAttribs4hvNV)
#define glPixelDataRangeNV               (_jit_gl_get_proctable()->PixelDataRangeNV)
#define glFlushPixelDataRangeNV          (_jit_gl_get_proctable()->FlushPixelDataRangeNV)
#define glPrimitiveRestartNV             (_jit_gl_get_proctable()->PrimitiveRestartNV)
#define glPrimitiveRestartIndexNV        (_jit_gl_get_proctable()->PrimitiveRestartIndexNV)
#define glMapObjectBufferATI             (_jit_gl_get_proctable()->MapObjectBufferATI)
#define glUnmapObjectBufferATI           (_jit_gl_get_proctable()->UnmapObjectBufferATI)
#define glStencilOpSeparateATI           (_jit_gl_get_proctable()->StencilOpSeparateATI)
#define glStencilFuncSeparateATI         (_jit_gl_get_proctable()->StencilFuncSeparateATI)
#define glVertexAttribArrayObjectATI     (_jit_gl_get_proctable()->VertexAttribArrayObjectATI)
#define glGetVertexAttribArrayObjectfvATI (_jit_gl_get_proctable()->GetVertexAttribArrayObjectfvATI)
#define glGetVertexAttribArrayObjectivATI (_jit_gl_get_proctable()->GetVertexAttribArrayObjectivATI)
#define glDepthBoundsEXT                 (_jit_gl_get_proctable()->DepthBoundsEXT)
#define glBlendEquationSeparateEXT       (_jit_gl_get_proctable()->BlendEquationSeparateEXT)
#define glAddSwapHintRectWIN             (_jit_gl_get_proctable()->AddSwapHintRectWIN)
#define glBindFramebufferEXT			 (_jit_gl_get_proctable()->BindFramebufferEXT)
#define glBindRenderbufferEXT			 (_jit_gl_get_proctable()->BindRenderbufferEXT)
#define glCheckFramebufferStatusEXT		 (_jit_gl_get_proctable()->CheckFramebufferStatusEXT)
#define glDeleteFramebuffersEXT			 (_jit_gl_get_proctable()->DeleteFramebuffersEXT)
#define glDeleteRenderbuffersEXT		 (_jit_gl_get_proctable()->DeleteRenderbuffersEXT)
#define glFramebufferRenderbufferEXT	 (_jit_gl_get_proctable()->FramebufferRenderbufferEXT)
#define glFramebufferTexture1DEXT		 (_jit_gl_get_proctable()->FramebufferTexture1DEXT)
#define glFramebufferTexture2DEXT		 (_jit_gl_get_proctable()->FramebufferTexture2DEXT)
#define glFramebufferTexture3DEXT		 (_jit_gl_get_proctable()->FramebufferTexture3DEXT)
#define glGenFramebuffersEXT			 (_jit_gl_get_proctable()->GenFramebuffersEXT)
#define glGenRenderbuffersEXT			 (_jit_gl_get_proctable()->GenRenderbuffersEXT)
#define glGenerateMipmapEXT				 (_jit_gl_get_proctable()->GenerateMipmapEXT)
#define glGetFramebufferAttachmentParameterivEXT (_jit_gl_get_proctable()->GetFramebufferAttachmentParameterivEXT)
#define glGetRenderbufferParameterivEXT  (_jit_gl_get_proctable()->GetRenderbufferParameterivEXT)
#define glIsFramebufferEXT				 (_jit_gl_get_proctable()->IsFramebufferEXT)
#define glIsRenderbufferEXT				 (_jit_gl_get_proctable()->IsRenderbufferEXT)
#define glRenderbufferStorageEXT		 (_jit_gl_get_proctable()->RenderbufferStorageEXT)


#define glProgramParameteriEXT				(_jit_gl_get_proctable()->ProgramParameteriEXT)
#define glFramebufferTextureEXT				(_jit_gl_get_proctable()->FramebufferTextureEXT)
#define glFramebufferTextureLayerEXT		(_jit_gl_get_proctable()->FramebufferTextureLayerEXT)
#define glFramebufferTextureFaceEXT			(_jit_gl_get_proctable()->FramebufferTextureFaceEXT)

#define glDrawBuffersARB					(_jit_gl_get_proctable()->DrawBuffersARB)





#ifdef MAC_VERSION
#define glElementPointerAPPLE            (_jit_gl_get_proctable()->ElementPointerAPPLE)
#define glDrawElementArrayAPPLE          (_jit_gl_get_proctable()->DrawElementArrayAPPLE)
#define glDrawRangeElementArrayAPPLE     (_jit_gl_get_proctable()->DrawRangeElementArrayAPPLE)
#define glMultiDrawElementArrayAPPLE     (_jit_gl_get_proctable()->MultiDrawElementArrayAPPLE)
#define glMultiDrawRangeElementArrayAPPLE (_jit_gl_get_proctable()->MultiDrawRangeElementArrayAPPLE)
#define glGenFencesAPPLE                 (_jit_gl_get_proctable()->GenFencesAPPLE)
#define glDeleteFencesAPPLE              (_jit_gl_get_proctable()->DeleteFencesAPPLE)
#define glSetFenceAPPLE                  (_jit_gl_get_proctable()->SetFenceAPPLE)
#define glIsFenceAPPLE                   (_jit_gl_get_proctable()->IsFenceAPPLE)
#define glTestFenceAPPLE                 (_jit_gl_get_proctable()->TestFenceAPPLE)
#define glFinishFenceAPPLE               (_jit_gl_get_proctable()->FinishFenceAPPLE)
#define glTestObjectAPPLE                (_jit_gl_get_proctable()->TestObjectAPPLE)
#define glFinishObjectAPPLE              (_jit_gl_get_proctable()->FinishObjectAPPLE)
#define glBindVertexArrayAPPLE           (_jit_gl_get_proctable()->BindVertexArrayAPPLE)
#define glDeleteVertexArraysAPPLE        (_jit_gl_get_proctable()->DeleteVertexArraysAPPLE)
#define glGenVertexArraysAPPLE           (_jit_gl_get_proctable()->GenVertexArraysAPPLE)
#define glIsVertexArrayAPPLE             (_jit_gl_get_proctable()->IsVertexArrayAPPLE)
#define glVertexArrayRangeAPPLE          (_jit_gl_get_proctable()->VertexArrayRangeAPPLE)
#define glFlushVertexArrayRangeAPPLE     (_jit_gl_get_proctable()->FlushVertexArrayRangeAPPLE)
#define glVertexArrayParameteriAPPLE     (_jit_gl_get_proctable()->VertexArrayParameteriAPPLE)
#define glTextureRangeAPPLE              (_jit_gl_get_proctable()->TextureRangeAPPLE)
#define glGetTexParameterPointervAPPLE   (_jit_gl_get_proctable()->GetTexParameterPointervAPPLE)
#define aglCreatePBuffer                 (_jit_gl_get_proctable()->CreatePBuffer)
#define aglDescribePBuffer               (_jit_gl_get_proctable()->DescribePBuffer)
#define aglDestroyPBuffer                (_jit_gl_get_proctable()->DestroyPBuffer)
#define aglGetPBuffer                    (_jit_gl_get_proctable()->GetPBuffer)
#define aglSetPBuffer                    (_jit_gl_get_proctable()->SetPBuffer)
#define aglTexImagePBuffer				 (_jit_gl_get_proctable()->TexImagePBuffer)
#define aglSurfaceTexture                (_jit_gl_get_proctable()->SurfaceTexture)
#endif
#ifdef _WIN32
#define wglCreateBufferRegionARB          (_jit_gl_get_proctable()->CreateBufferRegionARB)
#define wglDeleteBufferRegionARB          (_jit_gl_get_proctable()->DeleteBufferRegionARB)
#define wglSaveBufferRegionARB            (_jit_gl_get_proctable()->SaveBufferRegionARB)
#define wglRestoreBufferRegionARB         (_jit_gl_get_proctable()->RestoreBufferRegionARB)
#define wglGetExtensionsStringARB         (_jit_gl_get_proctable()->GetExtensionsStringARB)
#define wglGetPixelFormatAttribivARB      (_jit_gl_get_proctable()->GetPixelFormatAttribivARB)
#define wglGetPixelFormatAttribfvARB      (_jit_gl_get_proctable()->GetPixelFormatAttribfvARB)
#define wglChoosePixelFormatARB           (_jit_gl_get_proctable()->ChoosePixelFormatARB)
#define wglMakeContextCurrentARB          (_jit_gl_get_proctable()->MakeContextCurrentARB)
#define wglGetCurrentReadDCARB            (_jit_gl_get_proctable()->GetCurrentReadDCARB)
#define wglCreatePbufferARB               (_jit_gl_get_proctable()->CreatePbufferARB)
#define wglGetPbufferDCARB                (_jit_gl_get_proctable()->GetPbufferDCARB)
#define wglReleasePbufferDCARB            (_jit_gl_get_proctable()->ReleasePbufferDCARB)
#define wglDestroyPbufferARB              (_jit_gl_get_proctable()->DestroyPbufferARB)
#define wglQueryPbufferARB                (_jit_gl_get_proctable()->QueryPbufferARB)
#define wglBindTexImageARB                (_jit_gl_get_proctable()->BindTexImageARB)
#define wglReleaseTexImageARB             (_jit_gl_get_proctable()->ReleaseTexImageARB)
#define wglSetPbufferAttribARB            (_jit_gl_get_proctable()->SetPbufferAttribARB)
#define wglCreateDisplayColorTableEXT     (_jit_gl_get_proctable()->CreateDisplayColorTableEXT)
#define wglLoadDisplayColorTableEXT       (_jit_gl_get_proctable()->LoadDisplayColorTableEXT)
#define wglBindDisplayColorTableEXT       (_jit_gl_get_proctable()->BindDisplayColorTableEXT)
#define wglDestroyDisplayColorTableEXT    (_jit_gl_get_proctable()->DestroyDisplayColorTableEXT)
#define wglGetExtensionsStringEXT         (_jit_gl_get_proctable()->GetExtensionsStringEXT)
#define wglMakeContextCurrentEXT          (_jit_gl_get_proctable()->MakeContextCurrentEXT)
#define wglGetCurrentReadDCEXT            (_jit_gl_get_proctable()->GetCurrentReadDCEXT)
#define wglCreatePbufferEXT               (_jit_gl_get_proctable()->CreatePbufferEXT)
#define wglGetPbufferDCEXT                (_jit_gl_get_proctable()->GetPbufferDCEXT)
#define wglReleasePbufferDCEXT            (_jit_gl_get_proctable()->ReleasePbufferDCEXT)
#define wglDestroyPbufferEXT              (_jit_gl_get_proctable()->DestroyPbufferEXT)
#define wglQueryPbufferEXT                (_jit_gl_get_proctable()->QueryPbufferEXT)
#define wglGetPixelFormatAttribivEXT      (_jit_gl_get_proctable()->GetPixelFormatAttribivEXT)
#define wglGetPixelFormatAttribfvEXT      (_jit_gl_get_proctable()->GetPixelFormatAttribfvEXT)
#define wglChoosePixelFormatEXT           (_jit_gl_get_proctable()->ChoosePixelFormatEXT)
#define wglSwapIntervalEXT                (_jit_gl_get_proctable()->SwapIntervalEXT)
#define wglGetSwapIntervalEXT             (_jit_gl_get_proctable()->GetSwapIntervalEXT)
#define wglAllocateMemoryNV               (_jit_gl_get_proctable()->AllocateMemoryNV)
#define wglFreeMemoryNV                   (_jit_gl_get_proctable()->FreeMemoryNV)
#define wglGetSyncValuesOML               (_jit_gl_get_proctable()->GetSyncValuesOML)
#define wglGetMscRateOML                  (_jit_gl_get_proctable()->GetMscRateOML)
#define wglSwapBuffersMscOML              (_jit_gl_get_proctable()->SwapBuffersMscOML)
#define wglSwapLayerBuffersMscOML         (_jit_gl_get_proctable()->SwapLayerBuffersMscOML)
#define wglWaitForMscOML                  (_jit_gl_get_proctable()->WaitForMscOML)
#define wglWaitForSbcOML                  (_jit_gl_get_proctable()->WaitForSbcOML)
#define wglGetDigitalVideoParametersI3D   (_jit_gl_get_proctable()->GetDigitalVideoParametersI3D)
#define wglSetDigitalVideoParametersI3D   (_jit_gl_get_proctable()->SetDigitalVideoParametersI3D)
#define wglGetGammaTableParametersI3D     (_jit_gl_get_proctable()->GetGammaTableParametersI3D)
#define wglSetGammaTableParametersI3D     (_jit_gl_get_proctable()->SetGammaTableParametersI3D)
#define wglGetGammaTableI3D               (_jit_gl_get_proctable()->GetGammaTableI3D)
#define wglSetGammaTableI3D               (_jit_gl_get_proctable()->SetGammaTableI3D)
#define wglEnableGenlockI3D               (_jit_gl_get_proctable()->EnableGenlockI3D)
#define wglDisableGenlockI3D              (_jit_gl_get_proctable()->DisableGenlockI3D)
#define wglIsEnabledGenlockI3D            (_jit_gl_get_proctable()->IsEnabledGenlockI3D)
#define wglGenlockSourceI3D               (_jit_gl_get_proctable()->GenlockSourceI3D)
#define wglGetGenlockSourceI3D            (_jit_gl_get_proctable()->GetGenlockSourceI3D)
#define wglGenlockSourceEdgeI3D           (_jit_gl_get_proctable()->GenlockSourceEdgeI3D)
#define wglGetGenlockSourceEdgeI3D        (_jit_gl_get_proctable()->GetGenlockSourceEdgeI3D)
#define wglGenlockSampleRateI3D           (_jit_gl_get_proctable()->GenlockSampleRateI3D)
#define wglGetGenlockSampleRateI3D        (_jit_gl_get_proctable()->GetGenlockSampleRateI3D)
#define wglGenlockSourceDelayI3D          (_jit_gl_get_proctable()->GenlockSourceDelayI3D)
#define wglGetGenlockSourceDelayI3D       (_jit_gl_get_proctable()->GetGenlockSourceDelayI3D)
#define wglQueryGenlockMaxSourceDelayI3D  (_jit_gl_get_proctable()->QueryGenlockMaxSourceDelayI3D)
#define wglCreateImageBufferI3D           (_jit_gl_get_proctable()->CreateImageBufferI3D)
#define wglDestroyImageBufferI3D          (_jit_gl_get_proctable()->DestroyImageBufferI3D)
#define wglAssociateImageBufferEventsI3D  (_jit_gl_get_proctable()->AssociateImageBufferEventsI3D)
#define wglReleaseImageBufferEventsI3D    (_jit_gl_get_proctable()->ReleaseImageBufferEventsI3D)
#define wglEnableFrameLockI3D             (_jit_gl_get_proctable()->EnableFrameLockI3D)
#define wglDisableFrameLockI3D            (_jit_gl_get_proctable()->DisableFrameLockI3D)
#define wglIsEnabledFrameLockI3D          (_jit_gl_get_proctable()->IsEnabledFrameLockI3D)
#define wglQueryFrameLockMasterI3D        (_jit_gl_get_proctable()->QueryFrameLockMasterI3D)
#define wglGetFrameUsageI3D               (_jit_gl_get_proctable()->GetFrameUsageI3D)
#define wglBeginFrameTrackingI3D          (_jit_gl_get_proctable()->BeginFrameTrackingI3D)
#define wglEndFrameTrackingI3D            (_jit_gl_get_proctable()->EndFrameTrackingI3D)
#define wglQueryFrameTrackingI3D          (_jit_gl_get_proctable()->QueryFrameTrackingI3D)
#endif /* _WIN32 */

/*
 * Retrieval function for getting the current proc table from
 * the global context.  
 *
 * TODO: thread local proc/context dependent proc table?
 */
t_jit_gl_extprocs *_jit_gl_get_proctable(void);
//static _inline t_jit_gl_extprocs *_jit_gl_get_proctable(void);

/*
 * Initialization function for the proc table in case the application 
 * needs to use multiple proc tables (one per opengl context and/or thread). 
 */
static _inline void jit_gl_init_extension_procs(t_jit_gl_extprocs *procs)
{
	extern t_jit_gl_extprocs _jit_gl_extension_procs;
	*procs = _jit_gl_extension_procs;
}

/****************************************************************************/

#if C74_PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif C74_PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

/****************************************************************************/

#endif /* _GLPROCS_H_ */
