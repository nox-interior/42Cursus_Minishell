/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:06:08 by amarroyo          #+#    #+#             */
/*   Updated: 2024/05/08 14:00:26 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

// Compares the first n characters form two strings (s1 and s2)
// Return: an int value that shows the difference between the characters
// in the i position in s1 and s2.
// Return: An integer greater than, equal to, or less than 0, 
// as the string s1 is greater than, equal to, or less than the string s2.

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s1[i] == s2[i])
	{
		if (i < (n - 1))
			i++;
		else
			return (0);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
