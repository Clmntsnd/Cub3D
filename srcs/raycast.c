/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:49:36 by jpilotte          #+#    #+#             */
/*   Updated: 2023/10/17 13:49:51 by jpilotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3d.h"

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
	if (ms->game->ray_dir.x < 0)
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
	if (ms->game->ray_dir.y < 0)
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
	while (1)
	{
		if (ms->game->side_dist.x < ms->game->side_dist.y)
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
		if (ms->main_map[(int)ms->game->coord.x][(int)ms->game->coord.y] == '1')
			break ;
	}
}

void	set_draw_range(t_ms *ms)
{
	if (ms->game->side < 2)
		ms->game->perp_wall_dist = (ms->game->side_dist.x \
			- ms->game->delta_dist.x);
	else
		ms->game->perp_wall_dist = (ms->game->side_dist.y \
			- ms->game->delta_dist.y);
	ms->game->line_height = (int)(HEIGHT / ms->game->perp_wall_dist);
	ms->game->draw_start = -ms->game->line_height * 0.5 + HEIGHT * 0.5;
	if (ms->game->draw_start < 0)
		ms->game->draw_start = 0;
	ms->game->draw_end = ms->game->line_height * 0.5 + HEIGHT * 0.5;
	if (ms->game->draw_end >= HEIGHT)
		ms->game->draw_end = HEIGHT - 1;
}

void	loop(void *param)
{
	t_ms		*ms;
	int			x;
	(void)param;
	ms = get_ms();
	x = -1;
	while (++x < WIDTH)
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
}
