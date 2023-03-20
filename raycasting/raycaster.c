/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:32:56 by gde-alme          #+#    #+#             */
/*   Updated: 2023/03/16 22:32:53 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	_delta_step(t_data *gdata)
{
	if (gdata->p_dir.x > -0.00001 && gdata->p_dir.x < 0.00001)
		gdata->deltastep.x = 1e30;
	else
		gdata->deltastep.x = (1 / gdata->p_dir.x);
	if (gdata->p_dir.y > -0.00001 && gdata->p_dir.y < 0.00001)
		gdata->deltastep.y = 1e30;
	else
		gdata->deltastep.y = (1 / gdata->p_dir.y);
	if (gdata->deltastep.x < -0.00001)
		gdata->deltastep.x *= -1;
	if (gdata->deltastep.y < -0.00001)
		gdata->deltastep.y *= -1;
}

static void	_first_hit(t_data *gdata)
{
	if (gdata->p_dir.x < -0.00001)
	{
		gdata->step.x = -1;
		gdata->sidedist.x = (gdata->p_pos.x - (int)gdata->p_pos.x) \
			* gdata->deltastep.x;
	}
	else
	{
		gdata->step.x = 1;
		gdata->sidedist.x = ((int)gdata->p_pos.x + 1 - gdata->p_pos.x) * \
			gdata->deltastep.x;
	}
	if (gdata->p_dir.y < -0.00001)
	{
		gdata->step.y = -1;
		gdata->sidedist.y = (gdata->p_pos.y - (int)gdata->p_pos.y) * \
			gdata->deltastep.y;
	}
	else
	{
		gdata->step.y = 1;
		gdata->sidedist.y = ((int)gdata->p_pos.y + 1 - \
			gdata->p_pos.y) * gdata->deltastep.y;
	}
}

static void	_dda(t_data *gdata)
{
	gdata->side = -1;
	while (true)
	{
		if (gdata->sidedist.x < gdata->sidedist.y)
		{
			gdata->sidedist.x += gdata->deltastep.x;
			gdata->p_pos.x += gdata->step.x;
			gdata->side = 0;
		}
		else
		{
			gdata->sidedist.y += gdata->deltastep.y;
			gdata->p_pos.y += gdata->step.y;
			gdata->side = 1;
		}
		if (_check_hit(gdata, \
			(int)gdata->p_pos.y, (int)gdata->p_pos.x) > 0)
			break ;
	}
	if (gdata->side == 0)
		gdata->dist = gdata->sidedist.x - gdata->deltastep.x;
	else
		gdata->dist = gdata->sidedist.y - gdata->deltastep.y;
}

static void	_gdata_init(t_data *gdata, float pov)
{
	gdata->sidedist.x = 0;
	gdata->sidedist.y = 0;
	gdata->p_pos.x = gdata->player_pos->x;
	gdata->p_pos.y = gdata->player_pos->y;
	gdata->p_dir.x = cos(pov);
	if (gdata->p_dir.x > -0.00001 && gdata->p_dir.x < 0.00001)
		gdata->p_dir.x *= -1;
	gdata->p_dir.y = sin(pov);
	if (gdata->p_dir.y > -0.00001 && gdata->p_dir.y < 0.00001)
		gdata->p_dir.y *= -1;
}

void	_raycaster(t_data *gdata)
{
	int		r;
	float	pov;

	r = 0;
	pov = fix_angle(gdata->player_angle - (30 * DEGREE));
	while (r < RAYCOUNT)
	{
		_gdata_init(gdata, pov);
		_delta_step(gdata);
		_first_hit(gdata);
		_dda(gdata);
		_gdata_init(gdata, pov);
		_display_3d(gdata, pov, gdata->dist, r);
		pov = fix_angle(pov + (0.25F * DEGREE));
		r++;
	}
}
