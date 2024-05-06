/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:12:57 by sabakar-          #+#    #+#             */
/*   Updated: 2024/05/06 07:21:22 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	ft_get_path (t_pipex_bonus *data)
{
	char	**paths;
	char	**envp;

	envp = data->env;
	while (ft_strncmp_b(*envp, "PATH=", 5) != 0)
		envp++;
	*envp += 5;
	paths = ft_split(*envp, ':');
	if (paths == NULL || paths[0] == NULL)
		ft_err_handler(data, 2, NULL);
	data->paths = paths;
}

void	ft_execute (t_pipex_bonus *data, char *cmd)
{
	char	*cmd_path;
	char	*unfound_cmd;
	char	**cmd_argv;

	if (cmd[0] == '\0')
		ft_err_handler(data, 127, NULL);
	cmd_argv = ft_split(cmd, 32);
	if (cmd_argv == NULL)
		ft_err_handler(data, 2, NULL);
	cmd_path = ft_find_executable(data, cmd_argv[0]);
	if (cmd_path == NULL)
	{
		unfound_cmd = ft_strdup(cmd_argv[0]);
		ft_free(cmd_argv);
		ft_err_handler(data, 127, unfound_cmd);
	}
	execve(cmd_path, cmd_argv, data->env);
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

char	*ft_find_executable (t_pipex_bonus *data, char *cmd)
{
	char	*fpath;
	char	*tmp;
	int	x;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	x = 0;
	while (data->paths[x])
	{
		tmp = ft_join(data->paths[x], "/");
		fpath = ft_strjoin_gnl(tmp, cmd);
		free(tmp);
		if (access(fpath, X_OK) == 0)
			return (fpath);
		(free(fpath), x++);
	}
	return (NULL);
}

int	ft_get_exit_status (int exit_status)
{
	return (((exit_status & 0xff00) >> 8));
}