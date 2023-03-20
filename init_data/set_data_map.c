/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:29:56 by efreire-          #+#    #+#             */
/*   Updated: 2023/01/28 17:29:58 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	data_map_routine(t_data *data, char *line, bool *is_end_of_file);
static bool	set_data_map_line(t_data *data, char *line);
static void	add_line_to_map(t_data *data, char *line, int len);
static void	parse_map(t_data *data);

// Set the map variable
void	set_data_map(int fd, t_data *data)
{
	char	*line;
	bool	is_end_of_file;

	is_end_of_file = false;
	data->map = NULL;
	data->map_rows = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (!line || !ft_isstrspace(line))
			break ;
		free(line);
	}
	while (true)
	{
		if (!line)
			break ;
		data_map_routine(data, line, &is_end_of_file);
		free(line);
		line = get_next_line(fd);
	}
	parse_map(data);
	data_map_check(data);
}
// print_data_map(data);

// Add a line to the map
// When the map ends, check if the trailing lines are space only
static void	data_map_routine(t_data *data, char *line, bool *is_end_of_file)
{
	if (\
		(*is_end_of_file && !ft_isstrspace(line)) || \
		(!*is_end_of_file && !is_map_str_valid(line)) \
	)
	{
		free(line);
		throw_init_error("Invalid map");
	}
	if (!*is_end_of_file && !set_data_map_line(data, line))
	{
		if (ft_isstrspace(line))
			*is_end_of_file = true;
		else
		{
			free(line);
			throw_init_error("Invalid map");
		}
	}
}

// Check if the line is valid
// If valid, add it to the map
static bool	set_data_map_line(t_data *data, char *line)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	if ((len < 1) || ft_isstrspace(line))
		return (false);
	add_line_to_map(data, line, len);
	return (true);
}

// Add a line to the map
static void	add_line_to_map(t_data *data, char *line, int len)
{
	char	**new_map;
	int		i;

	data->map_rows++;
	new_map = (char **)malloc(sizeof(char *) * data->map_rows);
	if (!new_map)
		throw_init_error("Memory allocation fail");
	i = 0;
	while (i < (data->map_rows - 1))
	{
		new_map[i] = data->map[i];
		i++;
	}
	free(data->map);
	new_map[i] = ft_substr(line, 0, len);
	data->map = new_map;
}

static void	parse_map(t_data *data)
{
	int	i;

	i = 0;
	data->map_cols = 0;
	while (i < data->map_rows)
	{
		if ((int)ft_strlen(data->map[i]) > data->map_cols)
			data->map_cols = ft_strlen(data->map[i]);
		ft_replace(data->map[i], ' ', '0');
		i++;
	}
	i = 0;
	while (i < data->map_rows)
	{
		data->map[i] = ft_str_expand(data->map[i], data->map_cols, '0');
		i++;
	}
}
