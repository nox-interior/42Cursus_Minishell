/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:26:15 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/03 11:12:50 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_is_valid_token_sequence(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (!current)
		return (0);
	if (current->type == T_PIPE)
		return (0);
	while (current)
	{
		if (ft_is_special_character(current->type))
			return (0);
		if (current->type == T_PIPE)
			if (!current->next || current->next->type == T_PIPE)
				return (0);
		if (ft_is_redirection(current->type))
			if (!current->next || !ft_is_valid_arg_token(current->next->type))
				return (0);
		if (current->type == T_NONE)
			return (0);
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

t_command	*ft_parse_command(t_token *token_list)
{
	t_token		*current;
	t_command	*head;
	t_command	*tail;

	if (!ft_is_valid_token_sequence(token_list))
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
