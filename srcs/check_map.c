/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyehan <hyehan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:22:21 by hyehan            #+#    #+#             */
/*   Updated: 2024/08/22 14:59:59 by hyehan           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

static void	check_duplication(t_map *map);
static void	mod_view(t_map *map, char view);

void	check_map(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] != '1' && map->map[y][x] != ' ')
			{
				if (y - 1 < 0 || y + 1 >= map->height || \
					x - 1 < 0 || x + 1 >= map->width || \
					map->map[y - 1][x] == ' ' || \
					map->map[y][x - 1] == ' ' || \
					map->map[y + 1][x] == ' ' || \
					map->map[y][x + 1] == ' ')
					error_exit("error: cub3D: wrong file form\n");
			}
			x++;
		}
		y++;
	}
	check_duplication(map);
}

static void	check_duplication(t_map *map)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S' \
				|| map->map[i][j] == 'W' || map->map[i][j] == 'E')
			{
				mod_view(map, map->map[i][j]);
				count++;
			}
			if (count > 1)
				error_exit("error: cub3D: wrong file form\n");
			j++;
		}
		i++;
	}
	if (count == 0)
		error_exit("error: cub3D: wrong file form\n");
}

static void	mod_view(t_map *map, char view)
{
	if (view == 'N')
		map->view = NO;
	else if (view == 'S')
		map->view = SO;
	else if (view == 'W')
		map->view = WE;
	else if (view == 'E')
		map->view = EA;
}
