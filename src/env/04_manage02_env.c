/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_manage02_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:28:57 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/19 11:38:09 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_alloc_env(char ***new_env, int count)
{
	*new_env = malloc(sizeof(char *) * (count + 2));
	if (!*new_env)
		return (1);
	return (0);
}

static void	ft_copy_env_pointers(char **src, char **dest)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
}

static int	ft_join_var(char **joined, const char *name, const char *value)
{
	char	*tmp;

	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (1);
	*joined = ft_strjoin(tmp, value);
	free(tmp);
	if (!*joined)
		return (1);
	return (0);
}

int	ft_append_env_var(char ***envp, const char *name, const char *value)
{
	int		count;
	char	**new_env;
	char	*joined;

	count = 0;
	while ((*envp)[count])
		count++;
	if (ft_alloc_env(&new_env, count))
		return (1);
	ft_copy_env_pointers(*envp, new_env);
	if (ft_join_var(&joined, name, value))
	{
		free(new_env);
		return (1);
	}
	new_env[count] = joined;
	new_env[count + 1] = NULL;
	free(*envp);
	*envp = new_env;
	return (0);
}
