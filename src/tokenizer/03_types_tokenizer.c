/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_types_tokenizer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:30:45 by amarroyo          #+#    #+#             */
/*   Updated: 2025/07/08 11:44:07 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_word_char(char c)
{
	if (c == '\0')
		return (false);
	if (ft_isspace(c))
		return (false);
	if (c == '|' || c == '<' || c == '>' || c == '\'' || c == '\"')
		return (false);
	return (true);
}

char	*ft_quotes_token(const char *prompt, int *i)
{
	int		start;
	char	quote;
	char	*value;

	quote = prompt[*i];
	(*i)++;
	start = *i;
	while (prompt[*i] && prompt[*i] != quote)
		(*i)++;
	if (prompt[*i] == '\0')
	{
		ft_putstr_fd("minishell: error: non-closed quotes\n", 2);
		return (NULL);
	}
	value = ft_substr(prompt, start, *i - start);
	if (!value)
		return (NULL);
	(*i)++;
	return (value);
}

int	ft_word_token(t_token **tokens, const char *prompt, int i)
{
	int		start;
	int		len;
	char	*value;
	t_token	*new_token;

	start = i;
	while (prompt[i] && ft_is_word_char(prompt[i]))
		i++;
	len = i - start;
	value = ft_substr(prompt, start, len);
	if (!value)
		return (-1);
	new_token = ft_new_token(T_WORD, value);
	if (!new_token)
	{
		free(value);
		return (-1);
	}
	ft_add_token(tokens, new_token);
	return (i);
}
