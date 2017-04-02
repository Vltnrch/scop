/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:10:10 by vroche            #+#    #+#             */
/*   Updated: 2017/03/31 19:54:05 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "matrix.h"
# include "vector.h"
# include "mlx.h"
# include "mlx_opengl.h"
# include <OpenGL/gl3.h>
# include "math.h"
# include <fcntl.h>
# include <sys/mman.h>

# define WIDTH 1024
# define HEIGHT 768

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESCAPE 53

# define MOUSE_L 1
# define MOUSE_R 2
# define MOUSE_M 3
# define MOUSE_SD 4
# define MOUSE_SU 5

// One color for each vertex. They were generated randomly.
/*static const GLfloat g_color_buffer_data[] = { 
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
};*/
static const GLfloat g_color_buffer_data[] = { 
	68 /255.0f, 68/255.0f, 68/255.0f,
	68 /255.0f, 68/255.0f, 68/255.0f,
	68 /255.0f, 68/255.0f, 68/255.0f,
	102/255.0f, 102/255.0f, 102/255.0f,
	102/255.0f, 102/255.0f, 102/255.0f,
	102/255.0f, 102/255.0f, 102/255.0f
};
typedef struct		s_gl
{
	GLuint			program_id;
	GLfloat			*projection;
	GLfloat			*view;
	GLfloat			*model;
	GLuint			m_id;
	GLuint			v_id;
	GLuint			p_id;
	GLuint			vertexbuffer;
	GLuint			colorbuffer;
}					t_gl;

typedef struct		s_mk
{
	char			key[128];
	char			mouse[6];
	int				x;
	int				y;
	int				xprev;
	int				yprev;
}					t_mk;

typedef struct		s_ctn
{
	void			*ctn;
	int				size;
	int				w;
}					t_ctn;

typedef struct		s_obj
{
	t_ctn			vertices;
	t_ctn			uvs;
	t_ctn			normals;
}					t_obj;

typedef struct		s_scop
{
	void			*mlx;
	void			*win;
	t_mk			mk;
	t_gl			gl;
	t_obj			obj;
	float			theta;
	float			phi;
	float			zoom;
}					t_scop;

int					scop_expose(t_scop *scop);
void				ft_perror_exit(const char *str);

int					scop_loop(t_scop *scop);

int					scop_key_release(int keycode, t_scop *scop);
int					scop_key_press(int keycode, t_scop *scop);

int					scop_mouse_release(int keycode, int x, int y, t_scop *scop);
int					scop_mouse_press(int keycode, int x, int y, t_scop *scop);
int					scop_mouse_motion(int x, int y, t_scop *scop);

void				make_ctn_f(t_ctn *ctn, int size);
void				realoc_ctn_f(t_ctn *ctn);
void				add_ctn_f(t_ctn *ctn, float add);
void				make_ctn(t_ctn *ctn, int size);
void				realoc_ctn(t_ctn *ctn);
void				add_ctn(t_ctn *ctn, unsigned int add);

void				scop_init(t_scop *scop);
void 				loadOBJ(char *path, t_scop * scop);

void				load_shaders(t_scop *scop);

#endif
