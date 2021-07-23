# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/02 18:08:00 by mmaryjan          #+#    #+#              #
#    Updated: 2021/02/25 21:27:29 by mmaryjan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

DIR_OBJ = ./

SRCS	=   srcs/ft_atoi.c \
            srcs/ft_builtin.c \
            srcs/ft_export.c \
            srcs/ft_env.c \
            srcs/ft_forline.c \
            srcs/ft_forline2.c \
            srcs/ft_forline3.c \
            srcs/ft_forline4.c \
            srcs/ft_forline5.c \
            srcs/ft_lstadd_back.c \
            srcs/ft_lstadd_mem.c \
            srcs/ft_parse_utils.c \
            srcs/ft_pipes.c \
            srcs/ft_putstr_fd.c \
            srcs/ft_redirect.c \
            srcs/ft_split.c \
            srcs/ft_strncmp.c \
            srcs/ft_strtrim.c \
            srcs/ft_unset.c \
            srcs/get_next_line_exam.c \
            srcs/get_next_line_utils.c \
            srcs/main.c \
            srcs/mini_utils.c \
            srcs/ft_itoa.c \
            srcs/ft_cd.c \
            srcs/ft_doublelist.c \
            srcs/ft_termcap.c \
            srcs/ft_termcap1.c \
            srcs/ft_termcap2.c \
            srcs/ft_parse_utils1.c \
            srcs/ft_redirect1.c \

DIR_HEADERS	= ./includes/

OBJS	= $(SRCS:.c=.o)

RM		= rm -f


CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -g

.c.o:
			$(CC) $(CFLAGS) -c -I $(DIR_HEADERS) $< -o $(<:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) -I $(DIR_HEADERS) $(OBJS) -o $(NAME) -ltermcap

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
