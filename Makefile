# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/02 16:26:23 by amarroyo          #+#    #+#              #
#    Updated: 2025/06/30 13:08:06 by amarroyo         ###   ########.fr        #
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

EXIT		= $(SRC_DIR)exit/01_free.c \

SIGNALS		= $(SRC_DIR)signals/01_signals.c

EXECUTOR	= $(SRC_DIR)executor/01_executor.c \
			  $(SRC_DIR)executor/02_builtin_executor.c

BUILTINS	= $(SRC_DIR)builtins/01_echo.c \
			  $(SRC_DIR)builtins/02_pwd.c \
			  $(SRC_DIR)builtins/03_env.c \
			  $(SRC_DIR)builtins/04_cd.c \
			  $(SRC_DIR)builtins/05_export.c \
			  $(SRC_DIR)builtins/06_identifiers_export.c \
			  $(SRC_DIR)builtins/07_sort_export.c \
			  $(SRC_DIR)builtins/08_unset.c \
			  $(SRC_DIR)builtins/09_aux_unset.c

ENV			= $(SRC_DIR)/env/01_copy_env.c \
			  $(SRC_DIR)/env/02_free_env.c \
			  $(SRC_DIR)/env/03_manage_env.c \
			  $(SRC_DIR)/env/04_manage02_env.c

SRC			= $(MAIN) $(TOKENIZER) $(PARSER) $(EXIT) $(SIGNALS) \
			  $(VAR_EXP) $(ENV) $(BUILTINS) $(EXECUTOR)

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
