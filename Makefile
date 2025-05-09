# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 00:59:41 by kizuna            #+#    #+#              #
#    Updated: 2025/05/09 19:03:47 by kizuna           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	push_swap

CC			=	cc

CFLAGS		=	-g -Wall -Wextra -Werror

INCLUDE		=	-I.

LIB			=	-L./libft -lft

SRCS		=	mandatory/srcs/push_swap.c						\
				mandatory/srcs/errors_handling.c				\
				mandatory/srcs/operations.c						\
				mandatory/srcs/utils_stack.c					\
				mandatory/srcs/algorithm.c						\
				mandatory/srcs/algorithm_helper.c				\
				mandatory/srcs/utils.c

OBJS		= 	${SRCS:.c=.o}

LIBPATH		= 	libft/

all:			${NAME}

${NAME}:		${OBJS}
			make -C ${LIBPATH}
			${CC} ${CFLAGS} $^ ${INCLUDE} ${LIB} -o $@

clean:
			make clean -C ${LIBPATH}
			rm -f ${OBJS}

fclean:			clean
			make fclean -C ${LIBPATH}
			rm -f ${NAME} ${NAME_TEST}

re:				fclean all

.PHONY:			all clean fclean re
