/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:32:18 by gde-alme          #+#    #+#             */
/*   Updated: 2023/03/15 17:36:00 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void    _mlx_pPut(t_image *image, int x, int y, int color) {
    char    *dst;

    dst = image->addr + (y * image->lineS + x * (image->bpp / 8));
    *(unsigned int *)dst = color;
}

unsigned int    _mlx_get_color(t_image img, int x, int y) {
    return (*(unsigned int *)(img.addr + (y * img.lineS + x * (img.bpp / 8))));
}

void    _init_textures(t_data *gdata) {
    gdata->textures.northWall.img = mlx_xpm_file_to_image(gdata->mlx, "imgs/northwall.xpm", \
       &gdata->textures.northWall.width, &gdata->textures.northWall.height);
    gdata->textures.northWall.addr = mlx_get_data_addr(gdata->textures.northWall.img, \
        &gdata->textures.northWall.bpp, &gdata->textures.northWall.lineS, &gdata->textures.northWall.endian);
    gdata->textures.southWall.img = mlx_xpm_file_to_image(gdata->mlx, "imgs/southwall.xpm", \
        &gdata->textures.southWall.width, &gdata->textures.southWall.height);
    gdata->textures.southWall.addr = mlx_get_data_addr(gdata->textures.southWall.img, \
        &gdata->textures.southWall.bpp, &gdata->textures.southWall.lineS, &gdata->textures.southWall.endian);
    gdata->textures.westWall.img = mlx_xpm_file_to_image(gdata->mlx, "imgs/westWall.xpm", \
        &gdata->textures.westWall.width, &gdata->textures.westWall.height);
    gdata->textures.westWall.addr = mlx_get_data_addr(gdata->textures.westWall.img, \
        &gdata->textures.westWall.bpp, &gdata->textures.westWall.lineS, &gdata->textures.westWall.endian);
    gdata->textures.eastWall.img = mlx_xpm_file_to_image(gdata->mlx, "imgs/eastWall.xpm", \
        &gdata->textures.eastWall.width, &gdata->textures.eastWall.height);
    gdata->textures.eastWall.addr = mlx_get_data_addr(gdata->textures.eastWall.img, \
        &gdata->textures.eastWall.bpp, &gdata->textures.eastWall.lineS, &gdata->textures.eastWall.endian);
}

int	_wallRescale(t_display *ddata, t_image img, float px, float py) {
	t_vector	imgStep;
    float   ok;

	imgStep.y = (float)img.height / ddata->wallH;
	if (ddata->rest > 0.0F) {
		imgStep.y = (float)img.height / (ddata->wallH + ddata->rest);
		ok = (ddata->rest / 2.0F);
        return ((int)_mlx_get_color(img, (int)(px * (float)img.width), (int)((py - ddata->end + ok) * imgStep.y)));
	}
    return ((int)_mlx_get_color(img, (int)(px * (float)img.width), (int)((py - ddata->end) * imgStep.y)));
}

int _get_pixel_color(t_display *ddata, t_data *gdata, float px, float py) {
    //printf("rangle: %f side: %i\n", ddata->ray_angle, gdata->side);
    if (ddata->ray_angle > EAST) {
        if (gdata->side == 1)
            return (_wallRescale(ddata, gdata->textures.southWall, px, py));
        else if (ddata->ray_angle < (float)SOUTH)
            return (_wallRescale(ddata, gdata->textures.westWall, px, py));
        else
            return (_wallRescale(ddata, gdata->textures.eastWall, px, py));
    }
    else {
        if (gdata->side == 1)
            return (_wallRescale(ddata, gdata->textures.northWall, px, py));
        else if (ddata->ray_angle < (float)NORTH)
            return (_wallRescale(ddata, gdata->textures.eastWall, px, py));
        else
            return (_wallRescale(ddata, gdata->textures.westWall, px, py));
    }
    return (-1);
}