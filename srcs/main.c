/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:51:40 by jpilotte          #+#    #+#             */
/*   Updated: 2023/10/18 15:36:09 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_mlx(t_ms *ms)
{
	ms->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!(ms->mlx))
	{
		printf("%s\n", mlx_strerror(mlx_errno)); 
		return (EXIT_FAILURE);
	}
	ms->m_img = mlx_new_image(ms->mlx, WIDTH, HEIGHT);
	if (!(ms->m_img))
	{
		mlx_close_window(ms->mlx);
		printf("%s\n", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(ms->mlx, ms->m_img, 0, 0) == -1)
	{
		mlx_close_window(ms->mlx);
		printf("%s\n", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_ms	*ms;

	ms = get_ms();
	if (!ft_parse_arg(ac, av))
	{	
		mlx_terminate(ms->mlx);
		return (EXIT_FAILURE);
	}
	init_content(ms, av[1]);
	if (!get_texture(ms) || !get_color(ms) || init_mlx(ms) == 1)
	{
		mlx_terminate(ms->mlx);
		if (ms->mlx != NULL)
			ms->mlx = ft_freenull(ms->mlx);
		clean_exit(ms);
		return (1);
	}
	mlx_loop_hook(ms->mlx, loop, ms->mlx);
	mlx_loop(ms->mlx);
	mlx_terminate(ms->mlx);
	clean_exit(ms);
	return (0);
}
