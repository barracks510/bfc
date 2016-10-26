#include <string.h>

#include "bff4.h"

#define zalloci(p, sz, osz) zalloc(p, (sz) * sizeof(int), (osz) * sizeof(int));
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

