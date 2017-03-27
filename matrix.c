/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:10:55 by vroche            #+#    #+#             */
/*   Updated: 2017/03/27 20:23:08 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	matx_delete_44(GLfloat *matx)
{
	free(matx);
}

GLfloat	*matx_make_44(GLfloat v)
{
	GLfloat	*result;
	int		i;

	result = (GLfloat *)malloc(16 * sizeof(GLfloat));
	i = 0;
	while (i < 16)
		result[i++] = 0.0f;
	result[15] = v;
	return (result);
}

void	matx_dot(GLfloat *v, GLfloat *w, GLfloat *r)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		r[i] = v[(i / 4) * 4] * w[i % 4] + v[(i / 4) * 4 + 1] * w[(i % 4) + 4] + v[(i / 4) * 4 + 2] * w[(i % 4) + 8] + v[(i / 4) * 4 + 3] * w[(i % 4) + 12];
		i++;
	}
}

void	matx_print(GLfloat *r, char *str)
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

GLfloat	*perspective(float fovy, float aspect, float zNear, float zFar)
{
	float	tanHalfFovy;
	GLfloat	*result;

	result = matx_make_44(0.0f);
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


GLfloat	*lookat(t_vect eye, t_vect center, t_vect up)
{
	t_vect	f = normalize(sub(center, eye));
	t_vect	s = normalize(cross(f, up));
	t_vect	u = cross(s, f);
	GLfloat	*result;

	result = matx_make_44(1.0f);
	result[0] = s.x;	//[0][0]
	result[4] = s.y;	//[1][0]
	result[8] = s.z;	//[2][0]
	result[1] = u.x;	//[0][1]
	result[5] = u.y;	//[1][1]
	result[9] = u.z;	//[2][1]
	result[2] = -f.x;	//[0][2]
	result[6] = -f.y;	//[1][2]
	result[10] = -f.z;	//[2][2]
	result[12] = -dot(s, eye);	//[3][0]
	result[13] = -dot(u, eye);	//[3][1]
	result[14] = dot(f, eye);	//[3][2]
	return (result);
}
