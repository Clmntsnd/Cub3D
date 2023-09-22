#include "../includes/cub3d.h"

void	loop(void *param)
{
	(void)param;
	t_ms	*ms;
	int		x;
	double	ray_dirX;
	double	ray_dirY;
	int		mapX;
	int		mapY;
	double	side_distX;
	double	side_distY;
	double	delta_distX;
	double	delta_distY;
	int		stepX;
	int		stepY;
	double	perpWalldist;
	int		hit;
	int		side;

	ms = get_ms();
	x = 0;
	printf("enter while\n");
	while(x < ms->width)
	{
		ms->player->camX = 2 * x / (double)(ms->width - 1);
		ray_dirX = ms->player->dirX + ms->player->planeX * ms->player->camX;
		ray_dirY = ms->player->dirY + ms->player->planeY * ms->player->camX;
		mapX = (int)ms->player->posX;
		mapY = (int)ms->player->posY;
		
		printf("ms->width = %d\n", ms->width);
		printf("ms->player->camX = %f\n", ms->player->camX);
		printf("ray_dirX = %f\n", ray_dirX);
		printf("ray_dirY = %f\n", ray_dirY);


		if (ray_dirX == 0) {
			delta_distX = INT_MAX;  // Assign a very large value
		} else {
			delta_distX = fabs(1 / ray_dirX);
		}

		// Check for ray_dirY to prevent division by zero and assign delta_distY
		if (ray_dirY == 0) {
			delta_distY = INT_MAX;  // Assign a very large value
		} else {
			delta_distY = fabs(1 / ray_dirY);
		}

		if(ray_dirX < 0)
		{
			stepX = -1;
			side_distX = (ms->player->posX - mapX) * delta_distX;
		}
		else
		{
			stepX = 1;
			side_distX = (mapX + 1.0 - ms->player->posX) * delta_distX;
		}
		if(ray_dirY < 0)
		{
			stepY = -1;
			side_distY = (ms->player->posY - mapY) * delta_distY;
		}
		else
		{
			stepY = 1;
			side_distY = (mapY + 1.0 - ms->player->posY) * delta_distY;
		}

		//perform DDA
		while (hit == 0)
		{
	        //jump to next map square, either in x-direction, or in y-direction
			if (side_distX < side_distY)
			{
				side_distX += delta_distX;
				mapY += stepX;
				side = 0;
			}
			else
			{
				side_distY += delta_distY;
				mapY += stepY;
				side = 1;
			}
			// if(ms->map[mapY][mapX] == "1")
			if(ms->map[mapY][mapX] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWalldist = side_distX - delta_distX;
		else
			perpWalldist = side_distY - delta_distY;

		int	line_height;

        //jump to next map square, either in x-direction, or in y-direction
		line_height = (int)(ms->height / perpWalldist);

		int draw_start;
		draw_start = -line_height * 0.5 + ms->height * 0.5;
		int draw_end;
		draw_end = line_height * 0.5 + ms->height * 0.5;

		if (draw_start < 0)
			draw_start = 0;
		if(draw_end >= ms->height)
			draw_end = ms->height - 1;

		u_int32_t color;
		if (ms->map[mapY][mapX] == '1')
			color = get_rgba(255,0,0,255);
      	if(side == 1)
			color = color * 0.5;


		int k = draw_start;
		
		while(k <= draw_end)
		{
    		mlx_put_pixel(ms->m_img, x, k, color);
		 	k++;
		}	
		x++;
		if (mlx_is_key_down(ms->mlx, MLX_KEY_ESCAPE))
			mlx_close_window(ms->mlx);
	}
}