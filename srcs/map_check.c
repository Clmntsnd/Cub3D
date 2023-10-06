#include "../includes/cub3d.h"

// check that each 6 settings are there

int check_valid_char(t_ms *ms)
{
	int		i;
	int		j;

	j = 0;
	while (*ms->main_map[j] != '\0')
	{
		i = 0;
		while (ms->main_map[j][i] != '\0')
		{
			if (ms->main_map[j][i] == '0' || ms->main_map[j][i] == '1' || ms->main_map[j][i] == 'N' || ms->main_map[j][i] == 'S' || ms->main_map[j][i] == 'E' || ms->main_map[j][i] == 'W' || ms->main_map[j][i] == '\t' || ms->main_map[j][i] == '\n' || ms->main_map[j][i] == ' ')
			{
				i++;
			}
			else
			{
				printf("Error\nInvalid character in map\n");
				return (1);
			}
		}
		j++;
	}
	return (0);
}
