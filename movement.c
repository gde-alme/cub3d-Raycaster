/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:32:12 by gde-alme          #+#    #+#             */
/*   Updated: 2023/03/15 11:32:14 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

typedef	struct	s_wdata {
	t_vector	wdeltaStep;
	t_vector	wpDir;
	t_vector	wstep;
	t_vector	wsideDist;
	t_vector	wpPos;
    float       nextHit;
}	t_wdata;

//change player pov dir
int	_changeDir(int keycode, t_data *gdata) {
	if (keycode == KEY_LARROW) {
		gdata->player_angle = FixAngle(gdata->player_angle - 2.0F * degree);
		return (1);
	}
	else if (keycode == KEY_RARROW) {
		gdata->player_angle = FixAngle(gdata->player_angle + 2.0F * degree);
		return (2);
	}
	return (0);
}

void	_deltaStepWalk(t_wdata *wdata) {
	if (wdata->wpDir.x == 0.0F)
		wdata->wdeltaStep.x = 1e30;
	else
		wdata->wdeltaStep.x = (1.0F/wdata->wpDir.x);
	if (wdata->wpDir.y == 0.0F)
		wdata->wdeltaStep.y = 1e30;
	else
		wdata->wdeltaStep.y = (1.0F/wdata->wpDir.y);
	if (wdata->wdeltaStep.x < 0.0F)
		wdata->wdeltaStep.x *= -1;
	if (wdata->wdeltaStep.y < 0.0F)
		wdata->wdeltaStep.y *= -1;
}

void	_nextBlock(t_wdata *wdata) {
	if (wdata->wpDir.x < 0.0F) {
		wdata->wsideDist.x = (wdata->wpPos.x - (int)wdata->wpPos.x) * wdata->wdeltaStep.x;
        wdata->wpPos.x += -1.0F;
    }
	else {
		wdata->wsideDist.x = ((int)wdata->wpPos.x + 1 - wdata->wpPos.x) * wdata->wdeltaStep.x;
        wdata->wpPos.x += 1.0F;
    }
	if (wdata->wpDir.y < 0.0F) {
		wdata->wsideDist.y = (wdata->wpPos.y - (int)wdata->wpPos.y) * wdata->wdeltaStep.y;
        wdata->wpPos.y += -1.0F;
	}
	else {
		wdata->wsideDist.y = ((int)wdata->wpPos.y + 1 - wdata->wpPos.y) * wdata->wdeltaStep.y;
        wdata->wpPos.y += 1.0F;
    }
}

void	_init_wdata(t_wdata *wdata, t_data *gdata, float angle) {
	wdata->wdeltaStep.x = 0.0F;
	wdata->wdeltaStep.y = 0.0F;
	wdata->wpDir.x = cos(angle);
	wdata->wpDir.y = sin(angle);
	wdata->wstep.x = 0.0F;
	wdata->wstep.y = 0.0F;
	wdata->wsideDist.x = 0.0F;
	wdata->wsideDist.y = 0.0F;
	wdata->wpPos.x = gdata->player_pos_x;
	wdata->wpPos.y = gdata->player_pos_y;
}

int	_canWalk(int keycode, t_data *gdata, t_wdata *wdata) {
	if (keycode == KEY_W)
		_init_wdata(wdata, gdata, gdata->player_angle);
	else if (keycode == KEY_S)
		_init_wdata(wdata, gdata, FixAngle(gdata->player_angle + (float)PI));
	else if (keycode == KEY_A)
		_init_wdata(wdata, gdata, FixAngle(gdata->player_angle - (float)PI/2.0F));
	else if (keycode == KEY_D)
		_init_wdata(wdata, gdata, FixAngle(gdata->player_angle + (float)PI/2.0F));
	else
		return (-1);
    _deltaStepWalk(wdata);
    _nextBlock(wdata);
	if (wdata->wsideDist.x < wdata->wsideDist.y)
		wdata->nextHit = wdata->wsideDist.x;
	else
		wdata->nextHit = wdata->wsideDist.y;
	wdata->nextHit = 1e30;
	return (0);
}

int	_input(int keycode, t_data *gdata) {
	//if (keycode!=65293){printf("%i",keycode);exit(0);}
	t_wdata	wdata;

	if (gdata->frame.img) {
        mlx_destroy_image(gdata->mlx, gdata->frame.img);
        gdata->frame.img = mlx_new_image(gdata->mlx, 640, 480);
        gdata->frame.addr = mlx_get_data_addr(gdata->frame.img, &gdata->frame.bpp, &gdata->frame.lineS, &gdata->frame.endian);
	}
	if (keycode == 65307)
		quitC(gdata);
	if (_changeDir(keycode, gdata) > 0) {
		_raycaster(gdata);
		mlx_put_image_to_window(gdata->mlx, gdata->mlx_win, gdata->frame.img, 0, 0);
	}
	else if (_canWalk(keycode, gdata, &wdata) == 0) {
		if (wdata.nextHit <= WALKSIZE + SAFEDIST)
			return (0);
		else {
			gdata->player_pos_x += wdata.wpDir.x * (float)WALKSIZE;
			gdata->player_pos_y += wdata.wpDir.y * (float)WALKSIZE;
            		_raycaster(gdata);
					mlx_put_image_to_window(gdata->mlx, gdata->mlx_win, gdata->frame.img, 0, 0);
        	}
	}
	return (0);
}
