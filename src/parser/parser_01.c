/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:26:15 by amarroyo          #+#    #+#             */
/*   Updated: 2025/04/25 12:27:43 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	ft_init_command(t_command *cmd)
{
	cmd->argv = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->next = NULL;
}

static char	**ft_list_to_str_array(t_list *args)
{
	int		size;
	int		i;
	char	**array;
	t_list	*tmp;

	size = ft_lstsize(args);
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	tmp = args;
	i = 0;
	while (tmp)
	{
		array[i++] = ft_strdup((char *)tmp->content);
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
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

static int	ft_is_valid_token_sequence(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (!current)
		return (0);
	if (current->type == T_PIPE)
		return (0);
	while (current)
	{
		if (current->type == T_PIPE)
		{
			if (!current->next || current->next->type == T_PIPE)
				return (0);
		}
		if (ft_is_redirection(current->type))
		{
			if (!current->next || current->next->type != T_WORD)
				return (0);
		}
		if (current->type == T_NONE)
			return (0);
		current = current->next;
	}
	return (1);
}

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

	if (!ft_is_valid_token_sequence(token_list))
		return (NULL);
	current = token_list;
	head = NULL;
	tail = NULL;
	while (current)
	{
		if (ft_add_command_to_list(&head, &tail, &current) == -1)
			return (ft_free_command_list(&head), NULL);
		if (current && current->type == T_PIPE)
			current = current->next;
	}
	return (head);
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
