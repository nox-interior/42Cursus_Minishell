/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:22:57 by amarroyo          #+#    #+#             */
/*   Updated: 2025/04/04 12:30:03 by amarroyo         ###   ########.fr       */
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

// Liberar lista  de tokens
void	ft_free_token_list(t_token **tokens)
{
	t_token	*tmp;

	if (!tokens || !*tokens)
		return ;
	while (*tokens)
	{
		tmp = (*tokens)->next;
		if ((*tokens)->value)
			free((*tokens)->value);
		free(*tokens);
		*tokens = tmp;
	}
	*tokens = NULL;
}

/*
Advertencia menor:
	•	Si se usa esta función solo en ft_print_tokens(), está bien.
	•	Si alguna se usa ft_token_type_name() en una lógica más crítica,
			cuidado con el "UNKNOWN" y el NULL.
	Podría producir un segfault en printf("%s", NULL).*/

static char	*ft_token_type_name(t_tok_type type)
{
	if (type == T_NONE)
		return (NULL);
	else if (type == T_WORD)
		return ("WORD");
	else if (type == T_S_QUOTE)
		return ("S_QUOTE");
	else if (type == T_D_QUOTE)
		return ("D_QUOTE");
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
	return ("UNKNOWN");
}

// Esta solo sirve para hacer pruebas, ni caso.
static void	ft_print_tokens(t_token *head)
{
	while (head)
	{
		printf("Token: [%-10s] -> \"%s\"\n", ft_token_type_name(head->type),
			head->value);
		head = head->next;
	}
}

// Funcion para espacios en blanco (se puede añadir a libft?)
static int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

// Funcion para comillas
int	ft_quotes_token(t_token **tokens, const char *prompt, int i)
{
	int		start;
	char	quote;
	char	*value;

	quote = prompt[i];
	i++;
	start = i;
	while (prompt[i] && prompt[i] != quote)
		i++;
	if (prompt[i] == '\0')
	{
		ft_putstr_fd("minishell: error: non-closed quotes\n", 2);
		return (-1);
	}
	value = ft_substr(prompt, start, i - start);
	if (!value)
		return (-1);
	if (quote == '\'')
		ft_add_token(tokens, ft_new_token(T_S_QUOTE, value));
	else if (quote == '\"')
		ft_add_token(tokens, ft_new_token(T_D_QUOTE, value));
	return (i + 1);
}

// Funciones para caracteres especiales <, >, <<, >>
static void	ft_redir(t_token **token_list, const char c)
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

// static void	ft_redir(t_token **token_list, const char c)
// {
// 	t_token	*new_token;

// 	if (c == '<')
// 		new_token = ft_new_token(T_REDIR_IN, ft_strdup("<"));
// 	else
// 		new_token = ft_new_token(T_REDIR_OUT, ft_strdup(">"));
// 	if (!new_token)
// 		return ;
// 	ft_add_token(token_list, new_token);
// }

static void	ft_dub_redir(t_token **token_list, const char c)
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
// static void	ft_dub_redir(t_token **token_list, const char c)
// {
// 	t_token	*new_token;

// 	if (c == '<')
// 		new_token = ft_new_token(T_HEREDOC, ft_strdup("<<"));
// 	else
// 		new_token = ft_new_token(T_APPEND, ft_strdup(">>"));
// 	if (!new_token)
// 		return ;
// 	ft_add_token(token_list, new_token);
// }

// Función para pipe
static void	ft_pipe_token(t_token **token_list)
{
	t_token	*new_token;

	new_token = ft_new_token(T_PIPE, ft_strdup("|"));
	if (!new_token)
		return ;
	ft_add_token(token_list, new_token);
}

// Función para variables
// static int	ft_var_token(t_token **token_list, const char *prompt, int i)
// {
// 	int		start;
// 	t_token	*new_token;// NULL?

// 	start = i + 1;// Empieza en el siguiente al $
// 	i += 1;
// 	if (prompt[i] == '?')
// 	{
// 		new_token = ft_new_token(T_VAR, ft_strdup("?"));
// 		ft_add_token(token_list, new_token);
// 		return (i);
// 	}
// 	while (prompt[i])
// 	{
// 		// if (!ft_isalpha(prompt[i]) || !ft_isdigit(prompt[i])
// 		// 	|| !prompt[i] == '_')
// 		if (!(ft_isalpha(prompt[i]) || ft_isdigit(prompt[i])
//|| prompt[i] == '_'))
// 			break ;
// 		i++;
// 	}
// 	new_token = ft_new_token(T_VAR, ft_strdup(ft_substr(prompt, start, i
// 					- start)));
// 	ft_add_token(token_list, new_token);
// 	return (i - 1);
// }

// static int	ft_var_token(t_token **token_list, const char *prompt, int i)
// {
// 	int		start;
// 	char	*value;
// 	t_token	*new_token;

