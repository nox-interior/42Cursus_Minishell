/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 00:00:00 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/01 17:38:50 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_should_expand_vars(const char *delimit)
{
	int	len;

	if (!delimit)
		return (1);
	len = ft_strlen(delimit);
	if (len < 2)
		return (1);
	if ((delimit[0] == '"' && delimit[len - 1] == '"') || (delimit[0] == '\''
			&& delimit[len - 1] == '\''))
		return (0);
	return (1);
}

char	*ft_clean_delimit(char *delimit)
{
	int		len;
	char	*clean;

	if (!delimit)
		return (NULL);
	len = ft_strlen(delimit);
	if (len < 2)
		return (ft_strdup(delimit));
	if ((delimit[0] == '"' && delimit[len - 1] == '"') || (delimit[0] == '\''
			&& delimit[len - 1] == '\''))
	{
		clean = ft_substr(delimit, 1, len - 2);
		return (clean);
	}
	return (ft_strdup(delimit));
}

char	*ft_read_line_from_stdin(void)
{
	char	buffer[1024];
	char	c;
	int		i;
	int		bytes_read;

	i = 0;
	while (i < 1023)
	{
		bytes_read = read(STDIN_FILENO, &c, 1);
		if (bytes_read <= 0)
			break ;
		if (c == '\n')
			break ;
		buffer[i++] = c;
	}
	buffer[i] = '\0';
	if (i == 0 && bytes_read <= 0)
		return (NULL);
	return (ft_strdup(buffer));
}

static int	ft_process_heredoc_line(char *line, int write_fd, int should_expand,
		t_shell *shell)
{
	char	*expanded;

	if (should_expand)
		expanded = ft_expand_value(line, shell);
	else
		expanded = ft_strdup(line);
	write(write_fd, expanded, ft_strlen(expanded));
	write(write_fd, "\n", 1);
	free(expanded);
	return (0);
}

int	ft_read_heredoc_lines(int write_fd, char *delimit, t_shell *shell)
{
	char	*line;
	char	*clean_delim;
	int		should_expand;

	clean_delim = ft_clean_delimit(delimit);
	if (!clean_delim)
		return (-1);
	should_expand = ft_should_expand_vars(delimit);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			line = readline("> ");
		else
			line = ft_read_line_from_stdin();
		if (!line || ft_strcmp(line, clean_delim) == 0)
		{
			free(line);
			break ;
		}
		ft_process_heredoc_line(line, write_fd, should_expand, shell);
		free(line);
	}
	free(clean_delim);
	return (0);
}
