/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:07:55 by jsuk              #+#    #+#             */
/*   Updated: 2024/08/18 15:37:45 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_BONUS_H
# define STRUCT_BONUS_H

# include <pthread.h>

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
	char	door;
	t_view	face;
}	t_dis;

typedef struct s_dis_spt
{
	int		sprite_height;
	int		sprite_screen_x;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
	int		state;
	double	transform_y;
}	t_dis_spt;

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
	t_texture	door;
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
	char	*door;
	char	*mob0;
	char	*mob1;
	int		f_color;
	int		c_color;
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
}	t_plr;

typedef struct s_key
{
	char	w;
	char	a;
	char	s;
	char	d;
	char	left;
	char	right;
}	t_key;

typedef struct s_spt_data
{
	int			state;
	double		x;
	double		y;
}	t_spt_data;

typedef struct s_spt
{
	int			total;
	int			*order;
	double		*dist;
	double		zbuffer[SCREENWIDTH];
	t_texture	tex[2];
	t_spt_data	*data;
}	t_spt;

typedef struct s_task
{
	void			(*function)(void *);
	void			*arg;
	struct s_task	*next;
	struct s_task	*prev;
}	t_task;

typedef struct s_task_queue
{
	t_task	*head;
	t_task	*tail;
	int		size;
}	t_task_queue;

typedef struct s_pool
{
	pthread_t		*threads;
	t_task_queue	queue;
	int				num_threads;
	pthread_mutex_t	mutex;
	pthread_cond_t	condition;
	pthread_cond_t	synchronize;
	int				task_complete;
	int				total_task;
	char			shutdown;
}	t_pool;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	double	time;
	double	oldtime;
	double	frametime;
	int		map_x;
	int		map_y;
	t_img	frame;
	t_tex	tex;
	t_map	map;
	t_plr	player;
	t_key	key;
	t_spt	spt;
	t_pool	pool;
}	t_mlx;

typedef struct s_dda
{
	t_mlx	*mlx;
	int		cur_pixel_x;
	int		end_pixel_x;
}	t_dda;

typedef struct s_spt_dda
{
	t_mlx		*mlx;
	t_spt_data	*data;
	t_dis_spt	*dis_spt;
	int			draw_start;
	int			draw_end;
}	t_spt_dda;

#endif
