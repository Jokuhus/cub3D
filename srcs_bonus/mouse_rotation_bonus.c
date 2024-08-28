/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 09:12:01 by jsuk              #+#    #+#             */
/*   Updated: 2024/07/26 19:20:41 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx.h"
#include "cub3d_bonus.h"

void	draw_mouse_poointer(t_mlx *mlx)
{
	int	x;
	int	y;

	y = SCREENHEIGHT / 2 - 20;
	while (y < SCREENHEIGHT / 2 + 20)
	{
		x = SCREENWIDTH / 2;
		my_mlx_pixel_put(&mlx->frame, x, y, 0);
		y++;
	}
	x = SCREENWIDTH / 2 - 20;
	while (x < SCREENWIDTH / 2 + 20)
	{
		y = SCREENHEIGHT / 2;
		my_mlx_pixel_put(&mlx->frame, x, y, 0);
		x++;
	}
}

void	mouse_rotation(t_mlx *mlx)
{
	double	rad;
	int		x;
	int		y;

	mlx_mouse_get_pos(mlx->win, &x, &y);
	rad = M_PI / SCREENWIDTH * (x - SCREENWIDTH / 2);
	mlx_mouse_move(mlx->win, SCREENWIDTH / 2, SCREENHEIGHT / 2);
	rotate_player(&mlx->player, rad);
}
