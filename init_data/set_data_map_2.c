/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data_map_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:29:56 by efreire-          #+#    #+#             */
/*   Updated: 2023/01/28 17:29:58 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_data_map(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map_rows)
		printf("%s\n", data->map[i++]);
}

bool	is_map_str_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (!is_map_char_valid(str[i++]))
			return (false);
	return (true);
}

bool	is_map_char_valid(char c)
{
	return (c == ' ' || c == '0' || c == '1' || \
		is_char_player(c) || c == '\n');
}

bool	is_char_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	data_map_check(t_data *data)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (i < data->map_rows)
	{
		j = 0;
		while (j < data->map_cols)
		{
			if (is_char_player(data->map[i][j]))
			{
				player_count++;
				data->player_pos->y = (float)i + 0.5F;
				data->player_pos->x = (float)j + 0.5F;
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		throw_init_error("Need one, and only one, player starting position");
	set_player_angle(data);
	check_map_walls(data, (int)data->player_pos->y, (int)data->player_pos->x);
}