// 	start = i + 1;
// 	i++;
// 	if (prompt[i] == '?')
// 	{
// 		new_token = ft_new_token(T_VAR, ft_strdup("?"));
// 		if (!new_token)
// 			return (-1);
// 		ft_add_token(token_list, new_token);
// 		return (i);
// 	}
// 	while (prompt[i])
// 	{
// 		if (!ft_isalpha(prompt[i]) && !ft_isdigit(prompt[i]) && prompt[i] != '_'
// 			&& ft_isspace(prompt[i]))
// 			break ;
// 		i++;
// 	}
// 	if (i - start <= 0)
// 		return (0);
// 	value = ft_substr(prompt, start, i - start);
// 	if (!value)
// 		return (-1);
// 	new_token = ft_new_token(T_VAR, value);
// 	if (!new_token)
// 	{
// 		free(value);
// 		return (-1);
// 	}
// 	ft_add_token(token_list, new_token);
// 	return (i - 1);
// }

static int	ft_var_token(t_token **token_list, const char *prompt, int i)
{
	int		start;
	char	*value;
	t_token	*new_token;

	start = i + 1;
	i++;
	if (prompt[i] == '\0' || ft_isspace(prompt[i]))
		return (ft_word_token(token_list, prompt, i - 1));
	if (prompt[i] == '?')
	{
		new_token = ft_new_token(T_VAR, ft_strdup("?"));
		if (!new_token)
			return (-1);
		ft_add_token(token_list, new_token);
		return (i);
	}
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
	new_token = ft_new_token(T_VAR, value);
	if (!new_token)
	{
		free(value);
		return (-1);
	}
	ft_add_token(token_list, new_token);
	return (i - 1);
}

// static int	ft_var_token(t_token **token_list, const char *prompt, int i)
// {
// 	int	start;

// 	t_token *new_token; // NULL?
// 	start = i + 1;      // Empieza en el siguiente al $
// 	i += 1;
// 	if (prompt[i] == '?')
// 	{
// 		new_token = ft_new_token(T_VAR, "?");
// 		ft_add_token(token_list, new_token);
// 		return (i);
// 	}
// 	while (prompt[i])
// 	{
// 		if (!ft_isalpha(prompt[i]) || !ft_isdigit(prompt[i])
// 			|| !(prompt[i] == '_'))
// 			break ;
// 		i++;
// 	}
// 	new_token = ft_new_token(T_VAR, ft_strdup(ft_substr(prompt, start, i
// 					- start)));
// 	ft_add_token(token_list, new_token);
// 	return (i - 1);
// }

// Funcion para caracteres normales
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

// Tokenizer
// t_token	*ft_tokenizer(const char *prompt)
// {
// 	t_token	*token_list;
// 	int		i;

// 	i = 0;
// 	token_list = NULL;
// 	while (prompt[i])
// 	{
// 		if (prompt[i] == '<' || prompt[i] == '>')
// 		{
// 			if (prompt[i] == prompt[i + 1])
// 			{
// 				ft_dub_redir(&token_list, prompt[i]);
// 				i++;
// 			}
// 			else
// 				ft_redir(&token_list, prompt[i]);
// 		}
// 		else if (prompt[i] == '|')
// 			ft_pipe_token(&token_list);
// 		else if (prompt[i] == '\'' || prompt[i] == '\"')
// 			i = ft_quotes_token(&token_list, prompt, i);
// 		else if (prompt[i] == '$')
// 			i = ft_var_token(&token_list, prompt, i);
// 		else
// 			// caract normales
// 		i++;
// 	}
// 	return (token_list);

t_token	*ft_tokenizer(const char *prompt)
{
	t_token	*token_list;
	int		i;

	i = 0;
	token_list = NULL;
	while (prompt[i])
	{
		{
			if (ft_isspace(prompt[i]))
				i++;
		}
		if (prompt[i] == '<' || prompt[i] == '>')
		{
			if (prompt[i] == prompt[i + 1])
			{
				ft_dub_redir(&token_list, prompt[i]);
				i++;
			}
			else
				ft_redir(&token_list, prompt[i]);
			i++;
		}
		else if (prompt[i] == '|')
		{
			ft_pipe_token(&token_list);
			i++;
		}
		else if (prompt[i] == '\'' || prompt[i] == '\"')
		{
			i = ft_quotes_token(&token_list, prompt, i);
			if (i == -1)
			{
				ft_free_token_list(&token_list);
				return (NULL);
			}
		}
		else if (prompt[i] == '$')
		{
			i = ft_var_token(&token_list, prompt, i);
			if (i == -1)
			{
				ft_free_token_list(&token_list);
				return (NULL);
			}
			i++;
		}
		else if (ft_is_word_char(prompt[i]))
			i = ft_word_token(&token_list, prompt, i);
		if (i == -1)
		{
			ft_free_token_list(&token_list);
			return (NULL);
		}
	}
	return (token_list);
}

int	main(void)
{
	t_token	*tokens;

	tokens = NULL;
	tokens = ft_tokenizer("$   '' $  $$  $ \ \"$hola\" '$USER'|||<<<>>\'\' \"\" $$$ $$$$ ");
	ft_print_tokens(tokens);
	ft_free_token_list(&tokens);
	return (0);
}
