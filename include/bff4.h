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
extern void *zalloc(void *p, size_t sz, size_t osz);
extern void *zalloci(void *p, size_t sz, size_t osz);
#endif
