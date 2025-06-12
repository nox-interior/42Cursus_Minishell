/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_var_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:01:49 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/12 14:01:16 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_char(char *str, char c)
{
	char	*res;
	size_t	len;

	if (!str)
		return (ft_strdup(""));
	len = ft_strlen(str);
	res = malloc(len + 2);
	if (!res)
		return (NULL);
	ft_strlcpy(res, str, len + 1);
	res[len] = c;
	res[len + 1] = '\0';
	return (res);
}

static char	*ft_get_var_value(char *name, char **envp)
{
	int		i;
	size_t	len;

	if (!name || !*name)
		return (ft_strdup(""));
	if (ft_strncmp(name, "?", 2) == 0)
	{
		char *val = ft_itoa(ft_get_exit_status());
		return (val);
	}
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

static void	ft_append_expanded(char **result, char *input, int *i, char **envp)
{
	int		j;
	char	*name;
	char	*value;
	char	*tmp;

	(*i)++;
	j = *i;
	if (input[j] == '?')
		j++;
	else
		while (input[j] && (ft_isalnum(input[j]) || input[j] == '_'))
			j++;
	name = ft_substr(input, *i, j - *i);
	value = ft_get_var_value(name, envp);
	tmp = ft_strjoin(*result, value);
	free(*result);
	free(name);
	free(value);
	*result = tmp;
	*i = j;
}

char	*ft_expand_value(char *input, char **envp)
{
	char	*result;
	char	*tmp;
	int		i;

	i = 0;
	result = ft_calloc(1, 1);
	if (!result)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] && (ft_isalpha(input[i + 1])
				|| input[i + 1] == '_' || input[i + 1] == '?'))
			ft_append_expanded(&result, input, &i, envp);
		else
		{
			tmp = ft_strjoin_char(result, input[i]);
			free(result);
			result = tmp;
			i++;
		}
	}
	return (result);
}

void	ft_expand_variables(t_token *token_list, char **envp)
{
	t_token	*current;
	char	*expanded;

	current = token_list;
	while (current)
	{
		if ((current->type == T_WORD || current->type == T_VAR
				|| current->type == T_D_QUOTE) && ft_strchr(current->value,
				'$'))
		{
			expanded = ft_expand_value(current->value, envp);
			free(current->value);
			current->value = expanded;
			current->type = T_WORD;
		}
		current = current->next;
	}
}
