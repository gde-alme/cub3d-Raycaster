/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efreire- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:34:16 by efreire-          #+#    #+#             */
/*   Updated: 2023/01/28 18:34:18 by efreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_line_data(char *str, int fd, char *buf);
static char	*get_before_nl(char *str);
static char	*get_after_nl(char *str);
static char	*ft_strjoin_free_first(char *str1, char *str2);

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	static char	*list[1025];
	char		*res;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	list[fd] = get_line_data(list[fd], fd, buf);
	if (list[fd] == NULL)
		return (NULL);
	if (ft_strlen(list[fd]) == 0)
	{
		free(list[fd]);
		return (NULL);
	}
	res = get_before_nl(list[fd]);
	list[fd] = get_after_nl(list[fd]);
	return (res);
}

static char	*get_line_data(char *str, int fd, char *buf)
{
	int		bytes_read;

	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read <= 0 && str == (char *)0)
		return (NULL);
	buf[bytes_read] = '\0';
	if (str == (char *)0)
	{
		str = (char *)malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	str = ft_strjoin_free_first(str, buf);
	while (!ft_strchr(str, '\n') && bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		buf[bytes_read] = '\0';
		str = ft_strjoin_free_first(str, buf);
	}
	return (str);
}

static char	*get_before_nl(char *str)
{
	char	*res;
	int		i;

	i = 0;
	while (str[i])
		if (str[i++] == '\n')
			break ;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	res[i--] = '\0';
	while (i >= 0)
	{
		res[i] = str[i];
		i--;
	}
	return (res);
}

static char	*get_after_nl(char *str)
{
	char	*res;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(str);
	i = 0;
	while (str[i])
		if (str[i++] == '\n')
			break ;
	res = (char *)malloc(sizeof(char) * (len - i + 1));
	if (!res)
		return (NULL);
	j = 0;
	while (str[i])
		res[j++] = str[i++];
	res[j] = '\0';
	free(str);
	return (res);
}

static char	*ft_strjoin_free_first(char *str1, char *str2)
{
	char	*res;

	res = ft_strjoin(str1, str2);
	free(str1);
	return (res);
}
