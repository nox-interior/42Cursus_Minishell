/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:39:58 by amarroyo          #+#    #+#             */
/*   Updated: 2024/05/08 14:00:35 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

// Locates the last occurrence of c (converted to char) in the string
// pointed by s.
// Return: A pointer to the first occurrence of c in s
// Return: A NULL pointer if c is not found

char	*ft_strrchr(const char *s, int c)
{
	const char	*str;

	str = s;
	while (*s != '\0')
		s++;
	while (s >= str)
	{
		if (*s == (char)c)
			return ((char *)s);
		s--;
	}
	return (NULL);
}

// char *ft_strrchr(const char *s, int c)
// {
//     int len = 0;
//     while (s[len] != '\0')
//     {
//         len++;
//     }

//     int i = len;
//     while (i >= 0)
//     {
//         if (s[i] == (char)c)
//         {
//             return (char *)&s[i];
//         }
//         i--;
//     }
//     return NULL;
// }
