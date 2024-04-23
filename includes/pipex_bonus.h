/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:34:28 by sabakar-          #+#    #+#             */
/*   Updated: 2024/04/22 22:25:01 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../gnl/get_next_line.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex_bonus
{
	int		fd[2];
	int		cmd_num;
	char	**args;
	int		infile;
	int		outfile;
	char	*limiter;
	char	*fpath;
	int		flag;
	int		save;
	int		idx;
	int		arg_num;
}			t_pipex_bonus;

void		ft_free(char **arr);
int			ft_strncmp(char *s1, char *s2, int len);
int			ft_strlen(char *sr);
void		ft_put_err(char *sr);
char		**ft_split(char const *s, char c);
char		**ft_get_paths(char **env);
char		*ft_check_path(char *cmd, char **env);
int			ft_strncmp(char *str1, char *str2, int len);

#endif