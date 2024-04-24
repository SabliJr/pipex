/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:59:21 by sabakar-          #+#    #+#             */
/*   Updated: 2024/04/24 03:58:43 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	ft_first_cmd(t_pipex_bonus *data, char **av)
{
	data->infile = open(av[1], O_RDONLY);
	if (data->infile < 0)
		ft_put_err("Error opening a file!");
	if (dup2(data->infile, 0) == -1)
		ft_put_err("Error with dup2!");
	close(data->infile);
}

void	ft_last_cmd(t_pipex_bonus *data, char **av, char **env)
{
	if (data->flag == 1)
		data->outfile = open(av[data->arg_num - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		data->outfile = open(av[data->arg_num - 1],
				O_WRONLY | O_CREAT | O_TRUNC | 0777);
	if (data->outfile == -1)
		ft_put_err("There's an err happened!");
	if (dup2(data->outfile, 1) == -1)
		ft_put_err("Error with dup2");
	close(data->outfile);
	ft_execute(data, av, env);
}

void ft_execute (t_pipex_bonus *data, char **av, char **env)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(av[data->idx], 32);
	path = ft_check_path(cmd[0], env);
	execve(path, cmd, env);
	ft_put_err("There was an err with execve!");
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size && nmemb > INT_MAX / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

void	ft_bzero(void *a, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)a)[i] = 0;
		i++;
	}
}