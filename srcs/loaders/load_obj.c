/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 17:41:29 by vroche            #+#    #+#             */
/*   Updated: 2017/04/20 17:05:44 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*static void	obj_print(t_ctn *temp_vertices)
{
	int	i;
	int	j;

	i = 0;
	while (i < temp_vertices->w)
	{
		j = 0;
		while (j < 3)
		{
			printf("%f ", ((float *)temp_vertices->ctn)[i + j++]);
		}
		printf("\n");
		i += 3;
	}
}*/

static void	tidy_vertices(t_scop *scop, t_lobj *lobj)
{
	int i;

	vector_make(&scop->obj.vertices, 1024, sizeof(float));
	vector_make(&scop->obj.uvs, 1024, sizeof(float));
	vector_make(&scop->obj.normals, 1024, sizeof(float));
	i = 0;
	int	size = vector_size(&lobj->vertex_id);
	while (i < size)
	{
		unsigned int	a = *(unsigned int *)vector_get(&lobj->vertex_id, i);
		float			*b = (float *)vector_get(&lobj->temp_vertices, ((a - 1) * 3));
		vector_set(&scop->obj.vertices, &b[0]);
		vector_set(&scop->obj.vertices, &b[1]);
		vector_set(&scop->obj.vertices, &b[2]);
		i++;
	}
	i = 0;
	size = vector_size(&lobj->uv_id);
	while (i < size)
	{
		unsigned int	a = *(unsigned int *)vector_get(&lobj->uv_id, i);
		float			*b = (float *)vector_get(&lobj->temp_uvs, ((a - 1) * 2));
		vector_set(&scop->obj.uvs, &b[0]);
		vector_set(&scop->obj.uvs, &b[1]);
		i++;
	}
	i = 0;
	size = vector_size(&lobj->normal_id);
	while (i < size)
	{
		unsigned int	a = *(unsigned int *)vector_get(&lobj->normal_id, i);
		float			*b = (float *)vector_get(&lobj->temp_normals, ((a - 1) * 3));
		vector_set(&scop->obj.normals, &b[0]);
		vector_set(&scop->obj.normals, &b[1]);
		vector_set(&scop->obj.normals, &b[2]);
		i++;
	}
}

static void	load_vertices(t_lobj *lobj, char *line)
{
	t_vec v;

	if (*line == 't')
	{
		sscanf(line, " %f %f\n", &v.x, &v.y);
		vector_set(&lobj->temp_uvs, &v.x);
		vector_set(&lobj->temp_uvs, &v.y);
	}
	else if (*line == 'n')
	{
		sscanf((line + 1), " %f %f %f\n", &v.x, &v.y, &v.z);
		vector_set(&lobj->temp_normals, &v.x);
		vector_set(&lobj->temp_normals, &v.y);
		vector_set(&lobj->temp_normals, &v.z);
	}
	else
	{
		sscanf(line, " %f %f %f\n", &v.x, &v.y, &v.z);
		vector_set(&lobj->temp_vertices, &v.x);
		vector_set(&lobj->temp_vertices, &v.y);
		vector_set(&lobj->temp_vertices, &v.z);
	}
}

static void	load_v(t_lobj *lobj, char *line)
{
	unsigned int vertexIndex[4];
	int	match;

	match = sscanf((line + 1), "%d %d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2], &vertexIndex[3]);
	vector_set(&lobj->vertex_id, &vertexIndex[0]);
	vector_set(&lobj->vertex_id, &vertexIndex[1]);
	vector_set(&lobj->vertex_id, &vertexIndex[2]);
	if (match == 4)
	{
		vector_set(&lobj->vertex_id, &vertexIndex[0]);
		vector_set(&lobj->vertex_id, &vertexIndex[2]);
		vector_set(&lobj->vertex_id, &vertexIndex[3]);
	}
}

static void	load_vn(t_lobj *lobj, char *line)
{
	unsigned int vertexIndex[8];
	int	match;

	match = sscanf((line + 1), "%d//%d %d//%d %d//%d %d//%d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2], &vertexIndex[3], &vertexIndex[4], &vertexIndex[5], &vertexIndex[6], &vertexIndex[7]);
	vector_set(&lobj->vertex_id, &vertexIndex[0]);
	vector_set(&lobj->vertex_id, &vertexIndex[2]);
	vector_set(&lobj->vertex_id, &vertexIndex[4]);
	vector_set(&lobj->normal_id, &vertexIndex[1]);
	vector_set(&lobj->normal_id, &vertexIndex[3]);
	vector_set(&lobj->normal_id, &vertexIndex[5]);
	if (match == 8)
	{
		vector_set(&lobj->vertex_id, &vertexIndex[0]);
		vector_set(&lobj->vertex_id, &vertexIndex[4]);
		vector_set(&lobj->vertex_id, &vertexIndex[6]);
		vector_set(&lobj->normal_id, &vertexIndex[1]);
		vector_set(&lobj->normal_id, &vertexIndex[5]);
		vector_set(&lobj->normal_id, &vertexIndex[7]);
	}
}

static void	load_vun(t_lobj *lobj, char *line)
{
	unsigned int vertexIndex[12];
	int	match;

	match = sscanf((line + 1), "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2], &vertexIndex[3], &vertexIndex[4], &vertexIndex[5], &vertexIndex[6], &vertexIndex[7], &vertexIndex[8], &vertexIndex[9], &vertexIndex[10], &vertexIndex[11]);
	vector_set(&lobj->vertex_id, &vertexIndex[0]);
	vector_set(&lobj->vertex_id, &vertexIndex[3]);
	vector_set(&lobj->vertex_id, &vertexIndex[6]);
	vector_set(&lobj->uv_id, &vertexIndex[1]);
	vector_set(&lobj->uv_id, &vertexIndex[4]);
	vector_set(&lobj->uv_id, &vertexIndex[7]);
	vector_set(&lobj->normal_id, &vertexIndex[2]);
	vector_set(&lobj->normal_id, &vertexIndex[5]);
	vector_set(&lobj->normal_id, &vertexIndex[8]);
	if (match == 12)
	{
		vector_set(&lobj->vertex_id, &vertexIndex[0]);
		vector_set(&lobj->vertex_id, &vertexIndex[6]);
		vector_set(&lobj->vertex_id, &vertexIndex[9]);
		vector_set(&lobj->uv_id, &vertexIndex[1]);
		vector_set(&lobj->uv_id, &vertexIndex[7]);
		vector_set(&lobj->uv_id, &vertexIndex[10]);
		vector_set(&lobj->normal_id, &vertexIndex[0]);
		vector_set(&lobj->normal_id, &vertexIndex[8]);
		vector_set(&lobj->normal_id, &vertexIndex[11]);
	}
}

static void	load_faces(t_lobj *lobj, char *line)
{
	if (strstr(line, "//"))
		load_vn(lobj, line);
	else if (strstr(line, "/"))
		load_vun(lobj, line);
	else
		load_v(lobj, line);
}

void load_obj(t_scop *scop, char *path)
{
	t_lobj	lobj;
	int 	fd;
	char	*line;

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
		if (*line == 'v')
			load_vertices(&lobj, line + 1);
		else if (*line == 'f')
			load_faces(&lobj, line + 1);
		free(line);
	}
	tidy_vertices(scop, &lobj);
}
