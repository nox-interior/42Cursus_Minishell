/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_sp_types_tokenizer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:17:36 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/11 12:45:08 by amarroyo         ###   ########.fr       */
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

char	*ft_var_with_dollar(const char *prompt, int start, int end)
{
	char	*var_name;
	char	*result;

	var_name = ft_substr(prompt, start, end - start);
	if (!var_name)
		return (NULL);
	result = ft_strjoin("$", var_name);
	free(var_name);
	return (result);
}

// int	ft_var_token(t_token **token_list, const char *prompt, int i)
// {
// 	int		start;
// 	char	*value;
// 	t_token	*new_token;

// 	new_token = NULL;
// 	start = i + 1;                                  // start se salta el $
// 	i++;                                            // saltamos el $
// 	if (prompt[i] == '\0' || ft_isspace(prompt[i])) // el token = "$" (WORD)
// 		return (ft_word_token(token_list, prompt, i - 1));
// 	if (prompt[i] == '?')
// 		return (ft_is_exit_tok(token_list, new_token, i));
// 			// si todo va bien devuelve i + 1
// 	while (prompt[i] && (ft_isalpha(prompt[i]) || ft_isdigit(prompt[i])
// 			|| prompt[i] == '_'))
// 		i++;
// 	if (prompt[i] == '$')
// 		i++;
// 	if (i - start <= 0)
// 		return (-1);
// 	value = ft_substr(prompt, start, i - start);
// 	if (!value)
// 		return (-1);
// 	if (!ft_create_var_token(token_list, new_token, value))
// 		return (-1);
// 	return (i);
// }

int	ft_var_token(t_token **token_list, const char *prompt, int i)
{
	int		start;
	char	*value;

	start = i + 1;
	i++;
	if (prompt[i] == '\0' || ft_isspace(prompt[i]))
		return (ft_word_token(token_list, prompt, i - 1));
	if (prompt[i] == '?')
		return (ft_is_exit_tok(token_list, NULL, i));
	while (prompt[i] && (ft_isalpha(prompt[i]) || ft_isdigit(prompt[i])
			|| prompt[i] == '_'))
		i++;
	if (prompt[i] == '$')
		i++;
	if (i - start <= 0)
		return (-1);
	value = ft_var_with_dollar(prompt, start, i);
	if (!value)
		return (-1);
	if (!ft_create_var_token(token_list, NULL, value))
	{
		free(value);
		return (-1);
	}
	return (i);
}
