/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:31:23 by gakarbou          #+#    #+#             */
/*   Updated: 2024/11/12 21:54:45 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_fill_stash(char *stash, int fd)
{
	char	*dest;
	char	*temp;
	int		readed;

	dest = ft_strjoin(stash, NULL);
	if (!dest)
		return (NULL);
	readed = 1;
	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	while (readed > 0 && !ft_strchr(dest, '\n'))
	{
		readed = read(fd, temp, BUFFER_SIZE);
		if (readed < 0)
			return (ft_free_stuff(dest, temp, NULL));
		temp[readed] = 0;
		dest = ft_strjoin(dest, temp);
	}
	free(temp);
	return (dest);
}

char	*ft_get_line(char *str)
{
	char	*line;
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			break ;
	if (str[i])
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	line[i] = 0;
	while (--i >= 0)
		line[i] = str[i];
	return (line);
}

char	*move_stash(char *stash)
{
	size_t	i;
	size_t	pos;

	i = -1;
	pos = -1;
	while (stash[++pos])
		if (stash[pos] == '\n')
			break ;
	if (stash[pos])
		pos++;
	while (stash[(++i) + pos])
		stash[i] = stash[i + pos];
	while (pos)
	{
		stash[pos + i - 1] = 0;
		pos--;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	stash = ft_fill_stash(stash, fd);
	if (!stash)
		return (NULL);
	else if (!stash[0])
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = ft_get_line(stash);
	stash = move_stash(stash);
	return (line);
}

/*
#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int fd = open("f.txt", O_RDONLY);
	int	i = -1;
	char	*line;
	while (++i < 10)
	{
		line = get_next_line(fd);
		if (line)
			printf("%s", line);
		free(line);
	}
}
*/
