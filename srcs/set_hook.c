/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:35:03 by jsuk              #+#    #+#             */
/*   Updated: 2024/07/20 06:13:21 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "cub3d.h"

static int	exit_hook(void)
{
	exit(0);
	return (0);
}

static int	key_up_hook(int key_value, t_mlx *mlx)
{
	if (key_value == 53 || key_value == 12)
		exit(0);
	else if (key_value == 0)
		mlx->key.a = 0;
	else if (key_value == 1)
		mlx->key.s = 0;
	else if (key_value == 2)
		mlx->key.d = 0;
	else if (key_value == 13)
		mlx->key.w = 0;
	else if (key_value == 123)
		mlx->key.left = 0;
	else if (key_value == 124)
		mlx->key.right = 0;
	else if (key_value == 257)
		mlx->key.shift = 0;
	else if (key_value == 49)
		mlx->key.space = 0;
	return (0);
}

static int	key_down_hook(int key_value, t_mlx *mlx)
{
	if (key_value == 0)
		mlx->key.a = 1;
	else if (key_value == 1)
		mlx->key.s = 1;
	else if (key_value == 2)
		mlx->key.d = 1;
	else if (key_value == 13)
		mlx->key.w = 1;
	else if (key_value == 123)
		mlx->key.left = 1;
	else if (key_value == 124)
		mlx->key.right = 1;
	else if (key_value == 257)
		mlx->key.shift = 1;
	else if (key_value == 49)
		mlx->key.space = 1;
	return (0);
}

void	set_hook(t_mlx *mlx)
{
	mlx_key_hook(mlx->win, key_up_hook, mlx);
	mlx_hook(mlx->win, ON_DESTROY, 0, exit_hook, 0);
	mlx_hook(mlx->win, ON_KEYDOWN, 0, key_down_hook, mlx);
	mlx_loop_hook(mlx->mlx, &display, mlx);
}
