/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:10:30 by sabakar-          #+#    #+#             */
/*   Updated: 2024/04/19 17:21:05 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

int		has_end(char *str);
int		ft_strlen_gnl(const char *s);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*line_dealer(char *updated);
char	*get_next_line(int fd);

#endif