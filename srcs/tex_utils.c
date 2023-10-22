/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loulou <loulou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 18:37:17 by loulou            #+#    #+#             */
/*   Updated: 2023/10/22 18:39:12 by loulou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_xpm(t_ms *ms, char c)
{
	if (c == 'N')
		ms->tex->no_tex = mlx_load_xpm42(ms->paths);
	if (c == 'S')
		ms->tex->so_tex = mlx_load_xpm42(ms->paths);
	if (c == 'W')
		ms->tex->we_tex = mlx_load_xpm42(ms->paths);
	if (c == 'E')
		ms->tex->ea_tex = mlx_load_xpm42(ms->paths);
}

bool	load_single_texture(t_ms *ms, int i, char c)
{
	int	tex_index;

	tex_index = -1;
	if (c == 'N')
		tex_index = 0;
	if (c == 'S')
		tex_index = 1;
	if (c == 'W')
		tex_index = 2;
	if (c == 'E')
		tex_index = 3;
	if (tex_index != -1 && ms->texture_loaded[tex_index])
		return (printf("❌ Error\n❌ Duplicate texture found.\n"), false);
	ms->paths = ft_strdup(ms->map_args[i] + 2);
	if ((open(ms->paths, O_RDONLY)) == -1)
	{
		free(ms->paths);
		return (printf("❌ Error\n%s\n", ERR_TEX), false);
	}
	load_xpm(ms, c);
	if (tex_index != -1)
		ms->texture_loaded[tex_index] = true;
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
	{
		clean_exit(ms);
		return (false);
	}
	return (true);
}
