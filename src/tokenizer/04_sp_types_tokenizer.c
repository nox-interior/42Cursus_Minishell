/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_sp_types_tokenizer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:17:36 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/04 13:29:16 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe_token(t_token **token_list)
{
	t_token	*new_token;

	new_token = ft_new_token(T_PIPE, ft_strdup("|"));
	if (!new_token)
		return ;
	ft_add_token(token_list, new_token);
}

void	ft_dub_redir(t_token **token_list, const char c)
{
	t_token	*new_token;

	if (c == '<')
	{
		new_token = ft_new_token(T_HEREDOC, ft_strdup("<<"));
		if (!new_token)
			return ;
		ft_add_token(token_list, new_token);
		return ;
	}
	if (c == '>')
	{
		new_token = ft_new_token(T_APPEND, ft_strdup(">>"));
		if (!new_token)
			return ;
		ft_add_token(token_list, new_token);
		return ;
	}
}

void	ft_redir(t_token **token_list, const char c)
{
	t_token	*new_token;

	if (c == '<')
	{
		new_token = ft_new_token(T_REDIR_IN, ft_strdup("<"));
		if (!new_token)
			return ;
		ft_add_token(token_list, new_token);
		return ;
	}
	if (c == '>')
	{
		new_token = ft_new_token(T_REDIR_OUT, ft_strdup(">"));
		if (!new_token)
			return ;
		ft_add_token(token_list, new_token);
		return ;
	}
}

int	ft_var_token(t_token **token_list, const char *prompt, int i)
{
	int		start;
	char	*value;
	t_token	*new_token;

	new_token = NULL;
	start = i + 1; // start se salta el $
	i++; // saltamos el $
	if (prompt[i] == '\0' || ft_isspace(prompt[i])) // el token = "$" (WORD)
		return (ft_word_token(token_list, prompt, i - 1));
	if (prompt[i] == '?')
		return (ft_is_exit_tok(token_list, new_token, i)); // si todo va bien devuelve i + 1
	while (prompt[i] && (ft_isalpha(prompt[i]) || ft_isdigit(prompt[i])
			|| prompt[i] == '_'))
		i++;
	if (prompt[i] == '$')
		i++;
	if (i - start <= 0)
		return (-1);
	value = ft_substr(prompt, start, i - start);
	if (!value)
		return (-1);
	if (!ft_create_var_token(token_list, new_token, value))
		return (-1);
	return (i);
}
