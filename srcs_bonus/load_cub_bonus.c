/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cub_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyehan <hyehan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:41:39 by hyehan            #+#    #+#             */
/*   Updated: 2024/08/22 14:59:59 by hyehan           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
#include "cub3d_bonus.h"

static void	init_map(t_map *map);
static int	open_file(char *filename);

void	load_cub(t_mlx *mlx, int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		error_exit("error: cub3D: insufficient arguments count\n");
	init_map(&mlx->map);
	fd = open_file(argv[1]);
	read_cub(mlx, fd);
	close(fd);
}

static void	init_map(t_map *map)
{
	map->width = 0;
	map->height = 0;
	map->map = NULL;
	map->idx = 0;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->door = NULL;
	map->mob0 = NULL;
	map->mob1 = NULL;
	map->f_color = -1;
	map->c_color = -1;
	map->view = -1;
}

static int	open_file(char *filename)
{
	int	fd;
	int	i;

	fd = -1;
	i = ft_strlen(filename);
	while (i > 0)
	{
		if (filename[i] == '.')
		{
			if (!ft_strncmp(&filename[i], ".cub", 5))
			{
				fd = open(filename, O_RDONLY);
				if (fd < 0)
					error_exit("error: cub3D: cannot open file\n");
				return (fd);
			}
			else
				error_exit("error: cub3D: wrong file extension\n");
		}
		i--;
	}
	error_exit("error: cub3D: wrong file extension\n");
	return (fd);
}
