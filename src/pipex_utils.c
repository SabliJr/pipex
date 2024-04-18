/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:46:02 by sabakar-          #+#    #+#             */
/*   Updated: 2024/04/18 20:37:03 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void	ft_print_err(const char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		write(1, &str[x], 1);
		x++;
	}
	write(1, "\n", 1);
	exit(1);
}

int	ft_strlen(char *str)
{
	int	x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

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
	char	*full_path;
	int		x;

	x = -1;
	if (access(cmd, F_OK | R_OK | X_OK) == 0)
		return (cmd);
	if (ft_strncmp(cmd, "/", 5) == 0)
	{
		if (access(cmd, F_OK | R_OK | X_OK) == 0)
			return (cmd);
		else
			ft_print_err("Error in the command path");
	}
	paths = ft_get_paths(env);
	while (paths && paths[++x])
	{
		full_path = ft_strjoin_gnl(paths[x], "/");
		full_path = ft_strjoin_gnl(full_path, cmd);
		if (access(full_path, F_OK | R_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		full_path = NULL;
	}
	return (NULL);
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
