/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:06:31 by csenand           #+#    #+#             */
/*   Updated: 2023/07/05 11:35:17 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** 	SYNOPSIS: look for the first occurance contained in 'c'
**
** 	DESCRIPTION:
** 	Scan thru string 's' and look for the first char contained in 'c',
**	stop there and return the rest of the string.
*/

#include "../include/libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (0);
}
