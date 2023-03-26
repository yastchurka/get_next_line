/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralukasi <ralukasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:14:22 by ralukasi          #+#    #+#             */
/*   Updated: 2023/01/24 21:14:07 by ralukasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_save_all(int fd, char *static_buffer)
{
	char	*buffer;
	int		size;

	buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	size = 1;
	if (!buffer)
		return (NULL);
	while (!ft_strchr(static_buffer, '\n') && size != 0)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size == -1)
		{
			free(buffer);
			free(static_buffer);
			return (NULL);
		}
		buffer[size] = '\0';
		static_buffer = ft_strjoin(static_buffer, buffer);
	}
	free(buffer);
	return (static_buffer);
}

char	*fixed_line(char *static_buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!static_buffer[i])
		return (NULL);
	while (static_buffer[i] != '\n' && static_buffer[i] != '\0')
		i++;
	line = (char *)malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (static_buffer[i] != '\n' && static_buffer[i] != '\0')
	{
		line[i] = static_buffer[i];
		i++;
	}
	if (static_buffer[i] == '\n')
	{
		line[i] = static_buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*next_line(char *static_buffer)
{
	int		i;
	int		j;
	char	*next_line;

	i = 0;
	while (static_buffer[i] != '\n' && static_buffer[i])
		i++;
	if (!static_buffer[i])
	{
		free(static_buffer);
		return (NULL);
	}
	next_line = malloc(sizeof(char) * (ft_strlen(static_buffer) - i + 1));
	if (!next_line)
		return (NULL);
	i++;
	j = 0;
	while (static_buffer[i] != '\0')
		next_line[j++] = static_buffer[i++];
	next_line[j] = '\0';
	free(static_buffer);
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char		*static_buffer[100000];
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (0);
	static_buffer[fd] = read_save_all(fd, static_buffer[fd]);
	if (!static_buffer[fd])
		return (NULL);
	line = fixed_line(static_buffer[fd]);
	static_buffer[fd] = next_line(static_buffer[fd]);
	return (line);
}

#include <stdio.h>

int	main(void)
{
	char *line;
	int	counter;
	int fd;
	int fd1;
	int fd2;

	counter = 0;
	fd = open("test.txt", O_RDONLY);
	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	printf("I am the fucking FD: %i\n", fd);
	printf("I am the fucking FD1: %i\n", fd1);
	printf("I am the fucking FD2: %i\n", fd2);
	while (counter < 5)
	{
		printf("fd: %d %s\n", fd, get_next_line(fd));
		printf("fd1:%d %s\n", fd1, get_next_line(fd1));
		printf("fd2:%d %s\n", fd2, get_next_line(fd2));
		counter++;
	}
	close(fd);
	return 0;
}
