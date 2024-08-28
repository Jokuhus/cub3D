/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyehan <hyehan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:15:23 by jsuk              #+#    #+#             */
/*   Updated: 2024/08/22 14:44:08 by hyehan           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	ft_memset(&mlx, 0, sizeof(mlx));
	load_cub(&mlx, argc, argv);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, SCREENWIDTH, SCREENHEIGHT, argv[1]);
	set_data(&mlx);
	set_hook(&mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
