#include "../includes/cub3d.h"

# define MOVE_SPEED 0.025
# define ROTATE_SPEED 0.02

//dir NORTH
	// ms->game->pl_dir.x = -1;
	// ms->game->plane.y = 0.66;
//dir SOUTH
	// ms->game->pl_dir.x = 1;
	// ms->game->plane.y = -0.66;
//dir WEST
	// ms->game->pl_dir.x = -1;
	// ms->game->plane.y = -0.66;
//dir EAST
	// ms->game->pl_dir.x = 1;
	// ms->game->plane.y = 0.66;

int map[10][10] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,1,0,1},
		{1,0,0,0,0,0,1,1,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}};

void	init_game(t_ms *ms)
{
	ms->game->pl_pos.x = 2;
	ms->game->pl_pos.y = 7;

	//dir SOUTH
	ms->game->pl_dir.x = 1;
	ms->game->pl_dir.y = 0;
	ms->game->plane.y = -0.66;
	ms->game->plane.x = 0;

	ms->game->cam_x = 0;
	ms->game->side_dist.x = 0;
	ms->game->side_dist.y = 0;
	ms->game->delta_dist.x = 0;
	ms->game->delta_dist.y = 0;
	ms->game->step.x = 1;
	ms->game->step.y = 1;
}

void	set_ray_dir(t_ms *ms)
{
	ms->game->ray_dir.x = ms->game->pl_dir.x + ms->game->plane.x * ms->game->cam_x;
	ms->game->ray_dir.y = ms->game->pl_dir.y + ms->game->plane.y * ms->game->cam_x;
}

void	set_map_pos(t_ms *ms)
{
	ms->game->coord.x = ms->game->pl_pos.x;
	ms->game->coord.y = ms->game->pl_pos.y;
	// ms->game->coord.x = (int)ms->game->pl_pos.x;
	// ms->game->coord.y = (int)ms->game->pl_pos.y;
}

void	set_delta_dist(t_ms *ms)
{
	ms->game->delta_dist.x = fabs(1 / ms->game->ray_dir.x);
	ms->game->delta_dist.y = fabs(1 / ms->game->ray_dir.y);
}

void	set_side_dist(t_ms *ms)
{
	if(ms->game->ray_dir.x < 0)
	{
		ms->game->step.x = -1;
		ms->game->side_dist.x = (ms->game->pl_pos.x - ms->game->coord.x) * ms->game->delta_dist.x;
	}
	else
	{
		ms->game->step.x = 1;
		ms->game->side_dist.x = (ms->game->coord.x + 1.0 - ms->game->pl_pos.x) * ms->game->delta_dist.x;
	}
	if(ms->game->ray_dir.y < 0)
	{
		ms->game->step.y = -1;
		ms->game->side_dist.y = (ms->game->pl_pos.y - ms->game->coord.y) * ms->game->delta_dist.y;
	}
	else
	{
		ms->game->step.y = 1;
		ms->game->side_dist.y = (ms->game->coord.y + 1.0 - ms->game->pl_pos.y) * ms->game->delta_dist.y;
	}
}

void	dda(t_ms *ms)
{
	while(1)
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
		if(map[(int)ms->game->coord.x][(int)ms->game->coord.y])
			break;
	}
	if(ms->game->side == 0)
		ms->game->perp_wall_dist = (ms->game->side_dist.x - ms->game->delta_dist.x);
	else
		ms->game->perp_wall_dist = (ms->game->side_dist.y - ms->game->delta_dist.y);
}

void	set_draw_range(t_ms *ms)
{
	ms->game->line_height = (int)(HEIGHT / ms->game->perp_wall_dist);
	ms->game->draw_start = -ms->game->line_height * 0.5 + HEIGHT * 0.5;
	// ms->game->draw_start = -ms->game->line_height / 2 + HEIGHT / 2;
	if (ms->game->draw_start < 0)
		ms->game->draw_start = 0;
	ms->game->draw_end = ms->game->line_height * 0.5 + HEIGHT * 0.5;
	// ms->game->draw_end = ms->game->line_height / 2 + HEIGHT / 2;
	if ( ms->game->draw_end >= HEIGHT)
		ms->game->draw_end = HEIGHT - 1;
}

void	calculate_texture(t_ms *ms)
{
	if (ms->game->side == 0)
		ms->game->wall_x = ms->game->pl_pos.y + ms->game->perp_wall_dist * ms->game->ray_dir.y;
	else
		ms->game->wall_x = ms->game->pl_pos.x + ms->game->perp_wall_dist * ms->game->ray_dir.x;
	
	// ms->game->wall_x -= floor(ms->game->wall_x); //TODO implement this

	ms->game->wall_texture_x = (int)(ms->game->wall_x * (double)TEXTURE_W);
	if (ms->game->side == 0 && ms->game->ray_dir.x > 0)
		ms->game->wall_texture_x = TEXTURE_W - ms->game->wall_texture_x - 1;
	if (ms->game->side == 1 && ms->game->ray_dir.y < 0)
		ms->game->wall_texture_x = TEXTURE_W - ms->game->wall_texture_x - 1;
	ms->game->step_texture = 1.0 * TEXTURE_H / ms->game->line_height;
	ms->game->texture_pos = (ms->game->draw_start - HEIGHT / 2 + ms->game->line_height / 2) * ms->game->step_texture;
}

