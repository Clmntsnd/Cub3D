
#include "../includes/cub3d.h"

#define ROWS 13
#define COLS 28

void remove_map(t_ms *ms)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if(ms->main_map == NULL)
		ms->main_map = ft_calloc(ms->height + 1, sizeof(char *));
	if(ms->tmp_map == NULL)
		ms->tmp_map = ft_calloc(ms->height + 1, sizeof(char *));
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
				ms->main_map[j] = ms->map[i];
				ms->tmp_map[j] = ms->map[i];
				j++;
				i++;
			}
			else
				i++;
		}
		ms->main_map[j] = "\0";	
		ms->tmp_map[j] = "\0";
}

void remove_map_args(t_ms *ms)
{
	int i;
	int j;
	int flag;

	if(ms->map_args == NULL) 
		ms->map_args = ft_calloc(7, sizeof(char *));
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
				ms->map_args[flag] = ms->map[i];
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
}

//floodfill//

char **copy_map(t_ms *ms)
{
	int i;
	char **map;

	i = 0;
	map = ft_calloc(ms->height + 1, sizeof(char *));
	while (i < ms->height)
	{
		map[i] = ms->tmp_map[i];
		i++;
	}
	map[i] = "\0";
	return(map);
}


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

	floodfill(copy_map(ms), '0', '2', x, y);
	floodfill(copy_map(ms), '2', '0', x, y);

}

