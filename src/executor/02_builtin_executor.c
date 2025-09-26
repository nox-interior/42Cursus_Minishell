/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_builtin_executor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:04:01 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/26 15:18:41 by amarroyo         ###   ########.fr       */
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

static int	ft_execute_builtin_cmd(t_command *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (ft_exec_builtin_echo(cmd, shell));
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (ft_exec_builtin_cd(cmd, shell));
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (ft_exec_builtin_pwd(cmd, shell));
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (ft_exec_builtin_env(cmd, shell));
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (ft_exec_builtin_export(cmd, shell));
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (ft_exec_builtin_unset(cmd, shell));
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (ft_exec_builtin_exit(cmd, shell));
	return (0);
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
	if (ft_setup_redirection(cmd, shell) == -1)
	{
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	result = ft_execute_builtin_cmd(cmd, shell);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (result);
}

// int	ft_exec_builtin(t_command *cmd, t_shell *shell)
// {
// 	int	in_backup;
// 	int	out_backup;
// 	int	setup_status;
// 	int	status;

// 	in_backup = dup(STDIN_FILENO);
// 	out_backup = dup(STDOUT_FILENO);
// 	if (in_backup < 0 || out_backup < 0)
// 	{
// 		shell->exit_status = 1;
// 		return (1);
// 	}
// 	setup_status = ft_setup_redirection(cmd, shell);
// 	if (setup_status != 0)
// 	{
// 		dup2(in_backup, STDIN_FILENO);
// 		dup2(out_backup, STDOUT_FILENO);
// 		close(in_backup);
// 		close(out_backup);
// 		shell->exit_status = setup_status;
// 		return (setup_status);
// 	}
// 	status = ft_execute_builtin_cmd(cmd, shell);
// 	dup2(in_backup, STDIN_FILENO);
// 	dup2(out_backup, STDOUT_FILENO);
// 	close(in_backup);
// 	close(out_backup);
// 	shell->exit_status = status;
// 	return (status);
// }

// int	ft_exec_builtin(t_command *cmd, t_shell *shell)
// {
// 	int	saved_stdin;
// 	int	saved_stdout;
// 	int	status;

// 	if (!cmd || !cmd->argv || !cmd->argv[0])
// 		return (0);
// 	saved_stdin = dup(STDIN_FILENO);
// 	saved_stdout = dup(STDOUT_FILENO);
// 	if (saved_stdin == -1 || saved_stdout == -1)
// 	{
// 		if (saved_stdin != -1)
// 			close(saved_stdin);
// 		if (saved_stdout != -1)
// 			close(saved_stdout);
// 		return (1);
// 	}
// 	status = ft_execute_builtin_cmd(cmd, shell);
// 	if (dup2(saved_stdin, STDIN_FILENO) == -1)
// 		status = 1;
// 	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
// 		status = 1;
// 	close(saved_stdin);
// 	close(saved_stdout);
// 	return (status);
// }

// int	ft_exec_builtin(t_command *cmd, t_shell *shell)
// {
// 	int	saved_stdin;
// 	int	saved_stdout;
// 	int	status;
	
// 	saved_stdin = -1;
// 	saved_stdout = -1;
// 	if (!cmd || !cmd->argv || !cmd->argv[0])
// 		return (0);
// 	if (cmd->argv[0] && ft_strcmp(cmd->argv[0], "exit") == 0)
// 		return (ft_execute_builtin_cmd(cmd, shell));
// 	saved_stdin = dup(STDIN_FILENO);
// 	saved_stdout = dup(STDOUT_FILENO);
// 	if (saved_stdin == -1 || saved_stdout == -1)
// 	{
// 		if (saved_stdin != -1) close(saved_stdin);
// 		if (saved_stdout != -1) close(saved_stdout);
// 		return (1);
// 	}
// 	status = ft_execute_builtin_cmd(cmd, shell);
// 	if (dup2(saved_stdin, STDIN_FILENO) == -1) status = 1;
// 	if (dup2(saved_stdout, STDOUT_FILENO) == -1) status = 1;
// 	close(saved_stdin);
// 	close(saved_stdout);
// 	return (status);
// }
