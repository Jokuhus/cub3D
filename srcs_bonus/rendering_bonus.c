/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:19:42 by jsuk              #+#    #+#             */
/*   Updated: 2024/08/18 15:36:17 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "cub3d_bonus.h"

static void	set_delta_dist(t_plr *player, t_dis *dis, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)SCREENWIDTH - 1;
	dis->ray_dir_x = player->pdx + player->plane_x * camera_x;
	dis->ray_dir_y = player->pdy + player->plane_y * camera_x;
	dis->map_x = (int)player->pos_x;
	dis->map_y = (int)player->pos_y;
	dis->delta_dist_x = fabs(1 / dis->ray_dir_x);
	dis->delta_dist_y = fabs(1 / dis->ray_dir_y);
}

static void	set_side_dist(t_plr *player, t_dis *dis)
{
	if (dis->ray_dir_x < 0)
	{
		dis->step_x = -1;
		dis->side_dist_x = (player->pos_x - dis->map_x) * \
			dis->delta_dist_x;
	}
	else
	{
		dis->step_x = 1;
		dis->side_dist_x = (dis->map_x + 1.0 - player->pos_x) * \
			dis->delta_dist_x;
	}
	if (dis->ray_dir_y < 0)
	{
		dis->step_y = -1;
		dis->side_dist_y = (player->pos_y - dis->map_y) * \
			dis->delta_dist_y;
	}
	else
	{
		dis->step_y = 1;
		dis->side_dist_y = (dis->map_y + 1.0 - player->pos_y) * \
			dis->delta_dist_y;
	}
}

static void	check_hit(t_dis *dis, t_map *map)
{
	while (1)
	{
		if (dis->side_dist_x < dis->side_dist_y)
		{
			dis->side_dist_x += dis->delta_dist_x;
			dis->map_x += dis->step_x;
			dis->side = 0;
		}
		else
		{
			dis->side_dist_y += dis->delta_dist_y;
			dis->map_y += dis->step_y;
			dis->side = 1;
		}
		if (map->map[dis->map_y][dis->map_x] != '0' && \
			map->map[dis->map_y][dis->map_x] != 'd')
			break ;
	}
	if (dis->side == 0)
		dis->perp_wall_dist = (dis->side_dist_x - dis->delta_dist_x);
	else
		dis->perp_wall_dist = (dis->side_dist_y - dis->delta_dist_y);
}

static void	draw_on_image(t_dis *dis, t_mlx *mlx, int x)
{
	int	line_height;
	int	y;

	line_height = (int)(SCREENHEIGHT / dis->perp_wall_dist);
	dis->draw_start = -line_height / 2 + SCREENHEIGHT / 2;
	if (dis->draw_start >= SCREENHEIGHT)
		dis->draw_start = 0;
	dis->draw_end = line_height / 2 + SCREENHEIGHT / 2;
	if (dis->draw_end < 0)
		dis->draw_end = SCREENHEIGHT - 1;
	y = 0;
	while (y < SCREENHEIGHT)
	{
		if (y >= dis->draw_start && y <= dis->draw_end)
			draw_wall(dis, mlx, x, y);
		else if (y < dis->draw_start)
			my_mlx_pixel_put(&mlx->frame, x, y, mlx->map.c_color);
		else
			my_mlx_pixel_put(&mlx->frame, x, y, mlx->map.f_color);
		y++;
	}
}

void	draw_wall_routine(void *arg)
{
	t_dis	dis;
	t_dda	*dda;

	dda = (t_dda *)arg;
	while (dda->cur_pixel_x < dda->end_pixel_x)
	{
		set_delta_dist(&dda->mlx->player, &dis, dda->cur_pixel_x);
		set_side_dist(&dda->mlx->player, &dis);
		check_hit(&dis, &dda->mlx->map);
		check_face(&dis, dda->mlx->map.map);
		draw_on_image(&dis, dda->mlx, dda->cur_pixel_x);
		dda->mlx->spt.zbuffer[dda->cur_pixel_x] = dis.perp_wall_dist;
		dda->cur_pixel_x++;
	}
	free(dda);
}
