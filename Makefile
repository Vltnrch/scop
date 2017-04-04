# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vroche <vroche@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/16 10:49:38 by vroche            #+#    #+#              #
#    Updated: 2017/04/04 16:50:42 by vroche           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop

LIB = -framework OpenGL -framework AppKit \
		-L./minilibx_macos -lmlx -L./libft -lft -lm

HDR = -I./minilibx_macos -I./libft/includes

FLAGS = -Wall -Wextra -g

C = main.c \
	scop_init.c \
	scop_manage.c \
	load_shaders.c \
	mtx.c \
	scop_key.c \
	scop_mouse.c \
	load_obj.c \
	vec.c

O = $(C:.c=.o)

all: $(NAME)

$(NAME): $(O)
	make -C ./libft
	make -C ./minilibx_macos
	clang $(FLAGS) $^ $(HDR) $(LIB) -o $@

%.o:%.c
	clang $(FLAGS) $(HDR) -c $< -o $@

clean:
	make -C ./libft clean
	make -C ./minilibx_macos clean
	rm -f $(O)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
