/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:23:00 by efreire-          #+#    #+#             */
/*   Updated: 2021/10/23 15:23:01 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	char		*new_dst;
	const char	*new_src;

	if (dst == NULL && src == NULL)
		return (NULL);
	new_dst = dst;
	new_src = src;
	while (len--)
		*new_dst++ = *new_src++;
	return (dst);
}
