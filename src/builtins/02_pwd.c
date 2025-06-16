/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:18:53 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/16 17:45:12 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_builtin_pwd(t_command *cmd, t_shell *shell)
{
	char	*cwd;
	int		len;

	(void)cmd;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		shell->exit_status = 1;
		return (1);
	}
	len = ft_strlen(cwd);
	write(1, cwd, len);
	write(1, "\n", 1);
	free(cwd);
	shell->exit_status = 0;
	return (0);
}
