/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 10:47:57 by vroche            #+#    #+#             */
/*   Updated: 2017/03/28 10:50:36 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "math.h"

typedef struct		s_vect
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_vect;

t_vect				vect_make(float x, float y, float z);
float				vect_lenght(t_vect v);
t_vect				vect_normalize(t_vect v);
t_vect				vect_cross(t_vect v, t_vect w);
t_vect				vect_sub(t_vect v, t_vect w);
t_vect				vect_add(t_vect v, t_vect w);
float				vect_dot(t_vect v, t_vect w);

#endif
