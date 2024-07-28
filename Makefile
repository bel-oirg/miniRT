# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/16 01:38:09 by bel-oirg          #+#    #+#              #
#    Updated: 2024/07/28 06:42:37 by bel-oirg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT  

GLFLAGS = -lmlx -framework OpenGL -framework AppKit -g -fsanitize=address 

CFLAGS = -Wall -Wextra -Werror -Imlx

RM = rm -rf

SRCS = 	minirt.c vectors.c my_malloc.c rotation_matrix.c	\
		colors.c ft_mlx.c vectors2.c sphere.c material.c	\
		lighting.c

OBJS = $(SRCS:.c=.o)

HEADER = minirt.h

all : $(NAME)

$(NAME) : $(OBJS) 
	cc $(GLFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS) : $(HEADER)

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(OBJS)

re : fclean all

.PHONY: all clean fclean re
