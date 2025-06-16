/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:42:39 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/16 19:06:41 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_token	*ft_read_and_tokenize(t_shell *shell, char **line)
{
	t_token	*tokens;

	*line = ft_get_user_input();
	if (!*line)
		return (NULL);
	if (isatty(STDIN_FILENO) && **line)
		add_history(*line);
	tokens = ft_tokenizer(*line);
	if (!tokens)
	{
		shell->exit_status = 2;
		free(*line);
		return (NULL);
	}
	free(*line);
	return (tokens);
}

static void	ft_parse_and_execute(t_token *tokens, t_shell *shell)
{
	t_command	*commands;

	ft_expand_variables(tokens, shell);
	commands = ft_parse_command(tokens, shell);
	if (!commands)
	{
		ft_free_token_list(&tokens);
		return ;
	}
	ft_executor(commands, shell);
	ft_free_token_list(&tokens);
	ft_free_command_list(&commands);
}

void	ft_minishell_loop(t_shell *shell)
{
	char	*line;
	t_token	*tokens;

	while (1)
{
	if (g_signal)
	{
		shell->exit_status = g_signal;
		g_signal = 0;
	}
	tokens = ft_read_and_tokenize(shell, &line);
	if (ft_should_exit(line))
		break ;
	if (!tokens)
		continue ;
	ft_parse_and_execute(tokens, shell);
}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;

	(void)argc;
	(void)argv;
	shell.envp = ft_copy_env(envp);
	if (!shell.envp)
		return (perror("minishell: malloc"), 1);
	shell.exit_status = 0;
	ft_setup_interactive_signals();
	ft_minishell_loop(&shell);
	return (shell.exit_status);
}