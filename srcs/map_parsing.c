
#include "../includes/cub3d.h"

void remove_map(t_ms *ms)
{
	int i;
	int j;
	int flag;

	i = 0;
	j = 0;
	flag = 0;
	if(ms->main_map == NULL)
		ms->main_map = (char **)ft_calloc(ms->height + 1, sizeof(char *));
	while (i < ms->height)
	{
			while ((ft_strncmp(&*ms->map[i], &*ms->map_args[0], ft_strlen(ms->map_args[0])) == 0) || (ft_strncmp(&*ms->map[i], &*ms->map_args[1], ft_strlen(ms->map_args[1])) == 0)
				|| (ft_strncmp(&*ms->map[i], &*ms->map_args[2], ft_strlen(ms->map_args[2])) == 0) || (ft_strncmp(&*ms->map[i], &*ms->map_args[3], ft_strlen(ms->map_args[3])) == 0)
				|| (ft_strncmp(&*ms->map[i], &*ms->map_args[4], ft_strlen(ms->map_args[4])) == 0) || (ft_strncmp(&*ms->map[i], &*ms->map_args[5], ft_strlen(ms->map_args[5])) == 0))
					{
						i++;
						flag++;
					}
			if (((ms->map[i][j] == '1' || ms->map[i][j] == '0'  || ms->map[i][j] == 'N' || ms->map[i][j] == 'S' || ms->map[i][j] == 'E' || ms->map[i][j] == 'W' || ms->map[i][j] == ' ' || ms->map[i][j] == '\t') && (ms->map[i][j])) && (flag != 6))
			{
				printf("error\nToo few or too many textures..");
				map_error_exit(ms);
			}
			else if (((ms->map[i][j] == '1' || ms->map[i][j] == '0'  || ms->map[i][j] == 'N' || ms->map[i][j] == 'S' || ms->map[i][j] == 'E' || ms->map[i][j] == 'W' || ms->map[i][j] == ' ' || ms->map[i][j] == '\t')) && (flag == 6))
			{
				ms->main_map[j] = ft_strdup(ms->map[i]);
				j++;
			}
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
		ms->map_args = (char **)ft_calloc(7, sizeof(char *));
	j = 0;
	flag = 0;
	while (j < ms->width)
	{
				i = 0;
		while (i < ms->height){
			if ((ft_strncmp(&ms->map[i][j], "NO ", 3) == 0) || (ft_strncmp(&ms->map[i][j], "EA ", 3) == 0) 
				|| (ft_strncmp(&ms->map[i][j], "SO ", 3) == 0) || (ft_strncmp(&ms->map[i][j], "WE ", 3) == 0)
				|| (ft_strncmp(&ms->map[i][j], "C ", 2) == 0) || (ft_strncmp(&ms->map[i][j], "F ", 2) == 0))
			{
				ms->map_args[flag] = ft_strdup(*sanatize_args(&ms->map[i]));
				flag++;
			}
			i++;
		}
		j++;
	}
	// if(check_arg_order(ms) == 0)
	// 	map_error_exit(ms);
	// ms->map_args[flag] = "\0";
	if(flag == 6)
	{
		check_arg_dup(ms);
		remove_map(ms);
		return;
	}
	else
	{
		printf("Error\nNot enough arguments\n");
		map_error_exit(ms);
	}
}

void get_map(t_ms *ms, char *argv)
{
	int i;
	int fd;
	char *temp;

	i = 0;
	fd = open(argv, O_RDONLY);
	if(ms->map == NULL)
		ms->map = (char **)ft_calloc(ms->height + 1, sizeof(char *));
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



