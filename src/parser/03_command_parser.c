/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_command_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:42:05 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/01 17:17:21 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_process_redirection(t_command *cmd, t_token **current)
{
	char	*redir_target;

	if (!(*current)->next || !ft_is_valid_arg_token((*current)->next->type))
		return (-1);
	redir_target = ft_strdup((*current)->next->value);
	if (!redir_target)
		return (-1);
	return (ft_process_redirection_extended(cmd, current, redir_target));
}

int	ft_parse_command_body(t_command *cmd, t_token **current, t_list **args)
{
	int	first_arg;

	first_arg = 1;
	while (*current && (*current)->type != T_PIPE)
	{
		if (ft_is_redirection((*current)->type))
		{
			if (ft_process_redirection(cmd, current) == -1)
				return (-1);
			continue ;
		}
		if (ft_is_valid_arg_token((*current)->type))
		{
			if (first_arg)
			{
				if (ft_process_first_argument(args, current) == -1)
					return (-1);
				first_arg = 0;
			}
			else
			{
				if (ft_process_concatenated_argument(args, current) == -1)
					return (-1);
			}
		}
		else if ((*current)->type == T_NONE)
			return (-1);
		*current = (*current)->next;
	}
	return (0);
}

t_command	*ft_create_command(t_token **current)
{
	t_command	*cmd;
	t_list		*args;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_init_command(cmd);
	args = NULL;
	if (ft_parse_command_body(cmd, current, &args) == -1)
		return (ft_free_command_partial(cmd, args), NULL);
	cmd->argv = ft_list_to_str_array(args);
	ft_lstclear(&args, free);
	return (cmd);
}
