/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_command_parser_b.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbar-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:11:51 by calbar-c          #+#    #+#             */
/*   Updated: 2025/09/27 13:11:56 by calbar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setup_command_argv(t_command *cmd, t_list **args)
{
	if (*args)
	{
		cmd->argv = ft_list_to_str_array(*args);
		if (!cmd->argv)
			return (-1);
		return (0);
	}
	if (cmd->heredoc || cmd->infile || cmd->outfile)
	{
		cmd->argv = ft_calloc(1, sizeof(char *));
		if (!cmd->argv)
			return (-1);
	}
	return (0);
}

t_command	*ft_init_new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_init_command(cmd);
	return (cmd);
}
