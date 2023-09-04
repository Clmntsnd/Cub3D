/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:41:46 by csenand           #+#    #+#             */
/*   Updated: 2023/07/05 11:35:09 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s)
{
	char	*dst;
	size_t	i;
	size_t	len;

	len = ft_strlen(s) + 1;
	dst = malloc(sizeof(char) * len);
	i = 0;
	if (!dst)
		return (NULL);
	while (i < ft_strlen(s))
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
