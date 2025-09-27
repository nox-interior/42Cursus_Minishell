/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:22:57 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/04 13:54:07 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Revisar continue
t_token	*ft_tokenizer(const char *prompt)
{
	t_token	*token_list;
	int		i;

	i = 0;
	token_list = NULL;
	while (prompt[i])
	{
		if (ft_isspace(prompt[i]))
		{
			i++;
			continue ;
		}
		i = ft_create_token(&token_list, prompt, i);
		if (i == -1)
		{
			ft_free_token_list(&token_list);
			return (NULL);
		}
	}
	return (token_list);
}
