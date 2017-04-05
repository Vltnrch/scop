/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 14:21:31 by vroche            #+#    #+#             */
/*   Updated: 2017/04/05 15:57:50 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			scop_mouse_release(int keycode, int x, int y, t_scop *scop)
{
	scop->mk.mouse[keycode] = 0;
	return (0);
}

int			scop_mouse_press(int keycode, int x, int y, t_scop *scop)
{
	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
		return (1);
	scop->mk.mouse[keycode] = 1;
	return (0);
}

int			scop_mouse_motion(int x, int y, t_scop *scop)
{
	scop->mk.x = x;
	scop->mk.y = y;
	if (!scop->mk.mouse[MOUSE_L])
	{
		scop->mk.xprev = x;
		scop->mk.yprev = y;
	}
	return (0);
}
