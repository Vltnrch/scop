/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:17:40 by vroche            #+#    #+#             */
/*   Updated: 2017/05/15 13:36:54 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	scop_fps(void)
{
	static uint64_t	msprev = 0;
	static uint64_t	msmax = 0;
	static uint64_t	mscount = 0;
	uint64_t		msnow;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	msnow = (uint64_t)(tv.tv_sec) * 1000 + (uint64_t)(tv.tv_usec) / 1000;
	if (mscount > 100)
	{
		printf("\33[2K\r%f FPS", 1000 / (float)msmax);
		fflush(stdout);
		mscount = 0;
		msmax = 0;
	}
	if (msnow - msprev > msmax)
		msmax = msnow - msprev;
	mscount += msnow - msprev;
	msprev = msnow;
}

void	ft_perror_exit(const char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	ft_exit(const char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

void	ft_quit(t_scop *scop)
{
	glDeleteBuffers(1, &(scop->gl.vertexbuffer));
	glDeleteBuffers(1, &(scop->gl.colorbuffer));
	glDeleteBuffers(1, &(scop->gl.uvbuffer));
	glDeleteBuffers(1, &(scop->gl.normalbuffer));
	glDeleteProgram(scop->gl.program_t_id);
	glDeleteProgram(scop->gl.program_id);
	glDeleteTextures(1, &(scop->gl.texture_id));
	glDeleteVertexArrays(1, &(scop->gl.vertexarrayid));
	ft_putstr("\33[2K\r");
	exit(EXIT_SUCCESS);
}
