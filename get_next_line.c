/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleisti <cleisti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:21:28 by cleisti           #+#    #+#             */
/*   Updated: 2019/11/25 18:16:07 by cleisti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		find_line(char **str, char **line)
{
	char	*temp;
	size_t	len;

	len = 0;
	while ((*str)[len] != '\n' && (*str)[len] != '\0')
		len++;
	if ((*str)[len] == '\n')
	{
		if (!(*line = ft_strsub((*str), 0, len)))
			return (-1);
		temp = (*str);
		if (!((*str) = ft_strsub((*str), len + 1, ft_strlen((*str)) - len - 1)))
			return (-1);
		ft_strdel(&temp);
	}
	else if ((*str)[len] == '\0')
	{
		if (!(*line = ft_strdup(*str)))
			return (-1);
		ft_strclr(*str);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	char			*temp;
	int				ret;
	static char		*str[MAX_FD];

	if (fd < 0 || fd > MAX_FD || !(line) || BUFF_SIZE < 1
			|| read(fd, buf, 0) < 0)
		return (-1);
	if (!(str[fd]) && !(str[fd] = ft_strnew(0)))
		return (-1);
	while (!ft_strchr(str[fd], '\n') && (ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		temp = str[fd];
		if (!(str[fd] = ft_strjoin(str[fd], buf)))
			return (-1);
		ft_strdel(&temp);
	}
	if (ret == 0 && str[fd][0] == '\0')
	{
		ft_strdel(&str[fd]);
		*line = NULL;
		return (0);
	}
	return (find_line(&str[fd], line));
}
