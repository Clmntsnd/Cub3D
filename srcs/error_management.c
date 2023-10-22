/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:47:04 by jpilotte          #+#    #+#             */
/*   Updated: 2023/10/17 13:48:28 by jpilotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	len_of_double_p_int(int **pp)
{
	int	i;

	if (pp == NULL)
		return (0);
	i = 0;
	while (pp[i] != NULL)
		i++;
	return (i);
}

void	free_texture(t_ms *ms)
{
	if (ms->texture_loaded[0])
	{
		ft_free_tab_int(ms->tex->no, len_of_double_p_int(ms->tex->no));
		mlx_delete_xpm42(ms->tex->no_tex);
	}
	if (ms->texture_loaded[1])
	{
		ft_free_tab_int(ms->tex->so, len_of_double_p_int(ms->tex->so));
		mlx_delete_xpm42(ms->tex->so_tex);
	}
	if (ms->texture_loaded[2])
	{
		ft_free_tab_int(ms->tex->we, len_of_double_p_int(ms->tex->we));
		mlx_delete_xpm42(ms->tex->we_tex);
	}
	if (ms->texture_loaded[3])
	{
		ft_free_tab_int(ms->tex->ea, len_of_double_p_int(ms->tex->ea));
		mlx_delete_xpm42(ms->tex->ea_tex);
	}
}

void	free_exit(t_ms *ms)
{
	if (ms->map_args)
		ft_free_tab_char(ms->map_args);
	if (ms->main_map)
		ft_free_tab_char(ms->main_map);
	if (ms->tex)
	{
		free_texture(ms);
		ms->tex = ft_freenull(ms->tex);
	}
	if (ms->game)
		ms->game = ft_freenull(ms->game);
	if (ms != NULL)
		ms = ft_freenull(ms);
}

void	map_error_exit(t_ms *ms)
{
	free_exit(ms);
	exit(1);
}

int	clean_exit(t_ms *ms)
{
	free_exit(ms);
	printf("Exit\n");
	return (0);
}
