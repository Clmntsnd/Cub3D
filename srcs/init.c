#include "../includes/cub3d.h"

void print_map(t_ms *ms)
{
    int i;

    i = 0;
    while (ms->main_map[i])
    {
        printf("%s", ms->main_map[i]);
        i++;
    }
	int j = 0;
	printf("\n\nmap_args\n");
	while(j < 6)
	{
		printf("\nMap arg[%d] = %s", j,  ms->map_args[j]);
		// printf("\npath arg[%d] = %s", j,  ms->paths[j]);
		j++;
	}

	printf("Floodfill map\n");
	int k = 0;
	while(k < ms->height)
	{
		printf("%s", ms->main_map[k]);
		k++;
	}

	printf("Player position is x= %f, y= %f\n", ms->game->pl_pos.x, ms->game->pl_pos.y);
	printf("\n\nwidth = %d", ms->width);
	printf("\n\nheigth = %d", ms->height);
}

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

void	set_dir(t_ms *ms, int i, int j)
{
	if (ms->main_map[i][j] == 'N')
	{
		ms->game->pl_dir.x = -1;
		ms->game->plane.y = 0.66;
	}
	if (ms->main_map[i][j] == 'S')
	{
		ms->game->pl_dir.x = 1;
		ms->game->plane.y = -0.66;
	}
	if (ms->main_map[i][j] == 'E')
	{
		ms->game->pl_dir.y = 1; 
		ms->game->plane.x = 0.66;
	}
	if (ms->main_map[i][j] == 'W')
	{
		ms->game->pl_dir.y = -1; 
		ms->game->plane.x = -0.66;
	}
}

void get_player_pos(t_ms *ms)
{
	int i;
	int j;
	int flag;

	i = 0;
	flag = 0;
	while(ms->main_map[i])
	{
		j = 0;
		while(ms->main_map[i][j])
		{
			if((ft_strncmp(&ms->main_map[i][j], "N", 1) == 0) 
				|| (ft_strncmp(&ms->main_map[i][j], "S", 1) == 0) 
					|| (ft_strncmp(&ms->main_map[i][j], "W", 1) == 0) 
						|| (ft_strncmp(&ms->main_map[i][j], "E", 1) == 0))
			{
				flag++;
				ms->game->pl_pos.x = i + 0.5;
				ms->game->pl_pos.y = j + 0.5;
				set_dir(ms, i, j);
				ms->main_map[i][j] = '0';
			}
			if (flag > 1)
			{
				printf("Error\nMore than one player position\n");
				map_error_exit(ms);	
			}
			j++;
		}
		i++;
	}
}

bool get_texture(t_ms *ms)
{
	int i;

	i = -1;
	if(ms->tex == NULL)
		ms->tex = ft_calloc(1, sizeof(t_tex));
	if(ms->paths == NULL) 
		ms->paths = calloc_double_p(ms->paths, 4, ft_strlen(ms->map_args[0]));
	while (ms->map_args[++i])
	{
		if (ft_strncmp(ms->map_args[i], "NO", 2) == 0)
		{
			ms->paths[0] = ft_strdup(ms->map_args[i] + 2);
			if ((open(ms->map_args[i] + 2, O_RDONLY)) == -1)
				return(printf("❌ Error\n%s\n", ERR_N_TEX), false);
			ms->tex->no_tex = mlx_load_xpm42(ms->paths[0]);
		}
		else if (ft_strncmp(ms->map_args[i], "SO", 2) == 0)
		{
			ms->paths[1] = ft_strdup(ms->map_args[i] + 2);
			if ((open(ms->map_args[i] + 2, O_RDONLY)) == -1)
				return(printf("❌ Error\n%s\n", ERR_S_TEX), false);
			ms->tex->so_tex = mlx_load_xpm42(ms->paths[1]);
		}
		else if (ft_strncmp(ms->map_args[i], "WE", 2) == 0)
		{
			ms->paths[2] = ft_strdup(ms->map_args[i] + 2);
			if ((open(ms->map_args[i] + 2, O_RDONLY)) == -1)
				return(printf("❌ Error\n%s\n", ERR_W_TEX), false);
			ms->tex->we_tex = mlx_load_xpm42(ms->paths[2]);
		}
		else if (ft_strncmp(ms->map_args[i], "EA", 2) == 0)
		{
			ms->paths[3] = ft_strdup(ms->map_args[i] + 2);
			if ((open(ms->map_args[i] + 2, O_RDONLY)) == -1)
				return(printf("❌ Error\n%s\n", ERR_E_TEX), false);
			ms->tex->ea_tex = mlx_load_xpm42(ms->paths[3]);
		}
	}
	ms->tex->so = fill_texture(ms->tex->so_tex);
	ms->tex->no = fill_texture(ms->tex->no_tex);
	ms->tex->we = fill_texture(ms->tex->we_tex);
	ms->tex->ea = fill_texture(ms->tex->ea_tex);
	return (true);
}

char **sanatize_args(char **args)
{
	if (args == NULL || *args == NULL) {
        return(NULL); // Nothing to sanitize
    }
    char *src = *args;
    char *dst = *args;

    while (*src) {
        if (*src != ' ' && *src != '\t' && *src != '\n') {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
	return(args);
}

void init_content(t_ms *ms, char *argv)
{
	get_map_size(ms, argv);
	get_map(ms, argv);
	remove_map_args(ms);
	get_player_pos(ms);
	check_map(ms);
	print_map(ms);
}
