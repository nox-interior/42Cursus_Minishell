/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_builtin_executor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:04:01 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/26 17:10:08 by amarroyo         ###   ########.fr       */
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

static int	save_stdio(int *in, int *out)
{
	*in = dup(STDIN_FILENO);
	*out = dup(STDOUT_FILENO);
	if (*in == -1 || *out == -1)
	{
		if (*in != -1)
			close(*in);
		if (*out != -1)
			close(*out);
		perror("dup");
		return (-1);
	}
	return (0);
}

static int	restore_stdio(int in, int out)
{
	if (dup2(in, STDIN_FILENO) == -1 || dup2(out, STDOUT_FILENO) == -1)
	{
		close(in);
		close(out);
		perror("dup2");
		return (-1);
	}
	close(in);
	close(out);
	return (0);
}

int	ft_exec_builtin(t_command *cmd, t_shell *shell)
{
	int	in;
	int	out;
	int	result;
	int	is_exit;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	if (save_stdio(&in, &out) == -1)
		return (1);
	is_exit = (ft_strcmp(cmd->argv[0], "exit") == 0);
	if (ft_setup_redirection(cmd, shell) == -1)
	{
		close(in);
		close(out);
		return (1);
	}
	if (is_exit)
	{
		if (restore_stdio(in, out) == -1)
			return (1);
		return (ft_execute_builtin_cmd(cmd, shell));
	}
	result = ft_execute_builtin_cmd(cmd, shell);
	restore_stdio(in, out);
	return (result);
}
