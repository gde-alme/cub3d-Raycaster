/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:32:56 by gde-alme          #+#    #+#             */
/*   Updated: 2023/03/15 11:32:57 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include "worldMap.h"

int	_checkHit(t_data *gdata) {
	if (worldMap[(int)gdata->pPos.y][(int)gdata->pPos.x] > 0)
		return (1);
	else
		return (0);
}

static void	_deltaStep(t_data *gdata) {
	if (gdata->pDir.x > -0.00001 && gdata->pDir.x < 0.00001)
		gdata->deltaStep.x = 1e30;
	else
		gdata->deltaStep.x = (1/gdata->pDir.x);
	if (gdata->pDir.y > -0.00001 && gdata->pDir.y < 0.00001)
		gdata->deltaStep.y = 1e30;
	else
		gdata->deltaStep.y = (1/gdata->pDir.y);
	if (gdata->deltaStep.x < -0.00001)
		gdata->deltaStep.x *= -1;
	if (gdata->deltaStep.y < -0.00001)
		gdata->deltaStep.y *= -1;
}

static void	_firstHit(t_data *gdata) {
	if (gdata->pDir.x < -0.00001) {
		gdata->step.x = -1;
		gdata->sideDist.x = (gdata->pPos.x - (int)gdata->pPos.x) * gdata->deltaStep.x;
	}
	else {
		gdata->step.x = 1;
		gdata->sideDist.x = ((int)gdata->pPos.x + 1 - gdata->pPos.x) * gdata->deltaStep.x;
	}
	if (gdata->pDir.y < -0.00001) {
		gdata->step.y = -1;
		gdata->sideDist.y = (gdata->pPos.y - (int)gdata->pPos.y) * gdata->deltaStep.y;
	}
	else {
		gdata->step.y = 1;
		gdata->sideDist.y = ((int)gdata->pPos.y + 1 - gdata->pPos.y) * gdata->deltaStep.y;
	}
}

static void	_dda(t_data *gdata) {
	int	hit;

	hit = 0;
	gdata->side = -1;
	while (hit == 0) {
		if (gdata->sideDist.x < gdata->sideDist.y) {
			gdata->sideDist.x += gdata->deltaStep.x;
			gdata->pPos.x += gdata->step.x;
			gdata->side = 0;
		}
		else {
			gdata->sideDist.y += gdata->deltaStep.y;
			gdata->pPos.y += gdata->step.y;
			gdata->side = 1;
		}
		if (_checkHit(gdata) > 0)
			hit = 1;
	}
	if (gdata->side == 0)
		gdata->dist = gdata->sideDist.x - gdata->deltaStep.x;
	else
		gdata->dist = gdata->sideDist.y - gdata->deltaStep.y;
}

static void	_gdata_init(t_data *gdata, float pov) {
	gdata->sideDist.x = 0;
	gdata->sideDist.y = 0;
	gdata->pPos.x = gdata->player_pos_x;
	gdata->pPos.y = gdata->player_pos_y;
	gdata->pDir.x = cos(pov);
	if (gdata->pDir.x > -0.00001 && gdata->pDir.x < 0.00001)
		gdata->pDir.x *= -1;
	gdata->pDir.y = sin(pov);
	if (gdata->pDir.y > -0.00001 && gdata->pDir.y < 0.00001)
		gdata->pDir.y *= -1;
}

void	_raycaster(t_data *gdata) {
	int	r;
	float	pov;
	r = 0;
	pov = FixAngle(gdata->player_angle - (30*degree));
	while (r < RAYCOUNT) {
		_gdata_init(gdata, pov);
		_deltaStep(gdata);
		_firstHit(gdata);
		_dda(gdata);
		_gdata_init(gdata, pov);
		_display3D(gdata, pov, gdata->dist, r);
		pov = FixAngle(pov + (0.25F * degree));
		r++;
	}
}
