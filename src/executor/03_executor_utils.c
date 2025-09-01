/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_executor_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 00:00:00 by nox               #+#    #+#             */
/*   Updated: 2025/09/01 15:53:01 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_handle_child_status(int status, t_shell *shell)
{
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}

static void	ft_exec_child_process(t_command *cmd, t_shell *shell, char *path)
{
	ft_setup_child_signals();
	if (ft_setup_redirection(cmd, shell) == -1)
		exit(1);
	execve(path, cmd->argv, shell->envp);
	ft_print_exec_error(path);
	exit(127);
}

static void	ft_handle_fork_error(t_shell *shell)
{
	ft_print_fd_error("fork");
	shell->exit_status = 1;
}

void	ft_fork_and_exec(t_command *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	cmd_path = ft_get_cmd_path(cmd, shell);
	if (!cmd_path)
		return ;
	pid = fork();
	if (pid < 0)
	{
		ft_handle_fork_error(shell);
		return ;
	}
	if (pid == 0)
		ft_exec_child_process(cmd, shell, cmd_path);
	waitpid(pid, &status, 0);
	ft_handle_child_status(status, shell);
}
