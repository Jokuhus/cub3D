/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:21:02 by jsuk              #+#    #+#             */
/*   Updated: 2024/07/20 05:31:19 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d_bonus.h"

void	error_exit(char *error_message)
{
	ft_putstr_fd(error_message, 2);
	exit(1);
}

void	free_char_arr(char **arr)
{
	int	idx;

	if (arr == 0)
		return ;
	idx = 0;
	while (arr[idx])
	{
		free(arr[idx]);
		idx++;
	}
	free(arr);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

char	*strtrim_back(char *str, char c)
{
	int	i;

	if (str == NULL)
		return (NULL);
	i = ft_strlen(str) - 1;
	while (i >= 0 && str[i] == c)
	{
		str[i] = '\0';
		i--;
	}
	return (str);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
