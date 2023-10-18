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

void	free_exit(t_ms *ms)
{
	if (ms->main_map != NULL)
		ft_free_tab_char(ms->main_map);
	if (ms->paths != NULL)
		free(ms->paths);
}

void	map_error_exit(t_ms *ms)
{
	free_exit(ms);
	exit(1);
}

int		len_of_double_p_int(int **pp)
{
	int i;

	i = 0;
	while (pp[i] != NULL)
		i++;
	return (i);
}

void	free_texture(t_ms *ms)
{
	free(ms->tex->no_tex);
	free(ms->tex->so_tex);
	free(ms->tex->we_tex);
	free(ms->tex->ea_tex);
	ft_free_tab_int(ms->tex->no, len_of_double_p_int(ms->tex->no));
	ft_free_tab_int(ms->tex->so, len_of_double_p_int(ms->tex->so));
	ft_free_tab_int(ms->tex->we, len_of_double_p_int(ms->tex->we));
	ft_free_tab_int(ms->tex->ea, len_of_double_p_int(ms->tex->ea));
}

int clean_exit(t_ms *ms)
{
	free_texture(ms);
	if(ms->tex != NULL)
		free(ms->tex);
	printf("Exit\n");
	return(0);
}
