/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 09:55:21 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/01 17:21:26 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"
# include "../libft/inc/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_signal;

// Token codes
typedef enum e_tok_type
{
	T_NONE,
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
}								t_tok_type;

// Token Structure: lexical level
typedef struct s_token
{
	t_tok_type					type;
	char						*value;
	struct s_token				*next;
	struct s_token				*prev;
}								t_token;

// Command List Structure: syntactical level
typedef struct s_command
{
	char						**argv;
	char						*infile;
	char						*outfile;
	int							append;
	int							heredoc;
	char						*delimit;
	int							heredoc_fd;
	struct s_command			*next;
}								t_command;

typedef struct s_shell			t_shell;

// Structure for pipe execution parameters
typedef struct s_pipe_params
{
	t_command					*current;
	int							**pipes;
	int							i;
	int							pipe_count;
	t_shell						*shell;
}								t_pipe_params;

// Environment copy structure
struct							s_shell
{
	char						**envp;
	int							exit_status;
};

// Tokenizer
t_token							*ft_tokenizer(const char *prompt);
void							ft_add_token(t_token **head,
									t_token *new_token);
t_token							*ft_new_token(t_tok_type type, char *value);
int								ft_is_exit_tok(t_token **token_list,
									t_token *new_token, int i);
int								ft_create_var_token(t_token **t_list,
									t_token *token, char *value);
int								ft_create_token(t_token **token_list,
									const char *prompt, int i);
bool							ft_is_word_char(char c);
char							*ft_quotes_token(const char *prompt, int *i);
int								ft_word_token(t_token **tokens,
									const char *prompt, int i);
int								ft_handle_redirection(t_token **token_list,
									const char *prompt, int i);
int								ft_handle_pipe(t_token **token_list,
									const char *prompt, int i);
int								ft_handle_special(t_token **token_list,
									const char *prompt, int i);
int								ft_handle_quote_token(t_token **tokens,
									const char *prompt, int i);
int								ft_handle_invalid(t_token **token_list,
									const char *prompt, int i);
int								ft_handle_special_inv(t_token **token_list,
									const char *prompt, int i);
void							ft_pipe_token(t_token **token_list);
void							ft_dub_redir(t_token **token_list,
									const char c);
void							ft_redir(t_token **token_list, const char c);
int								ft_var_token(t_token **token_list,
									const char *prompt, int i);

// Variable expansion
char							*ft_var_with_dollar(const char *prompt,
									int start, int end);
char							*ft_strjoin_char(char *str, char c);
char							*ft_expand_value(char *input, t_shell *shell);
void							ft_expand_variables(t_token *token_list,
									t_shell *shell);

// Parser
int								ft_is_valid_arg_token(t_tok_type type);
int								ft_is_redirection(t_tok_type type);
int								ft_is_special_character(t_tok_type type);
void							ft_init_command(t_command *cmd);
char							**ft_list_to_str_array(t_list *args);
int								ft_process_argument(t_list **args,
									t_token *token);
int								ft_process_concatenated_argument(t_list **args,
									t_token **current);
int								ft_process_first_argument(t_list **args,
									t_token **current);
int								ft_process_redirection(t_command *cmd,
									t_token **current);
int								ft_process_redirection_extended(t_command *cmd,
									t_token **current, char *redir_target);
char							**ft_list_to_str_array(t_list *args);
int								ft_parse_command_body(t_command *cmd,
									t_token **current, t_list **args);
t_command						*ft_create_command(t_token **current);
int								ft_is_valid_token_sequence(t_token *tokens,
									t_shell *shell);
int								ft_add_command_to_list(t_command **head,
									t_command **tail, t_token **current);
void							ft_free_command_partial(t_command *cmd,
									t_list *args);
void							ft_free_command_list(t_command **cmd_list);
t_command						*ft_parse_command(t_token *token_list,
									t_shell *shell);

// Signals
void							ft_handle_sigint(int sig);
void							ft_handle_sigquit(int sig);
void							ft_setup_interactive_signals(void);
void							ft_setup_noninteractive_signals(void);
void							ft_setup_signals(void);
void							ft_setup_child_signals(void);

// Env
char							**ft_copy_env(char **envp);
void							ft_free_env(char **env);
char							*ft_get_env_value(char **envp,
									const char *name);
int								ft_find_env_index(char **envp,
									const char *name);
int								ft_replace_env_var(char **envp, int idx,
									const char *name, const char *val);
int								ft_append_env_var(char ***envp,
									const char *name, const char *value);
int								ft_update_env_var(char ***envp,
									const char *name, const char *value);

// Builtins
int								ft_exec_builtin_echo(t_command *cmd,
									t_shell *shell);
int								ft_exec_builtin_pwd(t_command *cmd,
									t_shell *shell);
int								ft_exec_builtin_env(t_command *cmd,
									t_shell *shell);
int								ft_exec_builtin_cd(t_command *cmd,
									t_shell *shell);
int								ft_exec_builtin_export(t_command *cmd,
									t_shell *shell);
int								ft_is_valid_identifier(const char *s);
void							ft_export_invalid_identifier(const char *arg,
									t_shell *shell);
void							ft_export_print_sorted(char **envp);
void							ft_remove_env_var(t_shell *shell,
									const char *name);
int								ft_exec_builtin_unset(t_command *cmd,
									t_shell *shell);
int								ft_exec_builtin_exit(t_command *cmd,
									t_shell *shell);

// Redirections
int								ft_setup_redirection(t_command *cmd,
									t_shell *shell);
int								ft_setup_input_redirection(t_command *cmd,
									t_shell *shell);
int								ft_setup_output_redirection(t_command *cmd);

// Executor
bool							ft_is_builtin(t_command *cmd);
int								ft_exec_builtin(t_command *cmd, t_shell *shell);
void							ft_executor(t_command *cmd_list,
									t_shell *shell);
char							*ft_find_in_path(const char *cmd,
									t_shell *shell);
char							*ft_get_cmd_path(t_command *cmd,
									t_shell *shell);
void							ft_fork_and_exec(t_command *cmd,
									t_shell *shell);
int								ft_setup_heredoc(t_command *cmd,
									t_shell *shell);
int								ft_create_heredoc_fd(t_command *cmd,
									t_shell *shell);
int								ft_preprocess_heredocs(t_command *cmd_list,
									t_shell *shell);
int								ft_should_expand_vars(const char *delimit);
char							*ft_clean_delimit(char *delimit);
int								ft_read_heredoc_lines(int write_fd,
									char *delimit, t_shell *shell);
int								ft_has_pipes(t_command *cmd_list);
void							ft_close_all_pipes(int **pipes, int pipe_count);
void							ft_wait_all_children(int child_count);
int								ft_count_commands(t_command *cmd_list);
int								**ft_create_pipes(int pipe_count);
void							ft_execute_pipeline(t_command *cmd_list,
									t_shell *shell);

// Exit and Free
void							ft_free_token_list(t_token **tokens);
void							ft_free_split(char **s);
void							ft_puterror(char *err, char *cmd);
void							ft_print_exec_error(char *cmd);
void							ft_print_fd_error(char *call);

// Main
char							*ft_get_user_input(void);
char							*ft_read_line_from_stdin(void);
int								ft_should_exit(char *line);
void							ft_minishell_loop(t_shell *shell);

#endif