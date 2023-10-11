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
	if(ms->map_args != NULL){
		int i = 0;
		while (ms->map_args[i])
		{
			printf("ms->map_args[%d]: %p\n", i, ms->map_args[i]);
			if (ms->map_args[i] != NULL)
				ms->map_args[i] = ft_freenull(ms->map_args[i]);
			i++;
		}
		ms->map_args = ft_freenull(ms->map_args);
	}
		// ft_free_tab_char(ms->map_args);
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
}
