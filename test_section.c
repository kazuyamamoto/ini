/**
 * @file test_section.c
 * @brief section.c のユニットテスト
 */

#include "PCUnit/PCUnit.h"
#include "section.h"
#include <stdlib.h>

static int initialize(void)
{
	return 0;
}

static int cleanup(void)
{
	return 0;
}

static int setup(void)
{
	return 0;
}

static int teardown(void)
{
	return 0;
}

void test_section_parse_null(void)
{
	PCU_ASSERT_PTR_NULL(section_parse(NULL));
}

void test_section_parse(void)
{
	Section *section = section_parse("[sectionname]");
	PCU_ASSERT_PTR_NOT_NULL(section);
	section_delete(section);
}

PCU_Suite *test_section_suite(void)
{
	static PCU_Test tests[] = {
		PCU_TEST(test_section_parse_null),
		PCU_TEST(test_section_parse),
	};
	static PCU_Suite suite = {
		"test_section", tests, sizeof tests / sizeof tests[0], setup, teardown, initialize, cleanup
	};
	return &suite;
}
