#include "../includes/cub3d.h"

void	init_player(t_ms *ms)
{
	ms->player->posX = 0;
	ms->player->posY = 0;
	ms->player->dirX = -1;
	ms->player->dirY = 0;
	ms->player->planeX = 0;
	ms->player->planeY = 0.66;
}

int	main(int ac, char **av)
{
	t_ms *ms;

	ms = get_ms();
	//TODO: put a ft_err in return that free too
	if (!ft_parse_arg(ac, av))
		return(EXIT_FAILURE);
	init_content(ms, av[1]);
	
	//TODO: maybe move this check elsewhere, 'init_mlx' kinda
	if (!(ms->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true)))
	{
		puts(mlx_strerror(mlx_errno)); //To modify, can't use "puts"
		return(EXIT_FAILURE);
	}
	init_player(ms);

	printf("\nposX= %.2f\n", ms->player->posX);
	printf("posY= %.2f\n", ms->player->posY);

	// Function that draws the minimap
	// if any init doesn't work, returns an error
	// if (draw_map2D(ms) != 0)
	// 	return(EXIT_FAILURE);

	// mlx_loop_hook(ms->mlx, ft_player_and_ray, ms->mlx); // create the player by filling the image w/ red pixels
	mlx_loop_hook(ms->mlx, ft_hook, ms->mlx); // key hook
	// mlx_loop_hook(ms->mlx, cast_ray, ms->mlx); // creat the ray, based on the same methid as the player
	// mlx_loop_hook(ms->mlx, print_player, ms->mlx); // print play position

	mlx_loop(ms->mlx);
	mlx_terminate(ms->mlx);

	return (0);
}
