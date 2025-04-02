/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:58:08 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/10 13:20:12 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

#ifndef OPEN_MAX
#define OPEN_MAX 1024
#endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
#include "libft.h"

char	*ft_read_file(int fd, char *store_buffer);
char	*ft_extract_line(char *store_buffer);
char	*ft_trim_buffer(char *store_buffer);
char	*get_next_line(int fd);

char	*ft_substr_gnl(char *s, unsigned int start, size_t len);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
char	*ft_join_and_free(char *s1, char *s2);

#endif