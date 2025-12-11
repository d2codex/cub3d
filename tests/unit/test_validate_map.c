#include "cub3d.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Minimal init for t_map
 */
static	void init_test_map(t_map *map)
{
	memset(map, 0, sizeof(*map));
}

/**
 * @brief Test a valid enclosed map
 */
void	test_map_valid(void)
{
	int			result;
	t_map		map;

	init_test_map(&map);
	// writable rows
	char	row0[] = "11111";
	char	row1[] = "10001";
	char	row2[] = "10001";
	char	row3[] = "11111";
	char	*grid[] = {row0, row1, row2, row3};
	map.grid = grid;
	map.height = 4;
	map.width = 5;
	printf("%s\n", row0);
	printf("%s\n", row1);
	printf("%s\n", row2);
	printf("%s\n\n", row3);
	result = check_valid_map(&map);
	assert(result == EXIT_SUCCESS);
	printf("test_map_valid OK\n");
}

/**
 * @brief Test a map with a leak (open boundary)
 */
void	test_map_leak(void)
{
	int			result;
	t_map		map;

	init_test_map(&map);
	char row0[] = "11111";
	char row1[] = "10001";
	char row2[] = "10000";
	char row3[] = "11111";
	char *grid[] = {row0, row1, row2, row3};
	map.grid = grid;
	map.height = 4;
	map.width = 5;
	printf("%s\n", row0);
	printf("%s\n", row1);
	printf("%s\n", row2);
	printf("%s\n\n", row3);
	result = check_valid_map(&map);
	assert(result == EXIT_FAILURE);
	printf("test_map_leak OK\n");
}

/**
 * @brief Test a map with invalid characters
 */
void	test_map_invalid_chars(void)
{
	int			result;
	t_map		map;

	init_test_map(&map);
	char row0[] = "1111";
	char row1[] = "1A01"; // invalid char 'A'
	char row2[] = "1111";
	char *grid[] = {row0, row1, row2};
	map.grid = grid;
	map.height = 3;
	map.width = 4;
	printf("%s\n", row0);
	printf("%s\n", row1);
	printf("%s\n\n", row2);
	result = check_valid_map(&map);
	assert(result == EXIT_FAILURE);
	printf("test_map_invalid_chars OK\n");
}

int	main(void)
{
	printf("===== Testing player setup =====\n");
	test_map_valid();
	printf("================================\n");
	test_map_leak();
	printf("================================\n");
	test_map_invalid_chars();
	printf("================================\n");
	printf("ALL MAP VALIDATION TESTS PASSED\n");
	return (0);
}
