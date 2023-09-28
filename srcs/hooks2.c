#include "../includes/cub3d.h"

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
			ms->game->side = 0;
		}
		else
		{
			ms->game->side_dist.y += ms->game->delta_dist.y;
			ms->game->coord.y += ms->game->step.y;
			ms->game->side = 1;
		}
		if(ms->main_map[(int)ms->game->coord.x][(int)ms->game->coord.y] == '1')
			hit = true;
	}
	if(ms->game->side == 0)
		ms->game->perp_wall_dist = (ms->game->side_dist.x - ms->game->delta_dist.x);
	else
		ms->game->perp_wall_dist = (ms->game->side_dist.y - ms->game->delta_dist.y);
}

void	set_draw_range(t_ms *ms)
{
	ms->game->line_height = (int)((HEIGHT * 125) / ms->game->perp_wall_dist);
	ms->game->draw_start = -ms->game->line_height * 0.5 + HEIGHT * 0.5;
	if (ms->game->draw_start < 0)
		ms->game->draw_start = 0;
	ms->game->draw_end = ms->game->line_height * 0.5 + HEIGHT * 0.5;
	if (ms->game->draw_end >= HEIGHT)
		ms->game->draw_end = HEIGHT - 1;
}

void	draw_vertline(t_ms *ms, u_int32_t x, u_int32_t color)
{
	u_int32_t	y;
	
	y = 0;
	while((int)y < ms->game->draw_start)
		mlx_put_pixel(ms->m_img, x, y++, ms->game->ceiling);
	while((int)y < ms->game->draw_end)
		mlx_put_pixel(ms->m_img, x, y++, color); // red
	while((int)y < HEIGHT)
		mlx_put_pixel(ms->m_img, x, y++, ms->game->floor);
}

u_int32_t	wall_color(t_ms *ms)
{
	if (ms->game->side == 1 && ms->game->ray_dir.y > 0)
		return (get_rgba(127,127,0,255));
	if (ms->game->side == 1 && ms->game->ray_dir.y < 0)
		return (get_rgba(0,127,127,255));
	if (ms->game->side == 0 && ms->game->ray_dir.x < 0)
		return (get_rgba(0,0,255,255));
	if (ms->game->side == 0 && ms->game->ray_dir.x > 0)
		return (get_rgba(128,0,128,255));
	return(0);
}

void	loop(void *param)
{
	(void)param;
	t_ms		*ms;
	int			x;
	u_int32_t	color;

	ms = get_ms();
	x = -1;
	while(++x < WIDTH)
	{
		ms->game->cam_x = 2 * x / (double)WIDTH - 1;
		set_data(ms);
		set_side_dist(ms);
		dda(ms);
		set_draw_range(ms);
		color = wall_color(ms);
		draw_vertline(ms, x, color);
		key_binding(ms);
		move_cursor(ms);
	}
}
