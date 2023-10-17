/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_binding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:51:48 by jpilotte          #+#    #+#             */
/*   Updated: 2023/10/17 13:51:50 by jpilotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_vector(double *x, double *y, double angle)
{
	double	old_x ;

	old_x = *x;
	*x = old_x * cos(angle) - *y * sin(angle);
	*y = old_x * sin(angle) + *y * cos(angle);
}

void	move_player(t_ms *ms, double move_speed)
{
	double	radius;
	double	hit_box;

	radius = 0.4;
	if (move_speed < 0)
		radius = -0.4;
	hit_box = move_speed + radius;
	if (ms->main_map[(int)(ms->game->pl_pos.x + ms->game->pl_dir.x * hit_box)] \
		[(int)ms->game->pl_pos.y] == '0')
		ms->game->pl_pos.x += ms->game->pl_dir.x * move_speed;
	if (ms->main_map[(int)ms->game->pl_pos.x][(int)(ms->game->pl_pos.y + \
		ms->game->pl_dir.y * hit_box)] == '0')
		ms->game->pl_pos.y += ms->game->pl_dir.y * move_speed;
}

void	strafe_player(t_ms *ms, double strafe_speed)
{
	double	radius;
	double	hit_box;

	radius = 0.4;
	if (strafe_speed < 0)
		radius = -0.4;
	hit_box = strafe_speed + radius;
	if (ms->main_map[(int)(ms->game->pl_pos.x + ms->game->pl_dir.y * hit_box)] \
		[(int)ms->game->pl_pos.y] == '0')
		ms->game->pl_pos.x += ms->game->pl_dir.y * strafe_speed;
	if (ms->main_map[(int)ms->game->pl_pos.x][(int)(ms->game->pl_pos.y - \
		ms->game->pl_dir.x * hit_box)] == '0')
		ms->game->pl_pos.y -= ms->game->pl_dir.x * strafe_speed;
}

void	key_binding(t_ms *ms)
{
	if (mlx_is_key_down(ms->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(ms->mlx);
	if (mlx_is_key_down(ms->mlx, MLX_KEY_W))
		move_player(ms, MOVE_SPEED);
	if (mlx_is_key_down(ms->mlx, MLX_KEY_S))
		move_player(ms, -MOVE_SPEED);
	if (mlx_is_key_down(ms->mlx, MLX_KEY_A))
		strafe_player(ms, -MOVE_SPEED);
	if (mlx_is_key_down(ms->mlx, MLX_KEY_D))
		strafe_player(ms, MOVE_SPEED);
	if (mlx_is_key_down(ms->mlx, MLX_KEY_RIGHT))
	{
		rotate_vector(&ms->game->pl_dir.x, &ms->game->pl_dir.y, -ROTATE_SPEED);
		rotate_vector(&ms->game->plane.x, &ms->game->plane.y, -ROTATE_SPEED);
	}
	if (mlx_is_key_down(ms->mlx, MLX_KEY_LEFT))
	{
		rotate_vector(&ms->game->pl_dir.x, &ms->game->pl_dir.y, ROTATE_SPEED);
		rotate_vector(&ms->game->plane.x, &ms->game->plane.y, ROTATE_SPEED);
	}
	if (mlx_is_key_down(ms->mlx, MLX_KEY_C))
		ms->game->m_activ = true;
	if (mlx_is_key_down(ms->mlx, MLX_KEY_M))
		ms->game->minimap_activ = true;
}

void	move_cursor(t_ms *ms)
{
	int32_t	x;
	int32_t	y;

	x = 0;
	y = 0;
	if (!ms->game->m_activ)
		return ;
	mlx_get_mouse_pos(ms->mlx, &x, &y);
	mlx_set_cursor_mode(ms->mlx, MLX_MOUSE_HIDDEN);
	if (x > (double)(WIDTH * 0.5))
	{
		rotate_vector(&ms->game->pl_dir.x, &ms->game->pl_dir.y, \
			-ROTATE_SPEED * MOUSE_SPEED);
		rotate_vector(&ms->game->plane.x, &ms->game->plane.y, \
			-ROTATE_SPEED * MOUSE_SPEED);
		mlx_set_mouse_pos(ms->mlx, WIDTH * 0.5, HEIGHT * 0.5);
	}
	if (x < (double)(WIDTH * 0.5))
	{
		rotate_vector(&ms->game->pl_dir.x, &ms->game->pl_dir.y, \
			ROTATE_SPEED * MOUSE_SPEED);
		rotate_vector(&ms->game->plane.x, &ms->game->plane.y, \
			ROTATE_SPEED * MOUSE_SPEED);
		mlx_set_mouse_pos(ms->mlx, WIDTH * 0.5, HEIGHT * 0.5);
	}
}
