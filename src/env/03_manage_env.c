/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_manage_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:01:07 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/19 11:53:58 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env_value(char **envp, const char *name)
{
	int	len;
	int	i;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	ft_find_env_index(char **envp, const char *name)
{
	int	len;
	int	i;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_replace_env_var(char **envp, int idx, const char *name, const char *val)
{
	char	*pair;
	char	*new;

	pair = ft_strjoin(name, "=");
	if (!pair)
		return (1);
	new = ft_strjoin(pair, val);
	free(pair);
	if (!new)
		return (1);
	free(envp[idx]);
	envp[idx] = new;
	return (0);
}

int	ft_update_env_var(char ***envp, const char *name, const char *value)
{
	int	idx;

	idx = ft_find_env_index(*envp, name);
	if (idx >= 0)
		return (ft_replace_env_var(*envp, idx, name, value));
	return (ft_append_env_var(envp, name, value));
}
