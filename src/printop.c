#include <stdio.h>
#include <string.h>

#include "bff4.h"

void printop(struct op *z)
{
	int j;

	printf("op='");
	if (!strchr("<>+-", z->c)) printf("%c", (char)z->c);
	for (j = 0; j < z->dbsz; j++) printf("%c", (char)z->db[j]);
	printf("' shift=%d off=%d go=%d { "
	       , z->shift, z->off, z->igo);
	for (j = 0; j < z->sz; j++)
		printf("%d ", z->d[j]);
	printf("}\n");
}

