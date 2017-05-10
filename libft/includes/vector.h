/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 15:29:42 by vroche            #+#    #+#             */
/*   Updated: 2017/05/10 11:17:58 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "libft.h"

typedef struct		s_vector
{
	void			*ptr;
	uint64_t		i;
	uint64_t		max;
	uint64_t		type;
}					t_vector;

void				*vector_make(t_vector *v, uint64_t size, uint64_t type);
void				vector_delete(t_vector *v);
void				*vector_realloc(t_vector *v);
void				vector_set_pos(t_vector *v, uint64_t pos, void *set);
void				*vector_set(t_vector *v, void *set);
void				*vector_get(t_vector *v, uint64_t i);
uint64_t			vector_size(t_vector *v);

#endif
