/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:03:51 by amarroyo          #+#    #+#             */
/*   Updated: 2024/05/08 14:01:07 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

// Converts lower-case to the corresponding upper-case
// Return: if the argument is a lower-case letter it returns the upper-case
// Return: otherwise the argument is returned unchanged.

int	ft_toupper(int c)
{
	int	upper;

	upper = (c - 32);
	if (c >= 'a' && c <= 'z')
	{
		return (upper);
	}
	return (c);
}
