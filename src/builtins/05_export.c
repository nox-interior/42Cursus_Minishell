/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:51:12 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/19 11:53:30 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_export_line(char *env_var)
{
	char	*equal;
	char	*name;
	char	*value;

	equal = ft_strchr(env_var, '=');
	if (!equal)
		return ;
	name = ft_substr(env_var, 0, equal - env_var);
	value = equal + 1;
	if (!name)
		return ;
	printf("declare -x %s=\"%s\"\n", name, value);
	free(name);
}

static void	ft_export_print_all(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_print_export_line(envp[i]);
		i++;
	}
}

static void	ft_export_put_error(t_shell *shell)
{
	ft_putstr_fd("minishell: export: malloc error\n", 2);
	shell->exit_status = 1;
}

static void	ft_export_set_var(char *arg, t_shell *shell)
{
	char	*equal;
	char	*name;
	char	*value;
	int		res;

	equal = ft_strchr(arg, '=');
	if (!equal)
		return ;
	name = ft_substr(arg, 0, equal - arg);
	value = ft_strdup(equal + 1);
	if (!name || !value)
	{
		free(name);
		free(value);
		ft_export_put_error(shell);
		return ;
	}
	res = ft_update_env_var(&shell->envp, name, value);
	if (res != 0)
		ft_export_put_error(shell);
	free(name);
	free(value);
}

int	ft_exec_builtin_export(t_command *cmd, t_shell *shell)
{
	int	i;

	if (!cmd->argv[1])
	{
		ft_export_print_all(shell->envp);
		shell->exit_status = 0;
		return (0);
	}
	i = 1;
	while (cmd->argv[i])
	{
		ft_export_set_var(cmd->argv[i], shell);
		i++;
	}
	shell->exit_status = 0;
	return (0);
}
