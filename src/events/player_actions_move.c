#include "cub3d.h"

/**
 * @brief Moves player forward in current direction
 *
 * Calculates new position by adding direction vector * speed.
 * Only moves if new position is not inside a wall.
 *
 * @param game Pointer to game structure
 */
void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	// calculate new position: current pos + direction * speed
	new_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
	new_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;
	// check collision: is new position a wall?
	// cast to int to get grid coordinates
	if (game->map.grid[(int)new_y][(int)new_x] != '1')
	{
		// no wall, safe to move
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
	// else: wall detected, don't move (collision!)
}

/**
 * @brief Moves player backward (opposite of current direction)
 *
 * Calculates new position by subtracting direction vector * speed.
 * Only moves if new position is not inside a wall.
 *
 * @param game Pointer to game structure
 */
void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	// calculate new position: current pos - direction * speed
	new_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;
	// check collision
	if (game->map.grid[(int)new_y][(int)new_x] != '1')
	{
		// no wall, safe to move
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

/**
 * @brief Strafes player to the left (perpendicular to direction)
 *
 * Uses perpendicular vector (90° rotation of direction).
 * Perpendicular left of (x, y) is (-y, x).
 *
 * Example: direction (1, 0) → perpendicular left (0, 1)
 *
 * @param game Pointer to game structure
 */
void	strafe_left(t_game *game)
{
	double	new_x;
	double	new_y;

	// perpendicular left = rotate direction 90° counter-clockwise
	// if dir = (x, y), perpendicular = (-y, x)
	new_x = game->player.pos_x - game->player.dir_y * MOVE_SPEED;
	new_y = game->player.pos_y + game->player.dir_x * MOVE_SPEED;
	// check collision
	if (game->map.grid[(int)new_y][(int)new_x] != '1')
	{
		// no wall, safe to move
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

/**
 * @brief Strafes player to the right (perpendicular to direction)
 *
 * Uses perpendicular vector (90° rotation of direction).
 * Perpendicular right of (x, y) is (y, -x).
 *
 * Example: direction (1, 0) → perpendicular right (0, -1)
 *
 * @param game Pointer to game structure
 */
void	strafe_right(t_game *game)
{
	double	new_x;
	double	new_y;

	// perpendicular right = rotate direction 90° clockwise
	// if dir = (x, y), perpendicular = (y, -x)
	new_x = game->player.pos_x + game->player.dir_y * MOVE_SPEED;
	new_y = game->player.pos_y - game->player.dir_x * MOVE_SPEED;
	// check collision
	if (game->map.grid[(int)new_y][(int)new_x] != '1')
	{
		// no wall, safe to move
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}
