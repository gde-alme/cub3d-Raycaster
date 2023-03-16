/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:33:18 by gde-alme          #+#    #+#             */
/*   Updated: 2023/03/15 17:35:00 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	quitC(t_data *gdata) {
	mlx_destroy_image(gdata->mlx, gdata->textures.northWall.img);
	mlx_destroy_image(gdata->mlx, gdata->textures.southWall.img);
	mlx_destroy_image(gdata->mlx, gdata->textures.westWall.img);
	mlx_destroy_image(gdata->mlx, gdata->textures.eastWall.img);
	mlx_clear_window(gdata->mlx, gdata->mlx_win);
	mlx_destroy_window(gdata->mlx, gdata->mlx_win);
	mlx_destroy_display(gdata->mlx);
	if (gdata->mlx)
		free(gdata->mlx);
	exit(0);
}

int	main(int argc, char **argv, char **env) {
	(void *)argv;
	(void *)env;

	t_data	gdata;

	//init mlx & vars
	gdata.mlx = mlx_init();
	gdata.mlx_win = mlx_new_window(gdata.mlx, screenWidth, screenHeight, "3Draycaster");
	gdata.player_angle = (float)EAST;// + (2*degree);
	gdata.mapSize.x = mapWidth;
	gdata.mapSize.y = mapHeight;
	gdata.voxel.x = screenWidth / mapWidth;
	gdata.voxel.y = screenHeight / mapHeight;

	gdata.player_pos_x = 1.5F;
	gdata.player_pos_y = 1.5F;

	gdata.frame.img = mlx_new_image(gdata.mlx, 640, 480);
	gdata.frame.addr = mlx_get_data_addr(gdata.frame.img, &gdata.frame.bpp, &gdata.frame.lineS, &gdata.frame.endian);

	_init_textures(&gdata);

	_raycaster(&gdata);
	mlx_put_image_to_window(gdata.mlx, gdata.mlx_win, gdata.frame.img, 0, 0);
	mlx_hook(gdata.mlx_win, 2, 1L<<0, _input, &gdata);
	mlx_do_key_autorepeaton(gdata.mlx);
	mlx_loop(gdata.mlx);
}
