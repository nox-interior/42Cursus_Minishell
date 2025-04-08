# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/02 16:26:23 by amarroyo          #+#    #+#              #
#    Updated: 2025/04/04 10:18:34 by amarroyo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Standard
NAME		= minishell_test
SRC			= tokenizer.c
OBJ			= $(SRC:.c=.o)
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g3
LIBFT_DIR	= ../libft
LIBFT		= $(LIBFT_DIR)/libft.a
INCLUDES	= -I$(LIBFT_DIR)

# Rules
all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re