/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:42:39 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/11 13:06:19 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_token	*ft_read_and_tokenize(char **line)
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
		ft_set_exit_status(2);
		free(*line);
		return (NULL);
	}
	free(*line);
	return (tokens);
}

static void	ft_parse_and_execute(t_token *tokens, char **envp, int *exit_status)
{
	t_command	*commands;

	ft_expand_variables(tokens, envp);
	//ELIMINAR BLOQUE; SOLO PARA TESTEO
	t_token	*debug = tokens;
	printf("Tokens tras expansión:\n");
	while (debug)
	{
		printf("  Token: [%d] -> \"%s\"\n", debug->type, debug->value);
		debug = debug->next;
	}
	//HASTA AQUÍ
	commands = ft_parse_command(tokens, exit_status);
	if (ft_get_exit_status() != 0)
		return ;
	ft_set_exit_status(0);
	(void)envp;
	ft_free_token_list(&tokens);
	if (!commands)
		return ;
	// executor(commands, envp, exit_status);
	ft_free_command_list(&commands);
}

void	ft_minishell_loop(char **envp, int *exit_status)
{
	char		*line;
	t_token		*tokens;

	while (1)
	{
		tokens = ft_read_and_tokenize(&line);
		if (ft_should_exit(line))
			break ;
		if (!tokens)
			continue ;
		ft_parse_and_execute(tokens, envp, exit_status);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	exit_status;

	(void)argc;
	(void)argv;
	exit_status = 0;
	ft_setup_interactive_signals();
	ft_minishell_loop(envp, &exit_status);
	return (ft_get_exit_status());
}
