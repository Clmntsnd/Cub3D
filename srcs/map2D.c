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
	
	x = -1;
	while (++x < minimap->tile_s)
	{
		y = -1;
		while(++y < minimap->tile_s)
			mlx_put_pixel(minimap->map_img, j * minimap->tile + x, i * minimap->tile + y, color);
	}
}

void	put_color_to_tile(t_ms *ms, t_minimap *minimap)
{
	int 		i;
	int			j;

	i = -1;
	while (ms->map[++i])
	{
		j = -1;
		while (ms->map[i][++j])
		{
			if(ms->map[i][j] == '1')
				minimap->color = get_rgba(255,255,255,255); //assign white to char 1
			else if(ms->map[i][j] == '0')
				minimap->color = get_rgba(0,0,0,255); //assign black to char 0
			else if(ms->map[i][j] == 'N' || ms->map[i][j] == 'S' || ms->map[i][j] == 'W' || ms->map[i][j] == 'E')
			{
				minimap->color = get_rgba(0,0,0,255); //assign red to char N
				minimap->pl_x = j * minimap->tile + (minimap->tile - minimap->pl_w) * 0.5;
				minimap->pl_y = i * minimap->tile + (minimap->tile - minimap->pl_w) * 0.5;
			}
			else
				continue; //skip char other than 1, 0 and N, S, W, E (e.g. "\n")
			put_pixel_to_map2D(minimap, i, j, minimap->color);
		}
	}
}

void	init_minimap(t_minimap *minimap)
{
	minimap->ray.x = 0;
	minimap->ray.y = 0;
	minimap->ray.hit_wall = false;
	minimap->pl_h = 20;
	minimap->pl_w = 20;
	minimap->pl_x = 0;
	minimap->pl_y = 0;
	minimap->pl_dir = 0; 
	minimap->pl_dx = cos(minimap->pl_dir) * 5;
	minimap->pl_dy = sin(minimap->pl_dir) * 5;
	minimap->tile_s = 62; //tile_size : Change this size to be in function of a certain ratio
	minimap->tile_b = 1; //tile_border: 1 pixel
	minimap->tile = minimap->tile_s + 2 * minimap->tile_b;
}

/* 
**	Draw a minimap of the map passed as an arg
*/
int	draw_map2D(t_ms *ms)
{
	t_minimap	*minimap;

	minimap = get_minimap();
	init_minimap(minimap);

	if(!(minimap->map_img = mlx_new_image(ms->mlx, WIDTH, HEIGHT)) 
		|| !(minimap->player_img = mlx_new_image(ms->mlx, minimap->pl_w, minimap->pl_h)))
			// || !(minimap->ray_img = mlx_new_image(ms->mlx, 10, 100)))
	{
		mlx_close_window(ms->mlx);
		puts(mlx_strerror(mlx_errno)); //To modify, can't use "puts"
		return(EXIT_FAILURE);
	}
    // put_color_to_tile(ms, minimap);
    // cast_ray();
	if(mlx_image_to_window(ms->mlx, minimap->map_img, 0, 0) == -1 
		|| mlx_image_to_window(ms->mlx, minimap->player_img, minimap->pl_x, minimap->pl_y) == -1)
			// || mlx_image_to_window(ms->mlx, minimap->ray_img, minimap->pl_x + minimap->pl_h*0.5, minimap->pl_y + minimap->pl_h*0.5) == -1)
	{
		mlx_close_window(ms->mlx);
		puts(mlx_strerror(mlx_errno)); //To modify, can't use "puts"
		return(EXIT_FAILURE);
	}
	return (0);
}