void	draw_vertline(t_ms *ms, u_int32_t x)
{
	u_int32_t	y;
	
	y = 0;
	while((int)y < ms->game->draw_start)
	{
		mlx_put_pixel(ms->m_img, x, y, get_rgba(0,0,0,255)); //ceiling color (Black)
		y++;
	}
	while((int)y < ms->game->draw_end)
	{
		mlx_put_pixel(ms->m_img, x, y, get_rgba(255,0,0,255)); // red
		y++;
	}
	while((int)y < HEIGHT)
	{
		mlx_put_pixel(ms->m_img, x, y, get_rgba(255,255,255,255)); //floor color (white)
		y++;
	}

}

void	put_buffer_to_img(t_ms *ms)
{
	int x;
	int y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			mlx_put_pixel(ms->m_img, x, y, get_rgba(255,255,255,255));
			y++;
		}
		x++;
	}
}

void	loop(void *param)
{
	(void)param;
	t_ms		*ms;
	int	x;

	ms = get_ms();
	x = 0;
	// printf("enter while\n");
	while(x < WIDTH)
	{
		ms->game->cam_x = 2 * x / (double)WIDTH - 1;
		set_ray_dir(ms);
		// printf("\nprint in while");
		// print_init(ms);
		set_map_pos(ms);
		set_delta_dist(ms);
		set_side_dist(ms);
		dda(ms);
		set_draw_range(ms);
		draw_vertline(ms, x);
		// calculate_texture(ms); // TODO TBD if necessary

		x++;
		if (mlx_is_key_down(ms->mlx, MLX_KEY_ESCAPE))
			mlx_close_window(ms->mlx);
		// if (mlx_is_key_down(ms->mlx, MLX_KEY_W))
		// {
		// 	if(map[(int)(ms->game->pl_pos.x + ms->game->pl_dir.x * MOVE_SPEED)][(int)ms->game->pl_pos.y] == 0)
		// 		ms->game->pl_pos.x += ms->game->pl_dir.x * MOVE_SPEED;
		// 	if (map[(int)ms->game->pl_pos.x][(int)(ms->game->pl_pos.y + ms->game->pl_dir.y * MOVE_SPEED)] == 0)
		// 		ms->game->pl_pos.y += ms->game->pl_dir.y * MOVE_SPEED;
		// }
		// if (mlx_is_key_down(ms->mlx, MLX_KEY_S))
		// {
		// 	if(map[(int)(ms->game->pl_pos.x - ms->game->pl_dir.x * MOVE_SPEED)][(int)ms->game->pl_pos.y] == 0)
		// 		ms->game->pl_pos.x += ms->game->pl_dir.x * MOVE_SPEED;
		// 	if (map[(int)ms->game->pl_pos.x][(int)(ms->game->pl_pos.y - ms->game->pl_dir.y * MOVE_SPEED)] == 0)
		// 		ms->game->pl_pos.y += ms->game->pl_dir.y * MOVE_SPEED;
		// }
		if (mlx_is_key_down(ms->mlx, MLX_KEY_RIGHT))
		{
			double old_dir_x;
			double old_plane_x;
			old_dir_x = ms->game->pl_dir.x;
			ms->game->pl_dir.x = ms->game->pl_dir.x * cos(-ROTATE_SPEED) - ms->game->pl_dir.y * sin(-ROTATE_SPEED);
			ms->game->pl_dir.y = old_dir_x * sin(-ROTATE_SPEED) + ms->game->pl_dir.y * cos(-ROTATE_SPEED);
			old_plane_x = ms->game->plane.x;
			ms->game->plane.x = ms->game->plane.x * cos(-ROTATE_SPEED) - ms->game->plane.y * sin(-ROTATE_SPEED);
			ms->game->plane.y = old_plane_x * sin(-ROTATE_SPEED) + ms->game->plane.y * cos(-ROTATE_SPEED);
		}
		if (mlx_is_key_down(ms->mlx, MLX_KEY_LEFT))
		{
			double old_dir_x;
			double old_plane_x;
			old_dir_x = ms->game->pl_dir.x;
			ms->game->pl_dir.x = ms->game->pl_dir.x * cos(ROTATE_SPEED) - ms->game->pl_dir.y * sin(ROTATE_SPEED);
			ms->game->pl_dir.y = old_dir_x * sin(ROTATE_SPEED) + ms->game->pl_dir.y * cos(ROTATE_SPEED);
			old_plane_x = ms->game->plane.x;
			ms->game->plane.x = ms->game->plane.x * cos(ROTATE_SPEED) - ms->game->plane.y * sin(ROTATE_SPEED);
			ms->game->plane.y = old_plane_x * sin(ROTATE_SPEED) + ms->game->plane.y * cos(ROTATE_SPEED);
		}
	}
}