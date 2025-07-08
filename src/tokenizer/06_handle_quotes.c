/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_handle_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:01:17 by amarroyo          #+#    #+#             */
/*   Updated: 2025/07/08 11:02:58 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_handle_double_quote_token(t_token **tokens, const char *prompt,
	int i, char *quoted)
{
	char	*rest;
	char	*joined;
	int		start;

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
		ft_add_token(tokens, ft_new_token(T_WORD, joined));
	}
	else
		ft_add_token(tokens, ft_new_token(T_D_QUOTE, quoted));
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

	quote = prompt[i];
	quoted = ft_quotes_token(prompt, &i);
	if (!quoted)
		return (-1);
	if (quote == '"')
		return (ft_handle_double_quote_token(tokens, prompt, i, quoted));
	else
		return (ft_handle_single_quote_token(tokens, quoted, i));
}
