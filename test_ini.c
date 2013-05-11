#include "PCUnit/PCUnit.h"
#include "ini.h"
#include <stddef.h>

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


static void test_ini_get(void)
{
	Ini* ini;
	const char* value;
	size_t errline;

	ini = ini_parse("[Section]\nKey=Value", &errline);
	PCU_ASSERT_PTR_NOT_NULL(ini);

	value = ini_get(ini, "Section", "Key");
	PCU_ASSERT_STRING_EQUAL("Value", value);

	ini_delete(ini);
}


PCU_Suite *test_ini_suite(void)
{
	static PCU_Test tests[] = {
		PCU_TEST(test_ini_get),
	};
	static PCU_Suite suite = {
		"test_ini", tests, sizeof tests / sizeof tests[0], setup, teardown, initialize, cleanup
	};
	return &suite;
}

