/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:17:08 by efreire-          #+#    #+#             */
/*   Updated: 2021/10/23 13:21:25 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	routine(char *str, int *i, int *j, int *k);
static bool	initial_test(char *str);
static bool	is_value_valid(char *str, int start, int len);

bool	ft_valid_rgb(char *str)
{
	int	i;
	int	j;
	int	k;

	if (!initial_test(str))
		return (false);
	i = 0;
	j = 0;
	k = 0;
	while (i < 3)
		if (!routine(str, &i, &j, &k))
			return (false);
	return (true);
}

static bool	routine(char *str, int *i, int *j, int *k)
{
	if (str[(*j)] == ',')
	{
		if (*i == 0)
			return (false);
		(*j)++;
	}
	while (ft_isdigit(str[*j + *k]))
		(*k)++;
	if (!is_value_valid(str, *j, *k))
		return (false);
	*j += *k;
	*k = 0;
	(*i)++;
	return (true);
}

/*
	1. Check if only the valid characters are in the string (digits and commas);
	2. Check if it has 2 commas.
*/
static bool	initial_test(char *str)
{
	int	i;
	int	num_commas;

	i = 0;
	num_commas = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			if (str[i] == ',')
				num_commas++;
			else
				return (false);
		}
		i++;
	}
	return (num_commas == 2);
}

/*
	Check if the RGB num is between 0 and 255.
*/
static bool	is_value_valid(char *str, int start, int len)
{
	char	*test_str;
	int		test_num;

	test_str = ft_substr(str, start, len);
	if (!test_str)
		return (false);
	test_num = ft_atoi(test_str);
	free(test_str);
	return ((test_num >= 0) && (test_num <= 255));
}
