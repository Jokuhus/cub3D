/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyehan <hyehan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:59:29 by hyehan            #+#    #+#             */
/*   Updated: 2024/08/22 14:59:59 by hyehan           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "cub3d.h"

static int	check_line(t_map *map, char *line);
static int	check_identifier(t_map *map, char **arr);
static void	check_info_set(t_map *map);

void	read_cub(t_map *map, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (line == NULL)
		error_exit("error: cub3D: file is emtpy\n");
	while (line)
	{
		if (check_line(map, strtrim_back(line, '\n')))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	check_info_set(map);
	read_map(map, line, fd);
}

static int	check_line(t_map *map, char *line)
{
	char	**arr;
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (0);
	arr = ft_split(line, ' ');
	if (!arr)
		error_exit("error: cub3D: cannot allocate memory\n");
	i = -1;
	if (check_identifier(map, arr))
	{
		while (arr[++i])
			free(arr[i]);
		free(arr);
		return (1);
	}
	while (arr[++i])
		free(arr[i]);
	free(arr);
	return (0);
}

static int	check_identifier(t_map *map, char **arr)
{
	int	i;

	i = 0;
	if (!ft_strncmp(arr[0], "NO", 3) && arr[1] && !arr[2])
		map->no = set_info(arr[1], map->no);
	else if (!ft_strncmp(arr[0], "SO", 3) && arr[1] && !arr[2])
		map->so = set_info(arr[1], map->so);
	else if (!ft_strncmp(arr[0], "WE", 3) && arr[1] && !arr[2])
		map->we = set_info(arr[1], map->we);
	else if (!ft_strncmp(arr[0], "EA", 3) && arr[1] && !arr[2])
		map->ea = set_info(arr[1], map->ea);
	else if (!ft_strncmp(arr[0], "F", 2) && arr[1] && !arr[2])
		map->f_color = set_color(arr[1], map->f_color);
	else if (!ft_strncmp(arr[0], "C", 2) && arr[1] && !arr[2])
		map->c_color = set_color(arr[1], map->c_color);
	else if (arr[0][0] == '1')
		return (1);
	else
		error_exit("error: cub3D: wrong file form\n");
	while (arr[i])
		i++;
	if (i != 2)
		error_exit("error : cub3D : Wrong file form\n");
	return (0);
}

static void	check_info_set(t_map *map)
{
	if (!map->no)
		error_exit("error: cub3D: missing NO identifier\n");
	else if (!map->so)
		error_exit("error: cub3D: missing SO identifier\n");
	else if (!map->ea)
		error_exit("error: cub3D: missing EA identifier\n");
	else if (!map->we)
		error_exit("error: cub3D: missing WE identifier\n");
	else if (map->f_color == -1)
		error_exit("error: cub3D: missing F identifier\n");
	else if (map->c_color == -1)
		error_exit("error: cub3D: missing C identifier\n");
}
