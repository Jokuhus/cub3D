/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_action_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:12:24 by jsuk              #+#    #+#             */
/*   Updated: 2024/08/10 20:44:26 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d_bonus.h"

static double	calculate_dist(double pd, double pos, int map, int *step)
{
	double	dist;

	if (pd < 0)
	{
		*step = -1;
		dist = (pos - map) * fabs(1 / pd);
	}
	else
	{
		*step = 1;
		dist = (map + 1.0 - pos) * fabs(1 / pd);
	}
	return (dist);
}

static void	find_door_position(int *x, int *y, t_plr *player)
{
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;

	side_dist_x = calculate_dist(player->pdx, player->pos_x, *x, &step_x);
	side_dist_y = calculate_dist(player->pdy, player->pos_y, *y, &step_y);
	if (side_dist_x < side_dist_y)
		*x += step_x;
	else
		*y += step_y;
}

static int	check_stuck(int map_x, int map_y, double x, double y)
{
	int	max_x;
	int	max_y;
	int	min_x;
	int	min_y;

	max_x = x + 0.2;
	max_y = y + 0.2;
	min_x = x - 0.2;
	min_y = y - 0.2;
	if (max_x == map_x || min_x == map_x)
	{
		if (max_y == map_y || min_y == map_y)
			return (1);
	}
	return (0);
}

static void	open_door(t_mlx *mlx)
{
	int		map_x;
	int		map_y;

	map_x = (int)mlx->player.pos_x;
	map_y = (int)mlx->player.pos_y;
	find_door_position(&map_x, &map_y, &mlx->player);
	if (mlx->map.map[map_y][map_x] == 'D')
	{
		mlx->map.map[map_y][map_x] = 'd';
		return ;
	}
	else if (mlx->map.map[map_y][map_x] == 'd' && \
		!check_stuck(map_x, map_y, mlx->player.pos_x, mlx->player.pos_y))
	{
		mlx->map.map[map_y][map_x] = 'D';
		return ;
	}
	else if (mlx->map.map[map_y][map_x] == '1')
		return ;
	find_door_position(&map_x, &map_y, &mlx->player);
	if (mlx->map.map[map_y][map_x] == 'D')
		mlx->map.map[map_y][map_x] = 'd';
	else if (mlx->map.map[map_y][map_x] == 'd')
		mlx->map.map[map_y][map_x] = 'D';
}

int	mouse_click(int button, int x, int y, t_mlx *mlx)
{
	if (x || y || mlx)
		;
	if (button == 1)
		open_door(mlx);
	return (0);
}
