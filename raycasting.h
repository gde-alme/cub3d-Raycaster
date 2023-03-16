/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:32:50 by gde-alme          #+#    #+#             */
/*   Updated: 2023/03/16 18:45:42 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

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
# define mapWidth 24
# define mapHeight 24
# define SCRWIDTH 640
# define SCRHEIGHT 480
# define WALKSIZE	0.1
# define SAFEDIST	0.05

# define RED	15209763
# define YELLOW	15001621
# define BLUE	2102760
# define WHITE	16777215

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

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	float		player_angle;
	float		player_pos_x;
	float		player_pos_y;
	float		dist;
	t_vector	mapsize;
	t_vector	voxel;
	t_vector	p_pos;
	t_vector	hit;
	t_vector	p_dir;
	t_vector	sidedist;
	t_vector	step;
	t_vector	deltastep;
	int			side;
	t_texture	textures;
	t_image		frame;
}	t_data;

//images.c
unsigned int	_mlx_get_color(t_image img, int x, int y);
void			_mlx_pixel_put(t_image *image, int x, int y, int color);
void			_init_textures(t_data *gdata);
int				_wall_rescale(t_display *ddata, t_image img, \
	float px, float py);

void			quit_game(t_data *gdata);

//utils.c
float			fix_angle(float angle);
int				_get_pixel_color(t_display *ddata, t_data *gdata, \
	float px, float py);

//movement.c
int				_change_dir(int keycode, t_data *gdata);
void			_delta_step_walk(t_wdata *wdata);
void			_next_block(t_wdata *wdata);
void			_init_wdata(t_wdata *wdata, t_data *gdata, float angle);
int				_can_walk(int keycode, t_data *gdata, t_wdata *wdata);
int				_input(int keycode, t_data *gdata);

//raycaster.c
int				_check_hit(t_data *gdata); //rmv
void			_raycaster(t_data *gdata);

//3D display
void			_display_3d(t_data *gdata, float pov, float dist, int r);

#endif