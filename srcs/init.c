#include "../includes/cub3d.h"

t_data *get_data(void)
{
	static t_data *data = NULL;

	if (data == NULL)
		data = ft_calloc(1, sizeof(t_data));
	return (data);
}

void init_content(t_data *data, char *argv)
{
	get_map(data, argv);
	get_map_size(data, argv);
	check_map(data);
}
