/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:15:24 by sabakar-          #+#    #+#             */
/*   Updated: 2024/04/24 04:05:41 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

static void	ft_read_lines(t_pipex_bonus *data, char *line, int tmp_fd);
static char	*get_file_name(void);

void	ft_handle_here_doc(t_pipex_bonus *data, char **av, char **env)
{
	char	*line;
	int		tmp_fd;

	line = NULL;
	data->fpath = get_file_name();
	data->limiter = av[2];
	data->flag = 1;
	tmp_fd = open(data->fpath, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd == -1)
		ft_put_err("Error");
	ft_read_lines(data, line, tmp_fd);
	close(tmp_fd);
	ft_pipex(data, av, env);
	unlink(data->fpath);
	free(data->fpath);
	data->fpath = NULL;
}

static void	ft_read_lines(t_pipex_bonus *data, char *line, int tmp_fd)
{
	while (1)
	{
		write(1, ">", 1);
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if ((ft_strncmp_b(line, data->limiter, ft_strlen(data->limiter)) == 0)
			&& (ft_strlen(line) - 1 == ft_strlen(data->limiter)))
		{
			free(line);
			break ;
		}
		if (write(tmp_fd, line, ft_strlen(line)) == -1)
		{
			free(line);
			close(tmp_fd);
			unlink(data->fpath);
			ft_put_err("An error");
		}
		free(line);
	}
}

void	ft_here_doc(t_pipex_bonus *data)
{
	int	tmp_fd;

	tmp_fd = open(data->fpath, O_RDONLY);
	if (tmp_fd == -1)
		ft_put_err("An error!");
	if (dup2(tmp_fd, 0) == -1)
		ft_put_err("Error in dup2");
	close(tmp_fd);
}

// static char	*get_file_name(void)
// {
// 	char *path;
// 	int x;

// 	x = 0;
// 	while (x < OPEN_MAX)
// 	{
// 		path = ft_strjoin_gnl("/tmp/", ft_itoa(x));
// 		if (access(path, F_OK) == -1)
// 			return (path);
// 		x++;
// 	}
// 	return (NULL);
// }

static char *get_file_name(void)
{
    char *path;
    int x;
    int open_max;

    #ifdef OPEN_MAX
        open_max = OPEN_MAX;
    #else
        open_max = sysconf(_SC_OPEN_MAX);
    #endif

    x = 0;
    while (x < open_max)
    {
        path = ft_strjoin_gnl("/tmp/", ft_itoa(x));
        if (access(path, F_OK) == -1)
            return (path);
        x++;
    }
    return (NULL);
}