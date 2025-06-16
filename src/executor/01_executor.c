/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:00:25 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/16 18:56:49 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_handle_child_status(int status, t_shell *shell)
{
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}

static void	ft_fork_and_exec(t_command *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		shell->exit_status = 1;
		return ;
	}
	if (pid == 0)
	{
		execve(cmd->argv[0], cmd->argv, shell->envp);
		perror("minishell");
		exit(127);
	}
	waitpid(pid, &status, 0);
	ft_handle_child_status(status, shell);
}

void	ft_executor(t_command *cmd_list, t_shell *shell)
{
	if (!cmd_list || !cmd_list->argv || !cmd_list->argv[0])
	{
		shell->exit_status = 0;
		return ;
	}
	if (ft_is_builtin(cmd_list))
	{
		shell->exit_status = ft_exec_builtin(cmd_list, shell);
		return ;
	}
	ft_fork_and_exec(cmd_list, shell);
}
