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
		j++;
	}

	printf("Floodfill map\n");
	int k = 0;
	while(ms->tmp_map[k])
	{
		printf("%s", ms->tmp_map[k]);
		k++;
	}

	printf("Player position is x= %f, y= %f\n", ms->game->pl_pos.x, ms->game->pl_pos.y);
	// printf("\n\nwidth = %d", data->width);
	// printf("\n\nheigth = %d", data->height);
}

t_ms *get_ms(void)
{
	static t_ms *ms = NULL;

	if (ms == NULL)
	{
		ms = ft_calloc(1, sizeof(t_ms));
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

	i = 0;
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
				ms->game->pl_pos.x = i + 0.5;
				ms->game->pl_pos.y = j + 0.5;
				set_dir(ms, i, j);
				ms->main_map[i][j] = '0';
			}	
			j++;
		}
		i++;
	}
}

void get_color(t_ms *ms)
{
	int 		i;
	char 		*tmp;
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	i = 0;
	while (ms->map_args[i])
	{
		if (ms->map_args[i][0] == 'C')
		{
			tmp = ms->map_args[i] + 2;
			r = (u_int32_t)ft_atoi(tmp);
			tmp = strchr(tmp, ',') + 1;
			g = (u_int32_t)ft_atoi(tmp);
			tmp = strchr(tmp, ',') + 1;
			b = (u_int32_t)ft_atoi(tmp);
			ms->game->ceiling = get_rgba(r,g,b,255);
		}
		if (ms->map_args[i][0] == 'F')
		{
			tmp = ms->map_args[i] + 2;
			r = (u_int32_t)ft_atoi(tmp);
			tmp = strchr(tmp, ',') + 1;
			g = (u_int32_t)ft_atoi(tmp);
			tmp = strchr(tmp, ',') + 1;
			b = (u_int32_t)ft_atoi(tmp);
			ms->game->floor = get_rgba(r,g,b,255);
		}
		i++;
	}
}

void init_content(t_ms *ms, char *argv)
{
	get_map_size(ms, argv);
	get_map(ms, argv);
	remove_map_args(ms);
	get_player_pos(ms);
	get_color(ms);
	check_map(ms);
	print_map(ms);
}
