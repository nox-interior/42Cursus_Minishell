/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:42:39 by amarroyo          #+#    #+#             */
/*   Updated: 2025/04/25 09:44:07 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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

	tokens = NULL;
	tokens = ft_tokenizer("$   '' $  $$  $ \"$hola\" '$USER'|||<<<>>\'\' \"\" $$$ $$$$ ");
	ft_print_tokens(tokens);
	ft_free_token_list(&tokens);
	return (0);
}
