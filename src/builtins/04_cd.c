/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:15:03 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/19 11:53:14 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_expand_tilde(const char *path, t_shell *shell)
{
	char	*home;
	char	*res;

	if (path[0] != '~')
		return (NULL);
	home = ft_get_env_value(shell->envp, "HOME");
	if (!home)
		return (NULL);
	res = ft_strjoin(home, path + 1);
	return (res);
}

static char	*ft_get_cd_target(t_command *cmd, t_shell *shell)
{
	char	*home;

	if (!cmd->argv[1])
	{
		home = ft_get_env_value(shell->envp, "HOME");
		if (!home)
			return (NULL);
		return (ft_strdup(home));
	}
	if (cmd->argv[1][0] == '~')
		return (ft_expand_tilde(cmd->argv[1], shell));
	return (ft_strdup(cmd->argv[1]));
}

static int	ft_change_directory(const char *path, t_shell *shell)
{
	if (!path || chdir(path) < 0)
	{
		perror("minishell: cd");
		shell->exit_status = errno;
		return (errno);
	}
	shell->exit_status = 0;
	return (0);
}

static const char	*ft_oldpwd_or_empty(char *oldpwd)
{
	if (oldpwd)
		return (oldpwd);
	return ("");
}

int	ft_exec_builtin_cd(t_command *cmd, t_shell *shell)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;
	char	*target;

	oldpwd = ft_get_env_value(shell->envp, "PWD");
	target = ft_get_cd_target(cmd, shell);
	if (ft_change_directory(target, shell) != 0)
	{
		free(target);
		return (shell->exit_status);
	}
	free(target);
	ft_update_env_var(&shell->envp, "OLDPWD", ft_oldpwd_or_empty(oldpwd));
	getcwd(cwd, sizeof(cwd));
	ft_update_env_var(&shell->envp, "PWD", cwd);
	return (shell->exit_status);
}
