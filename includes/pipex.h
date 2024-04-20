/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:21:39 by sabakar-          #+#    #+#             */
/*   Updated: 2024/04/21 01:18:05 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../gnl/get_next_line.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		fd[2];
	pid_t	child1;
	pid_t	child2;
	char	**args;
	int		cmd_count;
	int		in_file;
	int		out_file;
}			t_pipex;

void		ft_print_err(const char *str);
int			ft_strlen(char *str);
int			ft_strncmp(char *str1, char *str2, int len);
void		ft_pipex(t_pipex *data, char **args, char **env);
char		**ft_split(char const *s, char c);
void		*ft_second_child_process(t_pipex *data, char **args, char **env);
char		**ft_get_paths(char **env);
void		*ft_first_child_process(t_pipex *data, char **args, char **env);
char		*ft_check_path(char *cmd, char **env);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *a, size_t n);
void		ft_free(char **arr);
char		*ft_strjoin(char *s1, char *s2);

#endif