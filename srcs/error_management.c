#include "../includes/cub3d.h"


void map_error_exit(t_ms *ms)
{
	if(ms->map != NULL)
	{
		ft_free_tab_char(ms->map);
	}
	if(ms->main_map != NULL)
	{
		ft_free_tab_char(ms->main_map);
	}
	if(ms->tmp_map)
	{
		ft_free_tab_char(ms->tmp_map);
	}
	printf("Error\nInvalid map or map not found\n");
	exit(1);
}

void free_args(t_ms *ms)
{
	int i;

	i = 0;
	while(ms->map_args[i])
	{
		free(ms->map_args[i]);
		i++;
	}
	free(ms->map_args);
}