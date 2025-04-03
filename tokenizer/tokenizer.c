/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:22:57 by amarroyo          #+#    #+#             */
/*   Updated: 2025/04/03 12:23:18 by amarroyo         ###   ########.fr       */
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
	if (new_token->type == T_NONE)
	{
		free(new_token->value);
		free(new_token);
		return ;
	}
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

static char	*ft_token_type_name(t_tok_type type)
{
	if (type == T_NONE)
		return (NULL);
	else if (type == T_SPACES)
		// Es necesario si vamos a saltar espacios? No creo
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
	return ("UNKNOWN");
	// no sé si tendrçia más sentido devolver un error o quitarlo directamente porque ya maneja t_none un error
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
// static int	ft_isspace(char c)
// {
// 	if (c == 32 || (c >= 9 && c <= 13))
// 		return (1);
// 	return (0);
// }

// // Funcion para saltar espacios en blanco
// static int	ft_skip_spaces(const char *prompt, int i)
// {
// 	while (prompt[i] && ft_isspace(prompt[i]))
// 		i++;
// 	return (i);
// }

// Función para variables
// Función para pipe

// Funcion para comillas
// static void	ft_quotes(t_token **token_list, const char *prompt, int *i)

#include "minishell.h"

// Detecta una cadena entre comillas y añade un token STRING.
// Devuelve el nuevo valor de i tras la comilla de cierre,
// o -1 si no se encuentra comilla de cierre.
int	ft_handle_quotes(t_token **tokens, const char *prompt, int i)
{
	int		start;
	char	quote;
	char	*value;

	quote = prompt[i]; // puede ser ' o "
	i++;               // saltar la comilla de apertura
	start = i;
	while (prompt[i] && prompt[i] != quote)
		i++;
	if (prompt[i] == '\0')
	{
		ft_putstr_fd("minishell: error: comilla sin cerrar\n", 2);
		return (-1);
	}
	// Extraer el contenido entre comillas
	value = ft_substr(prompt, start, i - start);
	if (!value)
		return (-1);
	ft_add_token(tokens, ft_new_token(T_STRING, value));
	return (i + 1); // avanzar tras la comilla de cierre
}

// Funcion para caracteres normales

// Funciones para caracteres especiales <, >, <<, >>
static void	ft_redir(t_token **token_list, const char c)
{
	t_token	*new_token;

	if (c == '<')
	{
		new_token = ft_new_token(T_REDIR_IN, "<");
		ft_add_token(token_list, new_token);
		return ;
	}
	if (c == '>')
	{
		new_token = ft_new_token(T_REDIR_OUT, ">");
		ft_add_token(token_list, new_token);
		return ;
	}
}

static void	ft_dub_redir(t_token **token_list, const char c)
{
	t_token	*new_token;

	if (c == '<')
	{
		new_token = ft_new_token(T_HEREDOC, "<<");
		ft_add_token(token_list, new_token);
		return ;
	}
	if (c == '>')
	{
		new_token = ft_new_token(T_APPEND, ">>");
		ft_add_token(token_list, new_token);
		return ;
	}
}

static void	ft_pipe_token(t_token **token_list)
{
	new_token = ft_new_token(T_PIPE, "|");
	ft_add_token(token_list, new_token);
}

static int	ft_var_token(t_token **token_list, const char *prompt, int i)
{
	int	start;

	t_token *new_token; // NULL?
	start = i + 1;      // Empieza en el siguiente al $
	i += 1;
	if (prompt[i] == '?')
	{
		new_token = ft_new_token(T_VAR, "?");
		ft_add_token(token_list, new_token);
		return (i);
	}
	while (prompt[i])
	{
		if (!ft_isalpha(prompt[i]) || !ft_isdigit(prompt[i])
			|| !prompt[i] == '_')
			break ;
		i++;
	}
	new_token = ft_new_token(T_VAR, ft_strdup(ft_substr(prompt, start, i
					- start)));
	ft_add_token(token_list, new_token);
	return (i - 1);
}

t_token	*ft_tokenizer(const char *prompt)
{
	t_token	*token_list;
	int		i;

	i = 0;
	token_list = NULL;
	while (prompt[i])
	{
		if (prompt[i] == '<' || prompt[i] == '>')
		{
			if (prompt[i] == prompt[i + 1])
			{
				ft_dub_redir(&token_list, prompt[i]);
				i++;
			}
			else
				ft_redir(&token_list, prompt[i]);
		}
		else if (prompt[i] == '|')
			ft_pipe_token(&token_list);
		else if (prompt[i] == '\'' || prompt[i] == '\"')
			i = ft_loqueseaprimo();
		else if (prompt[i] == '$')
			i = ft_var_token(&token_list, prompt, i);
		else
			;//caract normales
		i++;
	}
	return (token_list);
}

int	main(void)
{
	t_token	*tokens;

	tokens = NULL;
	tokens = ft_tokenizer("<<<>>>");
	/*ft_add_token(&tokens, ft_new_token(T_WORD, ft_strdup("echo")));
	ft_add_token(&tokens, ft_new_token(T_STRING,
			ft_strdup("hola mundo")));
	ft_add_token(&tokens, ft_new_token(T_REDIR_OUT, ft_strdup(">")));
	ft_add_token(&tokens, ft_new_token(T_WORD,
			ft_strdup("salida.txt")));*/
	ft_print_tokens(tokens);
	return (0);
}
