/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:05:06 by jpilotte          #+#    #+#             */
/*   Updated: 2023/10/17 13:46:12 by jpilotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	ft_parse_arg(int ac, char **av)
{
	char	*ext;
	int		len;

	ext = ft_strrchr(av[1], '.');
	len = ft_strlen(av[1]);
	if (ac != 2)
		return (printf("❌ Error\n%s\n%s\n", ERR_ARG, ERR_USG), false);
	if (open(av[1], O_RDWR, 0644) == -1)
		return (printf("❌ Error\n%s\n%s\n", ERR_FILE, ERR_USG), false);
	if (ext == NULL || ft_strncmp(ext, ".cub", 5) != 0)
		return (printf("❌ Error\n%s\n%s\n", ERR_EXT, ERR_USG), false);
	if (len < 5)
		return (printf("❌ Error\n%s\n%s\n", ERR_NAME, ERR_USG), false);
	return (true);
}

bool	check_map_character(char ch, int flag, bool flag_state)
{
	bool	is_valid_char;

	is_valid_char = (ch == '1' || ch == '0' || ch == 'N' || ch == 'S'
			|| ch == 'E' || ch == 'W' || ch == ' ' || ch == '\t');
	if (flag_state && flag == 6)
		return (is_valid_char);
	else if (!flag_state && flag != 6)
		return (is_valid_char);
	return (false);
}

bool	map_starts_with_any_arg(t_ms *ms, int i)
{
	int	arg_index;

	arg_index = -1;
	while (++arg_index < 6)
	{
		if (ft_strncmp(ms->map[i], ms->map_args[arg_index], \
			ft_strlen(ms->map_args[arg_index])) == 0)
			return (true);
	}
	return (false);
}

void	check_flag(t_ms *ms, int flag)
{
	if (flag == 6)
	{
		check_arg_dup(ms);
		remove_map(ms);
		return ;
	}
	else
	{
		printf("❌ Error\n%s\n", ERR_ARG);
		if (ms->map_args)
			ft_free_tab_char(ms->map_args);
		map_error_exit(ms);
	}
}
