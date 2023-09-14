#include "../includes/cub3d.h"

// check that each 6 settings are there

int check_valid_char(t_data *data)
{
	int		i;
	int		j;

	j = 0;
	while (j < data->width)
	{
		i = 0;
		while (i < data->height)
		{
			i++;

			// Add map restrictions here //

			// if (data->map[i][j] == ' ' || data->map[i][j] == '\t' || data->map[i][j] == 'E' || data->map[i][j] == 'O' || data->map[i][j] == 'N' || data->map[i][j] == 'S'|| data->map[i][j] == '1' || data->map[i][j] == '0' || data->map[i][j] == '\n')
			// 			i++;
			// else
			// 	map_error_exit(data);
		}
		j++;
	}
	return (0);
}

int check_walls(t_data *data){
	(void)data;
	return(0);
}