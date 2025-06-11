/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 09:55:21 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/11 13:03:23 by amarroyo         ###   ########.fr       */
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
# include <signal.h>

extern int	g_exit_status;

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
int					ft_is_exit_tok(t_token **token_list, t_token *new_token,
						int i);
int					ft_create_var_token(t_token **t_list, t_token *token,
						char *value);
int					ft_create_token(t_token **token_list, const char *prompt,
						int i);
bool				ft_is_word_char(char c);
int					ft_quotes_token(t_token **tokens, const char *prompt,
						int i);
int					ft_word_token(t_token **tokens, const char *prompt, int i);
int					handle_redirection(t_token **token_list, const char *prompt,
						int i);
int					handle_pipe(t_token **token_list, const char *prompt,
						int i);
int					handle_special(t_token **token_list, const char *prompt,
						int i);
int					handle_invalid(t_token **token_list, const char *prompt,
						int i);
int					handle_special_inv(t_token **token_list, const char *prompt,
						int i);
void				ft_pipe_token(t_token **token_list);
void				ft_dub_redir(t_token **token_list, const char c);
void				ft_redir(t_token **token_list, const char c);
int					ft_var_token(t_token **token_list, const char *prompt,
						int i);

// Variable expansion
char				*ft_var_with_dollar(const char *prompt, int start, int end);
char				*ft_strjoin_char(char *str, char c);
char				*ft_expand_value(char *input, char **envp);
void				ft_expand_variables(t_token *token_list, char **envp);

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
int					ft_is_valid_token_sequence(t_token *tokens,
						int *exit_status);
int					ft_add_command_to_list(t_command **head, t_command **tail,
						t_token **current);
void				ft_free_command_partial(t_command *cmd, t_list *args);
void				ft_free_command_list(t_command **cmd_list);
t_command			*ft_parse_command(t_token *token_list, int *exit_status);

// Executor

// Signals
void				ft_handle_sigint(int sig);
void				ft_handle_sigquit(int sig);
void				ft_setup_interactive_signals(void);

// Exit and Free
void				ft_free_token_list(t_token **tokens);
void				ft_set_exit_status(int status);
int					ft_get_exit_status(void);

// Main
char				*ft_get_user_input(void);
int					ft_should_exit(char *line);
void				ft_minishell_loop(char **envp, int *exit_status);

#endif