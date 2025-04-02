/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:43:49 by amarroyo          #+#    #+#             */
/*   Updated: 2024/05/08 14:27:37 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	arg_ptr;
	int		printlen;
	int		i;

	va_start(arg_ptr, format);
	printlen = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			printlen += ft_specifiers(format[i], arg_ptr);
		}
		else
			printlen += write(1, &format[i], 1);
		i++;
	}
	va_end(arg_ptr);
	return (printlen);
}
