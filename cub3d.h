/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:59:50 by efreire-          #+#    #+#             */
/*   Updated: 2023/03/16 22:57:45 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef VAR_BUILDER_ARR_SIZE
#  define VAR_BUILDER_ARR_SIZE 6
# endif

# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdlib.h>//exit
# include <stdio.h> //printf
# include <unistd.h> //write

# define PI	3.1415926535

# define KEY_W	119
# define KEY_A	97
# define KEY_S	115
# define KEY_D	100
# define KEY_RARROW	65363
# define KEY_LARROW	65361

# define SOUTH	1.57079632679
# define NORTH	4.71238898038
# define EAST	PI
# define WEST	0
# define DEGREE	0.0174533
# define RAYCOUNT	240

# define SCRWIDTH 640
# define SCRHEIGHT 480

# define WALKSIZE	0.25
# define SAFEDIST	0.15

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_s;
	int		endian;
}	t_image;

typedef struct s_texture
{
	t_image	northwall;
	t_image	southwall;
	t_image	eastwall;
	t_image	westwall;
}	t_texture;

typedef struct s_display
{
	float	start;
	float	end;
	float	wall_h;
	float	rest;
	float	r;
	int		side;
	float	ray_angle;
}	t_display;

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

typedef struct s_wdata
{
	t_vector	wdeltastep;
	t_vector	wp_dir;
	t_vector	wstep;
	t_vector	wsidedist;
	t_vector	wp_pos;
	float		nexthit;
}	t_wdata;

typedef struct s_var_builder
{
	char	**var_p;
	char	*code;
	bool	was_init;
}				t_var_builder;

typedef struct s_data
{
	void			*mlx;
	void			*mlx_win;
	float			player_angle;
	float			dist;
	t_vector		voxel;
	t_vector		p_pos;
	t_vector		hit;
	t_vector		p_dir;
	t_vector		sidedist;
	t_vector		step;
	t_vector		deltastep;
	int				side;
	t_texture		textures;
	t_image			frame;
	char			*exec_path;
	char			*path_no;
	char			*path_so;
	char			*path_we;
	char			*path_ea;
	char			*floor_color;
	char			*ceiling_color;
	unsigned long	floor_color_value;
	unsigned long	ceiling_color_value;
	t_var_builder	**var_builder_arr;
	t_vector		*player_pos;
	char			**map;
	int				map_cols;
	int				map_rows;
}					t_data;

// BEGIN: INIT DATA
t_data			*init_data(int argc, char **argv);
void			throw_init_error(char *message);

// Data Base Vars
void			set_data_base_vars(int fd, t_data *data);

// Data Map
void			set_data_map(int fd, t_data *data);
void			print_data_map(t_data *data);
bool			is_map_str_valid(char *str);
bool			is_map_char_valid(char c);
bool			is_char_player(char c);
void			data_map_check(t_data *data);
void			set_player_angle(t_data *gdata);
void			check_map_walls(t_data *data, int y, int x);

// Var Builder Utils
void			var_builder_arr_init(t_data *data);
void			var_builder_arr_check(t_data *data);
bool			is_var_builder_arr_all_init(t_data *data);
// END: INIT DATA

// BEGIN: MLX
void			exec(t_data *data);

// Images
unsigned int	_mlx_get_color(t_image img, int x, int y);
void			_mlx_pixel_put(t_image *image, int x, int y, int color);
void			_init_textures(t_data *gdata);
int				_wall_rescale(t_display *ddata, t_image img, \
	float px, float py);
void			quit_game(t_data *gdata);

// Utils
float			fix_angle(float angle);
int				_get_pixel_color(t_display *ddata, t_data *gdata, \
	float px, float py);

// Movement
int				_change_dir(int keycode, t_data *gdata);
void			_delta_step_walk(t_wdata *wdata);
void			_next_block(t_wdata *wdata);
void			_init_wdata(t_wdata *wdata, t_data *gdata, float angle);
int				_can_walk(int keycode, t_data *gdata, t_wdata *wdata);
int				_input(int keycode, t_data *gdata);

// Raycaster
int				_check_hit(t_data *gdata, int y, int x);
void			_raycaster(t_data *gdata);

// 3D Display
void			_display_3d(t_data *gdata, float pov, float dist, int r);
// END: MLX

#endif
