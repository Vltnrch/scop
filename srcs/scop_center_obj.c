/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_center_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 12:30:50 by vroche            #+#    #+#             */
/*   Updated: 2017/05/15 13:36:28 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static float	scop_center_obj_putset(t_scop *scop, float *p, float *v, int i)
{
	static float	max = 0.0f;
	int				j;
	float			r;

	j = 0;
	while (j < 3)
	{
		r = p[j] - v[j];
		vector_set_pos(&scop->obj.vertices, i + j, &r);
		if (fabs(r) > max)
			max = r;
		j++;
	}
	return (max);
}

static float	scop_center_obj_set(t_scop *scop, float *v)
{
	uint64_t	i;
	float		*p;
	uint64_t	size;
	float		max;

	i = 0;
	size = vector_size(&scop->obj.vertices);
	p = (float *)vector_get(&scop->obj.vertices, i);
	while (i < size)
	{
		max = scop_center_obj_putset(scop, p, v, i);
		i += 3;
		p += 3;
	}
	return (max);
}

static void		scop_check_minmax(float *p, float *v)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (p[i] > v[i])
			v[i] = p[i];
		if (p[i] < v[i + 3])
			v[i + 3] = p[i];
		i++;
	}
}

float			scop_center_obj(t_scop *scop)
{
	float		v[6];
	uint64_t	i;
	uint64_t	size;
	float		*p;

	ft_bzero(v, 6 * sizeof(float));
	i = 0;
	size = vector_size(&scop->obj.vertices);
	p = (float *)vector_get(&scop->obj.vertices, i);
	while (i < size)
	{
		scop_check_minmax(p, v);
		i += 3;
		p += 3;
	}
	v[0] = (v[0] + v[3]) / 2.0f;
	v[1] = (v[1] + v[4]) / 2.0f;
	v[2] = (v[2] + v[5]) / 2.0f;
	return (scop_center_obj_set(scop, v));
}
