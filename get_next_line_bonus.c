/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:25:36 by ilmahjou          #+#    #+#             */
/*   Updated: 2024/12/18 17:56:22 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read_file(int fd, char *buffer)
{
	char	*buff;
	ssize_t	byte_read;
	char	*temp;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	byte_read = 1;
	while (byte_read > 0 && !ft_strchr(buffer, '\n'))
	{
		byte_read = read(fd, buff, BUFFER_SIZE);
		if (byte_read < 0)
			return (free(buff), free(buffer), NULL);
		buff[byte_read] = '\0';
		temp = buffer;
		buffer = ft_strjoin(buffer, buff);
		free(temp);
	}
	free(buff);
	return (buffer);
}

char	*ft_extract_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer || buffer[0] == '\0')
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_store(char *buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!new_buffer)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i] != '\0')
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FOPEN_MAX];
	char		*line;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = ft_read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_extract_line(buffer[fd]);
	buffer[fd] = ft_store(buffer[fd]);
	return (line);
}
/* int main()
{
	int fd1 = open ("file1.txt", O_RDONLY);
	int fd2 = open ("file2.txt", O_RDONLY);
	char *line1 = get_next_line(fd1);
	char *line2 = get_next_line(fd2);

	while (line1 || line2)
	{
		if(line1)
		{
			printf("%s", line1);
			free(line1);
			line1 = get_next_line(fd1);
		}
		if(line2)
		{
			printf("%s", line2);
			free(line2);
			line2 = get_next_line(fd2);
		}
	}
	close (fd1);
	close(fd2);
	return (0);
} */
