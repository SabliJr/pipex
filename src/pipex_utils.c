/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:46:02 by sabakar-          #+#    #+#             */
/*   Updated: 2024/05/07 08:30:08 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_print_err(char *str)
{
	int		x;
	int		len;
	char	*new_str;

	len = ft_strlen(str);
	x = 0;
	new_str = (char *)malloc(sizeof(char) * len + 1);
	if (!new_str)
		return ;
	while (str[x])
	{
		new_str[x] = str[x];
		x++;
	}
	new_str[x] = '\n';
	write(2, new_str, len + 1);
	free(new_str);
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
	char	*fpath;

	fpath = check_cmd_access(cmd);
	if (fpath != NULL)
		return (fpath);
	fpath = check_cmd_path(cmd);
	if (fpath != NULL)
		return (fpath);
	paths = ft_get_paths(env);
	if (!paths || paths[0] == NULL)
		return (cmd);
	fpath = check_paths(paths, cmd);
	if (fpath != NULL)
		return (fpath);
	return (ft_free(paths), NULL);
}

char	**ft_get_paths(char **env)
{
	char	**path;
	int		x;

	x = 0;
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
