/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 16:48:53 by vroche            #+#    #+#             */
/*   Updated: 2017/05/03 16:55:29 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	vector_set_pos(t_vector *v, int pos, void *set)
{
	if (pos >= v->max)
		return ;
	ft_memcpy(((char *)v->ptr + (pos * v->type)), set, v->type);
}

void	vector_set(t_vector *v, void *set)
{
	if (v->i >= v->max)
		vector_realloc(v);
	ft_memcpy(((char *)v->ptr + (v->i * v->type)), set, v->type);
	v->i += 1;
}

void	*vector_get(t_vector *v, int i)
{
	if (i >= v->max)
		return (NULL);
	return ((char *)v->ptr + (i * v->type));
}

int		vector_size(t_vector *v)
{
	return (v->i);
}
