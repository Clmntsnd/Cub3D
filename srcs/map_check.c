/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:51:25 by jpilotte          #+#    #+#             */
/*   Updated: 2023/10/17 16:16:50 by jpilotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_map(t_ms *ms)
{
	int	x;
	int	y;

	x = ms->game->pl_pos.x;
	y = ms->game->pl_pos.y;
	if (check_valid_char(ms))
		map_error_exit(ms);
	floodfill(ms->main_map, 'X', x, y);
	rev_floodfill(ms->main_map, '0', x, y);
}

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
	while (*ms->main_map[++j] != '\0')
	j = 0;
	while (ms->main_map[j] != NULL)
	{
		if (check_valid_char_in_row(ms->main_map[j]) == 1)
		{
			return (1);
		}
	}
	return (0);
}

void	check_arg_dup(t_ms *ms)
{
	int	i;
	int	*flag;

	i = -1;
	flag = ft_calloc(6, sizeof(int));
	while (++i < 5)
	{
		if (ms->map_args[i][0] == 'N')
			flag[0] = 1;
		else if (ms->map_args[i][0] == 'S')
			flag[1] = 1;
		else if (ms->map_args[i][0] == 'W')
			flag[2] = 1;
		else if (ms->map_args[i][0] == 'E')
			flag[3] = 1;
		else if (ms->map_args[i][0] == 'F')
			flag[4] = 1;
		else if (ms->map_args[i][0] == 'C')
			flag[5] = 1;
		else if (flag[i] != 1)
		{
			printf("❌ Error\n%s\n", ERR_D_ARG);
			map_error_exit(ms);
		}
	}
}

void	floodfill(char **map, char v, int x, int y)
{
	while (map[x][y] == '0')
	{
		map[x][y] = v;
		floodfill(map, v, x + 1, y);
		floodfill(map, v, x - 1, y);
		floodfill(map, v, x, y - 1);
		floodfill(map, v, x, y + 1);
	}
	if (map[x][y] == ' ' || map[x][y] == '\t' || map[x][0] == '0'
		|| (map[x][y + 1] == '\n' && map[x][y] == '0'))
		printf("❌ Error\n%s\n", ERR_WALL);
}

void	rev_floodfill(char **map, char v, int x, int y)
{
	while (map[x][y] == 'X')
	{
		map[x][y] = v;
		rev_floodfill(map, v, x + 1, y);
		rev_floodfill(map, v, x - 1, y);
		rev_floodfill(map, v, x, y - 1);
		rev_floodfill(map, v, x, y + 1);
	}
	if (map[x][y] == ' ' || map[x][y] == '\t' || map[x][0] == '0' 
		|| (map[x][y + 1] == '\n' && map[x][y] == '0'))
		printf("❌ Error\n%s\n", ERR_WALL);
}
