/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_executor_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 00:00:00 by nox               #+#    #+#             */
/*   Updated: 2025/09/08 10:26:32 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_build_cmd_path(const char *dir, const char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}

static int	ft_check_cmd_access(char *full_path, char **dir, t_shell *shell)
{
	if (access(full_path, F_OK) == 0)
	{
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(dir);
			return (1);
		}
		else
		{
			ft_free_split(dir);
			free(full_path);
			shell->exit_status = 126;
			ft_puterror("Permission denied", NULL);
			return (-1);
		}
	}
	free(full_path);
	return (0);
}

static char	**ft_get_path_dirs(const char *cmd, t_shell *shell)
{
	char	*path;

	path = getenv("PATH");
	if (!path)
	{
		ft_puterror("No such file or directory", (char *)cmd);
		shell->exit_status = 127;
		return (NULL);
	}
	return (ft_split(path, ':'));
}

char	*ft_find_in_path(const char *cmd, t_shell *shell)
{
	char	**dir;
	char	*full_path;
	int		i;
	int		access_result;

	dir = ft_get_path_dirs(cmd, shell);
	if (!dir)
		return (NULL);
	i = 0;
	while (dir[i])
	{
		full_path = ft_build_cmd_path(dir[i], cmd);
		if (!full_path)
			continue ;
		access_result = ft_check_cmd_access(full_path, dir, shell);
		if (access_result == 1)
			return (full_path);
		if (access_result == -1)
			return (NULL);
		i++;
	}
	ft_free_split(dir);
	ft_puterror("cmd not found", (char *)cmd);
	shell->exit_status = 127;
	return (NULL);
}

char	*ft_get_cmd_path(t_command *cmd, t_shell *shell)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (NULL);
	if (cmd->argv[0][0] == '/' || cmd->argv[0][0] == '.'
		|| ft_strchr(cmd->argv[0], '/'))
	{
		if (ft_validate_path(cmd->argv[0], shell))
			return (cmd->argv[0]);
		return (NULL);
	}
	return (ft_find_in_path(cmd->argv[0], shell));
}
