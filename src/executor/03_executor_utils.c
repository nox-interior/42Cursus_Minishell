/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_executor_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 00:00:00 by nox               #+#    #+#             */
/*   Updated: 2025/09/16 12:02:25 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_validate_path(const char *path, t_shell *shell)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
	{
		ft_puterror("No such file or directory", (char *)path);
		shell->exit_status = 127;
		return (0);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_puterror("Is a directory", (char *)path);
		shell->exit_status = 126;
		return (0);
	}
	if (access(path, X_OK) != 0)
	{
		ft_puterror("Permission denied", (char *)path);
		shell->exit_status = 126;
		return (0);
	}
	return (1);
}

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
		if (cmd_path != cmd->argv[0])
			free(cmd_path);
		return ;
	}
	if (pid == 0)
		ft_exec_child_process(cmd, shell, cmd_path);
	ft_setup_exec_signals();
	waitpid(pid, &status, 0);
	ft_setup_signals();
	ft_handle_child_status(status, shell);
	if (cmd_path != cmd->argv[0])
		free(cmd_path);
}
