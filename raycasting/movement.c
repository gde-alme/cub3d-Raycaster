/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:32:12 by gde-alme          #+#    #+#             */
/*   Updated: 2023/03/16 22:48:28 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//change player pov dir
int	_change_dir(int keycode, t_data *gdata)
{
	if (keycode == KEY_LARROW)
	{
		gdata->player_angle = fix_angle(gdata->player_angle - 2.0F * DEGREE);
		return (1);
	}
	else if (keycode == KEY_RARROW)
	{
		gdata->player_angle = fix_angle(gdata->player_angle + 2.0F * DEGREE);
		return (2);
	}
	return (0);
}

void	_delta_step_walk(t_wdata *wdata)
{
	if (wdata->wp_dir.x == 0.0F)
		wdata->wdeltastep.x = 1e30;
	else
		wdata->wdeltastep.x = (1.0F / wdata->wp_dir.x);
	if (wdata->wp_dir.y == 0.0F)
		wdata->wdeltastep.y = 1e30;
	else
		wdata->wdeltastep.y = (1.0F / wdata->wp_dir.y);
	if (wdata->wdeltastep.x < 0.0F)
		wdata->wdeltastep.x *= -1;
	if (wdata->wdeltastep.y < 0.0F)
		wdata->wdeltastep.y *= -1;
}

void	_next_block(t_wdata *wdata)
{
	if (wdata->wp_dir.x < 0.0F)
	{
		wdata->wsidedist.x = (wdata->wp_pos.x - \
			(int)wdata->wp_pos.x) * wdata->wdeltastep.x;
		wdata->wp_pos.x += -1.0F;
	}
	else
	{
		wdata->wsidedist.x = ((int)wdata->wp_pos.x + 1 - \
			wdata->wp_pos.x) * wdata->wdeltastep.x;
		wdata->wp_pos.x += 1.0F;
	}
	if (wdata->wp_dir.y < 0.0F)
	{
		wdata->wsidedist.y = (wdata->wp_pos.y - \
			(int)wdata->wp_pos.y) * wdata->wdeltastep.y;
		wdata->wp_pos.y += -1.0F;
	}
	else
	{
		wdata->wsidedist.y = ((int)wdata->wp_pos.y + \
			1 - wdata->wp_pos.y) * wdata->wdeltastep.y;
		wdata->wp_pos.y += 1.0F;
	}
}

void	_init_wdata(t_wdata *wdata, t_data *gdata, float angle)
{
	wdata->wdeltastep.x = 0.0F;
	wdata->wdeltastep.y = 0.0F;
	wdata->wp_dir.x = cos(angle);
	wdata->wp_dir.y = sin(angle);
	wdata->wstep.x = 0.0F;
	wdata->wstep.y = 0.0F;
	wdata->wsidedist.x = 0.0F;
	wdata->wsidedist.y = 0.0F;
	wdata->wp_pos.x = gdata->player_pos->x;
	wdata->wp_pos.y = gdata->player_pos->y;
}

int	_can_walk(int keycode, t_data *gdata, t_wdata *wdata)
{
	if (keycode == KEY_W)
		_init_wdata(wdata, gdata, gdata->player_angle);
	else if (keycode == KEY_S)
		_init_wdata(wdata, gdata, fix_angle(gdata->player_angle + (float)PI));
	else if (keycode == KEY_A)
		_init_wdata(wdata, gdata, fix_angle(gdata->player_angle - \
			(float)PI / 2.0F));
	else if (keycode == KEY_D)
		_init_wdata(wdata, gdata, fix_angle(gdata->player_angle + \
			(float)PI / 2.0F));
	else
		return (-1);
	_delta_step_walk(wdata);
	_next_block(wdata);
	if (wdata->wsidedist.x < wdata->wsidedist.y)
		wdata->nexthit = wdata->wsidedist.x;
	else
		wdata->nexthit = wdata->wsidedist.y;
	return (0);
}
