/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:14:45 by efreire-          #+#    #+#             */
/*   Updated: 2021/10/23 15:14:47 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	unsigned char	*new_str;
	size_t			i;

	new_str = (unsigned char *) str;
	i = 0;
	while (i < len)
		new_str[i++] = (unsigned char) c;
	return (str);
}
