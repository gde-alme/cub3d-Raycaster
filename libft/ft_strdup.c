/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 14:57:46 by efreire-          #+#    #+#             */
/*   Updated: 2021/10/23 15:07:05 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*new_src;
	int		len;

	len = ft_strlen(src);
	new_src = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_src)
		return (NULL);
	while (len >= 0)
	{
		new_src[len] = src[len];
		len--;
	}
	return (new_src);
}
