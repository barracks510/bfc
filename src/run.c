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

#include "bff4.h"

int bff4_run(struct op *o, const int n)
{
	struct op *z, *zend;
	int *m, mp, mn;
	int i;

	mn = 1000; /* any number */
	m = zalloci(0, mn, 0);
	mp = 0;

	z = o;
	zend = o + n;
	for (; z != zend; ++z) {
#ifdef DEBUG
		printop(z);
#endif

		if (z->c == ']') {
			if (m[mp]) z = z->go;
		} else if (z->c == '[') {
			if (!m[mp]) z = z->go;
		} else if (z->c == ',') {
			m[mp] = getchar(); continue;
		} else if (z->c == '.') {
			putchar(m[mp]); continue;
		}

		/* apply */
		if (z->sz) {
			int nmn = mp + z->sz + z->off;
			if (nmn > mn) {
				m = zalloci(m, nmn, mn);
				mn = nmn;
			}


#ifndef NOLNR
			if (z->linear) {
				int del = m[mp] / z->linear;
				for (i = 0; i < z->sz; i++) m[mp + z->off + i] += del * z->d[i];
			} else
#endif
			for (i = 0; i < z->sz; i++) m[mp + z->off + i] += z->d[i];
		}

		if (z->shift > 0) {
			int nmn = mp + z->shift + 1;
			if (nmn > mn) {
				m = zalloci(m, nmn, mn);
				mn = nmn;
			}
		}
		mp += z->shift;

#ifdef DEBUG
		for (i = 0; i < mn; i++) {
			if (i == mp) printf("'");
			printf("%d ", m[i]);
		}
		printf("\n");
#endif
	}
	return 0;
}
