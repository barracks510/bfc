#ifndef BFF4_H
#define BFF4_H
struct op {
	int		shift, off;
	int *		d, sz;
	struct op *	go;
	int		c;
	int		igo, linear;
	int *		db, dbsz;
};


extern int consume(struct op *o);
extern int getbf();
extern void printop(struct op *z);
extern void *zalloc(void *p, int sz, int osz);
#endif
