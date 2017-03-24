/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:09:46 by vroche            #+#    #+#             */
/*   Updated: 2017/03/24 13:04:34 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLuint	load_shaders(void)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const char	*VertexShaderCode = 
	"#version 410\n"
	"layout(location = 0) in vec3 vertexPosition_modelspace;"
	"uniform mat4 MVP;"
	"void main() {"
	"	gl_Position = vec4(vertexPosition_modelspace,1);"
	"}";
	const char	*FragmentShaderCode = 
	"#version 410\n"
	"out vec4 frag_colour;"
	"void main() {"
	"	frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
	"}";

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	ft_printf("Compiling shader \n");
	glShaderSource(VertexShaderID, 1, &VertexShaderCode , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		char	VertexShaderErrorMessage[256];
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, VertexShaderErrorMessage);
		ft_printf("%s\n", VertexShaderErrorMessage);
	}

	// Compile Fragment Shader
	ft_printf("Compiling shader \n");
	glShaderSource(FragmentShaderID, 1, &FragmentShaderCode , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		char	FragmentShaderErrorMessage[256];
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, FragmentShaderErrorMessage);
		printf("%s\n", FragmentShaderErrorMessage);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		char	ProgramErrorMessage[256];
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, ProgramErrorMessage);
		printf("%s\n", ProgramErrorMessage);
	}
	
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

void	ft_scop(t_scop *scop)
{

	//Init VAO
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
	 0.0f,  0.5f,  0.0f,
	 0.5f, -0.5f,  0.0f,
	-0.5f, -0.5f,  0.0f
	};


	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);

	mlx_opengl_swap_buffers(scop->win);

}

int	main(void)
{
	t_scop	scop;

	if (!(scop.mlx = mlx_init()))
		ft_perror_exit("mlx_init() fails\n");
	if (!(scop.win = mlx_new_opengl_window(scop.mlx, LENGHT, HEIGHT, "Scop / OpenGL 4.1")))
		ft_perror_exit("mlx_new_window() fails to create a new window\n");
	mlx_opengl_window_set_context(scop.win);

	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	ft_printf("Renderer: %s\n", renderer);
	ft_printf("OpenGL version supported %s\n", version);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Create and compile our GLSL program from the shaders
	GLuint programID = load_shaders();
	glUseProgram(programID);
	ft_scop(&scop);

	mlx_expose_hook(scop.win, ft_expose, &scop);
	mlx_key_hook(scop.win, key_hook, &scop);
	mlx_loop(scop.mlx);

	return (0);
}