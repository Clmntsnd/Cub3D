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
	ms->game->coord.x = ms->game->pl_pos.x;
	ms->game->coord.y = ms->game->pl_pos.y;
	ms->game->delta_dist.x = fabs(1 / ms->game->ray_dir.x);
	ms->game->delta_dist.y = fabs(1 / ms->game->ray_dir.y);
}

void	set_side_dist(t_ms *ms)
{
	if(ms->game->ray_dir.x < 0)
	{
		ms->game->step.x = -0.01;
		ms->game->side_dist.x = (ms->game->pl_pos.x - \
			ms->game->coord.x) * ms->game->delta_dist.x;
	}
	else
	{
		ms->game->step.x = 0.01;
		ms->game->side_dist.x = (ms->game->coord.x + 1.0 - \
			ms->game->pl_pos.x) * ms->game->delta_dist.x;
	}
	if(ms->game->ray_dir.y < 0)
	{
		ms->game->step.y = -0.01;
		ms->game->side_dist.y = (ms->game->pl_pos.y - \
			ms->game->coord.y) * ms->game->delta_dist.y;
	}
	else
	{
		ms->game->step.y = 0.01;
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
	ms->game->line_height = (int)((HEIGHT * 100) / ms->game->perp_wall_dist);
	ms->game->draw_start = -ms->game->line_height * 0.5 + HEIGHT * 0.5;
	if (ms->game->draw_start < 0)
		ms->game->draw_start = 0;
	ms->game->draw_end = ms->game->line_height * 0.5 + HEIGHT * 0.5;
	if (ms->game->draw_end >= HEIGHT)
		ms->game->draw_end = HEIGHT - 1;
}

void	draw_vert_line(t_ms *ms, u_int32_t x, u_int32_t color)
{
	u_int32_t	y;
	
	y = 0;
	while ((int)y < ms->game->draw_start)
		mlx_put_pixel(ms->m_img, x, y++, ms->game->ceiling);
	while ((int)y < ms->game->draw_end)
		mlx_put_pixel(ms->m_img, x, y++, color);
	while ((int)y < HEIGHT)
		mlx_put_pixel(ms->m_img, x, y++, ms->game->floor);
}

u_int32_t	wall_color(t_ms *ms)
{
	if (ms->game->side == 0) 
		return (get_rgba(128,128,255,255)); //south wall
	if (ms->game->side == 1)
		return (get_rgba(128,255,128,255)); //north wall
	if (ms->game->side == 2)
		return (get_rgba(255,128,128,255)); //east wall
	if (ms->game->side == 3)
		return (get_rgba(128,0,128,255)); //west wall
	return(0);
}

// WIP
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
	if (ms->game->side == 0 && ms->game->ray_dir.x > 0)
		ms->game->tex_x = texture->texture.width - ms->game->ray_dir.x;
	// if ((ms->game->side == 2 || ms->game->side == 3) && ms->game->ray_dir.y < 0)
	// 	ms->game->tex_x = texture->texture.width - ms->game->ray_dir.x - 1;
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

	dist = 10 * wall_text->texture.height / ms->game->line_height;
	pos = ((double)ms->game->draw_start - (double)HEIGHT * 0.5 + (double)ms->game->line_height * 0.5) * dist;
	if (pos < 0)
		pos = 0;
	j = ms->game->draw_start;
	while(++j < ms->game->draw_end)
	{
		tex_y = (int)pos;
		if (pos > wall_text->texture.height - 1)
			pos = wall_text->texture.height - 1;
		pos += dist;
		mlx_put_pixel(ms->m_img, x, j, array[ms->game->tex_x][tex_y]);
	}
}

void	pick_texture(t_ms *ms, int x)
{
	ms->tex = ft_calloc(1, sizeof(t_tex));
	
	//grab the texture from the path
	ms->tex->so_tex = mlx_load_xpm42("./assets/textures/test.xpm42");
	if (!ms->tex->so_tex)
		printf("pb texture\n");

	//populate the 2D array from the texture 
	ms->tex->so = fill_texture(ms->tex->so_tex);
	if (ms->game->side == 0)
	{
		find_texture_hit(ms, ms->tex->so_tex);
		draw_vert_pix(ms, x, ms->tex->so_tex, ms->tex->so);
	}
}
// WIP

void	loop(void *param)
{
	(void)param;
	t_ms		*ms;
	int			x;
	// u_int32_t	color;

	ms = get_ms();
	x = -1;
	while(++x < WIDTH)
	{
		ms->game->cam_x = 2 * x / (double)WIDTH - 1;
		set_data(ms);
		set_side_dist(ms);
		dda(ms);
		set_draw_range(ms);
		// color = wall_color(ms);
		// draw_vert_line(ms, x, color);

		pick_texture(ms, x);
		key_binding(ms);
		// move_cursor(ms);
	}
}
