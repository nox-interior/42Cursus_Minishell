/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:42:39 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/03 12:43:43 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

/*static void	ft_print_tokens(t_token *head)
{
	while (head)
	{
		printf("Token: [%-10s] -> \"%s\"\n", ft_token_type_name(head->type),
			head->value);
		head = head->next;
	}
}

int	main(void)
{
	t_token	*tokens;
	t_command *comandos;
	char *cmd_line;
	int i = 0;

	cmd_line = get_next_line(0);
	tokens = NULL;
	tokens = ft_tokenizer(cmd_line);
	ft_print_tokens(tokens);
	comandos = ft_parse_command(tokens);
	if (!comandos)
		printf("cagaste\n");
	else
		while (comandos)
		{
			printf("[CMD %d]\n", i);
			while ((*comandos->argv))
			{
				printf("%s\n", (*comandos->argv));
				comandos->argv++;
			}
			if (comandos->infile)
				printf("%s\n", comandos->infile);
			if (comandos->outfile)
				printf("%s\n", comandos->outfile);
			if (comandos->append)
				printf("(append)\n");
			if (comandos->heredoc)
				printf("(heredoc)\n");
			comandos = comandos->next;
			i++;
		}
	//ft_free_token_list(tokens); TODO: en el parser y en los frees de errores del parser
	return (0);
}*/

// static void	minishell_loop(void)
// {
// 	char	*prompt;

// 	while (1)
// 	{
// 		prompt = readline("$ ");
// 		printf("La línea ingresada es: %s\n", prompt);
// 	}
// }

static char	*ft_get_user_input(void)
{
	if (isatty(STDIN_FILENO))
		return (readline("$ "));
	return (get_next_line(STDIN_FILENO));
}

static int	ft_should_exit(char *line)
{
	if (!line)
	{
		if (isatty(STDIN_FILENO))
			write(1, "exit\n", 5);
		return (1);
	}
	return (0);
}

static t_token	*ft_read_and_tokenize(char **line)
{
	t_token	*tokens;

	*line = ft_get_user_input();
	if (!*line)
		return (NULL);
	if (isatty(STDIN_FILENO) && **line)
		add_history(*line);
	tokens = ft_tokenizer(*line);
	free(*line);
	return (tokens);
}

static void	parse_and_execute(t_token *tokens, char **envp, int *exit_status)
{
	t_command	*commands;

	commands = ft_parse_command(tokens);
	ft_free_token_list(&tokens);
	if (!commands)
		return ;
	// executor(commands, envp, exit_status);
	ft_free_command_list(&commands);
}

void	minishell_loop(char **envp, int *exit_status)
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
	ft_minishell_loop(envp, &exit_status);
	return (0);
}