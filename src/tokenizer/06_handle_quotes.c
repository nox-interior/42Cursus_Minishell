/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_handle_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:01:17 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/02 18:47:46 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*ft_get_last_token(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

static int	ft_handle_double_quote_token(t_token **tokens, const char *prompt,
		int i, char *quoted, int quote_start)
{
	char	*rest;
	char	*joined;
	char	*final_joined;
	int		start;
	t_token	*last_token;
	int		should_concatenate;

	should_concatenate = (quote_start > 0 && !ft_isspace(prompt[quote_start
				- 1]));
	start = i;
	while (prompt[i] && !ft_isspace(prompt[i]) && prompt[i] != '|'
		&& prompt[i] != '<' && prompt[i] != '>' && prompt[i] != '\''
		&& prompt[i] != '\"')
		i++;
	if (i > start)
	{
		rest = ft_substr(prompt, start, i - start);
		if (!rest)
			return (-1);
		joined = ft_strjoin(quoted, rest);
		free(quoted);
		free(rest);
		if (!joined)
			return (-1);
		last_token = ft_get_last_token(*tokens);
		if (last_token && last_token->type == T_WORD && should_concatenate)
		{
			final_joined = ft_strjoin(last_token->value, joined);
			free(joined);
			free(last_token->value);
			if (!final_joined)
				return (-1);
			last_token->value = final_joined;
		}
		else
			ft_add_token(tokens, ft_new_token(T_WORD, joined));
	}
	else
	{
		last_token = ft_get_last_token(*tokens);
		if (last_token && last_token->type == T_WORD && should_concatenate)
		{
			final_joined = ft_strjoin(last_token->value, quoted);
			free(quoted);
			free(last_token->value);
			if (!final_joined)
				return (-1);
			last_token->value = final_joined;
		}
		else
			ft_add_token(tokens, ft_new_token(T_D_QUOTE, quoted));
	}
	return (i);
}

static int	ft_handle_single_quote_token(t_token **tokens, char *quoted, int i)
{
	ft_add_token(tokens, ft_new_token(T_S_QUOTE, quoted));
	return (i);
}

int	ft_handle_quote_token(t_token **tokens, const char *prompt, int i)
{
	char	quote;
	char	*quoted;
	int		quote_start;

	quote_start = i;
	quote = prompt[i];
	quoted = ft_quotes_token(prompt, &i);
	if (!quoted)
		return (-1);
	if (quote == '"')
		return (ft_handle_double_quote_token(tokens, prompt, i, quoted,
				quote_start));
	else
		return (ft_handle_single_quote_token(tokens, quoted, i));
}
