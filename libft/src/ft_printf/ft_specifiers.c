/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifiers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:47:40 by amarroyo          #+#    #+#             */
/*   Updated: 2024/05/08 14:27:05 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	ft_specifiers(char specifier, va_list arg_ptr)
{
	int	printlen;

	printlen = 0;
	if (specifier == 'c')
		printlen += ft_print_char(va_arg(arg_ptr, int));
	else if (specifier == 's')
		printlen += ft_print_str(va_arg(arg_ptr, char *));
	else if (specifier == 'd' || specifier == 'i')
		printlen += ft_print_nbr((va_arg(arg_ptr, int)));
	else if (specifier == 'x')
		printlen += ft_print_hex((va_arg(arg_ptr, unsigned int)), 0);
	else if (specifier == 'X')
		printlen += ft_print_hex((va_arg(arg_ptr, unsigned int)), 1);
	else if (specifier == 'u')
		printlen += ft_print_unsint(va_arg(arg_ptr, unsigned int));
	else if (specifier == 'p')
	{
		printlen += write(1, "0x", 2);
		printlen += ft_print_ptr(va_arg(arg_ptr, uintptr_t));
	}
	else if (specifier == '%')
		printlen += ft_print_char(specifier);
	else
		printlen += ft_print_char('%');
	return (printlen);
}
