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
extern int bff4_consume3(char const *buffer, int *cursor, struct op *o);
extern int getbf();
extern int bff4_getbf2(char const *buffer, int *cursor);
extern int bff4_parse(char const *buffer, struct op **result);
extern int bff4_run(struct op *o, const int n);
extern void printop(struct op *z);
extern void *zalloc(void *p, int sz, int osz);
#endif
