/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:21:24 by csenand           #+#    #+#             */
/*   Updated: 2023/09/04 15:40:39 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_free_tab_int(int **tab, size_t len)
{
	while (len-- > 0)
		tab[len] = ft_freenull(tab[len]);
	tab = ft_freenull(tab);
	return (0);
}
