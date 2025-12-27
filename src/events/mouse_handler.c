/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafroidu <pafroidu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:03:01 by pafroidu          #+#    #+#             */
/*   Updated: 2025/12/27 18:06:03 by pafroidu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Handles mouse movement for FPS-style camera rotation
 *
 * Tracks horizontal mouse movement to rotate the camera view.
 * Ignores movements near screen edges (5px threshold) to prevent
 * jittery behavior when cursor reaches window boundaries.
 * Only handles horizontal rotation (yaw), not vertical (pitch).
 *
 * @param x Current mouse X position in window coordinates
 * @param y Current mouse Y position in window coordinates
 * @param param Pointer to game structure (void* from MLX, must cast)
 * @return EXIT_SUCCESS
 */
int	handle_mouse_move(int x, int y, void *param)
{
	t_game	*game;
	int		delta_x;

	game = (t_game *)param;
	if (x <= 5 || x >= WINDOWS_X - 5)
		return (EXIT_SUCCESS);
	delta_x = x - game->last_mouse_x;
	if (delta_x != 0)
		apply_camera_rotation(game, delta_x * MOUSE_SENSITIVITY);
	game->last_mouse_x = x;
	game->last_mouse_y = y;
	return (EXIT_SUCCESS);
}
