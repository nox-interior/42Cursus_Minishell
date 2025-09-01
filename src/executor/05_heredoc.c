/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:45:00 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/01 16:12:54 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_create_heredoc_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

int	ft_setup_heredoc(t_command *cmd, t_shell *shell)
{
	int	pipefd[2];

	if (ft_create_heredoc_pipe(pipefd) == -1)
		return (-1);
	if (ft_read_heredoc_lines(pipefd[1], cmd->delimit, shell) == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	return (0);
}
