/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_handle_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:01:17 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/02 18:57:35 by amarroyo         ###   ########.fr       */
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
		ft_add_token(tokens, ft_new_token(T_D_QUOTE, quoted));
}

static int	ft_handle_double_quote_token(t_token **tokens, const char *prompt,
		int i, char *quoted)
{
	char	*rest;
	int		should_concat;
	int		quote_start;

	quote_start = i - (ft_strlen(quoted) + 2);
	should_concat = ft_should_concatenate_quote(prompt, quote_start);
	rest = ft_get_rest_after_quote(prompt, &i);
	if (rest)
		ft_process_quoted_with_rest(tokens, quoted, rest, should_concat);
	else
		ft_process_quoted_without_rest(tokens, quoted, should_concat);
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
