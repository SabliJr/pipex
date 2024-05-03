/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:12:57 by sabakar-          #+#    #+#             */
/*   Updated: 2024/05/03 08:34:25 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

char	**ft_find_path(char **env)
{
	char	**path;
	int		x;

	x = 0;
	path = NULL;
	while (env[x])
	{
		if (ft_strncmp_b("PATH", env[x], 4) == 0)
		{
			path = ft_split(env[x] + 5, ':');
			if (!path)
				ft_process_err();
			return (path);
		}
		x++;
	}
	return (NULL);
}

char	*ft_join(char *s1, char *s2)
{
	char	*new_arr;
	int		i;
	int		s_len;
	int		total_len;

	if (!s1 || !s2)
		return (NULL);
	s_len = ft_strlen(s1);
	total_len = (ft_strlen(s1) + ft_strlen(s2));
	new_arr = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!new_arr)
		return (NULL);
	i = -1;
	while (s1[++i])
		new_arr[i] = s1[i];
	i = -1;
	while (s2[++i])
		new_arr[s_len + i] = s2[i];
	new_arr[s_len + i] = '\0';
	return (new_arr);
}

void	ft_execute(char *av, char *env[])
{
	int	x;
	char	**cmd;
	char	**paths;
	char	*la_path;
	
	x = 1;
	cmd = ft_split(av, ' ');
	paths = ft_find_path(env);
	la_path = ft_get_cmd(cmd[0], paths);
	if (execve(la_path, cmd, env) == -1)
		ft_putstr("An err with execve");
}

char	*ft_get_cmd (char *cmd, char *env[])
{
	char	*fpath;
	int	x;

	x = 0;
	while (env[x])
	{
		fpath = ft_join(env[x], "/");
		fpath = ft_strjoin_gnl(fpath, cmd);
		if (access(fpath, F_OK) == 0)
			return (fpath);
		(free(fpath), x++);
	}
	ft_cmd_err(cmd);
	return (NULL);
}

int	ft_open_file(char	*av, int x)
{
	int	fd;
	
	fd = 0;
	if (x == 0)
		fd = open(av, O_WRONLY |  O_CREAT | O_APPEND, 0777);
	else if (x == 1)
		fd = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (x == 2)
		fd = open(av, O_RDONLY, 0777);
	if (fd == -1)
		ft_file_err(av);
	return (fd);
}