# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/02 16:26:23 by amarroyo          #+#    #+#              #
#    Updated: 2025/04/25 09:41:13 by amarroyo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Standard
NAME		= minishell

# Compiler and Flags
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g3 -I$(INC_DIR) -I$(LIBFT_DIR)
RM			= rm -f

# Directories
INC_DIR		= inc/
SRC_DIR		= src/
OBJ_DIR		= obj/
LIBFT_DIR	= libft/
LIBFT		= $(LIBFT_DIR)/libft.a

# Source files
TOKENIZER	= $(SRC_DIR)tokenizer/tokenizer.c

#PARSER		= $(SRC_DIR)parser/

#EXECUTOR	= $(SRC_DIR)executor/

MAIN		= main.c

SRC			= $(MAIN) $(TOKENIZER) #$(PARSER) $(EXECUTOR)

OBJ			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

# Compilation Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re