/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:36:22 by efreire-          #+#    #+#             */
/*   Updated: 2021/10/23 13:38:57 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_expand(char *str, int len, char c)
{
	int		i;
	int		str_len;
	char	*res;

	str_len = ft_strlen(str);
	if (str_len >= len)
		return (str);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (res);
	i = 0;
	while (i < str_len)
	{
		res[i] = str[i];
		i++;
	}
	free(str);
	while (i < len)
		res[i++] = c;
	res[i] = '\0';
	return (res);
}
