/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:49:41 by amarroyo          #+#    #+#             */
/*   Updated: 2025/04/25 12:14:19 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Recorrer la lista de tokens
// Separarla en comandos simples
//	- caso 1: el prompt es un único comando simple
//	- caso 2: el prompt es una pipeline
// Añadir cada comando simple como un nodo t_command a la lista de comandos
//	- crear la lista si es el primer nodo
//	- añadir el nodo a la lista existente si no es el primero
// Control de errores:
//	- no se crea el nodo, liberar memoria, terminar el programa.
//	- errores en el prompt:
//		- pipe al inicio del prompt [| ls]
//		- pipe al final del prompt [ls |]
//		- dos pipes seguidas [ls || echo]
//		- redirección sin archivo [ls >] ; [cat <]
//		- redirección con token siguiente no válido: no es T_WORD o T_VAR
//		- dos redirecciones sin archivo entre ellas [ls > > file]
//		- tokens inesperados: Token T_NONE o cualquier token que indique que el
//			tokenizer falló o devolvió algo no válido. (En principio lo controla
//			el tokenizer, pero podemos valorar un control extra, si necesario).

// Funciones posibles:
// 0. Inicializar estructura: como funcion aux o en la que crea nodos.
// 1. Función general : t_command *ft_parse_commands(t_token *token_list)
/* Tiene que recorrer token_list y guardar cada comando en un nodo.
Definimos un t_command *current para recorrer los tokens separados.
Cuando current encuentra T_PIPE, o es == NULL, significa que ha encontrado un
comando antes de una pipe, que ha llegado al final de la lista, o que es un
comando simple unico.
Entonces hay que crear el nodo (llamada a funcion aux para este propósito
ft_create_command(),por ejemplo)
Hay que tener una función auxiliar para implementar una lista enlazada de 
comandos (ft_add_command_to_list(), por ejemplo), añadiendo cada nodo al final 
de la lista, para no alterar el orden del prompt o token_list.
Habrá que liberar en algún momento la lista de nodos, porque vamos a usar malloc
para reservar el espacio de cada nodo, en caso de error. 
(ft_free_command_list()) */

static int	ft_add_command_to_list(t_command **head, t_command **tail,
		t_token **current)
{
	t_command	*cmd;

	cmd = ft_create_command(current);
	if (!cmd)
		return (-1);
	if (!*head)
	{
		*head = cmd;
		*tail = cmd;
	}
	else
	{
		(*tail)->next = cmd;
		*tail = cmd;
	}
	return (0);
}

t_command	*ft_parse_command(t_token *token_list)
{
	t_token		*current;
	t_command	*head;
	t_command	*tail;

	current = token_list;
	head = NULL;
	tail = NULL;
	while (current)
	{
		if (current->type == T_PIPE && (!current->prev
				|| current->prev->type == T_PIPE))
			return (ft_free_command_list(&head), NULL);
		if (ft_add_command_to_list(&head, &tail, &current) == -1)
			return (ft_free_command_list(&head), NULL);
		if (current && current->type == T_PIPE)
			current = current->next;
	}
	return (head);
}

// 2. Funciones aux:
//		2.1. t_command *ft_create_command(t_token **current);
//
static int	ft_is_valid_arg_token(t_tok_type type)
{
	return (type == T_WORD || type == T_VAR || type == T_S_QUOTE
		|| type == T_D_QUOTE);
}

static int	ft_is_redirection(t_tok_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT || type == T_HEREDOC
		|| type == T_APPEND);
}

static void	*ft_init_command(t_command *cmd)
{
	cmd->argv = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->next = NULL;
}

static int	ft_process_redirection(t_command *cmd, t_token **current)
{
	char	*redir_target;

	if (!(*current)->next || (*current)->next->type != T_WORD)
		return (-1);
	redir_target = ft_strdup((*current)->next->value);
	if (!redir_target)
		return (-1);
	if ((*current)->type == T_REDIR_IN || (*current)->type == T_HEREDOC)
	{
		cmd->infile = redir_target;
		cmd->heredoc = ((*current)->type == T_HEREDOC);
	}
	else
	{
		cmd->outfile = redir_target;
		cmd->append = ((*current)->type == T_APPEND);
	}
	*current = (*current)->next->next;
	return (1);
}

static int	ft_process_argument(t_list **args, t_token *token)
{
	char	*dup;

	dup = ft_strdup(token->value);
	if (!dup)
		return (-1);
	ft_lstadd_back(args, ft_lstnew(dup));
	return (1);
}

static int	ft_parse_command_body(t_command *cmd, t_token **current,
		t_list **args)
{
	while (*current && (*current)->type != T_PIPE)
	{
		if (ft_is_redirection((*current)->type))
		{
			if (ft_process_redirection(cmd, current) == -1)
				return (-1);
			continue ;
		}
		if (ft_is_valid_arg_token((*current)->type))
		{
			if (ft_process_argument(args, *current) == -1)
				return (-1);
		}
		else if ((*current)->type == T_NONE)
			return (-1);
		*current = (*current)->next;
	}
	return (0);
}

void	ft_free_command_partial(t_command *cmd, t_list *args)
{
	if (cmd)
	{
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		free(cmd);
	}
	if (args)
		ft_lstclear(&args, free);
}

void	ft_free_command_list(t_command **cmd_list)
{
	t_command	*current;
	t_command	*next;
	int			i;

	if (!cmd_list || !*cmd_list)
		return ;
	current = *cmd_list;
	while (current)
	{
		next = current->next;
		if (current->argv)
		{
			i = 0;
			while (current->argv[i])
				free(current->argv[i++]);
			free(current->argv);
		}
		if (current->infile)
			free(current->infile);
		if (current->outfile)
			free(current->outfile);
		free(current);
		current = next;
	}
	*cmd_list = NULL;
}

t_command	*ft_create_command(t_token **current)
{
	t_command	*cmd;
	t_list		*args;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_init_command(cmd);
	args = NULL;
	if (ft_parse_command_body(cmd, current, &args) == -1)
		return (ft_free_command_partial(cmd, args), NULL);
	cmd->argv = ft_list_to_str_array(args);
	ft_lstclear(&args, free);
	return (cmd);
}
