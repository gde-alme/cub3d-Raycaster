/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:53:55 by efreire-          #+#    #+#             */
/*   Updated: 2021/10/23 13:58:57 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t len)
{
	char	c1;
	char	c2;

	while (len--)
	{
		c1 = *str1++;
		c2 = *str2++;
		if (c1 != c2)
			return ((unsigned char)c1 - (unsigned char)c2);
		if (!c1)
			break ;
	}
	return (0);
}
