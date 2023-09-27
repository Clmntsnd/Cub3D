#include "../includes/cub3d.h"

void print_map(t_ms *ms)
{
    int i;

    i = 0;
    while (ms->map[i])
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
			if((ft_strncmp(&ms->main_map[i][j], "N", 1) == 0) || (ft_strncmp(&ms->main_map[i][j], "S", 1) == 0) || (ft_strncmp(&ms->main_map[i][j], "W", 1) == 0) || (ft_strncmp(&ms->main_map[i][j], "E", 1) == 0))
			{
				ms->game->pl_pos.x = i;
				ms->game->pl_pos.y = j;
			}
			j++;
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
	check_map(ms);
	print_map(ms);
}
