/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:29:56 by efreire-          #+#    #+#             */
/*   Updated: 2023/01/28 17:29:58 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_vector	*create_position(void);
static void		parse_file(t_data *data, char *filepath);

// Init the data struct with the relevant variables
t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	if (argc <= 1)
		throw_init_error("No arguments");
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		throw_init_error("Memory allocation fail");
	data->exec_path = "./";
	data->player_pos = create_position();
	parse_file(data, argv[1]);
	return (data);
}

// Throws the standard error referenced by the subject
void	throw_init_error(char *message)
{
	printf("Error\n");
	printf("%s\n", message);
	exit(1);
}

static t_vector	*create_position(void)
{
	t_vector	*res;

	res = (t_vector *)malloc(sizeof(t_vector));
	if (!res)
		throw_init_error("Memory allocation fail");
	res->y = (float)0;
	res->x = (float)0;
	return (res);
}

// Parse the file to set the data struct variables
static void	parse_file(t_data *data, char *filepath)
{
	int		fd;
	int		i;

	if (!ft_strends(filepath, ".cub"))
		throw_init_error("Invalid argument (does not have the .cub extension)");
	fd = open(filepath, O_RDONLY, 0777);
	if (fd == -1)
	{
		close(fd);
		throw_init_error("Invalid argument");
	}
	i = ft_str_find_last(filepath, '/');
	if (i >= 0)
		data->exec_path = ft_substr(filepath, 0, i + 1);
	set_data_base_vars(fd, data);
	set_data_map(fd, data);
}
