/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_02_pipes_executor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:08:43 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/08 09:23:59 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_setup_child_pipes(int **pipes, int i, int pipe_count,
		t_command *current)
{
	if (i > 0)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
	}
	if (current->next)
	{
		dup2(pipes[i][1], STDOUT_FILENO);
	}
	ft_close_all_pipes(pipes, pipe_count);
}

static void	ft_setup_and_exec(t_pipe_params *params)
{
	char	*cmd_path;

	if (ft_setup_redirection(params->current, params->shell) == -1)
		exit(1);
	cmd_path = ft_get_cmd_path(params->current, params->shell);
	if (!cmd_path)
		exit(127);
	execve(cmd_path, params->current->argv, params->shell->envp);
	exit(127);
}

static void	ft_execute_single_command(t_pipe_params *params)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_setup_child_signals();
		ft_setup_child_pipes(params->pipes, params->i, params->pipe_count,
			params->current);
		ft_setup_and_exec(params);
	}
}

static void	ft_execute_all_commands(t_command *cmd_list, int **pipes,
		int pipe_count, t_shell *shell)
{
	t_command		*current;
	t_pipe_params	params;
	int				i;

	current = cmd_list;
	i = 0;
	while (current)
	{
		params.current = current;
		params.pipes = pipes;
		params.i = i;
		params.pipe_count = pipe_count;
		params.shell = shell;
		ft_execute_single_command(&params);
		current = current->next;
		i++;
	}
}

void	ft_execute_pipeline(t_command *cmd_list, t_shell *shell)
{
	int	pipe_count;
	int	**pipes;

	if (!cmd_list)
		return ;
	if (ft_preprocess_heredocs(cmd_list, shell) == -1)
		return ;
	pipe_count = ft_count_commands(cmd_list);
	pipes = ft_create_pipes(pipe_count);
	if (!pipes)
		return ;
	ft_execute_all_commands(cmd_list, pipes, pipe_count, shell);
	ft_close_all_pipes(pipes, pipe_count);
	ft_setup_exec_signals();
	ft_wait_all_children(pipe_count + 1);
	ft_setup_signals();
}
