/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 17:41:29 by vroche            #+#    #+#             */
/*   Updated: 2017/04/05 12:28:52 by vroche           ###   ########.fr       */
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

	vector_make(&scop->obj.vertices, 1, sizeof(float));
	vector_make(&scop->obj.uvs, 1, sizeof(float));
	vector_make(&scop->obj.normals, 1, sizeof(float));
	i = 0;
	int	size = vector_size(&lobj->vertex_id);
	while (i < size)
	{
		// Get the attributes thanks to the index
		//float *vertex = &((float *)lobj.temp_vertices.ctn)[((unsigned int *)lobj.vertex_id.ctn)[i]];
		//float *uv = &((float *)lobj.temp_uvs.ctn)[((unsigned int *)(lobj.uv_id.ctn))[i] * 3 - 1];
		//float *normal = &((float *)lobj.normals.ctn)[((unsigned int *)(lobj.normal_id.ctn))[i] * 3 - 1];

		//lobj.temp_vertices[ face[i].a ].x,lobj.temp_vertices[ face[i].a ].y,vertex[ face[i].a ].z

		// Put the attributes in buffers
		//int a = ((unsigned int *)(lobj->vertex_id.ptr))[i];
		//float	*b = ((float *)(lobj->temp_vertices.ptr)) + ((a - 1) * 3);
		unsigned int	a = *(unsigned int *)vector_get(&lobj->vertex_id, i);
		float			*b = (float *)vector_get(&lobj->temp_vertices, ((a - 1) * 3));
		vector_set(&scop->obj.vertices, &b[0]);
		vector_set(&scop->obj.vertices, &b[1]);
		vector_set(&scop->obj.vertices, &b[2]);
		//add_ctn(&scop->obj.uvs, uv[0]);
		//add_ctn(&scop->obj.uvs, uv[1]);
		//add_ctn(&scop->obj.normals, normal[0]);
		//add_ctn(&scop->obj.normals, normal[1]);
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
		vector_set(&lobj->normals, &v.x);
		vector_set(&lobj->normals, &v.y);
		vector_set(&lobj->normals, &v.z);
	}
	else
	{
		sscanf(line, " %f %f %f\n", &v.x, &v.y, &v.z);
		vector_set(&lobj->temp_vertices, &v.x);
		vector_set(&lobj->temp_vertices, &v.y);
		vector_set(&lobj->temp_vertices, &v.z);
	}
}

static void	load_faces(t_lobj *lobj, char *line)
{
	unsigned int vertexIndex[4];
	int matches = sscanf((line + 1), "%d %d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2], &vertexIndex[3]);
	vector_set(&lobj->vertex_id, &vertexIndex[0]);
	vector_set(&lobj->vertex_id, &vertexIndex[1]);
	vector_set(&lobj->vertex_id, &vertexIndex[2]);
	if (matches == 4)
	{
		vector_set(&lobj->vertex_id, &vertexIndex[0]);
		vector_set(&lobj->vertex_id, &vertexIndex[2]);
		vector_set(&lobj->vertex_id, &vertexIndex[3]);
	}
}

void load_obj(t_scop *scop, char *path)
{
	t_lobj	lobj;
	int 	fd;
	char	*line;

	vector_make(&lobj.vertex_id, 1, sizeof(unsigned int));
	vector_make(&lobj.uv_id, 1, sizeof(unsigned int));
	vector_make(&lobj.normal_id, 1, sizeof(unsigned int));
	vector_make(&lobj.temp_vertices, 1, sizeof(float));
	vector_make(&lobj.temp_uvs, 1, sizeof(float));
	vector_make(&lobj.normals, 1, sizeof(float));
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
