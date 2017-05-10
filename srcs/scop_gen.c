/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_gen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 14:39:06 by vroche            #+#    #+#             */
/*   Updated: 2017/05/10 12:25:59 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	scop_gen_color(t_scop *scop)
{
	char		*color;
	uint64_t	i;
	uint64_t	size;

	size = vector_size(&scop->obj.vertices) * sizeof(float);
	color = (char *)malloc(size);
	i = 0;
	while (i < size)
	{
		ft_memcpy(color + i, g_color_buffer_data, \
			size - i > sizeof(g_color_buffer_data) ? \
				sizeof(g_color_buffer_data) : size - i);
		i += sizeof(g_color_buffer_data);
	}
	glGenBuffers(1, &scop->gl.colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, scop->gl.colorbuffer);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBufferData(GL_ARRAY_BUFFER, \
		vector_size(&scop->obj.vertices) * sizeof(float), color, \
				GL_STATIC_DRAW);
	free(color);
}

/*
**		float	r = sqrt(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
**		float	theta = acos(p[2] / r);
**		float	phi = atan(p[1] / fabsf(p[0]));
**		vector_set(&scop->obj.uvs, &theta);
**		vector_set(&scop->obj.uvs, &phi);
**
**		float	phi = atan2(p[1], fabs(p[0]));
**		vector_set(&scop->obj.uvs, &phi);
**		vector_set(&scop->obj.uvs, &(p[2]));
**
**		ro = sqrt(p[0] * p[0] + p[1] * p[1]);
**		phi = 0.0f;
**		if (p[0] == 0.0f && p[1] == 0.0f)
**			phi = 0.0f;
**		else if (p[0] >= 0.0f)
**			phi = asin(fabs(p[1]) / ro);
**		else if (p[0] > 0.0f)
**			phi = atan(fabs(p[1]) / p[0]);
**		else if (p[0] < 0.0f)
**			phi = -asin(fabs(p[1]) / ro) + M_PI;
**		vector_set(&scop->obj.uvs, &phi);
**		vector_set(&scop->obj.uvs, &(p[2]));
*/

void	scop_gen_uvs(t_scop *scop)
{
	uint64_t	i;
	float		*p;
	uint64_t	size;
	float		phi;

	i = 0;
	size = vector_size(&scop->obj.vertices);
	p = (float *)vector_get(&scop->obj.vertices, i);
	while (i < size)
	{
		phi = atan2(p[1], fabs(p[0]));
		vector_set(&scop->obj.uvs, &phi);
		vector_set(&scop->obj.uvs, &(p[2]));
		i += 3;
		p += 3;
	}
}

void	scop_gen_normals(t_scop *scop)
{
	uint64_t	i;
	float		*p;
	uint64_t	size;
	t_vec		vec;

	i = 0;
	size = vector_size(&scop->obj.vertices);
	p = (float *)vector_get(&scop->obj.vertices, i);
	while (i < size)
	{
		vec = vec_normalize(vec_cross(\
			vec_sub(vec_make(p[3], p[4], p[5]), vec_make(p[0], p[1], p[2])), \
			vec_sub(vec_make(p[6], p[7], p[8]), vec_make(p[0], p[1], p[2]))));
		vector_set(&scop->obj.normals, &vec.x);
		vector_set(&scop->obj.normals, &vec.y);
		vector_set(&scop->obj.normals, &vec.z);
		vector_set(&scop->obj.normals, &vec.x);
		vector_set(&scop->obj.normals, &vec.y);
		vector_set(&scop->obj.normals, &vec.z);
		vector_set(&scop->obj.normals, &vec.x);
		vector_set(&scop->obj.normals, &vec.y);
		vector_set(&scop->obj.normals, &vec.z);
		i += 9;
		p += 9;
	}
}
