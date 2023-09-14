#include "../includes/cub3d.h"

t_minimap *get_minimap(void)
{
	static t_minimap *minimap = NULL;

	if (minimap == NULL)
		minimap = ft_calloc(1, sizeof(t_minimap));
	return (minimap);
}

int32_t get_rgba(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

/*
**	Put pixel on an image per their 
**	tile color in the map
*/
void	put_pixel_to_map2D(t_minimap *minimap, int i, int j, uint32_t color)
{
	int	x;
	int	y;
	
	minimap->tile = minimap->tile_s + minimap->tile_b;
	x = -1;
	while (++x < minimap->tile_s)
	{
		y = -1;
		while(++y < minimap->tile_s)
			mlx_put_pixel(minimap->map_img, j * minimap->tile + x, i * minimap->tile + y, color);
	}
}

void	put_color_to_tile(t_data *data, t_minimap *minimap)
{
	int 		i;
	int			j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if(data->map[i][j] == '1')
				minimap->color = get_rgba(255,255,255,255); //assign white to char 1
			else if(data->map[i][j] == '0')
				minimap->color = get_rgba(0,0,0,255); //assign black to char 0
			else if(data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				minimap->color = get_rgba(0,0,0,255); //assign red to char N
				data->pl_x = j;
				data->pl_y = i;
			}
			else
				continue; //skip char other than 1, 0 and N (e.g. "\n")
			put_pixel_to_map2D(minimap, i, j, minimap->color);
		}
	}
}

/* 
**	Draw a minimap of the map passed as an arg
*/
int	draw_map2D(t_data *data)
{
	t_minimap	*minimap;

	minimap = get_minimap();
	minimap->tile_s = 48; //tile_size : Change this size to be in function of a certain ratio
	minimap->tile_b = 1; //tile_border: 1 pixel
	if(!(minimap->map_img = mlx_new_image(data->mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno)); //To modify, can't use "puts"
		return(EXIT_FAILURE);
	}
    put_color_to_tile(data, minimap);
	if(mlx_image_to_window(data->mlx, minimap->map_img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno)); //To modify, can't use "puts"
		return(EXIT_FAILURE);
	}
	return (0);
}