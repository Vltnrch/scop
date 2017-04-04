/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 15:29:42 by vroche            #+#    #+#             */
/*   Updated: 2017/04/04 16:53:28 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "libft.h"

typedef struct		s_vector
{
	void			*ptr;
	int				i;
	int				max;
	int				type;
}					t_vector;

void				vector_make(t_vector *v, int size, int type);
void				vector_delete(t_vector *v);
void				vector_realloc(t_vector *v);
void				vector_set_pos(t_vector *v, int pos, void *set);
void				vector_set(t_vector *v, void *set);
void				*vector_get(t_vector *v, int i);
int					vector_size(t_vector *v);

#endif
