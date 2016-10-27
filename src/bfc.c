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

#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bff4.h"

extern int errno;

char *readall_stdin()
{
#define BUF_SIZE 1024
	char buffer[BUF_SIZE];
	size_t content_size = 1;
	/* Preallocate space.  We could just allocate one char here,
	 * but that wouldn't be efficient. */
	char *content = malloc(sizeof(char) * BUF_SIZE);
	if (content == NULL) {
		perror("Failed to allocate content");
		exit(1);
	}
	content[0] = '\0';
	while (fgets(buffer, BUF_SIZE, stdin)) {
		char *old = content;
		content_size += strlen(buffer);
		content = realloc(content, content_size);
		if (content == NULL) {
			perror("Failed to reallocate content");
			free(old);
			exit(2);
		}
		strcat(content, buffer);
	}

	if (ferror(stdin)) {
		free(content);
		perror("Error reading from stdin.");
		exit(3);
	}

	return content;
}

int main(int argc, char **argv)
{
	struct op *o = 0;
	int n;
	char *program;

	int fd;

	if (argc > 1) {
		char *filename = argv[1];
		int errnum;
#if DEBUG
		printf("Using file: %s\n", filename);
#endif
		fd = dup(fileno(stdin));
		freopen(filename, "r", stdin);
		if ((errnum = errno) != 0) {
			fprintf(stderr, "Error opening %s: %s\n", filename, strerror(errnum));
			return 1;
		}
	}

	program = readall_stdin();
	n = bff4_parse(program, &o);
#if DEBUG
	printf("parsed size: %d\n", n);
#endif

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

	bff4_run(o, n);

	return 0;
}
