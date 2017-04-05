/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:10:10 by vroche            #+#    #+#             */
/*   Updated: 2017/04/05 16:43:35 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "mtx.h"
# include "vec.h"
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
# define KEY_T 17

# define MOUSE_L 1
# define MOUSE_R 2
# define MOUSE_M 3
# define MOUSE_SD 4
# define MOUSE_SU 5

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
	GLuint			program_t_id;
	GLuint			texture_id;
	t_mtx			projection;
	t_mtx			view;
	t_mtx			model;
	GLuint			vertexbuffer;
	GLuint			colorbuffer;
	GLuint			uvbuffer;
	GLuint			normalbuffer;
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

typedef struct		s_obj
{
	t_vector		vertices;
	t_vector		uvs;
	t_vector		normals;
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
	int				is_textured;
}					t_scop;

typedef struct		s_lobj
{
	t_vector		vertex_id;
	t_vector		uv_id;
	t_vector		normal_id;
	t_vector		temp_vertices;
	t_vector		temp_uvs;
	t_vector		normals;
}					t_lobj;

void				ft_perror_exit(const char *str);

int					scop_loop(t_scop *scop);

int					scop_key_release(int keycode, t_scop *scop);
int					scop_key_press(int keycode, t_scop *scop);

int					scop_mouse_release(int keycode, int x, int y, t_scop *scop);
int					scop_mouse_press(int keycode, int x, int y, t_scop *scop);
int					scop_mouse_motion(int x, int y, t_scop *scop);

void				scop_init(t_scop *scop, char **av);

void 				load_obj(t_scop * scop, char *path);

void 				load_bmp(t_scop *scop, char *file);

void				load_shaders(t_scop *scop);

void				scop_center_obj(t_scop *scop);
char				*scop_gen_color(t_scop *scop);
void				scop_gen_uvs(t_scop *scop);
void				scop_gen_normals(t_scop *scop);

#endif
