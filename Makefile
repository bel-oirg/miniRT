# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/16 01:38:09 by bel-oirg          #+#    #+#              #
#    Updated: 2024/07/15 11:37:18 by bel-oirg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT  

GLFLAGS = -lmlx -framework OpenGL -framework AppKit

CFLAGS = -Wall -Wextra -Werror -Imlx

RM = rm -rf

SRCS = 	minirt.c

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