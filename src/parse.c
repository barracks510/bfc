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

/* bff4_parse parses a BrainFuck program
 *
 * @param buffer is a pointer to the program in memory
 * @param result will be written with a pointer to the parsed result in memory
 * @return the length of the result array
 */
int bff4_parse(char const *buffer, struct op **result)
{
	int a;
	int i;
	int cursor = 0;

	struct op *o = 0;
	int sz = 0;

	a = bff4_getbf2(buffer, &cursor);

	for (;; sz++) {
		o = zalloc(o, (sz + 1) * sizeof(struct op), sz * sizeof(struct op));
		if (a == -1 || a == '!') break;

		o[sz].c = a;
		if (strchr(",.", a)) {
			a = bff4_getbf2(buffer, &cursor); continue;
		}
		if (a == ']') {
			int l = 1, i = sz;
			while (l && i >= 0) if (i--) l += (o[i].c == ']') - (o[i].c == '[');
			if (i < 0) {
				printf("unbalanced ']'\n");
				return 1;
			}
			o[i].igo = sz;
			o[sz].igo = i;
		}
		a = bff4_consume3(buffer, &cursor, o + sz);
	}

	for (i = 0; i < sz; i++) {
		o[i].go = &o[o[i].igo];
#ifndef NOLNR
		if (o[i].c == '[' && o[i].igo == i + 1 && o[i].shift == 0 && o[i].off <= 0) {
			o[i].linear = -o[i].d[-o[i].off];
			if (o[i].linear < 0) {
				printf("Warning: infinite loop "); printop(&o[i]);
				printf("linear=%d\n", o[i].linear);
				o[i].linear = 0;
			}
		} else {
			o[i].linear = 0;
		}
#endif
	}

	*result = o;
	return sz;
}
