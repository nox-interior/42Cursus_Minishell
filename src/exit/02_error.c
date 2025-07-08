/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:10:56 by amarroyo          #+#    #+#             */
/*   Updated: 2025/07/08 12:11:09 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_puterror(char *err, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(err, 2);
	ft_putstr_fd("\n", 2);
}

void	print_exec_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void	print_fd_error(char *call)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(call, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}