/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:46:33 by jpilotte          #+#    #+#             */
/*   Updated: 2023/10/20 14:49:43 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int32_t	get_rgba(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

bool	convert_color(t_ms *ms, int i, char *str)
{
	u_int32_t	r;
	u_int32_t	g;
	u_int32_t	b;

	r = (u_int32_t)ft_atoi(str);
	str = ft_strchr(str, ',') + 1;
	g = (u_int32_t)ft_atoi(str);
	str = ft_strchr(str, ',') + 1;
	b = (u_int32_t)ft_atoi(str);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (false);
	if (ms->map_args[i][0] == 'C')
		ms->game->ceiling = get_rgba(r, g, b, 255);
	else
		ms->game->floor = get_rgba(r, g, b, 255);
	return (true);
}

bool	get_color(t_ms *ms)
{
	int		i;
	char	*tmp;
	int 	flag_c;
	int 	flag_f;

	i = -1;
	flag_c = 0;
	flag_f = 0;
	while (ms->map_args[++i])
	{
		if (ms->map_args[i][0] == 'C' || ms->map_args[i][0] == 'F')
		{
			if (ms->map_args[i][0] == 'C')	 
				flag_c++; //needs to be 1 to be valid
			if (ms->map_args[i][0] == 'F')	 
				flag_f++; //needs to be 1 to be valid
			tmp = ms->map_args[i] + 1;
			if (!is_valid_arg(tmp) || !convert_color(ms, i, tmp))
				return (printf("❌ Error\n%s\n", ERR_COL), false);
		}
	}
	if (flag_c != 1 || flag_f != 1)
		return (printf("❌ Error\n%s\n", ERR_COL), false);		
	return (true);
}

bool	is_valid_arg(char *str)
{
	int		i;
	int		j;
	char	**color;

	color = ft_split(str, ',');
	if (!color)
		return (false);
	i = 0;
	while (color[i] != NULL)
		i++;
	if (i != 3)
		return (ft_free_tab_char(color), false);
	i = -1;
	while (color[++i])
	{
		if (color[i][0] == '\0' || color[i][0] == '\n')
			return (ft_free_tab_char(color), false);
		j = 0;
		while (color[i][j] && color[i][j] != '\n')
			if (ft_isdigit(color[i][j++]) == 0)
				return (ft_free_tab_char(color), false);
	}
	ft_free_tab_char(color);
	return (true);
}
