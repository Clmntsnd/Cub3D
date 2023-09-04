/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:45:25 by csenand           #+#    #+#             */
/*   Updated: 2023/07/05 11:33:53 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** 	SYNOPSIS: look for the last occurance contained in 'c'
**
** 	DESCRIPTION:
** 	Scan thru string 's' and then scan from the end to look for the  
**	last char contained in 'c', stop there and return it.
*/

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i--;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (0);
}
