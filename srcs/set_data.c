/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
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
#include "cub3d.h"

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

static void	load_texture(t_mlx *mlx)
{
	load_image(mlx->mlx, mlx->map.no, &mlx->tex.no);
	load_image(mlx->mlx, mlx->map.so, &mlx->tex.so);
	load_image(mlx->mlx, mlx->map.we, &mlx->tex.we);
	load_image(mlx->mlx, mlx->map.ea, &mlx->tex.ea);
}

static void	set_player_face(t_mlx *mlx)
{
	mlx->player.pa = (int)mlx->map.view * M_PI_2;
	mlx->player.pdx = sin(mlx->player.pa);
	mlx->player.pdy = -cos(mlx->player.pa);
	mlx->player.plane_x = 0.66 * cos(mlx->player.pa);
	mlx->player.plane_y = 0.66 * sin(mlx->player.pa);
	mlx->player.z = 0;
	mlx->player.nbr = 0;
	mlx->player.jump = 0;
}

static void	set_key(t_key *key)
{
	key->w = 0;
	key->a = 0;
	key->s = 0;
	key->d = 0;
	key->left = 0;
	key->right = 0;
	key->space = 0;
	key->shift = 0;
}

void	set_data(t_mlx *mlx)
{
	load_texture(mlx);
	mlx->player.pos_x = mlx->map.pos_x + 0.2;
	mlx->player.pos_y = mlx->map.pos_y + 0.2;
	set_player_face(mlx);
	set_key(&mlx->key);
	mlx->map_x = 10;
	mlx->map_y = 10;
	mlx->frame.img = mlx_new_image(mlx->mlx, SCREENWIDTH, SCREENHEIGHT);
	mlx->frame.addr = mlx_get_data_addr(mlx->frame.img, &mlx->frame.bpp, \
		&mlx->frame.len, &mlx->frame.endian);
	mlx->frame.width = SCREENWIDTH;
	mlx->frame.height = SCREENHEIGHT;
}
