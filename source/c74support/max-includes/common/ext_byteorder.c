
float byteorder_swapf32(float f){
	unsigned char c,*a;

	a = (unsigned char *)&f;
	c=a[3]; a[3]=a[0]; a[0]=c;
	c=a[2]; a[2]=a[1]; a[1]=c;

	return f;
}

double byteorder_swapf64(double f){
	unsigned char c,*a;

	a = (unsigned char *)&f;
	c=a[7]; a[7]=a[0]; a[0]=c;
	c=a[6]; a[6]=a[1]; a[1]=c;
	c=a[5]; a[5]=a[2]; a[2]=c;
	c=a[4]; a[4]=a[3]; a[3]=c;

	return f;
}	

// these functions are inplace
void byteorder_swap_pointer_16(unsigned char *p)
{
	unsigned char c;
	c=p[1]; p[1]=p[0]; p[0]=c;
}

void byteorder_swap_pointer_32(unsigned char *p)
{
	unsigned char c;
	c=p[3]; p[3]=p[0]; p[0]=c;
	c=p[2]; p[2]=p[1]; p[1]=c;
}

void byteorder_swap_pointer_64(unsigned char *p)
{
	unsigned char c;
	c=p[7]; p[7]=p[0]; p[0]=c;
	c=p[6]; p[6]=p[1]; p[1]=c;
	c=p[5]; p[5]=p[2]; p[2]=c;
	c=p[4]; p[4]=p[3]; p[3]=c;
}	

// these function copy from one pointer to another (src!=dst)
void byteorder_swap_pointer_16_copy(unsigned char *src, unsigned char *dst)
{
	dst[1] = src[0];
	dst[0] = src[1];
}

void byteorder_swap_pointer_32_copy(unsigned char *src, unsigned char *dst)
{
	dst[3] = src[0];
	dst[2] = src[1];
	dst[1] = src[2];
	dst[0] = src[3];
}

void byteorder_swap_pointer_64_copy(unsigned char *src, unsigned char *dst)
{
	dst[7] = src[0];
	dst[6] = src[1];
	dst[5] = src[2];
	dst[4] = src[3];
	dst[3] = src[4];
	dst[2] = src[5];
	dst[1] = src[6];
	dst[0] = src[7];
}

// these functions return floating point values from a byteswapped pointer
float byteorder_swap_pointer_32_to_float32(unsigned char *p)
{
	float f;
	byteorder_swap_pointer_32_copy(p,(unsigned char *)&f);
	return f;
}

double byteorder_swap_pointer_64_to_float64(unsigned char *p)
{
	double f;
	byteorder_swap_pointer_64_copy(p,(unsigned char *)&f);
	return f;
}

