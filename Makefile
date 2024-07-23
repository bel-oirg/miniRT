# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/16 01:38:09 by bel-oirg          #+#    #+#              #
#    Updated: 2024/07/24 00:18:20 by abennar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT  

GLFLAGS = -lmlx -framework OpenGL -framework AppKit # -fsanitize=address -g

CFLAGS = -Wall -Wextra -Werror -Imlx

RM = rm -rf

SRCS = 	minirt.c vectors.c my_malloc.c rotation_matrix.c cylinder.c plane.c

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
