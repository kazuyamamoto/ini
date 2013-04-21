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
	char *name;
	char *value;
} Key;

/* セクション */
typedef struct {
	char *name;
	size_t numkeys;
	Key *keys;
} Section;

/* INI 全体 */
struct Ini {
	size_t numsections;
	Section *sections;
};

static char *parse_sectionname(const char *line);
static Section* section_new(void);

Ini* ini_new(void)
{
	Ini* ini = malloc(sizeof *ini);
	if (ini == NULL) {
		return NULL;
	}

	ini->numsections = 0;
	ini->sections = NULL;
	return ini;
}

/* TODO エラー通知 */
Ini *ini_read(FILE *file)
{
	Ini *ini;
	char *line;
	char *sectionname;
	Section* section;

	if ((ini = ini_new()) == NULL) {
		return NULL;
	}

	/* 最初はセクションが来る */
	if ((line = freadline(file)) == NULL) {
		goto ERROR;
	}
	if ((sectionname = parse_sectionname(line)) == NULL) {
		free(line);
		goto ERROR;
	}
	free(line);
	if ((section = section_new()) == NULL) {
		goto ERROR;
	}
	section->name = sectionname;
	ini->numsections = 1;
	ini->sections = section;

	return ini;

ERROR:
	ini_delete(ini);
	return NULL;
}

void ini_delete(Ini *ini)
{
	free(ini);
}

char *ini_get(const Ini *ini, const char *section, const char *name)
{
	if (ini == NULL || section == NULL || name == NULL) {
		errno = EINVAL;
		return NULL;
	}

	return NULL;
}

static char *parse_sectionname(const char *line)
{
	enum { BEFORE, OPEN, NAME, CLOSE, AFTER } state = BEFORE;
	char *sectionname = NULL;
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

	if ((sectionname = malloc(num + 1)) == NULL) {
		return NULL;
	}
	memcpy(sectionname, line + 1, num);
	sectionname[num] = '\0';
	return sectionname;
}

static Section* section_new(void)
{
	Section *section = malloc(sizeof *section);
	if (section == NULL) {
		return NULL;
	}

	section->name = NULL;
	section->numkeys = 0;
	section->keys = NULL;

	return section;
}
