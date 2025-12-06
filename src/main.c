#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;
	int		i;
	int		j;

	if (argc != 2)
	{
		print_errors(ARG_USAGE, NULL, NULL);
		return (EXIT_FAILURE);
	}
	if (validate_argument(argv[1]) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	init_data(&game);
	if (parse_map(argv[1], &game.map))
		return (EXIT_FAILURE);
	if (init_game_data(&game) != EXIT_SUCCESS)
		return (EXIT_FAILURE);

	i = 0;
	while (i < 50)
	{
		j = 0;
		while (j < 50)
		{
			draw_pixel_in_buffer(&game, j, i, 0x0000FF00);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);
	print_map_grid(&game.map);
	free_map(&game.map);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
