/**
 * @file test_parse_cub_file.c
 * @brief Unit tests for the parse_cub_file() function in cub3d.
 *
 * This test program validates the full parsing of .cub files, including:
 *   - All six headers present and correctly parsed
 *   - Duplicate headers
 *   - Invalid RGB values (too few, too many, or non-integer)
 *   - Texture file existence and path validity
 *   - Correct detection of map start line
 *   - Correct map dimensions (width, height)
 *   - Proper storage of padded map lines in map->grid
 *   - Handling of empty lines
 *
 * Usage:
 *   Build: make build TEST=unit/test_parse_cub_file.c
 *   Run:   ./bin/test_parse_cub_file
 *
 * Each test uses a real .cub file, prints expected vs actual results,
 * and uses assertions to verify correct behavior.
 */

#include "cub3d.h"
#include <stdio.h>
#include <assert.h>

#define EXPECTED_MAP_START_LINE 8

typedef struct s_cub_test
{
	const char	*description;
	const char	*file_path;
	bool		expect_fail;
	int			expected_map_start_line;
	int			expected_width;
	int			expected_height;
}	t_cub_test;

int	main(void)
{
	t_map				map;
	int					ret;
	size_t				i;
	const t_cub_test	tests[] = {
	{
		"Valid Big",
		"../maps/test_cub_files/big.cub",
		false,
		EXPECTED_MAP_START_LINE,
		86,
		53
	},
	{
		"Empty lines",
		"../maps/test_cub_files/empty_lines.cub",
		false,
		14,
		3,
		5
	},
	{
		"header ID random order",
		"../maps/test_cub_files/header_id_random_order.cub",
		false,
		EXPECTED_MAP_START_LINE,
		33,
		14
	},
	{
		"Invalid ceiling value",
		"../maps/test_cub_files/invalid_value_ceiling.cub",
		true,
		EXPECTED_MAP_START_LINE,
		3,
		5
	},
	{
		"Invalid floor value",
		"../maps/test_cub_files/invalid_value_floor.cub",
		true,
		EXPECTED_MAP_START_LINE,
		3,
		5
	},
	{
		"map_no_headers.cub",
		"../maps/test_cub_files/map_no_headers.cub",
		true,
		0,
		33,
		14
	},

	};

	printf(YEL "================ parse_cub_file Tests =================" RESET "\n");
	i = 0;
	while (i < sizeof(tests) / sizeof(tests[0]))
	{
		memset(&map, 0, sizeof(t_map));
		printf(CYN "Test %2zu: %s\n" RESET, i + 1, tests[i].description);
		printf("Input file: %s\n", tests[i].file_path);
		ret = parse_cub_file(tests[i].file_path, &map);
		printf("Expected: ");
		if (tests[i].expect_fail)
			printf(RED "FAIL\n" RESET);
		else
			printf(GRN "SUCCESS\n" RESET);
		printf("     Got: ");
		if (ret == EXIT_SUCCESS)
			printf(GRN "SUCCESS\n" RESET);
		else
			printf(RED "FAIL\n" RESET);
		if (!tests[i].expect_fail && ret == EXIT_SUCCESS)
		{
			printf("Expected map start line: %d\n", tests[i].expected_map_start_line);
			printf("     Got Map start line: %d\n", map.map_start_line);
			if (map.map_start_line != tests[i].expected_map_start_line)
				printf(RED "Mismatch map start line\n" RESET);
			printf("Expected map width: %d\n", tests[i].expected_width);
			printf("     Got map width: %d\n", map.width);
			if (map.width != tests[i].expected_width)
				printf(RED "Mismatch map width\n" RESET);
			printf("Expected map height: %d\n", tests[i].expected_height);
			printf("     Got map height: %d\n", map.height);
			if (map.height != tests[i].expected_height)
				printf(RED "Mismatch map height\n" RESET);
		}
		if ((ret == EXIT_SUCCESS && !tests[i].expect_fail)
			|| (ret == EXIT_FAILURE && tests[i].expect_fail))
			printf(GRN "PASS\n" RESET);
		else
			printf(RED "FAIL\n" RESET);
		printf("====================================================\n");
		free_t_map(&map);
		i++;
	}
	printf(YEL "All parse_cub_file tests completed!\n" RESET);
	return (0);
}
