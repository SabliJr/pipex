/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:12:57 by sabakar-          #+#    #+#             */
/*   Updated: 2024/04/22 22:14:28 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_strncmp(char *str1, char *str2, int len)
{
	int	x;

	x = 0;
	while (str1[x] && str2[x] && x < len)
	{
		if (str1[x] != str2[x])
			return (str1[x] - str2[x]);
		x++;
	}
	return (0);
}

char	*ft_check_path(char *cmd, char **env)
{
	char	**paths;
	char	*fpath;
	int		x;

	x = -1;
	if (access(cmd, F_OK | R_OK | X_OK) == 0)
		return (cmd);
	if (ft_strncmp(cmd, "/", 1) == 0)
	{
		if (access(cmd, F_OK | R_OK | X_OK) == 0)
			return (cmd);
		(ft_print_err("Error in the command path"));
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
		if (ft_strncmp("PATH", env[x], 4) == 0)
		{
			path = ft_split(env[x] + 5, ':');
			return (path);
		}
		x++;
	}
	return (NULL);
}
