/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 17:41:29 by vroche            #+#    #+#             */
/*   Updated: 2017/05/09 16:03:16 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	tidy_vertices_part(t_vector *v_id, t_vector *v_tmp, t_vector *v, \
																		int n)
{
	int				i;
	int				size;
	unsigned int	*a;
	float			*b;

	i = 0;
	size = vector_size(v_id);
	a = (unsigned int *)vector_get(v_id, i);
	while (i < size)
	{
		b = (float *)vector_get(v_tmp, ((*a - 1) * n));
		if (!b)
			ft_exit("Error in tidy_vertices");
		vector_set(v, &b[0]);
		vector_set(v, &b[1]);
		if (n == 3)
			vector_set(v, &b[2]);
		i++;
		a++;
	}
}

static void	tidy_vertices(t_scop *scop, t_lobj *lobj)
{
	vector_make(&scop->obj.vertices, 1024, sizeof(float));
	vector_make(&scop->obj.uvs, 1024, sizeof(float));
	vector_make(&scop->obj.normals, 1024, sizeof(float));
	tidy_vertices_part(&lobj->vertex_id, &lobj->temp_vertices, \
						&scop->obj.vertices, 3);
	tidy_vertices_part(&lobj->uv_id, &lobj->temp_uvs, &scop->obj.uvs, 2);
	tidy_vertices_part(&lobj->normal_id, &lobj->temp_normals, \
						&scop->obj.normals, 3);
	vector_delete(&lobj->vertex_id);
	vector_delete(&lobj->uv_id);
	vector_delete(&lobj->normal_id);
	vector_delete(&lobj->temp_vertices);
	vector_delete(&lobj->temp_uvs);
	vector_delete(&lobj->temp_normals);
}

static void	load_vertices(t_lobj *lobj, char **cut)
{
	t_vec	v;

	if (cut[1])
		v.x = atof(cut[1]);
	if (cut[1] && cut[2])
		v.y = atof(cut[2]);
	if (cut[1] && cut[2] && cut[3])
		v.z = atof(cut[3]);
	if (cut[0][1] == 't')
	{
		vector_set(&lobj->temp_uvs, &v.x);
		vector_set(&lobj->temp_uvs, &v.y);
	}
	else if (cut[0][1] == 'n')
	{
		vector_set(&lobj->temp_normals, &v.x);
		vector_set(&lobj->temp_normals, &v.y);
		vector_set(&lobj->temp_normals, &v.z);
	}
	else
	{
		vector_set(&lobj->temp_vertices, &v.x);
		vector_set(&lobj->temp_vertices, &v.y);
		vector_set(&lobj->temp_vertices, &v.z);
	}
}

static void	load_faces(t_lobj *lobj, char **cut, char *line)
{
	if (strstr(line, "//"))
		load_vn(lobj, cut);
	else if (strstr(line, "/"))
		load_vun(lobj, cut);
	else
		load_v(lobj, cut);
}

void		load_obj(t_scop *scop, char *path)
{
	t_lobj	lobj;
	int		fd;
	char	*line;
	char	**cut;

	vector_make(&lobj.vertex_id, 1024, sizeof(unsigned int));
	vector_make(&lobj.uv_id, 1024, sizeof(unsigned int));
	vector_make(&lobj.normal_id, 1024, sizeof(unsigned int));
	vector_make(&lobj.temp_vertices, 1024, sizeof(float));
	vector_make(&lobj.temp_uvs, 1024, sizeof(float));
	vector_make(&lobj.temp_normals, 1024, sizeof(float));
	if (!(fd = open(path, O_RDONLY)))
		ft_perror_exit("open .obj");
	while (get_next_line(fd, &line) > 0)
	{
		cut = ft_strsplit_space(line);
		if (*line == 'v')
			load_vertices(&lobj, cut);
		else if (*line == 'f')
			load_faces(&lobj, cut, line);
		free(line);
		ft_freetab(cut);
	}
	tidy_vertices(scop, &lobj);
}
