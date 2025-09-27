/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_overflow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:05:47 by amarroyo          #+#    #+#             */
/*   Updated: 2025/06/16 19:24:20 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>

int	check_overflow(long nbr, int sign)
{
	if (sign == 1 && nbr > INT_MAX)
		return (-1);
	if (sign == -1 && (-nbr) < INT_MIN)
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	nbr;
	int		sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while ((str[i] >= 8 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10) + (str[i] - '0');
		if (check_overflow(nbr, sign) != 1)
			return (check_overflow(nbr, sign));
		i++;
	}
	return (sign * nbr);
}
