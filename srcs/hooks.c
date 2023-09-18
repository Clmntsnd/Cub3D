#include "../includes/cub3d.h"

//TODO to rename, draw a red square to represent the player
void ft_randomize(void* param) 
{
	(void)param;
	t_minimap	*minimap;
	u_int32_t	i;
	u_int32_t	j;

	minimap = get_minimap();
	i = 0;
	while (++i < minimap->player_img->width)
	{
		j = 0;
		while (++j < minimap->player_img->height)
			mlx_put_pixel(minimap->player_img, i, j, get_rgba(250,0,0,255));
	}
}

// Saved for now, doesn't req 
// uint32_t color = get_rgba(
// 	rand() % 0xFF, // R
// 	rand() % 0xFF, // G
// 	rand() % 0xFF, // B
// 	rand() % 0xFF  // A
// );

void ft_hook(void* param)
{
	t_minimap	*minimap;
	mlx_t* mlx = param;

	minimap = get_minimap();
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP)){
		minimap->player_img->instances[0].y -= 2.5;
		minimap->ray_img->instances[0].y -= 2.5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN)){
		minimap->player_img->instances[0].y += 2.5;
		minimap->ray_img->instances[0].y += 2.5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		//WIP on directions
		// minimap->pl_dir -= 0.1;
		// if(minimap->pl_dir < 0)
		// 	minimap->pl_dir += 2 * M_PI;
		// minimap->pl_dx = cos(minimap->pl_dir);
		// minimap->pl_dy = sin(minimap->pl_dir);
		minimap->player_img->instances[0].x -= 2.5;
		minimap->ray_img->instances[0].x -= 2.5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		//WIP on directions
		// minimap->pl_dir -= 0.1;
		// if(minimap->pl_dir > 2 * M_PI)
		// 	minimap->pl_dir -= 2 * M_PI;
		// minimap->pl_dx = cos(minimap->pl_dir) * 5;
		// minimap->pl_dy = sin(minimap->pl_dir) * 5;
		minimap->player_img->instances[0].x += 2.5;
		minimap->ray_img->instances[0].x += 2.5;
	}
}

void	print_player(void *param)
{
	(void)param;
	t_minimap	*minimap;

	minimap = get_minimap();
	printf("\npl_x:	%.4f\n", minimap->pl_x);
	printf("pl_y:	%.4f\n", minimap->pl_y);
	printf("pl_dx:	%.4f\n", minimap->pl_dx);
	printf("pl_dy:	%.4f\n", minimap->pl_dy);
	printf("pl_dir:	%.4f\n", minimap->pl_dir);

}
