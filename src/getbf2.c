#include <stdio.h>
#include <string.h>

#include "bff4.h"

int bff4_getbf2(char const *buffer, int *cursor)
{
	int a;

	do {
		a = buffer[*cursor];
		(*cursor)++;
		if (a == '\0') return -1;
	} while (!strchr(",.[]+-<>!", a));

	return a;
}
