#include "cub3d.h"

/**
 * @brief Draws a vertical wall column at screen position x
 *
 * Calculates wall height from distance, draws a centered vertical line.
 * Clamps to screen bounds to prevent out-of-bounds writes.
 * Color depends on wall side (vertical=red, horizontal=blue).
 *
 * @param game Pointer to the game structure
 * @param x Screen column position (0 to WINDOWS_X-1)
 * @param wall_distance Perpendicular distance to the wall
 * @param side Wall side hit (0=vertical/N-S, 1=horizontal/E-W)
 */
static void	draw_wall_column(t_game *game, int x, double wall_distance, int side)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	y;
	int	color;

	line_height = (int)(WINDOWS_Y / wall_distance);
	draw_start = (WINDOWS_Y - line_height) / 2;
	draw_end = draw_start + line_height - 1;

	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WINDOWS_Y)
		draw_end = WINDOWS_Y - 1;
	if (side == 0)
		color = 0xFF0000;
	else
		color = 0x0000FF;
	y = draw_start;
	while (y <= draw_end)
	{
		draw_pixel_in_buffer(game, x, y, color);
		y++;
	}
}

/**
 * @brief Casts a single ray for one screen column and renders it
 *
 * Converts screen column x to camera space (-1.0 to +1.0),
 * calculates ray direction using linear algebra,
 * performs raycasting via DDA to find wall distance and side,
 * then delegates drawing to draw_wall_column.
 *
 * @param game Pointer to the game structure
 * @param x Screen column index (0 to WINDOWS_X-1)
 */
static void	cast_column_ray(t_game *game, int x)
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	wall_distance;
	int		side;

	camera_x = 2.0 * x / WINDOWS_X - 1.0;
	ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	wall_distance = cast_ray(game, ray_dir_x, ray_dir_y, &side);
	draw_wall_column(game, x, wall_distance, side);
}

/**
  * @brief Renders a complete frame with full raycasting
  *
  * Main rendering loop that casts one ray per screen column
  * (WINDOWS_X rays total).
  *
  * @param game Pointer to the game structure
*/
void	render_frame(t_game *game)
{
	int		x;

	x = 0;
	while (x < WINDOWS_X)
	{
		cast_column_ray(game, x);
		x++;
	}
}

