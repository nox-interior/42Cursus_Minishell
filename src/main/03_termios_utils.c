/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_termios_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 00:00:00 by amarroyo          #+#    #+#             */
/*   Updated: 2025/09/25 20:34:06 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>

void	ft_disable_echoctl(void)
{
	struct termios	term;

	if (isatty(STDIN_FILENO))
	{
		if (tcgetattr(STDIN_FILENO, &term) == 0)
		{
			term.c_lflag &= ~ECHOCTL;
			tcsetattr(STDIN_FILENO, TCSANOW, &term);
		}
	}
}

void	ft_enable_echoctl(void)
{
	struct termios	term;

	if (isatty(STDIN_FILENO))
	{
		if (tcgetattr(STDIN_FILENO, &term) == 0)
		{
			term.c_lflag |= ECHOCTL;
			tcsetattr(STDIN_FILENO, TCSANOW, &term);
		}
	}
}
