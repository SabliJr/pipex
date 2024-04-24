/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:12:57 by sabakar-          #+#    #+#             */
/*   Updated: 2024/04/24 04:05:18 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

char	*ft_check_path(char *cmd, char **env)
{
	char	**paths;
	char	*fpath;
	int		x;

	x = -1;
	if (access(cmd, F_OK | R_OK | X_OK) == 0)
		return (cmd);
	if (ft_strncmp_b(cmd, "/", 1) == 0)
	{
		if (access(cmd, F_OK | R_OK | X_OK) == 0)
			return (cmd);
		(ft_put_err("Error in the command path"));
	}
	paths = ft_get_paths(env);
	if (!paths || paths[0] == NULL)
		(ft_free(paths), free(cmd));
	while (paths && paths[++x])
	{
		fpath = ft_join(paths[x], "/");
		fpath = ft_strjoin_gnl(fpath, cmd);
		if (access(fpath, F_OK | R_OK | X_OK) == 0)
			return (ft_free(paths), fpath);
		(free(fpath), fpath = NULL);
	}
	return (ft_free(paths), NULL);
}

char	**ft_get_paths(char **env)
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
