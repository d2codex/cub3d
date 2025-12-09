#include "cub3d.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Minimal init for t_game to avoid touching MLX
 */
static void	init_test_game(t_game *g)
{
	memset(g, 0, sizeof(*g));
}

/**
 * @brief Single player on map, facing North
 */
void	test_single_player_north(void)
{
	int		result;
	t_game	g;

	init_test_game(&g);
    // Make writable copies of the rows
	char row0[] = "1111";
	char row1[] = "1N01";
	char row2[] = "1111";
	char *grid[] = {row0, row1, row2};

	g.map.grid = grid;
	g.map.height = 3;
	g.map.width = 4;
	result = init_player(&g);
	assert(result == EXIT_SUCCESS);
	assert(g.player.pos_x == 1.5);
	assert(g.player.pos_y == 1.5);
	assert(g.player.dir_x == 0.0);
	assert(g.player.dir_y == -1.0);
	assert(g.player.plane_x == 0.66);
	assert(g.player.plane_y == 0.0);
	printf("test_single_player_north OK\n");
}

void	test_single_player_south(void)
{
	int		result;
	t_game	g;

	init_test_game(&g);
	char row0[] = "1111";
	char row1[] = "1S01";
	char row2[] = "1111";
	char *grid[] = {row0, row1, row2};
	g.map.grid = grid;
	g.map.height = 3;
	g.map.width = 4;
	result = init_player(&g);
	assert(result == EXIT_SUCCESS);
	assert(g.player.pos_x == 1.5);
	assert(g.player.pos_y == 1.5);
	assert(g.player.dir_x == 0.0);
	assert(g.player.dir_y == 1.0);
	assert(g.player.plane_x == -0.66);
	assert(g.player.plane_y == 0.0);
	printf("test_single_player_south OK\n");
}

void	test_single_player_east(void)
{
	int		result;
	t_game	g;

	init_test_game(&g);
	char row0[] = "1111";
	char row1[] = "1E01";
	char row2[] = "1111";
	char *grid[] = {row0, row1, row2};
	g.map.grid = grid;
	g.map.height = 3;
	g.map.width = 4;
	result = init_player(&g);
	assert(result == EXIT_SUCCESS);
	assert(g.player.pos_x == 1.5);
	assert(g.player.pos_y == 1.5);
	assert(g.player.dir_x == 1.0);
	assert(g.player.dir_y == 0.0);
	assert(g.player.plane_x == 0.0);
	assert(g.player.plane_y == 0.66);
	printf("test_single_player_east OK\n");
}

void	test_single_player_west(void)
{
	int		result;
	t_game	g;

	init_test_game(&g);
	char row0[] = "1111";
	char row1[] = "1W01";
	char row2[] = "1111";
	char *grid[] = {row0, row1, row2};
	g.map.grid = grid;
	g.map.height = 3;
	g.map.width = 4;
	result = init_player(&g);
	assert(result == EXIT_SUCCESS);
	assert(g.player.pos_x == 1.5);
	assert(g.player.pos_y == 1.5);
	assert(g.player.dir_x == -1.0);
	assert(g.player.dir_y == 0.0);
	assert(g.player.plane_x == 0.0);
	assert(g.player.plane_y == -0.66);
	printf("test_single_player_west OK\n");
}

/**
 * @brief Two players on the map → should fail
 */
void	test_multiple_players_error(void)
{
	int		result;
	t_game	g;

	init_test_game(&g);
	char row0[] = "1111";
	char row1[] = "1N01";
	char row2[] = "1S01";
	char row3[] = "1111";
	char *grid[] = { row0, row1, row2, row3 };
	g.map.grid = grid;
	g.map.height = 4;
	g.map.width = 4;
	result = init_player(&g);
	assert(result == EXIT_FAILURE);
	printf("test_multiple_players_error OK\n");
}

/**
 * @brief No player on the map → should fail
 */
void	test_no_player_error(void)
{
	int		result;
	t_game	g;

	init_test_game(&g);
	char row0[] = "1111";
	char row1[] = "1001";
	char row2[] = "1001";
	char row3[] = "1111";
	char *grid[] = { row0, row1, row2, row3 };
	g.map.grid = grid;
	g.map.height = 4;
	g.map.width = 4;
	result = init_player(&g);
	assert(result == EXIT_FAILURE);
	printf("test_no_player_error OK\n");
}

int	main(void)
{
	printf("===== Testing player setup =====\n");
	test_single_player_north();
	printf("================================\n");
	test_single_player_south();
	printf("================================\n");
	test_single_player_east();
	printf("================================\n");
	test_single_player_west();
	printf("================================\n");
	test_multiple_players_error();
	printf("================================\n");
	test_no_player_error();
	printf("================================\n");
	printf("ALL PLAYER INIT TESTS PASSED\n");
	return (0);
}
