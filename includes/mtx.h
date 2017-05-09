/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 10:53:00 by vroche            #+#    #+#             */
/*   Updated: 2017/05/08 13:07:54 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MTX_H
# define MTX_H

# include "math.h"
# include "vec.h"
# include "libft.h"
# include <stdio.h>

typedef struct		s_mtx
{
	float			m[16];
}					t_mtx;

t_mtx				mtx_make_44(float v);
t_mtx				mtx_dot(t_mtx v, t_mtx w);
t_mtx				mtx_perspective(float fovy, float aspect, \
									float znear, float zfar);
t_mtx				mtx_lookat(t_vec eye, t_vec center, t_vec up);
t_mtx				mtx_translate(t_mtx m, t_vec v);
t_mtx				mtx_rotate(t_mtx m, float a, t_vec v);

void				mtx_print(t_mtx r, char *str);

#endif
