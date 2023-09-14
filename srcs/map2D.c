#include "../includes/cub3d.h"

int32_t get_rgba(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

/*
**	Put pixel on an image per their 
**	tile color in the map
*/
void	put_pixel_to_map2D(t_data *data, int i, int j, uint32_t color)
{
	int	x;
	int	y;
	int	tile;
	int	tile_s;
	int tile_b;

	tile_s = 28;
	tile_b = 1;
	tile = tile_s + tile_b;
	x = -1;
	while (++x < tile_s)
	{
		y = -1;
		while(++y < tile_s)
			mlx_put_pixel(data->mini_map, j * tile + x, i * tile + y, color);
	}
}

/*
**	Draw a minimap of the map passed as an arg
*/
void	draw_map2D(t_data *data)
{
    int 		i;
	int			j;
	uint32_t	color;
    
	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if(data->map[i][j] == '1')
				color = get_rgba(255,255,255,255); //assign white to char 1
			else if(data->map[i][j] == '0')
				color = get_rgba(0,0,0,255); //assign black to char 0
			else if(data->map[i][j] == 'N')
				color = get_rgba(255,0,0,255); //assign red to char N
			else
				continue; //skip char other than 1 and 0
			put_pixel_to_map2D(data, i, j, color);
		}
	}
}
