/*
 * Copyright (c) 2016 Dennis Chen <barracks510@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

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
