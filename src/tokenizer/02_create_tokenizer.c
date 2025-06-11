/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_create_tokenizer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:45:46 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/11 12:47:15 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_new_token(t_tok_type type, char *value)
{
	t_token	*token;

	if (type == T_NONE)
	{
		free(value);
		return (NULL);
	}
	token = malloc(sizeof(t_token));
	if (!token)
	{
		free(value);
		return (NULL);
	}
	token->type = type;
	token->value = value;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	ft_add_token(t_token **head, t_token *new_token)
{
	t_token	*last_token;

	if (!head || !new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	last_token = *head;
	while (last_token->next)
		last_token = last_token->next;
	last_token->next = new_token;
	new_token->prev = last_token;
}

int	ft_is_exit_tok(t_token **token_list, t_token *new_token, int i)
{
	new_token = ft_new_token(T_VAR, ft_strdup("$?"));
	if (!new_token)
		return (-1);
	ft_add_token(token_list, new_token);
	return (i + 1);
}

int	ft_create_var_token(t_token **t_list, t_token *token, char *value)
{
	token = ft_new_token(T_VAR, value);
	if (!token)
	{
		free(value);
		return (0);
	}
	ft_add_token(t_list, token);
	return (1);
}

int	ft_create_token(t_token **token_list, const char *prompt, int i)
{
	if (prompt[i] == '<' || prompt[i] == '>' || prompt[i] == '|'
		|| prompt[i] == '&' || prompt[i] == ';' || prompt[i] == '!'
		|| prompt[i] == '\'' || prompt[i] == '\"' || prompt[i] == '$')
		i = handle_special(token_list, prompt, i);
	else if (ft_is_word_char(prompt[i]))
		i = ft_word_token(token_list, prompt, i);
	else
		i = handle_invalid(token_list, prompt, i);
	return (i);
}
