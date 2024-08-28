/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyehan <hyehan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:08:40 by jsuk              #+#    #+#             */
/*   Updated: 2024/08/22 14:59:59 by hyehan           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "cub3d_bonus.h"

static void	load_image(void *mlx, char *file_path, t_texture *tex)
{
	t_img	img;

	img.img = mlx_xpm_file_to_image(mlx, file_path, &img.width, &img.height);
	if (img.img == 0)
		error_exit("error: cub3D: wrong texture\n");
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);
	tex->texture = (int **)malloc(sizeof(int *) * img.height);
	if (tex->texture == 0)
		error_exit("error: cub3D: cannot allocate memory\n");
	tex->height = 0;
	while (tex->height < img.height)
	{
		tex->texture[tex->height] = (int *)malloc(sizeof(int) * img.width);
		if (tex->texture[tex->height] == 0)
			error_exit("error: cub3D: cannot allocate memory\n");
		tex->width = 0;
		while (tex->width < img.width)
		{
			tex->texture[tex->height][tex->width] = *(unsigned int *)
				(img.addr + img.len * tex->height + tex->width * (img.bpp / 8));
			tex->width++;
		}
		tex->height++;
	}
	mlx_destroy_image(mlx, img.img);
}

void	set_mob_position(t_map *map, t_spt_data *data, int total)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (count < total && y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 'M')
			{
				data[count].y = y + 0.5;
				data[count].x = x + 0.5;
				data[count].state = ((x + y) % 2) * 50;
				map->map[y][x] = '0';
				count++;
			}
			x++;
		}
		y++;
	}
}

static void	load_texture(t_mlx *mlx)
{
	load_image(mlx->mlx, mlx->map.no, &mlx->tex.no);
	load_image(mlx->mlx, mlx->map.so, &mlx->tex.so);
	load_image(mlx->mlx, mlx->map.we, &mlx->tex.we);
	load_image(mlx->mlx, mlx->map.ea, &mlx->tex.ea);
	if (mlx->map.door)
		load_image(mlx->mlx, mlx->map.door, &mlx->tex.door);
	mlx->spt.order = (int *)malloc(sizeof(int) * mlx->spt.total);
	mlx->spt.dist = (double *)malloc(sizeof(double) * mlx->spt.total);
	if (mlx->spt.total)
	{
		mlx->spt.data = (t_spt_data *)malloc(sizeof(t_spt_data) \
			* mlx->spt.total);
		if (!mlx->spt.order || !mlx->spt.dist || !mlx->spt.data)
			error_exit("error: cub3D: cannot allocate memory\n");
		load_image(mlx->mlx, mlx->map.mob0, &mlx->spt.tex[0]);
		load_image(mlx->mlx, mlx->map.mob1, &mlx->spt.tex[1]);
		set_mob_position(&mlx->map, mlx->spt.data, mlx->spt.total);
	}
}

static void	set_player_face(t_mlx *mlx)
{
	mlx->player.pa = (int)mlx->map.view * M_PI_2;
	mlx->player.pdx = sin(mlx->player.pa);
	mlx->player.pdy = -cos(mlx->player.pa);
	mlx->player.plane_x = 0.66 * cos(mlx->player.pa);
	mlx->player.plane_y = 0.66 * sin(mlx->player.pa);
}

void	set_data(t_mlx *mlx)
{
	load_texture(mlx);
	mlx->player.pos_x += 0.2;
	mlx->player.pos_y += 0.2;
	set_player_face(mlx);
	mlx->key.w = 0;
	mlx->key.a = 0;
	mlx->key.s = 0;
	mlx->key.d = 0;
	mlx->key.left = 0;
	mlx->key.right = 0;
	mlx->map_x = 10;
	mlx->map_y = 10;
	mlx->oldtime = 0;
	mlx->time = 0;
	mlx->frametime = 0;
	mlx->frame.img = mlx_new_image(mlx->mlx, SCREENWIDTH, SCREENHEIGHT);
	mlx->frame.addr = mlx_get_data_addr(mlx->frame.img, &mlx->frame.bpp, \
		&mlx->frame.len, &mlx->frame.endian);
	mlx->frame.width = SCREENWIDTH;
	mlx->frame.height = SCREENHEIGHT;
}
