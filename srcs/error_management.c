#include "../includes/cub3d.h"

void free_double_p(char **map, int numRows) {
    // Free memory for each row
    for (int i = 0; i < numRows; i++) {
        free(map[i]);
    }

    // Free the array of pointers
    free(map);
}

void free_exit(t_ms *ms){
	if(ms->map != NULL)
	{
		ft_free_tab_char(ms->map);
	}
	if(ms->main_map != NULL)
	{
		ft_free_tab_char(ms->main_map);
	}
	if(ms->map_args != NULL)
	{
		ft_free_tab_char(ms->map_args);
	}
	if(ms->game != NULL)
	{
		free(ms->game);
	}
	if(ms != NULL)
	{
		free(ms);
	}
	if(ms->mlx != NULL)
	{
		mlx_close_window(ms->mlx);
	}
}


void map_error_exit(t_ms *ms)
{
	free_exit(ms);
	printf("Error\nInvalid map or map not found\n");
	exit(1);
}

