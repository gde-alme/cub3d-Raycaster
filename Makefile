# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efreire- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 17:00:02 by efreire-          #+#    #+#              #
#    Updated: 2023/01/28 17:00:03 by efreire-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
SRCS		=	main.c
INIT_SRCS	=	init_data.c				set_data_base_vars.c	set_data_map.c			set_data_map_2.c	\
				set_data_map_3.c		var_builder_utils.c
RAY_SRCS	=	exec.c					utils.c					movement.c				display.c			\
				raycaster.c				images.c
OBJS		=	$(patsubst %.c, %.o, $(SRCS))	\
				$(patsubst %.c, %.o, $(addprefix init_data/, $(INIT_SRCS)))	\
				$(patsubst %.c, %.o, $(addprefix raycasting/, $(RAY_SRCS)))
LIBFT		=	-L libft -lft
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror -fsanitize=address

all:		$(NAME)

$(NAME):	$(OBJS)
			@make -C libft/
			$(CC) $(FLAGS) $(OBJS) $(LIBFT) -L ./minilibx-linux -lmlx -lXext -lX11 -lm -o $(NAME)

%.o:		%.c $(INS)
			$(CC) $(FLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
			@make clean -C libft/
			rm -f $(OBJS)

fclean:		clean
			@make fclean -C libft/
			rm -f $(NAME)

re:			fclean all

test:		all
			@make clean
			clear
			./$(NAME) ./maps/valid/map.cub

norm:
			norminette -R CheckForbiddenSourceHeader $(SRCS)
			norminette -R CheckDefine $(INS)

.PHONY :	all clean fclean re test norm

# \
./cub3d ./maps/invalid/map-00.cub; \
./cub3d ./maps/invalid/map-01.cub; \
./cub3d ./maps/invalid/map-02.cub; \
./cub3d ./maps/invalid/map-03.cub; \
./cub3d ./maps/invalid/map-04.cub; \
./cub3d ./maps/invalid/map-05.cub; \
./cub3d ./maps/invalid/map-06.cub; \
./cub3d ./maps/invalid/map-07.cub; \
./cub3d ./maps/invalid/map-08.cub; \
./cub3d ./maps/invalid/map-09.cub; \
./cub3d ./maps/invalid/map-10.cub; \
./cub3d ./maps/invalid/map-11.cub; \
./cub3d ./maps/invalid/map-12.cub;
