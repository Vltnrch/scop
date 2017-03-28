/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 16:12:16 by vroche            #+#    #+#             */
/*   Updated: 2017/03/28 10:53:31 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vect	vect_make(float x, float y, float z)
{
	t_vect	result;

	result.x = x;
	result.y = y;
	result.z = z;
	result.w = 1.0f;
	return (result);
}
//param v must be v[x y z]
float	vect_lenght(t_vect v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

//param v must be v[x y z]
t_vect	vect_normalize(t_vect v)
{
	float len = vect_lenght(v);

	return (vect_make(v.x / len, v.y / len, v.z / len));
}

//param v and w must be v[x y z]
t_vect	vect_cross(t_vect v, t_vect w)
{
	return (vect_make(v.y * w.z - v.z * w.y, v.z * w.x - v.x * w.z, v.x * w.y - v.y * w.x));
}

//param v and w must be v[x y z]
t_vect	vect_sub(t_vect v, t_vect w)
{
	return (vect_make(v.x - w.x, v.y - w.y, v.z - w.z));
}

//param v and w must be v[x y z]
t_vect	vect_add(t_vect v, t_vect w)
{
	return (vect_make(v.x + w.x, v.y + w.y, v.z + w.z));
}

//param v and w must be v[x y z]
float		vect_dot(t_vect v, t_vect w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}
