/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:40:58 by hyehan            #+#    #+#             */
/*   Updated: 2024/07/18 11:10:13 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "struct.h"

/*setting*/
void	set_data(t_mlx *mlx);
void	set_hook(t_mlx *mlx);

/*rendering*/
int		display(t_mlx *mlx);
void	draw_mini_map(t_mlx *mlx);
void	draw_game_screen(t_mlx *mlx);
void	check_face(t_dis *dis);
void	draw_wall(t_dis *dis, t_mlx *mlx, int x, int y);

/*player_movement*/
void	player_movement(int key_value, t_mlx *mlx, double rad, double speed);

/*utils*/
void	error_exit(char *error_message);
void	free_char_arr(char **arr);
char	*strtrim_back(char *str, char c);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);
void	error_exit(char *err);

/*load_map*/
void	load_cub(t_mlx *mlx, int argc, char **argv);
void	read_cub(t_map *map, int fd);
char	*set_info(char *arr, char *element);
int		set_color(char *arr, int element);
void	read_map(t_map *map, char *line, int fd);
void	set_map(t_map *map, char *str);
void	check_map(t_map *map);

#endif
