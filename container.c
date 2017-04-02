/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 18:01:02 by vroche            #+#    #+#             */
/*   Updated: 2017/03/29 18:31:19 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	make_ctn_f(t_ctn *ctn, int size)
{
	ctn->ctn = (float *)malloc(size * sizeof(float));
	ctn->w = 0;
	ctn->size = size;
}

void	realoc_ctn_f(t_ctn *ctn)
{
	ctn->ctn = ft_realloc(ctn->ctn, ctn->size * sizeof(float), ctn->size * sizeof(float) * 2);
	ctn->size = ctn->size * 2;
}

void	add_ctn_f(t_ctn *ctn, float add)
{
	if (ctn->w >= ctn->size)
		realoc_ctn_f(ctn);
	((float *)ctn->ctn)[ctn->w++] = add;
}

void	make_ctn(t_ctn *ctn, int size)
{
	ctn->ctn = (unsigned int *)malloc(size * sizeof(unsigned int));
	ctn->w = 0;
	ctn->size = size;
}

void	realoc_ctn(t_ctn *ctn)
{
	ctn->ctn = ft_realloc(ctn->ctn, ctn->size * sizeof(unsigned int), ctn->size * sizeof(unsigned int) * 2);
	ctn->size = ctn->size * 2;
}

void	add_ctn(t_ctn *ctn, unsigned int add)
{
	if (ctn->w >= ctn->size)
		realoc_ctn(ctn);
	((unsigned int *)ctn->ctn)[ctn->w++] = add;
}
