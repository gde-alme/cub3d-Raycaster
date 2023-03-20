/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:33:39 by gde-alme          #+#    #+#             */
/*   Updated: 2023/03/16 23:15:03 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	fix_angle(float angle)
{
	if (angle <= 0)
		return ((float)(angle + 2 * PI));
	else if (angle >= (float)(2 * PI))
		return ((float)(angle - 2 * PI));
	return (angle);
}

int	_get_pixel_color(t_display *ddata, t_data *gdata, float px, float py)
{
	if (ddata->ray_angle < EAST)
	{
		if (gdata->side == 1)
			return (_wall_rescale(ddata, gdata->textures.southwall, px, py));
		else if (ddata->ray_angle < (float)SOUTH)
			return (_wall_rescale(ddata, gdata->textures.eastwall, px, py));
		else
			return (_wall_rescale(ddata, gdata->textures.westwall, px, py));
	}
	else
	{
		if (gdata->side == 1)
			return (_wall_rescale(ddata, gdata->textures.northwall, px, py));
		else if (ddata->ray_angle < (float)NORTH)
			return (_wall_rescale(ddata, gdata->textures.westwall, px, py));
		else
			return (_wall_rescale(ddata, gdata->textures.eastwall, px, py));
	}
	return (-1);
}

static int	_try_walk(int keycode, t_data *gdata, t_wdata *wdata)
{
	t_vector	next_step;

	if (_can_walk(keycode, gdata, wdata) == 0)
	{
		next_step.x = gdata->player_pos->x + wdata->wp_dir.x * (float)WALKSIZE;
		next_step.y = gdata->player_pos->y + wdata->wp_dir.y * (float)WALKSIZE;
		if (_check_hit(gdata, (int)next_step.y, (int)next_step.x) > 0)
			return (1);
		gdata->player_pos->x = next_step.x;
		gdata->player_pos->y = next_step.y;
		_raycaster(gdata);
		mlx_put_image_to_window(gdata->mlx, gdata->mlx_win, \
		gdata->frame.img, 0, 0);
	}
	return (0);
}

int	_input(int keycode, t_data *gdata)
{
	t_wdata	wdata;

	if (gdata->frame.img)
	{
		mlx_destroy_image(gdata->mlx, gdata->frame.img);
		gdata->frame.img = mlx_new_image(gdata->mlx, 640, 480);
		gdata->frame.addr = mlx_get_data_addr(gdata->frame.img, \
			&gdata->frame.bpp, &gdata->frame.line_s, &gdata->frame.endian);
	}
	if (keycode == 65307)
		quit_game(gdata);
	if (_change_dir(keycode, gdata) > 0)
	{
		_raycaster(gdata);
		mlx_put_image_to_window(gdata->mlx, gdata->mlx_win, \
			gdata->frame.img, 0, 0);
	}
	else
		return (_try_walk(keycode, gdata, &wdata));
	return (0);
}

int	_check_hit(t_data *gdata, int y, int x)
{
	if (gdata->map[y][x] != '0')
		return (1);
	else
		return (0);
}
