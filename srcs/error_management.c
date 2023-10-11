#include "../includes/cub3d.h"

void free_double_p(char **map, int numRows) {
    // Free memory for each row
    for (int i = 0; i < numRows; i++) {
        free(map[i]);
    }

    // Free the array of pointers
    free(map);
}

// void free_exit(t_ms *ms)
// {
// 	if(ms->map != NULL)
// 		ft_free_tab_char(ms->map);
// 	if(ms->main_map != NULL)
// 		ft_free_tab_char(ms->main_map);
// 	if(ms->map_args != NULL)
// 		ft_free_tab_char(ms->map_args);
// 	if(ms->game != NULL)
// 		free(ms->game);
// 	if(ms->mlx != NULL)
// 		mlx_close_window(ms->mlx);
// 	if(ms->tex != NULL)
// 		free(ms->tex);
// 	if(ms->paths != NULL)
// 		ft_free_tab_char(ms->paths);
// 	if(ms != NULL)
// 		free(ms);
// }

void free_exit(t_ms *ms){
	printf("ms: %p\n", ms);

	printf("ms->map: %p\n", ms->map);
	printf("ms->main_map:%p\n", ms->main_map);
	printf("ms->map_args: %p\n", ms->map_args);
	printf("ms->game: %p\n", ms->game);
	printf("ms->mlx: %p\n", ms->mlx);
	printf("ms->tex: %p\n", ms->tex);
	printf("ms->paths: %p\n", ms->paths);
	if(ms->map != NULL)
		ft_free_tab_char(ms->map);
	if(ms->main_map != NULL)
		ft_free_tab_char(ms->main_map);
	if(ms->map_args != NULL)
		ft_free_tab_char(ms->map_args);
	if(ms->game != NULL)
		free(ms->game);
	if(ms->mlx != NULL)
		mlx_close_window(ms->mlx);
	if(ms->tex != NULL)
		free(ms->tex);
	if(ms->paths != NULL)
		ft_free_tab_char(ms->paths);
	if(ms != NULL)
		free(ms);
	printf("\nms: %p\n", ms);
	printf("ms->map: %p\n", ms->map);
	printf("ms->main_map:%p\n", ms->main_map);
	printf("ms->map_args: %p\n", ms->map_args);
	printf("ms->game: %p\n", ms->game);
	printf("ms->mlx: %p\n", ms->mlx);
	printf("ms->tex: %p\n", ms->tex);
	printf("ms->paths: %p\n", ms->paths);
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
