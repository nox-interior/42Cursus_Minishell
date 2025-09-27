/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_signals_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:00:00 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/25 20:41:28 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handler para SIGQUIT durante la ejecución: no hace nada
void	ft_handle_sigquit_exec(int sig)
{
	(void)sig;
}

// Handler para SIGQUIT en el prompt: redibuja el prompt
void	ft_handle_sigquit_prompt(int sig)
{
	(void)sig;
	if (isatty(STDIN_FILENO))
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_setup_noninteractive_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_setup_signals(void)
{
	if (isatty(STDIN_FILENO))
		ft_setup_interactive_signals();
	else
		ft_setup_noninteractive_signals();
}

void	ft_setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
