/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 17:04:32 by vroche            #+#    #+#             */
/*   Updated: 2017/03/31 20:16:54 by vroche           ###   ########.fr       */
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
	scop->zoom = 0.0f;
	scop->gl.projection = mtx_perspective(45.0f, WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	scop->gl.model = mtx_make_44(1.0f);
	scop->gl.view = mtx_lookat(vect_make(0.0f, 0.0f, 20.0f), vect_make(0.0f, 0.0f, 0.0f), vect_make(0.0f, 1.0f, 0.0f));
}

static void	scop_init_mlx(t_scop *scop)
{
	if (!(scop->mlx = mlx_init()))
		ft_perror_exit("mlx_init() fails\n");
	if (!(scop->win = mlx_new_opengl_window(scop->mlx, WIDTH, HEIGHT, "Scop / OpenGL 4.1")))
		ft_perror_exit("mlx_new_window() fails to create a new window\n");
	mlx_opengl_window_set_context(scop->win);
	ft_bzero(&(scop->mk.key), 128 * sizeof(char));
	ft_bzero(&(scop->mk.mouse), 6 * sizeof(char));
}

static void	scop_init_gl(t_scop * scop)
{
	const GLubyte	*vendor = glGetString(GL_VENDOR);
	const GLubyte	*renderer = glGetString(GL_RENDERER);
	const GLubyte	*version = glGetString(GL_VERSION);
	const GLubyte	*shading = glGetString(GL_SHADING_LANGUAGE_VERSION);
	GLuint			VertexArrayID;

	ft_printf("Vendor: %s\n", vendor);
	ft_printf("Renderer: %s\n", renderer);
	ft_printf("OpenGL version supported %s\n", version);
	ft_printf("OpenGL shading languade version supported %s\n", shading);
	glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
}

static char	*scop_init_color(t_scop *scop)
{
	char	*color;
	size_t	i;
	size_t	size;

	size = scop->obj.vertices.w * sizeof(float);
	color = (char *)malloc(size);
	i = 0;
	while(i < size)
	{
		ft_memcpy(color + i, g_color_buffer_data, size - i > sizeof(g_color_buffer_data) ? sizeof(g_color_buffer_data) : size - i);
		i += sizeof(g_color_buffer_data);
	}
	return (color);
}

static void	scop_center_obj(t_scop *scop)
{
	float	v[3];
	int		i;

	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	i = 0;
	while (i < scop->obj.vertices.w)
	{
		v[0] += ((float *)(scop->obj.vertices.ctn))[i];
		v[1] += ((float *)(scop->obj.vertices.ctn))[i + 1];
		v[2] += ((float *)(scop->obj.vertices.ctn))[i + 2];
		i += 3;
	}
	v[0] /= (scop->obj.vertices.w / 3);
	v[1] /= (scop->obj.vertices.w / 3);
	v[2] /= (scop->obj.vertices.w / 3);
	i = 0;
	while (i < scop->obj.vertices.w)
	{
		((float *)(scop->obj.vertices.ctn))[i] -= v[0];
		((float *)(scop->obj.vertices.ctn))[i + 1] -= v[1];
		((float *)(scop->obj.vertices.ctn))[i + 2] -= v[2];
		i += 3;
	}
}

void		scop_init(t_scop *scop)
{
	char	*color;

	loadOBJ("./42.obj", scop);
	scop_center_obj(scop);
	scop_init_struct(scop);
	scop_init_mlx(scop);
	scop_init_gl(scop);
	color = scop_init_color(scop);
	// Load it into a VBO
	glGenBuffers(1, &scop->gl.vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, scop->gl.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, scop->obj.vertices.w * sizeof(float), scop->obj.vertices.ctn, GL_STATIC_DRAW);
	glGenBuffers(1, &scop->gl.colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, scop->gl.colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, scop->obj.vertices.w * sizeof(float), color, GL_STATIC_DRAW);
	free(color);
	free(scop->obj.vertices.ctn);
	free(scop->obj.uvs.ctn);
	free(scop->obj.normals.ctn);
}
