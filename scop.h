/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:10:10 by vroche            #+#    #+#             */
/*   Updated: 2017/03/27 20:13:47 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "libft.h"
# include "ft_printf.h"
# include "mlx.h"
# include "mlx_opengl.h"
# include <OpenGL/gl3.h>
# include "math.h"

# define WIDTH 1024
# define HEIGHT 768

typedef struct		s_scop
{
	void			*mlx;
	void			*win;
	GLuint			program_id;
	GLfloat			*projection;
	GLfloat			*view;
	GLfloat			*mvp;
	GLuint			mvp_id;
}					t_scop;

typedef struct		s_vect
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_vect;

int					key_hook(int keycode, t_scop *scop);
int					ft_expose(t_scop *scop);
void				ft_perror_exit(const char *str);

void				matx_delete_44(GLfloat *matx);
GLfloat				*matx_make_44(GLfloat v);
void				matx_print(GLfloat *v, char *str);
void				matx_dot(GLfloat *v, GLfloat *w, GLfloat *r);
GLfloat				*perspective(float fovy, float aspect, float zNear, float zFar);
GLfloat				*lookat(t_vect eye, t_vect center, t_vect up);

t_vect				vect_make(GLfloat x, GLfloat y, GLfloat z);
t_vect				normalize(t_vect v);
t_vect				cross(t_vect v, t_vect w);
t_vect				sub(t_vect v, t_vect w);
GLfloat				dot(t_vect v, t_vect w);

#endif
