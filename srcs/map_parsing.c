
#include "../includes/cub3d.h"

// void init_assets(t_data *data)
// {

// }


void remove_map_args(t_data *data)
{
	int i;
	int j;
	int flag;

	data->map_args = ft_calloc(6, sizeof(char *));
	j = 0;
	flag = 0;
	while (j < data->width)
	{
		i = 0;
		while (i < data->height)
		{
			if ((ft_strncmp(&data->map[i][j], "NO ", 3) == 0) || (ft_strncmp(&data->map[i][j], "EA ", 3) == 0) 
					|| (ft_strncmp(&data->map[i][j], "SO ", 3) == 0) || (ft_strncmp(&data->map[i][j], "WE ", 3) == 0)
					|| (ft_strncmp(&data->map[i][j], "C ", 2) == 0) || (ft_strncmp(&data->map[i][j], "F ", 2) == 0))
			{
				data->map_args[flag] = data->map[i];
				printf("[i = %d][j = %d]\n", i, j);
				printf("map_args = %s\n", data->map_args[flag]);
				flag++;
			}
				i++;
		}
		data->map_args++;
		j++;
	}
	if(flag == 6)
	{		
		printf("\n\n You have the correct amount of args in your map: %d \n\n", flag);
		// init_assets(data);
	}
	else
		map_error_exit(data);
}

void get_map(t_data *data, char *argv)
{
	int i;
	int fd;
	char *temp;

	i = 0;
	fd = open(argv, O_RDONLY);
	data->map = ft_calloc(data->height + 1, sizeof(char *));
	while(i <= data->height)
	{
		temp = get_next_line(fd);
		data->map[i] = temp;
		i++;
	}
	close(fd);
}

void get_map_size(t_data *data, char argv[1]) {
	int i;
	int fd;
	char *rows;

	i = 0;
	fd = open(argv, O_RDONLY);
	rows = get_next_line(fd);
	data->height = 0;
	data->width = -1;
	while(rows[i])
	{
		i++;
		data->width++;
	}
	while (rows != NULL)
	{
		free(rows);
		rows = get_next_line(fd);
		data->height++;
	}

}

void check_map(t_data *data)
{
	// int x;
	// int y;


	//parsing for top of map information(textures and shit)

	//add floodfill to checks
	if(check_valid_char(data) && check_walls(data))
	{
		map_error_exit(data);
	}

}

