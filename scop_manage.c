/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:17:40 by vroche            #+#    #+#             */
/*   Updated: 2017/03/28 16:29:25 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		scop_expose(t_scop *scop)
{

	// Model matrix : an identity matrix (model will be at the origin)
	//glm::mat4 Model = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	GLfloat			*mvp = mtx_make_44(0.0f);
	mtx_dot(scop->gl.view, scop->gl.projection, mvp);

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(scop->gl.mvp_id, 1, GL_FALSE, mvp);

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
	glBindBuffer(GL_ARRAY_BUFFER, scop->gl.colorbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);


	mlx_opengl_swap_buffers(scop->win);

	return (0);
}

int			scop_loop(t_scop *scop)
{
	static float speed = 0.1f; // 3 units / second
	static float horizontalAngle = 3.14f;
			// Initial vertical angle : none
	static float verticalAngle = 0.0f;
	static float mouseSpeed = 0.001f;

	// Compute new orientation
	horizontalAngle += mouseSpeed * (float)(scop->mk.x - scop->mk.xprev);
	verticalAngle   += mouseSpeed * (float)(scop->mk.y - scop->mk.yprev);
	scop->mk.xprev = scop->mk.x;
	scop->mk.yprev = scop->mk.y;
	t_vect	direction = vect_make(cos(verticalAngle) * sin(horizontalAngle), \
					sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));
	t_vect	right = vect_make(sin(horizontalAngle - 3.14f/2.0f), 0.0f,
					cos(horizontalAngle - 3.14f/2.0f));
	t_vect	up = vect_cross(right, direction);
	if (scop->mk.key[KEY_ESCAPE])
		exit(0);
	if (scop->mk.mouse[MOUSE_SU])
	{
		scop->position.x += direction.x /** deltaTime*/ * speed;
		scop->position.y += direction.y /** deltaTime*/ * speed;
		scop->position.z += direction.z /** deltaTime*/ * speed;
		scop->mk.mouse[MOUSE_SU] = 0;
	}
	if (scop->mk.mouse[MOUSE_SD])
	{
		scop->position.x -= direction.x /** deltaTime*/ * speed;
		scop->position.y -= direction.y /** deltaTime*/ * speed;
		scop->position.z -= direction.z /** deltaTime*/ * speed;
		scop->mk.mouse[MOUSE_SD] = 0;
	}
	if (scop->mk.key[KEY_UP])
	{
		scop->position.x += up.x /** deltaTime*/ * speed;
		scop->position.y += up.y /** deltaTime*/ * speed;
		scop->position.z += up.z /** deltaTime*/ * speed;
	}
	if (scop->mk.key[KEY_DOWN])
	{
		scop->position.x -= up.x /** deltaTime*/ * speed;
		scop->position.y -= up.y /** deltaTime*/ * speed;
		scop->position.z -= up.z /** deltaTime*/ * speed;
	}
	if (scop->mk.key[KEY_LEFT])
	{
		scop->position.x -= right.x /** deltaTime*/ * speed;
		scop->position.y -= right.y /** deltaTime*/ * speed;
		scop->position.z -= right.z /** deltaTime*/ * speed;
	}
	if (scop->mk.key[KEY_RIGHT])
	{
		scop->position.x += right.x /** deltaTime*/ * speed;
		scop->position.y += right.y /** deltaTime*/ * speed;
		scop->position.z += right.z /** deltaTime*/ * speed;
	}
	// Camera matrix
	free(scop->gl.view);
	scop->gl.view = mtx_lookat(scop->position, vect_add(scop->position, direction), up);
	scop_expose(scop);
	return (0);
}

void	ft_perror_exit(const char *str)
{
	ft_dprintf(2, "Error: %s\n", str);
	exit(EXIT_FAILURE);
}
