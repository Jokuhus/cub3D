/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyehan <hyehan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:05:20 by hyehan            #+#    #+#             */
/*   Updated: 2024/08/22 14:59:59 by hyehan           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "cub3d.h"

static void	cnt_w_h(t_map *map, char *str);
static void	leveling_map(char *str, int *j, t_map *map, int i);

void	set_map(t_map *map, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	cnt_w_h(map, str);
	map->map = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
		error_exit("error: cub3D: cannot allocate memory\n");
	map->map[map->height] = NULL;
	while (i < map->height)
	{
		map->map[i] = (char *)malloc(sizeof(char) * (map->width + 1));
		if (!map->map[i])
			error_exit("error: cub3D: cannot allocate memory\n");
		leveling_map(str, &j, map, i);
		map->map[i][map->width] = '\0';
		i++;
	}
	free(str);
	check_map(map);
}

static void	cnt_w_h(t_map *map, char *str)
{
	int	i;
	int	cur_width;

	i = 0;
	cur_width = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			map->height++;
			if (map->width < cur_width)
				map->width = cur_width;
			cur_width = 0;
		}
		else
			cur_width++;
		i++;
	}
	if (cur_width > 0)
	{
		map->height++;
		if (map->width < cur_width)
			map->width = cur_width;
	}
}

static void	leveling_map(char *str, int *j, t_map *map, int i)
{
	int	k;

	k = 0;
	while (str[*j] != '\n' && str[*j] != '\0' && k < map->width)
	{
		if (str[*j] == 'N' || str[*j] == 'S'
			|| str[*j] == 'W' || str[*j] == 'E')
		{
			map->pos_x = k;
			map->pos_y = i;
		}
		map->map[i][k] = str[*j];
		(*j)++;
		k++;
	}
	while (k < map->width)
	{
		map->map[i][k] = ' ';
		k++;
	}
	if (str[*j] == '\n')
		(*j)++;
}
