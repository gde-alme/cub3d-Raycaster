/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_value_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:17:08 by efreire-          #+#    #+#             */
/*   Updated: 2021/10/23 13:21:25 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_single_value(char *str, int start, int len);

unsigned long	ft_value_rgb(char *str)
{
	int				i;
	int				j;
	int				k;
	unsigned long	res;

	if (!ft_valid_rgb(str))
		return (0);
	i = 0;
	j = 0;
	k = 0;
	res = 0;
	while (i < 3)
	{
		if (str[j] == ',')
			j++;
		while (ft_isdigit(str[j + k]))
			k++;
		res += get_single_value(str, j, k) * ft_pow(256, 2 - i);
		j += k;
		k = 0;
		i++;
	}
	return (res);
}

static int	get_single_value(char *str, int start, int len)
{
	char	*test_str;
	int		test_num;

	test_str = ft_substr(str, start, len);
	if (!test_str)
		return (false);
	test_num = ft_atoi(test_str);
	free(test_str);
	return (test_num);
}
