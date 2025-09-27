/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:37:19 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/26 16:45:36 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_token_list(t_token **tokens)
{
	t_token	*tmp;

	if (!tokens || !*tokens)
		return ;
	while (*tokens)
	{
		tmp = (*tokens)->next;
		if ((*tokens)->value)
			free((*tokens)->value);
		free(*tokens);
		*tokens = tmp;
	}
	*tokens = NULL;
}

void	ft_free_split(char **s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	s = NULL;
}

void	ft_free_str_array(char **v)
{
	size_t	i;

	if (!v)
		return ;
	i = 0;
	while (v[i])
	{
		free(v[i]);
		i++;
	}
	free(v);
}

void	ft_cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->live_tokens)
	{
		ft_free_token_list(&shell->live_tokens);
		shell->live_tokens = NULL;
	}
	if (shell->live_commands)
	{
		ft_free_command_list(&shell->live_commands);
		shell->live_commands = NULL;
	}
	ft_enable_echoctl();
	if (shell->envp)
	{
		ft_free_split(shell->envp);
		shell->envp = NULL;
	}
}
