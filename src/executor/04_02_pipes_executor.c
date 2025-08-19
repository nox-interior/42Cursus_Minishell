/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_02_pipes_executor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:08:43 by amarroyo          #+#    #+#             */
/*   Updated: 2025/08/19 15:07:15 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_cmd_path(t_command *cmd, t_shell *shell)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (NULL);
	if (cmd->argv[0][0] == '/' || cmd->argv[0][0] == '.')
		return (cmd->argv[0]);
	return (ft_find_in_path(cmd->argv[0], shell));
}

static void	ft_setup_child_pipes(int **pipes, int i, int pipe_count,
		t_command *current)
{
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (current->next)
		dup2(pipes[i][1], STDOUT_FILENO);
	ft_close_all_pipes(pipes, pipe_count);
}

static void	ft_execute_single_command(t_command *current, int **pipes, int i,
		int pipe_count, t_shell *shell)
{
	pid_t	pid;
	char	*cmd_path;

	pid = fork();
	if (pid == 0)
	{
		ft_setup_child_signals();
		ft_setup_child_pipes(pipes, i, pipe_count, current);
		if (ft_setup_redirection(current) == -1)
			exit(1);
		cmd_path = ft_get_cmd_path(current, shell);
		if (!cmd_path)
			exit(127);
		execve(cmd_path, current->argv, shell->envp);
		exit(127);
	}
}

static void	ft_execute_all_commands(t_command *cmd_list, int **pipes,
		int pipe_count, t_shell *shell)
{
	t_command	*current;
	int			i;

	current = cmd_list;
	i = 0;
	while (current)
	{
		ft_execute_single_command(current, pipes, i, pipe_count, shell);
		current = current->next;
		i++;
	}
}

void	ft_execute_pipeline(t_command *cmd_list, t_shell *shell)
{
	int	pipe_count;
	int	**pipes;

	pipe_count = ft_count_commands(cmd_list);
	pipes = ft_create_pipes(pipe_count);
	if (!pipes)
		return ;
	ft_execute_all_commands(cmd_list, pipes, pipe_count, shell);
	ft_close_all_pipes(pipes, pipe_count);
	ft_wait_all_children(pipe_count + 1);
}
