/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:16:25 by ilmahjou          #+#    #+#             */
/*   Updated: 2024/12/13 19:17:56 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_read_line(int fd, char *buffer)
{
	ssize_t byte_read;
	char	*buff;
	char	*tmp;

	buff = malloc(BUFFER_SIZE + 1);
	if(!buff)
		return(NULL);
	if (!buffer)
		buffer = ft_strdup("");
	byte_read = 1;
	while (byte_read > 0 && !ft_strchr(buff, '\n'))
	{
		byte_read = read(fd, buff, BUFFER_SIZE);
		if(byte_read < 0)
		{
			free(buff);
			free(buffer);
			return(NULL);
		}
		buff[byte_read] = '\0';
		tmp = buffer;
		buffer = ft_strjoin(buffer, buff);
		free(tmp);
	}
	free(buff);
	return (buffer);
}

char	*ft_extract_line(char *buffer)
{
	char	*line;
	int		i;
	int j;

	i = 0;
	if (!buffer[0])
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i++;
	j = 0;
	while (j < i)
	{
		line[j] = buffer[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_store(char *buffer)
{
	char	*new_buffer;
	int		i;
	int 	j;

	i = 0;
	while(buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
    {
        free(buffer);
        return (NULL);
    }
	new_buffer = malloc(ft_strlen(buffer) - i + 1);
	if (!new_buffer)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i] != '\0')
	{
		new_buffer[j] = buffer[i];
		j++;
		i++;
	}
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	char	*line;
	static char	*buffer;

	if(fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read_line(fd, buffer);
	if(!buffer)
		return (NULL);
	line = ft_extract_line(buffer);
	buffer = ft_store(buffer);
	return (line);
}

#include <stdio.h>
int main(void)
{
	int fd = open("file.txt", O_RDONLY);
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
