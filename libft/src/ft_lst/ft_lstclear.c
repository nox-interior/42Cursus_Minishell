/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 12:18:55 by amarroyo          #+#    #+#             */
/*   Updated: 2024/05/08 13:57:39 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*store_next;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		store_next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = store_next;
	}
}
