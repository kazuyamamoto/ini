/**
 * @file sutil.c
 * @brief 文字列処理ユーティリティ実装。
 */

#include "sutil.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *sgetline(const char *s, const char **next)
{
	size_t n;
	char *line;

	if (s == NULL || next == NULL) {
		errno = EINVAL;
		return NULL;
	}

	/* 1行の終わりまでの文字数を数える */
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

char *strclone(const char *s)
{
	size_t len;
	char *clone;

	if (s == NULL) {
		errno = EINVAL;
		return NULL;
	}

	len = strlen(s);
	if ((clone = malloc(len + 1)) == NULL) {
		return NULL;
	}

	strcpy(clone, s);
	return clone;
}

char *strnclone(const char *s, size_t len)
{
	char *clone;

	if (s == NULL) {
		errno = EINVAL;
		return NULL;
	}

	if ((clone = malloc(len + 1)) == NULL) {
		return NULL;
	}

	memcpy(clone, s, len);
	clone[len] = '\0';

	return clone;
}
