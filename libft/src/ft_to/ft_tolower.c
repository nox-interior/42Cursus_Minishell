/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:52:28 by amarroyo          #+#    #+#             */
/*   Updated: 2024/05/08 14:01:02 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

// converts upper-case into lower-case
// return: if the argument is upper-case, its lower-case.
// return: if the argument is not upper-case, returns the original c.

int	ft_tolower(int c)
{
	int	lower;

	lower = (c + 32);
	if (c >= 'A' && c <= 'Z')
	{
		return (lower);
	}
	return (c);
}
