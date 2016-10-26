#include <stdlib.h>
#include <string.h>

#include "bff4.h"

void *zalloc(void *p, int sz, int osz)
{
	p = realloc(p, sz);
	memset((char *)p + osz, 0, sz - osz);
	return p;
}

