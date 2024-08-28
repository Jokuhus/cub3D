/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:00:36 by jsuk              #+#    #+#             */
/*   Updated: 2024/07/18 07:53:55 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"

static int	is_in_circle(int col, int row, int r)
{
	int	x;
	int	y;

	x = col - r;
	y = row - r;
	if ((x * x) + (y * y) <= (r * r))
		return (1);
	return (0);
}

static void	draw_pixel(t_mlx *mlx, int col, int row)
{
	int		x;
	int		y;
	double	mag;

	mag = 10;
	x = ((double)col / mag - (double)MAPWIDTH / (double)2 / mag)
		* cos(mlx->player.pa)
		- ((double)row / mag - (double)MAPHEIGHT / (double)2 / mag)
		* sin(mlx->player.pa) + mlx->player.pos_x;
	y = ((double)col / mag - (double)MAPWIDTH / (double)2 / mag)
		* sin(mlx->player.pa)
		+ ((double)row / mag - (double)MAPHEIGHT / (double)2 / mag)
		* cos(mlx->player.pa) + mlx->player.pos_y;
	if (x >= 0 && x < mlx->map.width && \
		y >= 0 && y < mlx->map.height)
	{
		if (mlx->map.map[y][x] == '1')
			my_mlx_pixel_put(&mlx->frame, col, row,
				create_trgb(0, 255, 255, 255));
		else
			my_mlx_pixel_put(&mlx->frame, col, row, 0);
	}
	else
		my_mlx_pixel_put(&mlx->frame, col, row, 0);
}

static void	draw_player(t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	while (x < 9)
	{
		y = 0;
		while (y < 9)
		{
			if (is_in_circle(x, y, 3))
				my_mlx_pixel_put(&mlx->frame, x + (MAPWIDTH - 3) / 2,
					y + (MAPHEIGHT - 3) / 2 - 2, create_trgb(0, 0, 255, 0));
			y++;
		}
		x++;
	}
}

void	draw_mini_map(t_mlx *mlx)
{
	int	row;
	int	col;

	row = 0;
	while (row < MAPHEIGHT)
	{
		col = 0;
		while (col < MAPWIDTH)
		{
			if (is_in_circle(col, row, MAPWIDTH / 2))
				draw_pixel(mlx, col, row);
			col++;
		}
		row++;
	}
	draw_player(mlx);
}
