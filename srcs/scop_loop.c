/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 12:41:08 by vroche            #+#    #+#             */
/*   Updated: 2017/05/06 17:35:51 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		scop_draw_tc(t_scop *scop, GLuint program_id, int is_t)
{
	// Use our shader
	glUseProgram(program_id);
	// give MVP to opengl
	glUniformMatrix4fv(glGetUniformLocation(program_id, "M"), 1, GL_FALSE, scop->gl.model.m);
	glUniformMatrix4fv(glGetUniformLocation(program_id, "V"), 1, GL_FALSE, scop->gl.view.m);
	glUniformMatrix4fv(glGetUniformLocation(program_id, "P"), 1, GL_FALSE, scop->gl.projection.m);
	glUniform3f(glGetUniformLocation(program_id, "LightPosition_worldspace"), 5.0, 5.0, 10.0 + scop->pos.z);
	glEnableVertexAttribArray(1);
	if (is_t)
	{
		glUniform1i(glGetUniformLocation(program_id, "TextureSampler"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, scop->gl.texture_id);
		glBindBuffer(GL_ARRAY_BUFFER, scop->gl.uvbuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, scop->gl.colorbuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
}

static int		scop_draw(t_scop *scop)
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// VERTICES
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, scop->gl.vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	if (scop->is_textured)
		scop_draw_tc(scop, scop->gl.program_t_id, 1);
	else
		scop_draw_tc(scop, scop->gl.program_id, 0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, scop->gl.normalbuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, vector_size(&scop->obj.vertices));
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	mlx_opengl_swap_buffers(scop->win);
	return (0);
}

int			scop_loop(t_scop *scop)
{
	scop_mouse_event(scop);
	scop_key_event(scop);
	scop->gl.model = 
	mtx_rotate(
		mtx_rotate(
			mtx_translate(mtx_make_44(1.0f), scop->pos), 
		scop->phi, vec_make(1.0f, 0.0f, 0.0f)), 
	scop->theta, vec_make(0.0f, 1.0f, 0.0f));
	scop_draw(scop);
	return (0);
}
