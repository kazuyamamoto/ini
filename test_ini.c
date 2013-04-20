#include "PCUnit/PCUnit.h"
#include "ini.h"
#include <stdio.h>

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
	FILE *file;
	const char* value;

	file = fopen("sample1.ini", "r");
	PCU_ASSERT_PTR_NOT_NULL(file);

	ini = ini_read(file);
	fclose(file);
	PCU_ASSERT_PTR_NOT_NULL(ini);

	value = ini_get(ini, "abc", "def");
	PCU_ASSERT_STRING_EQUAL(value, "ghi");

	ini_delete(ini);
}


PCU_Suite *test_ini_suite(void)
{
	static PCU_Test tests[] = {
		PCU_TEST(test_ini_get),
	};
	static PCU_Suite suite = {
		"ini_test", tests, sizeof tests / sizeof tests[0], setup, teardown, initialize, cleanup
	};
	return &suite;
}

