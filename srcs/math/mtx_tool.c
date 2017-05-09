/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_tool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 12:22:13 by vroche            #+#    #+#             */
/*   Updated: 2017/05/08 12:33:34 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mtx.h"

t_mtx	mtx_perspective(float fovy, float aspect, float znear, float zfar)
{
	float	tanhalffovy;
	t_mtx	result;

	result = mtx_make_44(0.0f);
	tanhalffovy = tan(fovy / (float)2);
	result.m[0] = 1 / (aspect * tanhalffovy);
	result.m[5] = 1 / (tanhalffovy);
	result.m[11] = -1;
	result.m[10] = zfar / (znear - zfar);
	result.m[14] = -(zfar * znear) / (zfar - znear);
	return (result);
}

t_mtx	mtx_lookat(t_vec eye, t_vec center, t_vec up)
{
	t_vec	f;
	t_vec	s;
	t_vec	u;
	t_mtx	result;

	result = mtx_make_44(1.0f);
	f = vec_normalize(vec_sub(center, eye));
	s = vec_normalize(vec_cross(f, up));
	u = vec_cross(s, f);
	result.m[0] = s.x;
	result.m[4] = s.y;
	result.m[8] = s.z;
	result.m[1] = u.x;
	result.m[5] = u.y;
	result.m[9] = u.z;
	result.m[2] = -f.x;
	result.m[6] = -f.y;
	result.m[10] = -f.z;
	result.m[12] = -vec_dot(s, eye);
	result.m[13] = -vec_dot(u, eye);
	result.m[14] = vec_dot(f, eye);
	return (result);
}

t_mtx	mtx_translate(t_mtx m, t_vec v)
{
	t_mtx	result;
	int		i;

	result = mtx_make_44(1.0f);
	i = 0;
	while (i < 12)
	{
		result.m[i] = m.m[i];
		i++;
	}
	result.m[12] = m.m[0] * v.x + m.m[4] * v.y + m.m[8] * v.z + m.m[12];
	result.m[13] = m.m[1] * v.x + m.m[5] * v.y + m.m[9] * v.z + m.m[13];
	result.m[14] = m.m[2] * v.x + m.m[6] * v.y + m.m[10] * v.z + m.m[14];
	result.m[15] = m.m[3] * v.x + m.m[7] * v.y + m.m[11] * v.z + m.m[15];
	return (result);
}

t_mtx	mtx_rotate_result(t_mtx m, t_mtx r)
{
	t_mtx result;

	result = mtx_make_44(0.0f);
	result.m[0] = m.m[0] * r.m[0] + m.m[4] * r.m[1] + m.m[8] * r.m[2];
	result.m[1] = m.m[1] * r.m[0] + m.m[5] * r.m[1] + m.m[9] * r.m[2];
	result.m[2] = m.m[2] * r.m[0] + m.m[6] * r.m[1] + m.m[10] * r.m[2];
	result.m[3] = m.m[3] * r.m[0] + m.m[7] * r.m[1] + m.m[11] * r.m[2];
	result.m[4] = m.m[0] * r.m[4] + m.m[4] * r.m[5] + m.m[8] * r.m[6];
	result.m[5] = m.m[1] * r.m[4] + m.m[5] * r.m[5] + m.m[9] * r.m[6];
	result.m[6] = m.m[2] * r.m[4] + m.m[6] * r.m[5] + m.m[10] * r.m[6];
	result.m[7] = m.m[3] * r.m[4] + m.m[7] * r.m[5] + m.m[11] * r.m[6];
	result.m[8] = m.m[0] * r.m[8] + m.m[4] * r.m[9] + m.m[8] * r.m[10];
	result.m[9] = m.m[1] * r.m[8] + m.m[5] * r.m[9] + m.m[9] * r.m[10];
	result.m[10] = m.m[2] * r.m[8] + m.m[6] * r.m[9] + m.m[10] * r.m[10];
	result.m[11] = m.m[3] * r.m[8] + m.m[7] * r.m[9] + m.m[11] * r.m[10];
	result.m[12] = m.m[12];
	result.m[13] = m.m[13];
	result.m[14] = m.m[14];
	result.m[15] = m.m[15];
	return (result);
}

t_mtx	mtx_rotate(t_mtx m, float a, t_vec v)
{
	float	c;
	float	s;
	t_vec	axis;
	t_vec	temp;
	t_mtx	rotate;

	c = cos(a);
	s = sin(a);
	axis = vec_normalize(v);
	temp = vec_make((1.0f - c) * axis.x, (1.0f - c) * axis.y, \
					(1.0f - c) * axis.z);
	rotate = mtx_make_44(0.0f);
	rotate.m[0] = c + temp.x * axis.x;
	rotate.m[1] = temp.x * axis.y + s * axis.z;
	rotate.m[2] = temp.x * axis.z - s * axis.y;
	rotate.m[4] = temp.y * axis.x - s * axis.z;
	rotate.m[5] = c + temp.y * axis.y;
	rotate.m[6] = temp.y * axis.z + s * axis.x;
	rotate.m[8] = temp.z * axis.x + s * axis.y;
	rotate.m[9] = temp.z * axis.y - s * axis.x;
	rotate.m[10] = c + temp.z * axis.z;
	return (mtx_rotate_result(m, rotate));
}
