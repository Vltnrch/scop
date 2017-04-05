# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vroche <vroche@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/16 10:49:38 by vroche            #+#    #+#              #
#    Updated: 2017/04/05 12:42:46 by vroche           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop

LIB = -framework OpenGL -framework AppKit \
		-L./minilibx_macos -lmlx -L./libft -lft -lm

HDR = -I./minilibx_macos -I./libft/includes -I./includes

FLAGS = -Wall -Wextra -g

C = srcs/main.c \
	srcs/scop_init.c \
	srcs/scop_key.c \
	srcs/scop_loop.c \
	srcs/scop_manage.c \
	srcs/scop_mouse.c \
	srcs/scop_obj.c \
	srcs/loaders/load_bmp.c \
	srcs/loaders/load_obj.c \
	srcs/loaders/load_shaders.c \
	srcs/math/mtx.c \
	srcs/math/mtx_tool.c \
	srcs/math/vec.c \
	srcs/math/vec_calc.c

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
