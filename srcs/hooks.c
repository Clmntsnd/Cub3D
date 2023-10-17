/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:52:47 by jpilotte          #+#    #+#             */
/*   Updated: 2023/10/17 13:56:44 by jpilotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_player_and_ray(void *param)
{
	(void)param;
	t_minimap	*minimap;
	u_int32_t	i;
	u_int32_t	j;

	minimap = get_minimap();
	i = -1;
	while (++i < minimap->player_img->width)
	{
		j = -1;
		while (++j < 20)
			mlx_put_pixel(minimap->player_img, i, j, get_rgba(250,0,0,255));
	}
}

void	draw_pl(t_minimap *minimap)
{
	u_int32_t	i;
	u_int32_t	j;

	i = -1;
	while (++i < minimap->player_img->width)
	{
		j = -1;
		while (++j < 20)
			mlx_put_pixel(minimap->player_img, i, j, get_rgba(250,0,0,255));
	}
}

void	cast_ray(t_minimap *minimap)
{
	int	i;
	int	len;
	
	minimap->ray.x = minimap->player_img->instances[0].x + minimap->pl_h * 0.5;
	minimap->ray.y = minimap->player_img->instances[0].y + minimap->pl_h * 0.5;
	
	i = 0;
	len = 50;
	while (++i < len)
	{
		mlx_put_pixel(minimap->map_img, minimap->ray.x, minimap->ray.y, get_rgba(0,250,0,255));
		minimap->ray.x += 0.5;
		minimap->ray.y += 0;
	}
	
}

void	print_player(void *param)
{
	(void)param;
	t_minimap	*minimap;

	minimap = get_minimap();
	printf("\npl_x:			%.4f\n", minimap->pl_x);
	printf("pl_y:			%.4f\n", minimap->pl_y);
	printf("pl_dx:			%.4f\n", minimap->pl_dx);
	printf("pl_dy:			%.4f\n", minimap->pl_dy);
	printf("pl_dir:			%.4f\n", minimap->pl_dir);

	printf("player_img_count:	%zu\n", minimap->player_img->count);
	printf("map_img_count:		%zu\n", minimap->map_img->count);
}
