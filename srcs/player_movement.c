/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:40:02 by jsuk              #+#    #+#             */
/*   Updated: 2024/07/26 17:34:37 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"

static void	rotate_player(t_plr *player, double rad)
{
	double	old_pdx;
	double	old_plane_x;

	old_pdx = player->pdx;
	player->pdx = player->pdx * cos(rad) - player->pdy * sin(rad);
	player->pdy = old_pdx * sin(rad) + player->pdy * cos(rad);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rad) - player->plane_y * sin(rad);
	player->plane_y = old_plane_x * sin(rad) + player->plane_y * cos(rad);
}

static int	is_collided(t_map *map, double x, double y)
{
	int	max_x;
	int	max_y;
	int	min_x;
	int	min_y;

	max_x = x + 0.2;
	max_y = y + 0.2;
	min_x = x - 0.2;
	min_y = y - 0.2;
	if (min_x >= 0 && min_x < map->width && min_y >= 0 && \
		min_y < map->height && map->map[min_y][min_x] == '1')
		return (0);
	if (min_x >= 0 && min_x < map->width && max_y >= 0 && \
		max_y < map->height && map->map[max_y][min_x] == '1')
		return (0);
	if (max_x >= 0 && max_x < map->width && min_y >= 0 && \
		min_y < map->height && map->map[min_y][max_x] == '1')
		return (0);
	if (max_x >= 0 && max_x < map->width && max_y >= 0 && \
		max_y < map->height && map->map[max_y][max_x] == '1')
		return (0);
	return (1);
}

static void	move_fb_player(t_map *map, t_plr *player, double speed, char flag)
{
	double	mov_x;
	double	mov_y;

	if (flag)
	{
		mov_x = player->pos_x + player->pdx / speed;
		mov_y = player->pos_y + player->pdy / speed;
	}
	else
	{
		mov_x = player->pos_x - player->pdx / speed;
		mov_y = player->pos_y - player->pdy / speed;
	}
	if (is_collided(map, mov_x, player->pos_y))
		player->pos_x = mov_x;
	if (is_collided(map, player->pos_x, mov_y))
		player->pos_y = mov_y;
}

static void	move_lr_player(t_map *map, t_plr *player, double speed, double rad)
{
	double	pdx;
	double	pdy;
	double	mov_x;
	double	mov_y;

	pdx = player->pdx * cos(rad) - player->pdy * sin(rad);
	pdy = player->pdx * sin(rad) + player->pdy * cos(rad);
	mov_x = player->pos_x + pdx / speed / 2;
	mov_y = player->pos_y + pdy / speed / 2;
	if (is_collided(map, mov_x, player->pos_y))
		player->pos_x = mov_x;
	if (is_collided(map, player->pos_x, mov_y))
		player->pos_y = mov_y;
}

void	player_movement(int key_value, t_mlx *mlx, double rad, double speed)
{
	if (key_value == 123)
	{
		mlx->player.pa -= rad;
		if (mlx->player.pa < 0)
			mlx->player.pa += 2 * M_PI;
		rotate_player(&mlx->player, -rad);
	}
	else if (key_value == 124)
	{
		mlx->player.pa += rad;
		if (mlx->player.pa > 2 * M_PI)
			mlx->player.pa -= 2 * M_PI;
		rotate_player(&mlx->player, rad);
	}
	else if (key_value == 13)
		move_fb_player(&mlx->map, &mlx->player, speed, 1);
	else if (key_value == 1)
		move_fb_player(&mlx->map, &mlx->player, speed, 0);
	else if (key_value == 0)
		move_lr_player(&mlx->map, &mlx->player, speed, 3 * M_PI_2);
	else if (key_value == 2)
		move_lr_player(&mlx->map, &mlx->player, speed, M_PI_2);
}
