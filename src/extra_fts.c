/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:39:48 by sabakar-          #+#    #+#             */
/*   Updated: 2024/05/10 13:19:15 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_check_file(t_pipex *data, char **args)
{
	if (data->in_file < 0)
	{
		if (access(args[1], W_OK) != 0)
			(close(data->fd[1]), ft_print_err(PER_ERR), exit(127));
		else
			(close(data->fd[1]), ft_print_err(OPEN_ERR), exit(EXIT_FAILURE));
	}
}

char	*check_cmd_access(char *cmd)
{
	if (access(cmd, F_OK | R_OK | X_OK) == 0)
		return (cmd);
	return (NULL);
}

char	*check_cmd_path(char *cmd)
{
	if (ft_strncmp(cmd, "/", 5) == 0)
	{
		if (access(cmd, F_OK | R_OK | X_OK) == 0)
			return (cmd);
		(ft_print_err("Error in the command path"));
	}
	return (NULL);
}

char	*check_paths(char **paths, char *cmd)
{
	char	*fpath;
	int		x;

	x = -1;
	while (paths && paths[++x])
	{
		fpath = ft_join(paths[x], "/");
		if (!fpath)
			return (ft_free(paths), NULL);
		fpath = ft_strjoin_gnl(fpath, cmd);
		if (!fpath)
			return (ft_free(paths), NULL);
		if (access(fpath, F_OK | R_OK | X_OK) == 0)
			return (ft_free(paths), fpath);
		(free(fpath), fpath = NULL);
	}
	return (NULL);
}
