/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_builtin_executor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:04:01 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/25 18:32:28 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_builtin(t_command *cmd)
{
	char	*cmd_name;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (false);
	cmd_name = cmd->argv[0];
	return (ft_strcmp(cmd_name, "echo") == 0
		|| ft_strcmp(cmd_name, "cd") == 0
		|| ft_strcmp(cmd_name, "pwd") == 0
		|| ft_strcmp(cmd_name, "export") == 0
		|| ft_strcmp(cmd_name, "unset") == 0
		|| ft_strcmp(cmd_name, "env") == 0
		|| ft_strcmp(cmd_name, "exit") == 0);
}

int	ft_exec_builtin(t_command *cmd, t_shell *shell)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (ft_exec_builtin_echo(cmd, shell));
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (ft_exec_builtin_cd(cmd, shell));
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (ft_exec_builtin_pwd(cmd, shell));
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (ft_exec_builtin_env(cmd, shell));
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (ft_exec_builtin_export(cmd, shell));
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (ft_exec_builtin_unset(cmd, shell));
	return (0);
}
