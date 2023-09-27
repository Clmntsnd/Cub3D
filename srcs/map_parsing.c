
#include "../includes/cub3d.h"

<<<<<<< HEAD
// void init_assets(t_data *data)
// {

// }


void remove_map_args(t_data *data)
=======
void remove_map_args(t_ms *ms)
>>>>>>> map2D
{
	int i;
	int j;
	int flag;

	data->map_args = ft_calloc(6, sizeof(char *));
	j = 0;
	flag = 0;
	while (j < ms->width)
	{
		i = 0;
		while (i < ms->height)
		{
			if ((ft_strncmp(&ms->map[i][j], "NO ", 3) == 0) || (ft_strncmp(&ms->map[i][j], "EA ", 3) == 0) 
					|| (ft_strncmp(&ms->map[i][j], "SO ", 3) == 0) || (ft_strncmp(&ms->map[i][j], "WE ", 3) == 0)
					|| (ft_strncmp(&ms->map[i][j], "C ", 2) == 0) || (ft_strncmp(&ms->map[i][j], "F ", 2) == 0))
			{
				data->map_args[flag] = data->map[i];
				printf("[i = %d][j = %d]\n", i, j);
				printf("map_args = %s flag= %d \n", data->map_args[flag], flag);
				flag++;
			}
				i++;
		}
		j++;
	}
	if(flag == 6)
	{		
		printf("\n\n You have the correct amount of args in your map: %d \n\n", flag);
<<<<<<< HEAD
		// init_assets(data);
	}
=======
		// init_assets(ms);
>>>>>>> map2D
	else
		map_error_exit(ms);
}

void get_map(t_ms *ms, char *argv)
{
	int i;
	int fd;
	char *temp;

	i = 0;
	fd = open(argv, O_RDONLY);
	ms->map = ft_calloc(ms->height + 1, sizeof(char *));
	while(i <= ms->height)
	{
		temp = get_next_line(fd);
		ms->map[i] = temp;
		i++;
	}
	close(fd);
}

void get_map_size(t_ms *ms, char argv[1]) {
	int i;
	int fd;
	char *rows;

	i = 0;
	fd = open(argv, O_RDONLY);
	rows = get_next_line(fd);
	ms->height = 0;
	ms->width = -1;
	while(rows[i])
	{
		i++;
		ms->width++;
	}
	while (rows != NULL)
	{
		free(rows);
		rows = get_next_line(fd);
		ms->height++;
	}

}

void check_map(t_ms *ms)
{
	// int x;
	// int y;


	//parsing for top of map information(textures and shit)

	//add floodfill to checks
	if(check_valid_char(ms) && check_walls(ms))
	{
		map_error_exit(ms);
	}

}

