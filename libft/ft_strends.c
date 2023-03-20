/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strends.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:05:21 by efreire-          #+#    #+#             */
/*   Updated: 2021/10/23 13:11:25 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_strends(char *string, char *substring)
{
	int	str_len;
	int	substr_len;

	str_len = ft_strlen(string);
	substr_len = ft_strlen(substring);
	if (str_len < substr_len)
		return (false);
	return (ft_strncmp(\
		string + str_len - substr_len, \
		substring, \
		ft_strlen(substring) \
	) == 0);
}
