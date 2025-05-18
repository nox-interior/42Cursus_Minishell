/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_aux_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:37:49 by amarroyo          #+#    #+#             */
/*   Updated: 2025/05/18 12:59:12 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_valid_arg_token(t_tok_type type)
{
	return (type == T_WORD || type == T_VAR || type == T_S_QUOTE
		|| type == T_D_QUOTE);
}

int	ft_is_redirection(t_tok_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT || type == T_HEREDOC
		|| type == T_APPEND);
}

int	ft_is_special_character(t_tok_type type)
{
	return (type == T_SEMICOLON || type == T_EXCLAMATION || type == T_AMPERSAND
		|| type == T_AND || type == T_OR || type == T_INVALID);
}

void	ft_init_command(t_command *cmd)
{
	cmd->argv = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->next = NULL;
}
