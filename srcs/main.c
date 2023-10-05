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

	//TODO put this in a function
	//grab the texture from the path
	// ms->tex = ft_calloc(1, sizeof(t_tex));
	// if (!ms->tex)
	// 	printf("❌ Error\n%s\n%s\n", ERR_MEM, ERR_USG);

	// ms->tex->so_tex = mlx_load_xpm42("./assets/textures/s_wall.xpm42");
	// if (!ms->tex->so_tex)
	// 	printf("❌ Error\n%s\n%s\n", ERR_S_TEX, ERR_USG);
	// ms->tex->no_tex = mlx_load_xpm42("./assets/textures/n_wall.xpm42");
	// if (!ms->tex->no_tex)
	// 	printf("❌ Error\n%s\n%s\n", ERR_N_TEX, ERR_USG);
	// ms->tex->ea_tex = mlx_load_xpm42("./assets/textures/e_wall.xpm42");
	// if (!ms->tex->no_tex)
	// 	printf("❌ Error\n%s\n%s\n", ERR_E_TEX, ERR_USG);
	// ms->tex->we_tex = mlx_load_xpm42("./assets/textures/w_wall.xpm42");
	// if (!ms->tex->no_tex)
	// 	printf("❌ Error\n%s\n%s\n", ERR_W_TEX, ERR_USG);
	
	//populate the 2D array from the texture 
	ms->tex->so = fill_texture(ms->tex->so_tex);
	ms->tex->no = fill_texture(ms->tex->no_tex);
	ms->tex->we = fill_texture(ms->tex->we_tex);
	ms->tex->ea = fill_texture(ms->tex->ea_tex);
	//TODO put the above in a function
	
	mlx_loop_hook(ms->mlx, loop, ms->mlx);
	
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