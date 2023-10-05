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
	// if(!get_texture(ms))
	// 	return (EXIT_FAILURE);
	if(!get_color(ms))
        return (EXIT_FAILURE);
	if (init_mlx(ms) == 1)
		return(EXIT_FAILURE);

	//grab the texture from the path
	ms->tex = ft_calloc(1, sizeof(t_tex));
	ms->tex->so_tex = mlx_load_xpm42("./assets/textures/s_wall.xpm42");
	ms->tex->no_tex = mlx_load_xpm42("./assets/textures/test.xpm42");
	ms->tex->ea_tex = mlx_load_xpm42("./assets/textures/test2.xpm42");
	ms->tex->we_tex = mlx_load_xpm42("./assets/textures/w_wall.xpm42");
	if (!ms->tex->so_tex)
		printf("pb texture\n");
	//populate the 2D array from the texture 
	ms->tex->so = fill_texture(ms->tex->so_tex);
	ms->tex->no = fill_texture(ms->tex->no_tex);
	ms->tex->we = fill_texture(ms->tex->we_tex);
	ms->tex->ea = fill_texture(ms->tex->ea_tex);
	//TODO put the above in a function
	
	// draw_map2D(ms);
	mlx_loop_hook(ms->mlx, loop, ms->mlx);
	// mlx_loop_hook(ms->mlx, draw_map2D, ms->mlx);
	// mlx_loop_hook(ms->mlx, ft_hook, ms->mlx);
	
	// Function that draws the minimap
	// if any init doesn't work, returns an error
	// if (draw_map2D(ms) != 0)
	// 	return(EXIT_FAILURE);

	// mlx_delete_image(ms->mlx, ms->m_img);
	mlx_loop(ms->mlx);
	mlx_terminate(ms->mlx);
	//TODO don't forget to free shit
	return (0);
}

//TODO grabs textures from file and put them in raycast