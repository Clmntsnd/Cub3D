
#include "../includes/cub3d.h"

char **calloc_double_p(char **data, int numRows, int numCols) {
    data = (char **)ft_calloc(numRows + 1, sizeof(char *));

    if (data == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    int i = 0;
    while (i < numRows + 1) {
        data[i] = (char *)ft_calloc(numCols, sizeof(char));
        if (data[i] == NULL) {
            perror("Memory allocation failed");
            exit(1);
        }
		i++;
    }
    return data;
}

void remove_map(t_ms *ms)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if(ms->main_map == NULL)
		ms->main_map = calloc_double_p(ms->main_map, ms->height, ms->width);
	while (i < ms->height)
	{
			while((ft_strncmp(&*ms->map[i], &*ms->map_args[0], ft_strlen(ms->map_args[0])) == 0) || (ft_strncmp(&*ms->map[i], &*ms->map_args[1], ft_strlen(ms->map_args[1])) == 0)
				|| (ft_strncmp(&*ms->map[i], &*ms->map_args[2], ft_strlen(ms->map_args[2])) == 0) || (ft_strncmp(&*ms->map[i], &*ms->map_args[3], ft_strlen(ms->map_args[3])) == 0)
				|| (ft_strncmp(&*ms->map[i], &*ms->map_args[4], ft_strlen(ms->map_args[4])) == 0) || (ft_strncmp(&*ms->map[i], &*ms->map_args[5], ft_strlen(ms->map_args[5])) == 0))
					{
						i++;
					}
			if ((ft_strncmp(&*ms->map[i], "1", 1) == 0) || (ft_strncmp(&*ms->map[i], "0", 1) == 0) || (ft_strncmp(&*ms->map[i], " ", 1) == 0) || *ms->map[i] == '\0')
			{
				ms->main_map[j] = ft_strdup(ms->map[i]);
				j++;
				i++;
			}
			else
				i++;
	}
	ms->main_map[j] = "\0";
	ft_free_tab_char(ms->map);
}


void remove_map_args(t_ms *ms)
{
	int i;
	int j;
	int flag;

	if(ms->map_args == NULL) 
		ms->map_args = calloc_double_p(ms->map_args, 6, ms->width);
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
				ms->map_args[flag] = ft_strdup(ms->map[i]);
				flag++;
			}
				i++;
		}
		j++;
	}
	
	//added this
	ms->map_args[flag] = "\0";
	if(flag >= 6)
	{
		remove_map(ms);
		return;
	}
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
	if(ms->map == NULL)
		ms->map = calloc_double_p(ms->map, ms->height, ms->width);
	while(i <= ms->height)
	{
		temp = get_next_line(fd);
		ms->map[i] = temp;
		i++;
	}
	free(temp);
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

	// changed this to 0
	ms->width = 0;

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
	free(rows);
	close(fd);
}

//floodfill//



void	floodfill(char **map, char u, char v, int x, int y)
{
	while (map[x][y] == u)
	{
		map[x][y] = v;
		floodfill(map, u, v, x + 1, y);
		floodfill(map, u, v, x - 1, y);
		floodfill(map, u, v, x, y - 1);
		floodfill(map, u, v, x, y + 1);
	}
	if (map[x][y] == ' ' || map[x][y] == '\t')
	{
		printf("Error\nMap is not surrounded by walls\n");
		exit(0);
	}
}

void check_map(t_ms *ms)
{
	int x;
	int y;


	x = ms->game->pl_pos.x;
	y = ms->game->pl_pos.y;
	//add floodfill to checks
	if(check_valid_char(ms) || check_walls(ms))
	{
		map_error_exit(ms);
	}

	floodfill(ms->main_map, '0', '2', x, y);
	floodfill(ms->main_map, '2', '0', x, y);

}

