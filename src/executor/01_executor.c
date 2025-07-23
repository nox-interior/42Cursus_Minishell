/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:00:25 by amarroyo          #+#    #+#             */
/*   Updated: 2025/07/23 12:08:15 by amarroyo         ###   ########.fr       */
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

static char	*ft_find_in_path(const char *cmd, t_shell *shell)
{
	char	*path;
	char	**dir;
	char	*full_path;
	int		i;

	path = getenv("PATH");
	if (!path)
	{
		ft_puterror("No such file or directory", (char *)cmd);
		shell->exit_status = 127;
		return (NULL);
	}
	dir = ft_split(path, ':');
	i = 0;
	while (dir[i])
	{
		full_path = ft_strjoin(dir[i], "/");
		full_path = ft_strjoin(full_path, cmd);
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == 0)
			{
				ft_free_split(dir);
				return (full_path);
			}
			else
			{
				ft_free_split(dir);
				shell->exit_status = 126;
				ft_puterror("Permission denied", NULL);
				return (NULL);
			}
		}
		i++;
	}
	ft_free_split(dir);
	ft_puterror("cmd not found", (char *)cmd);
	shell->exit_status = 127;
	return (NULL);
}

static int	ft_setup_input_redirection(t_command *cmd)
{
	int	fd_in;

	if (!cmd->infile)
		return (0);
	fd_in = open(cmd->infile, O_RDONLY);
	if (fd_in == -1)
		return (perror("minishell"), -1);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	return (0);
}

static int	ft_setup_output_redirection(t_command *cmd)
{
	int	fd_out;
	int	flags;

	if (!cmd->outfile)
		return (0);
	flags = O_WRONLY | O_CREAT;
	if (cmd->append)
		flags = flags | O_APPEND;
	else
		flags = flags | O_TRUNC;
	fd_out = open(cmd->outfile, flags, 0644);
	if (fd_out == -1)
		return (perror("minishell"), -1);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return (0);
}

static int	ft_setup_redirection(t_command *cmd)
{
	if (ft_setup_input_redirection(cmd) == -1)
		return (-1);
	if (ft_setup_output_redirection(cmd) == -1)
		return (-1);
	return (0);
}

static void	ft_fork_and_exec(t_command *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	if (cmd->argv[0][0] == '/' || cmd->argv[0][0] == '.')
		cmd_path = cmd->argv[0];
	else
		cmd_path = ft_find_in_path(cmd->argv[0], shell);
	if (!cmd_path)
		return ;
	pid = fork();
	if (pid < 0)
	{
		ft_print_fd_error("fork");
		shell->exit_status = 1;
		return ;
	}
	if (pid == 0)
	{
		if (ft_setup_redirection(cmd) == -1)
			exit(1);
		execve(cmd_path, cmd->argv, shell->envp);
		ft_print_exec_error(cmd_path);
		exit(127);
	}
	waitpid(pid, &status, 0);
	ft_handle_child_status(status, shell);
}

static int	ft_setup_input_redirection(t_command *cmd)
{
	int	fd_in;

	if (!cmd->infile)
		return (0);
	fd_in = open(cmd->infile, O_RDONLY);
	if (fd_in == -1)
		return (perror("minishell"), -1);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	return (0);
}

static int	ft_setup_output_redirection(t_command *cmd)
{
	int	fd_out;
	int	flags;

	if (!cmd->outfile)
		return (0);
	flags = O_WRONLY | O_CREAT;
	if (cmd->append)
		flags = flags | O_APPEND;
	else
		flags = flags | O_TRUNC;
	fd_out = open(cmd->outfile, flags, 0644);
	if (fd_out == -1)
		return (perror("minishell"), -1);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return (0);
}

static int	ft_setup_redirection(t_command *cmd)
{
	if (ft_setup_input_redirection(cmd) == -1)
		return (-1);
	if (ft_setup_output_redirection(cmd) == -1)
		return (-1);
	return (0);
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
