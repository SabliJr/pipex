/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:10:30 by sabakar-          #+#    #+#             */
/*   Updated: 2024/04/05 10:56:09 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

size_t	ft_strlen_gnl(const char *str);
char	*get_next_line(int fd);
char	*ft_read_file(int fd, char *lines);
char	*ft_get_line(char *lines);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strchr_gnl(char *s, int c);

#endif