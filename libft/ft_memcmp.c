/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:37:48 by efreire-          #+#    #+#             */
/*   Updated: 2021/10/23 15:37:49 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t len)
{
	unsigned char	*new_str1;
	unsigned char	*new_str2;
	size_t			i;

	new_str1 = (unsigned char *) str1;
	new_str2 = (unsigned char *) str2;
	i = 0;
	while (i < len)
	{
		if (new_str1[i] != new_str2[i])
			return (new_str1[i] - new_str2[i]);
		i++;
	}
	return (0);
}
