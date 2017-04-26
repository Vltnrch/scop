/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 12:27:46 by vroche            #+#    #+#             */
/*   Updated: 2017/04/20 14:53:05 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	load_bmp(char *ptr)
{
	unsigned short	width;
	unsigned short	height;

	if (*(int *)&(ptr[0x1E]) != 0)
		ft_perror_exit("Not a correct BMP file\n");
	if (*(int *)&(ptr[0x1C]) != 24)
		ft_perror_exit("Not a correct BMP file\n");
	width      = *(unsigned short*)&(ptr[0x12]);
	height     = *(unsigned short*)&(ptr[0x16]);
	printf("datapos %d / imagesize %d / width %d / height %d\n", *(int*)&(ptr[0x0A]), *(int*)&(ptr[0x22]), width, height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, ptr + *(int*)&(ptr[0x0A]));
}

void	texture_gl(t_scop *scop)
{
	// Create one OpenGL texture
	glGenTextures(1, &scop->gl.texture_id);
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, scop->gl.texture_id);
	// Give the image to OpenGL
	// Poor filtering, or ...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	// ... nice trilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
}

void load_texture(t_scop *scop, char *file)
{
	printf("Reading image %s\n", file);
	// Open the file
	int	fd;
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_perror_exit("open() BMP");
	int	size;
	if ((size = lseek(fd, 0, SEEK_END)) == -1)
		ft_perror_exit("lseek() BMP");
	char *ptr;
	if ((ptr = mmap(0, size, PROT_WRITE|PROT_READ,MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		ft_perror_exit("mmap() BMP");
	texture_gl(scop);
	// Read the header, i.e. the 54 first bytes
	// A BMP files always begins with "BM"
	if (ptr[0] =='B' || ptr[1] =='M')
		load_bmp(ptr);
	else
		ft_perror_exit("WTF Texture");
	glGenerateMipmap(GL_TEXTURE_2D);
}