/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 08:15:31 by jsuk              #+#    #+#             */
/*   Updated: 2024/07/18 08:30:44 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"

void	check_face(t_dis *dis)
{
	if (dis->side)
	{
		if (dis->step_y > 0)
			dis->face = NO;
		else
			dis->face = SO;
	}
	else
	{
		if (dis->step_x > 0)
			dis->face = WE;
		else
			dis->face = EA;
	}
}

static int	find_color(t_texture *tex, double col, double row, t_view face)
{
	int	result_row;
	int	result_col;

	result_row = (tex->height - 1) * row;
	col -= floor(col);
	result_col = tex->width * col;
	if (face == WE || face == SO)
		result_col = tex->width - result_col - 1;
	return (tex->texture[result_row][result_col]);
}

void	draw_wall(t_dis *dis, t_mlx *mlx, int x, int y)
{
	double	height;
	int		color;

	height = dis->draw_end - dis->draw_start;
	if (dis->face == NO)
		color = find_color(&mlx->tex.no, mlx->player.pos_x + \
			dis->perp_wall_dist * dis->ray_dir_x, \
			(double)(y - dis->draw_start) / height, NO);
	else if (dis->face == SO)
		color = find_color(&mlx->tex.so, mlx->player.pos_x + \
			dis->perp_wall_dist * dis->ray_dir_x, \
			(double)(y - dis->draw_start) / height, SO);
	else if (dis->face == EA)
		color = find_color(&mlx->tex.ea, mlx->player.pos_y + \
			dis->perp_wall_dist * dis->ray_dir_y, \
			(double)(y - dis->draw_start) / height, EA);
	else
		color = find_color(&mlx->tex.we, mlx->player.pos_y + \
			dis->perp_wall_dist * dis->ray_dir_y, \
			(double)(y - dis->draw_start) / height, WE);
	my_mlx_pixel_put(&mlx->frame, x, y, color);
}
