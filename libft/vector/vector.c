/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 18:01:02 by vroche            #+#    #+#             */
/*   Updated: 2017/04/04 16:53:03 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	vector_make(t_vector *v, int size, int type)
{
	v->ptr = malloc(size * type);
	v->i = 0;
	v->max = size;
	v->type = type;
}

void	vector_delete(t_vector *v)
{
	free(v->ptr);
	v->ptr = NULL;
	v->i = 0;
	v->max = 0;
	v->type = 0;
}

void	vector_realloc(t_vector *v)
{
	v->ptr = ft_realloc(v->ptr, v->max * v->type, v->max * v->type * 2);
	v->max = v->max * 2;
}
