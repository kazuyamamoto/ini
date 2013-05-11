/**
 * @file futil.c
 * @brief ファイルアクセスユーティリティ実装。
 */

#include "futil.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

char* freadall(FILE* file)
{
	long start, end;
	char* data;
	long readsize;

	if (file == NULL) {
		errno = EINVAL;
		return NULL;
	}

	if ((start = ftell(file)) == -1L) {
		return NULL;
	}

	if (fseek(file, 0L, SEEK_END) == EOF) {
		return NULL;
	}

	if ((end = ftell(file)) == -1L) {
		return NULL;
	}

	readsize = end - start;
	if (readsize == 0) {
		return NULL;
	}

	if (fseek(file, start, SEEK_SET) == EOF) {
		return NULL;
	}

	if ((data = malloc(readsize + 1)) == NULL) {
		return NULL;
	}

	if (fread(data, 1, readsize, file) != readsize) {
		const int errnosave = errno;
		free(data);
		errno = errnosave;
		return NULL;
	}

	data[readsize] = '\0';
	return data;
}

char* freadline(FILE* file)
{
	size_t num = 0;
	int c;
	char* line;

	if (file == NULL) {
		errno = EINVAL;
		return NULL;
	}

	while ((c = fgetc(file)) != '\n' && c != EOF) {
		num++;
	}
	if (ferror(file)) {
		return NULL;
	}
	if (c == EOF && num == 0) {
		return NULL;
	}

	if ((line = malloc(num + 1)) == NULL) {
		return NULL;
	}

	if (num) {
		if (fseek(file, -num - 1, SEEK_CUR) == EOF ||
			fread(line, 1, num + 1, file) != num + 1) {
			const int errnosave = errno;
			free(line);
			errno = errnosave;
			return NULL;
		}
	}

	line[num] = '\0';
	return line;
}
