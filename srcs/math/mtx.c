/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:10:55 by vroche            #+#    #+#             */
/*   Updated: 2017/05/08 12:17:00 by vroche           ###   ########.fr       */
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

t_mtx	mtx_dot(t_mtx v, t_mtx w)
{
	int		i;
	t_mtx	r;

	r = mtx_make_44(1.0f);
	i = 0;
	while (i < 16)
	{
		r.m[i] = v.m[(i / 4) * 4] * w.m[i % 4] + \
			v.m[(i / 4) * 4 + 1] * w.m[(i % 4) + 4] + \
			v.m[(i / 4) * 4 + 2] * w.m[(i % 4) + 8] + \
			v.m[(i / 4) * 4 + 3] * w.m[(i % 4) + 12];
		i++;
	}
	return (r);
}

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
