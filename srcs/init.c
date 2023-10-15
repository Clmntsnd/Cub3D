#include "../includes/cub3d.h"

t_ms *get_ms(void)
{
	static t_ms *ms = NULL;

	if (ms == NULL)
	{
		ms = (t_ms *)ft_calloc(1, sizeof(t_ms));
		ms->game = ft_calloc(1, sizeof(t_game));
	}
	return (ms);
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

bool get_texture(t_ms *ms)
{
	int i;

	i = -1;
	if(ms->tex == NULL)
		ms->tex = ft_calloc(1, sizeof(t_tex));
	if(ms->paths == NULL) 
		ms->paths = ft_calloc(4, sizeof(char *));
	while (ms->map_args[++i])
	{
		if (ft_strncmp(ms->map_args[i], "NO", 2) == 0)
		{
			ms->paths[0] = ft_strdup(ms->map_args[i] + 2);
			if ((open(ms->map_args[i] + 2, O_RDONLY)) == -1)
				return(printf("❌ Error\n%s\n", ERR_N_TEX), false);
			ms->tex->no_tex = mlx_load_xpm42(ms->paths[0]);
			if(!ms->tex->no_tex)
				return(printf("❌ Error\n%s\n", ERR_XPM_TEX), false);
			free(ms->paths[0]);
			free(ms->map_args[i]);
		}
		else if (ft_strncmp(ms->map_args[i], "SO", 2) == 0)
		{
			ms->paths[1] = ft_strdup(ms->map_args[i] + 2);
			if ((open(ms->map_args[i] + 2, O_RDONLY)) == -1)
				return(printf("❌ Error\n%s\n", ERR_S_TEX), false);
			ms->tex->so_tex = mlx_load_xpm42(ms->paths[1]);
			if(!ms->tex->so_tex)
				return(printf("❌ Error\n%s\n", ERR_XPM_TEX), false);
			free(ms->paths[1]);
			free(ms->map_args[i]);
		}
		else if (ft_strncmp(ms->map_args[i], "WE", 2) == 0)
		{
			ms->paths[2] = ft_strdup(ms->map_args[i] + 2);
			if ((open(ms->map_args[i] + 2, O_RDONLY)) == -1)
				return(printf("❌ Error\n%s\n", ERR_W_TEX), false);
			ms->tex->we_tex = mlx_load_xpm42(ms->paths[2]);
			if(!ms->tex->we_tex)
				return(printf("❌ Error\n%s\n", ERR_XPM_TEX), false);
			free(ms->paths[2]);
			free(ms->map_args[i]);
		}
		else if (ft_strncmp(ms->map_args[i], "EA", 2) == 0)
		{
			ms->paths[3] = ft_strdup(ms->map_args[i] + 2);
			if ((open(ms->map_args[i] + 2, O_RDONLY)) == -1)
				return(printf("❌ Error\n%s\n", ERR_E_TEX), false);
			ms->tex->ea_tex = mlx_load_xpm42(ms->paths[3]);
			if(!ms->tex->ea_tex)
				return(printf("❌ Error\n%s\n", ERR_XPM_TEX), false);
			free(ms->paths[3]);
			free(ms->map_args[i]);
		}
	}
	ms->tex->so = fill_texture(ms->tex->so_tex);
	ms->tex->no = fill_texture(ms->tex->no_tex);
	ms->tex->we = fill_texture(ms->tex->we_tex);
	ms->tex->ea = fill_texture(ms->tex->ea_tex);
	return (true);
}

void init_content(t_ms *ms, char *argv)
{
	get_map_size(ms, argv);
	get_map(ms, argv);
	remove_map_args(ms);
	get_player_pos(ms);
	check_map(ms);
}
