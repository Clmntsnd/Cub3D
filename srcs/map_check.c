#include "../includes/cub3d.h"

// check that each 6 settings are there

int check_valid_char(t_ms *ms)
{
	int		i;
	int		j;

	j = 0;
	while (j < ms->width)
	{
		i = 0;
		while (i < ms->height)
		{
			i++;

			// Add map restrictions here //

			// if (ms->map[i][j] == ' ' || ms->map[i][j] == '\t' || ms->map[i][j] == 'E' || ms->map[i][j] == 'O' || ms->map[i][j] == 'N' || ms->map[i][j] == 'S'|| ms->map[i][j] == '1' || ms->map[i][j] == '0' || ms->map[i][j] == '\n')
			// 			i++;
			// else
			// 	map_error_exit(ms);
		}
		j++;
	}
	return (0);
}

int check_walls(t_ms *ms){
	(void)ms;
	return(0);
}