/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 12:41:08 by vroche            #+#    #+#             */
/*   Updated: 2017/05/09 15:58:00 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static GLuint	getvar(GLuint program_id, char *var)
{
	return (glGetUniformLocation(program_id, var));
}

static void		scop_putvar(t_scop *scop, GLuint program_id)
{
	static float	offset = 0.0f;

	if (offset == 0.0f)
		offset = fabs(scop->pos.z);
	glUseProgram(program_id);
	glUniformMatrix4fv(getvar(program_id, "M"), 1, GL_FALSE, scop->gl.model.m);
	glUniformMatrix4fv(getvar(program_id, "V"), 1, GL_FALSE, scop->gl.view.m);
	glUniformMatrix4fv(getvar(program_id, "P"), 1, GL_FALSE, \
													scop->gl.projection.m);
	glUniform3f(getvar(program_id, "LightPosition_worldspace"), \
				1.0 + offset, 1.0 + offset, \
				1.0 + offset + scop->pos.z);
}

static void		scop_draw_tc(t_scop *scop, GLuint program_id, int is_t)
{
	static int	t = 1;

	scop_putvar(scop, program_id);
	if (is_t != t && is_t)
	{
		glDisableVertexAttribArray(1);
		glEnableVertexAttribArray(1);
		glUniform1i(getvar(program_id, "TextureSampler"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, scop->gl.texture_id);
		glBindBuffer(GL_ARRAY_BUFFER, scop->gl.uvbuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		t = is_t;
	}
	else if (is_t != t)
	{
		glDisableVertexAttribArray(1);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, scop->gl.colorbuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		t = is_t;
	}
}

static int		scop_draw(t_scop *scop)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (scop->is_textured)
		scop_draw_tc(scop, scop->gl.program_t_id, 1);
	else
		scop_draw_tc(scop, scop->gl.program_id, 0);
	glDrawArrays(GL_TRIANGLES, 0, vector_size(&scop->obj.vertices));
	mlx_opengl_swap_buffers(scop->win);
	return (0);
}

int				scop_loop(t_scop *scop)
{
	scop_mouse_event(scop);
	scop_key_event(scop);
	scop->gl.model = \
	mtx_rotate(\
		mtx_rotate(\
			mtx_translate(mtx_make_44(1.0f), scop->pos), \
			scop->phi, vec_make(1.0f, 0.0f, 0.0f)), \
		scop->theta, vec_make(0.0f, 1.0f, 0.0f));
	scop_draw(scop);
	return (0);
}
