/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:38:42 by sabakar-          #+#    #+#             */
/*   Updated: 2024/04/05 19:16:37 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	data;

	if (!envp)
		ft_print_err("The the env is empty!");
	if (argc != 5)
		ft_print_err("The usage: i.e ./pipex file1 cmd1 cmd2 file2");
	ft_pipex(&data, argv, envp);
	return (0);
}

void	ft_pipex(t_pipex *data, char **args, char **env)
{
	int	status;

	if (pipe(data->fd) == -1)
		ft_print_err("An Error with pipe\n");
	data->child1 = fork();
	if (data->child1 < 0)
		ft_print_err("An Error has occuered with Fork child1");
	data->child2 = fork();
	if (data->child2 < 0)
		ft_print_err("An Error has occuered with Fork child2");
	if (data->child1 == 0)
		ft_first_child_process(&data, args, env);
	if (data->child2 == 0)
		ft_second_child_process(&data, args, env);
	close(data->fd[0]);
	close(data->fd[1]);
	waitpid(data->child1, &status, 0);
	waitpid(data->child2, &status, 0);
}

void	*ft_first_child_process(t_pipex *data, char **args, char **env)
{
	char	**cmd;
	char	*la_path;

	close(data->fd[0]);
	data->in_file = open(args[1], O_RDONLY);
	if (data->in_file == -1)
		return (close(data->fd[1]), ft_print_err("Error opening the file"),
			NULL);
	if (dup2(data->in_file, 0) == -1)
		return (close(data->in_file),
			ft_print_err("An Error occoured with dup2"), NULL);
	if (dup2(data->fd[1], 1) == -1)
	{
		close(data->fd[1]);
		close(data->in_file);
		return (ft_print_err("An Error occoured with dup2"), NULL);
	}
	cmd = ft_split(args[1], ' ');
	la_path = ft_check_path(cmd[0], env);
	close(data->fd[0]);
	execev(la_path, cmd, env);
	ft_print_err("An error has occured on execev");
	return (free(cmd), free(la_path), NULL);
}

void	*ft_second_child_process(t_pipex *data, char **args, char **env)
{
	char	**cmd;
	char	*la_path;

	close(data->fd[1]);
	data->out_file = open(args[4], O_RDONLY | O_WRONLY | O_CREAT | 0777);
	if (data->out_file < 0)
		return (close(data->fd[0]), ft_print_err("Error opening file"), NULL);
	if (dup2(data->out_file, 1) == -1)
		return (close(data->out_file), ft_print_err("An err with dup2"), NULL);
	if (dup2(data->fd[0], 0) == -1)
	{
		close(data->out_file);
		close(data->fd[0]);
		return (ft_print_err("An err occoured with dup2"), NULL);
	}
	cmd = ft_split(args[3], ' ');
	la_path = ft_cheak_path(cmd[0], env);
	close(data->fd[1]);
	execve(la_path, cmd, env);
	return (free(cmd), free(la_path), NULL);
}
