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
		ft_free_tab_char(ms->map);
	if(ms->main_map != NULL)
		ft_free_tab_char(ms->main_map);
	if(ms->map_args != NULL)
		ft_free_tab_char(ms->map_args);
	if(ms->game != NULL)
		free(ms->game);
	if(ms != NULL)
		free(ms);
	if(ms->mlx != NULL)
		mlx_close_window(ms->mlx);
	if(ms->tex != NULL)
		free(ms->tex);
	if(ms->paths != NULL)
		ft_free_tab_char(ms->paths);
}

void map_error_exit(t_ms *ms)
{
	free_exit(ms);
	printf("Error\nInvalid map or map not found\n");
	exit(1);
}

void free_texture(t_ms *ms)
{
	free(ms->tex->no_tex);
	free(ms->tex->so_tex);
	free(ms->tex->we_tex);
	free(ms->tex->ea_tex);
	free(ms->tex);
}

int clean_exit(t_ms *ms)
{
	free(ms->game);
	free_texture(ms);
	if(ms->map_args != NULL)
		ft_free_tab_char(ms->map_args);
	printf("Exit\n");
	return(0);
}
