/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loulou <loulou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 18:56:44 by loulou            #+#    #+#             */
/*   Updated: 2023/10/22 18:59:05 by loulou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_valid_position(char **map, int x, int y)
{
	return (x >= 0 && y >= 0 && map[x] && map[x][y]
		&& (map[x][y] == '0' || map[x][y] == 'N'
		|| map[x][y] == 'S' || map[x][y] == 'E' || map[x][y] == 'W'));
}

bool	has_boundary_violation(char **map, int x, int y)
{
	if (!map[x] || !map[x][y] || map[x][y] == ' ' || map[x][y] == '\t'
		|| (map[x][y + 1] == '\0' && map[x][y] == '0')
		|| (map[x][y + 1] == '\n' && map[x][y] == '0'))
		return (true);
	return (false);
}

int	floodfill(char **map, char v, int x, int y)
{
	if (has_boundary_violation(map, x, y))
		return (1);
	if (is_valid_position(map, x, y) && map[x][y] == '0')
	{
		map[x][y] = v;
		return (floodfill(map, v, x + 1, y)
			|| floodfill(map, v, x - 1, y)
			|| floodfill(map, v, x, y + 1)
			|| floodfill(map, v, x, y - 1));
	}
	return (0);
}

int	rev_floodfill(char **map, char v, int x, int y)
{
	if (has_boundary_violation(map, x, y))
		return (1);
	if (map[x][y] == 'X')
	{
		map[x][y] = v;
		return (rev_floodfill(map, v, x + 1, y)
			|| rev_floodfill(map, v, x - 1, y)
			|| rev_floodfill(map, v, x, y + 1)
			|| rev_floodfill(map, v, x, y - 1));
	}
	return (0);
}
