/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstarts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:05:21 by efreire-          #+#    #+#             */
/*   Updated: 2021/10/23 13:11:25 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_strstarts(char *string, char *substring)
{
	return (ft_strncmp(\
		string, \
		substring, \
		ft_strlen(substring) \
	) == 0);
}
