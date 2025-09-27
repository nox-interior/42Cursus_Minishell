/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:54:57 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/16 19:15:22 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_builtin_env(t_command *cmd, t_shell *shell)
{
	int	i;

	if (cmd->argv[1])
	{
		ft_printf("minishell: env: '%s': No such file or directory\n",
			cmd->argv[1]);
		shell->exit_status = 127;
		return (127);
	}
	i = 0;
	while (shell->envp[i])
	{
		write(1, shell->envp[i], ft_strlen(shell->envp[i]));
		write(1, "\n", 1);
		i++;
	}
	shell->exit_status = 0;
	return (0);
}
