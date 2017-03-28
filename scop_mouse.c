/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 14:21:31 by vroche            #+#    #+#             */
/*   Updated: 2017/03/28 16:08:45 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			scop_mouse_release(int keycode, int x, int y, t_scop *scop)
{
	(void)x;
	(void)y;
	scop->mk.mouse[keycode] = 0;
	return (0);
}

int			scop_mouse_press(int keycode, int x, int y, t_scop *scop)
{
	(void)x;
	(void)y;
	scop->mk.mouse[keycode] = 1;
	return (0);
}

int		scop_mouse_motion(int x, int y, t_scop *scop)
{
	scop->mk.x = x;
	scop->mk.y = y;
	if (!scop->mk.mouse[MOUSE_L])
	{
		scop->mk.xprev = x;
		scop->mk.yprev = y;
	}
	/*t_mdb	*mdb;

	mdb = env->mdb;
	if (mdb->mouse == 0)
		return (0);
	mdb->pr = (((2 * (double)y) / (double)WIDTH) - 1.7);
	mdb->pi = ((double)x / (double)HEIGHT);
	ft_julia(env, mdb);
	ft_expose_jla(env);*/
	return (0);
}
