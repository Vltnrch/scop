/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:10:55 by vroche            #+#    #+#             */
/*   Updated: 2017/03/29 12:44:55 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void	mtx_delete_44(float *matx)
{
	free(matx);
}

float	*mtx_make_44(float v)
{
	float	*result;
	int		i;

	result = (float *)malloc(16 * sizeof(float));
	i = 0;
	while (i < 16)
		result[i++] = 0.0f;
	result[0] = v;
	result[5] = v;
	result[10] = v;
	result[15] = v;
	return (result);
}

void	mtx_dot(float *v, float *w, float *r)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		r[i] = v[(i / 4) * 4] * w[i % 4] + v[(i / 4) * 4 + 1] * w[(i % 4) + 4] + v[(i / 4) * 4 + 2] * w[(i % 4) + 8] + v[(i / 4) * 4 + 3] * w[(i % 4) + 12];
		i++;
	}
}

/*ATTENTION PRINT*/

void	mtx_print(float *r, char *str)
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
			printf("%f ", r[i]);
			j++;
			i++;
		}
		printf("\n");
	}
	printf("---------------\n");
}

/*!!!!!!!!!!!!!!!*/

float	*mtx_perspective(float fovy, float aspect, float zNear, float zFar)
{
	float	tanHalfFovy;
	float	*result;

	result = mtx_make_44(0.0f);
	tanHalfFovy = tan(fovy / (float)2);
	result[0] = 1 / (aspect * tanHalfFovy);	//[0][0]
	result[5] = 1 / (tanHalfFovy);	//[1][1]
	result[11] = -1; //[2][3]
	result[10] = zFar / (zNear - zFar);	//[2][2]
	result[14] = -(zFar * zNear) / (zFar - zNear);	//[3][2]
	//result[2][2] = - (zFar + zNear) / (zFar - zNear);
	//result[3][2] = - (2 * zFar * zNear) / (zFar - zNear);
	return (result);
}


float	*mtx_lookat(t_vect eye, t_vect center, t_vect up)
{
	t_vect	f = vect_normalize(vect_sub(center, eye));
	t_vect	s = vect_normalize(vect_cross(f, up));
	t_vect	u = vect_cross(s, f);
	float	*result;

	result = mtx_make_44(1.0f);
	result[0] = s.x;	//[0][0]
	result[4] = s.y;	//[1][0]
	result[8] = s.z;	//[2][0]
	result[1] = u.x;	//[0][1]
	result[5] = u.y;	//[1][1]
	result[9] = u.z;	//[2][1]
	result[2] = -f.x;	//[0][2]
	result[6] = -f.y;	//[1][2]
	result[10] = -f.z;	//[2][2]
	result[12] = -vect_dot(s, eye);	//[3][0]
	result[13] = -vect_dot(u, eye);	//[3][1]
	result[14] = vect_dot(f, eye);	//[3][2]
	return (result);
}

float	*mtx_translate(float *m, t_vect v)
{
	float	*result;
	int		i;

	result = mtx_make_44(1.0f);
	i = 0;
	while (i < 12)
	{
		result[i] = m[i];
		i++;
	}
	result[12] = m[0] * v.x + m[4] * v.y + m[8] * v.z + m[12];
	result[13] = m[1] * v.x + m[5] * v.y + m[9] * v.z + m[13];
	result[14] = m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14];
	result[15] = m[3] * v.x + m[7] * v.y + m[11] * v.z + m[15];
	return result;
}

float	*mtx_rotate(float *m, float a, t_vect v)
{
	float c = cos(a);
	float s = sin(a);

	t_vect	axis = vect_normalize(v);
	t_vect	temp = vect_make((1.0f - c) * axis.x, (1.0f - c) * axis.y, (1.0f - c) * axis.z);

	float	*rotate = mtx_make_44(0.0f);
	rotate[0] = c + temp.x * axis.x;
	rotate[1] = temp.x * axis.y + s * axis.z;
	rotate[2] = temp.x * axis.z - s * axis.y;
	rotate[4] = temp.y * axis.x - s * axis.z;
	rotate[5] = c + temp.y * axis.y;
	rotate[6] = temp.y * axis.z + s * axis.x;
	rotate[8] = temp.z * axis.x + s * axis.y;
	rotate[9] = temp.z * axis.y - s * axis.x;
	rotate[10] = c + temp.z * axis.z;
	float	*result = mtx_make_44(0.0f);
	result[0] = m[0] * rotate[0] + m[4] * rotate[1] + m[8] * rotate[2];
	result[1] = m[1] * rotate[0] + m[5] * rotate[1] + m[9] * rotate[2];
	result[2] = m[2] * rotate[0] + m[6] * rotate[1] + m[10] * rotate[2];
	result[3] = m[3] * rotate[0] + m[7] * rotate[1] + m[11] * rotate[2];
	result[4] = m[0] * rotate[4] + m[4] * rotate[5] + m[8] * rotate[6];
	result[5] = m[1] * rotate[4] + m[5] * rotate[5] + m[9] * rotate[6];
	result[6] = m[2] * rotate[4] + m[6] * rotate[5] + m[10] * rotate[6];
	result[7] = m[3] * rotate[4] + m[7] * rotate[5] + m[11] * rotate[6];
	result[8] = m[0] * rotate[8] + m[4] * rotate[9] + m[8] * rotate[10];
	result[9] = m[1] * rotate[8] + m[5] * rotate[9] + m[9] * rotate[10];
	result[10] = m[2] * rotate[8] + m[6] * rotate[9] + m[10] * rotate[10];
	result[11] = m[3] * rotate[8] + m[7] * rotate[9] + m[11] * rotate[10];
	result[12] = m[12];
	result[13] = m[13];
	result[14] = m[14];
	result[15] = m[15];
	return result;
}
