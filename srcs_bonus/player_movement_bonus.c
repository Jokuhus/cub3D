/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:40:02 by jsuk              #+#    #+#             */
/*   Updated: 2024/08/18 14:28:45 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d_bonus.h"

void	rotate_player(t_plr *player, double rad)
{
	double	old_pdx;
	double	old_plane_x;

	player->pa += rad;
	if (player->pa < 0)
		player->pa += 2 * M_PI;
	else if (player->pa > 2 * M_PI)
		player->pa -= 2 * M_PI;
	old_pdx = player->pdx;
	player->pdx = player->pdx * cos(rad) - player->pdy * sin(rad);
	player->pdy = old_pdx * sin(rad) + player->pdy * cos(rad);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rad) - player->plane_y * sin(rad);
	player->plane_y = old_plane_x * sin(rad) + player->plane_y * cos(rad);
}

int	is_collided(t_map *map, double x, double y)
{
	int	max_x;
	int	max_y;
	int	min_x;
	int	min_y;

	max_x = x + 0.2;
	max_y = y + 0.2;
	min_x = x - 0.2;
	min_y = y - 0.2;
	if (min_x >= 0 && min_x < map->width && min_y >= 0 && min_y < map->height \
		&& map->map[min_y][min_x] != '0' && map->map[min_y][min_x] != 'd')
		return (0);
	if (min_x >= 0 && min_x < map->width && max_y >= 0 && max_y < map->height \
		&& map->map[max_y][min_x] != '0' && map->map[max_y][min_x] != 'd')
		return (0);
	if (max_x >= 0 && max_x < map->width && min_y >= 0 && min_y < map->height \
		&& map->map[min_y][max_x] != '0' && map->map[min_y][max_x] != 'd')
		return (0);
	if (max_x >= 0 && max_x < map->width && max_y >= 0 && max_y < map->height \
		&& map->map[max_y][max_x] != '0' && map->map[max_y][max_x] != 'd')
		return (0);
	return (1);
}

void	move_fb_player(t_map *map, t_plr *player, double speed, char flag)
{
	double	mov_x;
	double	mov_y;

	if (flag)
	{
		mov_x = player->pos_x + player->pdx * speed * 1.5;
		mov_y = player->pos_y + player->pdy * speed * 1.5;
	}
	else
	{
		mov_x = player->pos_x - player->pdx * speed * 1.5;
		mov_y = player->pos_y - player->pdy * speed * 1.5;
	}
	if (is_collided(map, mov_x, player->pos_y))
		player->pos_x = mov_x;
	if (is_collided(map, player->pos_x, mov_y))
		player->pos_y = mov_y;
}

void	move_lr_player(t_map *map, t_plr *player, double speed, double rad)
{
	double	pdx;
	double	pdy;
	double	mov_x;
	double	mov_y;

	pdx = player->pdx * cos(rad) - player->pdy * sin(rad);
	pdy = player->pdx * sin(rad) + player->pdy * cos(rad);
	mov_x = player->pos_x + pdx * speed;
	mov_y = player->pos_y + pdy * speed;
	if (is_collided(map, mov_x, player->pos_y))
		player->pos_x = mov_x;
	if (is_collided(map, player->pos_x, mov_y))
		player->pos_y = mov_y;
}
