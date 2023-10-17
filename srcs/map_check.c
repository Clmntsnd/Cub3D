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
	if (check_valid_char(ms) )
		map_error_exit(ms);
	if (floodfill(ms->main_map, 'X', x, y) 
		|| rev_floodfill(ms->main_map, '0', x, y))
	{
		printf("❌ Error\n%s\n", ERR_WALL),
		map_error_exit(ms);
	}
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

int	floodfill(char **map, char v, int x, int y)
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
		return (1);
	return (0);
}

int	rev_floodfill(char **map, char v, int x, int y)
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
		return (1);
	return (0);
}
