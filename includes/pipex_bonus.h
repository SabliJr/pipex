/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:34:28 by sabakar-          #+#    #+#             */
/*   Updated: 2024/05/07 08:29:27 by sabakar-         ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

enum		e_bool
{
	FALSE,
	TRUE
};

typedef struct s_pipex_bonus
{
	int		here_doc;
	char	**argv;
	char	**env;
	char	**paths;
	int		argc;
	int		*pids;
	int		pids_num;
}			t_pipex_bonus;

int			ft_init_data(t_pipex_bonus *data, int ac, char *av[], char *envp[]);
void		ft_get_path(t_pipex_bonus *data);
void		ft_execute(t_pipex_bonus *data, char *cmd);
char		*ft_find_executable(t_pipex_bonus *data, char *cmd);
int			ft_get_exit_status(int exit_status);
char		*ft_strdup(char *s);

void		ft_free(char **arr);
int			ft_strncmp_b(char *s1, char *s2, int len);
char		*ft_join(char *s1, char *s2);
char		**ft_split(char const *s, char c);
int			ft_strlen(char *sr);
void		ft_putstr_fd(char *s, int fd);

void		ft_err_handler(t_pipex_bonus *data, int exit_status, char *msg);
int			ft_here_doc(t_pipex_bonus *data, char *delimiter);
int			ft_open_outfile(t_pipex_bonus *data);
int			ft_open_infile(t_pipex_bonus *data, int *x);

void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *a, size_t n);

#endif