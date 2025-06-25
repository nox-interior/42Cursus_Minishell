/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:37:19 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/23 12:36:03 by amarroyo         ###   ########.fr       */
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
