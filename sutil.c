/**
 * @file sutil.c
 * @brief 文字列処理ユーティリティ実装。
 */

#include "sutil.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *sgetline(const char **s)
{
	size_t n;
	char *line;

	/* パラメータチェック */
	if (s == NULL || *s == NULL) {
		errno = EINVAL;
		return NULL;
	}

	/* 1行の終わりか、文字列終端までの文字数を数える */
	n = 0;
	for ( ; **s != '\n' && **s != '\r' && **s != '\0'; (*s)++)
		n++;

	/* 文字列の終端で1行を読み取ろうとしていた */
	if (n == 0 && **s == '\0')
		return NULL;

	/* 1行文の文字列のクローンを生成する */
	if ((line = malloc(n + 1)) == NULL) {
		*s -= n;
		return NULL;
	}
	memcpy(line, *s - n, n);
	line[n] = '\0';

	if (**s == '\r' && *(*s + 1) == '\n')
		*s = *s + 2; /* CRLFの場合の次の行開始位置 */
	else if (**s != '\0')
		*s = *s + 1;

	return line;
}

char *sclone(const char *s)
{
	size_t len;
	char *clone;

	if (s == NULL) {
		errno = EINVAL;
		return NULL;
	}

	len = strlen(s);
	if ((clone = malloc(len + 1)) == NULL)
		return NULL;

	strcpy(clone, s);
	return clone;
}

char *snclone(const char *s, size_t len)
{
	char *clone;

	if (s == NULL) {
		errno = EINVAL;
		return NULL;
	}

	if ((clone = malloc(len + 1)) == NULL)
		return NULL;

	memcpy(clone, s, len);
	clone[len] = '\0';

	return clone;
}
