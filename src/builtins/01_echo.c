/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:54:33 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/16 17:44:49 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_builtin_echo(t_command *cmd, t_shell *shell)
{
	char	**argv;
	int		i;
	int		newline;

	argv = cmd->argv;
	i = 1;
	newline = 1;
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
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
