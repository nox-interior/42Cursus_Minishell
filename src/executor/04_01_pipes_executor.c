/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_01_pipes_executor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:08:28 by amarroyo          #+#    #+#             */
/*   Updated: 2025/07/24 14:15:48 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_all_pipes(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	ft_wait_all_children(int child_count)
{
	int	i;
	int	status;

	i = 0;
	while (i < child_count)
	{
		wait(&status);
		i++;
	}
}

int	ft_count_commands(t_command *cmd_list)
{
	t_command	*current;
	int			count;

	current = cmd_list;
	count = 0;
	while (current)
	{
		if (current->next)
			count++;
		current = current->next;
	}
	return (count);
}

int	**ft_create_pipes(int pipe_count)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * pipe_count);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < pipe_count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
			return (NULL);
		i++;
	}
	return (pipes);
}

int	ft_has_pipes(t_command *cmd_list)
{
	t_command	*current;

	current = cmd_list;
	while (current)
	{
		if (current->next)
			return (1);
		current = current->next;
	}
	return (0);
}
