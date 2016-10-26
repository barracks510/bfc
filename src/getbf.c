#include <stdio.h>
#include <string.h>

#include "bff4.h"

int getbf()
{
	int a;

next:
	a = getchar();
	if (a == -1) return -1;
	if (!strchr(",.[]+-<>!", a)) goto next;
	return a;
}
