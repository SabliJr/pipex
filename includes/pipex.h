/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:21:39 by sabakar-          #+#    #+#             */
/*   Updated: 2024/05/10 13:23:37 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./get_next_line.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>

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

# define PER_ERR "Permission denied, you can't\
open this file! Or file doesn't exit, Or it's a directory"
# define CMD_ERR "Command not found!"
# define OPEN_ERR "Error opening file"
# define DUP_ERR "An err has occoured with dup2"
# define FORK_C2 "An Error has occuered with Fork child2"
# define FORK_C1 "An Error has occuered with Fork child1"

void		ft_print_err(char *str);
int			ft_strlen(char *str);
int			ft_strncmp(char *str1, char *str2, int len);
int			ft_pipex(t_pipex *data, char **args, char **env);
char		**ft_split(char const *s, char c);
void		ft_second_child_process(t_pipex *data, char **args, char **env);
char		**ft_get_paths(char **env);
void		ft_first_child_process(t_pipex *data, char **args, char **env);
char		*ft_check_path(char *cmd, char **env);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *a, size_t n);
void		ft_free(char **arr);
char		*ft_join(char *s1, char *s2);
void		ft_err(t_pipex *data);
void		ft_check_file(t_pipex *data, char **args);
char		*check_cmd_access(char *cmd);
char		*check_cmd_path(char *cmd);
char		*check_paths(char **paths, char *cmd);

#endif