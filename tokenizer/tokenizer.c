/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:22:57 by amarroyo          #+#    #+#             */
/*   Updated: 2025/04/02 13:55:06 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_tokenizer(char *prompt)
{
    t_token *token;
    int i;
    
    i = 0;
    while (prompt[i])
    {
        if (prompt[i] == '<')
            set_status(T_REDIR_IN); // o return, como lo metemos en la estructura??
    }
}