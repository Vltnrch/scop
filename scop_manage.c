/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:17:40 by vroche            #+#    #+#             */
/*   Updated: 2017/04/04 16:28:52 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		scop_expose(t_scop *scop)
{

	// in the "MVP" uniform
	glUniformMatrix4fv(scop->gl.m_id, 1, GL_FALSE, scop->gl.model.m);
	glUniformMatrix4fv(scop->gl.v_id, 1, GL_FALSE, scop->gl.view.m);
	glUniformMatrix4fv(scop->gl.p_id, 1, GL_FALSE, scop->gl.projection.m);
	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, scop->gl.texture_id);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(scop->gl.ts_id, 0);
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Use our shader
	glUseProgram(scop->gl.program_id);
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, scop->gl.vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	//glBindBuffer(GL_ARRAY_BUFFER, scop->gl.colorbuffer);
	//glVertexAttribPointer(
	//	1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
	//	3,                                // size
	//	GL_FLOAT,                         // type
	//	GL_FALSE,                         // normalized?
	//	0,                                // stride
	//	(void*)0                          // array buffer offset
	//);
	glBindBuffer(GL_ARRAY_BUFFER, scop->gl.uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
	// Draw the triangle !

	glDrawArrays(GL_TRIANGLES, 0, vector_size(&scop->obj.vertices));

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	mlx_opengl_swap_buffers(scop->win);
	return (0);
}

void		scop_key_event(t_scop *scop)
{
	if (scop->mk.key[KEY_ESCAPE])
		exit(0);
}

void		scop_mouse_event(t_scop *scop)
{
	static float mouseSpeed = 0.1f;

	if (scop->mk.y != scop->mk.yprev || scop->mk.x != scop->mk.xprev)
	{
		scop->phi += mouseSpeed * (float)(scop->mk.y - scop->mk.yprev);
		scop->theta += mouseSpeed * (float)(scop->mk.x - scop->mk.xprev);
		scop->mk.xprev = scop->mk.x;
		scop->mk.yprev = scop->mk.y;
	}
	if (scop->phi > M_PI / 2)
		scop->phi = M_PI / 2;
	if (scop->phi < -M_PI / 2)
		scop->phi = -M_PI / 2;
	if (scop->mk.mouse[MOUSE_SD])
		scop->zoom -= mouseSpeed * 5;
	else if (scop->mk.mouse[MOUSE_SU])
		scop->zoom += mouseSpeed * 5;
	scop->mk.mouse[MOUSE_SD] = 0;
	scop->mk.mouse[MOUSE_SU] = 0;
}

int			scop_loop(t_scop *scop)
{
	t_mtx	result;

	scop_mouse_event(scop);
	scop_key_event(scop);
	result = mtx_make_44(1.0f);
	scop->gl.model = mtx_translate(result, vec_make(0.0f, 0.0f, 1.0f + scop->zoom));
	result = mtx_rotate(scop->gl.model, scop->phi, vec_make(1.0f, 0.0f, 0.0f));
	scop->gl.model = mtx_rotate(result, scop->theta, vec_make(0.0f, 1.0f, 0.0f));
	scop_expose(scop);
	return (0);
}

void	ft_perror_exit(const char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
