#include "../includes/cub3d.h"

#define WIDTH 512
#define HEIGHT 512

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
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}
// -----------------------------------------------------------------------------

bool	ft_parse_arg(int ac, char **av)
{
    char	*ext;
	int		len;

	ext = ft_strrchr(av[1], '.');
	len = ft_strlen(av[1]);
	if (ac != 2)
		return (printf("❌ Error\n%s\n%s\n", ERR_ARG, ERR_USG), false);
	if (len < 5)
		return (printf("❌ Error\n%s\n%s\n", ERR_NAME, ERR_USG), false);
    if (ext == NULL || ft_strncmp(ext, ".cub", 5) != 0)
        return (printf("❌ Error\n%s\n%s\n", ERR_EXT, ERR_USG), false);
	if (open(av[1], O_RDWR, 0644) == -1)
		return (printf("❌ Error\n%s\n%s\n", ERR_FILE, ERR_USG), false);
    return (true);
}

int	main(int ac, char **av)
{

	mlx_t* mlx;

	if (!ft_parse_arg(ac, av))
		return(EXIT_FAILURE);
	
	// Test MLX42
	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 128, 128)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	// Test End
	
	return (0);
}
