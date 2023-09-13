#include "../includes/cub3d.h"

mlx_image_t	*draw_map2D()
{
	static mlx_image_t	*map2D;
	int	x = -1; 
	int	y = -1;
	int mapX = 8;
	int mapY = 8;
	// int map_size = 64;
	uint32_t color;
	int map[]= {
		1,1,1,1,1,1,1,1,
		1,0,1,0,0,0,0,1,
		1,0,1,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,1,0,0,1,
		1,1,1,1,1,1,1,1,
	};

	while(++y < mapY)
	{
		while(++x < mapX)
		{
			if (map[y * mapX + x] == 1)
				color = ft_pixel(1,1,1,1);
			else
				color = ft_pixel(0,0,0,1);
		}
		mlx_put_pixel(map2D, x, y, color);
	}
	return (map2D);
}