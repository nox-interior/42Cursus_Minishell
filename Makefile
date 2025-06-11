# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/02 16:26:23 by amarroyo          #+#    #+#              #
#    Updated: 2025/06/11 13:04:12 by amarroyo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Standard
NAME		= minishell

# Compiler and Flags
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g3 -I$(INC_DIR) -I$(LIBFT_DIR)
LDFLAGS		= -lreadline
RM			= rm -f

# Directories
INC_DIR		= inc/
SRC_DIR		= src/
OBJ_DIR		= obj/
LIBFT_DIR	= libft/
LIBFT		= $(LIBFT_DIR)/libft.a

# Source files
MAIN		= $(SRC_DIR)main/01_main.c \
			  $(SRC_DIR)main/02_aux_main.c

TOKENIZER	= $(SRC_DIR)tokenizer/01_tokenizer.c \
			  $(SRC_DIR)tokenizer/02_create_tokenizer.c \
			  $(SRC_DIR)tokenizer/03_types_tokenizer.c \
			  $(SRC_DIR)tokenizer/04_sp_types_tokenizer.c \
			  $(SRC_DIR)tokenizer/05_handles_tokenizer.c


VAR_EXP		= $(SRC_DIR)var_exp/01_var_exp.c

PARSER		= $(SRC_DIR)parser/01_main_parser.c \
			  $(SRC_DIR)parser/02_aux_parser.c \
			  $(SRC_DIR)parser/03_command_parser.c \
			  $(SRC_DIR)parser/04_free_parser.c

#EXECUTOR	= $(SRC_DIR)executor/

EXIT		= $(SRC_DIR)exit/01_free.c \
			  $(SRC_DIR)exit/02_exit.c

SIGNALS		= $(SRC_DIR)signals/01_signals.c

SRC			= $(MAIN) $(TOKENIZER) $(PARSER) $(EXIT) $(SIGNALS) \
			  $(VAR_EXP) #$(EXECUTOR)

# Object files
OBJ			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

# Compilation Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LDFLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning Rules
clean:
	make -C $(LIBFT_DIR) clean
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
