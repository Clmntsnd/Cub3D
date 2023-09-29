#include "../includes/cub3d.h"

// check that each 6 settings are there

int check_valid_char(t_ms *ms)
{
	int		i;
	int		j;
	int 	flag;

	j = 0;
	flag = 0;
	while (*ms->main_map[j] != '\0')
	{
		i = 0;
		while (ms->main_map[j][i] != '\0')
		{
				i++;
		}
		j++;
	}
	return (0);
}

int check_walls(t_ms *ms){
	(void)ms;
	return(0);
}