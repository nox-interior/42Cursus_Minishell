/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:27:36 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/30 13:06:52 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_unset_invalid_identifier(const char *arg, t_shell *shell)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd((char *)arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	shell->exit_status = 1;
}

int	ft_exec_builtin_unset(t_command *cmd, t_shell *shell)
{
	int	i;

	i = 1;
	shell->exit_status = 0;
	while (cmd->argv[i])
	{
		if (!ft_is_valid_identifier(cmd->argv[i]))
			ft_unset_invalid_identifier(cmd->argv[i], shell);
		else
			ft_remove_env_var(shell, cmd->argv[i]);
		i++;
	}
	return (shell->exit_status);
}
