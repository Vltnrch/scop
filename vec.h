/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 10:47:57 by vroche            #+#    #+#             */
/*   Updated: 2017/04/04 14:48:55 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include "math.h"

typedef struct		s_vec
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_vec;

t_vec				vec_make(float x, float y, float z);
float				vec_lenght(t_vec v);
t_vec				vec_normalize(t_vec v);
t_vec				vec_cross(t_vec v, t_vec w);
t_vec				vec_sub(t_vec v, t_vec w);
t_vec				vec_add(t_vec v, t_vec w);
float				vec_dot(t_vec v, t_vec w);

#endif
