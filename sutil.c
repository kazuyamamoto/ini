/**
 * @file sutil.c
 * @brief 文字列処理ユーティリティ実装。
 */

#include "sutil.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *sgetline(const char* s, const char** next)
{
	size_t n;
	char *line;

	if (s == NULL || next == NULL) {
		errno = EINVAL;
		return NULL;
	}

	for (n = 0; *s != '\n' && *s != '\0'; n++, s++)
		;

	if (n == 0 && *s == '\0') {
		*next = s;
		return NULL;
	}

	if ((line = malloc(n + 1)) == NULL) {
		return NULL;
	}
	memcpy(line, s - n, n);
	line[n] = '\0';

	if (*s == '\0') {
		*next = s;
	} else {
		*next = s + 1;
	}

	return line;
}
