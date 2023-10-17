/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:51:59 by jpilotte          #+#    #+#             */
/*   Updated: 2023/10/17 14:55:18 by jpilotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_ms	*get_ms(void)
{
	static t_ms	*ms = NULL;

	if (ms == NULL)
	{
		ms = (t_ms *)ft_calloc(1, sizeof(t_ms));
		ms->game = ft_calloc(1, sizeof(t_game));
	}
	return (ms);
}

bool	load_single_texture(t_ms *ms, int i, char c)
{
	ms->paths = ft_strdup(ms->map_args[i] + 2);
	if ((open(ms->paths, O_RDONLY)) == -1)
	{
		free(ms->paths);
		return (printf("❌ Error\n%s\n", ERR_TEX), false);
	}
	if (c == 'N')
		ms->tex->no_tex = mlx_load_xpm42(ms->paths);
	if (c == 'S')
		ms->tex->so_tex = mlx_load_xpm42(ms->paths);
	if (c == 'W')
		ms->tex->we_tex = mlx_load_xpm42(ms->paths);
	if (c == 'E')
		ms->tex->ea_tex = mlx_load_xpm42(ms->paths);
	free(ms->paths);
	return (true);
}

bool	fill_texture(t_ms *ms)
{
	if (!ms->tex->no_tex || !ms->tex->so_tex 
		|| !ms->tex->ea_tex || !ms->tex->we_tex)
		return (printf("❌ Error\n%s\n", ERR_XPM_TEX), false);
	ms->tex->so = convert_texture(ms->tex->so_tex);
	ms->tex->no = convert_texture(ms->tex->no_tex);
	ms->tex->we = convert_texture(ms->tex->we_tex);
	ms->tex->ea = convert_texture(ms->tex->ea_tex);
	return (true);
}

bool	get_texture(t_ms *ms)
{
	int	i;

	ms->tex = ft_calloc(1, sizeof(t_tex));
	i = -1;
	while (ms->map_args[++i])
	{
		if (ft_strncmp(ms->map_args[i], "NO", 2) == 0)
			if (!load_single_texture(ms, i, 'N'))
				return (false);
		if (ft_strncmp(ms->map_args[i], "SO", 2) == 0)
			if (!load_single_texture(ms, i, 'S'))
				return (false);
		if (ft_strncmp(ms->map_args[i], "WE", 2) == 0)
			if (!load_single_texture(ms, i, 'W'))
				return (false);
		if (ft_strncmp(ms->map_args[i], "EA", 2) == 0)
			if (!load_single_texture(ms, i, 'E'))
				return (false);
	}
	if (!fill_texture(ms))
		return (false);
	return (true);
}

void	init_content(t_ms *ms, char *argv)
{
	get_map_size(ms, argv);
	get_map(ms, argv);
	remove_map_args(ms);
	get_player_pos(ms);
	check_map(ms);
}
