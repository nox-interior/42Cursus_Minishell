/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:45:00 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/01 15:53:01 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_should_expand_vars(const char *delimit)
{
	int	len;

	if (!delimit)
		return (1);
	len = ft_strlen(delimit);
	if (len < 2)
		return (1);
	if ((delimit[0] == '"' && delimit[len - 1] == '"')
		|| (delimit[0] == '\'' && delimit[len - 1] == '\''))
		return (0);
	return (1);
}

static char	*ft_clean_delimit(char *delimit)
{
	int		len;
	char	*clean;

	if (!delimit)
		return (NULL);
	len = ft_strlen(delimit);
	if (len >= 2 && ((delimit[0] == '"' && delimit[len - 1] == '"')
			|| (delimit[0] == '\'' && delimit[len - 1] == '\'')))
	{
		clean = ft_substr(delimit, 1, len - 2);
		return (clean);
	}
	return (ft_strdup(delimit));
}

static int	ft_create_heredoc_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	return (0);
}

static int	ft_read_heredoc_lines(int write_fd, char *delimit, t_shell *shell)
{
	char	*line;
	char	*expanded;
	char	*clean_delim;
	int		should_expand;

	clean_delim = ft_clean_delimit(delimit);
	if (!clean_delim)
		return (-1);
	should_expand = ft_should_expand_vars(delimit);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, clean_delim) == 0)
		{
			free(line);
			break ;
		}
		if (should_expand)
			expanded = ft_expand_value(line, shell);
		else
			expanded = ft_strdup(line);
		write(write_fd, expanded, ft_strlen(expanded));
		write(write_fd, "\n", 1);
		free(line);
		free(expanded);
	}
	free(clean_delim);
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
