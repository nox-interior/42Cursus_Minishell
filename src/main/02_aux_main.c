/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_aux_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:01:22 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/11 13:04:46 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_user_input(void)
{
	if (isatty(STDIN_FILENO))
		return (readline("$ "));
	return (get_next_line(STDIN_FILENO));
}

int	ft_should_exit(char *line)
{
	if (!line)
	{
		if (isatty(STDIN_FILENO))
			write(1, "exit\n", 5);
		return (1);
	}
	return (0);
}
