/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_command_parser_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 00:00:00 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/01 16:12:54 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_create_quoted_delimit(t_token *next_token, char *redir_target)
{
	char	*quote_char;
	char	*temp1;
	char	*temp2;

	if (next_token->type == T_S_QUOTE)
		quote_char = "'";
	else
		quote_char = "\"";
	temp1 = ft_strjoin(quote_char, redir_target);
	temp2 = ft_strjoin(temp1, quote_char);
	free(temp1);
	free(redir_target);
	return (temp2);
}

static int	ft_handle_heredoc_case(t_command *cmd, t_token **current,
	char *redir_target)
{
	if ((*current)->next->type == T_S_QUOTE
		|| (*current)->next->type == T_D_QUOTE)
		cmd->delimit = ft_create_quoted_delimit((*current)->next, redir_target);
	else
		cmd->delimit = redir_target;
	cmd->heredoc = 1;
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
