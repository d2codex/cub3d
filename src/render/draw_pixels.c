#include "cub3d.h"

void	draw_pixel_in_buffer(t_game *game, int x, int y, int color)
{
	char	*dest;

	dest = game->img_addr + (y * game->img_line_len + x * (game->img_bpp / 8));
	*(unsigned int*)dest = color;
}
