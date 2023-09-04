/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:24:16 by csenand           #+#    #+#             */
/*   Updated: 2023/07/05 11:36:16 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	SYNOPSIS
**	Create new list
**
** 	DESCRIPTION
** 	Allocates (with malloc(3)) and returns a new node.
**	The member variable ’content’ is initialized with
**	the value of the parameter ’content’. The variable
**	’next’ is initialized to NULL.
** 	
**	PARAMETERS
**	content: The content to create the node with.
**
**	RETURN VALUE
**	The new node
*/

#include "../include/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->content = content;
	new->next = NULL;
	return (new);
}
