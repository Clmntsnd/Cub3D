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
	ms->game->pl_pos.x = i + 0.5;
	ms->game->pl_pos.y = j + 0.5;
	ms->main_map[i][j] = '0';
}

void get_player_pos(t_ms *ms)
{
	int i;
	int j;
	int flag;

	i = -1;
	flag = 0;
	while(ms->main_map[++i])
	{
		j = -1;
		while(ms->main_map[i][++j])
		{
			if((ms->main_map[i][j] == 'N') || (ms->main_map[i][j] == 'S') || (ms->main_map[i][j] == 'W' || (ms->main_map[i][j] == 'E')))
			{
				flag++;
				set_dir(ms, i, j);
			}
		}
	}
	if (flag > 1 || flag == 0)
	{
		printf("Error\nMore than one player position or no starting position..\n");
		map_error_exit(ms);	
	}
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

char **sanatize_args(char **args)
{
	if (args == NULL || *args == NULL) {
        return(NULL);
    }
    char *src = *args;
    char *dst = *args;

    while (*src)
	{
        if (*src != ' ' && *src != '\t' && *src != '\n') 
		{
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
	printf("test\n");
	get_player_pos(ms);
	check_map(ms);
	//remove before grading
	// print_map(ms);
}
