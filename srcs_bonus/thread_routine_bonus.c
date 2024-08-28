/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyehan <hyehan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 07:45:34 by jsuk              #+#    #+#             */
/*   Updated: 2024/08/22 14:59:59 by hyehan           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d_bonus.h"

void	draw_wall_thread(t_mlx *mlx)
{
	t_dda	*dda;
	int		i;

	i = 0;
	start_wait_for_threads(&mlx->pool, mlx->pool.num_threads);
	while (i < mlx->pool.num_threads)
	{
		dda = (t_dda *)malloc(sizeof(t_dda));
		if (dda == 0)
		{
			thread_pool_shutdown(&mlx->pool);
			error_exit("error: cub3D: cannot allocate memory\n");
		}
		dda->mlx = mlx;
		dda->cur_pixel_x = SCREENWIDTH / mlx->pool.num_threads * i;
		dda->end_pixel_x = SCREENWIDTH / mlx->pool.num_threads * (i + 1);
		if (i == mlx->pool.num_threads - 1)
			dda->end_pixel_x = SCREENWIDTH;
		add_task(&mlx->pool, create_task(draw_wall_routine, dda));
		i++;
	}
	wait_for_threads(&mlx->pool);
}

void	draw_sprite_thread(t_mlx *mlx, t_dis_spt *dis, t_spt_data *data, int i)
{
	t_spt_dda	*dda;
	int			diff;

	diff = dis->draw_end_x - dis->draw_start_x;
	start_wait_for_threads(&mlx->pool, mlx->pool.num_threads);
	while (i < mlx->pool.num_threads)
	{
		dda = (t_spt_dda *)malloc(sizeof(t_spt_dda));
		if (dda == 0)
		{
			thread_pool_shutdown(&mlx->pool);
			error_exit("error: cub3D: cannot allocate memory\n");
		}
		dda->mlx = mlx;
		dda->data = data;
		dda->dis_spt = dis;
		dda->draw_start = dis->draw_start_x + diff / mlx->pool.num_threads * i;
		dda->draw_end = dis->draw_start_x + \
			(diff / mlx->pool.num_threads) * (i + 1);
		if (i == mlx->pool.num_threads - 1)
			dda->draw_end = dis->draw_end_x;
		add_task(&mlx->pool, create_task(draw_sprite_routine, dda));
		i++;
	}
	wait_for_threads(&mlx->pool);
}
