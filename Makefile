# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/16 01:38:09 by bel-oirg          #+#    #+#              #
#    Updated: 2024/08/01 08:45:43 by bel-oirg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = miniRT  
GLFLAGS = -lmlx -framework OpenGL -framework AppKit #-fsanitize=address 
CFLAGS = -Wall -Wextra -Werror -Imlx
RM = rm -rf

SRCS = 	minirt.c vectors.c my_malloc.c transform.c	\
		colors.c ft_mlx.c vectors2.c sphere.c material.c	\
		lighting.c cam.c sphere_intersection.c tuples.c \
		matrix.c

OBJS = $(SRCS:.c=.o)
HEADER = minirt.h

all : $(NAME)

$(NAME) : $(OBJS) 
	$(CC) $(GLFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS) : $(HEADER)

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(OBJS)

re : fclean all

.PHONY: all clean fclean re
