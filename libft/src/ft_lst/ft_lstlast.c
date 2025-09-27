/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:29:43 by amarroyo          #+#    #+#             */
/*   Updated: 2024/05/08 13:58:21 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

// Returns the last node of the list

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*second_last;

	second_last = lst;
	if (!lst)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	while (second_last->next->next != NULL)
	{
		second_last = second_last->next;
	}
	return (second_last->next);
}
