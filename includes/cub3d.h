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
# define ERR_COL	"❌ Invalid Color"
# define ERR_S_TEX	"❌ Invalid South Texture"
# define ERR_N_TEX	"❌ Invalid North Texture"
# define ERR_W_TEX	"❌ Invalid West Texture"
# define ERR_E_TEX	"❌ Invalid East Texture"

//Window specs
#define WIDTH 1024
#define HEIGHT 768
# define MOVE_SPEED 0.00004
# define ROTATE_SPEED 0.00003
# define MOUSE_SPEED 1000

/* ------------------ STRUCTS ------------------ */
typedef	struct s_vect
{
	double x;
	double y;
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
	char 		**main_map;
	char    	**paths;
	int			height; 	//map height
	int			width;		//map width
	t_game		*game;		//game informations
	mlx_image_t *m_img;
	t_tex		*tex;
	void		*wall;
	void		*floor;
	void		*ceiling;	
}	t_ms;

typedef struct s_ray
{
	double	x;
	double	y;
	bool	hit_wall;
}	t_ray;

typedef struct s_minimap
{
	mlx_image_t *map_img;
	mlx_image_t *player_img;
	mlx_image_t *ray_img;
	t_ray		ray;
	double		pl_w;	// 'size' of the player (in pixel)
	double		pl_h;	// 'size' of the player (in pixel)
	double		pl_x;	// 'position' of the player in x
	double		pl_y;	// 'position' of the player in y
	double		pl_dx;	// delta 'position' of the player in x
	double		pl_dy;	// delta 'position' of the player in y
	double		pl_dir;	// view direction of the player
	int			tile;
	int			tile_s;
	int			tile_b;
	uint32_t	color;
}	t_minimap;

/* ------------------ Error ------------------- */
void map_error_exit(t_ms *ms);
void free_exit(t_ms *ms);

/* ------------------ Parsing ------------------ */

bool	ft_parse_arg(int ac, char **av);
void get_map(t_ms *ms, char *argv);
void get_map_size(t_ms *ms, char argv[1]);
void check_map(t_ms *ms);
int check_valid_char(t_ms *ms);
int check_walls(t_ms *ms);
void remove_map_args(t_ms *ms);
char **sanatize_args(char **args);

/* -------------------- Init ------------------- */
t_ms		*get_ms(void);
t_minimap	*get_minimap(void);
void		init_content(t_ms *ms, char *argv);
bool 		get_color(t_ms *ms);
bool		get_texture(t_ms *ms);

/* ------------------ Minimap ------------------ */
void			draw_map2D(void *param);
// int			draw_map2D(t_ms *ms);

/* ------------------ Utils ------------------ */
int32_t 	get_rgba(int32_t r, int32_t g, int32_t b, int32_t a);
void 		ft_hook(void* param);
void		ft_player_and_ray(void* param);
void		print_player(void *param);
void		cast_ray(t_minimap *minimap);
char **calloc_double_p(char **data, int numRows, int numCols);
void		loop(void *param);
void		print_init(t_ms *ms);
void		key_binding(t_ms *ms);
void		move_cursor(t_ms *ms);
void		rotate_vector(double *x, double *y, double angle);


void	put_color_to_tile(t_ms *ms, t_minimap *minimap);
void	put_pixel_to_map2D(t_minimap *minimap, int i, int j, uint32_t color);
int		**fill_texture(xpm_t *texture);





#endif