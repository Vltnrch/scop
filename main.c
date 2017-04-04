/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:09:46 by vroche            #+#    #+#             */
/*   Updated: 2017/04/04 12:37:40 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"


int	main(int ac, char **av)
{
	t_scop	scop;

	scop_init(&scop);
	scop_loop(&scop);
	load_shaders(&scop);
	scop.gl.m_id = glGetUniformLocation(scop.gl.program_id, "M");
	scop.gl.v_id = glGetUniformLocation(scop.gl.program_id, "V");
	scop.gl.p_id = glGetUniformLocation(scop.gl.program_id, "P");
	scop.gl.ts_id = glGetUniformLocation(scop.gl.program_id, "TextureSampler");
	mlx_expose_hook(scop.win, &scop_expose, &scop);
	mlx_hook(scop.win, 2, 0, &scop_key_press, &scop);
	mlx_hook(scop.win, 3, 0, &scop_key_release, &scop);
	mlx_mouse_hook(scop.win, &scop_mouse_press, &scop);
	mlx_hook(scop.win, 5, 0, &scop_mouse_release, &scop);
	mlx_hook(scop.win, 6, 0, &scop_mouse_motion, &scop); 
	mlx_loop_hook(scop.mlx, &scop_loop, &scop);
	mlx_loop(scop.mlx);
	// Cleanup VBO and shader
	//glDeleteBuffers(1, &vertexbuffer);
	//glDeleteBuffers(1, &colorbuffer);
	//glDeleteProgram(scop->program_id);
	//glDeleteVertexArrays(1, &VertexArrayID);
	return (0);
}