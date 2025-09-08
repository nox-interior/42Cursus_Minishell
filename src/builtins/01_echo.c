/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:54:33 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/08 13:56:23 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_handle_echo_n_flag(char **argv, int *i)
{
	int	newline;

	newline = 1;
	if (argv[1] && (ft_strcmp(argv[1], "-n") == 0 || (ft_strncmp(argv[1], "-n",
					2) == 0 && argv[1][2] != '\0')))
	{
		newline = 0;
		if (ft_strcmp(argv[1], "-n") == 0)
			*i = 2;
		else
		{
			write(1, argv[1] + 2, ft_strlen(argv[1] + 2));
			*i = 2;
		}
	}
	return (newline);
}

int	ft_exec_builtin_echo(t_command *cmd, t_shell *shell)
{
	char	**argv;
	int		i;
	int		newline;

	argv = cmd->argv;
	i = 1;
	newline = ft_handle_echo_n_flag(argv, &i);
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	shell->exit_status = 0;
	return (0);
}
