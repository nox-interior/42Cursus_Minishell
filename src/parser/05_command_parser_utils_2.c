/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_command_parser_utils_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:15:00 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/02 19:15:00 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_process_argument(t_list **args, t_token *token)
{
	char	*dup;

	dup = ft_strdup(token->value);
	if (!dup)
		return (-1);
	ft_lstadd_back(args, ft_lstnew(dup));
	return (1);
}

int	ft_process_first_argument(t_list **args, t_token **current)
{
	char	*dup;

	dup = ft_strdup((*current)->value);
	if (!dup)
		return (-1);
	ft_lstadd_back(args, ft_lstnew(dup));
	return (1);
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

int	ft_process_redirection_extended(t_command *cmd, t_token **current,
	char *redir_target)
{
	if ((*current)->type == T_REDIR_IN || (*current)->type == T_HEREDOC)
	{
		if ((*current)->type == T_HEREDOC)
			ft_handle_heredoc_case(cmd, current, redir_target);
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
