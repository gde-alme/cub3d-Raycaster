/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 17:52:38 by efreire-          #+#    #+#             */
/*   Updated: 2021/10/23 17:52:43 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen(int n);

char	*ft_itoa(int n)
{
	char		*res;
	int			len_n;
	int			i;
	int long	new_n;

	len_n = numlen(n);
	res = (char *)malloc(sizeof(char) * (len_n + 1));
	if (!res)
		return (NULL);
	i = len_n - 1;
	new_n = n;
	res[len_n] = '\0';
	if (new_n == 0)
		res[i--] = '0';
	if (new_n < 0)
	{
		res[0] = '-';
		new_n *= -1;
	}
	while (new_n != 0)
	{
		res[i--] = '0' + (new_n % 10);
		new_n /= 10;
	}
	return (res);
}

static int	numlen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}
