/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 14:20:53 by vroche            #+#    #+#             */
/*   Updated: 2017/05/09 15:50:35 by vroche           ###   ########.fr       */
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
	if (scop->mk.key[keycode] == 0)
		scop->mk.key[keycode] = 1;
	return (0);
}

void		scop_key_event(t_scop *scop)
{
	static float speed = 0.03f;

	if (scop->mk.key[KEY_ESCAPE])
		exit(0);
	if (scop->mk.key[KEY_T] == 1)
	{
		scop->is_textured = !scop->is_textured ? 1 : 0;
		scop->mk.key[KEY_T] = 2;
	}
	if (scop->mk.key[KEY_UP] == 1)
		scop->pos.y += speed * scop->coef_zoom;
	if (scop->mk.key[KEY_DOWN] == 1)
		scop->pos.y -= speed * scop->coef_zoom;
	if (scop->mk.key[KEY_LEFT] == 1)
		scop->pos.x -= speed * scop->coef_zoom;
	if (scop->mk.key[KEY_RIGHT] == 1)
		scop->pos.x += speed * scop->coef_zoom;
	if (scop->mk.key[KEY_PLUS] == 1)
		scop->pos.z += speed * scop->coef_zoom;
	if (scop->mk.key[KEY_MOINS] == 1)
		scop->pos.z -= speed * scop->coef_zoom;
	if (scop->pos.z > 1)
		scop->pos.z = 1;
}
