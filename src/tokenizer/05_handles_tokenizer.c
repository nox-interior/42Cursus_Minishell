/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_handles_tokenizer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:22:09 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/04 13:29:54 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirection(t_token **token_list, const char *prompt, int i)
{
	if (prompt[i] == prompt[i + 1])
	{
		ft_dub_redir(token_list, prompt[i]);
		i++;
	}
	else
		ft_redir(token_list, prompt[i]);
	i++;
	return (i);
}

int	handle_pipe(t_token **token_list, const char *prompt, int i)
{
	if (prompt[i + 1] == '|')
	{
		ft_add_token(token_list, ft_new_token(T_OR, ft_strdup("||")));
		i += 2;
	}
	else
	{
		ft_pipe_token(token_list);
		i++;
	}
	return (i);
}

int	handle_special(t_token **token_list, const char *prompt, int i)
{
	if (prompt[i] == '<' || prompt[i] == '>')
		i = handle_redirection(token_list, prompt, i);
	else if (prompt[i] == '|')
		i = handle_pipe(token_list, prompt, i);
	else if (prompt[i] == '&' || prompt[i] == ';' || prompt[i] == '!')
		i = handle_special_inv(token_list, prompt, i);
	else if (prompt[i] == '\'' || prompt[i] == '\"')
		i = ft_quotes_token(token_list, prompt, i);
	else if (prompt[i] == '$')
		i = ft_var_token(token_list, prompt, i);
	return (i);
}

int	handle_invalid(t_token **token_list, const char *prompt, int i)
{
	char	*str;

	str = ft_substr(prompt, i, 1);
	if (!str)
	{
		free(str);
		return (-1);
	}
	ft_add_token(token_list, ft_new_token(T_INVALID, str));
	i++;
	free(str);
	return (i);
}

int	handle_special_inv(t_token **token_list, const char *prompt, int i)
{
	if (prompt[i] == '&')
	{
		if (prompt[i + 1] == '&')
		{
			ft_add_token(token_list, ft_new_token(T_AND, ft_strdup("&&")));
			i += 2;
		}
		else
		{
			ft_add_token(token_list, ft_new_token(T_AMPERSAND, ft_strdup("&")));
			i++;
		}
	}
	else if (prompt[i] == ';')
	{
		ft_add_token(token_list, ft_new_token(T_SEMICOLON, ft_strdup(";")));
		i++;
	}
	else if (prompt[i] == '!')
	{
		ft_add_token(token_list, ft_new_token(T_EXCLAMATION, ft_strdup("!")));
		i++;
	}
	return (i);
}
