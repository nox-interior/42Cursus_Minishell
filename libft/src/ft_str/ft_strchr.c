/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:04:51 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/10 12:59:05 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

//Locates the first occurrence of c (converted to a char) in the string 
//pointed to by s.  The terminating null character is considered to be part of
//the string; therefore if c is ‘\0', the function locates the terminating ‘\0'
//Return: A pointer to the first occurrence of the char c in s.
//Return: A NULL pointer if the char is not found.

char	*ft_strchr(const char *s, int c )
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}
