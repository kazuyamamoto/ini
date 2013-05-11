/**
 * @file ini.c
 * @brief INIファイルアクセス実装。
 */

#include "ini.h"
#include "sutil.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <assert.h>

/* キー */
struct Key;
typedef struct Key Key;

/* セクション */
struct Section;
typedef struct Section Section;
static Section *section_new(char *name);
static void section_delete(Section *section);

/* INI */
struct Ini {
	size_t nsections;
	Section **sections;
};
static char *parse_sectionname(const char *line);
static Ini *ini_add_section(Ini *ini, Section *section);

Ini* ini_new(void)
{
	Ini* ini = malloc(sizeof *ini);
	if (ini == NULL) {
		return NULL;
	}

	ini->nsections = 0;
	ini->sections = NULL;
	return ini;
}

Ini *ini_parse(const char* data, size_t* errline)
{
	Ini *ini;
	char *line;
	char *sectionname;
	Section* section;
	const char *next;

	if (data == NULL || errline == NULL) {
		return NULL;
	}

	if ((ini = ini_new()) == NULL) {
		return NULL;
	}

	if ((line = sgetline(data, &next)) == NULL) {
		return ini;
	}

	/* 最初はセクションが来る */
	if ((sectionname = parse_sectionname(line)) == NULL) {
		free(line);
		goto ERROR;
	}
	free(line);

	if ((section = section_new(sectionname)) == NULL) {
	   goto ERROR;
	}
	ini_add_section(ini, section);

	return ini;

ERROR:
	ini_delete(ini);
	return NULL;
}

void ini_delete(Ini *ini)
{
	int i;
	for (i = 0; i < ini->nsections; i++) {
		section_delete(ini->sections[i]);
	}
	free(ini);
}

char *ini_get(const Ini *ini, const char *section, const char *name)
{
	if (ini == NULL || section == NULL || name == NULL) {
		errno = EINVAL;
		return NULL;
	}

	/* TODO: implement */

	return NULL;
}

/* セクション名を解釈して取得する。
 * 例えば "[abc]" を解釈して "abc" を取得する。 */
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

/* Ini オブエジェクトにセクションオブジェクトを追加する */
static Ini* ini_add_section(Ini *ini, Section *section)
{
	if (ini->nsections) {
		Section **tmp;
		if ((tmp = realloc(ini->sections, sizeof(Section*) * (ini->nsections + 1))) == NULL) {
			return NULL;
		} else {
			ini->sections[ini->nsections] = section;
			ini->nsections++;
			return ini;
		}
	} else {
		if ((ini->sections = malloc(sizeof section)) == NULL) {
			return NULL;
		} else {
			ini->nsections = 1;
			ini->sections[0] = section;
			return ini;
		}
	}
}

/* セクション */
struct Section {
	char *name;
	size_t nkeys;
	Key *keys;
};

/* セクションオブジェクトの初期化 */
static Section* section_new(char *name)
{
	Section *section = malloc(sizeof *section);
	if (section == NULL) {
		return NULL;
	}

	section->name = name;
	section->nkeys = 0;
	section->keys = NULL;
	return section;
}

/* セクションオブジェクトの解放 */
static void section_delete(Section *section)
{
	free(section->name);
	free(section);
	/* TODO: free keys */
}
