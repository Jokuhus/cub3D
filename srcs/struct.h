/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:07:55 by jsuk              #+#    #+#             */
/*   Updated: 2024/07/26 17:35:28 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define TRUE	1
# define FALSE	0
# define SCREENWIDTH 1640
# define SCREENHEIGHT 1080
# define MAPWIDTH 144
# define MAPHEIGHT 144

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef enum e_view
{
	NO,
	EA,
	SO,
	WE
}	t_view;

typedef struct s_dis
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		side;
	int		draw_start;
	int		draw_end;
	t_view	face;
}	t_dis;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_texture
{
	int	**texture;
	int	width;
	int	height;
}	t_texture;

typedef struct s_tex
{
	t_texture	no;
	t_texture	so;
	t_texture	we;
	t_texture	ea;
}	t_tex;

typedef struct s_map
{
	int		width;
	int		height;
	char	**map;
	int		idx;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f_color;
	int		c_color;
	int		pos_x;
	int		pos_y;
	t_view	view;
}	t_map;

typedef struct s_plr
{
	double	pos_x;
	double	pos_y;
	double	pdx;
	double	pdy;
	double	pa;
	double	plane_x;
	double	plane_y;
	int		z;
	int		nbr;
	int		jump;
}	t_plr;

typedef struct s_key
{
	char	w;
	char	a;
	char	s;
	char	d;
	char	left;
	char	right;
	char	space;
	char	shift;
}	t_key;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		map_x;
	int		map_y;
	t_img	frame;
	t_map	map;
	t_plr	player;
	t_tex	tex;
	t_key	key;
}	t_mlx;

#endif
