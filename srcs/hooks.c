#include "../includes/cub3d.h"

//TODO to rename, draw a red square to represent the player
void ft_player_and_ray(void* param)
{
	(void)param;
	t_minimap	*minimap;
	u_int32_t	i;
	u_int32_t	j;

	minimap = get_minimap();
	// Draw a red cube (here 20x20) that represents a player
	i = -1;
	while (++i < minimap->player_img->width) // width is 20
	{
		j = -1;
		while (++j < 20)
			mlx_put_pixel(minimap->player_img, i, j, get_rgba(250,0,0,255));
	}

	// i--; // used to start the ray at the edge of the box
	
	// while loop to print a line from the middle 
	// of the image (x axis) to the end of the image (y axis)
	// while (++i < minimap->player_img->height) 
	// 	mlx_put_pixel(minimap->player_img, minimap->player_img->width*0.5, i, get_rgba(0,250,0,255));
}

// Saved for now, doesn't req 
// uint32_t color = get_rgba(
// 	rand() % 0xFF, // R
// 	rand() % 0xFF, // G
// 	rand() % 0xFF, // B
// 	rand() % 0xFF  // A
// );

void	draw_pl(t_minimap *minimap)
{
	u_int32_t	i;
	u_int32_t	j;

	// Draw a red cube (here 20x20) that represents a player
	i = -1;
	while (++i < minimap->player_img->width) // width is 20
	{
		j = -1;
		while (++j < 20)
			mlx_put_pixel(minimap->player_img, i, j, get_rgba(250,0,0,255));
	}
}
void	cast_ray(t_minimap *minimap)
{
	// (void)param;
	// t_minimap *minimap;
	int	i;
	int	len;

	// minimap = get_minimap();
	
	minimap->ray.x = minimap->player_img->instances[0].x + minimap->pl_h * 0.5;
	minimap->ray.y = minimap->player_img->instances[0].y + minimap->pl_h * 0.5;
	// minimap->ray.x = minimap->pl_x + minimap->pl_h * 0.5;
	// minimap->ray.y = minimap->pl_y + minimap->pl_h * 0.5;
	
	i = 0;
	len = 50;
	while (++i < len)
	{
		mlx_put_pixel(minimap->map_img, minimap->ray.x, minimap->ray.y, get_rgba(0,250,0,255));
		minimap->ray.x += 0.5;
		minimap->ray.y += 0;
	}
	
}

void ft_hook(void* param)
{
	t_minimap	*minimap;
	t_data		*data;
	mlx_t* 		mlx = param;
	// int			mapX;
	// int			mapY;


	minimap = get_minimap();
	data = get_data();
	// mapX = minimap->pl_x / minimap->tile;
	// mapY = minimap->pl_y / minimap->tile;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		//WIP on directions
		// minimap->pl_dir += 0.1;
		// if(minimap->pl_dir < 0)
		// 	minimap->pl_dir += 2 * M_PI;
		// minimap->pl_dx = cos(minimap->pl_dir) * 5;
		// minimap->pl_dy = sin(minimap->pl_dir) * 5;
		// minimap->player_img->instances[0].x -= 2.5;
		// minimap->player_img->instances[0].x -= minimap->pl_dx;
		// minimap->player_img->instances[0].y -= minimap->pl_dy;
		// if (data->map[mapY][mapX] == '1')
		// 	minimap->pl_x -= 0;
		// else
		//	minimap->pl_x -= 2.5;
		minimap->player_img->instances[0].x -= 2.5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		//WIP on directions
		// minimap->pl_dir -= 0.1;
		// if(minimap->pl_dir > 2 * M_PI)
		// 	minimap->pl_dir -= 2 * M_PI;
		// minimap->pl_dx = cos(minimap->pl_dir) * 5;
		// minimap->pl_dy = sin(minimap->pl_dir) * 5;
		// minimap->player_img->instances[0].x += minimap->pl_dx;
		// minimap->player_img->instances[0].y += minimap->pl_dy;
		// minimap->ray_img->instances[0].x += 2.5;
		minimap->player_img->instances[0].x += 2.5;

	}
	if (mlx_is_key_down(mlx, MLX_KEY_UP)){
		// minimap->player_img->instances[0].x -= minimap->pl_dx;
		// minimap->player_img->instances[0].y -= minimap->pl_dy;
		minimap->player_img->instances[0].y -= 2.5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN)){
		// minimap->player_img->instances[0].x += minimap->pl_dx;
		// minimap->player_img->instances[0].y += minimap->pl_dy;
		minimap->player_img->instances[0].y += 2.5;
		// minimap->ray_img->instances[0].y += 2.5;
	}
	// cast_ray(minimap);
	// draw_map2D(data);
    put_color_to_tile(data, minimap);
	draw_pl(minimap);
	cast_ray(minimap);

}

void	print_player(void *param)
{
	(void)param;
	t_minimap	*minimap;

	minimap = get_minimap();
	printf("\npl_x:			%.4f\n", minimap->pl_x);
	printf("pl_y:			%.4f\n", minimap->pl_y);
	printf("pl_dx:			%.4f\n", minimap->pl_dx);
	printf("pl_dy:			%.4f\n", minimap->pl_dy);
	printf("pl_dir:			%.4f\n", minimap->pl_dir);

	printf("player_img_count:	%zu\n", minimap->player_img->count);
	printf("map_img_count:		%zu\n", minimap->map_img->count);
}
