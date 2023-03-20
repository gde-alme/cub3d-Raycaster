/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:46:57 by efreire-          #+#    #+#             */
/*   Updated: 2021/10/23 13:52:24 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*new_str;

	i = ft_strlen(str) - 1;
	new_str = (char *) str;
	if ((char)c == '\0')
		return (new_str + i + 1);
	while (i >= 0)
	{
		if (new_str[i] == (char)c)
			return (new_str + i);
		i--;
	}
	return (NULL);
}
