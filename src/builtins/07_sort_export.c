/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_sort_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:23:22 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/23 15:23:58 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_copy_env_export(char **envp)
{
	int		count;
	char	**copy;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	copy = malloc((count + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	ft_sort_strs_ascii(char **arr)
{
	int		i;
	int		sorted;
	char	*tmp;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (arr[i] && arr[i + 1])
		{
			if (ft_strncmp(arr[i], arr[i + 1], ft_strlen(arr[i]) + 1) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
}

static void	ft_print_export_entry(char *entry)
{
	char	*equal;
	char	*name;
	char	*value;

	equal = ft_strchr(entry, '=');
	if (!equal)
		return ;
	name = ft_substr(entry, 0, equal - entry);
	value = equal + 1;
	if (name)
	{
		printf("declare -x %s=\"%s\"\n", name, value);
		free(name);
	}
}

void	ft_export_print_sorted(char **envp)
{
	char	**copy;
	int		i;

	copy = ft_copy_env_export(envp);
	if (!copy)
		return ;
	ft_sort_strs_ascii(copy);
	i = 0;
	while (copy[i])
	{
		ft_print_export_entry(copy[i]);
		i++;
	}
	ft_free_split(copy);
}
