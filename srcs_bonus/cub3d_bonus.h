/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:40:58 by hyehan            #+#    #+#             */
/*   Updated: 2024/08/18 15:40:05 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "struct_bonus.h"

/*setting*/
void	set_data(t_mlx *mlx);
void	set_hook(t_mlx *mlx);
int		mouse_click(int button, int x, int y, t_mlx *mlx);

/*rendering*/
int		display(t_mlx *mlx);
void	draw_mini_map(t_mlx *mlx);
void	draw_wall_routine(void *arg);
void	check_face(t_dis *dis, char **map);
void	draw_wall(t_dis *dis, t_mlx *mlx, int x, int y);
void	draw_mouse_poointer(t_mlx *mlx);
void	draw_sprite(t_spt *spt, t_plr *plr, t_mlx *mlx);

/*player_movement*/
void	rotate_player(t_plr *player, double rad);
void	move_fb_player(t_map *map, t_plr *player, double speed, char flag);
void	move_lr_player(t_map *map, t_plr *player, double speed, double rad);
void	mouse_rotation(t_mlx *mlx);
int		is_collided(t_map *map, double x, double y);

/*utils*/
void	error_exit(char *error_message);
void	free_char_arr(char **arr);
char	*strtrim_back(char *str, char c);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);
void	error_exit(char *err);

/*load_map*/
void	load_cub(t_mlx *mlx, int argc, char **argv);
void	read_cub(t_mlx *mlx, int fd);
char	*set_info(char *arr, char *element);
int		set_color(char *arr, int element);
void	read_map(t_mlx *mlx, char *line, int fd);
void	set_map(t_mlx *mlx, char *str);
void	check_map(t_map *map);

/*thread_task*/
void	init_thread(t_pool *pool);
void	thread_pool_shutdown(t_pool *pool);
void	start_wait_for_threads(t_pool *pool, int total_task);
void	wait_for_threads(t_pool *pool);
t_task	*create_task(void (*function)(void *), void *arg);
void	add_task(t_pool *pool, t_task *task);
t_task	*pop_task(t_pool *pool);

/*thread_routine*/
void	draw_wall_thread(t_mlx *mlx);
void	draw_sprite_thread(t_mlx *mlx, t_dis_spt *dis, t_spt_data *data, int i);

/*draw_sprite*/
void	draw_sprite_routine(void *arg);
void	sort_sprites_bubble(int *order, double *dist, int total);
void	calc_sprite_data(t_dis_spt *dis_spt, t_spt *spt, t_plr *plr, int i);
void	calc_sprite_draw(t_dis_spt *dis_spt);
void	draw_by_pixel(t_dis_spt *dis, t_mlx *mlx, int tex_x, int x);

#endif
