#include "../includes/cub3d.h"

void	rotate_vector(double *x, double *y, double angle) 
{
	double old_x ;

	old_x = *x;
	*x = old_x * cos(angle) - *y * sin(angle);
	*y = old_x * sin(angle) + *y * cos(angle);
}

void	move_player(t_ms *ms, double move_speed) 
{
	double radius;
	double hit_box;

	radius = 0.3;
	if (move_speed < 0)
		radius = -0.3;
	hit_box = move_speed + radius;
    // Move along X direction
    if(ms->main_map[(int)(ms->game->pl_pos.x + ms->game->pl_dir.x * hit_box)][(int)ms->game->pl_pos.y] == '0')
        ms->game->pl_pos.x += ms->game->pl_dir.x * move_speed;
    
    // Move along Y direction
    if(ms->main_map[(int)ms->game->pl_pos.x][(int)(ms->game->pl_pos.y + ms->game->pl_dir.y * hit_box)] == '0')
        ms->game->pl_pos.y += ms->game->pl_dir.y * move_speed;
}

void strafe_player(t_ms *ms, double strafe_speed) 
{
	double radius;
	double hit_box;

	radius = 0.3;
	if (strafe_speed < 0)
		radius = -0.3;
	hit_box = strafe_speed + radius;
    // Strafe along X direction (perpendicular to direction of facing, so we use pl_dir.y)
    if(ms->main_map[(int)(ms->game->pl_pos.x + ms->game->pl_dir.y * hit_box)][(int)ms->game->pl_pos.y] == '0')
        ms->game->pl_pos.x += ms->game->pl_dir.y * strafe_speed;
    
    // Strafe along Y direction (perpendicular to direction of facing, so we use -pl_dir.x)
    if(ms->main_map[(int)ms->game->pl_pos.x][(int)(ms->game->pl_pos.y - ms->game->pl_dir.x * hit_box)] == '0')
        ms->game->pl_pos.y -= ms->game->pl_dir.x * strafe_speed;
}

void	key_binding(t_ms *ms)
{
	if (mlx_is_key_down(ms->mlx, MLX_KEY_ESCAPE))
			mlx_close_window(ms->mlx);

	if (mlx_is_key_down(ms->mlx, MLX_KEY_W)) 
		move_player(ms, MOVE_SPEED); // Move forward
	if (mlx_is_key_down(ms->mlx, MLX_KEY_S))
		move_player(ms, -MOVE_SPEED); // Move backward

	if (mlx_is_key_down(ms->mlx, MLX_KEY_A))
		strafe_player(ms, -MOVE_SPEED); // Strafe left
	if (mlx_is_key_down(ms->mlx, MLX_KEY_D))
		strafe_player(ms, MOVE_SPEED); // Strafe right

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
}
