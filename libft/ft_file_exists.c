/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_exists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:17:08 by efreire-          #+#    #+#             */
/*   Updated: 2021/10/23 13:21:25 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_file_exists(char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY, 0777);
	close(fd);
	if (fd == -1)
		return (false);
	return (true);
}
