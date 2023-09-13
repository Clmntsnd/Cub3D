
#include "../includes/cub3d.h"

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
	data->map[i] = "\0";
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
	data->width = 0;
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

