/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:09:46 by vroche            #+#    #+#             */
/*   Updated: 2017/03/28 16:04:13 by vroche           ###   ########.fr       */
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
	"layout(location = 1) in vec3 vertexColor;"
	"out vec3 fragmentColor;"
	"uniform mat4 MVP;"
	"void main() {"
	"	gl_Position = MVP * vec4(vertexPosition_modelspace,1);"
	"	fragmentColor = vertexColor;"
	"}";
	const char	*FragmentShaderCode = 
	"#version 410\n"
	"in vec3 fragmentColor;"
	"out vec3 color;"
	"void main() {"
	"	color = fragmentColor;"
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

void	scop_init(t_scop *scop)
{
	if (!(scop->mlx = mlx_init()))
		ft_perror_exit("mlx_init() fails\n");
	if (!(scop->win = mlx_new_opengl_window(scop->mlx, WIDTH, HEIGHT, "Scop / OpenGL 4.1")))
		ft_perror_exit("mlx_new_window() fails to create a new window\n");
	mlx_opengl_window_set_context(scop->win);

	ft_bzero(&(scop->mk.key), 128 * sizeof(char));
	ft_bzero(&(scop->mk.mouse), 6 * sizeof(char));
	scop->mk.x = 0;
	scop->mk.y = 0;
	scop->mk.xprev = 0;
	scop->mk.yprev = 0;
	scop->position = vect_make(0.0f, 0.0f, 10.0f); 
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	scop->gl.projection = mtx_perspective(45.0f, WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
	//glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around	
	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glGenBuffers(1, &scop->gl.vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, scop->gl.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &scop->gl.colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, scop->gl.colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
}



int	main(void)
{
	t_scop	scop;

	scop_init(&scop);
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	ft_printf("Renderer: %s\n", renderer);
	ft_printf("OpenGL version supported %s\n", version);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Create and compile our GLSL program from the shaders
	scop.gl.program_id = load_shaders();

	// Get a handle for our "MVP" uniform
	// Only during the initialisation
	scop.gl.mvp_id = glGetUniformLocation(scop.gl.program_id, "MVP");

	scop_loop(&scop);
	mlx_expose_hook(scop.win, &scop_expose, &scop);
	mlx_hook(scop.win, 2, 0, &scop_key_press, &scop);
	mlx_hook(scop.win, 3, 0, &scop_key_release, &scop);
	mlx_mouse_hook(scop.win, &scop_mouse_press, &scop);
	mlx_hook(scop.win, 5, 0, &scop_mouse_release, &scop);
	mlx_hook(scop.win, 6, 0, &scop_mouse_motion, &scop); 
	mlx_loop_hook(scop.mlx, &scop_loop, &scop);
	mlx_loop(scop.mlx);

	// Cleanup VBO and shader
	//glDeleteBuffers(1, &vertexbuffer);
	//glDeleteBuffers(1, &colorbuffer);
	//glDeleteProgram(scop->program_id);
	//glDeleteVertexArrays(1, &VertexArrayID);
	return (0);
}