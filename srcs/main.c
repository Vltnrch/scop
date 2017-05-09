/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:09:46 by vroche            #+#    #+#             */
/*   Updated: 2017/05/08 12:16:48 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int	main(int ac, char **av)
{
	t_scop	scop;

	if (ac < 2 || ac > 3)
	{
		printf("usage: %s obj_file.obj [texture_file]\n", av[0]);
		return (-1);
	}
	scop_init(&scop, av);
	load_shaders(&scop);
	scop_loop(&scop);
	mlx_hook(scop.win, 2, 0, &scop_key_press, &scop);
	mlx_hook(scop.win, 3, 0, &scop_key_release, &scop);
	mlx_mouse_hook(scop.win, &scop_mouse_press, &scop);
	mlx_hook(scop.win, 5, 0, &scop_mouse_release, &scop);
	mlx_hook(scop.win, 6, 0, &scop_mouse_motion, &scop);
	mlx_loop_hook(scop.mlx, &scop_loop, &scop);
	mlx_loop(scop.mlx);
	return (0);
}
