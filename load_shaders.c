/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_shaders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 11:45:10 by vroche            #+#    #+#             */
/*   Updated: 2017/03/31 20:07:22 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	err_shader(GLuint shader_id, int log_len)
{
	char	msg[256];

	glGetShaderInfoLog(shader_id, log_len, NULL, msg);
	printf("%s\n", msg);
	exit(-1);
}

static void	compile_shader(char *file, GLuint shader_id, char *err)
{
	GLint		result;
	int			log_len;
	int			fd;
	int			size;
	const char	*ptr;

	result = GL_FALSE;
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_perror_exit(err);
	if ((size = lseek(fd, 0, SEEK_END)) == -1)
		ft_perror_exit(err);
	if ((ptr = mmap(0, size, PROT_WRITE|PROT_READ,MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		ft_perror_exit(err);
	glShaderSource(shader_id, 1, &ptr , NULL);
	glCompileShader(shader_id);
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_len);
	if (log_len > 0)
		err_shader(shader_id, log_len);
	munmap((void *)ptr, size);
	close(fd);
}

static void	link_shader(t_scop *scop, GLuint vertex_id, GLuint fragment_id)
{
	GLint	result;
	int		log_len;

	result = GL_FALSE;
	scop->gl.program_id = glCreateProgram();
	glAttachShader(scop->gl.program_id, vertex_id);
	glAttachShader(scop->gl.program_id, fragment_id);
	glLinkProgram(scop->gl.program_id);
	glGetProgramiv(scop->gl.program_id, GL_LINK_STATUS, &result);
	glGetProgramiv(scop->gl.program_id, GL_INFO_LOG_LENGTH, &log_len);
	if (log_len > 0)
		err_shader(scop->gl.program_id, log_len);
	glDetachShader(scop->gl.program_id, vertex_id);
	glDetachShader(scop->gl.program_id, fragment_id);
	glDeleteShader(vertex_id);
	glDeleteShader(fragment_id);
}

void		load_shaders(t_scop *scop)
{
	GLuint	vertex_id;
	GLuint	fragment_id;

	vertex_id = glCreateShader(GL_VERTEX_SHADER);
	compile_shader("glsl/vertex_shader.glsl", vertex_id, "vertex_shader");
	fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
	compile_shader("glsl/fragment_shader.glsl", fragment_id, "fragment_shader");
	link_shader(scop, vertex_id, fragment_id);
}
