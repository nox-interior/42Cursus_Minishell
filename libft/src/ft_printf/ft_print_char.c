/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:53:49 by amarroyo          #+#    #+#             */
/*   Updated: 2024/05/08 14:28:03 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	ft_print_char(int c)
{
	int	printlen;

	printlen = write(1, &c, 1);
	return (printlen);
}

// int	ft_print_char(int c)
// {
//     int	printlen = 0;

//     if (c == '\a')
//         printlen = write(1, "\\a", 2);
//     else if (c == '\b')
//         printlen = write(1, "\\b", 2);
//     else if (c == '\t')
//         printlen = write(1, "\\t", 2);
//     else if (c == '\n')
//         printlen = write(1, "\\n", 2);
//     else if (c == '\v')
//         printlen = write(1, "\\v", 2);
//     else if (c == '\f')
//         printlen = write(1, "\\f", 2);
//     else if (c == '\r')
//         printlen = write(1, "\\r", 2);
//     else
//         printlen = write(1, &c, 1);
//     return (printlen);
// }