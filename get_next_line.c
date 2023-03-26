/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralukasi <ralukasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:14:22 by ralukasi          #+#    #+#             */
/*   Updated: 2023/01/24 20:40:33 by ralukasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
			free(static_buffer);
			free(buffer);
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
	next_line = (char *)malloc(sizeof(char) * ft_strlen(static_buffer) - i + 1);
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
	static char		*static_buffer;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	static_buffer = read_save_all(fd, static_buffer);
	if (!static_buffer)
	{
		free(static_buffer);
		return (NULL);
	}
	line = fixed_line(static_buffer);
	static_buffer = next_line(static_buffer);
	return (line);
}

/* int	main(void)
{
	char *line;
	int	counter;
	int fd;

	counter = 0;
	fd = open("cat.txt", O_RDONLY);
	while (counter < 5)
	{
		line = get_next_line(fd);
		printf("%s\n", line);
		counter++;
	}
	close(fd);
	return 0;
} */