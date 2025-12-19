#include "cub3d.h"

/**
 * @brief Returns wall color based on direction
 *
 * @param wall_dir Wall direction (NORTH/SOUTH/EAST/WEST)
 * @return Color in 0xRRGGBB format
 */
int	get_wall_color(int wall_dir)
{
	if (wall_dir == NORTH)
		return (0xFF0000);
	else if (wall_dir == SOUTH)
		return (0x00FF00);
	else if (wall_dir == EAST)
		return (0x0000FF);
	else
		return (0xFFFF00);
}

/**
 * @brief Retrieves a pixel color from a texture at given coordinates
 *
 * Performs boundary checks before memory access to prevent segfaults.
 * Uses MLX texture memory layout: offset = y * line_len + x * (bpp/8)
 *
 * @param texture Pointer to the texture structure
 * @param tex_x X coordinate in texture (0 to width-1)
 * @param tex_y Y coordinate in texture (0 to height-1)
 * @return Pixel color in 0xRRGGBB format, or TEXTURE_FALLBACK_COLOR if out of bounds
 */
int	get_texture_pixel(t_texture *texture, int tex_x, int tex_y)
{
	char	*pixel;

	if (tex_x < 0 || tex_x >= texture->width)
		return (TEXTURE_FALLBACK_COLOR);
	if (tex_y < 0 || tex_y >= texture->height)
		return (TEXTURE_FALLBACK_COLOR);
	pixel = texture->addr + (tex_y * texture->line_len + tex_x
			* (texture->bpp / 8));
	return (*(int *)pixel);
}
