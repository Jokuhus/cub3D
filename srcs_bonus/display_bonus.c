/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyehan <hyehan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:53:18 by jsuk              #+#    #+#             */
/*   Updated: 2024/08/22 14:59:59 by hyehan           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <sys/time.h>
#include "mlx.h"
#include "libft.h"
#include "cub3d_bonus.h"

static void	clear_image(t_img *frame)
{
	int	x;
	int	y;

	y = 0;
	while (y < frame->height)
	{
		x = 0;
		while (x < frame->width)
		{
			my_mlx_pixel_put(frame->img, x, y, 0);
			x++;
		}
		y++;
	}
}

static void	move_camera_player(t_mlx *mlx)
{
	if (mlx->key.w && !mlx->key.s)
		move_fb_player(&mlx->map, &mlx->player, mlx->frametime, 1);
	if (mlx->key.s && !mlx->key.w)
		move_fb_player(&mlx->map, &mlx->player, mlx->frametime, 0);
	if (mlx->key.a && !mlx->key.d)
		move_lr_player(&mlx->map, &mlx->player, mlx->frametime, 3 * M_PI_2);
	if (mlx->key.d && !mlx->key.a)
		move_lr_player(&mlx->map, &mlx->player, mlx->frametime, M_PI_2);
	if (mlx->key.left && !mlx->key.right)
		rotate_player(&mlx->player, -mlx->frametime);
	if (mlx->key.right && !mlx->key.left)
		rotate_player(&mlx->player, mlx->frametime);
	mouse_rotation(mlx);
}

static void	calculate_fps(t_mlx *mlx)
{
	struct timeval	time;
	char			*fps_str;
	char			*win_str;
	double			fps;

	if (gettimeofday(&time, 0))
		error_exit("error: cub3D: failed to get current time\n");
	mlx->oldtime = mlx->time;
	mlx->time = time.tv_sec * 1000 + time.tv_usec / 1000;
	mlx->frametime = (mlx->time - mlx->oldtime) / 1000;
	fps = 1 / mlx->frametime;
	fps_str = ft_itoa((int)fps);
	if (!fps_str)
		error_exit("error: cub3D: cannot allocate memory\n");
	win_str = ft_strjoin("FPS: ", fps_str);
	if (!win_str)
		error_exit("error: cub3D: cannot allocate memory\n");
	free(fps_str);
	mlx_string_put(mlx->mlx, mlx->win, SCREENWIDTH - 50, 15, 0, win_str);
	free(win_str);
}

int	display(t_mlx *mlx)
{
	move_camera_player(mlx);
	clear_image(&mlx->frame);
	draw_wall_thread(mlx);
	draw_sprite(&mlx->spt, &mlx->player, mlx);
	draw_mini_map(mlx);
	draw_mouse_poointer(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win,
		mlx->frame.img, 0, 0);
	calculate_fps(mlx);
	return (0);
}
