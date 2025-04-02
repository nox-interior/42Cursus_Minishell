/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 09:55:21 by amarroyo          #+#    #+#             */
/*   Updated: 2025/04/02 16:34:20 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
//# include "ft_printf.h"
//# include "get_next_line.h"
# include <stdio.h>
# include <stdlib.h> // malloc
# include <string.h> // para strdup
# include <readline/history.h>
# include <readline/readline.h>

// Token codes
typedef enum e_tok_type
{
	T_NONE, // para evitar tener tokens sin tipo, control de errores
	T_SPACES,
	T_WORD,
	T_STRING,
	T_VAR,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_HEREDOC,
	T_APPEND
}					t_tok_type;

// Token structure
typedef struct s_token
{
	t_tok_type		type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

//

#endif
