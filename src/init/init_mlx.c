#include "cub3d.h"

/**
 * @brief Initializes MLX connection to X11 display server
 *
 * Establishes connection between program and graphical system.
 * All other MLX functions require this connection to work.
 *
 * @param game Pointer to main game structure
 * @return EXIT_SUCCESS on success, EXIT_FAILURE if connection fails
 */
static int	init_game_connection(t_game *game)
{
	if (!game)
	{
		print_errors(NULL_TGAME, NULL, NULL);
		return (EXIT_FAILURE);
	}
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		print_errors(MLX_INIT, NULL, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Creates the game window with specified dimensions
 *
 * Opens a new window via X11 server using dimensions from defines.
 * Requires a valid MLX connection to exist beforehand.
 *
 * @param game Pointer to main game structure (must have valid mlx pointer)
 * @return EXIT_SUCCESS on success, EXIT_FAILURE if window creation fails
 */
static int	init_game_windows(t_game *game)
{
	if (!game)
	{
		print_errors(NULL_TGAME, NULL, NULL);
		return (EXIT_FAILURE);
	}
	game->win = mlx_new_window(game->mlx, WINDOWS_X, WINDOWS_Y, WINDOWS_MSG);
	if (!game->win)
	{
		print_errors(WIN_INIT, NULL, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Allocates image buffer for pixel-by-pixel rendering
 *
 * Creates an image in memory and retrieves its data address.
 * Also gets technical info (bpp, line_len, endian) needed for pixel writing.
 *
 * @param game Pointer to main game structure (must have valid mlx and win)
 * @return EXIT_SUCCESS on success, EXIT_FAILURE if buffer allocation fails
 */
static int	init_game_image_buffer(t_game *game)
{
	if (!game)
	{
		print_errors(NULL_TGAME, NULL, NULL);
		return (EXIT_FAILURE);
	}
	game->img = mlx_new_image(game->mlx, WINDOWS_X, WINDOWS_Y);
	if (!game->img)
	{
		print_errors(IMG_INIT, NULL, NULL);
		return (EXIT_FAILURE);
	}
	game->img_addr = mlx_get_data_addr(game->img, &game->img_bpp,
			&game->img_line_len, &game->img_endian);
	if (!game->img_addr)
	{
		print_errors(IMG_DATA, NULL, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Facade function that initializes all MLX components
 *
 * Calls connection, window, and buffer init functions in required order.
 * Stops and returns error if any step fails.
 *
 * @param game Pointer to main game structure
 * @return EXIT_SUCCESS if all inits succeed, EXIT_FAILURE otherwise
 */
int	init_game_data(t_game *game)
{
	if (!game)
	{
		print_errors(NULL_TGAME, NULL, NULL);
		return (EXIT_FAILURE);
	}
	if (init_game_connection(game) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (init_game_windows(game) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (init_game_image_buffer(game) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
