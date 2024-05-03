/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:34:28 by sabakar-          #+#    #+#             */
/*   Updated: 2024/05/03 08:45:42 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "./get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

void	ft_free(char **arr);
int		ft_strncmp_b(char *s1, char *s2, int len);
int		ft_strlen(char *sr);
char	**ft_split(char const *s, char c);
char	**ft_get_paths(char **env);
char	*ft_check_path(char *cmd, char **env);
int		ft_strncmp(char *str1, char *str2, int len);
void	ft_pipex(int ac, char **av, char **env);
char	*ft_join(char *s1, char *s2);
void	ft_bzero(void *a, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_execute(char *av, char *env[]);
void	ft_args_err(void);
void	ft_process_err(void);
void	ft_cmd_err(char *cmd);
void	ft_file_err(char *file);
int		ft_get_next_line(char **line);
void	ft_putstr(char *sr);
void	ft_process_here_doc(int fd, char *limiter);
void	ft_here_doc(char *limiter);
void	ft_child_process(char *av, char *env[]);
char	**ft_find_path(char **env);
char	*ft_get_cmd(char *cmd, char *env[]);
int		ft_open_file(char *av, int x);
void	ft_args_err(void);

#endif