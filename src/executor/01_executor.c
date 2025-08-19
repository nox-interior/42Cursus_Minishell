/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:00:25 by amarroyo          #+#    #+#             */
/*   Updated: 2025/08/19 19:09:30 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_setup_input_redirection(t_command *cmd)
{
	int	fd;

	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
		{
			ft_puterror("No such file or directory", cmd->infile);
			return (-1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

int	ft_setup_output_redirection(t_command *cmd)
{
	int	fd;

	if (cmd->outfile)
	{
		if (cmd->append)
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_puterror("Permission denied", cmd->outfile);
			return (-1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

int	ft_setup_redirection(t_command *cmd)
{
	if (ft_setup_input_redirection(cmd) == -1)
		return (-1);
	if (ft_setup_output_redirection(cmd) == -1)
		return (-1);
	return (0);
}

void	ft_executor(t_command *cmd_list, t_shell *shell)
{
	if (!cmd_list)
		return ;
	if (ft_has_pipes(cmd_list))
		ft_execute_pipeline(cmd_list, shell);
	else
	{
		if (ft_is_builtin(cmd_list))
		{
			if (ft_setup_redirection(cmd_list) != -1)
				ft_exec_builtin(cmd_list, shell);
		}
		else
			ft_fork_and_exec(cmd_list, shell);
	}
}
