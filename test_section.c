/**
 * @file test_section.c
 * @brief section.c のユニットテスト
 */

#include "PCUnit/PCUnit.h"
#include "section.h"
#include "key.h"
#include <stdlib.h>

void test_section_parse_null(void)
{
	PCU_ASSERT_PTR_NULL(section_parse(NULL));
}

void test_section_parse(void)
{
	Section *section = section_parse("[sectionname]");
	PCU_ASSERT_PTR_NOT_NULL(section);
	PCU_ASSERT_STRING_EQUAL("sectionname", section_get_name(section));

	section_delete(section);
}

void test_section_search_key(void)
{
	Section *section = section_parse("[hoge]");
	Key* key = key_parse("fuga=piyo");
	Key* key_get;

	PCU_ASSERT_EQUAL(0, section_add_key(section, key));
	key_get = section_search_key(section, "fuga");
	PCU_ASSERT_PTR_NOT_NULL(key_get);
	PCU_ASSERT_STRING_EQUAL("fuga", key_get_name(key_get));
	PCU_ASSERT_STRING_EQUAL("piyo", key_get_value(key_get));

	section_delete(section);
}

PCU_Suite *test_section_suite(void)
{
	static PCU_Test tests[] = {
		PCU_TEST(test_section_parse_null),
		PCU_TEST(test_section_parse),
		PCU_TEST(test_section_search_key),
	};
	static PCU_Suite suite = {
		"test_section", tests, sizeof tests / sizeof tests[0]
	};
	return &suite;
}
