/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 16:12:16 by vroche            #+#    #+#             */
/*   Updated: 2017/03/27 19:38:54 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_vect	vect_make(GLfloat x, GLfloat y, GLfloat z)
{
	t_vect	result;

	result.x = x;
	result.y = y;
	result.z = z;
	result.w = 1.0f;
	return (result);
}

//param v must be v[x y z]
t_vect	normalize(t_vect v)
{
	float len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	t_vect	result;

	result.x = v.x / len;
	result.y = v.y / len;
	result.z = v.z / len;
	return (result);
}

//param v and w must be v[x y z]
t_vect	cross(t_vect v, t_vect w)
{
	t_vect	result;

	result.x = v.y * w.z - v.z * w.y;
	result.y = v.z * w.x - v.x * w.z;
	result.z = v.x * w.y - v.y * w.x;
	return (result);
}

//param v and w must be v[x y z]
t_vect	sub(t_vect v, t_vect w)
{
	t_vect	result;

	result.x = v.x - w.x;
	result.y = v.y - w.y;
	result.z = v.z - w.z;
	return (result);
}

//param v and w must be v[x y z]
GLfloat		dot(t_vect v, t_vect w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}
