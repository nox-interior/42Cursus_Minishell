/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_aux_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:04:16 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/30 13:12:20 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_env(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

static int	ft_should_remove(const char *entry, const char *name)
{
	size_t	len;

	len = ft_strlen(name);
	return (ft_strncmp(entry, name, len) == 0 && entry[len] == '=');
}

static char	**ft_alloc_env_copy(int count)
{
	char	**copy;

	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	copy[count] = NULL;
	return (copy);
}

static void	ft_copy_if_not_removed(char **src, char **dst, const char *name)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (!ft_should_remove(src[i], name))
			dst[j++] = ft_strdup(src[i]);
		i++;
	}
	dst[j] = NULL;
}

void	ft_remove_env_var(t_shell *shell, const char *name)
{
	int		count;
	char	**old_env;
	char	**new_env;

	old_env = shell->envp;
	count = ft_count_env(old_env);
	new_env = ft_alloc_env_copy(count);
	if (!new_env)
		return ;
	ft_copy_if_not_removed(old_env, new_env, name);
	ft_free_split(old_env);
	shell->envp = new_env;
}
