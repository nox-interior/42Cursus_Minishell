/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:00:25 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/12 13:59:15 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_handle_child_status(int status)
{
	if (WIFEXITED(status))
		ft_set_exit_status(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		ft_set_exit_status(128 + WTERMSIG(status));
}

static void	ft_fork_and_exec(t_command *cmd, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		ft_set_exit_status(1);
		return ;
	}
	if (pid == 0)
	{
		execve(cmd->argv[0], cmd->argv, envp);
		perror("minishell");
		exit(127);
	}
	waitpid(pid, &status, 0);
	ft_handle_child_status(status);
}

void	ft_executor(t_command *cmd_list, char **envp)
{
	if (!cmd_list || !cmd_list->argv || !cmd_list->argv[0])
	{
		ft_set_exit_status(0);
		return ;
	}
	if (ft_is_builtin(cmd_list))
	{
		(ft_exec_builtin(cmd_list, envp));
		return ;
	}
	ft_fork_and_exec(cmd_list, envp);
}
