/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_and_opens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 07:18:25 by sabakar-          #+#    #+#             */
/*   Updated: 2024/05/17 17:59:39 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

int	ft_open_infile(t_pipex_bonus *data, int *x)
{
	int	infile;

	infile = open(data->argv[1], O_RDONLY);
	if (infile == -1)
	{
		close(x[1]);
		ft_err_handler(data, 1, data->argv[1]);
	}
	return (infile);
}

int	ft_open_outfile(t_pipex_bonus *data)
{
	int		outfile;
	char	*file_name;

	file_name = data->argv[data->argc - 1];
	if (data->here_doc)
		outfile = open(file_name, O_RDWR | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		outfile = open(file_name, O_RDWR | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (outfile == -1)
		ft_err_handler(data, 1, file_name);
	return (outfile);
}

int	ft_here_doc(t_pipex_bonus *data, char *delimiter)
{
	int		fds[2];
	char	*line;

	if (pipe(fds) == -1)
		ft_err_handler(data, 1, NULL);
	while (1)
	{
		ft_putstr_fd("here_doc> ", STDOUT_FILENO);
		line = get_next_line(0, 0);
		if (!line)
			return (close(fds[0]), close(fds[1]), (-1));
		if ((ft_strncmp_b(line, delimiter, ft_strlen(delimiter)) == 0)
			&& (line[ft_strlen(delimiter)] == '\n'))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fds[1]);
		free(line);
	}
	get_next_line(0, 1);
	close(fds[1]);
	return (fds[0]);
}

void	ft_err_handler(t_pipex_bonus *data, int exit_status, char *msg)
{
	if (exit_status == 1)
	{
		ft_free(data->paths);
		ft_print_err(msg);
	}
	else if (exit_status == 2)
		(ft_print_err("Error: Couldn't split the commands!"));
	else if (exit_status == 3)
		ft_print_err("Invalid arguments!");
	else if (exit_status == 127)
	{
		write(2, msg, ft_strlen(msg));
		ft_print_err(": command not found!");
		free(msg);
		ft_free(data->paths);
	}
	if (data->pids)
		free(data->pids);
	exit(exit_status);
}
