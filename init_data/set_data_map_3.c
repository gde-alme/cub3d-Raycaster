/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data_map_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:29:56 by efreire-          #+#    #+#             */
/*   Updated: 2023/01/28 17:29:58 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_map_walls_recursive(t_data *data, int y, int x);

void	set_player_angle(t_data *gdata)
{
	char	player;

	player = gdata->map[(int)gdata->player_pos->y][(int)gdata->player_pos->x];
	if (player == 'N')
		gdata->player_angle = (float)NORTH;
	else if (player == 'S')
		gdata->player_angle = (float)SOUTH;
	else if (player == 'W')
		gdata->player_angle = (float)WEST;
	else
		gdata->player_angle = (float)EAST;
}

void	check_map_walls(t_data *data, int y, int x)
{
	int	i;

	check_map_walls_recursive(data, y, x);
	i = 0;
	while (i < data->map_rows)
		ft_replace(data->map[i++], 'V', '0');
}

static void	check_map_walls_recursive(t_data *data, int y, int x)
{
	if ((y < 0) || (y >= data->map_rows) || (x < 0) || (x >= data->map_cols))
		throw_init_error("Map not enclosed by walls");
	if ((data->map[y][x] == '0') || is_char_player(data->map[y][x]))
	{
		data->map[y][x] = 'V';
		check_map_walls_recursive(data, y - 1, x);
		check_map_walls_recursive(data, y + 1, x);
		check_map_walls_recursive(data, y, x - 1);
		check_map_walls_recursive(data, y, x + 1);
	}
}
