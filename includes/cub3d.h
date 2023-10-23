/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loulou <loulou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 18:59:55 by loulou            #+#    #+#             */
/*   Updated: 2023/10/22 18:59:55 by loulou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <math.h>
# include <fcntl.h>
# include "../libs/libft/include/libft.h"
# include "../libs/libft/include/gnl.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"

/* ------------------ COLORS ------------------- */
# define KNRM	"\x1B[m"
# define BLD	"\x1B[1m"
# define KGRE	"\x1B[2m"
# define KITA	"\x1B[3m"
# define KUND	"\x1B[4m"
# define KRED	"\x1B[31m"
# define KGRN	"\x1B[32m"
# define KYEL	"\x1B[33m"
# define KBLU	"\x1B[34m"
# define KMAG	"\x1B[35m"
# define KCYN	"\x1B[36m"
# define KWHT	"\x1B[37m"
# define KRT	"\033[1;0m"

/* ---------------- Error Msgs ---------------- */
# define ERR_USG		"✅ Usage: ./cub3d <filename.cub>"
# define ERR_ARG		"❌ Arguments number is invalid"
# define ERR_EXT		"❌ File must have a '.cub' extension"
# define ERR_FILE		"❌ File doesn't exist"
# define ERR_NAME		"❌ Invalid File name"
# define ERR_MEM		"❌ Memory allocation failed"
# define ERR_COL		"❌ Invalid Color"
# define ERR_TEX		"❌ Invalid Texture"
# define ERR_XPM_TEX	"❌ Invalid XPM Texture"
# define ERR_M_PL		"❌ More than one player position or no starting \
position.."
# define ERR_C_MAP		"❌ Invalid character in map"
# define ERR_D_ARG		"❌ Duplicate arguments.."
# define ERR_WALL		"❌ Map is not surrounded by walls"

//Window specs
# define WIDTH 1024
# define HEIGHT 768
# define MOVE_SPEED 0.00004
# define ROTATE_SPEED 0.00003
# define MOUSE_SPEED 750

/* ------------------ STRUCTS ------------------ */
typedef struct s_vect
{
	double	x;
	double	y;
}	t_vect;

typedef struct s_game {
	uint32_t	floor;
	uint32_t	ceiling;
	t_vect		pl_pos;
	t_vect		pl_dir;
	t_vect		plane;
	double		cam_x;
	t_vect		ray_dir;
	t_vect		coord;
	t_vect		side_dist;
	t_vect		delta_dist;
	t_vect		step;
	int			side;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	bool		m_activ;
	bool		minimap_activ;
	int			tex_x;
}	t_game;

typedef struct s_tex{
	int			**no;
	int			**so;
	int			**ea;
	int			**we;
	xpm_t		*no_tex;
	xpm_t		*so_tex;
	xpm_t		*ea_tex;
	xpm_t		*we_tex;
}	t_tex;

typedef struct s_ms {
	void		*mlx;
	char		**map;
	char		**map_args;
	char		**main_map;
	char		*paths;
	int			height;
	int			width;
	t_game		*game;
	mlx_image_t	*m_img;
	t_tex		*tex;
	bool		texture_loaded[4];
}	t_ms;

/* ------------------ Error ------------------- */
int		clean_exit(t_ms *ms);
void	map_error_exit(t_ms *ms);
void	free_exit(t_ms *ms);

/* ------------------ Parsing ------------------ */
bool	ft_parse_arg(int ac, char **av);
void	get_map(t_ms *ms, char *argv);
int		get_map_size(t_ms *ms, char argv[1]);
int		check_valid_char(t_ms *ms);
void	remove_map_args(t_ms *ms);
char	*clean_string(char *str);

/* -------------------- Init ------------------- */
t_ms	*get_ms(void);
int		init_mlx(t_ms *ms);
void	init_content(t_ms *ms, char *argv);
bool	get_texture(t_ms *ms);

/* ------------------- Checks ------------------ */
void	check_map(t_ms *ms);
void	check_arg_dup(t_ms *ms);
int		floodfill(char **map, char v, int x, int y);
int		rev_floodfill(char **map, char v, int x, int y);

/* ------------------ Raycast ------------------ */
void	loop(void *param);
void	pick_texture(t_ms *ms, int x);
void	draw_vert_pix(t_ms *ms, int x, xpm_t *wall_text, int **array);
int		**convert_texture(xpm_t *texture);
void	find_texture_hit(t_ms *ms, xpm_t *texture);

/* ------------------ Colors ------------------ */
int32_t	get_rgba(int32_t r, int32_t g, int32_t b, int32_t a);
bool	get_color(t_ms *ms);
bool	convert_color(t_ms *ms, int i, char *str);
bool	is_valid_arg(char *str);

/* ------------------ Utils ------------------ */
void	key_binding(t_ms *ms);
void	move_cursor(t_ms *ms);
void	rotate_vector(double *x, double *y, double angle);
void	get_player_pos(t_ms *ms);
void	set_dir(t_ms *ms, int i, int j);
int		is_valid_char(char c);
bool	check_map_character(char ch, int flag, bool flag_state);
bool	map_starts_with_any_arg(t_ms *ms, int i);
void	check_flag(t_ms *ms, int flag);
void	remove_map(t_ms *ms);
int		floodfill(char **map, char v, int x, int y);
int		rev_floodfill(char **map, char v, int x, int y);

#endif