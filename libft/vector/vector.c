/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 18:01:02 by vroche            #+#    #+#             */
/*   Updated: 2017/05/10 14:18:40 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	*vector_make(t_vector *v, uint64_t size, uint64_t type)
{
	if (!(v->ptr = malloc(size * type)))
		return (NULL);
	v->i = 0;
	v->max = size;
	v->type = type;
	return (v->ptr);
}

void	vector_delete(t_vector *v)
{
	free(v->ptr);
	v->ptr = NULL;
	v->i = 0;
	v->max = 0;
	v->type = 0;
}

void	*vector_realloc(t_vector *v)
{
	if (!(v->ptr = ft_realloc(v->ptr, v->max * v->type, v->max * v->type * 2)))
		return (NULL);
	v->max = v->max * 2;
	return (v->ptr);
}
