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

LIBFT		=	${LIBPATH}libft.a

HEADER		=	mandatory/push_swap.h

all:			${NAME}

${NAME}:		${OBJS} ${LIBFT}
			${CC} ${CFLAGS} ${OBJS} ${INCLUDE} ${LIB} -o $@

${LIBFT}:
			make -C ${LIBPATH}

${OBJS}:		${HEADER}

clean:
			make clean -C ${LIBPATH}
			rm -f ${OBJS}

fclean:			clean
			make fclean -C ${LIBPATH}
			rm -f ${NAME}

re:				fclean all

test:			all
			python3 tests/test_push_swap.py ./${NAME}

.PHONY:			all clean fclean re test
