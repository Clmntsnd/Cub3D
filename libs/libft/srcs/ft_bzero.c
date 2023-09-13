/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:14:15 by csenand           #+#    #+#             */
/*   Updated: 2023/09/04 15:40:12 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

/*
				** LONG VERSION **
				
void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ucs;

	ucs = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ucs[i] = 0;
		i++;
	}
	s = ucs;
}
*/