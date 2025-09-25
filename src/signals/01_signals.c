/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:47:58 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/25 20:41:19 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	ft_handle_sigint(int sig)
{
	(void)sig;
	g_signal = SIGINT + 128;
	write(1, "^C\n", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// Handler para cuando se está ejecutando un comando
void	ft_handle_sigint_exec(int sig)
{
	(void)sig;
	g_signal = SIGINT + 128;
	write(1, "\n", 1);
}

void	ft_setup_interactive_signals(void)
{
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, ft_handle_sigquit_prompt);
}

void	ft_setup_exec_signals(void)
{
	signal(SIGINT, ft_handle_sigint_exec);
	signal(SIGQUIT, ft_handle_sigquit_exec);
}
