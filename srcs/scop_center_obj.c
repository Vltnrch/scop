/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_center_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 12:30:50 by vroche            #+#    #+#             */
/*   Updated: 2017/05/10 12:25:22 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		scop_center_obj_set(t_scop *scop, float *v)
{
	uint64_t	i;
	float		r;
	float		*p;
	uint64_t	size;

	i = 0;
	size = vector_size(&scop->obj.vertices);
	p = (float *)vector_get(&scop->obj.vertices, i);
	while (i < size)
	{
		r = p[0] - v[0];
		vector_set_pos(&scop->obj.vertices, i, &r);
		r = p[1] - v[1];
		vector_set_pos(&scop->obj.vertices, i + 1, &r);
		r = p[2] - v[2];
		vector_set_pos(&scop->obj.vertices, i + 2, &r);
		i += 3;
		p += 3;
	}
}

static float	scop_minpos_obj(t_scop *scop)
{
	uint64_t	i;
	uint64_t	size;
	float		*p;
	float		max;

	i = 0;
	max = 0.0f;
	size = vector_size(&scop->obj.vertices);
	p = (float *)vector_get(&scop->obj.vertices, i);
	while (i < size)
	{
		if (fabs(*p) > max)
			max = *p;
		i++;
		p++;
	}
	return (max);
}

float			scop_center_obj(t_scop *scop)
{
	float		v[3];
	uint64_t	i;
	uint64_t	size;
	float		*p;

	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	i = 0;
	size = vector_size(&scop->obj.vertices);
	p = (float *)vector_get(&scop->obj.vertices, i);
	while (i < size)
	{
		v[0] += p[0];
		v[1] += p[1];
		v[2] += p[2];
		i += 3;
		p += 3;
	}
	v[0] /= (size / 3);
	v[1] /= (size / 3);
	v[2] /= (size / 3);
	scop_center_obj_set(scop, v);
	return (scop_minpos_obj(scop));
}
