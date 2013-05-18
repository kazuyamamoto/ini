#include "PCUnit/PCUnit.h"
#include <stdio.h>

PCU_Suite *test_ini_suite(void);
PCU_Suite *test_key_suite(void);
PCU_Suite *test_section_suite(void);
PCU_Suite *test_sutil_suite(void);

int main(int argc, char *argv[])
{
	const PCU_SuiteMethod suites[] = {
		test_ini_suite,
		test_key_suite,
		test_section_suite,
		test_sutil_suite,
	};
	PCU_set_putchar(putchar);
	PCU_set_getchar(getchar);
	PCU_enable_color();
	if (argc >= 2) {
		PCU_set_verbose(1);
	}
	return PCU_run(suites, sizeof suites / sizeof suites[0]);
}

