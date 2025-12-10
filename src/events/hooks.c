#include "cub3d.h"

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win, 3, 1L << 1, handle_keyrelease, game);
	mlx_hook(game->win, 17, 0, handle_close, game);
	mlx_hook(game->win, 6, 1L << 6, handle_mouse_move, game);
}
