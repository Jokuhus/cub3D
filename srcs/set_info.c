/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyehan <hyehan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:45:38 by hyehan            #+#    #+#             */
/*   Updated: 2024/08/22 14:59:59 by hyehan           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

static int	set_rgb(char **str);
static void	check_comma(const char *str);

char	*set_info(char *arr, char *element)
{
	char	*new;

	if (element != NULL)
		error_exit("error: cub3D: wrong file form\n");
	new = ft_strdup(arr);
	if (!new)
		error_exit("error: cub3D: cannot allocate memory");
	return (new);
}

int	set_color(char *arr, int element)
{
	char	**str;
	int		color;
	int		i;

	if (element != -1)
		error_exit("error: cub3D: wrong file form\n");
	check_comma(arr);
	str = ft_split(arr, ',');
	if (!str)
		error_exit("error: cub3D: cannot allocate memory");
	i = 0;
	while (str[i])
		i++;
	if (i != 3)
		error_exit("error: cub3D: wrong file form\n");
	color = set_rgb(str);
	i = -1;
	while (++i < 3)
		free(str[i]);
	free(str);
	return (color);
}

static void	check_comma(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == ',')
		error_exit("error: cub3D: wrong file form\n");
	while (str[i])
	{
		if (str[i] == ',')
		{
			if (str[i + 1] == ',')
				error_exit("error: cub3D: wrong file form\n");
		}
		i++;
	}
	if (str[i - 1] == ',')
		error_exit("error: cub3D: wrong file form\n");
}

static void	check_number(const char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (!ft_isdigit(str[idx]))
			error_exit("error: cub3D: wrong file form\n");
		idx++;
	}
}

static int	set_rgb(char **str)
{
	int	r;
	int	g;
	int	b;
	int	color;

	color = 0;
	check_number(str[0]);
	check_number(str[1]);
	check_number(str[2]);
	r = ft_atoi(str[0]);
	g = ft_atoi(str[1]);
	b = ft_atoi(str[2]);
	if (!(0 <= r && r <= 255) || !(0 <= g && g <= 255) || \
		!(0 <= b && b <= 255))
		error_exit("error: cub3D: wrong file form\n");
	color = create_trgb(0, r, g, b);
	return (color);
}
