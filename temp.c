void free_exit(t_ms *ms){
	printf("ms: %p\n", ms);

	printf("ms->map: %p\n", ms->map);
	printf("ms->main_map:%p\n", ms->main_map);
	printf("ms->map_args: %p\n", ms->map_args);
	printf("ms->game: %p\n", ms->game);
	printf("ms->mlx: %p\n", ms->mlx);
	printf("ms->tex: %p\n", ms->tex);
	printf("ms->paths: %p\n", ms->paths);
	if(ms->map != NULL)
		ft_free_tab_char(ms->map);
	if(ms->main_map != NULL)
		ft_free_tab_char(ms->main_map);
	if(ms->map_args != NULL){
		int i = 0;
		while (ms->map_args[i])
		{
			printf("ms->map_args[%d]: %p\n", i, ms->map_args[i]);
			if (ms->map_args[i] != NULL)
				ms->map_args[i] = ft_freenull(ms->map_args[i]);
			i++;
		}
		ms->map_args = ft_freenull(ms->map_args);
	}
		// ft_free_tab_char(ms->map_args);
	if(ms->game != NULL)
		free(ms->game);
	if(ms->mlx != NULL)
		mlx_close_window(ms->mlx);
	if(ms->tex != NULL)
		free(ms->tex);
	if(ms->paths != NULL)
		ft_free_tab_char(ms->paths);
	if(ms != NULL)
		free(ms);
}


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
	if(ms->map_args != NULL)
		ft_free_tab_char(ms->map_args);
	if(ms->game != NULL)
		free(ms->game);
	if(ms != NULL)
		free(ms);
}

void	map_error_exit(t_ms *ms)
{
	free_exit(ms);
	printf("\nFree from here\n");
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

// void free_exit(t_ms *ms){
// 	printf("ms: %p\n", ms);

// 	printf("ms->map: %p\n", ms->map);
// 	printf("ms->main_map:%p\n", ms->main_map);
// 	printf("ms->map_args: %p\n", ms->map_args);
// 	printf("ms->game: %p\n", ms->game);
// 	printf("ms->mlx: %p\n", ms->mlx);
// 	printf("ms->tex: %p\n", ms->tex);
// 	printf("ms->paths: %p\n", ms->paths);
// 	// if(ms->map != NUL
// 	if(ms->main_map != NULL)
// 		ft_free_tab_char(ms->main_map);
// 	if(ms->map_args != NULL)
// 		ft_free_tab_char(ms->map_args);
// 	if(ms->game != NULL)
// 		free(ms->game);
// 	if(ms->mlx != NULL)
// 		mlx_close_window(ms->mlx);
// 	if(ms->tex != NULL)
// 		free(ms->tex);
// 	if(ms->paths != NULL)
// 		ft_free_tab_char(ms->paths);
// 	if(ms != NULL)
// 		free(ms);
// 	printf("\nms: %p\n", ms);
// 	printf("ms->map: %p\n", ms->map);
// 	printf("ms->main_map:%p\n", ms->main_map);
// 	printf("ms->map_args: %p\n", ms->map_args);
// 	printf("ms->game: %p\n", ms->game);
// 	printf("ms->mlx: %p\n", ms->mlx);
// 	printf("ms->tex: %p\n", ms->tex);
// 	printf("ms->paths: %p\n", ms->paths);
// }

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
	free_exit(ms);
	printf("Exit\n");
	return(0);
}
