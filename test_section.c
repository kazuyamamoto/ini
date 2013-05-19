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

void test_parse_section_name_null(void)
{
	PCU_ASSERT_PTR_NULL(parse_section_name(NULL));
}

void test_parse_section_name(void)
{
	char *name = parse_section_name("[sectionname]");
	PCU_ASSERT_STRING_EQUAL("sectionname", name);
	free(name);
}

PCU_Suite *test_section_suite(void)
{
	static PCU_Test tests[] = {
		PCU_TEST(test_parse_section_name_null),
		PCU_TEST(test_parse_section_name),
	};
	static PCU_Suite suite = {
		"test_section", tests, sizeof tests / sizeof tests[0], setup, teardown, initialize, cleanup
	};
	return &suite;
}
