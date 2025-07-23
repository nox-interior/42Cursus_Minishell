/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_builtin_executor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:04:01 by amarroyo          #+#    #+#             */
/*   Updated: 2025/07/23 12:45:13 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_builtin(t_command *cmd)
{
	char	*cmd_name;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (false);
	cmd_name = cmd->argv[0];
	return (ft_strcmp(cmd_name, "echo") == 0 || ft_strcmp(cmd_name, "cd") == 0
		|| ft_strcmp(cmd_name, "pwd") == 0 || ft_strcmp(cmd_name, "export") == 0
		|| ft_strcmp(cmd_name, "unset") == 0 || ft_strcmp(cmd_name, "env") == 0
		|| ft_strcmp(cmd_name, "exit") == 0);
}

int	ft_exec_builtin(t_command *cmd, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;
	int	result;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (ft_setup_redirection(cmd) == -1)
	{
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		result = ft_exec_builtin_echo(cmd, shell);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		result = ft_exec_builtin_cd(cmd, shell);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		result = ft_exec_builtin_pwd(cmd, shell);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		result = ft_exec_builtin_env(cmd, shell);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		result = ft_exec_builtin_export(cmd, shell);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		result = ft_exec_builtin_unset(cmd, shell);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		result = ft_exec_builtin_exit(cmd, shell);
	else
		result = 0;
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (result);
}
