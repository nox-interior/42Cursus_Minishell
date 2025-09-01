/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_command_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:42:05 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/01 15:53:01 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_process_redirection(t_command *cmd, t_token **current)
{
	char	*redir_target;
	char	*quote_char;
	char	*temp1;
	char	*temp2;

	if (!(*current)->next || !ft_is_valid_arg_token((*current)->next->type))
		return (-1);
	redir_target = ft_strdup((*current)->next->value);
	if (!redir_target)
		return (-1);
	if ((*current)->type == T_REDIR_IN || (*current)->type == T_HEREDOC)
	{
		if ((*current)->type == T_HEREDOC)
		{
			if ((*current)->next->type == T_S_QUOTE
				|| (*current)->next->type == T_D_QUOTE)
			{
				quote_char = ((*current)->next->type == T_S_QUOTE) ? "'" : "\"";
				temp1 = ft_strjoin(quote_char, redir_target);
				temp2 = ft_strjoin(temp1, quote_char);
				free(temp1);
				free(redir_target);
				cmd->delimit = temp2;
			}
			else
				cmd->delimit = redir_target;
			cmd->heredoc = 1;
		}
		else
		{
			cmd->infile = redir_target;
			cmd->heredoc = 0;
		}
	}
	else
	{
		cmd->outfile = redir_target;
		cmd->append = ((*current)->type == T_APPEND);
	}
	*current = (*current)->next->next;
	return (1);
}

int	ft_process_argument(t_list **args, t_token *token)
{
	char	*dup;

	dup = ft_strdup(token->value);
	if (!dup)
		return (-1);
	ft_lstadd_back(args, ft_lstnew(dup));
	return (1);
}

int	ft_parse_command_body(t_command *cmd, t_token **current, t_list **args)
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

char	**ft_list_to_str_array(t_list *args)
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
