/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:41:34 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/10 13:19:30 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

// used to allocate a block of contiguous memory for a specified 
// number of objects, each of a specified size.
// and sets them to '0'.
// Return: a pointer to the allocated memory. 

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)malloc(count * size);
	i = 0;
	if (str == NULL)
		return (NULL);
	while (i < count * size)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}
