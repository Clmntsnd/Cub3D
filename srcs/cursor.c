#include "../includes/cub3d.h"

void	move_cursor(t_ms *ms)
{
	int32_t	x = WIDTH * 0.5;
	int32_t	y = HEIGHT * 0.5;

	mlx_get_mouse_pos(ms->mlx, &x, &y);
	mlx_set_cursor_mode(ms->mlx, MLX_MOUSE_HIDDEN);
	
	if (!ms->game->m_activ)
		return ;
	if(x > WIDTH / 2)
	{
		rotate_vector(&ms->game->pl_dir.x, &ms->game->pl_dir.y, -ROTATE_SPEED * MOUSE_SPEED);
		rotate_vector(&ms->game->plane.x, &ms->game->plane.y, -ROTATE_SPEED * MOUSE_SPEED);
	}
	if(x < WIDTH / 2)
	{
		rotate_vector(&ms->game->pl_dir.x, &ms->game->pl_dir.y, ROTATE_SPEED * MOUSE_SPEED);
		rotate_vector(&ms->game->plane.x, &ms->game->plane.y, ROTATE_SPEED * MOUSE_SPEED);
	}
	if (y < HEIGHT * 0.5 || y > HEIGHT * 0.5 || x < WIDTH * 0.5 || x > WIDTH * 0.5)
		mlx_set_mouse_pos(ms->mlx, WIDTH * 0.5, HEIGHT * 0.5);
}