/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_gen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 14:39:06 by vroche            #+#    #+#             */
/*   Updated: 2017/05/06 15:22:00 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

char	*scop_gen_color(t_scop *scop)
{
	char	*color;
	size_t	i;
	size_t	size;

	size = vector_size(&scop->obj.vertices) * sizeof(float);
	color = (char *)malloc(size);
	i = 0;
	while(i < size)
	{
		ft_memcpy(color + i, g_color_buffer_data, \
			size - i > sizeof(g_color_buffer_data) ? \
				sizeof(g_color_buffer_data) : size - i);
		i += sizeof(g_color_buffer_data);
	}
	return (color);
}

void		scop_gen_uvs(t_scop *scop)
{
	int		i;
	float	*p;

	i = 0;
	int	size = vector_size(&scop->obj.vertices);
	while (i < size)
	{
		p = (float *)vector_get(&scop->obj.vertices, i);

		//float	r = sqrt(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
		//float	theta = acos(p[2] / r);
		//float	phi = atan(p[1] / fabsf(p[0]));
		//vector_set(&scop->obj.uvs, &theta);
		//vector_set(&scop->obj.uvs, &phi);

		float ro = sqrt(p[0] * p[0] + p[1] * p[1]);
		float phi;
		phi = 0.0f;
		if (p[0] == 0.0f && p[1] == 0.0f)
			phi = 0.0f;
		else if (p[0] >= 0.0f)
			phi = asin(fabs(p[1]) / ro);
		else if (p[0] > 0.0f)
			phi = atan(fabs(p[1]) / p[0]);
		else if (p[0] < 0.0f)
			phi = -asin(fabs(p[1]) / ro) + M_PI;
		vector_set(&scop->obj.uvs, &phi);
		vector_set(&scop->obj.uvs, &(p[2]));

		//float	phi = atan2(p[1], fabs(p[0]));
		//vector_set(&scop->obj.uvs, &phi);
		//vector_set(&scop->obj.uvs, &(p[2]));

		i += 3;
	}
}

void		scop_gen_normals(t_scop *scop)
{
	int		i;
	float	*p;

	i = 0;
	int	size = vector_size(&scop->obj.vertices);
	while (i < size)
	{
		p = (float *)vector_get(&scop->obj.vertices, i);
		t_vec vec = vec_normalize( \
			vec_cross( \
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
	}
}
