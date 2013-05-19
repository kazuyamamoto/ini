/**
 * @file section.c
 * @brief INI ファイルのセクション部分処理の実装。
 */

#include "key.h"
#include "section.h"
#include "sutil.h"
#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct Section {
	char *name;
	size_t nkeys;
	Key **keys;
};

static Section *section_new(void)
{
	Section *section;

	if ((section = malloc(sizeof *section)) == NULL) {
		return NULL;
	}

	section->name = NULL;
	section->nkeys = 0;
	section->keys = NULL;

	return section;
}

Section *section_parse(const char *s)
{
	enum { BEFORE, OPEN, NAME, CLOSE, AFTER } state = BEFORE;
	char *section_name = NULL;
	size_t len = 0, i;
	Section *section;

	if (s == NULL) {
		return NULL;
	}

	/* セクション名の長さを調べる */
	for (i = 0; i < strlen(s); i++) {
		if (s[i] == '[') {
			if (state == BEFORE) {
				state = OPEN;
			} else {
				return NULL;
			}
		} else if (isalnum((int)s[i])) {
			if (state == OPEN) {
				state = NAME;
				len = 1;
			} else if (state == NAME) {
				len++;
			} else {
				return NULL;
			}
		} else if (s[i] == ']') {
			if (state == NAME) {
				state = AFTER;
			} else {
				return NULL;
			}
		} else {
			return NULL;
		}
	}

	/* セクション名の取り出し */
	if ((section_name = malloc(len + 1)) == NULL) {
		return NULL;
	}
	memcpy(section_name, s + 1, len);
	section_name[len] = '\0';

	/* セクションオブジェクトの生成 */
	if ((section = section_new()) == NULL) {
		free(section_name);
		return NULL;
	}
	section->name = section_name;

	return section;
}

void section_delete(Section *section)
{
	size_t i;

	free(section->name);
	for (i = 0; i < section->nkeys; i++) {
		key_delete(section->keys[i]);
	}
	free(section->keys);
	free(section);
}

const char *section_name(const Section *section)
{
	return section->name;
}
