/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:03:57 by amarroyo          #+#    #+#             */
/*   Updated: 2024/05/08 13:59:56 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

// allocates sufficient memory for a copy of the string s1,
// does the copy,
// returns a pointer to it.
// The pointer may subsequently be used as an argument to the function free
// If insufficient memory is available, NULL is returned.

char	*ft_strdup(const char *s1)
{
	size_t	length;
	char	*copy;

	length = ft_strlen(s1);
	copy = malloc(length + 1);
	if (s1 == NULL)
		return (NULL);
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, s1, length + 1);
	return (copy);
}
