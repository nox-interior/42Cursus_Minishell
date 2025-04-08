/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:41:42 by amarroyo          #+#    #+#             */
/*   Updated: 2024/01/25 10:43:50 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <stdint.h>

int		ft_print_char(int c);
int		ft_print_str(char *str);
int		ft_print_nbr(int nbr);
int		ft_print_hex(long nbr, int is_uppercase);
int		ft_print_unsint(unsigned int nbr);
int		ft_print_ptr(uintptr_t nbr);
int		ft_specifiers(char specifier, va_list arg_ptr);
int		ft_printf(const char *format, ...);

#endif
