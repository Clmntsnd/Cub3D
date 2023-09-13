#include "../includes/cub3d.h"


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
			if (data->map[i][j] == ' ' || data->map[i][j] == '\t' || data->map[i][j] == 'E' || data->map[i][j] == 'O' || data->map[i][j] == 'N' || data->map[i][j] == 'S'|| data->map[i][j] == '1' || data->map[i][j] == '0' || data->map[i][j] == '\n')
						i++;
			else
				map_error_exit(data);
			i++;
		}
		j++;
	}
	return (0);
}

int check_walls(t_data *data){
	(void)data;
	return(0);
}