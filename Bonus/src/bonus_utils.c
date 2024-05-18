/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:12:57 by sabakar-          #+#    #+#             */
/*   Updated: 2024/05/18 16:50:17 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

char *ft_check_if_cmd (char *cmd)
{
	int x;
	char *new_cmd;

	x = 0;
	new_cmd = malloc(sizeof(char) * ft_strlen(cmd) + 2);
	if (!new_cmd)
		return (NULL);
	while (cmd[x])
	{
		new_cmd[x] = cmd[x];
		x++;
	}
	new_cmd[x] = '/';
	new_cmd[++x] = '\0';
	return (new_cmd);
}

char	**ft_get_paths(char **env)
{
	char	**path;
	int		x;

	x = 0;
	while (env && env[x])
	{	
		if (ft_strncmp_b("PATH=", env[x], 5) == 0)
		{
			path = ft_split(env[x] + 5, ':');
			return (path);
		}
		x++;
	}
	return (NULL);
}

void	ft_execute(t_pipex_bonus *data, char *cmd)
{
	char	*cmd_path;
	char	*unfound_cmd;
	char	**cmd_argv;

	if (cmd[0] == '\0')
		ft_err_handler(data, 127, NULL);
	cmd_argv = ft_split(cmd, 32);
	if (cmd_argv == NULL || cmd_argv[0] == NULL)
		ft_err_handler(data, 2, NULL);
	cmd_path = ft_find_executable(data, cmd_argv[0]);
	if (cmd_path == NULL)
	{
		unfound_cmd = ft_strdup(cmd_argv[0]);
		ft_free(cmd_argv);
		ft_err_handler(data, 127, unfound_cmd);
	}
	if (execve(cmd_path, cmd_argv, data->env) == -1)
		(ft_free(cmd_argv), ft_err_handler(data, 143, "execve failed"));
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

char	*ft_find_executable(t_pipex_bonus *data, char *cmd)
{
	char	*fpath;
	char	*tmp;
	int		x;
	char *new_cmd;

	if (access(cmd, F_OK | R_OK | X_OK) == 0)
	{
		new_cmd = ft_check_if_cmd(cmd);
		if (new_cmd == NULL)
			return (NULL);
		if (access(new_cmd, F_OK | R_OK | X_OK) == 0)
			return (free(new_cmd), NULL);
		return (cmd);
	}
	
	x = 0;
	while (data->paths && data->paths[x])
	{
		tmp = ft_join(data->paths[x], "/");
		(fpath = ft_join(tmp, cmd), free(tmp));
		if (access(fpath, F_OK | R_OK | X_OK) == 0)
			return (fpath);
		(free(fpath), x++);
	}
	return (NULL);
}

int	ft_get_exit_status(int exit_status)
{
	return (((exit_status & 0xff00) >> 8));
}
