/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:32:22 by gde-alme          #+#    #+#             */
/*   Updated: 2023/03/16 18:45:42 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	_display_wall(t_data *gdata, t_display *ddata, float x)
{
	float	px;
	float	py;
	float	speed;

	speed = (float)SCRWIDTH / (float)RAYCOUNT;
	px = speed * ddata->r;
	py = ddata->start;
	speed = speed * (ddata->r + 1.0F);
	while (px <= speed && px <= 640.0F)
	{
		while (py >= ddata->end && py >= 0.0F && py <= 480.0F)
		{
			_mlx_pixel_put(&gdata->frame, (int)px, (int)py, \
				_get_pixel_color(ddata, gdata, x, py));
			py--;
		}
		py = ddata->start;
		px++;
	}
}

static	void	_display_floor(t_data *gdata, t_display *ddata)
{
	float	px;
	float	py;
	float	speed;

	speed = (float)SCRWIDTH / (float)RAYCOUNT;
	px = speed * ddata->r;
	py = (float)SCRHEIGHT;
	speed = (float)SCRWIDTH / (float)RAYCOUNT * (ddata->r + 1.0F);
	while ((int)px <= speed && px <= 640.0F)
	{
		while ((int)py > ddata->start && py >= 0.0F)
		{
			_mlx_pixel_put(&gdata->frame, (int)px, (int)py, \
				gdata->floor_color_value);
			py--;
		}
		py = (float)SCRHEIGHT;
		px++;
	}
}

static void	_display_ceiling(t_data *gdata, t_display *ddata)
{
	float	px;
	float	py;
	float	speed;

	speed = (float)SCRWIDTH / (float)RAYCOUNT;
	px = speed * ddata->r;
	py = ddata->end - 1.0F;
	speed = speed * (ddata->r + 1.0F);
	while (px <= speed && px <= 640.0F)
	{
		while (py >= 0.0F)
		{
			_mlx_pixel_put(&gdata->frame, (int)px, (int)py, \
				gdata->ceiling_color_value);
			py--;
		}
		py = ddata->end - 1.0F;
		px++;
	}
}

static void	_init_display(t_display *ddata, float dist, int r, float pov)
{
	ddata->ray_angle = pov;
	ddata->wall_h = (float)(SCRHEIGHT / dist);
	ddata->start = ((float)SCRHEIGHT / 2.0F) + (ddata->wall_h / 2.0F);
	if (ddata->start < 0.0F)
		ddata->start = 0.0F;
	else if (ddata->start > 480.0F)
		ddata->start = 480.0F;
	ddata->end = ((float)SCRHEIGHT / 2.0F) - (ddata->wall_h / 2.0F);
	if (ddata->end < 0.0F)
		ddata->end = 0.0F;
	ddata->rest = 0.0F;
	if (ddata->wall_h > (float)SCRHEIGHT)
	{
		ddata->rest = (ddata->wall_h - (float)SCRHEIGHT);
		ddata->wall_h = (float)SCRHEIGHT;
	}
	ddata->r = (float)r;
}

void	_display_3d(t_data *gdata, float pov, float dist, int r)
{
	float		camera;
	t_display	ddata;
	float		x;

	if (gdata->side == 0)
		x = sin(pov) * dist + gdata->player_pos->y;
	else
		x = cos(pov) * dist + gdata->player_pos->x;
	x = (int)x + 1.0F - x;
	camera = fix_angle(gdata->player_angle - pov);
	dist = dist * cos(camera);
	if (dist < 0.0F)
		dist *= -1;
	_init_display(&ddata, dist, r, pov);
	_display_floor(gdata, &ddata);
	_display_wall(gdata, &ddata, x);
	_display_ceiling(gdata, &ddata);
}
