/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 10:29:54 by amarroyo          #+#    #+#             */
/*   Updated: 2023/10/01 15:51:42 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

// It takes a string as input and converts it to an integer. 
// Skips any leading whitespace characters and then converts 
// the remaining characters until a non-digit character is encountered.
// Return: the resulting integer

int	ft_atoi(const char *str)
{
	int	i;
	int	nbr;
	int	sign;
	
	i = 0;
	nbr = 0;
	sign = 1;
	while (str[i])
	{
		while ((str[i] >= 8 && str[i] <= 13) || str[i] == 32)
			i++;
		if (str[i] == '-' || str[i] == '+')
		{
			if (str[i] == '-')
				sign = -1;
			i++;
		}
		while (str[i] >= '0' && str[i] <= '9')
		{
			nbr = (nbr * 10) + (str[i] - '0');
			i++;
		}
		break;
	}
	return (sign * nbr);
}
