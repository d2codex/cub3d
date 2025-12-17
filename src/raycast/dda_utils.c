#include "cub3d.h"

/**
 * @brief Checks if ray hit a wall or went out of bounds
 *
 * Performs bounds checking before grid access to prevent segfaults
 * and infinite loops if ray escapes map boundaries.
 *
 * @param game Pointer to the game structure (contains the map)
 * @param ray Pointer to the ray structure
 * @return true if hit wall or out of bounds, false otherwise
 */
bool	check_hit(t_game *game, t_ray *ray)
{
	if (ray->map_x < 0 || ray->map_x >= game->map.width)
		return (true);
	if (ray->map_y < 0 || ray->map_y >= game->map.height)
		return (true);
	if (game->map.grid[ray->map_y][ray->map_x] == '1')
		return (true);
	return (false);
}
