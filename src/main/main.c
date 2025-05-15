/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:42:39 by amarroyo          #+#    #+#             */
/*   Updated: 2025/05/15 18:11:31 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

static void	ft_print_tokens(t_token *head)
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
}
