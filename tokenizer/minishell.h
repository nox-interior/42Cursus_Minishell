/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 09:55:21 by amarroyo          #+#    #+#             */
/*   Updated: 2025/04/02 10:21:23 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "stdio.h"

// Token codes
typedef enum e_token
{
    T_STRING,           //ENTRE COMILLAS "" ''?
    T_WORD,             //SIN COMILLAS
    T_PIPE,
    T_REDIR_IN,
    T_REDIR_OUT,
    T_HEREDOC,
    T_APPEND,
    T_PIPE,
    T_QUOTE,
    T_DOUBLE_QUOTE,
    
    
}

#endif
