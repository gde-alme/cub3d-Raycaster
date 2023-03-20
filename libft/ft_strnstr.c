/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 14:25:24 by efreire-          #+#    #+#             */
/*   Updated: 2021/10/23 14:37:47 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	len_needle;
	size_t	letters_left;
	char	*new_haystack;

	len_needle = ft_strlen(needle);
	new_haystack = (char *) haystack;
	if (len_needle == 0)
		return (new_haystack);
	i = 0;
	letters_left = len;
	while (new_haystack[i] && (letters_left >= len_needle))
	{
		if (ft_strncmp(needle, (new_haystack + i), len_needle) == 0)
			return (new_haystack + i);
		i++;
		letters_left--;
	}
	return (NULL);
}
