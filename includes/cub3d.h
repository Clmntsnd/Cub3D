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
# define ERR_USG	"✅ Usage: ./cub3d <filename.cub>"
# define ERR_ARG	"❌ Arguments number is invalid"
# define ERR_EXT	"❌ File must have a '.cub' extension"
# define ERR_FILE	"❌ File doesn't exist"
# define ERR_NAME	"❌ Invalid File name"
# define ERR_MEM	"❌ Memory allocation failed"

//Window specs
#define WIDTH 10240
#define HEIGHT 5120

/* ------------------ STRUCTS ------------------ */

typedef struct s_data {
	void *mlx;
	void *win;
	int height;
	int width;
	void *wall;
	void *floor;
	void *ceiling;
	void *direction_assets;
	char direction;
	void *player_pos;
	int	pl_x;
	int	pl_y;
	char **map;
	char **tmp_map;
}	t_data;

typedef struct s_minimap
{
	mlx_image_t *map_img;
	int			tile;
	int			tile_s;
	int			tile_b;
	uint32_t	color;
}	t_minimap;

/* ------------------ Error ------------------- */
void map_error_exit(t_data *data);

/* ------------------ Parsing ------------------ */

bool	ft_parse_arg(int ac, char **av);
void get_map(t_data *data, char *argv);
void get_map_size(t_data *data, char argv[1]);
void check_map(t_data *data);
int check_valid_char(t_data *data);
int check_walls(t_data *data);
void remove_map_args(t_data *data);

/* -------------------- Init ------------------- */
t_data *get_data(void);
void init_content(t_data *data, char *argv);

/* -------------------- Utils ------------------ */
int32_t		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int			draw_map2D(t_data *data);

#endif