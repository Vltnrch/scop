/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:10:10 by vroche            #+#    #+#             */
/*   Updated: 2017/03/24 13:12:28 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "libft.h"
# include "ft_printf.h"
# include "mlx.h"
# include "mlx_opengl.h"
# include <OpenGL/gl3.h>
# include "math.h"

# define LENGHT 1024
# define HEIGHT 768

typedef struct		s_scop
{
	void			*mlx;
	void			*win;
}					t_scop;


int					key_hook(int keycode, t_scop *scop);
int					ft_expose(t_scop *scop);
void				ft_perror_exit(const char *str);

#endif
