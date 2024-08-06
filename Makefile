# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/16 01:38:09 by bel-oirg          #+#    #+#              #
#    Updated: 2024/08/05 01:53:34 by abennar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = miniRT  
GLFLAGS = -lmlx -framework OpenGL -framework AppKit -fsanitize=address 
CFLAGS =  -Imlx
RM = rm -rf

SRCS = cam.c colors.c draw_world.c ft_mlx.c lighting.c material.c \
	matrix.c minirt.c my_malloc.c plane_inter.c sphere.c sphere_intersection.c transform.c \
	tuples.c vectors.c vectors2.c



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
