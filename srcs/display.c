/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:53:18 by jsuk              #+#    #+#             */
/*   Updated: 2024/07/20 06:13:02 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"

static void	clear_image(t_img *frame)
{
	int	x;
	int	y;

	y = 0;
	while (y < frame->height)
	{
		x = 0;
		while (x < frame->width)
		{
			my_mlx_pixel_put(frame->img, x, y, 0);
			x++;
		}
		y++;
	}
}

static void	move_camera_player(t_mlx *mlx)
{
	if (mlx->key.w && !mlx->key.s)
		player_movement(13, mlx, 0.03, 20);
	if (mlx->key.s && !mlx->key.w)
		player_movement(1, mlx, 0.03, 20);
	if (mlx->key.a && !mlx->key.d)
		player_movement(0, mlx, 0.03, 20);
	if (mlx->key.d && !mlx->key.a)
		player_movement(2, mlx, 0.03, 20);
	if (mlx->key.left && !mlx->key.right)
		player_movement(123, mlx, 0.03, 20);
	if (mlx->key.right && !mlx->key.left)
		player_movement(124, mlx, 0.03, 20);
}

static void	jump_squat(t_mlx *mlx)
{
	if (mlx->key.space && !mlx->player.jump)
	{
		mlx->player.jump = 1;
		mlx->player.nbr = SCREENHEIGHT / 25;
	}
	if (mlx->player.jump)
	{
		mlx->player.nbr -= 3;
		mlx->player.z += mlx->player.nbr;
		if (mlx->player.z <= 0)
		{
			mlx->player.z = 0;
			mlx->player.nbr = 0;
			mlx->player.jump = 0;
		}
	}
	if (mlx->key.shift && !mlx->player.jump && \
		mlx->player.z > -SCREENHEIGHT / 20)
		mlx->player.z -= SCREENHEIGHT / 50;
	else if (!mlx->key.shift && mlx->player.z < 0)
		mlx->player.z += SCREENHEIGHT / 50;
}

int	display(t_mlx *mlx)
{
	jump_squat(mlx);
	move_camera_player(mlx);
	clear_image(&mlx->frame);
	draw_game_screen(mlx);
	draw_mini_map(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win,
		mlx->frame.img, 0, 0);
	return (0);
}
