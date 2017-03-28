/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 10:53:00 by vroche            #+#    #+#             */
/*   Updated: 2017/03/28 10:58:53 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "math.h"
# include "vector.h"
# include "libft.h"

#include <stdio.h>

void	mtx_delete_44(float *mtx);
float	*mtx_make_44(float v);
void	mtx_dot(float *v, float *w, float *r);
float	*mtx_perspective(float fovy, float aspect, float zNear, float zFar);
float	*mtx_lookat(t_vect eye, t_vect center, t_vect up);

void	mtx_print(float *r, char *str);

#endif
