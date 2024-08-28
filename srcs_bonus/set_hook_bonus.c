/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hook_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:35:03 by jsuk              #+#    #+#             */
/*   Updated: 2024/08/18 15:34:22 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "cub3d_bonus.h"

static int	exit_hook(t_mlx *mlx)
{
	thread_pool_shutdown(&mlx->pool);
	exit(0);
	return (0);
}

static int	key_up_hook(int key_value, t_mlx *mlx)
{
	if (key_value == 53 || key_value == 12)
	{
		thread_pool_shutdown(&mlx->pool);
		exit(0);
	}
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
	return (0);
}

static int	key_down_hook(int key_value, t_key *key)
{
	if (key_value == 0)
		key->a = 1;
	else if (key_value == 1)
		key->s = 1;
	else if (key_value == 2)
		key->d = 1;
	else if (key_value == 13)
		key->w = 1;
	else if (key_value == 123)
		key->left = 1;
	else if (key_value == 124)
		key->right = 1;
	return (0);
}

void	set_hook(t_mlx *mlx)
{
	mlx_mouse_hide();
	mlx_mouse_move(mlx->win, SCREENWIDTH / 2, SCREENHEIGHT / 2);
	mlx_mouse_hook(mlx->win, mouse_click, mlx);
	mlx_key_hook(mlx->win, key_up_hook, mlx);
	mlx_hook(mlx->win, ON_DESTROY, 0, exit_hook, mlx);
	mlx_hook(mlx->win, ON_KEYDOWN, 0, key_down_hook, &mlx->key);
	mlx_loop_hook(mlx->mlx, &display, mlx);
}
