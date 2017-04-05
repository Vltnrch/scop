/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 12:25:06 by vroche            #+#    #+#             */
/*   Updated: 2017/04/05 12:25:11 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

//param v must be v[x y z]
float	vec_lenght(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

//param v and w must be v[x y z]
t_vec	vec_cross(t_vec v, t_vec w)
{
	return (vec_make(v.y * w.z - v.z * w.y, v.z * w.x - v.x * w.z, v.x * w.y - v.y * w.x));
}

//param v and w must be v[x y z]
t_vec	vec_sub(t_vec v, t_vec w)
{
	return (vec_make(v.x - w.x, v.y - w.y, v.z - w.z));
}

//param v and w must be v[x y z]
t_vec	vec_add(t_vec v, t_vec w)
{
	return (vec_make(v.x + w.x, v.y + w.y, v.z + w.z));
}

//param v and w must be v[x y z]
float	vec_dot(t_vec v, t_vec w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}