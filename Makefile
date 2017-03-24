# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vroche <vroche@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/16 10:49:38 by vroche            #+#    #+#              #
#    Updated: 2017/03/23 17:58:41 by vroche           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop

LIB = -framework OpenGL -framework AppKit \
		-L./minilibx_macos -lmlx -L./libft -lft -lm

HDR = -I./minilibx_macos -I./libft/includes

FLAGS = -Wall -Werror -Wextra

C = main.c \
	scop_manage.c

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