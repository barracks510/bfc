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

#include <stdlib.h>
#include <string.h>

#include "bff4.h"

void *zalloc(void *p, size_t sz, size_t osz)
{
	p = realloc(p, sz);
	memset((char *)p + osz, 0, sz - osz);
	return p;
}

void *zalloci(void *p, size_t sz, size_t osz)
{
	return zalloc(p, sz * sizeof(int), osz * sizeof(int));
}
