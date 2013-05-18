/**
 * @file section.c
 * @brief INI ファイルのセクション部分処理の実装。
 */

#include "key.h"
#include "section.h"
#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct Section {
	char *name;
	size_t nkeys;
	Key *keys;
};

char *parse_sectionname(const char *line)
{
	enum { BEFORE, OPEN, NAME, CLOSE, AFTER } state = BEFORE;
	char *sectionname = NULL;
	size_t len = 0, i;

	if (line == NULL) {
		return NULL;
	}

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
				len = 1;
			} else if (state == NAME) {
				len++;
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

	/* セクション名の取り出し */
	if ((sectionname = malloc(len + 1)) == NULL) {
		return NULL;
	}
	memcpy(sectionname, line + 1, len);
	sectionname[len] = '\0';
	return sectionname;
}

/* セクションオブジェクトの初期化 */
Section *section_new(char *name)
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
void section_delete(Section *section)
{
	free(section->name);
	free(section);
	/* TODO: free keys */
}
