/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:38:42 by sabakar-          #+#    #+#             */
/*   Updated: 2024/04/21 01:24:08 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	data;

	if (!envp)
		ft_print_err("The the env is empty!");
	if (argc != 5)
		ft_print_err("The usage: i.e ./pipex file1 cmd1 cmd2 file2");
	ft_pipex(&data, argv, envp);
}

void	ft_pipex(t_pipex *data, char **args, char **env)
{
	int	status;

	if (pipe(data->fd) == -1)
		ft_print_err("An Error with pipe\n");
	data->child1 = fork();
	if (data->child1 < 0)
		ft_print_err("An Error has occuered with Fork child1");
	if (data->child1 == 0)
		ft_first_child_process(data, args, env);
	data->child2 = fork();
	if (data->child2 < 0)
		ft_print_err("An Error has occuered with Fork child2");
	if (data->child2 == 0)
		ft_second_child_process(data, args, env);
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
	if (data->in_file < 0)
	{
		if (access(args[1], W_OK) != 0)
			return (close(data->fd[1]), ft_print_err("Permission denied, you can't open this file!"), NULL);
		else
			return (close(data->fd[1]), ft_print_err("Error opening the file"),
				NULL);
	}
	if (dup2(data->in_file, 0) == -1)
		return (close(data->in_file),
			ft_print_err("An Error occoured with dup2"), NULL);
	if (dup2(data->fd[1], 1) == -1)
	{
		close(data->fd[1]);
		close(data->in_file);
		return (ft_print_err("An Error occoured with dup2"), NULL);
	}
	close(data->fd[1]);
	cmd = ft_split(args[2], ' ');
	if (cmd == NULL || cmd[0] == NULL)
	{
		ft_free(cmd);
		return (NULL);
	}
	la_path = ft_check_path(cmd[0], env);
	close(data->in_file);
	if (execve(la_path, cmd, env) == -1)
	{
		ft_free(cmd);
		free(la_path);
		ft_print_err("Command not found!");
		exit(1);
	}
	return (ft_free(cmd), free(la_path), la_path = NULL,
		ft_print_err("Command not found!"), NULL);
}

void	*ft_second_child_process(t_pipex *data, char **args, char **env)
{
	char	**cmd;
	char	*la_path;

	close(data->fd[1]);
	data->out_file = open(args[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (data->out_file < 0)
	{
		if (access(args[4], W_OK) != 0)
			return (close(data->fd[0]), ft_print_err("Permission denied, you can't open this file!"), NULL);
		else
			return (close(data->fd[0]), ft_print_err("Error opening file"),
				NULL);
	}
	if (dup2(data->out_file, 1) == -1)
		return (close(data->out_file), ft_print_err("An err with dup2"), NULL);
	if (dup2(data->fd[0], 0) == -1)
	{
		close(data->out_file);
		close(data->fd[0]);
		return (ft_print_err("An err occoured with dup2"), NULL);
	}
	close(data->fd[0]);
	cmd = ft_split(args[3], ' ');
	if (cmd == NULL || cmd[0] == NULL )
	{
		ft_print_err("We are here!");
		ft_free(cmd);
		return (NULL);
	}
	la_path = ft_check_path(cmd[0], env);
	close(data->out_file);
	if (execve(la_path, cmd, env) == -1) 
	{
		ft_free(cmd);
		free(la_path);
		ft_print_err("Command not found!");
		exit(1);
	}
	return (ft_free(cmd), free(la_path), la_path = NULL,
		ft_print_err("Command not found!"), NULL);
}
