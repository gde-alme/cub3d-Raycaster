# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efreire- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 17:41:45 by efreire-          #+#    #+#              #
#    Updated: 2021/11/05 17:48:41 by efreire-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	\
			ft_isalpha.c		ft_isdigit.c		ft_isalnum.c		ft_isascii.c		\
			ft_isprint.c		ft_isspace.c		ft_isstrspace.c		ft_strlen.c			ft_memset.c			ft_pow.c		ft_bzero.c	\
			ft_memcpy.c			ft_memmove.c		ft_strlcpy.c		ft_strlcat.c		\
			ft_toupper.c		ft_tolower.c		ft_strchr.c			ft_strrchr.c		\
			ft_strncmp.c		ft_memchr.c			ft_memcmp.c			ft_strnstr.c		\
			ft_atoi.c			ft_calloc.c			ft_file_exists.c	ft_strdup.c			ft_strends.c		ft_substr.c			\
			ft_strjoin.c		ft_strtrim.c		ft_split.c			ft_str_expand.c		ft_str_find_last.c	ft_strstarts.c		ft_itoa.c			\
			ft_strmapi.c		ft_striteri.c		ft_putchar_fd.c		ft_putstr_fd.c		ft_replace.c		\
			ft_putendl_fd.c		ft_putnbr_fd.c		ft_valid_rgb.c		ft_value_rgb.c		ft_lstnew.c			ft_lstadd_front.c	\
			ft_lstsize.c		ft_lstlast.c		ft_lstadd_back.c	ft_lstdelone.c 		\
			ft_lstclear.c     	ft_lstiter.c 		ft_lstmap.c			get_next_line.c
OBJS	=	$(SRCS:.c=.o)
INS		=	libft.h
NAME	=	libft.a
LIB		=	ar rc
RL		=	ranlib
CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror -fsanitize=address
RM		=	rm -f

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I.$(INS)

$(NAME):	$(OBJS)
			$(LIB) $(NAME) $(OBJS)
			$(RL) $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

norm :
			norminette -R CheckForbiddenSourceHeader $(SRCS)
			norminette -R CheckDefine $(INS)

.PHONY:		all re clean fclean
