#include "../includes/cub3d.h"

void print_map(t_ms *ms)
{
    int i;

    i = 0;
    while (ms->map[i])
    {
        printf("%s", ms->map[i]);
        i++;
    }
<<<<<<< HEAD
	int j = 0;
	while(j < 6)
	{
		printf("\nMap arg[%d] = %s", j,  data->map_args[j]);
		j++;
	}
	printf("\n\nwidth = %d", data->width);
	printf("\n\nheigth = %d", data->height);
=======
	printf("\n\nwidth = %d", ms->width);
	printf("\n\nheigth = %d", ms->height);
>>>>>>> map2D
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

void init_content(t_ms *ms, char *argv)
{
	get_map_size(ms, argv);
	get_map(ms, argv);
	// remove_map_args(ms);
	check_map(ms);
	print_map(ms);
}
