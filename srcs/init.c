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
		printf("\nMap arg[%d] = %s", j,  ms->map_args[j] + 2);
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

bool	is_valid_arg(char *str) 
{
	int		i;
	int		j;
	char	**color;

	color = ft_split(str, ',');
	if (!color)
		return (false);
	i = 0;
	while(color[i] != NULL)
		i++;
	if (i != 3)
		return (ft_free_tab_char(color), false);
	i = -1;
	while (color[++i])
	{
		if (color[i][0] == '\0' || color[i][0] == '\n')
			return (ft_free_tab_char(color), false);
		j = 0;
		while (color[i][j] && color[i][j] != '\n')
			if (ft_isdigit(color[i][j++]) == 0)
				return (ft_free_tab_char(color), false);
	}
	ft_free_tab_char(color);
	return (true);
}

bool	convert_color(t_ms *ms, int i, char *str)
{
	u_int32_t	r;
	u_int32_t	g;
	u_int32_t	b;

	r = (u_int32_t)ft_atoi(str);
	str = ft_strchr(str, ',') + 1;
	g = (u_int32_t)ft_atoi(str);
	str = ft_strchr(str, ',') + 1;
	b = (u_int32_t)ft_atoi(str);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (false);
	if (ms->map_args[i][0] == 'C')
		ms->game->ceiling = get_rgba(r,g,b,255);
	else
		ms->game->floor = get_rgba(r,g,b,255);
	return (true);
}

bool get_color(t_ms *ms)
{
	int			i;
	char		*tmp;
	
	i = -1;
    while (ms->map_args[++i]) 
	{
        if (ms->map_args[i][0] == 'C' || ms->map_args[i][0] == 'F') 
		{
            tmp = ms->map_args[i] + 1; 
            if (!is_valid_arg(tmp) || !convert_color(ms, i, tmp)) 
            	return (printf("❌ Error\n%s\n", ERR_COL), false);
        }
    }
	return (true);
}

bool get_texture(t_ms *ms)
{
	int i;
	int fd;

	i = -1;
	while (ms->map_args[++i])
	{
		if (ft_strncmp(ms->map_args[i], "NO", 2) == 0)
		{
			if ((fd = open(ms->map_args[i] + 2, O_RDONLY)) != 0)
				return (printf("❌ Error\n"), false);
			ms->tex->no_tex = mlx_load_xpm42(ms->map_args[i]);
			close(fd);
		}
		else if (ft_strncmp(ms->map_args[i], "SO", 2) == 0)
		{
			if ((fd = open(ms->map_args[i] + 2, O_RDONLY)) != 0)
				return (printf("❌ Error\n"), false);
			ms->tex->so_tex = mlx_load_xpm42(ms->map_args[i] + 2);
			close(fd);
		}
		else if (ft_strncmp(ms->map_args[i], "WE", 2) == 0)
		{
			if ((fd = open(ms->map_args[i] + 2, O_RDONLY)) != 0)
				return (printf("❌ Error\n"), false);
			ms->tex->we_tex = mlx_load_xpm42(ms->map_args[i]);
			close(fd);
		}
		else if (ft_strncmp(ms->map_args[i], "EA", 2) == 0)
		{
			if ((fd = open(ms->map_args[i] + 2, O_RDONLY)) != 0)
				return (printf("❌ Error\n"), false);
			ms->tex->ea_tex = mlx_load_xpm42(ms->map_args[i]);
			close(fd);
		}
		i++;
	}
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
        if (*src != ' ' && *src != '\t') {
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
