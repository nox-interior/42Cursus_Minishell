/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:55:31 by amarroyo          #+#    #+#             */
/*   Updated: 2024/05/08 14:27:41 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	ft_print_unsint(unsigned int nbr)
{
	int	printlen;

	printlen = 0;
	if (nbr > 9)
		printlen += ft_print_unsint(nbr / 10);
	printlen += ft_print_char(nbr % 10 + '0');
	return (printlen);
}
