/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:31:23 by gakarbou          #+#    #+#             */
/*   Updated: 2024/11/12 23:34:20 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_fill_stash(char *stash, int fd)
{
	char	*dest;
	char	*temp;
	int		readed;

	dest = ft_strjoin(stash, NULL);
	if (!dest)
		return (ft_free_stuff(stash, dest, NULL));
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
	static char	*stash[4096];
	char		*line;

	if (fd < 0)
		return (NULL);
	stash[fd] = ft_fill_stash(stash[fd], fd);
	if (!stash[fd])
		return (NULL);
	else if (!stash[fd][0])
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	line = ft_get_line(stash[fd]);
	stash[fd] = move_stash(stash[fd]);
	return (line);
}

/*
#include <stdio.h>
#include <fcntl.h>

void	test_gnl(int fd, char *supposed)
{
	printf("%s%s\n\n\n", get_next_line(fd), supposed);
}

int	main(void)
{
	int fd = open("read_error.txt", O_RDONLY);
	int fd2 = open("lines_around_10.txt", O_RDONLY);
	test_gnl(fd, "aaaaaaaaaa\n");
	test_gnl(fd2, "0123456789\n");
	test_gnl(fd, "bbbbbbbbbb\n");
	test_gnl(fd2, "012345678\n");
	if (BUFFER_SIZE > 100) {
		char *temp;
		do
		{
			temp = get_next_line(fd);
			free(temp);
		} while (temp);
	}
	close(fd);
	test_gnl(fd2, "90123456789\n");
	fd = open("read_error.txt", O_RDONLY);
	test_gnl(fd, "aaaaaaaaaa\n");
	test_gnl(fd2, "0123456789\n");
	test_gnl(fd, "bbbbbbbbbb\n");
	test_gnl(fd, "cccccccccc\n");
	test_gnl(fd2, "xxxx\n");
	test_gnl(fd2, NULL);
	test_gnl(fd, "dddddddddd\n");
	test_gnl(fd, NULL);
}
*/
