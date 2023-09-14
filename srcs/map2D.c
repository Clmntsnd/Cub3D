#include "../includes/cub3d.h"

#define TILE_SIZE 28
#define BORDER_SIZE 1

int32_t get_rgba(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void		draw_map2D(t_data *data)
{
    int 		i;
	int			j;
	int			x;
	int			y;
	uint32_t	color;
    
	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if(data->map[i][j] == '1')
				color = get_rgba(255,255,255,255); //white
			else if(data->map[i][j] == '0')
				color = get_rgba(0,0,0,255); //black
			else
				continue;
			x = -1;
			while (++x < TILE_SIZE)
			{
				y = -1;
				while(++y < TILE_SIZE)
					mlx_put_pixel(data->mini_map, j * (TILE_SIZE + BORDER_SIZE) + x, i * (TILE_SIZE + BORDER_SIZE) + y, color);
			}
		}
	}
}
