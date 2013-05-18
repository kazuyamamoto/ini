/**
 * @file test_key.c
 * @brief key.c のユニットテスト
 */

#include "PCUnit/PCUnit.h"
#include "key.h"
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

void test_key_parse(void)
{
	PCU_FAIL("TODO: implement!");
}

PCU_Suite *test_key_suite(void)
{
	static PCU_Test tests[] = {
		PCU_TEST(test_key_parse),
	};
	static PCU_Suite suite = {
		"test_key", tests, sizeof tests / sizeof tests[0], setup, teardown, initialize, cleanup
	};
	return &suite;
}
