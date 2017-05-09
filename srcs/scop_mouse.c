/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 14:21:31 by vroche            #+#    #+#             */
/*   Updated: 2017/05/09 16:04:15 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			scop_mouse_release(int keycode, int x, int y, t_scop *scop)
{
	x = y;
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

void		scop_mouse_event(t_scop *scop)
{
	static float speed = 0.1f;

	if (scop->mk.y != scop->mk.yprev || scop->mk.x != scop->mk.xprev)
	{
		scop->phi += speed * (float)(scop->mk.y - scop->mk.yprev);
		scop->theta += speed * (float)(scop->mk.x - scop->mk.xprev);
		scop->mk.xprev = scop->mk.x;
		scop->mk.yprev = scop->mk.y;
	}
	if (scop->phi > M_PI / 2)
		scop->phi = M_PI / 2;
	if (scop->phi < -M_PI / 2)
		scop->phi = -M_PI / 2;
	if (scop->mk.mouse[MOUSE_SD])
		scop->pos.z -= speed * 5 * scop->coef_zoom;
	else if (scop->mk.mouse[MOUSE_SU])
	{
		scop->pos.z += speed * 5 * scop->coef_zoom;
		if (scop->pos.z > 1)
			scop->pos.z = 1;
	}
	scop->mk.mouse[MOUSE_SD] = 0;
	scop->mk.mouse[MOUSE_SU] = 0;
}
