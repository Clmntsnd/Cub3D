/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isdigit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:26:05 by csenand           #+#    #+#             */
/*   Updated: 2023/09/04 15:41:20 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
Library :
	#include <ctype.h>
Description : 
	The ft_str_isdigit() function tests for a string and checks if each
	character of the string is a digit.
Declaration :
	int	ft_str_isdigit(str *str)
Parameters :
	str - The string to test.
Return value :
	The str_isdigit() function returns zero if a character tests false and 
	returns 1 if all characters in the string are digits.
*/
bool	ft_str_isdigit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (ft_isdigit(str[i]) == 0)
			return (false);
	return (true);
}
