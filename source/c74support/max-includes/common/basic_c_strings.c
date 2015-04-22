#include "ext.h"

#ifdef WIN_VERSION

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>

#endif // #ifdef WIN_VERSION

#ifndef WIN_VERSION
#ifndef NDEBUG

char *strcpy(char *s1, const char *s2)
{
	char *ret = s1;
	
	while ((*s1++ = *s2++) != 0)
		;

	return ret;
}

char *strcat(char *s1, const char *s2)
{
	char *ret = s1;

	while (*s1++)
		;
	--s1;
	while ((*s1++ = *s2++) != 0)
		;
	return ret;
}

int strcmp(const char *s1, const char *s2)
{
	char c1, c2, dif;
	
	for (;;) {
		if (!(c1 = *s1++))
			return *s2 ? -1 : 0;
		if (!(c2 = *s2++))
			return 1;
		if (!(dif = (c1 - c2)))
			continue;
		if (dif < 0)
			return -1;
		else
			return 1;
	}

	return 0;
}

unsigned long strlen(const char *s)
{
	long len = 0;
	
	while (*s++)
		++len;
	
	return len;
}

char *strncpy(char *s1, const char *s2, unsigned long n)
{
	char *res = s1;
	
	while (n--) {
		if ((*s1++ = *s2)!=0)
			++s2;
	}
	return res;
}

char *strncat(char *s1, const char *s2, unsigned long n)
{
	char *res = s1;
	
	if (n) {
		while (*s1++)
			;
		--s1;
		while (n--)
			if (!(*s1++ = *s2++))
				return res;
		*s1 = '\0';			
	}
	return res;
}

int strncmp(const char *s1, const char *s2, unsigned long n)
{
	char c1, c2, dif;
	
	while (n--) {
		if (!(c1 = *s1++))
			return *s2 ? -1 : 0;
		if (!(c2 = *s2++))
			return 1;
		if (!(dif = (c1 - c2)))
			continue;
		if (dif < 0)
			return -1;
		else
			return 1;
	}
	return 0;
}

#endif // NDEBUG
#endif // #ifndef WIN_VERSION

void ctopcpy(unsigned char *p1, char *p2)
{
	long len= (long) strlen(p2);
	//changed this to not rely on CtoPstr
	strcpy((char *)p1+1, p2);
	p1[0]=(len>255)?255:(unsigned char)len;
}

void ptoccpy(char *p1, unsigned char *p2)
{
	register int len = (*p2++) & 0xff;
	while (len--) *p1++ = *p2++;
	*p1 = '\0';
}

void setmem(void *ss, long n, short b)
{
	register int i;
	unsigned char *s = (unsigned char *)ss;
	
	for (i=0; i < n; i++,s++)
		*s = (unsigned char)b;
}

void pstrcpy(unsigned char *p2, unsigned char *p1)
{
	register int len;
	
	len = *p2++ = *p1++;
	while (--len>=0) *p2++=*p1++;
}
