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
		ft_free_tab_char(ms->paths);
}

void	map_error_exit(t_ms *ms)
{
	free_exit(ms);
	// (void) ms;
	// printf("\nFree from here\n");
	// exit(1);
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
	// if(ms->tex->no_tex != NULL)
		free(ms->tex->no_tex);
	// if(ms->tex->so_tex != NULL)
		free(ms->tex->so_tex);
	// if(ms->tex->we_tex != NULL)
		free(ms->tex->we_tex);
	// if(ms->tex->ea_tex != NULL)
		free(ms->tex->ea_tex);
	// if(ms->tex->no != NULL)
		ft_free_tab_int(ms->tex->no, len_of_double_p_int(ms->tex->no));
	// if(ms->tex->so != NULL)
		ft_free_tab_int(ms->tex->so, len_of_double_p_int(ms->tex->so));
	// if(ms->tex->we != NULL)
		ft_free_tab_int(ms->tex->we, len_of_double_p_int(ms->tex->we));
	// if(ms->tex->ea != NULL)
		ft_free_tab_int(ms->tex->ea, len_of_double_p_int(ms->tex->ea));
}

int clean_exit(t_ms *ms)
{
	free_texture(ms);
	if(ms->tex != NULL)
		free(ms->tex);
	// free_exit(ms);
	printf("Exit\n");
	return(0);
}
