/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 19:28:14 by jsuk              #+#    #+#             */
/*   Updated: 2024/08/18 15:39:46 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d_bonus.h"

void	draw_by_pixel(t_dis_spt *dis, t_mlx *mlx, int tex_x, int x)
{
	int	d;
	int	y;
	int	tex_y;
	int	color;

	y = dis->draw_start_y;
	while (y < dis->draw_end_y)
	{
		d = y * 256 - (SCREENHEIGHT * 128) + (dis->sprite_height * 128);
		tex_y = ((d * mlx->spt.tex[0].height) / \
			dis->sprite_height) / 256;
		if (tex_y < 0 || tex_y >= mlx->spt.tex[0].height || \
			tex_x < 0 || tex_x >= mlx->spt.tex[0].width)
		{
			y++;
			continue ;
		}
		if (dis->state < 50)
			color = mlx->spt.tex[0].texture[tex_y][tex_x];
		else
			color = mlx->spt.tex[1].texture[tex_y][tex_x];
		if ((color & 0x00FFFFFF) != 0x00FFFFFF)
			my_mlx_pixel_put(&mlx->frame, x, y, color);
		y++;
	}
}

void	calc_sprite_data(t_dis_spt *dis_spt, t_spt *spt, t_plr *plr, int i)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;

	sprite_x = spt->data[spt->order[i]].x - plr->pos_x;
	sprite_y = spt->data[spt->order[i]].y - plr->pos_y;
	inv_det = 1.0 / (plr->plane_x * plr->pdy - plr->pdx * plr->plane_y);
	transform_x = inv_det * (plr->pdy * sprite_x - plr->pdx * sprite_y);
	dis_spt->transform_y = inv_det * \
			(-plr->plane_y * sprite_x + plr->plane_x * sprite_y);
	dis_spt->sprite_screen_x = (int)((SCREENWIDTH / 2) * \
			(1 + transform_x / dis_spt->transform_y));
	dis_spt->sprite_height = abs((int)(SCREENHEIGHT / dis_spt->transform_y));
}

void	calc_sprite_draw(t_dis_spt *dis_spt)
{
	dis_spt->draw_start_y = -dis_spt->sprite_height / 2 + SCREENHEIGHT / 2;
	if (dis_spt->draw_start_y < 0)
		dis_spt->draw_start_y = 0;
	dis_spt->draw_end_y = dis_spt->sprite_height / 2 + SCREENHEIGHT / 2;
	if (dis_spt->draw_end_y >= SCREENHEIGHT)
		dis_spt->draw_end_y = SCREENHEIGHT - 1;
	dis_spt->draw_start_x = -dis_spt->sprite_height / 2 + \
		dis_spt->sprite_screen_x;
	if (dis_spt->draw_start_x < 0)
		dis_spt->draw_start_x = 0;
	dis_spt->draw_end_x = dis_spt->sprite_height / 2 + dis_spt->sprite_screen_x;
	if (dis_spt->draw_end_x >= SCREENWIDTH)
		dis_spt->draw_end_x = SCREENWIDTH - 1;
}

void	sort_sprites_bubble(int *order, double *dist, int total)
{
	int		i;
	int		count;
	int		temp_int;
	double	temp_double;

	count = 0;
	while (count < total - 1)
	{
		i = 0;
		while (i < total - count - 1)
		{
			if (dist[i] < dist[i + 1])
			{
				temp_double = dist[i + 1];
				dist[i + 1] = dist[i];
				dist[i] = temp_double;
				temp_int = order[i + 1];
				order[i + 1] = order[i];
				order[i] = temp_int;
			}
			i++;
		}
		count++;
	}
}
