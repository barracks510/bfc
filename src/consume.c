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

#include <string.h>

#include "bff4.h"

int consume(struct op *o)
{
	int mp = 0, i;
	int a = o->c;

	if (strchr("[]", a)) a = getbf();

	o->sz = 1;
	o->d = zalloci(0, 1, 0);
	o->off = 0;

	o->dbsz = 0;
	o->db = 0;

	for (;; a = getbf()) {
		if (a == -1 || a == '!') break;
		if (strchr(",.[]", a)) break;

		o->db = zalloci(o->db, o->dbsz + 1, o->dbsz);
		o->db[o->dbsz++] = a;

		if (a == '+') o->d[mp]++;
		if (a == '-') o->d[mp]--;
		if (a == '>') {
			mp++;
			if (mp >= o->sz) {
				o->d = zalloci(o->d, o->sz + 1, o->sz);
				o->sz++;
			}
		}
		if (a == '<') {
			if (mp > 0) {
				mp--;
			} else {
				o->off--;
				o->d = zalloci(o->d, o->sz + 1, o->sz);
				for (i = o->sz; i > 0; i--) o->d[i] = o->d[i - 1];
				o->d[0] = 0;
				o->sz++;
			}
		}
	}
	o->shift = mp + o->off;

	/* cut corners */
	while (o->sz && o->d[o->sz - 1] == 0) o->sz--;
	while (o->sz && o->d[0] == 0) {
		o->sz--;
		for (i = 0; i < o->sz; i++) o->d[i] = o->d[i + 1];
		o->off++;
	}

	return a;
}
