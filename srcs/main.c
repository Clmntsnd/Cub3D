#include "../includes/cub3d.h"

int	init_mlx(t_ms *ms)
{
	if (!(ms->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true)))
	{
		printf("%s\n", mlx_strerror(mlx_errno)); 
		return(EXIT_FAILURE);
	}
	if(!(ms->m_img = mlx_new_image(ms->mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(ms->mlx);
		printf("%s\n", mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if(mlx_image_to_window(ms->mlx, ms->m_img, 0, 0) == -1)
	{
		mlx_close_window(ms->mlx);
		printf("%s\n", mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// void ft_hook(void* param)
// {
// 	mlx_t* mlx = param;

// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_UP))
// 		image->instances[0].y -= 2;
// 	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
// 		image->instances[0].y += 2;
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
// 		image->instances[0].x -= 2;
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 		image->instances[0].x += 2;
// }

int	main(int ac, char **av)
{
	t_ms *ms;

	ms = get_ms();
	//TODO: put a ft_err in return that free too
	if (!ft_parse_arg(ac, av))
		return(EXIT_FAILURE);

	init_content(ms, av[1]);

	//TODO get_texture needs rework
	if(!get_texture(ms))
		return (EXIT_FAILURE);
	if(!get_color(ms))
        return (EXIT_FAILURE);
	if (init_mlx(ms) == 1)
		return(EXIT_FAILURE);
	
	// draw_map2D(ms);
	mlx_loop_hook(ms->mlx, loop, ms->mlx);
	// mlx_loop_hook(ms->mlx, draw_map2D, ms->mlx);
	// mlx_loop_hook(ms->mlx, ft_hook, ms->mlx);
	
	// Function that draws the minimap
	// if any init doesn't work, returns an error
	// if (draw_map2D(ms) != 0)
	// 	return(EXIT_FAILURE);

	mlx_loop(ms->mlx);
	mlx_terminate(ms->mlx);
	//TODO don't forget to free shit
	return (0);
}

//TODO grabs textures from file and put them in raycast