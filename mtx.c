/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:10:55 by vroche            #+#    #+#             */
/*   Updated: 2017/04/04 15:26:48 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mtx.h"

t_mtx	mtx_make_44(float v)
{
	t_mtx	result;
	int		i;

	i = 0;
	while (i < 16)
		result.m[i++] = 0.0f;
	result.m[0] = v;
	result.m[5] = v;
	result.m[10] = v;
	result.m[15] = v;
	return (result);
}

t_mtx mtx_dot(t_mtx v, t_mtx w)
{
	int	i;
	t_mtx	r;

	r = mtx_make_44(1.0f);
	i = 0;
	while (i < 16)
	{
		r.m[i] = v.m[(i / 4) * 4] * w.m[i % 4] + v.m[(i / 4) * 4 + 1] * w.m[(i % 4) + 4] + v.m[(i / 4) * 4 + 2] * w.m[(i % 4) + 8] + v.m[(i / 4) * 4 + 3] * w.m[(i % 4) + 12];
		i++;
	}
	return (r);
}

/*ATTENTION PRINT*/

void	mtx_print(t_mtx r, char *str)
{
	int	i;
	int	j;

	i = 0;
	printf("Matrix %s\n", str);
	while (i < 16)
	{
		j = 0;
		while (j < 4)
		{
			printf("%f ", r.m[i]);
			j++;
			i++;
		}
		printf("\n");
	}
	printf("---------------\n");
}

/*!!!!!!!!!!!!!!!*/

t_mtx	mtx_perspective(float fovy, float aspect, float zNear, float zFar)
{
	float	tanHalfFovy;
	t_mtx	result;

	result = mtx_make_44(0.0f);
	tanHalfFovy = tan(fovy / (float)2);
	result.m[0] = 1 / (aspect * tanHalfFovy);	//[0][0]
	result.m[5] = 1 / (tanHalfFovy);	//[1][1]
	result.m[11] = -1; //[2][3]
	result.m[10] = zFar / (zNear - zFar);	//[2][2]
	result.m[14] = -(zFar * zNear) / (zFar - zNear);	//[3][2]
	//result[2][2] = - (zFar + zNear) / (zFar - zNear);
	//result[3][2] = - (2 * zFar * zNear) / (zFar - zNear);
	return (result);
}


t_mtx	mtx_lookat(t_vec eye, t_vec center, t_vec up)
{
	t_vec	f = vec_normalize(vec_sub(center, eye));
	t_vec	s = vec_normalize(vec_cross(f, up));
	t_vec	u = vec_cross(s, f);
	t_mtx	result;

	result = mtx_make_44(1.0f);
	result.m[0] = s.x;	//[0][0]
	result.m[4] = s.y;	//[1][0]
	result.m[8] = s.z;	//[2][0]
	result.m[1] = u.x;	//[0][1]
	result.m[5] = u.y;	//[1][1]
	result.m[9] = u.z;	//[2][1]
	result.m[2] = -f.x;	//[0][2]
	result.m[6] = -f.y;	//[1][2]
	result.m[10] = -f.z;	//[2][2]
	result.m[12] = -vec_dot(s, eye);	//[3][0]
	result.m[13] = -vec_dot(u, eye);	//[3][1]
	result.m[14] = vec_dot(f, eye);	//[3][2]
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
	return result;
}

t_mtx	mtx_rotate(t_mtx m, float a, t_vec v)
{
	float c = cos(a);
	float s = sin(a);

	t_vec	axis = vec_normalize(v);
	t_vec	temp = vec_make((1.0f - c) * axis.x, (1.0f - c) * axis.y, (1.0f - c) * axis.z);

	t_mtx rotate = mtx_make_44(0.0f);
	rotate.m[0] = c + temp.x * axis.x;
	rotate.m[1] = temp.x * axis.y + s * axis.z;
	rotate.m[2] = temp.x * axis.z - s * axis.y;
	rotate.m[4] = temp.y * axis.x - s * axis.z;
	rotate.m[5] = c + temp.y * axis.y;
	rotate.m[6] = temp.y * axis.z + s * axis.x;
	rotate.m[8] = temp.z * axis.x + s * axis.y;
	rotate.m[9] = temp.z * axis.y - s * axis.x;
	rotate.m[10] = c + temp.z * axis.z;
	t_mtx result = mtx_make_44(0.0f);
	result.m[0] = m.m[0] * rotate.m[0] + m.m[4] * rotate.m[1] + m.m[8] * rotate.m[2];
	result.m[1] = m.m[1] * rotate.m[0] + m.m[5] * rotate.m[1] + m.m[9] * rotate.m[2];
	result.m[2] = m.m[2] * rotate.m[0] + m.m[6] * rotate.m[1] + m.m[10] * rotate.m[2];
	result.m[3] = m.m[3] * rotate.m[0] + m.m[7] * rotate.m[1] + m.m[11] * rotate.m[2];
	result.m[4] = m.m[0] * rotate.m[4] + m.m[4] * rotate.m[5] + m.m[8] * rotate.m[6];
	result.m[5] = m.m[1] * rotate.m[4] + m.m[5] * rotate.m[5] + m.m[9] * rotate.m[6];
	result.m[6] = m.m[2] * rotate.m[4] + m.m[6] * rotate.m[5] + m.m[10] * rotate.m[6];
	result.m[7] = m.m[3] * rotate.m[4] + m.m[7] * rotate.m[5] + m.m[11] * rotate.m[6];
	result.m[8] = m.m[0] * rotate.m[8] + m.m[4] * rotate.m[9] + m.m[8] * rotate.m[10];
	result.m[9] = m.m[1] * rotate.m[8] + m.m[5] * rotate.m[9] + m.m[9] * rotate.m[10];
	result.m[10] = m.m[2] * rotate.m[8] + m.m[6] * rotate.m[9] + m.m[10] * rotate.m[10];
	result.m[11] = m.m[3] * rotate.m[8] + m.m[7] * rotate.m[9] + m.m[11] * rotate.m[10];
	result.m[12] = m.m[12];
	result.m[13] = m.m[13];
	result.m[14] = m.m[14];
	result.m[15] = m.m[15];
	return result;
}
