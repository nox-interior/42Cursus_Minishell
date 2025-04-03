/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:22:57 by amarroyo          #+#    #+#             */
/*   Updated: 2025/04/03 08:14:42 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_new_token(t_tok_type type, char *value)
{
	t_token	*token;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
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

char	*ft_token_type_name(t_tok_type type)
{
	if (type == T_NONE) // No estoy segura de si este es necesario o no pero por 
	//el momento lo incluyo, tendría más sentido para gestionar errores, 
	//pero bueno, iremos viendo si esto sirve de algo o no.
		return ("NONE");
	else if (type == T_SPACES)
		return ("SPACES");
	else if (type == T_WORD)
		return ("WORD");
	else if (type == T_STRING)
		return ("STRING");
	else if (type == T_VAR)
		return ("VAR");
	else if (type == T_PIPE)
		return ("PIPE");
	else if (type == T_REDIR_IN)
		return ("REDIR_IN");
	else if (type == T_REDIR_OUT)
		return ("REDIR_OUT");
	else if (type == T_HEREDOC)
		return ("HEREDOC");
	else if (type == T_APPEND)
		return ("APPEND");
	return ("UNKNOWN"); // mismo rollo que NONE, no sé si tendrçia más sentido devolver un error.
}

void	ft_print_tokens(t_token *head)
{
	while (head)
	{
		printf("Token: [%-10s] -> \"%s\"\n",
			ft_token_type_name(head->type), head->value);
		head = head->next;
	}
}

int	main(void)
{
	t_token	*tokens = NULL;

	ft_add_token(&tokens, ft_new_token(T_WORD, ft_strdup("echo")));
	ft_add_token(&tokens, ft_new_token(T_STRING, ft_strdup("hola mundo")));
	ft_add_token(&tokens, ft_new_token(T_REDIR_OUT, ft_strdup(">")));
	ft_add_token(&tokens, ft_new_token(T_WORD, ft_strdup("salida.txt")));

	ft_print_tokens(tokens);
	return (0);
}

void	ft_tokenizer(char *prompt)
{
	t_token *token_list;
	int i;

	i = 0;
	token_list = NULL;
	while (prompt[i])
	{
		if (prompt[i] == 32)
			i++;
		else if (prompt[i])
	}
}