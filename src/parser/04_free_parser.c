/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_free_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:39:34 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/01 17:22:19 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_command_partial(t_command *cmd, t_list *args)
{
	if (cmd)
	{
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		if (cmd->delimit)
			free(cmd->delimit);
		free(cmd);
	}
	if (args)
		ft_lstclear(&args, free);
}

static void	ft_free_command_content(t_command *cmd)
{
	int	i;

	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd->argv);
	}
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->delimit)
		free(cmd->delimit);
	if (cmd->heredoc_fd != -1)
		close(cmd->heredoc_fd);
}

void	ft_free_command_list(t_command **cmd_list)
{
	t_command	*current;
	t_command	*next;

	if (!cmd_list || !*cmd_list)
		return ;
	current = *cmd_list;
	while (current)
	{
		next = current->next;
		ft_free_command_content(current);
		free(current);
		current = next;
	}
	*cmd_list = NULL;
}
