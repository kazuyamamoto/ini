/**
 * @file ini.c
 * @brief INIファイルアクセス実装。
 */

#include "ini.h"
#include "futil.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <assert.h>

/* キー */
typedef struct {
	char* name;
	char* value;
} Key;

/* セクション */
typedef struct {
	char* name;
	size_t numkeys;
	Key *keys;
} Section;

/* INI 全体 */
struct Ini {
	size_t numsections;
	Section* sections;
};

Ini* ini_new()
{
	Ini* ini = malloc(sizeof *ini);
	if (ini == NULL) {
		return NULL;
	}

	ini->numsections = 0;
	ini->sections = NULL;
	return ini;
}

Ini* ini_read(FILE* file)
{
	Ini* ini = ini_new();
	char* line;

	if (ini == NULL) {
		return NULL;
	}

	while ((line = freadline(file)) != NULL) {
		free(line);
	}
	if (ferror(file)) {
		free(line);
		return NULL;
	}

	return ini;
}

void ini_delete(Ini* ini)
{
	free(ini);
}

char* ini_get(const Ini* ini, const char* section, const char* name)
{
	if (ini == NULL || section == NULL || name == NULL) {
		errno = EINVAL;
		return NULL;
	}

	return NULL;
}

char* parse_section(const char* line)
{
	enum { BEFORE, OPEN, NAME, CLOSE, AFTER } state = BEFORE;
	char* section = NULL;
	size_t num = 0;
	int i;

	assert(line);

	for (i = 0; i < strlen(line); i++) {
		if (line[i] == '[') {
			if (state == BEFORE) {
				state = OPEN;
			} else {
				return NULL;
			}
		} else if (isalnum((int)line[i])) {
			if (state == OPEN) {
				state = NAME;
				num = 1;
			} else if (state == NAME) {
				num++;
			} else {
				return NULL;
			}
		} else if (line[i] == ']') {
			if (state == NAME) {
				state = AFTER;
			} else {
				return NULL;
			}
		} else {
			return NULL;
		}
	}

	if ((section = malloc(num + 1)) == NULL) {
		return NULL;
	}
	memcpy(section, line + 1, num);
	section[num] = '\0';
	return section;
}
