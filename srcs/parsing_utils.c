/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:34:41 by csenand           #+#    #+#             */
/*   Updated: 2023/10/17 18:34:44 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == '\t' || c == '\n' || c == ' ');
}

int	check_valid_char_in_row(char *row)
{
	int	i;

	i = -1;
	while (row[++i] != '\0')
	{
		if (!is_valid_char(row[i]))
		{
			printf("Error\nInvalid character in map\n");
			return (1);
		}
	}
	return (0);
}

int	check_valid_char(t_ms *ms)
{
	int	j;

	j = -1;
	while (ms->main_map[++j] != NULL)
	{
		if (check_valid_char_in_row(ms->main_map[j]) == 1)
			return (1);
	}
	return (0);
}
