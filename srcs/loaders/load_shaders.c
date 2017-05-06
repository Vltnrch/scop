/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_shaders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 11:45:10 by vroche            #+#    #+#             */
/*   Updated: 2017/05/06 16:33:13 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		err_shader(GLuint shader_id, int log_len)
{
	char	msg[256];

	glGetShaderInfoLog(shader_id, log_len, NULL, msg);
	printf("%s\n", msg);
	exit(-1);
}

static void		compile_shader(char *file, GLuint shader_id, char *err)
{
	int			log_len;
	int			fd;
	int			size;
	const char	*ptr;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_perror_exit(err);
	if ((size = lseek(fd, 0, SEEK_END)) == -1)
		ft_perror_exit(err);
	if ((ptr = mmap(0, size, PROT_WRITE|PROT_READ,MAP_PRIVATE, fd, 0)) \
			== MAP_FAILED)
		ft_perror_exit(err);
	glShaderSource(shader_id, 1, &ptr , NULL);
	glCompileShader(shader_id);
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_len);
	if (log_len > 0)
		err_shader(shader_id, log_len);
	munmap((void *)ptr, size);
	close(fd);
}

static GLuint	link_shader(GLuint vertex_id, GLuint fragment_id)
{
	int		log_len;
	GLuint	p_id;

	p_id = glCreateProgram();
	glAttachShader(p_id, vertex_id);
	glAttachShader(p_id, fragment_id);
	glLinkProgram(p_id);
	glGetProgramiv(p_id, GL_INFO_LOG_LENGTH, &log_len);
	if (log_len > 0)
		err_shader(p_id, log_len);
	glDetachShader(p_id, vertex_id);
	glDetachShader(p_id, fragment_id);
	glDeleteShader(vertex_id);
	glDeleteShader(fragment_id);
	return (p_id);
}

void			load_shaders(t_scop *scop)
{
	GLuint	vertex_id;
	GLuint	fragment_id;

	vertex_id = glCreateShader(GL_VERTEX_SHADER);
	compile_shader("glsl/vertex_shader_t.glsl", vertex_id, \
					"vertex_shader_t");
	fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
	compile_shader("glsl/fragment_shader_t.glsl", fragment_id, \
					"fragment_shader_t");
	scop->gl.program_t_id = link_shader(vertex_id, fragment_id);
	vertex_id = glCreateShader(GL_VERTEX_SHADER);
	compile_shader("glsl/vertex_shader.glsl", vertex_id, \
					"vertex_shader");
	fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
	compile_shader("glsl/fragment_shader.glsl", fragment_id, \
					"fragment_shader");
	scop->gl.program_id = link_shader(vertex_id, fragment_id);
}
