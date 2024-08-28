/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 08:15:31 by jsuk              #+#    #+#             */
/*   Updated: 2024/07/26 19:02:52 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d_bonus.h"

void	check_face(t_dis *dis, char **map)
{
	if (map[dis->map_y][dis->map_x] == 'D')
		dis->door = 1;
	else
		dis->door = 0;
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

	if (row < 0)
		row = 0;
	result_row = (tex->height - 1) * row;
	col -= floor(col);
	result_col = tex->width * col;
	if (face == WE || face == SO)
		result_col = tex->width - result_col - 1;
	return (tex->texture[result_row][result_col]);
}

static int	wall_color(t_dis *dis, t_mlx *mlx, int y, double height)
{
	int		color;

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
	return (color);
}

static int	door_color(t_dis *dis, t_mlx *mlx, int y, double height)
{
	int		color;

	if (dis->face == NO)
		color = find_color(&mlx->tex.door, mlx->player.pos_x + \
			dis->perp_wall_dist * dis->ray_dir_x, \
			(double)(y - dis->draw_start) / height, NO);
	else if (dis->face == SO)
		color = find_color(&mlx->tex.door, mlx->player.pos_x + \
			dis->perp_wall_dist * dis->ray_dir_x, \
			(double)(y - dis->draw_start) / height, SO);
	else if (dis->face == EA)
		color = find_color(&mlx->tex.door, mlx->player.pos_y + \
			dis->perp_wall_dist * dis->ray_dir_y, \
			(double)(y - dis->draw_start) / height, EA);
	else
		color = find_color(&mlx->tex.door, mlx->player.pos_y + \
			dis->perp_wall_dist * dis->ray_dir_y, \
			(double)(y - dis->draw_start) / height, WE);
	return (color);
}

void	draw_wall(t_dis *dis, t_mlx *mlx, int x, int y)
{
	double	height;
	int		color;

	height = dis->draw_end - dis->draw_start;
	if (dis->door)
		color = door_color(dis, mlx, y, height);
	else
		color = wall_color(dis, mlx, y, height);
	my_mlx_pixel_put(&mlx->frame, x, y, color);
}
