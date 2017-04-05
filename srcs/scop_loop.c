/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 12:41:08 by vroche            #+#    #+#             */
/*   Updated: 2017/04/05 17:09:06 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int		scop_draw(t_scop *scop)
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// VERTICES
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, scop->gl.vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	if (scop->is_textured)
	{
		// Use our shader
		glUseProgram(scop->gl.program_t_id);
		// give MVP to opengl
		glUniformMatrix4fv(glGetUniformLocation(scop->gl.program_t_id, "M"), 1, GL_FALSE, scop->gl.model.m);
		glUniformMatrix4fv(glGetUniformLocation(scop->gl.program_t_id, "V"), 1, GL_FALSE, scop->gl.view.m);
		glUniformMatrix4fv(glGetUniformLocation(scop->gl.program_t_id, "P"), 1, GL_FALSE, scop->gl.projection.m);
		glUniform1i(glGetUniformLocation(scop->gl.program_t_id, "TextureSampler"), 0);
		glUniform3f(glGetUniformLocation(scop->gl.program_t_id, "LightPosition_worldspace"), 2.0, 2.0, 20.0);
		// TEXTURES
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, scop->gl.texture_id);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, scop->gl.uvbuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
	else
	{
		// Use our shader
		glUseProgram(scop->gl.program_id);
		// give MVP to opengl
		glUniformMatrix4fv(glGetUniformLocation(scop->gl.program_id, "M"), 1, GL_FALSE, scop->gl.model.m);
		glUniformMatrix4fv(glGetUniformLocation(scop->gl.program_id, "V"), 1, GL_FALSE, scop->gl.view.m);
		glUniformMatrix4fv(glGetUniformLocation(scop->gl.program_id, "P"), 1, GL_FALSE, scop->gl.projection.m);
		glUniform3f(glGetUniformLocation(scop->gl.program_id, "LightPosition_worldspace"), 2.0, 2.0, 20.0);
		// COLORS
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, scop->gl.colorbuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, scop->gl.normalbuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	// Draw!
	glDrawArrays(GL_TRIANGLES, 0, vector_size(&scop->obj.vertices));
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	mlx_opengl_swap_buffers(scop->win);
	return (0);
}

static void		scop_key_event(t_scop *scop)
{
	if (scop->mk.key[KEY_ESCAPE])
		exit(0);
	else if (scop->mk.key[KEY_T] == 1)
	{
		scop->is_textured = !scop->is_textured ? 1 : 0;
		scop->mk.key[KEY_T] = 2;
	}
}

static void		scop_mouse_event(t_scop *scop)
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
	scop_draw(scop);
	return (0);
}
