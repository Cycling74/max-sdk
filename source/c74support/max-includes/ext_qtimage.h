#ifndef _qtimage_H_
#define _qtimage_H_

#ifdef __cplusplus
extern "C" {
#endif

#define QTI_SCALEMODE_NONE 			0
#define QTI_SCALEMODE_MATRIX 		1
#define QTI_SCALEMODE_RECT 			2
#define QTI_SCALEMODE_AUTOFIT 		3

#define QTI_FLAG_QTML_GWORLD		0x00000001L

#ifdef MAC_VERSION
#ifndef __QUICKDRAW__
struct CGrafPort {
	long	opaque;
};
typedef struct CGrafPort				CGrafPort;
typedef struct CGrafPort*				CGrafPtr;

struct RGBColor {
	unsigned short		red;
	unsigned short		green;
	unsigned short		blue;
};
typedef struct RGBColor				RGBColor;
#endif // __QUICKDRAW__
#endif // MAC_VERSION

long qtimage_open(char *name, short path, CGrafPtr *gp, void *extra);
long qtimage_getrect(char *name, short path, Rect *r, void *extra);
void *qti_extra_new           (void);
void qti_extra_free           (void *p);
long qti_extra_pixelformat_get(void *p, OSType *pixelformat); 
long qti_extra_pixelformat_set(void *p, OSType pixelformat); 
long qti_extra_matrix_get     (void *p, void *m);
long qti_extra_matrix_set     (void *p, void *m);
long qti_extra_rect_get       (void *p, Rect *r);
long qti_extra_rect_set       (void *p, Rect *r);
long qti_extra_scalemode_get  (void *p, long *scalemode);
long qti_extra_scalemode_set  (void *p, long scalemode);
long qti_extra_time_get       (void *p, double *time);
long qti_extra_time_set       (void *p, double time);
long qti_extra_flags_get      (void *p, long *flags);
long qti_extra_flags_set      (void *p, long flags);

#ifdef __cplusplus
}
#endif

#endif // _qtimage_H_
