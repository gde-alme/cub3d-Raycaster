/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:32:22 by gde-alme          #+#    #+#             */
/*   Updated: 2023/03/15 11:32:43 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void	_displayWall(t_data *gdata, t_display *ddata, float x) {
	float	px;
	float	py;
	float	speed;

	speed = (float)screenWidth / (float)RAYCOUNT;
	px = speed * ddata->r;
	py = ddata->start;
	speed = speed * (ddata->r + 1.0F);
	while (px <= speed && px <= 640.0F) {
		while (py >= ddata->end && py >= 0.0F && py <= 480.0F) {
			_mlx_pPut(&gdata->frame, (int)px, (int)py, _get_pixel_color(ddata, gdata, x, py));
			py--;
		}
		py = ddata->start;
		px++;
	}
}

static	void	_displayFloor(t_data *gdata, t_display *ddata) {
	float	px;
	float	py;
	float	speed;

	speed = (float)screenWidth / (float)RAYCOUNT;
	px = speed * ddata->r;
	py = (float)screenHeight;
	speed = (float)screenWidth / (float)RAYCOUNT * (ddata->r + 1.0F);
	while ((int)px <= speed && px <= 640.0F) {
		while ((int)py > ddata->start && py >= 0.0F) {
			_mlx_pPut(&gdata->frame, (int)px, (int)py, BLUE);
			py--;
		}
		py = (float)screenHeight;
		px++;
	}
}

static void	_displayCeiling(t_data *gdata, t_display *ddata) {
	float	px;
	float	py;
	float	speed;

	speed = (float)screenWidth / (float)RAYCOUNT;
	px = speed * ddata->r;
	py = ddata->end - 1.0F;
	speed = speed * (ddata->r + 1.0F);
	while (px <= speed && px <= 640.0F) {
		while (py >= 0.0F) {
			_mlx_pPut(&gdata->frame, (int)px, (int)py, YELLOW);
			py--;
		}
		py = ddata->end - 1.0F;
		px++;
	}
}

static void	_init_display(t_display *ddata, float dist, int r, float pov) {
	ddata->ray_angle = pov;
	ddata->wallH = (float)(screenHeight / dist);
	ddata->start = ((float)screenHeight / 2.0F) + (ddata->wallH / 2.0F);
	if (ddata->start < 0.0F)
		ddata->start = 0.0F;
	else if (ddata->start > 480.0F)
		ddata->start = 480.0F;
	ddata->end = ((float)screenHeight / 2.0F) - (ddata->wallH / 2.0F);
	if (ddata->end < 0.0F)
		ddata->end = 0.0F;
	ddata->rest = 0.0F;
	if (ddata->wallH > (float)screenHeight) {
		ddata->rest = (ddata->wallH - (float)screenHeight);
		ddata->wallH = (float)screenHeight;
	}
	ddata->r = (float)r;
}

void	_display3D(t_data *gdata, float pov, float dist, int r) {
	float	camera;
	t_display	ddata;
	float		x;

	if (gdata->side == 0)
		x = sin(pov)*dist + gdata->player_pos_y;
	else
		x = cos(pov)*dist + gdata->player_pos_x;
	x = (int)x + 1.0F - x;
	camera = FixAngle(gdata->player_angle - pov);
	dist = dist * cos(camera);
	if (dist < 0.0F)
		dist *= -1;
	_init_display(&ddata, dist, r, pov);
	_displayFloor(gdata, &ddata);
	_displayWall(gdata, &ddata, x);
	_displayCeiling(gdata, &ddata);
}