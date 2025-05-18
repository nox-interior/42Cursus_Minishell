/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_free_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:39:34 by amarroyo          #+#    #+#             */
/*   Updated: 2025/05/18 12:58:51 by amarroyo         ###   ########.fr       */
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
		free(cmd);
	}
	if (args)
		ft_lstclear(&args, free);
}

void	ft_free_command_list(t_command **cmd_list)
{
	t_command	*current;
	t_command	*next;
	int			i;

	if (!cmd_list || !*cmd_list)
		return ;
	current = *cmd_list;
	while (current)
	{
		next = current->next;
		if (current->argv)
		{
			i = 0;
			while (current->argv[i])
				free(current->argv[i++]);
			free(current->argv);
		}
		if (current->infile)
			free(current->infile);
		if (current->outfile)
			free(current->outfile);
		free(current);
		current = next;
	}
	*cmd_list = NULL;
}
