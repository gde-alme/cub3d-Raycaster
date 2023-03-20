/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 14:40:23 by efreire-          #+#    #+#             */
/*   Updated: 2021/10/23 14:52:47 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	exceeds_long_value(long num, int next_digit);
static int	get_excess_long_value(int sign);

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		if (exceeds_long_value(res, (str[i] - '0')))
			return (get_excess_long_value(sign));
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

static int	exceeds_long_value(long num, int next_digit)
{
	long	max_value;

	max_value = 922337203685477580;
	return (((num == max_value) && (next_digit >= 8)) || (num > max_value));
}

static int	get_excess_long_value(int sign)
{
	if (sign == 1)
		return (-1);
	else
		return (0);
}
