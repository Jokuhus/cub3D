/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyehan <hyehan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:05:20 by hyehan            #+#    #+#             */
/*   Updated: 2024/08/22 15:00:00 by hyehan           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "cub3d_bonus.h"

static void	cnt_w_h(t_map *map, char *str);
static void	leveling_map(char *str, int *j, t_mlx *mlx, int i);

void	set_map(t_mlx *mlx, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	cnt_w_h(&mlx->map, str);
	mlx->map.map = (char **)malloc(sizeof(char *) * (mlx->map.height + 1));
	if (!mlx->map.map)
		error_exit("error: cub3D: cannot allocate memory\n");
	mlx->map.map[mlx->map.height] = NULL;
	mlx->spt.total = 0;
	while (i < mlx->map.height)
	{
		mlx->map.map[i] = (char *)malloc(sizeof(char) * (mlx->map.width + 1));
		if (!mlx->map.map[i])
			error_exit("error: cub3D: cannot allocate memory\n");
		leveling_map(str, &j, mlx, i);
		mlx->map.map[i][mlx->map.width] = '\0';
		i++;
	}
	free(str);
	check_map(&mlx->map);
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

static void	check_info_exist(char c, t_mlx *mlx)
{
	if ((c == 'D' || c == 'd') && !mlx->map.door)
		error_exit("error: cub3D: missing DO identifier\n");
	if (c == 'M')
	{
		if (!mlx->map.mob0 || !mlx->map.mob1)
			error_exit("error: cub3D: missing M identifier\n");
		else
			mlx->spt.total++;
	}
}

static void	leveling_map(char *str, int *j, t_mlx *mlx, int i)
{
	int	k;

	k = 0;
	while (str[*j] != '\n' && str[*j] != '\0' && k < mlx->map.width)
	{
		if (str[*j] == 'N' || str[*j] == 'S'
			|| str[*j] == 'W' || str[*j] == 'E')
		{
			mlx->player.pos_x = k;
			mlx->player.pos_y = i;
		}
		check_info_exist(str[*j], mlx);
		mlx->map.map[i][k] = str[*j];
		(*j)++;
		k++;
	}
	while (k < mlx->map.width)
	{
		mlx->map.map[i][k] = ' ';
		k++;
	}
	if (str[*j] == '\n')
		(*j)++;
}
