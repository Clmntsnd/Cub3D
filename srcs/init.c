#include "../includes/cub3d.h"

void print_map(t_data *data)
{
    int i;

    i = 0;
    while (data->map[i])
    {
        printf("%s", data->map[i]);
        i++;
    }
	int j = 0;
	while(j < 6)
	{
		printf("\nMap arg[%d] = %s", j,  data->map_args[j]);
		j++;
	}
	printf("\n\nwidth = %d", data->width);
	printf("\n\nheigth = %d", data->height);
}

t_data *get_data(void)
{
	static t_data *data = NULL;

	if (data == NULL)
		data = ft_calloc(1, sizeof(t_data));
	return (data);
}

void init_content(t_data *data, char *argv)
{
	get_map_size(data, argv);
	get_map(data, argv);
	remove_map_args(data);
	check_map(data);
	print_map(data);
}
