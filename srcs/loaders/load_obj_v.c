/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj_v.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 17:58:54 by vroche            #+#    #+#             */
/*   Updated: 2017/05/03 17:59:20 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	load_v(t_lobj *lobj, char **cut)
{
	int		count;
	int		convert[4];

	count = 1;
	while (count <= 4 && cut[count])
	{
		convert[(count - 1)] = atoi(cut[count]);
		if (count == 4)
		{
			vector_set(&lobj->vertex_id, &convert[0]);
			vector_set(&lobj->vertex_id, &convert[2]);
		}
		vector_set(&lobj->vertex_id, &convert[(count - 1)]);
		count++;
	}
}

static void	load_vn_part(t_vector *v, char **param, int count, int i)
{
	static int	convert[8];

	convert[(count - 1) * 2 + i] = atoi(param[i]);
	if (count == 4)
	{
		vector_set(v, &convert[0 + i]);
		vector_set(v, &convert[4 + i]);
	}
	vector_set(v, &convert[(count - 1) * 2 + i]);
}

void		load_vn(t_lobj *lobj, char **cut)
{
	char	**param;
	int		count;

	count = 1;
	while (count <= 4 && cut[count])
	{
		param = ft_strsplit(cut[count], '/');
		if (param[0])
			load_vn_part(&lobj->vertex_id, param, count, 0);
		if (param[1])
			load_vn_part(&lobj->normal_id, param, count, 1);
		count++;
		ft_freetab(param);
	}
}

static void	load_vun_part(t_vector *v, char **param, int count, int i)
{
	static int	convert[12];

	convert[(count - 1) * 3 + i] = atoi(param[i]);
	if (count == 4)
	{
		vector_set(v, &convert[0 + i]);
		vector_set(v, &convert[6 + i]);
	}
	vector_set(v, &convert[(count - 1) * 3 + i]);
}

void		load_vun(t_lobj *lobj, char **cut)
{
	char	**param;
	int		count;

	count = 1;
	while (count <= 4 && cut[count])
	{
		param = ft_strsplit(cut[count], '/');
		if (param[0])
			load_vun_part(&lobj->vertex_id, param, count, 0);
		if (param[1])
			load_vun_part(&lobj->uv_id, param, count, 1);
		if (param[2])
			load_vun_part(&lobj->normal_id, param, count, 2);
		count++;
		ft_freetab(param);
	}
}
