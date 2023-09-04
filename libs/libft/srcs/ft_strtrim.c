/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:55:53 by csenand           #+#    #+#             */
/*   Updated: 2023/07/05 11:34:23 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** 	DESCRIPTION
** 	Allocates (with malloc(3)) and returns a copy of 's1' with the characters 
**	specified in ’set’ removed from the beginning and the end of the string.
** 	
**	PARAMETERS
**	s1: The string to be trimmed.
**	set: The reference set of characters to trim
**
**	RETURN VALUE
**	The trimmed string.
**	NULL if the allocation fails.
*/

#include "../include/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i]))
		i--;
	return (ft_substr(s1, 0, i + 1));
}
