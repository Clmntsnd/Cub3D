/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:58:06 by csenand           #+#    #+#             */
/*   Updated: 2023/07/05 11:35:49 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ucb;

	i = 0;
	if (!b)
		return (NULL);
	ucb = (unsigned char *)b;
	while (i < len)
	{
		ucb[i] = c;
		i++;
	}
	return (b = ucb);
}
