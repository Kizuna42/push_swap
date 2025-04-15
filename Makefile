# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/01 12:00:00 by kizuna            #+#    #+#              #
#    Updated: 2025/04/15 20:20:39 by kizuna           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

INCLUDE = -I. -I$(LIBFT_DIR)

# Source directories
SRC_DIR = src/
MAIN_DIR = $(SRC_DIR)main/
OPERATIONS_DIR = $(SRC_DIR)operations/
STACK_UTILS_DIR = $(SRC_DIR)stack_utils/
UTILS_DIR = $(SRC_DIR)utils/
CMD_UTILS_DIR = $(SRC_DIR)command_utils/

# Source files
MAIN_SRCS = $(MAIN_DIR)main.c \
			$(MAIN_DIR)push_swap.c \
			$(MAIN_DIR)sort.c

OPERATIONS_SRCS = $(OPERATIONS_DIR)rotate.c \
				$(OPERATIONS_DIR)swap.c \
				$(OPERATIONS_DIR)push.c \
				$(OPERATIONS_DIR)reverse_rotate.c

STACK_UTILS_SRCS = $(STACK_UTILS_DIR)stack_checker.c \
				$(STACK_UTILS_DIR)stack_info.c \
				$(STACK_UTILS_DIR)stack_management.c

UTILS_SRCS = $(UTILS_DIR)error.c \
			$(UTILS_DIR)push_swap_atoi.c

CMD_UTILS_SRCS = $(CMD_UTILS_DIR)command_utils.c \
				$(CMD_UTILS_DIR)command_utils2.c \
				$(CMD_UTILS_DIR)command_utils3.c

SRCS = $(MAIN_SRCS) $(OPERATIONS_SRCS) $(STACK_UTILS_SRCS) $(UTILS_SRCS) $(CMD_UTILS_SRCS)

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) full

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
