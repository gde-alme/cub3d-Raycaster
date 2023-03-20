/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:32:18 by gde-alme          #+#    #+#             */
/*   Updated: 2023/03/16 18:34:05 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_s + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	_mlx_get_color(t_image img, int x, int y)
{
	return (*(unsigned int *)(img.addr + (y * img.line_s + x * (img.bpp / 8))));
}

void	_init_textures_norm(t_data *gdata)
{
	gdata->textures.westwall.img = mlx_xpm_file_to_image(gdata->mlx, \
		gdata->path_we, &gdata->textures.westwall.width, \
		&gdata->textures.westwall.height);
	gdata->textures.westwall.addr = \
	mlx_get_data_addr(gdata->textures.westwall.img, \
		&gdata->textures.westwall.bpp, \
		&gdata->textures.westwall.line_s, &gdata->textures.westwall.endian);
	gdata->textures.eastwall.img = mlx_xpm_file_to_image(gdata->mlx, \
	gdata->path_ea, &gdata->textures.eastwall.width, \
		&gdata->textures.eastwall.height);
	gdata->textures.eastwall.addr = \
	mlx_get_data_addr(gdata->textures.eastwall.img, \
		&gdata->textures.eastwall.bpp, \
		&gdata->textures.eastwall.line_s, &gdata->textures.eastwall.endian);
}

void	_init_textures(t_data *gdata)
{
	gdata->textures.northwall.img = mlx_xpm_file_to_image(gdata->mlx, \
		gdata->path_no, &gdata->textures.northwall.width, \
			&gdata->textures.northwall.height);
	gdata->textures.northwall.addr = \
	mlx_get_data_addr(gdata->textures.northwall.img, \
		&gdata->textures.northwall.bpp, \
		&gdata->textures.northwall.line_s, &gdata->textures.northwall.endian);
	gdata->textures.southwall.img = mlx_xpm_file_to_image(gdata->mlx, \
		gdata->path_so, &gdata->textures.southwall.width, \
			&gdata->textures.southwall.height);
	gdata->textures.southwall.addr = \
	mlx_get_data_addr(gdata->textures.southwall.img, \
		&gdata->textures.southwall.bpp, \
		&gdata->textures.southwall.line_s, &gdata->textures.southwall.endian);
	_init_textures_norm(gdata);
}

int	_wall_rescale(t_display *ddata, t_image img, float px, float py)
{
	t_vector	imgstep;
	float		ok;

	imgstep.y = (float)img.height / ddata->wall_h;
	if (ddata->rest > 0.0F)
	{
		imgstep.y = (float)img.height / (ddata->wall_h + ddata->rest);
		ok = (ddata->rest / 2.0F);
		return ((int)_mlx_get_color(img, (int)(px * (float)img.width), \
			(int)((py - ddata->end + ok) * imgstep.y)));
	}
	return ((int)_mlx_get_color(img, (int)(px * (float)img.width), \
		(int)((py - ddata->end) * imgstep.y)));
}
