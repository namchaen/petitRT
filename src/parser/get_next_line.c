/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 08:51:46 by chaejkim          #+#    #+#             */
/*   Updated: 2022/11/11 17:06:40 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <unistd.h>

static char	*get_line(char *save);
static char	*save_line(char *save, int start_len);
static char	*read_line(int fd, char *save);

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	save = read_line(fd, save);
	if (!save)
		return (NULL);
	line = get_line(save);
	if (line)
		save = save_line(save, ft_strlen(line));
	else
		save = save_line(save, 0);
	return (line);
}

static char	*read_line(int fd, char *save)
{
	char	*buff;
	int		read_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	while (42)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		save = ft_strjoin(save, buff);
		if (read_bytes == 0)
			break ;
	}
	free(buff);
	return (save);
}

static char	*get_line(char *save)
{
	char	*rval;
	char	*s;
	int		i;

	if (!*save)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
		return (ft_strdup(save));
	s = (char *)malloc(sizeof(char) * (i + 2));
	if (!s)
		return (NULL);
	rval = s;
	while (*save && *save != '\n')
		*s++ = *save++;
	if (*save == '\n')
		*s++ = *save++;
	*s = '\0';
	return (rval);
}

static char	*save_line(char *save, int start_len)
{
	char	*s;

	if (!*(save + start_len))
	{
		free(save);
		return (NULL);
	}
	s = ft_strdup(save + start_len);
	if (!s)
	{
		free(save);
		return (NULL);
	}
	free(save);
	return (s);
}
