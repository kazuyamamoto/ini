#include "PCUnit/PCUnit.h"
#include "ini.h"

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


static void test_TODO(void)
{
	Ini* ini = ini_new();

	ini_delete(ini);
}


PCU_Suite *test_ini_suite(void)
{
	static PCU_Test tests[] = {
		PCU_TEST(test_TODO),
	};
	static PCU_Suite suite = {
		"ini_test", tests, sizeof tests / sizeof tests[0], setup, teardown, initialize, cleanup
	};
	return &suite;
}

