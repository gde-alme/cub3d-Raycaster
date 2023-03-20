/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:51:02 by efreire-          #+#    #+#             */
/*   Updated: 2021/10/23 15:51:07 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*temp;
	const char	*new_src;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst <= src)
		ft_memcpy(dst, src, len);
	else
	{
		temp = dst;
		temp += len;
		new_src = src;
		new_src += len;
		while (len--)
			*--temp = *--new_src;
	}
	return (dst);
}
