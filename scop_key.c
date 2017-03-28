/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 14:20:53 by vroche            #+#    #+#             */
/*   Updated: 2017/03/28 16:08:15 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			scop_key_release(int keycode, t_scop *scop)
{
	scop->mk.key[keycode] = 0;
	return (0);
}

int			scop_key_press(int keycode, t_scop *scop)
{
	scop->mk.key[keycode] = 1;
	return (0);
}
