#include "../includes/cub3d.h"

int32_t get_rgba(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	set_data(t_ms *ms)
{
	ms->game->ray_dir.x = ms->game->pl_dir.x + \
		ms->game->plane.x * ms->game->cam_x;
	ms->game->ray_dir.y = ms->game->pl_dir.y + \
		ms->game->plane.y * ms->game->cam_x;
	ms->game->coord.x = (int)ms->game->pl_pos.x;
	ms->game->coord.y = (int)ms->game->pl_pos.y;
	ms->game->delta_dist.x = fabs(1 / ms->game->ray_dir.x);
	ms->game->delta_dist.y = fabs(1 / ms->game->ray_dir.y);
}

void	set_side_dist(t_ms *ms)
{
	if(ms->game->ray_dir.x < 0)
	{
		ms->game->step.x = -1;
		ms->game->side_dist.x = (ms->game->pl_pos.x - \
			ms->game->coord.x) * ms->game->delta_dist.x;
	}
	else
	{
		ms->game->step.x = 1;
		ms->game->side_dist.x = (ms->game->coord.x + 1.0 - \
			ms->game->pl_pos.x) * ms->game->delta_dist.x;
	}
	if(ms->game->ray_dir.y < 0)
	{
		ms->game->step.y = -1;
		ms->game->side_dist.y = (ms->game->pl_pos.y - \
			ms->game->coord.y) * ms->game->delta_dist.y;
	}
	else
	{
		ms->game->step.y = 1;
		ms->game->side_dist.y = (ms->game->coord.y + 1.0 - \
			ms->game->pl_pos.y) * ms->game->delta_dist.y;
	}
}

void	dda(t_ms *ms)
{
	bool	hit;

	hit = false;
	while(!hit)
	{
		if(ms->game->side_dist.x < ms->game->side_dist.y)
		{
			ms->game->side_dist.x += ms->game->delta_dist.x;
			ms->game->coord.x += ms->game->step.x;
			if (ms->game->ray_dir.x > 0)
				ms->game->side = 0; 
			else
				ms->game->side = 1;
		}
		else
		{
			ms->game->side_dist.y += ms->game->delta_dist.y;
			ms->game->coord.y += ms->game->step.y;
			if (ms->game->ray_dir.y > 0)
				ms->game->side = 2;
			else
				ms->game->side = 3;
		}
		if(ms->main_map[(int)ms->game->coord.x][(int)ms->game->coord.y] == '1')
			hit = true;
	}
	if(ms->game->side < 2)
		ms->game->perp_wall_dist = (ms->game->side_dist.x - ms->game->delta_dist.x);
	else
		ms->game->perp_wall_dist = (ms->game->side_dist.y - ms->game->delta_dist.y);
}

void	set_draw_range(t_ms *ms)
{
	ms->game->line_height = (int)(HEIGHT / ms->game->perp_wall_dist);
	ms->game->draw_start = -ms->game->line_height * 0.5 + HEIGHT * 0.5;
	if (ms->game->draw_start < 0)
		ms->game->draw_start = 0;
	ms->game->draw_end = ms->game->line_height * 0.5 + HEIGHT * 0.5;
	if (ms->game->draw_end >= HEIGHT)
		ms->game->draw_end = HEIGHT - 1;
}

void	find_texture_hit(t_ms *ms, xpm_t *texture)
{
	double	hit;

	hit = 0;
	if (ms->game->side == 0 || ms->game->side == 1) 
		hit = ms->game->pl_pos.y + ms->game->perp_wall_dist * ms->game->ray_dir.y;
	else
		hit = ms->game->pl_pos.x + ms->game->perp_wall_dist * ms->game->ray_dir.x;
	hit -= (int)hit;
	ms->game->tex_x = (int)(hit * (double)texture->texture.width);
	if ((ms->game->side == 0 || ms->game->side == 1) && ms->game->ray_dir.x > 0)
		ms->game->tex_x = texture->texture.width - ms->game->tex_x - 1;
	if ((ms->game->side == 2 || ms->game->side == 3) && ms->game->ray_dir.y < 0)
		ms->game->tex_x = texture->texture.width - ms->game->tex_x - 1;
}

int **fill_texture(xpm_t *texture)
{
	int	**array;
	int	i;
	int	j;

	array = ft_calloc(sizeof(int *), texture->texture.height + 1);
	i = 3;
	while(++i < (int) texture->texture.height + 4)
	{
		j = 3;
		array[i - 4] = ft_calloc(texture->texture.width, sizeof(int));
		while (++j < (int) texture->texture.width + 4)
		{
			array[i - 4][j - 4] = get_rgba(
				texture->texture.pixels[(texture->texture.width * 4 * (i - 4)) + (4 * (j - 4)) + 0],
				texture->texture.pixels[(texture->texture.width * 4 * (i - 4)) + (4 * (j - 4)) + 1],
				texture->texture.pixels[(texture->texture.width * 4 * (i - 4)) + (4 * (j - 4)) + 2],
				texture->texture.pixels[(texture->texture.width * 4 * (i - 4)) + (4 * (j - 4)) + 3]);
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
	pos = ((double)ms->game->draw_start - (double)HEIGHT * 0.5 + (double)ms->game->line_height * 0.5) * dist;
	if (pos < 0)
		pos = 0;
	j = 0;
	while (j < ms->game->draw_start)
		mlx_put_pixel(ms->m_img, x, j++, ms->game->ceiling);
	while(j < ms->game->draw_end)
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

void	loop(void *param)
{
	(void)param;
	t_ms		*ms;
	t_minimap	*minimap;
	int			x;

	ms = get_ms();
	minimap = get_minimap();
	x = -1;
	while(++x < WIDTH)
	{
		ms->game->cam_x = 2 * x / (double)WIDTH - 1;
		set_data(ms);
		set_side_dist(ms);
		dda(ms);
		set_draw_range(ms);
		pick_texture(ms, x);
		key_binding(ms);
		move_cursor(ms);
	}
	// if (!ms->game->minimap_activ)
	// 	return ;
	// if(mlx_image_to_window(ms->mlx, minimap->map_img, 0, 0) == -1)
	// {
	// 	mlx_close_window(ms->mlx);
	// 	puts(mlx_strerror(mlx_errno)); //To modify, can't use "puts"
	// 	return ;
	// }
}
