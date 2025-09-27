/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:57:53 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/10 13:19:44 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"
#include "../../inc/libft.h"

char	*ft_read_file(int fd, char *store_buffer)
{
	char		*line_buffer;
	ssize_t		num_bytes_read;

	num_bytes_read = 1;
	line_buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!line_buffer)
		return (NULL);
	while (ft_strchr(store_buffer, '\n') == NULL && num_bytes_read != 0)
	{
		num_bytes_read = read(fd, line_buffer, BUFFER_SIZE);
		if (num_bytes_read < 0)
			return (free(store_buffer), free(line_buffer), store_buffer = NULL,
				line_buffer = NULL, NULL);
		line_buffer[num_bytes_read] = '\0';
		store_buffer = ft_join_and_free(store_buffer, line_buffer);
		if (!store_buffer)
			return (free(store_buffer), free(line_buffer), store_buffer = NULL,
				line_buffer = NULL, NULL);
	}
	free(line_buffer);
	return (store_buffer);
}

char	*ft_extract_line(char *store_buffer)
{
	char	*line_buffer;
	size_t	i;

	i = 0;
	if (!store_buffer)
		return (NULL);
	if (store_buffer[i] == '\0')
		return (NULL);
	while (store_buffer[i] != '\0' && store_buffer[i] != '\n')
		i++;
	if (store_buffer[i] == '\n')
		i++;
	line_buffer = ft_substr_gnl(store_buffer, 0, i);
	if (!line_buffer)
		return (NULL);
	return (line_buffer);
}

char	*ft_trim_buffer(char *store_buffer)
{
	char	*remaining_buffer;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!store_buffer)
		return (NULL);
	while (store_buffer[i] != '\0' && store_buffer[i] != '\n')
		i ++;
	if (store_buffer[i] == '\0')
		return (free(store_buffer), store_buffer = NULL, NULL);
	i ++;
	remaining_buffer = ft_calloc(ft_strlen(store_buffer) - i + 1, sizeof(char));
	if (!remaining_buffer)
		return (NULL);
	while (store_buffer[i] != '\0')
	{
		remaining_buffer[j] = store_buffer[i];
		j ++;
		i ++;
	}
	remaining_buffer[j] = '\0';
	free(store_buffer);
	return (remaining_buffer);
}

char	*get_next_line(int fd)
{
	char		*current_line;
	static char	*store_buffer = NULL;

	if (fd < 0)
		return (NULL);
	store_buffer = ft_read_file(fd, store_buffer);
	if (!store_buffer)
		return (NULL);
	current_line = ft_extract_line(store_buffer);
	store_buffer = ft_trim_buffer(store_buffer);
	return (current_line);
}
