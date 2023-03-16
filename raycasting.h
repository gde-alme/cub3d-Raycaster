/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:32:50 by gde-alme          #+#    #+#             */
/*   Updated: 2023/03/15 17:35:41 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdlib.h>//exit
#include <stdio.h> //printf
#include <unistd.h> //write

#define PI	3.1415926535

#define KEY_W	119
#define KEY_A	97
#define KEY_S	115
#define KEY_D	100
#define KEY_RARROW	65363
#define KEY_LARROW	65361

#define SOUTH	PI/2
#define	NORTH	3*PI/2
#define	EAST	PI
#define	WEST	0
#define degree	0.0174533
#define RAYCOUNT	240
#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480
#define	WALKSIZE	0.1
#define	SAFEDIST	0.05

#define RED	15209763
#define YELLOW	15001621
#define BLUE	2102760
#define WHITE	16777215

typedef struct  s_image {
    void    *img;
    char    *addr;
	int		width;
	int		height;
    int     bpp;
    int     lineS;
    int     endian;
}   t_image;

typedef	struct s_texture {
	t_image	northWall;
	t_image	southWall;
	t_image	eastWall;
	t_image	westWall;
}	t_texture;

typedef	struct	s_display {
	float	start;
	float	end;
	float	wallH;
	float	rest;
	float	r;
	int	side;
	float	ray_angle;
}	t_display;

typedef struct	s_vector {
	float	x;
	float	y;
}	t_vector;

typedef	struct	s_data {
	void	*mlx;
	void	*mlx_win;
	float	player_angle;
	float	player_pos_x;
	float	player_pos_y;
	//raycaster
	float	dist;
	t_vector	mapSize;
	t_vector	voxel;
	t_vector	pPos;
	t_vector	hit;
	t_vector	pDir;
	t_vector	sideDist;
	t_vector	step;
	t_vector	deltaStep;
	int		side;
	t_texture	textures;
	t_image		frame;
}	t_data;

char	*_povAtoi(float	pov);
void	quitC(t_data *gdata);

//utils.c
float	FixAngle(float angle);

//movement.c
int		_input(int keycode, t_data *gdata);

//raycaster.c
int		_checkHit(t_data *gdata); //rmv
void	_raycaster(t_data *gdata);

//images.c
void	_mlx_pPut(t_image *image, int x, int y, int color);
unsigned int	_mlx_get_color(t_image img, int x, int y);
void	_init_textures(t_data *gdata);
int	_wallRescale(t_display *ddata, t_image img, float px, float py);
int _get_pixel_color(t_display *ddata, t_data *gdata, float px, float py);

//3D display
void	_display3D(t_data *gdata, float pov, float dist, int r);
