/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data_base_vars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:29:56 by efreire-          #+#    #+#             */
/*   Updated: 2023/01/28 17:29:58 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	data_base_var_routine(t_data *data, char *line);
static void	data_base_var_routine_1(t_var_builder *var_builder, char *line);
static void	parse_paths(t_data *data);
static void	parse_path(t_data *data, char **path_var);

// Set the 6 base vars (textures and colors)
// Spaces are ignored, trailling chars throws an error
void	set_data_base_vars(int fd, t_data *data)
{
	int		i;
	char	*line;

	var_builder_arr_init(data);
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i = 0;
		while (ft_isspace(line[i]))
			i++;
		if (line[i] != '\0')
			data_base_var_routine(data, line + i);
		free(line);
		if (is_var_builder_arr_all_init(data))
			break ;
	}
	parse_paths(data);
	var_builder_arr_check(data);
	data->floor_color_value = ft_value_rgb(data->floor_color);
	data->ceiling_color_value = ft_value_rgb(data->ceiling_color);
}

// Check which variable to set
// If one isn't set, throws an error
static void	data_base_var_routine(t_data *data, char *line)
{
	int		i;
	bool	was_var_init;

	i = 0;
	was_var_init = false;
	while (i < VAR_BUILDER_ARR_SIZE)
	{
		if (ft_strstarts(line, data->var_builder_arr[i]->code))
		{
			data_base_var_routine_1(data->var_builder_arr[i++], line);
			was_var_init = true;
			break ;
		}
		i++;
	}
	if (!was_var_init)
		throw_init_error("Undefined variable declared");
}

// Set a variable value
static void	data_base_var_routine_1(t_var_builder *var_builder, char *line)
{
	int	i;

	if (var_builder->was_init)
		throw_init_error("Variable declared in duplicate");
	else
	{
		line = (line + ft_strlen(var_builder->code));
		i = 0;
		while (ft_isspace(*line))
			line++;
		while (line[i] && !ft_isspace(line[i]))
			i++;
		if (i == 0)
			throw_init_error("Invalid variable value (empty string)");
		*(var_builder->var_p) = ft_substr(line, 0, i);
		var_builder->was_init = true;
		while (line[i])
			if (!ft_isspace(line[i++]))
				throw_init_error("Invalid variable value (spaces in-between)");
	}
}

// Add the executable path to the relative path of all path vars
static void	parse_paths(t_data *data)
{
	parse_path(data, &data->path_ea);
	parse_path(data, &data->path_no);
	parse_path(data, &data->path_so);
	parse_path(data, &data->path_we);
}

// Add the executable path to the relative path of a var
static void	parse_path(t_data *data, char **path_var)
{
	char	*temp;

	temp = ft_strjoin(data->exec_path, *path_var);
	free(*path_var);
	*path_var = temp;
}
