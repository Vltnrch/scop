/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 16:12:16 by vroche            #+#    #+#             */
/*   Updated: 2017/04/05 12:24:40 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec	vec_make(float x, float y, float z)
{
	t_vec	result;

	result.x = x;
	result.y = y;
	result.z = z;
	result.w = 1.0f;
	return (result);
}

//param v must be v[x y z]
t_vec	vec_normalize(t_vec v)
{
	float len = vec_lenght(v);

	return (vec_make(v.x / len, v.y / len, v.z / len));
}
