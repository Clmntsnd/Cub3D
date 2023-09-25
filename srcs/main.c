#include "../includes/cub3d.h"

void	print_init(t_ms *ms)
{
	printf("\nplpos.x: 	%.2f\n", ms->game->pl_pos.x);
	printf("plpos.y: 	%.2f\n", ms->game->pl_pos.y);
	printf("pldir.x: 	%.2f\n", ms->game->pl_dir.x);
	printf("pldir.y: 	%.2f\n", ms->game->pl_dir.y);
	printf("plane.x: 	%.2f\n", ms->game->plane.x);
	printf("plane.y: 	%.2f\n", ms->game->plane.y);
	printf("cam_x: 		%.2f\n", ms->game->cam_x);
	printf("ray_dir.x: 	%.2f\n", ms->game->ray_dir.x);
	printf("ray_dir.y: 	%.2f\n", ms->game->ray_dir.y);
	// printf("map.x: 		%.2f\n", ms->game->map.x);
	// printf("map.y: 		%.2f\n", ms->game->map.y);
	printf("side_dist.x: 	%.2f\n", ms->game->side_dist.x);
	printf("side_dist.y: 	%.2f\n", ms->game->side_dist.y);
	printf("delta_dist.x: 	%.2f\n", ms->game->delta_dist.x);
	printf("delta_dist.y: 	%.2f\n", ms->game->delta_dist.y);
	printf("step.x: 	%.2f\n", ms->game->step.x);
	printf("step.y: 	%.2f\n", ms->game->step.y);
	printf("side:		%d\n", ms->game->side);
}

int	main(int ac, char **av)
{
	t_ms *ms;

	ms = get_ms();
	//TODO: put a ft_err in return that free too
	if (!ft_parse_arg(ac, av))
		return(EXIT_FAILURE);
	// init_content(ms, av[1]);
	
	//TODO: maybe move this check elsewhere, 'init_mlx' kinda
	if (!(ms->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true)))
	{
		puts(mlx_strerror(mlx_errno)); //To modify, can't use "puts"
		return(EXIT_FAILURE);
	}
	init_game(ms);
	print_init(ms);
	if(!(ms->m_img = mlx_new_image(ms->mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(ms->mlx);
		puts(mlx_strerror(mlx_errno)); //To modify, can't use "puts"
		return(EXIT_FAILURE);
	}
	if(mlx_image_to_window(ms->mlx, ms->m_img, 0, 0) == -1)
	{
		mlx_close_window(ms->mlx);
		puts(mlx_strerror(mlx_errno)); //To modify, can't use "puts"
		return(EXIT_FAILURE);
	}

	mlx_loop_hook(ms->mlx, loop, ms->mlx);
	
	// Function that draws the minimap
	// if any init doesn't work, returns an error
	// if (draw_map2D(ms) != 0)
	// 	return(EXIT_FAILURE);

	// mlx_loop_hook(ms->mlx, ft_player_and_ray, ms->mlx); // create the player by filling the image w/ red pixels
	// mlx_loop_hook(ms->mlx, ft_hook, ms->mlx); // key hook
	// mlx_loop_hook(ms->mlx, cast_ray, ms->mlx); // creat the ray, based on the same methid as the player
	// mlx_loop_hook(ms->mlx, print_player, ms->mlx); // print play position

	mlx_loop(ms->mlx);
	mlx_terminate(ms->mlx);

	return (0);
}
