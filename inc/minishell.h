/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 09:55:21 by amarroyo          #+#    #+#             */
/*   Updated: 2025/05/18 12:35:02 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h> // para bool
# include <stdio.h>
# include <stdlib.h> // malloc
# include <string.h> // para strdup

// Token codes
typedef enum e_tok_type
{
	T_NONE, // para evitar tener tokens sin tipo, control de errores
	T_SPACES,
	T_WORD,
	T_S_QUOTE,
	T_D_QUOTE,
	T_VAR,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_HEREDOC,
	T_APPEND,
	T_SEMICOLON,
	T_EXCLAMATION,
	T_AMPERSAND,
	T_AND,
	T_OR,
	T_INVALID
}					t_tok_type;

// Token Structure: lexical level
typedef struct s_token
{
	t_tok_type		type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

// Command List Structure: syntactical level
typedef struct s_command
{
	char				**argv;
	char				*infile;
	char				*outfile;
	int					append;
	int					heredoc;
	struct s_command	*next;
}						t_command;

// Tokenizer
t_token				*ft_tokenizer(const char *prompt);
void				ft_add_token(t_token **head, t_token *new_token);
t_token				*ft_new_token(t_tok_type type, char *value);
void				ft_free_token_list(t_token **tokens);
int					ft_word_token(t_token **tokens, const char *prompt, int i);

// Parser
int					ft_is_valid_arg_token(t_tok_type type);
int					ft_is_redirection(t_tok_type type);
int					ft_is_special_character(t_tok_type type);
void				ft_init_command(t_command *cmd);
char				**ft_list_to_str_array(t_list *args);
int					ft_process_argument(t_list **args, t_token *token);
int					ft_process_redirection(t_command *cmd, t_token **current);
int					ft_parse_command_body(t_command *cmd, t_token **current,
						t_list **args);
t_command			*ft_create_command(t_token **current);
int					ft_is_valid_token_sequence(t_token *tokens);
int					ft_add_command_to_list(t_command **head, t_command **tail,
						t_token **current);
void				ft_free_command_partial(t_command *cmd, t_list *args);
void				ft_free_command_list(t_command **cmd_list);
t_command			*ft_parse_command(t_token *token_list);

// Eliminar: funciones para pruebas
char				*ft_token_type_name(t_tok_type type);

#endif