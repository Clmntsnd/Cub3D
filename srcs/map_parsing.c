
#include "../includes/cub3d.h"

#define ROWS 13
#define COLS 28

void remove_map(t_ms *ms)
{
	int i;
	int j;

	i = 0;
	j = 0;
	ms->main_map = ft_calloc(ms->height + 1, sizeof(char *));
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

	// ms->map_args = ft_calloc(6, sizeof(char *));
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
	if(flag == 6)
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

int is_valid(int x, int y) {
    // Check if the coordinates (x, y) are within the map boundaries
    return x >= 0 && x < ROWS && y >= 0 && y < COLS;
}

int flood_fill(int x, int y, char **map) {
	int dx[] = {-1, 1, 0, 0};
	int dy[] = {0, 0, -1, 1};
    int surrounded;
	int i;

	i = 0;
	surrounded = 1;
    if (!is_valid(x, y)) {
        return 0;
    }

    if (map[x][y] == '1') {
        return 1;  // We've reached a wall, so it's surrounded
    }

    if (map[x][y] == 'F') {
        return 0;  // We've already visited this cell
    }

    // Mark the current cell as visited
    map[x][y] = 'F';

    // Check the neighboring cells in all four directions
    while (i <= 4) {
        surrounded = surrounded && flood_fill(x + dx[i], y + dy[i], map);
		i++;
    }

    return surrounded;
}

int is_surrounded_by_walls(char **map, t_ms *ms)
{
    return flood_fill(ms->game->pl_pos.x, ms->game->pl_pos.y, map);
}


void check_map(t_ms *ms)
{

	//add floodfill to checks
	if(check_valid_char(ms) && check_walls(ms))
	{
		map_error_exit(ms);
	}

	int surrounded;
	surrounded = is_surrounded_by_walls(ms->tmp_map, ms);

	if (!surrounded) {
        printf("The map and empty spaces are surrounded by walls.\n");
    } else {
		printf("The map and empty spaces are not surrounded by walls.\n");
		map_error_exit(ms);
    }
}

