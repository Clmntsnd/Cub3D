/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:51:25 by jpilotte          #+#    #+#             */
/*   Updated: 2023/10/17 16:16:50 by jpilotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_map(t_ms *ms)
{
	int	x;
	int	y;

	x = ms->game->pl_pos.x;
	y = ms->game->pl_pos.y;
	if (check_valid_char(ms))
		map_error_exit(ms);
	if (floodfill(ms->main_map, 'X', x, y) 
		|| rev_floodfill(ms->main_map, '0', x, y))
	{
		printf("❌ Error\n%s\n", ERR_WALL),
		map_error_exit(ms);
	}
}

void	error_flag(t_ms *ms, int *flag)
{
	printf("❌ Error\n%s\n", ERR_D_ARG);
	free(flag);
	map_error_exit(ms);
}

void	check_arg_dup(t_ms *ms)
{
	int	i;
	int	*flag;

	i = -1;
	flag = ft_calloc(6, sizeof(int));
	while (++i < 5)
	{
		if (ms->map_args[i][0] == 'N')
			flag[0] = 1;
		else if (ms->map_args[i][0] == 'S')
			flag[1] = 1;
		else if (ms->map_args[i][0] == 'W')
			flag[2] = 1;
		else if (ms->map_args[i][0] == 'E')
			flag[3] = 1;
		else if (ms->map_args[i][0] == 'F')
			flag[4] = 1;
		else if (ms->map_args[i][0] == 'C')
			flag[5] = 1;
		else if (flag[i] != 1)
			error_flag(ms, flag);
	}
	free(flag);
}

bool is_valid_position(char **map, int x, int y) {
    return x >= 0 && y >= 0 && map[x] && map[x][y] && 
           (map[x][y] == '0' || map[x][y] == 'N' || map[x][y] == 'S' || 
            map[x][y] == 'E' || map[x][y] == 'W');
}

bool has_boundary_violation(char **map, int x, int y) {
    if (!map[x] || !map[x][y] || map[x][y] == ' ' || map[x][y] == '\t' || 
        (map[x][y + 1] == '\0' && map[x][y] == '0') || 
        (map[x][y + 1] == '\n' && map[x][y] == '0')) {
        return true;
    }
    return false;
}

int floodfill(char **map, char v, int x, int y) {
    if (has_boundary_violation(map, x, y)) {
        return 1;
    }
    
    if (is_valid_position(map, x, y) && map[x][y] == '0') {
        map[x][y] = v;
        return floodfill(map, v, x + 1, y) ||
               floodfill(map, v, x - 1, y) ||
               floodfill(map, v, x, y + 1) ||
               floodfill(map, v, x, y - 1);
    }
    return 0;
}

int rev_floodfill(char **map, char v, int x, int y) 
{
    if (has_boundary_violation(map, x, y))
        return 1;
    if (map[x][y] == 'X') {
        map[x][y] = v;
        return rev_floodfill(map, v, x + 1, y) ||
               rev_floodfill(map, v, x - 1, y) ||
               rev_floodfill(map, v, x, y + 1) ||
               rev_floodfill(map, v, x, y - 1);
    }
    return 0;
}
