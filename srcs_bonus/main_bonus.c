/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuk <jsuk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:15:23 by jsuk              #+#    #+#             */
/*   Updated: 2024/08/17 08:55:52 by jsuk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "cub3d_bonus.h"

int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	ft_memset(&mlx, 0, sizeof(mlx));
	load_cub(&mlx, argc, argv);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, SCREENWIDTH, \
		SCREENHEIGHT, argv[1]);
	set_data(&mlx);
	init_thread(&mlx.pool);
	set_hook(&mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
