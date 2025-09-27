/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_identifiers_export.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:48:37 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/23 11:52:26 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_valid_identifier(const char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	if (!(ft_isalpha(s[0]) || s[0] == '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	ft_export_invalid_identifier(const char *arg, t_shell *shell)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd((char *)arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	shell->exit_status = 1;
}
