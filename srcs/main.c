/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:51:40 by jpilotte          #+#    #+#             */
/*   Updated: 2023/10/17 13:51:42 by jpilotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_ms *ms;

	ms = get_ms();
	if (!ft_parse_arg(ac, av))
		return(EXIT_FAILURE);
	init_content(ms, av[1]);
	if(!get_texture(ms))
		return (EXIT_FAILURE);
	if(!get_color(ms))
        return (EXIT_FAILURE);
	if (init_mlx(ms) == 1)
		return(EXIT_FAILURE);
	mlx_loop_hook(ms->mlx, loop, ms->mlx);
	mlx_loop(ms->mlx);
	mlx_terminate(ms->mlx);
	clean_exit(ms);
	return (0);
}
