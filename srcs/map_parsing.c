
#include "../includes/cub3d.h"

// void init_assets(t_data *data)
// {

// }

// void remove_map(t_data *data)
// {
// 	int i;
// 	int j;
// 	int flag;

// 	i = 0;
// 	flag = 0;
// 	data->tmp_map = ft_calloc(data->height + 1, sizeof(char *));
// 	while (i < data->height)
// 	{
// 		j = 0;
// 		data->tmp_map[i] = ft_calloc(data->width + 1, sizeof(char));
// 		while (j < data->width)
// 		{
// 			if ((ft_strncmp(&data->map[i][j], "NO ", 3) == 0) || (ft_strncmp(&data->map[i][j], "EA ", 3) == 0) 
// 					|| (ft_strncmp(&data->map[i][j], "SO ", 3) == 0) || (ft_strncmp(&data->map[i][j], "WE ", 3) == 0)
// 					|| (ft_strncmp(&data->map[i][j], "C ", 2) == 0) || (ft_strncmp(&data->map[i][j], "F ", 2) == 0))
// 			{
// 				flag = 1;
// 				break;
// 			}
// 			data->tmp_map[i][j] = data->map[i][j];
// 			j++;
// 		}
// 		if(flag == 1)
// 			break;
// 		i++;
// 	}
// 	i++;
// 	while (i < data->height)
// 	{
// 		j = 0;
// 		data->tmp_map[i] = ft_calloc(data->width + 1, sizeof(char));
// 		while (j < data->width)
// 		{
// 			data->tmp_map[i][j] = data->map[i][j];
// 			j++;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (i < data->height)
// 	{
// 		free(data->map[i]);
// 		i++;
// 	}
// 	free(data->map);
// 	data->map = data->tmp_map;
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
				flag++;
			}
				i++;
		}
		j++;
	}
	i = 0;
	if(flag == 6)
	{
		remove_map(data);
		return;
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

