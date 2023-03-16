/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:33:18 by gde-alme          #+#    #+#             */
/*   Updated: 2023/03/16 18:53:44 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	quit_game(t_data *gdata)
{
	mlx_destroy_image(gdata->mlx, gdata->textures.northwall.img);
	mlx_destroy_image(gdata->mlx, gdata->textures.southwall.img);
	mlx_destroy_image(gdata->mlx, gdata->textures.westwall.img);
	mlx_destroy_image(gdata->mlx, gdata->textures.eastwall.img);
	mlx_clear_window(gdata->mlx, gdata->mlx_win);
	mlx_destroy_window(gdata->mlx, gdata->mlx_win);
	mlx_destroy_display(gdata->mlx);
	if (gdata->mlx)
		free(gdata->mlx);
	exit(0);
}

int	_event_destroy(t_data *gdata)
{
	quit_game(gdata);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	gdata;

	(void *)argv;
	(void *)env;
	gdata.mlx = mlx_init();
	gdata.mlx_win = mlx_new_window(gdata.mlx, SCRWIDTH, SCRHEIGHT, "cub3d");
	gdata.player_angle = (float)EAST;
	gdata.mapsize.x = mapWidth;
	gdata.mapsize.y = mapHeight;
	gdata.voxel.x = SCRWIDTH / mapWidth;
	gdata.voxel.y = SCRHEIGHT / mapHeight;
	gdata.player_pos_x = 1.5F;
	gdata.player_pos_y = 1.5F;
	gdata.frame.img = mlx_new_image(gdata.mlx, 640, 480);
	gdata.frame.addr = mlx_get_data_addr(gdata.frame.img, &gdata.frame.bpp, \
		&gdata.frame.line_s, &gdata.frame.endian);
	_init_textures(&gdata);
	_raycaster(&gdata);
	mlx_put_image_to_window(gdata.mlx, gdata.mlx_win, gdata.frame.img, 0, 0);
	mlx_hook(gdata.mlx_win, 2, 1L << 0, _input, &gdata);
	mlx_hook(gdata.mlx_win, 17, 0L, _event_destroy, &gdata);
	mlx_do_key_autorepeaton(gdata.mlx);
	mlx_loop(gdata.mlx);
}
