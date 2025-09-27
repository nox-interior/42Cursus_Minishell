/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:00:25 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/08 14:15:41 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_handle_heredoc_only(t_command *cmd, t_shell *shell)
{
	int		saved_stdin;
	int		saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (ft_setup_redirection(cmd, shell) != -1)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

int	ft_setup_input_redirection(t_command *cmd, t_shell *shell)
{
	int	fd;

	if (cmd->heredoc && cmd->heredoc_fd != -1)
	{
		dup2(cmd->heredoc_fd, STDIN_FILENO);
		close(cmd->heredoc_fd);
		return (0);
	}
	if (cmd->heredoc)
		return (ft_setup_heredoc(cmd, shell));
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
			if (errno == ENOENT)
				ft_puterror("No such file or directory", cmd->outfile);
			else if (errno == EACCES)
				ft_puterror("Permission denied", cmd->outfile);
			else
				ft_puterror("Permission denied", cmd->outfile);
			return (-1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

int	ft_setup_redirection(t_command *cmd, t_shell *shell)
{
	if (ft_setup_input_redirection(cmd, shell) == -1)
		return (-1);
	if (ft_setup_output_redirection(cmd) == -1)
		return (-1);
	return (0);
}

void	ft_executor(t_command *cmd_list, t_shell *shell)
{
	if (!cmd_list)
		return ;
	if (cmd_list->heredoc && (!cmd_list->argv || !cmd_list->argv[0]))
	{
		ft_handle_heredoc_only(cmd_list, shell);
		return ;
	}
	if (ft_has_pipes(cmd_list))
		ft_execute_pipeline(cmd_list, shell);
	else
	{
		if (ft_is_builtin(cmd_list))
			ft_exec_builtin(cmd_list, shell);
		else
			ft_fork_and_exec(cmd_list, shell);
	}
}
