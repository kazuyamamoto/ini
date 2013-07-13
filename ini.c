/**
 * @file ini.c
 * @brief INIファイルアクセス実装。
 */

#include "ini.h"
#include "sutil.h"
#include "cutil.h"
#include "section.h"
#include "key.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

/* INI オブジェクト */
struct Ini {
	size_t nsections;
	Section **sections;
	Section *current;
};

static int ini_add_section(Ini *ini, Section *section);
static Section *ini_search_section(const Ini *ini, const char* section_name);
static Ini *ini_new(void);
static void ini_parse_first_section(Ini *ini, const char **data);
static void ini_parse_sections_and_keys(Ini *ini, const char *data);

Ini *ini_parse(const char *d)
{
	Ini *ini;
	const char *data = d;

	if (data == NULL)
		return NULL;

	if ((ini = ini_new()) == NULL)
		return NULL;

	ini_parse_first_section(ini, &data);
	ini_parse_sections_and_keys(ini, data);

	return ini;
}

void ini_delete(Ini *ini)
{
	size_t i;

	if (ini == NULL)
		return;

	for (i = 0; i < ini->nsections; i++)
		section_delete(ini->sections[i]);

	free(ini);
}

const char *ini_get(const Ini *ini, const char *section_name, const char *key_name)
{
	Section *section;
	Key *key;

	if (ini == NULL || section_name == NULL || key_name == NULL)
		return NULL;

	if ((section = ini_search_section(ini, section_name)) == NULL)
		return NULL;

	if ((key = section_search_key(section, key_name)) == NULL)
		return NULL;

	return key_get_value(key);
}

/* Ini オブジェクトにセクションオブジェクトを追加する */
static int ini_add_section(Ini *ini, Section *section)
{
	Section **tmp;

	assert(ini != NULL);
	assert(section != NULL);

	if ((tmp = realloc(ini->sections, sizeof(Section*) * (ini->nsections + 1))) == NULL)
		return -1;

	ini->sections = tmp;
	ini->sections[ini->nsections] = section;
	ini->nsections++;

	return 0;
}

static Section *ini_search_section(const Ini *ini, const char* section_name)
{
	size_t i;

	assert(ini != NULL);
	assert(section_name != NULL);

	for (i = 0; i < ini->nsections; i++) {
		if (strcmp(section_get_name(ini->sections[i]), section_name) == 0) {
			return ini->sections[i];
		}
	}

	return NULL;
}

static Ini *ini_new(void)
{
	Ini *ini = malloc(sizeof *ini);
	if (ini == NULL)
		return NULL;

	ini->nsections = 0;
	ini->sections = NULL;
	ini->current = NULL;

	return ini;
}

/* 空行かコメント行であることを調べる。
 * 空行＝空文字列 or スペースとタブのみ。
 * コメント行＝スペースとタブに続いて;、;に続いて任意の文字 */
static int isingnorableline(const char *line)
{
	int i;

	assert(line != NULL);

	for (i = 0; i < strlen(line); i++) {
		if (!isspacetab(line[i])) {
			if (line[i] == ';') {
				return 1; /* コメント行 */
			} else {
				return 0;
			}
		}
	}

	return 1; /* 空行 */
}

/* 最初のセクションの解釈 */
static void ini_parse_first_section(Ini *ini, const char **data)
{
	char *line;

	/* 空行をとばす */
	while (1) {
		line = sgetline(data);
		if (line == NULL)
			return;
		if (!isingnorableline(line))
			break;
		free(line);
	}

	ini->current = section_parse(line);
	free(line);
	if (ini->current == NULL)
		return;

	if (ini_add_section(ini, ini->current))
		section_delete(ini->current);
}

static void ini_parse_sections_and_keys(Ini *ini, const char *data)
{
	Key *key;
	Section *section;
	char *line;

	while ((line = sgetline(&data)) != NULL) {

		/* キーとして解釈 */
		if ((key = key_parse(line)) != NULL) {
			free(line);
			if (section_add_key(ini->current, key)) {
				key_delete(key);
				return;
			}
			continue;
		}

		/* セクションとして解釈 */
		if ((section = section_parse(line)) != NULL) {
			ini->current = section;
			free(line);
			if (ini_add_section(ini, ini->current)) {
				section_delete(ini->current);
				return;
			}
			continue;
		}

		free(line);
	}
}
