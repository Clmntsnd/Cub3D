/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:36:11 by csenand           #+#    #+#             */
/*   Updated: 2023/07/05 11:36:25 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** 	DESCRIPTION
** 	Returns the last node of the list.
** 	
**	PARAMETERS
**	lst: The beginning of the list.
**
**	RETURN VALUE
**	Last node of the list
*/

#include "../include/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr_lst;

	if (!lst)
		return (0);
	ptr_lst = lst;
	while (ptr_lst && ptr_lst ->next != NULL)
		ptr_lst = ptr_lst -> next;
	return (ptr_lst);
}
