/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 17:04:32 by vroche            #+#    #+#             */
/*   Updated: 2017/05/10 16:44:46 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	scop_init_struct(t_scop *scop)
{
	scop->mk.x = 0;
	scop->mk.y = 0;
	scop->mk.xprev = 0;
	scop->mk.yprev = 0;
	scop->theta = 0.0f;
	scop->phi = 0.0f;
	scop->pos = vec_make(0.0f, 0.0f, 0.0f);
	scop->is_textured = 0;
	scop->gl.projection = mtx_perspective(45.0f, WIDTH / (float)HEIGHT, \
										0.1f, 10000.0f);
	scop->gl.model = mtx_make_44(1.0f);
	scop->gl.view = mtx_lookat(vec_make(0.0f, 0.0f, 1.0f), \
					vec_make(0.0f, 0.0f, 0.0f), vec_make(0.0f, 1.0f, 0.0f));
}

static void	scop_init_mlx(t_scop *scop)
{
	if (!(scop->mlx = mlx_init()))
		ft_exit("mlx_init() fails\n");
	if (!(scop->win = mlx_new_opengl_window(scop->mlx, WIDTH, HEIGHT, \
					"Scop / OpenGL")))
		ft_exit("mlx_new_window() fails to create a new window\n");
	mlx_opengl_window_set_context(scop->win);
	ft_bzero(&(scop->mk.key), 128 * sizeof(char));
	ft_bzero(&(scop->mk.mouse), 6 * sizeof(char));
}

static void	scop_init_gl(void)
{
	const GLubyte	*vendor;
	const GLubyte	*renderer;
	const GLubyte	*version;
	const GLubyte	*shading;
	GLuint			vertexarrayid;

	vendor = glGetString(GL_VENDOR);
	renderer = glGetString(GL_RENDERER);
	version = glGetString(GL_VERSION);
	shading = glGetString(GL_SHADING_LANGUAGE_VERSION);
	printf("Vendor: %s\n", vendor);
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);
	printf("OpenGL shading languade version supported %s\n", shading);
	glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glGenVertexArrays(1, &vertexarrayid);
	glBindVertexArray(vertexarrayid);
}

static void	scop_init_gl_buffer(t_scop *scop)
{
	glGenBuffers(1, &scop->gl.vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, scop->gl.vertexbuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBufferData(GL_ARRAY_BUFFER, \
		vector_size(&scop->obj.vertices) * sizeof(float), \
				(float *)vector_get(&scop->obj.vertices, 0), GL_STATIC_DRAW);
	glGenBuffers(1, &scop->gl.uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, scop->gl.uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, \
		vector_size(&scop->obj.uvs) * sizeof(float), \
				(float *)vector_get(&scop->obj.uvs, 0), GL_STATIC_DRAW);
	scop_gen_color(scop);
	glGenBuffers(1, &scop->gl.normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, scop->gl.normalbuffer);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBufferData(GL_ARRAY_BUFFER, \
		vector_size(&scop->obj.normals) * sizeof(float), \
				(float *)vector_get(&scop->obj.normals, 0), GL_STATIC_DRAW);
}

void		scop_init(t_scop *scop, char **av)
{
	load_obj(scop, av[1]);
	scop_init_struct(scop);
	scop_init_mlx(scop);
	scop_init_gl();
	if (av[2])
		load_texture(scop, av[2]);
	scop->pos.z = -scop_center_obj(scop) - 5;
	scop->coef_zoom = fabs(scop->pos.z / 5.0);
	if (!vector_size(&scop->obj.uvs))
		scop_gen_uvs(scop);
	if (!vector_size(&scop->obj.normals))
		scop_gen_normals(scop);
	scop_init_gl_buffer(scop);
}
