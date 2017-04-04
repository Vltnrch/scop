/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 17:04:32 by vroche            #+#    #+#             */
/*   Updated: 2017/04/04 17:01:33 by vroche           ###   ########.fr       */
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
	scop->gl.view = mtx_lookat(vec_make(0.0f, 0.0f, 20.0f), vec_make(0.0f, 0.0f, 0.0f), vec_make(0.0f, 1.0f, 0.0f));
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

	size = vector_size(&scop->obj.vertices) * sizeof(float);
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
	int	size = vector_size(&scop->obj.vertices);
	float	*p;
	while (i < size)
	{
		p = (float *)vector_get(&scop->obj.vertices, i);
		v[0] += p[0];
		v[1] += p[1];
		v[2] += p[2];
		i += 3;
	}
	v[0] /= (size / 3);
	v[1] /= (size / 3);
	v[2] /= (size / 3);
	i = 0;
	float r;
	while (i < size)
	{
		p = (float *)vector_get(&scop->obj.vertices, i);
		r = p[0] - v[0];
		vector_set_pos(&scop->obj.vertices, i, &r);
		r = p[1] - v[1];
		vector_set_pos(&scop->obj.vertices, i + 1, &r);
		r = p[2] - v[2];
		vector_set_pos(&scop->obj.vertices, i + 2, &r);
		i += 3;
	}
}

static void loadBMP(t_scop *scop, const char *file)
{
	printf("Reading image %s\n", file);
	// Data read from the header of the BMP file
	unsigned short width, height;
	// Actual RGB data
	char *data;
	// Open the file
	int	fd;
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_perror_exit("open() BMP");
	int	size;
	if ((size = lseek(fd, 0, SEEK_END)) == -1)
		ft_perror_exit("lseek() BMP");
	char *ptr;
	if ((ptr = mmap(0, size, PROT_WRITE|PROT_READ,MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		ft_perror_exit("mmap() BMP");
	// Read the header, i.e. the 54 first bytes
	// A BMP files always begins with "BM"
	if (ptr[0]!='B' || ptr[1]!='M' )
		ft_perror_exit("Not a correct BMP file\n");
	// Make sure this is a 24bpp file
	if (*(int *)&(ptr[0x1E]) != 0)
		ft_perror_exit("Not a correct BMP file\n");
	if (*(int *)&(ptr[0x1C]) != 24)
		ft_perror_exit("Not a correct BMP file\n");
	// Read the information about the image
	width      = *(unsigned short*)&(ptr[0x12]);
	height     = *(unsigned short*)&(ptr[0x16]);
	printf("datapos %d / imagesize %d / width %d / height %d\n", *(int*)&(ptr[0x0A]), *(int*)&(ptr[0x22]), width, height);
	// Some BMP files are misformatted, guess missing information
	// Create a buffer
	data = ptr + *(int*)&(ptr[0x0A]);
	// Create one OpenGL texture
	glGenTextures(1, &scop->gl.texture_id);
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, scop->gl.texture_id);
	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	// Poor filtering, or ...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	// ... nice trilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glGenerateMipmap(GL_TEXTURE_2D);
}

void		scop_gen_uvs(t_scop *scop)
{
	int		i;
	float	*p;

	i = 0;
	int	size = vector_size(&scop->obj.vertices);
	while (i < size)
	{
		p = (float *)vector_get(&scop->obj.vertices, i);

		float	r = sqrt(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
		float	theta = acos(p[2] / r);
		float	phi = atan(p[1] / fabsf(p[0]));
		vector_set(&scop->obj.uvs, &theta);
		vector_set(&scop->obj.uvs, &phi);

		//float ro = sqrt(p[0] * p[0] + p[1] * p[1]);
		//float phi;
		//phi = 0.0f;
		//if (p[0] == 0.0f && p[1] == 0.0f)
		//	phi = 0.0f;
		//else if (p[0] >= 0.0f)
		//	phi = asin(fabs(p[1]) / ro);
		//else if (p[0] > 0.0f)
		//	phi = atan(fabs(p[1]) / p[0]);
		//else if (p[0] < 0.0f)
		//	phi = -asin(fabs(p[1]) / ro) + M_PI;
		//vector_set(&scop->obj.uvs, &phi);
		//vector_set(&scop->obj.uvs, &(p[2]));

		//float	phi = atan2(p[1], fabs(p[0]));
		//vector_set(&scop->obj.uvs, &phi);
		//vector_set(&scop->obj.uvs, &(p[2]));

		i += 3;
	}
}

void		scop_init(t_scop *scop)
{
	char	*color;

	loadOBJ("./teapot.obj", scop);
	scop_center_obj(scop);
	scop_init_struct(scop);
	scop_init_mlx(scop);
	scop_init_gl(scop);
	color = scop_init_color(scop);
	loadBMP(scop, "./img.bmp");
	scop_gen_uvs(scop);
	// Load it into a VBO
	glGenBuffers(1, &scop->gl.vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, scop->gl.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vector_size(&scop->obj.vertices) * sizeof(float), (float *)vector_get(&scop->obj.vertices, 0), GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	//glGenBuffers(1, &scop->gl.colorbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, scop->gl.colorbuffer);
	//glBufferData(GL_ARRAY_BUFFER, vector_size(&scop->obj.vertices) * sizeof(float), color, GL_STATIC_DRAW);

	glGenBuffers(1, &scop->gl.uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, scop->gl.uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, vector_size(&scop->obj.uvs) * sizeof(float), (float *)vector_get(&scop->obj.uvs, 0), GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	free(color);
	//vector_delete(&scop->obj.vertices);
	//vector_delete(&scop->obj.uvs);
	//vector_delete(&scop->obj.normals);
}
