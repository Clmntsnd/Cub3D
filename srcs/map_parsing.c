/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:51:08 by jpilotte          #+#    #+#             */
/*   Updated: 2023/10/17 15:07:48 by jpilotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	remove_map(t_ms *ms)
{
	int	i;
	int	j;
	int	flag;

	i = -1;
	j = 0;
	flag = 0;
	ms->main_map = (char **)ft_calloc(ms->height + 1, sizeof(char *));
	while (++i < ms->height)
	{
		while (map_starts_with_any_arg(ms, i))
		{
			i++;
			flag++;
		}
		if (check_map_character(ms->map[i][j], flag, false))
		{
			printf("❌ Error\n❌ Too few or too many textures..\n");
			ft_free_tab_char(ms->map);
			map_error_exit(ms);
		}
		else if (check_map_character(ms->map[i][j], flag, true))
			ms->main_map[j++] = ft_strdup(ms->map[i]);
	}
	ft_free_tab_char(ms->map);
}

bool	should_clean_string(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return ((ft_strncmp(str, "NO", 2) == 0)
		|| (ft_strncmp(str, "EA", 2) == 0)
		|| (ft_strncmp(str, "SO", 2) == 0)
		|| (ft_strncmp(str, "WE", 2) == 0)
		|| (ft_strncmp(str, "C", 1) == 0)
		|| (ft_strncmp(str, "F", 1) == 0));
}

void	remove_map_args(t_ms *ms)
{
	int		i;
	int		flag;
	char	*temp;

	ms->map_args = (char **)ft_calloc(7, sizeof(char *));
	i = -1;
	flag = 0;
	while (ms->map[++i])
	{
		if (should_clean_string(ms->map[i]))
			temp = ft_strdup(clean_string(ms->map[i]));
		else
			temp = ft_strdup(ms->map[i]);
		if ((ft_strncmp(ms->map[i], "NO", 2) == 0)
			|| (ft_strncmp(ms->map[i], "EA", 2) == 0)
			|| (ft_strncmp(ms->map[i], "SO", 2) == 0)
			|| (ft_strncmp(ms->map[i], "WE", 2) == 0)
			|| (ft_strncmp(ms->map[i], "C", 1) == 0)
			|| (ft_strncmp(ms->map[i], "F", 1) == 0))
			ms->map_args[flag++] = ft_strdup(temp);
		free(temp);
	}
	check_flag(ms, flag);
}

void	get_map(t_ms *ms, char *argv)
{
	int		i;
	int		fd;
	char	*temp;

	i = 0;
	fd = open(argv, O_RDONLY);
	if (ms->map == NULL)
		ms->map = (char **)ft_calloc(ms->height + 1, sizeof(char *));
	while (i <= ms->height)
	{
		temp = get_next_line(fd);
		ms->map[i] = temp;
		i++;
	}
	free(temp);
	close(fd);
}

void	get_map_size(t_ms *ms, char argv[1])
{
	int		i;
	int		fd;
	char	*rows;

	fd = open(argv, O_RDONLY);
	rows = get_next_line(fd);
	ms->height = 0;
	ms->width = 0;
	i = -1;
	while (rows[++i])
	{
		i++;
		ms->width++;
	}
	while (rows != NULL)
	{
		free(rows);
		rows = get_next_line(fd);
		ms->height++;
	}
	free(rows);
	close(fd);
}
