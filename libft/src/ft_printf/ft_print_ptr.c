/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:10:08 by amarroyo          #+#    #+#             */
/*   Updated: 2024/05/08 14:27:52 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	ft_print_ptr(uintptr_t nbr)
{
	int		printlen;
	char	*lower_case;

	lower_case = "0123456789abcdef";
	printlen = 0;
	if (nbr < 16)
		printlen += ft_print_char(lower_case[nbr]);
	else
	{
		printlen += ft_print_ptr(nbr / 16);
		printlen += ft_print_char(lower_case[nbr % 16]);
	}
	return (printlen);
}
