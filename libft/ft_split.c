/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 17:46:08 by efreire-          #+#    #+#             */
/*   Updated: 2021/10/23 17:46:10 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_words(char const *str, char sep);
static char	*get_next_word(char const *str, char sep, int *pos_str);

char	**ft_split(char const *str, char c)
{
	char	**res;
	char	*word;
	int		i;
	int		*pos_str;
	int		pos_res;

	if (str == NULL)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * (str_words(str, c) + 1));
	if (!res)
		return (NULL);
	i = 0;
	pos_str = &i;
	pos_res = 0;
	while (pos_res < str_words(str, c))
	{
		word = get_next_word(str, c, pos_str);
		if (!word)
			break ;
		res[pos_res++] = word;
	}
	res[pos_res] = NULL;
	return (res);
}

static int	str_words(char const *str, char sep)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i] == '\0')
			break ;
		while (str[i] && str[i] != sep)
			i++;
		res++;
	}
	return (res);
}

static char	*get_next_word(char const *str, char sep, int *pos_str)
{
	char	*res;
	int		len_res;
	int		i;

	while (str[*pos_str] == sep)
		if (str[(*pos_str)++] == '\0')
			return (NULL);
	len_res = 0;
	while (str[*pos_str + len_res] && str[*pos_str + len_res] != sep)
		len_res++;
	if (len_res == 0)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (len_res + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len_res)
		res[i++] = str[(*pos_str)++];
	res[i] = '\0';
	return (res);
}
