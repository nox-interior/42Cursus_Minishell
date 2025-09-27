/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:54:49 by amarroyo          #+#    #+#             */
/*   Updated: 2024/05/08 14:27:48 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	ft_print_str(char *str)
{
	int	printlen;
	int	i;

	printlen = 0;
	i = 0;
	if (!str)
		printlen += write(1, "(null)", 6);
	else
	{
		while (str[i] != '\0')
		{
			printlen += ft_print_char(str[i]);
			i++;
		}
	}
	return (printlen);
}
