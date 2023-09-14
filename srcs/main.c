#include "../includes/cub3d.h"

static mlx_image_t* image;

// -----------------------------------------------------------------------------
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 2;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 2;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 2;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 2;
}
// -----------------------------------------------------------------------------

int	main(int ac, char **av)
{
	t_data *data;

	data = get_data();

	if (!ft_parse_arg(ac, av))
		return(EXIT_FAILURE);
	init_content(data, av[1]);
	
	// Test MLX42
	// Gotta error check this stuff
	if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true)))
	{
		puts(mlx_strerror(mlx_errno)); //To modify, can't use "puts"
		return(EXIT_FAILURE);
	}
	draw_map2D(data);
	if (!(image = mlx_new_image(data->mlx, 30, 30)))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno)); //To modify, can't use "puts"
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(data->mlx, image, data->pl_x, data->pl_y) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno)); //To modify, can't use "puts"
		return(EXIT_FAILURE);
	}
	mlx_loop_hook(data->mlx, ft_randomize, data->mlx);
	mlx_loop_hook(data->mlx, ft_hook, data->mlx);

	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	// Test End

	return (0);
}
