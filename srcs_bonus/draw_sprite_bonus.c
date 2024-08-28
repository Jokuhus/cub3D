/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 07:48:10 by jsuk              #+#    #+#             */
/*   Updated: 2024/08/18 15:40:19 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d_bonus.h"

static void	update_sprite_distance(t_spt *spt, t_plr *plr, t_map *map)
{
	int		count;
	double	x;
	double	y;

	count = 0;
	while (count < spt->total)
	{
		x = spt->data[count].x;
		y = spt->data[count].y;
		if (x - plr->pos_x >= 0 && is_collided(map, x - 0.001, y))
			spt->data[count].x -= 0.001;
		else if (is_collided(map, x + 0.001, y))
			spt->data[count].x += 0.001;
		if (y - plr->pos_y >= 0 && is_collided(map, x, y - 0.001))
			spt->data[count].y -= 0.001;
		else if (is_collided(map, x, y + 0.001))
			spt->data[count].y += 0.001;
		spt->data[count].state++;
		if (spt->data[count].state >= 100)
			spt->data[count].state = 0;
		count++;
	}
}

void	draw_sprite_routine(void *arg)
{
	t_spt_dda	*dda;
	t_dis_spt	*dis;
	t_spt		*spt;
	int			tex_x;
	int			stripe;

	dda = (t_spt_dda *)arg;
	dis = dda->dis_spt;
	spt = &dda->mlx->spt;
	stripe = dda->draw_start;
	while (stripe < dda->draw_end)
	{
		tex_x = (256 * (stripe - (-dis->sprite_height / 2.0 + \
				dis->sprite_screen_x))) * spt->tex[0].width / \
				dis->sprite_height / 256.0;
		if (dis->transform_y > 0 && stripe > 0 && stripe < SCREENWIDTH && \
			dis->transform_y < spt->zbuffer[stripe])
			draw_by_pixel(dis, dda->mlx, tex_x, stripe);
		stripe++;
	}
	free(dda);
}

void	draw_sprite(t_spt *spt, t_plr *plr, t_mlx *mlx)
{
	int			i;
	t_dis_spt	dis_spt;

	update_sprite_distance(spt, plr, &mlx->map);
	i = 0;
	while (i < spt->total)
	{
		spt->order[i] = i;
		spt->dist[i] = (plr->pos_x - spt->data[i].x) * \
			(plr->pos_x - spt->data[i].x) + (plr->pos_y - spt->data[i].y) * \
			(plr->pos_y - spt->data[i].y);
		i++;
	}
	sort_sprites_bubble(spt->order, spt->dist, spt->total);
	i = 0;
	while (i < spt->total)
	{
		dis_spt.state = spt->data[spt->order[i]].state;
		calc_sprite_data(&dis_spt, spt, plr, i);
		calc_sprite_draw(&dis_spt);
		draw_sprite_thread(mlx, &dis_spt, &spt->data[spt->order[i]], 0);
		i++;
	}
}
