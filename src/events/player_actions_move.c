#include "cub3d.h"

/**
 * @brief Attempts to move player to new position if valid
 *
 * Checks collision at target position and updates player coordinates
 * only if the position is walkable (not a wall).
 *
 * @param game Pointer to game structure
 * @param new_x Target X coordinate
 * @param new_y Target Y coordinate
 */
static void	try_move(t_game *game, double new_x, double new_y)
{
	if (game->map.grid[(int)new_y][(int)new_x] != '1')
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

/**
 * @brief Moves player forward in current direction
 *
 * @param game Pointer to game structure
 */
void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
	new_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;
	try_move(game, new_x, new_y);
}

/**
 * @brief Moves player backward (opposite of current direction)
 *
 * @param game Pointer to game structure
 */
void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;
	try_move(game, new_x, new_y);
}

/**
 * @brief Strafes player to the left (perpendicular to direction)
 *
 * @param game Pointer to game structure
 */
void	strafe_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.dir_y * MOVE_SPEED;
	new_y = game->player.pos_y + game->player.dir_x * MOVE_SPEED;
	try_move(game, new_x, new_y);
}

/**
 * @brief Strafes player to the right (perpendicular to direction)
 *
 * @param game Pointer to game structure
 */
void	strafe_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_y * MOVE_SPEED;
	new_y = game->player.pos_y - game->player.dir_x * MOVE_SPEED;
	try_move(game, new_x, new_y);
}
