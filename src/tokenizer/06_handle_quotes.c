/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_handle_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:01:17 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/09 14:59:35 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_process_quoted_with_rest(t_token **tokens, char *quoted,
		char *rest, int should_concat)
{
	char	*joined;

	joined = ft_strjoin(quoted, rest);
	free(quoted);
	free(rest);
	if (!joined)
		return ;
	if (should_concat)
		ft_concat_with_last_token(tokens, joined);
	else
		ft_add_token(tokens, ft_new_token(T_WORD, joined));
}

static void	ft_process_quoted_without_rest(t_token **tokens, char *quoted,
		int should_concat)
{
	if (should_concat)
		ft_concat_with_last_token(tokens, quoted);
	else
		ft_add_token(tokens, ft_new_token(T_WORD, quoted));
}

static int	ft_handle_double_quote_token(t_quote_params *params)
{
	char	*rest;
	int		should_concat;

	should_concat = ft_should_concatenate_quote(params->prompt,
			params->quote_start);
	rest = ft_get_rest_after_quote(params->prompt, &(params->i));
	if (rest)
		ft_process_quoted_with_rest(params->tokens, params->quoted, rest,
			should_concat);
	else
		ft_process_quoted_without_rest(params->tokens, params->quoted,
			should_concat);
	return (params->i);
}

static int	ft_handle_single_quote_token(t_token **tokens, char *quoted, int i)
{
	ft_add_token(tokens, ft_new_token(T_S_QUOTE, quoted));
	return (i);
}

int	ft_handle_quote_token(t_token **tokens, const char *prompt, int i)
{
	char			quote;
	char			*quoted;
	t_quote_params	params;

	params.quote_start = i;
	quote = prompt[i];
	quoted = ft_quotes_token(prompt, &i);
	if (!quoted)
		return (-1);
	if (quote == '"')
	{
		params.tokens = tokens;
		params.prompt = prompt;
		params.i = i;
		params.quoted = quoted;
		return (ft_handle_double_quote_token(&params));
	}
	else
		return (ft_handle_single_quote_token(tokens, quoted, i));
}
