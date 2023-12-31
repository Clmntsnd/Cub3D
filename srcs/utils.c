/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loulou <loulou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:49:26 by jpilotte          #+#    #+#             */
/*   Updated: 2023/10/22 18:41:29 by loulou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*clean_string(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			str[j++] = str[i];
		i++;
	}
	if (j > 0 && str[j - 1] == ' ')
		j--;
	str[j] = '\0';
	return (str);
}

void	get_player_pos(t_ms *ms)
{
	int	i;
	int	j;
	int	flag;

	i = -1;
	flag = 0;
	while (ms->main_map[++i])
	{
		j = -1;
		while (ms->main_map[i][++j])
		{
			if (ms->main_map[i][j] == 'N' || ms->main_map[i][j] == 'S'
				|| ms->main_map[i][j] == 'W' || ms->main_map[i][j] == 'E')
			{
				flag++;
				set_dir(ms, i, j);
			}
		}
	}
	if (flag > 1 || flag == 0)
	{
		printf("❌ Error\n%s\n", ERR_M_PL);
		map_error_exit(ms);
	}
}

void	set_dir(t_ms *ms, int i, int j)
{
	if (ms->main_map[i][j] == 'N')
	{
		ms->game->pl_dir.x = -1;
		ms->game->plane.y = 0.66;
	}
	if (ms->main_map[i][j] == 'S')
	{
		ms->game->pl_dir.x = 1;
		ms->game->plane.y = -0.66;
	}
	if (ms->main_map[i][j] == 'E')
	{
		ms->game->pl_dir.y = 1;
		ms->game->plane.x = 0.66;
	}
	if (ms->main_map[i][j] == 'W')
	{
		ms->game->pl_dir.y = -1;
		ms->game->plane.x = -0.66;
	}
	ms->game->pl_pos.x = i + 0.5;
	ms->game->pl_pos.y = j + 0.5;
	ms->main_map[i][j] = '0';
}
