/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:50:32 by amarroyo          #+#    #+#             */
/*   Updated: 2024/05/08 14:00:03 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

// Allocates memory with malloc and returns a new string, created by the
// concatenation of 's1' and 's2'
// Return: the new string
// Return: NULL if memory allocation fails.

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, (len_s1 + len_s2 + 1));
	ft_strlcat(str, s2, (len_s1 + len_s2 + 1));
	return (str);
}
