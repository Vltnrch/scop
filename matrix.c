/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:10:55 by vroche            #+#    #+#             */
/*   Updated: 2017/03/24 13:29:26 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

//param v must be v[x y z]
GLfloat		*normalize(GLfloat *v)
{
	float len = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	GLfloat	result[3];

	result[0] = v[0] / len;
	result[1] = v[1] / len;
	result[2] = v[2] / len;
	return (result);
}

GLfloat		*perspective(float fovy, float aspect, float zNear, float zFar)
{
	float	tanHalfFovy ;
	GLfloat	result[4][4];

	ft_bzero(result, 4 * 4 * sizeof(GLfloat));
	tanHalfFovy = tan(fovy / (float)2);
	Result[0][0] = 1 / (aspect * tanHalfFovy);
	Result[1][1] = 1 / (tanHalfFovy);
	Result[2][3] = -1;
	result[2][2] = zFar / (zNear - zFar);
	result[3][2] = -(zFar * zNear) / (zFar - zNear);
	//result[2][2] = - (zFar + zNear) / (zFar - zNear);
	//result[3][2] = - (static_cast<T>(2) * zFar * zNear) / (zFar - zNear);
	return (result);
}

GLfloat		*lookat(GLfloat *eye, GLfloat *center, GLfloat *up)
{
	tvec3<T, P> const f(normalize(center - eye));
	tvec3<T, P> const s(normalize(cross(f, up)));
	tvec3<T, P> const u(cross(s, f));
	GLfloat	result[4][4];

	ft_bzero(result, 4 * 4 * sizeof(GLfloat));
	result[0][0] = s.x;
	result[1][0] = s.y;
	result[2][0] = s.z;
	result[0][1] = u.x;
	result[1][1] = u.y;
	result[2][1] = u.z;
	result[0][2] = -f.x;
	result[1][2] = -f.y;
	result[2][2] = -f.z;
	result[3][0] = -dot(s, eye);
	result[3][1] = -dot(u, eye);
	result[3][2] = dot(f, eye);
	return (result);
}