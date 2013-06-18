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

/* Ini オブジェクトにセクションオブジェクトを追加する */
static int add_section(Ini *ini, Section *section)
{
	Section **tmp;

	assert(ini != NULL);
	assert(section != NULL);

	if ((tmp = realloc(ini->sections, sizeof(Section*) * (ini->nsections + 1))) == NULL) {
		return -1;
	}

	ini->sections = tmp;
	ini->sections[ini->nsections] = section;
	ini->nsections++;

	return 0;
}

static Section *search_section(const Ini *ini, const char* section_name)
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
	if (ini == NULL) {
		return NULL;
	}

	ini->nsections = 0;
	ini->sections = NULL;
	ini->current = NULL;

	return ini;
}

/* 最初のセクションの解釈 */
static void parse_first_section(Ini *ini, const char **data)
{
	char *line = sgetline(data);
	ini->current = section_parse(line);
	free(line);

	if (ini->current == NULL)
		return;

	if (add_section(ini, ini->current)) {
		section_delete(ini->current);
	}
}

static void parse_sections_and_keys(Ini *ini, const char *data)
{
	Key *key;
	char *line;

	while ((line = sgetline(&data)) != NULL) {

		if ((key = key_parse(line)) != NULL) {
			free(line);
			if (section_add_key(ini->current, key)) {
				key_delete(key);
				return;
			}
			continue;
		}

		if ((ini->current = section_parse(line)) != NULL) {
			free(line);
			if (add_section(ini, ini->current)) {
				section_delete(ini->current);
				return;
			}
			continue;
		}

		free(line);
	}
}

Ini *ini_parse(const char *d)
{
	Ini *ini;
	const char *data = d;

	if (data == NULL)
		return NULL;

	if ((ini = ini_new()) == NULL)
		return NULL;

	parse_first_section(ini, &data);
	parse_sections_and_keys(ini, data);

	return ini;
}

void ini_delete(Ini *ini)
{
	size_t i;

	if (ini == NULL) {
		return;
	}

	for (i = 0; i < ini->nsections; i++) {
		section_delete(ini->sections[i]);
	}
	free(ini);
}

const char *ini_get(const Ini *ini, const char *section_name, const char *key_name)
{
	Section *section;
	Key *key;

	if (ini == NULL || section_name == NULL || key_name == NULL) {
		errno = EINVAL;
		return NULL;
	}

	if ((section = search_section(ini, section_name)) == NULL) {
		return NULL;
	}

	if ((key = section_search_key(section, key_name)) == NULL) {
		return NULL;
	}

	return key_get_value(key);
}
