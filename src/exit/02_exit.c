/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:42:02 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/11 10:45:43 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

void	ft_set_exit_status(int status)
{
	g_exit_status = status;
}

int	ft_get_exit_status(void)
{
	return (g_exit_status);
}
