/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:51:02 by jpilotte          #+#    #+#             */
/*   Updated: 2023/10/17 13:51:05 by jpilotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_minimap *get_minimap(void)
{
	static t_minimap *minimap = NULL;

	if (minimap == NULL)
		minimap = ft_calloc(1, sizeof(t_minimap));
	return (minimap);
}

void	put_pixel_to_map2D(t_minimap *minimap, int i, int j, uint32_t color)
{
	int	x;
	int	y;
	
	minimap->tile = minimap->tile_s + minimap->tile_b;
	x = -1;
	while (++x < minimap->tile_s)
	{
		y = -1;
		while(++y < minimap->tile_s)
			mlx_put_pixel(minimap->map_img, j * minimap->tile + x, i * minimap->tile + y, color);
	}
}

void	put_color_to_tile(t_ms *ms, t_minimap *minimap)
{
	int 		i;
	int			j;

	i = -1;
	while (ms->main_map[++i])
	{
		j = -1;
		while (ms->main_map[i][++j])
		{
			if(ms->main_map[i][j] == '1')
				minimap->color = get_rgba(255,255,255,255);
			else if(ms->main_map[i][j] == '0')
				minimap->color = get_rgba(0,0,0,255);
			else if(ms->main_map[i][j] == 'N' || ms->main_map[i][j] == 'S' || ms->main_map[i][j] == 'W' || ms->main_map[i][j] == 'E')
			{
				minimap->color = get_rgba(0,0,0,255);
				minimap->pl_x = j;
				minimap->pl_y = i;
			}
			else
				continue;
			put_pixel_to_map2D(minimap, i, j, minimap->color);
		}
	}
}

void	draw_map2D(void *param)
{
	(void)param;
	t_ms		*ms;
	t_minimap	*minimap;

	ms = get_ms();
	minimap = get_minimap();
	minimap->tile_s = 24;
	minimap->tile_b = 0;
	if(!(minimap->map_img = mlx_new_image(ms->mlx, 512, 384)))
	{
		mlx_close_window(ms->mlx);
		puts(mlx_strerror(mlx_errno));
		return ;
	}
    put_color_to_tile(ms, minimap);
}