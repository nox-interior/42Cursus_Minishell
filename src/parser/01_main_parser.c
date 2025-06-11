/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:26:15 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/11 13:07:37 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_syntax_error(const char *token, int *exit_status)
{
	ft_printf("minishell: syntax error near unexpected token `%s'\n",
		(char *)token);
	*exit_status = 258;
	return (0);
}

static int	ft_unexpected_error(int *exit_status)
{
	ft_printf("minishell: unexpected error creating token\n");
	*exit_status = 2;
	return (0);
}

int	ft_is_valid_token_sequence(t_token *tokens, int *exit_status)
{
	t_token	*current;

	current = tokens;
	if (!current)
		return (ft_unexpected_error(exit_status));
	if (current->type == T_PIPE)
		return (ft_syntax_error("|", exit_status));
	while (current)
	{
		if (ft_is_special_character(current->type))
			return (ft_syntax_error(current->value, exit_status));
		if (current->type == T_PIPE)
			if (!current->next || current->next->type == T_PIPE)
				return (ft_syntax_error("|", exit_status));
		if (ft_is_redirection(current->type))
			if (!current->next || !ft_is_valid_arg_token(current->next->type))
				return (ft_syntax_error("newline", exit_status));
		if (current->type == T_NONE)
			return (ft_unexpected_error(exit_status));
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

t_command	*ft_parse_command(t_token *token_list, int *exit_status)
{
	t_token		*current;
	t_command	*head;
	t_command	*tail;

	if (!ft_is_valid_token_sequence(token_list, exit_status))
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
