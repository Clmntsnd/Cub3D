/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:43:37 by csenand           #+#    #+#             */
/*   Updated: 2023/07/05 11:35:55 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**						* ft_memcpy vs ft_memmove *
**	ft_memmove can handle overlapping destination and source blocks of memory
**	whereas for ft_memecpy if the destination and source of memory overlap 
**	the behavior is undefined
**
**	If we're not sure whether or not the dest ans src blocks of memory 
**	will overlap then we should use ft_memmove because it's guaranteed 
**	to be safe.
*/

#include "../include/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*c_dst;
	char	*c_src;

	c_src = (char *)src;
	c_dst = (char *)dst;
	if (!c_src || !c_dst)
		return (NULL);
	if (c_dst > c_src)
	{
		while (len > 0)
		{
			c_dst[len - 1] = c_src[len - 1];
			len--;
		}
	}
	else
	{
		ft_memcpy(c_dst, c_src, len);
	}
	return (dst);
}
