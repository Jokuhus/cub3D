/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyehan <hyehan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:22:37 by hyehan            #+#    #+#             */
/*   Updated: 2024/08/22 14:59:59 by hyehan           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "cub3d.h"

static char	*check_valid(char *tmp_map, int i, int j);
static char	*remove_space(char *line);

void	read_map(t_map *map, char *line, int fd)
{
	char	*tmp_map;
	char	*tmp_ret;
	char	*result;

	line = remove_space(line);
	tmp_map = ft_strdup(line);
	if (!tmp_map)
		error_exit("error: cub3D: cannot allocate memory\n");
	free(line);
	line = get_next_line(fd);
	while (line)
	{
		line = remove_space(line);
		tmp_ret = ft_strjoin(tmp_map, line);
		if (!tmp_ret)
			error_exit("error: cub3D: cannot allocate memory\n");
		free(tmp_map);
		tmp_map = tmp_ret;
		free(line);
		line = get_next_line(fd);
	}
	result = check_valid(tmp_map, -1, -1);
	set_map(map, result);
}

static char	*remove_space(char *line)
{
	char	*tmp_ret;

	line = strtrim_back(line, '\n');
	line = strtrim_back(line, ' ');
	tmp_ret = ft_strjoin(line, "\n");
	if (!tmp_ret)
		error_exit("error: cub3D: cannot allocate memory\n");
	free(line);
	line = tmp_ret;
	return (line);
}

static char	*check_valid(char *tmp_map, int i, int j)
{
	char	*result;

	while (tmp_map[++i])
	{
		if (!(tmp_map[i] == ' ' || tmp_map[i] == '1' || tmp_map[i] == '0' \
			|| tmp_map[i] == 'N' || tmp_map[i] == 'S' || tmp_map[i] == 'W' \
			|| tmp_map[i] == 'E' || tmp_map[i] == '\n'))
			error_exit("error: cub3D: wrong file form\n");
	}
	while (tmp_map[i] != '1' && tmp_map[i] != '0' && tmp_map[i] != 'N' \
		&& tmp_map[i] != 'S' && tmp_map[i] != 'W' && tmp_map[i] != 'E')
		i--;
	i += 1;
	result = (char *)malloc(sizeof(char) * (i + 1));
	if (!result)
		error_exit("error: cub3D: cannot allocate memory\n");
	while (++j < i)
		result[j] = tmp_map[j];
	result[j] = '\0';
	free(tmp_map);
	return (result);
}
