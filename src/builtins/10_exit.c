/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:16:28 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/30 13:45:23 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_numeric_string(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exec_builtin_exit(t_command *cmd, t_shell *shell)
{
	int	code;

	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	if (!cmd->argv[1])
		exit(shell->exit_status);
	if (!ft_is_numeric_string(cmd->argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(2);
	}
	if (cmd->argv[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		shell->exit_status = 1;
		return (1);
	}
	code = ft_atoi(cmd->argv[1]);
	exit((unsigned char)code);
}
