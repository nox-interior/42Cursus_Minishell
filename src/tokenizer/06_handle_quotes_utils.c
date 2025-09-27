/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_handle_quotes_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:00:00 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/02 18:57:35 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_get_last_token(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

int	ft_should_concatenate_quote(const char *prompt, int quote_start)
{
	return (quote_start > 0 && !ft_isspace(prompt[quote_start - 1]));
}

int	ft_concat_with_last_token(t_token **tokens, char *content)
{
	t_token	*last_token;
	char	*final_joined;

	last_token = ft_get_last_token(*tokens);
	if (!last_token || last_token->type != T_WORD)
	{
		ft_add_token(tokens, ft_new_token(T_WORD, content));
		return (1);
	}
	final_joined = ft_strjoin(last_token->value, content);
	free(content);
	free(last_token->value);
	if (!final_joined)
		return (-1);
	last_token->value = final_joined;
	return (1);
}

char	*ft_get_rest_after_quote(const char *prompt, int *i)
{
	char	*rest;
	int		start;

	start = *i;
	while (prompt[*i] && !ft_isspace(prompt[*i]) && prompt[*i] != '|'
		&& prompt[*i] != '<' && prompt[*i] != '>' && prompt[*i] != '\''
		&& prompt[*i] != '\"')
		(*i)++;
	if (*i > start)
	{
		rest = ft_substr(prompt, start, *i - start);
		return (rest);
	}
	return (NULL);
}
