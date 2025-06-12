/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:54:33 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/12 13:59:46 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_builtin_echo(t_command *cmd, char **envp)
{
	int i;
	int newline;
	
	(void)envp;
	i = 1;
	newline = 1;
	if (cmd->argv[1] && ft_strcmp(cmd->argv[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], 1);
		if (cmd->argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	ft_set_exit_status(0);
	return (0);
}
