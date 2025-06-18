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

static char	*ft_find_in_path(const char *cmd)
{
	char	*path;
	char	**dir;
	char	*full_path;
	int		i;

	cmd = ft_strjoin("/", cmd);
	path = getenv("PATH");
	if (!path)
		return (NULL); //minishell: <cmd>: No such file or directory //(127)
	dir = ft_split(path, ':');
	i = 0;
	while (dir[i] != NULL)
	{
		full_path = ft_strjoin(dir[i], cmd);
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == 0)
				return (full_path); // liberar dir??
			else
				return (); //minishell: <full_path>: Permission denied //(126)
		}
		i++;
	}
	//liberar dir o algo mas??
	return (NULL); //<cmd>: cmd not found //(127)
}

static void	ft_fork_and_exec(t_command *cmd, char **envp)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	if (cmd->argv[0][0] == '/')
		cmd_path = cmd->argv[0];
	else
		cmd_path = ft_find_in_path(cmd->argv[0]);
	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		ft_set_exit_status(1);
		return ;
	}
	if (pid == 0)
	{
		execve(cmd_path, cmd->argv, envp);
		perror("minishell");
		exit(127); //liberacion??
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
