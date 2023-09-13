#include "../includes/cub3d.h"


void init_content(t_data *data)
{
	get_map(data);
	get_map_size(data);
	check_map(data);
}