/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:50:02 by jpilotte          #+#    #+#             */
/*   Updated: 2023/10/17 17:12:40 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	find_texture_hit(t_ms *ms, xpm_t *texture)
{
	double	hit;

	hit = 0;
	if (ms->game->side == 0 || ms->game->side == 1)
		hit = ms->game->pl_pos.y + ms->game->perp_wall_dist \
			* ms->game->ray_dir.y;
	else
		hit = ms->game->pl_pos.x + ms->game->perp_wall_dist \
			* ms->game->ray_dir.x;
	hit -= (int)hit;
	ms->game->tex_x = (int)(hit * (double)texture->texture.width);
	if ((ms->game->side == 0 || ms->game->side == 1) && ms->game->ray_dir.x > 0)
		ms->game->tex_x = texture->texture.width - ms->game->tex_x - 1;
	if ((ms->game->side == 2 || ms->game->side == 3) && ms->game->ray_dir.y < 0)
		ms->game->tex_x = texture->texture.width - ms->game->tex_x - 1;
}

int	**convert_texture(xpm_t *texture)
{
	int	**array;
	int	i;
	int	j;

	array = ft_calloc(sizeof(int *), texture->texture.height + 1);
	i = 3;
	while (++i < (int) texture->texture.height + 4)
	{
		j = 3;
		array[i - 4] = ft_calloc(texture->texture.width, sizeof(int));
		while (++j < (int) texture->texture.width + 4)
		{
			array[i - 4][j - 4] = get_rgba(
					texture->texture.pixels[(texture->texture.width * 4 \
						* (i - 4)) + (4 * (j - 4)) + 0],
					texture->texture.pixels[(texture->texture.width * 4 \
						* (i - 4)) + (4 * (j - 4)) + 1],
					texture->texture.pixels[(texture->texture.width * 4 \
						* (i - 4)) + (4 * (j - 4)) + 2],
					texture->texture.pixels[(texture->texture.width * 4 \
					* (i - 4)) + (4 * (j - 4)) + 3]);
		}
	}
	return (array);
}

void	draw_vert_pix(t_ms *ms, int x, xpm_t *wall_text, int **array)
{
	double	dist;
	double	pos;
	int		tex_y;
	int		j;

	dist = 1.0 * wall_text->texture.height / ms->game->line_height;
	pos = ((double)ms->game->draw_start - (double)HEIGHT * 0.5 + \
			(double)ms->game->line_height * 0.5) * dist;
	if (pos < 0)
		pos = 0;
	j = 0;
	while (j < ms->game->draw_start)
		mlx_put_pixel(ms->m_img, x, j++, ms->game->ceiling);
	while (j < ms->game->draw_end)
	{
		tex_y = (int)pos;
		if (pos > wall_text->texture.height - 1)
			pos = wall_text->texture.height - 1;
		pos += dist;
		mlx_put_pixel(ms->m_img, x, j++, array[tex_y][ms->game->tex_x]);
	}
	while ((int)j < HEIGHT)
		mlx_put_pixel(ms->m_img, x, j++, ms->game->floor);
}

void	pick_texture(t_ms *ms, int x)
{
	if (ms->game->side == 0)
	{
		find_texture_hit(ms, ms->tex->so_tex);
		draw_vert_pix(ms, x, ms->tex->so_tex, ms->tex->so);
	}
	if (ms->game->side == 1)
	{
		find_texture_hit(ms, ms->tex->no_tex);
		draw_vert_pix(ms, x, ms->tex->no_tex, ms->tex->no);
	}
	if (ms->game->side == 2)
	{
		find_texture_hit(ms, ms->tex->ea_tex);
		draw_vert_pix(ms, x, ms->tex->ea_tex, ms->tex->ea);
	}
	if (ms->game->side == 3)
	{
		find_texture_hit(ms, ms->tex->we_tex);
		draw_vert_pix(ms, x, ms->tex->we_tex, ms->tex->we);
	}
}
