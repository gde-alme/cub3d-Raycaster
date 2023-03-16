# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gde-alme <gde-alme@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 11:33:26 by gde-alme          #+#    #+#              #
#    Updated: 2023/03/15 11:33:27 by gde-alme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	main.c utils.c movement.c display.c raycaster.c images.c
OBJS		=	$(SRCS:.c=.o)
NAME		=	cub3D
CC			=	gcc
# CFLAGS	=	-Wall -Wextra -Werror
CFLAGS		=
RM			=	rm -f

%.o: %.c
			$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -L ./minilibx-linux -lmlx -lXext -lX11 -lm -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

norm:
			norminette -R CheckForbiddenSourceHeader $(SRCS)

val:
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

.PHONY:		all re clean fclean norm val
