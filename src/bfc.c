/*
 * Optimizing brainfuck implementation of dialect based on
 * Daniel's dbfi (see "A very short self-interpreter")
 *
 * This interpreter has only one input: program and input to the
 * program have to be separated with ! e.g. ",.!a" prints 'a'
 * To use it in interactive mode paste your program as input.
 *
 * This program can be compiled with NOLNR macro defined.
 * NOLNR disables optimization of linear loops (where '<>' balanced), e.g. [->+>++<<].
 * Linear loop is then executed in one step.
 *
 * Oleg Mazonka 4 Dec 2006  http://mazonka.com/
 *
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>

#include <errno.h>
#include <unistd.h>

#include "bff4.h"

extern int errno;

#define zalloci(p, sz, osz) zalloc(p, (sz) * sizeof(int), (osz) * sizeof(int));
int main(int argc, char **argv)
{
	struct op *o = 0, *z, *zend;
	int sz = 0, i, *m, mp, msz;
	int a;

	int fd;

	if (argc > 1) {
		char *filename = argv[1];
		int errnum;
#if DEBUG
		printf("Using file: %s\n", filename);
#endif
		fd = dup(fileno(stdin));
		freopen(filename, "r", stdin);
		if ((errnum = errno) != 0)
			fprintf(stderr, "Error opening %s: %s\n", filename, strerror(errnum));
	}

	a = getbf();

	for (;; sz++) {
		o = zalloc(o, (sz + 1) * sizeof(struct op), sz * sizeof(struct op));
		if (a == -1 || a == '!') break;

		o[sz].c = a;
		if (strchr(",.", a)) {
			a = getbf(); continue;
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
		a = consume(o + sz);
	}

	if (argc > 1) {
		int errnum;
		dup2(fd, fileno(stdin));
		close(fd);
		clearerr(stdin);
		if ((errnum = errno) != 0) {
			fprintf(stderr, "Error re-joining stdin: %s\n", strerror(errnum));
			return 2;
		}
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

	msz = 1000; /* any number */
	m = zalloci(0, msz, 0);
	mp = 0;

	z = o;
	zend = o + sz;
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
			int nmsz = mp + z->sz + z->off;
			if (nmsz > msz) {
				m = zalloci(m, nmsz, msz);
				msz = nmsz;
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
			int nmsz = mp + z->shift + 1;
			if (nmsz > msz) {
				m = zalloci(m, nmsz, msz);
				msz = nmsz;
			}
		}
		mp += z->shift;

#ifdef DEBUG
		for (i = 0; i < msz; i++) {
			if (i == mp) printf("'");
			printf("%d ", m[i]);
		}
		printf("\n");
#endif
	}
	return 0;
}
