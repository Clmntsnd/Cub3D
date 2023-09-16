#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_data *data;

	data = get_data();
	//TODO: put a ft_err in return that free too
	if (!ft_parse_arg(ac, av))
		return(EXIT_FAILURE);
	init_content(data, av[1]);
	
	//TODO: maybe move this check elsewhere, 'init_mlx' kinda
	if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true)))
	{
		puts(mlx_strerror(mlx_errno)); //To modify, can't use "puts"
		return(EXIT_FAILURE);
	}

	// Function that draws the minimap
	// if any init doesn't work, returns an error
	if (draw_map2D(data) != 0)
		return(EXIT_FAILURE);

	//Hooks to manage key binding
	mlx_loop_hook(data->mlx, ft_randomize, data->mlx);
	mlx_loop_hook(data->mlx, ft_hook, data->mlx);

	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);

	return (0);
}
