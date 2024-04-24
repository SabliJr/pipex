/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:33:45 by sabakar-          #+#    #+#             */
/*   Updated: 2024/04/24 04:04:44 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

int	main(int ac, char *av[], char *env[])
{
	t_pipex_bonus	data;

	if (!env)
		ft_put_err("Error: Empty environment!");
	if (ac < 5)
		ft_put_err("Please provide suficent commands");
	if (!ft_strncmp_b(av[1], "here_doc", 9) && ac == 6)
	{
		data.arg_num = ac;
		ft_handle_here_doc(&data, av, env);
	}
	else if (ac >= 5)
	{
		data.arg_num = ac;
		data.flag = 0;
		ft_pipex(&data, av, env);
	}
	else
		ft_put_err("Please provide suficent commands!");
	return (0);
}

void	ft_pipex(t_pipex_bonus *data, char **av, char **env)
{
	data->idx = 2;
	if (data->flag == 1)
		data->idx = 3;
	data->save = -1;
	while (data->idx <= data->arg_num - 2)
	{
		ft_middle_processes(data, av, env);
		data->idx++;
	}
	ft_parent_process(data);
}

void	ft_middle_processes(t_pipex_bonus *data, char **av, char **env)
{
	pid_t	pid;

	if (pipe(data->fd) == -1)
		ft_put_err("Error with pipe");
	pid = fork();
	if (pid == -1)
		ft_put_err("Error in fork");
	if (pid == 0)
		ft_child_process(data, av, env);
	close(data->save);
	data->save = dup(data->fd[0]);
	if (data->save == -1)
		ft_put_err("An err has occourd!");
	close(data->fd[0]);
	close(data->fd[1]);
}

void	ft_child_process(t_pipex_bonus *data, char **av, char **env)
{
	close(data->fd[0]);
	if (data->idx == 2)
		ft_first_cmd(data, av);
	if ((data->flag == 1) && data->idx == 3)
		ft_here_doc(data);
	if (data->save != -1 && dup2(data->save, 0) == -1)
		ft_put_err("An err has occoured!");
	close(data->save);
	if (data->idx == data->arg_num - 2)
		ft_last_cmd(data, av, env);
	if (dup2(data->fd[1], 1) == -1)
		ft_put_err("An err has occoured!");
	close(data->fd[1]);
	ft_execute(data, av, env);
}

void	ft_parent_process(t_pipex_bonus *data)
{
	close(data->save);
	while (waitpid(-1, NULL, 0) != -1)
		;
}