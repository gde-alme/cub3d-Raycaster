/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_find_last.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:15:33 by efreire-          #+#    #+#             */
/*   Updated: 2021/10/23 13:16:24 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_find_last(const char *haystack, const char needle)
{
	int	i;

	i = ft_strlen(haystack);
	while (i >= 0)
	{
		if (haystack[i] == needle)
			break ;
		i--;
	}
	return (i);
}
