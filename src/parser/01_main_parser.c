/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:26:15 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/16 18:36:59 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_syntax_error(const char *token, t_shell *shell)
{
	shell->exit_status = 258;
	ft_printf("minishell: syntax error near unexpected token `%s'\n", token);
	return (0);
}

static int	ft_unexpected_error(t_shell *shell)
{
	shell->exit_status = 2;
	ft_printf("minishell: unexpected error creating token\n");
	return (0);
}

int	ft_is_valid_token_sequence(t_token *tokens, t_shell *shell)
{
	t_token	*current;

	current = tokens;
	if (!current)
		return (ft_unexpected_error(shell));
	if (current->type == T_PIPE)
		return (ft_syntax_error("|", shell));
	while (current)
	{
		if (ft_is_special_character(current->type))
			return (ft_syntax_error(current->value, shell));
		if (current->type == T_PIPE)
			if (!current->next || current->next->type == T_PIPE)
				return (ft_syntax_error("|", shell));
		if (ft_is_redirection(current->type))
			if (!current->next || !ft_is_valid_arg_token(current->next->type))
				return (ft_syntax_error("newline", shell));
		if (current->type == T_NONE)
			return (ft_unexpected_error(shell));
		current = current->next;
	}
	return (1);
}

int	ft_add_command_to_list(t_command **head, t_command **tail,
		t_token **current)
{
	t_command	*cmd;

	cmd = ft_create_command(current);
	if (!cmd)
		return (-1);
	if (!*head)
	{
		*head = cmd;
		*tail = cmd;
	}
	else
	{
		(*tail)->next = cmd;
		*tail = cmd;
	}
	return (0);
}

t_command	*ft_parse_command(t_token *token_list, t_shell *shell)
{
	t_token		*current;
	t_command	*head;
	t_command	*tail;

	if (!ft_is_valid_token_sequence(token_list, shell))
		return (NULL);
	current = token_list;
	head = NULL;
	tail = NULL;
	while (current)
	{
		if (ft_add_command_to_list(&head, &tail, &current) == -1)
			return (ft_free_command_list(&head), NULL);
		if (current && current->type == T_PIPE)
			current = current->next;
	}
	return (head);
}
