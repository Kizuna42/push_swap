# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 00:31:43 by kizuna            #+#    #+#              #
#    Updated: 2025/04/16 00:42:40 by kizuna           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	push_swap

NAME_BONUS	=	checker

CC			=	cc

CFLAGS		=	-g -Wall -Wextra -Werror

INCLUDE		=	-I.

LIB			=	-L./libft -lft

SRCS		=	srcs/push_swap.c						\
				srcs/algorithm_helper.c				\
				srcs/errors_handling.c				\
				srcs/operations.c						\
				srcs/utils_stack.c					\
				srcs/algorithm.c						\
				srcs/algorithm_optimized.c			\
				srcs/utils.c

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
