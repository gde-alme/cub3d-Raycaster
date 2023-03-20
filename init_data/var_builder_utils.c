/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_builder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:04:35 by efreire-          #+#    #+#             */
/*   Updated: 2023/01/29 16:04:36 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_var_builder	*var_builder_create(char **var_p, char *code);

void	var_builder_arr_init(t_data *data)
{
	int	size;

	size = sizeof(t_var_builder *) * VAR_BUILDER_ARR_SIZE;
	data->var_builder_arr = (t_var_builder **)malloc(size);
	if (!data->var_builder_arr)
		throw_init_error("Memory allocation fail");
	data->var_builder_arr[0] = var_builder_create(&(data->path_no), "NO ");
	data->var_builder_arr[1] = var_builder_create(&(data->path_so), "SO ");
	data->var_builder_arr[2] = var_builder_create(&(data->path_we), "WE ");
	data->var_builder_arr[3] = var_builder_create(&(data->path_ea), "EA ");
	data->var_builder_arr[4] = var_builder_create(&(data->floor_color), "F ");
	data->var_builder_arr[5] = var_builder_create(&(data->ceiling_color), "C ");
}

void	var_builder_arr_check(t_data *data)
{
	int	i;

	if (!is_var_builder_arr_all_init(data))
		throw_init_error("Missing variable value");
	i = 0;
	while (i < (VAR_BUILDER_ARR_SIZE - 2))
		if (!ft_file_exists(*(data->var_builder_arr[i++]->var_p)))
			throw_init_error("Invalid file path");
	i = VAR_BUILDER_ARR_SIZE - 2;
	while (i < VAR_BUILDER_ARR_SIZE)
	{
		if (!ft_valid_rgb(*(data->var_builder_arr[i]->var_p)))
			throw_init_error("Invalid RGB color value");
		i++;
	}
}

bool	is_var_builder_arr_all_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < VAR_BUILDER_ARR_SIZE)
		if (!data->var_builder_arr[i++]->was_init)
			return (false);
	return (true);
}

static t_var_builder	*var_builder_create(char **var_p, char *code)
{
	t_var_builder	*res;

	res = (t_var_builder *)malloc(sizeof(t_var_builder));
	if (!res)
		throw_init_error("Memory allocation fail");
	res->var_p = var_p;
	res->code = code;
	res->was_init = false;
	return (res);
}
