/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:51:25 by jpilotte          #+#    #+#             */
/*   Updated: 2023/10/17 13:51:25 by jpilotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void check_map(t_ms *ms)
{
	int x;
	int y;

	x = ms->game->pl_pos.x;
	y = ms->game->pl_pos.y;
	if(check_valid_char(ms))
		map_error_exit(ms);
	floodfill(ms->main_map, '0', '2', x, y);
	floodfill(ms->main_map, '2', '0', x, y);
}

int check_valid_char(t_ms *ms)
{
	int		i;
	int		j;

	j = 0;
	while (*ms->main_map[j] != '\0')
	{
		i = 0;
		while (ms->main_map[j][i] != '\0')
		{
			if (ms->main_map[j][i] == '0' || ms->main_map[j][i] == '1' || ms->main_map[j][i] == 'N' || ms->main_map[j][i] == 'S' || ms->main_map[j][i] == 'E' || ms->main_map[j][i] == 'W' || ms->main_map[j][i] == '\t' || ms->main_map[j][i] == '\n' || ms->main_map[j][i] == ' ')
			{
				i++;
			}
			else
			{
				printf("Error\nInvalid character in map\n");
				return (1);
			}
		}
		j++;
	}
	return (0);
}

void check_arg_dup(t_ms *ms)
{
	int i;
	int *flag;

	i = 0;
	flag = ft_calloc(6, sizeof(int));
	while(i < 6)
	{
		if(ms->map_args[i][0] == 'N')
			flag[0] = 1;
		else if(ms->map_args[i][0] == 'S')
			flag[1] = 1;
		else if(ms->map_args[i][0] == 'W')
			flag[2] = 1;
		else if(ms->map_args[i][0] == 'E')
			flag[3] = 1;
		else if(ms->map_args[i][0] == 'F')
			flag[4] = 1;
		else if(ms->map_args[i][0] == 'C')
			flag[5] = 1;
		i++;
	}
	i = 0;
	while(i < 6)
	{
		if(flag[i] != 1)
		{
			printf("Error:\nDuplicate arguments..");
			map_error_exit(ms);
		}
		i++;
	}
}

void	floodfill(char **map, char u, char v, int x, int y)
{
	while (map[x][y] == u)
	{
		map[x][y] = v;
		floodfill(map, u, v, x + 1, y);
		floodfill(map, u, v, x - 1, y);
		floodfill(map, u, v, x, y - 1);
		floodfill(map, u, v, x, y + 1);
	}
	if (map[x][y] == ' ' || map[x][y] == '\t' || map[x][0] == '0' || (map[x][y + 1] == '\n' && map[x][y] == '0'))
	{
		printf("Error\nMap is not surrounded by walls\n");
		exit(0);
	}
}