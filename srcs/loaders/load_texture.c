/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 12:27:46 by vroche            #+#    #+#             */
/*   Updated: 2017/05/09 16:15:21 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	load_bmp(char *ptr)
{
	unsigned short	width;
	unsigned short	height;

	if (*(int *)&(ptr[0x1E]) != 0)
		ft_exit("Not a correct BMP file");
	if (*(int *)&(ptr[0x1C]) != 24)
		ft_exit("Not a correct BMP file");
	width = *(unsigned short*)&(ptr[0x12]);
	height = *(unsigned short*)&(ptr[0x16]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGR, \
				GL_UNSIGNED_BYTE, ptr + *(int*)&(ptr[0x0A]));
}

void	texture_gl(t_scop *scop)
{
	glGenTextures(1, &scop->gl.texture_id);
	glBindTexture(GL_TEXTURE_2D, scop->gl.texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, \
									GL_LINEAR_MIPMAP_LINEAR);
}

void	load_texture(t_scop *scop, char *file)
{
	int		fd;
	char	*ptr;
	int		size;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_perror_exit("open() texture");
	if ((size = lseek(fd, 0, SEEK_END)) == -1)
		ft_perror_exit("lseek() texture");
	if ((ptr = mmap(0, size, PROT_WRITE | PROT_READ, MAP_PRIVATE, fd, 0)) \
			== MAP_FAILED)
		ft_perror_exit("mmap() texture");
	texture_gl(scop);
	if (ptr[0] == 'B' || ptr[1] == 'M')
		load_bmp(ptr);
	else
		ft_exit("Can't load this texture");
	munmap(ptr, size);
	close(fd);
	glGenerateMipmap(GL_TEXTURE_2D);
}
