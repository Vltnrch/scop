/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:17:40 by vroche            #+#    #+#             */
/*   Updated: 2017/03/24 12:44:03 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		key_hook(int keycode, t_scop *scop)
{ 
	if (keycode == 53 && scop)
		exit(0);
	return (0);
}

int		ft_expose(t_scop *scop)
{
	ft_printf("expose %x\n", scop);
	return (0);
}

void	ft_perror_exit(const char *str)
{
	ft_dprintf(2, "Error: %s\n", str);
	exit(EXIT_FAILURE);
}
